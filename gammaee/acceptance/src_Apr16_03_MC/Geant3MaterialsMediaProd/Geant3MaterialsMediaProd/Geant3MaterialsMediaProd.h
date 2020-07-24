#if !defined(GEANT3MATERIALSMEDIAPROD_GEANT3MATERIALSMEDIAPROD_H)
#define GEANT3MATERIALSMEDIAPROD_GEANT3MATERIALSMEDIAPROD_H
// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      Geant3MaterialsMediaProd
//
/**\class Geant3MaterialsMediaProd Geant3MaterialsMediaProd.h Geant3MaterialsMediaProd/Geant3MaterialsMediaProd.h
 
 Description: Produces Geant3-consistent materials & tracking media

 Usage:
    Select as a standard Suez producer.

*/
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 10:58:53 EST 1999
// $Id: Geant3MaterialsMediaProd.h,v 1.2 2001/01/16 20:06:31 bkh Exp $
//
// Revision history
//
// $Log: Geant3MaterialsMediaProd.h,v $
// Revision 1.2  2001/01/16 20:06:31  bkh
// Remove internal command to setup GEANT3
//
// Revision 1.1.1.1  1999/12/15 18:35:49  bkh
// imported Geant3MaterialsMediaProd sources
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"


// forward declarations

class Geant3MaterialsMediaProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      Geant3MaterialsMediaProd();
      virtual ~Geant3MaterialsMediaProd();

      // ------------ member functions ----------------------------


      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------
      // ------------ static member functions ---------------------
   protected:
      // ------------ protected member functions ------------------
      // ------------ protected const member functions ------------
   private:
      // ------------ Constructors and destructor -----------------
      Geant3MaterialsMediaProd( const Geant3MaterialsMediaProd& );
      // ------------ assignment operator(s) ----------------------
      const Geant3MaterialsMediaProd& operator=( const Geant3MaterialsMediaProd& );
      // ------------ private member functions --------------------
      // ------------ private const member functions --------------
      // ------------ data members --------------------------------

      // ------------ static data members -------------------------
};

// inline function definitions

#endif /* GEANT3MATERIALSMEDIAPROD_GEANT3MATERIALSMEDIAPROD_H */
