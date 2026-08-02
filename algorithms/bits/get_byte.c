#include <stdio.h>

int getByte(int x, int n) { return (x >> (n << 3)) & 0xFF; }

int main(void) {
    if (getByte(0x12345678, 0) == 0x78)
        printf("test case 1 passed.\n");
    if (getByte(0x12345678, 2) == 0x34)
        printf("test case 2 passed.\n");
    if (getByte(0x12345678, 1) == 0x56)
        printf("test case 3 passed.\n");
    return 0;
}
