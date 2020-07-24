// -*- C++ -*-
#if !defined(EVTGENPROD_EVTGENGENERATOR_H)
#define EVTGENPROD_EVTGENGENERATOR_H
//
// Package:     EvtGenProd
// Module:      EvtGenGenerator
//
/*
 Description: Interface from framework to EvtGen.

 Usage:
    <usage>

*/
//
// Author:      Anders Ryd
// Created:     Sat Sep 13 17:58:54 EDT 2003
// $Id: EvtGenGenerator.h,v 1.4 2004/09/02 03:12:08 ryd Exp $
//
// Revision history
//
// $Log: EvtGenGenerator.h,v $
// Revision 1.4  2004/09/02 03:12:08  ryd
// Fix event time
//
// Revision 1.3  2003/11/12 20:50:41  ryd
// Fix problem with vertex position and units
//
// Revision 1.2  2003/10/14 20:32:42  ryd
// Switch to jetset; bug fixes for initial quarks
//
// Revision 1.1.1.1  2003/10/07 02:48:56  ryd
// imported EvtGenProd sources
//
//

// system include files


// user include files

#include "MCBeam/MCEventVertex.h"
//#include "EvtGenProd/EvtGen.hh"

#include "FrameAccess/FAItem.h"

// forward declarations

class MCParticle;
class EvtParticle;
class EvtGen;
class MCParticlePropertyStore;
class HepPoint;


class EvtGenGenerator
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      EvtGenGenerator(const string& decayfile,const string& udecayfile,
		      const string& evtpdl);
      virtual ~EvtGenGenerator();          

      // ------------ member functions ----------------------------

      void decayParticles(MCParticle* vPhoton, MCEventVertex eventVertex,
			 FAItem<MCParticlePropertyStore>& mcPP);

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      EvtGenGenerator( const EvtGenGenerator& );

      // ------------ assignment operator(s) ----------------------
      const EvtGenGenerator& operator=( const EvtGenGenerator& );

      void makeTree(MCParticle* mcP,EvtParticle* evtP,
		FAItem<MCParticlePropertyStore>& mcPP,
		const HepPoint3D& interactionPoint, double t);
      // ------------ private member functions --------------------

      // ------------ private const member funtions --------------

      // ------------ data members --------------------------------

      EvtGen* m_EvtGen;

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* EVTGENPROD_EVTGENGENERATOR_H */





