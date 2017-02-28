#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "vasHandler.h"
#include "vas.h"
#include "common.h"

int listVAS()
{
  listFromProc(PROC_VAS);
  return 0;
}

int removeVAS(int pVasId)
{
  if (!verifyProcStatus(PROC_VAS))
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
