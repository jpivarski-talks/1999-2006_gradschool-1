#if !defined(MCINFO_MCPARTICLE_H)
#define MCINFO_MCPARTICLE_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCParticle
// 
// Description: Particle class: - Helicity information (simple QQ model)
//                              - 4 momentum info based on KinematicData
//                              - acts as a container of interaction vertices
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sun Jan 10 14:57:17 EST 1999
// $Id: MCParticle.h,v 1.8 2003/02/03 20:24:50 bkh Exp $
//
// Revision history
//
// $Log: MCParticle.h,v $
// Revision 1.8  2003/02/03 20:24:50  bkh
// Add new unwinding function
//
// Revision 1.7  2002/05/03 18:59:02  lkg
// add routine to translate the coordinate system
//
// Revision 1.6  2000/10/06 18:25:07  bkh
// Add constructor with MCParticleProperty and KTKinematicData
//
// Revision 1.5  2000/10/04 21:21:37  bkh
// Add default constructor, assignment operator
//
// Revision 1.4  2000/05/01 22:50:45  lkg
// StorageHelper-related changes: added valueType arg for MCListItr typedefs and == and != operators
//
// Revision 1.3  1999/10/19 21:46:53  lkg
// * Add static dumpHeader() member fcn, which will print out column headings
//   for output created by the << operator (which invokes the dump function)
// * fix the dead() member fcn, which returned true when particle was alive, etc.
//
// Revision 1.2  1999/07/06 21:35:47  lkg
// Add reverse_iterator and const_reverse_iterator and associated rbegin/rend
// functions.  Eliminate the lengthy names (vertexIterator) -- just too much
//
// Revision 1.1  1999/06/22 21:30:01  lkg
// First real version of MCInfo in repository
//

// system include files
#include <vector>

// user include files
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCDecayTree/MCTreeNode.h"
#include "MCInfo/MCDecayTree/MCListItr.h"
#include "KinematicTrajectory/KTKinematicData.h"
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"

// forward declarations
#include "C++Std/fwd_ostream.h"
#include "STLUtility/fwd_vector.h"
class MCVertex;
class MCParticleProperty;


class MCParticle : public KTKinematicData, public MCTreeNode
{
// ---------- friend classes and functions ---------------
      friend ostream& operator<<(ostream& aStream,
				 const MCParticle& aParticle);

      friend class MCVertex;

   public:
      // ---------- constants, enums and typedefs --------------
      typedef STL_VECTOR( MCVertex* )     vList;

      //
      // ------- define the various iterator classes -------
      //
      typedef MCListItr< vList::iterator, MCVertex, MCVertex >                 vIterator;
      typedef MCListItr< vList::reverse_iterator, MCVertex, MCVertex > reverse_vIterator;
      typedef MCListItr< vList::const_iterator, const MCVertex, MCVertex > 
                                                             const_vIterator;
      typedef MCListItr< vList::const_reverse_iterator, const MCVertex, MCVertex > 
                                                       const_reverse_vIterator;
      // --- synonyms for iterators and list
      typedef         const_vIterator         const_iterator; // STL-like
      typedef const_reverse_vIterator const_reverse_iterator; // STL-like
      typedef               vIterator               iterator; // STL-like
      typedef       reverse_vIterator       reverse_iterator; // STL-like

      // ---------- Constructors and destructor ----------------

      // All particles must have a type. Default 4 Momentum will be 0.
      // If the particle is a resonance, the mass for this instance of
      // the particle must be specified if its four momentum is not 
      // specified.  Either the production point or the production vertex
      // can be specified.  If neither is specified, the particle's origin
      // is constructed at the origin.
      MCParticle( const MCParticleProperty& particleType,
		  const HepLorentzVector&   the4Momentum = HepLorentzVector(),
		  const HepPoint3D&         productionPnt = HepPoint3D() );

      MCParticle( const MCParticleProperty& particleType,
		  const KTKinematicData&    kinDat        );

