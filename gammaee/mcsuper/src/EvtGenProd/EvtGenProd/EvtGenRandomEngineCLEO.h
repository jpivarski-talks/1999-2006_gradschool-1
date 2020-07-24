//--------------------------------------------------------------------------
//
// Author: Anders Ryd
// Created: Nov 5, 2003
//
// Provides the interface between CLEOc software and EvtGen for 
// generation of random numbers.
//
//------------------------------------------------------------------------

#ifndef EVTGENRANDOMENGINECLEO_HH
#define EVTGENRANDOMENGINECLEO_HH

#include "EvtGenBase/EvtRandomEngine.hh"

class EvtGenRandomEngineCLEO: public EvtRandomEngine{

public:

  virtual double random();
  
private:

};



#endif

