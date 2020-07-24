// -*- C++ -*-
//
// Package:     <package>
// Module:      TrkmanLatticeProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Mon Oct 21 14:36:20 EDT 2002
// $Id: TrkmanLatticeProxy.cc,v 1.1 2002/11/04 18:38:49 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanLatticeProxy.cc,v $
// Revision 1.1  2002/11/04 18:38:49  nea9
// New CleoIII Trkman
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "Trkman/TrkmanInfo.h"
#include "Trkman/TMClassification.h"
#include "TrkmanProd/TrkmanLatticeProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "TrkmanProd.TrkmanLatticeProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TrkmanLatticeProxy.cc,v 1.1 2002/11/04 18:38:49 nea9 Exp $";
static const char* const kTagString = "$Name:  $";

#define iout report( INFO, kFacilityString )
#define eout report( EMERGENCY, kFacilityString )
#define wout report( WARNING, kFacilityString )

//
// static data member definitions
//

//
// constructors and destructor
//
TrkmanLatticeProxy::TrkmanLatticeProxy()
   : m_TrkmanLattice( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &TrkmanLatticeProxy::boundMethod, Stream::kBeginRun );
}

// TrkmanLatticeProxy::TrkmanLatticeProxy( const TrkmanLatticeProxy& iproxy )
// {
//   *this = iproxy;
// }

TrkmanLatticeProxy::~TrkmanLatticeProxy()
{
   delete m_TrkmanLattice ;
}

//
// assignment operators
//
// const TrkmanLatticeProxy& TrkmanLatticeProxy::operator=( const TrkmanLatticeProxy& iproxy )
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
TrkmanLatticeProxy::invalidateCache()
{
   delete m_TrkmanLattice ;
   m_TrkmanLattice = 0 ;
}

//Fill the trackman Lattice
const TrkmanLatticeProxy::value_type*
TrkmanLatticeProxy::faultHandler( const Record& iRecord,
				  const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_TrkmanLattice );

   //if an exception is thrown during this function, p_TrkmanLattice will
   // automatically delete the object it is refering to
   auto_ptr<TrkmanLattice> p_TrkmanLattice;

   TrkmanLattice* lattice = new TrkmanLattice( TrkmanLattice::RNodeMulti,
					       TrkmanLattice::LNodeMulti,
					       TrkmanLattice::RLinkMulti );

   if( 0 == lattice )
   {
      eout << "Not enough memory to allocate TrkmanLattice!" << endl;
      assert(false);
      ::exit(1);
   }

   p_TrkmanLattice.reset( lattice );

   //Extract the track man info objects
   FATable< TrkmanInfo > trackInfoTable;
   extract( iRecord, trackInfoTable );

   FAItem< TMClassification > classifications;
   extract( iRecord, classifications );

   //Get the vectors of curlers and vees
   CurlerGroupVector curlerGroups = (*classifications).curlerGroupVector();
   VeeGroupVector veeGroups = (*classifications).veeGroupVector();

   //Put the curler groups in the lattice
   for( int cgroup = 0; cgroup<curlerGroups.size(); cgroup++ )
   {
      int goodTrack = 0;
      TrackVector badTrackList;

      int numTracks = curlerGroups[cgroup].size();
      for( int i=0; i<numTracks; i++ )
      {
	 int track = curlerGroups[cgroup][i];
	 
	 //Find the info object for this track
	 FATable< TrkmanInfo >::const_iterator infoIt = 
	    trackInfoTable.find( track );

	 int code = (*infoIt).classificationCode();
	 
	 if( code > 0 )
	 {
	    if( goodTrack != 0 )
	    {
	       wout << "Two good tracks found for group "
		    << cgroup+1 << ". Both " << goodTrack
		    << " and " << track << " are good!"
		    << endl;
	    }
	    goodTrack = track;
	 }
	 else
	 {
	    //Add the track to the list of bad tracks
	    badTrackList.push_back( track );
	 }

      }

      if( badTrackList.empty() )
      {
	 eout << "Didn't find any bad tracks for curler group "
	      << cgroup+1 <<endl;
	 
	 continue;
      }

      //If there is no good track in this group
      //make the first bad track the left most
      //track
      if( goodTrack == 0 )
      {
	 goodTrack = badTrackList[0];
	 badTrackList.erase(badTrackList.begin());
      }

      FATable< TrkmanInfo >::const_iterator infoIt = 
	 trackInfoTable.find( goodTrack );
      
      int groupCode = fabs( (*infoIt).classificationCode() );
      int groupId = (*infoIt).groupId();

      const TrkmanLink groupLink( groupId, groupCode, numTracks );

      TrkmanLattice::Link* realLink = lattice->connect( goodTrack,
							badTrackList[0],
							groupLink );

      if( 0 == realLink )
      {
	 eout << "Addition of link to trackman lattice failed!" << endl;
	 assert(false);
	 ::exit(1);
      }

      for( int bt=1; bt<badTrackList.size(); bt++ )
      {
	 lattice->connect( *realLink, badTrackList[bt] );
      }
      
      
   }


   //Put the vees in the lattice
   for( int vgroup = 0; vgroup<veeGroups.size(); vgroup++ )
   {
      int goodTrack = 0;
      TrackVector badTrackList;

      int numTracks = veeGroups[vgroup].size();
      for( int i=0; i<numTracks; i++ )
      {
	 int track = veeGroups[vgroup][i];
	 
	 //Find the info object for this track
	 FATable< TrkmanInfo >::const_iterator infoIt = 
	    trackInfoTable.find( track );

	 int code = (*infoIt).classificationCode();
	 
	 if( code > 0 )
	 {
	    if( goodTrack != 0 )
	    {
	       wout << "Two good tracks found for group "
		    << vgroup+curlerGroups.size()+1 << ". Both " << goodTrack
		    << " and " << track << " are good!"
		    << endl;
	    }
	    goodTrack = track;
	 }
	 else
	 {
	    badTrackList.push_back( track );
	 }

      }

      if( badTrackList.size() == 0 )
      {
	 eout << "Didn't find any bad tracks in vee pair "
	      << vgroup+curlerGroups.size()+1 <<endl;
	 
	 continue;
      }
      if( goodTrack == 0 )
      {
	 eout << "Didn't find a good track in the vee pair "
	      << vgroup+curlerGroups.size()+1 <<endl;
	 continue;
      }

      //If there is no good track in this group
      //make the first bad track the left most
      //track

      FATable< TrkmanInfo >::const_iterator infoIt = 
	 trackInfoTable.find( goodTrack );
      
      int groupCode = fabs( (*infoIt).classificationCode() );
      int groupId = (*infoIt).groupId();

      const TrkmanLink groupLink( groupId, groupCode, numTracks );

      TrkmanLattice::Link* realLink = lattice->connect( goodTrack,
							badTrackList[0],
							groupLink );

      if( 0 == realLink )
      {
	 eout << "Addition of link to trackman lattice failed!" << endl;
	 assert(false);
	 ::exit(1);
      }

      for( int bt=1; bt<badTrackList.size(); bt++ )
      {
	 lattice->connect( *realLink, badTrackList[bt] );
      }


   }

   //Clear memory
   curlerGroups.clear();
   veeGroups.clear();
   

   //Since no exception happened, tell p_TrkmanLattice to give its pointer to
   // m_TrkmanLattice
   return ( m_TrkmanLattice = p_TrkmanLattice.release() ) ;
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//


//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< TrkmanLattice >;

PROXY_BIND_METHOD( TrkmanLatticeProxy )
//-----------------------------------------------

