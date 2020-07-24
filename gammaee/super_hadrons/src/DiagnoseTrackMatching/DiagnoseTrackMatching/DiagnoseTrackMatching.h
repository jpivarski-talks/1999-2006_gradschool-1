// -*- C++ -*-
#if !defined(DIAGNOSETRACKMATCHING_DIAGNOSETRACKMATCHING_H)
#define DIAGNOSETRACKMATCHING_DIAGNOSETRACKMATCHING_H
//
// Package:     <DiagnoseTrackMatching>
// Module:      DiagnoseTrackMatching
//
/**\class DiagnoseTrackMatching DiagnoseTrackMatching.h DiagnoseTrackMatching/DiagnoseTrackMatching.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Feb 25 13:09:06 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"

// forward declarations

class DiagnoseTrackMatching : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      DiagnoseTrackMatching( void );                      // anal1 
      virtual ~DiagnoseTrackMatching();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);
      //virtual ActionBase::ActionResult geometry( Frame& iFrame);
      //virtual ActionBase::ActionResult hardware( Frame& iFrame);
      //virtual ActionBase::ActionResult user( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      DiagnoseTrackMatching( const DiagnoseTrackMatching& );

      // ------------ assignment operator(s) ---------------------
      const DiagnoseTrackMatching& operator=( const DiagnoseTrackMatching& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (DiagnoseTrackMatching::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_track_track;
      int m_notrack_track;
      int m_track_notrack;
      int m_notrack_notrack;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DIAGNOSETRACKMATCHING_DIAGNOSETRACKMATCHING_H */
