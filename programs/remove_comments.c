#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 1

void removeComments(int fd) {
    int in_single_comment = 0;
    int in_multi_comment = 0;
    int in_string = 0;
    int in_char = 0;

    char ch, next;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, &ch, 1)) > 0) {
        if ((in_string || in_char) && ch == '\\') {
            write(1, &ch, 1);
            if (read(fd, &next, 1) > 0) {
                write(1, &next, 1);
            }
            continue;
        }

        if (!in_single_comment && !in_multi_comment && !in_char && ch == '"') {
            in_string = !in_string;
            write(1, &ch, 1);
            continue;
        }

        if (!in_single_comment && !in_multi_comment && !in_string &&
            ch == '\'') {
            in_char = !in_char;
            write(1, &ch, 1);
            continue;
        }

        if (in_string || in_char) {
            write(1, &ch, 1);
            continue;
        }

        if (in_single_comment) {
            if (ch == '\n') {
                in_single_comment = 0;
                write(1, &ch, 1);
            }
            continue;
        }

        if (in_multi_comment) {
            if (ch == '*') {
                if (read(fd, &next, 1) > 0) {
                    if (next == '/') {
                        in_multi_comment = 0;
                    } else {
                        lseek(fd, -1, SEEK_CUR);
                    }
                }
            }
            continue;
        }

        if (ch == '/') {
            if (read(fd, &next, 1) > 0) {
                if (next == '/') {
                    in_single_comment = 1;
                    continue;
                } else if (next == '*') {
                    in_multi_comment = 1;
                    continue;
                } else {
                    lseek(fd, -1, SEEK_CUR);
                }
            }
        }

        write(1, &ch, 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s <filename.c>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    removeComments(fd);

    close(fd);
    return 0;
}
