#include "types.h"
#include "user.h"

int
main()
{
    printf(1, "Sizeof int: %d\n", sizeof(int));
    printf(1, "Sizeof uint: %d\n", sizeof(uint));
    printf(1, "Sizeof short: %d\n", sizeof(short));
    printf(1, "Sizeof long: %d\n", sizeof(long));
    printf(1, "Sizeof dll: %d\n", sizeof(long long));
    //backtrace();
    exit();
}