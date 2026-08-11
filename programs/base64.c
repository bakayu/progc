#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void encode(char *input, int size);
void decode();

static const char BASE64_TABLE[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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
        decode();
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

// TODO: Implement decode
void decode() { printf("decode not implemented yet\n"); };
