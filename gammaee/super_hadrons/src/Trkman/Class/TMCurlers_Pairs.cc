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
// Created:     Mon Dec 17 15:58:44 EST 2001
// $Id: TMCurlers_Pairs.cc,v 1.1 2002/11/04 18:31:32 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlers_Pairs.cc,v $
// Revision 1.1  2002/11/04 18:31:32  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"

// user include files
#include "Experiment/report.h"
#include "Trkman/TMCurlers.h"
#include "Navigation/NavTrack.h"
#include "Cleo/cleo_math.h"

//
// constants, enums and typedefs
//
static const double kPi = 3.1415926535898;
static const double kBFieldConstant = -0.0149896229;

static const char* const kFacilityString = "Trkman.TMCurlerPairs" ;

#define iout report( INFO, kFacilityString )

//Function called by the constructor to make the list of pairs.
void TMCurlers::makeCurlerPairs()
{
   DABoolean thisIsCPair = false;
   double dPhi;
   double dbMax, z0Max;
   int sign, iPair, i, j;
   UInt16 iT, jT;

   //Loop through the tracks in the event
   NavTrackConstIt iTrack;
   NavTrackConstIt jTrack;
   for( iTrack = m_theTracks.begin(); iTrack != m_theTracks.end(); iTrack++ )
   {
      i = iTrack->identifier()-1;
      jTrack = iTrack;
      jTrack++;
      for( ; jTrack != m_theTracks.end(); jTrack++ )
      {
	 thisIsCPair = false;
	 j = jTrack->identifier()-1;

	 iPair = pairNumber( i+1, j+1, m_theTracks.size() ); 
	 double iPhi = m_data->phi( i );
	 double jPhi = m_data->phi( j );

	 dPhi = fabs( iPhi - jPhi );
	 if( dPhi > kPi ) dPhi = 2*kPi - dPhi;

	 HepPoint3D iPos =      iTrack->seedTrack()->position();
	 double iCurv         = m_data->curvature( i );
	 HepPoint3D jPos =      jTrack->seedTrack()->position();
	 double jCurv         = m_data->curvature( j );
	 
	 if( iCurv * jCurv > 0 ) 
	    sign = 1;
	 else 
	    sign = -1;
	 
	 double dxr = m_data->rcImpactVec(i).x() - m_data->rcImpactVec(j).x();
	 double dyr = m_data->rcImpactVec(i).y() - m_data->rcImpactVec(j).y();
	 m_dRadiusCImVec[ iPair ] = sqrt( dxr*dxr + dyr*dyr );

	 double dxmin = m_data->minPoint(i).x() - m_data->minPoint(j).x();
	 double dymin = m_data->minPoint(i).y() - m_data->minPoint(j).y();
	 m_dT[ iPair ] = sqrt( dxmin*dxmin + dymin*dymin );

	 //Make the pair
	 if( (m_data->radiusOfCurv(i) < m_data->rcCut()) && 
	     (m_data->radiusOfCurv(j) < m_data->rcCut()) )
	 {
	    if( sign == -1 )
	    {
	       if( (dPhi > m_data->dPhiCut()) && 
		   (m_dRadiusCImVec[ iPair ] < m_data->dRCCut()) )
	       {
		  thisIsCPair = true;
	       }
 	    }
	    if( thisIsCPair )
	    {
	       if( m_dRadiusCImVec[ iPair ] > m_data->dRCCutLow() && 
		   m_dRadiusCImVec[ iPair ] < m_data->dRCCutHigh() )
	       {
		  dbMax = absMax( m_data->d0(i), m_data->d0(j) );
		  z0Max = absMax( m_data->z0(i), m_data->z0(j) );

		  if( z0Max < m_data->zMaxCut() && 
		      dbMax < m_data->dbMaxCut() )
		  { 
		      thisIsCPair = false;
		  }
	       }
	    }
	    if( thisIsCPair )
	    {
	       if( (dPhi > 3.04 && m_dRadiusCImVec[ iPair ] > 0.10 ) ||
		   (dPhi > 3.10 && m_dRadiusCImVec[ iPair ] > 0.06 ) )
		  thisIsCPair = false;
	    }
	 }

	 if( thisIsCPair )
	 {
	   
	    iT = (UInt16) i+1;
	    jT = (UInt16) j+1;
	    m_curlerPairs.push_back( CPair( iT, jT ) );
	 }

      }
   }

   m_numCurlerPairs = m_curlerPairs.size();


}

double TMCurlers::absMax( double a, double b )
{
   double m = fabs(a);
   if( fabs(b) > m )
      m = b;

   return m;
}


int TMCurlers::pairNumber( int track1Id, int track2Id, int numTracks ) const
{
   int retValue = -1;
   if( track2Id < track1Id ) 
   {
      retValue = numTracks*(track2Id - 1) - 0.5*track2Id*(track2Id-1) + track1Id - track2Id - 1;
      return retValue;
   }
   else
   {
      retValue = numTracks*(track1Id - 1) - 0.5*track1Id*(track1Id-1) + track2Id - track1Id - 1;
      return retValue;
   } 
}


int  TMCurlers::getNumCurlerPairs() const
{
   return m_numCurlerPairs; 
}

double TMCurlers::delRadiusCDAVec( int ipair ) const
{
   if( (ipair >= 0) && (ipair < m_numTrkPairs) )
   {
      return m_dRadiusCImVec[ipair];
   }
   else
   {
      report( WARNING, kFacilityString ) << "Invalid track pair number in delRadiusCDAVec()!!" << endl;
      return 999;
   }

}

double TMCurlers::delTails( int ipair ) const
{
   if( (ipair >= 0 ) && (ipair < m_numTrkPairs) )
   {
      return m_dT[ipair];
   }
   else
   {
      report( WARNING, kFacilityString ) << "Invalid track pair number in delTails!!" << endl;
      return 999;      
   }
}

TMCurlers::CPair TMCurlers::getCurlerPair( int i ) const
{
   if( i < m_curlerPairs.size() )
   {
      return m_curlerPairs[i];
   }
   else
   {
      report( WARNING, kFacilityString ) << "Invalid curler pair number in getCurlerPair()!!" << endl;
      return CPair( 0, 0 );
   }

}

TMCurlers::CPairVector TMCurlers::getCurlerPairVector() const
{
   return m_curlerPairs;
}



//
// static member functions
//







