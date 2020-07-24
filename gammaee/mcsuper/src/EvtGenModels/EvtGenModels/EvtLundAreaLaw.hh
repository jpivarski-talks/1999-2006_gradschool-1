//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/COPYRIGHT
//      Copyright (C) 1998,2004       Caltech, UCSB, Cornell
//
// Module: EvtGen/EvtLundAreaLaw.hh
//
// Description:
//
// Modification history:
//
//    RYD     Jan 31, 2004         Module created
//
//------------------------------------------------------------------------

#ifndef EVTLUNDAREALAW_HH
#define EVTLUNDAREALAW_HH

#include "EvtGenBase/EvtDecayIncoherent.hh"

class EvtParticle;

class EvtLundAreaLaw:public  EvtDecayIncoherent  {

public:
  
  EvtLundAreaLaw() {}
  virtual ~EvtLundAreaLaw();
  
  void getName(std::string& name);
  EvtDecayBase* clone();

  std::string commandName();
  void command(std::string cmd);

  void init();
  void initProbMax();

  void decay(EvtParticle *p); 

};

#endif
