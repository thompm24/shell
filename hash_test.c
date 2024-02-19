#include "shell.c"

int main(int argc, char *argv[]) {
  BST *tree = gen_bst();
  run(tree, argv);
}
