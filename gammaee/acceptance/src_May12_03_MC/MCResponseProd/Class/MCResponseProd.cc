// -*- C++ -*-
//
// Package:     <MCResponseProd>
// Module:      MCResponseProd
// 
// Description: Producer for MCResponse objects (RAWM stage in CLEO-II).
//              Currently this producer also creates Geant hits
//              and makes all calls to Geant.
//              This producer also results in an updated decay tree
//
// Implementation:
//
//
// Author:      John J O'Neill
// Created:     Mon Apr 12 11:34:57 EDT 1999
// $Id: MCResponseProd.cc,v 1.24 2002/09/27 20:27:56 bkh Exp $
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCResponseProd/MCResponseProd.h"
#include "Experiment/report.h"
#include "Experiment/fortran_types.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"

#include "FrameAccess/FAItem.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/insert.h"

// Run, Event objects
#include "CleoDB/DBRunHeader.h"
#include "CleoDB/DBEventHeader.h"

// MC Response proxies
#include "MCResponseProd/MCSVResponseProxy.h"
#include "MCResponseProd/MCDRResponseProxy.h"
#include "MCResponseProd/MCZDResponseProxy.h"
#include "MCResponseProd/MCCathodesResponseProxy.h"
#include "MCResponseProd/MCRichResponseProxy.h"
#include "MCResponseProd/MCCCResponseProxy.h"
#include "MCResponseProd/MCMUResponseProxy.h"
#include "MCResponseProd/MCTotalDecayTreeProxy.h"

#include "MCResponseProd/BuildGeantGeometry.h"
#include "DRMCUtil/InitDRMCFrameBrokers.h"

// MCDecayTree-related
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "G3DecayTree/G3DecayTree.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

#include "FortranInterface/FortranInterfacer.h"

// Fortran routines
//   setup_geant - GEANT begin job calls taken from gxint.F
//   set_geant_run - set Geant run number
//   setup_kuip - initialize KUIP
//   cleog_update_br - Cleog update begin run constants
//   usbrun - Geant user begin run routine
//   cleog_trig - routine to trigger Geant for the event
//   uglast - Geant user end of job call
//   paexit - CERN routine to exit & cleanup from paw
//   gpvolu - Geant routine to print geant volumes
//   gpmate - Geant routine to print geant materials
//   gptmed - Geant routine to print geant tracking media


//
extern "C" {
   extern void setup_geant_( FLogical& UseFFRead, FLogical& BatchMode );
   extern void set_geant_run_( const FInteger& runNumber);
   extern void setup_kuip_();
   extern void kuwhag_();
   extern void cleog_update_br_();
   extern void usbrun_();
   extern void cleog_trig_( const FInteger& runNumber,
			    const FInteger& eventNumber );
   extern void uglast_();
   extern void paexit_();
   extern void gpvolu_( FInteger& n );
   extern void gpmate_( FInteger& n );
   extern void gptmed_( FInteger& n );

   //extern void print_histograms_();
}

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "MCResponseProd.MCResponseProd" ;
static const char* const kIdentifierString = "GeantResponse";

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCResponseProd.cc,v 1.24 2002/09/27 20:27:56 bkh Exp $";
static const char* const kTagString = "$Name: v06_02_06 $";


//
// static data member definitions
//

