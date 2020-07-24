// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCParticleProperty
// 
// Description: Monte Carlo Particle Property object derived from decay.dec
//
// Implementation:
//     Particles property objects can be built in two ways. (a) All of the
//     information can be passed to the constructor in one huge blob,
//     though this is not at all type safe.  (b) Alternatively, an empty
//     object can be built, and the information passed into the object
//     through various set functions.  The latter is preferable, since
//     only one property is passed at a time (reducing the probability
//     that the values for different properties can be swapped), and
//     new properties can be added without affecting existing code
//     that do not rely on those properties.
//
// Author:      Jason Grollman / Lawrence Gibbons
// Created:     Wed Aug 19 13:13:31 EDT 1998
// $Id: MCParticleProperty.cc,v 1.11 2003/01/29 19:15:32 cdj Exp $
//
// Revision history
//
// $Log: MCParticleProperty.cc,v $
// Revision 1.11  2003/01/29 19:15:32  cdj
// get iomanip header from C++Std package
//
// Revision 1.10  2001/12/19 18:11:43  lkg
// new constructor plus other tweaks for StorageHelper compatibility. Implement missing flavor functions
//
// Revision 1.9  2001/11/01 21:26:31  lkg
// warn about and protect handling of decay modes w/ zero branching fractions
//
// Revision 1.8  2001/10/14 18:58:49  cdj
// fixed bug which could crash program when a MCParticleProperty instance is initialized at file scope
//
// Revision 1.7  2000/10/09 23:31:50  wsun
// Added charmed().
//
// Revision 1.6  2000/10/04 21:20:53  bkh
// Add unknown static function
//
// Revision 1.5  2000/01/18 22:22:38  lkg
// Bug fix: Initialize m_mixing member data in copy constructor.
//
// Revision 1.4  1999/10/31 14:21:06  lkg
// Add mixing info to <<() operator for particles that can mix
//
// Revision 1.3  1999/10/19 21:31:36  lkg
// * Add a "mixable" member fcn to the property, to flag whether conjugate
//   particles can mix.
// * isBaryon() --> baryon(), to conform to convention
// * lepton() and neutrino() member fcn's implemented
//
// Revision 1.2  1999/07/07 00:09:23  lkg
// Add findDecayMode member fcn based on QQ_id's.
// Add isBaryon() member fcn
//
// Revision 1.1  1999/06/22 21:28:53  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:21  lkg
// Initial MCInfo sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include "C++Std/iomanip.h"
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCParticleProperty/PDGScheme.h"

// STL classes
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCParticleProperty" ;

// default values for unspecified ID's.
const Geant_id  MCParticleProperty::kUnknownGeantId( -666 );
const PDG_id    MCParticleProperty::kUnknownPDGId( 0 );
const Stable_id MCParticleProperty::kUnstableId( -1 );
const Stable_id MCParticleProperty::kNeutrinoStableId( 0 );
const QQ_id     MCParticleProperty::kUnknownQQId( -666 );


//
// static data member definitions
//

