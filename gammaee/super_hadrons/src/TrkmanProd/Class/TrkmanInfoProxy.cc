// -*- C++ -*-
//
// File:    TrkmanInfoProxy.cc
// Package: TrkmanInfo
// Module:  TrkmanProd
// 
// Description: Proxy to provide (empty) TrkmanInfo to Frame
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Tue Jan 15 14:06:46 EST 2002
// $Id: TrkmanInfoProxy.cc,v 1.2 2002/11/04 18:38:48 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanInfoProxy.cc,v $
// Revision 1.2  2002/11/04 18:38:48  nea9
// New CleoIII Trkman
//
// Revision 1.1.1.1  2002/01/28 13:57:19  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES
#include <iostream>
#include <iomanip.h>
#include <stdlib.h>   // for ::exit
#include <assert.h>

// STL
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// USER INCLUDE FILES
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"
#include "FrameAccess/FAAutoEraseAllPtr.h"

#include "TrkmanProd/TrkmanInfoProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD
#include "Trkman/TMCurlers.h"
#include "Trkman/TMClassification.h"
#include "Trkman/TMData.h"

#include "Navigation/NavTrack.h" 

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCDecayTree/MCVertex.h"

// STL (again)
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// DEFINITIONS/MACROS
// Dumb shorthand for report
#define dout report(DEBUG, kFacilityString)
#define iout report(INFO, kFacilityString)
#define wout report(WARNING, kFacilityString)
#define eout report(EMERGENCY, kFacilityString)

//
// LOCAL FUNCTION PROTOTYPES
//

//
// CONSTANTS, ENUMS AND TYPEDEFS
//

static const char* const kFacilityString = "TrkmanProd.TrkmanInfoProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const
kIdString  = "$Id: TrkmanInfoProxy.cc,v 1.2 2002/11/04 18:38:48 nea9 Exp $";

static const char* const
kTagString = "$Name:  $";

typedef FATable< NavTrack > NavTrackTable;
typedef FAItem<  NavTrack > NavTrackItem;
typedef FATable< NavTrack >::const_iterator NavTrackConstIt;

//
// STATIC DATA MEMBER DEFINITIONS
//

//
// CONSTRUCTORS AND DESTRUCTOR
//

/* ======================================================================== */
TrkmanInfoProxy::TrkmanInfoProxy()
  : m_ptrTable( new value_type )
{
  
  //bind 'auxilliary' functions that you want called when a
  // new Record on the particular Stream appears
  //bind( &TrkmanInfoProxy::boundMethod, Stream::kBeginRun );
}
/* ======================================================================== */

/* ======================================================================== */
// TrkmanInfoProxy::TrkmanInfoProxy( const TrkmanInfoProxy& iproxy )
// {
//   *this = iproxy;
// }
/* ======================================================================== */

/* ======================================================================== */
TrkmanInfoProxy::~TrkmanInfoProxy()
{
  m_trkminfos.clear();
  
  // calls "eraseAll" internally!
  delete m_ptrTable;
}
/* ======================================================================== */

//
// ASSIGNMENT OPERATORS
//

/* ======================================================================== */
// const TrkmanInfoProxy& TrkmanInfoProxy::operator=( const TrkmanInfoProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }
/* ======================================================================== */

//
// MEMBER FUNCTIONS
//

/* ======================================================================== */
void
TrkmanInfoProxy::invalidateCache()
{
  if ( 0 != m_ptrTable ) {
    (*m_ptrTable).eraseAll();
  }
}
/* ======================================================================== */

