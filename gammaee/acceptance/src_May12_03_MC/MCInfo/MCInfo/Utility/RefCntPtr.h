#if !defined(MCINFO_REFCNTPTR_H)
#define MCINFO_REFCNTPTR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      RefCntPtr
// 
// Description: Smart pointer for use in managing the simplistic helicity
//              classes in MCDecayMode without having to copy
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:34 EST 1999
// $Id: RefCntPtr.h,v 1.1 1999/06/22 21:30:20 lkg Exp $
//
// Revision history
//
// $Log: RefCntPtr.h,v $
// Revision 1.1  1999/06/22 21:30:20  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files

template<class T>
class RefCntPtr
{
   public:
      // ---------- constants, enums and typedefs --------------
      typedef RefCntPtr< T > self;

      // ---------- Constructors and destructor ----------------
      RefCntPtr();
      RefCntPtr( T* );
      RefCntPtr( const self& rhs );

      virtual ~RefCntPtr();

      // ---------- assignment operator ---------------------
      const self& operator=( const self& rhs );

      // ---------- member functions ---------------------------

      T& operator*();
      // ---------- const member functions ---------------------

      DABoolean operator==( const self& ) const;
      DABoolean operator!=( const self& ) const;

      const T& operator*() const;

   private:
      // ---------- data members -------------------------------
      T* m_pointer;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "MCInfo/Utility/Template/RefCntPtr.cc"
#endif

#endif /* MCINFO_REFCNTPTR_H */
