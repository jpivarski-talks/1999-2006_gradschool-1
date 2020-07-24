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
// Created:     Tue Aug 27 15:18:01 EDT 2002
// $Id: TMClassification_BasicTrQual.cc,v 1.1 2002/11/04 18:31:28 nea9 Exp $
//
// Revision history
//
// $Log: TMClassification_BasicTrQual.cc,v $
// Revision 1.1  2002/11/04 18:31:28  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"
#include "Trkman/TMClassification.h"


//
// constants, enums and typedefs
//
static const double kPi       = 3.1415926535898;
static const char* const kFacilityString = "Trkman.TMBasicTrackQuality" ;

#define iout report( INFO, kFacilityString )


void TMClassification::removeBadTracks()
{

   //Loop over the tracks and check the distance from beam and 
   //density, if they haven't already been removed by curlers or vees
   //or extras.
   NavTrackTable::const_iterator trkIt = m_theTracks.begin();
   for( ; trkIt != m_theTracks.end(); trkIt++ )
   {
      int iTrack = (*trkIt).identifier();
      if( m_trackClass[iTrack-1] == 0 )
      {
	 //Get the density
	 double dens = m_data->densityOfHits( iTrack-1 );

	 //Get the initial distance of the track from the beam
	 double d0 = m_data->d0( iTrack-1 );

	 int reg = 0;
	 //Find what region the track lies in
	 if( reg == 0 )
	 {
	    if( dens > 0.65 )
	    {
	       if( fabs( d0 ) < 0.002 )
	       {
		  reg = 1;
	       }
	       else if( fabs(d0) >= 0.002 && fabs(d0) < 0.03 )
	       {
		  reg = 2;
	       }
	       else if( fabs(d0) > 0.03 )
	       {
		  reg = 3;
	       }
	    }
	 }

	 if( reg == 0 )
	 {
	    if( dens > 0.5 && dens <= 0.65 )
	    {
	       if( fabs( d0 ) < 0.002 )
	       {
		  reg = 4;
	       }
	       else if( fabs(d0) >= 0.002 && fabs(d0) < 0.03 )
	       {
		  reg = 5;
	       }
	       else if( fabs(d0) >= 0.03 )
	       {
		 if( dens <= 0.6 )
		   reg = 9;
		 else
		   reg = 6;
	       }
	    }
	 }

	 if( reg == 0 )
	 {
	    if( dens <= 0.5 )
	    {
	       if( fabs( d0 ) < 0.002 )
	       {
		  reg = 7;
	       }
	       else if( fabs(d0) >= 0.002 && fabs(d0) < 0.03 )
	       {
		  reg = 8;
	       }
	       else if( fabs(d0) >= 0.03 )
	       {
		  reg = 9;
	       }
	    }
	 }

	 if( (reg >= 7 && reg <= 9) )
	 //if( reg == 9 )
	 {
	    m_trackClass[ iTrack-1 ] = -401;
	 }
	 else if( m_data->hits( iTrack-1 ) < 2 )
	 {
	   m_trackClass[ iTrack-1 ] = -402;
	 }
	 else if( m_data->curvature( iTrack-1 ) == 0 )
	 {
	    m_trackClass[ iTrack-1 ] = -501;
	 }
      }
   }
}


