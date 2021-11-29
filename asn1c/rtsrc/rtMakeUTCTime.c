/*
 * Copyright (c) 1997-2009 Objective Systems, Inc.
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

#include <stdio.h>
#include <stdlib.h>
#include "rtsrc/rt_common.hh"
#include "rtsrc/asn1intl.h"

EXTRTMETHOD int rtMakeUTCTime (OSCTXT* pctxt, const OSNumDateTime* dateTime,
                   char** outdata, size_t outdataSize)
{
   char dateTimeStr[46];
   int  j;

   if (!rtxDateTimeIsValid (dateTime))
      return LOG_RTERR(pctxt, RTERR_INVFORMAT);

   /* Year is more restricted in UTC time */
   if (dateTime->year < 1950 || dateTime->year > 2049)
      return LOG_RTERR(pctxt, RTERR_INVFORMAT);

   /* YYYYMMDDHH[MM[SS[(.|,)SSSS]]][TZD] */
   j = sprintf (dateTimeStr, "%.2d%.2d%.2d%.2d%.2d", 
                dateTime->year%100, dateTime->mon, dateTime->day, 
                dateTime->hour, dateTime->min);

   if (dateTime->sec != 0) {
      j += sprintf (dateTimeStr + j, "%.2d", (int)dateTime->sec);
   }

   if (dateTime->tz_flag) {
      dateTimeStr [j++] = 'Z';
      dateTimeStr [j]   = '\0';
   }
   else if (dateTime->tzo != 0) {
      char tzd = (dateTime->tzo < 0) ? '-' : '+';
      int  tzo = dateTime->tzo;
      if (tzo < 0) tzo *= -1;
      sprintf (dateTimeStr + j, "%c%02d%02d", tzd, tzo/60, tzo%60);
   }
      
   if (outdataSize == 0) {
      *outdata = (char*) rtxMemAlloc (pctxt, strlen(dateTimeStr)+1);
      if (0 == *outdata)
         return LOG_RTERR (pctxt, RTERR_NOMEM);
   }
   else {
      size_t size = strlen (dateTimeStr);
      if (outdataSize <= size)
         return LOG_RTERR (pctxt, RTERR_STROVFLW);
   }
   strcpy (*outdata, dateTimeStr);

   return (0);
}

