#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <mvas/vas.h>

#include "vasHandler.h"
#include "common.h"
#include "dataType.h"

int listVAS()
{
  listFromSys(SYS_VAS);
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
    printf("Cannot delete VAS (%d): %s\n", pVasId, strerror(errno));
    return status;
  }

  return status;
}

int removeAllVAS()
{
  DIR * sysDir = verifyProcStatus(SYS_VAS);
  struct dirent * sysInfo = NULL;
  int idVas = 0;

  if (!sysDir) {
    printf("Cannot open %s\n", SYS_VAS);
    return -1;
  }

  // Iterate inside folder
  while((sysInfo = readdir(sysDir))) {
    if (!strcmp(sysInfo->d_name, "..") || !strcmp(sysInfo->d_name, "."))
      continue;

    idVas = atoi(sysInfo->d_name);
    printf("Remove VAS: %s %d\n", sysInfo->d_name, idVas);
    removeVAS(idVas);
  }

  closedir(sysDir);
  return 1;
}

int createVAS(const char * pName, mode_t pMode)
{
  int status = 0;
  status = vas_create(pName, pMode);
  if (status < 0) {
    printf("Error to create VAS, %s, %o: %s\n", pName, pMode, strerror(errno));
    return status;
  }
  return status;
}
