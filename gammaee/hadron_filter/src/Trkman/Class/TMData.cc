// -*- C++ -*-
//
// Package:     <package>
// Module:      TMData
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Tue Dec 18 09:56:45 EST 2001
// $Id$
//
// Revision history
//
// $Log$

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
#include "Cleo/cleo_math.h"

// user include files
//#include "Experiment/report.h"
#include "Trkman/TMData.h"
#include "TrackRoot/TRSeedTrack.h"

//
// constants, enums and typedefs
//

#define iout report( INFO, kFacilityString )

static const double kPi       = 3.1415926535898;
static const double zEndCap   = 0.9652;  //Need cleo3 value here!!!!
static const double rBarrel   = 0.816;   //Old value 0.947 And here!!!
static const char* const kFacilityString = "TrackManProd.TMData" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
double TMData::m_cellClass[ 162 ] = {

   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2,
   2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   1, 1, 1, 3, 1, 3, 5, 2, 1, 1, 1, 2, 1, 5, 3, 2, 1, 2, 1, 3,
   1, 2, 3, 1, 2, 2, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 4, 4, 4, 2,
   4, 3, 4, 5, 5, 5, 4, 4, 1, 5, 3, 3, 3, 3, 5, 5, 5, 2, 5, 3,
   5, 2, 5, 2, 1, 2, 5, 2, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 1, 3,
   1, 2, 2, 2, 1, 1, 3, 3, 3, 2, 3, 4, 4, 2, 3, 1, 1, 3, 2, 4,
   1, 1, 1, 2, 3, 3, 3, 3, 1, 1, 2, 2, 3, 3, 1, 2, 1, 2, 1, 2,
   1, 1 
};

double TMData::m_svrLayerRadius[ 4 ] = {
   
   25.0, 40.0, 70.0, 101

};


double TMData::m_drLayerRadius[ 47 ] = {

   132.105, 145.898, 160.122, 173.914, 188.417,
   202.235, 216.332, 230.124, 244.475, 258.293,
   272.542, 286.360, 300.355, 314.173, 328.371,
   342.163, 369.974, 383.919, 397.863, 411.782,
   426.108, 440.053, 453.972, 467.917, 482.192,
   496.111, 510.055, 523.975, 538.224, 552.143,
   566.088, 580.007, 594.231, 608.150, 622.095,
   636.014, 650.213, 664.132, 678.051, 691.996,
   706.144, 720.088, 734.008, 747.952, 762.100,
   776.019, 789.938
};

//
// constructors and destructor
//
TMData::TMData( NavTrackTable& theTracks, FAItem< BeamSpot >& beamSpot )
{

   //Set the beam spot
   m_beamSpot = beamSpot->center();


   //Set the track table
   m_theTracks = theTracks;

   //We haven't initialised the data yet
   m_initialised = false;

   //Set the array sizes.
   m_maxLayer      = new int[ m_theTracks.size() ];
   m_minLayer      = new int[ m_theTracks.size() ];

   m_hits          = new double[ m_theTracks.size() ];
   m_densityOfHits = new double[ m_theTracks.size() ];
   m_d0            = new double[ m_theTracks.size() ];
   m_dA            = new double[ m_theTracks.size() ];
   m_phi           = new double[ m_theTracks.size() ];
   m_z0            = new double[ m_theTracks.size() ];
   m_cotTheta      = new double[ m_theTracks.size() ];
   m_curvature     = new double[ m_theTracks.size() ];
   m_radiusC       = new double[ m_theTracks.size() ];
   m_radiusCIm     = new double[ m_theTracks.size() ];
   m_phiEnd        = new double[ m_theTracks.size() ];
   m_radiusEnd     = new double[ m_theTracks.size() ];

   //Set the 2D array size
   m_isLayerHit    = new DABoolean*[ m_theTracks.size() ];
   for( int i=0; i<m_theTracks.size(); i++ )
   {
      m_isLayerHit[i] = new DABoolean[56];
   }

   m_minPoint.reserve( m_theTracks.size() );
   m_maxPoint.reserve( m_theTracks.size() );
   m_radiusCImVec.reserve( m_theTracks.size() ); 

   //Initialise the data
   initData();

}