      MCParticle( const MCParticleProperty& particleType,
		        MCVertex*           productionVertex,
		  const HepLorentzVector&   the4Momentum = HepLorentzVector());

      MCParticle( const MCParticleProperty& particleType, 
  		        Double              resonantMass,
		  const HepPoint3D&         productionPnt = HepPoint3D() );
      
      MCParticle( const MCParticleProperty& particleType, 
  		        Double              resonantMass,
		        MCVertex*           productionVertex );
      
      // copy constructor, production vertex optional
      MCParticle( const MCParticle& rhsPart, MCVertex* prodVertex = 0 ); 

      MCParticle();

      // ---------- assignment operator(s) ---------------------
      const MCParticle& operator=( const MCParticle& rhs );

      virtual ~MCParticle();
      
      // ---------- const member functions ---------------------
      
      // see KTKinematicData.h for 4-momentum information

      // helicity of particle
      Helicity helicity() const;

      // "decay" vertex access (more generally, vertex at which particle
      // is lost) handled specially, since it is generally of most interest
      // a null pointer is returned for particles w/o a "decay" vertex
      const MCVertex* deathVertex() const;

      //
      // Vertex container: const access
      //

      // The number of interaction/decay vertices for this particle
      Count nVertices()  const;
      Count size()      const; // standard container synonym for nVertices
      Count empty()     const; // related standard container function

      // for iteration over all interaction vertices, including the
      // "decay" vertex.  Three synonyms for each
      const_vIterator          vBegin() const;
      const_iterator            begin() const; // standard container name
      const_reverse_vIterator rvBegin() const;
      const_reverse_iterator   rbegin() const; // standard container name

      const_vIterator          vEnd()   const;
      const_iterator            end()   const; // standard container name
      const_reverse_vIterator rvEnd()   const;
      const_reverse_iterator   rend()   const; // standard container name
      
      //
      // Parameters related to this Particle.  See KinematicData for
      // access to four momentum, mass of this instance (if resonance)
      // of this particle, etc.
      //

      // production vertex
      const MCVertex* productionVertex() const;

      // full blown Particle Property
      const MCParticleProperty& properties() const;

      // Query particle if it is dead yet, ie., it has decayed,
      // suffered a fatal interaction, ranged out, etc., etc.
      DABoolean dead() const { return (m_deathVertex != 0); };

      DABoolean operator==( const MCParticle& rhs ) const;
      DABoolean operator!=( const MCParticle& rhs ) const;

      // ---------- virtual const member functions -------------

      // A virtual CLONE functions for copying
      // derived classes with the user manipulating only the base
      // class.  Classes that inherit from this base class
      // should provide implementations of these functions so that
      // the base class only is not accidentally sliced out.  The
      // implementations MUST get done as deep clones.

      virtual MCParticle* clone( MCVertex* newProdVertex = 0 ) const;

      // A virtual DUMP function allows derived classes to override
      // or augment the output provided via the "<<" operator.
      virtual ostream& dump( ostream& ) const;

      // go up decay tree from this particle 
      // until find a particle which is inside
      // a given cylininder defined by a fabs(radius) and fabs(z).
      // negative values of either radius or z (default) means go back to
      // a particle produced directly in the e+e- interaction
      // Result may be this particle, or 0.
      const MCParticle* unwindToInsideRZ( const double aRadius = -1 ,
					  const double aZ      = -1  ) const ;

      // ---------- member functions ---------------------------

      // set this particle's helicity
      void setHelicity( Helicity newHelicity );

      // iterate over all vertices: intermediate vertices for which the
      // particle retains identity, and final vertex in which it dies,
      // ranges out, etc.
      
      vIterator           vBegin();
      iterator             begin(); // standard container name
      reverse_vIterator  rvBegin();
      reverse_iterator    rbegin(); // standard container name

      vIterator           vEnd();
      iterator             end();   // standard container name
      reverse_vIterator  rvEnd();
      reverse_iterator    rend();   // standard container name

