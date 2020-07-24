// -*- C++ -*-
//
// Package:     EventTypeFilterProc
// Module:      EventTypeFilterProc
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Jul 26 12:10:58 EDT 2001
// $Id: EventTypeFilterProc.cc,v 1.4 2001/11/01 18:08:01 bkh Exp $
//
// Revision history
//
// $Log: EventTypeFilterProc.cc,v $
// Revision 1.4  2001/11/01 18:08:01  bkh
// Add histograms
//
// Revision 1.3  2001/08/31 22:51:17  bkh
// Use BeamEnergy
//
// Revision 1.2  2001/08/03 18:07:11  bkh
// Add histogramming of all variables on all event types
//
// Revision 1.1.1.1  2001/07/31 18:14:14  bkh
// imported EventTypeFilterProc sources
//
//

#include "Experiment/Experiment.h"

#include <iomanip.h>
#include <assert.h>
// system include files

// user include files
#include "EventTypeFilterProc/EventTypeFilterProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "BeamEnergy/BeamEnergy.h"
#include "EventProperties/EventProperties.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.EventTypeFilterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EventTypeFilterProc.cc,v 1.4 2001/11/01 18:08:01 bkh Exp $";
static const char* const kTagString = "$Name:  $";


//
// static data member definitions
//

const UInt32 EventTypeFilterProc::k_nTk=0, 
   EventTypeFilterProc::k_qNet=1, 
   EventTypeFilterProc::k_pTk1=2, 
   EventTypeFilterProc::k_pTk2=3, 
   EventTypeFilterProc::k_eTk1=4,
   EventTypeFilterProc::k_eTk2=5, 
   EventTypeFilterProc::k_eVis=6, 
   EventTypeFilterProc::k_eGam1=7, 
   EventTypeFilterProc::k_eCC=8, 
   EventTypeFilterProc::k_pPerp=9, 
   EventTypeFilterProc::k_eSh1=10, 
   EventTypeFilterProc::k_eSh2=11,
   EventTypeFilterProc::k_eSh3=12,
   EventTypeFilterProc::k_eOverP1=13,
   EventTypeFilterProc::k_eOverP2=14,
   EventTypeFilterProc::k_acop=15,
   EventTypeFilterProc::k_acosth=16,
   EventTypeFilterProc::k_sinthm=17,
   EventTypeFilterProc::k_eChg=18,
   EventTypeFilterProc::k_eNeu=19 ;

const string EventTypeFilterProc::k_varNames[] =
{ "nTk"   , "qNet"  , "pTk1"  , "pTk2"  , "eTk1"  , "eTk2"  , "eVis"  ,
  "eGam1" , "eCC"   , "pPerp" , "eSh1"  , "eSh2"  , "eSh3"  , "eOverP1" ,
  "eOverP2","acop"  , "acosth", "sinThm", "eChg"  , "eNeu" } ;

const UInt32 EventTypeFilterProc::k_nBins[] =
{ 16, 21, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 12, 12,
  40, 20, 20, 120, 120 } ;

const float EventTypeFilterProc::k_loEdge[] =
{ -0.5, -10.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, .9, 0, 0, 0 } ;

const float EventTypeFilterProc::k_hiEdge[] =
{ 15.5, 10.5, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2,
  1.2, 1.2, 1.2, 0.2, 1, 1, 1.2, 1.2 } ;

//
// constructors and destructor
//
EventTypeFilterProc::EventTypeFilterProc( void )               // anal1
   : Processor( "EventTypeFilterProc" ) ,
     m_exclusive ( EventType::k_nFlags , (UInt32) 0 ) ,
     m_total ( 0 ) ,
     m_keep  ( 0 ) ,
     m_ask   ( false )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &EventTypeFilterProc::event,    Stream::kEvent );
   //bind( &EventTypeFilterProc::beginRun, Stream::kBeginRun );
   //bind( &EventTypeFilterProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   const PairInts dumPair ( 0, 0 ) ;
   PairList dumList ( EventType::k_nFlags , dumPair ) ;
   for( UInt16 i ( 0 ) ; i != EventType::k_nFlags ; ++i )
   {
      dumList[ i ] = PairInts( i, 0 ) ;
   }
   Matrix tmp ( EventType::k_nFlags, dumList ) ;
   m_matrix = tmp ;



   for( UInt32 j ( 0 ) ; j != EventType::k_nFlags ; ++j )
   {
      const string& name ( EventType::k_names[j] ) ;
      m_commands.push_back( new Parameter< DABoolean > 
			    ( string( name,0,
				      name.find_last_not_of(" ")+1 ),
			      this, false ) ) ;
      m_commands.back()->setHelpString( 
	 "Keep events classified by EventType as " + EventType::k_names[j] ) ;
   }

}

