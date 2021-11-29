/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/decRUA.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
--------------------------------------------------------------*/

#ifndef decRUAINCLUDED
#define decRUAINCLUDED

#include "ruaAsn1c.h"

/***********************************************************************
************************************************************************
                Decoding functions for RUA PDUs
************************************************************************
************************************************************************/

int decRUAPdu( uint *t_proc, uint *t_code, uchar *buf_in, size_t buf_in_len, OSOCTET *buf_out, uint *len_out );

int decRUAConnect( OSOCTET *buf_in, uint len );

int decRUADirectTransfer( OSOCTET *buf_in, uint len );

int decRUADisconnect( OSOCTET *buf_in, uint len );

int decRUAConnectionlessTransfer( OSOCTET *buf_in, uint len );

int decRUAErrorIndication( OSOCTET *buf_in, uint len );

int decRUAPrivateMessage( OSOCTET *buf_in, uint len );

#endif