//
// constructors and destructor
//
MCResponseProd::MCResponseProd( void )               // anal1
   : Producer( "MCResponseProd" ),
     m_geantInitialized( false ),
     m_geantGeomInit (false), 
     m_geantEventValid (false),
     m_cachedRunNumber( 0 ),
     m_useKuip( "UseKuip", this, false ),
     m_kuipEveryEvent( "KuipEveryEvent", this, false ),
     m_useFFRead( "UseFFRead", this, false ),
     m_geantBatchMode ("GeantBatch", this, true ),
     m_printGeantBanks( "PrintGeantBanks", this, true ),
     m_geantModifiedDecayTree( 0 ),
     m_doSVGeom ( "SVGeom", this, true ),
     m_doDRGeom ( "DRGeom", this, true ),
     m_doZDGeom ( "ZDGeom", this, true ),
     m_doRichGeom ( "RichGeom", this, true ),
     m_doCCGeom ( "CCGeom", this, true ),
     m_doMUGeom ( "MUGeom", this, true ),
     m_getSVResponses( "SVResponses", this, true ),
     m_getDRResponses( "DRResponses", this, true ),
     m_getZDResponses( "ZDResponses", this, true ),
     m_getCathodesResponses( "CathodesResponses", this, true ),
     m_getRichResponses( "RichResponses", this, true ),
     m_getCCResponses( "CCResponses", this, true ),
     m_getMUResponses( "MUResponses", this, true )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;
   
   // add help texts for Suez run-time parameters
   m_useKuip.setHelpString(
      "Boolean, if true calls KUIP at begin job to enter interactive Geant commands. Default is false \n" );
   m_kuipEveryEvent.setHelpString(
      "Boolean, if true calls KUIP each event to enter interactive Geant commands. Default is false \n" );
   m_useFFRead.setHelpString(
      "Boolean, if true calls FFREAD at begin job. Default is false \n" );
   m_geantBatchMode.setHelpString(
      "Boolean, sets Geant BATCH variable. Default is true \n" );
   m_printGeantBanks.setHelpString(
      "Boolean, if true dumps selected Geant banks at begin job. Default is true \n" );
   m_doSVGeom.setHelpString ( 
      "Boolean, enables building SV GEANT geometry \n");
   m_doDRGeom.setHelpString ( 
      "Boolean, enables building DR GEANT geometry \n");
   m_doZDGeom.setHelpString ( 
      "Boolean, enables building ZD GEANT geometry \n");
   m_doRichGeom.setHelpString ( 
      "Boolean, enables building Rich GEANT geometry \n");
   m_doCCGeom.setHelpString ( 
      "Boolean, enables building CC GEANT geometry \n");
   m_doMUGeom.setHelpString ( 
      "Boolean, enables building MU GEANT geometry \n");
   m_getSVResponses.setHelpString ( 
      "Boolean, enables getting SV responses back \n");
   m_getDRResponses.setHelpString ( 
      "Boolean, enables getting DR responses back \n");
   m_getZDResponses.setHelpString ( 
      "Boolean, enables getting ZD responses back \n");
   m_getCathodesResponses.setHelpString ( 
      "Boolean, enables getting Cathodes responses back \n");
   m_getRichResponses.setHelpString ( 
      "Boolean, enables getting Rich responses back \n");
   m_getCCResponses.setHelpString ( 
      "Boolean, enables getting CC responses back \n");
   m_getMUResponses.setHelpString ( 
      "Boolean, enables getting MU responses back \n");

   // ----- register proxy factories ------------------
   // (Please see the "ProxyExample" library for examples!)
   //
   // Two steps: 1) use "registerProxyFactory" to register
   //            2) instantiate ProxyFactory/Function
   //               (if you're using the standard templated factories;
   //                you may of course roll your own!)

   // Proxy Registration Step 1 (default-ctor proxy):

   // Proxy Registration Step 1 (non-default-ctor proxy):
   // sv response
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryFunction< MCResponseProd, MCSVResponseProxy >
			 ( *this, &MCResponseProd::makeMCSVResponseProxy ),
			 UsageTag() );    // or UsageTag( "MyUsage" )
   // dr anode response
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryFunction< MCResponseProd, MCDRResponseProxy >
			 ( *this, &MCResponseProd::makeMCDRResponseProxy ),
			 UsageTag() );    // or UsageTag( "MyUsage" )
   // zd anode response
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryFunction< MCResponseProd, MCZDResponseProxy >
			 ( *this, &MCResponseProd::makeMCZDResponseProxy ),
			 UsageTag() );    // or UsageTag( "MyUsage" )
   // dr cathode response
   registerProxyFactory( Stream::kEvent, 
 			 new ProxyFactoryFunction< MCResponseProd, MCCathodesResponseProxy >
 			 ( *this, &MCResponseProd::makeMCCathodesResponseProxy ),
 			 UsageTag() );    // or UsageTag( "MyUsage" )
   // rich response
   registerProxyFactory( Stream::kEvent, 
   			 new ProxyFactoryFunction< MCResponseProd, MCRichResponseProxy >
   			 ( *this, &MCResponseProd::makeMCRichResponseProxy ),
   			 UsageTag() );    // or UsageTag( "MyUsage" )
   // cc response
   registerProxyFactory( Stream::kEvent, 
   			 new ProxyFactoryFunction< MCResponseProd, MCCCResponseProxy >
   			 ( *this, &MCResponseProd::makeMCCCResponseProxy ),
   			 UsageTag() );    // or UsageTag( "MyUsage" )
   // mu response
   registerProxyFactory( Stream::kEvent, 
   			 new ProxyFactoryFunction< MCResponseProd, MCMUResponseProxy >
   			 ( *this, &MCResponseProd::makeMCMUResponseProxy ),
   			 UsageTag() );    // or UsageTag( "MyUsage" )
   // update decay tree
   registerProxyFactory( Stream::kEvent, 
   			 new ProxyFactoryFunction< MCResponseProd, MCTotalDecayTreeProxy >
   			 ( *this, &MCResponseProd::makeMCTotalDecayTreeProxy ),
   			 UsageTag() );    // or UsageTag( "MyUsage" )
}

