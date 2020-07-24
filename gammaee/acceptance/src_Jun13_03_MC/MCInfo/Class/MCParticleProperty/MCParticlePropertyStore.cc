// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCParticlePropertyStore
// 
// Description: Container of Particle Property objects
//
// Implementation:
//
// Author:      Jason Grollman / Lawrence Gibbons
// Created:     Wed Aug 19 20:01:36 EDT 1998
// $Id: MCParticlePropertyStore.cc,v 1.10 2003/01/29 19:15:32 cdj Exp $
//
// Revision history
//
// $Log: MCParticlePropertyStore.cc,v $
// Revision 1.10  2003/01/29 19:15:32  cdj
// get iomanip header from C++Std package
//
// Revision 1.9  2002/02/05 03:39:00  lkg
// upgraded diagnostics
//
// Revision 1.8  2002/01/20 19:29:17  lkg
// MCParticlePropertyStore.cc
//
// Revision 1.7  2001/12/19 18:11:54  lkg
// non-const access names now have 'Modifiable' in name.  Store names of .dec files used to create store
//
// Revision 1.6  2001/10/14 18:58:49  cdj
// fixed bug which could crash program when a MCParticleProperty instance is initialized at file scope
//
// Revision 1.5  2001/05/12 17:45:26  lkg
// implement a dereferencing iterator for the particle property store, and provide begin and end member fcn's for it
//
// Revision 1.4  1999/10/31 14:20:00  lkg
// Return kUnknownQQId in mem. fcn. geantIdToQQId in the case of a geantId that
// doesn't exist in the store
//
// Revision 1.3  1999/10/19 21:56:33  lkg
// add a handleQQKluges() member fcn that does just that.  It acts as a single
// point that deals with all the evils that QQ does behind the scenes with
// decays that are not explicitly documented in decay.dec
//
// Revision 1.2  1999/07/07 00:11:02  lkg
// Add an addSpecialParticles member function with an "e+e-" kluge for use
// with the production vertex of the -->decay<-- tree
//
// Revision 1.1  1999/06/22 21:28:53  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:21  lkg
// Initial MCInfo sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif             
#include <assert.h>
#include "C++Std/iomanip.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCParticleProperty/MCQQBar.h"

// STL classes
#include <map>
#include <vector>

//
// constants, enums and typedefs
//
typedef STL_VECTOR( MCParticleProperty* )::const_iterator PPListItr; 
typedef STL_MAP( string, QQ_id )::const_iterator        NameListItr; 
typedef STL_MAP( QQ_id, QQ_id )::const_iterator          PDGListItr; 
typedef STL_VECTOR( QQ_id )::const_iterator            GeantListItr;

//static const char* const kFacilityString = "MCInfo.MCParticlePropertyStore" ;
static const char* const kFacilityString = "MCInfo.MCParPropStore" ;
static MCParticleProperty* kNullPropertyPointer = (MCParticleProperty*) 0;
static const string kLineOffset = "    ";
//
// static data member definitions
//
// --- default sizes for use in building the member-item vectors
static const Integer kQQidOffset = -MCQQBar::kQQBarIdToQQId;
static const Integer kQQidMax    = 400;
static const Integer kDefaultListSize = kQQidOffset + kQQidMax;
static const Integer kQQIdEpem   = -14;
static const Integer kPDGIdEpem  = 9900000;


//
// constructors and destructor
//
MCParticlePropertyStore::MCParticlePropertyStore() : 
   m_ppList(     *new STL_VECTOR(MCParticleProperty*)(
      kDefaultListSize,
      kNullPropertyPointer) ), 
   m_geantToQQ(  *new STL_VECTOR(QQ_id)(
      kDefaultListSize,
      MCParticleProperty::kUnknownGeantId) ),
   m_nameToQQ(   *new STL_MAP(string, QQ_id) ),
   m_pdgToQQ(    *new STL_MAP(PDG_id, QQ_id) ),
   m_qqToName(   *new STL_VECTOR(string)(
      kDefaultListSize,
      MCParticleProperty::unknownName()) ),
   m_qqToPDG(    *new STL_VECTOR(PDG_id)(
      kDefaultListSize,
      MCParticleProperty::kUnknownPDGId) ),
   m_standardDecayFile( "" ),
   m_userDecayFile( "" )
{
   if( 0 == &m_ppList      ||
       0 == &m_geantToQQ   ||
       0 == &m_qqToName    ||
       0 == &m_qqToPDG     ||
       0 == &m_nameToQQ    ||
       0 == &m_pdgToQQ        )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }  
}

