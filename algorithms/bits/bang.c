#include <stdio.h>

int bang(int x) { return (((~x + 1) | x) >> 31) + 1; }

int main(void) {
    if (bang(5) == 0)
        printf("test case 1 passed.\n");
    if (bang(-4) == 0)
        printf("test case 2 passed.\n");
    if (bang(0) == 1)
        printf("test case 3 passed.\n");
    if (bang(0x80000000) == 0)
        printf("test case 4 passed.\n");
    return 0;
}
