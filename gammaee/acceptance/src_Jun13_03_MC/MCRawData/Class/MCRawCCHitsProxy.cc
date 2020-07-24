// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawCCHitsProxy
// 
// Description: transform responses into raw data w/help of constants
//
// Implementation:
//                 The job of this class is to create the raw CC hits
//                 from the MC responses plus whatever constants are needed.
//                 Several useful stl vectors are created at construction
//                 time and re-used on each event both to allow global
//                 access within this unit and to avoid repeated new
//                 memory allocations.
//
//                 The constants are extracted in the bound methods
//                 into member data.
//
//                 The sparsification proceeds as follows:
//                 (1) integrate over MC particle type, summing
//                     energies by daqId
//                 (2) transform energies into floating point
//                     digis using peds & gains; also save range
//                 (3) add noise to digis (to save time here
//                     we only generate some new gaussian randoms
//                     each event and shuffle up the rest)
//                 (4) truncate digis to integers
//                 (5) sparsify using neighbor lists & thresholds
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawCCHitsProxy.cc,v 1.27 2003/02/04 19:34:46 cdj Exp $
//
// Revision history
//
// $Log: MCRawCCHitsProxy.cc,v $
// Revision 1.27  2003/02/04 19:34:46  cdj
// get iomanip header from C++Std
//
// Revision 1.26  2003/01/29 19:31:04  cleo3
// changes needed to compile using g++
//
// Revision 1.25  2002/11/21 21:12:53  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.24  2002/09/27 20:23:08  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.23  2002/06/13 19:53:34  bkh
// Implement use of ccmcpeeldaqmap in the calorimeter processing
// Implement parameter to turn off trigger simulation as with other detectors
//
// Revision 1.22  2001/12/18 22:33:09  bkh
// Institute CC "fake merge" flag like other detectors
// Force trigger to get CalibratedDRHits not raw data
//
// Revision 1.21  2001/09/21 16:38:07  bkh
// Fix bug in which a negative fluctuation would becine positive
// Fix sparsification for early run numbers
// Just read mc gain constants from file now instead of mucking with them
//
// Revision 1.20  2001/07/09 20:47:30  bkh
// Protect digi from being too big and warn when it is truncated
//
// Revision 1.19  2001/06/05 17:24:51  bkh
// Fine tune CC MC again
//
// Revision 1.18  2001/06/04 21:20:35  bkh
// More CC tuning
//
// Revision 1.17  2001/06/04 07:11:27  bkh
// smear CC a bit more for agreement with BLV study
//
// Revision 1.16  2001/06/04 03:21:56  bkh
// Tune CC
//
// Revision 1.15  2001/04/30 17:05:21  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.14  2000/09/28 15:21:02  bkh
// Eliminate irrelevant check of constants validity
//
// Revision 1.13  2000/04/06 21:19:28  bkh
// Accomodate unphysical daqId's in FBUS constants
//
// Revision 1.12  2000/04/04 21:17:45  bkh
// Add coherent noise
//
// Revision 1.11  2000/02/10 22:59:30  bkh
// Use precanned seeds at construction time, not interrupting sequence
//
// Revision 1.10  1999/11/03 19:07:11  bkh
// Fix bug which triggered out of range assert
//
// Revision 1.9  1999/10/30 12:31:48  cleo3
// updated to work with cxx 6.2
//
// Revision 1.8  1999/10/25 17:37:06  bkh
// Use official new random number generator
//
// Revision 1.7  1999/10/24 20:37:21  cdj
// removed inappropriate use of typename
//
// Revision 1.6  1999/07/05 17:25:22  bkh
// fix setting of CC rising-edge bit
//
// Revision 1.5  1999/06/15 14:56:07  bkh
// Improve CC simulation with MC gain;
//       allow missing detectors in MCRawEventDataProxy
//
// Revision 1.4  1999/06/10 20:22:25  bkh
// Better stab at CC simulation
//
// Revision 1.3  1999/06/04 21:38:50  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.2  1999/05/19 17:01:41  bkh
// Make compatible with recent RawData changes
//
// Revision 1.1  1999/02/25 22:02:49  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>
#include "C++Std/iomanip.h"
#include "C++Std/fstream.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "MCRawData/MCRawCCHitsProxy.h"