// Proxy Registration Step 2:  template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< MCResponseProd, MCSVResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCDRResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCZDResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCCathodesResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCRichResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCCCResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCMUResponseProxy >;
template class ProxyFactoryFunction< MCResponseProd, MCTotalDecayTreeProxy >;

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)

// MCResponseProd::MCResponseProd( const MCResponseProd& iMCResponseProd )
// {
//    *this = iMCResponseProd;
// }

MCResponseProd::~MCResponseProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

   // debugging hbook - print histograms
   //print_histograms_();
   
   if ( m_geantInitialized ) {
     report( DEBUG, kFacilityString ) << "Calling UGLAST - Geant User end of job routine" << endl;
     uglast_();

     report( DEBUG, kFacilityString ) << "Calling PAEXIT to exit from PAW/Geant" << endl;
     paexit_();
   }

}

//
// assignment operators
//
// const MCResponseProd& MCResponseProd::operator=( const MCResponseProd& iMCResponseProd )
// {
//   if( this != &iMCResponseProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iMCResponseProd );
//   }
//
//   return *this;
// }


//
// member functions
//

void MCResponseProd::updateCleogBeginRun( Frame& iFrame )
{
   // This method will update Cleog begin run info if it hasn't been done for this run
   // Not sure if this is the best way to do this, but we need a way when we extract
   // each subdetectors MCResponse objects from the Frame to be able to check if the
   // begin run info has been updated, if needed.  So I save run # in m_cachedRunNumber.
   

   // Get the run # from the Frame
   DBRunHeader runHeader( iFrame.record(Stream::kBeginRun).syncValue().runNumber() );

   // Build Cleog Geometry
   // One cannot redefine the Geant geometry in the middle of the job
   // so Cleog needs to check if the geometry has been updated and if
   // so, stop the job because we cannot update the Geant geometry.
   //report( WARNING, kFacilityString )
   //   << "********************************************" << endl
   //   << "Need to check if Geometry data is still valid" << endl
   //   << "If Geometry data has changed, need to end the job" << endl
   //   << "As one cannot update the Geant Geometry in the middle of the job" << endl
   //   << "********************************************" << endl;


   // If run # != cached value, then update begin run.
   // Also, build Geant geometry the first time.
   if ( runHeader.number() != m_cachedRunNumber )
   {
      report( DEBUG, kFacilityString )
	 << "Updating Cleog BeginRun info via CLEOG_UPDATE_BR from updateCleogBeginRun()" << endl
	 << "Old Run Number = " << m_cachedRunNumber << endl
	 << "New Run Number = " << runHeader.number() << endl; 

      // After we know the geometry constants are valid for this run, 
      // Set Geant run number after converting to Fortran type
      FInteger runNumber = runHeader.number();
      set_geant_run_( runNumber );

      // Update cleog begin run constants - This should change in the Suez environment
      // This sets the JRUNG bank with the run number.  Before this call this value is
      // 0 because we dont set the run # via FFREAD card at the begining of the job.
      cleog_update_br_();

      // Begin run update for DR related items
      if ( m_doDRGeom.value() != 0 ) {
        InitDRMCFrameBrokers( iFrame );
      } else {
        report( DEBUG, kFacilityString ) << "InitDRMCFrameBrokers *** NOT EXECUTED ***" 
                                         << endl;
      }

      // Begin run update for ZD related items
      if ( m_doZDGeom.value() != 0 ) {
//        InitZDMCFrameBrokers( iFrame );
      } else {
        report( DEBUG, kFacilityString ) << "InitZDMCFrameBrokers *** NOT EXECUTED ***" 
                                         << endl;
      }

      // Begin run update for CC related items
      if ( m_doCCGeom.value() != 0 ) {
           MCCCResponseProxy::whoAmI()->beginRunProcessing( iFrame );
      } else {
        report( DEBUG, kFacilityString ) << "CC beginRunProcessing *** NOT EXECUTED ***" 
                                         << endl;
      }

      // Create Geant geometry the 1st time and
      // optionally call KUIP user interface for "experts".
      if ( !m_geantGeomInit )
      {
	 // Create Geant Geometry 
	 BuildGeantGeometry geantGeom;

         BuildGeantGeometry::UseComponent iUseComponent(m_doSVGeom.value(),
                                                        m_doDRGeom.value(),
                                                        m_doZDGeom.value(),
                                                        m_doRichGeom.value(),
                                                        m_doCCGeom.value(),
                                                        m_doMUGeom.value());
	 geantGeom.create( iFrame , iUseComponent );

	 if ( m_printGeantBanks.value() )
	 {
	    report( INFO, kFacilityString )
	       << "updateCleogBeginRun() printing selected Geant banks" << endl
	       << "Turn off via MCResponseProd Suez parameter PrintGeantBanks" << endl;
	    FInteger n = 0;
	    gpvolu_(n);
	    gpmate_(n);
	    gptmed_(n);
	 }
	 
	 // Optional KUIP user interface should only be called by geant "experts"
	 // Turned on via suez run time parameters m_useKuip (UseKuip) or
	 // m_kuipEveryEvent (KuipEveryEvent)
	 if ( m_useKuip.value() | m_kuipEveryEvent.value() )
	 {
	    report( INFO, kFacilityString ) << "Calling KUIP for interactive Cleog Commands" << endl;
	    setup_kuip_();
	 }
      

	 // Set flag saying we initialized Geant
	 m_geantGeomInit = true;
      }
      
      // Save cached value of the run number 
      //  waited till now just incase of an exception
      m_cachedRunNumber = runHeader.number();

      // Geant user begin run routine
      usbrun_();
   }
}



