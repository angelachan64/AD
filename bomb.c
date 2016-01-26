#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "color.c"
#include "bomb_helper.h"

int main() {
  textcolor(BRIGHT, RED, BLACK);
  printf("This is the Bomb component of Attempting Diffusal.\n");
  textcolor(RESET, WHITE, BLACK);
  
  /* CREATE a module array */
  module *a = create_module("./asciiart/symbols/s1.dat");
  
  while (!completed_module(a)) { //!game_complete(module array) 
    print_module(a);

    printf("What do you do? ('%s'): ", "TEST");
    char user_input[64];
    fgets(user_input, sizeof(user_input), stdin);
    *strchr(user_input, '\n') = 0;

    if (verify_module(a, user_input)) {
      printf("\e[1;1H\e[2J\n");
      printf("That was correct!");
    } else {
      printf("You Lose!");
      exit(0);
    }
  }
  printf("Congratz! You survived.");
  return 0;
}
