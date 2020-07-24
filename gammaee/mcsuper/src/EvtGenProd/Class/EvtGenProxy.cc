// -*- C++ -*-
//
// Package:     <package>
// Module:      EvtGenProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Anders Ryd
// Created:     Sun Sep 14 16:51:23 EDT 2003
// $Id: EvtGenProxy.cc,v 1.6 2004/09/02 03:12:07 ryd Exp $
//
// Revision history
//
// $Log: EvtGenProxy.cc,v $
// Revision 1.6  2004/09/02 03:12:07  ryd
// Fix event time
//
// Revision 1.5  2003/11/24 17:54:02  ryd
// Use MC namespace for PDG id's
//
// Revision 1.4  2003/11/12 20:50:37  ryd
// Fix problem with vertex position and units
//
// Revision 1.3  2003/10/14 20:32:40  ryd
// Switch to jetset; bug fixes for initial quarks
//
// Revision 1.2  2003/10/13 15:55:46  ryd
// Silence some debug messages
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
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "EvtGenProd/EvtGenProxy.h"
#include "EvtGenProd/EvtGenGenerator.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD
#include "MCBeam/MCBeamParticles.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCParticleProperty/pdgNum.h"

#if 0
#include "TrackDelivery/TDKinematicPionFit.h" 
#endif

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
static const char* const kFacilityString = "package.EvtGenProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EvtGenProxy.cc,v 1.6 2004/09/02 03:12:07 ryd Exp $";
static const char* const kTagString = "$Name:  $";

static const Integer kVirtualPhotonQQId = 0;

//
// static data member definitions
//

//
// constructors and destructor
//
EvtGenProxy::EvtGenProxy(const string& decayfile, const string& udecayfile,
			 const string& evtpdl)
   : m_EvtGenMCDecayTree( 0 )
{
  
  //cout << "RYD:EvtGenProxy::EvtGenProxy"<<endl;

  //EvtGen* aEvtGen=new EvtGen("/home/ryd/CLEOc/src/EvtGenProd/DECAY.DEC",
  //			     "/home/ryd/CLEOc/src/EvtGenProd/evt.pdl");

  m_EvtGenGenerator = new EvtGenGenerator(decayfile,udecayfile,evtpdl);
  
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &EvtGenProxy::boundMethod, Stream::kBeginRun );

}

// EvtGenProxy::EvtGenProxy( const EvtGenProxy& iproxy )
// {
//   *this = iproxy;
// }

EvtGenProxy::~EvtGenProxy()
{
  //cout << "RYD:EvtGenProxy::~EvtGenProxy"<<endl;
  
 delete m_EvtGenMCDecayTree ;
}

//
// assignment operators
//
// const EvtGenProxy& EvtGenProxy::operator=( const EvtGenProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
EvtGenProxy::invalidateCache()
{
   delete m_EvtGenMCDecayTree ;
   m_EvtGenMCDecayTree = 0 ;
}

const EvtGenProxy::value_type*
EvtGenProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_EvtGenMCDecayTree );

   FAItem<MCEventVertex> eventVertex;
   extract(iRecord, eventVertex);

   //cout << "RYD: event time:"<<eventVertex->t()<<endl;

   assert(eventVertex.valid());

   FAItem<MCBeamParticles> beamParticles;
   extract(iRecord, beamParticles);

   const HepLorentzVector& totalMomentum = beamParticles->totalMomentum();
   const HepPoint3D productionPoint = beamParticles->electron().position();

   FAItem<MCParticlePropertyStore> properties;
   extract(iRecord.frame().record(Stream::kPhysics),
	   properties,"UserMCParticleProperties");
   const MCParticleProperty& vPhotonProperty = properties->getUsingPDGId(MC::k_vpho);

   MCParticle* vPhoton = new MCParticle(vPhotonProperty,
					totalMomentum,
					productionPoint);

   //if an exception is thrown during this function, p_EvtGen will
   // automatically delete the object it is refering to
   auto_ptr<MCDecayTree> p_EvtGenMCDecayTree(new MCDecayTree(vPhoton,true));

   m_EvtGenGenerator->decayParticles(vPhoton,*eventVertex,properties);
   
   report( DEBUG, kFacilityString) << *p_EvtGenMCDecayTree <<endl;


   //Since no exception happened, tell p_EvtGenMCDecayTree to give its pointer to
   // m_EvtGenMCDecayTree
   return ( m_EvtGenMCDecayTree = p_EvtGenMCDecayTree.release() ) ;
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//

//void
//EvtGenProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< MCDecayTree >;

PROXY_BIND_METHOD( EvtGenProxy )
//-----------------------------------------------





































