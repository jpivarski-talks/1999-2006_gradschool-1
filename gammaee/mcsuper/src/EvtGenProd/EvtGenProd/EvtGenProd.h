// -*- C++ -*-
#if !defined(EVTGENPROD_EVTGENPROD_H)
#define EVTGENPROD_EVTGENPROD_H
//
// Package:     <EvtGenProd>
// Module:      EvtGenProd
//
/**\class EvtGenProd EvtGenProd.h EvtGenProd/EvtGenProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Anders Ryd
// Created:     Sat Sep 13 17:58:54 EDT 2003
// $Id: EvtGenProd.h,v 1.2 2003/10/14 20:32:43 ryd Exp $
//
// Revision history
//
// $Log: EvtGenProd.h,v $
// Revision 1.2  2003/10/14 20:32:43  ryd
// Switch to jetset; bug fixes for initial quarks
//
// Revision 1.1.1.1  2003/10/07 02:48:56  ryd
// imported EvtGenProd sources
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"
#include "EvtGenProd/EvtGenProxy.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class EvtGenProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      EvtGenProd( void );                      // anal1 
      virtual ~EvtGenProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      ProxyBase* makeEvtGenProxy() {
	return new EvtGenProxy(m_decayfile.value(),m_udecayfile.value(),
			       m_evtpdl.value());
      }


      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      EvtGenProd( const EvtGenProd& );

      Parameter<string> m_decayfile;
      Parameter<string> m_udecayfile;
      Parameter<string> m_evtpdl;


      // ------------ assignment operator(s) ----------------------
      const EvtGenProd& operator=( const EvtGenProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* EVTGENPROD_EVTGENPROD_H */


