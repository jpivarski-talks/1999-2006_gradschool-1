#if !defined(TRKMAN_TMCLASSIFICATION_H)
#define TRKMAN_TMCLASSIFICATION_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      TMClassification
// 
/**\class TMClassification TMClassification.h package/TMClassification.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Mon Jul 22 11:04:06 EDT 2002
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "Experiment/Experiment.h"
#include "Experiment/report.h"

#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"

#include "Trkman/TMData.h"
#include "Trkman/TMCurlers.h"


// forward declarations

class TMClassification
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef FATable< NavTrack >                 NavTrackTable;
      typedef FATable< NavTrack >::const_iterator NavTrackConstIt;
      typedef TMCurlers::TrackCodes               TrackClassification;
      typedef TMCurlers::CurlerGroupVector        CurlerGroupVector;
      typedef TMCurlers::CurlerGroup              VeeGroup;
      typedef TMCurlers::CurlerGroupVector        VeeGroupVector;
      typedef TMCurlers::TruthVector              TruthVector;

      // ---------- Constructors and destructor ----------------
      TMClassification( NavTrackTable& theTracks, TMData*& data );
      virtual ~TMClassification();

      // ---------- member functions ---------------------------



      //Returns the classification for each track after it has been
      //processed by trkman
      TrackClassification trackClassifications() const;

      //Returns the vector specifying whether each track
      //should be used for matching or not.
      DABoolean useTrack( int track ) const;

      //Return the vector of curler groups
      CurlerGroupVector curlerGroupVector() const;

      //Return the vector of vee groups
      VeeGroupVector veeGroupVector() const;

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      TMClassification( const TMClassification& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TMClassification& operator=( const TMClassification& ); // stop default

      // ---------- private member functions -------------------
      void findVees ();
      DABoolean vertexProperties( HepPoint3D& vtx, DABoolean first );
      DABoolean calculateTrackHitDensities( int i, int j );
      void mergeVeeGroups();
      void makeVeeList( VeeGroupVector pairList, TruthVector& matched, VeeGroup& list );
      void reclassifyVees();
      void removeBadTracks();
      void removeTails();
      void matchTracksToShowers();


      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      NavTrackTable m_theTracks;

      TMCurlers* m_curlers;
      TMData*    m_data;

      TrackClassification m_trackClass;
      DABoolean*          m_matched;
      CurlerGroupVector   m_curlerGroups;
      VeeGroupVector      m_veeGroups;
      VeeGroupVector      m_tmpVeeGroups;
      
      //I circle vars
      double m_iCurv;
      double m_iRadius;      
      double m_iPhi;
      double m_iDA;
      double m_iSign;
      double m_iXC; 
      double m_iYC;
      double m_iPsi;
      double m_iZ0;
      double m_iCotTheta;
      HepPoint3D m_iCentre; 
      HepVector3D m_iMom;
      HepVector3D m_iVMom;

      //J circle vars
      double m_jCurv;
      double m_jRadius;      
      double m_jPhi;
      double m_jDA;
      double m_jSign;
      double m_jXC; 
      double m_jYC;
      double m_jPsi;
      double m_jZ0;
      double m_jCotTheta;
      HepPoint3D m_jCentre; 
      HepVector3D m_jMom;
      HepVector3D m_jVMom;

      //Vertex veriables
      DABoolean m_posPassed;
      DABoolean m_negPassed;
      double m_vxCosAngle;
      double m_vxDelZ;
      double m_vxRMiss;
      double m_vxChiSq;
      HepPoint3D m_vxPos;
      HepVector3D m_vxMom;


      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/TMClassification.cc"
//#endif

#endif /* PACKAGE_TMCLASSIFICATION_H */
