#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/queue.h>

#include "cli.h"

#define COMMAND_OPTIONS "adrclhv:s:n:m:t:"

static commandList listOfParameters;

static struct option longOptions[] =
{
  {"lv", no_argument, 0, 0},
  {"ls", no_argument, 0, 0},
  {"detach", no_argument, 0, 0},
  {"remove", no_argument, 0, 0},
  {"remove-all-vas", no_argument, 0, 0},
  {"create", no_argument, 0, 0},
  {"size", required_argument, 0, 0},
  {"start", required_argument, 0, 0},
  {"name", required_argument, 0, 0},
  {"list", no_argument, 0, 0},
  {"help", no_argument, 0, 0},
  {"verbose", no_argument, 0, 0},
  {"vid", required_argument, 0, 0},
  {"mode", required_argument, 0, 0},
  {"type", required_argument, 0, 0},
  {0, 0, 0, 0}
};

static int insertParameter(const char * pParameter, const char * pValue)
{
  struct singleParameter * item = NULL;

  if (!pParameter)
  {
    return -1;
  }

  item = (struct singleParameter *) malloc(sizeof(struct singleParameter));
  if (!item)
  {
    printf("cannot allocated memory\n");
    return -1;
  }

  item->parameter = strdup(pParameter);
  if (pValue)
  {
    item->value = strdup(pValue);
  }
  else
  {
    item->value = NULL;
  }

  TAILQ_INSERT_TAIL(&listOfParameters.head, item, pointers);
  return 0;
}

commandList * typedCommand(int pArgc, char ** pArgv)
{
  int optionCharacter = 0;
  char breakParser = 1;
  int optionIndex = 0;

  TAILQ_INIT(&listOfParameters.head);

  while(breakParser)
  {
    optionIndex = 0;
    optionCharacter = getopt_long_only(pArgc, pArgv, COMMAND_OPTIONS,
                                       longOptions, &optionIndex);
    if (optionCharacter == -1)
    {
      break;
    }

    switch (optionCharacter)
    {
      case 0:
        insertParameter(longOptions[optionIndex].name, optarg);
        break;
      case 'a':
        insertParameter("a", NULL);
        break;
      case 'd':
        insertParameter("d", NULL);
        break;
      case 'r':
        insertParameter("r", NULL);
        break;
      case 'c':
        insertParameter("c", NULL);
        break;
      case 'n':
        insertParameter("n", optarg);
        break;
      case 'm':
        insertParameter("m", optarg);
        break;
      case 'l':
        insertParameter("l", NULL);
        break;
      case 'h':
        insertParameter("h", NULL);
        break;
      case 'v':
        insertParameter("v", optarg);
        break;
      case 's':
        insertParameter("s", optarg);
        break;
      case 't':
        insertParameter("t", optarg);
        break;
      default:
        printf("Invalid option\n");
        //TODO: FREE LIST
        breakParser = 0;
        break;
    };
  }

  if (optind < pArgc)
  {
    printf("non-option ARGV: ");
    while (optind < pArgc)
    {
      printf("%s ", pArgv[optind++]);
    }
    printf("\n");
  }

  return &listOfParameters;
}

int syntaxCommand (const commandList * pParameters)
{
  int rc = NOTHING;
  if (!pParameters)
  {
    return ERROR;
  }

  rc = listOption(pParameters);
  if (rc != NOTHING)
  {
    return rc;
  }

  rc = removeOption(pParameters);
  if (rc != NOTHING)
  {
    return rc;
  }

  rc = removeAllVASesOption(pParameters);
  if (rc != NOTHING)
  {
    return rc;
  }

  rc = createOption(pParameters);
  if (rc != NOTHING)
  {
    return rc;
  }

  return rc;
}

char listOption(const commandList * pParameters)
{
  struct singleParameter * first = NULL;

  if (!pParameters)
  {
    return NOTHING;
  }

  first = pParameters->head.tqh_first;

  // Verify list command
  if (strstr(first->parameter, "list") || !strcmp(first->parameter, "l"))
  {
    return LIST;
  }
  else if (strstr(first->parameter, "ls"))
  {
    return LIST_SEG;
  }
  else if (strstr(first->parameter, "lv"))
  {
    return LIST_VAS;
  }

  return NOTHING;
}

char removeOption(const commandList * pParameters)
{
  struct singleParameter * first = NULL;

  if (!pParameters)
  {
    return NOTHING;
  }

  first = pParameters->head.tqh_first;

  if (!strcmp(first->parameter, "remove") || !strcmp(first->parameter, "r"))
  {
    first = first->pointers.tqe_next;
    // Next should be a vas id or both
    for(; first != NULL; first = first->pointers.tqe_next)
    {
      if (!strcmp(first->parameter, "vid") ||
          !strcmp(first->parameter, "v"))
        continue;

      return NOTHING;
    }
  }
  else
  {
    return NOTHING;
  }
  return REMOVE;
}

char removeAllVASesOption(const commandList * pCommand)
{
  struct singleParameter * first = NULL;

  if (!pCommand)
  {
    return NOTHING;
  }

  first = pCommand->head.tqh_first;

  if (!strcmp(first->parameter, "remove-all-vas"))
  {
    return REMOVE_ALL_VASES;
  }
  else
  {
    return NOTHING;
  }
}

char createOption(const commandList * pParameters)
{
  struct singleParameter * first = NULL;
  unsigned char countMandatoryParameters = 0;

  if (!pParameters)
  {
    return NOTHING;
  }

  first = pParameters->head.tqh_first;

  if (!strcmp(first->parameter, "create") || !strcmp(first->parameter, "c"))
  {
    first = first->pointers.tqe_next;
    // Next should be: name + mode (mode + name)
    for(; first != NULL; first = first->pointers.tqe_next)
    {
      // Mandatory parameters
      if (!strcmp(first->parameter, "name") || !strcmp(first->parameter, "n") ||
          !strcmp(first->parameter, "mode") || !strcmp(first->parameter, "m"))
      {
        countMandatoryParameters++;
        continue;
      }
      // Segment parameters
      if (!strcmp(first->parameter, "size") ||
          !strcmp(first->parameter, "start"))
      {
        continue;
      }
      return NOTHING;
    }
  }
  else
  {
    return NOTHING;
  }

  if (countMandatoryParameters == 2)
  {
    return CREATE;
  }
  else
  {
    return NOTHING;
  }
}
