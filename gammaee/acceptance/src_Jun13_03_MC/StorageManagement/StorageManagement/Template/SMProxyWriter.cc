#if !defined(STORAGEMANAGEMENT_SMPROXYWRITER_CC)
#define STORAGEMANAGEMENT_SMPROXYWRITER_CC
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMProxyWriter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon May 24 17:26:44 EDT 1999
// $Id: SMProxyWriter.cc,v 1.3 2000/09/26 21:58:12 cdj Exp $
//
// Revision history
//
// $Log: SMProxyWriter.cc,v $
// Revision 1.3  2000/09/26 21:58:12  cdj
// SMProxyWriter now clears its cache before trying to read new data
//
// Revision 1.2  1999/12/10 14:45:57  cdj
// catches DANoDataException
//
// Revision 1.1.1.1  1999/09/13 21:21:43  cdj
// imported package
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMProxyWriter.h"
#include "DataHandler/RecordMethods.h"
#include "DAException/DANoDataException.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

//static const char* const kFacilityString = "StorageManagement.SMProxyWriter" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMProxyWriter.cc,v 1.3 2000/09/26 21:58:12 cdj Exp $";
//static const char* const kTagString = "$Name: v05_13_05 $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SMProxyWriter::SMProxyWriter()
//{
//}

// SMProxyWriter::SMProxyWriter( const SMProxyWriter& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMProxyWriter::~SMProxyWriter()
//{
//}

//
// assignment operators
//
// const SMProxyWriter& SMProxyWriter::operator=( const SMProxyWriter& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
template <class T>
DABoolean 
SMProxyWriter<T>::extractData( const DataKey& iKey,
			       const Record&  iRecord,
			       SMSinkStream&  iOStream )
{
   DABoolean returnValue = false;

   try {
      //get the proxy
      const ProxyTemplate< T >* proxy = RecordMethods<T>::extractProxy( 
	 iRecord, 
	 iKey.usage(),
	 iKey.production() );
      
      m_data = 0;
      if( 0 != proxy ) {
	 m_data = proxy->get( iRecord, iKey );
      }
      
      if ( 0 != m_data ) {
	 returnValue = true;
      }
   } catch( DANoDataException< T >& ) {
   }
   return returnValue;
}

//
// const member functions
//
template <class T>
void 
SMProxyWriter<T>::writeData( SMSinkStream& iOStream ) const 
{
   m_helper->store( iOStream, *m_data );
}

//
// static member functions
//

#endif /* STORAGEMANAGEMENT_SMPROXYWRITER_CC */
