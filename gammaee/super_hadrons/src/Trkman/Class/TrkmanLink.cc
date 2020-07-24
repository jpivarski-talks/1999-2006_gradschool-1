// -*- C++ -*-
//
// File:    TrkmanLink.cc
// Package: TrkmanLattice
// Module:  Trkman
// 
// Description: Link data for the TrkmanLattice
//
// Implementation:
//
// Author:      Nadia Adam
// Created:     Sun Jan 20 16:10:57 EST 2002
// $Id: TrkmanLink.cc,v 1.1.1.1 2002/01/28 13:56:14 tom Exp $
//
// Revision history
//
// $Log: TrkmanLink.cc,v $
// Revision 1.1.1.1  2002/01/28 13:56:14  tom
// Imported Trkman library sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES

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
#include "Trkman/TrkmanLink.h"

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

static const char* const kFacilityString = "Trkman.TrkmanLink" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const
kIdString  = "$Id: TrkmanLink.cc,v 1.1.1.1 2002/01/28 13:56:14 tom Exp $";

static const char* const
kTagString = "$Name:  $";

//
// STATIC DATA MEMBER DEFINITIONS
//

//
// CONSTRUCTORS AND DESTRUCTOR
//

/* ======================================================================== */
TrkmanLink::TrkmanLink() :
  m_groupId(0),
  m_groupCode(0),
  m_numTracks(0)
{
}
/* ======================================================================== */

/* ======================================================================== */
TrkmanLink::TrkmanLink(int groupId, int groupCode, int numTracks) :
  m_groupId(groupId),
  m_groupCode(groupCode),
  m_numTracks(numTracks)
{
}
/* ======================================================================== */

/* ======================================================================== */
TrkmanLink::TrkmanLink(const TrkmanLink& rhs)
{
  *this = rhs;
}
/* ======================================================================== */

/* ======================================================================== */
TrkmanLink::~TrkmanLink()
{
}
/* ======================================================================== */

//
// ASSIGNMENT OPERATORS
//

/* ======================================================================== */
const TrkmanLink& TrkmanLink::operator=(const TrkmanLink& rhs)
{
  if ( this != &rhs )
  {
    m_groupId   = rhs.m_groupId;
    m_groupCode = rhs.m_groupCode;
    m_numTracks = rhs.m_numTracks;
  }

  return *this;
}
/* ======================================================================== */

//
// MEMBER FUNCTIONS
//

/* ======================================================================== */
void
TrkmanLink::setGroupId(int groupId)
{
  m_groupId = groupId;
  return;
}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanLink::setGroupCode(int groupCode)
{
  m_groupCode = groupCode;
  return;
}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanLink::setNumTracks(int numTracks)
{
  m_numTracks = numTracks;
  return;
}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanLink::addTrack()
{
  ++m_numTracks;
  return;
}
/* ======================================================================== */

//
// CONST MEMBER FUNCTIONS
//

/* ======================================================================== */
DABoolean
TrkmanLink::use() const
{
  return (m_groupCode >= 0);
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanLink::groupId() const
{
  return m_groupId;
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanLink::numTracks() const
{
  return m_numTracks;
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanLink::groupCode() const
{
  return m_groupCode;
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanLink::type() const
{
  return abs(m_groupCode)/100;
}
/* ======================================================================== */

/* ======================================================================== */
int
TrkmanLink::subtype() const
{
  return (abs(m_groupCode)%100);
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanLink::good() const
{
  return (0 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanLink::ghost() const
{
  return (1 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanLink::curler() const
{
  return (2 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanLink::wee() const
{
  return (3 == type());
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanLink::other() const
{
  return (type() > 3);
}
/* ======================================================================== */

/* ======================================================================== */
DABoolean
TrkmanLink::operator==(const TrkmanLink& rhs) const
{
  return ( (groupId()   == rhs.groupId()) &&
           (groupCode() == rhs.groupCode()) &&
           (numTracks() == rhs.numTracks()));
}
/* ======================================================================== */

//
// STATIC MEMBER FUNCTIONS
//
