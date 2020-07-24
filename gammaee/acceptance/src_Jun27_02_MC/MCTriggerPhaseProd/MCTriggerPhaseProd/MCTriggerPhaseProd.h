// -*- C++ -*-
#if !defined(MCTRIGGERPHASEPROD_MCTRIGGERPHASEPROD_H)
#define MCTRIGGERPHASEPROD_MCTRIGGERPHASEPROD_H
//
// Package:     <MCTriggerPhaseProd>
// Module:      MCTriggerPhaseProd
//
/**\class MCTriggerPhaseProd MCTriggerPhaseProd.h MCTriggerPhaseProd/MCTriggerPhaseProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 31 16:43:50 EST 2001
// $Id: MCTriggerPhaseProd.h,v 1.2 2001/02/07 02:49:09 lkg Exp $
//
// Revision history
//
// $Log: MCTriggerPhaseProd.h,v $
// Revision 1.2  2001/02/07 02:49:09  lkg
// Added a parameter to allow a specification of a width for gaussian smearing
// of the trigger phase.  Defaults to 0, in which case smearing code is
// short circuited.  Conveniently cures stupid compilation problem at the
// same time.
//
// Revision 1.1.1.1  2001/02/05 16:17:26  lkg
// imported MCTriggerPhaseProd source
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "CommandPattern/Parameter.h"
#include "HistogramInterface/HistogramPackage.h"

// forward declarations

class MCTriggerPhaseProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      MCTriggerPhaseProd( void );                      // anal1 
      virtual ~MCTriggerPhaseProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------
      double triggerPhaseWidth() const {
	 return m_triggerPhaseWidth.value();
      }

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      MCTriggerPhaseProd( const MCTriggerPhaseProd& );

      // ------------ assignment operator(s) ----------------------
      const MCTriggerPhaseProd& operator=( const MCTriggerPhaseProd& );

      // ------------ private member functions --------------------
      ProxyBase* makeMCTriggerPhaseProxy( void );

      // ------------ data members --------------------------------
      Parameter< double > m_triggerPhaseWidth;

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* MCTRIGGERPHASEPROD_MCTRIGGERPHASEPROD_H */
