#if !defined(PACKAGE_BUILDGEANTGEOMETRY_H)
#define PACKAGE_BUILDGEANTGEOMETRY_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      BuildGeantGeometry
// 
// Description: Class to create the Geant Geometry description
//              used by cleog by extracting the Detector geometry
//              (DGDetectorStore) store + extra Geant specific description
//              of the volumes (G3iExtraVolSpecsStore).  
// Usage:
//    <usage>
//
// Author:      John J O'Neill
// Created:     Fri Mar 12 13:21:52 EST 1999
// $Id: BuildGeantGeometry.h,v 1.3 2001/04/14 06:08:22 mahlke Exp $
//
// Revision history
//
// $Log: BuildGeantGeometry.h,v $
// Revision 1.3  2001/04/14 06:08:22  mahlke
// changed handover of doXXGeom flags to BuildGeantGeometry; now using a class
//
// Revision 1.2  2001/04/09 14:24:28  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.1  1999/05/03 20:21:31  jjo
// Reorganize code to make running Cleog under Suez more robust
//

// system include files

// user include files

// forward declarations
class Frame;

class BuildGeantGeometry
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      class UseComponent
      {
         public:
         UseComponent():m_doSVGeom(true),
                        m_doDRGeom(true),
                        m_doRichGeom(true),
                        m_doCCGeom(true),
                        m_doMUGeom(true){}
         UseComponent(DABoolean iDoSVGeom, 
                      DABoolean iDoDRGeom, 
                      DABoolean iDoRichGeom,
                      DABoolean iDoCCGeom, 
                      DABoolean iDoMUGeom ):m_doSVGeom(iDoSVGeom),
                                            m_doDRGeom(iDoDRGeom),
                                            m_doCCGeom(iDoCCGeom),
                                            m_doRichGeom(iDoRichGeom),
                                            m_doMUGeom(iDoMUGeom){} 
           DABoolean doSVGeom() const { return m_doSVGeom;}
           DABoolean doDRGeom() const { return m_doDRGeom;}
           DABoolean doRichGeom() const { return m_doRichGeom;}
           DABoolean doCCGeom() const { return m_doCCGeom;}
           DABoolean doMUGeom() const { return m_doMUGeom;}
         private: 
           DABoolean m_doSVGeom;
           DABoolean m_doDRGeom;
           DABoolean m_doRichGeom;
           DABoolean m_doCCGeom;
           DABoolean m_doMUGeom;
      };

      // ---------- Constructors and destructor ----------------
      BuildGeantGeometry();
      virtual ~BuildGeantGeometry();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static void create ( const Frame& iFrame, const UseComponent& iUseComponent=UseComponent() );
			 

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      BuildGeantGeometry( const BuildGeantGeometry& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const BuildGeantGeometry& operator=( const BuildGeantGeometry& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/BuildGeantGeometry.cc"
//#endif

#endif /* PACKAGE_BUILDGEANTGEOMETRY_H */
