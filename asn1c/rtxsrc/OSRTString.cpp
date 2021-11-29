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

#include "rtxsrc/OSRTString.h"

EXTRTMETHOD OSRTString::OSRTString ()
{ 
   mValue = new OSUTF8CHAR [1];
   *mValue = '\0';
}

EXTRTMETHOD OSRTString::OSRTString (const char* strval)
{
   if (0 != strval) {
      size_t bufsiz = OSCRTLSTRLEN(strval)+1;
      mValue = new OSUTF8CHAR [bufsiz];
      if (0 != mValue)
         rtxUTF8Strcpy (mValue, bufsiz, (OSUTF8CHAR*)strval);
      else
      {
         mValue = new OSUTF8CHAR [1];
         *mValue = '\0';
      }   
   }
   else {
      mValue = new OSUTF8CHAR [1];
      *mValue = '\0';
   }
}

EXTRTMETHOD OSRTString::OSRTString (const OSRTString& str)
{
   delete [] mValue;
   size_t bufsiz = OSCRTLSTRLEN((const char*)str.mValue)+1;
   mValue = new OSUTF8CHAR [bufsiz];
   if (0 != mValue)
      rtxUTF8Strcpy (mValue, bufsiz, str.mValue);
}

EXTRTMETHOD OSRTString::~OSRTString () 
{
   delete [] mValue;
}

EXTRTMETHOD void OSRTString::setValue (const char* strval) 
{
   if (0 != strval) {
      delete [] mValue;
      size_t bufsiz = OSCRTLSTRLEN(strval)+1;
      mValue = new OSUTF8CHAR [bufsiz];
      if (0 != mValue)
         rtxUTF8Strcpy (mValue, bufsiz, (OSUTF8CHAR*)strval);
   }
}

EXTRTMETHOD void OSRTString::setValue (const OSUTF8CHAR* strval) 
{
   if (0 != strval) {
      delete [] mValue;
      size_t bufsiz = OSCRTLSTRLEN((const char*)strval)+1;
      mValue = new OSUTF8CHAR [bufsiz];
      if (0 != mValue)
         rtxUTF8Strcpy (mValue, bufsiz, strval);
   }
}

 OSRTString& OSRTString::operator= (const OSRTString& original)
{
   setValue (original.mValue);
   return *this;
}

