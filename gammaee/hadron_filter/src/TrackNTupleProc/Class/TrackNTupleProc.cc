// -*- C++ -*-
//
// Package:     TrackNTupleProc
// Module:      TrackNTupleProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Oct 21 10:30:06 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TrackNTupleProc/TrackNTupleProc.h"
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

#include "EventProperties/EventProperties.h"
#include "TrackRoot/TRSubdetectorLists.h"

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
static const char* const kFacilityString = "Processor.TrackNTupleProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TrackNTupleProc::TrackNTupleProc( void )               // anal1
   : Processor( "TrackNTupleProc" )
   , m_beam_x( "beamX", this, -1e-3 )
   , m_beam_y( "beamY", this, 6e-4 )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TrackNTupleProc::event,    Stream::kEvent );
   //bind( &TrackNTupleProc::beginRun, Stream::kBeginRun );
   //bind( &TrackNTupleProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TrackNTupleProc::~TrackNTupleProc()                    // anal5
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
TrackNTupleProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TrackNTupleProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TrackNTupleProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* track_label[kTrackVars] = {
      "curv", "phi0", "d0", "cotTh", "z0",
      "pperp", "pz",
      "chi2", "dof", "hitf", "hitexp", "fitab",
      "avax", "avst", "rmsax", "rmsst",
      "ev_mul", "ev_char", "ev_neue", "ev_ci", "ev_wz0", "ev_wciz",
   };

   m_track = iHistoManager.ntuple(
      1, "track", kTrackVars, 262144, track_label );

   const char* event_label[kEventVars] = {
      "ntr", "char", "neue",
      "pos_ab", "neg_ab",
      "ci", "wz0", "wciz",
      "p_all", "n_all", "p_z0", "n_z0", "p_d0", "n_d0", "p_tm", "n_tm"
   };
   m_event = iHistoManager.ntuple(
      2, "event", kEventVars, 262144, event_label );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TrackNTupleProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_begin = tracks.begin();
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();
   FATable< NavTrack >::const_iterator track_iter;

   float ve[kEventVars];  for ( int i = 0;  i < kEventVars;  i++ ) ve[i] = 0;
   for ( track_iter = tracks_begin;
         track_iter != tracks_end;
         track_iter++ ) {
      DABoolean positive( track_iter->pionHelix()->curvature() > 0. );

      ve[kNumTracks]++;
      ve[kCharge] += ( positive ? 1. : -1. );
      if ( track_iter->pionQuality()->fitAbort() ) {
	 if ( positive ) ve[kPosAborts]++;
	 else ve[kNegAborts]++;
      }
      ve[kClosestIntersection] = get_closest_intersection( iFrame );
      ve[kWeightedZ0] = get_weighted_z0( iFrame );
      ve[kWeightedCIZ] = get_weighted_ciz( iFrame );

   }
   ve[kNeutralEnergy] = props->neutralEnergy();

   for ( track_iter = tracks_begin;
         track_iter != tracks_end;
         track_iter++ ) {
      float vt[kTrackVars];  for ( int j = 0;  j < kTrackVars;  j++ ) vt[j] = 0.;

      KTHelix tmpHelix( *track_iter->pionHelix() );
      double distanceMoved;
      tmpHelix.moveToReferencePoint(
	 HepPoint3D( m_beam_x.value(), m_beam_y.value(), 0. ), distanceMoved );

      vt[kCurvature] = tmpHelix.curvature();
      vt[kPhi0] = tmpHelix.phi0();
      vt[kD0] = tmpHelix.d0();
      vt[kCotTheta] = tmpHelix.cotTheta();
      vt[kZ0] = tmpHelix.z0();

      vt[kPPerp] = track_iter->pionFit()->momentum().perp();
      vt[kPz] = track_iter->pionFit()->momentum().z();

      vt[kChi2] = track_iter->pionQuality()->chiSquare();
      vt[kDOF] = float(track_iter->pionQuality()->degreesOfFreedom());
      vt[kHitFraction] = track_iter->pionQuality()->ratioNumberHitsToExpected();
      if ( vt[kHitFraction] > 1000. ) vt[kHitFraction] = 1000.;
      vt[kHitsExpected] = track_iter->pionQuality()->numberHitsExpected();

      vt[kAverageAxResidual] = track_iter->pionQuality()->averageResidual(
	 TRSubdetectorLists::kDR3Axial );
      vt[kAverageStResidual] = track_iter->pionQuality()->averageResidual(
	 TRSubdetectorLists::kDR3Stereo );
      vt[kRMSAxResidual] = track_iter->pionQuality()->rmsResidual(
	 TRSubdetectorLists::kDR3Axial );
      vt[kRMSStResidual] = track_iter->pionQuality()->rmsResidual(
	 TRSubdetectorLists::kDR3Stereo );

      vt[kFitAbort] = track_iter->pionQuality()->fitAbort();

      vt[kEventMultiplicity] = ve[kNumTracks];
      vt[kEventCharge] = ve[kCharge];
      vt[kEventNeutralEnergy] = ve[kNeutralEnergy];
      vt[kEventClosestIntersection] = ve[kClosestIntersection];
      vt[kEventWeightedZ0] = ve[kWeightedZ0];
      vt[kEventWeightedCIZ] = ve[kWeightedCIZ];

      m_track->fill(vt);

      if ( track_iter->pionHelix()->curvature() > 0. ) {
	 ve[kPosTracks]++;
	 if ( abs( track_iter->pionHelix()->z0() ) < 0.9 ) ve[kPosGoodZ0Tracks]++;
	 if ( abs( tmpHelix.d0() ) < 0.01 ) ve[kPosGoodD0Tracks]++;
      }
      else {
	 ve[kNegTracks]++;
	 if ( abs( track_iter->pionHelix()->z0() ) < 0.9 ) ve[kNegGoodZ0Tracks]++;
	 if ( abs( tmpHelix.d0() ) < 0.01 ) ve[kNegGoodD0Tracks]++;
      } // end if track is positive/negative
   } // end loop over tracks

   FATable< NavTrack > trkman_tracks;
   extract( iFrame.record( Stream::kEvent ), trkman_tracks, "TrkmanApproved" );
   FATable< NavTrack >::const_iterator trkman_tracks_begin = trkman_tracks.begin();
   FATable< NavTrack >::const_iterator trkman_tracks_end = trkman_tracks.end();
   FATable< NavTrack >::const_iterator trkman_track_iter;

   for ( trkman_track_iter = trkman_tracks_begin;
         trkman_track_iter != trkman_tracks_end;
         trkman_track_iter++ ) {
      if ( trkman_track_iter->pionHelix()->curvature() > 0. )
	 ve[kPosTrkManTracks]++;
      else
	 ve[kNegTrkManTracks]++;

   } // end loop over trkman tracks

   m_event->fill(ve);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TrackNTupleProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TrackNTupleProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

