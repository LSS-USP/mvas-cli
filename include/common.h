#ifndef __COMMON_H__
#define __COMMON_H__

#include <sys/types.h>
#include <dirent.h>

extern DIR * verifyProcStatus(const char * pPath);
extern int listFromProc(const char * pPath);

#endif
