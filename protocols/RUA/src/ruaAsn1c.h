/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/ruaAsn1c.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------
--------------------------------------------------------------*/

/*............................................................*/
#ifndef ruaAsn1cINCLUDED
#define ruaAsn1cINCLUDED

#undef EXTERN
#include "asn1type.h"
#include "defs.h"

#pragma pack (4)

#include "./asn1c/C/RUA-CommonDataTypes.h"
#include "./asn1c/C/RUA-Constants.h"
#include "./asn1c/C/RUA-Containers.h"
#include "./asn1c/C/RUA-IEs.h"
#include "./asn1c/C/RUA-PDU-Contents.h"
#include "./asn1c/C/RUA-PDU-Descriptions.h"

#pragma pack ()

#define tmITP tm_compatITP()

#endif
