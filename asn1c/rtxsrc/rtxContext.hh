#ifndef _RTXCONTEXT_HH_
#define _RTXCONTEXT_HH_

#include "rtxsrc/rtxContext.h"

#define OSCTXTINIT    0x1aa2a34a

#ifdef __cplusplus
extern "C" {
#endif
int rtxCheckLicense (OSCTXT* pctxt, int bits);
int rtxInitAndCheckLicense (OSCTXT* pctxt, int bits);

EXTERNRT void rtxCtxtSetMemHeap (OSCTXT* pctxt, OSCTXT* pSrcCtxt);
EXTERNRT void rtxCtxtSetMsgMemHeap (OSCTXT* pctxt, OSCTXT* pSrcCtxt);

#ifdef LICCHECK
int rtxlc (OSCTXT* pctxt);

#define LCHECKX(pctxt) \
{ int ret = rtxlc (pctxt); if (0 != ret) return ret; }

#define LCHECKX2(pctxt) \
{ if (0 != rtxlc (pctxt)) return NULL; }

#else
#define LCHECKX(pctxt)
#define LCHECKX2(pctxt)
#endif

#ifdef __cplusplus
}
#endif

#endif
