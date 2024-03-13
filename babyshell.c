#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shell.h"

#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define SEPARATORS " \t\n"


/*
   TO DO:
   I/O REDIRECTION
       dup2 implmentation
       refactor args after removion something for i/o like ><&>>


   ERROR CHECK EVERYTHING, MALLOC, FOPENS ETC.
   MANUAL

   MAKEFILE

   Peer reviewed sources


IF EXTRA TIME:
   OPTIONS FOR LONG LS AND RECURISVE

   ADD PIPE AND GREP

   SEND HTTP REQUESTS?

   MAKE COMPRESSION ALGORITHM SQUISH SQUASH DESQISH DESQUASH

   DISPLAY IMAGES WITH OPENGL?????????? who knows



  DONE:
  FUNCTIONS:

   PUT POINTERS TO FUNCTIONS IN A HASH MAP AND CALL THEM THAT WAY, ALL ARE (void)(*pfunction)(char**)

   BATCHFILE EXECUTION:
     ./baby full_of_commands.txt


   ../../.. APPENDS TO CWD PART OF PROMPT?

   ADD & TO MAKE BACKGROUND PROCESS

    CD, DIR, LS, ENVIRON AND EXECUTE FILES IN SEPARATE PROCESS

    FIXED ISSUE WITH CHILD PROCESS READING MAIN BY MAKING HEADER FILE TO CONTAIN FORK

    DYNAMIC PROMPT
*/


//////////////////////////////////////////////////////////////////
int get_argc(char **args) {
  int length = 0;
  while (args[length] != NULL)
  {
    length++;
  }
  return length;
}

int redirect_output_truncate(char *file_name)
{
  int redirect_fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
  if (redirect_fd == -1) {
    printf("Error encountered trying to open '%s'\n", file_name);
  }
  if (dup2(redirect_fd, STDOUT_FILENO) == -1)
  {
    printf("Error encountered trying to redirect standard output\n");
  }
  close(redirect_fd);
}

int redirect_output_append(char *file_name)
{
  int redirect_fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
  if (redirect_fd == -1) {
    printf("Error encountered trying to open '%s'\n", file_name);
  }
  if (dup2(redirect_fd, STDOUT_FILENO) == -1)
  {
    printf("Failed redirecting standard output\n");
  }
  close(redirect_fd);
}



int redirect_input(char *file_name)
{
  int redirect_fd = open(file_name, O_RDONLY, 0777);
  if (redirect_fd == -1) {
    printf("Error encountered trying to open '%s'\n", file_name);
  }
  if (dup2(redirect_fd, STDIN_FILENO) == -1)
  {
    printf("Error redirecting standard input");
  }
  close(redirect_fd);
}

int check_redirection(char **args, int length) {
  int i = 0;
  while (i < length - 1)	//length - 1 because we only want to run these functions if there is a file name after character.
  {
    if (!strcmp(args[i], ">"))
    {
      redirect_output_truncate(args[i + 1]);
    }
    if (!strcmp(args[i], ">>"))
    {
      redirect_output_append(args[i + 1]);
    }
    if (!strcmp(args[i], "<"))
    {
      redirect_input(args[i + 1]);
    }
    i++;
  }
}


int restore_io(int og_in, int og_out)
{
  dup2(og_in, STDIN_FILENO);
  close(og_in);
  dup2(og_out, STDOUT_FILENO);
  close(og_out);
}

//////////////////////////////////////////////




int main(int argc, char **argv) {

  signal(SIGINT, signalhandler);
  BST *tree = gen_bst();


  char buf[MAX_BUFFER];
  char *args[MAX_ARGS];
  char **arg;

  int original_stdout = dup(STDOUT_FILENO);
  int original_stdin = dup(STDIN_FILENO);

  FILE *fptr;
  if (argv[1]) {
    fptr = fopen(argv[1], "r");
  }
  else {
    fptr = stdin;
  }


  if (fptr == stdin) {
  printf("\033[2J\033[H");
  printf("    **************************\n"
    	 "    *        MY SHELL        *\n"
    	 "    *                        *\n"
    	 "    *         use at         *\n"
    	 "    *        own risk        *\n"
    	 "    *                        *\n"
    	 "    **************************\n\n\n"
        );
  }


  while(!feof(fptr))
  {
    if (fptr == stdin)
    {
      printf("%s", get_prompt());
    }
    if (fgets(buf, MAX_BUFFER, fptr))
    {
      if (strstr(buf, " &") != NULL) {
        execute_file(args, 0);
      }

      arg = args;
      *arg++ = strtok(buf, SEPARATORS);


      while ((*arg++ = strtok(NULL, SEPARATORS)));
      check_redirection(args, get_argc(args));

      if (!run(tree, args))
      {
        execute_file(args ,1);
      }
      restore_io(original_stdin, original_stdout);
      continue;
    }
  }
}
