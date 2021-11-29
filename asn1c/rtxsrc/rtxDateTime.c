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

#include "rtxsrc/rtxDateTime.hh"
#include "rtxsrc/rtxErrCodes.h"

const signed char gDaysInMonth[12] =
     { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

EXTRTMETHOD OSBOOL rtxDateTimeIsValid (const OSNumDateTime* dateTime)
{
   int dim;
   if (dateTime->year < 0 || dateTime->year > 9999 ||
       dateTime->mon < 1 || dateTime->mon > 12 ||
       dateTime->day < 1 || dateTime->day > 31 ||
       /* dateTime->hour < 0 || */ dateTime->hour > 23 ||
       /* dateTime->min < 0 || */ dateTime->min > 59 ||
       dateTime->sec < 0 || dateTime->sec > 59 ||
       dateTime->tzo < -1440 || dateTime->tzo > 1440)
      return FALSE;

   dim = (int) gDaysInMonth [dateTime->mon - 1];

   /* check for February of leap-year */
   if (dateTime->mon == 2 && dateTime->year % 4 == 0 && 
       (dateTime->year % 100 != 0 || dateTime->year % 400 == 0))
      dim++;

   if (dateTime->day < 1 || dateTime->day > dim)
      return FALSE;

   return TRUE;
}

/**
  * rtxGetCurrDateTime:
  * This function reads the system date and time and return the same in
  * OSNumDateTime structure
  */
EXTRTMETHOD int rtxGetCurrDateTime(OSNumDateTime* pvalue)
{
   time_t tim = time((time_t *)NULL);
   return rtxSetLocalDateTime (pvalue, tim);
}

EXTRTMETHOD int rtxSetDateTime (OSNumDateTime* pvalue, struct tm* timeStruct)
{
   pvalue->year = 1900 + timeStruct->tm_year;
   pvalue->mon = (OSINT8)(1 + timeStruct->tm_mon);
   pvalue->day = (OSINT8)(timeStruct->tm_mday);
   pvalue->hour = (OSINT8)(timeStruct->tm_hour);
   pvalue->min = (OSINT8)(timeStruct->tm_min);
   pvalue->sec = timeStruct->tm_sec;
   pvalue->tz_flag = FALSE;
   pvalue->tzo = 0;
   return RT_OK;
}

EXTRTMETHOD int rtxSetLocalDateTime (OSNumDateTime* pvalue, time_t timeMs)
{
#if _MSC_VER >= 1400
   // TODO: fix this call
   // struct tm *ltime = localtime_s (&timeMs);
   struct tm *ltime = localtime (&timeMs); // TEMPORARY!!!
#else
   struct tm *ltime = localtime (&timeMs);
#endif
   return rtxSetDateTime (pvalue, ltime);
}

EXTRTMETHOD int rtxSetUtcDateTime (OSNumDateTime* pvalue, time_t timeMs)
{
#if _MSC_VER >= 1400
   // TODO: fix this call
   // struct tm *gtime_s = gmtime(&timeMs);
   struct tm *gtime = gmtime(&timeMs); // TEMPORARY!!!
#else
   struct tm *gtime = gmtime(&timeMs);
#endif
   return rtxSetDateTime (pvalue, gtime);
}

EXTRTMETHOD int rtxGetDateTime (const OSNumDateTime* pvalue, time_t* timeMs)
{
   struct tm timeStruct;

   if (timeMs == 0 || pvalue == 0) return RTERR_INVPARAM;
   timeStruct.tm_year = pvalue->year - 1900;
   timeStruct.tm_mon = pvalue->mon - 1;
   timeStruct.tm_mday = pvalue->day;
   timeStruct.tm_hour = pvalue->hour;
   timeStruct.tm_min = pvalue->min;
   timeStruct.tm_sec = (int)pvalue->sec;
   timeStruct.tm_isdst = -1;
   *timeMs = mktime (&timeStruct);
   return RT_OK;
}

