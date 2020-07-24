#if !defined(PACKAGE_INTERSECTIONINFO_H)
#define PACKAGE_INTERSECTIONINFO_H
// -*- C++ -*-
//
// Package:     BeamGasFilterProc
// Module:      IntersectionInfo
// 
/**\class IntersectionInfo IntersectionInfo.h package/IntersectionInfo.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Feb  4 17:20:48 EST 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files

// forward declarations

class IntersectionInfo
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      IntersectionInfo(double closestIntersection = 0., double eventZ = 0.);
      IntersectionInfo( const IntersectionInfo& );
      virtual ~IntersectionInfo();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      Meters closestIntersection() const { return m_closestIntersection; }
      Meters eventZ() const { return m_eventZ; }

      DABoolean operator==( const IntersectionInfo& other ) const
      { return ( closestIntersection() == other.closestIntersection()  &&
		 eventZ()              == other.eventZ()                  ); }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------
      const IntersectionInfo& operator=( const IntersectionInfo& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      double m_closestIntersection;
      double m_eventZ;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/IntersectionInfo.cc"
//#endif

#endif /* PACKAGE_INTERSECTIONINFO_H */