// TMData::TMData( const TMData& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

TMData::~TMData()
{
   m_minPoint.clear();
   m_maxPoint.clear();
   m_radiusCImVec.clear();

   delete[] m_maxLayer;
   delete[] m_minLayer;

   delete[] m_hits;
   delete[] m_densityOfHits;
   delete[] m_d0;
   delete[] m_dA;
   delete[] m_phi;
   delete[] m_z0;
   delete[] m_cotTheta;
   delete[] m_curvature;
   delete[] m_radiusC;  
   delete[] m_radiusCIm;
   delete[] m_phiEnd;
   delete[] m_radiusEnd;

   for( int i=0; i<m_theTracks.size(); i++ )
   {
      delete[] m_isLayerHit[i];
   }
   delete[] m_isLayerHit;
} 

//
// assignment operators
//
// const TMData& TMData::operator=( const TMData& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void TMData::initData()
{
   //Set the cuts, initally use the old values and see how we go
//    m_dPhiCut    = 2.8;
//    m_dRCCut     = 0.1;
//    m_rcCut      = 1.1;
//    m_dRCCutLow  = 0.05;
//    m_dRCCutHigh = 0.1;
//    m_zMaxCut    = 0.025;
//    m_dbMaxCut   = 0.0015;

   m_dPhiCut    = 2.8;
   m_dRCCut     = 0.14;
   m_rcCut      = 1.0;
   m_dRCCutLow  = 0.09;
   m_dRCCutHigh = 0.14;
   m_zMaxCut    = 0.025;
   m_dbMaxCut   = 0.0015;


   //Loop over the tracks
   int i = 0;
   NavTrackConstIt nTrack;
   for( nTrack = m_theTracks.begin(); nTrack != m_theTracks.end(); nTrack++ )
   {

      //Set the density of hits
      int numLayers = TRSubdetectorLists::layerMapNLayers( TRSubdetectorLists::kCLEOIII,
							   TRSubdetectorLists::kEntireDetector );
      DABoolean firstLayer = true;
      FAItem< TRTrackFitQuality > nQ = (*nTrack).pionQuality();
      int ll = 0;
      m_hits[i] = 0;
      if( nQ->fit() && !nQ->fitAbort() )
	 //if( !nQ->fitAbort() )
      {
	 DABoolean jHit;
	 for( int j=1; j<=numLayers; j++ )
	 {
	    jHit = nQ->isLayerHit( TRSubdetectorLists::kEntireDetector, j );
	    m_isLayerHit[i][j-1] = jHit;
	    if( jHit )
	    { 
	       m_hits[i]++; 
	       ll = j; 

	       if( firstLayer )
	       { 
		  firstLayer = false; 
		  m_minLayer[i] = ll; 
	       }
	    }
	 }
	 m_maxLayer[i] = ll;
	 if( ll != 0 )
	 {
	    m_densityOfHits[i] = m_hits[i]/ll;
	 }
	 else
	 {
	    m_densityOfHits[i] = 0;
	 }
      }
      else
      {
	 for( int j=1; j<=numLayers; j++ )
	 {
	    m_isLayerHit[i][j-1] = false;
	 }
	 m_minLayer[i] = 0;
	 m_maxLayer[i] = numLayers;
	 m_hits[i] = (double) nTrack->seedQuality()->numberLayers();
	 m_densityOfHits[i] = -1.0;	 
      }

      //Set the radius of curvature
      double curvature = nTrack->seedTrack()->curvature();
      double d0        = nTrack->seedTrack()->d0();
      double phi       = nTrack->seedTrack()->phi0();
      double z0        = nTrack->seedTrack()->z0();
      double cotTheta  = nTrack->seedTrack()->cotTheta();


      KTHelix* aHelix = new KTHelix( nTrack->seedTrack()->curvature(),
				     nTrack->seedTrack()->phi0(),
				     nTrack->seedTrack()->d0(),
				     nTrack->seedTrack()->cotTheta(),
				     nTrack->seedTrack()->z0(),
				     nTrack->seedTrack()->referencePoint());

      double dist_moved;
      KTMoveControl::MoveStatus status;

      status = aHelix->moveToReferencePoint( m_beamSpot, dist_moved );

      if( status != KTMoveControl::kMoveOK )
      {
	 report( ERROR, kFacilityString ) << "Could not move Helix to the reference point!!" << endl;
      }

      double dB = aHelix->d0();
      delete aHelix;


      HepPoint3D tmpVec;
      if( curvature != 0 )
      {
	 m_dA[i] = d0;
	 m_d0[i] = dB;
	 m_phi[i] = phi;
	 m_z0[i] = z0;
	 m_cotTheta[i] = cotTheta;
	 m_curvature[i] = curvature;
	 m_radiusC[i]   = 1/curvature;
	 m_radiusCIm[i] = m_radiusC[i] + d0;
	 tmpVec.setX( -m_radiusCIm[i]*sin( phi ) );
	 tmpVec.setY(  m_radiusCIm[i]*cos( phi ) );
	 tmpVec.setZ( 0 );
	 m_radiusCImVec.push_back( tmpVec );
	 m_radiusC[i]  = fabs( m_radiusC[i] );
	 m_radiusCIm[i] = fabs( m_radiusCIm[i] );

      }
      else
      {
	 m_radiusC[i]   = 0;
	 m_radiusCIm[i] = 0;
	 tmpVec.setX( 0 );
	 tmpVec.setY( 0 );
	 tmpVec.setZ( 0 );
	 m_radiusCImVec.push_back( tmpVec );
	 report( INFO, kFacilityString ) << "The curvature of track " << nTrack->identifier() << " is zero."
	                                 << " Setting the various radii to zero." << endl;
	 
      }
      tmpVec.setX( -d0*sin( phi ) );
      tmpVec.setY(  d0*cos( phi ) );
      tmpVec.setZ( 0 );

      m_minPoint.push_back( tmpVec );
      double y = m_radiusCImVec[i].y();
      double x = m_radiusCImVec[i].x();
      if( x==0 && y==0 ) m_phiEnd[i] = -kPi/2;
      else               m_phiEnd[i] = atan2( y, x );

      if( curvature != 0 ) m_maxPoint.push_back( maximumPoint( nTrack ) );
      else                 m_maxPoint.push_back( tmpVec );
      x = m_maxPoint[i].x();
      y = m_maxPoint[i].y();
      m_radiusEnd[i] = sqrt( x*x + y*y ); 


      i++;
      
   }
   m_initialised = true;

}

