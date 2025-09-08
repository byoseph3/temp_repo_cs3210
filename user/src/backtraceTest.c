#include "types.h"
#include "user.h"

void b() {
    backtrace();
    return;
}

void a() {
    b();
    backtrace();
    return;
}

int
main()
{
    // printf(1, "Sizeof int: %d\n", sizeof(int));
    // printf(1, "Sizeof uint: %d\n", sizeof(uint));
    // printf(1, "Sizeof short: %d\n", sizeof(short));
    // printf(1, "Sizeof long: %d\n", sizeof(long));
    // printf(1, "Sizeof dll: %d\n", sizeof(long long));
    //a();
    //backtrace();

    // 0x80106be6 backtrace call in getpid
    getpid();
    exit();
}