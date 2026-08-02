#include <stdio.h>

int logicalShift(int x, int n) { return (x >> n) & ~(((1 << 31) >> n) << 1); }

int main(void) {
    if (logicalShift(0x87654321, 4) == 0x08765432)
        printf("test case 1 passed.\n");
    if (logicalShift(0x80000000, 0) == 0x80000000)
        printf("test case 2 passed.\n");
    if (logicalShift(0xFFFFFFFF, 31) == 0x00000001)
        printf("test case 3 passed.\n");

    return 0;
}