HepPoint3D TMData::maximumPoint( NavTrackConstIt aTrack )
{

   HepPoint3D retPoint( 0,0,0 );

   double curvature = aTrack->seedTrack()->curvature();
   double d0        = aTrack->seedTrack()->d0();
   double phi       = aTrack->seedTrack()->phi0();
   double cotTheta  = aTrack->seedTrack()->cotTheta();
   double z0        = aTrack->seedTrack()->z0();

   //Initialise some more variables that we need.
   double radiusC      = fabs( 0.5/curvature );
   double apexDistance = 1/curvature + d0;
   double apexX        = -apexDistance*sin( phi );
   double apexY        =  apexDistance*cos( phi );
   double apexZ        =  fabs( radiusC*kPi*cotTheta + z0 );

   //If the particle cannot hit the barrel ...
   if( apexDistance <= rBarrel )
   {
      //Can it hit the endcap?
      if( fabs( apexZ ) > zEndCap )
      {
	 retPoint = endcapProjection( aTrack->seedTrack() );
	 if( retPoint.x() == retPoint.y() && retPoint.y() == retPoint.z() 
	     && retPoint.z() == 0)
	 {
	    report( WARNING, kFacilityString ) << "Could not find the intersection point with endcap!!!" << endl;
	 }
	 return retPoint;
      }
      else
      {
	 retPoint.setX( apexX );
	 retPoint.setY( apexY );
	 retPoint.setZ( apexZ );
	 return retPoint;
      }

   }
   //If the particle CAN hit the barrel ...
   else
   {
      double theta;
      double phiS;
      double absRCDA = fabs( 0.5/curvature + d0 );
      double thetaRCDA;
      if( curvature > 0) thetaRCDA = phi + kPi/2;
      else              thetaRCDA = phi - kPi/2;
      if( cotTheta != 0 )
      {
	 theta = fabs( (zEndCap - z0)/(radiusC*cotTheta) );
      }
      else
      {
	 //If cosTheta is equal to zero set theta to 2Pi 
	 //which is outside of the allowed region.
	 theta = 2*kPi;
      }
      if( curvature > 0 )
      {
	 phiS = theta + phi - kPi/2; 
      }
      else
      {
	 phiS = phi + kPi/2 - theta;
      }
      double endcapX    = absRCDA*cos( thetaRCDA ) + radiusC*cos( phiS );
      double endcapY    = absRCDA*sin( thetaRCDA ) + radiusC*sin( phiS );
      double endcapDist = sqrt( endcapX*endcapX + endcapY*endcapY );

      if( theta > kPi || endcapDist > rBarrel )
      {
	 retPoint = barrelProjection( aTrack->seedTrack() );
	 if( retPoint.x() == retPoint.y() && retPoint.y() == retPoint.z() 
	     && retPoint.z() == 0)
	 {
	    report( WARNING, kFacilityString ) << "Could not find the intersection point with barrel!!!" << endl;
	 }
	 return retPoint;
      }
      else
      {
	 retPoint = endcapProjection( aTrack->seedTrack() );
	 if( retPoint.x() == retPoint.y() && retPoint.y() == retPoint.z() 
	     && retPoint.z() == 0)
	 {
	    report( WARNING, kFacilityString ) << "Could not the intersection point with endcap!!!" << endl;
	 }
	 return retPoint;
      }

   }

}

