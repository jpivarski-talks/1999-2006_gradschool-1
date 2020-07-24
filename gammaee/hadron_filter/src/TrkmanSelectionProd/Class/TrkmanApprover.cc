// -*-C++-*-
//
// File:    TrkmanApprover.cc
// Package: TrkmanApprover
// Module:  TrkmanProd
// 
// Description: Filter NavTracks into "TrkmanApproved" ones
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Wed Sep 12 11:14:01 EDT 2001
// $Id: TrkmanApprover.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $
//
// Revision history
//
// $Log: TrkmanApprover.cc,v $
// Revision 1.1.1.1  2002/01/28 13:57:19  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES

// STL
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// USER INCLUDE FILES
#include "Experiment/report.h"

#include "FrameAccess/extract.h"           

#include "TrkmanProd/TrkmanApprover.h"
#include "Navigation/NavTrack.h"

// DEFINITIONS/MACROS
// Dumb shorthand for report
#define dout report(DEBUG, kFacilityString)
#define iout report(INFO, kFacilityString)
#define wout report(WARNING, kFacilityString)
#define eout report(EMERGENCY, kFacilityString)

//
// CONSTANTS, ENUMS AND TYPEDEFS
//

static const char* const
kFacilityString = "TrkmanProd.TrkmanApprover" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const
kIdString  = "$Id: TrkmanApprover.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $";

static const char* const
kTagString = "$Name:  $";

//
// STATIC DATA MEMBER DEFINITIONS
//

//
// CONSTRUCTORS AND DESTRUCTOR
//

/* ======================================================================== */
TrkmanApprover::TrkmanApprover()
{
}
/* ======================================================================== */

/* ======================================================================== */
TrkmanApprover::~TrkmanApprover()
{
}
/* ======================================================================== */

//
// ASSIGNMENT OPERATORS
//

/* ======================================================================== */
// const TrkmanApprover& TrkmanApprover::operator=( const TrkmanApprover& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }
/* ======================================================================== */

//
// MEMBER FUNCTIONS
//

/* ======================================================================== */
void
TrkmanApprover::prefix(const Record& iRecord)
{
  // Extract list of TrkmanInfo objects from Frame
  extract(iRecord, m_trkmanInfoTable );

  return;
}
/* ======================================================================== */

//
// CONST MEMBER FUNCTIONS
//

/* ======================================================================== */
DABoolean
TrkmanApprover::select(const NavTrack& track) const
{
  // Find out track Id
  const NavTrack::Identifier trackId = track.identifier();

  // Find associated TrkmanInfo object
  TrkmanInfoConstIt info = m_trkmanInfoTable.find(trackId);
  
  if (info == m_trkmanInfoTable.end())
  {
    wout << "Didn't find TrkmanInfo object for Track Id: "
         << trackId << "!" << endl;
    return false;
  }
  
  if (info->use()) return true;

  return false;
}
/* ======================================================================== */

//
// STATIC MEMBER FUNCTIONS
//
