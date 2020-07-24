// -*- C++ -*-
//
// Package:     CountEvents
// Module:      CountEvents
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Jul 14 16:37:23 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CountEvents/CountEvents.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"


#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCTrackTagger/MCTrackTagsByMCParticle.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level3TagWord/Level3TagWord.h"
#include "Level4Proc/Level4Decision.h"
#include "BeamEnergy/BeamEnergy.h"
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
#include "BeamSpot/BeamSpot.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "Level4Proc/Level4DecisionProxy.h"
#include "TriggerInfoProd/TriggerInfo.h"
#include "MagField/MagneticField.h"
#include "CleoDB/DBEventHeader.h"



// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
// #include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.CountEvents" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
CountEvents::CountEvents( void )               // anal1
   : Processor( "CountEvents" )
   , m_run("run", this, 0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CountEvents::event,    Stream::kEvent );
   //bind( &CountEvents::beginRun, Stream::kBeginRun );
   //bind( &CountEvents::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_goodEvents = 0;
   m_cosmicEvents = 0;
   m_bgpEvents = 0;
   m_bgeEvents = 0;

}

CountEvents::~CountEvents()                    // anal5
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
CountEvents::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

   m_goodEvents = 0;
   m_cosmicEvents = 0;
   m_bgpEvents = 0;
   m_bgeEvents = 0;
}

// -------------------- terminate method ----------------------------
void
CountEvents::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   report(SYSTEM, kFacilityString)
      << "goodEvents " << m_goodEvents
      << " cosmicEvents " << m_cosmicEvents
      << " bgpEvents " << m_bgpEvents
      << " bgeEvents " << m_bgeEvents << endl;
}


