#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>

#include <mvas/segment.h>

#include "segmentHandler.h"
#include "common.h"

int listSegment()
{
  listFromSys(SYS_VAS_SEG);
  return 0;
}

int removeSegment (int pSegmentId)
{
  if (!verifyProcStatus(SYS_VAS_SEG))
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

int createSegment (const char * const pName, unsigned long pStart,
                   unsigned long pSize, mode_t pMode)
{
  if (!pName || !pMode)
  {
    return -1;
  }

  int status = 0;
  status = segment_create_sz(pName, pStart, pSize, pMode);
  if (status < 0)
  {
    printf("Error to create new segment: %s\n", strerror(errno));
    return status;
  }
  return status;
}

int attachSegmentToVas(const int pVasId, const int pSegId, int pType)
{
  if (pVasId < 0 || pSegId < 0 || pType < 0)
  {
    return -1;
  }

  int status = 0;
  status = segment_attach(pVasId, pSegId, pType);
  if (status < 0)
  {
    printf("Error to attach segment to VAS: %s\n", strerror(errno));
    return status;
  }
  return status;
}
