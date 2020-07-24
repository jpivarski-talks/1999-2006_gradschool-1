// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCQQBar
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sun May  2 21:45:27 EDT 1999
// $Id: MCQQBar.cc,v 1.2 1999/07/07 00:12:06 lkg Exp $
//
// Revision history
//
// $Log: MCQQBar.cc,v $
// Revision 1.2  1999/07/07 00:12:06  lkg
// Change the QQBar id functions to use Integer rather than Count
//
// Revision 1.1  1999/06/22 21:28:54  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"
#include "Experiment/units.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCQQBar.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCQQBar" ;
const Integer MCQQBar::kQQBarIdToQQId = -61;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCQQBar.cc,v 1.2 1999/07/07 00:12:06 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCQQBar::MCQQBar() :
   MCParticleProperty(),
   m_qqBarId( 0 )
{}

MCQQBar::MCQQBar( const MCQQBar& rhs ) :
   MCParticleProperty( rhs ),
   m_qqBarId( rhs.m_qqBarId )
{}

MCQQBar::~MCQQBar()
{}

//
// assignment operators
//
const MCQQBar& MCQQBar::operator=( const MCQQBar& rhs )
{
  if( this != &rhs ) {
     m_qqBarId = rhs.m_qqBarId;
     MCParticleProperty::operator=( rhs );
  }

  return *this;
}

//
// member functions
//
void
MCQQBar::setQQBarId( Integer newId ) {

   m_qqBarId = newId;
   QQ_id newQQId = kQQBarIdToQQId + newId;
   MCParticleProperty::setQQId( newQQId );
}

//
// const member functions
//
Integer
MCQQBar::qqBarId() const {
   return m_qqBarId;
}

//
// static member functions
//
DABoolean
MCQQBar::upType( MCQQBar::quarkNumber quark ) {
   return ( (quark/2) * 2 ) == quark;
}

DABoolean
MCQQBar::downType( MCQQBar::quarkNumber quark ) {
   return ! upType( quark );
}

Double MCQQBar::calculateCharge( MCQQBar::quarkNumber     quark,
				 MCQQBar::quarkNumber antiquark ) {
   Integer charge( 0 );
   if ( upType( quark ) ) {
      charge = 2;
   } else {
      charge = -1;
   }
   if ( upType( antiquark ) ) {
      charge -= 2;
   } else {
      charge += 1;
   }

   charge /= 3;
   Double dcharge = charge;
   return dcharge;
}

Integer MCQQBar::calculatePDGId( MCQQBar::quarkNumber     quark,
				 MCQQBar::quarkNumber antiquark ) {
   // PDG and user-defined particles
   // standard offset is 9900000, but we would get clashes with
   // special definitions for KS/KL, for example
   Integer pdgOffset = 99900000;

   Integer pdg = pdgOffset + 100*quark + 10*antiquark;
   if ( downType(quark) && (quark != antiquark) ) {
      pdg = -pdg;
   }

   return pdg;
}

Double MCQQBar::calculateMinMass( MCQQBar::quarkNumber     quark,
				  MCQQBar::quarkNumber antiquark ) {
   static const Double quarkMasses[7] = 
      { 0.,           // generic, so unknown
	3.0*k_MeV,    // down
	2.0*k_MeV,    // up
	125.*k_MeV,   // strange
	1.1*k_GeV,    // charm
	4.2*k_GeV,    // bottom
	174.*k_GeV }; // top

   return quarkMasses[quark] + quarkMasses[antiquark];
}

MCQQBar::quarkNumber
MCQQBar::nameToNumber( char quarkName ) {

   quarkNumber quark;
   switch( quarkName ) {
      case 'd':
      case 'D':
         quark = d;
	 break;
      case 'u':
      case 'U':
         quark = u;
	 break;
      case 's':
      case 'S':
         quark = s;
	 break;
      case 'c':
      case 'C':
         quark = c;
	 break;
      case 'b':
      case 'B':
         quark = b;
	 break;
      case 't':
      case 'T':
         quark = t;
	 break;
      default:
         quark = q;
	 break;
   }

   return quark;
}
