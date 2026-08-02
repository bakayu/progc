#include <stdio.h>

int conditional(int x, int y, int z) {
    int mask = (!!x << 31) >> 31;
    return mask & y | ~mask & z;
}

int main(void) {
    if (conditional(1, 2, 3) == 2)
        printf("test case 1 passed.\n");
    if (conditional(0, 1, 2) == 2)
        printf("test case 2 passed.\n");
    if (conditional(-1, 0, 1) == 0)
        printf("test case 3 passed.\n");

    return 0;
}
