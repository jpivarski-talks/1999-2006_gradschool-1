// -*- C++ -*-
//
// Package:     <TriggerInfoProd>
// Module:      TriggerInfo
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:03:58 EDT 2004
// $Id$
//
// Revision history
//
// $Log$

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "TriggerInfoProd/TriggerInfo.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "TriggerInfoProd.TriggerInfo" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerInfo::TriggerInfo()
   : m_axial(-1)
   , m_stereo(-1)
   , m_cblo(-1)
   , m_cbmd(-1)
{
}

TriggerInfo::TriggerInfo(int axial, int stereo, int cblo, int cbmd)
   : m_axial(axial)
   , m_stereo(stereo)
   , m_cblo(cblo)
   , m_cbmd(cbmd)
{
}

TriggerInfo::TriggerInfo( const TriggerInfo& rhs )
{
   // do actual copying here; if you implemented
   // operator= correctly, you may be able to use just say      
   *this = rhs;
}

TriggerInfo::~TriggerInfo()
{
}

//
// assignment operators
//
const TriggerInfo& TriggerInfo::operator=( const TriggerInfo& rhs )
{
  if( this != &rhs ) {
     m_axial = rhs.axial();
     m_stereo = rhs.stereo();
     m_cblo = rhs.cblo();
     m_cbmd = rhs.cbmd();
  }

  return *this;
}

DABoolean TriggerInfo::operator==( const TriggerInfo& rhs ) const {
   return (rhs.axial() == m_axial    &&
	   rhs.stereo() == m_stereo  &&
	   rhs.cblo() == m_cblo      &&
	   rhs.cbmd() == m_cbmd         );
}

DABoolean TriggerInfo::operator!=( const TriggerInfo& rhs ) const {
   return !(*this == rhs);
}

//
// member functions
//

//
// const member functions
//

//
// static member functions
//
