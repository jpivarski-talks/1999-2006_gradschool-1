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
// Created:     Wed Sep 18 11:24:29 EDT 2002
// $Id$
//
// Revision history
//
// $Log$

#include "Experiment/Experiment.h"
#include "Trkman/TMClassification.h"
#include "TrackRoot/TRSeedTrack.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Geometry/Point3D.h"

//Initialise some static variables
static const double kPi       = 3.1415926535898;
static const double kDelKsMass  = 0.03;
static const double kDelLamMass = 0.01;
static const double kDelGamMass = 0.035;

static const double kKsMass  = 0.498;
static const double kLamMass = 1.115;

static const char* const kFacilityString = "Trkman.TMVees" ;

#define iout report( INFO, kFacilityString )
#define wout report( WARNING, kFacilityString )


//
// member functions
//
void TMClassification::findVees()
{

   NavTrackConstIt iTrack = m_theTracks.begin();
   for( ; iTrack != m_theTracks.end(); iTrack++ )
   {
      int i = (*iTrack).identifier();
      //if( m_trackClass[ i-1 ] != 0 ) continue;
      if( m_trackClass[ i-1 ] != 0 && 
	  fabs( m_trackClass[ i-1 ] ) != 301 ) continue;

      //Get the Fits for the iTrack
      DABoolean iIsPiFit = false;
      FAItem< TRTrackFitQuality > ipiTQ = (*iTrack).pionQuality();
      FAItem< TDKinematicFit > iPiFit;
      if( ipiTQ->fit() && !ipiTQ->fitAbort() )
	 //if( !ipiTQ->fitAbort() )
      {
	 iIsPiFit = true;
	 iPiFit = (*iTrack).pionFit();
      }

      if( !iIsPiFit ) continue;

      DABoolean iIsPrFit = false;
      double iprC = -1; 
      FAItem< TRTrackFitQuality > iprTQ = (*iTrack).protonQuality();
      FAItem< TDKinematicFit > iPrFit;
      if( iprTQ->fit() && !iprTQ->fitAbort() )
      {
	 iIsPrFit = true;
	 iprC = iprTQ->chiSquare()/(double)iprTQ->degreesOfFreedom();
	 iPrFit = (*iTrack).protonFit();
      }

      //iTrack Variables
      m_iCurv = (*m_data).curvature( i-1 );
      m_iRadius = 1/(2*m_iCurv);
      m_iPhi = (*m_data).phi( i-1 );
      m_iDA = (*m_data).dA( i-1 );
      m_iSign = m_iCurv/fabs(m_iCurv);
      m_iXC = -( m_iRadius + m_iDA )*sin( m_iPhi ); 
      m_iYC =  ( m_iRadius + m_iDA )*cos( m_iPhi ); 
      HepPoint3D iCentre( m_iXC, m_iYC, 0 );
      m_iCentre = iCentre;  
      m_iMom = iPiFit->momentum();
      m_iZ0 = (*m_data).z0( i-1 );
      m_iCotTheta = (*m_data).cotTheta( i-1 );

      //Loop over the remaining tracks
      DABoolean foundPair = false;
      NavTrackConstIt jTrack = iTrack;
      jTrack++;
      for( ; jTrack != m_theTracks.end(); jTrack++ )
      {
	 //if( foundPair ) continue;
	 
	 int  j = (*jTrack).identifier();
 	 if( m_trackClass[ j-1 ] != 0 && 
	     fabs( m_trackClass[ j-1 ] ) != 301 ) continue;
	 //if( m_trackClass[ j-1 ] != 0 ) continue;

	 //Get the Fits for the jTrack
	 DABoolean jIsPiFit = false;
	 FAItem< TRTrackFitQuality > jpiTQ = (*jTrack).pionQuality();
	 FAItem< TDKinematicFit > jPiFit;
	 if( jpiTQ->fit() && !jpiTQ->fitAbort() )
	    //if( !jpiTQ->fitAbort() )
	 {
	    jIsPiFit = true;
	    jPiFit = (*jTrack).pionFit();
	 }
	 
	 DABoolean jIsPrFit = false;
	 double jprC = -1;
	 FAItem< TRTrackFitQuality > jprTQ = (*jTrack).protonQuality();
	 FAItem< TDKinematicFit > jPrFit;
	 if( jprTQ->fit() && !jprTQ->fitAbort() )
	 {
	    jIsPrFit = true;
	    jprC = jprTQ->chiSquare()/(double)jprTQ->degreesOfFreedom();
	    jPrFit = (*jTrack).protonFit();
	 }

	 //Make sure that these tracks do not come from a
	 //neutral decay, Ks, /\, Gam, in that case we want to keep them
	 //both!
	 double ksMass = -1;
	 if( jIsPiFit )
	 {
	    HepLorentzVector sum = jPiFit->lorentzMomentum() 
	                         + iPiFit->lorentzMomentum();
	    ksMass = sum.mag();
	 }
	 else continue;

	 if( fabs( ksMass - kKsMass ) < kDelKsMass ) continue;  

	 double lamMass = -1;
	 if( iIsPrFit && jIsPrFit )
	 {
	    //Which track is more likely to be a proton?
	    if( iprC < jprC )
	    {
	       HepLorentzVector sum = iPrFit->lorentzMomentum() 
		                    + jPiFit->lorentzMomentum();
	       lamMass = sum.mag();
	       
	    }
	    else
	    {
	       HepLorentzVector sum = jPrFit->lorentzMomentum() 
		                    + iPiFit->lorentzMomentum();
	       lamMass = sum.mag();
	    }
	 }

	 if( fabs( lamMass - kLamMass ) < kDelLamMass ) continue;


	 //Electron fits are not usually stored so we need to
	 //estimate the gam mass using the pion momenta
	 double gamMass = -1;
	 m_jMom = jPiFit->momentum();

	 double mE = 0.000511;
	 double iE = sqrt( m_iMom.mag2() + mE*mE ); 
	 double jE = sqrt( m_jMom.mag2() + mE*mE );

	 HepLorentzVector sum = HepLorentzVector( m_iMom+m_jMom, iE+jE );
	 gamMass = sum.mag();


	 if( fabs( gamMass ) < kDelGamMass ) continue;

	 //Now we know this pair of tracks didn't come from
	 //a neutral decay, see if it is some other sort of 
	 //vee.
	 
	 //jTrack Variables
	 m_jCurv = (*m_data).curvature( j-1 );
	 m_jRadius = 1/(2*m_jCurv);
	 m_jPhi = (*m_data).phi( j-1 );
	 m_jDA = (*m_data).dA( j-1 );
	 m_jSign = m_jCurv/fabs(m_jCurv);
	 m_jXC = -( m_jRadius + m_jDA )*sin( m_jPhi ); 
	 m_jYC =  ( m_jRadius + m_jDA )*cos( m_jPhi );
	 HepPoint3D jCentre( m_jXC, m_jYC, 0 );
	 m_jCentre = jCentre; 
	 m_jZ0 = (*m_data).z0( j-1 );
	 m_jCotTheta = (*m_data).cotTheta( j-1 );

	 double centreDiff = ( m_jCentre - m_iCentre ).mag();
	 double radiiSum = fabs( m_iRadius ) + fabs( m_jRadius );
	 double radiiDiff = fabs( fabs( m_iRadius ) - fabs( m_jRadius ) );

	 //The tracks will have an intersection if the
	 //sum of the radii is greater that the distance
	 //between the two centres, as long as one circle
	 //is not entirely contained within the other.

	 ///////////////////////////////////////////////
	 // ** Define intersection variables **       //
	 //                                           //
	 // p0 = centre point of i circle             //
	 // p1 = centre point of j circle             //
	 // d  = | p1 - p0 | (dist between centres)   //
	 // r0 = radius of i circle                   //
	 // r1 = radius of j circle                   //
	 // p3+/p3- = circle intersection points      //
	 // p2 = intersection point of line joining   //
	 //      p3pos and p3neg and the line joining //
	 //      p0 and p1.                           //
	 // h  = distance from p2 to p3pos or p3neg   //
	 // hVec = unit vector from p2 to p3pos       //
	 // a  = distance from p0 to p2               //
	 //                                           //
	 // Using these variables we have:            //
	 //                                           //
	 // p2 = p0 + (a/d)*( p1 - p0 )               //
	 // p3+ = p2 + h*hVec                         //
	 // p3- = p2 - h*hVec                         //
	 ///////////////////////////////////////////////

	 double d = centreDiff;
	 if( d==0 ) continue;
	 double r0 = m_iRadius;
	 double r1 = m_jRadius;
	 HepPoint3D p0( m_iCentre );
	 HepPoint3D p1( m_jCentre );

	 if( (centreDiff  - radiiSum) < 0  && 
	     (centreDiff >= radiiDiff) )
	 {
	    //First check the the cross product is not
	    //zero or close to. 
	    double det = (m_iCentre.cross( m_jCentre )).z();
	    if( fabs(det) < 1e-16 ) continue;

	    HepPoint3D hVec( (p1.y()-p0.y())/d, -(p1.x()-p0.x())/d, 0 );
	    double a = ( d*d + r0*r0 -r1*r1 )/(2*d);
	    double h = sqrt( r0*r0 - a*a );

	    HepPoint3D p2 = p0 + (a/d)*( p1 - p0 ); 

	    HepPoint3D p3pos = p2 + h*hVec;
	    HepPoint3D p3neg = p2 - h*hVec;
	    
	    double intRadiusSqP = p3pos.mag2(); 
	    double intRadiusSqM = p3neg.mag2(); 
	    
	    m_posPassed = vertexProperties( p3pos, true );
	    m_negPassed = vertexProperties( p3neg, false );

	    if( !m_posPassed && !m_negPassed ) continue;

	 }
	 else if( centreDiff - radiiSum < 0.002 )
	 {
	    //Here we calculate the two points on the circles
	    //that lie on the line joining the centres. They
	    //should lie very close together. The intersection
	    //point will be taken as the average of these two 
	    //points. 
	    
	    HepPoint3D pp0 = p0 + (r0/d)*( p1 - p0 );
	    HepPoint3D pp1 = p1 - (r1/d)*( p1 - p0 );

	    double mX = 0.5*(pp0.x() + pp1.x() );
	    double mY = 0.5*(pp0.y() + pp1.y() );
	    HepPoint3D mid( mX, mY, 0 );	    
	    if( !vertexProperties( mid, true ) ) continue;

	 }
	 else continue;

	 //Calculate the radial impact paramter
	 //If we are here then all the vertex 
	 //variables are filled.
	 HepPoint3D beamSpot = (*m_data).beamSpot();
	 beamSpot.setZ(0);
	 HepVector3D cross = ( m_vxPos - beamSpot ).cross( m_vxMom ); 
	 m_vxRMiss = cross.mag()/m_vxMom.mag();

	 //Scott calculated the variance of the 
	 //delZ and rMiss distributions, for now
	 //use these, but should calculate my own.
	 m_vxChiSq = m_vxDelZ*m_vxDelZ/(3.4e-5) + 
	             m_vxRMiss*m_vxRMiss/(3.1e-7);
	 
	 foundPair = calculateTrackHitDensities( i, j );

      }

   }


   //Now merge the groups and if they have more than two
   //tracks reclassify. Groups with more than two tracks
   //are usually very messy, all tagged to one particle.
   //Choose the best track to represent the group, this 
   //should be the track with greatest density.
   reclassifyVees();
}

