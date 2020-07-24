// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iMakeStuffBase
// 
// Description: class that holds a map of string and UInt16
//
// Implementation: straightforward
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec  8 11:11:36 EST 1998
// $Id: G3iMakeStuffBase.cc,v 1.1.1.1 1999/12/15 18:35:50 bkh Exp $
//
// Revision history
//
// $Log: G3iMakeStuffBase.cc,v $
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3MaterialsMediaProd sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "Geant3MaterialsMediaProd/G3iMakeStuffBase.h"

// STL classes
#include <map>

//
// constants, enums and typedefs
//

static const char* const kReport = "Geant3MaterialsMediaProd.G3iMakeStuffBase" ;

//
// static data member definitions
//

//
// constructors and destructor
//

G3iMakeStuffBase::G3iMakeStuffBase() :
   m_stringIntMap ( *new STL_MAP( string, UInt16 ) )
{
}

// G3iMakeStuffBase::G3iMakeStuffBase( const G3iMakeStuffBase& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

G3iMakeStuffBase::~G3iMakeStuffBase()
{
   delete &m_stringIntMap ;
}

//
// assignment operators
//
// const G3iMakeStuffBase& G3iMakeStuffBase::operator=( const G3iMakeStuffBase& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

STL_MAP( string, UInt16 )&
G3iMakeStuffBase::stringIntMap()
{
   return m_stringIntMap ;
}

//
// const member functions
//

const STL_MAP( string, UInt16 )& 
G3iMakeStuffBase::stringIntMap() const 
{
   return m_stringIntMap ;
}

//
// static member functions
//
