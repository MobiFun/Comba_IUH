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
#include "rt_common.hh"
#include "asn1intl.h"

#ifdef __SYMBIAN32__
#include "rtxsrc/osSysTypes.h"
#include "rtxsrc/osMacros.h"
#endif

int rtSetLocalTime (OSDATETIME* dateTime, time_t long_time, ASN1BOOL diffTime)
{
   struct tm loctm;
   time( &long_time );                 /* Get time as long integer. */
   loctm = *localtime( &long_time );   /* Convert to local time. */

   dateTime->mYear = loctm.tm_year + 1900;
   dateTime->mMonth = loctm.tm_mon + 1;
   dateTime->mDay = loctm.tm_mday;
   dateTime->mHour = loctm.tm_hour;
   dateTime->mMinute = loctm.tm_min;
   dateTime->mSecond = loctm.tm_sec;
   dateTime->mSecondFrac[0] = 0;
   dateTime->mDiffHour = 0;
   dateTime->mDiffMin = 0;

   if (diffTime) {
      long diff;
      struct tm gmtm = *gmtime(&long_time);
      gmtm.tm_isdst = loctm.tm_isdst;
      diff = (long)(mktime(&loctm) - mktime(&gmtm));
      /* diff is casted to long because on some platforms the time_t is 
         unsigned (e.g. WinCE, ARM) */
      dateTime->mDiffHour = (short) (diff/3600);
      dateTime->mDiffMin = (short) (diff%60);
      dateTime->mUtcFlag = TRUE;
   }
   else {
      dateTime->mDiffHour = dateTime->mDiffMin = 0;
      dateTime->mUtcFlag = TRUE;
   }

   return (ASN_OK);
}

