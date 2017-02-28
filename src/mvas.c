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
  vidAndSegmentId * params = NULL;
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
      listSegment();
      break;
    case LIST_VAS:
      listVAS();
      break;
    case LIST_SEG:
      listSegment();
      break;
    case REMOVE:
      params = getVidAndSegment(inputCommand, 'r');
      if (params)
      {
        printf("vid: %d\n", params->vidId);
        if (params->vidId >= 0)
        {
          removeVAS(params->vidId);
        }
        if (params->segId >= 0)
        {
          removeSegment(params->segId);
        }
      }
      free(params);
      break;
    default:
      printf("Wrong syntax or not implemented yet\n");
      break;
  }

  free(inputCommand);

  return 0;
}
