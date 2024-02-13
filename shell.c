#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>


void signalhandler(int sig);
void cd(char *args[]);
void dir(char *args[]);

void execute_file(char *args[]);

char *getprompt(void);
char *cd_back(void);
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