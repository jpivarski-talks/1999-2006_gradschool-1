// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCDecayMode
// 
// Description: <one line class summary>
//
// Implementation:
//     For this very rough implementation, I have just used pointers to
//     the different simple helicity configurations.  This should probably
//     be done differently.
//
// Author:      Lawrence Gibbons
// Created:     Wed Mar 31 18:05:53 EST 1999
// $Id: MCDecayMode.cc,v 1.9 2003/01/29 19:15:32 cdj Exp $
//
// Revision history
//
// $Log: MCDecayMode.cc,v $
// Revision 1.9  2003/01/29 19:15:32  cdj
// get iomanip header from C++Std package
//
// Revision 1.8  2002/01/20 19:29:03  lkg
// repair assignment operator, change handling of unknown decay mode to prevent sig11
//
// Revision 1.7  2001/12/19 18:11:31  lkg
// new constructor plus other tweaks for StorageHelper compatibility
//
// Revision 1.6  2001/11/01 21:27:49  lkg
// add more information to error message for charge NONconservation
//
// Revision 1.5  2001/10/14 18:58:49  cdj
// fixed bug which could crash program when a MCParticleProperty instance is initialized at file scope
//
// Revision 1.4  2001/02/14 02:32:41  lkg
// Implement an "unknown" static function that returns a reference to
// a default decay mode.  Will allow us to handle bugs in QQ common blocls
// more gracefully
//
// Revision 1.3  1999/10/19 21:35:59  lkg
// * isDeterministic() -> deterministic(), to conform to convention
// * add setDeterministic member fcn, so auto-guess can be overwritten
// * mods to support determistic() and baryon() forms, rather than isX() forms
//
// Revision 1.2  1999/07/07 00:07:21  lkg
// Suppress decay-mode charge conservation violation for baryonic modes
// involving QQBAR pairs:  in these cases QQBAR is a misnomer, they are
// diquarks!  Yeccch.
//
// Revision 1.1  1999/06/22 21:28:52  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include "C++Std/iomanip.h"
#include <assert.h>
#include <typeinfo>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCQQBar.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <string>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCDecayMode" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDecayMode.cc,v 1.9 2003/01/29 19:15:32 cdj Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

const Count MCDecayMode::kUnknownMode( 0 );

//
// static data member definitions
//

//
// constructors and destructor
//
MCDecayMode::MCDecayMode( MCParticleProperty* parentProperty,
			  Double  branchingFraction,
			  const STL_VECTOR( QQ_id )& childrenTypes,
			  Integer model,
			  SimpleHelicity* helicityConfigs,
			  SimpleAngularHelicity* angularConfigs ) :
   m_identifier( kUnknownMode ),
   m_pParentProp( parentProperty ),
   m_parentType( parentProperty->QQId() ),
   m_daughterTypes( *new STL_VECTOR(QQ_id) ),
   m_branchingFraction( branchingFraction ),
   m_decayModelId( model ),
   m_pHelicityConfigs( helicityConfigs ),
   m_pAngularDistribs( angularConfigs ),
   m_deterministic( false )
{
   if ( &m_daughterTypes == 0 ) {
      report( ERROR, kFacilityString )
	 << "No Memory for daughter-type list" << endl;
      assert( false );
      ::exit( 1 );
   }
   setChildrenTypes( childrenTypes );
}

MCDecayMode::MCDecayMode() :
   m_identifier( kUnknownMode ),
   m_pParentProp( 0 ),
   m_parentType( MCParticleProperty::kUnknownQQId ),
   m_daughterTypes( *new STL_VECTOR(QQ_id) ),
   m_branchingFraction( 0 ),
   m_decayModelId( 0 ),
   m_pHelicityConfigs( 0 ),
   m_pAngularDistribs( 0 ),
   m_deterministic( false )
{
   if ( &m_daughterTypes == 0 ) {
      report( ERROR, kFacilityString )
	 << "No Memory for daughter-type list" << endl;
      assert( false );
      ::exit( 1 );
   }
}

