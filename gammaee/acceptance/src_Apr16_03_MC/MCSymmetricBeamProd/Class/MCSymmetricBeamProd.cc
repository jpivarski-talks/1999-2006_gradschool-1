// -*- C++ -*-
//
// Package:     <MCSymmetricBeamProd>
// Module:      MCSymmetricBeamProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Fri Jan 19 15:30:52 EST 2001
// $Id: MCSymmetricBeamProd.cc,v 1.3 2002/03/26 17:28:53 bkh Exp $
//
// Revision history
//
// $Log: MCSymmetricBeamProd.cc,v $
// Revision 1.3  2002/03/26 17:28:53  bkh
// Use BeamEnergy object not CesrBeamEnergy and remove related parameters
//
// Revision 1.2  2001/03/01 19:55:58  lkg
// access beam energy from and provide proxy for startrun rather than beginrun
//
// Revision 1.1.1.1  2001/01/31 21:10:49  lkg
// imported MCSymmetricBeamProd source
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MCSymmetricBeamProd/MCSymmetricBeamProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

#include "MCSymmetricBeamProd/MCBeamParametersProxy.h"

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
static const char* const kFacilityString = "MCSymmetricBeamProd.MCSymmetricBeamProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCSymmetricBeamProd.cc,v 1.3 2002/03/26 17:28:53 bkh Exp $";
static const char* const kTagString = "$Name: v01_02_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCSymmetricBeamProd::MCSymmetricBeamProd( void )               // anal1
   : MCBeamProdBase( "MCSymmetricBeamProd" ),
     m_tenGevTotalEnergySpread( "totalEnergySpreadAt10GeV", this, 0.0045 )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ----- register proxy factories ------------------
   // startRun stream proxies
   registerProxyFactory( 
      Stream::kStartRun, 
      new ProxyFactoryFunction< MCSymmetricBeamProd, MCBeamParametersProxy >( 
	 *this, &MCSymmetricBeamProd::makeMCBeamParametersProxy ),
      UsageTag() );
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< MCSymmetricBeamProd, MCBeamParametersProxy >;

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)
ProxyBase*
MCSymmetricBeamProd::makeMCBeamParametersProxy()
{ 
   return new MCBeamParametersProxy( this );
}

// MCSymmetricBeamProd::MCSymmetricBeamProd( const MCSymmetricBeamProd& iMCSymmetricBeamProd )
// {
//    *this = iMCSymmetricBeamProd;
// }

MCSymmetricBeamProd::~MCSymmetricBeamProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const MCSymmetricBeamProd& MCSymmetricBeamProd::operator=( const MCSymmetricBeamProd& iMCSymmetricBeamProd )
// {
//   if( this != &iMCSymmetricBeamProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iMCSymmetricBeamProd );
//   }
//
//   return *this;
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
MCSymmetricBeamProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
MCSymmetricBeamProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
MCSymmetricBeamProd::hist_book( HIHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