MCParticlePropertyStore::MCParticlePropertyStore( const MCParticlePropertyStore& rhs ) :
   m_ppList(     *new STL_VECTOR(MCParticleProperty*)(
      kDefaultListSize,
      kNullPropertyPointer) ),
   m_geantToQQ(  *new STL_VECTOR(QQ_id)(
      kDefaultListSize,
      MCParticleProperty::kUnknownGeantId) ),
   m_nameToQQ(   *new STL_MAP(string, QQ_id) ),
   m_pdgToQQ(    *new STL_MAP(PDG_id, QQ_id) ),
   m_qqToName(   *new STL_VECTOR(string)(
      kDefaultListSize,
      MCParticleProperty::unknownName()) ),
   m_qqToPDG(    *new STL_VECTOR(PDG_id)(
      kDefaultListSize,
      MCParticleProperty::kUnknownPDGId) ),
   m_standardDecayFile( rhs.m_standardDecayFile ),
   m_userDecayFile( rhs.m_userDecayFile )
{
   // Make sure that we could create all the member items we needed
   if( 0 == &m_ppList      ||
       0 == &m_geantToQQ   ||
       0 == &m_qqToName    ||
       0 == &m_qqToPDG     ||
       0 == &m_nameToQQ    ||
       0 == &m_pdgToQQ        )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }
  
   /*
    * A copy of the vector containing the particle properties is implemented as
    * a deep copy. This avoids possible clashes in the memory management of the
    * MCParticleProperty objects contained in the store. The copy makes use of
    * the AddProperty member function to simplify the procedure.
    */
   
   // Copy the property objects from rhs to the new vectors
   // that we have created.  Note that  copyAllPropertyObjects
   // utilizes addProperty, which automatically updates all
   // the various ID vectors/maps
   copyAllPropertyObjects( rhs );

   // copy the version number
   m_storeVersion = rhs.m_storeVersion;
}

MCParticlePropertyStore::~MCParticlePropertyStore() {
   // first, delete all of the property objects that we created
   killAllPropertyObjects();
   
   // now delete the vectors and maps themselves
   delete &m_ppList;
   delete &m_geantToQQ;
   delete &m_nameToQQ;
   delete &m_pdgToQQ;
   delete &m_qqToName;
   delete &m_qqToPDG;
}

//
// assignment operators
//
const MCParticlePropertyStore& 
MCParticlePropertyStore::operator=( const MCParticlePropertyStore& rhs ) {
   if( this != &rhs ) {
      // start out by removing all particle property objects that are contained
      // in *this.  Wouldn't want to leave some stale objects floating in
      // memory!
      killAllPropertyObjects();
      
      // resize the vectors to be the same size as that of rhs
      m_ppList.resize( rhs.m_ppList.size() );
      
      // now copy the all of the property objects.  Note that 
      // copyAllPropertyObjects utilizes addProperty, which automatically
      // updates all the various ID vectors/maps
      copyAllPropertyObjects( rhs );

      // copy the version number
      m_storeVersion = rhs.m_storeVersion;

      // copy the file names
      m_standardDecayFile = rhs.m_standardDecayFile;
      m_userDecayFile = rhs.m_userDecayFile;
   }
   
   return *this;
}

//
// member functions
//
void
MCParticlePropertyStore::setStandardDecayFile( const string& iFileName ) {
   m_standardDecayFile = iFileName;
}

void
MCParticlePropertyStore::setUserDecayFile( const string& iFileName ) {
   m_userDecayFile = iFileName;
}

void
MCParticlePropertyStore::addProperty(const MCParticleProperty& newParticle )
{
   MCParticleProperty* localParticle = new MCParticleProperty( newParticle );
   addProperty_noCopy( localParticle );
}

