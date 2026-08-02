#include <stdio.h>

int sign(int x) { return (x >> 31) | (!!x); }

int main(void) {
    if (sign(130) == 1)
        printf("test case 1 passed.\n");
    if (sign(-13) == -1)
        printf("test case 2 passed.\n");
    if (sign(0) == 0)
        printf("test case 3 passed.\n");
    return 0;
}
