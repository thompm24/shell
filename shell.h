#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include "shell.c"

void signalhandler(int sig);
void cd(char *args[]);
void dir(char *args[]);

void execute_file(char *args[]);

char *getprompt(void);
char *cd_back(void);
extern char **environ;


