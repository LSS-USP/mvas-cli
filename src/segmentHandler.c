#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include "segmentHandler.h"
#include "segment.h"
#include "common.h"

int removeSegment(int pSegmentId)
{
  if (!verifyProcStatus(PROC_SEGMENT))
  {
    printf("There is no Segment\n");
    return -1;
  }

  int status = 0;
  status = segment_delete(pSegmentId);
  if (status < 0)
  {
    printf("Error on Segment delete: %s\n", strerror(errno));
    return status;
  }

  return status;
}

int listSegment()
{
  listFromProc(PROC_SEGMENT);
  return 0;
}


int createSegment (const char * const pName, unsigned long pStart,
                   unsigned long pSize, mode_t pMode)
{
  if (!pName || !pMode)
    return -1;

  int status = 0;
  status = segment_create_sz(pName, pStart, pSize, pMode);
  if (status < 0)
  {
    printf("Error to create new segment: %s\n", strerror(errno));
    return status;
  }
  return status;
}
