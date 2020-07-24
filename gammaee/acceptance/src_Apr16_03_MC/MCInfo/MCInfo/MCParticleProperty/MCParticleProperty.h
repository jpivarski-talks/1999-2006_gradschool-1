// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLEPROPERTY_H)
#define MCINFO_MCPARTICLEPROPERTY_H
//
// Package:     <MCInfo>
// Module:      MCParticleProperty
// 
// Description: Particle Property object derived from decay.dec
//
// Usage:
//    This is a general class to store the properties like nominal mass,
//    width, etc., of a particle, the list of decay modes, various package
//    numbers (QQ/PDG/GEANT/...).  Currently, object contains the
//    information described in decay.dec.
//
//    Particles property objects can be built in two ways. (a) All of the
//    information can be passed to the constructor in one huge blob,
//    though this is not at all type safe.  (b) Alternatively, an empty
//    object can be built, and the information passed into the object
//    through various set functions.  The latter is preferable, since
//    only one property is passed at a time (reducing the probability
//    that the values for different properties can be swapped), and
//    new properties can be added without affecting existing code
//    that do not rely on those properties.
//
// Author:      Jason Grollman / Lawrence Gibbons
// Created:     Wed Aug 19 13:13:36 EDT 1998
// $Id: MCParticleProperty.h,v 1.8 2002/01/20 19:33:58 lkg Exp $
//
// Revision history
//
// $Log: MCParticleProperty.h,v $
// Revision 1.8  2002/01/20 19:33:58  lkg
// add [] operator for access to decay mode via id
//
// Revision 1.7  2001/12/19 18:11:46  lkg
// new constructor plus other tweaks for StorageHelper compatibility. Implement missing flavor functions
//
// Revision 1.6  2001/10/14 18:58:54  cdj
// fixed bug which could crash program when a MCParticleProperty instance is initialized at file scope
//
// Revision 1.5  2000/10/09 23:31:58  wsun
// Added charmed().
//
// Revision 1.4  2000/10/04 21:21:56  bkh
// Add static unknown function
//
// Revision 1.3  1999/10/19 21:31:20  lkg
// * Add a "mixable" member fcn to the property, to flag whether conjugate
//   particles can mix.
// * isBaryon() --> baryon(), to conform to convention
// * lepton() and neutrino() member fcn's implemented
//
// Revision 1.2  1999/07/06 19:36:09  lkg
// * add a findDecayMode member function based on QQ id
// * implement first of the isXXX member functions: isBaryon
//
// Revision 1.1  1999/06/22 21:30:13  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:22  lkg
// Initial MCInfo sources
//

// system include files
#include <vector>
//#include <string>

// user include files
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// forward declarations
#include "C++Std/fwd_ostream.h"
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
class MCParticlePropertyStore;

class MCParticleProperty
{
      // ---------- friend classes and functions ---------------

      // default output operator for the particle property object
      friend ostream& operator<<(ostream& s, const MCParticleProperty& prop);

   public:
      // ---------- constants, enums and typedefs --------------
      typedef STL_VECTOR( MCDecayMode )::const_iterator const_iterator;
      typedef STL_VECTOR( MCDecayMode )::iterator iterator;
      
      // default values for unspecified ID's.
      static const QQ_id     kUnknownQQId;    // value when QQ id unknown
      static const Geant_id  kUnknownGeantId; // default: no GEANT id
      static const PDG_id    kUnknownPDGId;   // default: no PDG id
      static const Stable_id kUnstableId;     // default: Unstable
      static const Stable_id kNeutrinoStableId; // all neutrinos share ID
      static const string&   unknownName();    // default: no name
      
      // ---------- Constructors and destructor ----------------
      // for storage helper
      MCParticleProperty( const string& name,
			  QQ_id QQId,
			  Stable_id stableId,
			  PDG_id PDGId,
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
			  DABoolean mixable );

      MCParticleProperty();
      MCParticleProperty( const MCParticleProperty& );

      virtual ~MCParticleProperty();
      
      // ---------- member functions ---------------------------
      const MCParticleProperty& operator=( const MCParticleProperty& );
      
      // access functions for querying and setting/resetting individual 
      // properties of this particle
      
      // the store in which this property lives.  Needed for consistency
      // checks of decay modes.
      const MCParticlePropertyStore& store() const;
      void                        setStore( const MCParticlePropertyStore& );

      // the particle name
      const string&  name() const;
      void        setName(const string& name ) ;
      
