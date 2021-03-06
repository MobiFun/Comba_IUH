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

#include "rtxsrc/rtxStreamSocket.h"
#include "rtxsrc/OSRTSocketOutputStream.h"

EXTRTMETHOD OSRTSocketOutputStream::OSRTSocketOutputStream (OSRTSocket& socket) :
   mSocket (socket)
{
   if (!isInitialized ()) return;

   mStatus = mInitStatus = rtxStreamSocketAttach 
      (mpContext->getPtr (), mSocket.getSocket (), OSRTSTRMF_OUTPUT);
   if (mInitStatus != 0) LOG_RTERR (mpContext->getPtr (), mInitStatus);
}

EXTRTMETHOD OSRTSocketOutputStream::OSRTSocketOutputStream 
   (OSRTContext* pContext, OSRTSocket& socket) :
   OSRTOutputStream (pContext), mSocket (socket)
{
   if (!isInitialized ()) return;

   mStatus = mInitStatus = rtxStreamSocketAttach 
      (mpContext->getPtr (), mSocket.getSocket (), OSRTSTRMF_OUTPUT);
   if (mInitStatus != 0) LOG_RTERR (mpContext->getPtr (), mInitStatus);
}

EXTRTMETHOD OSRTSocketOutputStream::OSRTSocketOutputStream 
   (OSRTSOCKET socket, OSBOOL ownership) :
   mSocket (socket, ownership)
{
   if (!isInitialized ()) return;

   mStatus = mInitStatus = rtxStreamSocketAttach 
      (mpContext->getPtr (), mSocket.getSocket (), OSRTSTRMF_OUTPUT);
   if (mInitStatus != 0) LOG_RTERR (mpContext->getPtr (), mInitStatus);
}

OSRTSocketOutputStream::OSRTSocketOutputStream 
   (OSRTContext* pContext, OSRTSOCKET socket, OSBOOL ownership) :
   OSRTOutputStream (pContext), mSocket (socket, ownership)
{
   if (!isInitialized ()) return;

   mStatus = mInitStatus = rtxStreamSocketAttach 
      (mpContext->getPtr (), mSocket.getSocket (), OSRTSTRMF_OUTPUT);
   if (mInitStatus != 0) LOG_RTERR (mpContext->getPtr (), mInitStatus);
}

