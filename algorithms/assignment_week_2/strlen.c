#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s [some string]\n", argv[0]);
        return 1;
    }

    int idx = 0;
    while (argv[1][idx] != '\0')
        idx++;
    printf("size of string: %d\n", idx);

    return 0;
}