double TrackNTupleProc::get_weighted_z0( Frame& iFrame )
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double weighted_z0(1000.);
   double znumer(0.);
   double zdenom(0.);

   vector< KTHelix* > intersecting_helices;
   FATable< NavTrack >::const_iterator track_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      // Quality cuts for weighted z0 determination
      if ( ! track_iter->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! track_iter->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&  // - Diameter must be greater than 42 cm
                                                                    //   to guarantee that it pokes through
                                                                    //   the first stereo superlayer
	   ! track_iter->pionHelix()->hasNullErrorMatrix()          // - I want an error matrix for
                                                                    //   weighted means
	 ) {
	 double z0err2( track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );

	 znumer += track_iter->pionHelix()->z0() / z0err2;
	 zdenom += 1. / z0err2;
      } // end passes weighted z0 track cuts
   } // end loop over tracks

   if ( zdenom != 0. )
      weighted_z0 = znumer / zdenom;

   return weighted_z0;
}

double TrackNTupleProc::get_closest_intersection( Frame& iFrame )
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double closest_inter(1000.);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ )
      for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ )
	 if ( other_iter != track_iter  &&
	      (! track_iter->pionQuality()->fitAbort())  &&
	      (! other_iter->pionQuality()->fitAbort()) ) {
	    double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
	    if ( calc_intersection( tx, ty, tz, tsig2z, tzsep,
				    *track_iter->pionHelix(),
				    *other_iter->pionHelix() ) ) {
	       
	       double perp( sqrt(sqr(tx - m_beam_x.value()) + sqr(ty - m_beam_y.value())) );
	       if ( perp < closest_inter ) closest_inter = perp;

	    } // end if successful intersection
	 } // end cuts on track_iter and other_iter

   return closest_inter;
}

double TrackNTupleProc::get_weighted_ciz( Frame& iFrame )
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double weighted_ciz(1000.);
   double ciznumer(0.);
   double cizdenom(0.);

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
	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep,
				       *track_iter->pionHelix(),
				       *other_iter->pionHelix() ) ) {

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) +
				    sqr(tx - m_beam_x.value()) +
				    sqr(ty - m_beam_y.value()) );
		  ciznumer += tz / z_uncert2;
		  cizdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track
      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( cizdenom != 0. ) weighted_ciz = ciznumer / cizdenom;

   return weighted_ciz;
}

DABoolean TrackNTupleProc::calc_intersection(
   double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean TrackNTupleProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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
