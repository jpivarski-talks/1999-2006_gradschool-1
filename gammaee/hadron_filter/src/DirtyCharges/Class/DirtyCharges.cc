// -*- C++ -*-
//
// Package:     DirtyCharges
// Module:      DirtyCharges
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Nov 13 10:30:28 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "DirtyCharges/DirtyCharges.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"
#include "BeamSpot/BeamSpot.h"

//RICH example 
//Dedx example
//Event Shape example


// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.DirtyCharges" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
DirtyCharges::DirtyCharges( void )               // anal1
   : Processor( "DirtyCharges" )
   , m_beam_x(0.)
   , m_beam_y(0.)
   , m_beam_z(0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &DirtyCharges::event,    Stream::kEvent );
   //bind( &DirtyCharges::beginRun, Stream::kBeginRun );
   //bind( &DirtyCharges::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

DirtyCharges::~DirtyCharges()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
DirtyCharges::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
DirtyCharges::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
DirtyCharges::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_spreadPerp = iHistoManager.histogram(
      100, "Distances of Intersections from Closest Intersection", 100, 0., 0.05 );
   m_spreadZSep = iHistoManager.histogram(
      200, "Z Separation of Intersections (central value + tracking uncertainties)", 100, 0., 0.05 );

   m_charge = iHistoManager.histogram(
      300, "charge", 31, -15.5, 15.5 );

   m_charge_perp = iHistoManager.profile(
      310, "charge balance VS. distClosestInter in mm", 50, 0.5, 50.5, -1000., 1000.,
      HIHistProf::kErrorOnMean );
   m_charge_perp_2mm = iHistoManager.histogram(
      311, "charge distClosestInter 2 mm", 31, -15.5, 15.5 );
   m_charge_perp_4mm = iHistoManager.histogram(
      312, "charge distClosestInter 4 mm", 31, -15.5, 15.5 );
   m_charge_perp_1cm = iHistoManager.histogram(
      313, "charge distClosestInter 1 cm", 31, -15.5, 15.5 );
   m_charge_perp_5cm = iHistoManager.histogram(
      314, "charge distClosestInter 5 cm", 31, -15.5, 15.5 );

   m_charge_z = iHistoManager.profile(
      320, "charge balance VS. zSepInter in mm", 50, 0.5, 50.5, -1000., 1000.,
      HIHistProf::kErrorOnMean );
   m_charge_z_5mm = iHistoManager.histogram(
      321, "charge zSepInter 5 mm", 31, -15.5, 15.5 );
   m_charge_z_1cm = iHistoManager.histogram(
      322, "charge zSepInter 1 cm", 31, -15.5, 15.5 );


}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
DirtyCharges::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double ci_perp(1000.);
   double x(1000.);
   double y(1000.);
   double z(1000.);

   double znumer(0.);
   double zdenom(0.);

   int i;
   int charge(0);
   int charge_perp[50];  for ( i = 0;  i < 50;  i++ ) charge_perp[i] = 0;
   int charge_perp_2mm(0);
   int charge_perp_4mm(0);
   int charge_perp_1cm(0);
   int charge_perp_5cm(0);
   int charge_z[50];  for ( i = 0;  i < 50;  i++ ) charge_z[i] = 0;
   int charge_z_5mm(0);
   int charge_z_1cm(0);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./abs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  double perp( sqrt(sqr(tx - m_beam_x) + sqr(ty - m_beam_y)) );
		  if ( perp < ci_perp ) {
		     ci_perp = perp;
		     x = tx;
		     y = ty;
		  }

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - m_beam_x) + sqr(ty - m_beam_y) );
		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( zdenom != 0. ) z = znumer / zdenom;

   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 DABoolean pass_perp[50];  for ( i = 0;  i < 50;  i++) pass_perp[i] = false;
	 DABoolean pass_perp_2mm(false);
	 DABoolean pass_perp_4mm(false);
	 DABoolean pass_perp_1cm(false);
	 DABoolean pass_perp_5cm(false);

	 DABoolean pass_z[50];  for ( i = 0;  i < 50;  i++) pass_z[i] = false;
	 DABoolean pass_z_5mm(false);
	 DABoolean pass_z_1cm(false);

	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./abs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {
		  double perp(sqrt(sqr(tx - x) + sqr(ty - y)));

		  if ( tx != x  && ty != y ) m_spreadPerp->fill( perp );
		  m_spreadZSep->fill( tzsep );

		  for ( i = 0;  i < 50;  i++ ) {
		     float cut( float(i+1) * 0.001 );
		     if ( perp < cut ) pass_perp[i] = true;
		     if ( tzsep < cut ) pass_z[i] = true;
		  }

		  if ( perp < 0.002 ) pass_perp_2mm = true;
		  if ( perp < 0.004 ) pass_perp_4mm = true;
		  if ( perp < 0.01 ) pass_perp_1cm = true;
		  if ( perp < 0.05 ) pass_perp_5cm = true;

		  if ( tzsep < 0.005 ) pass_z_5mm = true;
		  if ( tzsep < 0.01 ) pass_z_1cm = true;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

	 int track_charge( track_iter->pionHelix()->curvature() > 0. ? 1 : -1 );

	 charge += track_charge;
	 for ( i = 0;  i < 50;  i++ ) {
	    if ( pass_perp[i] ) charge_perp[i] += track_charge;
	    if ( pass_z[i] ) charge_z[i] += track_charge;
	 }
	 if ( pass_perp_2mm ) charge_perp_2mm += track_charge;
	 if ( pass_perp_4mm ) charge_perp_4mm += track_charge;
	 if ( pass_perp_1cm ) charge_perp_1cm += track_charge;
	 if ( pass_perp_5cm ) charge_perp_5cm += track_charge;
	 if ( pass_z_5mm ) charge_z_5mm += track_charge;
	 if ( pass_z_1cm ) charge_z_1cm += track_charge;

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( tracks.size() > 20 ) {
      m_charge->fill( charge );
      for ( i = 0;  i < 50;  i++ ) {
	 m_charge_perp->fill( float(i+1), charge_perp[i] );
	 m_charge_z->fill( float(i+1), charge_z[i] );
      }
      m_charge_perp_2mm->fill( charge_perp_2mm );
      m_charge_perp_4mm->fill( charge_perp_4mm );
      m_charge_perp_1cm->fill( charge_perp_1cm );
      m_charge_perp_5cm->fill( charge_perp_5cm );
      m_charge_z_5mm->fill( charge_z_5mm );
      m_charge_z_1cm->fill( charge_z_1cm );
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
DirtyCharges::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
DirtyCharges::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

DABoolean DirtyCharges::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
					       KTHelix& a, KTHelix& b )
{
   x = y = z = sig2z = zsep = 1000.;  // To more easily find unchecked failures

   // Express the two helices in terms of (x - xa)^2 + (y - ya)^2 == ra^2
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // Zero or infinitely many solutions
   // I don't want to deal with either case
   if ( xa == xb  &&  ya == yb ) return false;

   double disc( (pow(4.*sqr(ra)*(xa - xb) - 
		     4.*(sqr(rb)*(xa - xb) + 
			(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))
		     ,2.) - 16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		 (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
		  2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
		  2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
		  pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
		  4.*sqr(rb)*sqr(ya - yb)))/
		(64.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   // no real solutions
   if ( disc < 0 ) return false;

   double pre( (sqr(rb)*(xa - xb) + sqr(ra)*(-xa + xb) + 
		(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))/
	       (2.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))) );

   // The two x solutions
   double xsol1( pre + sqrt( disc ) );
   double xsol2( pre - sqrt( disc ) );

   // Two possibilities for the y solution to each x solution
   double ysol1a( yb + sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1b( yb - sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1;
   if ( abs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	abs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( abs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	abs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
      ysol2 = ysol2a;
   else
      ysol2 = ysol2b;

   // Calculate the arclength of each solution along the two tracks.
   // Throw out a solution if the particle needs to travel (too far)
   // backward to get to it. If both solutions are okay, take the one
   // closest to the origin.
   DABoolean arclength1_ok( arclength_test( xsol1, ysol1, a, b ) );
   DABoolean arclength2_ok( arclength_test( xsol2, ysol2, a, b ) );
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;
   }

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;
   }

   else {
      x = xsol2;  y = ysol2;
   }      

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   double az( a.cotTheta() * aarclength + a.z0() );
   double bz( b.cotTheta() * barclength + b.z0() );
   double sig2_az( a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(aarclength)
		   + a.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * aarclength * a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );
   double sig2_bz( b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(barclength)
		   + b.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * barclength * b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );

   z = (az/sig2_az + bz/sig2_bz) / (1./sig2_az + 1./sig2_bz);
   sig2z = 1. / (1./sig2_az + 1./sig2_bz);
   zsep = abs(az - bz) + sqrt(sig2_az) + sqrt(sig2_bz);  // so that uncertain intersections may be ruled out

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

DABoolean DirtyCharges::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   const double tailCut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./abs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./abs(b.curvature()) );
}

//
// const member functions
//

//
// static member functions
//
