#if !defined(STUPIDPROD_STUPID_H)
#define STUPIDPROD_STUPID_H
// -*- C++ -*-
//
// Package:     <StupidProd>
// Module:      Stupid
// 
/**\class Stupid Stupid.h StupidProd/Stupid.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Mar 22 01:31:56 EST 2004
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files

// forward declarations

class Stupid
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Stupid(int tracks0 = -1, int tracks1 = -1, int tracks2 = -1, int tracks3 = -1);
      virtual ~Stupid();

      // ---------- member functions ---------------------------

      Stupid( const Stupid& );
      DABoolean operator==( const Stupid& other ) const;
      const Stupid& operator=( const Stupid& other );

      // ---------- const member functions ---------------------

      int tracks0() const {return m_tracks0;};
      int tracks1() const {return m_tracks1;};
      int tracks2() const {return m_tracks2;};
      int tracks3() const {return m_tracks3;};

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      int m_tracks0;
      int m_tracks1;
      int m_tracks2;
      int m_tracks3;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StupidProd/Template/Stupid.cc"
//#endif

#endif /* STUPIDPROD_STUPID_H */
