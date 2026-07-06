#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int sourceFd, destFd, openFlags;
    mode_t filePerms;

    ssize_t numRead;

    char buf[BUF_SIZE];

    if (argc != 3) {
        printf("Usage: ./cp SOURCE DESTINATION\n");
        exit(-1);
    }

    sourceFd = open(argv[1], O_RDONLY);
    if (sourceFd == -1) {
        printf("Error: couldn't open file %s\n", argv[1]);
        exit(-1);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // rw-r--r-- : 644
    destFd = open(argv[2], openFlags, filePerms);

    if (destFd == -1) {
        printf("Error: couldn't open file %s\n", argv[2]);
        exit(-1);
    }

    while ((numRead = read(sourceFd, buf, BUF_SIZE)) > 0) {
        if (write(destFd, buf, numRead) != numRead) {
            printf("Error: couldn't copy SOURCE to DEST");
            exit(-1);
        }
    }

    close(sourceFd);
    close(destFd);

    return 0;
}
