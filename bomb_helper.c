#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "bomb_helper.h"

module* create_module(char* filename) {
  module *m = (module *)malloc(sizeof(module));
  
  int input_status = open(filename, O_RDONLY);
  if (input_status < 0) {
    printf("ERROR: %s",strerror(errno));
    exit(1);
  }

  char *temp = (char *)malloc(sizeof(char)*49152);
  int reader = read(input_status, temp, 49152);
  if (reader < -1) {
    printf("Error: %s\n", strerror(errno));
    exit(1);
  }

  m->complete = 0;

  int counter = 0;
  char** lines = (char**)malloc(sizeof(char)*49152); 
  while (temp) {
    lines[counter] = strsep(&temp, "\n");
    counter++;
  }

  m->steps = atoi(lines[0]); 
  m->current_step = 0;
  m->visual_representation = &temp;
  return m;
}

void print_module(module *m) {
  int displacement = 1 + m->current_step * 28;
  int counter = 0;
  while (counter < 27) {
    printf("%s\n",m->visual_representation[displacement+counter]);
  }
}

int verify_module(module *m) {
  return 0;
}
