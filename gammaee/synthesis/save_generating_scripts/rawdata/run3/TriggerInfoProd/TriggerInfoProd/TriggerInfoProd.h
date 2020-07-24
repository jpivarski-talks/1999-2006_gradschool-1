// -*- C++ -*-
#if !defined(TRIGGERINFOPROD_TRIGGERINFOPROD_H)
#define TRIGGERINFOPROD_TRIGGERINFOPROD_H
//
// Package:     <TriggerInfoProd>
// Module:      TriggerInfoProd
//
/**\class TriggerInfoProd TriggerInfoProd.h TriggerInfoProd/TriggerInfoProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:03:40 EDT 2004
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

class TriggerInfoProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      TriggerInfoProd( void );                      // anal1 
      virtual ~TriggerInfoProd();                   // anal5 

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
      TriggerInfoProd( const TriggerInfoProd& );

      // ------------ assignment operator(s) ----------------------
      const TriggerInfoProd& operator=( const TriggerInfoProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* TRIGGERINFOPROD_TRIGGERINFOPROD_H */
