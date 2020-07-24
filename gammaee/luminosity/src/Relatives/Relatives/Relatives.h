// -*- C++ -*-
#if !defined(RELATIVES_RELATIVES_H)
#define RELATIVES_RELATIVES_H
//
// Package:     <Relatives>
// Module:      Relatives
//
/**\class Relatives Relatives.h Relatives/Relatives.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Apr  5 12:25:36 EDT 2005
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

class Relatives : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Relatives( void );                      // anal1 
      virtual ~Relatives();                   // anal5 

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
      Relatives( const Relatives& );

      // ------------ assignment operator(s) ---------------------
      const Relatives& operator=( const Relatives& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Relatives::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      bool Relatives::excludeBlockA(double westphi, double cotTheta);
      bool Relatives::excludeBlockBC(double westphi, double cotTheta);
      bool Relatives::safeb2b(double cotTheta1, double cotTheta2);
      bool Relatives::ggacop(double phi1, double phi2);
      bool Relatives::bbacop(double phi1, double phi2);
      void Relatives::print();

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;
      int m_event;
      int m_nuncorrected;
      int m_neetrackless;
      int m_neenom;
      int m_histogram[138];
      int m_histogram_energyup[138];
      int m_eenom_numer[138];
      int m_eenom_denom[138];
      int m_eephiup_numer[138];
      int m_eephiup_denom[138];
      int m_eephidown_numer[138];
      int m_eephidown_denom[138];
      int m_eethetaup_numer[138];
      int m_eethetaup_denom[138];
      int m_eethetadown_numer[138];
      int m_eethetadown_denom[138];
      int m_eeenergyup_numer[138];
      int m_eeenergyup_denom[138];
      double m_eenom_correct[138];
      double m_eenom_error[138];
      double m_eephiup_correct[138];
      double m_eephiup_error[138];
      double m_eephidown_correct[138];
      double m_eephidown_error[138];
      double m_eethetaup_correct[138];
      double m_eethetaup_error[138];
      double m_eethetadown_correct[138];
      double m_eethetadown_error[138];
      double m_eeenergyup_correct[138];
      double m_eeenergyup_error[138];
      double m_eenom_int;
      double m_eenom_err;
      double m_eephiup_int;
      double m_eephiup_err;
      double m_eephidown_int;
      double m_eephidown_err;
      double m_eethetaup_int;
      double m_eethetaup_err;
      double m_eethetadown_int;
      double m_eethetadown_err;
      double m_eeenergyup_int;
      double m_eeenergyup_err;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* RELATIVES_RELATIVES_H */
