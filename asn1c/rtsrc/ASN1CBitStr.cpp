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

#include "rtsrc/ASN1CBitStr.h"
#include "rtsrc/asn1intl.h"
#include "rtxsrc/rtxUtil.h"
#include <limits.h>

// delta (in units) for adding to size of memory being allocating
#define ADD_DELTA 1024 

#define UNIT_MASK ((OSOCTET)-1)

#define ADDRESS_BITS       3 // as char has 8 bits (2^3)

#define BITS_PER_UNIT (OSINTCONST(1) << ADDRESS_BITS) 
#define BIT_INDEX_MASK  (BITS_PER_UNIT - 1)

//////////////////////////////////////////////////////////////////////
//
// ASN1CBitStr
// 
// Bit string implementation. This class provides all functionalty
// necessary for bit strings. 
//
// Author Artem Bolgar.
// version 1.52  21 Feb, 2003 (ASN1CType::mMsgBuf changed to mpMsgBuf)
//
// history:
//         1.04  31 Oct, 2001
//         1.05  05 Jun, 2002 (some warnings on Solaris were eliminated)
//         1.06  13 Jul, 2002 (bug in checkCapacity fixed)
// version 1.50  31 Jul, 2002
// version 1.51  11 Feb, 2003 (ASN1CType::mMsgBuf changed to mpMsgBuf)
//

/*
* Returns a unit that has all bits that are less significant
* than the specified index set to 1. All other bits are 0.
*/
inline static OSOCTET bitsRightOf(int x) {
   return (UNIT_MASK >> x);
}

/*
* Returns a unit that has all the bits that are more significant
* than or equal to the specified index set to 1. All other bits are 0.
*/
inline static OSOCTET bitsLeftOf(int x) {
   return (x==0 ? UNIT_MASK : (UNIT_MASK << (BITS_PER_UNIT - x)));
}

/*
* Given a bit index return unit index containing it.
*/
inline static int unitIndex(int bitIndex) {
   return bitIndex >> ADDRESS_BITS;
}

/*
* Given a bit index, return a unit that masks that bit in its unit.
*/
inline static long bit(int bitIndex) {
   return (OSINTCONST(1) << (BITS_PER_UNIT - 1)) >> (bitIndex & BIT_INDEX_MASK);
}