      // the particle number in the QQ scheme
      QQ_id   QQId() const;
      void setQQId( QQ_id );
      
      // the stable particle code in the QQ scheme
      Stable_id stableId() const;
      void   setStableId( Stable_id );
      
      // the particle number in the PDG scheme
      PDG_id  PDGId() const;
      void setPDGId( PDG_id );
      
      // the particle number in the GEANT 3 numbering scheme
      Geant_id geantId() const;
      void  setGeantId( Geant_id );
      
      // the charge of the particle
      Double  charge() const;
      void setCharge( Double );
      
      // the lifetime of the particle (times the speed of light)
      Double  ctau() const;
      void setCtau( Double );
      
      // the nominal mass of the particle
      Double  mass() const;
      void setMass( Double );
      
      // the nominal width of the particle (0 if this is not a resonance)
      Double  width() const;
      void setWidth( Double );
      
      // the minimum and maximum masses allowed in simulating this particle
      Double minMass() const;
      Double maxMass() const;
      void      setMinMass( Double );
      void      setMaxMass( Double );
      
      // the spin of the particle
      Double  spin() const ;
      void setSpin( Double );
      
      // the particle's parity
      Integer parity() const;
      void setParity( Integer );
      
      // the particle's charge parity
      Integer cParity() const;
      void setCParity( Integer Cparity ) ;

      // whether particle can mix with its charge conjugate
      DABoolean mixable() const;
      void   setMixable( DABoolean );

      // the particle's decay modes
      void clearDecayModes();
      void addDecayMode( const MCDecayMode& );
      const MCDecayMode& throwDecayMode() const;
      const_iterator findDecayMode( const STL_VECTOR( QQ_id  )& daughterList ) const;
      const_iterator findDecayMode( const STL_VECTOR( string )& daughterList ) const;

      // lepton and quark-content info
      virtual DABoolean lepton() const; // charged lepton, that is
      virtual DABoolean neutrino() const;
      virtual DABoolean meson() const;
      virtual DABoolean baryon() const;
      virtual DABoolean strange() const;
      virtual DABoolean charmed() const;
      virtual DABoolean bottom() const;
      virtual DABoolean top() const;

      // Container-like behaviour, since this is a container of the decay
      // modes
      // allow (const) iteration over the decay modes contained in here
      const_iterator begin() const;
      iterator begin();
      const_iterator end() const;
      iterator end();
      Count size() const;
      DABoolean empty() const;
      const MCDecayMode& operator[]( Integer ) const;

      // comparison operators
      DABoolean operator==( const MCParticleProperty& ) const;
      DABoolean operator!=( const MCParticleProperty& ) const;

      // ---------- static member functions --------------------

      static const MCParticleProperty& unknown() ; // the unknown PP
      
   protected:
      // ---------- protected member functions -----------------
      
      // ---------- protected const member functions -----------
      
   private:
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------

      string m_name;
      
      // ID number in various schemes: QQ, stable QQ, PDG and GEANT
      QQ_id m_qq_id;
      Stable_id m_stable_id;
      PDG_id m_pdg_id;
      Geant_id m_geant_id ;
      
      // charge of the particle
      Double m_charge;
      
      // lifetime of the particle (in units c*tau)
      Double m_ctau;
      
      // nominal mass and width
      Double m_mass;
      Double m_width;
      
      // Mass range (if resonance) used for simulation
      Double m_min_mass;
      Double m_max_mass;
      
      // Quantum numbers: spin, parity, charge-parity
      Double m_spin;
      Integer m_parity;
      Integer m_cparity;
      
      // whether particle is mixable
      DABoolean m_mixable;

      // list of all decay modes for this particle
      STL_VECTOR( MCDecayMode )&  m_decayModes;
      // map of the integrated probability (normalized to unity)
      // vs decay mode
      STL_MAP( Likelihood, const MCDecayMode* )&  m_decayModeMap;
      // for use in building map, keep the unnormalized sum of the
      // BF's assigned this mode.
      Likelihood m_branchingFractionSum;
      
      // a pointer to the store in which this lives
      const MCParticlePropertyStore* m_store;

};

// inline function definitions
inline const MCDecayMode& 
MCParticleProperty::operator[]( Integer identifier ) const {
   return m_decayModes[identifier];
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCParticleProperty.cc"
//#endif

#endif /* MCINFO_MCPARTICLEPROPERTY_H */
