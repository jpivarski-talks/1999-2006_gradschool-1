// -*- C++ -*-
#if !defined(EVTGENMODELS_EVTGENMODELSINTERNALCOMMAND_H)
#define EVTGENMODELS_EVTGENMODELSINTERNALCOMMAND_H
//
// Package:     <EvtGenModels>
// Module:      EvtGenModelsInternalCommand
//
/**\class EvtGenModelsInternalCommand EvtGenModelsInternalCommand.h EvtGenModels/InternalCommand.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Anders Ryd
// Created:     Fri Sep 12 21:22:48 EDT 2003
// $Id: EvtGenModelsInternalCommand.h,v 1.1.1.1 2003/10/07 02:48:02 ryd Exp $
//
// Revision history
//
// $Log: EvtGenModelsInternalCommand.h,v $
// Revision 1.1.1.1  2003/10/07 02:48:02  ryd
// imported EvtGenModels sources
//
//

// system include files

// user include files
#include "CommandPattern/Command.h"

// forward declarations
class EvtGenModels;

class EvtGenModelsInternalCommand : public Command
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      EvtGenModelsInternalCommand( const Command::Name& iName, 
			      EvtGenModels* target );
      virtual ~EvtGenModelsInternalCommand();

      // ---------- member functions ---------------------------
      // You may override the base class's execute method, but it's
      // easier to use the "Subcommand" class to handle subcommands.
      // (Have a look at the command::ctor for an example.)
      //virtual int execute( int argc, char* argv[] );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual int helpHandler();
      virtual int printHandler();

      EvtGenModels* target();
      const EvtGenModels* target() const;

   private:
      // ---------- Constructors and destructor ----------------
      EvtGenModelsInternalCommand( const EvtGenModelsInternalCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const EvtGenModelsInternalCommand& operator=( 
	 const EvtGenModelsInternalCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "EvtGenModels/Template/EvtGenModelsInternalCommand.cc"
//#endif

#endif /* EVTGENMODELS_EVTGENMODELSINTERNALCOMMAND_H */