//Function to determine vertex properties
DABoolean TMClassification::vertexProperties( HepPoint3D& vtx, DABoolean first )
{
   //Calculate the radial flight distance from
   //the interaction point
   HepPoint3D beamSpot = (*m_data).beamSpot();
   beamSpot.setZ(0);
   double rBeam = ( vtx - beamSpot ).mag();

   //If the vertex is too close or too far from
   //the interaction point we don't want it.
   //Ie, it should be outside the BP (2.0cm) and
   //inside the DR (82cm).
   if( rBeam > 0.82 ) return false;
   if( rBeam < 0.02 ) return false;
   
   //Calculate the angle between the phi of
   //the tracks and the intersection vtx.
   //If this angle is > pi/2 this shouldn't be
   //a vee.
   //iTrack
   double iDot = vtx.x()*cos(m_iPhi) + vtx.y()*sin(m_iPhi);
   double cosPhiV = iDot/vtx.mag();

   if( fabs( cosPhiV ) > 1 ) return false;

   double phiV = acos( cosPhiV );
   if( phiV > kPi/2 ) return false;

   //jTrack
   double jDot = vtx.x()*cos(m_jPhi) + vtx.y()*sin(m_jPhi); 
   cosPhiV = jDot/vtx.mag();

   if( fabs( cosPhiV ) > 1 ) return false;

   phiV = acos( cosPhiV );
   if( phiV > kPi/2 ) return false;

   //Calculate the rotation angle to the
   //intersection. The sin of the rotation
   //angle is the projection of the vertex
   //vector onto the unit p-Vector, divided
   //by the radius.
   //iTrack
   double iSinPsi = iDot/m_iRadius;
   if( fabs( iSinPsi > 1 ) ) return false;
   double iPsi = asin( iSinPsi );
   
   //jTrack
   double jSinPsi = jDot/m_jRadius;
   if( fabs( jSinPsi > 1 ) ) return false;
   double jPsi = asin( jSinPsi );

   //Recalculate each tracks three momentum at the
   //vertex. Then calculate the total momentum
   //at the vertex.
   //iTrack
   double newPhi = m_iPhi + iPsi;
   if( newPhi > 2*kPi ) newPhi -= 2*kPi;
   if( newPhi < 0 )     newPhi += 2*kPi;
   
   double sinPhi = sin( newPhi );
   double cosPhi = cos( newPhi );
   double r      = m_iMom.perp();
   HepVector3D iVMom( r*cosPhi, r*sinPhi, 0 );

   //jTrack
   newPhi = m_jPhi + jPsi;
   if( newPhi > 2*kPi ) newPhi -= 2*kPi;
   if( newPhi < 0 )     newPhi += 2*kPi;
   
   sinPhi = sin( newPhi );
   cosPhi = cos( newPhi );
   r      = m_jMom.perp();
   HepVector3D jVMom( r*cosPhi, r*sinPhi, 0 );
   
   //Vertex
   HepVector3D vxMom = iVMom + jVMom;

   //Calculate the cosine of the angle between
   //the vertex location and the vertex direction.
   double vxCosAngle = (beamSpot.unit()).dot( vxMom.unit() );

   //Calculate the intersection z coords
   double iZ = m_iZ0 + m_iRadius*iPsi*m_iCotTheta;
   double jZ = m_jZ0 + m_jRadius*jPsi*m_jCotTheta;

   vtx.setZ( 0.5*( iZ + jZ ) );

   double vxDelZ = iZ - jZ;

   //Set the variables if this is the first vertex,
   //OR if its the second vertex and the first one
   //didn't pass, OR if its the second vertex and
   //its a better candidate than the first.
   if( first ||
     (!first && !m_posPassed) ||
     (!first && ( fabs( vxDelZ ) < fabs( m_vxDelZ ) )) )
   {
      m_iPsi = iPsi;
      m_jPsi = jPsi;
      
      m_iVMom = iVMom;
      m_jVMom = jVMom;

      m_vxMom = vxMom;
      m_vxPos = vtx;

      m_vxCosAngle = vxCosAngle;
      m_vxDelZ = vxDelZ;
	 
   }

   return true;
}