//
// constructors and destructor
//
MCParticleProperty::MCParticleProperty() : 
	m_name( unknownName() ),
	m_qq_id(     kUnknownQQId ),
	m_pdg_id(    kUnknownPDGId ),
	m_geant_id(  kUnknownGeantId ),
	m_stable_id( kUnstableId ),
	m_charge( 0.0 ),
	m_ctau( -1.0 ),
	m_mass( 0.0 ),
	m_width( 0.0 ),
	m_min_mass( 0.0 ),
	m_max_mass( 0.0 ),
	m_spin( 0.0 ),
	m_parity( 0 ),
	m_cparity( 0 ),
	m_mixable( false ),
	m_decayModes( *new STL_VECTOR( MCDecayMode ) ),
	m_decayModeMap( *new STL_MAP( Likelihood, const MCDecayMode* ) ),
	m_branchingFractionSum( 0 ),
	m_store( 0 )
{
   if ( (&m_decayModes == 0) || (&m_decayModeMap == 0) ) {
      report( ERROR, kFacilityString )
	 << "Out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }
}

MCParticleProperty::MCParticleProperty( const string& name,
					QQ_id qqId,
					Stable_id stableId,
					PDG_id pdgId,
					Geant_id geantId,
					Double charge,
					Double ctau,
					Double mass,
					Double width,
					Double minMass,
					Double maxMass,
					Double spin,
					Integer parity,
					Integer cParity,
					DABoolean mixable ) :
   m_store( 0 ),
   m_name( name ),
   m_qq_id( qqId ),
   m_pdg_id( pdgId ),
   m_geant_id( geantId ),
   m_stable_id( stableId ),
   m_charge( charge ),
   m_ctau( ctau ),
   m_mass( mass ),
   m_width(width ),
   m_min_mass( minMass ),
   m_max_mass( maxMass ),
   m_spin( spin ),
   m_parity( parity ),
   m_cparity( cParity ),
   m_mixable( mixable ),
   m_decayModes( *new STL_VECTOR( MCDecayMode ) ),
   m_decayModeMap( *new STL_MAP( Likelihood, const MCDecayMode* ) ),
   m_branchingFractionSum( 0 )
{
   if ( (&m_decayModes == 0) || (&m_decayModeMap == 0) ) {
      report( ERROR, kFacilityString )
	 << "Out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }
}

MCParticleProperty::MCParticleProperty( const MCParticleProperty& rhs ) : 
	m_name(     rhs.m_name ),
	m_qq_id(    rhs.m_qq_id ),
	m_pdg_id(   rhs.m_pdg_id ),
	m_geant_id( rhs.m_geant_id ),
	m_stable_id(rhs.m_stable_id ),
	m_charge( rhs.m_charge ),
	m_ctau( rhs.m_ctau ),
	m_mass( rhs.m_mass ),
	m_width(rhs.m_width ),
	m_min_mass( rhs.m_min_mass ),
	m_max_mass( rhs.m_max_mass ),
	m_spin( rhs.m_spin ),
	m_parity( rhs.m_parity ),
	m_cparity( rhs.m_cparity ),
	m_mixable( rhs.m_mixable ),
	m_decayModes( *new STL_VECTOR( MCDecayMode ) ),
	m_decayModeMap( *new STL_MAP( Likelihood, const MCDecayMode* ) ),
	m_branchingFractionSum( rhs.m_branchingFractionSum ),
	m_store( rhs.m_store )
{
   if ( (&m_decayModes == 0) || (&m_decayModeMap == 0) ) {
      report( ERROR, kFacilityString )
	 << "Out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }
   
   // create the decay mode vector and map.  For safety, use addDecayMode
   // to get ParentProperty <-- DecayMode pointer relationships safely
   // configured
   typedef STL_VECTOR( MCDecayMode )::const_iterator dmIter;
   dmIter done = rhs.m_decayModes.end();
   for ( dmIter mode = rhs.m_decayModes.begin(); mode != done; ++mode ) {
      addDecayMode( *mode );
   }
}

MCParticleProperty::~MCParticleProperty()
{
   delete &m_decayModes;
   delete &m_decayModeMap;
}

//
// assignment operators
//
const MCParticleProperty& 
MCParticleProperty::operator=( const MCParticleProperty& rhs )  {

   if ( this != &rhs ) {

      m_name     = rhs.m_name;
      m_qq_id    = rhs.m_qq_id;
      m_pdg_id   = rhs.m_pdg_id;
      m_geant_id = rhs.m_geant_id;
      m_stable_id= rhs.m_stable_id;
      m_charge   = rhs.m_charge;
      m_ctau     = rhs.m_ctau;
      m_mass     = rhs.m_mass;
      m_width    = rhs.m_width;
      m_min_mass = rhs.m_min_mass;
      m_max_mass = rhs.m_max_mass;
      m_spin     = rhs.m_spin;
      m_parity   = rhs.m_parity;
      m_cparity  = rhs.m_cparity;
      m_store    = rhs.m_store;
      m_decayModes = *new STL_VECTOR( MCDecayMode )( rhs.m_decayModes );
      m_decayModeMap = 
	 *new STL_MAP( Likelihood, const MCDecayMode* )(rhs.m_decayModeMap);
      m_branchingFractionSum = rhs.m_branchingFractionSum;
   }

   return *this;
}

//
// const member functions
//

const MCParticlePropertyStore&
MCParticleProperty::store() const {
   return *m_store;
}

const string&
MCParticleProperty::name() const
{
   return ( m_name ) ;
}

QQ_id
MCParticleProperty::QQId() const
{
   return ( m_qq_id ) ;
}

Stable_id
MCParticleProperty::stableId() const
{
   return ( m_stable_id ) ;
}

PDG_id
MCParticleProperty::PDGId() const
{
   return ( m_pdg_id ) ;
}


Geant_id
MCParticleProperty::geantId() const
{
   return ( m_geant_id ) ;
}

Double
MCParticleProperty::mass() const
{
   return ( m_mass ) ;
}

Double
MCParticleProperty::charge() const
{
   return ( m_charge ) ;
}

Double
MCParticleProperty::spin() const
{
   return ( m_spin ) ;
}

Double
MCParticleProperty::ctau() const
{
   return ( m_ctau ) ;
}


Double
MCParticleProperty::width() const
{
   return ( m_width ) ;
}

Double
MCParticleProperty::minMass() const
{
   return ( m_min_mass ) ;
}

Double
MCParticleProperty::maxMass() const
{
   return ( m_max_mass ) ;
}

Integer
MCParticleProperty::parity() const
{
   return ( m_parity );
}

Integer
MCParticleProperty::cParity() const
{
   return (m_cparity );
}

const MCDecayMode&
MCParticleProperty::throwDecayMode() const {

   report( WARNING, kFacilityString )
      << "Needs a random number generator for proper implementation" << "\n"
      << "Returning mode that would correspond to a random number = 0.5"
      << endl;
   Likelihood diceThrow( 0.5 );

   // look for the first occurence in the map of a key that's
   // >= our random number
   typedef pair<const Likelihood, const MCDecayMode*> LDMPair;
   LDMPair dicePair( diceThrow, static_cast<const MCDecayMode*>(0) );
   typedef STL_MAP( Likelihood, const MCDecayMode* )::const_iterator mapItr;
   mapItr theMode = find_if( m_decayModeMap.begin(),
			     m_decayModeMap.end(),
			     bind2nd(greater_equal<LDMPair>(), dicePair ));

   return *((*theMode).second);
}

MCParticleProperty::const_iterator
MCParticleProperty::begin() const {
   return m_decayModes.begin();
}

MCParticleProperty::iterator
MCParticleProperty::begin() {
   return m_decayModes.begin();
}

MCParticleProperty::const_iterator
MCParticleProperty::end() const {
   return m_decayModes.end();
}

MCParticleProperty::iterator
MCParticleProperty::end() {
   return m_decayModes.end();
}

Count
MCParticleProperty::size() const { 
   return m_decayModes.size(); 
}

DABoolean
MCParticleProperty::empty() const {
   return m_decayModes.empty(); 
}

//
// member functions
//

void 
MCParticleProperty::setName( const string& name ){
   m_name=( name ); 
}

void 
MCParticleProperty::setQQId( QQ_id qq_id ){
   m_qq_id=( qq_id );
}

void 
MCParticleProperty::setStableId( Stable_id stable_id ){
   m_stable_id=( stable_id);
}

void 
MCParticleProperty::setGeantId ( Geant_id geant_id ){
   m_geant_id=( geant_id );
}

void 
MCParticleProperty::setPDGId( PDG_id pdg_id ){
   m_pdg_id=( pdg_id );
}

void MCParticleProperty::setMass( Double mass ){
   m_mass=( mass );
}

void MCParticleProperty::setCharge( Double charge ){
   m_charge=( charge );
}

void MCParticleProperty::setSpin( Double spin ){
   m_spin=( spin);
}

void MCParticleProperty::setCtau( Double ctau ){
   m_ctau=( ctau );
}

void MCParticleProperty::setWidth( Double width ){
   m_width=( width );
}

void MCParticleProperty::setMinMass( Double min_mass ){
   m_min_mass=( min_mass );
}

void MCParticleProperty::setMaxMass( Double max_mass ){
   m_max_mass=( max_mass);
}

void MCParticleProperty::setParity ( Integer parity ){
   m_parity=( parity );
}

void MCParticleProperty::setCParity ( Integer cparity ){
   m_cparity=( cparity );
}

void MCParticleProperty::setMixable( DABoolean mixability ) {
   m_mixable = mixability;
}

void MCParticleProperty::clearDecayModes() {
   m_decayModes.clear();
   m_decayModeMap.clear();
   m_branchingFractionSum = 0;
}
  
void MCParticleProperty::addDecayMode ( const MCDecayMode& newDecayMode){

   // update the sum of branching fractions so far
   m_branchingFractionSum += newDecayMode.branchingFraction();

   // put the new Mode at the end of the list of modes
   m_decayModes.push_back( newDecayMode );

   // give the decay mode an identifier relative to this parent
   m_decayModes.back().setIdentifier( m_decayModes.size() );
   m_decayModes.back().setParentProp( *this );

   if ( newDecayMode.branchingFraction() == 0 ) {
      report( WARNING, kFacilityString )
         << "Adding a decay mode with a branching fraction of zero!!!!\n"
         << m_decayModes.back()
         << endl;
   }
   //
   // remake the map.  
   //
   // Since the keys are the integrated, normalized probability, all 
   // the keys will change.  Therefore we must clear the map and 
   // start afresh
     m_decayModeMap.clear();

   // now actually build the map from the info stored in the vector
   typedef STL_VECTOR( MCDecayMode )::iterator modeIter;
   Likelihood runningProb( 0 );
   modeIter done = m_decayModes.end();
   for ( modeIter itMode = m_decayModes.begin(); itMode != done; ++itMode ) {

      // get the normalized running probability, which acts as a key into
      // the map
      runningProb += itMode->branchingFraction();
      Double integratedProb;
      if ( m_branchingFractionSum != 0 ) {
         integratedProb = runningProb / m_branchingFractionSum;
      } else {
         integratedProb = 0;
      }
      	

      // add (a pointer to) this key/config to the map
      MCDecayMode& modeToStore( *itMode );
      m_decayModeMap[integratedProb] = &modeToStore;

   }
}

MCParticleProperty::const_iterator
MCParticleProperty::findDecayMode( const STL_VECTOR( string )& daughterList ) const {
   MCDecayMode::ModeCheck thisChecker( name(), daughterList );
   return find_if( begin(), end(), thisChecker );
}

MCParticleProperty::const_iterator
MCParticleProperty::findDecayMode( const STL_VECTOR( QQ_id )& daughterList ) const {
   MCDecayMode::ModeCheckId thisChecker( QQId(), daughterList );
   return find_if( begin(), end(), thisChecker );
}

void
MCParticleProperty::setStore( const MCParticlePropertyStore& aStore ) {
   m_store = &aStore;
}

DABoolean
MCParticleProperty::lepton() const {
   Integer absPdg( abs(m_pdg_id) );
   Integer leptonType = absPdg % 2;
   return (absPdg > 10 && absPdg < 20 && leptonType == 1 );
}

DABoolean
MCParticleProperty::neutrino() const {
   Integer absPdg( abs(m_pdg_id) );
   Integer leptonType = absPdg % 2;
   return (absPdg > 10 && absPdg < 20 && leptonType == 0 );
}

DABoolean
MCParticleProperty::baryon() const {
   Integer baryonDigit = (abs(m_pdg_id) / kNq1) % 10;
   return (baryonDigit != 0);
}

DABoolean 
MCParticleProperty::meson() const {
  if ( baryon() ) return false;

  Integer q2Digit = (abs(m_pdg_id) / kNq2) % 10;
  return (q2Digit != 0);
}

DABoolean
MCParticleProperty::strange() const {

    Integer q1Digit = (abs(m_pdg_id) / kNq1) % 10;
    Integer q2Digit = (abs(m_pdg_id) / kNq2) % 10;
    Integer q3Digit = (abs(m_pdg_id) / kNq3) % 10;

    return (q1Digit == kStrange) ||
           (q2Digit == kStrange) ||
           (q3Digit == kStrange);
}

DABoolean
MCParticleProperty::charmed() const {

    Integer q1Digit = (abs(m_pdg_id) / kNq1) % 10;
    Integer q2Digit = (abs(m_pdg_id) / kNq2) % 10;
    Integer q3Digit = (abs(m_pdg_id) / kNq3) % 10;

    return (q1Digit == kCharm) ||
           (q2Digit == kCharm) ||
           (q3Digit == kCharm);
}

DABoolean
MCParticleProperty::bottom() const {

    Integer q1Digit = (abs(m_pdg_id) / kNq1) % 10;
    Integer q2Digit = (abs(m_pdg_id) / kNq2) % 10;
    Integer q3Digit = (abs(m_pdg_id) / kNq3) % 10;

    return (q1Digit == kBottom) ||
           (q2Digit == kBottom) ||
           (q3Digit == kBottom);
}

DABoolean
MCParticleProperty::top() const {

    Integer q1Digit = (abs(m_pdg_id) / kNq1) % 10;
    Integer q2Digit = (abs(m_pdg_id) / kNq2) % 10;
    Integer q3Digit = (abs(m_pdg_id) / kNq3) % 10;

    return (q1Digit == kTop) ||
           (q2Digit == kTop) ||
           (q3Digit == kTop);
}

DABoolean 
MCParticleProperty::mixable() const {
   return m_mixable;
}

DABoolean
MCParticleProperty::operator==( const MCParticleProperty& rhs ) const {

   return 
      ( m_name == rhs.m_name ) &&
      ( m_qq_id == rhs.m_qq_id ) &&
      ( m_pdg_id == rhs.m_pdg_id ) &&
      ( m_geant_id == rhs.m_geant_id ) &&
      ( m_stable_id == rhs.m_stable_id ) &&
      ( m_charge == rhs.m_charge ) &&
      ( m_ctau == rhs.m_ctau ) &&
      ( m_mass == rhs.m_mass ) &&
      ( m_width == rhs.m_width ) &&
      ( m_min_mass == rhs.m_min_mass ) &&
      ( m_max_mass == rhs.m_max_mass ) &&
      ( m_spin == rhs.m_spin ) &&
      ( m_parity == rhs.m_parity ) &&
      ( m_cparity == rhs.m_cparity ) &&
      ( m_mixable == rhs.m_mixable ) &&
      ( m_decayModes == rhs.m_decayModes );
}

DABoolean
MCParticleProperty::operator!=( const MCParticleProperty& rhs ) const {

   return ! operator==( rhs );
}

//
// static member functions
//

const MCParticleProperty& 
MCParticleProperty::unknown() 
{
  static const MCParticleProperty k_unknownPP = MCParticleProperty() ;
  return k_unknownPP ;
}

/*
void
MCParticleProperty::quarkContent( PDG_Id pdg, 
				  Integer& quarkN1,
				  Integer& quarkN2,
				  Integer& quarkN3 ) {
   // reminder: the pdg ID number
}
*/
//
// friend functions
//

// default output operator for the particle property object
ostream& operator<<(ostream& s, const MCParticleProperty& prop)
{
   // Output the PARTICLE decay.dec command line info
   s << "PARTICLE  " 
     << setw(6)                     << prop.m_name
     << setw(5)  		    << prop.m_qq_id
     << setw(5)  		    << prop.m_stable_id
     << setw(10) << setprecision(6) << prop.m_mass
     << setw(5)  << setprecision(1) << prop.m_charge
     << setw(5)  << setprecision(1) << prop.m_spin
     << setw(11) << setprecision(6) << prop.m_ctau
     << setw(7)  << setprecision(3) << prop.m_width
     << setw(7)  << setprecision(3) << prop.m_min_mass
     << setw(7)  << setprecision(3) << prop.m_max_mass << '\n'
     << "    PDG:" << setw(7)                  << prop.m_pdg_id << "/"
     <<   "Geant:" << setw(7)                  << prop.m_geant_id
     << "      P/C:"
     << prop.m_parity << "/"
     << prop.m_cparity;

   if ( prop.mixable() ) {
      const MCParticlePropertyStore& aStore( prop.store() );
      const string& conjName(aStore.qqIdToName(aStore.conjugateQQ(prop.m_qq_id)));
      s << ", mixes to " << conjName;
   }

   // now list the decay modes
   typedef MCParticleProperty::const_iterator modeIter;
   modeIter done = prop.end();
   for ( modeIter itMode = prop.begin(); itMode != done; ++itMode ) {
      s << '\n' << "     " << *itMode;
   }

   return s;
}


const string&    
MCParticleProperty::unknownName()
{ 
  static string kUnknownName("Unknown");
    return kUnknownName;
}
