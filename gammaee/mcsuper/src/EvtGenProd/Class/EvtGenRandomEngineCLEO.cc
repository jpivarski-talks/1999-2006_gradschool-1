//--------------------------------------------------------------------------
//
// Author: Anders Ryd
// Created: Nov 5, 2003
//
// Provides the interface between CLEOc software and EvtGen for 
// generation of random numbers.
//
//------------------------------------------------------------------------

#include "Experiment/Experiment.h"
#include "RandomModule/RandomGenerator.h"
#include "EvtGenProd/EvtGenRandomEngineCLEO.h"

double EvtGenRandomEngineCLEO::random(){

  return RandomGenerator::instance().flat();
  
}



