#include <stdio.h>

int find_substring(const char *haystack, const char *needle) {
    if (needle[0] == '\0') {
        return 0;
    }

    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
            j++;
        }
        if (needle[j] == '\0') {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "USAGE: %s [haystack] [needle]\n", argv[0]);
        return 1;
    }

    int index = find_substring(argv[1], argv[2]);
    printf("Output: %d\n", index);

    return 0;
}
