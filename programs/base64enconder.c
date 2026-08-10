#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void char_to_binary(unsigned char ch, char *out) {
    for (int i = 0; i < 8; i++) {
        out[i] = (ch & (1 << (7 - i))) ? '1' : '0';
    }
    out[8] = '\0';
}

void copy_at(char *in, char *out, int size, int at) {
    for (int i = 0; i < size; i++) {
        out[at + i] = in[i];
    }
}

int binary_to_int(char *bits, int size) {
    int res = 0;
    for (int i = 0; i < size; i++) {
        res = (res << 1) + (bits[i] - '0' ? 1 : 0);
    }

    return res;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s <STRING>\n", argv[0]);
        exit(-1);
    }

    char BUFFER[9];
    char OUT[(strlen(argv[1]) * 8) + 1];
    int index = 0;
    const char BASE64_TABLE[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (int i = 0; argv[1][i] != '\0'; i++) {
        char_to_binary(argv[1][i], BUFFER);
        printf("%c -> %s\n", argv[1][i], BUFFER);
        copy_at(BUFFER, OUT, 8, index);
        index += 8;
    }
    OUT[index] = '\0';

    int out_size = strlen(OUT);
    for (int i = 0; i < out_size; i += 6) {
        int remaining_bits = out_size - i;
        if (remaining_bits >= 6) {
            int bits = binary_to_int(OUT + i, 6);
            printf("%c", BASE64_TABLE[bits]);
        } else {
            char temp[7];
            for (int idx = 0; idx < 6; idx++)
                temp[idx] = '0';
            temp[6] = '\0';
            for (int j = i; j < remaining_bits + i; j++) {
                temp[j - i] = OUT[j];
            }

            int bits = binary_to_int(temp, 6);
            printf("%c", BASE64_TABLE[bits]);
            if (remaining_bits == 2) {
                printf("==");
            } else {
                printf("=");
            }
        }
    }
    printf("\n");

    return 0;
}
