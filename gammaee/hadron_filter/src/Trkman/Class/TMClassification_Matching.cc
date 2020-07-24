// -*- C++ -*-
//
// Package:     Trkman
// Module:      TMClassification
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Mon Oct 21 09:26:52 EDT 2002
// $Id$
//
// Revision history
//
// $Log$

#include "Experiment/Experiment.h"
#include "Trkman/TMClassification.h"


//
// constants, enums and typedefs
//
static const double kPi = 3.1415926535898;
static const char* const kFacilityString = "Trkman.TMTrackShowerMatching" ;

#define iout report( INFO, kFacilityString )
#define wout report( WARNING, kFacilityString )


//Decides which tracks if any should not be matched to showers.
void TMClassification::matchTracksToShowers()
{
   //Loop over tracks
   NavTrackConstIt trkIt = m_theTracks.begin();
   for( ; trkIt != m_theTracks.end(); trkIt++ )
   {
      int track = (*trkIt).identifier();
      
      //Set default value to true
      m_matched[ track-1 ] = true;

      FAItem< TRTrackFitQuality > nQ = (*trkIt).pionQuality();
      if( !(nQ->fit() && !nQ->fitAbort()) ) continue;
      
      //If this track is a curler or a vee parent we 
      //don't want to use it for matching.
      int iTC = m_trackClass[ track-1 ]/100;

      if( m_trackClass[ track-1 ] == 301 )
      {
	 m_matched[ track-1 ] = false;
	 continue;
      }
      if( m_trackClass[ track-1 ] == -302 )
      {
	 m_matched[ track-1 ] = false;
	 continue;
      }
      if( fabs( iTC ) == 2 )
      {
	 m_matched[ track-1 ] = false;
	 continue;
      }

      int minLayer = (*m_data).minLayer( track-1 );

      //Get the number of hits in the last 5, 10
      //and 20 layers. Get the density in the last 
      //20 layers.
      int min;
      int max = (*m_data).maxLayer( track-1 );

      int lFiveHits = 0;
      min =  max - 4;
      if( min < minLayer ) min = minLayer;
      for( int i=min; i<=max; i++ )
      {
	 if( (*m_data).isLayerHit( track-1, i ) ) lFiveHits++;
      }

      int lTenHits = 0;
      min =  max - 9;
      if( min < minLayer ) min = minLayer;
      for( int j=min; j<=max; j++ )
      {
	 if( (*m_data).isLayerHit( track-1, j ) ) lTenHits++;
      }

      int lTwentyHits = 0;
      min =  max - 19;
      if( min < minLayer ) min = minLayer;
      for( int k=min; k<=max; k++ )
      {
	 if( (*m_data).isLayerHit( track-1, k ) ) lTwentyHits++;
      }

      //Density in the last twenty layers
      double densTwenty;
      if( (max - min) != 0 ) 
      {
	 densTwenty = (double)lTwentyHits/(double)(max - min);
      }
      else densTwenty = -1;


      //Cosine Theta
      double zAngle = 0;
      if( (*m_data).cotTheta( track-1 ) != 0 )
	 zAngle = atan( 1/(*m_data).cotTheta( track-1 ) );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta = cos( zAngle );


      if( m_trackClass[ track-1 ] == 0  || 
	  m_trackClass[ track-1 ] == 302 )
      {
	 if( lTwentyHits < 5 )
	 {
	    
	    //Exempt the poles from scrutiny
	    if( cosTheta < 0.8 )
	    {
	       FAItem< TRTrackFitQuality > piTQ = (*trkIt).pionQuality();
	       FAItem< TDKinematicFit > piFit;
	       //if( jpiTQ->fit() && !jpiTQ->fitAbort() )
	       if( !piTQ->fitAbort() )
	       {
		  piFit = (*trkIt).pionFit();
		  double p = piFit->pmag();

		  if( p > 0.25 )
		  {
		     if( densTwenty < 0.25 )
		     {
			m_matched[ track-1 ] = false;
		     }
		  }
		  else 
		  {
		     if( densTwenty < 0.3 )
		     {
			m_matched[ track-1 ] = false;
		     }
		  }
	       }
	       else
	       {
		  if( densTwenty < 0.25 )
		  {
		     m_matched[ track-1 ] = false;
		  }
	       }
	       
	       //Get the momentum of the track
	    }
	 }
      }
      else if( fabs( iTC ) == 4 )
      {
	 if( lTwentyHits < 5 && (*m_data).densityOfHits( track-1 ) < 0.3 )
	 {
	    m_matched[ track-1 ] = false;
	 }
	 if( (*m_data).rcImpact( track-1 ) < 0.82 &&
	     cosTheta > 0.8 && (*m_data).densityOfHits( track-1 ) < 0.5 )
	 {
	    m_matched[ track-1 ] = false;	    
	 }
      }

      //Explcitly use backsplash for matching
      double sign = 1.0;
      if( (*m_data).curvature( track-1 ) < 0 ) sign = -1.0;

      double sD0 = sign*(*m_data).d0( track-1 ); 
      if( sD0 > 0.3 && (*m_data).rcImpact( track-1 )>1.0 &&
	  lTenHits > 7 )
      {
	 m_matched[ track-1 ] = true;
      }

   }

}






