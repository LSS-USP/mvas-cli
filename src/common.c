#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "dataType.h"

static void printEachElement(const char * pPath)
{
  DIR * sysDir = verifyProcStatus(pPath);
  FILE * vasStatusFile = NULL;
  struct dirent * sysInfo = NULL;
  char * fileLine = NULL;
  int total = 0;
  size_t lenght = 0;
  char target[MAX_PARAM_SIZE];

  if (isFile(pPath))
  {
    return;
  }

  memset(target, 0, MAX_PARAM_SIZE * sizeof(char));

  if (!sysDir)
  {
    printf("Cannot open %s\n", pPath);
    return;
  }

  while ((sysInfo = readdir(sysDir)))
  {
    if (!strcmp(sysInfo->d_name, "..") || !strcmp(sysInfo->d_name, "."))
    {
      continue;
    }

    strcat(target, pPath);
    strcat(target, sysInfo->d_name);
    if (isFile(pPath))
    {
      return;
    }

    vasStatusFile = fopen(target, "r");
    if (!vasStatusFile)
    {
      printf("Cannot open: %s\nError: %s\n", target, strerror(errno));
      continue;
    }

    while ((total = getline(&fileLine, &lenght, vasStatusFile) != -1))
    {
      printf("%s: %s\n", sysInfo->d_name, fileLine);
    }

    memset(target, 0, MAX_PARAM_SIZE * sizeof(char));
    fclose(vasStatusFile);
  }
  printf("\n");
  closedir(sysDir);
}

int isFile(const char * pPath)
{
  struct stat pathStat;
  stat(pPath, &pathStat);
  return S_ISREG(pathStat.st_mode);
}

DIR * verifyProcStatus(const char * pPath)
{
  DIR * sysDir = opendir(pPath);
  if (sysDir)
  {
    return sysDir;
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

int listFromSys(const char * pPath)
{
  DIR * sysDir = verifyProcStatus(pPath);
  struct dirent * sysInfo = NULL;
  char target[MAX_PARAM_SIZE];

  memset(target, 0, MAX_PARAM_SIZE * sizeof(char));

  if (!sysDir)
  {
    printf("Cannot open %s\n", pPath);
  }

  // Iterate inside folder
  while((sysInfo = readdir(sysDir)))
  {
    if (!strcmp(sysInfo->d_name, "..") || !strcmp(sysInfo->d_name, "."))
    {
      continue;
    }

    strcat(target, pPath);
    strcat(target, sysInfo->d_name);
    strcat(target, "/");

    printf("%s\n", target);
    printEachElement(target);

    memset(target, 0, MAX_PARAM_SIZE * sizeof(char));
  }

  closedir(sysDir);
  return 0;
}
