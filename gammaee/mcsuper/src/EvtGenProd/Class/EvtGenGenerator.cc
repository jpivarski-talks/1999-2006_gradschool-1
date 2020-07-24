// -*- C++ -*-
//
// Package:     EvtGenProd
// Module:      EvtGenGenerator
// 
// Description: Implementation of EvtGen interface
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Anders Ryd
// Created:     Sun Sep 14 16:51:23 EDT 2003
// $Id: EvtGenGenerator.cc,v 1.7 2004/09/02 03:12:07 ryd Exp $
//
// Revision history
//
// $Log: EvtGenGenerator.cc,v $
// Revision 1.7  2004/09/02 03:12:07  ryd
// Fix event time
//
// Revision 1.6  2003/11/12 20:50:37  ryd
// Fix problem with vertex position and units
//
// Revision 1.5  2003/11/06 18:22:18  ryd
// Use correct random number and spin density of initial vpho
//
// Revision 1.4  2003/10/14 20:32:40  ryd
// Switch to jetset; bug fixes for initial quarks
//
// Revision 1.3  2003/10/13 15:55:45  ryd
// Silence some debug messages
//
// Revision 1.2  2003/10/13 04:54:10  ryd
// Fixes for linking and unknown particles
//
// Revision 1.1.1.1  2003/10/07 02:48:57  ryd
// imported EvtGenProd sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
//#include "Experiment/report.h"

//#include "DataHandler/Record.h"
//#include "DataHandler/Frame.h"
//#include "FrameAccess/extract.h"           
//#include "FrameAccess/FATable.h"

#include "EvtGenProd/EvtGen.hh"
#include "EvtGenProd/EvtGenProxy.h"
#include "EvtGenProd/EvtGenGenerator.h"
#include "EvtGenProd/EvtGenRandomEngineCLEO.h"
#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtIdSet.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtDecayTable.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "CLHEP/Geometry/Point3D.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayTree/interaction_types.h"
//#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD
//#include "MCBeam/MCBeamParticles.h"
//#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "EvtGenProd.EvtGenGenerator" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EvtGenGenerator.cc,v 1.7 2004/09/02 03:12:07 ryd Exp $";
static const char* const kTagString = "$Name:  $";

static const Integer kVirtualPhotonQQId = 0;

//
// static data member definitions
//

//
// constructors and destructor
//
EvtGenGenerator::EvtGenGenerator(const string& decayfile,
				 const string& udecayfile,
				 const string& evtpdl):
  m_EvtGen(0)
{
 
  //bind 'auxilliary' functions that you want called when a
  // new Record on the particular Stream appears
  //bind( &EvtGenProxy::boundMethod, Stream::kBeginRun );

  static EvtGenRandomEngineCLEO randomEngine;

  m_EvtGen=new EvtGen(decayfile.c_str(),
		      evtpdl.c_str(),&randomEngine);

  if (udecayfile!="") {
    EvtDecayTable::readDecayFile(udecayfile.c_str());
  }

}

EvtGenGenerator::~EvtGenGenerator()
{

  delete m_EvtGen;
  
}

void EvtGenGenerator::makeTree(MCParticle* mcP,EvtParticle* evtP,
			       FAItem<MCParticlePropertyStore>& mcPPS,
			       const HepPoint3D& interactionPoint, double t){

  if (evtP->getNDaug()==0) return;

  if (EvtPDL::getctau(evtP->getId())>10.0) {
    //std::cout << "Will not use decay of: "<<EvtPDL::name(evtP->getId())<<std::endl;
    return;
  }

  int idaug=0;
  EvtVector4R pos4=evtP->getDaug(0)->get4Pos();
  EvtVector4R p4=evtP->getP4Lab();
  //MCVertex* mcV = MCVertex::newVertex( kiDecay,mcP,
  //                   HepPoint3D(pos4.get(1),pos4.get(2),pos4.get(3)), 
  //                   pos4.get(0),
  //                   HepLorentzVector(p4.get(1),p4.get(2),p4.get(3),p4.get(0))
  //			      );

  MCVertex* mcV = MCVertex::newVertex( MCDecayMode::unknown(),mcP,
                     HepPoint3D(pos4.get(1)/1000.0,pos4.get(2)/1000.0,
				pos4.get(3)/1000.0)+interactionPoint, 
                     pos4.get(0)*1.0e12/EvtConst::c+t,
                     HepLorentzVector(p4.get(1),p4.get(2),p4.get(3),p4.get(0))
				      );


  //std::cout << "ANDERS PARENT:"<<EvtPDL::name(evtP->getId())<<std::endl;

  STL_VECTOR(MCParticle*) pList;
  for(idaug=0;idaug<evtP->getNDaug();idaug++){


    EvtParticle* daug=evtP->getDaug(idaug);

    static EvtIdSet quarks("u","d","s","c","b",
			   "anti-u","anti-d","anti-s","anti-c","anti-b");

    if (quarks.contains(daug->getId())) continue;

    EvtVector4R p4daug=daug->getP4Lab();
    HepLorentzVector p4(p4daug.get(1),p4daug.get(2),
			p4daug.get(3),p4daug.get(0));
    MCParticle* mcDaug=new MCParticle(mcPPS->getUsingPDGId(EvtPDL::getStdHep(daug->getId())),p4,HepPoint3D());

    //std::cout << "ANDERS DAUG:"<<EvtPDL::name(daug->getId())<<" "<<mcPPS->getUsingPDGId(EvtPDL::getStdHep(daug->getId())).name()<<std::endl;


    pList.push_back(mcDaug);
    makeTree(mcDaug,daug,mcPPS,interactionPoint,t);
  }

  mcV->setChildren(pList);

}

void EvtGenGenerator::decayParticles(MCParticle* vPhoton, MCEventVertex eventVertex, FAItem<MCParticlePropertyStore>& mcPPS){


  //hack!!!!
  EvtId id(EvtPDL::getId("vpho"));
  EvtVector4R p4(vPhoton->energy(),vPhoton->px(),vPhoton->py(),vPhoton->pz());

  HepPoint3D interactionPoint=eventVertex;

  EvtParticle *p=EvtParticleFactory::particleFactory(id,p4);

  p->setVectorSpinDensity();

  m_EvtGen->generateDecay(p);

  makeTree(vPhoton,p,mcPPS,interactionPoint,eventVertex.t());

  p->deleteTree();

  return;

}


//
// const member functions
//

//
// static member functions
//













