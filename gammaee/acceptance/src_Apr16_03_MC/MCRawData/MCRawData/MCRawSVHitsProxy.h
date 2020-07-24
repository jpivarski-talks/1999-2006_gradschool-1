// -*- C++ -*-
#if !defined(MCRAWDATA_MCRAWSVHITSPROXY_H)
#define MCRAWDATA_MCRAWSVHITSPROXY_H
//
// Package:     MCRawData
// Module:      MCRawSVHitsProxy
// 
// Description: 
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawSVHitsProxy.h,v 1.7 2002/09/27 20:23:44 bkh Exp $
//
// Revision history
//
// $Log: MCRawSVHitsProxy.h,v $
// Revision 1.7  2002/09/27 20:23:44  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.6  2001/12/20 17:11:30  bkh
// Install fake merge flag for Cathodes as with other detectors
// Use fake merge flag for Cathodes
// Fix SV proxy fcn to avoid compiler warning about
//      argument overriding member data
//
// Revision 1.5  2001/11/20 05:07:21  victor
// switched to a bindable proxy, introduced online (VME CPU) sparsifier, revised back-end chip level sparsification/decisions, simulated wire-bonding bugs (for jammed channels), attempted to speed up the code (many thanks to ajm36), other small changes
//
// Revision 1.4  2001/04/30 17:05:29  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.3  2000/12/01 19:21:40  cja23
// addToMap function declaration added
//
// Revision 1.2  1999/06/04 21:39:08  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:13  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "RawData/RawSVHits.h"
#include "DBSVChannel.hh"
#include "FrameAccess/FAConstants.h"
#include "CommandPattern/Parameter.h"
#include "DataHandler/SyncValue.h"
#include "CleoDB/DBEventHeader.h"
#include "DBSVChannelOnline.hh" 
#include "SVChannelOnlineEnum.hxx"
#include "CopySiSparsifier.hxx"
#include "CommandPattern/Parameter.h"
#include "RandomModule/RandomGenerator.h"

// forward declarations
#include "STLUtility/fwd_vector.h"



class MCRawSVHitsProxy : public ProxyBindableTemplate< RawSVHits >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawSVHits value_type;

      typedef STL_MAP(int,float) StripMap;

      // Constructors and destructor
      MCRawSVHitsProxy(Parameter< DABoolean > & ,
		       Parameter< DABoolean > & ,
		       Parameter< float > & );

      virtual ~MCRawSVHitsProxy();

      // member functions

      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );

      //updateSparAlgorithm() is bound to SiStream::kSVCalibOnline. 
      //It it meant to update the object containing the sparsifier
      void updateSparAlgorithm(const Record&);

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      MCRawSVHitsProxy( const MCRawSVHitsProxy& );

      
      // assignment operator(s)
      const MCRawSVHitsProxy& operator=( const MCRawSVHitsProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (MCRawSVHitsProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions
      void addToMap(const UInt32,  const float);

      //returns the crate number based on channel number;
      inline UInt32 crateNumber(UInt32 address);

      //returns the index based for indexing into the constants arrays
      inline UInt32 get_SVXIdx(UInt32 address);

      //loads intrinsic to the sparsifier constants
      void loadSparsifierConsts();

      //fills arrays with indices of jammed channels,
      //these arrays are needed for the copysisparsifiers
      void fillJammedChannelIndices(UInt32*, 
			CLEOConstants< DBSVChannelOnline > * );

      //fill yet another array with jammed channel address,
      //this array is used for insertion of jammed channels into
      //the data stream
      void fillJammedChannelAddresses();

      //splits the channel constants into two chunks - 
      //one for each of the two online readout crates
      void splitConstants(const CLEOConstants< DBSVChannelOnline > *,
			        DBSVChannelOnline  *,
			        DBSVChannelOnline  *);

      //fills arrays with chip constants for faster access
      int upDateChipConstants(const Record&);

      //returns sparsifier version based on the run number
      int sparsifierVersion();

      // data members
      value_type* m_RawSVHits ;

      STL_VECTOR( UInt32 ) m_words ; //this proxy owns the data words!

      const Parameter<DABoolean>& m_makeMCRawSVHits;
      const Parameter<DABoolean>& m_useFakeMerge;
      const Parameter<float>    & m_CMNScaleFactor;


      //CopySiSparsifier contains sparsification algorithm(s) used online,
      //two such objects are created - one for each of the two readout crates
      CopySiSparsifier* myAlgorithm1;
      CopySiSparsifier* myAlgorithm2;

      //pointers to the data word in the crates
      UInt32 *pCrate1;
      UInt32 *pCrate2;

      FAConstants< DBSVChannelOnline > myChannelOnlineConsts;
      FAConstants<DBSVChannel>         myChannelConsts;

      //the channel constants are split into two chunks - one for each crate
      CLEOConstants< DBSVChannelOnline > *crate1Constants;
      CLEOConstants< DBSVChannelOnline > *crate2Constants;

      //
      //FAConstants<DBSVXSparsifier>  mySparConsts;
      
      UInt32 m_sparsifierVersion;

      UInt32 runNumber;
      DABoolean doesSparExist;

      DABoolean areAddressesFilled;
      UInt32 *AddressesOfJammedChannels;

      
      UInt8 *backEndChipThreshold;
      UInt8 *backEndChipMode;
      SyncValue m_chipSetSync;

      StripMap & unique;

      RandomGenerator& ran;
      
      // static data members

      static const UInt32  maxNumberOfWords;
      static const UInt32  crateOffset;
      const float kSiBandGap;
      const float kElectronsPerADC;
};

// inline function definitions

inline UInt32 MCRawSVHitsProxy::crateNumber(UInt32 address)
{
  if(  ( address > 0     && address <= 31232 ) ||
       ( address > 62464 && address <= 93696 )   )
  {
      return 1;
  }
  else if (address > 0 && address <= 124928)
  {
      return 2;
  }
  else //this should not happen 
  {
     cout<<"MCRawSVHitsProxy: crateNumber(): bad address = "<<address<<endl;
     return 3;
  }
}

inline UInt32 MCRawSVHitsProxy::get_SVXIdx(UInt32 address)
{
   if(address > NUM_SVX_CHANNELS_RPHI)
   {
      address -= NUM_SVX_CHANNELS_RPHI;
      
      if(address > NUM_SVX_CHANNELS_RPHIPERCRATE)
      {
         return (address - 1);
      }
      else 
      {
         return (address - 1) + NUM_SVX_CHANNELS_RPHIPERCRATE;
      }
   }
   else
   {
      if (address > NUM_SVX_CHANNELS_RPHIPERCRATE)
      {
         return (address - NUM_SVX_CHANNELS_RPHIPERCRATE - 1);
      }
      else
      {
         return (address - 1);
      }
   }
}

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "package/Template/MCRawSVHitsProxy.cc"
//#endif

#endif /* PACKAGE_MCRAWSVHITSPROXY_H */




