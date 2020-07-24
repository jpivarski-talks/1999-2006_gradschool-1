// -*- C++ -*-
//
// File:    TrkmanInfo.h
// Package: TrkmanInfo
// Module:  Trkman
// 
/**\class TrkmanInfo TrkmanInfo.h Trkman/TrkmanInfo.h

 Description: Track information in the spirit of Trkman

 Usage:
    <usage>

*/
//
// Author:      Thomas Meyer
// Created:     Tue Jan 15 10:21:18 EST 2002
// $Id: TrkmanInfo.h,v 1.2 2002/11/04 18:31:01 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanInfo.h,v $
// Revision 1.2  2002/11/04 18:31:01  nea9
// New CleoIII Trkman
//
// Revision 1.1.1.1  2002/01/28 13:56:13  tom
// Imported Trkman library sources
//
/* ******************************************************************** */
#ifndef TRKMAN_TRKMANINFO_H
#define TRKMAN_TRKMANINFO_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES
#include "FrameAccess/FAItem.h"

// FORWARD DECLARATIONS

class TrkmanInfo
{
  // ---------- FRIEND CLASSES AND FUNCTIONS ---------------
  friend class TrkmanInfoProxy;

public:
  // ---------- CONSTANTS, ENUMS AND TYPEDEFS --------------

  // So that we can live in an FATable
  typedef Count Identifier;

  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
  TrkmanInfo(Identifier identifier, int classificationCode,
	     DABoolean useForMatching, int groupId );

  TrkmanInfo( Identifier identifier, int classificationCode );

  virtual ~TrkmanInfo();

  // ---------- MEMBER FUNCTIONS ---------------------------
  void setUseForMatching(DABoolean use);
  void setGroupId(int groupId);

  // ---------- CONST MEMBER FUNCTIONS ---------------------
  Identifier identifier() const;

  // Whether Trkman approved this track for use as a real particle
  DABoolean use() const;

  // Whether Trkman approved this track for use in track-shower matching
  DABoolean useForMatching() const;

  // Detailed code describing how Trkman classified this track
  int classificationCode() const;

  // Interpretation of Trkman code
  DABoolean good() const;
  DABoolean ghost() const;
  DABoolean curler() const;
  DABoolean wee() const;
  DABoolean other() const;

  // Hundreds place of classification code---type of classification
  int type() const;

  // Tens and units place of classification code---subcategory
  //   within broader type
  int subtype() const;

  // Group number used in the Trkman common blocks
  // Provided really just as a check. Group may be "curler", "ghost"
  //   or "wee"---this is the index in the appropriate list
  int groupId() const;

  // ---------- STATIC MEMBER FUNCTIONS --------------------

  TrkmanInfo( const TrkmanInfo& ); // stop default

  // ---------- ASSIGNMENT OPERATOR(S) ---------------------
  const TrkmanInfo& operator=( const TrkmanInfo& ); // stop default

protected:
  // ---------- PROTECTED MEMBER FUNCTIONS -----------------

  // ---------- PROTECTED CONST MEMBER FUNCTIONS -----------

private:
  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------

  // ---------- PRIVATE MEMBER FUNCTIONS -------------------
  void setTrackCode(int trackCode);

  // ---------- PRIVATE CONST MEMBER FUNCTIONS -------------

  // ---------- DATA MEMBERS -------------------------------
  Identifier m_trackId;
  
  int m_trackCode;

  DABoolean m_useForMatching;

  int m_groupId;

  // ---------- STATIC DATA MEMBERS ------------------------

};

// INLINE FUNCTION DEFINITIONS

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Trkman/Template/TrkmanInfo.cc"
//#endif

#endif /* TRKMAN_TRKMANINFO_H */
