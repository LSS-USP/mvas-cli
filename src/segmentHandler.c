#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "segmentHandler.h"
#include "segment.h"

int removeSegment(int pSegmentId)
{
 // if (!verifySegment())
 // {
 //   printf("There is no VAS\n");
 //   return -1;
 // }

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
  //TODO
  printf("TODO\n");
  return 0;
}
