#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cli.h"

int main(int argc, char ** argv)
{
  char * inputCommand = NULL;
  int action = 0;

  inputCommand = typedCommand(argc, argv);
  if (!inputCommand)
  {
    return -1;
  }

  action = syntaxCommand(inputCommand);
  switch(action)
  {
    case LIST:
      //TODO
      printf("INPUT: %s\n", inputCommand);
      break;
    case REMOVE:
      //TODO
      printf("INPUT: %s\n", inputCommand);
      break;
    default:
      printf("Wrong syntax\n");
      break;
  }
  printf("action: %d\n", action);
  free(inputCommand);

  return 0;
}
