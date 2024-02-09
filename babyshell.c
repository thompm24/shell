#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define SEPARATORS " \t\n"

/*
I want one thread always taking input

when a function is called, it should be done in a new thread, and input taker should wait on it to finish.

when a | is used, the function called should fork and pipe info from one to another.


*/


/*
TO DO:
READ ABOUT STRDUP STRTOK

LEARN TO RUN FUNCTION AS SEPARATE THREAD




*/




extern char **environ;

int main(int argc, char **argv) {
  //SIGNAL HERE FOR INTERRUPTION
  char buf[MAX_BUFFER];
  char *args[MAX_ARGS];
  char **arg;
  char *prompt = "[}";


  while(!feof(stdin)){
    printf ("%s", prompt);
    if (fgets(buf, MAX_BUFFER, stdin)) {
	arg = args;
	*arg++ = strtok(buf, SEPARATORS);

	while ((*arg++ = strtok(NULL, SEPARATORS)));

	if (args[0]) {
	  if (!strcmp(args[0], "clr")) {
            system("clear");
	    continue;
	  }
	  if (!strcmp(args[0], "quit")) {
            break;
	  }
	  if (!strcmp(args[0], "dir")) {
            if (args[1]) {
              int i = 1;
	      while (args[i]) {
	        char *str = (char *)malloc(sizeof(char) * 40);
	        sprintf(str, "ls -al %s", args[i]);
                system(str);
		i++;
	      }
	    }
	    else {
	      system("ls -al .");
	    }
	    continue;
	  }
          if (!strcmp(args[0], "environ")) {
            for (char **env = environ; *env != NULL; env++) {
              printf("%s\n", *env);
	    }
	    continue;
	  }
	}
    }
  }
}
