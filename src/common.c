#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "common.h"
#include "dataType.h"

DIR * verifyProcStatus(const char * pPath)
{
  DIR * procDir = opendir(pPath);
  if (procDir)
  {
    return procDir;
  }
  else
  {
    if (ENOENT == errno)
    {
      return NULL;
    }
    return NULL;
  }
}

int listFromProc(const char * pPath)
{
  DIR * procDir = verifyProcStatus(pPath);
  FILE * vasStatusFile = NULL;
  struct dirent * procInfo = NULL;
  char * fileLine = NULL;
  int total = 0;
  size_t lenght = 0;
  char target[MAX_PARAM_SIZE];

  memset(target, 0, MAX_PARAM_SIZE * sizeof(char));

  if (!procDir)
  {
    printf("Cannot open %s\n", pPath);
  }

  while((procInfo = readdir(procDir)))
  {
    if (!strcmp(procInfo->d_name, "..") || !strcmp(procInfo->d_name, "."))
    {
      continue;
    }

    strcat(target, pPath);
    strcat(target, procInfo->d_name);
    strcat(target, "/status");

    vasStatusFile = fopen(target, "r");
    if (!vasStatusFile)
    {
      printf("Cannot open: %s\nError: %s\n", target, strerror(errno));
      continue;
    }

    while ((total = getline(&fileLine, &lenght, vasStatusFile) != -1))
    {
      printf("%s", fileLine);
    }

    memset(target, 0, MAX_PARAM_SIZE * sizeof(char));
    fclose(vasStatusFile);
  }

  closedir(procDir);
  
  return 0;
}
