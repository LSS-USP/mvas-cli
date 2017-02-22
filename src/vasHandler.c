#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <string.h>

#include "vasHandler.h"

DIR * verifyVAS()
{
  DIR * procDir = opendir(PROC_VAS);
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

int listVAS()
{
  DIR * procDir = verifyVAS();
  FILE * vasStatusFile = NULL;
  struct dirent * procInfo = NULL;
  char * fileLine;
  int total = 0;
  size_t lenght = 0;
  char target[MAX_PARAM_SIZE];

  memset(target, 0, MAX_PARAM_SIZE * sizeof(char));

  if (!procDir)
  {
    printf("Cannot open %s\n", PROC_VAS);
  }

  while((procInfo = readdir(procDir)))
  {
    if (!strcmp(procInfo->d_name, "..") || !strcmp(procInfo->d_name, "."))
    {
      continue;
    }

    strcat(target, PROC_VAS);
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

    fclose(vasStatusFile);
  }

  closedir(procDir);
  
  return 0;
}

int removeVAS(const char * pId)
{
  //TODO
  return 0;
}
