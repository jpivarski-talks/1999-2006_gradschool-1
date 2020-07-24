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
// Created:     Mon Feb 18 14:15:25 EST 2002
// $Id: TMCurlers_Circles.cc,v 1.1 2002/11/04 18:31:31 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlers_Circles.cc,v $
// Revision 1.1  2002/11/04 18:31:31  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"
#include "Trkman/TMCurlers.h"

//
// constants, enums and typedefs
//
static const double kPi = 3.1415926535898;
static const char* const kFacilityString = "Trkman.TMCurlerCircles" ;

#define iout report( INFO, kFacilityString )
//
// member functions
//
void TMCurlers::makeCurlerCircles()
{
   CircleVector candTrack;
   candTrack.reserve( m_numCurlerGroups );
 
   //Loop over all possible track pairings of tracks in
   //the group and find pairs with small differences in 
   //radius.
   for( int i=0; i<m_numCurlerGroups; i++ )
   {
      CurlerGroup cg = m_curlerGroups[i];
      int numTracks = cg.size();
      for( int j=0; j<numTracks-1; j++ )
      {
	 int trk1 = cg[j];
	 for( int k=j+1; k<numTracks; k++ )
	 {
	    DABoolean trk1New;
	    DABoolean trk2New;
	    int trk2 = cg[k];
	    int ipair = -1;
	    if( trk1 < trk2 )
	    {
	       ipair = pairNumber( trk1, trk2, m_theTracks.size() );
	    }
	    else if( trk2 < trk1 )
	    {
	       ipair = pairNumber( trk2, trk1, m_theTracks.size() );
	    }
	    else
	    {
	       report( WARNING, kFacilityString ) << "Track " << trk1 << " is in group "
						  << i << " twice!!" << endl;
	    }

	    if( (ipair != -1) && (delRadiusCDAVec( ipair ) < (m_data->dRCCut()-0.04) ) )
	    {
	       double sign = m_data->curvature(trk1-1)*m_data->curvature(trk2-1);
	       if( sign < 0 )
	       {
		  trk1New = true;
		  trk2New = true;
		  //Have these tracks already been listed as circle candidates?
		  for( int n=0; n<candTrack.size(); n++ ) 
		  {
		     if( candTrack[n] == trk1 ) trk1New = false;
		     if( candTrack[n] == trk2 ) trk2New = false;
		  }
		  
		  if( trk1New ) candTrack.push_back( trk1 );
		  if( trk2New ) candTrack.push_back( trk2 );
	       }
	    }

	 }
      }
      //End of loop over track pairs

      
      //If there are track candidates to define the circle look through them
      //for the track with acceptable hit density that has endpoint with the
      //greatest distance from the interaction region.
      double radiusEndMax = 0;
      double densityCut = 0.6;
      int track = -1;
      if( candTrack.size() != 0 )
      {
	 for( int j=0; j<candTrack.size(); j++ )
	 {
	    int densTrack = candTrack[j];
	    if( m_data->densityOfHits( densTrack-1 ) > densityCut )
	    {
	       if( m_data->radiusEnd( densTrack - 1 ) > radiusEndMax )
	       {
		  track = densTrack;
		  radiusEndMax = m_data->radiusEnd( track-1 );
	       }
	    }
	 }
	 //If no track candidate was found choose the one with the greatest
	 //density of hits
	 if( track == -1)
	 {
	    int maxHits = 0;
	    for( int k=0; k<candTrack.size(); k++ )
	    {
	       int hitsTrack = candTrack[k];
	       if( m_data->hits( hitsTrack - 1 ) > maxHits )
	       {
		  track = hitsTrack;
		  maxHits = m_data->hits( track-1 );
	       }
	    }
	 }
	 if( track == -1 ) 
	 {
	    report( WARNING, kFacilityString ) << "No track was picked for the circle"
					    << " even though there were candidates!!" << endl;
	 }
	 m_circleTracks.push_back( track );
	 
	 //A track has been chosen to define the circle BUT the best defining
	 //track may not have a matching inward going curler to make it one of 
	 //the candidates. Look through the non-candidate tracks for a track with
	 //a larger endRadius()
	 for( int n=0; n<cg.size(); n++ )
	 {
	    int trk = cg[n];
	    DABoolean trackNotCand = true;
	    for( int m=0; m<candTrack.size(); m++ )
	    {
	       if( trk == candTrack[m] )
	       {
		  trackNotCand = false;
		  m=candTrack.size();
	       } 
	    }
	    if( trackNotCand )
	    {
	       int cTrk = m_circleTracks[i];
	       if( m_data->radiusEnd( trk-1 ) > m_data->radiusEnd( cTrk-1 ) )
	       {
		  if( m_data->densityOfHits( trk-1 ) > densityCut )
		  {
		     m_circleTracks[i] = trk;
		  }
	       }   
	    }	    
	 }
      }
      //If there were no candidate tracks then take the track of furthest extent which has a 
      //good DR Hit density
      else
      {
	 DABoolean ctChosen = false;
	 for( int l=0; l<cg.size(); l++ )
	 {
	    int track = cg[l];
	    if( m_data->densityOfHits( track-1 ) > densityCut )
	    {
	       if( m_data->radiusEnd( track-1 ) > radiusEndMax )
	       {
		  if( !ctChosen )
		  {
		     m_circleTracks.push_back( track );
		     ctChosen = true;
		  }
	       }
	    }
	 }
	 //If there is STILL no track ... be very unfussy ...
	 if( m_circleTracks.size() < i+1 )
	 {
	    for( int m=0; m<cg.size(); m++ )
	    {
	       int track = cg[m];
	       if( m_data->radiusEnd( track-1 ) > radiusEndMax )
	       {
		  if( !ctChosen )
		  {
		     m_circleTracks.push_back( track );
		     ctChosen = true;
		  }
	       }
	    }
	 }
	 //If there is no track after this make no requirement
	 if( m_circleTracks.size() < i+1 ) m_circleTracks.push_back( cg[0] );
	 
      }

      //Now a track has been chosen, so calculate the difference between its
      //phi and the group average.
      if( m_circleTracks.size() == i+1 )
      {
	 
	 track = m_circleTracks[i];
	 if( (m_data-> phiEnd( track-1 ) < 0) && (phiAverage( i ) > 0) )
	 {
	    m_diffAngle = phiAverage( i ) - m_data->phiEnd( track-1 );
	    if( m_diffAngle > kPi ) m_diffAngle = 2*kPi - m_diffAngle;
	 }
	 else if( (m_data-> phiEnd( track-1 ) > 0) && (phiAverage( i ) < 0) )
	 {
	    m_diffAngle = m_data->phiEnd( track-1 ) - phiAverage( i );
	    if( m_diffAngle > kPi ) m_diffAngle = 2*kPi - m_diffAngle;
	 }
	 else
	 {
	    m_diffAngle = fabs( m_data->phiEnd( track-1 ) - phiAverage( i ) );
	    
	 }
      }
      else
      {
	 //Something has gone terribly wrong, we should never be in here
	 report( WARNING, kFacilityString ) << "Could not find a circle track for group " << i << endl;
      }

      //Clear the candidate tracks
      candTrack.clear();
      cg.clear();
   }
   candTrack.clear();

}

//Function to set the cicle track, since this will be done more accurately
//if possible in the classification class
void TMCurlers::setCircleTrack( int i, int track )
{
   if( i >= 0 && i<m_numCurlerGroups )
   {
      m_circleTracks[i] = track;
   }
   else
   {
      report( WARNING, kFacilityString ) << "Could not set circle track for group " << i << endl;
   }
   
}


//
// const member functions
//
int TMCurlers::circleTrack( int i ) const
{
   if( i >= 0 && i<m_numCurlerGroups )
   {
      return m_circleTracks[i];
   }
   else
   {
      report( WARNING, kFacilityString ) << "Could not get circle track for group " << i << endl;
      return 0;
   }
}
//
// static member functions
//










