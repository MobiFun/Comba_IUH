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
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxStreamFile.h"

typedef struct FileDesc {
   OSCTXT* pctxt;
   FILE* fp;
   OSBOOL attached;
   long savedIndex;
} FileDesc;

static long fileWrite (OSRTSTREAM* pStream, const OSOCTET* data, size_t numocts)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_FILE || !(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return RTERR_INVPARAM;
   if (fwrite (data, 1, numocts, fdesc->fp) < numocts)
      return RTERR_WRITEERR;
   return 0;
}

static long fileRead (OSRTSTREAM* pStream, OSOCTET* pbuffer, 
                     size_t bufSize)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;
   long readBytes;

   if (pStream->id != OSRTSTRMID_FILE || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   readBytes = (long)fread (pbuffer, 1, bufSize, fdesc->fp);
   if (ferror (fdesc->fp) != 0)
      return RTERR_READERR;
   return readBytes;
}

static int fileSkip (OSRTSTREAM* pStream, size_t skipBytes)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_FILE || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   if (fseek (fdesc->fp, (long)skipBytes, SEEK_CUR))
      return RTERR_READERR;
   return 0;
}

static int fileFlush (OSRTSTREAM* pStream)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_FILE) 
      return RTERR_INVPARAM;
   fflush (fdesc->fp);
   return 0;
}

static int fileClose (OSRTSTREAM* pStream)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_FILE) 
      return RTERR_INVPARAM;
   if (!fdesc->attached)
      fclose (fdesc->fp);
   rtxMemFreePtr (fdesc->pctxt, pStream->extra);
   return 0;
}

static int fileMark (OSRTSTREAM* pStream, size_t readAheadLimit)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_FILE || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   fdesc->savedIndex = ftell (fdesc->fp);
   if (fdesc->savedIndex < 0) return RTERR_READERR;

   pStream->readAheadLimit = readAheadLimit;
   pStream->markedBytesProcessed = pStream->bytesProcessed;
   return 0;
}

static int fileReset (OSRTSTREAM* pStream)
{
   FileDesc* fdesc = (FileDesc*)pStream->extra;

   if (fdesc->savedIndex < 0) 
      return RTERR_INVPARAM;

   if (fseek (fdesc->fp, fdesc->savedIndex, SEEK_SET) != 0) 
      return RTERR_READERR;
   
   pStream->bytesProcessed = pStream->markedBytesProcessed;
   fdesc->savedIndex = 0;
   pStream->readAheadLimit = INT_MAX;
   pStream->flags |= OSRTSTRMF_POSMARKED;
   return 0;
}

EXTRTMETHOD int rtxStreamFileOpen (OSCTXT* pctxt, const char* pFilename, OSUINT16 flags)
{
   OSRTSTREAM* pStream;
   FILE* fp;
   FileDesc* fdesc;

   if (pFilename == 0)
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (0 == pctxt->pStream) {
      int stat = rtxStreamInit (pctxt);
      if (0 != stat) return LOG_RTERR (pctxt, stat);
   }
   pStream = pctxt->pStream;

   if (flags & OSRTSTRMF_OUTPUT) {
      fp = fopen (pFilename, "wb");
      pStream->write = fileWrite;
      pStream->flush = fileFlush;
   }
   else if (flags & OSRTSTRMF_INPUT) {
      fp = fopen (pFilename, "rb");
      pStream->read  = fileRead;
      pStream->blockingRead  = fileRead;
      pStream->skip  = fileSkip;
      pStream->mark  = fileMark;
      pStream->reset  = fileReset;
      pctxt->buffer.size = 0;
   }
   else 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (fp == 0) 
      return LOG_RTERRNEW (pctxt, RTERR_FILNOTFOU);

   fdesc = rtxMemAllocType (pctxt, FileDesc);
   if (fdesc == NULL) {
      fclose (fp);
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   }
   rtxMemHeapMarkSaved (&pctxt->pMemHeap, fdesc, TRUE);

   fdesc->pctxt = pctxt;
   fdesc->fp = fp;
   fdesc->attached = FALSE;
   fdesc->savedIndex = 0;

   pStream->flags = (OSUINT16) (flags | OSRTSTRMF_POSMARKED);
   pStream->id    = OSRTSTRMID_FILE;
   pStream->extra = fdesc;
   pStream->close = fileClose;
   return 0;
}

EXTRTMETHOD int rtxStreamFileAttach (OSCTXT* pctxt, FILE* pFile, OSUINT16 flags)
{
   OSRTSTREAM *pStream;
   FileDesc* fdesc;

   if (0 == pctxt->pStream) {
      int stat = rtxStreamInit (pctxt);
      if (0 != stat) return LOG_RTERR (pctxt, stat);
   }
   pStream = pctxt->pStream;

   if (pFile == 0 || 
      (!(flags & OSRTSTRMF_OUTPUT) && !(flags & OSRTSTRMF_INPUT)))
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   fdesc = rtxMemAllocType (pctxt, FileDesc);
   if (fdesc == NULL)
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   rtxMemHeapMarkSaved (&pctxt->pMemHeap, fdesc, TRUE);
   fdesc->pctxt = pctxt;
   fdesc->fp = pFile;
   fdesc->attached = TRUE;
   fdesc->savedIndex = 0;

   if (flags & OSRTSTRMF_OUTPUT) {
      pStream->write = fileWrite;
      pStream->flush = fileFlush;
   }
   else if (flags & OSRTSTRMF_INPUT) {
      pStream->read  = fileRead;
      pStream->blockingRead  = fileRead;
      pStream->skip  = fileSkip;
      pStream->mark  = fileMark;
      pStream->reset  = fileReset;
      pctxt->buffer.size = 0;
   }
   pStream->flags = (OSUINT16) (flags | OSRTSTRMF_POSMARKED);
   pStream->id    = OSRTSTRMID_FILE;
   pStream->extra = fdesc;
   pStream->close = fileClose;
   return 0;
}

EXTRTMETHOD int rtxStreamFileCreateReader (OSCTXT* pctxt, const char* pFilename)
{
   return rtxStreamFileOpen (pctxt, pFilename, OSRTSTRMF_INPUT);
}

EXTRTMETHOD int rtxStreamFileCreateWriter (OSCTXT* pctxt, const char* pFilename)
{
   return rtxStreamFileOpen (pctxt, pFilename, OSRTSTRMF_OUTPUT);
}