MCDecayMode::MCDecayMode( const MCParticleProperty& theParent ) :
   m_identifier( 0 ),
   m_pParentProp( &theParent ),
   m_parentType( theParent.QQId() ),
   m_daughterTypes( *new STL_VECTOR(QQ_id) ),
   m_branchingFraction( 0 ),
   m_decayModelId( 0 ),
   m_pHelicityConfigs( 0 ),
   m_pAngularDistribs( 0 ),
   m_deterministic( false )
{
   if ( &m_daughterTypes == 0 ) {
      report( ERROR, kFacilityString )
	 << "No Memory for daughter-type list" << endl;
      assert( false );
      ::exit( 1 );
   }
}

// copy constructor: deep copy of the helicity-related pointers
MCDecayMode::MCDecayMode( const MCDecayMode& rhs ) :
   m_identifier( rhs.m_identifier ),
   m_pParentProp( rhs.m_pParentProp ),
   m_parentType( rhs.m_parentType ),
   m_daughterTypes( *new STL_VECTOR(QQ_id)(rhs.m_daughterTypes) ),
   m_branchingFraction( rhs.m_branchingFraction ),
   m_decayModelId( rhs.m_decayModelId ),
   m_pHelicityConfigs( 0 ),
   m_pAngularDistribs( 0 ),
   m_deterministic( rhs.m_deterministic )
{
   if ( rhs.m_pHelicityConfigs != 0 ) {
      m_pHelicityConfigs = new SimpleHelicity(*rhs.m_pHelicityConfigs);
   }
   if ( rhs.m_pAngularDistribs != 0 ) {
      m_pAngularDistribs = new SimpleAngularHelicity(*rhs.m_pAngularDistribs);
   }
}

MCDecayMode::~MCDecayMode()
{
   // now delete our list of daughter types
   delete &m_daughterTypes;
   delete m_pHelicityConfigs;
   delete m_pAngularDistribs;
}

//
// assignment operators
//
const MCDecayMode& MCDecayMode::operator=( const MCDecayMode& rhs )
{
  if( this != &rhs ) {
     m_identifier       = rhs.m_identifier;
     m_pParentProp      = rhs.m_pParentProp;
     m_parentType       = rhs.m_parentType;
     m_daughterTypes    = rhs.m_daughterTypes;
     m_branchingFraction= rhs.m_branchingFraction;
     m_decayModelId     = rhs.m_decayModelId;
     if ( rhs.m_pHelicityConfigs != 0 ) {
     	delete m_pHelicityConfigs;
	m_pHelicityConfigs = new SimpleHelicity( *rhs.m_pHelicityConfigs );
     }
     if ( rhs.m_pAngularDistribs != 0 ) {
     	delete m_pAngularDistribs;
	m_pAngularDistribs = new SimpleAngularHelicity( *rhs.m_pAngularDistribs );
     }
     m_deterministic    = rhs.m_deterministic;
  }
  
  return *this;
}

//
// member functions
//
void
MCDecayMode::setBranchingFraction( Double theBF ) {
   m_branchingFraction = theBF;
}

void 
MCDecayMode::setParentProp( const MCParticleProperty& parentProp ) {

   // store the pointer to the parent that will own this property
   m_pParentProp = &parentProp;

   // convert the name passed in to QQ Id for internal use
   m_parentType = parentProp.QQId();
}


void 
MCDecayMode::setChildrenTypes( const STL_VECTOR( QQ_id )& childList ) {

   // get the particle property store so that we can translate QQ_id
   // to names
   const MCParticlePropertyStore& parentStore = m_pParentProp->store();

   // the vector to hold the list of names
   STL_VECTOR( string ) nameBasedList;

   typedef STL_VECTOR( QQ_id )::const_iterator idIter;
   idIter itDone = childList.end();
   idIter itChild;
   for ( itChild = childList.begin(); itChild != itDone; ++itChild ) {
      nameBasedList.push_back( parentStore.qqIdToName( *itChild ) );
   }

   // use the name-based implementation
   setChildrenTypes( nameBasedList );
}

