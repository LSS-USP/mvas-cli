#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>

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
      listVAS();
      printf("\n");
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
        if (!strcmp(elements->parameter, "name") ||
            !strcmp(elements->parameter, "n"))
        {
          name = elements->value;
          continue;
        }
        if (!strcmp(elements->parameter, "mode") ||
            !strcmp(elements->parameter, "m"))
        {
          if (elements->value[0] != '0')
          {
            mode = (mode_t)strtol(elements->value, NULL, 8);
          }
          else
          {
            mode = (mode_t)strtol(elements->value, NULL, 0);
          }
          continue;
        }
        if (!strcmp(elements->parameter, "size"))
        {
          if (!strstr(elements->value, "0x"))
          {
            printf("Please, inform size in hexadecimal (0x)\n");
            return -1;
          }
          size = (unsigned long int)strtol(elements->value, NULL, 16);
          continue;
        }
        if (!strcmp(elements->parameter, "start"))
        {
          if (!strstr(elements->value, "0x"))
          {
            printf("Please, inform start in hexadecimal (0x)\n");
            return -1;
          }
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
    case ATTACH_SEGMENT:
      elements = currentCommands->head.tqh_first;
      elements = elements->pointers.tqe_next;
      int status = 0;
      int type = 0;
      unsigned long int vasId = 0;
      unsigned long segId = 0;

      for(; elements != NULL; elements = elements->pointers.tqe_next)
      {
        if (!strcmp(elements->parameter, "vid") ||
            !strcmp(elements->parameter, "v"))
        {
          vasId = (unsigned long int)strtol(elements->value, NULL, 0);
          continue;
        }
        if (!strcmp(elements->parameter, "segment") ||
            !strcmp(elements->parameter, "s"))
        {
          segId = (unsigned long int)strtol(elements->value, NULL, 0);
          continue;
        }
        if (!strcmp(elements->parameter, "type") ||
            !strcmp(elements->parameter, "t"))
        {
          if (!strcmp(elements->value, "wr") || !strcmp(elements->value, "rw"))
          {
            type = O_RDWR;
          }
          else if (!strcmp(elements->value, "w"))
          {
            type = O_WRONLY;
          }
          else
          {
            type = O_RDONLY;
          }
        }
      }
      status = attachSegmentToVas(vasId, segId, type);
      if (status < 0)
      {
        return status;
      }
      break;
    default:
      printf("Wrong syntax or not implemented yet\n");
      break;
  }

  free(inputCommand);

  return 0;
}
