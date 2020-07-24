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
// Created:     Wed Feb 27 10:42:20 EST 2002
// $Id: TMCurlers_Classification.cc,v 1.1 2002/11/04 18:31:31 nea9 Exp $
//
// Revision history
//
// $Log: TMCurlers_Classification.cc,v $
// Revision 1.1  2002/11/04 18:31:31  nea9
// New CleoIII Trkman
//

#include "Experiment/Experiment.h"
#include "Experiment/fortran_types.h"
#include "ToolBox/TBFortranArrays.h"


#include "Trkman/TMCurlers.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "CLHEP/Matrix/SymMatrix.h"

//
// constants, enums and typedefs
//
static const double kPi = 3.1415926535898;
static const char* const kFacilityString = "Trkman.TMCurlerClassification" ;

#define iout report( INFO, kFacilityString )


//
// static data member definitions
//
int TMCurlers::threeCurlerCellListNormal[486] =
{
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 6, 6, 6, 6,
   2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2,
   6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6,
   6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6,
   2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2,
   6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6,
   6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 4, 4,
   4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 1, 3, 1, 3,
   2, 2, 1, 5, 1, 5, 2, 2, 1, 5, 1, 5, 2, 2, 1, 3, 1, 3, 2, 2,
   1, 5, 1, 5, 2, 2, 1, 5, 1, 5, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4,
   4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 1, 3, 1, 3, 2, 2, 1, 6, 1, 2,
   2, 2, 1, 3, 1, 2, 2, 2, 1, 3, 1, 3, 2, 2, 1, 6, 1, 2, 2, 2,
   1, 3, 1, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2,
   4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 1, 3,
   1, 3, 2, 2, 1, 6, 1, 6, 2, 2, 1, 6, 1, 6, 2, 2, 1, 3, 1, 3,
   2, 2, 1, 6, 1, 6, 2, 2, 1, 6, 1, 6, 2, 2, 4, 4, 4, 4, 2, 2,
   4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 1, 3, 1, 3, 2, 2, 1, 6,
   1, 6, 2, 2, 1, 6, 1, 6, 2, 2, 1, 3, 1, 3, 2, 2, 1, 6, 1, 6,
   2, 2, 1, 6, 1, 6

};

int TMCurlers::fourCurlerCellListNormal[486] =
{
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 1, 6, 1, 6, 2, 2,
   1, 6, 1, 6, 2, 2, 3, 3, 3, 3, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4,
   4, 4, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 2, 2, 1, 6, 1, 6, 2, 2, 1, 6, 1, 6, 2, 2,
   3, 3, 3, 3, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 3, 3,
   3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 1, 3, 1, 3,
   2, 2, 1, 3, 1, 3, 2, 2, 3, 3, 3, 3, 2, 2, 4, 4, 4, 4, 2, 2,
   4, 4, 4, 4, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 1, 3, 1, 3, 2, 2, 1, 3, 1, 3,
   2, 2, 3, 3, 3, 3, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2,
   3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
   5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 1, 6,
   1, 6, 2, 2, 1, 6, 1, 6, 2, 2, 3, 3, 3, 3, 2, 2, 4, 4, 4, 4,
   2, 2, 4, 4, 4, 4, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 1, 6, 1, 6, 2, 2, 1, 6,
   1, 6, 2, 2, 3, 3, 3, 3, 2, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4,
   2, 2, 3, 3, 3, 3

};


double TMCurlers::cosTL[6] = 
{
   0.814, 0.818, 0.746, 0.534, 0.836, 0.816
};

double TMCurlers::d0L[4] =
{
   0.721, 0.642, 0.743, 0.8
};

double TMCurlers::thErrL[4] = 
{
   0.781, 0.765, 0.748, 0.64 
};

double TMCurlers::z0L[4] =
{
   0.81, 0.753, 0.697, 0.94
};

double TMCurlers::zErrL[4] = 
{
   0.759, 0.772, 0.674, 0.692
};

double TMCurlers::zHitL[7] = 
{
   0.482, 0.391, 0.617, 0.788,
   0.709, 0.837, 0.434
};

double TMCurlers::rcProb[25] =
{
   0.382, 0.259, 0.215, 0.126, 0.0171,
   0.0,   0.0,   0.0,   0.0,   0.0,
   0.0,   0.0,   0.0,   0.0,   0.0,
   0.0,   0.0,   0.0,   0.0,   0.0,
   0.0,   0.0,   0.0,   0.0,   0.0
};

double TMCurlers::dbProb[25] =
{
   0.184,   0.294, 0.317, 0.191, 0.0102,
   0.00340, 0.0,   0.0,   0.0,   0.0,
   0.0,     0.0,   0.0,   0.0,   0.0,
   0.0,     0.0,   0.0,   0.0,   0.0,
   0.0,     0.0,   0.0,   0.0,   0.0
};

double TMCurlers::zHProb[25] =
{
   0.485, 0.232, 0.171, 0.109, 0.0034,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0
};

double TMCurlers::denProb[25] =
{
   0.446, 0.228, 0.141, 0.174,  0.011,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0
};

double TMCurlers::svrHProb[25] =
{
   0.604, 0.198, 0.167, 0.0239, 0.0068,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0,
   0.0,   0.0,   0.0,   0.0,    0.0
};



