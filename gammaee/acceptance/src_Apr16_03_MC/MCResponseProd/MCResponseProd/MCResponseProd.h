#if !defined(MCRESPONSEPROD_MCRESPONSEPROD_H)
#define MCRESPONSEPROD_MCRESPONSEPROD_H
// -*- C++ -*-
//
// Package:     <MCResponseProd>
// Module:      MCResponseProd
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      John J O'Neill
// Created:     Mon Apr 12 11:12:11 EDT 1999
// $Id: MCResponseProd.h,v 1.11 2002/09/27 20:28:10 bkh Exp $
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "ToolBox/HistogramPackage.h"

// for suez run time parameters
#include "CommandPattern/Parameter.h"
#include "CommandPattern/Menu.h"


// forward declarations
#include "STLUtility/fwd_vector.h"
class Frame;
class ProxyBase;
class MCDecayTree;

class MCResponseProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      MCResponseProd( void );                      // anal1 
      virtual ~MCResponseProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( TBHistoManager& );                  

      // method to update begin run info, if needed
      void updateCleogBeginRun( Frame& iFrame );
      
      // triggerGeantEvent - calls cgtrig to trigger Geant event
      void triggerGeantEvent( Frame& iFrame );

      // invalidateGeantEvent - says that we need to trigger Geant for this event
      void invalidateGeantEvent();

      // validateGeantEvent - says that we need have triggered Geant for this event
      void validateGeantEvent();
      
      // returns the geant-modified decay tree for this event
      MCDecayTree* geantModifiedDecayTree();
      void deleteGeantModifiedDecayTree();

      // MCResponse Proxies which have a pointer back to the producer
      ProxyBase* makeMCSVResponseProxy();
      ProxyBase* makeMCDRResponseProxy();
      ProxyBase* makeMCZDResponseProxy();
      ProxyBase* makeMCCathodesResponseProxy();
      ProxyBase* makeMCRichResponseProxy();
      ProxyBase* makeMCCCResponseProxy();
      ProxyBase* makeMCMUResponseProxy();
      ProxyBase* makeMCTotalDecayTreeProxy();

      // parameters stating for which detector components responses 
      // are wanted
      Parameter<DABoolean> m_getSVResponses;
      Parameter<DABoolean> m_getDRResponses;
      Parameter<DABoolean> m_getZDResponses;
      Parameter<DABoolean> m_getCathodesResponses;
      Parameter<DABoolean> m_getRichResponses;
      Parameter<DABoolean> m_getCCResponses;
      Parameter<DABoolean> m_getMUResponses;

      // ------------ const member functions ----------------------
      const char* identifier() const;

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      MCResponseProd( const MCResponseProd& );

      // ------------ assignment operator(s) ----------------------
      const MCResponseProd& operator=( const MCResponseProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------
      // m_geantInitialized(init to false) - flags whether we have made to
      //     the geant initialization phase (in init()) so that the destructor 
      //     knows whether or not to "stand down" geant/zebra
      // m_geantGeomInit   (default false) - If true, Geant Geometry has been initialized
      // m_geantEventValid (default false) - If true, Geant has been triggered for this event
      // m_cachedRunNumber (default 0)     - run # that cleog used to update begin run constants
      // m_geantModifiedDecayTree          - pointer to the decay Tree for this
      //                                     event, with GEANT mods added
      // m_useKuip         (default false) - true call KUIP at begin job for Geant "Experts"
      // m_kuipEveryEvent  (default false) - true call KUIP for each event for Geant "Experts"
      // m_useFFRead       (default false) - true call FFREAD at begin job for Geant "Experts"
      // m_geantBatchMode  (default true)  - sets Geant BATCH variable
      // m_dumpGeantBanks  (default true)  - true prints selected Geants banks 
      DABoolean m_geantInitialized;
      DABoolean m_geantGeomInit;
      DABoolean m_geantEventValid;
      UInt32 m_cachedRunNumber;
      MCDecayTree* m_geantModifiedDecayTree;
      Parameter<DABoolean> m_useKuip;
      Parameter<DABoolean> m_kuipEveryEvent;
      Parameter<DABoolean> m_useFFRead;
      Parameter<DABoolean> m_geantBatchMode;
      Parameter<DABoolean> m_printGeantBanks;

      // parameters stating for which detector components the GEANT
      // geometry is wanted
      Parameter<DABoolean> m_doSVGeom;
      Parameter<DABoolean> m_doDRGeom;
      Parameter<DABoolean> m_doZDGeom;
      Parameter<DABoolean> m_doRichGeom;
      Parameter<DABoolean> m_doCCGeom;
      Parameter<DABoolean> m_doMUGeom;

      // ------------ static data members -------------------------

};

// inline function definitions


// Revision history
//
// $Log: MCResponseProd.h,v $
// Revision 1.11  2002/09/27 20:28:10  bkh
// Add ZD
//
// Revision 1.10  2001/04/14 06:08:44  mahlke
// changed handover of doXXGeom flags to BuildGeantGeometry; now using a class
//
// Revision 1.9  2001/04/09 14:24:36  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.8  2000/06/02 01:11:23  lkg
// DABoolean member fcn added to track whether the GEANT initialization
// phase has happened (in call to init).  Used to prevent zebra manipulation
// in destructor from happening in the case that something goes wrong after
// MCResponseProd constructor but before init is called.
//
// Revision 1.7  2000/05/22 16:04:45  jjo
// Add Suez run-time parameters for:
// 1) Make FFREAD optional by default - turned on via Suez run
// time parameter.  2) Set Geant "BATCH" flag to true by default,
// if BATCH=false, Geant will prompt user for Higz window to open.
//
// Revision 1.6  2000/04/19 17:25:26  lkg
// Added deleteGeantModifiedDecayTree(), which allows MCResponseProd to
// effectively do the memory management for the decay tree it initially
// creates
//
// Revision 1.5  2000/01/26 23:41:53  lkg
// * new member item: a pointer to the geant-modified MCDecayTree
// * new member function to return above pointer
// * new proxy factory stuff: makeMCTotalDecayTreeProxy
//
// Revision 1.4  1999/11/09 19:04:41  jjo
// Add suez parameter m_printGeantBanks to printout geant banks
//
// Revision 1.3  1999/10/13 17:05:10  jjo
// Add Suez parameter m_kuipEveryEvent to call KUIP before every event
//
// Revision 1.2  1999/05/03 20:21:32  jjo
// Reorganize code to make running Cleog under Suez more robust
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//

#endif /* MCRESPONSEPROD_MCRESPONSEPROD_H */