/*
* Creates an empty bits string. The string should be additionaly initialized 
* by call to 'init' method.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTMessageBufferIF& msgBuf) :
   ASN1CType(msgBuf), _numbits (0), _units (0), mpUnits(&_units), mMaxNumBits (0),
   mpNumBits(&_numbits), mUnitsUsed (0), mUnitsAllocated (0), mDynAlloc (FALSE)
{
}

/*
* Default protected ctor. mpContext should be set and the string should be 
* additionaly initialized by call to 'init' method.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr() :
   ASN1CType(), _numbits (0), _units (0), mpUnits(&_units), mMaxNumBits (0),
   mpNumBits(&_numbits), mUnitsUsed (0), mUnitsAllocated (0), mDynAlloc (FALSE)
{
}

/*
* Creates an empty bits string. The string should be additionaly initialized 
* by call to 'init' method.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTContext& ctxt) : 
   ASN1CType(ctxt), _numbits (0), _units (0), mpUnits(&_units), mMaxNumBits (0),
   mpNumBits(&_numbits), mUnitsUsed (0), mUnitsAllocated (0), mDynAlloc (FALSE)
{
}

EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSOCTET* bitStr, 
   OSUINT32& octsNumbits, OSUINT32 maxNumbits_):
   ASN1CType(), mpUnits(&_units), mpNumBits(&octsNumbits)
{
   privateInit (bitStr, maxNumbits_);
}

/*
* Creates bits string from ASN1TDynBitStr. Ctor does not copy bytes,
* just assign array (data member of ASN1TDynBitStr) to units.
* This string will be extendable.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr (ASN1TDynBitStr& bitStr): 
   ASN1CType(), mpUnits((OSOCTET**)&bitStr.data), mpNumBits(&bitStr.numbits)
{
   privateInit (bitStr);
}

EXTRTMETHOD void ASN1CBitStr::init (OSOCTET* pBits, OSUINT32& numbits, OSUINT32 maxNumbits) {
   (*mpUnits) = pBits;
   mpNumBits = &numbits;
   mMaxNumBits = maxNumbits;
   mUnitsUsed = numbits * 8;
   mUnitsAllocated = maxNumbits * 8;
}

EXTRTMETHOD void ASN1CBitStr::init (ASN1TDynBitStr& bitStr) {
   mpUnits = (OSOCTET**)&bitStr.data;
   mpNumBits = &bitStr.numbits;
   mMaxNumBits = UINT_MAX;
   mUnitsAllocated = mUnitsUsed = (unitIndex(bitStr.numbits - 1) + 1);
}

EXTRTMETHOD void ASN1CBitStr::privateInit (OSUINT32 nbits)
{
   (*mpNumBits) = 0;
   mDynAlloc = TRUE;
   if(nbits == 0) {
      (*mpUnits) = 0;
      mMaxNumBits = UINT_MAX;
      mUnitsUsed = mUnitsAllocated = 0;
      return;
   }
   mUnitsUsed = 0;
   mUnitsAllocated = (unitIndex(nbits - 1) + 1);
   (*mpUnits) = allocateMemory(mUnitsAllocated);
   mMaxNumBits = nbits;
}

EXTRTMETHOD void ASN1CBitStr::privateInit (OSOCTET* bitStr, 
      OSUINT32 maxNumbits_)
{
   this->mMaxNumBits = maxNumbits_;
   (*mpUnits) = bitStr;
   if(mMaxNumBits < (*mpNumBits)) 
      (*mpNumBits) = mMaxNumBits;
   mUnitsUsed = (unitIndex((*mpNumBits) - 1) + 1);
   mUnitsAllocated = (unitIndex(mMaxNumBits - 1) + 1);
   // remove unused bits in the last octet
   if(mUnitsUsed > 0) 
      (*mpUnits)[mUnitsUsed - 1] &= bitsLeftOf((*mpNumBits) & BIT_INDEX_MASK);
   // clear out unused bytes
   if(mUnitsAllocated - mUnitsUsed > 0)
      memset(&(*mpUnits)[mUnitsUsed], 0, (mUnitsAllocated - mUnitsUsed)
         * sizeof(OSOCTET));
   mDynAlloc = FALSE;
}

EXTRTMETHOD void ASN1CBitStr::privateInit (ASN1TDynBitStr& bitStr)
{
   mMaxNumBits = UINT_MAX;
   mUnitsAllocated = mUnitsUsed = (unitIndex(bitStr.numbits - 1) + 1);
   // remove unused bits in the last octet
   if(mUnitsUsed > 0)
      (*mpUnits)[mUnitsUsed - 1] &= bitsLeftOf(mMaxNumBits & BIT_INDEX_MASK);
   mDynAlloc = FALSE;
}

/*
* Creates empty bit string. If nbits == 0 then bit string is dynamic; 
* else capacity will be fixed to nbits.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTMessageBufferIF& msgBuf, OSUINT32 nbits):
   ASN1CType(msgBuf), mpUnits(&_units), mpNumBits(&_numbits)
{
   privateInit (nbits);
}

/*
* Copy constructor.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(const ASN1CBitStr& bitStr): 
   ASN1CType(bitStr), mpUnits(&_units), mpNumBits(&_numbits)
{
   mMaxNumBits = bitStr.mMaxNumBits;
   (*mpNumBits) = (*bitStr.mpNumBits);
   mUnitsAllocated = bitStr.mUnitsAllocated;
   if(mUnitsAllocated) {
      mUnitsUsed = bitStr.mUnitsUsed;
      (*mpUnits) = allocateMemory(mUnitsAllocated);
      memcpy(*mpUnits, *bitStr.mpUnits, mUnitsUsed * sizeof(OSOCTET));
   }
   else {
      (*mpUnits) = 0;
      mUnitsUsed = 0;
   }
   mDynAlloc = TRUE;
}

/*
* Copy constructor, but allows to specify 'extendable' parameter
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(const ASN1CBitStr& bitStr, OSBOOL extendable): 
   ASN1CType(bitStr), mpUnits(&_units), mpNumBits(&_numbits)
{
   if(extendable) { 
      mUnitsAllocated = bitStr.mUnitsUsed + ADD_DELTA;
      mMaxNumBits = UINT_MAX;
   }
   else {
      mUnitsAllocated = bitStr.mUnitsAllocated;
      mMaxNumBits = bitStr.mMaxNumBits;
   }
   (*mpNumBits) = (*bitStr.mpNumBits);
   if(mUnitsAllocated) {
      mUnitsUsed = bitStr.mUnitsUsed;
      (*mpUnits) = allocateMemory(mUnitsAllocated);
      memcpy(*mpUnits, *bitStr.mpUnits, mUnitsUsed * sizeof(OSOCTET));
      }
   else {
      (*mpUnits) = 0;
      mUnitsUsed = 0;
   }
   mDynAlloc = TRUE;
}

/*
* Creates bits string from ASN1TDynBitStr. Ctor does not copy bytes,
* just assign array (data member of ASN1TDynBitStr) to units.
* This string will be extendable.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTMessageBufferIF& msgBuf, ASN1TDynBitStr& bitStr): 
   ASN1CType(msgBuf), mpUnits((OSOCTET**)&bitStr.data), mpNumBits(&bitStr.numbits)
{
   privateInit (bitStr);
}

/* Creates bits string from array of bits. Ctor does not copy bytes,
* just assign passed array to units.
* Param bitStr - pointer to static byte array
* Param numbits - reference to length of bit string (in bits);
* Param mMaxNumBits  - sets maximum length in bits
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTMessageBufferIF& msgBuf, OSOCTET* bitStr, 
   OSUINT32& octsNumbits, OSUINT32 maxNumbits_):
   ASN1CType(msgBuf), mpUnits(&_units), mpNumBits(&octsNumbits)
{
   privateInit (bitStr, maxNumbits_);
}


/*
* Creates empty bit string. If nbits == 0 then bit string is dynamic; 
* else capacity will be fixed to nbits.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTContext& ctxt, OSUINT32 nbits):
   ASN1CType(ctxt), mpUnits(&_units), mpNumBits(&_numbits)
{
   privateInit (nbits);
}

/*
* Creates bits string from ASN1TDynBitStr. Ctor does not copy bytes,
* just assign array (data member of ASN1TDynBitStr) to units.
* This string will be extendable.
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTContext& ctxt, ASN1TDynBitStr& bitStr): 
   ASN1CType(ctxt), mpUnits((OSOCTET**)&bitStr.data), mpNumBits(&bitStr.numbits)
{
   privateInit (bitStr);
}

/* Creates bits string from array of bits. Ctor does not copy bytes,
* just assign passed array to units.
* Param bitStr - pointer to static byte array
* Param numbits - reference to length of bit string (in bits);
* Param mMaxNumBits  - sets maximum length in bits
*/
EXTRTMETHOD ASN1CBitStr::ASN1CBitStr(OSRTContext& ctxt, OSOCTET* bitStr, 
   OSUINT32& octsNumbits, OSUINT32 maxNumbits_):
   ASN1CType(ctxt), mpUnits(&_units), mpNumBits(&octsNumbits)
{
   privateInit (bitStr, maxNumbits_);
}