void 
MCParticlePropertyStore::addProperty_noCopy(MCParticleProperty* newParticle )
{
   // get the QQ id of the particle to be added
   QQ_id newQQid = newParticle->QQId();

   // check to see that the current store can handle this QQ id.  For now
   // issue an error and abort.  Later on, we can do something like shift
   // all of the objects in the store to a higher index
   if ( newQQid < -kQQidOffset )
   {
      report( ERROR, kFacilityString )
	 << "The particle with QQ ID " << newQQid
	 << "has a QQ ID too negative for this implementation of the store"
	 << "Talk to the current maintainer of the store." << endl;
      assert( false );
      exit(1);
   }


   // check to see that a previously existing property doesn't already
   // exist with that QQ id.  If it does, issue an ERROR
   DABoolean idAlreadyExists = propertyExists( newQQid );
   if ( idAlreadyExists )
   {
      const MCParticleProperty& previousProperty = getUsingQQId(newQQid);
      
      report( ERROR, kFacilityString )
	 << "The QQ ID " << newQQid 
	 << "already exists in the store. "
	 << "It can not be overwritten by addProperty" << endl;
      report( INFO, kFacilityString )
	 << "The pre-existing object has the following info" << '\n'
	 << previousProperty 
	 << endl;
      assert( false );
      exit( 1 );
   }

   // require the new particle to have a name
   const string& newName = newParticle->name();
   if ( newName == MCParticleProperty::unknownName() )
   {
      report( ERROR, kFacilityString )
	 << "Attempt to add particle with QQ id " << newQQid 
	 << ", which has no name" << endl;
      assert( false );
      exit(1);
   }


   // check that all of the alternate ID's are unique
   DABoolean alternateIdOk = true;
   string badIDtypes = " ";

   // -- name:
   if ( m_nameToQQ.find( newName ) != m_nameToQQ.end() )
   {
   	alternateIdOk = false;
   	badIDtypes += "Name  ";
   }
   

   // -- PDG id
   PDG_id newPDG = newParticle->PDGId();
   STL_MAP(PDG_id, QQ_id)::const_iterator idPair = m_pdgToQQ.find( newPDG );
   if ( idPair != m_pdgToQQ.end() )
   {
   	report( ERROR, kFacilityString )
   	   << "Found pre-existing property "
   	   << getUsingQQId( (*idPair).second )
   	   <<endl;
   	   
   	alternateIdOk = false;
   	badIDtypes += "PDG id  ";
   }


   // -- Geant id: this is allowed to be undefined, so don't issue
   //    an error in that case, but it should be a valid id if specified
   Geant_id newGeant = newParticle->geantId();
   if ( newGeant != MCParticleProperty::kUnknownGeantId )
   {
      QQ_id foundQQid =
	 MCParticleProperty::kUnknownGeantId;
      if ( newGeant >= 0 && newGeant < m_geantToQQ.size() )
      {
	 foundQQid = m_geantToQQ[newGeant];
      }
      if ( foundQQid != MCParticleProperty::kUnknownGeantId ||
           newGeant < 0 )
      {
   	   alternateIdOk = false;
   	   badIDtypes += "Geant id  ";
      }
   }

   // if one of the ID's found is already present, issue error
   if ( ! alternateIdOk )
   {
      report( ERROR, kFacilityString )
	 << "The ID  of type(s) " << '\n'  << kLineOffset << kLineOffset
	 << badIDtypes << '\n'  << kLineOffset
	 << "for the new particle with QQ id " 
	 << newQQid  << '\n' << kLineOffset
	 << "is already used by other particles in the store,"  
	 << '\n' << kLineOffset
	 << "or perhaps has an invalid range" << endl;
      assert( false );
      exit(1);
   }
   
   //
   // Finally, from the store's point-of-view, the property is
   // well-enough behaved to add to the store...
   //

   // 1) because the QQ ID's can be negative, we need to offset the
   // QQ id before accessing the vector
   QQ_id offsetQQid = newQQid + kQQidOffset;
   // 2) if we've gone beyond the current end of the store, resize it to
   // hold this new QQ ID.  Add a bit of extra room, since chances are we'll
   // hit a few particles in a row with large'ish QQ ID's
   if ( m_ppList.size() <= offsetQQid ) 
   {
      m_ppList.resize( offsetQQid+10, kNullPropertyPointer );
      m_qqToName.resize( offsetQQid+10 );
      m_qqToPDG.resize( offsetQQid+10 );
   }
   // 3) save a pointer to new property (whose memory will be owned
   // by the store), made via a copy of the property passed in
   m_ppList[offsetQQid] = newParticle;
   m_ppList[offsetQQid]->setStore( *this );

   // bring the other ID's for referencing this particle up to date in the
   // store.  Note that we've obtained all of the alternate ID's from the
   // object when checking the validity of those id's
   
   // -- name
   m_qqToName[offsetQQid] = newName;
   m_nameToQQ[newName] = newQQid;

   // -- pdg ID
   m_qqToPDG[offsetQQid] = newPDG;
   if ( newPDG != MCParticleProperty::kUnknownPDGId ) {
      m_pdgToQQ[newPDG] = newQQid;
   }

   // -- geant ID
   Integer arraySize = m_geantToQQ.size();
   if ( arraySize <= newGeant ) {
      m_geantToQQ.resize( newGeant, MCParticleProperty::kUnknownGeantId );
   }
   if ( newGeant != MCParticleProperty::kUnknownGeantId ) {
      m_geantToQQ[newGeant] = newQQid;
   }
}

