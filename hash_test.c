#include "shell.c"

int main(int argc, char *argv[]) {
  printf("hello\n");
  BST *tree = gen_bst();
  printf("hello\n");
  run(tree, argv);
}
