#if !defined(PACKAGE_TMDATA_H)
#define PACKAGE_TMDATA_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      TMData
// 
/**\class TMData TMData.h package/TMData.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Tue Dec 18 09:57:01 EST 2001
// $Id: TMData.h,v 1.1 2002/11/04 18:31:01 nea9 Exp $
//
// Revision history
//
// $Log: TMData.h,v $
// Revision 1.1  2002/11/04 18:31:01  nea9
// New CleoIII Trkman
//

// system include files

// user include files
#include "Experiment/report.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"


#include "STLUtility/fwd_vector.h"
#include "CLHEP/Geometry/Point3D.h"
#include "Navigation/NavTrack.h"
#include "BeamSpot/BeamSpot.h"

// forward declarations

class TMData
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef FATable< NavTrack >                 NavTrackTable;
      typedef FATable< NavTrack >::const_iterator NavTrackConstIt;
      typedef FAItem< TRSeedTrack >               SeedTrackItem;
      typedef STL_VECTOR( HepPoint3D )            PointVector;

      // ---------- Constructors and destructor ----------------
      TMData( NavTrackTable& theTracks, FAItem< BeamSpot >& beamSpot );
      virtual ~TMData();

      // ---------- member functions ---------------------------
      void initData();
      HepPoint3D maximumPoint( NavTrackConstIt aTrack );
      HepPoint3D endcapProjection( SeedTrackItem seedTrack );
      HepPoint3D barrelProjection( SeedTrackItem seedTrack );

      DABoolean isLayerHit( int i, int layer );

      HepPoint3D beamSpot();

      int layerAtRadius( double radius );
      int maxLayer( int i );
      int minLayer( int i );

      double hits( int i );
      double densityOfHits( int i );
      double d0( int i );
      double dA( int i );
      double phi( int i );
      double z0( int i );
      double cotTheta( int i );
      double curvature( int i );
      double radiusOfCurv( int i );
      double rcImpact( int i );
      double phiEnd( int i );
      double radiusEnd( int i );
      HepPoint3D rcImpactVec( int i );
      HepPoint3D minPoint( int i );
      HepPoint3D maxPoint( int i );

      double dPhiCut();
      double dRCCut();
      double rcCut();
      double dRCCutLow();
      double dRCCutHigh();
      double zMaxCut();
      double dbMaxCut();
      
      DABoolean initialised();
      

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      TMData( const TMData& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TMData& operator=( const TMData& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      NavTrackTable m_theTracks;
      DABoolean m_initialised;

      int* m_maxLayer;
      int* m_minLayer;

      double* m_d0;
      double* m_dA;
      double* m_phi;
      double* m_z0;
      double* m_cotTheta;
      double* m_hits;
      double* m_densityOfHits;
      double* m_curvature;
      double* m_radiusC;
      double* m_radiusCIm;
      double* m_phiEnd;
      double* m_radiusEnd;

      DABoolean** m_isLayerHit;
      PointVector m_radiusCImVec;
      PointVector m_minPoint;
      PointVector m_maxPoint;

      //Cuts
      double m_dPhiCut;
      double m_dRCCut;
      double m_rcCut;
      double m_dRCCutLow;
      double m_dRCCutHigh;
      double m_zMaxCut;
      double m_dbMaxCut;

      //Beam Spot
      HepPoint3D m_beamSpot;

      // ---------- static data members ------------------------
      static double  m_cellClass[ 162 ];
      static double  m_drLayerRadius[ 47 ];
      static double  m_svrLayerRadius[ 4 ];
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/TMData.cc"
//#endif

#endif /* PACKAGE_TMDATA_H */
