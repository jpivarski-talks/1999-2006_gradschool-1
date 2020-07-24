// -*- C++ -*-
#if !defined(LUMIRUNCHECK_LUMIRUNCHECK_H)
#define LUMIRUNCHECK_LUMIRUNCHECK_H
//
// Package:     <LumiRunCheck>
// Module:      LumiRunCheck
//
/**\class LumiRunCheck LumiRunCheck.h LumiRunCheck/LumiRunCheck.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Nov 12 16:40:44 EST 2004
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

class LumiRunCheck : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LumiRunCheck( void );                      // anal1 
      virtual ~LumiRunCheck();                   // anal5 

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
      LumiRunCheck( const LumiRunCheck& );

      // ------------ assignment operator(s) ---------------------
      const LumiRunCheck& operator=( const LumiRunCheck& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LumiRunCheck::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void spill();

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;
      int m_numer[200];
      int m_denom[200];
      int m_thetaphi[10][10];

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LUMIRUNCHECK_LUMIRUNCHECK_H */
