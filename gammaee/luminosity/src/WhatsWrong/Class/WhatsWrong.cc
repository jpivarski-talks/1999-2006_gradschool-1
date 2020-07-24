// -*- C++ -*-
//
// Package:     WhatsWrong
// Module:      WhatsWrong
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Apr 19 10:04:15 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "WhatsWrong/WhatsWrong.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "TriggerL1Data/TriggerL1Data.h"
#include "Level3TagWord/Level3TagWord.h"
#include "Level4Proc/Level4Decision.h"
#include "Level4Proc/Level4DecisionProxy.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "MagField/MagneticField.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"
#include "CleoDB/DBEventHeader.h"
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcShowerAttributes.h"


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
static const char* const kFacilityString = "Processor.WhatsWrong" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
WhatsWrong::WhatsWrong( void )               // anal1
   : Processor( "WhatsWrong" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &WhatsWrong::event,    Stream::kEvent );
   //bind( &WhatsWrong::beginRun, Stream::kBeginRun );
   //bind( &WhatsWrong::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

WhatsWrong::~WhatsWrong()                    // anal5
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
WhatsWrong::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
WhatsWrong::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
WhatsWrong::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* label[kNumEntries] = {
//       "t1had", "t1rad", "t1el", "t1bb",
//       "d0close", "e1", "p2", "wz", "z0close",
//       "visen", "tracks", "l4dec", "ccen", "ebeam",
//       "etwo", "westphi", "eastphi", "cott", "westcot",
//      "tfit", "tchi", "thit", "td0", "tz0", "tp", "tcot", "tert", "terz",
//      "shot", "senergy", "stheta", "sphi"
      "t1had", "t1rad", "t1el", "t1bb",
      "d0close", "z0close", "wz",
      "e1", "e2", "u1", "p1", "p2", "pmiss", "pemiss",
      "visen", "cvisen", "tracks", "l4dec", "ccen", "ebeam",
      "westphi", "eastphi", "cott", "westcot",
      "fvisen", "fccen", "fe1"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);

