// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLEPROPERTYSTORE_H)
#define MCINFO_MCPARTICLEPROPERTYSTORE_H
//
// Package:     <MCInfo>
// Module:      MCParticlePropertyStore
// 
// Description: Container of Particle Property objects, conversion utilities
//              between name/QQ/PDG id's for Property objects stored
//
// Usage:
//    A MCParticlePropertyStore object maintains a container of
//    MCParticleProperty objects that are to be used for simulating
//    particle decays.  Various unique identifiers can be used to access
//    particle properties.  So far, these are
//       QQ id
//       Name
//       PDG id
//       Geant id
//    In the standard decay.dec, there are at least two cases involving
//    8 particles for which the Stable code is not unique.  Therefore
//    access to properties in the store via stable code is not supported.
// 
//    Utilities for managing Property objects in the store:
//   
// Author:      Jason Grollman / Lawrence Gibbons
// Created:     Wed Aug 19 20:01:42 EDT 1998
// $Id: MCParticlePropertyStore.h,v 1.7 2002/01/20 19:31:58 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropertyStore.h,v $
// Revision 1.7  2002/01/20 19:31:58  lkg
// pass file name strings as references
//
// Revision 1.6  2001/12/19 18:11:56  lkg
// non-const access names now have 'Modifiable' in name.  Store names of .dec files used to create store
//
// Revision 1.5  2001/05/12 17:45:28  lkg
// implement a dereferencing iterator for the particle property store, and provide begin and end member fcn's for it
//
// Revision 1.4  1999/10/31 14:22:46  lkg
// Add geantIdToQQId member fcn def.
//
// Revision 1.3  1999/10/19 21:56:42  lkg
// add a handleQQKluges() member fcn that does just that.  It acts as a single
// point that deals with all the evils that QQ does behind the scenes with
// decays that are not explicitly documented in decay.dec
//
// Revision 1.2  1999/07/06 19:37:28  lkg
// Add a "addSpecialParticles" option for use with "special", nonphysical
// particles that one doesn't want cluttering decay.dec
//
// Revision 1.1  1999/06/22 21:30:13  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:22  lkg
// Initial MCInfo sources
//

// system include files
#include <functional>

// user include files
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCPPStoreItr.h"

// forward declarations
#include "C++Std/fwd_ostream.h"
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"

class MCParticlePropertyStore
{
      // ---------- friend classes and functions ---------------

      // default output operator for the particle property object
      friend ostream& operator<<(ostream& aStream, 
				 const MCParticlePropertyStore& aStore);

   public:
      // ---------- constants, enums and typedefs --------------
      
      // ---------- Constructors and destructor ----------------
      // create an empty store
      MCParticlePropertyStore();

      // Implement a copy constructor that creates a deep copy of
      // the particle store.  Then users can create an extended
      // version of the store without (a) modifying the standard
      // store and (b) confusion as to control of memory management
      MCParticlePropertyStore( const MCParticlePropertyStore& );

      // Ditto for the assignment operator
      const MCParticlePropertyStore& 
      operator=( const MCParticlePropertyStore& );

      virtual ~MCParticlePropertyStore();
      
      // ---------- member functions ---------------------------
      
      // addProperty
      // -- takes a reference to a property object, and creates a
      //    new copy of this property object in the container.
      //    It will be an ERROR to replace a pre-existing particle
      //    in this fashion.
      void addProperty( const MCParticleProperty& newParticle );

      // addProperty_noCopy
      // -- takes a pointer to a property object, and assumes
      //    ownership of the property object.
      //    It will be an ERROR to replace a pre-existing particle
      //    in this fashion.
      void addProperty_noCopy( MCParticleProperty* newParticle );
      
      // replaceProperty
      // -- This function will delete the old property object
      //    with the QQ ID of the new Particle, and replace
      //    it with the new property object
      void replaceProperty( const MCParticleProperty& replacementParticle );
      
      // deleteProperty
      // -- deletes the requested particle property from the store
      void deleteProperty( QQ_id );
      
      // setStoreVersion
      // -- sets the version number associated with this group of property
      //    objects
      void setVersion( Integer );

      // add special purpose particles that we don't necessarily want in
      // decay.dec
      void addSpecialParticles();

      // handle kluges because QQ handles decays in ways that are sometimes
      // opaque from the spec's in decay.dec
      void handleQQKluges();

      // Set Decay File names
      void setStandardDecayFile( const string& iFileName );
      void setUserDecayFile( const string& iFileName );

      // pass back properties that can be modified
      MCParticleProperty& getModifiableUsingName(const string& name);
      MCParticleProperty& getModifiableUsingQQId(QQ_id);
      MCParticleProperty& getModifiableUsingPDGId(PDG_id);

      // ---------- const member functions ---------------------
      
      // container-like functions.  MCPPStoreItr is a const iterator
      MCPPStoreItr begin() const;
      MCPPStoreItr end() const;

      // version number assigned to this property store
      Integer version() const;

      // propertyExists
      // -- check whether a Property with a given QQ ID is defined
      DABoolean propertyExists( QQ_id ) const;
      
      // getUsingXxxx
      // -- lookup functions that return a reference to a property
      //    object.  One for each of the various ID's associated with
      //    each object.  These should be used for looking at properties
      //    of particles in the store
      
      const MCParticleProperty& operator[](const string&) const;
      const MCParticleProperty& getUsingName(const string& name) const;

      const MCParticleProperty& operator[](QQ_id) const;
      const MCParticleProperty& getUsingQQId(QQ_id) const;

      const MCParticleProperty& getUsingGeantId(Geant_id) const;