void 
MCParticlePropertyStore::deleteProperty( QQ_id staleQQid ) {
   // to map the negative QQ id's to positive vector references in the map,
   // offset the QQ id
   QQ_id offsetStaleId = staleQQid + kQQidOffset;

   // check to make sure that an object with this QQ ID is actually stored.
   MCParticleProperty* foundProp = (MCParticleProperty*) 0;
   Integer listSize = m_ppList.size();
   if ( offsetStaleId >=0 && offsetStaleId < listSize )
   {
      foundProp = m_ppList[offsetStaleId];
   }
   
   // if the property object exists, eliminate all references to it in the
   // various member stores
   if ( foundProp != 0 ) {
      // zero out the pointer to this property in the store
      m_ppList[offsetStaleId] = 0;

      // get all of the other ID's
      const string&                    pName = foundProp->name();
      PDG_id       pdgID = foundProp->PDGId();
      Geant_id   geantID = foundProp->geantId();
      

      // do an erase in the case of the map member functions
      STL_MAP( string, QQ_id)::iterator nameLookUp = m_nameToQQ.find( pName );
      if ( nameLookUp != m_nameToQQ.end() ) {
	 m_nameToQQ.erase( nameLookUp );
      }

      STL_MAP(PDG_id, QQ_id)::iterator pdgLookUp = m_pdgToQQ.find( pdgID );
      if ( pdgLookUp != m_pdgToQQ.end() ) {
	 m_pdgToQQ.erase( pdgLookUp );
      }
      
      // for the vectors, set the qq ID to unknown.  Note that such an
      // action is not valid if the geant ID is not defined
      // for the Property object we are deleting.
      if ( geantID != MCParticleProperty::kUnknownGeantId ) {
	 m_geantToQQ[geantID] = MCParticleProperty::kUnknownGeantId;
      }
      m_qqToName[offsetStaleId] = MCParticleProperty::unknownName();
      m_qqToName[offsetStaleId] = MCParticleProperty::kUnknownPDGId;

      // Last but not least, delete the old, unwanted object
      delete foundProp;
   } // foundProp !=0 block
}

void 
MCParticlePropertyStore::replaceProperty( 
   const MCParticleProperty& replacementParticle )
{
    // delete the previous incarnation of this particle
    QQ_id replacementID = 
        replacementParticle.QQId();

    deleteProperty( replacementID );
    
    // now add the replacement particle back in
    addProperty( replacementParticle );
}


MCParticleProperty&
MCParticlePropertyStore::getModifiableUsingQQId( QQ_id qqId )
{
   MCParticleProperty* temp 
      = const_cast<MCParticleProperty*>( &getUsingQQId( qqId ) );
   return *temp;
}

MCParticleProperty&
MCParticlePropertyStore::getModifiableUsingName( const string& name )
{
   MCParticleProperty* temp 
      = const_cast<MCParticleProperty*>( &getUsingName( name ) );
   return *temp;
}

