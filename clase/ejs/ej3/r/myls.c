#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
 void 
usage(const char *s)
{
	fprintf(stderr, "usage: %s\n", s);
	exit(EXIT_FAILURE);
}  void 

error_cant_open_dir(void)
{
	fprintf(stderr, "error: cant open dir\n");
	exit(EXIT_FAILURE);
 }  char *

what_type(mode_t mode)
{
	switch (mode & S_IFMT) {
	case S_IFDIR:
		return "d";
	case S_IFREG:
		return "f";
	case S_IFLNK:
		return "l";
	default:
		return "o";
	}
}

 void 
error_lstat(const char *nombre)
{
	fprintf(stderr, "error: cannot stat %s\n", nombre);
}  int 

main(int argc, char **argv)
{
	char *path = ".";

	DIR * d;
	struct dirent *ent;
	struct stat statbuf;

	 if (argc != 1) {
		usage(argv[0]);
	}
	 d = opendir(path);
	if (d == NULL) {
		error_cant_open_dir();
	}
	 while ((ent = readdir(d)) != NULL) {
		if ((lstat(ent->d_name, &statbuf)) == -1) {
			error_lstat(ent->d_name);
			continue;
		}
		 printf("%s\t%d\t%d\t%ld\t\t%s\n", what_type(statbuf.st_mode),
			  statbuf.st_uid, statbuf.st_gid, statbuf.st_size,
			  ent->d_name);
	}
	closedir(d);
	return 0;
}