#include "C3cc/CcStream.h"

#include "RandomModule/RandomGenerator.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kReport = "MCRawData.MCRawCCHitsProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawCCHitsProxy::MCRawCCHitsProxy( const Parameter<DABoolean>& aMake ,
				    const Parameter<DABoolean>& aFake ) :
   m_RawCCHits ( 0 ) ,
   m_words     (   ) ,
   m_energies  ( CCDatum::k_maxDaqId + 9, MCCCResponse::EnergyType(0) ) ,
   m_ranges    ( CCDatum::k_maxDaqId + 9, CcRangeType(0)   ) ,
   m_digis     ( CCDatum::k_maxDaqId + 9, CcDigiType(0)    ) ,
   m_gaussInc  ( CCDatum::k_maxDaqId + 9, HepDouble(0)     ) ,
   m_gaussCoh  ( CCDatum::k_maxDaqId + 9, HepDouble(0)     ) ,
   m_seedFlags ( CCDatum::k_maxDaqId + 9, DABoolean(false) ) ,
   m_keepFlags ( CCDatum::k_maxDaqId + 9, DABoolean(false) ) ,
   m_seedThr   ( CCDatum::k_maxDaqId + 9, CcDigiType(0)    ) ,
   m_nbrThr    ( CCDatum::k_maxDaqId + 9, CcDigiType(0)    ) ,
//   m_smc       ( CCDatum::k_maxDaqId + 9, Double(0)        ) ,
   m_gains     () ,
   m_elec      () ,
   m_peelIds   () ,
   m_daqIds    () ,
   m_mc        () ,
   m_cohNoise  () ,
   m_fbus      () ,
   m_neighbors () ,
   m_geomSpec  () ,
   m_make      ( aMake ) ,
   m_fake      ( aFake )
{
   m_words.reserve( 2000 ) ; // allocate reasonable length!

   if( m_make.value() ) 
   {
      bind( &MCRawCCHitsProxy::boundMethodECalChannel ,
	    CcStream::kECalChannel ) ;
      bind( &MCRawCCHitsProxy::boundMethodDaqPeelMap  ,
	    CcStream::kDaqPeelMap  ) ;
      bind( &MCRawCCHitsProxy::boundMethodPeelDaqMap  ,
	    CcStream::kMCPeelDaqMap  ) ;
      bind( &MCRawCCHitsProxy::boundMethodGainProducts,
	    Stream::kBeginRun      ) ;
      bind( &MCRawCCHitsProxy::boundMethodBaseGeometry,
	    Stream::kBaseGeometry  ) ;
      bind( &MCRawCCHitsProxy::boundMethodFBUSChannel ,
	    CcStream::kFBUSChannel ) ;
      bind( &MCRawCCHitsProxy::boundMethodMCCrystal   ,
	    CcStream::kMCCrystal   ) ;
      bind( &MCRawCCHitsProxy::boundMethodCohNoise    ,
	    CcStream::kCoherentNoise);

      RandomGenerator& ran ( RandomGenerator::instance() ) ;

      const RandomGenerator::SeedPair oldSeeds ( ran.seeds() ) ;

      const RandomGenerator::SeedPair newSeeds ( 9, 0 ) ;
      ran.setSeeds( newSeeds ) ;

      ran.gauss( &(*(m_gaussInc.begin())), &(*(m_gaussInc.end())) ) ;

      ran.gauss( &(*(m_gaussCoh.begin())), &(*(m_gaussCoh.end())) ) ;

      ran.setSeeds( oldSeeds ) ;
   }
}

