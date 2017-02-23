#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "cli.h"

#define COMMAND_OPTIONS "adrlhv:s:"

static struct option longOptions[] =
{
  {"lv", no_argument, 0, 0},
  {"ls", no_argument, 0, 0},
  {"attach", no_argument, 0, 0},
  {"detach", no_argument, 0, 0},
  {"remove", no_argument, 0, 0},
  {"list", no_argument, 0, 0},
  {"help", no_argument, 0, 0},
  {"verbose", no_argument, 0, 0},
  {"vid", required_argument, 0, 0},
  {"segment", required_argument, 0, 0},
  {0, 0, 0, 0}
};

char * typedCommand(int pArgc, char ** pArgv)
{
  int optionCharacter = 0;
  char breakParser = 1;
  char * inputCommand = 0;

  inputCommand = malloc(BUFFER * sizeof(char));
  if (!inputCommand)
  {
    return NULL;
  }

  while(breakParser)
  {
    int optionIndex = 0;

    optionCharacter = getopt_long(pArgc, pArgv, COMMAND_OPTIONS,
                                  longOptions, &optionIndex);
    if (optionCharacter == -1)
    {
      break;
    }

    strcat(inputCommand, " ");
    switch (optionCharacter)
    {
      case 0:
        strcat(inputCommand, longOptions[optionIndex].name);
        if (optarg)
        {
          strcat(inputCommand, ":");
          strcat(inputCommand, optarg);
        }
        break;
      case 'a':
        strcat(inputCommand, "a");
        break;
      case 'd':
        strcat(inputCommand, "d");
        break;
      case 'r':
        strcat(inputCommand, "r");
        break;
      case 'l':
        strcat(inputCommand, "l");
        break;
      case 'h':
        strcat(inputCommand, "h");
        break;
      case 'v':
        strcat(inputCommand, "v");
        strcat(inputCommand, ":");
        strcat(inputCommand, optarg);
        break;
      case 's':
        strcat(inputCommand, "s");
        strcat(inputCommand, ":");
        strcat(inputCommand, optarg);
        break;
      default:
        printf("Invalid option\n");
        free(inputCommand);
        inputCommand = NULL;
        breakParser = 0;
        break;
    };
  }

  if (optind < pArgc)
  {
    printf("non-option ARGV: ");
    while (optind < pArgc)
      printf("%s ", pArgv[optind++]);
    printf("\n");
  }

  return inputCommand;
}

int syntaxCommand(const char * pCommand)
{
  int rc = NOTHING;
  if (!pCommand)
  {
    return ERROR;
  }

  rc = listOption(pCommand) == NOTHING ? rc : LIST;
  rc = removeOption(pCommand) ==  NOTHING ? rc : REMOVE;

  return rc;
}

char listOption(const char * pCommand)
{
  // Verify list command
  if (strstr("list", pCommand))
  {
    return LIST;
  }
  else
  {
    for (int i = 0; pCommand[i]; i++)
    {
      if (pCommand[i] == 'l' || pCommand[i] == ' ' || pCommand[i] == '\n')
      {
        continue;
      }
      return NOTHING;
    }
  }
  return LIST;
}

char removeOption(const char * pCommand)
{
  int i = 0;
  int removeVasSeg = 0;
  if (strstr("remove", pCommand))
  {
    return REMOVE;
  }
  else
  {
    for (i = 0; pCommand[i]; i++)
    {
      if (pCommand[i] == 'r' || pCommand[i] == ' ' || pCommand[i] == '\n')
      {
        removeVasSeg = 1;
        break;
      }
    }
    if (removeVasSeg)
    {
      for (; pCommand[i]; i++)
      {
        if (pCommand[i] == 'v' || pCommand[i] == 's')
        {
          return REMOVE;
        }
      }
    }
  }
  return NOTHING;
}

vidAndSegmentId * getVidAndSegment(const char * pOptions, const char pDelimiter)
{
  if (!pOptions)
  {
    printf("Invalid parameter\n");
    return NULL;
  }

  char * handleOptions = strdup(pOptions);
  int i = 0, extractVidSeg = 0;
  char * stringToBreak = NULL;
  char * nextToken = NULL;
  vidAndSegmentId * params = NULL;

  for (i = 0; i < strlen(handleOptions); i++)
  {
    if (handleOptions[i] == pDelimiter)
    {
      extractVidSeg = 1;
      i++;
      break;
    }
  }

  if (extractVidSeg)
  {
    params = malloc(sizeof(vidAndSegmentId));
    if (!params)
    {
      printf("Cannot allocate vidAndSegmentId\n");
      return NULL;
    }
    params->vidId = -1;
    params->segId = -1;

    stringToBreak = strdup(&handleOptions[i]);
    nextToken = strtok(stringToBreak, ":");
    while(nextToken != NULL)
    {
      if (strstr(nextToken, "v") != NULL)
      {
        nextToken = strtok(NULL, " ");
        params->vidId = atoi(nextToken);
      }
      if (strstr(nextToken, "s") != NULL)
      {
        nextToken = strtok(NULL, " ");
        params->segId = atoi(nextToken);
      }
      nextToken = strtok(NULL, ":");
    }
  }
  return params;
}
