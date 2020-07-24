// -*- C++ -*-
//
// Package:     ExploreTauHadron
// Module:      ExploreTauHadron
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Jul 10 16:23:20 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ExploreTauHadron/ExploreTauHadron.h"
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

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

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
static const char* const kFacilityString = "Processor.ExploreTauHadron" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//


//
// constructors and destructor
//
ExploreTauHadron::ExploreTauHadron( void )               // anal1
   : Processor( "ExploreTauHadron" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ExploreTauHadron::event,    Stream::kEvent );
   //bind( &ExploreTauHadron::beginRun, Stream::kBeginRun );
   //bind( &ExploreTauHadron::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ExploreTauHadron::~ExploreTauHadron()                    // anal5
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
ExploreTauHadron::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ExploreTauHadron::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ExploreTauHadron::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ExploreTauHadron::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;
   float v[kNumEntries];  for (int i = 0;  i < kNumEntries;  i++) v[i] = 5000.;

   if (m_isMC.value()) {
      v[kDecay3S] = 0.;
      v[kDecay2P] = 0.;
      v[kDecay2S] = 0.;
      v[kDecay1P] = 0.;
      v[kDecay1S] = 0.;

      FAItem<MCDecayTree> decay;
      extract(iFrame.record(Stream::kEvent), decay, "Generator");
      MCDecayTree::const_vIterator decay_end(decay->vEnd());
      const MCParticlePropertyStore& mcppstore = decay->topParticle().properties().store();
 
      int gamma(mcppstore.nameToQQId("GAMM"));
      int eplus(mcppstore.nameToQQId("E+"));
      int eminus(mcppstore.nameToQQId("E-"));
      int muplus(mcppstore.nameToQQId("MU+"));
      int muminus(mcppstore.nameToQQId("MU-"));
      int tauplus(mcppstore.nameToQQId("TAU+"));
      int tauminus(mcppstore.nameToQQId("TAU-"));
      int pizero(mcppstore.nameToQQId("PI0"));
      int piplus(mcppstore.nameToQQId("PI+"));
      int piminus(mcppstore.nameToQQId("PI-"));
      int ups1(mcppstore.nameToQQId("UPS1"));
      int ups2(mcppstore.nameToQQId("UPS2"));
      int ups3(mcppstore.nameToQQId("UPS3"));
      int chib0p1(mcppstore.nameToQQId("CHIB0"));
      int chib1p1(mcppstore.nameToQQId("CHIB1"));
      int chib2p1(mcppstore.nameToQQId("CHIB2"));
      int chib0p2(mcppstore.nameToQQId("CHBP0"));
      int chib1p2(mcppstore.nameToQQId("CHBP1"));
      int chib2p2(mcppstore.nameToQQId("CHBP2"));

      Hep3Vector ups3s_p(-1000., -1000., -1000.);
      Hep3Vector ups2s_p(-1000., -1000., -1000.);
      Hep3Vector ups1s_p(-1000., -1000., -1000.);

      for (MCDecayTree::const_vIterator decay_iter = decay->vBegin();
	   decay_iter != decay_end;
	   ++decay_iter) {
	 int parent(decay_iter->parentPtr()->properties().QQId());

	 int decayNumber(1);
	 if (decay_iter->size() == 2) {
	    int first(decay_iter->pBegin()->properties().QQId());
	    int second((++(decay_iter->pBegin()))->properties().QQId());

	    if ( (first == eplus   &&  second == eminus)  ||
		 (first == eminus  &&  second == eplus)      ) {
	       decayNumber = 4;
	    } else if ( (first == muplus   &&  second == muminus)  ||
			(first == muminus  &&  second == muplus)      ) {
	       decayNumber = 5;
	    } else if ( (first == tauplus   &&  second == tauminus)  ||
			(first == tauminus  &&  second == tauplus)      ) {
	       decayNumber = 6;
	    } else if ( (first == gamma    &&  second == chib0p1)  ||
			(first == chib0p1  &&  second == gamma)      ) {
	       decayNumber = 30;
	    } else if ( (first == gamma    &&  second == chib1p1)  ||
			(first == chib1p1  &&  second == gamma)      ) {
	       decayNumber = 31;
	    } else if ( (first == gamma    &&  second == chib2p1)  ||
			(first == chib2p1  &&  second == gamma)      ) {
	       decayNumber = 32;
	    } else if ( (first == gamma    &&  second == chib0p2)  ||
			(first == chib0p2  &&  second == gamma)      ) {
	       decayNumber = 40;
	    } else if ( (first == gamma    &&  second == chib1p2)  ||
			(first == chib1p2  &&  second == gamma)      ) {
	       decayNumber = 41;
	    } else if ( (first == gamma    &&  second == chib2p2)  ||
			(first == chib2p2  &&  second == gamma)      ) {
	       decayNumber = 42;
	    } else if ( (first == gamma  &&  second == ups1)  ||
			(first == ups1   &&  second == gamma)    ) {
	       decayNumber = 51;
	    } else if ( (first == gamma  &&  second == ups2)  ||
			(first == ups2   &&  second == gamma)    ) {
	       decayNumber = 52;
	    }
	 }
	 else if (decay_iter->size() == 3) {
	    int first(decay_iter->pBegin()->properties().QQId());
	    int second((++(decay_iter->pBegin()))->properties().QQId());
	    int third((++(++(decay_iter->pBegin())))->properties().QQId());

	    if ( (first == ups1  &&  second == pizero  &&  third == pizero)  ||
		 (first == pizero  &&  second == ups1  &&  third == pizero)  ||
		 (first == pizero  &&  second == pizero  &&  third == ups1)     ) {
	       decayNumber = 10;
	    } else if ( (first == ups1  &&  second == piplus  &&  third == piminus)  ||
			(first == ups1  &&  second == piminus  &&  third == piplus)  ||
			(first == piplus  &&  second == ups1  &&  third == piminus)  ||
			(first == piplus  &&  second == piminus  &&  third == ups1)  ||
			(first == piminus  &&  second == ups1  &&  third == piplus)  ||
			(first == piminus  &&  second == piplus  &&  third == ups1)     ) {
	       decayNumber = 11;
	    } else if ( (first == ups1  &&  second == gamma  &&  third == gamma)  ||
			(first == gamma  &&  second == ups1  &&  third == gamma)  ||
			(first == gamma  &&  second == gamma  &&  third == ups1)     ) {
	       decayNumber = 12;
	    } else if ( (first == ups2  &&  second == pizero  &&  third == pizero)  ||
			(first == pizero  &&  second == ups2  &&  third == pizero)  ||
			(first == pizero  &&  second == pizero  &&  third == ups2)     ) {
	       decayNumber = 20;
	    } else if ( (first == ups2  &&  second == piplus  &&  third == piminus)  ||
			(first == ups2  &&  second == piminus  &&  third == piplus)  ||
			(first == piplus  &&  second == ups2  &&  third == piminus)  ||
			(first == piplus  &&  second == piminus  &&  third == ups2)  ||
			(first == piminus  &&  second == ups2  &&  third == piplus)  ||
			(first == piminus  &&  second == piplus  &&  third == ups2)     ) {
	       decayNumber = 21;
	    } else if ( (first == ups2  &&  second == gamma  &&  third == gamma)  ||
			(first == gamma  &&  second == ups2  &&  third == gamma)  ||
			(first == gamma  &&  second == gamma  &&  third == ups2)     ) {
	       decayNumber = 22;
	    }
	 }

	 if (parent == ups3) {
	    v[kDecay3S] = decayNumber;
	 }
	 else if (parent == chib0p2  ||  parent == chib1p2  ||  parent == chib2p2) {
	    v[kDecay2P] = decayNumber;
	 }
	 else if (parent == ups2) {
	    v[kDecay2S] = decayNumber;
	 }
	 else if (parent == chib0p1  ||  parent == chib1p1  ||  parent == chib2p1) {
	    v[kDecay1P] = decayNumber;
	 }
	 else if (parent == ups1) {
	    v[kDecay1S] = decayNumber;
	 }

      } // end loop over vertices

   } // end if Monte Carlo

   FATable<NavTrack> navtrack;
   extract(iFrame.record(Stream::kEvent), navtrack);
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   FATable<NavTrack>::const_iterator track_end = navtrack.end();

   FAItem<EventProperties> level5_data;
   extract(iFrame.record(Stream::kEvent), level5_data);
   v[kL5Tracks] = level5_data->nbChargedTracks();
   v[kL5VisibleEnergy] = level5_data->eVis();
   v[kL5CCEnergy] = level5_data->ccTotalEnergy();
   v[kL5BiggestShower] = level5_data->firstLargestEShower();
   v[kL5FirstTrack] = level5_data->firstLargestPTrack();
   v[kL5SecondTrack] = level5_data->secondLargestPTrack();

   FAItem<BeamEnergy> beam_energy;
   extract(iFrame.record(Stream::kStartRun), beam_energy);
   v[kL5BeamEnergy] = beam_energy->value();

   double ci_perp(1000.);
   double weighted_z(1000.);
   double znumer(0.);
   double zdenom(0.);

   for ( track_iter = tracks.begin();  track_iter != track_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != track_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./fabs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  double perp( sqrt(sqr(tx - beamspot->center().x()) + sqr(ty - beamspot->center().y())) );
		  if ( perp < ci_perp ) ci_perp = perp;

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - beamspot->center().x()) + sqr(ty - beamspot->center().y()) );
		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( zdenom != 0. ) {
      weighted_z = znumer / zdenom;
      weighted_z -= beamspot->center().z();
   }

   v[kL6RPhi] = ci_perp;
   v[kL6Z] = weighted_z;

   FAItem<Level4Decision> level4_decision;
   extract(iFrame.record(Stream::kEvent), level4_decision);
   v[kL4Decision] = level4_decision->decision();

   FAItem<EventType> level5_decision;
   extract(iFrame.record(Stream::kEvent), level5_decision);
   v[kL5Decision] = 0.;
   if (level5_decision->hadron()) v[kL5Decision] += 1.;
   if (level5_decision->tau()) v[kL5Decision] += 2.;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ExploreTauHadron::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ExploreTauHadron::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

DABoolean ExploreTauHadron::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean ExploreTauHadron::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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