MCParticleProperty&
MCParticlePropertyStore::getModifiableUsingPDGId( PDG_id pdgId )
{
   MCParticleProperty* temp 
      = const_cast<MCParticleProperty*>( &getUsingPDGId( pdgId ) );
   return *temp;
}

//
// const member functions
//

MCPPStoreItr
MCParticlePropertyStore::begin() const {
   STL_VECTOR( MCParticleProperty* )::const_iterator realBegin;
   STL_VECTOR( MCParticleProperty* )::const_iterator endItr = m_ppList.end();
   STL_VECTOR( MCParticleProperty* )::const_iterator bgnItr = m_ppList.begin();
   for( STL_VECTOR( MCParticleProperty* )::const_iterator prop = bgnItr;
	prop != endItr, (*prop) == 0;
	++prop ) {
      realBegin = prop;
   }
   return MCPPStoreItr( ++realBegin, endItr );
}

MCPPStoreItr
MCParticlePropertyStore::end() const {
//   STL_VECTOR( MCParticleProperty* )::const_iterator realEnd;
   STL_VECTOR( MCParticleProperty* )::const_iterator endItr = m_ppList.end();
//   STL_VECTOR( MCParticleProperty* )::const_iterator bgnItr = m_ppList.begin();
//   for( STL_VECTOR( MCParticleProperty* )::const_iterator prop = endItr; 
//	prop != bgnItr, (*(prop-1)) != 0; 
//	--prop ) {
//      realEnd = prop;
//   }
   return MCPPStoreItr( endItr, endItr );
}

DABoolean
MCParticlePropertyStore::propertyExists( 
   QQ_id idToCheck ) const
{
   // offset the ID to map QQ id's to s non-negative set
   QQ_id offsetIdToCheck = idToCheck + kQQidOffset;

   // if there is a pointer, the id exists
   if ( offsetIdToCheck >=0 && offsetIdToCheck < m_ppList.size() )
   {
      return m_ppList[offsetIdToCheck] != 0;
   }
   else
   {
      return false;
   }
}

const MCParticleProperty&
MCParticlePropertyStore::getUsingQQId( QQ_id QQid ) const
{
   // offset the ID to map QQ id's to s non-negative set
   QQ_id offsetId = QQid + kQQidOffset;

   MCParticleProperty* idPointer = 0;

   if ( offsetId >=0 && offsetId < m_ppList.size() )
   {
      idPointer = m_ppList[offsetId];
   }

   // issue warning and abort if there is no object
   if ( idPointer == 0 )
   {
      report( WARNING, kFacilityString ) << '\n' << kLineOffset
	 << "No particle with the requested QQ ID " << QQid
	 << "exists in the store." << '\n'  << kLineOffset
	 << "(The problem may also have originiated with an invalid "
	 << "GEANT ID)" << endl;
      assert( false );
      exit(1);
   }

   return *idPointer;
}

const MCParticleProperty&
MCParticlePropertyStore::getUsingName( const string& name ) const
{
   // Does this name exist?
   STL_MAP(string, QQ_id)::iterator itName = m_nameToQQ.find( name );
   if ( itName == m_nameToQQ.end() )
   {
      report( WARNING, kFacilityString )
	 << "No particle with the requested name '" << name
	 << "' exists in the store" << endl;
      assert( false );
      exit(1);
   }

   // get the qq id
   QQ_id theQQid = (*itName).second;
   
   // return the pointer to the object
   return getUsingQQId( theQQid );
}

const MCParticleProperty&
MCParticlePropertyStore::getUsingPDGId( PDG_id PDGId ) const
{
   if ( m_pdgToQQ.find( PDGId ) == m_pdgToQQ.end() )
   {
      report( WARNING, kFacilityString )
	 << "No particle with PDG ID " << PDGId
	 << " exists in the store" << endl;
      assert( false );
      exit(1);
   }

   // get the qq id
   QQ_id theQQid = m_pdgToQQ[PDGId];
   
   // return the pointer to the object
   return getUsingQQId( theQQid );
}

