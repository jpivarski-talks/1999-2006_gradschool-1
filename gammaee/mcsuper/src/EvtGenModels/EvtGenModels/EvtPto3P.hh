//-----------------------------------------------------------------------
// File and Version Information: 
//      $Id: EvtPto3P.hh,v 1.1.1.1 2003/10/07 02:48:08 ryd Exp $
// 
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations. If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information:
//      Copyright (C) 1998 Caltech, UCSB
//
// Module creator:
//      Alexei Dvoretskii, Caltech, 2001-2002.
//-----------------------------------------------------------------------

#ifndef EVT_PTO3P_HH
#define EVT_PTO3P_HH

#include <vector>
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenModels/EvtIntervalDecayAmp.hh"
#include "EvtGenBase/EvtDalitz2D.hh"


class EvtPto3P : public  EvtIntervalDecayAmp<EvtDalitz2D> {

public:
  
  EvtPto3P() {}
  virtual ~EvtPto3P() {}
  void getName(std::string& model_name) { model_name="PTO3P"; }
  EvtDecayBase* clone() { return new EvtPto3P(); } 
  
  
  virtual EvtAmpFactory<EvtDalitz2D>* createFactory(const EvtMultiChannelParser& parser);
  virtual std::vector<EvtVector4R> initDaughters(const EvtDalitzPoint& p) const;

  EvtDalitzPlot dp();

};

#endif

