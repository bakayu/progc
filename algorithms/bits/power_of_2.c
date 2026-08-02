#include <stdio.h>

int isPower2(int x) { return !(x >> 31) & !!x & !(x & (x + ~0)); }

int main(void) {
    if (isPower2(5) == 0)
        printf("test case 1 passed.\n");
    if (isPower2(8) == 1)
        printf("test case 2 passed.\n");
    if (isPower2(0) == 0)
        printf("test case 3 passed.\n");
    if (isPower2(0x80000000) == 0)
        printf("test case 4 passed.\n");
    return 0;
}
