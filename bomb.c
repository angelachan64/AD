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

  char user_input[64];

  int mod_number = 0;
  int game_over = 0;
  
  /* CREATE a module array */
  module *a = create_module("./asciiart/symbols/s1.dat");
  //module *b = create_module("./asciiart/symbols/s2.dat");
  //module *c = create_module("./asciiart/symbols/s3.dat");
  //module *d = create_module("./asciiart/symbols/s4.dat");
  //module *e = create_module("./asciiart/symbols/s5.dat");
   
  module *modules[1] = {a};//[5] = {a, b, c, d, e};
  
  while (!completed_game(modules) && ! game_over) { //!game_complete(module array) 
    //Show original Bomb
    printf("Select a module (1 - 5): ");
    fgets(user_input, sizeof(user_input), stdin);
    *strchr(user_input, '\n') = 0;

    //mod_number = validate_input(user_input);
    
    while (mod_number >= 0 && !completed_module(modules[mod_number])) {
      print_module(modules[mod_number]);

      printf("What do you do? ('%s' or 'back'): ", modules[mod_number]->visual_representation[1]);
      fgets(user_input, sizeof(user_input), stdin);
      *strchr(user_input, '\n') = 0;

      if (!strcmp("back", user_input)) {
	mod_number = -1;
      } else if (verify_module(modules[mod_number], user_input)) {
	printf("\e[1;1H\e[2J\n");
	printf("\tThat was correct!\n");
      } else {
	mod_number = -1;
	game_over = 1;
      }

      if (completed_module(modules[mod_number])) {
	printf("You cracked this module!");
	mod_number = -1;
      }
    }
    
  }

  //Post Game (Either game_over is true or completed_game(modules) is true
  if (game_over) {
    int age = fork();
    if (age) {
      int information;
      int waiting = wait(&information);
      printf("Sorry, You Lost! We hope you enjoyed and are willing to try again.");
    } else {
      execlp("cat", "cat", "asciiart/gameover.dat", NULL);
    }
  } else {
    printf("Congratz! You survived.\n");
  }
  return 0;
}