// ---------------- standard place to book histograms ---------------
void
CountEvents::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   char title[200];

   sprintf(title, "%d closest track d0", m_run.value());
   m_d0close = iHistoManager.histogram(100, title, 200, -0.01, 0.01);

   sprintf(title, "%d biggest shower", m_run.value());
   m_e1 = iHistoManager.histogram(200, title, 50, 0., 1.25);

   sprintf(title, "%d second-biggest track", m_run.value());
   m_p2 = iHistoManager.histogram(300, title, 50, 0., 1.25);

   sprintf(title, "%d event vertex Z", m_run.value());
   m_wz = iHistoManager.histogram(400, title, 160, -0.3, 0.3);

   sprintf(title, "%d closest track z0 for one-track events", m_run.value());
   m_z0close = iHistoManager.histogram(500, title, 160, -0.3, 0.3);

   sprintf(title, "%d visible energy", m_run.value());
   m_visen = iHistoManager.histogram(600, title, 50, 0., 1.25);

   sprintf(title, "%d number of quality tracks", m_run.value());
   m_tracks = iHistoManager.histogram(700, title, 19, -0.5, 18.5);

   sprintf(title, "%d CC total energy", m_run.value());
   m_ccen = iHistoManager.histogram(800, title, 50, 0., 1.25);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CountEvents::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);
   assert(head->run() == m_run.value());

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);
   bool passTrig = (triggerDecision->isHadron()  ||
		    triggerDecision->isRadTau()  ||
		    triggerDecision->isElTrack()    );
   report(DEBUG, kFacilityString)
      << "isHadron? " << (triggerDecision->isHadron() ? "yes" : "no") << " "
      << "isRadTau? " << (triggerDecision->isRadTau() ? "yes" : "no") << " "
      << "isElTrack? " << (triggerDecision->isElTrack() ? "yes" : "no") << endl;
   if (!passTrig) return ActionBase::kFailed;
   report(DEBUG, kFacilityString)
      << "L4decision " << l4dec->decision() << endl;
   bool passL4 = l4dec->decision() > 0;
   if (!passL4) return ActionBase::kFailed;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);
   report(DEBUG, kFacilityString)
      << "eBeam " << eBeam->value() << endl;
   double p2 = props->secondLargestPTrack() / eBeam->value();
   double e1 = props->firstLargestEShower() / eBeam->value();
   double visen = (props->neutralEnergy() + props->chargedEnergy()) / 2. / eBeam->value();
   double ccen = props->ccTotalEnergy() / 2. / eBeam->value();
   double ntracks = double(props->nbChargedTracks());

   report(DEBUG, kFacilityString)
      << "p2 " << p2 << " e1 " << e1 << " visen " << visen << " ccen " << ccen << " ntracks " << ntracks << endl;

   if (p2 >= 0.85) {
      report(WARNING, kFacilityString) << "p2 = " << p2 << endl;
      return ActionBase::kFailed;
   }
   if (e1 >= 0.85) {
      report(WARNING, kFacilityString) << "e1 = " << e1 << endl;
      return ActionBase::kFailed;
   }
   if (visen <= 0.20) {
      report(WARNING, kFacilityString) << "visen = " << visen << endl;
      return ActionBase::kFailed;
   }
   if (ccen >= 0.85) {
      report(WARNING, kFacilityString) << "ccen = " << ccen << endl;
      return ActionBase::kFailed;
   }
   if (ntracks <= 1) {
      report(WARNING, kFacilityString) << "ntracks = " << ntracks << endl;
      return ActionBase::kFailed;
   }
   assert(p2 < 0.85);
   assert(e1 < 0.85);
   assert(visen > 0.20);
   assert(ccen < 0.85);
   assert(ntracks > 1);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   double d0close = 1000.;
   double z0close = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
   double wpz = 0.;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(spot->center(),
				     distance_moved,
				     KTMoveControl::kDirectionEither);
      if (fabs(movetrack.d0()) < fabs(d0close)) d0close = movetrack.d0();
      if (fabs(movetrack.z0()) < fabs(z0close)) z0close = movetrack.z0();

      if (! track_iter->seedQuality()->originUsed()            &&
	  ! track_iter->pionQuality()->fitAbort()              &&
	  1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	  ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {

	 if (sqrt(fabs(track_iter->pionFit()->errorMatrix()(
			  KTKinematicData::kPz, KTKinematicData::kPz))) < 1.) {
	    wpz += track_iter->pionFit()->pz();
	 }

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

   double wz = 1000.;
   if (zdenom != 0.) {
      wz = znumer / zdenom;
      wz -= spot->center().z();
   }   

   report(DEBUG, kFacilityString)
      << "d0close " << d0close << " z0close " << z0close << " wz " << wz << endl;

   double trperp1 = 1000.;
   if (0.075 < abs(wz) < 0.4) {
      FATable<NavTrack>::const_iterator track1(tracks_end), track2(tracks_end);
      if (props->nbChargedTracks() >= 2  &&  props->firstTrackIdentifier() != 0  &&  props->secondTrackIdentifier() != 0) {
	 track1 = tracks.find(props->firstTrackIdentifier());
	 track2 = tracks.find(props->secondTrackIdentifier());
      }
      else if (tracks.size() >= 2) {
	 double firstp(0.), secondp(0.);
	 for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
	    double thisp = track_iter->pionFit()->momentum().mag();
	    if (thisp > firstp) {
	       secondp = firstp;
	       track2 = track1;

	       firstp = thisp;
	       track1 = track_iter;
	    }
	    else if (thisp > secondp) {
	       secondp = thisp;
	       track2 = track_iter;
	    }
	 }
      }
      if (track1 != tracks_end  &&  track2 != tracks_end) {
	 double phi1 = track1->pionHelix()->phi0();
	 double phi2 = track2->pionHelix()->phi0();
	 trperp1 = cos(phi1)*cos(phi2) + sin(phi1)*sin(phi2);
      }
   }

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end(showers.end());
   double accen = 0.;
   for( FATable< NavShower >::const_iterator showerItr ( showers.begin() ) ; 
	showerItr != showers_end ; ++showerItr ) 
   { 
      const GeV showerEnergy ( showerItr->attributes().energy() ) ;
      const UInt32 showerID ( showerItr->identifier() ) ;
      const double absCosTheta ( fabs(cos(showerItr->attributes().theta())) );
      if( showerEnergy > 0.01*eBeam->value()         &&
	  showerItr->attributes().status()     ) 
      {
	 if (!showerItr->attributes().hot()            &&
	     showerItr->attributes().bigCellId() != 314   &&
	     showerItr->attributes().bigCellId() != 344   &&
	     showerItr->attributes().bigCellId() != 427   &&
	     showerItr->attributes().bigCellId() != 459   &&
	     showerItr->attributes().bigCellId() != 460   &&
	     showerItr->attributes().bigCellId() != 551   &&
	     showerItr->attributes().bigCellId() != 553   &&
	     showerItr->attributes().bigCellId() != 555   &&
	     showerItr->attributes().bigCellId() != 576   &&
	     showerItr->attributes().bigCellId() != 591   &&
	     showerItr->attributes().bigCellId() != 650   &&
	     showerItr->attributes().bigCellId() != 672   &&
	     showerItr->attributes().bigCellId() != 688   &&
	     showerItr->attributes().bigCellId() != 6990  &&
	     showerItr->attributes().bigCellId() != 6997  &&
	     showerItr->attributes().bigCellId() != 7033  &&
	     showerItr->attributes().bigCellId() != 7034  &&
	     showerItr->attributes().bigCellId() != 7097  &&
	     showerItr->attributes().bigCellId() != 7098  &&
	     showerItr->attributes().bigCellId() != 7657     ) {
	    if (!showerItr->noTrackMatch()  ||  
		!((absCosTheta > 0.84  &&  showerEnergy < 0.06)  ||
		  (absCosTheta > 0.4   &&  showerEnergy < 0.03)    ))
	       accen += showerEnergy;
	 }

      } // end loop over good showers
   } // end loop over showers

   assert(passTrig && passL4);
   assert(e1 < 0.85    &&
	  p2 < 0.85    &&
	  visen > 0.20 &&
	  ccen < 0.85  &&
	  ntracks > 1    );
   bool passOuterLimits = (abs(d0close) < 0.005  &&
			   ((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075)));
   bool gassy = (abs(d0close) < 0.02    &&
		 0.075 < abs(wz) < 0.4  &&
		 -0.9 < trperp1 < 0.9);
   bool positronic = (wpz > 1.);
   bool electronic = (wpz < -1.);

   if (passTrig     &&
       e1 < 0.85    &&
       p2 < 0.85    &&
       visen > 0.2  &&
       ccen < 0.85  &&
       ntracks > 1  &&
       passL4       &&
       trperp1 < -0.999                &&
       accen/2./eBeam->value() <= 0.2  &&
       abs(z0close) > 0.075)
      m_cosmicEvents++;

   if (passOuterLimits  &&  visen > 0.35) {
      report(DEBUG, kFacilityString) << "passed and counted!" << endl;

      m_goodEvents++;

      m_d0close->fill(d0close);
      m_e1->fill(e1);
      m_p2->fill(p2);
      m_wz->fill(wz);
      if (wz > 800.) m_z0close->fill(z0close);
      m_visen->fill(visen);
      m_tracks->fill(ntracks);
      m_ccen->fill(ccen);
   }

   if (!passOuterLimits) {
      if (gassy) {
	 if (positronic) m_bgpEvents++;
	 else if (electronic) m_bgeEvents++;
      }
      return ActionBase::kFailed;
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
CountEvents::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
CountEvents::endRun( Frame& iFrame )         // anal4 equiv.
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

DABoolean CountEvents::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean CountEvents::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