//    const char* label2[kNumEntries2] = {
//       "shot", "senergy", "stheta", "sphi"
//    };
//    m_ntuple2 = iHistoManager.ntuple(
//       2, "vars", kNumEntries2, 262144, label2);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
WhatsWrong::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;
   FAItem<TriggerL1Data> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   v[k_t1had] = trig->isHadron();
   v[k_t1rad] = trig->isRadTau();
   v[k_t1el] = trig->isElTrack();
   v[k_t1bb] = trig->isBarrelBhabha();

   v[k_p1] = props->firstLargestPTrack() / eBeam->value();
   v[k_p2] = props->secondLargestPTrack() / eBeam->value();

   v[k_visen] = (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value();
   v[k_tracks] = props->nbChargedTracks();
   v[k_l4dec] = l4dec->decision();
   v[k_ccen] = props->ccTotalEnergy() / 2. / eBeam->value();
   v[k_ebeam] = eBeam->value();

   v[k_d0close] = 1000.;
   v[k_z0close] = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(spot->center(),
				     distance_moved,
				     KTMoveControl::kDirectionEither);
      if (fabs(movetrack.d0()) < fabs(v[k_d0close])) v[k_d0close] = movetrack.d0();
      if (fabs(movetrack.z0()) < fabs(v[k_z0close])) v[k_z0close] = movetrack.z0();

      if (! track_iter->seedQuality()->originUsed()            &&
	  ! track_iter->pionQuality()->fitAbort()              &&
	  1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	  ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {

	 // Secondary track loop to calculate pairwise intersections
	 for (other_iter = track_iter;  other_iter != tracks_end;  ++other_iter) {
	    if (other_iter != track_iter  &&
		! other_iter->seedQuality()->originUsed()            &&
		! other_iter->pionQuality()->fitAbort()              &&
		1./fabs(other_iter->pionHelix()->curvature()) > 0.42  &&
		! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 

	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
	       KTHelix track(*track_iter->pionHelix());
	       KTHelix other(*other_iter->pionHelix());
	       if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
		  double perp(sqrt(sqr(tx - spot->center().x()) + sqr(ty - spot->center().y())));
		  double z_uncert2(tsig2z + sqr(tzsep) +
				   sqr(tx - spot->center().x()) +
				   sqr(ty - spot->center().y()));

		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if (zdenom != 0.) {
      v[k_wz] = znumer / zdenom;
      v[k_wz] -= spot->center().z();
   }   

   v[k_cvisen] = props->chargedEnergy();
   v[k_fvisen] = props->chargedEnergy();

   FATable<NavShower>::const_iterator showers_end, one, two, unmatched;
   showers_end = one = two = unmatched = showers.end();
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()    &&
	  shower_iter->attributes().status()  &&
	  shower_iter->attributes().energy()/eBeam->value() > 0.01) {
	 if (one == showers_end  ||  shower_iter->attributes().energy() > one->attributes().energy()) {
	    two = one;
	    one = shower_iter;
	 }
	 else if (two == showers_end  ||  shower_iter->attributes().energy() > two->attributes().energy()) {
	    two = shower_iter;
	 }

	 if( shower_iter->noTrackMatch()       && 
	     shower_iter->noTrackMatchConReg() &&
	     ( !shower_iter->bremTrack().valid() ||
	       ( shower_iter->bremTrack()->trackShowerMatch().valid() &&
		 shower_iter->bremTrack()->trackShowerMatch()->eOverP()<0.5 ))) {
	    v[k_cvisen] += shower_iter->attributes().energy();

	    if (unmatched == showers_end  ||  unmatched->attributes().energy() < shower_iter->attributes().energy()) {
	       unmatched = shower_iter;
	    }

	    if (!(cos(shower_iter->attributes().theta()) > 0.8  &&
		  atan2(sin(shower_iter->attributes().phi()), cos(shower_iter->attributes().phi())) > 1.5)) {
	       v[k_fvisen] += shower_iter->attributes().energy();
	    }

	 }
      }
   }
   v[k_cvisen] /= 2. * eBeam->value();
   v[k_fvisen] /= 2. * eBeam->value();

   v[k_fccen] = 0.;
   v[k_fe1] = 0.;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
      if (shower_iter->attributes().status()  &&
	  shower_iter->attributes().energy()/eBeam->value() > 0.01) {
	 if (!(cos(shower_iter->attributes().theta()) > 0.8  &&
	       atan2(sin(shower_iter->attributes().phi()), cos(shower_iter->attributes().phi())) > 1.5)) {
	    v[k_fccen] += shower_iter->attributes().energy();

	    if (v[k_fe1] < shower_iter->attributes().energy()) {
	       v[k_fe1] = shower_iter->attributes().energy();
	    }
	 }
      }
   }
   v[k_fccen] /= 2. * eBeam->value();
   v[k_fe1] /= eBeam->value();

   if (v[k_cvisen] > v[k_visen] + 0.00001) report(SYSTEM, kFacilityString)
      << "Ack! " << v[k_cvisen] << " " << v[k_visen] << endl;
   
   if (one != showers_end) v[k_e1] = one->attributes().energy() / eBeam->value();
   if (two != showers_end) v[k_e2] = two->attributes().energy() / eBeam->value();
   if (unmatched != showers_end) v[k_u1] = unmatched->attributes().energy() / eBeam->value();

   FATable<NavTrack>::const_iterator tone = tracks.find(props->firstTrackIdentifier());
   FATable<NavTrack>::const_iterator ttwo = tracks.find(props->secondTrackIdentifier());
   if (tone != tracks_end  &&  ttwo != tracks_end) {
      v[k_pmiss] = (tone->pionFit()->momentum() + ttwo->pionFit()->momentum()).mag() / eBeam->value();
   }
   if (tone != tracks_end  &&  ttwo != tracks_end  &&  unmatched != showers_end) {
      v[k_pemiss] = (tone->pionFit()->momentum() + ttwo->pionFit()->momentum() + unmatched->attributes().momentum()).mag() / eBeam->value();
   }

   if (one != showers_end  &&  two != showers_end  &&
       cos(one->attributes().theta())*cos(two->attributes().theta()) <= 0.) {
      FATable<NavShower>::const_iterator west = (cos(one->attributes().theta()) > 0. ? one : two);
      FATable<NavShower>::const_iterator east = (cos(one->attributes().theta()) > 0. ? two : one);
   
      double westphi, eastphi, westcotT, eastcotT;
      if (true) {
	 double d = west->attributes().distance();
	 double th = west->attributes().theta();
	 double ph = west->attributes().phi();
	 westphi = atan2(d*sin(th)*sin(ph) - spot->center().y(),
			 d*sin(th)*cos(ph) - spot->center().x());
	 westcotT = (d*cos(th) - spot->center().z()) /
	    sqrt(sqr(d*sin(th)*cos(ph) - spot->center().x()) +
		 sqr(d*sin(th)*sin(ph) - spot->center().y()));
      }
      if (true) {
	 double d = east->attributes().distance();
	 double th = east->attributes().theta();
	 double ph = east->attributes().phi();
	 eastphi = atan2(d*sin(th)*sin(ph) - spot->center().y(),
			 d*sin(th)*cos(ph) - spot->center().x());
	 eastcotT = (d*cos(th) - spot->center().z()) /
	    sqrt(sqr(d*sin(th)*cos(ph) - spot->center().x()) +
		 sqr(d*sin(th)*sin(ph) - spot->center().y()));
      }
      double cotT = (westcotT - eastcotT)/2.;

      v[k_westphi] = westphi;
      v[k_eastphi] = eastphi;
      v[k_cott] = cotT;
      v[k_westcot] = westcotT;
   }

//    track_iter = tracks.find(props->secondTrackIdentifier());
//    if (props->secondTrackIdentifier() != 0  &&  track_iter != tracks_end) {
//    for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
//       float v[kNumEntries];
//       for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

//       FAItem< TRTrackFitQuality > pionQuality( track_iter->pionQuality() );

//       const DABoolean trackFitOK ( pionQuality->fit()       &&
// 				   !pionQuality->fitAbort()     );

//       const double dof         ( pionQuality->degreesOfFreedom() ) ;
//       const double reducedChi2 ( dof > 0 ? pionQuality->chiSquare()/dof : 0 ) ;

//       const double hitFraction ( pionQuality->numberHitsExpected() > 0 ? 
// 				 pionQuality->ratioNumberHitsToExpected() : 0 );

//       // Particle kinematic parameters
//       FAItem< TDKinematicFit > pion ( track_iter->pionFit() ) ;

//       GeV          pTk ( pion->momentum().mag() ) ; // track momentum
//       const int    qTk ( pion->charge()<0 ? ceil( pion->charge() - 0.5 ) :
// 			 floor( pion->charge() + 0.5 ) ) ; // electric charge

//       // Energy of matched shower
//       const GeV eTk ( track_iter->trackShowerMatch().valid() ?
// 		      track_iter->trackShowerMatch()->matchedEnergy() : 0 ) ;

//       // Helix parameters
//       FAItem< TRHelixFit > helix ( track_iter->pionHelix() ) ;

//       const double adacd       ( fabs( helix->d0() ) ) ;
//       const double az0         ( fabs( helix->position().z() ) ) ;
//       const double phi0        ( helix->phi0() ) ;
//       const double aCotTheta   ( fabs( helix->cotTheta() ) ) ;
//       const double errCotTheta ( sqrt( fabs(
// 	 helix->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta ) ) ) ) ;
//       const double errz0       ( sqrt( fabs(
// 	 helix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) ) ) ) ;

//       // Apply (loose) track selection criteria
//       const DABoolean thisTrackIsGood ( trackFitOK
// 					&& reducedChi2 < 100.0
// 					&& hitFraction > 0.5
// 					&& hitFraction < 1.2
// 					&& adacd       < 0.03
// 					&& az0         < 0.18
// 					&& pTk         > 0.01*eBeam->value()
// 					&& pTk         < 1.500*eBeam->value()
// 					&& aCotTheta   < 3.0424 // |cosTh|<0.95
// 					&& errCotTheta < 0.5
// 					&& errz0       < 0.25 ) ;

//       v[k_tfit] = trackFitOK;
//       v[k_tchi] = reducedChi2;
//       v[k_thit] = hitFraction;
//       v[k_td0]  = adacd;
//       v[k_tz0]  = az0;
//       v[k_tp]   = pTk;
//       v[k_tcot] = aCotTheta;
//       v[k_tert] = errCotTheta;
//       v[k_terz] = errz0;

//       m_ntuple->fill(v);
//    }

// //    FATable<NavShower>::const_iterator shower_iter = showers.find(props->firstShowerIdentifier());
// //    if (props->firstShowerIdentifier() != 0  &&  shower_iter != showers_end) {
//    for(FATable<NavShower>::const_iterator shower_iter = showers.begin();
//        shower_iter != showers.end();
//        ++shower_iter) {
//       float v[kNumEntries2];
//       for (int i = 0;  i < kNumEntries2;  i++) v[i] = -1000.;

//       v[k_shot] = shower_iter->attributes().hot();
//       v[k_senergy] = shower_iter->attributes().energy();
//       v[k_stheta] = shower_iter->attributes().theta();
//       v[k_sphi] = shower_iter->attributes().phi();

//       m_ntuple2->fill(v);
//    }

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
WhatsWrong::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
WhatsWrong::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//

DABoolean WhatsWrong::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
				      KTHelix& a, KTHelix& b)
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
   if ( fabs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	fabs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( fabs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	fabs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
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
   zsep = az - bz;

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

DABoolean WhatsWrong::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./fabs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./fabs(b.curvature()) );
}
