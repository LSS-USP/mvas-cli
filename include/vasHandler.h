#ifndef __DEFINE_VAS_HANDLER_H__
#define __DEFINE_VAS_HANDLER_H__

#include <dirent.h>

#define PROC_VAS "/proc/vas/"

enum
{
  PROC_VAS_EXIST,
  PROC_VAS_NOT_EXIST,
  PROC_CANNOT_BE_OPEN
};

extern int listVAS();
extern int removeVAS(int pVasId);

#endif
