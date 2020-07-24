// -*- C++ -*-
#if !defined(TRKMANSELECTIONPROD_TRKMANSELECTIONPROD_H)
#define TRKMANSELECTIONPROD_TRKMANSELECTIONPROD_H
//
// Package:     <TrkmanSelectionProd>
// Module:      TrkmanSelectionProd
//
/**\class TrkmanSelectionProd TrkmanSelectionProd.h TrkmanSelectionProd/TrkmanSelectionProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Mon Oct 28 12:14:24 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"

// forward declarations

class TrkmanSelectionProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      TrkmanSelectionProd( void );                      // anal1 
      virtual ~TrkmanSelectionProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      TrkmanSelectionProd( const TrkmanSelectionProd& );

      // ------------ assignment operator(s) ----------------------
      const TrkmanSelectionProd& operator=( const TrkmanSelectionProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* TRKMANSELECTIONPROD_TRKMANSELECTIONPROD_H */
