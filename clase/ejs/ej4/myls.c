#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void
usage(const char *s){
    fprintf(stderr, "usage: %s [directory]\n", s);
    exit(EXIT_FAILURE);
}

void
error_cant_open_dir(void){
    fprintf(stderr, "error: cant open dir\n");
    exit(EXIT_FAILURE);

}

int
main(int argc, char **argv){
    char *path = ".";
    DIR *d;
    struct dirent *ent;
    struct stat statbuf;
    char *type;

    if (argc > 2){
        usage(argv[0]);
    }

    if (argc == 2){
        path = argv[1];
    }
    d = opendir(path);

    if (d == NULL){
        error_cant_open_dir();
    }

    while ((ent =readdir(d)) != NULL){
        //controlar que si me da -1 sea error de lstat
        lstat(ent ->d_name, &statbuf); //enlaces simbólicos es obligatorio lstat

        switch(statbuf.st_mode & S_IFMT){
            //dir "d"
            case S_IFDIR: type = "d";
                break;
            //fich "f"
            case S_IFCHR: type = "f";
                break;
            //enl simb "l"
            case S_IFLNK: type = "l"; //revisar por que tiene qe ser con lstat
                break;
            //otro caso "o"
            default:      type = "o";
                break;
        }

       

        printf("%s %d %d %ld %s\n", type, statbuf.st_uid, statbuf.st_gid, statbuf.st_size, ent -> d_name);
    }
    closedir(d);
    return 0;
}