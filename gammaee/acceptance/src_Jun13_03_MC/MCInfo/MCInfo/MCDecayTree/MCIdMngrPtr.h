#if !defined(MCINFO_MCIDMNGRPTR_H)
#define MCINFO_MCIDMNGRPTR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCIdMngrPtr
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:34 EST 1999
// $Id: MCIdMngrPtr.h,v 1.2 2002/02/05 03:30:05 lkg Exp $
//
// Revision history
//
// $Log: MCIdMngrPtr.h,v $
// Revision 1.2  2002/02/05 03:30:05  lkg
// add const dereferencing
//
// Revision 1.1  1999/06/22 21:30:00  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files

// forward declarations
class MCIdManager;

class MCIdMngrPtr
{
   public:
      // ---------- constants, enums and typedefs --------------
      
      // ---------- Constructors and destructor ----------------
      MCIdMngrPtr();
      MCIdMngrPtr( MCIdManager* aManager );
      MCIdMngrPtr( const MCIdMngrPtr& rhs );

      virtual ~MCIdMngrPtr();

      // ---------- assignment operator ---------------------
      const MCIdMngrPtr& operator=( const MCIdMngrPtr& );

      // ---------- member functions ---------------------------

      MCIdManager& operator*();
      
      // ---------- const member functions ---------------------
      const MCIdManager& operator*() const;

      DABoolean operator==( const MCIdMngrPtr& );
      DABoolean operator!=( const MCIdMngrPtr& );

   private:
      // ---------- data members -------------------------------
      MCIdManager* m_pManager;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCIdMngrPtr.cc"
//#endif

#endif /* MCINFO_MCIDMNGRPTR_H */
