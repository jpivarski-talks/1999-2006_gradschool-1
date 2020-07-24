// -*- C++ -*-
#if !defined(EVTGENMODELS_EVTGENMODELS_H)
#define EVTGENMODELS_EVTGENMODELS_H
//
// Package:     EvtGenModels
// Module:      EvtGenModels
//
/**\class EvtGenModels EvtGenModels.h EvtGenModels/EvtGenModels.h
 
 Description: (dynamically-loadable) module

 Usage:
    <usage>

*/
//
// Author:      Anders Ryd
// Created:     Fri Sep 12 21:22:48 EDT 2003
// $Id: EvtGenModels.h,v 1.1.1.1 2003/10/07 02:48:02 ryd Exp $
//
// Revision history
//
// $Log: EvtGenModels.h,v $
// Revision 1.1.1.1  2003/10/07 02:48:02  ryd
// imported EvtGenModels sources
//
//

// system include files

// user include files
#include "CommandPattern/Module.h"
#include "EvtGenModels/EvtGenModelsCommand.h"
#include "EvtGenModels/EvtGenModelsInternalCommand.h"

// forward declarations

class EvtGenModels : public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      EvtGenModels();
      virtual ~EvtGenModels();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void printNumber( int iNumber ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      EvtGenModels( const EvtGenModels& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const EvtGenModels& operator=( const EvtGenModels& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // NOTE: if you want a command (or commands) to be available 
      //       upon loading of the module, you need an external 
      //       command (or commands);
      //       and you can have any number of internal commands...
      EvtGenModelsCommand m_command;
      EvtGenModelsInternalCommand m_internalCommand;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "EvtGenModels/Template/EvtGenModels.cc"
//#endif

#endif /* EVTGENMODELS_EVTGENMODELS_H */
