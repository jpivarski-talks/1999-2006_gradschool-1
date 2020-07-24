// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCCathodesResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCCathodesResponseProxy.cc,v 1.14 2002/05/14 14:31:32 hennessy Exp $
//
// Revision history
//
// $Log: MCCathodesResponseProxy.cc,v $
// Revision 1.14  2002/05/14 14:31:32  hennessy
// protection against array overun
//
// Revision 1.13  2001/05/23 14:34:33  hennessy
// Removed if statement that Brian put in temporarily
//
// Revision 1.12  2001/05/18 23:17:00  hennessy
// Problems with OSF fixed
//
// Revision 1.8  2000/04/19 00:44:19  pg
// Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
//
// Revision 1.7  2000/04/17 20:12:01  bkh
// Elim checks of ptr after new
//
// Revision 1.6  2000/03/24 01:21:09  hennessy
// Implemented cathode response proxy code
//
// Revision 1.5  1999/10/24 20:52:32  cdj
// removed inappropriate use of typename
//
// Revision 1.4  1999/10/22 15:24:18  jjo
// Remove time from cathode responses
//
// Revision 1.3  1999/10/20 22:42:42  jjo
// Use the bulk method to fill cathode responses
//
// Revision 1.2  1999/06/10 20:07:29  bkh
// fix argument ordering problem in add_response usage
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/25 21:30:53  bkh
// Update
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

// Frame access
#include "DataHandler/Frame.h"
#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"

// needed for PROXY_BIND_METHOD
#include "ProxyBind/ProxyBoundMethodAction.h" 

// Producer that calls this proxy
#include "MCResponseProd/MCResponseProd.h"

#include "MCResponseProd/MCCathodesResponseProxy.h"

// sense wire stuff
//#include "DetectorGeometry/DGConstLabVolumePtr.h"
#include "ADRGeomProd/ADRSenseWireStoreFactory.h"
#include "ADRGeom/ADRSenseWireStore.h"
#include "ADRGeom/ADRWireAddress.h"
#include "ADRGeom/ADRCathodeStore.h"

//#include "ADRGeom/ADRWireLayerRealistic.h"
//#include "ADRGeom/ADRWireSurveyConstants.h"
#include "ActiveElements/AEWireInfo.h"
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Vector3D.h"
// Random number generation
#include "RandomModule/RandomGenerator.h"
// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kReport = "MCResponse.MCCathodesResponseProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)

static const char* const kIdString  = "$Id: MCCathodesResponseProxy.cc,v 1.14 2002/05/14 14:31:32 hennessy Exp $";
static const char* const kTagString = "$Name: v05_03_01 $";

//
// static data member definitions
//

MCCathodesResponseProxy* MCCathodesResponseProxy::k_whoAmI ( 0 ) ;

//
// constructors and destructor
//

MCCathodesResponseProxy::MCCathodesResponseProxy( MCResponseProd& iProducer )
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )   
{
   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCCathodesResponseProxy::updateBeginRun, Stream::kBeginRun );
}

// MCCathodesResponseProxy::MCCathodesResponseProxy( const MCCathodesResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCCathodesResponseProxy::~MCCathodesResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const MCCathodesResponseProxy& MCCathodesResponseProxy::operator=( const MCCathodesResponseProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//

void MCCathodesResponseProxy::invalidateCache()
{
   // Tell the producer that we need to trigger geant for the next event
   m_producer->invalidateGeantEvent() ;

   // erase ptr table of MC Response objects
   if ( 0 != m_ptrTable ) 
   {
      (*m_ptrTable).eraseAll() ;
   }
   m_howMany = 0 ;
}

MCCathodesResponseProxy* MCCathodesResponseProxy::whoAmI()
{
   return k_whoAmI ;
}


