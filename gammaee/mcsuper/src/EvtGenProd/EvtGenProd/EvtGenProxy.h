// -*- C++ -*-
#if !defined(PACKAGE_EVTGENPROXY_H)
#define PACKAGE_EVTGENPROXY_H
//
// Package:     EvtGenProd
// Module:      EvtGenProxy
//
/**\class EvtGenProxy EvtGenProxy.h package/EvtGenProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Anders Ryd
// Created:     Sun Sep 14 16:51:22 EDT 2003
// $Id: EvtGenProxy.h,v 1.2 2003/10/14 20:32:43 ryd Exp $
//
// Revision history
//
// $Log: EvtGenProxy.h,v $
// Revision 1.2  2003/10/14 20:32:43  ryd
// Switch to jetset; bug fixes for initial quarks
//
// Revision 1.1.1.1  2003/10/07 02:48:56  ryd
// imported EvtGenProd sources
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"

// forward declarations
class EvtGenGenerator;

class EvtGenProxy : public ProxyBindableTemplate< MCDecayTree >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCDecayTree value_type;

      // Constructors and destructor
      EvtGenProxy(const string& decayfile, const string& udecayfile,
		  const string& evtpdl);
      virtual ~EvtGenProxy();

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
      EvtGenProxy( const EvtGenProxy& );

      // assignment operator(s)
      const EvtGenProxy& operator=( const EvtGenProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (EvtGenProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_EvtGenMCDecayTree ;

      EvtGenGenerator* m_EvtGenGenerator;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "package/Template/EvtGenProxy.cc"
//#endif

#endif /* PACKAGE_EVTGENPROXY_H */