// MCRawCCHitsProxy::MCRawCCHitsProxy( const MCRawCCHitsProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawCCHitsProxy::~MCRawCCHitsProxy()
{
   delete m_RawCCHits  ;
}

//
// assignment operators
//
// const MCRawCCHitsProxy& MCRawCCHitsProxy::operator=( const MCRawCCHitsProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//

void
MCRawCCHitsProxy::invalidateCache()
{
   delete m_RawCCHits ;
   m_RawCCHits = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawCCHitsProxy::value_type*
MCRawCCHitsProxy::faultHandler( const Record&  iRecord ,
				const DataKey& iKey      )
{
 
   assert( 0 == m_RawCCHits ) ;
   assert( m_words.empty()  ) ; // always start out empty

   // check if MCRawCCHits are wanted at all; otherwise leave m_RawCCHits empty 

   if( m_make.value() ) 
   { //--------------------------------- check constants validity ------------
     if( !m_elec.valid()      || 
         !m_peelIds.valid()   ||
         !m_daqIds.valid()    ||
         !m_mc.valid()        ||
         !m_cohNoise.valid()  ||
         !m_gains.valid()     ||
         !m_fbus.valid()      ||
         !m_neighbors.valid() ||
         !m_geomSpec.valid()        )
     {
        report( ERROR, kReport ) << "Invalid CC Constants" << endl;
        return 0 ;
     }
     //-----------------------------------------------------------------------

     RandomGenerator& ran ( RandomGenerator::instance() ) ;

     const UInt16 incSize ( m_gaussInc.size() ) ;
     const UInt16 cohSize ( m_gaussCoh.size() ) ;

     static STL_VECTOR( HepDouble ) gInc ( incSize, HepDouble(0) ) ;
     static STL_VECTOR( HepDouble ) gCoh ( cohSize, HepDouble(0) ) ;

     UInt16 tmp ;
     const UInt16 shift ( ( tmp = floor( ran.flat()*incSize ) ) < incSize 
	   		  ? tmp : tmp-1 ) ;

     const HepDouble flat ( ran.flat() ) ;

     const STL_VECTOR( HepDouble )& g1 
	( 0.5 < flat ? m_gaussInc : m_gaussCoh ) ;
     const STL_VECTOR( HepDouble )& g2
	( 0.5 < flat ? m_gaussCoh : m_gaussInc ) ;

     assert( shift < incSize ) ;

     rotate_copy( g1.begin() , g1.begin() + shift , g1.end() , gInc.begin() ) ;

     rotate_copy( g2.begin() , g2.begin() + shift , g2.end() , gCoh.begin() ) ;

     //--------------------------------------------------------------------

     //--------------------------------------- extract MC responses -------
     FATable< MCCCResponse > responses ; 
     extract( iRecord,       responses ); 
     //--------------------------------------------------------------------

     static const MCCCResponse::EnergyType myZero ( 0 ) ;
     fill( m_energies.begin(), m_energies.end() , myZero ) ;

     const CcDaqIdType firstCell ( (*m_geomSpec).specialCellId(
        CcGeometrySpec::k_firstEastEndcap ) ) ;
     const CcDaqIdType lastCell  ( (*m_geomSpec).specialCellId(
        CcGeometrySpec::k_lastWestEndcap  ) ) ;

     const CcDaqIdType firstDaqId ( m_peelIds.front().get_DaqId() ) ;
     const CcDaqIdType lastDaqId  ( m_peelIds.back() .get_DaqId()  ) ;

     //--------------------------- in energies, integrate over MC particle id 
     for( FATable< MCCCResponse >::const_iterator iR ( responses.begin() ) ;
	  iR != responses.end() ; ++iR )
     {
        m_energies[ m_daqIds[ iR->cellId() ].get_DaqId() ] += iR->energy() ;
     }
     //-----------------------------------------------------------------------

     assert( m_ranges.size() > lastDaqId ) ;
     assert( m_digis.size()  > lastDaqId ) ;

     //-------------------------------------- convert energies to TDC counts -
     {for( CcDaqIdType daqId ( firstDaqId ) ;
	   daqId <= lastDaqId ; ++daqId )
     {
	const DBCCECalChannel&    elec   ( m_elec[     daqId ]   ) ;

	const DBCCCoherentNoise&  cohe   ( m_cohNoise[ daqId ]   ) ;

	const CcCellIdType        peelId ( m_peelIds[ daqId ].get_PeelId() ) ;

	assert( firstCell <= peelId && lastCell >= peelId ) ;

	CcRangeType range ( 0 ) ;

	CcReal      tdc   ( 0 ) ;

	const CcGeV en ( m_energies[ daqId ] ) ;

//	if( en > 0.01 )
//	{
//	   report( DEBUG, kReport ) << "..........DaqId = " << daqId
//				    << ", energy=" << en << endl ;
//	}

	do // bump up the range repeatedly if off scale in this range
	{
	   ++range;

	   const CcReal tGain ( (*m_gains).gain( range, peelId ) ) ;

	   // ;
	   const CcReal mGain ( m_mc[ peelId ].get_EnergyFactor() ) ;//m_smc[ peelId ] ) ; 

	   const CcReal ePed  ( 1 == range ?
				elec.get_PedestalLow() :
				( 2 == range ? 
				  elec.get_PedestalMid() :
				  elec.get_PedestalHigh() ) ) ;

	   static const CcReal fac ( -0.032/log(10.) ) ;

	   static const CcReal bint ( -fac*log(.5) ) ;

	   const CcReal sGain ( en > 0.5 || en < 0.01 ? 1 :
				1 + ( fac*log( en ) + bint)*ran.gauss()) ;

	   tdc = en*sGain*tGain*mGain + ePed ; // now TDC counts

	   tdc = ( 15000. < tdc ? 15000. : tdc ) ; // max at 15000. range 3

//	   if( tdc-ePed > 500 )
//	   {
//	      report( DEBUG, kReport ) << "----------daqId = " << daqId
//				       << " has tdc-ped= " << tdc-ePed 
//				       << ", tdc=" << tdc
//				       << ", thresh="
//				       << m_seedThr[daqId]
//				       << endl;
//	   }
	}
	while( 14000. < tdc && 3 > range ) ; // do again if out of range

	// now add noise
	const CcReal iNoise ( 1 == range ?
			      elec.get_NoiseLow() :
			      ( 2 == range ? 
				elec.get_NoiseMid() :
				elec.get_NoiseHigh() ) ) ;

	const CcReal cNoise ( 1 == range ?
			      cohe.get_NoiseLow() :
			      ( 2 == range ? 
				cohe.get_NoiseMid() :
				cohe.get_NoiseHigh() ) ) ;

	static const CcReal fac ( -0.55/log(10.) ) ;

	static const CcReal bint ( fac*log(0.5) ) ;

	const CcReal fInc ( en > 0.5 || en < 0.01 ? 1 :
			    1 + ( fac*log( en ) - bint) ) ;

	tdc += fInc*iNoise*gInc[ daqId ] + cNoise*gCoh[ cohe.get_Group() ] ;

	// truncate at 0 and round
	m_digis[  daqId ] = ( tdc < 0 ? 0 : floor( tdc + 0.5 ) ) ;
	m_ranges[ daqId ] = range ;
     }}
     //-----------------------------------------------------------------------

     const DABoolean myFalse ( false ) ;
     const DABoolean myTrue  ( !false ) ;
     fill( m_seedFlags.begin() , m_seedFlags.end() , DABoolean ( false ) ) ;
     fill( m_keepFlags.begin() , m_keepFlags.end() , DABoolean ( false ) ) ;

     {for( CcDaqIdType daqId ( firstDaqId ) ; daqId <= lastDaqId ; ++daqId )
     {
        sparsify( daqId, m_peelIds[ daqId ].get_PeelId() ) ;
     }}

     for( CcDaqIdType daqId ( firstDaqId ) ; daqId <= lastDaqId ; ++daqId )
     {
        if( m_keepFlags[ daqId ] )
        {
	   if( !m_fake.value() ) // don't keep if no real signal nearby
	   {
	      if( !realEnergy( daqId ) )
	      {
//		 cout << "$$$$$$$$$$$$$$$$ Rejecting CC noise hit for "
//		      << daqId << ", " << m_energies[daqId] << endl ;
		 continue ;
	      }
	   }

	   static const CCDatum::DigiType bigDigi 
	      ( ~(UInt16)0 & CCDatum::k_digiBitMask ) ;
	   const        CCDatum::DigiType rDigi  ( m_digis[ daqId ] ) ;
	   const        CCDatum::DigiType digi   ( 
	      ( rDigi & CCDatum::k_digiBitMask ) == rDigi ? rDigi : bigDigi ) ;

	   const CCDatum::IsSeedType seed   ( m_seedFlags[ daqId ] ) ;
	   const CCDatum::RangeType  range  ( m_ranges[    daqId ] ) ;
	   const CCDatum::RisingType rising ( range == 1 ||
					      range == 3    ?
					      false : !false       ) ;

	   const CCDatum::ControlType control 
	      ( CCDatum::packControl( seed, rising, range ) ) ;

       	   m_words.push_back(
	      RawHits< CCDatum >::packRawWord( daqId, control, digi ) ) ;

	   if( digi != rDigi )
	   {
	      report( WARNING, kReport ) << "Unusual digi = " 
					 << m_digis[daqId]
					 << " for daqId = "
					 << daqId << endl ;
	   }
        }
     }
   }
   
   m_RawCCHits = new RawCCHits( &(*(m_words.begin())), m_words.size() );

   return m_RawCCHits ;
}

void 
MCRawCCHitsProxy::sparsify( const CcDaqIdType  aDaqId  ,
			    const CcCellIdType aCellId   )
{
   // if not already marked as seed AND is above seed threshold or range>1
   if( !m_seedFlags[ aDaqId ] && 
       ( ( m_seedThr[ aDaqId ] < m_digis[  aDaqId ] ) ||
	 ( 1                   < m_ranges[ aDaqId ] )    ) )
   {
      m_seedFlags[ aDaqId ] = true ; // mark as seed
      m_keepFlags[ aDaqId ] = true ; // mark as kept

      const CcNbr::NbrList& nbrs ( m_neighbors[ aCellId ].nbrs() ) ;
      for( CcNbr::const_iterator iNbr ( nbrs.begin() ) ;
	   iNbr != nbrs.end() ; ++iNbr )
      {
	 const CcNbr::Identifier nbr ( *iNbr ) ; // nbr object

	 const CcDaqIdType daqNbr ( m_daqIds[ nbr ].get_DaqId() ) ;

	 // if not already marked as kept AND is above nbr threshold
	 if( !m_keepFlags[ daqNbr ]                       && 
	     ( m_nbrThr[   daqNbr ] < m_digis[ daqNbr ] )    )
	 {
	    m_keepFlags[ daqNbr ] = true ; // mark as kept
	    sparsify(    daqNbr, nbr ) ;   // then sparsify this one
	 }
      }
   }
}

DABoolean 
MCRawCCHitsProxy::realEnergy( const CcDaqIdType aDaqId ) const
{
   static const double energyCut ( 0.005 ) ;

   DABoolean value ( false ) ;

   if( energyCut < m_energies[ aDaqId ] )
   {
      value = true ;
   }
   else
   {
      const CcCellIdType peelId ( m_peelIds[ aDaqId ].get_PeelId() ) ;
      const CcNbr::NbrList& nbrs ( m_neighbors[ peelId ].nbrs() ) ;
      for( CcNbr::const_iterator iNbr ( nbrs.begin() ) ;
	   iNbr != nbrs.end() ; ++iNbr )
      {
	 const CcNbr::Identifier nbr ( *iNbr ) ; // nbr object

	 const CcDaqIdType daqNbr ( m_daqIds[ nbr ].get_DaqId() ) ;

	 value = value || ( energyCut < m_energies[ daqNbr ] ) ;

	 if( value )
	 {
	    break ;
	 }
      }
   }
   return value ;
}

//
// const member functions
//

//
// static member functions
//

void 
MCRawCCHitsProxy::boundMethodECalChannel(  const Record& iRecord )
{
   report( DEBUG, kReport ) << "Electronic Constants BoundMethod" << endl ;

   extract( iRecord , m_elec ) ;
}

void 
MCRawCCHitsProxy::boundMethodMCCrystal(    const Record& iRecord ) 
{
   report( DEBUG, kReport ) << "MC Crystal Constants BoundMethod" << endl ;

   extract( iRecord , m_mc ) ;

/*
   RandomGenerator& ran ( RandomGenerator::instance() ) ;

   const RandomGenerator::SeedPair oldSeeds ( ran.seeds() ) ;

   const RandomGenerator::SeedPair newSeeds ( 11, 0 ) ;
   ran.setSeeds( newSeeds ) ;

   ofstream output ( "mcconstants.txt" ) ;

   for( UInt16 peel ( 1 ) ; peel <= CCDatum::k_maxDaqId ; ++peel )
   {
      const UInt16 ringId ( m_geomSpec->ringId( peel ) ) ;

      const double smear ( peel < 821 || peel > 6964 ? 0.010 : 0.004 ) ;

      double fact  ( peel < 621 || peel > 7164 ? 0.990 :
		     ( ( peel >  620 && peel < 1205 ) ||
		       ( peel > 6580 && peel < 7165 ) ? 0.944 :
		       1.0005 ) ) ;

      if( 3 == ringId || 66 == ringId ) { fact = fact*1.021 ; }
      if( 4 == ringId || 65 == ringId ) { fact = fact*1.000 ; }
      if( 5 == ringId || 64 == ringId ) { fact = fact*1.012 ; }
      if( 6 == ringId || 63 == ringId ) { fact = fact*1.010 ; }
      if( 7 == ringId || 62 == ringId ) { fact = fact*1.018 ; }
      if( 8 == ringId || 61 == ringId ) { fact = fact*0.980 ; }
      if( 9 == ringId || 60 == ringId ) { fact = fact*0.735 ; }
      if(10 == ringId || 59 == ringId ) { fact = fact*0.970 ; }
      if(11 == ringId || 58 == ringId ) { fact = fact*0.953 ; }
      if(12 == ringId || 57 == ringId ) { fact = fact*0.995 ; }
      if(13 == ringId || 56 == ringId ) { fact = fact*1.018 ; }
      if(14 == ringId || 55 == ringId ) { fact = fact*1.008 ; }
      if(15 == ringId || 54 == ringId ) { fact = fact*1.005 ; }
      if(16 == ringId || 53 == ringId ) { fact = fact*1.001 ; }
      if(17 == ringId || 52 == ringId ) { fact = fact*0.998 ; }
      if(18 == ringId || 51 == ringId ) { fact = fact*1.002 ; }
      if(19 == ringId || 50 == ringId ) { fact = fact*1.000 ; }
      if(20 == ringId || 49 == ringId ) { fact = fact*1.002 ; }
      if(21 == ringId || 48 == ringId ) { fact = fact*0.999 ; }
      if(22 == ringId || 47 == ringId ) { fact = fact*1.002 ; }
      if(23 == ringId || 46 == ringId ) { fact = fact*1.002 ; }
      if(24 == ringId || 45 == ringId ) { fact = fact*0.997 ; }
      if(25 == ringId || 44 == ringId ) { fact = fact*1.000 ; }
      if(26 == ringId || 43 == ringId ) { fact = fact*1.004 ; }
      if(27 == ringId || 42 == ringId ) { fact = fact*1.006 ; }
      if(28 == ringId || 41 == ringId ) { fact = fact*1.000 ; }
      if(29 == ringId || 40 == ringId ) { fact = fact*1.000 ; }
      if(30 == ringId || 39 == ringId ) { fact = fact*1.005 ; }
      if(31 == ringId || 38 == ringId ) { fact = fact*1.005 ; }
      if(32 == ringId || 37 == ringId ) { fact = fact*1.000 ; }
      if(33 == ringId || 36 == ringId ) { fact = fact*0.992 ; }
      if(34 == ringId || 35 == ringId ) { fact = fact*0.995 ; }

      const double smc ( fact*( m_mc[ peel ].get_EnergyFactor())*
			 ( 1 + smear*ran.gauss() ) ) ;
//      m_smc[ peel ] = fact*( m_mc[ peel ].get_EnergyFactor())*

      output << setw(4) << peel 
	     << setw(10) << setprecision(4) << smc << endl ;
   }

   output.close() ;
   ran.setSeeds( oldSeeds ) ;
   */   
}

void 
MCRawCCHitsProxy::boundMethodCohNoise(    const Record& iRecord ) 
{
   report( DEBUG, kReport ) << "CC Coherent Noise BoundMethod" << endl ;

   extract( iRecord , m_cohNoise ) ;
}

void 
MCRawCCHitsProxy::boundMethodDaqPeelMap(   const Record& iRecord )
{
   report( DEBUG, kReport ) << "DaqPeelMap Constants BoundMethod" << endl ;

   extract( iRecord , m_peelIds ) ;
}

void 
MCRawCCHitsProxy::boundMethodPeelDaqMap(   const Record& iRecord )
{
   report( DEBUG, kReport ) << "MCPeelDaqMap Constants BoundMethod" << endl ;

   extract( iRecord , m_daqIds ) ;
}

void 
MCRawCCHitsProxy::boundMethodGainProducts( const Record& iRecord )
{
   report( DEBUG, kReport ) << "Gain Constants BoundMethod" << endl ;

   extract( iRecord , m_gains ) ;
}

void
MCRawCCHitsProxy::boundMethodBaseGeometry( const Record& iRecord )
{
   report( DEBUG, kReport ) << "Bound Method for BaseGeometry" << endl ;

   extract( iRecord, m_neighbors );

   extract( iRecord, m_geomSpec );
}

void 
MCRawCCHitsProxy::boundMethodFBUSChannel(  const Record& iRecord )
{
   report( DEBUG, kReport ) << "FBUS Constants BoundMethod" << endl ;

   const UInt32 run ( iRecord.syncValue().runNumber() ) ;

   const DABoolean ccspa ( run > 111000 ) ;

   assert( m_seedThr.size() == m_nbrThr.size() ) ;

   extract( iRecord , m_fbus ) ;

   for( FANonSeqConstants< DBCCFBUSChannel >::const_iterator 
	   iFbus ( m_fbus.begin() ) ; iFbus != m_fbus.end() ; ++iFbus )
   {
      const DBCCFBUSChannel& fbus ( *iFbus ) ;
      const CcDaqIdType daqId ( fbus.get_DaqId() ) ;

      if( 0 < daqId && m_seedThr.size() > daqId ) 
      {
	 m_nbrThr[  daqId ] = fbus.get_SparsThreshold() ;
	 m_seedThr[ daqId ] = ( ccspa ? fbus.get_SeedThreshold() :
				m_nbrThr[ daqId ] ) ;
      }
   }
}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< RawCCHits >;

PROXY_BIND_METHOD( MCRawCCHitsProxy )
//-----------------------------------------------


