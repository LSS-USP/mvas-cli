#ifndef __SEGMENT_HANDLER_H__
#define __SEGMENT_HANDLER_H__

#define SYS_VAS_SEG "/sys/kernel/vas_segs/"

#include <linux/types.h>

extern int listSegment ();
extern int removeSegment (int pVasId);
extern int createSegment (const char * const pName, unsigned long pStart,
                          unsigned long pSize, mode_t pMode);
extern int attachSegmentToVas(const int pVasId, const int pSegId, int pType);

#endif