const MCCathodesResponseProxy::value_type* 
MCCathodesResponseProxy::faultHandler( const Record&  iRecord,
				       const DataKey& iKey )
{


//===============================================================
//   init stuff
//===============================================================

// Phase 1 - run (trigger) Geant for this event.
// m_producer points to this producer (MCResponseProd) and call the 
// function triggerGeantEvent() which will trigger Geant for this 
// event if it hasn't been done yet.
   m_producer->triggerGeantEvent( iRecord.frame() );

   
// Phase 2 - creation of MC Response objects
// Initialize - require ptr table of MC Responses to be empty & initialize m_ho// wMany
   assert( 0 == (*m_ptrTable).size() ); 
   m_howMany = 0 ; 


   // check whether CathodesResponses are wanted at all
   report ( DEBUG, kReport) << "Cathodes Responses wanted: "
                 << m_producer->m_getCathodesResponses.value() << endl;
   // if not, skip adding responses into m_ptrTable

   if (m_producer -> m_getCathodesResponses.value() != 0) {
     



// Phase 3- For each anode response (in layer 47) multiple (20) cathode 
// response objects are created. Probably want to cut out cathode responses
// with no charge later


// Extract simulation parameters
//    Frame& iFrame=iRecord.frame(); 
//    extract( iFrame.record( DRCAStream::kDRCASim ), m_SimDRCA );
//    assert( m_SimDRCA.valid() );

//    float scToIons    = m_SimDRCA[0].scaleToIons();
//    float scToCathode = m_SimDRCA[0].scaleToCathode();
//    float zDiff       = m_SimDRCA[0].zDiffusion();
//    float LayerFrac   = m_SimDRCA[0].innerLayerFrac();	
//    float aParam      = m_SimDRCA[0].aParameter();
//    float bParam      = m_SimDRCA[0].bParameter();	   
    
   
// hardcode Response Constants for now
   float scToIons = 0.15;
   float scToCathode = 4.25;
   float zDiff = 0.001;
   float LayerFrac = 0.1;	
   float aParam = 0.0;
   float bParam = 0.0;	


// I will need some geometry of anodes
   FAItem< ADRSenseWireStore > senseWireStore;
   extract( iRecord.frame().record(Stream::kBaseGeometry), senseWireStore);
   ADRSenseWireStore::LayerWire layerWire;	



// I will need anode response objects
   FATable< MCDRResponse > responses ;
   extract( iRecord, responses );

// I will need a RN gen
   RandomGenerator& ran ( RandomGenerator::instance() ) ;


  // Extract the geometry information
  FAItem< ADRCathodeStore > cathodeGeometry;
  extract( iRecord.frame().record(Stream::kDRAlignment), cathodeGeometry);


//====================================================================
// Loop over the anode responses
// This collates anode response objects
//  we integrate over phi cells belonging to the parent particle
//=====================================================================


  const unsigned int numAnodeCollections = 4000;
  const unsigned int numQDeps = 80;
  
   int   drIDR[numAnodeCollections];
   float xR[numAnodeCollections][numQDeps];
   float yR[numAnodeCollections][numQDeps]; 
   float zR[numAnodeCollections][numQDeps]; 
   float qR[numAnodeCollections][numQDeps]; 
   float dipR[numAnodeCollections][numQDeps];  
   int nAnodes[numAnodeCollections];
   int pidR[numAnodeCollections];
   int layR[numAnodeCollections];
   int wireR[numAnodeCollections];
   int iResp = 0; 
   int iLoop = 0;
   float minRadius=10000.;
   float qTotalR[numAnodeCollections];   
   float mR[numAnodeCollections];
   float mZ[numAnodeCollections];
   float mDipR[numAnodeCollections];
   float mPhiR[numAnodeCollections];
   int  exitPadId = -1;
   int  entrPadId = -1;
   float exitPadZ = 0.;
   float entrPadZ = 0.;
   int increment = 0;
   int j=0;
   int i=0;
   float TwoPi = 6.2831853;
   

// ===========================================================================
/*
  This section loops over anode response objects and saves 
  info from Layers 46 and 47 
  */
// =========================================================================== 
   for ( FATable<MCDRResponse>::const_iterator responseIter=responses.begin();
         responseIter != responses.end() ; ++responseIter )
   {


       int   drID   = responseIter->cellId();   
       LayerWire LastLayer(47,0);

// I only want to consider charges on the last two layers of wires
     if( senseWireStore->layerWire(drID).first==LastLayer.first ||
         senseWireStore->layerWire(drID).first==(LastLayer.first-1))
     {
	
      int indL = senseWireStore->layerWire(drID).first;
      int indW = senseWireStore->layerWire(drID).second;
      
// loop over previous anodes to see if this particle was seen before
      report(DEBUG, kReport) << "---------new anode response object----------- " << endl;
 report(DEBUG, kReport) << "---------new anode response object----------- " << endl;
 report(DEBUG, kReport) << "pid" << responseIter->mcParticleId() << endl;
 report(DEBUG, kReport) << "Layer " <<  indL << endl;
 report(DEBUG, kReport) << "Wire  " <<  indW << endl;
 report(DEBUG, kReport) << "Z of anode" << responseIter->zPosition() << endl; 
 report(DEBUG, kReport) << "X of anode" << responseIter->xPosition() << endl;
 report(DEBUG, kReport) << "Y of anode" << responseIter->yPosition() << endl;
 report(DEBUG, kReport) << "Dip of anode" << responseIter->dipAngle() << endl;
 report(DEBUG, kReport) << "Charge" << responseIter->chargeDep() << endl;
      bool found = false;

      for(iLoop=0; iLoop<iResp; iLoop++){
	 if(responseIter->mcParticleId()==pidR[iLoop]&& 
            indL==layR[iLoop]&&
            abs(senseWireStore->layerWire(drID).second-wireR[iLoop])==1){
	    if(nAnodes[iLoop]<numQDeps){
// watchout for having an intitialized 0 for wireR	    
// also need proper delta for wrap around
	    report(DEBUG, kReport) << "adding to existing" << iLoop << endl;
	    found = true; 
	    
	    xR[iLoop][ nAnodes[iLoop]]=responseIter->xPosition();
	    yR[iLoop][ nAnodes[iLoop]]=responseIter->yPosition();   
	    zR[iLoop][ nAnodes[iLoop]]=responseIter->zPosition();
	    qR[iLoop][ nAnodes[iLoop]]=responseIter->chargeDep();
// no more scaling of anode at this place
//            qR[iLoop][ nAnodes[iLoop]]=abs(qR[iLoop][nAnodes[iLoop]]);
	    dipR[iLoop][ nAnodes[iLoop]]= responseIter->dipAngle();  
            nAnodes[iLoop]++;   
            }else{
	       report(WARNING, kReport) << "Too many anode responses" << endl;
            }
	 }
       }
      if(!found){
	 if(iResp<numAnodeCollections){   
	 report(DEBUG, kReport) << "making new one " << iResp << endl;
	 pidR[iResp] = responseIter->mcParticleId();
	 layR[iResp] = indL;
	 wireR[iResp] = indW;
	 
	 nAnodes[iResp]=0;
	 xR[iResp][ nAnodes[iResp]]=responseIter->xPosition();
	 yR[iResp][ nAnodes[iResp]]=responseIter->yPosition();   
	 zR[iResp][ nAnodes[iResp]]=responseIter->zPosition();
	 qR[iResp][ nAnodes[iResp]]=responseIter->chargeDep();
	 qR[iResp][ nAnodes[iResp]]=abs(1.2*qR[iResp][ nAnodes[iResp]]);
	 dipR[iResp][ nAnodes[iResp]]= responseIter->dipAngle(); 
	 drIDR[iResp] = responseIter->cellId();
	 nAnodes[iResp]++;
	 iResp++;
         }else{
	    report(WARNING, kReport) << "Too many anode responses" << endl; }         
 
      }
     }}  

// ===========================================================================
/*
  This section loops over anode response objects and saves 
  info from Layers 46 and 47 
  */
// =========================================================================== 
// end loop over anode response objects
  report(DEBUG, kReport) << "Done looping Anodes " << iResp << endl;












//==============================================================
// Now loop over collated anodes and produce cathode responses
//==============================================================
//
//  -sum charge 
//  -get minimum radius position
//  -propagate to wire radius
//  -calcualte entrance and exit Zs
//  -get nearest cathode pad to each of entrance and exit Zs
//  -calcualte fraction of charge seen by first and last 
//   cathode
//  -distribute charge over all pads between first and last (inclusve)
//  -make Response objects  
//==============================================================


  
  

// loop over collections of anodes
   for(iLoop=0; iLoop<iResp; iLoop++){
    exitPadId = -1;
    entrPadId = -1;
    exitPadZ = 0.;
    entrPadZ = 0.;


// for each collection of anodes find total Charge and Minumum Radius

    qTotalR[iLoop]=  0.;  
    minRadius=1000.;
    for(j=0; j<nAnodes[iLoop]; j++){
      qTotalR[iLoop]+= qR[iLoop][j];
      float tRadius=sqrt(xR[iLoop][j]*xR[iLoop][j]+yR[iLoop][j]*yR[iLoop][j]);
      if(tRadius<minRadius){
	 minRadius=tRadius;
	 mR[iLoop]=tRadius;
	 mZ[iLoop]=zR[iLoop][j];
	 mDipR[iLoop] = dipR[iLoop][j];
       
      } 
    }
   }


// ===========================================================================
//
// End loop over collections
//
// =========================================================================== 

   report(DEBUG, kReport) << "done looping collections "  << endl;













// loop over collections again and 
// get important Zs of Cell
   float cellZR[numAnodeCollections];
   float exitRadius[numAnodeCollections];
   float entrRadius[numAnodeCollections];
   float exitZ[numAnodeCollections];
   float entrZ[numAnodeCollections];
   float exitZDif[numAnodeCollections];
   float entrZDif[numAnodeCollections];
   float wireRadius = 0.;

      const ADRCathodePanel& dPanel = cathodeGeometry->panel(1);
      unsigned short firstPad = 
		cathodeGeometry->padInPanelOfPadID(1);
      unsigned short secondPad = 
		cathodeGeometry->padInPanelOfPadID(2);
//      cout << " firstPad " << firstPad << endl;
//      cout << " secondPad " << secondPad << endl;
      const ADRCathodePadInfo& padFirst = dPanel.ADRCathodePad(firstPad);   
      const ADRCathodePadInfo& padSecond = dPanel.ADRCathodePad(secondPad);  
//      cout << "zs " << endl;
//      cout << " z1 " << padFirst.point0().z() << endl;
//      cout << " z2 " << padSecond.point0().z() << endl;
      float halfPadWid = abs(padFirst.point0().z()-padSecond.point0().z())/2.;
      float padWid = 2*halfPadWid;   
      float cathodeRadius= dPanel.panelRadius();
      

   int savePanel = 0;

//=========================================================================
//
// loop over collections again - and distribute the charge this time
//
//=========================================================================

   for(iLoop=0; iLoop<iResp; iLoop++){
//      cout << " CellZ " << cellZR[iLoop] << endl;
      HepPoint3D xyz=(senseWireStore->wire(ADRWireAddress(layR[iLoop],wireR[iLoop]))).wirePoint(mZ[iLoop]);
//      cout << " CellZ " << cellZR[iLoop] << endl;
      wireRadius = sqrt(xyz.x()*xyz.x() + xyz.y()*xyz.y() );
// change later to a better calc
      mPhiR[iLoop] = xyz.phi();
      if(mPhiR[iLoop]<0.0){mPhiR[iLoop]=mPhiR[iLoop]+TwoPi;}  
// check this calc for all possibilities
      float deltaR=wireRadius-mR[iLoop];
      float deltaZ=deltaR*tan(mDipR[iLoop]);
      cellZR[iLoop]=mZ[iLoop]+deltaZ;
  report(DEBUG, kReport) << " CellZ " << cellZR[iLoop] << " mZ " << mZ[iLoop] << endl;
      if(layR[iLoop]==47)
      {
	exitRadius[iLoop]=cathodeRadius;

// get radius of field wire for layer 47
// assume half way between 46 and 47 sense wires
        HepPoint3D xyzL46 
        =(senseWireStore->wire(ADRWireAddress(46,0))).wirePoint(cellZR[iLoop]);

        HepPoint3D xyzL47 
        =(senseWireStore->wire(ADRWireAddress(47,0))).wirePoint(cellZR[iLoop]);
	float r46=sqrt(xyzL46.x()*xyzL46.x() + xyzL46.y()*xyzL46.y() );
	float r47=sqrt(xyzL47.x()*xyzL47.x() + xyzL47.y()*xyzL47.y() );  
        entrRadius[iLoop]=(r47+r46)/2.;      	  
      }else
      {  
// get radius of field wire for layer 47
//  assume half way between 46 and 47 sense wires
        HepPoint3D xyzL46 
        =(senseWireStore->wire(ADRWireAddress(46,0))).wirePoint(cellZR[iLoop]);
        HepPoint3D xyzL47 
        =(senseWireStore->wire(ADRWireAddress(47,0))).wirePoint(cellZR[iLoop]);
	float r46=sqrt(xyzL46.x()*xyzL46.x() + xyzL46.y()*xyzL46.y() );
	float r47=sqrt(xyzL47.x()*xyzL47.x() + xyzL47.y()*xyzL47.y() );  
	exitRadius[iLoop]=(r47+r46)/2.;
// get radius of field wire for layer 46
// assume half way between 45 and 46 sense wires
        HepPoint3D xyzL45 
        =(senseWireStore->wire(ADRWireAddress(45,0))).wirePoint(cellZR[iLoop]);
	float r45=sqrt(xyzL45.x()*xyzL45.x() + xyzL45.y()*xyzL45.y() );  
        entrRadius[iLoop]=(r46+r45)/2.;
      }

       exitZ[iLoop]=mZ[iLoop]+(exitRadius[iLoop]-mR[iLoop])*tan(mDipR[iLoop]);
       entrZ[iLoop]=mZ[iLoop]+(entrRadius[iLoop]-mR[iLoop])*tan(mDipR[iLoop]);

 report(DEBUG, kReport) << "entr z " << entrZ[iLoop] << " " << mZ[iLoop] << endl;
 report(DEBUG, kReport) << "exit z " << exitZ[iLoop] << " " << mZ[iLoop] << endl;
       
//       float diffusionZ = 0.001;
       float dSign = 1.;
// expand the charge cloud a little for diffusion
       if(exitZ[iLoop]<entrZ[iLoop]){
	  exitZDif[iLoop]=exitZ[iLoop]-zDiff;
	  entrZDif[iLoop]=entrZ[iLoop]+zDiff;
          dSign = -1.;
       }else{
	  exitZDif[iLoop]=exitZ[iLoop]+zDiff;
	  entrZDif[iLoop]=entrZ[iLoop]-zDiff;
          dSign = 1.;
       }

//saturation should already be counted
      
//  int savePanel=0;
  bool inThisPanel = false;
  bool phiGap = false;
  float fracPhiGap=0.;
  for( unsigned iPanel = ADRCathodeStore::kFirstPanel; 
	iPanel < ADRCathodeStore::kNumberOfPanels;
	++iPanel )
  {

 report(DEBUG, kReport) << " Panel " << iPanel << " is " << endl;

     const ADRCathodePanel& panel = cathodeGeometry->panel(iPanel);
     
     float panelPhiLo = panel.phiMin();
     if(panelPhiLo<0.0){panelPhiLo=panelPhiLo+TwoPi;}     
     float panelPhiHi = panel.phiMax(); 
     if(panelPhiHi<0.0){panelPhiHi=panelPhiHi+TwoPi;}     
     
     if(iPanel==ADRCathodeStore::kNumberOfPanels-1){panelPhiHi = panelPhiHi + TwoPi;}

    unsigned int iNextPanel = iPanel+1;
    if(iNextPanel==ADRCathodeStore::kNumberOfPanels){iNextPanel=ADRCathodeStore::kFirstPanel;}
    const ADRCathodePanel& nextPanel = cathodeGeometry->panel(iNextPanel);
    float nextPanelPhiLo = nextPanel.phiMin(); 
    if(nextPanelPhiLo<0.0){nextPanelPhiLo=nextPanelPhiLo+TwoPi;}      

     if(iPanel==ADRCathodeStore::kNumberOfPanels-1){nextPanelPhiLo = nextPanelPhiLo + TwoPi;}

    inThisPanel = false;

//    cout << " Lo " << panelPhiLo << " phi " << mPhiR[iLoop] << " Hi " << panelPhiHi << " Lo Next " << nextPanelPhiLo << endl;

    if(mPhiR[iLoop]>panelPhiLo&&mPhiR[iLoop]<=panelPhiHi){
       inThisPanel = true;
       phiGap =false;
    }else
    if(mPhiR[iLoop]>panelPhiHi&&mPhiR[iLoop]<=nextPanelPhiLo)   
    {
       inThisPanel = true;
       phiGap = true;
       fracPhiGap = (nextPanelPhiLo-mPhiR[iLoop])/(nextPanelPhiLo-panelPhiHi);
    } 

 report(DEBUG, kReport) << " true or false " << inThisPanel << endl;
    
   if(inThisPanel){
    savePanel = iPanel;
    float minDeltaZexit = 1000.;
    float minDeltaZentr = 1000.;   
    exitPadId = -1;
    entrPadId = -1;
    exitPadZ = 0.;
    entrPadZ = 0.;

    for ( unsigned int ipad = ADRCathodeStore::kFirstPadID; 
	    ipad < ADRCathodeStore::kNumberOfPadsInPanel+ADRCathodeStore::kFirstPadID;
	    ipad++ )
    {
    
//      cout << " checking pad " <<  ipad; 
      
      unsigned short padInPanel = 
	  cathodeGeometry->padInPanelOfPadID( ipad );
      const ADRCathodePadInfo& pad = panel.ADRCathodePad(padInPanel);
//      cout << " checking pad z" <<  pad.point0().z();
      Meters zpos = pad.point0().z();
//      cout << " done " << endl;

      float tDeltaZexit = abs(zpos-exitZDif[iLoop]);
      if(tDeltaZexit<minDeltaZexit){
	 minDeltaZexit = tDeltaZexit;
	 exitPadId=(iPanel*ADRCathodeStore::kNumberOfPadsInPanel)+ipad;	    
         exitPadZ=zpos;
//	 cout << "found minimum of exit" << zpos << " " << exitZDif[iLoop] << endl;
      }
      float tDeltaZentr = abs(zpos-entrZDif[iLoop]);
      if(tDeltaZentr<minDeltaZentr){
	 minDeltaZentr = tDeltaZentr;
	 entrPadId=(iPanel*ADRCathodeStore::kNumberOfPadsInPanel)+ipad;
	 entrPadZ=zpos;
//	 cout << "found minimum of entr" << zpos << " " << exitZDif[iLoop] << endl;
      }
     }     
    }

 } //end loop over panels

  report(DEBUG, kReport) << " done looping panels " << endl;
    
  report(DEBUG, kReport) << "found minimum of entr " << entrPadId << " "  << entrPadZ << " " << entrZDif[iLoop] << endl;    
  report(DEBUG, kReport) << "found minimum of exit " << exitPadId << " "  << exitPadZ << " " << exitZDif[iLoop] << endl;
  int loPadId = entrPadId;
  int hiPadId = exitPadId;
  if( entrPadId > exitPadId){loPadId = exitPadId; hiPadId = entrPadId;}  

// we should have a min and max pads
// time to figure out over lap with ionization

// find fraction of cathode cross

     float fracPad[1536];

      for(i=loPadId; i<hiPadId+1; i++){
        fracPad[i] = 1.;
	   }   


 
//      float dSign = tan(mDipR[iLoop])/abs(tan(mDipR[iLoop]));
    fracPad[entrPadId]=abs((entrPadZ+dSign*halfPadWid)-entrZDif[iLoop])/padWid;
    fracPad[exitPadId]=abs((exitPadZ-dSign*halfPadWid)-exitZDif[iLoop])/padWid;

// handle one pad scenario
      if(entrPadId==exitPadId){fracPad[entrPadId]=abs(exitZDif[iLoop]-entrZDif[iLoop])/padWid;}


// handle endpoints
      if(fracPad[entrPadId]>1.){fracPad[entrPadId]=1.;} 
      if(fracPad[exitPadId]>1.){fracPad[exitPadId]=1.;} 
      
// now we know the proportion of charge on each pad -
// at least on average. Still need to input ionization 
// statistics
      float sumF = 0.;
      for(i=loPadId; i<hiPadId+1; i++){
	 sumF += fracPad[i]; 
      } 
//      float Scale = 0.15; 
      float depQ[1536];
      float sumQ = 0.;
  report(DEBUG, kReport) << " distributing charge" << endl;
  report(DEBUG, kReport) << " qTotalR   " << qTotalR[iLoop] << endl;
  report(DEBUG, kReport) << " sumF " << sumF << endl;
      for(i=loPadId; i<hiPadId+1; i++){
	 report(DEBUG, kReport) << " ID " << i << "frac " << fracPad[i] << endl;
	 
	 float meanQ = scToIons*qTotalR[iLoop]*fracPad[i]/sumF;
	 
	 const double myPoissonRandom ( ran.poisson(meanQ) ) ;
	 report(DEBUG, kReport) << " meanQ " << meanQ << " actQ " << myPoissonRandom << endl;
         depQ[i] = myPoissonRandom;
	 sumQ+=depQ[i];
      }  
      
      if(entrPadId!=-1&&exitPadId!=-1){
      float padQ[ADRCathodeStore::kNumberOfPadsTotal+1];
      float padZ[ADRCathodeStore::kNumberOfPadsTotal+1];

      for(i=1; i<ADRCathodeStore::kNumberOfPadsTotal+1; i++){padQ[i]=0.0;}	     
      
      for(i=loPadId; i<hiPadId+1; i++){
// if by chance poisson fluctuates to 0 total charge then charge
// then protect against divide by zero
	 if(sumQ <= 0){sumQ=1;}
	 
         depQ[i] = scToCathode*depQ[i]*qTotalR[iLoop]/sumQ;
// loop nearby pads to deposit image of this charge
// do this in the frame defined by the current pad and in units 
// of pads in Z.
      const ADRCathodePanel& sPanel = cathodeGeometry->panel(savePanel);
      int iPad=i%ADRCathodeStore::kNumberOfPadsInPanel; 
      if(iPad==0){iPad =192;}
      unsigned short padInPanel = 
      cathodeGeometry->padInPanelOfPadID( iPad );
  report(DEBUG, kReport) << " asking for pad " << padInPanel << endl;
      const ADRCathodePadInfo& pad = sPanel.ADRCathodePad(padInPanel);
      Meters zCenter = pad.point0().z();
      Meters zEdgeHi = zCenter+padWid/2.; 
      Meters zEdgeLo = zCenter-padWid/2.;
      
      int IdOfLastPadInPanel = (savePanel+1)*ADRCathodeStore::kNumberOfPadsInPanel;

      int IdOfFirstPadInPanel = savePanel*ADRCathodeStore::kNumberOfPadsInPanel + 1;


  report(DEBUG, kReport) << " IdOfLastPadInPanel " << IdOfLastPadInPanel << endl;
  report(DEBUG, kReport) << " IdOfFirstPadInPanel " << IdOfFirstPadInPanel << endl;

	    float zCellLo=0;
	    float zCellHi=0;
	    if( entrZDif[iLoop]< exitZDif[iLoop]){ 
	     zCellLo = entrZDif[iLoop];
	     zCellHi = exitZDif[iLoop];
	    }else {
	     zCellLo = exitZDif[iLoop];
	     zCellHi = entrZDif[iLoop];
	    }  
	    
	    report(DEBUG, kReport) << "zCellLo " << zCellLo  << "zCellHi " << zCellHi << endl;   

	 for(int j=i-5; j<i+5; j++){
	  float x2=(float) (j-i)+.5;
          float x1=(float) (j-i)-.5; 
          int idOfPad=j;	    
	  if(idOfPad<IdOfLastPadInPanel+1&&idOfPad>IdOfFirstPadInPanel-1){
// three cases for segment over which charge is spread
// 1) loPadId=hiPadId (exit and entr pad the same)
// 2) exit pad  or entr but not both
// 3) middle pad fully crossed 
	     
	 report(DEBUG, kReport) << "going on idOfPad " << idOfPad << endl;

	    float zf1 = zCellLo;
	    if(zCellLo<zEdgeLo){zf1=zEdgeLo;}
	    float zf2 = zCellHi;
	    if(zCellHi>zEdgeHi){zf2=zEdgeHi;}

	    
	    
	    float f2=(zf2-zCenter)/padWid;	    
	    float f1=(zf1-zCenter)/padWid;
	    
	    if(f2>.51){report(DEBUG, kReport) << "integration pointU nonsense " << f2 << endl;}
	    if(f1<-.51){report(DEBUG, kReport) << "integration pointT nonsense " << f1 << endl;}

// "a" should be the dist of the wire from the cathode in units of pads

  	    float a=.7;    
	    float t2 = (x2-f2)*atan((x2-f2)/a) -(x1-f2)*atan((x1-f2)/a);    
            float t1 = (x2-f1)*atan((x2-f1)/a) -(x1-f1)*atan((x1-f1)/a);    
            float num=(t2-t1)/(2*(f2-f1)*a*a*a);
            float den=-4.58; 
            float fracDep = num/den;
	    float fracLay = 1.;
	    float tdepQ = depQ[i];
	    if(layR[iLoop]==46){fracLay=LayerFrac;}	 
	    report(DEBUG, kReport) << " fracDep " <<  fracDep << "fracLay " << fracLay << "depQ"		 << tdepQ << endl;
            padQ[idOfPad]=padQ[idOfPad]+fracLay*fracDep*depQ[i];
	    padZ[idOfPad] = zCenter;
	    
	  }   
	 }}

      for(i=1; i<ADRCathodeStore::kNumberOfPadsTotal+1; i++)
      {
	 if(padQ[i]>0.){
          int padID          = i;
	  int padParentPid   = pidR[iLoop];
	  float padParentCellZ   =  cellZR[iLoop]; 
	  int padParentAnodeID = drIDR[iLoop];
	  float padParentPhi = mPhiR[iLoop];
	  float padQFinal = padQ[i];

	  report(DEBUG, kReport) << "adding a reponse object" << endl;
	  report(DEBUG, kReport) << "padID " << padID  << endl;
	  report(DEBUG, kReport) << "padParenrID " << padParentPid    << endl;
	  report(DEBUG, kReport) << "padParentCellZ " << padParentCellZ << endl;
	  report(DEBUG, kReport) << "padParentPhi" << padParentPhi  << endl;
	  report(DEBUG, kReport) << "padQFinal " << padQFinal << endl;
    report(DEBUG, kReport) << "padZ " << padZ[i] << endl;	  


       MCCathodesResponse* tmp( new MCCathodesResponse( 
                       increment, 
                       padParentPid,
       	 	       padID ,
       	 	       padParentCellZ,
       		       padParentPhi,
       	               padQFinal,
                       padParentAnodeID ) );
              (*m_ptrTable).insert( tmp ) ;
              increment++;      	  

      }else
      {
       if(padQ[i]<0.){report(DEBUG, kReport) << "negative charge on cathode" << endl;}
      }
      }

     }
   }  

//=========================================================================
//
// loop over collections 
//
//=========================================================================




// end if statement (only execute loop if CathodesResponses were wanted)
   } 

//Return the objects

   return m_ptrTable ;

}


 
// const member functions
//

//
// static member functions
//


//
// 'bound' functions
//
void MCCathodesResponseProxy::updateBeginRun( const Record& iRecord )
{
   // Make sure Cleog begin run data is valid.
   // This bindable proxy is tied to the beginRun stream.
   // m_producer points to MCResponseProd producer which has the function
   // updateCleogBeginRun which checks if begin run is valid
   // TODO: 4/11/99 - Temp fix of (Frame&) (CHANGE WHEN CURRENT UPDATED))
   m_producer->updateCleogBeginRun( (Frame&) iRecord.frame() );
}


//-----------------------------------------------
// Bindable proxy - method to bind to other streams
PROXY_BIND_METHOD( MCCathodesResponseProxy )
//-----------------------------------------------
