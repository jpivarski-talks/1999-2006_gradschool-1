// -*- C++ -*-
#if !defined(MCINFO_DELIVERDUMMYMCDT_H)
#define MCINFO_DELIVERDUMMYMCDT_H
//
// Package:     <MCInfo>
// Module:      DeliverDummyMCDT
// 
/*

 Description: A singleton class that will serve up the dummy versions
              of MCDecayTree, MCVertex, MCParticle needed for the
              storage helper

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr  2 17:27:32 EDT 2000
// $Id: DeliverDummyMCDT.h,v 1.2 2001/12/19 18:12:30 lkg Exp $
//
// Revision history
//
// $Log: DeliverDummyMCDT.h,v $
// Revision 1.2  2001/12/19 18:12:30  lkg
// don't build privaty dummy propert store.  Use dummy store created for property Storage Helpers
//
// Revision 1.1  2000/05/01 22:39:33  lkg
// added storage helpers to repository
//

// system include files

// user include files
#include "MCInfo/MCDecayTree/MCDecayTree.h"

// forward declarations
class MCParticle;
class MCVertex;

class DeliverDummyMCDT
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DeliverDummyMCDT();
      virtual ~DeliverDummyMCDT();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      MCDecayTree&              dummyMCDecayTree();
      MCParticle&               dummyMCParticle();
      MCVertex&                 dummyMCVertex();

      // ---------- static member functions --------------------
      // Singleton constructor-surrogate function
      static DeliverDummyMCDT& instance( void );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DeliverDummyMCDT( const DeliverDummyMCDT& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DeliverDummyMCDT& operator=( const DeliverDummyMCDT& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      MCDecayTree m_dummyDecayTree;

      // ---------- static data members ------------------------
      static DeliverDummyMCDT* m_instance;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/DeliverDummyMCDT.cc"
//#endif

#endif /* MCINFO_DELIVERDUMMYMCDT_H */