const MCParticleProperty&
MCParticlePropertyStore::getUsingGeantId( Geant_id GeantId ) const
{
   // Does this GEANT id  exist?
   if ( GeantId < 0 || GeantId >= m_geantToQQ.size() )
   {
      report( WARNING, kFacilityString )
	 << "No particle with GEANT ID " << GeantId
	 << " exists in the store" << endl;
      assert( false );
      exit(1);
   }

   // get the qq id
   QQ_id theQQid = m_geantToQQ[GeantId];
   
   // return the pointer to the object
   return getUsingQQId( theQQid );
}

void MCParticlePropertyStore::addSpecialParticles() {

   // add an "e+e-" particle that can live on the top of the tree
   // offset the ID to map QQ id's to s non-negative set
   QQ_id offsetId = kQQIdEpem + kQQidOffset;
   if ( m_ppList[offsetId] == 0 ) {
      MCParticleProperty epemProperty;
      string epemName( "e+e-" );
      epemProperty.setName( epemName );
      epemProperty.setQQId( kQQIdEpem );
      epemProperty.setPDGId( kPDGIdEpem );
      epemProperty.setStableId( -1 );
      epemProperty.setWidth(   20. );
      epemProperty.setMaxMass( 20. );
      epemProperty.setSpin( 1 );
      addProperty( epemProperty );
   }
}
      
void MCParticlePropertyStore::handleQQKluges() {

   // 1) make the PSI->l+l- decays nondeterministic, since they can
   //    be radiative decays

   // -- load up vectors with the list of daughters for the l+l- decay modes
   STL_VECTOR( string ) eNames;
   STL_VECTOR( string ) muNames;
   eNames.push_back( "E+" );
   eNames.push_back( "E-" );
   muNames.push_back( "MU+" );
   muNames.push_back( "MU-" );

   //  limit scope of the  local variables...
   {
      // -- get the PSI property and modify the modes.  Only attempt this
      // if it exists in the first place!
      QQ_id checkForPsiId = nameToQQId( "PSI" );
      if ( checkForPsiId != MCParticleProperty::kUnknownQQId ) {
	 MCParticleProperty psiProp( this->getUsingName("PSI") );
	 MCParticleProperty::iterator lastMode = psiProp.end();
	 for( MCParticleProperty::iterator modeIter = psiProp.begin(); 
	      modeIter != lastMode; ++modeIter ) {
	    if ( (*modeIter).isMode( "PSI", eNames ) ||
		 (*modeIter).isMode( "PSI", muNames ) ) {
	       modeIter->setDeterministic( false );
	    }
	 }  // loop over props
	 this->replaceProperty( psiProp );
      } // particle prop is known, since it has an id
   }

   {
      // -- get the PSI property and modify the modes.  Only attempt this
      // if it exists in the first place!
      QQ_id checkForPsiId = nameToQQId( "PSI2" );
      if ( checkForPsiId != MCParticleProperty::kUnknownQQId ) {
	 MCParticleProperty psi2Prop( this->getUsingName("PSI2") );
	 MCParticleProperty::iterator lastMode = psi2Prop.end();
	 for( MCParticleProperty::iterator modeIter = psi2Prop.begin();
	      modeIter != lastMode; ++modeIter ) {
	    if ( (*modeIter).isMode( "PSI2", eNames ) ||
		 (*modeIter).isMode( "PSI2", muNames ) ) {
	       modeIter->setDeterministic( false );
	    }
	 }  // loop over props
	 this->replaceProperty( psi2Prop );
      } // particle prop is known, since it has an id
   }

}
//
// private member functions
//
void MCParticlePropertyStore::killAllPropertyObjects()
{
   // Delete the non-quark/gluon particles (non-negative QQ ID's)
   PPListItr ppListEnd = m_ppList.end();
   for ( PPListItr itProp = m_ppList.begin(); 
	 itProp != ppListEnd; 
	 ++itProp )
   {
      if ( *itProp != 0 ) delete *itProp;
   }
}    

