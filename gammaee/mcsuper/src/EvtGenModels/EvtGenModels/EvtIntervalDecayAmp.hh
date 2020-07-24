//-----------------------------------------------------------------------
// File and Version Information: 
//      $Id: EvtIntervalDecayAmp.hh,v 1.1.1.1 2003/10/07 02:48:06 ryd Exp $
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

// Decay model that uses the "amplitude on an interval"
// templatization

#ifndef EVT_INTERVAL_DECAY_AMP
#define EVT_INTERVAL_DECAY_AMP

#define VERBOSE true
#include <iostream>
#include <vector>
#include <string>
#include "EvtGenBase/EvtDecayAmp.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtMacros.hh"
#include "EvtGenBase/EvtRandDist.hh"
#include "EvtGenBase/EvtPdf.hh"
#include "EvtGenBase/EvtAmpFactory.hh"
#include "EvtGenBase/EvtMultiChannelParser.hh"
#include "EvtGenBase/EvtAmpPdf.hh"
#include "EvtGenBase/EvtPoleCompPdfSum.hh"
#include "EvtGenBase/EvtCPUtil.hh"
#include "EvtGenBase/EvtPDL.hh"

template <class Interval>
class EvtIntervalDecayAmp : public  EvtDecayAmp {

public:
  
  EvtIntervalDecayAmp()
    : _probMax(0.), _nScan(0), _fact(0)
  {}

  EvtIntervalDecayAmp(const EvtIntervalDecayAmp<Interval>& other)
    : _probMax(other._probMax), _nScan(other._nScan),
      COPY_PTR(_fact)
  {}

  virtual ~EvtIntervalDecayAmp()
  {
    delete _fact;
  }


  // Initialize model

  virtual void init()
  {
    // Collect model parameters and parse them

    vector<std::string> args;
    int i;
    for(i=0;i<getNArg();i++) args.push_back(getArgStr(i));
    EvtMultiChannelParser parser;
    parser.parse(args);

    // Create factory and interval

    if(VERBOSE) report(INFO,"EvtGen") << "Create factory and interval" << std::endl;
    _fact = createFactory(parser);
    
    
    // Maximum PDF value over the Dalitz plot can be specified, or a scan 
    // can be performed.
    
    _probMax = parser.pdfMax();
    _nScan = parser.nScan();
    if(VERBOSE) report(INFO,"EvtGen") << "Pdf maximum " << _probMax << std::endl;
    if(VERBOSE) report(INFO,"EvtGen") << "Scan number " << _nScan << std::endl;    
  }
  
    
  virtual void initProbMax()
  {
    if(0 == _nScan) {
      
      if(_probMax > 0) setProbMax(_probMax);
      else assert(0);
    }
    else {
      
      double factor = 1.2; // increase maximum probability by 20%
      _probMax = factor * _fact->findMax(_nScan).value();
      setProbMax(_probMax);
    }
  }
      
  virtual void decay(EvtParticle *p)
  {
    // Set things up in most general way
    
    static EvtId B0=EvtPDL::getId("B0");
    static EvtId B0B=EvtPDL::getId("anti-B0");
    double t;
    EvtId other_b;  
    EvtComplex ampl(0.,0.);
    
    // Sample using pole-compensator pdf
    
    typename Interval::point_type x = _fact->generate();
    
    if(_fact->isCPModel()) {
      
      EvtCPUtil::OtherB(p,t,other_b);
      EvtComplex A = _fact->amp(x);
      EvtComplex Abar = _fact->ampConj(x);
      double dm = _fact->dm();
      
      if (other_b==B0B) ampl=A*cos(dm*t/(2*EvtConst::c))+Abar*sin(dm*t/(2*EvtConst::c));
      if (other_b==B0) ampl=A*cos(dm*t/(2*EvtConst::c))-Abar*sin(dm*t/(2*EvtConst::c));
    }
    else {
      
      ampl = _fact->amp(x);
    }
    
    // Pole-compensate
    
    double comp = sqrt(_fact->pc(x));
    assert(comp > 0);
    vertex(ampl/comp);
  
    // Now generate random angles, rotate and setup 
    // the daughters
    
    std::vector<EvtVector4R> v = initDaughters(x);
    
    int N = p->getNDaug();  
    if(v.size() != N) {
      
      report(INFO,"EvtGen") << "Number of daughters " << N << std::endl;
      report(INFO,"EvtGen") << "Momentum vector size " << v.size() << std::endl;
      assert(0);
    }
    
    int i;
    for(i=0;i<N;i++){
      
      p->getDaug(i)->init(getDaugs()[i],v[i]);
    }    
  }



  virtual EvtAmpFactory<Interval>* createFactory(const EvtMultiChannelParser& parser) = 0;
  virtual std::vector<EvtVector4R> initDaughters(const typename Interval::point_type& p) const = 0;

protected:

  double _probMax;          // Maximum probability
  int _nScan;               // Number of points for max prob DP scan

  EvtAmpFactory<Interval>*  _fact; // factory
};


#endif




