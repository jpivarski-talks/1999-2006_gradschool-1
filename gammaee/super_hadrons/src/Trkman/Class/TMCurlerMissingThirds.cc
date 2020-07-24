// -*- C++ -*-
//
// Package:     <package>
// Module:      TMCurlerMissingThirds
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Thu Sep  5 10:38:17 EDT 2002
// $Id: TMCurlerMissingThirds.cc,v 1.1 2002/11/04 18:31:30 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlerMissingThirds.cc,v $
// Revision 1.1  2002/11/04 18:31:30  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "Trkman/TMCurlerMissingThirds.h"
#include "Navigation/NavTrack.h"
#include "MagField/MagneticField.h"


#define iout report( INFO, kFacilityString )
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Trkman.TMCurlerMissingThirds" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TMCurlerMissingThirds.cc,v 1.1 2002/11/04 18:31:30 nea9 Exp $";
static const char* const kTagString = "$Name:  $";

static const double kPi       = 3.1415926535898;


//
// constructors and destructor
//
TMCurlerMissingThirds::TMCurlerMissingThirds( NavTrackTable& theTracks, 
					      TMData*& data,
					      TMClassification::TrackClassification& trackClass,
					      TMCurlers*& curlers )
{
   m_theTracks = theTracks;
   m_curlers = curlers;
   m_curlerGroups = (*m_curlers).curlerGroupVector();

   findMissingThirds( trackClass, data );
}

TMCurlerMissingThirds::~TMCurlerMissingThirds()
{
   m_curlerGroups.clear();
}

//
// member functions
//
void TMCurlerMissingThirds::findMissingThirds( TMClassification::TrackClassification& trackClass,
					       TMData*& data)
{

   //Loop over all the surviving curler track 
   //combinations, not including any tracks killed
   //already.   
   for( int i=0; i<m_curlerGroups.size(); i++ )
   {

      //The cirle track for group i
      int circleTrack = (*m_curlers).circleTrack( i );

      if( trackClass[ circleTrack-1 ] == -201 )
      {

	 double circleCurv = data->curvature( circleTrack-1 );
	 double circlePhi = data->phi( circleTrack-1 );
	 double circleSign = circleCurv/fabs(circleCurv);

	 NavTrackTable::const_iterator trkIt = m_theTracks.begin();
	 for( ; trkIt != m_theTracks.end(); trkIt++ )
	 {
	    int track = (*trkIt).identifier();
	    
	    if( circleTrack != track )
	    {
	       if( trackClass[track-1] == 0 )
	       {
		  double trackCurv = data->curvature( track-1 );
		  double trackPhi = data->phi( track-1 );
		  
		  DABoolean sameSign = false;
		  if( circleCurv*trackCurv > 0 )
		  { 
		     sameSign = true;
		  }
		  
		  if( !sameSign )
		  {

		     double delPhi;
		     delPhi = fabs( trackPhi - circlePhi );
		     
		     if( delPhi > kPi )
		     {
			delPhi = 2*kPi - delPhi;
		     }
		     		     
		     double delR = fabs( data->rcImpact( circleTrack-1 ) 
					 - data->rcImpact( track-1 ) );
		

		     if( delPhi > 3.05 && delR < 0.05 && 
			 fabs( data->d0( track-1 ) ) < 0.002 )
		     {
			trackClass[ track-1 ] = -250;
		     }

		  }
	       }
	    }
	 }
      }
   }

}

//
// const member functions
//

//
// static member functions
//