// triggerGeantEvent - triggers Cleog/Geant event
void 
MCResponseProd::triggerGeantEvent( Frame& iFrame )
{
   // If Geant hasn't been triggered for this event, trigger it
   if (!m_geantEventValid)
   {
      // Call KUIP every event if Suez parameter m_kuipEveryEvent ("KuipEveryEvent") set
      if ( m_kuipEveryEvent.value() )
      {
	 report( INFO, kFacilityString ) << "Calling KUIP every event" << endl
					 << "Need to leave KUIP prompt with QUIT (DO NOT USE EXIT)"
					 << endl;
	 kuwhag_();
      }
      
      // Get run & event numbers from the Frame
      // iFrame.record(Stream::kBeginRun).syncValue().eventNumber() );
      DBEventHeader eventHeader( 
	 iFrame.record(Stream::kBeginRun).syncValue().runNumber(),
	 iFrame.record(Stream::kEvent).syncValue().eventNumber() );

      // convert to Fortran types
      FInteger runNumber = eventHeader.run();
      FInteger eventNumber = eventHeader.number();
 
      report( DEBUG, kFacilityString )
	 << "Trigger Geant Event via CLEOG_TRIG for Run " <<  runNumber
	 << ", Event "    << eventNumber << endl;


      // get the generator-level MCDecayTree from the frame
      FAItem< MCDecayTree > generatorDecayTree;
      extract( iFrame.record(Stream::kEvent), 
	       generatorDecayTree,
	       "Generator" );
      if ( ! generatorDecayTree.valid() ) {
	 report( ERROR, kFacilityString )
	    << "Could not extract the MC generator decay tree from the frame"
	    << endl;
	 assert( false );
	 ::exit( 1 );
      }
#if defined(CLEO_DEBUG)
      report( DEBUG,  kFacilityString )
	 << "extracted the generator tree:" << endl
	 << *generatorDecayTree << endl;
#endif

      // make a copy of the decay tree that we can modify, and set up the
      // G3DecayTree interface that the GEANT fortran code can talk to
      m_geantModifiedDecayTree = new MCDecayTree( *generatorDecayTree );
      G3DecayTree& g3dInterface( G3DecayTree::instance() );
      g3dInterface.init( *m_geantModifiedDecayTree );

      // prepare to hand the frame to c/c++ called from Fortran
      FortranInterfacer::instance().useFrame( iFrame ); 

      // Call Fortran routine to trigger Cleog/Geant for this event
      cleog_trig_( runNumber, eventNumber);

      // release handle to the frame
      FortranInterfacer::instance().releaseFrame();

      // The Geant event is now valid so set the flag
      validateGeantEvent();
   }

}

