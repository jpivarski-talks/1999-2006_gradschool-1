// -*- C++ -*-
//
// File:    TrkmanProd.h
// Package: TrkmanProd
// Module:  TrkmanProd
//
/**\class TrkmanProd TrkmanProd.h TrkmanProd/TrkmanProd.h
 
 Description: Wrapped-up CLEO II Trkman common blocks

 Usage:
    <usage>

*/
//
// Author:      Thomas Meyer
// Created:     Mon Jan 14 11:28:13 EST 2002
// $Id: TrkmanProd.h,v 1.2 2002/11/04 18:38:28 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanProd.h,v $
// Revision 1.2  2002/11/04 18:38:28  nea9
// New CleoIII Trkman
//
// Revision 1.1.1.1  2002/01/28 13:57:18  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */
#ifndef TRKMANPROD_TRKMANPROD_H
#define TRKMANPROD_TRKMANPROD_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"

// #include "Trkman/TMClassification.h"
// #include "Trkman/TMData.h"

// FORWARD DECLARATIONS

class TrkmanProd : public Producer
{
  // ------------ FRIEND CLASSSES AND FUNCTIONS ---------------

public:
  // ------------ CONSTANTS, ENUMS AND TYPEDEFS ---------------

  // ------------ CONSTRUCTORS AND DESTRUCTOR -----------------
  TrkmanProd( void );

  virtual ~TrkmanProd();

  // ------------ MEMBER FUNCTIONS ----------------------------

  // Methods for beginning/end "Interactive"
  virtual void init( void );
  virtual void terminate( void );

  // Standard place for booking histograms
  virtual void hist_book( HIHistoManager& );		  

//   ProxyBase* makeTrkmanInfoProxy(); 

//   TMClassification* trkmanClassifications();

//   TMData* trkmanData();    
    

  // ------------ CONST MEMBER FUNCTIONS ----------------------

  // ------------ STATIC MEMBER FUNCTIONS ---------------------

protected:
  // ------------ PROTECTED MEMBER FUNCTIONS ------------------

  // ------------ PROTECTED CONST MEMBER FUNCTIONS ------------

private:
  // ------------ CONSTRUCTORS AND DESTRUCTOR -----------------
  TrkmanProd( const TrkmanProd& );

  // ------------ ASSIGNMENT OPERATOR(S) ----------------------
  const TrkmanProd& operator=( const TrkmanProd& );

  // ------------ PRIVATE MEMBER FUNCTIONS --------------------

  // ------------ PRIVATE CONST MEMBER FUNCTIONS --------------

  // ------------ DATA MEMBERS --------------------------------
      //Parameter< string > m_dataType;
//   TMData* m_data;
//   TMClassification* m_trkmanClassifications;    

  // ------------ STATIC DATA MEMBERS -------------------------

};

// INLINE FUNCTION DEFINITIONS

#endif /* TRKMANPROD_TRKMANPROD_H */
