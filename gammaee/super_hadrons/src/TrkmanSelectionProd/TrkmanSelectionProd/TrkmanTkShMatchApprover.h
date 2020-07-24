// -*- C++ -*-
//
// File:    TrkmanTkShMatchApprover.h
// Package: TrkmanTkShMatchApprover
// Module:  TrkmanProd
// 
/**\class TrkmanTkShMatchApprover TrkmanTkShMatchApprover.h TrkmanProd/TrkmanTkShMatchApprover.h

 Description: Filter NavTracks into ones "TrkmanApproved" for use in trk-sh matching

 Usage:
    <usage>

*/
//
// Author:      Thomas Meyer
// Created:     Wed Sep 12 11:14:01 EDT 2001
// $Id: TrkmanTkShMatchApprover.h,v 1.1.1.1 2002/11/04 18:18:54 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanTkShMatchApprover.h,v $
// Revision 1.1.1.1  2002/11/04 18:18:54  nea9
// imported TrkmanSelectionProd
//
// Revision 1.1.1.1  2002/01/28 13:57:18  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */
#ifndef TRKMANPROD_TRKMANTKSHMATCHAPPROVER_H
#define TRKMANPROD_TRKMANTKSHMATCHAPPROVER_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES
#include "DataHandler/Record.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "Trkman/TrkmanInfo.h"

// FORWARD DECLARATIONS
class NavTrack;

class TrkmanTkShMatchApprover
{
  // ---------- FRIEND CLASSES AND FUNCTIONS ---------------

public:
  // ---------- CONSTANTS, ENUMS AND TYPEDEFS --------------
  typedef NavTrack value_type;

  typedef FAItem<  TrkmanInfo > TrkmanInfoItem;
  typedef FATable< TrkmanInfo > TrkmanInfoTable;
  typedef FATable< TrkmanInfo >::const_iterator TrkmanInfoConstIt;

  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
  TrkmanTkShMatchApprover();

  virtual ~TrkmanTkShMatchApprover();

  // ---------- MEMBER FUNCTIONS ---------------------------
  void prefix(const Record& iRecord);
  
  // ---------- CONST MEMBER FUNCTIONS ---------------------
  DABoolean select(const NavTrack& var) const;

  // ---------- STATIC MEMBER FUNCTIONS --------------------

protected:
  // ---------- PROTECTED MEMBER FUNCTIONS -----------------

  // ---------- PROTECTED CONST MEMBER FUNCTIONS -----------

private:
  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
  //TrkmanTkShMatchApprover( const TrkmanTkShMatchApprover& ); // allow default

  // ---------- ASSIGNMENT OPERATOR(S) ---------------------
  const TrkmanTkShMatchApprover& operator=( const TrkmanTkShMatchApprover& );
  
  // ---------- PRIVATE MEMBER FUNCTIONS -------------------
  
  // ---------- PRIVATE CONST MEMBER FUNCTIONS -------------
  
  // ---------- DATA MEMBERS -------------------------------
  // Keep a list of the TrkmanInfo objects, since they're not yet
  //   included as part of a NavTrack
  TrkmanInfoTable m_trkmanInfoTable;

  // ---------- STATIC DATA MEMBERS ------------------------

};

// INLINE FUNCTION DEFINITIONS

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "TrkmanProd/Template/TrkmanTkShMatchApprover.cc"
//#endif

#endif /* TRKMANPROD_TRKMANTKSHMATCHAPPROVER_H */
