// -*- C++ -*-
#if !defined(MCSYMMETRICBEAMPROD_MCSYMMETRICBEAMPROD_H)
#define MCSYMMETRICBEAMPROD_MCSYMMETRICBEAMPROD_H
//
// Package:     <MCSymmetricBeamProd>
// Module:      MCSymmetricBeamProd
//
/**\class MCSymmetricBeamProd MCSymmetricBeamProd.h MCSymmetricBeamProd/MCSymmetricBeamProd.h
 
 Description: Supplies the proxy for the item
              - MCBeamParameters
	      for a symmetric beam configuration

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Fri Jan 19 15:30:52 EST 2001
// $Id: MCSymmetricBeamProd.h,v 1.2 2002/03/26 17:28:59 bkh Exp $
//
// Revision history
//
// $Log: MCSymmetricBeamProd.h,v $
// Revision 1.2  2002/03/26 17:28:59  bkh
// Use BeamEnergy object not CesrBeamEnergy and remove related parameters
//
// Revision 1.1.1.1  2001/01/31 21:10:49  lkg
// imported MCSymmetricBeamProd source
//
//

// system include files

// user include files
#include "MCBeamProdBase/MCBeamProdBase.h"
#include "HistogramInterface/HistogramPackage.h"

// forward declarations

class MCSymmetricBeamProd : public MCBeamProdBase
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      MCSymmetricBeamProd( void );                      // anal1 
      virtual ~MCSymmetricBeamProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------

      double totalEnergySpreadAt10GeV() const {
	 return m_tenGevTotalEnergySpread.value();
      }


      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      MCSymmetricBeamProd( const MCSymmetricBeamProd& );

      // ------------ assignment operator(s) ----------------------
      const MCSymmetricBeamProd& operator=( const MCSymmetricBeamProd& );

      // ------------ private member functions --------------------
      ProxyBase* makeMCBeamParametersProxy();

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      Parameter<double> m_tenGevTotalEnergySpread;

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* MCSYMMETRICBEAMPROD_MCSYMMETRICBEAMPROD_H */
