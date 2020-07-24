// -*- C++ -*-
//
// Package:     Trkman
// Module:      TMCurlers
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Wed Feb 13 12:43:45 EST 2002
// $Id: TMCurlers_Groups.cc,v 1.1 2002/11/04 18:31:32 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlers_Groups.cc,v $
// Revision 1.1  2002/11/04 18:31:32  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"
#include <vector>
#include "Trkman/TMCurlers.h"
#include "Experiment/report.h"
#include "Navigation/NavTrack.h"
#include "MagField/MagneticField.h"
#include "Cleo/cleo_math.h"


//
// constants, enums and typedefs
//
static const double kPi = 3.1415926535898;
static const char* const kFacilityString = "Trkman.TMCurlerGroups" ;

//
// member functions
//
//Take the curler pairs and merge them into larger groups 
//if required
void TMCurlers::makeCurlerGroups()
{
   CurlerGroup curlerList;
   curlerList.reserve(10);
   for( int k=0; k< m_numCurlerPairs; k++ ) m_pairMatched.push_back( false );

   int seedPair = 0;
   DABoolean stillUnmatchedPairs = true;
   while( stillUnmatchedPairs )
   {
      //Start the new list with the next unmatched curler pair
      curlerList.push_back( m_curlerPairs[seedPair].first );
      curlerList.push_back( m_curlerPairs[seedPair].second );
      
      m_pairMatched[seedPair] = true;

      makeCurlerList( m_curlerPairs, m_pairMatched, curlerList );

      m_curlerGroups.push_back( curlerList );
      curlerList.clear();

      stillUnmatchedPairs = false;
      for( int i=0; i<m_numCurlerPairs; i++ )
      {
	 if( !m_pairMatched[i] )
	 {
	    seedPair = i;
	    stillUnmatchedPairs = true;
	 } 
      }

   }

   m_numCurlerGroups = m_curlerGroups.size();
}


void TMCurlers::makeCurlerList( CPairVector pairList, TruthVector& matched, CurlerGroup& list )
{
   int count = 1;
   int newCurler;
   DABoolean moreCurlersInList = true;
   while( moreCurlersInList )
   {
      for( int i=0; i<pairList.size(); i++ )
      {
	 if( !matched[i] )
	 {
	    DABoolean addNewCurler = false;
	    if( list[count-1] == pairList[i].first )
	    {
	       matched[i] = true;
	       addNewCurler = true;
	       newCurler = pairList[i].second;
	    }
	    else if( list[count-1] == pairList[i].second )
	    {
	       matched[i] = true;
	       addNewCurler = true;
	       newCurler = pairList[i].first;
	    }
	    
	    //If there is a new track loop over the current list 
	    //to make sure the it's not already there.
	    if( addNewCurler )
	    {
	       if( matched[i] )
	       {
		  for( int j=0; j<list.size(); j++ )
		  {
		     if( newCurler == list[j] )
		     {
			addNewCurler = false;
			j = list.size();
			}
		  }
		  if( addNewCurler ) list.push_back( newCurler );
	       }
	    }
	 }
      }
      
      count++;
      if( count > list.size() ) moreCurlersInList = false;
      
   }
}

void TMCurlers::computePhiAvg()
{
   //Zero the phiAvg vector to start with.
   m_phiAvg.clear();
   for( int gr = 0; gr<m_numCurlerGroups; gr++ ) m_phiAvg.push_back(0.0);

   for( int i=0; i<m_numCurlerGroups; i++ )
   {
      CurlerGroup cg = m_curlerGroups[i];
      for( int j=0; j<cg.size(); j++ )
      {
	 int track = cg[j];
	 if( m_phiAvg[i] > 0 && m_phiAvg[i] < kPi )
	 {
	    if( (m_data->phiEnd(track-1) > -kPi) && (m_data->phiEnd(track-1) < (m_phiAvg[i]-kPi)) )
	    {
	       m_phiAvg[i] = j*m_phiAvg[i] + m_data->phiEnd(track-1) + 2*kPi;
	       m_phiAvg[i] = m_phiAvg[i]/((double)j + 1);
	       if( m_phiAvg[i] > kPi ) m_phiAvg[i] -= 2*kPi;
	    }
	    else
	    {
	       m_phiAvg[i] = j*m_phiAvg[i] + m_data->phiEnd(track-1);
	       m_phiAvg[i] = m_phiAvg[i]/((double)j + 1);
	    }
	 }
	 else
	 {
	    if( (m_data->phiEnd(track-1) < kPi) && (m_data->phiEnd(track-1) > (m_phiAvg[i]+kPi)) )
	    {
	       m_phiAvg[i] = j*m_phiAvg[i] + m_data->phiEnd(track-1) - 2*kPi;
	       m_phiAvg[i] = m_phiAvg[i]/((double)j + 1);
	       if( m_phiAvg[i] > kPi ) m_phiAvg[i] += 2*kPi;
	    }
	    else
	    {
	       m_phiAvg[i] = j*m_phiAvg[i] + m_data->phiEnd(track-1);
	       m_phiAvg[i] = m_phiAvg[i]/((double)j + 1);
	    }
	 }
      }
      cg.clear();
   }
}

