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

#include "rtxsrc/OSRTSocket.h"
#include "rtxsrc/rtxMemory.h"

EXTRTMETHOD OSRTSocket::OSRTSocket () : mSocket (OSRTSOCKET_INVALID), mOwner (TRUE)
{
   rtxSocketsInit ();
   mInitStatus = mStatus = rtxSocketCreate (&mSocket);
}

EXTRTMETHOD OSRTSocket::OSRTSocket (OSRTSOCKET socket, OSBOOL ownership) : 
   mSocket (socket), mOwner (ownership), mStatus (0)
{
   rtxSocketsInit ();
   mInitStatus = mStatus;
}

EXTRTMETHOD OSRTSocket::OSRTSocket (const OSRTSocket& socket) :
   mSocket (socket.mSocket), mOwner (FALSE), mStatus (0),
   mInitStatus (socket.mInitStatus)
{
   rtxSocketsInit ();
}

EXTRTMETHOD OSRTSocket::~OSRTSocket ()
{
   if (mOwner && mSocket != OSRTSOCKET_INVALID)
      close ();
}

EXTRTMETHOD OSRTSocket* OSRTSocket::accept (OSIPADDR* destIP, int *port)
{
   OSRTSOCKET sock;

   if (!isInitialized ()) return 0;

   mStatus = rtxSocketAccept (mSocket, &sock, destIP, port);
   if (mStatus != 0) return 0;

   return new OSRTSocket (sock, TRUE);
}

EXTRTMETHOD const char* OSRTSocket::addrToString (OSIPADDR ipAddr, 
                                     char* pAddrStr, 
                                     int bufsize)
{
   return (rtxSocketAddrToStr (ipAddr, pAddrStr, bufsize) != 0) ?
      0 : pAddrStr;
}

EXTRTMETHOD int OSRTSocket::bind (OSIPADDR addr, int port) 
{
   if (!isInitialized ()) return mInitStatus;

   return (mStatus = rtxSocketBind (mSocket, addr, port));
}

EXTRTMETHOD int OSRTSocket::bind (const char* pAddrStr, int port) 
{
   OSIPADDR ipAddr = OSIPADDR_ANY;

   if (!isInitialized ()) return mInitStatus;

   if (pAddrStr != 0) {
      if ((mStatus = rtxSocketStrToAddr (pAddrStr, &ipAddr)) != 0)
         return mStatus;
   }
   mStatus = rtxSocketBind (mSocket, ipAddr, port);
   return mStatus;
}

EXTRTMETHOD int OSRTSocket::close ()
{
   if (!isInitialized ()) return mInitStatus;

   if (mSocket != OSRTSOCKET_INVALID) {
      mStatus = rtxSocketClose (mSocket);

      mSocket = OSRTSOCKET_INVALID;
   }
   else
      mStatus = 0;

   return mStatus;
}

EXTRTMETHOD int OSRTSocket::listen (int maxConnections)
{
   if (!isInitialized ()) return mInitStatus;

   mStatus = rtxSocketListen (mSocket, maxConnections);
   return mStatus;
}

EXTRTMETHOD int OSRTSocket::connect (const char* host, int port)
{
   if (!isInitialized ()) return mInitStatus;

   mStatus = rtxSocketConnect (mSocket, host, port);
   return mStatus;
}

EXTRTMETHOD int OSRTSocket::recv (OSOCTET* pbuf, OSUINT32 bufsize)
{
   if (!isInitialized ()) return mInitStatus;

   int len = rtxSocketRecv (mSocket, pbuf, bufsize);
   mStatus = (len < 0) ? len : 0;
   return len;
}

EXTRTMETHOD int OSRTSocket::blockingRead (OSOCTET* pbuf, size_t readBytes)
{
   if (!isInitialized ()) return mInitStatus;

   int len;
   size_t rlen = 0;
   while (rlen < readBytes) {
      len = OSRTSocket::recv (pbuf+rlen, readBytes-rlen);
      if (len < 0) {
         mStatus = len; return len;
      }
      else if (len > 0) {
         rlen += len;
      }
      else break;
   }

   return rlen;
}

EXTRTMETHOD int OSRTSocket::send (const OSOCTET* pdata, OSUINT32 size)
{
   if (!isInitialized ()) return mInitStatus;

   mStatus = rtxSocketSend (mSocket, pdata, size);
   return mStatus;
}

EXTRTMETHOD OSIPADDR OSRTSocket::stringToAddr (const char* pAddrStr)
{
   int stat;
   OSIPADDR ipAddr;

   if ((stat = rtxSocketStrToAddr (pAddrStr, &ipAddr)) != 0)
      return (OSIPADDR)-1;

   return ipAddr;
}