DABoolean TMClassification::calculateTrackHitDensities( int i, int j )
{

   //Track densities
   double iDens = (*m_data).densityOfHits( i-1 );
   double jDens = (*m_data).densityOfHits( j-1 );

   //Layer number of the vertex
   int vxLayer = (*m_data).layerAtRadius( m_vxPos.perp() );

   
   //Get the maximum layer to which the tracks
   //extend
   double maxLayer = 56;
   int iMaxL = (*m_data).maxLayer( i-1 );
   int jMaxL = (*m_data).maxLayer( j-1 );

   if( iMaxL < maxLayer ) maxLayer = iMaxL;
   if( jMaxL < iMaxL )    maxLayer = jMaxL;
   if( maxLayer < vxLayer ) maxLayer = 56;

   double iDensBefore = 0;
   double jDensBefore = 0;
   double iDensAfter = 0;
   double jDensAfter = 0;

   int iHitsBefore = 0;
   int jHitsBefore = 0;
   int iHitsAfter = 0;
   int jHitsAfter = 0;

   //Make sure the vertex is outside of the silicon
   //or else cannot do densities properly.
   if( vxLayer > 9 )
   {
      int k;
      int iHits = 0;
      int jHits = 0;
      for( k=9; k<=vxLayer; k++ )
      {
	 if( (*m_data).isLayerHit( i-1, k ) ) iHits++;
	 if( (*m_data).isLayerHit( j-1, k ) ) jHits++;
      }
      iDensBefore = (double)iHits/(double)(vxLayer-8);
      jDensBefore = (double)jHits/(double)(vxLayer-8);

      iHits = 0;
      jHits = 0;
      for( k=vxLayer-5; k<=vxLayer-1; k++ )
      {
	 if( (*m_data).isLayerHit( i-1, k ) ) iHits++;
	 if( (*m_data).isLayerHit( j-1, k ) ) jHits++;
      } 
      iHitsBefore = iHits;
      jHitsBefore = jHits;


      iHits = 0;
      jHits = 0;
      if( maxLayer > vxLayer )
      {
	 for( k=vxLayer+1; k<=maxLayer; k++ )
	 {
	    if( (*m_data).isLayerHit( i-1, k ) ) iHits++;
	    if( (*m_data).isLayerHit( j-1, k ) ) jHits++;
	 }
	 iDensAfter = (double)iHits/(double)(maxLayer-vxLayer);
	 jDensAfter = (double)jHits/(double)(maxLayer-vxLayer);

	 iHits = 0;
	 jHits = 0;
	 int max = vxLayer+5;
	 if( maxLayer < max ) max = maxLayer;
	 for( k=vxLayer+1; k<=max; k++ )
	 {
	    if( (*m_data).isLayerHit( i-1, k ) ) iHits++;
	    if( (*m_data).isLayerHit( j-1, k ) ) jHits++;
	 } 
	 iHitsAfter = iHits;
	 jHitsAfter = jHits;
      }
   }

   //Make XOR and AND
   int xor = 0;
   int and = 0;
   int lastL;
   if( iMaxL < jMaxL ) lastL = iMaxL;
   else iMaxL = jMaxL;
   for( int nn=1; nn<=lastL; nn++ )
   {
      DABoolean iHit = (*m_data).isLayerHit( i-1, nn );
      DABoolean jHit = (*m_data).isLayerHit( j-1, nn );
      if(  iHit && jHit ) and++;
      else if( iHit || jHit ) xor++;
   }


   //Skip the Vee if it doesn't pass the following cuts
   if( (iDensBefore > 0.1 && iDensAfter > 0.1) )
      return false;
   if( (jDensBefore > 0.1 && jDensAfter > 0.1) )
      return false;

   //Tight
   if( !( and<6 && xor<15 ) ) return false;

   if( vxLayer <= 16 || vxLayer >= 54 ) return false;

   if( fabs( m_vxDelZ ) >= 0.85 ) return false;

   //This IS a Vee!! Keep the track with the greater
   //density of hits before the vertex
   if( iDensBefore > jDensBefore )
   {
      m_trackClass[ i-1 ] =  301;
      m_trackClass[ j-1 ] = -301;
   }
   else if( jDensBefore > iDensBefore )
   {
      m_trackClass[ i-1 ] = -301;
      m_trackClass[ j-1 ] =  301;      
   }
   else
   {
      if( iDens > jDens )
      {
	 m_trackClass[ i-1 ] =  301;
	 m_trackClass[ j-1 ] = -301;
      }
      else if( jDens > iDens )
      {
	 m_trackClass[ i-1 ] = -301;
	 m_trackClass[ j-1 ] =  301;      
      }
      else
      {
	 if( (*m_data).d0( i-1 ) <= (*m_data).d0( j-1 ) )
	 {
	    m_trackClass[ i-1 ] =  301;
	    m_trackClass[ j-1 ] = -301;
	 }
	 else
	 {
	    m_trackClass[ i-1 ] = -301;
	    m_trackClass[ j-1 ] =  301;
	 }
      }
      
   }

   //Make the vee group vector
   VeeGroup vG;
   vG.push_back( i );
   vG.push_back( j );

   //m_tmpVeeGroups.push_back( vG );
   m_tmpVeeGroups.push_back( vG );
   vG.clear();

   return true;
}


