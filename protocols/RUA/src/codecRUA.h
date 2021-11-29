/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/codecRUA.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------
Description : RUA SIGNALS ENCODING/DECODING
--------------------------------------------------------------*/

#ifndef codecRUAINCLUDED
#define codecRUAINCLUDED

#include "tm_compat.h"


int codecRUAInit(tmITPt* itp, ushort rua_sapi);
int codecRUADec( uchar *PduPtr, uint PduLen );
int codecRUAEnc( uint type, uchar *pdu, uint *pdulen );

#endif
