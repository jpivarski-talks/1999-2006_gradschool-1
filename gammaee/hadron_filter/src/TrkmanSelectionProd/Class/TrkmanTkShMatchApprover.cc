// -*-C++-*-
//
// File:    TrkmanTkShMatchApprover.cc
// Package: TrkmanTkShMatchApprover
// Module:  TrkmanProd
// 
// Description: Filter NavTracks into ones "TrkmanApproved" for use in trk-sh matching
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Wed Sep 12 11:14:01 EDT 2001
// $Id: TrkmanTkShMatchApprover.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $
//
// Revision history
//
// $Log: TrkmanTkShMatchApprover.cc,v $
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

#include "TrkmanProd/TrkmanTkShMatchApprover.h"
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
kFacilityString = "TrkmanProd.TrkmanTkShMatchApprover" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const
kIdString  = "$Id: TrkmanTkShMatchApprover.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $";

static const char* const
kTagString = "$Name:  $";

//
// STATIC DATA MEMBER DEFINITIONS
//

//
// CONSTRUCTORS AND DESTRUCTOR
//

/* ======================================================================== */
TrkmanTkShMatchApprover::TrkmanTkShMatchApprover()
{
}
/* ======================================================================== */

/* ======================================================================== */
TrkmanTkShMatchApprover::~TrkmanTkShMatchApprover()
{
}
/* ======================================================================== */

//
// ASSIGNMENT OPERATORS
//

/* ======================================================================== */
// const TrkmanTkShMatchApprover& TrkmanTkShMatchApprover::operator=( const TrkmanTkShMatchApprover& rhs )
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
TrkmanTkShMatchApprover::prefix(const Record& iRecord)
{
  // Extract list of TrkmanInfo objects from Frame
  extract(iRecord, m_trkmanInfoTable);

  return;
}
/* ======================================================================== */

//
// CONST MEMBER FUNCTIONS
//

/* ======================================================================== */
DABoolean
TrkmanTkShMatchApprover::select(const NavTrack& track) const
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
  
  if (info->useForMatching()) return true;

  return false;
}
/* ======================================================================== */

//
// STATIC MEMBER FUNCTIONS
//
