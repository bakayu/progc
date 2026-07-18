#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void url_encode(char *str, int true_length) {
    int space_count = 0;
    for (int i = 0; i < true_length; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    int index = true_length + space_count * 2;
    str[index] = '\0';

    for (int i = true_length - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            str[index - 1] = '0';
            str[index - 2] = '2';
            str[index - 3] = '%';
            index -= 3;
        } else {
            str[index - 1] = str[i];
            index--;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s [string]\n", argv[0]);
        return 1;
    }

    int true_length = my_strlen(argv[1]);

    char *buffer = (char *)malloc(true_length * 3 + 1);
    if (!buffer) {
        return 1;
    }

    for (int i = 0; i < true_length; i++) {
        buffer[i] = argv[1][i];
    }
    buffer[true_length] = '\0';

    url_encode(buffer, true_length);
    printf("Output: %s\n", buffer);

    free(buffer);
    return 0;
}
