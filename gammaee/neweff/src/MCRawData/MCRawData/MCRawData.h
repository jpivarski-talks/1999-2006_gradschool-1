#if !defined(MCRAWDATA_MCRAWDATA_H)
#define MCRAWDATA_MCRAWDATA_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawData
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:23:59 EST 1999
// $Id: MCRawData.h,v 1.8 2002/09/27 20:23:41 bkh Exp $
//
// Revision history
//
// $Log: MCRawData.h,v $
// Revision 1.8  2002/09/27 20:23:41  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.7  2002/06/13 19:53:45  bkh
// Implement use of ccmcpeeldaqmap in the calorimeter processing
// Implement parameter to turn off trigger simulation as with other detectors
//
// Revision 1.6  2001/12/20 17:11:30  bkh
// Install fake merge flag for Cathodes as with other detectors
// Use fake merge flag for Cathodes
// Fix SV proxy fcn to avoid compiler warning about
//      argument overriding member data
//
// Revision 1.5  2001/12/18 22:33:20  bkh
// Institute CC "fake merge" flag like other detectors
// Force trigger to get CalibratedDRHits not raw data
//
// Revision 1.4  2001/11/29 23:13:56  ts
// add parameters to control noise merging in Rich
//
// Revision 1.3  2001/11/20 04:58:03  victor
// introduced two parameters for SV
//
// Revision 1.2  2001/04/30 17:05:28  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "ToolBox/HistogramPackage.h"
#include "CommandPattern/Parameter.h"
#include "DataHandler/Template/ProxyFactoryFunction.cc"


class MCRawData : public Producer
{
      // ------------ friend classses and functions ---------------
   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      MCRawData( void );                      // anal1 
      virtual ~MCRawData();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( TBHistoManager& );                  
      ProxyBase* makeMCRawCCHitsProxy();
      ProxyBase* makeMCRawCathodesProxy();
      ProxyBase* makeMCRawSVHitsProxy();
      ProxyBase* makeMCRawRichHitsProxy();

      Parameter<DABoolean> m_getMCRawSVHits; 
      Parameter<DABoolean> m_getMCRawDRHits; 
      Parameter<DABoolean> m_getMCRawZDHits; 
      Parameter<DABoolean> m_getMCRawCathodesHits; 
      Parameter<DABoolean> m_getMCRawRichHits; 
      Parameter<DABoolean> m_getMCRawCCHits; 
      Parameter<DABoolean> m_getMCRawMUHits;
      Parameter<DABoolean> m_getMCRawTrigger;

      Parameter<DABoolean> m_useCCFakeMerge;
      Parameter<DABoolean> m_useCathodesFakeMerge;

      Parameter<DABoolean> m_useSVFakeMerge;
      Parameter< float >   m_useSVCMNoiseValue;

      Parameter<DABoolean> m_useRichFakeMerge;
      Parameter< float >   m_useRichNoiseScaleFactor;


      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------
   protected:
      // ------------ protected member functions ------------------
      // ------------ protected const member functions ------------
   private:
      // ------------ Constructors and destructor -----------------
      MCRawData( const MCRawData& );
      // ------------ assignment operator(s) ----------------------
      const MCRawData& operator=( const MCRawData& );
      // ------------ private member functions --------------------
      // ------------ private const member functions --------------
      // ------------ data members --------------------------------
      // ------------ static data members -------------------------
};

// inline function definitions

#endif /* MCRAWDATA_MCRAWDATA_H */
