#include <stdio.h>

/*
left == right :  0
left > right  :  1
left < right  : -1
*/
int cmpInt(void *left, void *right) {
    if (*(int *)left == *(int *)right)
        return 0;
    return *(int *)left > *(int *)right ? 1 : -1;
}

int main(void) {
    int a = -2, b = 2;
    int (*cmp)(void *, void *) = cmpInt;
    printf("%d\n", cmp(&a, &b));
}
