// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCListItr
// 
// Description: A smart pointer that implements an iterator over a
//              container of T*, eliminating the need for users to
//              double dereference.
//
// Implementation:
//     This just holds an STL list iterator, with the dereferencing
//     operators performing the first level of iteration, returning
//     either a T* (->) or a T& (*).
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 17:09:44 EST 1999
// $Id: MCListItr.cc,v 1.4 2001/09/10 20:04:37 cleo3 Exp $
//
// Revision history
//
// $Log: MCListItr.cc,v $
// Revision 1.4  2001/09/10 20:04:37  cleo3
// removed unnecessary includes for list
//
// Revision 1.3  2001/05/12 17:44:06  lkg
// implement access to bare iterator and let MCPPStoreItr have access
//
// Revision 1.2  2000/05/01 22:48:07  lkg
// added valueType as an additional template parameter to make this more STL-like for StorageHelper -- entire scheme should get reevaluated
//
// Revision 1.1  1999/06/22 21:30:09  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files

// user include files
//#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCListItr.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCListItr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCListItr.cc,v 1.4 2001/09/10 20:04:37 cleo3 Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>::MCListItr()
{}

template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>::MCListItr( const T_iter& anIterator ) :
   m_iterator( anIterator )
{}

template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>::MCListItr( const MCListItr<T_iter, T_return, T_valueType>& rhs ) :
   m_iterator( rhs.m_iterator )
{}

template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>::~MCListItr()
{
}

//
// assignment operators
//
template<class T_iter, class T_return, class T_valueType>
const MCListItr<T_iter, T_return, T_valueType>& 
MCListItr<T_iter, T_return, T_valueType>::operator=(const MCListItr<T_iter, T_return, T_valueType>& rhs)
{
  if( this != &rhs ) 
  {
     
     m_iterator = rhs.m_iterator;
  }

  return *this;
}

//
// member functions
//
template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>&
MCListItr<T_iter, T_return, T_valueType>::operator++()        // prefix
{
   ++m_iterator;
   return *this;
}

template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>
MCListItr<T_iter, T_return, T_valueType>::operator++(int)     // postfix
{
   MCListItr<T_iter, T_return, T_valueType> before( *this );
   ++(*this); // use prefix operator
   return( before );
}


template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>&
MCListItr<T_iter, T_return, T_valueType>::operator--()        // prefix
{
   --m_iterator;
   return *this;
}


template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>
MCListItr<T_iter, T_return, T_valueType>::operator--(int)     // postfix
{
   MCListItr<T_iter, T_return, T_valueType> before( *this );
   --(*this); // use prefix operator
   return ( before );
}


template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>&
MCListItr<T_iter, T_return, T_valueType>::operator+=( relative_address n )
{
   for ( relative_address i = 0; i != n; ++i, ++*this ) {}
   return *this;
}


template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>&
MCListItr<T_iter, T_return, T_valueType>::operator-=( relative_address n )
{
   for ( relative_address i = 0; i != n; ++i, --*this ) {}
   return *this;
}


//
// const member functions
//

template<class T_iter, class T_return, class T_valueType>
T_return&
MCListItr<T_iter, T_return, T_valueType>::operator*()
{
   return( **m_iterator );
}


template<class T_iter, class T_return, class T_valueType>
T_return*
MCListItr<T_iter, T_return, T_valueType>::operator->()
{
   return( *m_iterator );
}


template<class T_iter, class T_return, class T_valueType>
DABoolean
MCListItr<T_iter, T_return, T_valueType>::operator==( const self& anMCListItr ) const
{
   return ( m_iterator == anMCListItr.m_iterator );
}


template<class T_iter, class T_return, class T_valueType>
DABoolean
MCListItr<T_iter, T_return, T_valueType>::operator!=( const self& anItr ) const
{
   return !( *this == anItr.m_iterator ); // use ==
}


template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>
MCListItr<T_iter, T_return, T_valueType>::operator+( relative_address n ) const
{
   MCListItr<T_iter, T_return, T_valueType> tempItr( *this );
   for( relative_address i = 0; i != n; ++i, ++tempItr ) {}
   return tempItr;
}


template<class T_iter, class T_return, class T_valueType>
MCListItr<T_iter, T_return, T_valueType>
MCListItr<T_iter, T_return, T_valueType>::operator-( relative_address n ) const
{
   MCListItr<T_iter, T_return, T_valueType> tempItr( *this );
   for( relative_address i = 0; i != n; ++i, --tempItr ) {}
   return tempItr;
}


template<class T_iter, class T_return, class T_valueType>
const T_iter&
MCListItr<T_iter, T_return, T_valueType>::bareIterator() const
{
   return( m_iterator );
}

//
// static member functions
//
