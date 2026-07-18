#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s [command separated words: C,Rust,Go,Java]\n",
                argv[0]);
        return 1;
    }
    char *token = strtok(argv[1], ",");

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
