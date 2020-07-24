// -*- C++ -*-
//
// Package:     WierdVisenTrigger
// Module:      WierdVisenTrigger
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Aug  9 16:34:01 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "WierdVisenTrigger/WierdVisenTrigger.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "EventProperties/EventProperties.h"
#include "BeamEnergy/BeamEnergy.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "TriggerInfoProd/TriggerInfo.h"
#include "BeamSpot/BeamSpot.h"
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "MagField/MagneticField.h"
#include "CleoDB/DBEventHeader.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCTrackTagger/MCTrackTagsByMCParticle.h"

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
static const char* const kFacilityString = "Processor.WierdVisenTrigger" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
WierdVisenTrigger::WierdVisenTrigger( void )               // anal1
   : Processor( "WierdVisenTrigger" )
   , m_res("res", this, 0)
   , m_evtgen("evtgen", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &WierdVisenTrigger::event,    Stream::kEvent );
   //bind( &WierdVisenTrigger::beginRun, Stream::kBeginRun );
   //bind( &WierdVisenTrigger::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_passing = 0;
   m_total = 0;

}

WierdVisenTrigger::~WierdVisenTrigger()                    // anal5
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
WierdVisenTrigger::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

   m_passing = 0;
   m_total = 0;

}

// -------------------- terminate method ----------------------------
void
WierdVisenTrigger::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
WierdVisenTrigger::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_e1_gggam = iHistoManager.histogram("e1 for gggam", 200, 0., 10.);
   m_gggam = iHistoManager.histogram("photon energy in gggam / CM", 150, 0., 1.5);
   m_other_side = iHistoManager.histogram("other side / CM", 200, 0., 5);
   m_gggam_vs_other_side = iHistoManager.histogram("photon energy in gggam vs other side / CM", 50, 0., 5, 50, 0., 1.);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
WierdVisenTrigger::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> ebeam;
   extract(iFrame.record(Stream::kStartRun), ebeam);

   FAItem<TriggerL1Data> trigL1;
   extract(iFrame.record(Stream::kEvent), trigL1);

//    FAItem<TriggerInfo> triginfo;
//    extract(iFrame.record(Stream::kEvent), triginfo);

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   double d0close = 1000.;
   double z0close = 1000.;
//    double ci = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
//    double wpz = 0.;
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

// 	 if (sqrt(fabs(track_iter->pionFit()->errorMatrix()(
// 			  KTKinematicData::kPz, KTKinematicData::kPz))) < 1.) {
// 	    wpz += track_iter->pionFit()->pz();
// 	 }

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

