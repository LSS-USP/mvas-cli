#ifndef __MENU_H__
#define __MENU_H__

#define BUFFER 4096

enum
{
  LIST,
  REMOVE,
  DETACH,
  ATTACH,
  ERROR,
  NOTHING
};

extern char * typedCommand(int pArgc, char ** pArgv);
extern int syntaxCommand(const char * pCommand);
extern char listOption(const char * pCommand);
extern char removeOption(const char * pCommand);

#endif
