#if !defined(MCINFO_DECAYCOMMAND_H)
#define MCINFO_DECAYCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      DecayCommand
// 
// Description: Class to parse the Decay command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: DecayCommand.h,v 1.2 2002/11/21 21:11:58 cleo3 Exp $
//
// Revision history
//
// $Log: DecayCommand.h,v $
// Revision 1.2  2002/11/21 21:11:58  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1  1999/06/22 21:29:49  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:42  lkg
// Initial MCDecayFileParser sources
//

// system include files
#include "C++Std/fstream.h"

// user include files
#include "MCInfo/MCDecayFileParser/CommandParser.h"

// STL
#include <vector>
#include <deque>

// forward declarations
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_deque.h"

class MCParticlePropertStore;
class MCDecayMode;

class DecayCommand : public CommandParser
{
   public:

      // an internal class used to shepherd the information needed to
      // completely specify a decay mode a la QQ
      class DecayModeInfo : public CommandParser::ExtraInfo {
	 public:
	    // constructor
	    DecayModeInfo( MCParticleProperty& theParent ) :
	       CommandParser::ExtraInfo(),
	       m_parent( &theParent ) {};
	    // destructor
	    ~DecayModeInfo() {};

	    // public member data that subcommands may alter
	    STL_DEQUE( Double )&               helicityFraction()
	       { return m_helicityFraction; };
	    STL_DEQUE( STL_VECTOR( Double ) )& helicityConfig()
	       { return m_helicityConfig; };
	    STL_DEQUE( Double )&               angularHelList()
	       { return m_angularHelList; };
	    STL_DEQUE( STL_VECTOR( Double ) )& angularHelParam()
	       { return m_angularHelParam; };
	    // reference to the particle property that will be altered
	    MCParticleProperty& parentProp() { return *m_parent; };
	 private:
	    DecayModeInfo(); // suppress default
	    DecayModeInfo( const DecayModeInfo& rhs ); // suppress default
	    
	    MCParticleProperty* m_parent;
	    STL_DEQUE( Double )               m_helicityFraction;
	    STL_DEQUE( STL_VECTOR( Double ) ) m_helicityConfig;
	    STL_DEQUE( Double )               m_angularHelList;
	    STL_DEQUE( STL_VECTOR( Double ) ) m_angularHelParam;
      };


      // ---------- Constructors and destructor ----------------
      DecayCommand();
      virtual ~DecayCommand();

      // ---------- const member functions ---------------------
      void run( const CommandParser::Command&,
		MCParticlePropertyStore&,
		ifstream&,
		CommandParser::ExtraInfo* ) const;

   private:
      // ---------- Constructors and destructor ----------------
      DecayCommand( const DecayCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DecayCommand& operator=( const DecayCommand& ); // stop default

};

// inline function definitions

#endif /* MCINFO_DECAYCOMMAND_H */
