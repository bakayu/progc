#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void encode(char *input, int size);
void decode(char *input, int size);

static const char BASE64_TABLE[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int base64_reverse[256];

/*
USAGE: ./base64 [-d] <String>

For encoding:

$ ./base64 Man
TWFu

...
For decoding:

$ ./base64 -d TWFu
Man

*/
int main(int argc, char *argv[]) {
    int opt;
    int decode_flag = 0;

    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
        case 'd':
            decode_flag = 1;
            break;
        default:
            fprintf(stderr, "USAGE: %s [-d] <string>\n", argv[0]);
            exit(-1);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "USAGE: %s [-d] <string>\n", argv[0]);
        exit(-1);
    }

    if (!decode_flag) {
        encode(argv[optind], strlen(argv[optind]));
    } else {
        decode(argv[optind], strlen(argv[optind]));
    };

    return 0;
}

void encode(char *input, int size) {
    for (int i = 0; i < size; i += 3) {
        unsigned char b0 = input[i];
        unsigned char b1 = (i + 1 < size) ? input[i + 1] : 0;
        unsigned char b2 = (i + 2 < size) ? input[i + 2] : 0;

        char c1 = BASE64_TABLE[b0 >> 2];
        char c2 = BASE64_TABLE[((b0 & 0x03) << 4) | (b1 >> 4)];
        char c3 = BASE64_TABLE[((b1 & 0x0F) << 2) | (b2 >> 6)];
        char c4 = BASE64_TABLE[b2 & 0x3F];

        printf("%c%c%c%c", c1, c2, (i + 1 < size) ? c3 : '=',
               (i + 2 < size) ? c4 : '=');
    }
    printf("\n");
}

void decode(char *input, int size) {
    for (int i = 0; i < 256; i++) {
        base64_reverse[i] = -1;
    }
    for (int i = 0; i < 64; i++) {
        base64_reverse[(unsigned char)BASE64_TABLE[i]] = i;
    }

    for (int i = 0; i < size; i += 4) {
        int v1 = base64_reverse[(unsigned char)input[i]];
        int v2 = base64_reverse[(unsigned char)input[i + 1]];
        int v3 = base64_reverse[(unsigned char)input[i + 2]];
        int v4 = base64_reverse[(unsigned char)input[i + 3]];

        char b0 = (v1 << 2) | (v2 >> 4);
        char b1 = ((v2 & 0x0F) << 4) | (v3 >> 2);
        char b2 = ((v3 & 0x03) << 6) | v4;

        printf("%c", b0);
        if (input[i + 2] != '=')
            printf("%c", b1);
        if (input[i + 3] != '=')
            printf("%c", b2);
    }
    printf("\n");
};