EventTypeFilterProc::~EventTypeFilterProc()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   for( STL_VECTOR( Parameter< DABoolean >* )::const_iterator iP 
	   ( m_commands.begin() ); iP != m_commands.end() ; ++iP )
   {
      delete *iP ;
   }
}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
EventTypeFilterProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)


   for( STL_VECTOR( Parameter< DABoolean >* )::const_iterator iP1 
	   ( m_commands.begin() ); iP1 != m_commands.end() ; ++iP1 )
   {
      if( (*iP1)->value() )
      {
	 m_ask = true ;
      }
   }

   if( ! m_ask )
   {
      report( INFO, kFacilityString ) 
	 << " No selection made: passing all events:\n\n" ;
   }
   else
   {
      report( INFO, kFacilityString ) 
	 << " Only passing following events:\n\n" ;

      for( STL_VECTOR( Parameter< DABoolean >* )::const_iterator iP 
	      ( m_commands.begin() ); iP != m_commands.end() ; ++iP )
      {
	 if( (*iP)->value() )
	 {
	    const UInt32 j ( iP-m_commands.begin() ) ;
	    report( INFO, kFacilityString ) << "        " 
					    << EventType::k_names[j] << "\n";
	 }
      }
   }
   report( INFO, kFacilityString )  << "\n" << endl ;
}

// -------------------- terminate method ----------------------------
void
EventTypeFilterProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   summary() ;
 
}

// ---------------- standard place to book histograms ---------------
void
EventTypeFilterProc::hist_book( HIHistoManager& aMgr )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   UInt32 iH ( 0 ) ;
   for( UInt32 i ( 0 ) ; i != EventType::k_nFlags ; ++i )
   {
      const string& name ( EventType::k_names[i] ) ;
      if( name[0] != '-' )
      {
	 const string& tName ( string( name,0,
				       name.find_last_not_of(" ")+1 ) ) ;
	 for( UInt32 j ( 0 ) ; j != k_nHist ; ++j )
	 {
	    const string& vName ( k_varNames[j] ) ;
	    m_hst[i][j] = aMgr.histogram( 100*i+j+1, tName+": "+vName ,
					  k_nBins[j]  ,
					  k_loEdge[j] ,
					  k_hiEdge[j]    ) ;
	 }
      }
   }
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
EventTypeFilterProc::event( Frame& aFrame )
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< BeamEnergy >                          cesr   ;
   extract( aFrame.record( Stream::kStartRun ) , cesr ) ;
   const double eBeam                          ( cesr->value() ) ;

   FAItem< EventProperties >                             props   ; 
   extract(  aFrame.record( Stream::kEvent )   ,         props ) ; 

   const double eCM   ( 2*eBeam )       ;

   const double eNeu ( props->neutralEnergy()/eCM ) ;
   const double eChg ( props->chargedEnergy()/eCM ) ;
   const double eVis ( eNeu + eChg ) ;
   const double eSh1 ( props->firstLargestEShower() /eBeam ) ;
   const double eSh2 ( props->secondLargestEShower()/eBeam ) ;
   const double eSh3 ( props->thirdLargestEShower() /eBeam ) ;

   const double arVtx ( 0 ) ;  // later fill with event vertex ABSOLUTE VALS
   const double azVtx ( 0 ) ;

   const DABoolean goodVertex ( arVtx < 0.02   &&
				azVtx < 0.075      ) ;

   const UInt32 nTk        ( props->nbChargedTracks() ) ;
   const double eCC        ( props->ccTotalEnergy()/eCM   ) ;
   const double pPerp      ( props->totalMomentumVect().perp()/eCM ) ;
   const double pNet       ( props->totalMomentumVect().mag()/eCM ) ;
   const double aCosTh     ( pNet > 0 ? 
			     fabs( props->totalMomentumVect().cosTheta() ) :
			     0 ) ;
   const DABoolean endShow ( props->showerInEndcap() ) ;
   const DABoolean barShow ( props->showerInBarrel() ) ;
   const DABoolean endBtoB ( props->backToBackECShower() ) ;
   const double    acop    ( props->acoplanarity() ) ;
   const double    pTk1    ( props->firstLargestPTrack() /eBeam ) ;
   const double    pTk2    ( props->secondLargestPTrack()/eBeam ) ;
   const double    eTk1    ( props->firstMatchedEnergy() /eBeam ) ;
   const double    eTk2    ( props->secondMatchedEnergy()/eBeam ) ;
   const double    eOverP1 ( pTk1 > 0 ? eTk1/pTk1 : 0  ) ;
   const double    eOverP2 ( pTk2 > 0 ? eTk2/pTk2 : 0  ) ;
   const Int32     qNet    ( props->netCharge() ) ;
   const Int32     aqNet   ( abs( qNet ) ) ;
   const double    eGam1   ( props->highestIsolatedShowerEnergy()/eBeam ) ;
   const DABoolean loneTk  ( props->isolatedTrack() ) ;

   const double    sinthm  ( eVis < 1 ? pPerp/(1-eVis) : 1 ) ;

   static float var[ k_nHist ] ;

   var[ k_nTk   ] = nTk   ;
   var[ k_qNet  ] = qNet  ;
   var[ k_pTk1  ] = pTk1  ;
   var[ k_pTk2  ] = pTk2  ;
   var[ k_eTk1  ] = eTk1  ;
   var[ k_eTk2  ] = eTk2  ;
   var[ k_eVis  ] = eVis  ;
   var[ k_eGam1 ] = eGam1 ;
   var[ k_eCC   ] = eCC   ;
   var[ k_pPerp ] = pPerp ;
   var[ k_eSh1  ] = eSh1  ;
   var[ k_eSh2  ] = eSh2  ;
   var[ k_eSh3  ] = eSh3  ;
   var[ k_eOverP1]= eOverP1  ;
   var[ k_eOverP2]= eOverP2  ;
   var[ k_acop  ] = acop  ;
   var[ k_acosth] = aCosTh  ;
   var[ k_sinthm] = sinthm  ;
   var[ k_eChg  ] = eChg ;
   var[ k_eNeu  ] = eNeu ;

   DABoolean keep ( false ) ;

   ++m_total ;

   STL_VECTOR( Parameter< DABoolean >* )::const_iterator myEnd 
      ( m_commands.end() ) ;
   STL_VECTOR( Parameter< DABoolean >* )::const_iterator myBeg 
      ( m_commands.begin() ) ;

   FAItem< EventType >                        evType   ;
   extract( aFrame.record( Stream::kEvent ) , evType ) ;

   for( UInt16 i ( 0 ) ; i != EventType::k_nFlags ; ++i )
   {
      if( evType->flags( i ) )
      {
	 STL_VECTOR( Parameter< DABoolean >* )::const_iterator iP ( myBeg );
	 while( m_ask && !keep && iP != myEnd )
	 {
	    keep = (*iP)->value() && ( i == iP-myBeg ) ;
	    ++iP ;
	 }
	 if( evType->only( i ) )
	 {
	    ++m_exclusive[i] ;
	 }
	 for( UInt16 j ( 0 ) ; j != EventType::k_nFlags ; ++j )
	 {
	    if( evType->flags( j ) )
	    {
	       ++m_matrix[i][j].second ;
	    }
	 }

//---------------------------------------------- histograms

	 {
	    for( UInt32 j ( 0 ) ; j != k_nHist ; ++j )
	    {
	       if( m_hst[i][j] != 0 )
	       {
		  m_hst[i][j]->fill( var[j] ) ;
	       }
	    }
	 }

//----------------------------------------------

      }
   }

   if( !m_ask || keep ) 
   {
      ++m_keep ;
   }

   return ( (!m_ask) || keep ? ActionBase::kPassed : ActionBase::kFailed ) ;
}

