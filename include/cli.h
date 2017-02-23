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

// TODO: It will be better, if typedCommand return a linked list of specific
// struct related to commands.

typedef struct _vidAndSegmentId
{
  int vidId;
  int segId;
}vidAndSegmentId;

extern char * typedCommand(int pArgc, char ** pArgv);
extern int syntaxCommand(const char * pCommand);
extern char listOption(const char * pCommand);
extern char removeOption(const char * pCommand);
extern vidAndSegmentId * getVidAndSegment(const char * pOptions, const char pDelimiter);

#endif
