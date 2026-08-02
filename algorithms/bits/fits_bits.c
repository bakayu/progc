#include <stdio.h>

int fitsBits(int x, int n) { return !((x >> (n + (~0))) ^ (x >> 31)); }

int main(void) {
    if (fitsBits(5, 3) == 0)
        printf("test case 1 passed.\n");
    if (fitsBits(-4, 3) == 1)
        printf("test case 2 passed.\n");
    if (fitsBits(3, 3) == 1)
        printf("test case 3 passed.\n");
    return 0;
}
