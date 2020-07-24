#if !defined(MCINFO_QUOTECHILDREN_H)
#define MCINFO_QUOTECHILDREN_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      quoteChildren
// 
// Description: stream "effector" for writing a vector of strings (like
//              a list of decay product (children) names) to a stream
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Mon Jun  7 21:48:58 EDT 1999
// $Id: quoteChildren.h,v 1.2 1999/07/07 00:19:30 lkg Exp $
//
// Revision history
//
// $Log: quoteChildren.h,v $
// Revision 1.2  1999/07/07 00:19:30  lkg
// Update so that setting the stream width before quoteChildren or quoteDecay
// will affect the width of all of the name fields:
//
//    report(a,b) << setw(5) << quoteDecay( parentName, childrenNames ) << endl;
//
// will result in each parent and child name being printed in a field of
// width 5.
//
// Revision 1.1  1999/06/22 21:30:20  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files

class quoteChildren
{
      // ---------- friend classes and functions ---------------
      friend ostream& operator<<( ostream& os, const quoteChildren& qc ) {
	 int userWidth = os.width();
	 if ( userWidth > 0 ) --userWidth;

	 typedef STL_VECTOR( string )::const_iterator Itr;
	 Itr done = qc.m_childNames.end();
	 for ( Itr itName = qc.m_childNames.begin(); 
	       itName != done; ++itName ) { 
	    os << setw(userWidth) << *itName << " "; 
	 }
	 return os;
      };

   public:
      // ---------- Constructors and destructor ----------------
      quoteChildren( const STL_VECTOR( string )& childNames ) :
	 m_childNames( childNames ) {};
      ~quoteChildren() {};

   private:
      // ---------- Constructors and destructor ----------------
      quoteChildren(); // stop default
      quoteChildren( const quoteChildren& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const quoteChildren& operator=( const quoteChildren& ); // stop default

      // ---------- data members -------------------------------
      const STL_VECTOR( string )& m_childNames;
};
#endif /* MCINFO_QUOTECHILDREN_H */
