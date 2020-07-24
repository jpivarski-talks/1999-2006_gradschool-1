#if !defined(PACKAGE_TMCURLERMISSINGTHIRDS_H)
#define PACKAGE_TMCURLERMISSINGTHIRDS_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      TMCurlerMissingThirds
// 
/**\class TMCurlerMissingThirds TMCurlerMissingThirds.h package/TMCurlerMissingThirds.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Thu Sep  5 10:38:32 EDT 2002
// $Id: TMCurlerMissingThirds.h,v 1.1 2002/11/04 18:31:00 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlerMissingThirds.h,v $
// Revision 1.1  2002/11/04 18:31:00  nea9
// New CleoIII Trkman
//

// system include files

// user include files
#include "Trkman/TMData.h"
#include "Trkman/TMClassification.h"
#include "Trkman/TMCurlers.h"
#include "Experiment/report.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"
#include "STLUtility/fwd_vector.h"

// forward declarations
class NavTrack;
class MagneticField;


class TMCurlerMissingThirds
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef FATable< NavTrack >                 NavTrackTable;
      typedef FATable< NavTrack >::const_iterator NavTrackConstIt;
      typedef FAItem< MagneticField >             MagFieldItem;
      typedef TMCurlers::CurlerGroupVector        CurlerGroupVector;

      // ---------- Constructors and destructor ----------------
      TMCurlerMissingThirds( NavTrackTable& theTracks, 
			     TMData*& data,
			     TMClassification::TrackClassification& trackClass,
			     TMCurlers*& curlers );
      virtual ~TMCurlerMissingThirds();

      // ---------- member functions ---------------------------
      void findMissingThirds( TMClassification::TrackClassification& trackClass,
			      TMData*& data );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      TMCurlerMissingThirds( const TMCurlerMissingThirds& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TMCurlerMissingThirds& operator=( const TMCurlerMissingThirds& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      NavTrackTable           m_theTracks;
      TMCurlers*              m_curlers;
      CurlerGroupVector       m_curlerGroups;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/TMCurlerMissingThirds.cc"
//#endif

#endif /* PACKAGE_TMCURLERMISSINGTHIRDS_H */
