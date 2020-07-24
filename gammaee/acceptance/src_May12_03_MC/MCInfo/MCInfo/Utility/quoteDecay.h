#if !defined(MCINFO_QUOTEDECAY_H)
#define MCINFO_QUOTEDECAY_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      quoteDecay
// 
// Description: stream "effector" for quoting the decay mode
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Mon Jun  7 21:32:45 EDT 1999
// $Id: quoteDecay.h,v 1.2 1999/07/07 00:19:31 lkg Exp $
//
// Revision history
//
// $Log: quoteDecay.h,v $
// Revision 1.2  1999/07/07 00:19:31  lkg
// Update so that setting the stream width before quoteChildren or quoteDecay
// will affect the width of all of the name fields:
//
//    report(a,b) << setw(5) << quoteDecay( parentName, childrenNames ) << endl;
//
// will result in each parent and child name being printed in a field of
// width 5.
//
// Revision 1.1  1999/06/22 21:30:21  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files
#include "MCInfo/Utility/quoteChildren.h"

class quoteDecay
{
      // ---------- friend classes and functions ---------------
      friend ostream& operator<<( ostream& os, const quoteDecay& qd ) {
	 int userWidth = os.width();
	 return os << setw(userWidth) << qd.m_parentName << " --> " 
		   << setw(userWidth) << quoteChildren( qd.m_childNames );
      };

   public:
      // ---------- Constructors and destructor ----------------
      quoteDecay( const string& parentName,
		  const STL_VECTOR( string )& childNames ) :
	 m_parentName( parentName ),
	 m_childNames( childNames ) {};
      ~quoteDecay() {};
   private:
      // ---------- Constructors and destructor ----------------
      quoteDecay(); // stop default
      quoteDecay( const quoteDecay& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const quoteDecay& operator=( const quoteDecay& ); // stop default

      // ---------- data members -------------------------------
      const string& m_parentName;
      const STL_VECTOR( string )& m_childNames;
};

#endif /* MCINFO_QUOTEDECAY_H */