// Destructor
EXTRTMETHOD ASN1CBitStr::~ASN1CBitStr() {
   if(mDynAlloc)
      freeMemory((*mpUnits));
}

/* Allocates memory, and fills by zeros. */
EXTRTMETHOD OSOCTET* ASN1CBitStr::allocateMemory(int sz) {
   OSOCTET* mem = (OSOCTET*)memAlloc(sz * sizeof(OSOCTET));   
   memset(mem, 0, sz * sizeof(OSOCTET));
   return mem;
}

/* Reallocates memory. */
EXTRTMETHOD OSOCTET* ASN1CBitStr::reallocateMemory(OSOCTET* old, int oldBufSz, int newBufSz) {
   OSOCTET* mem = (OSOCTET*)memRealloc(old, newBufSz * sizeof(OSOCTET));
   memset(mem + oldBufSz, 0, (newBufSz - oldBufSz) * sizeof(OSOCTET));
   return mem;
}

/* Free memory. */
EXTRTMETHOD void ASN1CBitStr::freeMemory(OSOCTET* ptr) {
   memFreePtr (ptr);
}

/*
* Set the field mUnitsUsed with the logical size in units of the bit
* set.  WARNING:This function assumes that the number of units actually
* in use is less than or equal to the current value of mUnitsUsed!
*/
EXTRTMETHOD void ASN1CBitStr::recalculateUnitsUsed() {
   if(mUnitsUsed > 0 && (*mpUnits)[mUnitsUsed - 1] == 0) {
      // Traverse the bitstr until a used unit is found
      int i;
      for(i = mUnitsUsed - 1; i >= 0; i--) {
         if((*mpUnits)[i] != 0)
            break;
      }
      mUnitsUsed = i + 1; // The new logical size
   }
   (*mpNumBits) = length();
} 

/*
* Ensures that the bit string can hold enough units.
* param	unitsRequired the minimum acceptable number of units.
*/
EXTRTMETHOD int ASN1CBitStr::checkCapacity(int unitsRequired) {
   if(mUnitsAllocated < unitsRequired) {
      if(mMaxNumBits != UINT_MAX)
         return ASN_E_INVLEN; // do not reallocate memory for fixed bitstr
      int wasAllocated = mUnitsAllocated;
      mUnitsAllocated = unitsRequired + ADD_DELTA;
      if(wasAllocated > 0) {     // (AB, 07/13/02: check wasAllocated rather than units
         if(mDynAlloc && (*mpUnits))   // because units might be uninitialized
            (*mpUnits) = reallocateMemory((*mpUnits), wasAllocated, mUnitsAllocated);
         else {
            OSOCTET* newUnits = (OSOCTET*)allocateMemory(mUnitsAllocated);
            memcpy(newUnits, (*mpUnits), wasAllocated * sizeof(OSOCTET));
            (*mpUnits) = newUnits;
            mDynAlloc = TRUE;  
         }
      }
      else 
         (*mpUnits) = (OSOCTET*)allocateMemory(mUnitsAllocated);
   }
   if(mUnitsUsed < unitsRequired)
      mUnitsUsed = unitsRequired;
   return 0;
}

