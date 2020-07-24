// -*- C++ -*-
#if !defined(MCINFO_MCDECAYMODE_H)
#define MCINFO_MCDECAYMODE_H
//
// Package:     <MCInfo>
// Module:      MCDecayMode
// 
// Description: Summary of the information known for a given decay:
//              branching fraction, decay dynamics model, parent,
//              daughters.  Also holds information for the naive QQ
//              helicity modelling
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Wed Mar 31 18:05:49 EST 1999
// $Id: MCDecayMode.h,v 1.6 2001/12/19 18:11:33 lkg Exp $
//
// Revision history
//
// $Log: MCDecayMode.h,v $
// Revision 1.6  2001/12/19 18:11:33  lkg
// new constructor plus other tweaks for StorageHelper compatibility
//
// Revision 1.5  2001/02/14 02:34:29  lkg
// Implement an "unknown"  static function  that returns a default, empty
// DecayMode.  Will allow us to handle bugs in QQ commons more gracefully
//
// Revision 1.4  2000/05/01 22:50:47  lkg
// StorageHelper-related changes: added valueType arg for MCListItr typedefs and == and != operators
//
// Revision 1.3  1999/10/19 21:37:01  lkg
// * isDeterministic() -> deterministic(), to conform to convention
// * add setDeterministic member fcn, so auto-guess can be overwritten
// * in ModeCheckId subclass, don't use reference to QQ_id as member item,
//   just plain QQ_id
//
// Revision 1.2  1999/07/06 19:34:42  lkg
// Add a unary_function for use with STL algorithms in searching for decay
// modes using QQ id's
//
// Revision 1.1  1999/06/22 21:30:12  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"

// forward declarations
class MCParticleProperty;
#include "C++Std/fwd_ostream.h"
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"

class MCDecayMode
{
      // ---------- friend classes and functions ---------------

      // output operator for the decay mode
      friend ostream& operator<<(ostream& aStream,
				 const MCDecayMode& aMode );

   public:
      // ---------- constants, enums and typedefs --------------
      static const Count kUnknownMode;    // value when decay mode is unknown

      // ---------- Constructors and destructor ----------------
      // for storage Helper
      MCDecayMode(  MCParticleProperty* parentProperty,
		    Double  branchingFraction,
		    const STL_VECTOR( QQ_id )& childrenTypes,
		    Integer model,
		    SimpleHelicity* helicityConfigs,
		    SimpleAngularHelicity* angularConfigs );

      MCDecayMode();
      MCDecayMode( const MCParticleProperty& );
      MCDecayMode( const MCDecayMode& );

      // ---------- assignment operator(s) ---------------------
      const MCDecayMode& operator=( const MCDecayMode& );

      virtual ~MCDecayMode();

      // ---------- member functions ---------------------------

      // branching fraction for this decay
      void setBranchingFraction( Double );
      Double  branchingFraction() const;

      void setChildrenTypes( const STL_VECTOR( string )& );
      void setChildrenTypes( const STL_VECTOR( QQ_id )& );
      Count numberChildren() const;
      const STL_VECTOR( QQ_id )& childList() const {return m_daughterTypes; }
      const STL_VECTOR( QQ_id )& childrenTypes() const {return m_daughterTypes; } // for storage helpers
      QQ_id         childType( Count iChild ) const;
      const string& childName( Count iChild ) const;

      // what model should be used for this decay
      void setModel( Integer aModel );
      Integer   model( void ) const;

      // probably should have derived classes that deal with the
      // simplistic model of helicity.  This gets us going...
      void setHelicityConfigs( const SimpleHelicity& );
      const SimpleHelicity* helicityConfigs() const { 
	 return m_pHelicityConfigs; }
      void setAngularDistribs( const SimpleAngularHelicity& );
      const SimpleAngularHelicity* angularDistribs() const { 
	 return m_pAngularDistribs; }

      // the Property object for the parent type of this decay
      void                   setParentProp( const MCParticleProperty& );
      const MCParticleProperty& parentProp() const;
      const string& parentType() const;

      // identifier of this mode for this parent
      void setIdentifier( Count );
      Count   identifier() const;

      // Equality: based on parent & children only (isMode)
      // or on all properties, Model, helicity-related info, etc.
      DABoolean isMode( const MCDecayMode& rhs ) const;
      DABoolean isMode( const string& parentName,
			const STL_VECTOR(string)& daughterNames ) const;
      DABoolean isMode( QQ_id parentQQId,
			const STL_VECTOR(QQ_id)& daughterList ) const;

      DABoolean operator==( const MCDecayMode& rhs ) const;
      DABoolean operator!=( const MCDecayMode& rhs ) const;
			
      // Does this decay mode have a fully-specified list of
      // daughters, or does the full list of daughters thrown
      // on a decay-by-decay basis
      void setDeterministic( DABoolean );
      DABoolean deterministic() const;

      // ---------- static member functions --------------------
      static const MCDecayMode& unknown() ; // the unknown PP

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // assign an identifier for this mode within this parent
      Count m_identifier;

      // pointer to the parent property
      const MCParticleProperty* m_pParentProp;

      // what type, the parent -- for convenience
      QQ_id m_parentType;

      // what type, the daughters
      STL_VECTOR(QQ_id)& m_daughterTypes;

      // what's the branching fraction
      Double m_branchingFraction;

      // what model to use for this decay
      Integer m_decayModelId;

      // true if all children are "physical" (ie, list of daughters is
      // fully determined).  false otherwise (model 2, "QQBAR" daughters, ...)
      DABoolean m_deterministic;

      // specific child Helicities produced in this decay, if any
      SimpleHelicity* m_pHelicityConfigs;

      // specific angular orientation of children if parent in a
      // particular helicity
      SimpleAngularHelicity* m_pAngularDistribs;

      // ---------- STL algorithm helpers -------------
   public:
      // functions that can check if an arbitrary decay mode has a
      // specific parent and daughters
      struct ModeCheck : public unary_function<const MCDecayMode&, DABoolean> {
	 ModeCheck( const string& parent, 
		    const STL_VECTOR( string )& daughters ) :
	    m_parent( parent ),
	    m_daughters( daughters ) {};
	 DABoolean operator()( const MCDecayMode& aMode ) {
	    return aMode.isMode( m_parent, m_daughters ); };
	 const string& m_parent;
	 const STL_VECTOR( string )& m_daughters;
      };
      struct ModeCheckId : public unary_function<const MCDecayMode&, DABoolean> {
	 ModeCheckId( QQ_id parent, 
		    const STL_VECTOR( QQ_id )& daughters ) :
	    m_parent( parent ),
	    m_daughters( daughters ) {};
	 DABoolean operator()( const MCDecayMode& aMode ) {
	    return aMode.isMode( m_parent, m_daughters ); };
	 const QQ_id m_parent;
	 const STL_VECTOR( QQ_id )& m_daughters;
      };

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCDecayMode.cc"
//#endif

#endif /* MCINFO_MCDECAYMODE_H */
