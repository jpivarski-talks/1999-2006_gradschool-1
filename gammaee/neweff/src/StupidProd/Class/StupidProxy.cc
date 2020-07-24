// -*- C++ -*-
//
// Package:     <StupidProd>
// Module:      StupidProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Mar 22 01:38:43 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "StupidProd/StupidProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "TriggerData/TriggerData.h"

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
static const char* const kFacilityString = "StupidProd.StupidProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxyone.cc,v 1.12 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
StupidProxy::StupidProxy()
   : m_Stupid( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &StupidProxy::boundMethod, Stream::kBeginRun );
}

// StupidProxy::StupidProxy( const StupidProxy& iproxy )
// {
//   *this = iproxy;
// }

StupidProxy::~StupidProxy()
{
   delete m_Stupid ;
}

//
// assignment operators
//
// const StupidProxy& StupidProxy::operator=( const StupidProxy& iproxy )
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
StupidProxy::invalidateCache()
{
   delete m_Stupid ;
   m_Stupid = 0 ;
}

const StupidProxy::value_type*
StupidProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_Stupid );

   //if an exception is thrown during this function, p_Stupid will
   // automatically delete the object it is refering to
   auto_ptr<Stupid> p_Stupid;

   FAItem<TriggerData> trig;
   extract(iRecord, trig);

   p_Stupid.reset(new Stupid(trig->getAxTrackCount(0),
			     trig->getAxTrackCount(1),
			     trig->getAxTrackCount(2),
			     trig->getAxTrackCount(3)));


#if 0
// ---------------- Sample implementation -------------------
   // ---------- create the new object --------------------

   // first get ahold of 
   FATable< TDKinematicPionFit > pions ; 
   extract( iRecord, pions ); 


   HepVector3D varStupid; 

   // loop over pions with new STL-style iterator for loop 
   FATable< TDKinematicPionFit >::const_iterator endIter = pions.end(); 
   for( FATable< TDKinematicPionFit >::const_iterator pion = pions.begin();
        pion != endIter; 
        ++pion ) 
   { 
      varStupid += (*pion).momentum(); 
   } 

   //have p_Stupid hold onto the new object
   p_Stupid.reset( new Stupid( varStupid ) );
#endif
   
   //Since no exception happened, tell p_Stupid to give its pointer to
   // m_Stupid
   return ( m_Stupid = p_Stupid.release() ) ;
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
//StupidProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< Stupid >;

PROXY_BIND_METHOD( StupidProxy )
//-----------------------------------------------

