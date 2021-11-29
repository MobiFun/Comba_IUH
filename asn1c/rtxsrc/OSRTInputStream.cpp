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

#include "rtxsrc/rtxStream.h"
#include "rtxsrc/OSRTInputStream.h"

EXTRTMETHOD OSRTInputStreamIF::~OSRTInputStreamIF () {}

EXTRTMETHOD OSRTInputStream::OSRTInputStream ()
{
}

EXTRTMETHOD OSRTInputStream::OSRTInputStream (OSRTContext* mpContext, OSBOOL attachStream) : 
   OSRTStream (mpContext, attachStream)
{
}

/*
 * Virtual destructor. Closes the stream if it was opened.
 */
EXTRTMETHOD OSRTInputStream::~OSRTInputStream ()
{
}

EXTRTMETHOD int OSRTInputStream::close ()
{
   return OSRTStream::close ();
}

EXTRTMETHOD int OSRTInputStream::flush ()
{
   return OSRTStream::flush ();
}

EXTRTMETHOD OSBOOL OSRTInputStream::isOpened ()
{
   return OSRTStream::isOpened ();
}

EXTRTMETHOD size_t OSRTInputStream::currentPos ()
{
   size_t pos;

   if (!isInitialized ()) return 0;

   mStatus = rtxStreamGetIOBytes (mpContext->getPtr (), &pos);
   if (mStatus < 0) {
      LOG_RTERR (mpContext->getPtr (), mStatus);
      return 0;
   }

   return pos;
}

EXTRTMETHOD OSBOOL OSRTInputStream::markSupported () 
{ 
   return rtxStreamMarkSupported (mpContext->getPtr ()); 
}

EXTRTMETHOD int OSRTInputStream::mark (size_t readAheadLimit) 
{ 
   if (!isInitialized ()) return mInitStatus;

   int mStatus = rtxStreamMark (mpContext->getPtr (), readAheadLimit); 
   if (mStatus < 0) return LOG_RTERR (mpContext->getPtr (), mStatus);

   return 0;
}

EXTRTMETHOD int OSRTInputStream::reset () 
{ 
   if (!isInitialized ()) return mInitStatus;

   int mStatus = rtxStreamReset (mpContext->getPtr ()); 
   if (mStatus < 0) return LOG_RTERR (mpContext->getPtr (), mStatus);

   return 0;
}

EXTRTMETHOD long OSRTInputStream::read (OSOCTET* pDestBuf, size_t maxToRead)
{
   if (!isInitialized ()) return mInitStatus;

   long stat = rtxStreamRead (mpContext->getPtr (), pDestBuf, maxToRead); 

   if (stat < 0) {
      mStatus = (int)stat;
      return LOG_RTERR (mpContext->getPtr (), mStatus);
   }
   else
      mStatus = 0;

   return stat;
}

EXTRTMETHOD long OSRTInputStream::readBlocking (OSOCTET* pDestBuf, size_t toReadBytes)
{
   if (!isInitialized ()) return mInitStatus;

   long stat = rtxStreamRead (mpContext->getPtr (), pDestBuf, toReadBytes); 

   if (stat < 0) {
      mStatus = (int)stat;
      return LOG_RTERR (mpContext->getPtr (), mStatus);
   }
   else
      mStatus = 0;

   return stat;
}

EXTRTMETHOD int OSRTInputStream::skip (size_t n) 
{
   if (!isInitialized ()) return mInitStatus;

   mStatus = rtxStreamSkip (mpContext->getPtr (), n); 
   if (mStatus < 0) return LOG_RTERR (mpContext->getPtr (), mStatus);

   return mStatus;
}
