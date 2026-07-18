#include <stdio.h>

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void reverse_string(char *str) {
    int start = 0;
    int end = my_strlen(str) - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s [some string]\n", argv[0]);
        return 1;
    }

    reverse_string(argv[1]);
    printf("Reversed string: %s\n", argv[1]);

    return 0;
}
