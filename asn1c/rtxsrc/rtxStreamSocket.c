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

#include <stdio.h>
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxSocket.h"
#include "rtxsrc/rtxStreamSocket.h"

#ifndef _WIN32
#include <unistd.h> /* for sleep */
#endif

#define MAX_CONNECT_ATTEMPTS    3

typedef struct SocketDesc {
   OSCTXT *pctxt;
   OSRTSOCKET socket;
   OSBOOL ownSocket;
} SocketDesc;

static long socketWrite 
(OSRTSTREAM* pStream, const OSOCTET* data, size_t numocts)
{
   SocketDesc* sdesc;
   int stat;
   
   if (pStream->id != OSRTSTRMID_SOCKET || 
       !(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return RTERR_INVPARAM;

   sdesc = (SocketDesc*) pStream->extra;

   if ((stat = rtxSocketSend (sdesc->socket, data, (int)numocts)) != 0)
      return stat;

   return 0;
}

static long socketRead (OSRTSTREAM* pStream, OSOCTET* pbuffer, size_t bufSize)
{
   SocketDesc* sdesc;
   
   if (pStream->id != OSRTSTRMID_SOCKET || 
       !(pStream->flags & OSRTSTRMF_INPUT)) 
      return RTERR_INVPARAM;

   sdesc = (SocketDesc*) pStream->extra;
   return rtxSocketRecv (sdesc->socket, pbuffer, (int)bufSize);
}

static long socketBlockingRead 
(OSRTSTREAM* pStream, OSOCTET* pbuffer, size_t readBytes)
{
   SocketDesc* sdesc;
   size_t curlen = 0;
   
   if (pStream->id != OSRTSTRMID_SOCKET || 
       !(pStream->flags & OSRTSTRMF_INPUT)) 
      return RTERR_INVPARAM;

   sdesc = (SocketDesc*) pStream->extra;

   while (curlen < readBytes) {
      int len = rtxSocketRecv (sdesc->socket, 
         pbuffer + curlen, (int)(readBytes - curlen));
      if (len < 0) return len; /* < 0 - error  */
      if (len == 0) break;     /* ==0 - closed */
      curlen += len;
   }

   if (curlen != readBytes)
      return RTERR_READERR;

   return (long)curlen;
}

static int socketSkip (OSRTSTREAM* pStream, size_t skipBytes)
{
   SocketDesc* sdesc;
   OSOCTET buf[128];
   
   if (pStream->id != OSRTSTRMID_SOCKET || 
       !(pStream->flags & OSRTSTRMF_INPUT)) 
      return RTERR_INVPARAM;

   sdesc = (SocketDesc*) pStream->extra;

   while (skipBytes > 0) {
      int len = rtxSocketRecv (sdesc->socket, (OSOCTET*)buf, sizeof (buf));
      if (len < 0) return len;
      skipBytes -= len;
   }

   return 0;
}

static int socketFlush (OSRTSTREAM* pStream)
{
   if (0 != pStream) /* workaround for VC++ level 4 warning */
      ;
   return 0;
}

static int socketClose (OSRTSTREAM* pStream)
{
   SocketDesc* sdesc;
   int stat = 0;
   
   if (pStream->id != OSRTSTRMID_SOCKET) 
      return RTERR_INVPARAM;

   sdesc = (SocketDesc*) pStream->extra;
   if (0 == sdesc) return 0;

   if (sdesc->ownSocket) {
      stat = rtxSocketClose (sdesc->socket);
   }
   rtxMemFreePtr (sdesc->pctxt, pStream->extra);
   pStream->extra = 0;

   return stat;
}

EXTRTMETHOD int rtxStreamSocketAttach (OSCTXT* pctxt, OSRTSOCKET socket, OSUINT16 flags)
{
   OSRTSTREAM *pStream;
   SocketDesc* sdesc;

   if (0 == pctxt->pStream) {
      int stat = rtxStreamInit (pctxt);
      if (0 != stat) return LOG_RTERR (pctxt, stat);
   }
   pStream = pctxt->pStream;

   if (socket == OSRTSOCKET_INVALID) 
      return LOG_RTERRNEW (pctxt, RTERR_INVSOCKET);

   sdesc = rtxMemAllocType (pctxt, SocketDesc);
   if (sdesc == NULL)
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   rtxMemHeapMarkSaved (&pctxt->pMemHeap, sdesc, TRUE);
   sdesc->pctxt = pctxt;
   sdesc->socket = socket;
   sdesc->ownSocket = TRUE;

   if (flags & OSRTSTRMF_INPUT) {
      pctxt->buffer.size = 0;
      pStream->read  = socketRead;
      pStream->blockingRead = socketBlockingRead;
      pStream->skip  = socketSkip;
   }
   if (flags & OSRTSTRMF_OUTPUT) {
      pStream->write = socketWrite;
      pStream->flush = socketFlush;
   }

   pStream->flags = flags;
   pStream->id    = OSRTSTRMID_SOCKET;
   pStream->extra = sdesc;
   pStream->close = socketClose;
   return 0;
}

EXTRTMETHOD int rtxStreamSocketClose (OSCTXT* pctxt)
{
   int stat;

#ifndef _WIN32
   /* We need to add the delay to avoid a bug in some Unix systems when
    * the socket is closed quickly before connection is actually accepted.
    * In this case 'accept()' returns the error and errno == ECONNABORTED. 
    * Client (writer) program does not receive any errors from sockets in 
    * this case. */
   sleep (2);
#endif

   stat = socketClose (pctxt->pStream);
   if (0 != stat) return LOG_RTERR (pctxt, stat);

   stat = rtxStreamClose (pctxt);
   if (0 != stat) return LOG_RTERR (pctxt, stat);
   
   return 0;
}

EXTRTMETHOD int rtxStreamSocketCreateWriter (OSCTXT* pctxt, const char* host, int port)
{
   int i, stat;
   OSRTSOCKET socket;

   if (0 != pctxt->pStream) {
      return LOG_RTERR (pctxt, RTERR_STRMINUSE);
   }

   stat = rtxSocketCreate (&socket);
   if (0 != stat) return LOG_RTERR (pctxt, stat);

   RTDIAG3 (pctxt, "Connecting to %s:%i..", host, port);
   for (i = 0; i < MAX_CONNECT_ATTEMPTS; i++) {
      stat = rtxSocketConnect (socket, host, port);
      if (0 != stat) {
         if (i + 1 == MAX_CONNECT_ATTEMPTS) {
            RTDIAG2 (pctxt, "\nConnection failed, error code is %i\n", stat);
            return LOG_RTERR (pctxt, stat);
         }
      }
      else break;
   }
   RTDIAG1 (pctxt, "\nConnection established.\n");

   rtxStreamInit (pctxt);

   stat = rtxStreamSocketAttach (pctxt, socket, OSRTSTRMF_OUTPUT);

   if (0 != stat) return LOG_RTERR (pctxt, stat);

   return 0;
}

EXTRTMETHOD int rtxStreamSocketSetOwnership (OSCTXT* pctxt, OSBOOL ownSocket)
{
   SocketDesc* sdesc;

   if (0 == pctxt->pStream || 0 == pctxt->pStream->extra) {
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);
   }
   sdesc = (SocketDesc*)pctxt->pStream->extra;
   sdesc->ownSocket = ownSocket;
   return 0;
}

