#ifndef __SEGMENT_HANDLER_H__
#define __SEGMENT_HANDLER_H__

#define PROC_SEGMENT "/proc/segments/"
#include <linux/types.h>

extern int listSegment ();
extern int removeSegment (int pVasId);
extern int createSegment (const char * const pName, unsigned long pStart,
                          unsigned long pSize, mode_t pMode);

#endif
