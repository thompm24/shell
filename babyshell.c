#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define SEPARATORS " \t\n"


/*
   TO DO:
   I/O REDIRECTION

   ERROR CHECK EVERYTHING, MALLOC, FOPENS ETC.
   MANUAL

   MAKEFILE



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
  if (freopen(file_name, "w", stdout) != NULL)
  {
    return 1;
  }
  else
  {
    printf("output redirection failed\n");
    return 0;
  }
}

int redirect_output_append(char *file_name)
{
  if (freopen(file_name, "a", stdout) != NULL)
  {
    return 1;
  }
  else
  {
    printf("output redirection failed\n");
  }
}



int redirect_input(char *file_name)
{
  if (freopen(file_name, "r", stdin) != NULL)
  {
    return 1;
  }
  else
  {
    printf("input redirection failed\n");
  }
}

int check_redirection(char **args, int length) {
  int i = 0;
  while (i < length)
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


int restore_io(FILE *og_in, FILE *og_out, FILE *in, FILE *out)
{
  fclose(in);
  fclose(out);
  freopen(NULL, "r", og_in);
  freopen(NULL, "w", og_out);
}

//////////////////////////////////////////////




int main(int argc, char **argv) {

  signal(SIGINT, signalhandler);
  BST *tree = gen_bst();


  char buf[MAX_BUFFER];
  char *args[MAX_ARGS];
  char **arg;

  FILE *original_stdout = freopen(NULL, "w", stdout);
  FILE *original_stdin = freopen(NULL, "r", stdin);

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
    if (fptr == stdin) {
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

        if (!run(tree, args)) {
            execute_file(args ,1);
        }
	    continue;
	  }
      }

      restore_io(original_stdin, original_stdout, stdin, stdout);


}
