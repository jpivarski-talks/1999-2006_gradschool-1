// -*- C++ -*-
#if !defined(PACKAGE_TMCLASSIFICATIONPROXY_H)
#define PACKAGE_TMCLASSIFICATIONPROXY_H
//
// Package:     <package>
// Module:      TMClassificationProxy
//
/**\class TMClassificationProxy TMClassificationProxy.h package/TMClassificationProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Tue Oct 22 14:49:18 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "Trkman/TMClassification.h"

// forward declarations

class TMClassificationProxy : public ProxyBindableTemplate< TMClassification >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef TMClassification value_type;

      // Constructors and destructor
      TMClassificationProxy();
      virtual ~TMClassificationProxy();

      // member functions

      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      TMClassificationProxy( const TMClassificationProxy& );

      // assignment operator(s)
      const TMClassificationProxy& operator=( const TMClassificationProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (TMClassificationProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_TMClassification ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "package/Template/TMClassificationProxy.cc"
//#endif

#endif /* PACKAGE_TMCLASSIFICATIONPROXY_H */
