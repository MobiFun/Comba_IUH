/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/encRUA.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------
Description : RUA SIGNALS ENCODING
--------------------------------------------------------------*/

#ifndef encRUAINCLUDED
#define encRUAINCLUDED

#include "ruaAsn1c.h"

/***********************************************************************
************************************************************************
                Encoding functions for RUA PDUs
************************************************************************
************************************************************************/

int encRUAConnect( OSOCTET *buf_out, int *len );

int encRUADirectTransfer( OSOCTET *buf_out, int *len );

int encRUADisconnect( OSOCTET *buf_out, int *len );

int encRUAConnectionlessTransfer( OSOCTET *buf_out, int *len );

int encRUAErrorIndication( OSOCTET *buf_out, int *len );

int encRUAPrivateMessage( OSOCTET *buf_out, int *len );

#endif
