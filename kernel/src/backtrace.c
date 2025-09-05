#include "backtrace.h"
#include "asm/x86.h"
#include "stdio.h"

int
backtrace() {
    int* ebp;
    read_ebp(ebp);
    cprintf("Backtrace:\n");
    cprintf("   0x%x\n", *(ebp+4)); // go 4 bytes into the stack frame for the return address
    return 0;
}