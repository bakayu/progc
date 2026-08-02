#include <stdio.h>

int bitAnd(int x, int y) { return ~(~x | ~y); }

int main(void) {
    if (bitAnd(5, 6) == 4)
        printf("test case 1 passed.\n");
    if (bitAnd(0, 1) == 0)
        printf("test case 2 passed.\n");
    if (bitAnd(-1, 12) == 12)
        printf("test case 3 passed.\n");

    return 0;
}