// 		  if (perp < ci) ci = perp;
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

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree, "Generator");
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator tree_vend = tree->vEnd();
   MCDecayTree::const_pIterator piter;
   MCDecayTree::const_pIterator tree_pend = tree->pEnd();

   const MCParticlePropertyStore& mcppstore =
      tree->topParticle().properties().store();

   double prompt_photon = -1.;
   double other_side = 0.;
   assert((m_res.value() == 1) || (m_res.value() == 2) || (m_res.value() == 3) || (m_res.value() == 20));
   if (m_evtgen.value()) {
      const int ups1 = mcppstore.nameToQQId("Upsilon");
      const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
      const int ups3 = mcppstore.nameToQQId("Upsilon(3S)");
      const int gamm = mcppstore.nameToQQId("gamma");
      const int glue = mcppstore.nameToQQId("string");
      const int psi2 = mcppstore.nameToQQId("psi(2S)");

      report(INFO, kFacilityString) << *tree << endl;

      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if ((m_res.value() == 1  &&  viter->parent().properties().QQId() == ups1)  ||
	     (m_res.value() == 2  &&  viter->parent().properties().QQId() == ups2)  ||
	     (m_res.value() == 3  &&  viter->parent().properties().QQId() == ups3)  ||
	     (m_res.value() == 20 &&  viter->parent().properties().QQId() == psi2)    ) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    bool glue_(false);
	    bool gamm_(false);
	    double photon = 0.;
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == glue) glue_ = true;
	       if (chiter->properties().QQId() == gamm) {
		  gamm_ = true;
		  photon = chiter->momentum().mag();
	       }
	    }
	    if (glue_ && gamm_) prompt_photon = photon;
	 } // end if prompt
	 else if (viter->parent().properties().QQId() == glue) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    double side = 0.;
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       side += chiter->energy();
	    } // end loop over children
	    if (side > other_side) other_side = side;
	 } // end if daughters of glue
      } // end loop over vertices
   } else {
      const int ups1 = mcppstore.nameToQQId("UPS1");
      const int ups2 = mcppstore.nameToQQId("UPS2");
      const int ups3 = mcppstore.nameToQQId("UPS3");
      const int gamm = mcppstore.nameToQQId("GAMM");
      const int psi2 = mcppstore.nameToQQId("PSI2");

      const int psi1 = mcppstore.nameToQQId("PSI");
      const int chi0 = mcppstore.nameToQQId("CHI0");
      const int chi1 = mcppstore.nameToQQId("CHI1");
      const int chi2 = mcppstore.nameToQQId("CHI2");

      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if ((m_res.value() == 1  &&  viter->parent().properties().QQId() == ups1)  ||
	     (m_res.value() == 2  &&  viter->parent().properties().QQId() == ups2)  ||
	     (m_res.value() == 3  &&  viter->parent().properties().QQId() == ups3)  ||
	     (m_res.value() == 20 &&  viter->parent().properties().QQId() == psi2)    ) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    double photon = 0.;
	    bool gluedecay = true;
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == gamm  &&
		   chiter->momentum().mag() > prompt_photon)
		  photon = chiter->momentum().mag();
	       else
		  other_side += chiter->energy();
	       if (chiter->properties().QQId() == psi1  ||
		   chiter->properties().QQId() == chi0  ||
		   chiter->properties().QQId() == chi1  ||
		   chiter->properties().QQId() == chi2    ) gluedecay = false;
	    }
	    if (gluedecay) prompt_photon = photon;
	 } // end if prompt
      } // end loop over vertices

   }

   report(INFO, kFacilityString)
      << "triggers: " << (trigL1->isHadron() ? "hadron" : "") << " "
      << (trigL1->isRadTau() ? "radtau" : "") << " "
      << (trigL1->isElTrack() ? "eltrack" : "") << " "
      << d0close << " "
      << props->firstLargestEShower() / ebeam->value() << " "
      << prompt_photon << endl;

   if ((trigL1->isHadron()  ||  trigL1->isRadTau()  ||  trigL1->isElTrack())  &&  (abs(d0close) < 0.005)) {
      if (prompt_photon / ebeam->value() > 0.05) {
	 m_e1_gggam->fill(props->firstLargestEShower() / ebeam->value());
	 m_gggam->fill(prompt_photon / 2. / ebeam->value());
	 m_other_side->fill(other_side / 2. / ebeam->value());
	 m_gggam_vs_other_side->fill(other_side / 2. / ebeam->value(), prompt_photon / 2. / ebeam->value());
      }
//      if (props->firstLargestEShower() / ebeam->value() > 3.) return ActionBase::kPassed;
   }

   if (prompt_photon / ebeam->value() > 0.05) {
      m_total++;
      if ((trigL1->isHadron()  ||  trigL1->isRadTau()  ||  trigL1->isElTrack())  &&
	  (abs(d0close) < 0.005)  &&
	  (props->firstLargestEShower() / ebeam->value() < 0.85)  &&
	  (props->secondLargestPTrack() / ebeam->value() < 0.85)     )
	 m_passing++;

      report(SYSTEM, kFacilityString)
	 << "passing / total = " << m_passing << " / " << m_total << endl;

      return ActionBase::kPassed;
   }

   return ActionBase::kFailed;

//    if ((trigL1->isHadron()  ||  trigL1->isRadTau()  ||  trigL1->isElTrack())  &&
//        (props->neutralEnergy() + props->chargedEnergy())/2./ebeam->value() < 0.3  &&
//        props->nbChargedTracks() < 3  &&  props->secondLargestPTrack()/ebeam->value() < 0.85  &&
//        ((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075))  &&  abs(d0close) < 0.005) {
//       report(SYSTEM, kFacilityString)
// 	 << "visen " << (props->neutralEnergy() + props->chargedEnergy())/2./ebeam->value()
// 	 << " tracks " << props->nbChargedTracks()
// 	 << " t1had " << trigL1->isHadron()
// 	 << " t1rad " << trigL1->isRadTau()
// 	 << " t1el " << trigL1->isElTrack()
// 	 << " axial " << triginfo->axial()
// 	 << " stereo " << triginfo->stereo()
// 	 << " cblo " << triginfo->cblo()
// 	 << " cbmd " << triginfo->cbmd() << endl;

//       report(SYSTEM, kFacilityString)
// 	 << "from EventProperties: totccenergy " << props->ccTotalEnergy()
// 	 << " big1sh " << props->firstLargestEShower()
// 	 << " big2sh " << props->secondLargestEShower()
// 	 << " big3sh " << props->thirdLargestEShower() << endl;
//       report(SYSTEM, kFacilityString) << "all showers list:";
//       for (FATable<NavShower>::const_iterator shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
// 	 if (shower_iter->attributes().status()  &&
// 	     shower_iter->attributes().energy()/ebeam->value() > 0.01) {
// 	    report(SYSTEM, kFacilityString) << " " << shower_iter->attributes().energy();
// 	 }
//       }
//       report(SYSTEM, kFacilityString) << endl;

//       return ActionBase::kPassed;
//    }

//   return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
WierdVisenTrigger::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
WierdVisenTrigger::endRun( Frame& iFrame )         // anal4 equiv.
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

DABoolean WierdVisenTrigger::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean WierdVisenTrigger::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
