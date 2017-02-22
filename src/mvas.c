#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cli.h"
#include "vasHandler.h"

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
      listVAS();
      break;
    case REMOVE:
      //TODO
      printf("INPUT: %s\n", inputCommand);
      break;
    default:
      printf("Wrong syntax or not implemented yet\n");
      break;
  }

  free(inputCommand);

  return 0;
}
