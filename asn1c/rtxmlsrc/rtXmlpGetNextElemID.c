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

#include "rtxmlsrc/osrtxml.hh"
#include "rtxmlsrc/rtXmlPull.hh"
#include "rtxmlsrc/rtXmlErrCodes.h"

/*
 * This function should work only inside the current level. 
 * Once the start or end tag parsed is out of scope of current level
 * this function returns.
 */
EXTXMLMETHOD int rtXmlpGetNextElemID 
(OSCTXT* pctxt, const OSXMLElemIDRec* tab, size_t nrows, OSINT32 level, 
 OSBOOL continueParse)
{
   struct OSXMLReader* pXmlReader;
   OSXMLStrFragment localName;
   OSINT16 nsIndex;
   OSINT32 curLevel;
   int stat = 0;
   size_t i;
   OSXMLEvent event;

   pXmlReader = rtXmlpGetReader (pctxt);
   if (0 == pXmlReader) return LOG_RTERR (pctxt, RTERR_NOTINIT);
      
   if (level == -1)
      level = pXmlReader->mDecodeLevel;

   curLevel = rtXmlpGetCurrentLevel (pctxt);
   if (curLevel < level) {
      return XML_OK_EOB;
   }

   event = rtXmlRdGetLastEvent (pXmlReader);

   if (event.mId == OSXMLEVT_END_TAG) {
      if (event.mLevel == level) {
         return XML_OK_EOB;
      }
   }
   
   do {
      if (event.mId != OSXMLEVT_START_TAG) {
         stat = rtXmlRdNextEvent 
            (pXmlReader, OSXMLEVT_START_TAG | OSXMLEVT_END_TAG, level, &event);
         if (stat < 0) return LOG_RTERR (pctxt, stat);
      }

      if (event.mId == OSXMLEVT_END_TAG) {
         if (event.mLevel == level) {
            return XML_OK_EOB;
         }
      }
      
      if (event.mId == OSXMLEVT_START_TAG) {
         if (event.mLevel != level + 1) {
            rtXmlRdGetTagName (pXmlReader, &localName, 0);
            
            rtxErrAddStrnParm 
               (pctxt, (const char*)localName.value, localName.length);

            rtXmlRdErrAddSrcPos (pXmlReader, FALSE);
            return LOG_RTERRNEW (pctxt, XML_E_UNEXPSTARTTAG);
         }
      }   
      else {
         rtXmlRdGetTagName (pXmlReader, &localName, 0);
         
         rtxErrAddStrnParm 
            (pctxt, (const char*)localName.value, localName.length);

         rtXmlRdErrAddSrcPos (pXmlReader, FALSE);
         return LOG_RTERRNEW (pctxt, XML_E_UNEXPENDTAG);
      }

      rtXmlRdGetTagName (pXmlReader, &localName, &nsIndex);
#ifdef XMLPTRACE
      RTDIAG4 (pctxt, "rtXmlpGetNextElemID: localName = '%-*.*s'\n", 
               localName.length, localName.length, localName.value);
#endif
      /* first pass: check named elements */
      for (i = 0; i < nrows; i++) {
         if (tab[i].descr.localName.length == 0) continue;
         /* nsidx == -1 - check element name only */
         /*??? relax namespace index check for local elements */
         /*if ((tab[i].descr.nsidx == -1 || nsIndex == tab[i].descr.nsidx) && */
         if ((tab[i].descr.nsidx == -1 || nsIndex == tab[i].descr.nsidx || 
                 tab[i].descr.nsidx == 0) &&
             (tab[i].descr.localName.length == 0 ||    
                 OSXMLFRAGSEQUAL (localName, tab[i].descr.localName))) 
         {
            rtXmlRdMarkLastEventDone (pXmlReader);
#ifndef _COMPACT
            /* Add name to element name stack in context */
            rtxDListAppend (pctxt, &pctxt->elemNameStack, 
                            (void*)tab[i].descr.localName.value);
#endif
            return tab[i].id;
         }
      }
      
      /* second pass: check any elements by namespace */
      for (i = 0; i < nrows; i++) {
         OSBOOL found;
         if (tab[i].descr.localName.length != 0) continue;
         
         /* ##other - length == 0 and localName is not empty */
         found = FALSE;
         
         if (tab[i].descr.localName.value && 
             tab[i].descr.localName.value[0] != 0)
         {
            /* ##other */
            if (nsIndex != 0 && nsIndex != tab[i].descr.nsidx)
               found = TRUE;
         }
         else if (nsIndex == tab[i].descr.nsidx) {
            found = TRUE;
         }    
         
         if (found) {
            rtXmlRdMarkLastEventDone (pXmlReader);
#ifndef _COMPACT
            /* Add name to element name stack in context */
            rtxDListAppend (pctxt, &pctxt->elemNameStack, "*"); 
#endif
            return tab[i].id;
         }
      }

      /* not found! skip whole level and log warning here */

      if (continueParse) {
         rtxErrAddStrnParm 
            (pctxt, (const char*)localName.value, localName.length);

         rtXmlRdErrAddSrcPos (pXmlReader, FALSE);
         LOG_RTERRNEW (pctxt, RTERR_UNEXPELEM);

         stat = rtXmlRdSkipCurrentLevel (pXmlReader);
         event = rtXmlRdGetLastEvent (pXmlReader);
      }
      else {
         stat = RTERR_UNEXPELEM;
#ifndef _COMPACT
         /* Add dummy name to element name stack in context */
         rtxDListAppend (pctxt, &pctxt->elemNameStack, (void*)"<unknown>");
#endif
      }

   } while (stat == 0);

   return stat;
}

