#include "asn1version.h"

int rtxGetLibVersion ()
{
   return OS_ASN1RT_VERSION;
}

const char* rtxGetLibInfo ()
{
   return "ASN1RT, v."OS_ASN1RT_VERSION_STR
#ifdef _DEBUG
   ", debug"
#endif
#ifdef _COMPACT
   ", opt, compact"
#elif defined (_OPTIMIZED)
   ", opt"
#endif
#ifndef _NO_LICENSE_CHECK
   ", limited"
#endif
#ifdef _TRACE
   ", trace"
#endif
#ifdef _NO_STREAM
   ", no stream"
#endif
#ifdef _16BIT
   ", 16 bit"
#endif
#ifdef _NO_INT64_SUPPORT
   ", no int64 support"
#endif
   ".";
}
