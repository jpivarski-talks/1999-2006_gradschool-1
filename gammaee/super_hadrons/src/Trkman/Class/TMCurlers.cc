// -*- C++ -*-
//
// Package:     Trkman
// Module:      TMCurlers
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Wed Oct 23 19:57:26 EDT 2002
// $Id: TMCurlers.cc,v 1.1 2002/11/04 18:31:30 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlers.cc,v $
// Revision 1.1  2002/11/04 18:31:30  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"

// user include files
#include "Trkman/TMCurlers.h"
#include "Experiment/fortran_types.h"
#include "ToolBox/TBFortranArrays.h"

#include "TrackRoot/TRTrackFitQuality.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "Navigation/NavTrack.h"
#include "Cleo/cleo_math.h"

static const char* const kFacilityString = "Trkman.TMCurlers" ;

#define iout report( INFO, kFacilityString )


// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TMCurlers.cc,v 1.1 2002/11/04 18:31:30 nea9 Exp $";
static const char* const kTagString = "$Name:  $";

//
// constructors and destructor
//
TMCurlers::TMCurlers( NavTrackTable& theTracks, TMData*& data ) :
  m_theTracks( theTracks ),
  m_data( data ),
  m_numCurlerPairs(0),
  m_numCurlerGroups(0)
{
   //Reserve memory
//   m_curlerPairs.reserve( 100 );
//   m_curlerGroups.reserve( 25 );
//   m_pairMatched.reserve( 100 );
//   m_groupMerged.reserve( 25 );
//   m_grpPairList.reserve( 25 );
//   m_phiAvg.reserve( 25 );
//   m_circleTracks.reserve( 25 );
//   m_curlerCodes.reserve( 25 );      

   //Get num track pairs
   m_numTrkPairs = m_theTracks.size()*( m_theTracks.size() - 1 )*0.5;

   //Dynamic memory allocation
   m_dRadiusCImVec = new double[ m_numTrkPairs ];
   m_dT            = new double[ m_numTrkPairs ];

   //Make the curler pairs
   makeCurlerPairs();

   //If there are curler pairs, make groups
   //and if there is more than one group,
   //merge the groups
   if( m_numCurlerPairs > 0 )
   {
      makeCurlerGroups();
      computePhiAvg();

      if( m_numCurlerGroups > 1 )
      {
	 mergeGroups();
	 computePhiAvg();
      }
   }

   //If there is one or more groups classify
   //them according to the size and type
   //of the group.
   if( m_numCurlerGroups > 0 )
   {
      makeCurlerCircles();
      
      for( int i=0; i<m_numCurlerGroups; i++ )
      {
	 int numTracks = m_curlerGroups[i].size();
	 
	 if( numTracks == 2 )
	 {  
	    classifyTwoCurlerGroup( i );
	 }
	 else if( numTracks == 3 )
	 {
	       classifyThreeCurlerGroup( i );
	 }
	 else 
	 { 
	    classifyOtherCurlerGroup( i );
	 }
      }
   }
}

// TMCurlers::TMCurlers( const TMCurlers& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

TMCurlers::~TMCurlers()
{
   delete[] m_dRadiusCImVec;
   delete[] m_dT;

   m_curlerPairs.clear();
   m_curlerGroups.clear();
   m_cPairList.clear();
   m_pairMatched.clear();
   m_groupMerged.clear();
   m_phiAvg.clear();
   m_grpPairList.clear();
   m_curlerCodes.clear();

}

