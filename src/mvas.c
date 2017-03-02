#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cli.h"
#include "vasHandler.h"
#include "segmentHandler.h"

int main(int argc, char ** argv)
{
  char * inputCommand = NULL;
  int action = 0;
  struct singleParameter * elements = NULL;

  commandList * currentCommands = typedCommand(argc, argv);
  if (!currentCommands)
  {
    return -1;
  }

  action = syntaxCommand(currentCommands);
  switch(action)
  {
    case LIST:
      printf("VAS\n");
      listVAS();
      printf("SEGMENTS\n");
      listSegment();
      break;
    case LIST_VAS:
      listVAS();
      break;
    case LIST_SEG:
      listSegment();
      break;
    case REMOVE:
      elements = currentCommands->head.tqh_first;
      // Ignore first element (it is 'r' or 'remove')
      elements = elements->pointers.tqe_next;
      for(; elements != NULL; elements = elements->pointers.tqe_next)
      {
        if (!strcmp(elements->parameter, "vid") ||
            !strcmp(elements->parameter, "v"))
        {
          removeVAS(atoi(elements->value));
          continue;
        }
        if (!strcmp(elements->parameter, "segment") ||
            !strcmp(elements->parameter, "s"))
        {
          removeSegment(atoi(elements->value));
          continue;
        }
      }
      break;
    case CREATE:
      elements = currentCommands->head.tqh_first;
      // Ignore first element (it is 'r' or 'remove')
      elements = elements->pointers.tqe_next;
      mode_t mode = 0;
      char * name = NULL;
      unsigned long int size = 0;
      unsigned long start = 0;

      for(; elements != NULL; elements = elements->pointers.tqe_next)
      {
        if (!strcmp(elements->parameter, "name"))
        {
          name = elements->value;
          continue;
        }
        if (!strcmp(elements->parameter, "mode"))
        {
          mode = atoi(elements->value);
          continue;
        }
        if (!strcmp(elements->parameter, "size"))
        {
          size = (unsigned long int)strtol(elements->value, NULL, 16);
          continue;
        }
        if (!strcmp(elements->parameter, "start"))
        {
          start = (unsigned long int)strtol(elements->value, NULL, 16);
          continue;
        }
      }

      if (name && mode && start && size)
      {
        createSegment(name, start, size, mode);
      }
      else if (name && mode)
      {
        createVAS(name, mode);
      }
      break;
    default:
      printf("Wrong syntax or not implemented yet\n");
      break;
  }

  free(inputCommand);

  return 0;
}
