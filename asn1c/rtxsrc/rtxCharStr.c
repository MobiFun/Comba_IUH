/*
 * Copyright (c) 2003-2009 Objective Systems, Inc.
 *
 * This software is furnished under a license and may be used and copied
 * only in accordance with the terms of such license and with the
 * inclusion of the above copyright notice. This software or any other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of the software is hereby
 * transferred.
 *
 * The information in this software is subject to change without notice
 * and should not be construed as a commitment by Objective Systems, Inc.
 *
 * PROPRIETARY NOTICE
 *
 * This software is an unpublished work subject to a confidentiality agreement
 * and is protected by copyright and trade secret law.  Unauthorized copying,
 * redistribution or other use of this work is prohibited.
 *
 * The above notice of copyright on this source code product does not indicate
 * any actual or intended publication of such source code.
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "rtxsrc/rtxCharStr.h"

EXTRTMETHOD char* rtxStrcat (char* dest, size_t bufsiz, const char* src)
{
   if (0 == dest || 0 == bufsiz || 0 == src)
      return (char*)0;
   else
      return rtxStrncat (dest, bufsiz, src, OSCRTLSTRLEN(src));
}

EXTRTMETHOD char* rtxStrncat (char* dest, size_t bufsiz, const char* src, size_t nchars)
{
   size_t i;

   if (0 == dest || bufsiz <= nchars || 0 == src || 0 == nchars)
      return (char*)0;

   i = OSCRTLSTRLEN (dest);

   return rtxStrncpy (&dest[i], bufsiz - i, src, nchars);
}

EXTRTMETHOD char* rtxStrcpy (char* dest, size_t bufsiz, const char* src)
{
   if (0 == dest || 0 == bufsiz || 0 == src)
      return (char*)0;
   else
      return rtxStrncpy (dest, bufsiz, src, OSCRTLSTRLEN(src));
}

EXTRTMETHOD char* rtxStrncpy (char* dest, size_t bufsiz, const char* src, size_t nchars)
{
   size_t i;

   if (0 == dest || bufsiz <= nchars || 0 == src)
      return (char*)0;

   for (i = 0; i < nchars; i++) {
      dest[i] = src[i];
   }
   dest[i] = '\0';

   return dest;
}
