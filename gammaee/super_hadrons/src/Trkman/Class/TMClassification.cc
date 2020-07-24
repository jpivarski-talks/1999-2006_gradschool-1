// -*- C++ -*-
//
// Package:     Trkman
// Module:      TMClassification
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Mon Jul 22 11:03:18 EDT 2002
// $Id: TMClassification.cc,v 1.1 2002/11/04 18:31:27 nea9 Exp $
//
// Revision history
//
// $Log: TMClassification.cc,v $
// Revision 1.1  2002/11/04 18:31:27  nea9
// New CleoIII Trkman
//

// user include files
#include "Trkman/TMClassification.h"

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Trkman.TMClassification" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TMClassification.cc,v 1.1 2002/11/04 18:31:27 nea9 Exp $";
static const char* const kTagString = "$Name:  $";

#define iout report( INFO, kFacilityString )
#define wout report( WARNING, kFacilityString )

//
// constructors and destructor
//
TMClassification::TMClassification( NavTrackTable& theTracks, TMData*& data ) :
   m_data( data ),
   m_theTracks( theTracks )
{
   //Make the track by track classification vector
   //which is what most users require, and what is used
   //in the proxy
   
   //Curlers (inits any non-curler tracks to 0)
   m_curlers = new TMCurlers( theTracks, data );

   m_trackClass = m_curlers->classificationVector();
   m_curlerGroups = m_curlers->curlerGroupVector();

   //Vees
   findVees();

   //Bad Tracks (low density, large d0 etc )
   removeBadTracks();

   //Tails
   removeTails();

   //Track Shower Matching
   m_matched = new DABoolean[ m_theTracks.size() ];
   matchTracksToShowers();

}


TMClassification::~TMClassification()
{
   m_trackClass.clear();
   m_curlerGroups.clear();
   m_veeGroups.clear();

   delete m_curlers;
   delete[] m_matched;
}


//
// const member functions
//

TMClassification::TrackClassification TMClassification::trackClassifications() const
{
   return m_trackClass;
}

DABoolean TMClassification::useTrack( int track ) const
{
   if( track >=0 && track < m_theTracks.size() )
      return m_matched[ track ];
   else
   {
      wout << "Can't return useTracks for track "
	   << track << "!!!" << endl;
      return true;
   }
}


TMClassification::CurlerGroupVector TMClassification::curlerGroupVector() const
{
   return m_curlerGroups;
}


TMClassification::VeeGroupVector TMClassification::veeGroupVector() const
{
   return m_veeGroups;
}