void TMClassification::mergeVeeGroups( )
{
   VeeGroup veeList;
   veeList.reserve(10);
   int numVees = m_tmpVeeGroups.size();
   TruthVector pairMatched;
   for( int k=0; k<numVees; k++ ) pairMatched.push_back( false );

   int seedPair = 0;
   DABoolean stillUnmatchedPairs = true;
   while( stillUnmatchedPairs )
   {
      //Start the new list with the next unmatched curler pair
      veeList.push_back( m_tmpVeeGroups[seedPair][0] );
      veeList.push_back( m_tmpVeeGroups[seedPair][1] );
      
      pairMatched[seedPair] = true;

      makeVeeList( m_tmpVeeGroups, pairMatched, veeList );

      m_veeGroups.push_back( veeList );
      veeList.clear();

      stillUnmatchedPairs = false;
      for( int i=0; i<numVees; i++ )
      {
	 if( !pairMatched[i] )
	 {
	    seedPair = i;
	    stillUnmatchedPairs = true;
	 } 
      }

   }
}

void TMClassification::makeVeeList( VeeGroupVector pairList, TruthVector& matched, VeeGroup& list )
{
   int count = 1;
   int newVee;
   DABoolean moreVeesInList = true;
   while( moreVeesInList )
   {
      for( int i=0; i<pairList.size(); i++ )
      {
	 if( !matched[i] )
	 {
	    DABoolean addNewVee = false;
	    if( list[count-1] == pairList[i][0] )
	    {
	       matched[i] = true;
	       addNewVee = true;
	       newVee = pairList[i][1];
	    }
	    else if( list[count-1] == pairList[i][1] )
	    {
	       matched[i] = true;
	       addNewVee = true;
	       newVee = pairList[i][0];
	    }
	    
	    //If there is a new track loop over the current list 
	    //to make sure the it's not already there.
	    if( addNewVee )
	    {
	       if( matched[i] )
	       {
		  for( int j=0; j<list.size(); j++ )
		  {
		     if( newVee == list[j] )
		     {
			addNewVee = false;
			j = list.size();
			}
		  }
		  if( addNewVee ) list.push_back( newVee );
	       }
	    }
	 }
      }
      
      count++;
      if( count > list.size() ) moreVeesInList = false;
      
   }
}

