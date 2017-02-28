#include <stdio.h>
#include <string.h>
#include <errno.h>

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
