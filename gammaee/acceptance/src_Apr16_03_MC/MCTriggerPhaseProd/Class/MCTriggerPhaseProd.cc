// -*- C++ -*-
//
// Package:     <MCTriggerPhaseProd>
// Module:      MCTriggerPhaseProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 31 16:43:50 EST 2001
// $Id: MCTriggerPhaseProd.cc,v 1.2 2001/02/07 02:45:29 lkg Exp $
//
// Revision history
//
// $Log: MCTriggerPhaseProd.cc,v $
// Revision 1.2  2001/02/07 02:45:29  lkg
// Added a parameter to allow a specification of a width for gaussian smearing
// of the trigger phase.  Defaults to 0, in which case smearing code is
// short circuited.  Conveniently cures stupid compilation problem at the
// same time.
//
// Revision 1.1.1.1  2001/02/05 16:17:26  lkg
// imported MCTriggerPhaseProd source
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MCTriggerPhaseProd/MCTriggerPhaseProd.h"
#include "MCTriggerPhaseProd/MCTriggerPhaseProxy.h"
#include "MCTriggerPhaseProd/InvalidPhaseWidthException.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "MCTriggerPhaseProd.MCTriggerPhaseProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCTriggerPhaseProd.cc,v 1.2 2001/02/07 02:45:29 lkg Exp $";
static const char* const kTagString = "$Name: v01_02_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCTriggerPhaseProd::MCTriggerPhaseProd( void )               // anal1
   : Producer( "MCTriggerPhaseProd" ),
     m_triggerPhaseWidth( "triggerPhaseWidth", this, 0 ) 
{
   m_triggerPhaseWidth.setHelpString(
      "Set the gaussian width by which the trigger phase will be smeared."
      " The default is no smearing." );
   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< MCTriggerPhaseProd, MCTriggerPhaseProxy >(
	 *this,
	 &MCTriggerPhaseProd:: makeMCTriggerPhaseProxy ), 
      UsageTag() );    // or UsageTag( "MyUsage" )
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< MCTriggerPhaseProd, MCTriggerPhaseProxy >;

ProxyBase*
MCTriggerPhaseProd::makeMCTriggerPhaseProxy()
{ 
   return new MCTriggerPhaseProxy( this );
}

MCTriggerPhaseProd::~MCTriggerPhaseProd()                    // anal5
{}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
MCTriggerPhaseProd::init( void )          // anal1 "Interactive"
{
   // check the trigger phase width and make sure it is valid
   if ( m_triggerPhaseWidth.value() < 0 ) {
      throw InvalidPhaseWidthException( m_triggerPhaseWidth.value() );
   }
}

// -------------------- terminate method ----------------------------
void
MCTriggerPhaseProd::terminate( void )     // anal5 "Interactive"
{}

// ---------------- standard place to book histograms ---------------
void
MCTriggerPhaseProd::hist_book( HIHistoManager& )
{}

//
// const member functions
//

//
// static member functions
//
