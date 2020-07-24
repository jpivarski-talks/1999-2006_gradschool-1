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
// Created:     Tue Sep 10 09:02:11 EDT 2002
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
static const char* const kFacilityString = "Trkman.TMTails" ;

void TMClassification::removeTails()
{
   //Loop over tracks
   NavTrackTable::const_iterator iIt = m_theTracks.begin();
   for( ; iIt != m_theTracks.end(); iIt++ )
   {
      int iTrack = (*iIt).identifier();
      if( m_trackClass[ iTrack-1 ] == 0 || 
	  m_trackClass[ iTrack-1 ] == -410 )
      {
	 double iCurv = m_data->curvature( iTrack-1 );
	 double iSignedDb = m_data->d0( iTrack-1 );
	 if( iCurv < 0 )
	 {
	    iSignedDb = -1*iSignedDb;
	 }
	 double iAbsDb = fabs( iSignedDb );
	 double iPhi = m_data->phi( iTrack-1 );

	 NavTrackTable::const_iterator jIt = iIt;
	 jIt++;
	 for( ; jIt != m_theTracks.end(); jIt++ )
	 {
	    int jTrack = (*jIt).identifier();
	    if( m_trackClass[ jTrack-1 ] == 0 || 
	        m_trackClass[ jTrack-1 ] == -410 )
	    {
	       double jCurv = m_data->curvature( jTrack-1 );
	       double jSignedDb = m_data->d0( jTrack-1 );
	       if( jCurv < 0 )
	       {
		  jSignedDb = -1*jSignedDb;
	       }
	       double jAbsDb = fabs( jSignedDb );
	       double jPhi = m_data->phi( jTrack-1 );

	       double delPhi = fabs( iPhi - jPhi );
	       if( delPhi > kPi )
	       {
		  delPhi = 2*kPi - delPhi;
	       }

	       DABoolean sameSign = false;
	       if( iCurv*jCurv > 0 )
	       {
		  sameSign = true;
	       }

	       int iPair = (*m_curlers).pairNumber( iTrack, 
						    jTrack, 
						    m_theTracks.size() );
	       
	       if( iAbsDb > 0.02 && jAbsDb > 0.02 &&
		   (*m_curlers).delTails( iPair ) < 0.02 &&
		   delPhi > 2.8 && !sameSign )
	       {
		  if( m_trackClass[ iTrack-1 ] == 0 )
		  {
		     m_trackClass[ iTrack-1 ] = -410;
		  }
		  if( m_trackClass[ jTrack-1 ] == 0 )
		  {
		     m_trackClass[ jTrack-1 ] = -410;
		  }
	       }

	    }
	 }
      }
   }

}



