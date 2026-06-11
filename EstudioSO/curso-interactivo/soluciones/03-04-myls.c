#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    char path[PATH_MAX];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <directorio>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "error: no se puede abrir el directorio '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
        if (stat(path, &sb) < 0) {
            printf("[UNKNOWN]  %s\n", entry->d_name);
            continue;
        }
        if (S_ISDIR(sb.st_mode))
            printf("[DIR]  %s\n", entry->d_name);
        else if (S_ISREG(sb.st_mode))
            printf("[FILE] %s\n", entry->d_name);
        else
            printf("[OTHER] %s\n", entry->d_name);
    }

    closedir(dir);
    exit(EXIT_SUCCESS);
}
