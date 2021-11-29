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
#include "rtxsrc/OSRTOutputStream.h"

EXTRTMETHOD OSRTOutputStreamIF::~OSRTOutputStreamIF () {}

EXTRTMETHOD OSRTOutputStream::OSRTOutputStream ()
{
}

EXTRTMETHOD OSRTOutputStream::OSRTOutputStream (OSRTContext* mpContext, OSBOOL attachStream) : 
   OSRTStream (mpContext, attachStream)
{
}

/*
 * Virtual destructor. Closes the stream if it was opened.
 */
EXTRTMETHOD OSRTOutputStream::~OSRTOutputStream ()
{
}

EXTRTMETHOD int OSRTOutputStream::close ()
{
   return OSRTStream::close ();
}

EXTRTMETHOD int OSRTOutputStream::flush ()
{
   return OSRTStream::flush ();
}

EXTRTMETHOD OSBOOL OSRTOutputStream::isOpened ()
{
   return OSRTStream::isOpened ();
}

EXTRTMETHOD long OSRTOutputStream::write (const OSOCTET* pdata, size_t size)
{
   if (!isInitialized ()) return mInitStatus;

   long stat = rtxStreamWrite (mpContext->getPtr (), pdata, size);

   if (stat < 0) {
      mStatus = (int)stat;
      return LOG_RTERR (mpContext->getPtr (), mStatus);
   }
   else
      mStatus = 0;

   return stat;
}
