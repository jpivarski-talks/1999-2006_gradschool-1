// -*- C++ -*-
//
// Package:     PrintOutProc
// Module:      PrintOutProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Aug 26 14:23:20 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "PrintOutProc/PrintOutProc.h"
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
#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcShowerAttributes.h"
#include "EventProperties/EventProperties.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"

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
static const char* const kFacilityString = "Processor.PrintOutProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
PrintOutProc::PrintOutProc( void )               // anal1
   : Processor( "PrintOutProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PrintOutProc::event,    Stream::kEvent );
   //bind( &PrintOutProc::beginRun, Stream::kBeginRun );
   //bind( &PrintOutProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

PrintOutProc::~PrintOutProc()                    // anal5
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
PrintOutProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
PrintOutProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
PrintOutProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PrintOutProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

//     FATable< NavTrack > tracks;
//     extract( iFrame.record( Stream::kEvent ), tracks );
//     FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   static int number;
   number++;
   if ( number % 1000 == 0 )
      cout << number << endl;

   FAItem< MCDecayTree > decayTree;
   extract( iFrame.record( Stream::kEvent ), decayTree, "Generator" );

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   if ( props->neutralEnergy() < 0.01 ) {
      MCDecayTree::const_vIterator end = decayTree->vEnd();
      for ( MCDecayTree::const_vIterator viter = decayTree->vBegin();
	    viter != end;
	    viter++ ) {
	 viter->dump( report( SYSTEM, kFacilityString ) );
	 report( SYSTEM, kFacilityString ) << endl;
      }
   }

//     FAItem< DBEventHeader > header;
//     extract( iFrame.record( Stream::kEvent ), header );

//     vector< KTHelix* > cut_helix;
//     FATable< NavTrack >::const_iterator track_iter;
//     for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ )
//     {
//        // Quality cuts for cut-determining helices
//        if ( ! track_iter->pionQuality()->fitAbort()                  // - Just make sure it didn't abort
//                                                                      //   (since that might force the track
//                                                                      //   through the origin wrongly)
//  	 ) {
//  	 cut_helix.push_back( (KTHelix*)( &*track_iter->pionHelix() ) );
//        } // end passes cut cuts

//     } // end loop over tracks

//     double closest_inter( closest_intersection( cut_helix, 0., 0. ) );
//     double smallest_d0( smallest_dca( cut_helix, 0., 0. ) );

//     static int counter;
//     if ( counter % 1000 ) cout << "counter = " << counter << endl;

//     report( INFO, kFacilityString ) << *decayTree << endl;

   



   
   return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
PrintOutProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
PrintOutProc::endRun( Frame& iFrame )         // anal4 equiv.
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

double PrintOutProc::smallest_dca( vector< KTHelix* > helix,
				   double beam_x, double beam_y, double veto )
{
   double bestdca(1000.);

   // This is a loop over helices.
   int i, j;
   int nhelix( helix.size() );
   for ( i = 0;  i < nhelix;  i++ ) {
      double dca( abs(helix[i]->d0()) );
      if ( dca > veto  &&  dca < bestdca ) bestdca = dca;
   } // end loop over helices
   
   return bestdca;
}

double PrintOutProc::closest_intersection( vector< KTHelix* > helix,
					   double beam_x, double beam_y, double veto )
{
   double bestxy(1000.);

   // This is a loop over the upper triangle of the helix-helix
   // matrix.
   int i, j;
   int nhelix( helix.size() );
   for ( i = 0;  i < nhelix;  i++ )
      for ( j = i + 1;  j < nhelix;  j++ ) {
	 double tx(-1000.), ty(-1000.), dummysigx(-1000.), dummysigy(-1000.);
	 
	 // Don't bother with any failed intersections
	 if ( calc_intersection( tx, ty, dummysigx, dummysigy, *helix[i], *helix[j] ) ) {
	    double xy( sqrt(sqr(tx - beam_x) + sqr(ty - beam_y)) );
	    if ( xy > veto  &&  xy < bestxy ) bestxy = xy;
	 } // end if intersection succeeded

      } // end loop over pairs of helices
   
   return bestxy;
}

DABoolean PrintOutProc::calc_intersection( double& x, double& y, double& sigx, double& sigy,
					   KTHelix& a, KTHelix& b, DABoolean calc_uncerts )
{
   x = y = sigx = sigy = 1000.;  // To more easily find unchecked failures

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
   int which_num;
   char which_let;
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;  which_num = 1;
      if ( abs(ysol1 - ysol1a) < abs(ysol1 - ysol1b) )
	 which_let = 'a';  else  which_let = 'b';
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;  which_num = 2;
      if ( abs(ysol2 - ysol2a) < abs(ysol2 - ysol2b) )
	 which_let = 'a';  else  which_let = 'b';
   }      

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;  which_num = 1;
      if ( abs(ysol1 - ysol1a) < abs(ysol1 - ysol1b) )
	 which_let = 'a';  else  which_let = 'b';
   }

   else {
      x = xsol2;  y = ysol2;  which_num = 2;
      if ( abs(ysol2 - ysol2a) < abs(ysol2 - ysol2b) )
	 which_let = 'a';  else  which_let = 'b';
   }      

   return true;
}

DABoolean PrintOutProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   const double tailcut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailcut  &&  aarclength < M_PI/2./abs(a.curvature()) )  &&
      ( barclength > -tailcut  &&  barclength < M_PI/2./abs(b.curvature()) );
}
