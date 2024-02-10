#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

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

MAKE COMPRESSION ALGORITHM SQUISH SQUASH DESQISH DESQUASH

DISPLAY IMAGES WITH OPENGL??????????
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
    /*
    / Add recursive dir (CodeVault video)
    / Make it optional to print hidden directorys (check for .
    */

      if (args[1]) {

        char *directory_name = (char *)malloc(sizeof(char) * 40);
        sprintf(directory_name, "./%s", argv[1]);
        DIR* dir = opendir(directory_name);
        if (dir == NULL) {
          printf("You failed ypure a lopser youre nothing");
        }
        
        struct dirent *entity;

        entity = readdir(dir);
        while (entity != NULL) {
          printf("%s\n", entity->d_name);
          entity =readdir(dir);
        }

        closedir(dir);
	    }
      else {
        DIR *dir = opendir(".");
        struct dirent *entity;
        entity = readdir(dir);
        while (entity != NULL){
          printf("%s\n", entity->d_name);
          entity = readdir(dir);
        }
      }
	    continue;
	  }
    if (!strcmp(args[0], "cd")) {
        /*
        / This needs to be fixed
        */
        char *dir = (char*)malloc(strlen(getenv("PWD")) + strlen(args[1]) + 2);
        sprintf(dir, "%s/%s", strtok(getenv("PWD"), "="), args[1]);
        setenv("PWD", dir, 1);


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
