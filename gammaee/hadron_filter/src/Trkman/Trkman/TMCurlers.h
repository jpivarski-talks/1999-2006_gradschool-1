#if !defined(PACKAGE_TMCURLERS_H)
#define PACKAGE_TMCURLERS_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      TMCurlers
// 
/**\class TMCurlers TMCurlers.h package/TMCurlers.h

 Description: <one line class summary>




 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Wed Oct 23 19:57:43 EDT 2002
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "STLUtility/fwd_vector.h"
#include <vector>
#include <utility>

// user include files
#include "Trkman/TMData.h"
#include "Experiment/report.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"
#include "Cleo/types.h"
#include "CLHEP/Matrix/Matrix.h"

// forward declarations
class NavTrack;


class TMCurlers
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef FATable< NavTrack >                 NavTrackTable;
      typedef FATable< NavTrack >::const_iterator NavTrackConstIt;
      typedef pair< UInt16, UInt16 >              CPair;
      typedef STL_VECTOR( CPair )                 CPairVector;
      typedef STL_VECTOR( DABoolean )             TruthVector;
      typedef STL_VECTOR( int )                   CurlerGroup;
      typedef STL_VECTOR( CurlerGroup )           CurlerGroupVector;
      typedef STL_VECTOR( Double )                DoubleVec;
      typedef CurlerGroup                         CircleVector;
      //Store the code for each track just as the curler groups are stored
      //then use the curlerGroup vector and the track classification vector
      //to get the codes for individual tracks.
      typedef CurlerGroup                         TrackCodes;
      typedef CurlerGroupVector                   CurlerCodeVector;


      // ---------- Constructors and destructor ----------------
      TMCurlers( NavTrackTable& theTracks, TMData*& data );
      virtual ~TMCurlers();

      // ---------- member functions ---------------------------
      void makeCurlerPairs();
      double absMax( double a, double b );
      void makeCurlerGroups();
      void computePhiAvg();
      void mergeGroups();
      void makeCurlerList( CPairVector pairList, 
			   TruthVector& matched, 
			   CurlerGroup& list );
      void makeCurlerCircles();
      void setCircleTrack( int i, int track );
      void classifyTwoCurlerGroup( int i );
      void classifyThreeCurlerGroup( int i );
      void classifyOtherCurlerGroup( int i );
      int  getCellNum( int v1, int v2, int v3, int v4, int v5, int v6 );
      int  normalThreeCurlerInfo( int track1, int track2, int track3, 
				  double& minDRC, double& avgRC, 
				  int& num1, int& num2 );
      void setRadiusSortMatrix( HepMatrix& radiusSortMatrix,
				int sortPos );
      void setProbabilitySortMatrix( HepMatrix& sortMatrix,
				     int theCol );
      void chooseMessyGroups( int group, int& FH );


      // ---------- const member functions ---------------------


      // ---------- const member functions ---------------------
      int         pairNumber( int t1, int t2, int N ) const;
      int         getNumCurlerPairs() const;
      int         numCurlerGroups() const;
      int         circleTrack( int i ) const;
      double      delRadiusCDAVec( int ipair ) const;
      double      delTails( int ipair ) const;
      double      phiAverage( int i ) const;
      CPair       getCurlerPair( int i ) const;
      CPairVector getCurlerPairVector() const;
      CurlerGroup curlerGroup( int i ) const;
      CurlerGroupVector curlerGroupVector() const;
      CurlerCodeVector curlerCodes() const;
      TrackCodes classificationVector() const;


      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      TMCurlers( const TMCurlers& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TMCurlers& operator=( const TMCurlers& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      int           m_numCurlerPairs;
      int           m_numTrkPairs;
      int           m_numCurlerGroups;

      double        m_diffAngle;
      double*       m_dRadiusCImVec;
      double*       m_dT;

      CPairVector   m_curlerPairs;
      NavTrackTable m_theTracks;
      TMData*       m_data;

      CPairVector       m_cPairList;
      CPairVector       m_grpPairList;
      CurlerGroupVector m_curlerGroups;
      DoubleVec         m_phiAvg;
      TruthVector       m_pairMatched;
      TruthVector       m_groupMerged;
      CircleVector      m_circleTracks;
      CurlerCodeVector  m_curlerCodes;
 
      // ---------- static data members ------------------------
      static int threeCurlerCellListNormal[ 486 ];
      static int fourCurlerCellListNormal[ 486 ];

      static double cosTL[6]; 
      static double d0L[4];
      static double thErrL[4];
      static double z0L[4];
      static double zErrL[4]; 
      static double zHitL[7]; 

      static double rcProb[25];
      static double dbProb[25];
      static double zHProb[25];
      static double denProb[25];
      static double svrHProb[25];


};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/TMCurlers.cc"
//#endif

#endif /* PACKAGE_TMCURLERS_H */
