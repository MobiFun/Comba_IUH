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

#include "rtpersrc/pu_common.hh"

/***********************************************************************
 *
 *  Routine name: pu_getFullName
 *
 *  Description:  This routine returns the fully qualified name of
 *                the field with the given suffix appended.
 *
 *  Inputs:
 *
 *  Name        Type     Description
 *  ----        ----     -----------
 *  pctxt      struct*  Pointer to PER context block
 *
 *  Outputs:
 *
 *  Name        Type     Description
 *  ----        ----     -----------
 *  
 *
 **********************************************************************/

EXTPERMETHOD const char* pu_getFullName (OSCTXT* pctxt, const char* suffix)
{
   size_t memRequired = 0;
   char* fullName;
   OSRTDListNode* pnode;

   pnode = ACINFO(pctxt)->nameStack.dlist.tail;
   while (0 != pnode) {
      memRequired += strlen ((char*)pnode->data);
      memRequired++; /* for '.' */
      pnode = pnode->prev;
   }
   if (suffix) {
      memRequired += (strlen(suffix) + 2);
   }
   if (0 == memRequired) return (const char*)0;

   fullName = (char*) rtxMemAlloc (pctxt, memRequired);
   if (0 == fullName) return (const char*)0;
   else *fullName = '\0';

   pnode = ACINFO(pctxt)->nameStack.dlist.tail;
   while (0 != pnode) {
      strcat (fullName, ".");
      strcat (fullName, (char*)pnode->data);
      pnode = pnode->prev;
   }
   if (suffix) {
      strcat (fullName, " ");
      strcat (fullName, suffix);
   }

   return fullName;
}

/***********************************************************************
 *
 *  Routine name: pu_newField
 *
 *  Description:  This routine creates a new PER primitive field 
 *                record and links it to the PER field list.
 *
 *  Inputs:
 *
 *  Name        Type     Description
 *  ----        ----     -----------
 *  pctxt      struct*  Pointer to PER context block
 *
 *  Outputs:
 *
 *  Name        Type     Description
 *  ----        ----     -----------
 *  
 *
 **********************************************************************/

EXTPERMETHOD PERField* pu_newField (OSCTXT* pctxt, const char* nameSuffix)
{
   PERField* pField = 0;

   if ((pctxt->flags & ASN1TRACE) != 0) {
      pField = rtxMemAllocType (pctxt, PERField);
      if (pField == NULL) return NULL;

      pField->name = pu_getFullName (pctxt, nameSuffix);
      pField->bitOffset = PU_GETCTXTBITOFFSET (pctxt);
      pField->numbits = 0;
      pField->openTypeFields = 0;

      RTDIAGSTRM5 (pctxt,"pu_newField: name '%s', bitOffset %d, pField 0x%x\n",
              pField->name, pField->bitOffset, pField);

      rtxSListAppend (&ACINFO(pctxt)->fieldList, pField);
   }

   return pField;
}

EXTPERMETHOD void pu_popName (OSCTXT* pctxt)
{
   if ((pctxt->flags & ASN1TRACE) != 0)
      rtxStackPop (&(ACINFO(pctxt)->nameStack));
}

EXTPERMETHOD void pu_pushName (OSCTXT* pctxt, const char* name)
{
   if ((pctxt->flags & ASN1TRACE) != 0) {
      rtxStackPush (&(ACINFO(pctxt)->nameStack), (void*)name);
   }
}

EXTPERMETHOD void pu_pushElemName (OSCTXT* pctxt, int index)
{
   if ((pctxt->flags & ASN1TRACE) != 0) {
      char lbuf[20], *pName;
      sprintf (lbuf, "elem[%d]", index);
      pName = (char*) rtxMemAlloc (pctxt, strlen(lbuf)+1);
      if (pName != NULL) {
         strcpy (pName, lbuf);
         rtxStackPush (&(ACINFO(pctxt)->nameStack), pName);
      }
   }
}

EXTPERMETHOD void pu_setOpenTypeFldList (OSCTXT* pctxt, OSRTSList* plist)
{
   if ((pctxt->flags & ASN1TRACE) != 0) {
      OSRTSListNode* pNode = ACINFO(pctxt)->fieldList.tail;
      if (0 != pNode) {
         PERField* pfld = (PERField*) pNode->data;
         if (0 != pfld) {
            pfld->openTypeFields = plist;
         }
      }
   }
}
