#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("\033[48;5;21m");
  printf("\033[38;5;88mThis text will be in dark red.\033[0m\n");
}
