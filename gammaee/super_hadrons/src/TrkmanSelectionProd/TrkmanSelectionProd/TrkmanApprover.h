// -*- C++ -*-
//
// File:    TrkmanApprover.h
// Package: TrkmanApprover
// Module:  TrkmanProd
// 
/**\class TrkmanApprover TrkmanApprover.h TrkmanProd/TrkmanApprover.h

 Description: Filter NavTracks into "TrkmanApproved" ones

 Usage:
    <usage>

*/
//
// Author:      Thomas Meyer
// Created:     Wed Sep 12 11:14:01 EDT 2001
// $Id: TrkmanApprover.h,v 1.1.1.1 2002/11/04 18:18:54 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanApprover.h,v $
// Revision 1.1.1.1  2002/11/04 18:18:54  nea9
// imported TrkmanSelectionProd
//
// Revision 1.1.1.1  2002/01/28 13:57:18  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */
#ifndef TRKMANPROD_TRKMANAPPROVER_H
#define TRKMANPROD_TRKMANAPPROVER_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES
#include "DataHandler/Record.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "Trkman/TrkmanInfo.h"

// FORWARD DECLARATIONS
class NavTrack;

class TrkmanApprover
{
  // ---------- FRIEND CLASSES AND FUNCTIONS ---------------

public:
  // ---------- CONSTANTS, ENUMS AND TYPEDEFS --------------
  typedef NavTrack value_type;

  typedef FAItem<  TrkmanInfo > TrkmanInfoItem;
  typedef FATable< TrkmanInfo > TrkmanInfoTable;
  typedef FATable< TrkmanInfo >::const_iterator TrkmanInfoConstIt;

  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
  TrkmanApprover();

  virtual ~TrkmanApprover();

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
  //TrkmanApprover( const TrkmanApprover& ); // allow default

  // ---------- ASSIGNMENT OPERATOR(S) ---------------------
  const TrkmanApprover& operator=( const TrkmanApprover& );
  
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
//# include "TrkmanProd/Template/TrkmanApprover.cc"
//#endif

#endif /* TRKMANPROD_TRKMANAPPROVER_H */
