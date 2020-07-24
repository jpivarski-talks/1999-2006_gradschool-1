// -*- C++ -*-
#if !defined(EVENTVERTEXPROD_EVENTVERTEXPROD_H)
#define EVENTVERTEXPROD_EVENTVERTEXPROD_H
//
// Package:     <EventVertexProd>
// Module:      EventVertexProd
//
/**\class EventVertexProd EventVertexProd.h EventVertexProd/EventVertexProd.h
 
 Description:   Producer to generate event vertex

 Usage:
    <usage>

*/
//
// Author:      Roy A. Briere, Michael Earl Watkins
// Created:     Mon Mar 18 22:54:05 EST 2002
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
#include "EventVertexProd/EventVertexHolder.h"
#include "EventVertexProd/EventVertexPrivateProxy.h"
// forward declarations

class EventVertexProd : public Producer
{
  // ------------ friend classses and functions ---------------

 public:
  // ------------ constants, enums and typedefs ---------------
      
  // ------------ Constructors and destructor -----------------
      EventVertexProd( void );                      // anal1 
      virtual ~EventVertexProd();                   // anal5 

  // ------------ member functions ----------------------------
      ProxyBase* makeEventVertexPrivateProxy();
      ProxyBase* makeEventVertexProxy();     
      ProxyBase* makeEventVertexInfoProxy();
  // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

  // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

  // ------------ const member functions ----------------------
      inline EventVertexHolder* eventVertexHolder();
  // ------------ static member functions ---------------------

 protected:
  // ------------ protected member functions ------------------

  // ------------ protected const member functions ------------

 private:
  // ------------ Constructors and destructor -----------------
      EventVertexProd( const EventVertexProd& );
      
  // ------------ assignment operator(s) ----------------------
      const EventVertexProd& operator=( const EventVertexProd& );

  // ------------ private member functions --------------------

  // ------------ private const member functions --------------

  // ------------ data members --------------------------------
      EventVertexHolder m_eventVertexHolder;


      // ------------ static data members -------------------------

};
// inline function definitions
inline EventVertexHolder* EventVertexProd::eventVertexHolder()
{
  return &m_eventVertexHolder;
}

#endif /* EVENTVERTEXPROD_EVENTVERTEXPROD_H */