/* ======================================================================== */
const TrkmanInfoProxy::value_type*
TrkmanInfoProxy::faultHandler( const Record& iRecord,
                               const DataKey& iKey )
{
   // Be assertive: table should be empty 
   // Else it's a programming error
   assert( 0 == (*m_ptrTable).size() );
  
   // If an exception is thrown in this routine, m_ptrTable will be
   //   automatically emptied (which is the proper behavior).
   // Use ptrTable just like you would use m_ptrTable
   FAAutoEraseAllPtr<TrkmanInfo> ptrTable( m_ptrTable );
  
   // Make sure we have no stale info/lists lying around
   m_trkminfos.clear();
   
   // **********************************************************************
   // Extract NavTracks from Frame
   // **********************************************************************
   NavTrackTable tracks;
   extract(iRecord, tracks);

//    // **********************************************************************
//    // Extract the decayTree for the event Vertex 
//    // **********************************************************************
//    FAItem< MCDecayTree > decayTree;
//    extract( iRecord, decayTree );
   
//    //Init the data
//    TMData* myData = new TMData( tracks, decayTree );

//    //Get the classifications for each track from Trkman
//    TMClassification* classifications = 
//       new TMClassification( tracks, myData );

   FAItem< TMClassification > classifications;
   extract( iRecord, classifications );

   TMClassification::TrackClassification trackCodes = 
      classifications->trackClassifications();

   DABoolean* trackUse = new DABoolean[ tracks.size() ];
   for( int j=0; j<tracks.size(); j++ )
   {
      trackUse[j] = classifications->useTrack( j );
   }
   CurlerGroupVector curlerGroups = classifications->curlerGroupVector();
   VeeGroupVector veeGroups = classifications->veeGroupVector();

   // **********************************************************************
   // Create TrkmanInfo object for each NavTrack
   // **********************************************************************
   //Curlers
   int groupId = 1;
   for( int i=0; i<curlerGroups.size(); i++ )
   {
      for( int j=0; j<curlerGroups[i].size(); j++ )
      {
	 int trkId = curlerGroups[i][j];
	 TrkmanInfo* trkinfo = new TrkmanInfo(trkId, trackCodes[trkId-1],
					      trackUse[ trkId-1 ], groupId );
	 m_trkminfos.push_back(trkinfo);
      }
      groupId++;
   }

   //Vees
   for( int k=0; k<veeGroups.size(); k++ )
   {
      for( int j=0; j<veeGroups[k].size(); j++ )
      {
	 int trkId = veeGroups[k][j];
	 TrkmanInfo* trkinfo = new TrkmanInfo(trkId, trackCodes[trkId-1],
					      trackUse[ trkId-1 ], groupId );
	 m_trkminfos.push_back(trkinfo);
      }
      groupId++;
   }

   //Rest of the Tracks
   NavTrackConstIt   trackEnd = tracks.end();
   for (NavTrackConstIt track = tracks.begin();
	track != trackEnd; ++track)
   {
      int trkId = track->identifier();
      //If this is a curler or vee its already been done
      //so quit.
      int code = trackCodes[ trkId-1 ];
      int type = fabs( trackCodes[ trkId-1 ]/100 );
      if( (type == 2 || type == 3) && code != -250 ) continue;

      // Make a TrkmanInfo object for this track,
      TrkmanInfo* trkinfo = new TrkmanInfo(trkId, trackCodes[trkId-1],
					   trackUse[ trkId-1 ], 0 );

      // Add this track to our temporary list of TrkmanInfo objects
      // These will soon get inserted into the FATable we're supposed
      //   to be filling
      m_trkminfos.push_back(trkinfo);
   }

   // **********************************************************************
   // Put finished TrkmanInfo objects into the FATable
   // **********************************************************************
   // This surrenders memory management!
   for (int n = 0; n < m_trkminfos.size(); ++n)
   {
      (*m_ptrTable).insert(m_trkminfos[n]);
   }

   //Clear all memory before exiting
   trackCodes.clear();
   curlerGroups.clear();
   veeGroups.clear();
   delete[] trackUse;

   // The release returns m_ptrTable and stops ptrTable from erasing the 
   //   contents of m_ptrTable.
   return ptrTable.release();
}
/* ======================================================================== */

//
// CONST MEMBER FUNCTIONS
//

//
// STATIC MEMBER FUNCTIONS
//

//
// 'BOUND' FUNCTIONS
//

/* ======================================================================== */
//void
//TrkmanInfoProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}
/* ======================================================================== */

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< TrkmanInfo > >;

PROXY_BIND_METHOD( TrkmanInfoProxy )
//-----------------------------------------------
