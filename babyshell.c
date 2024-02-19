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
   PUT POINTERS TO FUNCTIONS IN A HASH MAP AND CALL THEM THAT WAY, ALL ARE (void)(*pfunction)(char**)

   ../../.. APPENDS TO CWD PART OF PROMPT?

   ADD & TO MAKE BACKGROUND PROCESS

   I/O REDIRECTION

   ERROR CHECK EVERYTHING, MALLOC, FOPENS ETC.

   BATCHFILE EXECUTION:
     ./baby full_of_commands.txt

   MANUAL

   MAKEFILE


IF EXTRA TIME:
   OPTIONS FOR LONG LS AND RECURISVE

   ADD PIPE AND GREP

   SEND HTTP REQUESTS?

   MAKE COMPRESSION ALGORITHM SQUISH SQUASH DESQISH DESQUASH

   DISPLAY IMAGES WITH OPENGL?????????? who knows
*/

/*
  DONE:
  FUNCTIONS:

    CD, DIR, LS, ENVIRON AND EXECUTE FILES IN SEPARATE PROCESS

    FIXED ISSUE WITH CHILD PROCESS READING MAIN BY MAKING HEADER FILE TO CONTAIN FORK

    DYNAMIC PROMPT
*/






int main(int argc, char **argv) {

  signal(SIGINT, signalhandler);
  BST *tree = gen_bst();




  char buf[MAX_BUFFER];
  char *args[MAX_ARGS];
  char **arg;

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
      printf("%s", getprompt());
    }
    if (fgets(buf, MAX_BUFFER, fptr))
    {
      arg = args;
      *arg++ = strtok(buf, SEPARATORS);


      while ((*arg++ = strtok(NULL, SEPARATORS)));
    /*  if (args[0])
      {
        if (!strcmp(args[0], "clr"))
	{
          printf("\033[2J\033[H");
          continue;
        }
        if (!strcmp(args[0], "quit"))
	{
          break;
        }
        if (!strcmp(args[0], "dir"))
	{
          dir(args);
          continue;
        }
        if (!strcmp(args[0], "cd")) {
          cd(args);
          continue;
        }
        if (!strcmp(args[0], "environ"))
	{
          for (char **env = environ; *env != NULL; env++)
	  {
            printf("%s\n", *env);
          }
          continue;
        } */

        if (!run(tree, args)) {
            execute_file(args);
        }
	    continue;
	  }
      }


}
