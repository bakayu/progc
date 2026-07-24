#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode))
        printf("Regular File\n");
    else if (S_ISDIR(mode))
        printf("Directory\n");
    else if (S_ISLNK(mode))
        printf("Symbolic Link\n");
    else if (S_ISCHR(mode))
        printf("Character Device\n");
    else if (S_ISBLK(mode))
        printf("Block Device\n");
    else if (S_ISFIFO(mode))
        printf("FIFO\n");
    else if (S_ISSOCK(mode))
        printf("Unix Socket\n");
    else
        printf("Unknown\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: ./%s <PATH>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (lstat(argv[1], &st) < 0) {
        perror(argv[1]);
        return 1;
    }

    printf("=== File Attributes for: %s ===\n", argv[1]);
    printf("File Type:\t\t");
    print_file_type(st.st_mode);
    printf("Permissions:\t\t%d\n", st.st_mode & 0777);
    printf("File Size:\t\t%ld\n", (long)st.st_size);
    printf("Hard Links Count:\t%lu\n", (unsigned long)st.st_nlink);
    printf("Owner (UID):\t\t%d\n", st.st_uid);
    printf("Group (GID):\t\t%d\n", st.st_gid);
    char *atime_str = ctime(&st.st_atime);
    char *mtime_str = ctime(&st.st_mtime);
    char *ctime_str = ctime(&st.st_ctime);

    if (atime_str)
        printf("Last Access Time:\t%.24s\n", atime_str);
    if (mtime_str)
        printf("Last Modification:\t%.24s\n", mtime_str);
    if (ctime_str)
        printf("Status Change Time:\t%.24s\n", ctime_str);
    return 0;
}
