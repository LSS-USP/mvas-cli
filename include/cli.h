#ifndef __MENU_H__
#define __MENU_H__

#include <sys/queue.h>

#define BUFFER 4096

enum
{
  LIST,
  LIST_VAS,
  LIST_SEG,
  REMOVE,
  REMOVE_ALL_VASES,
  CREATE,
  ERROR,
  NOTHING
};

struct singleParameter
{
  char * parameter;
  char * value;
  TAILQ_ENTRY(singleParameter) pointers;
};

typedef struct _commandList
{
  TAILQ_HEAD(parameters, singleParameter) head;
} commandList;

extern commandList * typedCommand(int pArgc, char ** pArgv);
extern int syntaxCommand(const commandList * pParameters);
extern char listOption(const commandList * pCommand);
extern char removeOption(const commandList * pCommand);
extern char removeAllVASesOption(const commandList * pCommand);
extern char createOption(const commandList * pCommand);

#endif
