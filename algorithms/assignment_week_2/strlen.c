#include <stdio.h>

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s [some string]\n", argv[0]);
        return 1;
    }

    int idx = my_strlen(argv[1]);
    printf("size of string: %d\n", idx);

    return 0;
}