HepPoint3D TMData::endcapProjection( SeedTrackItem seedTrack )
{
   
   KTHelix* aHelix = new KTHelix( seedTrack->curvature(),
		  		  seedTrack->phi0(),
				  seedTrack->d0(),
				  seedTrack->cotTheta(),
				  seedTrack->z0(),
				  seedTrack->referencePoint());
   HepPoint3D retPoint( 0,0,0 );

   //Move along the seedTrack to the z point of the endcap.
   double dist_moved = 0;

   KTMoveControl::MoveStatus status;
   KTMoveControl::MoveDirection direction = KTMoveControl::kDirectionForward;

   status = aHelix->moveToZPosition( zEndCap, dist_moved );

   if( status != KTMoveControl::kMoveOK )
   {
      report( ERROR, kFacilityString ) << "Could not project helix to the endcap!!" << endl;
      delete aHelix;
      return retPoint;
   }
   else
   {
      //The intersection point is the new reference point.
      const HepPoint3D& tmpPoint = aHelix->referencePoint();
      retPoint.setX( tmpPoint.x() );
      retPoint.setY( tmpPoint.y() );
      retPoint.setZ( tmpPoint.z() );

      delete aHelix;
      return retPoint;
   }
}

HepPoint3D TMData::barrelProjection( SeedTrackItem seedTrack )
{
   KTHelix* aHelix = new KTHelix( seedTrack->curvature(),
		  		  seedTrack->phi0(),
				  seedTrack->d0(),
				  seedTrack->cotTheta(),
				  seedTrack->z0(),
				  seedTrack->referencePoint());
   HepPoint3D retPoint( 0,0,0 );

   double dist_moved = 0;

   KTMoveControl::MoveStatus status;
   KTMoveControl::MoveDirection direction = KTMoveControl::kDirectionForward;

   status = aHelix->moveToRadius( rBarrel, dist_moved );

   if( status != KTMoveControl::kMoveOK )
   {
      report( ERROR, kFacilityString ) << "Could not project helix to the barrel!!" << endl;
      delete aHelix;
      return retPoint;
   }
   else
   {
      //The intersection point is the new reference point.
      const HepPoint3D& tmpPoint = aHelix->referencePoint();
      retPoint.setX( tmpPoint.x() );
      retPoint.setY( tmpPoint.y() );
      retPoint.setZ( tmpPoint.z() );

      delete aHelix;
      return retPoint;
   }


}