      const MCParticleProperty& getUsingPDGId(PDG_id) const;
      

      // getCopyUsingXxxx
      // -- lookup functions that return a copy of a property
      //    object.  These are utility routines meant mainly for
      //    for use in copying / modifying properties already in the
      // store
      
      MCParticleProperty getCopyUsingName( const string& Name) {
	 return getUsingName( Name ); }

      MCParticleProperty
      getCopyUsingQQId( QQ_id qqId ) const {
	 return getUsingQQId( qqId ); }

      MCParticleProperty
      getCopyUsingGeantId(Geant_id geantId) const {
	 return getUsingGeantId( geantId ); }

      MCParticleProperty
      getCopyUsingPDGId(PDG_id pdgId) const {
	 return getUsingPDGId( pdgId ); }
      

      // XxxxToQQid
      // QQidToXxxx
      // -- For convenience, provide fast conversion to/from the
      //    QQ ID and the other types of ID.  This way, a user doesn't
      //    have to actually grab a property object to do the conversion.
      //    Since access to the properties is via any of the possible
      //    ID's, assume that the implementation of the store can do
      //    the conversion efficiently, and hence is worthwhile to provide.
      // QQ_id <-> Name
      QQ_id nameToQQId( const string& aName )   const;
      const string& qqIdToName( QQ_id ) const;
      // QQ_id <-> PDGId
      QQ_id  pdgIdToQQId( PDG_id ) const;
      PDG_id qqIdToPDGId( QQ_id ) const;
      // QQ_id <-> GeantId
      QQ_id geantIdToQQId( Geant_id ) const;
//      Geant_id          qqIdToGeantId(  QQ_id ) const;

      // Return functions for decay file names
      const string& standardDecayFile() const { return m_standardDecayFile; }
      const string& userDecayFile() const { return m_userDecayFile; }
      
      // QQ_id for conjugate particle
      QQ_id conjugateQQ( QQ_id ) const;

      // comparison operators
      DABoolean operator==( const MCParticlePropertyStore& rhs ) const;
      DABoolean operator!=( const MCParticlePropertyStore& rhs ) const;

      // ---------- static member functions --------------------
      static PDG_id conjugatePDG( PDG_id );

   protected:
      // ---------- protected member functions -----------------
      
      // ---------- protected const member functions -----------
      
   private:
      
      // ---------- Constructors and destructor ----------------
      
      // ---------- private member functions -------------------
      // utility to delete all of the Property objects held by the store
      void killAllPropertyObjects();
      // utility to copy all of the Property objects held by another store
      void copyAllPropertyObjects( const MCParticlePropertyStore& );
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------
      
      
      // This representation of the particle property store keeps
      // a pointer to the particle property object, with the primary
      // reference by QQ ID.
      
      // The primary, fastest access store is via QQ id, though we must
      // offset the actual QQ ID by kQQidOffset because of the use of
      // negative QQ ID's (currently for quarks and gluons) in QQ
      STL_VECTOR( MCParticleProperty* )& m_ppList;
      

      // For fast reference by name, we store a map between name and 
      // QQ ID.  We also do the same for the PDG ID, which, while
      // an integer, isn't anywhere near to being sequential
      STL_MAP(string, QQ_id)& m_nameToQQ;
      STL_VECTOR(string)& m_qqToName;
      STL_MAP(PDG_id, QQ_id)&  m_pdgToQQ;
      STL_VECTOR(PDG_id)&  m_qqToPDG;
      
      // For fast reference by geant ID's which are roughly serial, 
      // we store a vector of QQ ID's referenced by the geant ID
      STL_VECTOR( QQ_id )& m_geantToQQ;

      // Hold the name of the standard/user decay files for safe keeping
      // These will be set by the decay file parser, and will be blank until 
      // then (needed to pass on to QQ when using generators)
      string m_standardDecayFile;
      string m_userDecayFile;

      // Finally, we let a version number be associated with the properties
      // in this store.  In practice, this will be set to the standard
      // decay.dec version number
      Integer m_storeVersion;

      // ---------- helper functions for use with STL algorithms ---------
   public:
      struct TransNameToQQ : public unary_function<const string&, QQ_id> {
	    TransNameToQQ( const MCParticlePropertyStore& aStore  ) : 
	       m_store( &aStore ){};
	    QQ_id operator()(const string& name) {
	       return m_store->nameToQQId(name); };
	    const MCParticlePropertyStore* m_store;
      };

      struct TransQQToName : public unary_function<QQ_id, const string&> {
	    TransQQToName( const MCParticlePropertyStore& aStore  ) : 
	       m_store( &aStore ){};
	    const string& operator()(QQ_id id) {
	       return m_store->qqIdToName(id); };
	    const MCParticlePropertyStore* m_store;
      };

      struct TransQQToConj : public unary_function<QQ_id, QQ_id> {
	    TransQQToConj( const MCParticlePropertyStore& aStore  ) : 
	       m_store( &aStore ){};
	    QQ_id operator()(QQ_id id) { return m_store->conjugateQQ(id); };
	    const MCParticlePropertyStore* m_store;
      };
};

// inline function definitions
inline const MCParticleProperty&
MCParticlePropertyStore::operator[]( QQ_id qqId ) const {
   return getUsingQQId( qqId );
}

inline const MCParticleProperty&
MCParticlePropertyStore::operator[]( const string& name ) const {
   return getUsingName( name );
}



// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/MCParticlePropertyStore.cc"
//#endif

#endif /* MCINFO_MCPARTICLEPROPERTYSTORE_H */
