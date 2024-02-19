#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

typedef struct Function Function;
typedef struct BST BST;

struct Function
{
  char *name;
  void (*pfunction)(char**);
  Function *left;
  Function *right;
};


struct BST
{
  Function *root;
};

BST *gen_bst();


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


//bst bollocks
void insert(Function *root, Function *new);
int gen_hashvalue(char *fname);
Function *new_function(char *name, void (*pfunction)(char**));
int run(BST *tree, char *args[]);
int search_and_execute(Function *root, char *fName, char *args[]);

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
  char *path = strstr(getenv("PWD"), getenv("USERNAME")) + strlen("USERNAME") + 1;
  char *indicator = ">";

  char *prompt = malloc(sizeof(char) * strlen(user) + strlen(path) + strlen(indicator) + 2);

  sprintf(prompt, "%s ~/%s\n%s", user, path, indicator);

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

BST *gen_bst(void) {
  BST *tree = (BST *)malloc(sizeof(BST));

  tree->root = (Function*)malloc(sizeof(Function));

  void(*shell_functions[])(char**) = {&cd, &dir};
  char *string_functions[] = {"cd", "dir"};

  tree->root = new_function(string_functions[0], shell_functions[0]);

  int i = 1;
  while (i < sizeof(string_functions)/ sizeof(string_functions[0])) {
    insert(tree->root, new_function(string_functions[i], shell_functions[i]));
    i++;
  }
  return tree;
}

Function *new_function(char *fname, void (*pfunction)(char *argv[])) {
  Function *new = (Function *)malloc(sizeof(Function));
  new->name = fname;
  new->pfunction = pfunction;
  return new;
}

void insert(Function *root, Function *new) {
  if (new == NULL) {
    printf("NEW FUNCTION IS EQUAL TO NULL YOU FAIL YOU LOSE\n");
  }

  int compare = strcmp(new->name, root->name);

  if (compare < 0) {
    if (root->left != NULL) {
      insert(root->left, new);
    }
    else {
      root->left = new;
    }
  }
  if (compare >= 0) {
    if (root->right != NULL) {
      insert(root->right, new);
    }
    else {
      root->right = new;
    }
  }
}

int run(BST *tree, char *args[]) {
  return search_and_execute(tree->root, args[0], args);
}



int search_and_execute(Function *root, char *fName, char *args[]) {
  int compare= strcmp(fName, root->name);

  if (!compare) {
    root->pfunction(args);
    return 1;
  }
  else if ((root->left == NULL) && (root->right == NULL)) {
    return 0;
  }
  else if (compare >= 1) {
    return search_and_execute(root->right, fName, args);
  }
  else if (compare < 0) {
    return search_and_execute(root->left, fName, args);
  }
  printf("search_and_execute failed");
}
