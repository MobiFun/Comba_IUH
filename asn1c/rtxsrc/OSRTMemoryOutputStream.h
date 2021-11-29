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
/** 
 * @file OSRTMemoryOutputStream.h 
 * C++ base class definitions for operations with output memory streams.
 */
#ifndef _OSRTMEMORYOUTPUTSTREAM_H_
#define _OSRTMEMORYOUTPUTSTREAM_H_

#include "rtxsrc/OSRTOutputStream.h"

/**
 * Generic memory output stream. This class opens an existing file for output in
 * binary mode and reads data from it.
 */
class EXTRTCLASS OSRTMemoryOutputStream : public OSRTOutputStream {
 public:
   /**
    * Initializes the memory output stream using the specified memory buffer.
    *
    * @param pMemBuf                   The pointer to the buffer.
    * @param bufSize                   The size of the buffer.
    * @exception OSCStreamException    stream can't be created or initialized.
    * @see                            ::rtxStreamMemoryAttach
    */
   EXTRTMETHOD OSRTMemoryOutputStream (OSOCTET* pMemBuf, size_t bufSize);

   /**
    * Initializes the memory output stream using the specified memory buffer.
    *
    * @param pContext                  Pointer to a context to use.
    * @param pMemBuf                   The pointer to the buffer.
    * @param bufSize                   The size of the buffer.
    * @exception OSCStreamException    stream can't be created or initialized.
    * @see                            ::rtxStreamMemoryAttach
    */
   EXTRTMETHOD OSRTMemoryOutputStream (OSRTContext* pContext, OSOCTET* pMemBuf, size_t bufSize);

} ;

#endif /* _OSRTMEMORYOUTPUTSTREAM_H_ */
