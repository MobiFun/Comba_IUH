/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/hnbapAsn1c.h $
$Author: roger $
$Date: 2012-07-12 18:11:54 +0200 (Thu, 12 Jul 2012) $
$Rev: 53111 $
----------------------------------------------------------------
--------------------------------------------------------------*/

/*............................................................*/
#ifndef hnbapAsn1cINCLUDED
#define hnbapAsn1cINCLUDED

#undef EXTERN
#include "asn1type.h"
#include "defs.h"

#pragma pack (4)

#include "./asn1c/C/HNBAP-CommonDataTypes.h"
#include "./asn1c/C/HNBAP-Constants.h"
#include "./asn1c/C/HNBAP-Containers.h"
#include "./asn1c/C/HNBAP-IEs.h"
#include "./asn1c/C/HNBAP-PDU-Contents.h"
#include "./asn1c/C/HNBAP-PDU-Descriptions.h"

#pragma pack ()

#define tmITP tm_compatITP()

#endif
