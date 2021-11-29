#if defined(_WIN32_WCE)
/* This file adds some functionality to Windows CE. Windows CE does not support
 * all time-related Run-Time functions. It also does not support abort function.
 * This file adds some of these functions. */
#include <windows.h>
#include "rtxsrc/wceAddon.h"
#include "rtxsrc/rtxCommon.h" // OSCRTL* macros

#define INT64 __int64
            
const INT64 n1SecIn100NS = (INT64)10000000;

const int days[]           = {-1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364};
const int leapYearDays[]   = {-1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
const int DAY_MILLISEC     = (24L * 60L * 60L * 1000L);
const int BASE_DOW         = 4;   /* 01-01-70 was a Thursday */
const int LEAP_YEAR_ADJUST = 17L; /* Leap years 1900 - 1970  */
static TIME_ZONE_INFORMATION g_TZInfoCache; /* ok to not be thread-safe */
static BOOL g_bTZInfoCacheInitialized = FALSE;
BOOL g_bUseDST = TRUE;
static INT64 yearOffset  = -1;

static INT64 getDiffSecs (FILETIME f1, FILETIME f2)
{
   INT64 t1 = f1.dwHighDateTime;
   INT64 t2 = f2.dwHighDateTime;

   /* Stuff the 2 FILETIMEs into their own __int64s. */
   t1 <<= 32;           
   t1 |= f1.dwLowDateTime;

   t2 <<= 32;           
   t2 |= f2.dwLowDateTime;

   /* Take the difference of 64-bit ints.
      This should be the number of 100-nanosecond intervals since Jan. 1970.
      Divide by 10,000,000 to get the number of seconds since Jan. 1970. */
   return (t2 - t1) / n1SecIn100NS;
}

static SYSTEMTIME tmToSystemTime (struct tm *t)
{
   SYSTEMTIME st;

   st.wYear      = t->tm_year + 1900;
   st.wMonth     = t->tm_mon+1;
   st.wDayOfWeek = t->tm_wday;
   st.wDay       = t->tm_mday;
   st.wHour      = t->tm_hour;
   st.wMinute    = t->tm_min;
   st.wSecond    = t->tm_sec;
   st.wMilliseconds = 0; 
   return st;
}

static FILETIME yearToFileTime (WORD year)
{  
   SYSTEMTIME st;
   FILETIME   ft;

   st.wYear         = year;
   st.wMonth        = 1;
   st.wDayOfWeek    = 1; /* ? */
   st.wDay          = 1;
   st.wHour         = 0;
   st.wMinute       = 0;
   st.wSecond       = 0;
   st.wMilliseconds = 0;

   SystemTimeToFileTime (&st, &ft);

   return ft;
}

static FILETIME int64ToFileTime (INT64 time)
{
   FILETIME ft;

   ft.dwHighDateTime = (DWORD)((time >> 32) & 0x00000000FFFFFFFF);
   ft.dwLowDateTime  = (DWORD)(time & 0x00000000FFFFFFFF);

   return ft;
}


static time_t systemTimeToYDay (SYSTEMTIME* st)
{
   FILETIME fMidnightJan1 = yearToFileTime(st->wYear);
   FILETIME ft;              
   
   SystemTimeToFileTime(st, &ft);
   return (time_t)(getDiffSecs(fMidnightJan1, ft) / (INT64)86400);
}

static struct tm systemTimeToTm (SYSTEMTIME* st)
{
   struct tm t;

   t.tm_year  = st->wYear - 1900;
   t.tm_mon   = st->wMonth-1;
   t.tm_wday  = st->wDayOfWeek;
   t.tm_mday  = st->wDay;
   t.tm_yday  = systemTimeToYDay (st);
   t.tm_hour  = st->wHour;
   t.tm_min   = st->wMinute;
   t.tm_sec   = st->wSecond;
   t.tm_isdst = 0; // ignored

   return t;
}

static void getTZBias (int* ptzBiasSecs, int* pdstBiasSecs)
{
   if(!g_bTZInfoCacheInitialized) {
      // WinCE: GetTimeZoneInformation is expensive, so we call it only once.
      if( GetTimeZoneInformation(&g_TZInfoCache) == 0xFFFFFFFF)
         return;
      g_bTZInfoCacheInitialized = TRUE;
   }

   if(ptzBiasSecs != NULL) {
      *ptzBiasSecs = g_TZInfoCache.Bias * 60;
      if (g_TZInfoCache.StandardDate.wMonth != 0)
         *ptzBiasSecs += (g_TZInfoCache.StandardBias * 60);
   }

   if(pdstBiasSecs != NULL) {
      if ((g_TZInfoCache.DaylightDate.wMonth != 0) && (g_TZInfoCache.DaylightBias != 0))
         *pdstBiasSecs = (g_TZInfoCache.DaylightBias - g_TZInfoCache.StandardBias) * 60;
      else
         *pdstBiasSecs = 0;
   }
}


typedef struct {
   int  yr;        // year of interest
   int  yd;        // day of year 
   long ms;        // milli-seconds in the day 
} transitionTime;

static void cvtdate (int trantype, int year, int month, int week, int dayofweek,
                     int date, int hour, int min, int sec, int msec,
                     transitionTime* pDST)
{
   BOOL bIsLeapYear = ((year & 3) == 0);
   int yearday;
   int monthdow;
   int dstBiasSecs;

   getTZBias (0, &dstBiasSecs);

   yearday = 1 + (bIsLeapYear ? leapYearDays[month - 1] : days[month - 1]);
   monthdow = (yearday + ((year - 70) * 365) + ((year - 1) >> 2) -
            LEAP_YEAR_ADJUST + BASE_DOW) % 7;
   if (monthdow <= dayofweek)
      yearday += (dayofweek - monthdow) + (week - 1) * 7;
   else 
      yearday += (dayofweek - monthdow) + week * 7;

   if ((week == 5) && (yearday > (bIsLeapYear ? leapYearDays[month] : days[month])))
      yearday -= 7;

   if (trantype == 1) {   // Converted date was for the start of DST
      pDST->yd = yearday;
      pDST->ms = (long)msec + (1000L * (sec + 60L * (min + 60L * hour)));
      pDST->yr = year;
   }
   else {   // Converted date was for the end of DST
      pDST->yd = yearday;
      pDST->ms = (long)msec + (1000L * (sec + 60L * (min + 60L * hour)));
      if ((pDST->ms += (dstBiasSecs * 1000L)) < 0) {
         pDST->ms += DAY_MILLISEC;
         pDST->ms--;
      }
      else if (pDST->ms >= DAY_MILLISEC) {
         pDST->ms -= DAY_MILLISEC;
         pDST->ms++;
      }
      pDST->yr = year;
   }
}

int rtWCEIsindst (struct tm *pt)
{
   transitionTime dstStart = { -1, 0, 0L }, dstEnd = { -1, 0, 0L };
   long ms;

   if(!g_bUseDST) 
      return 0;

   if(!g_bTZInfoCacheInitialized)
      getTZBias (0, 0);

   if((pt->tm_year != dstStart.yr) || (pt->tm_year != dstEnd.yr)) {  
      if (g_TZInfoCache.DaylightDate.wYear != 0 || g_TZInfoCache.StandardDate.wYear != 0)
         return 0;

      cvtdate(1,
               pt->tm_year,
               g_TZInfoCache.DaylightDate.wMonth,
               g_TZInfoCache.DaylightDate.wDay,
               g_TZInfoCache.DaylightDate.wDayOfWeek,
               0,
               g_TZInfoCache.DaylightDate.wHour,
               g_TZInfoCache.DaylightDate.wMinute,
               g_TZInfoCache.DaylightDate.wSecond,
               g_TZInfoCache.DaylightDate.wMilliseconds,
               &dstStart);

      cvtdate(0,
               pt->tm_year,
               g_TZInfoCache.StandardDate.wMonth,
               g_TZInfoCache.StandardDate.wDay,
               g_TZInfoCache.StandardDate.wDayOfWeek,
               0,
               g_TZInfoCache.StandardDate.wHour,
               g_TZInfoCache.StandardDate.wMinute,
               g_TZInfoCache.StandardDate.wSecond,
               g_TZInfoCache.StandardDate.wMilliseconds,
               &dstEnd);
   }

   if (dstStart.yd < dstEnd.yd) {
      // Northern hemisphere ordering
      if ((pt->tm_yday < dstStart.yd) || (pt->tm_yday > dstEnd.yd))
         return 0;
      if ((pt->tm_yday > dstStart.yd) && (pt->tm_yday < dstEnd.yd))
         return 1;
   }
   else {
      // Southern hemisphere ordering
      if ((pt->tm_yday < dstEnd.yd) || (pt->tm_yday > dstStart.yd))
         return 1;
      if ((pt->tm_yday > dstEnd.yd) && (pt->tm_yday < dstStart.yd))
         return 0;
   }

   ms = 1000L * (pt->tm_sec + 60L * pt->tm_min + 3600L * pt->tm_hour);

   if (pt->tm_yday == dstStart.yd) {
      if (ms >= dstStart.ms)
         return 1;
      else
         return 0;
   }
   else {
      // pt->tm_yday == dstEnd.yd
      if (ms < dstEnd.ms)
         return 1;
      else
         return 0;
   }
}

/* mktime () function replacement */
time_t rtWCEMkTime (struct tm* pt)
{
   int tzBiasSecs;
   int dstBiasSecs;
   FILETIME f1970 = yearToFileTime(1970);
   FILETIME f;
   // Convert input tm to SYSTEMTIME
   SYSTEMTIME s = tmToSystemTime (pt);

   // Fix the yday (needs to be correct in order for wce_isindst to work)
   pt->tm_yday = systemTimeToYDay (&s);

   // Convert SYSTEMTIME to FILETIME.
   SystemTimeToFileTime (&s, &f);

   // Incorporate time zone and daylight savings time
   getTZBias (&tzBiasSecs, &dstBiasSecs);
   if (rtWCEIsindst (pt))
      tzBiasSecs += dstBiasSecs;
   
   // Get the number of seconds since Jan 1, 1970
   return (time_t)(getDiffSecs(f1970, f) + tzBiasSecs);
}

/* localtime () function replacement */
struct tm* rtWCELocalTime (const time_t *ptime)
{
   static struct tm t;
   FILETIME   f;
   SYSTEMTIME s;
   int        tzBiasSecs;
   int        dstBiasSecs;
   INT64    time;

   if (yearOffset < 0) 
      yearOffset = getDiffSecs(yearToFileTime(1601), yearToFileTime(1970));

   OSCRTLMEMSET(&t, 0, sizeof(t));
   getTZBias (&tzBiasSecs, &dstBiasSecs);

   // Set time to number of 100 nanosecond intervals since Jan. 1601.
   time = ((INT64)*ptime + yearOffset - (INT64)tzBiasSecs) * n1SecIn100NS;

   f = int64ToFileTime(time);

   if(FileTimeToSystemTime(&f, &s)) {
      struct tm t2 = systemTimeToTm (&s);
      if(rtWCEIsindst (&t2)) {
         // Take DST into account
         f = int64ToFileTime(time - dstBiasSecs * n1SecIn100NS);
         FileTimeToSystemTime(&f, &s);
      }
      t = systemTimeToTm (&s);
   }

   return &t;
}

/* gmtime () function replacement */
struct tm* rtWCEGmtTime (const time_t *ptime)
{
   static struct tm t;
   FILETIME   f;
   SYSTEMTIME s;
   INT64    time;
   int dstBiasSecs;

   if (yearOffset < 0) 
      yearOffset = getDiffSecs(yearToFileTime(1601), yearToFileTime(1970));

   OSCRTLMEMSET(&t, 0, sizeof(t));
   getTZBias (NULL, &dstBiasSecs);

   // Set time to number of 100 nanosecond intervals since Jan. 1601.
   time = ((INT64)*ptime + yearOffset) * n1SecIn100NS;

   f = int64ToFileTime(time);

   if (FileTimeToSystemTime(&f, &s)) {
      struct tm t2 = systemTimeToTm (&s);
      if(rtWCEIsindst (&t2)) {
         // Take DST into account
         f = int64ToFileTime(time - dstBiasSecs * n1SecIn100NS);
         FileTimeToSystemTime(&f, &s);
      }
      t = systemTimeToTm (&s);
   }

   return &t;
}

/* time () function replacement */
time_t rtWCETime (time_t *timer)
{
   struct tm tm;  
   SYSTEMTIME s;
   time_t time;

   GetLocalTime (&s);
   tm = systemTimeToTm (&s);

   time = rtWCEMkTime (&tm);
   if (timer != NULL)
      *timer = time;

   return time;
}

/* abort () function replacement */
void rtWCEAbort (void) 
{
   exit (-1);
}
#endif /* _WIN32_WCE */

