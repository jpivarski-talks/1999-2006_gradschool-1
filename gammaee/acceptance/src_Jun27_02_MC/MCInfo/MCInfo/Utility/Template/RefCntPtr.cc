// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      RefCntPtr
// 
// Description: Reference-counting pointer
//
// Implementation:
//     The class T must supply member functions to manage the number of
//     references pointing to it:
//        void T.addReference()
//        void T.removeReference()
//        DABoolean T.hasRefs()
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:37 EST 1999
// $Id: RefCntPtr.cc,v 1.1 1999/06/22 21:30:23 lkg Exp $
//
// Revision history
//
// $Log: RefCntPtr.cc,v $
// Revision 1.1  1999/06/22 21:30:23  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
//#include "Experiment/report.h"
#include "MCInfo/Utility/RefCntPtr.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.RefCntPtr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: RefCntPtr.cc,v 1.1 1999/06/22 21:30:23 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
template<class T>
RefCntPtr<T>::RefCntPtr() : m_pointer( 0 )
{}

template<class T>
RefCntPtr<T>::RefCntPtr( T* aPointer ) :
   m_pointer( aPointer ) 
{
   if ( 0 != m_pointer ) { m_pointer->addReference(); }
}

template<class T>
RefCntPtr<T>::RefCntPtr( const RefCntPtr<T>& rhs ) :
   m_pointer( rhs.m_pointer ) 
{
   if ( 0 != m_pointer ) { m_pointer->addReference(); }
}

template<class T>
RefCntPtr<T>::~RefCntPtr()
{
   // eliminate the reference to the manager that "this" pointer
   // currently points at (if any)
   if ( 0 != m_pointer ) {
      m_pointer->removeReference();
      // delete that manager if this was the last pointer to it
      if ( ! (m_pointer->hasRefs()) ) { delete m_pointer; }
   }
}

//
// assignment operators
//
template<class T>
const RefCntPtr<T>& 
RefCntPtr<T>::operator=( const RefCntPtr<T>& rhs ) {

  if( this != &rhs ) {
     // first, eliminate the reference to the manager that "this" pointer
     // currently points at (if any)
     if ( 0 != m_pointer ) {
	m_pointer->removeReference();
	// delete that manager if this was the last pointer to it
	if ( ! (m_pointer->hasRefs()) ) { delete m_pointer; }
     }

     // now update pointer, to "rhs"'s pointer, and update the reference
     // count of the manager (if any) to which "this" now points
     m_pointer = rhs.m_pointer;
     if ( m_pointer != 0 ) { m_pointer->addReference(); }
  }

  return *this;
}

//
// member functions
//
template<class T>
T& RefCntPtr<T>::operator*() {
 
   assert( 0 != m_pointer );
   return *m_pointer;
}
//
// const member functions
//
template<class T>
DABoolean 
RefCntPtr<T>::operator==( const RefCntPtr<T>& anotherPtr ) const {
   return m_pointer == anotherPtr.m_pointer;
}

template<class T>
DABoolean 
RefCntPtr<T>::operator!=( const RefCntPtr<T>& anotherPtr ) const {
   return m_pointer != anotherPtr.m_pointer;
}

template<class T>
const T& RefCntPtr<T>::operator*() const {
 
   assert( 0 != m_pointer );
   return *m_pointer;
}
//
// static member functions
//
