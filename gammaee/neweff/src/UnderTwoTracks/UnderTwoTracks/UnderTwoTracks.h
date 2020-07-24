// -*- C++ -*-
#if !defined(UNDERTWOTRACKS_UNDERTWOTRACKS_H)
#define UNDERTWOTRACKS_UNDERTWOTRACKS_H
//
// Package:     <UnderTwoTracks>
// Module:      UnderTwoTracks
//
/**\class UnderTwoTracks UnderTwoTracks.h UnderTwoTracks/UnderTwoTracks.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Mar 29 14:15:47 EST 2004
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

class UnderTwoTracks : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      UnderTwoTracks( void );                      // anal1 
      virtual ~UnderTwoTracks();                   // anal5 

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

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      UnderTwoTracks( const UnderTwoTracks& );

      // ------------ assignment operator(s) ---------------------
      const UnderTwoTracks& operator=( const UnderTwoTracks& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (UnderTwoTracks::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* UNDERTWOTRACKS_UNDERTWOTRACKS_H */