/*
* Sets the bit at the specified index to 1.
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if 'bitIndex' is out of bounds, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::set(OSUINT32 bitIndex) {
   if(bitIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);

   int unitsIndex = unitIndex(bitIndex);
   int stat = checkCapacity(unitsIndex + 1);
   if(stat != 0) 
      return LOG_RTERR(mpContext->getPtr(), stat);
   (*mpUnits)[unitsIndex] |= bit(bitIndex);
   if((*mpNumBits) < bitIndex + 1)
      (*mpNumBits) = bitIndex + 1;
   return 0;
}                         

/*
* Sets the bits from the specified fromIndex(inclusive) to the
* specified toIndex(exclusive) to 1.
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if one of indexes is out of bounds, or
*          RTERR_BADVALUE - if fromIndex > toIndex, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::set(OSUINT32 fromIndex, OSUINT32 toIndex) {
   if(fromIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(toIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(fromIndex > toIndex)
      return LOG_RTERR(mpContext->getPtr(), RTERR_BADVALUE);

   // Increase capacity if necessary
   int endUnitIndex = unitIndex(toIndex - 1);
   int stat = checkCapacity(endUnitIndex + 1);
   if(stat != 0) 
      return LOG_RTERR(mpContext->getPtr(), stat);

   if((*mpNumBits) < toIndex)
      (*mpNumBits) = toIndex;
   int startUnitIndex = unitIndex(fromIndex);
   long bitMask;
   if(startUnitIndex == endUnitIndex) {
      // Case 1: One octet
      bitMask = ((OSINTCONST(1) << BITS_PER_UNIT) >> (fromIndex & BIT_INDEX_MASK)) -
                ((OSINTCONST(1) << BITS_PER_UNIT) >> (toIndex & BIT_INDEX_MASK));
      (*mpUnits)[startUnitIndex] |= bitMask;
      return 0;
   }
  
   // Case 2: Multiple octets
   // Handle first octet
   bitMask = bitsRightOf(fromIndex & BIT_INDEX_MASK);
   (*mpUnits)[startUnitIndex] |= bitMask;

   // Handle intermediate octets, if any
   if(endUnitIndex - startUnitIndex > 1) {
      for(int i=startUnitIndex+1; i<endUnitIndex; i++)
          (*mpUnits)[i] |= UNIT_MASK;
   }

   // Handle last octet
   bitMask = bitsLeftOf(toIndex & BIT_INDEX_MASK);
   (*mpUnits)[endUnitIndex] |= bitMask;
   return 0;
}

/*
* Sets the bit specified by the index to 0.
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if 'bitIndex' is out of bounds, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::clear(OSUINT32 bitIndex) {
   if(bitIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);

   int unitsIndex = unitIndex(bitIndex);
   if(unitsIndex >= mUnitsUsed)
      return 0;

   (*mpUnits)[unitsIndex] &= ~bit(bitIndex);
   recalculateUnitsUsed();
   return 0;
   }

/*
* Sets the bits from the specified fromIndex(inclusive) to the
* specified toIndex(exclusive) to 0.
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if one of indexes is out of bounds, or
*          RTERR_BADVALUE - if fromIndex > toIndex, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::clear(OSUINT32 fromIndex, OSUINT32 toIndex) {
   if(fromIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(toIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(fromIndex > toIndex)
      return LOG_RTERR(mpContext->getPtr(), RTERR_BADVALUE);

   int startUnitIndex = unitIndex(fromIndex);
   if(startUnitIndex >= mUnitsUsed)
      return 0;
   int endUnitIndex = unitIndex(toIndex - 1);

   long bitMask;
   if(startUnitIndex == endUnitIndex) {
      // Case 1: One octet
      bitMask = ((OSINTCONST(1) << BITS_PER_UNIT) >> (fromIndex & BIT_INDEX_MASK)) -
                ((OSINTCONST(1) << BITS_PER_UNIT) >> (toIndex & BIT_INDEX_MASK));
      (*mpUnits)[startUnitIndex] &= ~bitMask;
      recalculateUnitsUsed();
      return 0;
   }

   // Case 2: Multiple octets
   // Handle first octet
   bitMask = bitsRightOf(fromIndex & BIT_INDEX_MASK);
   (*mpUnits)[startUnitIndex] &= ~bitMask;

   // Handle intermediate octets, if any
   if(endUnitIndex - startUnitIndex > 1) {
      for(int i = startUnitIndex + 1; i < endUnitIndex; i++) {
         if(i < mUnitsUsed)
            (*mpUnits)[i] = 0;
      }
   }

   // Handle last octet
   if(endUnitIndex < mUnitsUsed) {
      bitMask = bitsLeftOf(toIndex & BIT_INDEX_MASK);
      (*mpUnits)[endUnitIndex] &= ~bitMask;
   }

   recalculateUnitsUsed();
   return 0;
}

/*
* Sets all of the bits in this bit string to 0.
*/
EXTRTMETHOD void ASN1CBitStr::clear() {
   int i;
   for(i = mUnitsUsed; i > 0;)
      (*mpUnits)[--i] = 0;
   mUnitsUsed = 0; // update mUnitsUsed
   (*mpNumBits) = 0;
}