EXTXMLMETHOD int rtXmlpGetNextSeqElemID 
(OSCTXT* pctxt, const OSXMLElemIDRec* tab, const OSXMLGroupDesc* ppGroup, 
 int curID, int lastMandatoryID, OSBOOL groupMode)
{
   int fromrow = ppGroup[curID].row;
   int rows = ppGroup[curID].num;
   int anyCase = ppGroup[curID].anyCase;
   int elemID;
   OSBOOL skipUnknown = TRUE;

   /* Decoding sequence in group and in base must be breaked on first unknown 
      element in optional tail. Decoding sequence in type skips unknown 
      elements */
   if (anyCase >= 0 || (curID > lastMandatoryID && groupMode))
      skipUnknown = FALSE;
      
   elemID = rtXmlpGetNextElemID (pctxt, tab + fromrow, rows, -1, skipUnknown);

   /* if group has any element use it */
   if (elemID == RTERR_UNEXPELEM && anyCase >= 0) {
      elemID = anyCase;
   }
   else if (elemID == RTERR_UNEXPELEM && curID > lastMandatoryID) {
      elemID = XML_OK_EOB;
   }
   else if (elemID < 0) {
      if (elemID == RTERR_UNEXPELEM) {
         OSXMLStrFragment localName;
         struct OSXMLReader* pXmlReader;

         OSRTASSERT (0 != pctxt->pXMLInfo);
         pXmlReader = ((OSXMLCtxtInfo*)pctxt->pXMLInfo)->pXmlPPReader;
         OSRTASSERT (0 != pXmlReader);

         rtXmlRdGetTagName (pXmlReader, &localName, 0);

         rtxErrAddStrnParm 
            (pctxt, (const char*)localName.value, localName.length);
         rtXmlRdErrAddSrcPos (pXmlReader, FALSE);
      }
      
      return LOG_RTERR (pctxt, elemID);
   }   
   else if (elemID == XML_OK_EOB) {
      /* if not all mandatory elements decoded */
      if (curID <= lastMandatoryID) 
         return LOG_RTERR (pctxt, XML_E_ELEMSMISRQ);
   }

   return elemID;
}