      //
      // non-const access to death vertex
      // 
      MCVertex* deathVertex();

      // translate the coordinate system for this particle (and descendents)
      void translateCoordinates( const Hep3Vector& translationVector );
      
      // ---------- static member functions --------------------
      static ostream& dumpHeader( ostream& );
      
   protected:
      // ---------- protected member functions -----------------
      // Creation of a vertex implies a parent particle in this
      // model.  That is, a particle can be created "from nothing",
      // but a vertex is always associated with a parent.  Therefore,
      // the vertex constructor always takes pointer to the parent.
      // The vertex then also INSERTS itself into the parent's decay
      // tree.  Hence, the only object that ever need see the addVertex
      // function is the MCVertex object. So, I've protected it.
      //
      void addVertex(     MCVertex* newInteraction );
      
      // setting the parent vertex seems most natural when attaching this
      // particle to its parent vertex.  Hence, we will let the "add"
      // fcn's in MCVertex look after this
      void setProductionVertex( MCVertex* theProductionVertex );

      // update the MCIdManager for this particle and any tree hanging
      // from it
      void updateManager( MCIdManager& theManager );

      // update the Id of this particle in the tree
      void updateId();

      // Have all the vertices update their ID's childrens ID's
      void updateChildrenIds();


      // ---------- protected const member functions -----------
      
   private:
      // ---------- Constructors and destructor ----------------
      
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------

      // particle property
      const MCParticleProperty* m_particleType;

      // helicity
      Helicity m_helicity;

      // parent Vertex
      const MCVertex* m_pProductionVertex;

      // Interaction vertices, with an extra, direct access pointer
      // to the vertex where the particle disappears (via decay
      // or interaction) or stops being traced by the final
      // detector tracing package
      vList m_vertexList;
      MCVertex* m_deathVertex;
};

// inline const function definitions
inline MCParticle::const_reverse_iterator
MCParticle::rbegin() const { return rvBegin(); };

inline MCParticle::const_reverse_iterator
MCParticle::rend() const { return rvEnd(); };

inline MCParticle::const_iterator
MCParticle::begin() const { return vBegin(); };

inline MCParticle::const_iterator
MCParticle::end() const { return vEnd(); };

inline Count
MCParticle::size() const { return nVertices(); };

// inline non-const function definitions
inline MCParticle::reverse_iterator
MCParticle::rbegin() { return rvBegin(); };

inline MCParticle::reverse_iterator
MCParticle::rend() { return rvEnd(); };

inline MCParticle::iterator
MCParticle::begin() { return vBegin(); };

inline MCParticle::iterator
MCParticle::end() { return vEnd(); };

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCParticle.cc"
//#endif

//
// If the ability to convert from vIterator to const_vIterator is needed,
// replace the first two typedefs at the start of the class definition to
// with the following classes
//
//      class const_vIterator;
//      class vIterator : public MCListItr< vList::iterator, MCVertex >
//      {
//	 friend class MCParticle::const_vIterator;
//	 public: 
//	    typedef MCListItr< vList::iterator, MCVertex > baseItr;
//	    vIterator() : baseItr() {};
//	    vIterator( const vList::iterator& anItr ) : baseItr(anItr) {};
//	    vIterator( const vIterator& rhs ) : baseItr( rhs ) {};
//      };
//
//      class const_vIterator : public MCListItr< vList::const_iterator, const MCVertex >
//      {
//	 public:
//	    typedef MCListItr< vList::const_iterator, const MCVertex > baseItr;
//	    const_vIterator() : baseItr() {};
//	    const_vIterator( const vList::const_iterator& anItr ) : 
//	       baseItr(anItr) {};
//	    const_vIterator( vIterator nonConstItr ) : 
//	       baseItr( nonConstItr.bareIterator() ) {};
//	    const_vIterator( const const_vIterator& rhs ) : baseItr( rhs ) {};
//      };

#endif /* MCINFO_MCPARTICLE_H */