/*
* Sets the bit at the specified index to to the complement of its
* current value.
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if 'bitIndex' is out of bounds, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::invert(OSUINT32 bitIndex) {
   if(bitIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);

   int unitsIndex = unitIndex(bitIndex);

   int stat = checkCapacity(unitsIndex + 1);
   if(stat != 0) 
      return LOG_RTERR(mpContext->getPtr(), stat);
   (*mpUnits)[unitsIndex] ^= bit(bitIndex);
   recalculateUnitsUsed();
   return 0;
}

/*
* Sets each bit from the specified fromIndex(inclusive) to the
* specified toIndex(exclusive) to the complement of its current
* value.
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if one of indexes is out of bounds, or
*          RTERR_BADVALUE - if fromIndex > toIndex, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::invert(OSUINT32 fromIndex, OSUINT32 toIndex) {
   if(fromIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(toIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(fromIndex > toIndex)
      return LOG_RTERR(mpContext->getPtr(), RTERR_BADVALUE);
  
   // Increase capacity if necessary
   int endUnitIndex = unitIndex(toIndex - 1);
   int stat = checkCapacity(endUnitIndex + 1);
   if(stat != 0) 
      return LOG_RTERR(mpContext->getPtr(), stat);

   int startUnitIndex = unitIndex(fromIndex);
   long bitMask;
   if(startUnitIndex == endUnitIndex) {
      // Case 1: One octet
      bitMask = ((OSINTCONST(1) << BITS_PER_UNIT) >> (fromIndex & BIT_INDEX_MASK)) -
                ((OSINTCONST(1) << BITS_PER_UNIT) >> (toIndex & BIT_INDEX_MASK));
      (*mpUnits)[startUnitIndex] ^= bitMask;
      recalculateUnitsUsed();
      return 0;
   }
  
   // Case 2: Multiple octets
   // Handle first octet
   bitMask = bitsRightOf(fromIndex & BIT_INDEX_MASK);
   (*mpUnits)[startUnitIndex] ^= bitMask;

   // Handle intermediate octets, if any
   if(endUnitIndex - startUnitIndex > 1) {
      for(int i = startUnitIndex + 1; i < endUnitIndex; i++)
         (*mpUnits)[i] ^= UNIT_MASK;
   }

   // Handle last octet
   bitMask = bitsLeftOf(toIndex & BIT_INDEX_MASK);
   (*mpUnits)[endUnitIndex] ^= bitMask;

   // Check to see if we reduced size
   recalculateUnitsUsed();
   return 0;
}

/*
* Returns the value of the bit with the specified index.
*/
EXTRTMETHOD OSBOOL ASN1CBitStr::get(OSUINT32 bitIndex) {
   if(bitIndex > mMaxNumBits)
      return FALSE;
   
   OSBOOL result = FALSE;
   int unitsIndex = unitIndex(bitIndex);
   if(unitsIndex < mUnitsUsed)
      result = (((*mpUnits)[unitsIndex] & bit(bitIndex)) != 0);

   return result;
}

/*
* Returns the number of bytes of space actually in use by this 
* bit string to represent bit values. 
*/
EXTRTMETHOD int ASN1CBitStr::size() const {
   return mUnitsUsed;
}

/*
* Returns the "logical size" of this bit string: the index of
* the highest set bit in the bit string plus one. Returns zero
* if the bit string contains no set bits.
*/
EXTRTMETHOD OSUINT32 ASN1CBitStr::length() const {
   if(mUnitsUsed == 0)
      return 0;

   OSOCTET highestUnit = (*mpUnits)[mUnitsUsed - 1];
   return BITS_PER_UNIT * (mUnitsUsed - 1) + rtxOctetBitLen (highestUnit);
}

/*
* Returns the number of bits set in val.
* For a derivation of this algorithm, see
* "Algorithms and data structures with applications to 
*  graphics and geometry", by Jurg Nievergelt and Klaus Hinrichs,
*  Prentice Hall, 1993.
*/
static int bitCount(unsigned long val) {
#ifndef __SYMBIAN32__
#if BITS_PER_UNIT <= 8
   val -= (val & 0xaaL) >> 1;
   val =  (val & 0x33L) + ((val >> 2) & 0x33L);
   val =  (val + (val >> 4)) & 0x0fL;
   return (int)(val & 0xff);

#elif BITS_PER_UNIT <= 16
   val -= (val & 0xaaaaL) >> 1;
   val =  (val & 0x3333L) + ((val >> 2) & 0x3333L);
   val =  (val + (val >> 4)) & 0x0f0fL;
   val += val >> 8;     
   return (int)(val & 0xff);

#elif BITS_PER_UNIT <= 32
   val -= (val & 0xaaaaaaaaL) >> 1;
   val =  (val & 0x33333333L) + ((val >> 2) & 0x33333333L);
   val =  (val + (val >> 4)) & 0x0f0f0f0fL;
   val += val >> 8;
   val += val >> 16;
   return (int)(val & 0xff);

#elif BITS_PER_UNIT <= 64
   val -= (val & 0xaaaaaaaaaaaaaaaaL) >> 1;
   val =  (val & 0x3333333333333333L) + ((val >> 2) & 0x3333333333333333L);
   val =  (val + (val >> 4)) & 0x0f0f0f0f0f0f0f0fL;
   val += val >> 8;
   val += val >> 16;
   return ((int)(val) + (int)(val >> 32)) & 0xff;

#else
#error Size of BITS_PER_UNITS greater than 64 bit does not supported
#endif
#else /* we are using SYMBIAN32 */
   return 0;
#endif
}

