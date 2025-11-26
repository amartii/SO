#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>
 int 
main(int argc, char **argv)  {  int args = argc - 1;
	 int status;
	 int i;
	 int exit_code;

	  pid_t pid;
	  if ((args % 2) != 0 || args == 0) {
		 fprintf(stderr, "error: bad number of arguments\n");
		 return EXIT_FAILURE;
	 }
	  for (i = 1; i < args; i += 2) {
		 pid = fork();
		 if (pid < 0) {
			 perror("error: fork ");
			 exit(EXIT_FAILURE);
		 }
		  if (pid == 0) {
			 execl("/usr/bin/fgrep", "fgrep", argv[i + 1],
				 argv[i], (char *)NULL);
			 perror("error: execl");
			 exit(EXIT_FAILURE);
		 }
	 }  while ((pid = wait(&status)) != -1) {
		 if (WIFEXITED(status)) {
			 exit_code = WEXITSTATUS(status);
			 if (exit_code > 1) {
				 fprintf(stderr,
					   "error: child %d exited with error %d\n",
					   pid, exit_code);
				 exit(EXIT_FAILURE);
			 }
		  } else {
			 fprintf(stderr,
				   "error: child %d did not exit normally\n",
				   pid);
			 exit(EXIT_FAILURE);
		 }
	  }
	  exit(EXIT_SUCCESS);
 }


