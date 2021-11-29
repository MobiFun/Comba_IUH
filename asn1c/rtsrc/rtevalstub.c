#ifndef _BUILD_LICOBJ
#define _BUILD_LICOBJ
#endif
#include "checklic.hhh"
#include "rtxsrc/rtxContext.h"

#ifndef _NO_LICENSE_CHECK
int rtCheckLicense (OSCTXT* pCtxt, int bits)
{
   return 0;
}

int rtInitAndCheckLicense (OSCTXT* pCtxt, int bits)
{
   return rtxInitContext (pCtxt);
}
#endif
