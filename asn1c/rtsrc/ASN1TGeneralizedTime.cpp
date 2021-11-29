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

//////////////////////////////////////////////////////////////////////
//
// ASN1CGeneralizedTime
// 
// ISO 8601 time and date for ITU-T X.680. 
//
// Author Artem Bolgar.
// version 2.17   11 Nov, 2003 (sscanf parameters changed to int from short;
//                              secFraction now may contain more than one 
//                              digit)
// version 2.15    4 Sep, 2003 (rtxsrc/wceAddon.h include added)
// version 2.14   31 Jul, 2003 (leap year bug fixed in addDays)
// version 2.13   11 Jul, 2003 (2038 year problem fixed + some other fixes)
// version 2.12   03 Aug, 2002 (copy ctor, some fixes)
//
// History:
// version 1.11   3 Aug, 2002 (copy ctor)
// version 1.08   5 Jun, 2002 (some warnings on Solaris were eliminated)
// version 1.07   5 Jan, 2002
//

#include <stdio.h>
#include <stdlib.h>
#include "rtsrc/ASN1TTime.h"
#include "rtxsrc/rtxCtype.h"
#include "rtsrc/asn1intl.h"

#if defined(_WIN32_WCE)
#include "rtxsrc/wceAddon.h"
#endif

EXTRTMETHOD ASN1TGeneralizedTime::ASN1TGeneralizedTime 
   (const char* timeStr, OSBOOL useDerRules) :
   ASN1TTime (useDerRules)
{
   ASN1TGeneralizedTime::parseString (timeStr);
} 

/* 
* Parses string. 
* Returns: 0 - if success;
*          RTERR_INVFORMAT - if value is invalid.
*/
EXTRTMETHOD int ASN1TGeneralizedTime::parseString (const char* str) {
   int year_, month_, day_, hour_, minute_, second_, secFraction_;
   int diffHour_, diffMin_, secFracLen_;

   year_ = month_ = day_ = hour_ = RTERR_IDNOTFOU;
   minute_ = second_ = secFraction_ = secFracLen_ = diffHour_ = diffMin_ = 0;
   mbUtcFlag = FALSE;
   if (str == 0) return LOG_TTMERR (0);

   const char* p = str;
   if (sscanf(p, "%4d%2d%2d", &year_, &month_, &day_) == 3) {
      p += 8;
      if (year_ < 0)
         return LOG_TTMERR (RTERR_INVFORMAT);
      if (month_ < 1 || month_ > 12)
         return LOG_TTMERR (RTERR_INVFORMAT);
      int dim = daysInMonth(month_); 
      // check for February of leap-year
      if (month_ == 2 && year_%4 == 0 && (year_%100 != 0 || year_%400 == 0))
         dim++;
      if (day_ < 1 || day_ > dim)
         return LOG_TTMERR (RTERR_INVFORMAT);
      int n = 0;
      if (OS_ISDIGIT(*p) && sscanf(p, "%2d", &hour_) >= 1) {
         p += 2;
         n++;
      }
      else 
         return LOG_TTMERR (RTERR_INVFORMAT);
      if (OS_ISDIGIT(*p) && sscanf(p, "%2d", &minute_) >= 1) {
         p += 2;
         n++;
         if (OS_ISDIGIT(*p) && sscanf(p, "%2d", &second_) >= 1) {
            p += 2;
            n++;
         }
      }
      if (n >= 1 && (hour_ < 0 || hour_ > 23))
         return LOG_TTMERR (RTERR_INVFORMAT);
      if (n >= 2 && (minute_ < 0 || minute_ > 59))
         return LOG_TTMERR (RTERR_INVFORMAT);
      if (n == 3 && (second_ < 0 || second_ > 59))
         return LOG_TTMERR (RTERR_INVFORMAT);

      if (*p == ',' && mbDerRules)
         return LOG_TTMERR (RTERR_INVFORMAT);
      if (*p == '.' || *p == ',') { // fraction
         p++;
         int frac = 0;
         if (n >= 3) {
            for (;*p != 0 && OS_ISDIGIT(*p); p++, secFracLen_++) {
               frac *= 10;
               frac += (*p) - '0';
            }
            secFraction_ = frac;
         }
         else
            return LOG_TTMERR (RTERR_INVFORMAT);
      }
      if (*p == 'Z') { // utc
         p++;
         mbUtcFlag = TRUE;
         if (*p != 0)
            return LOG_TTMERR (RTERR_INVFORMAT);
      }
      else {
         if (mbDerRules) // DER/CER/PER time should be terminated with 'Z'!
            return LOG_TTMERR (RTERR_INVFORMAT);
         mbUtcFlag = FALSE;
         char sign = *p;
         if (sign == '-' || sign == '+') {
            p++;
            if (!OS_ISDIGIT(*p) || sscanf(p, "%2d", &diffHour_) != 1)
               return LOG_TTMERR (RTERR_INVFORMAT);
            p += 2;
            if (diffHour_ < 0 || diffHour_ > 12)
               return LOG_TTMERR (RTERR_INVFORMAT);
            if (OS_ISDIGIT(*p)) {
               if (sscanf(p, "%2d", &diffMin_) != 1)
                  return LOG_TTMERR (RTERR_INVFORMAT);
               if (diffMin_ < 0 || diffMin_ > 59)
                  return LOG_TTMERR (RTERR_INVFORMAT);
               }
            if (sign == '-') {
               diffHour_ = -diffHour_;
               diffMin_ = -diffMin_;
            }
         }
      }
   }
   mYear = (short) year_;
   mMonth = (short) month_;
   mDay = (short) day_;
   mHour = (short) hour_;
   mMinute = (short) minute_;
   mSecond = (short) second_;
   mDiffHour = (short) diffHour_;
   mDiffMin = (short) diffMin_;
   mSecFraction = secFraction_;
   mSecFracLen = secFracLen_;
   return LOG_TTMERR (0);
}

