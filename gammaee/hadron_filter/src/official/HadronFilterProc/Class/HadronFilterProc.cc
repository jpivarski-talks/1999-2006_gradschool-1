// -*- C++ -*-
//
// Package:     HadronFilterProc
// Module:      HadronFilterProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Oct 16 11:23:37 EDT 2002
// $Id: HadronFilterProc.cc,v 1.3 2002/10/23 21:02:24 mccann Exp $
//
// Revision history
//
// $Log: HadronFilterProc.cc,v $
// Revision 1.3  2002/10/23 21:02:24  mccann
// Added EventProperties to the libarary dependancies so that HadronFilterProc can load by itself.
//
// Revision 1.2  2002/10/23 15:37:47  mccann
// Replaced weighted z0 cut with a weighted z-of-intersection cut, which gains a factor of two in tightness. I also loosened closest_intersection cut because the 3mm vs 5mm gains little hadron/beamgas.
//
// Revision 1.1.1.1  2002/10/16 17:40:04  mccann
// A processor that uses tracking to filter out beam wall/beam gas.
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "HadronFilterProc/HadronFilterProc.h"
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
static const char* const kFacilityString = "Processor.HadronFilterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: HadronFilterProc.cc,v 1.3 2002/10/23 21:02:24 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//



//
// constructors and destructor
//
HadronFilterProc::HadronFilterProc( void )               // anal1
   : Processor( "HadronFilterProc" )
   , m_closestIntersectionCut( "closestIntersectionCut", this, 0.005 )
   , m_weightedZ0Cut( "weightedZ0Cut", this, 0.10 )
   , m_neutralEnergyCut( "neutralEnergyCut", this, 0.01 )
   , m_weightedCIZCut( "weightedCIZCut", this, 0.05 )
   , m_explicitBeamSpot( "explicitBeamSpot", this, false )
   , m_beamX( "beamX", this, 0. )
   , m_beamY( "beamY", this, 0. )
   , m_beamZ( "beamZ", this, 0. )
   , m_passed(0)
   , m_total(0)
   , m_beam_x(0.)
   , m_beam_y(0.)
   , m_beam_z(0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &HadronFilterProc::event,    Stream::kEvent );
   bind( &HadronFilterProc::beginRun, Stream::kBeginRun );
   //bind( &HadronFilterProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

HadronFilterProc::~HadronFilterProc()                    // anal5
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
HadronFilterProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
HadronFilterProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   report( SYSTEM, kFacilityString )
      << "Passed " << m_passed << " out of " << m_total
      << " which is " << double(m_passed)/double(m_total)*100 << "%." << endl;
}


// ---------------- standard place to book histograms ---------------
void
HadronFilterProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   char closest_inter_cut[1024];
   char weighted_z0_cut[1024];
   char neutral_energy_cut[1024];
   char weighted_ciz_cut[1024];

   sprintf( closest_inter_cut, "%g", m_closestIntersectionCut.value() );
   sprintf( weighted_z0_cut, "%g", m_weightedZ0Cut.value() );
   sprintf( neutral_energy_cut, "%g", m_neutralEnergyCut.value() );
   sprintf( weighted_ciz_cut, "%g", m_weightedCIZCut.value() );

   m_hist_closest_inter = iHistoManager.histogram(
      100, (string("Closest intersection (cut at ") + string(closest_inter_cut) + string(")")).c_str(),
      100, 0., 0.10 );
   m_histclose_closest_inter = iHistoManager.histogram(
      101, (string("Closest intersection (cut at ") + string(closest_inter_cut) + string(")")).c_str(),
      100, 0., 0.005 );
   m_hist_weighted_z0 = iHistoManager.histogram(
      200, (string("Weighed Z0 (cut at ") + string(weighted_z0_cut) + string(")")).c_str(),
      100, -1., 1. );
   m_histclose_weighted_z0 = iHistoManager.histogram(
      201, (string("Weighed Z0 (cut at ") + string(weighted_z0_cut) + string(")")).c_str(),
      100, -0.10, 0.10 );
   m_hist_neutral_energy = iHistoManager.histogram(
      300, (string("Neutral Energy (cut at ") + string(neutral_energy_cut) + string(")")).c_str(),
      100, 0., 6. );
   m_histclose_neutral_energy = iHistoManager.histogram(
      301, (string("Neutral Energy (cut at ") + string(neutral_energy_cut) + string(")")).c_str(),
      100, 0., 0.100 );
   m_hist_weighted_ciz = iHistoManager.histogram(
      400, (string("Weighted CI Z (cut at ") + string(weighted_ciz_cut) + string(")")).c_str(),
      100, -1., 1. );
   m_histclose_weighted_ciz = iHistoManager.histogram(
      401, (string("Weighted CI Z (cut at ") + string(weighted_ciz_cut) + string(")")).c_str(),
      100, -0.10, 0.10 );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
HadronFilterProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< DBEventHeader > header;
   extract( iFrame.record( Stream::kEvent ), header );

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double ci_perp(1000.);

   double weighted_ciz(1000.);
   double ciznumer(0.);
   double cizdenom(0.);

   double weighted_z0(1000.);
   double znumer(0.);
   double zdenom(0.);

   int num_tracks(0.);

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
		  if ( perp < ci_perp ) ci_perp = perp;

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - m_beam_x) + sqr(ty - m_beam_y) );
		  ciznumer += tz / z_uncert2;
		  cizdenom += 1. / z_uncert2;

	       } // end if successful intersection
	       num_tracks++;
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

	 // Calculate the weighted z0
	 double z0err2( track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );
	 
	 znumer += track_iter->pionHelix()->z0() / z0err2;
	 zdenom += 1. / z0err2;
	 
      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( cizdenom != 0. ) weighted_ciz = ciznumer / cizdenom;

   if ( zdenom != 0. ) weighted_z0 = znumer / zdenom;

   m_total++;
   if ( m_total % 100 == 0 ) {
      report( INFO, kFacilityString )
	 << "Passed " << m_passed << " out of " << m_total
	 << " which is " << double(m_passed)/double(m_total)*100 << "%." << endl;
   }

   // Real, current cuts
   DABoolean passed_num_tracks( num_tracks > 2 );
   DABoolean passed_closest_inter( ci_perp < m_closestIntersectionCut.value() );
   DABoolean passed_weighted_ciz( abs( weighted_ciz - m_beam_z ) < m_weightedCIZCut.value() );
   DABoolean passed_neutral_energy( props->neutralEnergy() > m_neutralEnergyCut.value() );

   // Old cuts
   DABoolean passed_weighted_z0( abs( weighted_z0 - m_beam_z ) < m_weightedZ0Cut.value() );

   // Fill histograms
   if ( passed_num_tracks && true                 && passed_weighted_ciz && passed_neutral_energy ) {
      m_hist_closest_inter->fill( ci_perp );
      m_histclose_closest_inter->fill( ci_perp );
   }
   if ( passed_num_tracks && passed_closest_inter && true                && passed_neutral_energy ) {
      m_hist_weighted_z0->fill( weighted_z0 );
      m_histclose_weighted_z0->fill( weighted_z0 );
   }
   if ( passed_num_tracks && passed_closest_inter && passed_weighted_ciz && true                  ) {
      m_hist_neutral_energy->fill( props->neutralEnergy() );
      m_histclose_neutral_energy->fill( props->neutralEnergy() );
   }
   if ( passed_num_tracks && passed_closest_inter && true                && passed_neutral_energy ) {
      m_hist_weighted_ciz->fill( weighted_ciz );
      m_histclose_weighted_ciz->fill( weighted_ciz );
   }

//   if ( passed_num_tracks && passed_closest_inter && passed_weighted_ciz && passed_neutral_energy ) {
   if ( passed_num_tracks && passed_closest_inter && passed_weighted_ciz ) {
      m_passed++;
      return ActionBase::kPassed;
   } else {
      report( DEBUG, kFacilityString )
	 << "FAILED event; (num_tracks, closest_inter, weighted_ciz, "
	 << "weighted_z0, neutral_energy) = "
	 << num_tracks << " " << ci_perp << " " << weighted_ciz << " "
	 << weighted_z0 << " " << props->neutralEnergy() << endl;
      return ActionBase::kFailed;
   }
}

ActionBase::ActionResult
HadronFilterProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   if ( m_explicitBeamSpot.value() ) {
      m_beam_x = m_beamX.value();
      m_beam_y = m_beamY.value();
      m_beam_z = m_beamZ.value();
   }
   else {
      FAItem< BeamSpot > spot;
      extract( iFrame.record( Stream::kBeginRun ), spot );
      m_beam_x = spot->center().x();
      m_beam_y = spot->center().y();
      m_beam_z = spot->center().z();
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
HadronFilterProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

DABoolean HadronFilterProc::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean HadronFilterProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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
