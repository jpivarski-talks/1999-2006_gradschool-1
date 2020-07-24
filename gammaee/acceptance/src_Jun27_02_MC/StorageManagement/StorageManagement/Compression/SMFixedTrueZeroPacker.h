#if !defined(STORAGEMANAGEMENT_SMFIXEDTRUEZEROPACKER_H)
#define STORAGEMANAGEMENT_SMFIXEDTRUEZEROPACKER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFixedTrueZeroPacker
// 
/**\class SMFixedTrueZeroPacker SMFixedTrueZeroPacker.h StorageManagement/SMFixedTrueZeroPacker.h

 Description: Compresses a value of type T into two UInt32s using Fixed 
              compression but guarantees that a packed value of 0 always
	      returns 0

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon May  8 10:27:45 EDT 2000
// $Id: SMFixedTrueZeroPacker.h,v 1.3 2002/04/01 19:04:10 cdj Exp $
//
// Revision history
//
// $Log: SMFixedTrueZeroPacker.h,v $
// Revision 1.3  2002/04/01 19:04:10  cdj
// optimized doBitShift used while unpacking
//
// Revision 1.2  2001/05/11 20:31:24  cdj
// handles +-Infintity and NaN and properly calculate number of bits needed
//
// Revision 1.1  2000/05/08 15:25:57  cdj
// added SMFixedTrueZeroPacker
//

// system include files

// user include files
#include "StorageManagement/Compression/SMPackerTemplate.h"

// forward declarations

template< class T>
class SMFixedTrueZeroPacker : public SMPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFixedTrueZeroPacker( unsigned int iNumberOfBits,
			     T iPrecision,
			     T iOffset ) : 
	 SMPackerTemplate<T>( iNumberOfBits ),
	 m_precision( iPrecision ),
	 m_offset( iOffset ),
	 m_maxValue( ( ~UInt32(0) >> (32 - numberOfBits()) ) )
      {}
      //virtual ~SMFixedTrueZeroPacker();

      // ---------- member functions ---------------------------
      void pack( T iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 //first do compression
	 UInt32 compressedValue;

	 if( T(0) == iValue ) {
	    //always store 0 as 0
	    compressedValue = 0;
	 } else {
	    //shift all other values by 1
	    if( iValue < m_offset ) {
	       compressedValue = 1;
	    } else {
	       compressedValue = (iValue - m_offset)/m_precision + 1;
	    }
	    if( compressedValue > m_maxValue ) {
	       compressedValue = m_maxValue;
	    }
	 }
	 doBitShifting( compressedValue,
			ioStartWord,
			oOverflowWord,
			ioStartBit );
      }

      T unpack( const UInt32 iStartWord,
		const UInt32 iOverflowWord,
		unsigned char& ioStartBit ) const {

	 UInt32 compressedValue = undoBitShifting( iStartWord,
						   iOverflowWord,
						   ioStartBit );
	 if( 0 == compressedValue ) {
	    return compressedValue ;
	 }
	 //Now convert this to the proper type
	 return (compressedValue - 1)*m_precision + m_offset;
      }

      // accessors
      T precision() const { return m_precision; }
      T offset() const { return m_offset; }

      // ---------- static member functions --------------------
      static SMFixedTrueZeroPacker<T> createFromMinMaxPrecision( 
	 T iMin, T iMax, T iPrecision ) {
	 return SMFixedTrueZeroPacker<T>( 
	    //the +iPrecision is because we treat 0 special
	    calcNumberOfBitsNeeded( iMax - iMin + iPrecision, iPrecision ),
	    iPrecision,
	    iMin );
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMFixedTrueZeroPacker( const SMFixedTrueZeroPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFixedTrueZeroPacker& operator=( const SMFixedTrueZeroPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T m_precision;
      T m_offset;
      unsigned int m_maxValue;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMFixedTrueZeroPacker.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMFIXEDTRUEZEROPACKER_H */
