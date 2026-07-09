#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define logFile "app.log"

// print usage help to stdout and exit with -1
void printUsage() {

    char usage[] =
        "Usage: \t./auditlog --add \"YOUR LOG HERE\"\n\t./auditlog --view\n";
    write(1, usage, sizeof(usage));
    exit(-1);
}

// exit with errors provided by errno
void exitWithErr() {
    write(2, "Error: ", 7);
    write(2, strerror(errno), strlen(strerror(errno)));
    write(2, "\n", 1);
    exit(-1);
}

// write an Integer value to stdout
void writeInt(int num) {
    char digit[12];
    int idx = 0;

    if (num == 0) {
        if (write(1, "0", 1) == -1) {
            exitWithErr();
        }
        return;
    }

    while (num > 0) {
        digit[idx++] = (num % 10) + '0';
        num /= 10;
    }

    while (idx > 0) {
        if (write(1, &digit[--idx], 1) == -1) {
            exitWithErr();
        }
    }
}

int main(int argc, char *argv[]) {
    int appLogFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc < 2 || argc > 3) {
        printUsage();
    }

    if (argc == 2) {
        if (strcmp(argv[1], "--view") != 0) {
            printUsage();
        }

        // handle reading
        appLogFd = open(logFile, O_RDONLY);
        if (appLogFd == -1) {
            exitWithErr();
        }

        int lineNum = 1;
        int newLine = 1;
        while ((numRead = read(appLogFd, buf, BUF_SIZE)) > 0) {
            for (ssize_t i = 0; i < numRead; i++) {
                if (newLine) {
                    writeInt(lineNum++);
                    if (write(1, ": ", 2) == -1) {
                        exitWithErr();
                    };
                    newLine = 0;
                }

                if (write(1, &buf[i], 1) == -1) {
                    exitWithErr();
                }

                if (buf[i] == '\n')
                    newLine = 1;
            }
        }

        close(appLogFd);
        return 0;
    }

    if (strcmp(argv[1], "--add") != 0) {
        printUsage();
    }

    // handle adding
    openFlags = O_CREAT | O_WRONLY | O_APPEND;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // rw-r--r-- : 644
    appLogFd = open(logFile, openFlags, filePerms);

    if (appLogFd == -1) {
        exitWithErr();
    }

    if (write(appLogFd, argv[2], strlen(argv[2])) == -1) {
        exitWithErr();
    }

    // add a newline character
    if (write(appLogFd, "\n", 1) == -1) {
        exitWithErr();
    }

    close(appLogFd);
    return 0;
}
