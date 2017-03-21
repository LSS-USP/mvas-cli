#ifndef __COMMON_H__
#define __COMMON_H__

#include <sys/types.h>
#include <dirent.h>

extern int isFile(const char * pPath);
extern DIR * verifyProcStatus(const char * pPath);
extern int listFromProc(const char * pPath);

#endif