/*
* Returns the number of bits set to 1 in this
* bit string.
*/
EXTRTMETHOD int ASN1CBitStr::cardinality() const {
   int sum = 0;
   for(int i = 0; i < mUnitsUsed; i++)
      sum += bitCount((*mpUnits)[i]);
   return sum;
}

/*
* Copies bit string to buffer (pBuf).
*/
EXTRTMETHOD int ASN1CBitStr::getBytes(OSOCTET* pBuf, int bufSz) {
   if(bufSz < mUnitsUsed)
      return LOG_RTERR(mpContext->getPtr(), ASN_E_INVLEN);
   memcpy(pBuf, (*mpUnits), mUnitsUsed * sizeof(OSOCTET));
   if(bufSz > mUnitsUsed)
      memset(pBuf + mUnitsUsed, 0, (bufSz - mUnitsUsed) * sizeof(OSOCTET));
   return 0;
}

/* 
* Returns the unit of this bitset at index j as if this bit string had an
* infinite amount of storage.
*/
EXTRTMETHOD OSOCTET ASN1CBitStr::getBits(int j) {
   return (j < mUnitsUsed) ? (*mpUnits)[j] : 0;
}

/*
* Copies bit string composed of bits from this bit string
* from 'fromIndex'(inclusive) to 'toIndex'(exclusive).
*
* Returns: 0 - if succeed, or 
*          RTERR_OUTOFBND - if one of indexes is out of bounds, or
*          RTERR_BADVALUE - if fromIndex > toIndex, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::get
(OSUINT32 fromIndex, OSUINT32 toIndex, OSOCTET* pBuf, int bufSz) 
{
   if(fromIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(toIndex > mMaxNumBits)
      return LOG_RTERR(mpContext->getPtr(), RTERR_OUTOFBND);
   if(fromIndex > toIndex)
      return LOG_RTERR(mpContext->getPtr(), RTERR_BADVALUE);
   if(toIndex - fromIndex > (OSUINT32)(bufSz << ADDRESS_BITS))
      return LOG_RTERR(mpContext->getPtr(), RTERR_STROVFLW);

   memset(pBuf, 0, bufSz * sizeof(OSOCTET));
   
   OSUINT32 len = length();
   // If no set bits in range return empty bitset
   if(len <= fromIndex || fromIndex == toIndex)
      return 0;

   // An optimization
   if(len < toIndex)
      toIndex = len;

   int startBitIndex = fromIndex & BIT_INDEX_MASK;
   int endBitIndex = toIndex & BIT_INDEX_MASK;
   int targetOcts = ((toIndex - fromIndex + BITS_PER_UNIT - 1) >> ADDRESS_BITS);
   int sourceOcts = unitIndex(toIndex) - unitIndex(fromIndex) + 1;
   int inverseIndex = BITS_PER_UNIT - startBitIndex;
   int targetIndex = 0;
   int sourceIndex = unitIndex(fromIndex);

   // Process all octets but the last octet
   while(targetIndex < targetOcts - 1) {
      pBuf[targetIndex++] =
         ((*mpUnits)[sourceIndex] << startBitIndex) |
         ((inverseIndex == BITS_PER_UNIT) ? 0 : 
          (*mpUnits)[sourceIndex + 1] >> inverseIndex);
      sourceIndex++;
   }

   // Process the last octet
   pBuf[targetIndex] = 
      (sourceOcts == targetOcts ?
       ((*mpUnits)[sourceIndex] & bitsLeftOf(endBitIndex)) << startBitIndex :
       ((*mpUnits)[sourceIndex] << startBitIndex) | 
       ((inverseIndex == BITS_PER_UNIT) ? 0 :
        (getBits(sourceIndex + 1) & bitsLeftOf(endBitIndex)) >> inverseIndex));

   return 0;
}

/*
* Performs a logical AND of this target bit set with the 
* argument bit set.
*
* Returns: 0 - if succeed, or 
*          ASN_E_INVLEN - if 'octsNumbits' is negative, or
*          RTERR_INVPARAM - if pOctstr is the same bit string as this or null, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::doAnd(const OSOCTET* pOctstr, OSUINT32 octsNumbits) {
   if(octsNumbits == 0) {
      clear();
      return 0;
   }
   if((*mpUnits) == pOctstr || !pOctstr)
      return LOG_RTERR(mpContext->getPtr(), RTERR_INVPARAM);

   // Perform logical AND on bits in common
   int otherUnitsUsed = ((octsNumbits + BITS_PER_UNIT - 1) >> ADDRESS_BITS);

   int unitsInCommon = (otherUnitsUsed < mUnitsUsed) ? otherUnitsUsed : mUnitsUsed;
   int i;
   for(i = 0; i < unitsInCommon; i++)
      (*mpUnits)[i] &= pOctstr[i];
   
   // Clear out (*mpUnits) no longer used
   if(mUnitsUsed > i) 
      memset(&(*mpUnits)[i], 0, (mUnitsUsed - i) * sizeof(OSOCTET));

   // Recalculate units in use if necessary
   mUnitsUsed = unitsInCommon;
   recalculateUnitsUsed();
   return 0;
}

/*
* Performs a logical OR of this target bit set with the 
* argument bit set.
*
* Returns: 0 - if succeed, or 
*          ASN_E_INVLEN - if 'octsNumbits' is negative, or
*          RTERR_INVPARAM - if pOctstr is the same bit string as this or null, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::doOr(const OSOCTET* pOctstr, OSUINT32 octsNumbits) {
   if(octsNumbits == 0) {
      if(mMaxNumBits == UINT_MAX)
         return LOG_RTERR(mpContext->getPtr(), RTERR_INVPARAM);
      set(0, mMaxNumBits);
      return 0;
   }
   if((*mpUnits) == pOctstr || !pOctstr)
      return LOG_RTERR(mpContext->getPtr(), RTERR_INVPARAM);
   //if(octsNumbits < 0)
   //   return LOG_RTERR(mpContext->getPtr(), ASN_E_INVLEN);

   if(mMaxNumBits < octsNumbits)
      octsNumbits = mMaxNumBits; 
   int otherUnitsUsed = ((octsNumbits + BITS_PER_UNIT - 1) >> ADDRESS_BITS);
   int stat = checkCapacity(otherUnitsUsed);
   if(stat != 0)
      return LOG_RTERR(mpContext->getPtr(), stat);
   // Perform logical OR on bits in common
   int i;
   for(i = 0; i < otherUnitsUsed - 1; i++)
      (*mpUnits)[i] |= pOctstr[i];
   
   // Process last unit
   (*mpUnits)[i] |= (pOctstr[i] & bitsLeftOf(octsNumbits & BIT_INDEX_MASK));
   
   (*mpNumBits) = length();
   return 0;
}

/*
* Performs a logical XOR of this target bit set with the 
* argument bit set.
*
* Returns: 0 - if succeed, or 
*          ASN_E_INVLEN - if 'octsNumbits' is negative, or
*          RTERR_INVPARAM - if pOctstr is null, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::doXor(const OSOCTET* pOctstr, OSUINT32 octsNumbits) {
   if(octsNumbits == 0)
      return 0; // no need to change bit string if octsNumbits is zero
   if(!pOctstr) 
      return LOG_RTERR(mpContext->getPtr(), RTERR_INVPARAM);
   if(mMaxNumBits < octsNumbits)
      octsNumbits = mMaxNumBits; 
   int otherUnitsUsed = ((octsNumbits + BITS_PER_UNIT - 1) >> ADDRESS_BITS);

   if(mUnitsUsed < otherUnitsUsed) {
      int stat = checkCapacity(otherUnitsUsed);
      if(stat != 0)
         return LOG_RTERR(mpContext->getPtr(), stat);
   }

   // Perform logical XOR on bits in common
   int i;
   for(i = 0; i < otherUnitsUsed - 1; i++)
      (*mpUnits)[i] ^= pOctstr[i];    

   // Process last unit
   (*mpUnits)[i] ^= (pOctstr[i] & bitsLeftOf(octsNumbits & BIT_INDEX_MASK));

   recalculateUnitsUsed();
   return 0;
}

/*
* Clears all of the bits in this bit string whose corresponding
* bit is set in the specified bit string.
*
* Returns: 0 - if succeed, or 
*          ASN_E_INVLEN - if 'octsNumbits' is negative, or
*          RTERR_INVPARAM - if pOctstr is null, or
*          other error codes (see asn1type.h).
*/
EXTRTMETHOD int ASN1CBitStr::doAndNot(const OSOCTET* pOctstr, OSUINT32 octsNumbits) {
   if(octsNumbits == 0) 
      return 0; // no need to change bit string if octsNumbits is zero
   if(!pOctstr) 
      return LOG_RTERR(mpContext->getPtr(), RTERR_INVPARAM);
   int otherUnitsUsed = ((octsNumbits + BITS_PER_UNIT - 1) >> ADDRESS_BITS);
   int unitsInCommon = (mUnitsUsed < otherUnitsUsed) ? mUnitsUsed : otherUnitsUsed;

   // Perform logical (a & !b) on bits in common
   for(int i = 0; i < unitsInCommon; i++) {
      (*mpUnits)[i] &= ~pOctstr[i];
   }

   recalculateUnitsUsed();
   return 0;
}