//
// member functions
//
void TMCurlers::classifyTwoCurlerGroup( int i )
{
   //Set up the variables that are needed for the classification
   
   //The two tracks in the group
   int track1 = m_curlerGroups[i][0];
   int track2 = m_curlerGroups[i][1];

   double z0Abs1 = fabs( m_data->z0( track1-1 ) );
   double z0Abs2 = fabs( m_data->z0( track2-1 ) );

   double d0Abs1 = fabs( m_data->d0( track1-1 ) );
   double d0Abs2 = fabs( m_data->d0( track2-1 ) );

   double den1 = m_data->densityOfHits( track1-1 );
   double den2 = m_data->densityOfHits( track2-1 );

   double zAngle = 0;
   if( m_data->cotTheta( track1-1 ) != 0 )
      zAngle = atan( 1/m_data->cotTheta( track1-1 ) );
   else
      zAngle = kPi/2;
   if( zAngle < 0 )
   {
      zAngle += kPi;
   }
//    report( INFO, kFacilityString ) << "zAngle1 " << zAngle << endl;   
   double cosTheta1 = cos( zAngle );

   zAngle = 0;
   if( m_data->cotTheta( track2-1 ) != 0 )
      zAngle = atan( 1/m_data->cotTheta( track2-1 ) );
   else
      zAngle = kPi/2;
   if( zAngle < 0 )
   {
      zAngle += kPi;
   }
//    report( INFO, kFacilityString ) << "zAngle2 " << zAngle << endl;   
   double cosTheta2 = cos( zAngle );

//    report( INFO, kFacilityString ) << "cosTheta1 " << cosTheta1 << " cosTheta2 " << cosTheta2 << endl;

   //Need to get the tracks to see the SVHits
   FAItem< NavTrack > nTrack1 = m_theTracks.find( track1 );
   FAItem< NavTrack > nTrack2 = m_theTracks.find( track2 );

   //Find the no. of hits in each section required, use a pion fit.
   FAItem< TRTrackFitQuality > tQual1 = nTrack1->pionQuality();
   FAItem< TRTrackFitQuality > tQual2 = nTrack2->pionQuality();

   //Ratio of hits to expected
   double rHE1;
   if( tQual1->numberHitsExpected() != 0 )
     rHE1 = tQual1->ratioNumberHitsToExpected();
   else 
     rHE1 = 0;
   double rHE2; 
   if( tQual2->numberHitsExpected() != 0 )
     rHE2 = tQual2->ratioNumberHitsToExpected();
   else
     rHE2 = 0;


   //No. of stereo + cathode + svz hits
   unsigned int zHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
                       + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
                       + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );
   unsigned int zHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
                       + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
                       + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );

   unsigned int svrHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );
   unsigned int svrHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );

   //The maximum d0
   double d0Max = max( d0Abs1, d0Abs2 );
   double z0Max = max( z0Abs1, z0Abs2 );


   //Do the tracks have good z information? Use the error from the helix matrix
   const HepSymMatrix& eMatrix1 = nTrack1->pionHelix()->errorMatrix();
   const HepSymMatrix& eMatrix2 = nTrack2->pionHelix()->errorMatrix();

   double sigCT1 = sqrt( eMatrix1( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
   double sigZ01 = sqrt( eMatrix1( KTHelix::kZ0, KTHelix::kZ0 ) );
   double sigCT2 = sqrt( eMatrix2( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
   double sigZ02 = sqrt( eMatrix2( KTHelix::kZ0, KTHelix::kZ0 ) );

//    report( INFO, kFacilityString ) << "sigCT1 " << sigCT1 << " sigZ01 " << sigZ01 << endl;
//    report( INFO, kFacilityString ) << "sigCT2 " << sigCT2 << " sigZ02 " << sigZ02 << endl;

   DABoolean goodZ1 = (sigCT1 < 1) && (sigZ01 < 0.01);
   DABoolean goodZ2 = (sigCT2 < 1) && (sigZ02 < 0.01);

   //Classify the type of group
   int subCategory = 0; 

   //Split groups and incomplete messes are any groups where all dbcd's are greater than 2cm
   if( d0Abs1 > 0.02 && d0Abs2 > 0.02 ) subCategory = 1;

//    if( subCategory == 1 ) report( INFO, kFacilityString ) << "The group is a MESS :-)" << endl;

   //Decay and backSplash
   int bdTrack = 0;
   if( subCategory == 0 )
   {
      int numDB = 0;
      int numBkS = 0;
      int numDcy = 0;

      for( int j=0; j<2; j++ )
      {
	 int trk = m_curlerGroups[i][j];
	 if( fabs( m_data->d0(trk-1) ) > 0.02 )
	 {
	    numDB++;
	 }
	 else if( m_data->rcImpact(trk-1) > 0.82 )
	 {
	    numBkS++;
	    bdTrack = trk;
	 }
	 else
	 {
	    numDcy++;
	    bdTrack = trk;
	 }
      }
      if( numDB == 1 )
      {
	 if( numBkS == 1 )      subCategory = 2;
	 else if( numDcy == 1 ) subCategory = 3;
      }

   }

   //If the subcategory has not been set yet the group must be normal
   if( subCategory == 0 ) subCategory = 4;

//    report( INFO, kFacilityString ) << "The subcategory is " << subCategory << " bdTrack " << bdTrack << endl;
   int FH = 0;
   if( subCategory == 4 )
   {

      //Get the regions
      double cosReg;
      if( (cosTheta1 < -0.1 && cosTheta2 < -0.1) || (cosTheta1 > 0.1 && cosTheta2 > 0.1) )
	 cosReg = 1;
      else cosReg = 2;
      
      double d0Reg;
      if( d0Abs1 < 0.002 && d0Abs2 < 0.002 )
	 d0Reg = 2;
      else if( d0Abs1 < 0.002 || d0Abs2 < 0.002 )
	 d0Reg = 1;
      else
	 d0Reg = 3;
   
      double z0Reg;
      if( z0Abs1 < 0.002 && z0Abs2 < 0.002 )
	 z0Reg = 2;
      else if( z0Abs1 < 0.002 || z0Abs2 < 0.002 )
	 z0Reg = 1;
      else
	 z0Reg = 3;

      double denReg;
      if( (den1>0.8 && den2>0.8) || (den1<=0 || den2 <= 0) )
	 denReg = 3;
      else if( den1>0 && den2>0 && ( den1>0.8 || den2>0.8 ) )
	 denReg = 1;
      else denReg = 2;

      double zHReg;
      if( zHits1 > 6 && zHits2 > 6 )
	 zHReg = 1;
      else if( zHits1 <=6 && zHits2 <= 6 )
	 zHReg = 2;
      else
	 zHReg = 3;
   
      double svrHReg;
      if( svrHits1 < 2 && svrHits2 < 2 )
	 svrHReg = 2;
      else if( svrHits1 >= 2 && svrHits2 >= 2 )
	 svrHReg = 3;
      else
	 svrHReg = 1;
   
      double zEReg;
      if( sigZ01 < 0.0025 && sigZ02 < 0.0025 )
	 zEReg = 2;
      else if( sigZ01 >= 0.0025 && sigZ02 >= 0.0025 )
	 zEReg = 3;
      else zEReg = 1;
   
      double thEReg;
      if( sigCT1 < 0.015 && sigCT2 < 0.015 )
	 thEReg = 2;
      else if( sigCT1 >= 0.015 && sigCT2 >= 0.015 )
	 thEReg = 3;
      else thEReg = 1;

      double rHEReg;
      if( rHE1 > 0.5 && rHE1 < 1.0 && rHE2 > 0.5 && rHE2 < 1.0 )
	 rHEReg = 1;
      else if( (rHE1 > 0.5 && rHE1 < 1.0 && rHE2 <= 0.5) ||
	       (rHE2 > 0.5 && rHE2 < 1.0 && rHE2 <= 0.5) )
	 rHEReg = 2;
      else if( ( rHE1 <= 0.5 && rHE2 <= 0.5 ) ||
	       ( rHE1 >= 1.0 && rHE2 >= 1.0 ) )
	 rHEReg = 3;
      else
	 rHEReg = 4;

      //probabilty arrays
      double cosPr[2]   = { 0.85, 0.51 };
      double dbPr[3]    = { 0.91, 0.60, 0.61 };
      double z0Pr[3]    = { 0.90, 0.58, 0.52 };
      double denPr[3]   = { 0.96, 0.74, 0.64 };
      double zHPr[3]    = { 0.82, 0.55, 0.79 };
      double svrHPr[3]  = { 0.97, 0.22, 0.60 };
      double zErrPr[3]  = { 0.92, 0.73, 0.61 };
      double thErrPr[3] = { 0.93, 0.63, 0.79 };
      double rhePr[4]   = { 0.76, 0.95, 0.17, 0.35 };

      //Likelihood for each track
      double l1 = 1;
      double l2 = 1;
      for( int n=0; n<4; n++ )
      {
	 if( d0Reg == (n+1) )
	 {
	    if( d0Abs1 < d0Abs2 )
	    { 
	       l1 = l1*dbPr[n];
	       l2 = l2*(1-dbPr[n]);
	    }
	    else if( d0Abs1 > d0Abs2 )
	    {
	       l2 = l2*dbPr[n];
	       l1 = l1*(1-dbPr[n]);
	    }
	 }
	 if( z0Reg == (n+1) )
	 {
	    if( z0Abs1 < z0Abs2 )
	    { 
	       l1 = l1*z0Pr[n];
	       l2 = l2*(1-z0Pr[n]);
	    }
	    else
	    {
	       l2 = l2*z0Pr[n];
	       l1 = l1*(1-z0Pr[n]);
	    }
	 }
	 if( denReg == (n+1) )
	 {
	    if( den1 > den2 )
	    { 
	       l1 = l1*denPr[n];
	       l2 = l2*(1-denPr[n]);
	    }
	    else if( den1 > den2 )
	    {
	       l2 = l2*denPr[n];
	       l1 = l1*(1-denPr[n]);
	    }
	 }

	 if( cosReg == (n+1) )
	 {
	    if( fabs(cosTheta1) < fabs(cosTheta2) )
	    {	       
	       l1 = l1*cosPr[n];
	       l2 = l2*(1-cosPr[n]);
	    }
	    else if( fabs(cosTheta1) > fabs(cosTheta2) )
	    {
	       l2 = l2*cosPr[n];
	       l1 = l1*(1-cosPr[n]);
	    } 
	 }
	 if( zHReg == (n+1) )
	 {
	    if( zHits1 > zHits2 )
	    {	       
	       l1 = l1*zHPr[n];
	       l2 = l2*(1-zHPr[n]);
	    }
	    else if( zHits1 < zHits2 )
	    {
	       l2 = l2*zHPr[n];
	       l1 = l1*(1-zHPr[n]);
	    } 
	 }
	 if( svrHReg == (n+1) )
	 {
	    if( svrHits1 > svrHits2 )
	    {	       
	       l1 = l1*svrHPr[n];
	       l2 = l2*(1-svrHPr[n]);
	    }
	    else if( svrHits1 < svrHits2 )
	    {
	       l2 = l2*svrHPr[n];
	       l1 = l1*(1-svrHPr[n]);
	    } 
	 }
	 if( zEReg == (n+1) )
	 {
	    if( sigZ01 < sigZ02 )
	    {	       
	       l1 = l1*zErrPr[n];
	       l2 = l2*(1-zErrPr[n]);
	    }
	    else if( sigZ01 > sigZ02 )
	    {
	       l2 = l2*zErrPr[n];
	       l1 = l1*(1-zErrPr[n]);
	    } 
	 }
	 if( thEReg == (n+1) )
	 {
	    if( sigCT1 < sigCT2 )
	    {	       
	       l1 = l1*thErrPr[n];
	       l2 = l2*(1-thErrPr[n]);
	    }
	    else if( sigCT1 > sigCT2 )
	    {
	       l2 = l2*thErrPr[n];
	       l1 = l1*(1-thErrPr[n]);
	    } 
	 }
	 if( rHEReg == (n+1) )
	 {
	    if( rHE1 > rHE2 )
	    {
	       l1 = l1*rhePr[n];
	       l2 = l2*(1-rhePr[n]);
	    }
	    else if( rHE2 > rHE1 )
	    {
	       l2 = l2*rhePr[n];
	       l1 = l1*(1-rhePr[n]);	       
	    }
	 }
      }

      if( l1 > l2 ) FH = 1;
      else          FH = 2;


   }

   TrackCodes theCodes;
   theCodes.reserve( m_curlerGroups[i].size() );

   if( subCategory == 1 )
   {
      //All d0 large
      theCodes.push_back( -203 );
      theCodes.push_back( -203 );
   }
   else if( subCategory == 2 )
   {
      //BackSplash
      //Group circle is defined as the inward going arc
      //for back splash
      if( bdTrack == track1 )
      {
	 theCodes.push_back(  212 );
	 theCodes.push_back( -212 );
	 setCircleTrack( i, track2 );
      }
      else
      {
	 theCodes.push_back( -212 );
	 theCodes.push_back(  212 );
	 setCircleTrack( i, track1 );
      }
   }
   else if( subCategory == 3 )
   {
      //Decay
      if( bdTrack == track1 )
      {
	 theCodes.push_back(  202 );
	 theCodes.push_back( -202 );
	 setCircleTrack( i, track2 );
      }
      else
      {
	 theCodes.push_back( -202 );
	 theCodes.push_back(  202 );
	 setCircleTrack( i, track1 );
      }
   }
   else if( subCategory == 4 )
   {
      if( FH == 1 )
      {
	 theCodes.push_back(  201 );
	 theCodes.push_back( -201 );	 
      }
      else
      {
	 theCodes.push_back( -201 );
	 theCodes.push_back(  201 );
      }
   }
   else
   {
      report( ERROR, kFacilityString ) << "No category selected for two Curler Classification!!" << endl;
   }

   m_curlerCodes.push_back( theCodes );
   theCodes.clear();
}

void TMCurlers::classifyThreeCurlerGroup( int i )
{

   //Set up the variables that are needed for the classification
   
   //The two tracks in the group
   int track1 = m_curlerGroups[i][0];
   int track2 = m_curlerGroups[i][1];
   int track3 = m_curlerGroups[i][2];

   double z0Abs1 = fabs( m_data->z0( track1-1 ) );
   double z0Abs2 = fabs( m_data->z0( track2-1 ) );
   double z0Abs3 = fabs( m_data->z0( track3-1 ) );

   double d0Abs1 = fabs( m_data->d0( track1-1 ) );
   double d0Abs2 = fabs( m_data->d0( track2-1 ) );
   double d0Abs3 = fabs( m_data->d0( track3-1 ) );


   //Classify the type of group
   int subCategory = 0;

   //Split groups and incomplete messes. All have d0 greater than 2cm
   if( d0Abs1 > 0.02 && d0Abs2 > 0.02 && d0Abs3 > 0.02 )
      subCategory = 4;



   //Decay or backsplash groups. Divide these into four categories
   //decay with tight or loose tails, backsplash with tight or loose tails.
   //(Loose tails are defined as tail separation greater than 5cm.)
   int bdTrack1 = 0;
   int bdTrack2 = 0;
   int bdTrack3 = 0;

   if( subCategory == 0 )
   {
      int numD0 = 0;
      int numBkS = 0;
      int numDcy = 0;
      for( int j=0; j<3; j++ )
      {
	 int trk = m_curlerGroups[i][j];
	 if( fabs( m_data->d0(trk-1) ) > 0.035 )
	 {
	    numD0++;
	    if( bdTrack1 == 0 )
	    {
	       bdTrack1 = trk;
	    }
	    else
	    {
	       bdTrack2 = trk;
	    }
	 }
	 else if( m_data->radiusOfCurv(trk-1) > 0.94 )
	 {
	    numBkS++;
	    bdTrack3 = trk;
	 }
	 else
	 {
	    numDcy++;
	    bdTrack3 = trk;
	 }
      }
      //If two of the tracks have large d0 ...
      if( numD0 == 2 )
      {
	 int iPair;
	 if( bdTrack1 > bdTrack2 )
	 {
	    iPair = pairNumber( bdTrack2, bdTrack1, m_theTracks.size() );
	 }
	 else
	 {
	    iPair =  pairNumber( bdTrack1, bdTrack2, m_theTracks.size() );
	 }
	 if( delTails( iPair ) < 0.05 )
	 {
	    if( numBkS == 1 )
	    {
	       subCategory = 2;
	    }
	    else if( numDcy == 1 )
	    {
	       subCategory = 3;
	    }
	 }
	 else
	 {
	    if( numBkS == 1 )
	    {
	       subCategory = -2;	       
	    }
	    else if( numDcy == 1 )
	    {
	       subCategory = -3;
	    } 
	 }
      }
   }

   //If the group of tracks has not yet been classified it is normal.
   //For three curler groups there are four normal classes ...
   // i.   Normal third track inside  5
   // ii.  Abnormal third track outside 6
   // iii. Normal loose, third track inside  -5
   // iv.  Abnormal loose, third track outside -6
   int num1 = 0;
   int num2 = 0;
   int extraTrack = 0;
   if( subCategory == 0 )
   {

      double minDRC = 0.03;
      double avgRC = 0;

      extraTrack = normalThreeCurlerInfo( track1, track2, track3,  
					  minDRC, avgRC, num1, num2 ); 


      //If any of the opposite curvature pairs
      //had delRC smaller than 3cm then we can
      //stop here
      if( extraTrack > 0 ) 
      {
	 //If the extra track has a smaller radius than 
	 //the main two this is a normal group, otherwise 
	 //it is abnormal.
	 if( m_data->radiusOfCurv( extraTrack-1 ) < avgRC )
	    subCategory = 5;
	 else
	    subCategory = 6;


      }
      //If none of the opposite curvature pairs had
      //delRC smaller than 3cm then we have a looser 
      //group and must continue with classification
      else 
      {
	 minDRC = 1.0;

	 extraTrack = normalThreeCurlerInfo( track1, track2, track3,
					     minDRC, avgRC, num1, num2 );

	 
	 if( extraTrack > 0 )
	 {
	    if( m_data->radiusOfCurv( extraTrack-1 ) < avgRC )
	       subCategory = -5;
	    else
	       subCategory = -6;
	 }
	 else
	 {
	    subCategory = 7;
	 }

      }
   }


   //The group should have been subcategorised by now.
   if( subCategory == 0 )
   {
      report( ERROR, kFacilityString ) << "The group has not been put into a"
				       << " valid subcategory!!!!" << endl;
   }


   int FH = 0;
   //Abnormal Curler Groups, use liklihood method
   if( fabs( subCategory ) == 6 )
   {
      track1 = extraTrack;
      track2 = num1;
      track3 = num2;

      FAItem< NavTrack > t1 = m_theTracks.find( track1 );
      FAItem< NavTrack > t2 = m_theTracks.find( track2 );
      FAItem< NavTrack > t3 = m_theTracks.find( track3 );

      //Get the d0
      double d01 = fabs( m_data->d0( track1-1 ) );
      double d02 = fabs( m_data->d0( track2-1 ) );
      double d03 = fabs( m_data->d0( track3-1 ) );
      d02 = min(d02,d03);

      double z01 = fabs( t1->seedTrack()->z0() );
      double z02 = fabs( t2->seedTrack()->z0() );
      double z03 = fabs( t3->seedTrack()->z0() );
      z02 = min(z02,z03);
      
      FAItem< TRTrackFitQuality > tQual1 = t1->pionQuality();
      FAItem< TRTrackFitQuality > tQual2 = t2->pionQuality();
      FAItem< TRTrackFitQuality > tQual3 = t3->pionQuality();
      
      unsigned int zHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );
      unsigned int zHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );
      unsigned int zHits3 = tQual3->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual3->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual3->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );

      zHits2 = max(zHits2,zHits3);
      
      unsigned int svrHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );
      unsigned int svrHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );
      unsigned int svrHits3 = tQual3->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );
      svrHits2 = max(svrHits2,svrHits3);

      double zAngle = 0;
      double cotTheta1 = t1->seedTrack()->cotTheta();
      if( cotTheta1 != 0 )
	 zAngle = atan( 1/cotTheta1 );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta1 = cos( zAngle );
      
      zAngle = 0;
      double cotTheta2 = t2->seedTrack()->cotTheta();
      if( cotTheta2 != 0 )
	 zAngle = atan( 1/cotTheta2 );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta2 = cos( zAngle );

      zAngle = 0;
      double cotTheta3 = t3->seedTrack()->cotTheta();
      if( cotTheta3 != 0 )
	 zAngle = atan( 1/cotTheta3 );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta3 = cos( zAngle );
   
      if( fabs(cosTheta3) < fabs(cosTheta2) )
	 cosTheta2 = cosTheta3;


      const HepSymMatrix& eMatrix1 = t1->pionHelix()->errorMatrix();
      const HepSymMatrix& eMatrix2 = t2->pionHelix()->errorMatrix();
      const HepSymMatrix& eMatrix3 = t3->pionHelix()->errorMatrix();
   
      double sigCT1 = sqrt( eMatrix1( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ01 = sqrt( eMatrix1( KTHelix::kZ0, KTHelix::kZ0 ) );
      double sigCT2 = sqrt( eMatrix2( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ02 = sqrt( eMatrix2( KTHelix::kZ0, KTHelix::kZ0 ) );
      double sigCT3 = sqrt( eMatrix3( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ03 = sqrt( eMatrix3( KTHelix::kZ0, KTHelix::kZ0 ) );

      sigCT2 = min(sigCT2,sigCT3);
      sigZ02 = min(sigZ02,sigZ03);

      double thErr1 = sigCT1;
      double zErr1 = sigZ01;
      double thErr2 = sigCT2;
      double zErr2 = sigZ02;

      //Get the regions and calculate the liklihood
      int cosTReg = 0;
      if( cosTheta1 < 0 && cosTheta1 > -0.2
	  && fabs( cosTheta2 ) <= 0.1 )
      {
	 cosTReg = 1;
      }
      else if( cosTheta1 < 0.2 && cosTheta1 >= 0
	       && fabs( cosTheta2 ) <= 0.1 )
      {
	 cosTReg = 2;
      }
      else if( ( cosTheta1 <= -0.2 && cosTheta2 <= 0.1 ) ||
	       ( cosTheta1 >= 0.2 && cosTheta2 > 0.1 ) )
      {
	 cosTReg = 3;
      }
      else if( ( cosTheta1 <= -0.2 && cosTheta2 > 0.1 ) ||
	       ( cosTheta1 >= 0.2 && cosTheta2 <= 0.1 ) )
      {
	 cosTReg = 4;
      }
      else if( ( cosTheta1 < 0 && cosTheta1 > -0.2 && cosTheta2 < -0.1 ) ||
	       ( cosTheta1 < 0.2 && cosTheta1 > 0 && cosTheta2 > 0.1 ) )
      {
	 cosTReg = 5;
      }
      else
      {
	 cosTReg = 6;
      }

      int d0Reg = 0;
      if( d01 >= 0.005 && d02 < 0.005 )
      {
	 d0Reg = 1;
      }
      else if( d01 < 0.005 && d02 >= 0.005 )
      {
	 d0Reg = 2;
      }
      else if( d01 < 0.005 && d02 < 0.005 )
      {
	 d0Reg = 3;
      }
      else
      {
	 d0Reg = 4;
      }

      int thErrReg = 0;
      if( thErr1 >= 0.02 && thErr2 < 0.02 )
      {
	 thErrReg = 1;
      }
      else if( thErr1 < 0.02 && thErr2 >= 0.02 )
      {
	 thErrReg = 2;
      }
      else if( thErr1 < 0.02 && thErr2 < 0.02 )
      {
	 thErrReg = 3;
      }
      else
      {
	 thErrReg = 4;
      }

      int z0Reg = 0;
      if( z01 >= 0.05 && z02 < 0.05 )
      {
	 z0Reg = 1;
      }
      else if( z01 < 0.05 && z02 >= 0.05 )
      {
	 z0Reg = 2;
      }
      else if( z01 < 0.05 && z02 < 0.05 )
      {
	 z0Reg = 3;
      }
      else
      {
	 z0Reg = 4;
      }

      int zErrReg = 0;
      if( zErr1 >= 0.001 && zErr2 < 0.001 )
      {
	 zErrReg = 1;
      }
      else if( zErr1 < 0.001 && zErr2 >= 0.001 )
      {
	 zErrReg = 2;
      }
      else if( zErr1 < 0.001 && zErr2 < 0.001 )
      {
	 zErrReg = 3;
      }
      else
      {
	 zErrReg = 4;
      }

      int zHitReg = 0;
      if( zHits1 < 5 && zHits2 < 15 )
      {
	 zHitReg = 1;
      }
      else if( zHits1 < 5 && zHits2 >= 15 )
      {
	 zHitReg = 2;
      }
      else if( zHits1 > 5 && zHits1 < 30 && 
	       zHits2 < 15 && zHits1 > zHits2 )
      {
	 zHitReg = 3;
      }
      else if( zHits1 > 5 && zHits1 < 30 && 
	       zHits2 < 15 && zHits1 <= zHits2 )
      {
	 zHitReg = 4;
      }
      else if( zHits1 > 5 && zHits1 < 30 && 
	       zHits2 >= 15 && zHits1 > zHits2 )
      {
	 zHitReg = 5;
      }
      else if( zHits1 > 5 && zHits1 < 30 && 
	       zHits2 >= 15 && zHits1 <= zHits2 )
      {
	 zHitReg = 6;
      }
      else
      {
	 zHitReg = 7;
      }

      double likelihood = cosTL[cosTReg-1]*d0L[d0Reg-1]*thErrL[thErrReg-1]*
	                  z0L[z0Reg-1]*zErrL[zErrReg-1]*zHitL[zHitReg-1];
      
      if( likelihood <= 0.085 )
      {
	 //Reset the subCategory which will throw away
	 //the spurious extra track
	 if( subCategory == -6 )
	 {
	    subCategory = -8;
	 }
	 else
	 {
	    subCategory = 8;
	 }
      }

   }

   //Normal Curler Groups
   if( fabs( subCategory ) == 5 || fabs( subCategory ) == 8 )
   { 

      //Change the track order to match 
      //what was found
      track1 = num1;
      track2 = num2;
      track3 = extraTrack;


      d0Abs1 = fabs( m_data->d0( track1-1 ) );
      d0Abs2 = fabs( m_data->d0( track2-1 ) );

      double zAngle = 0;
      if( m_data->cotTheta( track1-1 ) != 0 )
	 zAngle = atan( 1/m_data->cotTheta( track1-1 ) );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta1 = cos( zAngle );

      zAngle = 0;
      if( m_data->cotTheta( track2-1 ) != 0 )
	 zAngle = atan( 1/m_data->cotTheta( track2-1 ) );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta2 = cos( zAngle );

      //Need to get the tracks to see the SVHits
      FAItem< NavTrack > nTrack1 = m_theTracks.find( track1 );
      FAItem< NavTrack > nTrack2 = m_theTracks.find( track2 );

      //Find the no. of hits in each section required, use a pion fit.
      FAItem< TRTrackFitQuality > tQual1 = nTrack1->pionQuality();
      FAItem< TRTrackFitQuality > tQual2 = nTrack2->pionQuality();

      //No. of stereo + cathode + svz hits
      unsigned int zHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );
      unsigned int zHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );

      unsigned int svrHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );
      unsigned int svrHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );

      //The maximum d0
      double d0Max = max( d0Abs1, d0Abs2 );
      double z0Max = max( z0Abs1, z0Abs2 );


      //Do the tracks have good z information? Use the error from the helix matrix
      const HepSymMatrix& eMatrix1 = nTrack1->pionHelix()->errorMatrix();
      const HepSymMatrix& eMatrix2 = nTrack2->pionHelix()->errorMatrix();

      double sigCT1 = sqrt( eMatrix1( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ01 = sqrt( eMatrix1( KTHelix::kZ0, KTHelix::kZ0 ) );
      double sigCT2 = sqrt( eMatrix2( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ02 = sqrt( eMatrix2( KTHelix::kZ0, KTHelix::kZ0 ) );

      //Get the regions
      double cosReg;
      if( (cosTheta1 < -0.05 && cosTheta2 < -0.05) || (cosTheta1 > 0.05 && cosTheta2 > 0.05) )
	 cosReg = 1;
      else cosReg = 2;
      
      double d0Reg;
      if( d0Abs1 < 0.001 && d0Abs2 < 0.001 )
	 d0Reg = 2;
      else if( d0Abs1 < 0.001 || d0Abs2 < 0.001 )
	 d0Reg = 1;
      else
	 d0Reg = 3;
   
      double zHReg;
      if( zHits1 > 6 && zHits2 > 6 )
	 zHReg = 1;
      else if( zHits1 <=6 && zHits2 <= 6 )
	 zHReg = 2;
      else
	 zHReg = 3;
   
      double svrHReg;
      if( svrHits1 < 2 && svrHits2 < 2 )
	 svrHReg = 2;
      else if( svrHits1 >= 2 && svrHits2 >= 2 )
	 svrHReg = 3;
      else
	 svrHReg = 1;
   
      double zEReg;
      if( sigZ01 < 0.0015 && sigZ02 < 0.0015 )
	 zEReg = 2;
      else if( sigZ01 >= 0.0015 && sigZ02 >= 0.0015 )
	 zEReg = 3;
      else zEReg = 1;
   
      double thEReg;
      if( sigCT1 < 0.015 && sigCT2 < 0.015 )
	 thEReg = 2;
      else if( sigCT1 >= 0.015 && sigCT2 >= 0.015 )
	 thEReg = 3;
      else thEReg = 1;


      //Get the cell number for the selection;
      int cellNumber = getCellNum( cosReg, d0Reg, zHReg, 
				   svrHReg, zEReg, thEReg );

      int choiceN = threeCurlerCellListNormal[ cellNumber ];

      if( choiceN == 5 )
      {
	 //Choose by zErr
	 if( sigZ01 < sigZ02 )
	 {	       
	    FH = 1; //FH
	 }
	 else
	 {
	    FH = 2;
	 }
	 
      }
      else if( choiceN == 6 )
      {
	 //Choose by thErr
	 if( sigCT1 < sigCT2 )
	 {	       
	    FH = 1;
	 }
	 else
	 {
	    FH = 2;
	 }
      }
      else if( choiceN == 2 )
      {
	 //Choose by d0
	 if( d0Abs1 < d0Abs2 )
	 {	       
	    FH = 1;
	 }
	 else
	 {
	    FH = 2;
	 }
      }
      else if( choiceN == 3 )
      {
	 //Choose by zHits
	 if( zHits1 > zHits2 )
	 {	       
	    FH = 1;
	 }
	 else
	 {
	    FH = 2;
	 }
      }
      else if( choiceN == 4 )
      {
	 //Choose by svrHits
	 if( svrHits1 > svrHits2 )
	 {	       
	    FH = 1;
	 }
	 else
	 {
	    FH = 2;
	 }
      }
      else if( choiceN == 1 )
      {
	 //Choose by cosTheta
	 if( fabs(cosTheta1) < fabs(cosTheta2) )
	 {	       
	    FH = 1;
	 }
	 else
	 {
	    FH = 2;
	 }
      }
   }



   TrackCodes theCodes;
   theCodes.reserve( m_curlerGroups[i].size() );

   if( fabs( subCategory ) == 5 )
   {
      for( int j=0; j<m_curlerGroups[i].size(); j++ )
      {
	 if( m_curlerGroups[i][j] == num1 )
	 {
	    if( FH == 1 ) theCodes.push_back( 206 );
	    else          theCodes.push_back( -206 );
	 }
	 else if( m_curlerGroups[i][j] == num2 )
	 {
	    if( FH == 2 ) theCodes.push_back( 206 );
	    else          theCodes.push_back( -206 );
	 }
	 else if( m_curlerGroups[i][j] == extraTrack )
	 {
	    theCodes.push_back( -206 );
	 }
      }

      if( FH == 1 ) setCircleTrack( i, num1  );
      else          setCircleTrack( i, num2  );

   }
   else if( fabs( subCategory ) == 8 )
   {
      for( int j=0; j<m_curlerGroups[i].size(); j++ )
      {
	 if( m_curlerGroups[i][j] == num1 )
	 {
	    if( FH == 1 ) theCodes.push_back( 231 );
	    else          theCodes.push_back( -231 );
	 }
	 else if( m_curlerGroups[i][j] == num2 )
	 {
	    if( FH == 2 ) theCodes.push_back( 231 );
	    else          theCodes.push_back( -231 );
	 }
	 else if( m_curlerGroups[i][j] == extraTrack )
	 {
	    theCodes.push_back( -231 );
	 }
      }        
      if( FH == 1 ) setCircleTrack( i, num1  );
      else          setCircleTrack( i, num2  );
   }
   else if( fabs( subCategory ) == 6 ) 
   {
      for( int j=0; j<m_curlerGroups[i].size(); j++ )
      {
	 if( m_curlerGroups[i][j] == num1 )
	 {
	    theCodes.push_back( -210 );
	 }
	 else if( m_curlerGroups[i][j] == num2 )
	 {
	    theCodes.push_back( -210 );
	 }
	 else if( m_curlerGroups[i][j] == extraTrack )
	 {
	    theCodes.push_back( 210 );
	 }
      }  
      setCircleTrack( i, extraTrack  );
   }
   else if( subCategory == 4 )
   {
      for( int j=0; j<m_curlerGroups[i].size(); j++ )
      {
	 theCodes.push_back( -211 );
      }
   }
   else if( fabs( subCategory ) == 3 )
   {
      for( int j=0; j<m_curlerGroups[i].size(); j++ )
      {
	 if( m_curlerGroups[i][j] == bdTrack1 )
	 {
	    theCodes.push_back( -216 );
	 }
	 else if( m_curlerGroups[i][j] == bdTrack2 )
	 {
	    theCodes.push_back( -216 );
	 }
	 else if( m_curlerGroups[i][j] == bdTrack3 )
	 {
	    theCodes.push_back( 216 );
	 }
      }
      setCircleTrack( i, bdTrack1 );
   }
   else if( fabs( subCategory ) == 2 )
   {
      for( int j=0; j<m_curlerGroups[i].size(); j++ )
      {
	 if( m_curlerGroups[i][j] == bdTrack1 )
	 {
	    theCodes.push_back( -217 );
	 }
	 else if( m_curlerGroups[i][j] == bdTrack2 )
	 {
	    theCodes.push_back( -217 );
	 }
	 else if( m_curlerGroups[i][j] == bdTrack3 )
	 {
	    theCodes.push_back( 217 );
	 }
      }
      setCircleTrack( i, bdTrack1 );
   }
   else report( WARNING, kFacilityString ) << "No subCategory given!!!" << endl;

   m_curlerCodes.push_back( theCodes );
   theCodes.clear();


}

void TMCurlers::classifyOtherCurlerGroup( int i )
{

   //First choose the pair of tracks with the largest average curvature
   //which also satisfy diametric end distance less than a certain cut.
   int track1 = 0;
   int track2 = 0;

   int jTrack;
   int kTrack;
   double avPairCurv = 0;
   int j;
   for( j=0; j<m_curlerGroups[i].size()-1; j++ )
   {
      jTrack = m_curlerGroups[i][j];
      for( int k=j+1; k<m_curlerGroups[i].size(); k++ )
      {
	 kTrack = m_curlerGroups[i][k];
	 //The tracks must be of opposite sign to be a 
	 //pair ( circle ).
	 if( m_data->curvature( jTrack-1 )*m_data->curvature( kTrack-1 ) < 0 )
	 {
	    int ipair = pairNumber( jTrack, kTrack, m_theTracks.size() );
	    double delJKAve = delRadiusCDAVec( ipair );
	    double delRCImpact = fabs( m_data->rcImpact( jTrack - 1 ) -
				       m_data->rcImpact( kTrack - 1 ) );
	    if( delJKAve < 0.1 && delRCImpact < 0.03 )
	    {
	       double avCurvJK = 0.5*( m_data->radiusOfCurv( jTrack-1 ) +
				   m_data->radiusOfCurv( kTrack-1 ) );
	       //Choose the pair with the larger average diameter of
	       //curvature.
	       if( avCurvJK > avPairCurv )
	       {
		  track1 = jTrack;
		  track2 = kTrack;
		  avPairCurv = avCurvJK;
	       }
	    }
	 }
      }
   }

//    iout << "The tracks " << track1 << " " << track2 << endl;

   //Count how many tracks are above the largest pair and how
   //many are below.
   int numAbove = 0;
   int numBelow = 0;
   for( j=0; j<m_curlerGroups[i].size(); j++ )
   {
      jTrack = m_curlerGroups[i][j];
      if( jTrack != track1 && jTrack != track2 )
      {
	 double rcIm = m_data->rcImpact( jTrack-1 );
	 if( rcIm > avPairCurv )
	 {
	    numAbove++;
	 }
	 else
	 {
	    numBelow++;
	 }
      }
   }

//    iout << "Num above " << numAbove << " Num below " << numBelow << endl;

   //Now the groups can be categorised.
   int subCategory = 0;

   //Split groups and incomplete messes,
   //all the tracks have dB > 2cm.
   int numDBLarge = 0;
   for( j=0; j<m_curlerGroups[i].size(); j++ )
   {
      jTrack = m_curlerGroups[i][j];
      if( fabs( m_data->d0( jTrack-1 ) ) > 0.02 )
      {
	 numDBLarge++;
      }
   }
   if( numDBLarge == m_curlerGroups[i].size() )
      subCategory = 6;

//    iout << "Num db large " << numDBLarge << endl;

   //Find decay and backsplash groups
   int numBkS = 0;
   int numDcy = 0;
   int bdTrack = 0;
   for( j=0; j<m_curlerGroups[i].size(); j++ )
   {
      jTrack = m_curlerGroups[i][j];
      if( fabs( m_data->d0( jTrack-1 ) ) <= 0.02 &&
	  m_data->rcImpact( jTrack-1 ) > 0.94 )
      {
	 numBkS++;
	 bdTrack = jTrack;
      }
      else if( fabs( m_data->d0( jTrack-1 ) ) <= 0.02 )
      {
	 numDcy++;
	 bdTrack = jTrack;
      }
   }   
   
//    iout << "NumBks " << numBkS << endl;
//    iout << "NumDcy " << numDcy << endl;

   if( numDBLarge == m_curlerGroups[i].size()-1 )
   {
      if( numBkS == 1 )
      {
	 subCategory = 2;
      }
      else if( numDcy == 1 )
      {
	 subCategory = 3;
      }
   }

//    iout << "Sbcat " << subCategory << endl;

   //Groups of four 2+ and 2-. Divide these groups into 
   //categories 'pretty' and 'ugly'
   if( subCategory == 0 )
   {
      HepMatrix radiusSortMatrix( 7, 25, 0 );
      if( m_curlerGroups[i].size() == 4 )
      {
	 int numNeg = 0;
	 int numPos = 0;
	 for( j=0; j<4; j++ )
	 {
	    jTrack = m_curlerGroups[i][j];
	    if( m_data->curvature( jTrack-1 ) > 0 )
	    {
	       numPos++;
	    }
	    else
	    {
	       numNeg++;
	    }
	    radiusSortMatrix( 1, j+1 ) = jTrack;
	    radiusSortMatrix( 2, j+1 ) = m_data->rcImpact( jTrack-1 );
	 }
// 	 iout << "Numpos is " << numPos << endl;
	 if( numPos == 2 )
	 {
	    setRadiusSortMatrix( radiusSortMatrix, -2 );
	 }
	 int t1 = radiusSortMatrix(1,1);
	 int t2 = radiusSortMatrix(1,2);
	 if( m_data->curvature( t1-1 )*m_data->curvature( t2-1 ) < 0 )
	 {
	    track1 = t1;
	    track2 = t2;
	    if( ( radiusSortMatrix(2,1) - radiusSortMatrix(2,3) > 0.03 ) &&
		( radiusSortMatrix(2,1) - radiusSortMatrix(2,4) > 0.03 ) && 
		( radiusSortMatrix(2,2) - radiusSortMatrix(2,3) > 0.03 ) &&
		( radiusSortMatrix(2,2) - radiusSortMatrix(2,4) > 0.03 ) )
	    {
	       subCategory = 7;
	    }
	    else
	    {
	       subCategory = 8;   
	    }
	 }
	 
      }
   }
   
   //2n n+ n- groups with all tracks below the largest pair
   //by some amount
   int numOver = 0;
   int overTrack;
   if( subCategory == 0 )
   {
      DABoolean allUnder = true;
      if( track1 != 0 && track2 != 0 )
      {
	 for( j=0; j<m_curlerGroups[i].size(); j++ )
	 {
	    jTrack = m_curlerGroups[i][j];
	    if( m_data->densityOfHits( jTrack-1 ) > 0.2 )
	    {
	       if( jTrack != track1 && jTrack != track2 )
	       {
		  if( ( m_data->radiusOfCurv( track1-1 ) 
			- m_data->radiusOfCurv( jTrack-1 ) < 0.03 ) ||
		      ( m_data->radiusOfCurv( track2-1 ) 
			- m_data->radiusOfCurv( jTrack-1 ) < 0.03 ) )
		  {
		     allUnder = false;
		  }
		  if( ( m_data->radiusOfCurv( jTrack-1 ) 
			- m_data->radiusOfCurv( track1-1 ) >= 0.03 ) &&
		      ( m_data->radiusOfCurv( jTrack-1 ) 
			- m_data->radiusOfCurv( track2-1 ) >= 0.03 ) )
		  {
		     numOver++;
		     overTrack = jTrack;
		  }
	       }
	    }
	 }
	 
	 if( allUnder )
	 {
	    subCategory = 9;
	 }
	 else if( numOver == 1 )
	 {
	    subCategory = 10;
	 }
      }
   }


   //Get the left over tracks
   if( subCategory == 0 )
   {
      if( track1 != 0 && track2 != 0 )
      {
	 subCategory = 11;
      }
      else
      {
	 subCategory = 12;
      }
   }


   int FH;
   if( track1 != 0 && track2 != 0 )
   {

      double d0Abs1 = fabs( m_data->d0( track1-1 ) );
      double d0Abs2 = fabs( m_data->d0( track2-1 ) );

      double zAngle = 0;
      if( m_data->cotTheta( track1-1 ) != 0 )
	 zAngle = atan( 1/m_data->cotTheta( track1-1 ) );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta1 = cos( zAngle );

      zAngle = 0;
      if( m_data->cotTheta( track2-1 ) != 0 )
	 zAngle = atan( 1/m_data->cotTheta( track2-1 ) );
      else
	 zAngle = kPi/2;
      if( zAngle < 0 )
      {
	 zAngle += kPi;
      }
      double cosTheta2 = cos( zAngle );

      //Get the relevant information for the tracks
      //Need to get the tracks to see the SVHits
      FAItem< NavTrack > nTrack1 = m_theTracks.find( track1 );
      FAItem< NavTrack > nTrack2 = m_theTracks.find( track2 );

      //Find the no. of hits in each section required, use a pion fit.
      FAItem< TRTrackFitQuality > tQual1 = nTrack1->pionQuality();
      FAItem< TRTrackFitQuality > tQual2 = nTrack2->pionQuality();

      //No. of stereo + cathode + svz hits
      unsigned int zHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );
      unsigned int zHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	 + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	 + tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );

      unsigned int svrHits1 = tQual1->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );
      unsigned int svrHits2 = tQual2->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );

      //The maximum d0
      double d0Max = max( d0Abs1, d0Abs2 );


      //Do the tracks have good z information? Use the error from the helix matrix
      const HepSymMatrix& eMatrix1 = nTrack1->pionHelix()->errorMatrix();
      const HepSymMatrix& eMatrix2 = nTrack2->pionHelix()->errorMatrix();

      double sigCT1 = sqrt( eMatrix1( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ01 = sqrt( eMatrix1( KTHelix::kZ0, KTHelix::kZ0 ) );
      double sigCT2 = sqrt( eMatrix2( KTHelix::kCotTheta, KTHelix::kCotTheta ) );
      double sigZ02 = sqrt( eMatrix2( KTHelix::kZ0, KTHelix::kZ0 ) );
      
   

      //Now choose the winning tracks
      if( subCategory == 7 || subCategory == 9 )
      {
	 //Get the regions
	 double cosReg;
	 if( (cosTheta1 < -0.1 && cosTheta2 < -0.1) || (cosTheta1 > 0.1 && cosTheta2 > 0.1) )
	    cosReg = 1;
	 else cosReg = 2;
	 
	 double d0Reg;
	 if( d0Abs1 < 0.002 && d0Abs2 < 0.002 )
	    d0Reg = 2;
	 else if( d0Abs1 < 0.002 || d0Abs2 < 0.002 )
	    d0Reg = 1;
	 else
	    d0Reg = 3;
	 
	 double zHReg;
	 if( zHits1 > 20 && zHits2 > 20 )
	    zHReg = 1;
	 else if( zHits1 <= 20 && zHits2 <= 20 )
	    zHReg = 2;
	 else
	    zHReg = 3;
	 
	 double svrHReg;
	 if( svrHits1 < 2 && svrHits2 < 2 )
	    svrHReg = 2;
	 else if( svrHits1 >= 2 && svrHits2 >= 2 )
	    svrHReg = 3;
	 else
	    svrHReg = 1;
      
	 double zEReg;
	 if( sigZ01 < 0.0015 && sigZ02 < 0.0015 )
	    zEReg = 2;
	 else if( sigZ01 >= 0.0015 && sigZ02 >= 0.0015 )
	    zEReg = 3;
	 else zEReg = 1;
      
	 double thEReg;
	 if( sigCT1 < 0.015 && sigCT2 < 0.015 )
	    thEReg = 2;
	 else if( sigCT1 >= 0.015 && sigCT2 >= 0.015 )
	    thEReg = 3;
	 else thEReg = 1;
	 

	 //Get the cell number for the selection;
	 int cellNumber = getCellNum( cosReg, d0Reg, zHReg, 
				      svrHReg, zEReg, thEReg );

	 int choiceN = fourCurlerCellListNormal[ cellNumber ];
      
	 if( choiceN == 5 )
	 {
	    //Choose by zErr
	    if( sigZ01 < sigZ02 )
	    {	       
	       FH = track1; //FH
	    }
	    else
	    {
	       FH = track2;
	    }
	 
	 }
	 else if( choiceN == 6 )
	 {
	    //Choose by thErr
	    if( sigCT1 < sigCT2 )
	    {	       
	       FH = track1;
	    }
	    else
	    {
	       FH = track2;
	    }
	 }
	 else if( choiceN == 2 )
	 {
	    //Choose by d0
	    if( d0Abs1 < d0Abs2 )
	    {	       
	       FH = track1;
	    }
	    else
	    {
	       FH = track2;
	    }
	 }
	 else if( choiceN == 3 )
	 {
	    //Choose by zHits
	    if( zHits1 > zHits2 )
	    {	       
	       FH = track1;
	    }
	    else
	    {
	       FH = track2;
	    }
	 }
	 else if( choiceN == 4 )
	 {
	    //Choose by svrHits
	    if( svrHits1 > svrHits2 )
	    {	       
	       FH = track1;
	    }
	    else
	    {
	       FH = track2;
	    }
	 }
	 else if( choiceN == 1 )
	 {
	    //Choose by cosTheta
	    if( fabs(cosTheta1) < fabs(cosTheta2) )
	    {	       
	       FH = track1;
	    }
	    else
	    {
	       FH = track2;
	    }
	 }
	 
      }
   }

   if( subCategory == 8 || subCategory == 10 ||
       subCategory == 11 || subCategory == 12 )
   {
      chooseMessyGroups( i, FH );
   }
   

   //Set the codes for the group.
   TrackCodes theCodes;
   theCodes.reserve( m_curlerGroups[i].size() );
   for( j=0; j<m_curlerGroups[i].size(); j++ )
   {
      jTrack = m_curlerGroups[i][j];
//       if( subCategory == 7 || subCategory == 9 )
//       {
// 	 jTrack = m_curlerGroups[i][j];
// 	 if( jTrack == track1 )
// 	 {
// 	    theCodes.push_back( 401 );
// 	 }
// 	 else if( jTrack == track2 )
// 	 {
// 	    theCodes.push_back( 402 );
// 	 }
// 	 else
// 	 {
// 	    theCodes.push_back( 403 );
// 	 }
//       }
      if( subCategory == 2 )
      {
	 if( jTrack == bdTrack )
	 {
	    theCodes.push_back( 220 );
	 }
	 else
	 {
	    theCodes.push_back( -220 );
	    setCircleTrack( i, jTrack );
	 }
      }
      else if( subCategory == 3 )
      {
	 if( jTrack == bdTrack )
	 {
	    theCodes.push_back( 215 );
	 }
	 else
	 {
	    theCodes.push_back( -215 );
	    setCircleTrack( i, jTrack );
	 }
      }
      else if( subCategory == 6 )
      {
	 theCodes.push_back( -218 );
      }
      else if( subCategory == 7 )
      {
	 if( jTrack == FH )
	 {
	    theCodes.push_back( 205 );
	    setCircleTrack( i, jTrack );
	 }
	 else
	 {
	    theCodes.push_back( -205 );
	 }
      }
      else if( subCategory == 8 )
      {
	 if( jTrack == FH )
	 {
	    theCodes.push_back( 219 );
	    setCircleTrack( i, jTrack );
	 }
	 else
	 {
	    theCodes.push_back( -219 );
	 }
// 	 theCodes.push_back( 400 );
      }
      else if( subCategory == 9 )
      {
	 if( jTrack == FH )
	 {
	    theCodes.push_back( 214 );
	    setCircleTrack( i, jTrack );
	 }
	 else
	 {
	    theCodes.push_back( -214 );
	 }	 
      }
      else if( subCategory == 10 )
      {
	 if( jTrack == FH )
	 {
	    theCodes.push_back( 230 );
	    setCircleTrack( i, jTrack );
	 }
	 else
	 {
	    theCodes.push_back( -230 );
	 }
// 	 theCodes.push_back( 400 );
      }
      else if( subCategory == 11 || 
	       subCategory == 12 )
      {
	 if( jTrack == FH )
	 {
	    theCodes.push_back( 207 );
	    setCircleTrack( i, jTrack );
	 }
	 else
	 {
	    theCodes.push_back( -207 );
	 }
// 	 theCodes.push_back( 400 );
      }
      else
      {
	 report( WARNING, kFacilityString ) << "No subcategory given to 4+ Curler group!!" << endl;
      }
   }

   m_curlerCodes.push_back( theCodes );
   theCodes.clear();

}


int TMCurlers::getCellNum( int v1, int v2, int v3, int v4, int v5, int v6 )
{
   int v1Max = 2;
   int v2Max = 3;
   int v3Max = 3;
   int v4Max = 3;
   int v5Max = 3;

   int x = v1;
   x += (v2 - 1) * v1Max;
   x += (v3 - 1) * v1Max * v2Max;
   x += (v4 - 1) * v1Max * v2Max * v3Max;
   x += (v5 - 1) * v1Max * v2Max * v3Max * v4Max;
   x += (v6 - 1) * v1Max * v2Max * v3Max * v4Max * v5Max;
   return x;


}

int TMCurlers::normalThreeCurlerInfo( int track1, int track2, int track3,
						   double& minDRC, double& avgRC, 
						   int& num1, int& num2 )
{

   double c1 = m_data->curvature( track1-1 );
   double c2 = m_data->curvature( track2-1 );
   double c3 = m_data->curvature( track3-1 );
   double rc1 = m_data->radiusOfCurv( track1-1 );
   double rc2 = m_data->radiusOfCurv( track2-1 );
   double rc3 = m_data->radiusOfCurv( track3-1 );
   double delRC = 0;

   int extraTrack = 0;
   
   if( c1*c2 < 0 )
   {
      delRC = fabs( rc1 - rc2 );
      if( delRC < minDRC )
      {
	 avgRC = ( rc1+rc2 )/2;
	 minDRC = delRC;
	 extraTrack = track3;
	 num1 = track1;
	 num2 = track2;
      }
   }
   if( c1*c3 < 0 )
   {
      delRC = fabs( rc1 - rc3 );
      if( delRC < minDRC ) 
      {
	 avgRC = ( rc1+rc3 )/2;
	 minDRC = delRC;
	 extraTrack = track2;
	 num1 = track1;
	 num2 = track3;
      }
   }
   if( c3*c2 < 0 )
   {
      delRC = fabs( rc3 - rc2 );
      if( delRC < minDRC ) 
      {
	 avgRC = ( rc3+rc2 )/2;
	 minDRC = delRC;
	 extraTrack = track1;
	 num1 = track3;
	 num2 = track2;
      }
   }

   return extraTrack;
}


//External functions
extern "C"
void sortm_( FDouble* radsort, 
	     FInteger& row,
	     FInteger& col,
	     FInteger& sPos );


void TMCurlers::setRadiusSortMatrix( HepMatrix& radiusSortMatrix, int sortPos )
{
   TBFortran2DArray< FDouble, 7, 25 > radsort;
   FInteger sPos = sortPos;
   FInteger row = 7;
   FInteger col = 25;

   //Set the fortran array to the value of our matrix
   int i, j;
   for( i=1; i<=7; i++ )
   {
      for( j=1; j<=25; j++ )
      {
	 radsort( i,j ) = radiusSortMatrix( i,j );
      }
   }

   sortm_( radsort.cArray(), row, col, sPos );


   for( i=1; i<=7; i++ )
   {
      for( j=1; j<=25; j++ )
      {
	 radiusSortMatrix( i,j ) = radsort( i,j );
// 	 if( i<=2 && j<=4 )
// 	    report( INFO, kFacilityString ) << i << " " << j << " " << radiusSortMatrix( i,j ) << endl;
      }
   }
}

void TMCurlers::setProbabilitySortMatrix( HepMatrix& sortMatrix, int theCol )
{
   TBFortran2DArray< FDouble, 2, 500 > radsort;
   FInteger sPos = -2;
   FInteger row = 2;
   FInteger col = theCol;
   FInteger maxCol = 500;

   //Set the fortran array to the value of our matrix
   int i,j,k;
   for( i=1; i<=2; i++ )
   {
      for( j=1; j<=col; j++ )
      {
	 radsort( i,j ) = sortMatrix( i,j );
      }
      for( k=col; k<=maxCol; k++ )
      {
	 radsort( i,k ) = 0;
      }
   }

   sortm_( radsort.cArray(), row, maxCol, sPos );

   for( i=1; i<=2; i++ )
   {
      for( j=1; j<=col; j++ )
      {
	 sortMatrix( i,j ) = radsort( i,j );
// 	 report( INFO, kFacilityString ) << i << " " << j << " " << sortMatrix( i,j ) << endl;
      }
   }
}

void TMCurlers::chooseMessyGroups( int group, int& FH )
{

   //Make two Sort matrices
   HepMatrix sort( 7, 25, 0 );
   HepMatrix cTrack( 2, m_theTracks.size(), 0 );

   //Fill the matrices and sort according to the
   //different variables.
   int j;
   int jTrack;
   for( j=0; j<m_curlerGroups[group].size(); j++ )
   {
      jTrack = m_curlerGroups[group][j];
      cTrack( 1, jTrack ) = jTrack;
      if( m_data->densityOfHits( jTrack-1 ) > 0.2 )
      {
	 FAItem< TRTrackFitQuality > tQual = m_theTracks.find(jTrack)->pionQuality();

	 //No. of stereo + cathode + svz hits
	 unsigned int zHits = tQual->numberSubdetectorHitLayers( TRSubdetectorLists::kSVZ )
	    + tQual->numberSubdetectorHitLayers( TRSubdetectorLists::kDR3Stereo )
	    + tQual->numberSubdetectorHitLayers( TRSubdetectorLists::kDRCathode );

	 unsigned int svrHits = tQual->numberSubdetectorHitLayers( TRSubdetectorLists::kSVR );

	 sort( 1, j+1 ) = jTrack;
	 sort( 2, j+1 ) = m_data->radiusOfCurv( jTrack-1 );
	 sort( 3, j+1 ) = 1 - fabs( m_data->d0( jTrack-1 ) );
	 sort( 4, j+1 ) = zHits;
	 sort( 5, j+1 ) = m_data->densityOfHits( jTrack-1 );
	 sort( 6, j+1 ) = svrHits;
	 
      }
   }

   //Sort by diameter of curve
   setRadiusSortMatrix( sort, -2 );
   for( j=0; j<m_curlerGroups[group].size(); j++ )
   {
      jTrack = sort( 1, j+1 );
      cTrack( 2, jTrack ) = rcProb[j];
   }   

   //Sort by distance from beam spot
   setRadiusSortMatrix( sort, -3 );
   for( j=0; j<m_curlerGroups[group].size(); j++ )
   {
      jTrack = sort( 1, j+1 );
      cTrack( 2, jTrack ) = dbProb[j]*cTrack( 2, jTrack );
   }   

   //Sort by z Hits
   setRadiusSortMatrix( sort, -4 );
   for( j=0; j<m_curlerGroups[group].size(); j++ )
   {
      jTrack = sort( 1, j+1 );
      cTrack( 2, jTrack ) = zHProb[j]*cTrack( 2, jTrack );
   }   

   //Sort by density of Hits
   setRadiusSortMatrix( sort, -5 );
   for( j=0; j<m_curlerGroups[group].size(); j++ )
   {
      jTrack = sort( 1, j+1 );
      cTrack( 2, jTrack ) = denProb[j]*cTrack( 2, jTrack );
   }   

   //Sort by silicon vertex radial hits 
   setRadiusSortMatrix( sort, -6 );
   for( j=0; j<m_curlerGroups[group].size(); j++ )
   {
      jTrack = sort( 1, j+1 );
      cTrack( 2, jTrack ) = svrHProb[j]*cTrack( 2, jTrack );
   }   
   
   setProbabilitySortMatrix( cTrack, m_theTracks.size() );
   FH = cTrack( 1,1 );

   if( cTrack( 2, 1 ) == 0 )
   {
      //If this hasn't worked just sort by zHits
      //which gave second best results from svr
      //but in later data sets svr is unreliable 
      //because of silicon degredation.
      setRadiusSortMatrix( sort, -4 );
      FH = sort( 1, 1 ); 
   }

}


//
// const member functions
//
TMCurlers::CurlerCodeVector TMCurlers::curlerCodes() const
{
   return m_curlerCodes;
}

TMCurlers::TrackCodes TMCurlers::classificationVector() const
{
   TrackCodes classVec;

   for( int j=0; j<m_theTracks.size(); j++ )
   {
      classVec.push_back( 0 );
   }


   for( int k=0; k<m_curlerGroups.size(); k++ )
   {
      for( int n=0; n<m_curlerGroups[k].size(); n++ )
      {
	 int track = m_curlerGroups[k][n];
	 int code = m_curlerCodes[k][n];
	 classVec[ track-1 ] = code;
      }
   }

   return classVec;
}
//
// static member functions
//