//Extract data functions
DABoolean TMData::isLayerHit( int i, int layer )
{
   if( i < m_theTracks.size() && i >= 0 &&
       ( layer >=1 && layer <= 56 ) )
   {
      return m_isLayerHit[i][layer-1];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot return hits "
				       << " for index value i = " << i 
				       << ", layer = " << layer << endl;
      return 0;
   }
   
}

HepPoint3D TMData::beamSpot()
{
   return m_beamSpot;
}


double TMData::hits( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_hits[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot return hits "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::densityOfHits( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_densityOfHits[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute density of hits "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::d0( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_d0[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get d0 "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::dA( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_dA[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get distance from origin "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::phi( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_phi[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get phi "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::z0( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_z0[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get z0 "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::cotTheta( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_cotTheta[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get cotTheta "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::curvature( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_curvature[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get curvature "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::radiusOfCurv( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_radiusC[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute radius of curvature "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::rcImpact( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_radiusCIm[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute impact "
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::phiEnd( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_phiEnd[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute phi end"
				       << " for index value i = " << i << endl;
      return 0;
   }
}

double TMData::radiusEnd( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_radiusEnd[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute radius end"
				       << " for index value i = " << i << endl;
      return 0;
   }
}

HepPoint3D TMData::rcImpactVec( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_radiusCImVec[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute impact vector "
				       << " for index value i = " << i << endl;
      HepPoint3D retVal(0,0,0);
      return retVal;
   }
}

HepPoint3D TMData::minPoint( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_minPoint[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot compute minPoint "
				       << " for index value i = " << i << endl;
      HepPoint3D retVal(0,0,0);
      return retVal;
   }
}


//Get the layer for a particular radius
int TMData::layerAtRadius( double radius )
{
   //Convert the radius to mm
   radius = radius*1000;
   
   //Start outside the beampipe
   double lastR = 20;

   //Search in the Silicon first
   for( int i=0; i<4; i++ )
   {
      if( (radius > lastR) && (radius <= m_svrLayerRadius[i]) )
      {
	 return i+1;
      }
      else
      {
	 lastR = m_svrLayerRadius[i];
      }
   }

   //Search the DR
   for( int j=0; j<47; j++ )
   {
      if( (radius > lastR) && (radius <= m_drLayerRadius[j]) )
      {
	 return j+9;
      }
      else
      {
	 lastR = m_drLayerRadius[j];
      }
   }

   //If we haven't returned anything yet, there
   //must be an error
   return -1;
   
}

int TMData::maxLayer( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_maxLayer[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get maxLayer "
				       << " for index value i = " << i << endl;
      return -1;
   }
}

int TMData::minLayer( int i )
{
   if( i < m_theTracks.size() && i >= 0  )
   {
      return m_minLayer[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get minLayer "
				       << " for index value i = " << i << endl;
      return -1;
   }
}

double TMData::dPhiCut()
{
   return m_dPhiCut;
}

double TMData::dRCCut()
{
   return m_dRCCut;
}

double TMData::rcCut()
{
   return m_rcCut;
}

double TMData::dRCCutLow()
{
   return m_dRCCutLow;
}

double TMData::dRCCutHigh()
{
   return m_dRCCutHigh;
}

double TMData::zMaxCut()
{
   return m_zMaxCut;
}

double TMData::dbMaxCut()
{
   return m_dbMaxCut;
}

DABoolean TMData::initialised()
{
   return m_initialised;
}


//
// const member functions
//

//
// static member functions
//
