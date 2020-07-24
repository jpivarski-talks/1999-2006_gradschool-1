// -*- C++ -*-
//
// File:    TrkmanLink
// Package: TrkmanLattice
// Module:  Trkman
// 
/**\class TrkmanLink TrkmanLink.h Trkman/TrkmanLink.h

 Description: Link data for the TrkmanLattice

 Usage:
 The job of Trkman is to choose the best track to use for each
   set of hits (or particle) in the tracking chambers. In making
   these determinations, it will "approve" some tracks and reject
   others. The TrkmanLattice records the relationship between the
   rejected tracks and the good track with which they share
   the same set of hits.
 The TrkmanLattice connects "good" tracks on the Left to "bad"
   tracks on the Right, as associated by the Trkman package.
 The link data in between holds details about the whole group
   of tracks: group Id, total number of tracks in the group,
   the group type (curler, ghost, wee, other), and more
   details supplied by the underlying Trkman package.

*/
//
// Author:      Nadia Adam
// Created:     Sun Jan 20 16:10:57 EST 2002
// $Id: TrkmanLink.h,v 1.1.1.1 2002/01/28 13:56:13 tom Exp $
//
// Revision history
//
// $Log: TrkmanLink.h,v $
// Revision 1.1.1.1  2002/01/28 13:56:13  tom
// Imported Trkman library sources
//
/* ******************************************************************** */
#ifndef TRKMAN_TRKMANLINK_H
#define TRKMAN_TRKMANLINK_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES

// FORWARD DECLARATIONS

class TrkmanLink
{
  // ---------- FRIEND CLASSES AND FUNCTIONS ---------------

public:
  // ---------- CONSTANTS, ENUMS AND TYPEDEFS --------------

  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
  TrkmanLink();
  
  TrkmanLink(int groupId, int groupCode, int numTracks = 2);

  TrkmanLink( const TrkmanLink& );

  const TrkmanLink& operator=( const TrkmanLink& );

  virtual ~TrkmanLink();

  // ---------- MEMBER FUNCTIONS ---------------------------
  void setGroupId(int groupId);
  void setGroupCode(int groupCode);
  void setNumTracks(int numTracks);

  // Increments number of tracks by one
  void addTrack();
  
  // ---------- CONST MEMBER FUNCTIONS ---------------------
  DABoolean use() const;

  // Group number
  int groupId() const;

  // (Total) number of tracks in the group
  int numTracks() const;

  // Classification code from Trkman
  int groupCode() const;

  // Intepret classification code into major types
  int type() const;
  DABoolean good() const;
    DABoolean ghost()  const;
  DABoolean curler() const;
  DABoolean wee()    const;
  DABoolean other()  const;

  // Detailed sub-classification of group
  int subtype() const;

  DABoolean operator==(const TrkmanLink& ) const;

  // ---------- STATIC MEMBER FUNCTIONS --------------------

protected:
  // ---------- PROTECTED MEMBER FUNCTIONS -----------------

  // ---------- PROTECTED CONST MEMBER FUNCTIONS -----------

private:
  // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------

  // ---------- ASSIGNMENT OPERATOR(S) ---------------------

  // ---------- PRIVATE MEMBER FUNCTIONS -------------------

  // ---------- PRIVATE CONST MEMBER FUNCTIONS -------------

  // ---------- DATA MEMBERS -------------------------------
  // Group Id labeling curler/ghost/wee group
  int m_groupId;

  // Group classification code from Trkman
  int m_groupCode;

  // Number of tracks in the "group"
  int m_numTracks;

  // ---------- STATIC DATA MEMBERS ------------------------

};

// INLINE FUNCTION DEFINITIONS

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Trkman/Template/TrkmanLink.cc"
//#endif

#endif /* TRKMAN_TRKMANLINK_H */
