// -*- C++ -*-
#if !defined(EVENTTYPEFILTERPROC_EVENTTYPEFILTERPROC_H)
#define EVENTTYPEFILTERPROC_EVENTTYPEFILTERPROC_H
//
// Package:     <EventTypeFilterProc>
// Module:      EventTypeFilterProc
//
/**\class EventTypeFilterProc EventTypeFilterProc.h EventTypeFilterProc/EventTypeFilterProc.h
 
 Description:

 Usage:

*/
//
// Author:      Brian K. Heltsley
// Created:     Thu Jul 26 12:10:58 EDT 2001
// $Id: EventTypeFilterProc.h,v 1.3 2001/11/01 18:08:09 bkh Exp $
//
// Revision history
//
// $Log: EventTypeFilterProc.h,v $
// Revision 1.3  2001/11/01 18:08:09  bkh
// Add histograms
//
// Revision 1.2  2001/08/03 18:07:16  bkh
// Add histogramming of all variables on all event types
//
// Revision 1.1.1.1  2001/07/31 18:14:13  bkh
// imported EventTypeFilterProc sources
//
//

// system include files
#include "STLUtility/fwd_vector.h"
#include <vector>
#include <utility>

// user include files
#include "EventType/EventType.h"

#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "CommandPattern/Parameter.h"
#include "STLUtility/fwd_vector.h"
#include <vector>

// forward declarations

class EventTypeFilterProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      typedef pair< UInt16, UInt32 > PairInts ;
      typedef STL_VECTOR( PairInts ) PairList ;
      typedef STL_VECTOR( PairList ) Matrix   ;
      typedef STL_VECTOR( UInt32   ) SumList  ;

      // ------------ Constructors and destructor ----------------
      EventTypeFilterProc( void );                      // anal1 
      virtual ~EventTypeFilterProc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);
      //virtual ActionBase::ActionResult geometry( Frame& iFrame);
      //virtual ActionBase::ActionResult hardware( Frame& iFrame);
      //virtual ActionBase::ActionResult user( Frame& iFrame);

      // ------------ const member functions ---------------------

      void summary() const ;

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      EventTypeFilterProc( const EventTypeFilterProc& );

      // ------------ assignment operator(s) ---------------------
      const EventTypeFilterProc& operator=( const EventTypeFilterProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (EventTypeFilterProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Matrix  m_matrix    ;
      SumList m_exclusive ;
      UInt32  m_total     ;

      STL_VECTOR( Parameter< DABoolean >* ) m_commands ;
      UInt32  m_keep ;

      DABoolean m_ask ;

      enum HistTypes { k_nHist = 20 } ;

      HIHist1D* m_hst[ EventType::k_nFlags ][ k_nHist ] ;

      static const UInt32 k_nTk, k_qNet, k_pTk1, k_pTk2, k_eTk1,
	 k_eTk2, k_eVis, k_eGam1, k_eCC, k_pPerp, k_eSh1, k_eSh2,
	 k_eSh3, k_eOverP1, k_eOverP2, k_acop, k_acosth, k_sinthm,
	 k_eChg, k_eNeu ;

      static const string k_varNames[ k_nHist ] ;

      static const UInt32 k_nBins[ k_nHist ] ;

      static const float k_loEdge[ k_nHist ] ;

      static const float k_hiEdge[ k_nHist ] ;


      // ------------ static data members ------------------------

   public:
      class ComparePairs // for sorting pairs
      {
	 public:
	    DABoolean operator()( const PairInts& p1 , const PairInts& p2 ) {
	       return p1.second > p2.second ;
	    }
      } ;
};

// inline function definitions

#endif /* EVENTTYPEFILTERPROC_EVENTTYPEFILTERPROC_H */
