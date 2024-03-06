#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *cwd = malloc(100);
  printf("%s\n", getcwd(cwd, 100));
  printf("%s\n", cwd);
  chdir("..");
  char *ncwd = malloc(100);
  printf("%s\n", getcwd(ncwd, 100));
}
