/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/codecHNBAP.h $
$Author: roger $
$Date: 2012-07-13 12:05:11 +0200 (Fri, 13 Jul 2012) $
$Rev: 53117 $
----------------------------------------------------------------
Description : HNBAP SIGNALS ENCODING/DECODING
--------------------------------------------------------------*/

#ifndef codecHNBAPINCLUDED
#define codecHNBAPINCLUDED

#include "tm_compat.h"
#include "tstmHNBAP.h"

int codecHNBAPInit(tmITPt* itp, ushort hnbap_sapi);
int codecHNBAPDec( uchar *PduPtr, uint PduLen );
int codecHNBAPEnc( uint type, uchar *pdu, uint *pdulen );

#endif
