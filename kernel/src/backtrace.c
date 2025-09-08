#include "backtrace.h"
#include "asm/x86.h"
#include "stdio.h"
#include "stab.h"

int
backtrace() {
    
    uint* ebp; 
    read_ebp(ebp);

    int staberr = 0; // This will catch if stab fails.
    int eip; // We will need to set this via the return addresses.
    struct stab_info info; // Sets struct to 0 without make complaining

    // follow back through ebps
    cprintf("Backtrace:\n");
    while (!staberr && *ebp > 0xF00) {
        // First need to get the return address by dereferencing to the address that ebp points to, then index the next word and dereference to get the return address
        eip = *(ebp + 1); // Indexes the next word after ebp, and then reads the value from it
        // eip is the return address within the previous function.

        // Update ebp so we don't need to worry about this anymore
        ebp = (uint *) *ebp;

        // get stab information
        staberr = stab_info(eip, &info);
        if (staberr) // stab_info returns 0 if no errors, this will catch any stab_info errors.
        {
            cprintf("stab_info call failed.\n");
            return -1; // can't actually exit from kernel, so will pass -1 if backtrace fails.
        }

        // print backtrace line (strncpy wasn't working for the string so had to make an array)
        const int fname_len = info.eip_fn_namelen + 1;
        char fname[fname_len];
        for (int i = 0; i < info.eip_fn_namelen; i++) {
            fname[i] = info.eip_fn_name[i];
        }
        fname[info.eip_fn_namelen] = 0;
        cprintf("   <0x%x> ", eip);
        cprintf("%s", &fname);
        cprintf("+%d\n", eip - info.eip_fn_addr);
    }
    return 0;
}