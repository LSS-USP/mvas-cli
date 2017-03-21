#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <mvas/vas.h>

#include "vasHandler.h"
#include "common.h"

int listVAS()
{
  listFromProc(SYS_VAS);
  return 0;
}

int removeVAS(int pVasId)
{
  if (!verifyProcStatus(SYS_VAS))
  {
    printf("There is no VAS\n");
    return -1;
  }

  int status = 0;
  status = vas_delete(pVasId);
  if (status < 0)
  {
    printf("Error on VAS delete: %s\n", strerror(errno));
    return status;
  }

  return status;
}

int createVAS(const char * pName, mode_t pMode)
{
  int status = 0;
  status = vas_create(pName, pMode);
  if (status < 0)
  {
    printf("Error to create VAS: %s\n", strerror(errno));
    return status;
  }
  return status;
}