/*
ActionBase::ActionResult
EventTypeFilterProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
EventTypeFilterProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

void
EventTypeFilterProc::summary() const
{
   report( DEBUG, kFacilityString ) << "here in summary()" << endl ;

   report( INFO, kFacilityString )
      << "\n\n ****** Summary from EventTypeFilterProc "
      << "****"
      << " for " << setw(8) << m_total << " events ******\n" ;

   report( INFO, kFacilityString )
      << "\n    **** # passed EventTypeFilterProc filtering = "
      << setw(8) << m_keep << " events ******\n" ;

   if( m_total == 0 )
   {
      report( INFO, kFacilityString )
	 << "\n\n ------- Zero events processed ------- \n" ;
   }
   else
   {
      const float total ( float( m_total )/100. ) ;

      report( INFO, kFacilityString )
	 << "\n\n      Type           Excl   Incl      Overlap"
	 << " (in %, use Incl # as denom)\n"
	 <<     "      ----           ----   ----      -------" 
	 << "----------------------------\n" ;

      for( UInt16 i ( 0 ) ; i != EventType::k_nFlags ; ++i )
      {
	 if( EventType::k_names[i][0] != '-' )
	 {

	    PairList pairs ( m_matrix[i] ) ;

	    assert( pairs[i].first == i ) ;

	    const UInt32 incl ( pairs[i].second ) ;

	    const float  fincl ( float(incl)/100. ) ;

	    sort( pairs.begin(), pairs.end(), ComparePairs() ) ;

	    report( INFO, kFacilityString )
	       << "\nT" << setw(2) << setfill('0') << i << setfill(' ') 
	       << " " << EventType::k_names[i]
	       << setw(7) << m_exclusive[i] << setw(7) << incl 
	       << setw(4) << int(floor(incl/total+0.5)) << "%" ;

	    static const UInt32 maxCol ( 5 ) ;
	    UInt16 iCol ( 0 ) ;

	    PairList::const_iterator iPair ( pairs.begin() ) ;
	    while( iCol != maxCol && iPair != pairs.end() )
	    {
	       if( iPair->first != i && 
		   iPair->second > 0 &&
		   iPair->first != EventType::k_known )
	       {
		  report( INFO, kFacilityString )
		     << " T" << setw(2) << setfill('0') << iPair->first
		     << setfill(' ') << "="
		     << setw(3)
		     << int( floor(iPair->second/fincl +0.5) ) ;
		  ++iCol ;
	       }
	       ++iPair ;
	    }
	 }
      }
      report( INFO, kFacilityString ) << "\n\n" << endl ;      
   }
}

//
// const member functions
//

//
// static member functions
//
