#ifndef __DEFINE_VAS_HANDLER_H__
#define __DEFINE_VAS_HANDLER_H__

#include <dirent.h>

#define PROC_VAS "/proc/vas/"

#define MAX_PARAM_SIZE 256

enum
{
  PROC_VAS_EXIST,
  PROC_VAS_NOT_EXIST,
  PROC_CANNOT_BE_OPEN
};

extern DIR * verifyVAS();
extern int listVAS();
extern int removeVAS(const char * pId);

#endif