void 
MCDecayMode::setChildrenTypes( const STL_VECTOR( string )& childList ) {

   Double massTotal( 0. );
   Double chargeTotal( 0. );
   DABoolean allRealDaughters( true );

   // add each child to the list, checking its existance in the
   // property store and its properties
   typedef STL_VECTOR( string )::const_iterator idIter;
   idIter itDone = childList.end();
   idIter itChild;
   const MCParticlePropertyStore& parentStore = m_pParentProp->store();
   for ( itChild = childList.begin(); itChild != itDone; ++itChild ) {
      // get the particle property for this child.  [] will be
      // unhappy and abort if the child doesn't exist
      const MCParticleProperty& childProp = parentStore[*itChild];

      // check if this is a QQBAR specification
      /* USE THIS when we can use RTTI
       * if ( typeid(childProp) == typeid(MCQQBar) ) {
       *    allRealDaughters = false;
       * }
       */
      // KLUGE, KLUGE, KLUGE --- no RTTI  !!!!!!!!!!!!!!!!!!
      if ( childProp.QQId() < 0 ) {
	 allRealDaughters = false;
      }

      // include the minimum mass for this child in the total mass sum
      if ( childProp.width() == 0 ) {
	 massTotal += childProp.mass();
      } else {
	 massTotal += childProp.minMass();
      }

      // include the charge for this child in the total charge sum
      chargeTotal += childProp.charge();

      // store the QQ id in the list of children types
      m_daughterTypes.push_back( childProp.QQId() );
   }
   m_deterministic = allRealDaughters;

   string childNameList = "";
   for ( itChild = childList.begin(); itChild != itDone; ++itChild ) {
      childNameList += *itChild;
      childNameList += " ";
   }
   if ( m_parentType == MCParticleProperty::kUnknownQQId ) {
      report( WARNING, kFacilityString )
	 << "Parent of decay unknown -- cannot verify charge/energy "
	 << "conservation. Children: " << "\n"
	 << childNameList << endl;
   } else {
      const MCParticleProperty& parentProp 
	 = m_pParentProp->store()[m_parentType];

      // check for invalid children mass total
      Double compareMass = (parentProp.mass()>parentProp.maxMass()) ? 
	 parentProp.mass() : parentProp.maxMass();
      if ( compareMass < massTotal ) {
	 report( WARNING, kFacilityString )
	    << "Potential Energy nonconservation: "
	    << parentProp.name() << " --> " << childNameList << endl;
      }

      // check for charge conservation -- NOTE: baryonic use of the QQBAR
      // does not allow one to check for charge conservation
      if ( abs(parentProp.charge()-chargeTotal)>1e-6 ) {
	 if ( !( parentProp.baryon() && (! deterministic()) ) ) {
	    report( ERROR, kFacilityString )
	       << "Charge NONconservation: "
	       << parentProp.name() << " --> " << childNameList << '\n'
	       << "parent chg,type = " << parentProp.charge() << "," << m_parentType
	       << "   dau chg = " << chargeTotal
	       << "\n" << parentProp
	       << endl;
	 }
      }
   }
}

void 
MCDecayMode::setModel( Integer aModel ) {
   m_decayModelId = aModel;
}

void 
MCDecayMode::setHelicityConfigs( const SimpleHelicity& helicityList ) {
   m_pHelicityConfigs = new SimpleHelicity( helicityList );
}

void
MCDecayMode::setAngularDistribs( const SimpleAngularHelicity& angDistList ) {
   m_pAngularDistribs = new SimpleAngularHelicity( angDistList );
}

void
MCDecayMode::setIdentifier( Count anId ) {
   m_identifier = anId;
}

void
MCDecayMode::setDeterministic( DABoolean wellIsIt ) {
   m_deterministic = wellIsIt;
}

//
// const member functions
//

DABoolean 
MCDecayMode::isMode( const MCDecayMode& rhs ) const {
   return isMode( rhs.m_parentType, rhs.m_daughterTypes );
}

