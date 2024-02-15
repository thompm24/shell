#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include "shell.c"

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