void TMCurlers::mergeGroups( )
{

   //Set the merged groups array to false
   m_groupMerged.clear();
   for( int gr=0; gr<m_numCurlerGroups; gr++ ) m_groupMerged.push_back( false );


   //Outer loop: the i Groups
   for( int iG=0; iG<m_numCurlerGroups-1; iG++ )
   {
      double riGmin = 1.0;
      double riGmax = 0;

      //Find the maximum and minimium diametrical radii 
      //for the i group.
      for( int iT=0; iT<m_curlerGroups[iG].size(); iT++ )
      {
	 CurlerGroup cg = m_curlerGroups[iG];
	 double radius = m_data->rcImpact( cg[iT]-1 );
	 if( radius > riGmax ) riGmax = radius;
	 if( radius < riGmin ) riGmin = radius;
	 cg.clear();
      }

      //Inner loop: the j Groups
      for( int jG=iG+1; jG<m_numCurlerGroups; jG++ )
      {
	 double delRadii;
	 double delPhiAvg = 0;
	 double rjGmax = 0;
	 double rjGmin = 1.1;

	 //Find the maximum and minimium diametrical radii 
	 //for the j group.
	 for( int jT=0; jT<m_curlerGroups[jG].size(); jT++ )
	 {
	    CurlerGroup cg = m_curlerGroups[jG];
	    double radius = m_data->rcImpact( cg[jT]-1 );
	    if( radius > rjGmax ) rjGmax = radius;
	    if( radius < rjGmin ) rjGmin = radius;
	    cg.clear();
	 }

	 //Calculate the radial difference of the two grps
	 if( riGmax > rjGmax ) delRadii = riGmin - rjGmax;
	 else                  delRadii = rjGmin - riGmax;
 
	 //Calculate the azimuthal angle difference of the 
	 //groups
	 if( (m_phiAvg[jG] < 0) && (m_phiAvg[iG] > 0) )
	 {
	    delPhiAvg = m_phiAvg[iG] - m_phiAvg[jG];
	    if( delPhiAvg > kPi ) delPhiAvg = 2*kPi - delPhiAvg;
	 }
	 else if( (m_phiAvg[jG] > 0) && (m_phiAvg[iG] < 0) )
	 {
	    delPhiAvg = m_phiAvg[jG] - m_phiAvg[iG];
	    if( delPhiAvg > kPi ) delPhiAvg = 2*kPi - delPhiAvg;
	 }
	 else
	 {
	    delPhiAvg = fabs( m_phiAvg[jG] - m_phiAvg[iG] );
	 }

	 //If these groups meet the requirements add them
	 //to the group pairs list
	 if( delPhiAvg < 0.21 && ( (delRadii > 0.06) && (delRadii < 0.3 )) )
	 {
	    m_grpPairList.push_back( CPair( iG, jG ) );
	    m_groupMerged[iG] = true;
	    m_groupMerged[jG] = true;
	 }

      }
   }

   //Have now made the grpPairList
   if( m_grpPairList.size() > 0 )
   {
      TruthVector grpPairMerged;
      grpPairMerged.clear();
      for( int gp=0; gp<m_grpPairList.size(); gp++ ) grpPairMerged.push_back( false );
      
      //Make a temp curler group vector
      CurlerGroup groupsList;
      groupsList.reserve( m_numCurlerGroups );

      CurlerGroupVector groupsListVec;
      groupsListVec.reserve( m_numCurlerGroups );

      int seedPair = 0;
      DABoolean stillUnmatchedPairs = true;
      while( stillUnmatchedPairs )
      {

	 //Start the new list with the next unmatched curler pair
	 groupsList.push_back( m_grpPairList[seedPair].first );
	 groupsList.push_back( m_grpPairList[seedPair].second );
	 
	 grpPairMerged[seedPair] = true;
	 
	 makeCurlerList( m_grpPairList, grpPairMerged, groupsList );

	 groupsListVec.push_back( groupsList );
	 groupsList.clear();

	 stillUnmatchedPairs = false;
	 for( int i=0; i<m_grpPairList.size(); i++ )
	 {
	    if( !grpPairMerged[i] )
	    {
	       seedPair = i;
	       stillUnmatchedPairs = true;
	    } 
	 }

      }

      //Now sort the merged groups and remake the curlerGroups vector
      CurlerGroupVector tmp;
      tmp.reserve( m_numCurlerGroups );
      
      CurlerGroup curlerList;
      curlerList.reserve( 10 );

      for( int i=0; i<groupsListVec.size(); i++ )
      {
	 CurlerGroup grpList = groupsListVec[i];
	 for( int j=0; j<grpList.size(); j++ )
	 {
	    CurlerGroup list = m_curlerGroups[ grpList[j] ];
	    for( int k=0; k<list.size(); k++ )
	    {
	       curlerList.push_back( list[k] );
	    }
	 }
	 tmp.push_back( curlerList );
	 curlerList.clear();
      }

      //First add any groups that were not merged
      for( int l=0; l<m_numCurlerGroups; l++ )
      {
	 if( !m_groupMerged[l] ) tmp.push_back( m_curlerGroups[l] ); 
      }

     //Now clear the curlerGroup vector and set it to the value of tmp
      m_curlerGroups.clear();
      m_curlerGroups = tmp;
      m_numCurlerGroups = m_curlerGroups.size();

      grpPairMerged.clear();
      tmp.clear();

   }

}


//
// const member functions
//


int TMCurlers::numCurlerGroups() const
{
   return m_numCurlerGroups;
}

TMCurlers::CurlerGroup TMCurlers::curlerGroup( int i ) const
{
   if( i < m_curlerGroups.size() )
   {
      return m_curlerGroups[i];
   }
   else
   {
      report( WARNING, kFacilityString ) << "Invalid curler group number in getCurlerGroup()!!" << endl;
      CurlerGroup retGroup(1,0);
      return retGroup;
   }
}

TMCurlers::CurlerGroupVector TMCurlers::curlerGroupVector() const
{
   return m_curlerGroups;
}

double TMCurlers::phiAverage( int i ) const
{
   if( i < m_curlerGroups.size() && i >= 0  )
   {
      return m_phiAvg[i];
   }
   else
   {
      report( ERROR, kFacilityString ) << "Cannot get phi average "
				       << " for index value i = " << i << endl;
      return 0;
   }
}


//
// static member functions
//
