DABoolean 
MCDecayMode::isMode( const string& parentName,
		     const STL_VECTOR( string )& daughterNames ) const {
   const MCParticlePropertyStore& store = m_pParentProp->store();
   QQ_id parentQQId = store.nameToQQId( parentName );

   MCParticlePropertyStore::TransNameToQQ translate( store );
   STL_VECTOR( QQ_id ) daughterList( daughterNames.size() );
   transform( daughterNames.begin(), daughterNames.end(),
	      daughterList.begin(), translate );

   return isMode( parentQQId, daughterList );
}

DABoolean 
MCDecayMode::isMode( QQ_id parentQQId,
		     const STL_VECTOR(QQ_id)& daughterList ) const {

   if ( (m_parentType == parentQQId) &&
	(m_daughterTypes.size() == daughterList.size()) ) {

      // sort copies of the daughter lists for ease of comparison
      STL_VECTOR(QQ_id) thisCopy( m_daughterTypes );
      STL_VECTOR(QQ_id)   inCopy( daughterList );
      sort( thisCopy.begin(), thisCopy.end() );
      sort(   inCopy.begin(),   inCopy.end() );

      // equality is based only on the parent and daughter types
      return equal( thisCopy.begin(), thisCopy.end(), inCopy.begin() );
   } else {
      return false;
   }
}

DABoolean 
MCDecayMode::deterministic() const {
   return m_deterministic;
}

DABoolean 
MCDecayMode::operator==( const MCDecayMode& rhs ) const {

   // first check the decay mode
   if ( ! isMode( rhs ) ) {
      return false;
   }

   // now check branching fraction and decay model
   if ( m_branchingFraction != rhs.m_branchingFraction ) {
      return false;
   }
   if ( m_decayModelId != rhs.m_decayModelId ) {
      return false;
   }

   // finally check the helicities
   if ( *m_pHelicityConfigs != *rhs.m_pHelicityConfigs ) {
      return false;
   }

   return *m_pAngularDistribs == *rhs.m_pAngularDistribs;
}

DABoolean 
MCDecayMode::operator!=( const MCDecayMode& rhs ) const {
   return ! operator==( rhs );
}

Double 
MCDecayMode::branchingFraction() const {
   return m_branchingFraction;
}

const string& 
MCDecayMode::parentType() const {
   return m_pParentProp->name();
}

Count
MCDecayMode::numberChildren() const {
   return m_daughterTypes.size();
}

QQ_id
MCDecayMode::childType( Count iChild ) const {
   if ( iChild < numberChildren() ) {
      return m_daughterTypes[iChild];
   } else {
      return MCParticleProperty::kUnknownQQId;
   }
}

const string& 
MCDecayMode::childName( Count iChild ) const {
   if ( iChild < numberChildren() ) {
      return m_pParentProp->store()[ m_daughterTypes[iChild] ].name();
   } else {
      return MCParticleProperty::unknownName();
   }
}

Integer
MCDecayMode::model( void ) const {
   return m_decayModelId;
}

Count
MCDecayMode::identifier() const {
   return m_identifier;
}

//
// friend functions
//

// default output operator for the particle property object
ostream& operator<<(ostream& s, const MCDecayMode& aMode )
{
   // Output the decay mode information
   s << "mode " << aMode.identifier() << ": "
     << "frac = " << setw(8) << setprecision(6) << aMode.branchingFraction()
     << " " << aMode.parentType() << " --> ";
   for ( Count i = 0; i != aMode.numberChildren(); ++i ) {
      s << aMode.childName(i) << " ";
   }
   s << " (Model " << aMode.model() << ")";

   // Output the helicity info for this decay, if any
   if ( aMode.m_pHelicityConfigs != 0 ) {
      s << '\n' << " ## " << *(aMode.m_pHelicityConfigs);
   }

   // Deterministic or not
   // s << '\n' << " ## Deterministic: ";
   // if ( aMode.m_deterministic ) { s << "true"; } else { s << "false"; }

   return s;
}

//
// static member functions
//

const MCDecayMode&
MCDecayMode::unknown() {
   static const MCDecayMode unknownDecayMode = MCDecayMode();
   return unknownDecayMode;
}