/*
* Shifts all bits to the left by 'shift' bits.
*/
EXTRTMETHOD int ASN1CBitStr::shiftLeft(OSUINT32 shift) {
   int srcOct = unitIndex(shift);
   int srcIndex = shift & BIT_INDEX_MASK;
   int invIndex = BITS_PER_UNIT - srcIndex;
   int dstOct = 0;
   int len = length();
   if(len == 0)
      return 0;
   int targetOcts = ((len - shift + BITS_PER_UNIT - 1) >> ADDRESS_BITS);
   // Process all octets but the last octet
   while(dstOct < targetOcts - 1) {
      (*mpUnits)[dstOct++] = 
         ((*mpUnits)[srcOct] << srcIndex) |
         ((invIndex == BITS_PER_UNIT) ? 0 : (*mpUnits)[srcOct + 1] >> invIndex);
      srcOct++;
      }
  
   len &= BIT_INDEX_MASK;
   // Process the last octet
   (*mpUnits)[dstOct] = (mUnitsUsed == targetOcts ?
     ((*mpUnits)[srcOct] & bitsLeftOf(len)) << srcIndex :
     ((*mpUnits)[srcOct] << srcIndex) | ((invIndex == BITS_PER_UNIT) ? 0 :
     (getBits(srcOct + 1) & bitsLeftOf(len)) >> invIndex));

   // Clear out unused bytes
   if(targetOcts < mUnitsUsed) {
      memset(&(*mpUnits)[targetOcts], 0, (mUnitsUsed - targetOcts) * sizeof(OSOCTET));
   } 
   
   recalculateUnitsUsed();
   return 0;
}

