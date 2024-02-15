#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

typedef struct
{
  char *name;
  (void)(*pfunction)(char**);
} Function;

typedef struct
{
  Function map[256];
} Hashmap;

Hashmap *gen_hashmap();

//Checks if in hashmap and if not returns 0, if executed returns 1
int search_and_execute(char *name);


//Handles signals like interruptions etc.
void signalhandler(int sig);


//Change Directory
void cd(char *args[]);
// If you do cd ../.. It appends them to prompt instead of removing files
//Subfunction of cd for reversal
char *cd_back(void);


//Lists items inside directory
void dir(char *args[]);
//To do: Add option of flags to do long list or recursive

// Handles execution of scripts or C files etc.
void execute_file(char *args[]);

//Gets prompt
char *getprompt(void);

//Lists enviroment variables
extern char **environ;





void execute_file(char *args[]) {

          pid_t pid = fork();

	  if (pid < 0) {
            printf("Your fork failed you lose you're nothing\n");
	  }
	  if (pid == 0){
	    execvp(args[0], &args[1]);
          }
	  else {
            wait(NULL);
	    kill(pid, SIGKILL);
	  }
}

char *getprompt(void)
{
  char *user = getenv("USER");
  char *path = strstr(getenv("PWD"), getenv("HOME")) + strlen("HOME") + 2;
  char *indicator = ">";

  char *prompt = malloc(sizeof(char) * strlen(user) + strlen(path) + strlen(indicator) + 2);

  sprintf(prompt, "%s ~%s\n%s", user, path, indicator);

  return prompt;
}

void cd(char *args[])
{
  char *dir;
  if (args[1])
  {
    dir = (char*)malloc(strlen(getenv("PWD")) + strlen(args[1]) + 2);

    if (!strcmp(args[1], ".."))
    {
      dir = cd_back();
    }
    else if (!strcmp(args[1], "."))
    {
      sprintf(dir, "%s", getenv("PWD"));
    }

    else
    {
      sprintf(dir, "%s/%s", getenv("PWD"), args[1]);
    }
  }
  else
  {
    dir = getenv("HOME");
  }
  if (chdir(dir) || setenv("PWD", dir, 1)){
    printf("You failed you lose you're nothing!\n");
  }
}

char *cd_back() {
  char *copy = strdup(getenv("PWD"));

  char *finalPos = strrchr(copy, '/');
  if (finalPos != copy) {  //Ensure not root directory
    *finalPos = '\0';
  } else {
    *(finalPos + 1) = '\0';
  }
  return copy;

}

void dir(char *args[]) {
  if (args[1]) {
    char *directory_name = (char *)malloc(sizeof(char) * strlen(getenv("PWD")) + 10);

    if (directory_name == NULL) {
      printf("malloc failed in dir function\n");
    }

    sprintf(directory_name, "./%s", args[1]);
    DIR* pdir = opendir(directory_name);
    free(directory_name);

    if (dir == NULL) {
      printf("You failed youre a loser youre nothing");
    }

    struct dirent *entity;
    entity = readdir(pdir);

    while (entity != NULL) {
      printf("%s\n", entity->d_name);
      entity =readdir(pdir);
    }
    closedir(pdir);
  }
  else {
    DIR *pdir = opendir(".");
    struct dirent *entity;
    entity = readdir(pdir);
    while (entity != NULL){
    printf("%s\n", entity->d_name);

    entity = readdir(pdir);
      /*
      Recursive???

      if (entity->d_type == DT_DIR) {
        ;
      }
      */
    }
  }
}

void signalhandler(int sig)
{
  if (sig == 2) printf("Noooo come backkk dont sigint mee\n");
  exit(1);
}

Hashmap *gen_hashmap() {
  Hashmap *hm = (Hashmap *)malloc(sizeof(Hashmap));

  hm->map = malloc(sizeof(Function) * 256);

  void(*shell_functions[])(char*) = {cd, dir};
  char *string_functions = {"cd", "dir"};


  int i = 0;
  while (i < sizeof(string_functions)/ sizeof(string_functionds[0])) {
    hm->map[ gen_hashvalue(string_functions[i]) ] = gen_function(shell_functions[i], string_functions[i]);
  }
  return map;
}

int gen_hashvalue(char *fName) {
  int hash = 0;
  int i = 0;
  while (i < strlen(fName)) {
    hash += *fName[i];
    i++
  }
  return (hash % 256);
}


/*
int search_and_execute(char *fName) {

  hm->map[gen_hashvalue(char *fName)]->pfunction();

  Must be refined to make sure function is in hash map first and return 0 if not.

  if not in hashmap:

    our execute thing

}
*/