/* 
* Gets century part of the year (first 2 digits of the year). 
* Returns: first 2 digits of the year - if success;
*          error code - if parsed value is invalid.
*/
EXTRTMETHOD int ASN1TGeneralizedTime::getCentury() const {
   if (mStatus == RTERR_NOTINIT) return mStatus;

   int year_ = getYear();
   if (year_ < 0)
      return year_;
   return mYear/100;
}

/*
* Sets century part of the year (first 2 digits).
* Returns 0, if succeed, or error code, if error.
*/
EXTRTMETHOD int ASN1TGeneralizedTime::setCentury(int century) {
   if (century < 0 || century > 99)
      return LOG_TTMERR (RTERR_INVFORMAT);
   mYear = century*100 + mYear%100;
   return 0;
}

/* 
* Converts time_t to time string.
* Parameter 'diffTime' == TRUE means the difference between local time 
*   and UTC will be calculated; in other case only local time
*   will be stored.
* Returns 0, if succeed, or error code, if error.
*/
EXTRTMETHOD int ASN1TGeneralizedTime::setTime(time_t time, OSBOOL diffTime) {
   struct tm loctm = *localtime(&time);
   if (diffTime || mbDerRules) {
      struct tm gmtm = *gmtime(&time);
      gmtm.tm_isdst = loctm.tm_isdst;
      long diff = (long)(mktime(&loctm) - mktime(&gmtm));
      // diff is casted to long because on some platforms the time_t is 
      // unsigned (e.g. WinCE, ARM)
      mDiffHour = (short) (diff/3600);
      mDiffMin = (short) (diff%60);
   }
   else {
      mDiffHour = mDiffMin = 0;
      mbUtcFlag = FALSE;
   }
   mYear = loctm.tm_year + 1900;
   mMonth = loctm.tm_mon + 1;
   mDay = loctm.tm_mday;
   mHour = loctm.tm_hour;
   mMinute = loctm.tm_min;
   mSecond = loctm.tm_sec;
   mSecFraction = mSecFracLen = 0;
   return LOG_TTMERR (0);
}

/*
* Compiles new time string accoring X.680 (clause 41) and ISO 8601.
* Returns 0, if succeed, or error code, if error.
*/
EXTRTMETHOD int ASN1TGeneralizedTime::compileString (char* pbuf, size_t bufsize) const {
   if (mYear < 0 || mMonth <= 0 || mDay <= 0 || mHour < 0)
      return RTERR_INVFORMAT;

   size_t cursize = 11; // incl trailing zero
   if (bufsize < cursize)
      return RTERR_BUFOVFLW;

   char* p = pbuf;
   short minute_;
   const char* ymdh = "%.4d%.2d%.2d%.2d";
   if ((mbDerRules || mbUtcFlag) && (mDiffHour || mDiffMin)) {
      // we need to recalculate time with zone offset
      short year_ = mYear;
      short month_ = mMonth;
      short day_ = mDay;
      short hour_ = mHour;
      minute_ = mMinute;
      short second_ = mSecond;
      int secFr_ = mSecFraction;
      addMilliseconds (-(mDiffHour * 60 + mDiffMin) * 60 * 1000L, 
                       year_, month_, day_, hour_, minute_, second_, secFr_,
                       mSecFracLen);
      sprintf(p, ymdh, year_, month_, day_, hour_);
   }
   else {
      minute_ = this->mMinute;
      sprintf(p, ymdh, mYear, mMonth, mDay, mHour);
   }

   p += 10;

   if (mbDerRules || minute_ > 0 || mSecond > 0 || 
       (mSecFraction > 0 && mSecFracLen > 0)) 
   {
      cursize += 2;
      if (bufsize < cursize)
         return RTERR_BUFOVFLW;
      sprintf(p, "%.2d", minute_);
      p += 2;
      if (mbDerRules || mSecond > 0 || (mSecFraction > 0 && mSecFracLen > 0)) {
         cursize += 2;
         if (bufsize < cursize)
            return RTERR_BUFOVFLW;
         sprintf(p, "%.2d", mSecond);
         p += 2;
         if (mSecFraction > 0 && mSecFracLen > 0) {
            char sfb[30];
            int sfsz;
            
            sfsz = getFractionStr (sfb, sizeof (sfb));
            cursize += sfsz + 1; // +1 is for '.'
            if (sfsz < 0 || bufsize < cursize) 
               return RTERR_BUFOVFLW;

            strcpy (p++, ".");
            strcpy (p, sfb);
            p += sfsz;
         }
      }
   }
   if (mbDerRules || mbUtcFlag) { 
      cursize++;
      if (bufsize < cursize)
         return RTERR_BUFOVFLW;
      *p++ = 'Z'; *p = 0; 
   }
   else if (mDiffHour || mDiffMin) {
      cursize += 1 + 2 + ((mDiffMin)?2:0);
      if (bufsize < cursize)
         return RTERR_BUFOVFLW;
      *p++ = (mDiffHour > 0) ? '+' : '-';
      if (mDiffMin)
         sprintf(p, "%.2d%.2d", abs(mDiffHour), abs(mDiffMin));
      else
         sprintf(p, "%.2d", abs(mDiffHour));
   }
   return 0;
}