void TMClassification::reclassifyVees()
{
   int numvees = m_tmpVeeGroups.size();
   if( numvees > 0 )
   {
      mergeVeeGroups();
      VeeGroup eraseGroups;
      for( int group=0; group<m_veeGroups.size(); group++ )
      {
	 if( m_veeGroups[group].size() > 2 )
	 {
	    double maxDens = -1;
	    int bestTrack = 0;
	    for( int trk=0; trk<m_veeGroups[group].size(); trk++ )
	    {
	       int tId = m_veeGroups[group][trk];
	       double trkDens = (*m_data).densityOfHits( tId-1 );
	       if( trkDens > maxDens )
	       {
		  bestTrack = tId;
		  maxDens = trkDens;
	       }
	    }
	    if( bestTrack == 0 )
	    {
	       wout << "Group " << group << " will be erased!" << endl;
	       eraseGroups.push_back( group );
	       for( int t=0; t<m_veeGroups[group].size(); t++ )
	       {
		  int tId = m_veeGroups[group][trk];
		  m_trackClass[ tId-1 ] = 0;
	       }
	    }
	    else
	    {
	       for( int t=0; t<m_veeGroups[group].size(); t++ )
	       {
		  int tId = m_veeGroups[group][t];
		  if( tId == bestTrack )
		  {
		     m_trackClass[ tId-1 ] = 302;
		  }
		  else
		  {
		     m_trackClass[ tId-1 ] = -302;
		  }
	       }
	    }
	 }
      }

      //Remove any groups with all low tracks.
      if( eraseGroups.size() != 0 )
      {
	 VeeGroupVector tmp = m_veeGroups;
	 m_veeGroups.clear();
	 for( int rg=0; rg<tmp.size(); rg++ )
	 {
	    DABoolean groupErased = false;
	    for( int eg=0; eg<eraseGroups.size(); eg++ )
	    {
	       if( rg == eraseGroups[eg] ) 
	       {
		  groupErased = true;
		  continue;
	       }
	    }
	    if( !groupErased ) m_veeGroups.push_back( tmp[rg] );
	 }
      }
   }
}





