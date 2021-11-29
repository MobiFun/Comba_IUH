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

#include "asn1type.h"
#include "asn1CharSet.h"

/* Helper function takes upper and lower bound to check characters against,
 * loops through the string. */
int helpValidateStr (const char *str, char lb, char ub);

int
rtValidateStr (ASN1TAG tag, const char *object_p) {
   /* Note:  we assume that the check for lax processing has already been 
    * done when this function is called.  We also assume the string is
    * null-terminated. */

   switch (tag) {
      case ASN_ID_NumericString:
         return helpValidateStr (object_p, NUM_CANSET[0], 
                                 NUM_CANSET[sizeof(NUM_CANSET) - 2]);

      case ASN_ID_PrintableString:
         return helpValidateStr (object_p, PRN_CANSET[0],
                                 PRN_CANSET[sizeof(PRN_CANSET) - 2]);

      case ASN_ID_T61String:
         return helpValidateStr (object_p, T61_CANSET[0],
                                 T61_CANSET[sizeof(T61_CANSET) - 2]);

      case ASN_ID_IA5String:
         return helpValidateStr (object_p, IA5_CANSET[0],
                                 IA5_CANSET[sizeof(IA5_CANSET) - 2]);

      case ASN_ID_VisibleString:
         return helpValidateStr (object_p, VIS_CANSET[0],
                                 VIS_CANSET[sizeof(VIS_CANSET) - 2]);

      case ASN_ID_GeneralString:
         return helpValidateStr (object_p, GEN_CANSET[0],
                                 GEN_CANSET[sizeof(GEN_CANSET) - 2]);

      default: break;
   }

   return 0;
}


int
helpValidateStr (const char *str, char lb, char ub)
{
   char c = *str;
   while (c != '\0') {
      if (c > ub || c < lb) {
         return c;
      }
      *str ++;
      c = *str;
   }

   return 0;
}
