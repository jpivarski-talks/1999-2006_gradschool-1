// -*- C++ -*-
//
// Package:     DuperCuts
// Module:      DuperCuts
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Feb 11 10:30:08 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "DuperCuts/DuperCuts.h"
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
#include "BeamSpot/BeamSpot.h"
#include "EventProperties/EventProperties.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "Level4Proc/Level4DecisionProxy.h"

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
static const char* const kFacilityString = "Processor.DuperCuts" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
DuperCuts::DuperCuts( void )               // anal1
   : Processor( "DuperCuts" )
   , m_mcll("mcll", this, false)
   , m_mcother("mcother", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &DuperCuts::event,    Stream::kEvent );
   //bind( &DuperCuts::beginRun, Stream::kBeginRun );
   //bind( &DuperCuts::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

DuperCuts::~DuperCuts()                    // anal5
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
DuperCuts::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
DuperCuts::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
DuperCuts::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "e1", "e2", "p1", "p2", "q2", "costh",
      "rawntk", "epntk", "visen", "ccen", "bgntk", "bgrphi", "bgz", "bgd0", "bgz0",
      "neue", "q", "nsh10", "nsh50", "nsh100", "nsh500",
      "trig1", "level4"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
DuperCuts::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   if (m_mcll.value()  ||  m_mcother.value()) {
      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree, "Generator");
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();

      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();
      const int ups1 = mcppstore.nameToQQId("UPS1");
      const int ups2 = mcppstore.nameToQQId("UPS2");
      const int ups3 = mcppstore.nameToQQId("UPS3");
      const int eplus = mcppstore.nameToQQId("E+");
      const int eminus = mcppstore.nameToQQId("E-");
      const int muplus = mcppstore.nameToQQId("MU+");
      const int muminus = mcppstore.nameToQQId("MU-");

      bool two_leptons = false;
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().QQId() == ups1  ||
	     viter->parent().properties().QQId() == ups2  ||
	     viter->parent().properties().QQId() == ups3    ) {

	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	 
	    int children = 0;
	    bool eplus_, eminus_, muplus_, muminus_;
	    eplus_ = eminus_ = muplus_ = muminus_ = false;
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       children++;
	       if (chiter->properties().QQId() == eplus) eplus_ = true;
	       if (chiter->properties().QQId() == eminus) eminus_ = true;
	       if (chiter->properties().QQId() == muplus) muplus_ = true;
	       if (chiter->properties().QQId() == muminus) muminus_ = true;
	    } // end loop over children
	    if (((eplus_ && eminus_) || (muplus_ && muminus_))  &&
		children == 2) {
	       if (viter->parent().properties().QQId() == ups1  ||
		   viter->parent().properties().QQId() == ups2  ||
		   viter->parent().properties().QQId() == ups3    ) {
		  two_leptons = true;
	       }
	    } // end if we're looking at a light lepton vertex

	 } // end switch parent QQId
      } // end loop over vertices
      if (m_mcll.value()  &&  !two_leptons) return ActionBase::kFailed;
      if (m_mcother.value()  &&  two_leptons) return ActionBase::kFailed;
   } // end if looking for mcll or mcother

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter = tracks.begin();
   FATable<NavTrack>::const_iterator track_end = tracks.end();

   double p1 = 0.;
   double p2 = 0.;
   FATable<NavTrack>::const_iterator track_iter1 = track_end;
   FATable<NavTrack>::const_iterator track_iter2 = track_end;
   for (; track_iter != track_end;  ++track_iter) {
      double p = track_iter->pionFit()->momentum().mag();
      if (p > p1) {
	 p2 = p1;
	 p1 = p;

	 track_iter2 = track_iter1;
	 track_iter1 = track_iter;
      }
      else if (p > p2) {
	 p2 = p;

	 track_iter2 = track_iter;
      }
   } // end track loop

   int q2 = 1000;
   if (track_iter1 != track_end  &&  track_iter2 != track_end) {
      q2 = (track_iter1->pionHelix()->curvature() > 0. ? 1 : -1) +
	 (track_iter2->pionHelix()->curvature() > 0. ? 1 : -1);
   }

   double cotTheta = -1000.;
   if (track_iter1 != track_end  &&  track_iter1->pionHelix()->curvature() > 0.) {
      cotTheta = track_iter1->pionHelix()->cotTheta();
   }
   else if (track_iter2 != track_end  &&  track_iter2->pionHelix()->curvature() > 0.) {
      cotTheta = track_iter2->pionHelix()->cotTheta();
   }

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_iter = showers.begin();
   FATable<NavShower>::const_iterator shower_end = showers.end();

   double e1 = 0.;
   double e2 = 0.;
   int nsh10 = 0;
   int nsh50 = 0;
   int nsh100 = 0;
   int nsh500 = 0;
   for (; shower_iter != shower_end;  ++shower_iter) {
      if (! shower_iter->attributes().hot()) {
	 double e = shower_iter->attributes().energy();
	 if (e > e1) {
	    e2 = e1;
	    e1 = e;
	 }
	 else if (e > e2) {
	    e2 = e;
	 }
	 if (e > 0.010) nsh10++;
	 if (e > 0.050) nsh50++;
	 if (e > 0.100) nsh100++;
	 if (e > 0.500) nsh500++;
      } // end if shower is hot
   } // end shower loop

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   double ci_perp = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
   int bg_tracks = 0;
   double d0close = 1000.;
   double z0close = 1000.;
   FATable<NavTrack>::const_iterator other_iter;
   for (track_iter = tracks.begin();  track_iter != track_end;  track_iter++) {
      if (! track_iter->seedQuality()->originUsed()            &&
	  ! track_iter->pionQuality()->fitAbort()              &&
	  1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	  ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {

	 bg_tracks++;
	 KTHelix movetrack(*track_iter->pionHelix());
	 double distance_moved;
	 movetrack.moveToReferencePoint(spot->center(),
					distance_moved,
					KTMoveControl::kDirectionEither);
	 if (fabs(movetrack.d0()) < fabs(d0close)) d0close = movetrack.d0();
	 if (fabs(movetrack.z0()) < fabs(z0close)) z0close = movetrack.z0();

	 // Secondary track loop to calculate pairwise intersections
	 for (other_iter = track_iter;  other_iter != track_end;  other_iter++) {
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
		  if (perp < ci_perp) ci_perp = perp;

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
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

   double weighted_z = 1000.;
   if (zdenom != 0.) {
      weighted_z = znumer / zdenom;
      weighted_z -= spot->center().z();
   }

   if (bg_tracks == 0  &&  tracks.size() > 0) {
      for (track_iter = tracks.begin();  track_iter != track_end;  track_iter++) {
	 KTHelix movetrack(*track_iter->pionHelix());
	 double distance_moved;
	 movetrack.moveToReferencePoint(spot->center(),
					distance_moved,
					KTMoveControl::kDirectionEither);
	 if (fabs(movetrack.d0()) < fabs(d0close)) d0close = movetrack.d0();
	 if (fabs(movetrack.z0()) < fabs(z0close)) z0close = movetrack.z0();
      } // end loop over ALL tracks
   } // end if there are tracks that missed my BG pass

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> beamEnergy;
   extract(iFrame.record(Stream::kStartRun), beamEnergy);

   FAItem<TriggerL1Data> t1;
   extract(iFrame.record(Stream::kEvent), t1);

   FAItem<Level4Decision> level4;
   extract(iFrame.record(Stream::kEvent), level4);

   float v[kNumEntries];
   v[kShower1] = e1 / beamEnergy->value();
   v[kShower2] = e2 / beamEnergy->value();
   v[kMomentum1] = p1 / beamEnergy->value();
   v[kMomentum2] = p2 / beamEnergy->value();
   v[kQ2] = q2;
   v[kCosTheta] = cotTheta / sqrt(sqr(cotTheta) + 1.);
   v[kRawNumTracks] = tracks.size();
   v[kEPNumTracks] = props->nbChargedTracks();
   v[kVisEn] = (props->neutralEnergy() + props->chargedEnergy())/ 2. / beamEnergy->value();
   v[kCCEn] = props->ccTotalEnergy() / 2. / beamEnergy->value();
   v[kBGNumTracks] = bg_tracks;
   v[kBGRPhi] = ci_perp;
   v[kBGZ] = weighted_z;
   v[kBGD0] = d0close;
   v[kBGZ0] = z0close;
   v[kNeuE] = props->neutralEnergy() / 2. / beamEnergy->value();
   v[kQ] = props->netCharge();
   v[kNSh10] = nsh10;
   v[kNSh50] = nsh50;
   v[kNSh100] = nsh100;
   v[kNSh500] = nsh500;
   v[kTrig1] = (
      (t1->isHadron() 	    ? 1. : 0.) +
      (t1->isMuPair() 	    ? 10. : 0.) +
      (t1->isCBSingleHi()   ? 100. : 0.) +
      (t1->isCESingleHi()   ? 1000. : 0.) +
      (t1->isBarrelBhabha() ? 10000. : 0.) +
      (t1->isEndcapBhabha() ? 100000. : 0.) +
      (t1->isElTrack()      ? 1000000. : 0.) +
      (t1->isRadTau() 	    ? 10000000. : 0.) +
      (t1->isPulser() 	    ? 100000000. : 0.) +
      (t1->isRandom() 	    ? 1000000000. : 0.) +
      (t1->isTwoTrack()     ? 10000000000. : 0.) +
      (t1->isMinBias()      ? 100000000000. : 0.)
      );
   v[kLevel4] = level4->decision();
   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
DuperCuts::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
DuperCuts::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

DABoolean DuperCuts::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean DuperCuts::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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

//
// const member functions
//

//
// static member functions
//
