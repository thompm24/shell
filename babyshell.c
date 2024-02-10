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


void cd(char *args[]);
char *getpath(void);
extern char **environ;

int main(int argc, char **argv) {
  //SIGNAL HERE FOR INTERRUPTION
  char buf[MAX_BUFFER];
  char *args[MAX_ARGS];
  char **arg;
  printf("\033[2J\033[H"); 
  printf("    **************************\n"
         "    *        MY SHELL        *\n"
         "    *                        *\n"
         "    *         use at         *\n"
         "    *        own risk        *\n"
         "    *                        *\n"
         "    **************************\n"
  );



  while(!feof(stdin)){
    char *prompt  = getpath();
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
          printf("You failed youre a loser youre nothing");
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
      cd(args);
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



char *getpath(void) {
  char *user = strtok(getenv("USER"), "=");
  char *delim = (char *)malloc(6 + strlen(user) + 2);
  sprintf(delim, "/home/%s", user);
  char *path = strstr(getenv("PWD"), delim) + strlen(delim);
  char *prompt = (char *)malloc(sizeof(char) * 70);
  sprintf(prompt,"%s ~%s\n[} ", user, path);

  return prompt;
}

void cd(char *args[]) {
  char *dir;
  if (args[1]){
    dir = (char*)malloc(strlen(getenv("PWD")) + strlen(args[1]) + 2);

    if (!strcmp(args[1], "..")) {

      char *copy = strdup(getenv("PWD"));

      char *finalPos = strrchr(copy, '/');
      if (finalPos != copy) {  //Ensure not root directory
        *finalPos = '\0';
      } else {
        *(finalPos + 1) = '\0';
      }
      dir = copy;
    }

    else if (!strcmp(args[1], ".")) {
      sprintf(dir, "%s", strtok(getenv("PWD"), "="));
    }

    else {
      sprintf(dir, "%s/%s", strtok(getenv("PWD"), "="), args[1]);
    }
  }
  else {
    dir = getenv("HOME");
  }
  if (chdir(dir) || setenv("PWD", dir, 1)){
    printf("You failed you lose you're nothing!\n");
  }
}
