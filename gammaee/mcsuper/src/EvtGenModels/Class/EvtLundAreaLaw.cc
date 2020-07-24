//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/COPYRIGHT
//      Copyright (C) 2004      Caltech, UCSB, Cornell
//
// Module: EvtLundAreaLaw.cc
//
// Description: Routine to generate e+e- --> q\barq  via LundAreaLaw 
//              Based on EvtUclaII
//
// Modification history:
//
//    Ryd     Jan 31, 2004        Module created
//
//------------------------------------------------------------------------
// 
#include <stdlib.h>
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtDecayTable.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenModels/EvtLundAreaLaw.hh"
#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtReport.hh"
#include <string>
#include <iostream.h>

extern "C" {
  extern void lundarealawcont_(double *,int *,int *,int *,
		       double *,double *,double *,double *);
}

extern "C" {
  extern void cclugive_(const char *cnfgstr,int length);
}


EvtLundAreaLaw::~EvtLundAreaLaw() {}

void EvtLundAreaLaw::getName(std::string& model_name){

  model_name="LUNDAREALAW";     

}

EvtDecayBase* EvtLundAreaLaw::clone(){

  return new EvtLundAreaLaw;

}


std::string EvtLundAreaLaw::commandName(){

  return std::string("LundAreaLawPar");
  
}


void EvtLundAreaLaw::command(std::string cmd){

  cclugive_(cmd.c_str(),strlen(cmd.c_str()));

}





void EvtLundAreaLaw::init(){

  // check that there are 1 argument

  checkNArg(1);

}


void EvtLundAreaLaw::initProbMax(){

  noProbMax();

}


void EvtLundAreaLaw::decay( EvtParticle *p){

  EvtParticle *pdaug[MAX_DAUG];
  EvtVector4R p4[100];
  
  double energy=p->mass();

  int flavor;

  int i,more;
  int ndaugjs;
  int kf[100];
  EvtId id[100];
  int type[MAX_DAUG]; 

  flavor=(int)getArg(0);

  double px[100],py[100],pz[100],e[100];

  if ( p->getNDaug() != 0 ) { return;}
  do{

    lundarealawcont_(&energy,&flavor,&ndaugjs,kf,px,py,pz,e);

    for(i=0;i<ndaugjs;i++){

      id[i]=EvtPDL::evtIdFromStdHep(kf[i]);

      type[i]=EvtPDL::getSpinType(id[i]);

      // have to protect against negative mass^2 for massless particles
      // i.e. neutrinos and photons.
      // this is uggly but I need to fix it right now....

      if (px[i]*px[i]+py[i]*py[i]+pz[i]*pz[i]>=e[i]*e[i]){

        e[i]=sqrt(px[i]*px[i]+py[i]*py[i]+pz[i]*pz[i])+0.0000000000001;

      }

     //report(INFO,"EvtGen")<< i<<" "<<kf[i]<<" "<<px[i]<<" "<<py[i]<<" "<<pz[i]<<endl;
 
     p4[i].set(e[i],px[i],py[i],pz[i]);

    }

    int channel=EvtDecayTable::inChannelList(p->getId(),ndaugjs,id);

    more=((channel!=-1)&&(channel!=p->getChannel()));


  }while(more);

  p->makeDaughters(ndaugjs,id);

  for(i=0;i<ndaugjs;i++){
    p->getDaug(i)->init( id[i], p4[i] );
  }
  return ;
}

