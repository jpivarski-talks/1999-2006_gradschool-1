#if !defined(TRIGGERINFOPROD_TRIGGERINFO_H)
#define TRIGGERINFOPROD_TRIGGERINFO_H
// -*- C++ -*-
//
// Package:     <TriggerInfoProd>
// Module:      TriggerInfo
// 
/**\class TriggerInfo TriggerInfo.h TriggerInfoProd/TriggerInfo.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:03:55 EDT 2004
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files

// forward declarations

class TriggerInfo
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      TriggerInfo();
      TriggerInfo(int axial, int stereo, int cblo, int cbmd);
      TriggerInfo( const TriggerInfo& );
      virtual ~TriggerInfo();

      // ---------- assignment operator(s) ---------------------
      const TriggerInfo& operator=( const TriggerInfo& );

      DABoolean operator==( const TriggerInfo& ) const;
      DABoolean operator!=( const TriggerInfo& ) const;

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      int axial() const {return m_axial;}
      int stereo() const {return m_stereo;}
      int cblo() const {return m_cblo;}
      int cbmd() const {return m_cbmd;}

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      int m_axial;
      int m_stereo;
      int m_cblo;
      int m_cbmd;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "TriggerInfoProd/Template/TriggerInfo.cc"
//#endif

#endif /* TRIGGERINFOPROD_TRIGGERINFO_H */