// invalidateGeantEvent - we need to trigger Geant for this event
void MCResponseProd::invalidateGeantEvent()
{
   m_geantEventValid = false;
   
}


// validateGeantEvent - we have triggered Geant for this event
void MCResponseProd::validateGeantEvent()
{
   m_geantEventValid = true;
}  

// give access to the GEANT-modifed decay tree
MCDecayTree*
MCResponseProd::geantModifiedDecayTree() {
   return m_geantModifiedDecayTree;
}

void
MCResponseProd::deleteGeantModifiedDecayTree() {
   report( DEBUG, kFacilityString )
      << "About to delete the geant-Modified decay tree, pval = "
      << m_geantModifiedDecayTree
      << endl;

   delete m_geantModifiedDecayTree;
   m_geantModifiedDecayTree = 0 ;

   report( DEBUG, kFacilityString )
      << "done geant-Modified decay tree deletion"
      << endl;
}

// Subdetector proxies get passed a reference to this producer so
// they can call functions of this producer:
// invalidateGeantEvent(), triggerGeantEvent(), updateCleogBeginRun()
ProxyBase* MCResponseProd::makeMCSVResponseProxy()
{
   return new MCSVResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCDRResponseProxy()
{
   return new MCDRResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCZDResponseProxy()
{
   return new MCZDResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCCathodesResponseProxy()
{
   return new MCCathodesResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCRichResponseProxy()
{
   return new MCRichResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCCCResponseProxy()
{
   return new MCCCResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCMUResponseProxy()
{
   return new MCMUResponseProxy( *this );
}

ProxyBase* MCResponseProd::makeMCTotalDecayTreeProxy()
{
   return new MCTotalDecayTreeProxy( *this );
}


// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
MCResponseProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;
   report( INFO, kFacilityString ) << "Parameter settings:" << endl;
   report( INFO, kFacilityString ) << "==================" << endl;
   report( INFO, kFacilityString ) << "SVGeom=" << m_doSVGeom.value() << endl;
   report( INFO, kFacilityString ) << "DRGeom=" << m_doDRGeom.value() << endl;
   report( INFO, kFacilityString ) << "ZDGeom=" << m_doZDGeom.value() << endl;
   report( INFO, kFacilityString ) << "RichGeom=" << m_doRichGeom.value() << endl;
   report( INFO, kFacilityString ) << "CCGeom=" << m_doCCGeom.value() << endl;
   report( INFO, kFacilityString ) << "MUGeom=" << m_doMUGeom.value() << endl;
   report( INFO, kFacilityString ) << "SVResponses=" << m_getSVResponses.value() << endl;
   report( INFO, kFacilityString ) << "DRResponses=" << m_getDRResponses.value() << endl;
   report( INFO, kFacilityString ) << "ZDResponses=" << m_getZDResponses.value() << endl;
   report( INFO, kFacilityString ) << "CathodesResponses=" << m_getCathodesResponses.value() << endl;
   report( INFO, kFacilityString ) << "RichResponses=" << m_getRichResponses.value() << endl;
   report( INFO, kFacilityString ) << "CCResponses=" << m_getCCResponses.value() << endl;
   report( INFO, kFacilityString ) << "MUResponses=" << m_getMUResponses.value() << endl;
   report( INFO, kFacilityString ) << "==================" << endl;
   report( DEBUG, kFacilityString ) << "here in init()" << endl;


   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)


   // setup_geant - Fortran subroutine initializes Geant (calls from gxint.F & gpaw.F)
   // Optionally call FFREAD, determined by m_useFFRead.value()
   // If BatchMode false will prompt user for Higz window.  Default is BatchMode=true
   FLogical FFRead (m_useFFRead.value());
   FLogical BatchMode (m_geantBatchMode.value());
   report( DEBUG, kFacilityString ) << "Initialize Geant under Suez via setup_geant_()" << endl;
   setup_geant_( FFRead, BatchMode );
   m_geantInitialized = true;
}

// -------------------- terminate method ----------------------------
void
MCResponseProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
MCResponseProd::hist_book( TBHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//
const char*
MCResponseProd::identifier() const {
   return kIdentifierString;
}
//
// static member functions
//



// Revision history
//
// $Log: MCResponseProd.cc,v $
// Revision 1.24  2002/09/27 20:27:56  bkh
// Add ZD
//
// Revision 1.23  2001/04/16 05:16:42  savinov
// FortranInterfacer is used to hand the frame to muon c/c++ utilities called from Fortran
//
// Revision 1.22  2001/04/14 06:07:56  mahlke
// changed handover of doXXGeom flags to BuildGeantGeometry; now using a class
//
// Revision 1.21  2001/04/09 14:24:08  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.20  2000/12/08 21:51:46  cdj
// made more exception safe
//
// Revision 1.19  2000/06/02 01:11:41  lkg
// DABoolean member fcn added to track whether the GEANT initialization
// phase has happened (in call to init).  Used to prevent zebra manipulation
// in destructor from happening in the case that something goes wrong after
// MCResponseProd constructor but before init is called.
//
// Revision 1.18  2000/05/22 16:00:08  jjo
// 1) Make FFREAD optional by default - turned on via Suez run
// time parameter.  2) Set Geant "BATCH" flag to true by default,
// if BATCH=false, Geant will prompt user for Higz window to open.
//
// Revision 1.17  2000/04/19 17:25:17  lkg
// Added deleteGeantModifiedDecayTree(), which allows MCResponseProd to
// effectively do the memory management for the decay tree it initially
// creates
//
// Revision 1.16  2000/04/19 00:44:20  pg
// Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
//
// Revision 1.15  2000/03/24 23:14:25  bkh
// Get CC constants for use of gradients
//
// Revision 1.14  2000/03/08 22:38:36  pg
// Forgot to commit changes to Si hit production.
//
// Revision 1.13  2000/02/15 00:51:18  jjo
// Call InitDRMCFrameBrokers instead of  DRMCUpdateBeginRun which is no longer used.
//
// Revision 1.12  2000/01/26 23:36:32  lkg
// Add interface for to feed generator particles from MCDecayTree -> GEANT and
// get the decay tree updated
// 1) register/create the MCTotalDecayTree proxy
// 2) In triggerGeantEvent
//     - extract the Generator-level decay tree from the frame
//     - copy that decay tree to a decay tree that can be modified.  This
//       is done on the heap, so that it can persist, being served via
//       the MCTotalDecayTree proxy, but will get cleared by the frame at the
//       end of the event
//     - set a pointer member item to the copy for this event so that
//       the MCTotalDecayTree proxy can serve up the correct Tree
//     - initialize the G3DecayTree interface class with the copy
// 3) implement a member function geantModifiedDecayTree() that returns
//    a pointer to the modified copy
//
// Revision 1.11  1999/12/08 00:27:07  jjo
// Add print_histograms to print hists - commented out by default.
// Can't get histogram output so print them if desired
//
// Revision 1.10  1999/11/18 19:50:32  jjo
// improve kuip help string
//
// Revision 1.9  1999/11/16 20:50:43  pg
// Added Si simulation
//
// Revision 1.8  1999/11/09 19:10:04  jjo
// Added suez parameter m_printGeantBanks to printout geant banks
//
// Revision 1.7  1999/10/19 16:21:43  jjo
// Include DRMCUpdateBeginRun.h
//
// Revision 1.6  1999/10/19 16:07:11  jjo
// Add call to DRMCUpdateBeginRun which was accidently removed
//
// Revision 1.5  1999/10/13 17:05:28  jjo
// Add Suez parameter m_kuipEveryEvent to call KUIP before every event
//
// Revision 1.4  1999/05/28 16:21:11  jjo
// Comment out report message for every event
//
// Revision 1.3  1999/05/03 20:33:53  jjo
// Fix typo
//
// Revision 1.2  1999/05/03 20:21:16  jjo
// Reorganize code to make running Cleog under Suez more robust
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
