#include <stdio.h>

int bitXor(int x, int y) { return ~(~x & ~y) & ~(x & y); }

int main(void) {
    if (bitXor(4, 5) == 1)
        printf("test case 1 passed.\n");
    if (bitXor(10, 10) == 0)
        printf("test case 2 passed.\n");
    if (bitXor(-1, 12) == -13)
        printf("test case 3 passed.\n");
    return 0;
}