EXTXMLMETHOD int rtXmlpGetNextAllElemID 
(OSCTXT* pctxt, const OSXMLElemIDRec* tab, size_t nrows, 
 const OSUINT8* pOrder, OSUINT32 nOrder, OSUINT32 maxOrder, int anyID)
{
   int elemID = rtXmlpGetNextElemID 
      (pctxt, tab, nrows, -1, (OSBOOL)(anyID < 0));
   
   if (nOrder == maxOrder && elemID >= 0 && elemID != XML_OK_EOB)
      elemID = RTERR_UNEXPELEM;
      
   if (elemID == RTERR_UNEXPELEM) {
      if (anyID >= 0) elemID = anyID;
   }
   
   if (elemID == XML_OK_EOB) {
      return elemID;
   }
   
   /* check duplicate elements */
   if (elemID >= 0) {
      const OSUINT8* p = pOrder;
      const OSUINT8* pEnd = pOrder + nOrder;
      
      while (p != pEnd) {
         if (*p++ == (OSUINT8)elemID) return LOG_RTERR (pctxt, RTERR_SETDUPL);
      }
   }
     
   if (elemID < 0) {
      if (elemID == RTERR_UNEXPELEM) {
         OSXMLStrFragment localName;
         struct OSXMLReader* pXmlReader;

         OSRTASSERT (0 != pctxt->pXMLInfo);
         pXmlReader = ((OSXMLCtxtInfo*)pctxt->pXMLInfo)->pXmlPPReader;
         OSRTASSERT (0 != pXmlReader);

         rtXmlRdGetTagName (pXmlReader, &localName, 0);

         rtxErrAddStrnParm 
            (pctxt, (const char*)localName.value, localName.length);
         rtXmlRdErrAddSrcPos (pXmlReader, FALSE);
      }
      return LOG_RTERR (pctxt, elemID);
   }

   return elemID;
}

EXTXMLMETHOD int rtXmlpGetNextAllElemID16 
(OSCTXT* pctxt, const OSXMLElemIDRec* tab, size_t nrows, 
 const OSUINT16* pOrder, OSUINT32 nOrder, OSUINT32 maxOrder, int anyID)
{
   int elemID = rtXmlpGetNextElemID 
      (pctxt, tab, nrows, -1, (OSBOOL)(anyID < 0));
   
   if (nOrder == maxOrder && elemID >= 0 && elemID != XML_OK_EOB)
      elemID = RTERR_UNEXPELEM;
      
   if (elemID == RTERR_UNEXPELEM) {
      if (anyID >= 0) elemID = anyID;
   }
   
   if (elemID == XML_OK_EOB) {
      return elemID;
   }
   
   /* check duplicate elements */
   if (elemID >= 0) {
      const OSUINT16* p = pOrder;
      const OSUINT16* pEnd = pOrder + nOrder;
      
      while (p != pEnd) {
         if (*p++ == (OSUINT16)elemID) return LOG_RTERR (pctxt, RTERR_SETDUPL);
      }
   }
     
   if (elemID < 0) {
      if (elemID == RTERR_UNEXPELEM) {
         OSXMLStrFragment localName;
         struct OSXMLReader* pXmlReader;

         OSRTASSERT (0 != pctxt->pXMLInfo);
         pXmlReader = ((OSXMLCtxtInfo*)pctxt->pXMLInfo)->pXmlPPReader;
         OSRTASSERT (0 != pXmlReader);

         rtXmlRdGetTagName (pXmlReader, &localName, 0);

         rtxErrAddStrnParm 
            (pctxt, (const char*)localName.value, localName.length);
         rtXmlRdErrAddSrcPos (pXmlReader, FALSE);
      }
      return LOG_RTERR (pctxt, elemID);
   }

   return elemID;
}

EXTXMLMETHOD void rtXmlpForceDecodeAsGroup (OSCTXT* pctxt)
{
   XMLPREADER(pctxt)->mbDecodeAsGroup = TRUE;
}

EXTXMLMETHOD OSBOOL rtXmlpIsDecodeAsGroup (OSCTXT* pctxt)
{
   return XMLPREADER(pctxt)->mbDecodeAsGroup;
}

