#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    size_t len;
    off_t offset;
    int fd;
    char *buf;
    size_t numRead, numWritten;

    if (argc < 3) {
        char usage[] =
            "Usage: ./seek <file> {r<length>|w<string>|s<offset>}...\n";
        write(2, usage, sizeof(usage));
        exit(-1);
    }

    fd = open(argv[1], O_RDWR | O_CREAT,
              S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH);

    if (fd == -1) {
        printf("Failed to open file.\n");
        exit(-1);
    }

    for (int i = 2; i < argc; i++) {
        switch (argv[i][0]) {
        case 'r':
            len = atoi(&argv[i][1]);
            buf = malloc(len);

            numRead = read(fd, buf, len);
            if (numRead == 0) {
                free(buf);
                printf("Error: EOF reached.\n");
                exit(-1);
            }

            for (int j = 0; j < len; j++) {
                printf("%c", buf[j]);
            }
            printf("\n");

            free(buf);
            break;

        case 'w':
            numWritten = write(fd, &argv[i][1], strlen(&argv[i][1]));
            printf("Written: %ld bytes to %s\n", numWritten, argv[1]);

            break;

        case 's':
            offset = atoi(&argv[i][1]);
            if (lseek(fd, offset, SEEK_CUR) == -1) {
                printf("Seek failed\n");
                exit(-1);
            }
            printf("Seek succeeded\n");

            break;

        default:
            printf("Error: arguments must be one of [rws]\n");
            break;
        }
    }

    exit(EXIT_SUCCESS);
}