/*
* Shifts all bits to the right by 'shift' bits.
*/
EXTRTMETHOD int ASN1CBitStr::shiftRight(OSUINT32 shift) {
   int invIndex = shift & BIT_INDEX_MASK;
   int srcIndex = BITS_PER_UNIT - invIndex;
   int len = length();
   if(len == 0)
      return 0;
   if(mMaxNumBits != UINT_MAX) {
      len -= shift;
      if(len <= 0) {
         clear();
      return 0;
      }
   }
   int srcOct = unitIndex(len - BITS_PER_UNIT + 1);
   int dstOct = unitIndex(len + shift - 1);
   int emptyOcts = unitIndex(shift);
   
   if(mMaxNumBits == UINT_MAX) { // dynamic? allocate more mem, if necessary
      int stat = checkCapacity(dstOct + 1);
      if(stat != 0)
         return LOG_RTERR(mpContext->getPtr(), stat);
      }

   // Process first (last in fact) unit
   if((len & BIT_INDEX_MASK) > srcIndex)
      (*mpUnits)[dstOct--] = ((*mpUnits)[srcOct + 1] << srcIndex);

   // Process all octets but the last octet
   while(srcOct >= 0) {
      (*mpUnits)[dstOct--] = 
         ((*mpUnits)[srcOct] << srcIndex) |
         ((invIndex == BITS_PER_UNIT) ? 0 : (*mpUnits)[srcOct + 1] >> invIndex);
      srcOct--;
      }
   
   // Process the last (first, in fact) unit
   if(invIndex != BITS_PER_UNIT) {
      (*mpUnits)[dstOct] = ((*mpUnits)[srcOct + 1] >> invIndex);;
   }

   // Clear out unused bytes
   if(emptyOcts > 0) {
      memset(&(*mpUnits)[0], 0, emptyOcts * sizeof(OSOCTET));
   }   
   if(mMaxNumBits != UINT_MAX) {
      // Clear out unised bits in last unit   
      (*mpUnits)[mUnitsUsed - 1] &= bitsLeftOf(mMaxNumBits & BIT_INDEX_MASK);
   }
   recalculateUnitsUsed();
   return 0;
}

/* 
* Returns number of unused bits in last unit. 
*/
EXTRTMETHOD int ASN1CBitStr::unusedBitsInLastUnit() {
   if(mUnitsUsed == 0)
      return 0;

   OSOCTET highestUnit = (*mpUnits)[mUnitsUsed - 1];
   return BITS_PER_UNIT - rtxOctetBitLen(highestUnit);
}

/*
* Returns filled ASN1TDynBitStr. Memory for data is not
* reallocated, thus, this ASN1TDynBitStr will be eligible while
* this ASN1CBitStr is in scope.
*/
EXTRTMETHOD ASN1CBitStr::operator ASN1TDynBitStr() {
   ASN1TDynBitStr dynOctStr;
   dynOctStr.data = (*mpUnits);
   dynOctStr.numbits = length();
   return dynOctStr;
}

/*
* Returns pointer to filled ASN1TDynBitStr. In this method,
* memory is allocated, and bits are copied to it.
*/
EXTRTMETHOD ASN1CBitStr::operator ASN1TDynBitStr*() {
   ASN1TDynBitStr* dynOctStr = (ASN1TDynBitStr*)memAlloc(sizeof(ASN1TDynBitStr));
   void* data = memAlloc(mUnitsUsed * sizeof(OSOCTET));
   memcpy(data, (*mpUnits), mUnitsUsed * sizeof(OSOCTET));
   dynOctStr->data = (const OSOCTET*)data;
   dynOctStr->numbits = length();
   return dynOctStr;
}
