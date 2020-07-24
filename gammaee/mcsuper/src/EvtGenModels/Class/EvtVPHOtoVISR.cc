//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/COPYRIGHT
//      Copyright (C) 2004      Cornell
//
// Module: EvtVPHOtoVISR.cc
//
// Description: Routine to decay vpho -> vector ISR photon
//
// Modification history:
//
//    Ryd       March 20, 2004       Module created
//
//------------------------------------------------------------------------
// 
#include <stdlib.h>
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtGenKine.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtVector4C.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenModels/EvtVPHOtoVISR.hh"
#include <string>

EvtVPHOtoVISR::~EvtVPHOtoVISR() {}

void EvtVPHOtoVISR::getName(std::string& model_name){

  model_name="VPHOTOVISR"; 
    
}


EvtDecayBase* EvtVPHOtoVISR::clone(){

  return new EvtVPHOtoVISR;

}

void EvtVPHOtoVISR::init(){

  // check that there are 0 or 1 arguments
  checkNArg(0,1);

  // check that there are 2 daughters
  checkNDaug(2);

  // check the parent and daughter spins
  checkSpinParent(EvtSpinType::VECTOR);
  checkSpinDaughter(0,EvtSpinType::VECTOR);
  checkSpinDaughter(1,EvtSpinType::PHOTON);
}

void EvtVPHOtoVISR::initProbMax() {

  //setProbMax(100000.0);

}      

void EvtVPHOtoVISR::decay( EvtParticle *p){

  //take photon along z-axis, either forward or backward.
  //Implement this as generating the photon momentum along 
  //the z-axis uniformly 

  double w=p->mass();
  double s=w*w;

  double L=2.0*log(w/0.000511);
  double alpha=1/137.0;
  double beta=(L-1)*2.0*alpha/EvtConst::pi;

  //Hardcoded threshold mass of the resonance decay.
  double md=1.87;

  double pgmax=(s-4.0*md*md)/(4.0*md);

  double pgz=0.99*pgmax*exp(log(EvtRandom::Flat(1.0))/beta);

  if (EvtRandom::Flat(1.0)<0.5) pgz=-pgz;

  double k=fabs(pgz);

  EvtVector4R p4g(k,0.0,0.0,pgz);

  EvtVector4R p4res=p->getP4Restframe()-p4g;

  double mres=p4res.mass();

  double ed=mres/2.0;

  double pd=sqrt(ed*ed-md*md);

  //std::cout << "k, mres, w, md, ed, pd:"<<k<<" "<<mres<<" "<<w<<" "<<md<<" "<<ed<<" "<<pd<<std::endl;

  p->getDaug(0)->init(getDaug(0),p4res);
  p->getDaug(1)->init(getDaug(1),p4g);


  double sigma=beta*pow(2/w,beta)*(1+alpha*(1.5*L-2.0+EvtConst::pi*EvtConst::pi/3.0)/EvtConst::pi);

  double power=3.0;

  if (getNArg()==1) power=getArg(0);

  double m=EvtPDL::getMeanMass(p->getId());
  double ww=EvtPDL::getWidth(p->getId());

  sigma*=pow(pd,power)/((mres*mres-m*m)*(mres*mres-m*m)+mres*mres*ww*ww);

  static double sigmax=sigma;

  if (sigma>sigmax){
    sigmax=sigma;
  }



  static int count=0;

  count++;

  //if (count%10000==0){
  //  std::cout << "sigma :"<<sigma<<std::endl;
  //  std::cout << "sigmax:"<<sigmax<<std::endl;
  //}

  double norm=sqrt(sigma);

  EvtParticle* d=p->getDaug(0);

  
  vertex(0,0,0,norm*p->eps(0)*p->epsParent(0).conj());
  vertex(1,0,0,norm*p->eps(1)*p->epsParent(0).conj());
  vertex(2,0,0,norm*p->eps(2)*p->epsParent(0).conj());

  vertex(0,1,0,norm*p->eps(0)*p->epsParent(1).conj());
  vertex(1,1,0,norm*p->eps(1)*p->epsParent(1).conj());
  vertex(2,1,0,norm*p->eps(2)*p->epsParent(1).conj());

  vertex(0,2,0,norm*p->eps(0)*p->epsParent(2).conj());
  vertex(1,2,0,norm*p->eps(1)*p->epsParent(2).conj());
  vertex(2,2,0,norm*p->eps(2)*p->epsParent(2).conj());

  vertex(0,0,1,norm*p->eps(0)*p->epsParent(0).conj());
  vertex(1,0,1,norm*p->eps(1)*p->epsParent(0).conj());
  vertex(2,0,1,norm*p->eps(2)*p->epsParent(0).conj());

  vertex(0,1,1,norm*p->eps(0)*p->epsParent(1).conj());
  vertex(1,1,1,norm*p->eps(1)*p->epsParent(1).conj());
  vertex(2,1,1,norm*p->eps(2)*p->epsParent(1).conj());

  vertex(0,2,1,norm*p->eps(0)*p->epsParent(2).conj());
  vertex(1,2,1,norm*p->eps(1)*p->epsParent(2).conj());
  vertex(2,2,1,norm*p->eps(2)*p->epsParent(2).conj());

  return;
}

