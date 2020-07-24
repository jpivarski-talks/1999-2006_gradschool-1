// -*- C++ -*-
#if !defined(MCINFO_MCLISTITR_H)
#define MCINFO_MCLISTITR_H
//
// Package:     <MCInfo>
// Module:      MCListItr
// 
// Description: A dereferencing iterator for MCVertex*/MCParticle* Lists
//
// Usage:
//    This is a template class meant to implement a more convenient
//    iterator for list<MCVertex*> or list<MCParticle*> -- an iterator
//    that reduces the level of indirection by one.
//
//    In reality, it is a smart pointer to a instance of a class T.
//    It is "smart" in the sense that from the user's point of view,
//    it behaves like an iterator over a container (currently implemented
//    as a list) of type T.
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 13:18:44 EST 1999
// $Id: MCListItr.h,v 1.7 2002/12/06 16:44:59 cleo3 Exp $
//
// Revision history
//
// $Log: MCListItr.h,v $
// Revision 1.7  2002/12/06 16:44:59  cleo3
// added typename
//
// Revision 1.6  2001/09/10 20:04:29  cleo3
// removed unnecessary includes for list
//
// Revision 1.5  2001/05/12 17:44:02  lkg
// implement access to bare iterator and let MCPPStoreItr have access
//
// Revision 1.4  2001/02/18 22:12:00  cleo3
// changed OLD_ITERATOR_CLASSES_BUG to NO_ITERATOR_TRAITS_BUG
//
// Revision 1.3  2000/05/04 17:52:31  cdj
// added the other typedefs that all iterators need
//
// Revision 1.2  2000/05/01 22:48:04  lkg
// added valueType as an additional template parameter to make this more STL-like for StorageHelper -- entire scheme should get reevaluated
//
// Revision 1.1  1999/06/22 21:30:01  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files

// forward declarations

typedef long relative_address;

template < class T_iter, class T_return, class T_valueType >
class MCListItr
{
      friend class MCPPStoreItr;

      // ---------- private typedefs ---------------
      typedef MCListItr< T_iter, T_return, T_valueType > self;
      
   public:
      // ---------- constants, enums and typedefs --------------
      typedef T_valueType      value_type;
      typedef relative_address difference_type;
      typedef T_return&        reference;
      typedef T_return*        pointer;

#if !defined(NO_ITERATOR_TRAITS_BUG)
      typedef  typename iterator_traits<T_iter>::iterator_category iterator_category;
#endif

      // ---------- Constructors and destructor ----------------
      // default constructor
      MCListItr();
      // constructor based on the STL implemented iterator for the
      // list of T* (takes double-dereferencing to get to T)
      MCListItr( const T_iter& anIterator );

      // copy constructor
      MCListItr( const self& rhs );

      // assignment operator
      const self& operator=( const self& rhs );

      virtual ~MCListItr();

      // ---------- member functions ---------------------------
      self& operator++();
      self  operator++(int);

      self& operator--();
      self  operator--(int);

      self& operator+=( relative_address n);
      self& operator-=( relative_address n);
      
      // dereferencing operators
      T_return& operator*();
      T_return* operator->();

      // ---------- const member functions ---------------------

      // comparison operators
      DABoolean operator==( const self& anMCListItr ) const;
      DABoolean operator!=( const self& anMCListItr ) const;

      // iterator addition/subtraction
      self  operator+(  relative_address n) const;
      self  operator-(  relative_address n) const;

   protected:
      // --------- not intended for public use -----------
      const T_iter& bareIterator() const;

   private:
      // ---------- data members -------------------------------
      T_iter m_iterator;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "MCInfo/MCDecayTree/Template/MCListItr.cc"
#endif

#endif /* MCINFO_MCLISTITR_H */