void 
MCParticlePropertyStore::copyAllPropertyObjects( 
   const MCParticlePropertyStore& rhs )
{
   // iterate over the ppList in rhs, creating the particle property objects
   //  in *this as we go
   
   PPListItr ppListEnd = rhs.m_ppList.end();
   for ( PPListItr itProp = rhs.m_ppList.begin(); 
	 itProp != ppListEnd; 
	 ++itProp )
   {
      if ( *itProp != 0 ) addProperty( **itProp );
   }
}

Integer MCParticlePropertyStore::version() const
{
   return m_storeVersion;
}

void MCParticlePropertyStore::setVersion( Integer theVersion )
{
   m_storeVersion = theVersion;
}

QQ_id
MCParticlePropertyStore::nameToQQId( const string& theName ) const
{
   // initialize the return value to UNKNOWN in case the name does not exist
   QQ_id theQQId = MCParticleProperty::kUnknownQQId;

   // check for this name, and grab the QQ id if we find it
   NameListItr namePosition = m_nameToQQ.find( theName );
   if ( namePosition != m_nameToQQ.end() )
   {
      theQQId = (*namePosition).second;
   }

   return theQQId;
}

QQ_id
MCParticlePropertyStore::pdgIdToQQId( PDG_id pId ) const
{
   // initialize the return value to UNKNOWN in case the name does not exist
   QQ_id theQQId = MCParticleProperty::kUnknownQQId;

   // check for this name, and grab the QQ id if we find it
   PDGListItr pdgPosition = m_pdgToQQ.find( pId );
   if ( pdgPosition != m_pdgToQQ.end() )
   {
      theQQId = (*pdgPosition).second;
   }

   return theQQId;
}

QQ_id
MCParticlePropertyStore::geantIdToQQId( Geant_id gId ) const
{
   // initialize the return value to UNKNOWN in case the name does not exist
   QQ_id theQQId = MCParticleProperty::kUnknownQQId;

   // check for this name, and grab the QQ id if we find it
   if ( gId >= 0 && gId < m_geantToQQ.size() ) {
      theQQId = m_geantToQQ[gId];
   }

   return theQQId;
}

const string& 
MCParticlePropertyStore::qqIdToName( QQ_id anId ) const {
   QQ_id offsetQQid = anId + kQQidOffset;
   return m_qqToName[offsetQQid];
}

PDG_id 
MCParticlePropertyStore::qqIdToPDGId( QQ_id anId ) const {
   QQ_id offsetQQid = anId + kQQidOffset;
   return m_qqToPDG[offsetQQid];
}

QQ_id
MCParticlePropertyStore::conjugateQQ( QQ_id id ) const {
   return pdgIdToQQId(conjugatePDG( qqIdToPDGId(id) ));
}

//
// static member functions
//
PDG_id
MCParticlePropertyStore::conjugatePDG( PDG_id id ) {

// Algorithm assumes that PDG numbering scheme of 1998 is in place
   int absId = (id < 0) ? -id : id;
   int modId = absId % 9900000;

   // 1) handle KL and KS special cases
   if ( modId == 310 || modId == 130 ) { return id; }

   // 2) handle mesons that are their own antiparticles
   int n_q3 = (absId /   10) % 10;
   int n_q2 = (absId /  100) % 10;
   int n_q1 = (absId / 1000) % 10;
   if ( n_q3 == n_q2 && n_q1 == 0 ) { return id; }

   // 3) everything else
   return -id;
}

DABoolean
MCParticlePropertyStore::operator==(const MCParticlePropertyStore& rhs) const {
   DABoolean identical = 
      (version() == rhs.version()) &&
      (m_ppList.size() == rhs.m_ppList.size()) &&
      equal( begin(), end(), rhs.begin() );
   return identical;
}
//
// friend functions
//

// default output operator for the particle property object
ostream& operator<<(ostream& theStream, 
		    const MCParticlePropertyStore& theStore)
{
   // list the store's version number
   theStream << "Store Version: " << theStore.m_storeVersion << '\n';

   // iterate over the particles, having each output its short summary
   PPListItr ppListEnd = theStore.m_ppList.end();
   for ( PPListItr itProp = theStore.m_ppList.begin(); 
	 itProp != ppListEnd; 
	 ++itProp )
   {
      if ( *itProp != 0 ) theStream << **itProp << '\n';
   }

   return theStream;
}

