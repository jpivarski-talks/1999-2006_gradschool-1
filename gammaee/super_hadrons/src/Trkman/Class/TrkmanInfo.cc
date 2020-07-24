// -*- C++ -*-
//
// File:    TrkmanInfo.cc
// Package: TrkmanInfo
// Module:  Trkman
// 
// Description: Track information in the spirit of Trkman
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Tue Jan 15 10:21:33 EST 2002
// $Id: TrkmanInfo.cc,v 1.2 2002/11/04 18:31:33 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanInfo.cc,v $
// Revision 1.2  2002/11/04 18:31:33  nea9
// New CleoIII Trkman
//
// Revision 1.1.1.1  2002/01/28 13:56:14  tom
// Imported Trkman library sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES

// STL
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// USER INCLUDE FILES
#include "Experiment/report.h"
#include "Experiment/cleo_math.h"

#include "Trkman/TrkmanInfo.h"

// STL (again)
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// DEFINITIONS/MACROS
// Dumb shorthand for report
#define dout report(DEBUG, kFacilityString)
#define iout report(INFO, kFacilityString)
#define wout report(WARNING, kFacilityString)
#define eout report(EMERGENCY, kFacilityString)

//
// CONSTANTS, ENUMS AND TYPEDEFS
//

static const char* const kFacilityString = "TrkmanProd.TrkmanInfo" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const
kIdString  = "$Id: TrkmanInfo.cc,v 1.2 2002/11/04 18:31:33 nea9 Exp $";

static const char* const
kTagString = "$Name:  $";

//
// STATIC DATA MEMBER DEFINITIONS
//

//
// CONSTRUCTORS AND DESTRUCTOR
//

/* ======================================================================== */
TrkmanInfo::TrkmanInfo( Identifier identifier, int classificationCode,
			DABoolean useForMatching, int groupId ) :
  m_trackId(identifier),
  m_trackCode(classificationCode),
  m_useForMatching(useForMatching),
  m_groupId(groupId)
{

}
/* ======================================================================== */

/* ======================================================================== */
TrkmanInfo::TrkmanInfo( Identifier identifier, int classificationCode ) :
  m_trackId(identifier),
  m_trackCode(classificationCode),
  m_useForMatching(true),
  m_groupId(0)
{

}
/* ======================================================================== */

/* ======================================================================== */
TrkmanInfo::TrkmanInfo( const TrkmanInfo& rhs )
{
   m_trackId = rhs.identifier();
   m_trackCode = rhs.classificationCode();
   m_useForMatching = rhs.useForMatching();
   m_groupId = rhs.groupId();
   
}
/* ======================================================================== */

/* ======================================================================== */
TrkmanInfo::~TrkmanInfo()
{
}
/* ======================================================================== */

//
// ASSIGNMENT OPERATORS
//

/* ======================================================================== */
const TrkmanInfo& TrkmanInfo::operator=( const TrkmanInfo& rhs )
{
  if( this != &rhs ) {
     m_trackId = rhs.identifier();
     m_trackCode = rhs.classificationCode();
     m_useForMatching = rhs.useForMatching();
     m_groupId = rhs.groupId();
  }
  return *this;
}

/* ======================================================================== */

//
// MEMBER FUNCTIONS
//

/* ======================================================================== */
void
TrkmanInfo::setTrackCode(int trackCode)
{
  m_trackCode = trackCode;

  return;
}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanInfo::setUseForMatching(DABoolean use)
{
  m_useForMatching = use;

  return;
}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanInfo::setGroupId(int groupId)
{
  m_groupId = groupId;
  
  return;
}


/* ======================================================================== */

//
// CONST MEMBER FUNCTIONS
//

/* ======================================================================== */
TrkmanInfo::Identifier
TrkmanInfo::identifier() const
{
  return m_trackId;
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::use() const
{
  return (m_trackCode >= 0);
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanInfo::classificationCode() const
{
  return m_trackCode;
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanInfo::type() const
{
  return abs(m_trackCode/100);
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanInfo::subtype() const
{
  return (abs(m_trackCode)%100);
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::good() const
{
  return (0 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::ghost() const
{
  return (1 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::curler() const
{
  return (2 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::wee() const
{
  return (3 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::other() const
{
  return (type() > 3);
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanInfo::useForMatching() const
{
  return m_useForMatching;
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanInfo::groupId() const
{
  return m_groupId;
}
/* ======================================================================== */

//
// STATIC MEMBER FUNCTIONS
//
