// -*- C++ -*-
//
// Package:     TwoPionsProc
// Module:      TwoPionsProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Wed Aug  7 13:49:13 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TwoPionsProc/TwoPionsProc.h"
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

#include "CesrCleoComm/CesrBeamEnergy.h"
#include "CleoDB/DBEventHeader.h"
#include "DedxInfo/DedxInfo.h"

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
static const char* const kFacilityString = "Processor.TwoPionsProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TwoPionsProc::TwoPionsProc( void )               // anal1
   : Processor( "TwoPionsProc" )
   , m_fillBuffer( "fillBuffer", this, true )
   , m_noBeamSpot( "noBeamSpot", this, false )
   , m_beamSpotVars( NULL )
   , m_centeredBeamSpot( NULL )
   , m_ntuple( NULL )
   , m_num_buffer_events( 0 )
   , m_buffer_pointer( 0 )
   , m_buf_x()
   , m_buf_sigx()
   , m_buf_y()
   , m_buf_sigy()
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TwoPionsProc::event,    Stream::kEvent );
   //bind( &TwoPionsProc::beginRun, Stream::kBeginRun );
   //bind( &TwoPionsProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TwoPionsProc::~TwoPionsProc()                    // anal5
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
TwoPionsProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TwoPionsProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TwoPionsProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* beamSpotVarsLabels[kNBeamSpotVars] = {
      "run", "event", "x", "sigx", "y", "sigy", "spread" };
   m_beamSpotVars = iHistoManager.ntuple(
      1, "beamSpotVars", kNBeamSpotVars, 262144, beamSpotVarsLabels );
   m_centeredBeamSpot = iHistoManager.histogram(
      2, "centered beamspot", 200, -0.01, 0.01, 200, -0.01, 0.01 );

   const char* ntupleLabels[kNNtupleVars] = {
      "psig", "nsig", "pz0", "pz0err2", "nz0", "nz0err2", "x", "shx", "y", "shy",
      "mrec", "prx", "pry", "prz", "ppx", "ppy", "ppz", "npx", "npy", "npz", "fitcrit" };
   m_ntuple = iHistoManager.ntuple(
      100, "ntuple", kNNtupleVars, 262144, ntupleLabels );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TwoPionsProc::event( Frame& iFrame )          // anal3 equiv.
{
   const double pionMass = 0.13957018;
   const double y1sMass = 9.46030;
   const double y2sMass = 10.02326;
   const double y3sMass = 10.3552;
   const double y4sMass = 10.5800;
   Hep3Vector xangle4s( -0.026, 0., 0. );
   Hep3Vector xangle( xangle4s * (y3sMass/y4sMass) );

   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< CesrBeamEnergy > cesrEnergy ;
   extract( iFrame.record( Stream::kStartRun ), cesrEnergy );
   if ( abs(cesrEnergy->value() - 5.17926) > 0.0005 ) return ActionBase::kFailed;

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   FAItem< DBEventHeader > header;
   extract( iFrame.record( Stream::kEvent ), header );
   static int run;
   if ( run != header->run() ) {
      report( NOTICE, kFacilityString ) << "Starting new run..." << endl;
      run = header->run();
   }

   FATable< DedxInfo > dedxinfo;
   extract( iFrame.record( Stream::kEvent ), dedxinfo );
   FATable< DedxInfo >::const_iterator dedxinfo_end = dedxinfo.end();

   vector< KTHelix* > beamspot_helix;
   vector< KTHelix* > pion;
   vector< float > sigma;
   vector< Hep3Vector > momentum;

   for ( FATable< NavTrack >::const_iterator track_iter = tracks.begin();
         track_iter != tracks_end;
         track_iter++ ) {
      FATable< DedxInfo >::const_iterator dedx_iter = dedxinfo.find( track_iter->identifier() );

      if ( ! track_iter->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! track_iter->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   dedx_iter != dedxinfo_end                            &&  // - Must have dedx info
	   abs( dedx_iter->piSigma() ) < 3.                         // - It must be a pion!
	 ) {
	 pion.push_back( (KTHelix*)( &*track_iter->pionHelix() ) );
	 sigma.push_back( dedx_iter->piSigma() );
	 momentum.push_back( track_iter->pionFit()->momentum() );
      } // end if it's a pion

      // Quality cuts for beamspot-finding helices
      if ( ! track_iter->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! track_iter->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&  // - Diameter must be greater than 42 cm
                                                                    //   to guarantee that it pokes through
                                                                    //   the first stereo superlayer
	   ! track_iter->pionHelix()->hasNullErrorMatrix()          // - I want an error matrix for
                                                                    //   weighted means
	 )
	 beamspot_helix.push_back( (KTHelix*)( &*track_iter->pionHelix() ) );

   } // end loop over tracks
      
   double beam_x(0.), beam_sigx(0.), beam_y(0.), beam_sigy(0.), beam_spread(0.);
   if ( ! m_noBeamSpot.value() ) {
      double x(2000.), y(2000.), sigx(2000.), sigy(2000.);
      const int min_bs_tracks = 5;
      const double max_bs_from_origin = 0.01;

      if ( m_fillBuffer.value() ) {
	 if ( beamspot_helix.size() > min_bs_tracks               &&
	      event_vertex( x, y, sigx, sigy, beamspot_helix )    &&
	      sqrt(sqr(x) + sqr(y)) < max_bs_from_origin ) {

	    m_buf_x.push_back( x );
	    m_buf_y.push_back( y );
	    m_buf_sigx.push_back( sigx );
	    m_buf_sigy.push_back( sigy );
	    m_num_buffer_events++;
	 }
	 return ActionBase::kFailed;
      } // end if doing nothing but filling the beamspot buffers

      double beam_xnumer(0.), beam_xdenom(0.), beam_ynumer(0.), beam_ydenom(0.);
      int i;
      for ( i = 0;  i < m_num_buffer_events;  i++ ) {
	 beam_xnumer += m_buf_x[i] / sqr(m_buf_sigx[i]);
	 beam_xdenom += 1. / sqr(m_buf_sigx[i]);

	 beam_ynumer += m_buf_y[i] / sqr(m_buf_sigy[i]);
	 beam_ydenom += 1. / sqr(m_buf_sigy[i]);
      }
      assert( beam_xdenom > 0.  &&  beam_ydenom > 0. );
      beam_x = beam_xnumer / beam_xdenom;
      beam_sigx = sqrt( 1. / beam_xdenom );
      beam_y = beam_ynumer / beam_ydenom;
      beam_sigy = sqrt( 1. / beam_ydenom );

      for ( i = 0;  i < m_num_buffer_events;  i++ )
	 beam_spread += sqr(m_buf_x[i]) + sqr(m_buf_y[i]);
      assert( m_num_buffer_events > 0 );
      beam_spread /= double(m_num_buffer_events);
      beam_spread = sqrt(beam_spread);

      if ( beamspot_helix.size() > min_bs_tracks               &&
	   event_vertex( x, y, sigx, sigy, beamspot_helix )    &&
	   sqrt(sqr(x) + sqr(y)) < max_bs_from_origin ) {

	 m_buf_x[ m_buffer_pointer ] = x;
	 m_buf_y[ m_buffer_pointer ] = y;
	 m_buf_sigx[ m_buffer_pointer ] = sigx;
	 m_buf_sigy[ m_buffer_pointer ] = sigy;
	 m_buffer_pointer++;

	 m_centeredBeamSpot->fill( x - beam_x, y - beam_y );

	 if ( m_buffer_pointer == m_num_buffer_events ) {
	    m_buffer_pointer = 0;

	    float bs[kNBeamSpotVars];
	    bs[kRunNum] = header->run();
	    bs[kEventNum] = header->number();
	    bs[kX] = beam_x;
	    bs[kSigX] = beam_sigx;
	    bs[kY] = beam_y;
	    bs[kSigY] = beam_sigy;
	    bs[kSpread] = beam_spread;

	    m_beamSpotVars->fill( bs );
	 } // end if wrap-around
      } // end if this makes a good beamspot element

   } // end if calculating a beamspot

   float v[kNNtupleVars];
   int fitCriteria( 0 );

   int i, j;
   int npions( pion.size() );
   for ( i = 0;  i < npions;  i++ )
      for ( j = i + 1;  j < npions;  j++ )
	 if ( pion[i]->curvature() * pion[j]->curvature() < 0. ) {
	    int a, b;
	    if ( pion[i]->curvature() > 0. ) { a = i; b = j; }
	    else { a = j; b = i; }

	    double za( pion[a]->z0() );
	    double zb( pion[b]->z0() );
	    double zaerr2( pion[a]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );
	    double zberr2( pion[b]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );

	    if ( abs(za) < 0.06  &&  abs(zb) < 0.06         &&
	         abs(za - zb) / sqrt(zaerr2 + zberr2) < 3.  &&
		 abs(za - zb) < 0.005                           ) {
	       double tx(-1000.), ty(-1000.), dummysigx(-1000.), dummysigy(-1000.);

	       if ( calc_intersection( tx, ty, dummysigx, dummysigy, *pion[a], *pion[b] ) )
		  if ( sqrt(sqr(tx - beam_x) + sqr(ty - beam_y)) < 0.003 ) { 
		     Hep3Vector precoil(xangle - momentum[a] - momentum[b]);
		     double mrecoil2( sqr(sqrt(sqr(y3sMass) + xangle.mag2())
					  - sqrt(sqr(pionMass) + momentum[a].mag2())
					  - sqrt(sqr(pionMass) + momentum[b].mag2()))
				      - precoil.mag2() );
		     if ( mrecoil2 > 0. ) {
			double mrecoil(sqrt(mrecoil2));

			if ( abs(mrecoil - y1sMass) < 0.1 ) {
			   v[kPSigma] = sigma[a];
			   v[kNSigma] = sigma[b];
			   v[kPZ0] = za;
			   v[kPZ0err2] = zaerr2;
			   v[kNZ0] = zb;
			   v[kNZ0err2] = zberr2;
			   v[kAbsX] = tx;
			   v[kShiftX] = tx - beam_x;
			   v[kAbsY] = ty;
			   v[kShiftY] = ty - beam_y;
			   v[kMRecoil] = mrecoil;
			   v[kPRx] = precoil.x();
			   v[kPRy] = precoil.y();
			   v[kPRz] = precoil.z();
			   v[kPPx] = momentum[a].x();
			   v[kPPy] = momentum[a].y();
			   v[kPPz] = momentum[a].z();
			   v[kNPx] = momentum[b].x();
			   v[kNPy] = momentum[b].y();
			   v[kNPz] = momentum[b].z();

			   fitCriteria++;
			} // end if good recoil mass
		     } // end if recoil mass exists
		  } // end if good XY intersection
	    } // end if good z agreement
	 } // end if oppositely-signed
   v[kFitCriteria] = float(fitCriteria);
   if ( fitCriteria > 0 ) {
      m_ntuple->fill( v );
      return ActionBase::kPassed;
   }
   else
      return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
TwoPionsProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TwoPionsProc::endRun( Frame& iFrame )         // anal4 equiv.
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

double TwoPionsProc::closest_intersection( vector< KTHelix* > helix, double beam_x, double beam_y )
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
	 if ( calc_intersection( tx, ty, dummysigx, dummysigy, *helix[i], *helix[j] ) )
	    if ( sqrt(sqr(tx - beam_x) + sqr(ty - beam_y)) < bestxy )
	       bestxy = sqrt(sqr(tx) + sqr(ty));
      } // end loop over pairs of helices
   
   return bestxy;
}

DABoolean TwoPionsProc::event_vertex( double& x, double& y, double& sigx, double& sigy,
					  vector< KTHelix* > helix )
{
   // These only affect beamspot determination, it's not sensitive
   // enough to need to be a parameter.
   const int minHelices = 3;
   const double rmscut = 0.0005;

   vector< KTHelix* > subset;
   int i, j;
   for ( i = 0;  i < helix.size();  i++ )
      subset.push_back( helix[i] );

   // Throw out helices until all the intersections form a tight
   // little bunch with RMS < rmscut.
   while ( subset.size() >= minHelices ) {
      // trial x and y intersections
      vector< double > trialx;
      vector< double > trialy;
      vector< int > hindex1;
      vector< int > hindex2;

      // This loop runs over the upper triangle of the helix-helix
      // matrix.
      int nsubset( subset.size() );
      for ( i = 0;  i < nsubset;  i++ )
	 for ( j = i + 1;  j < nsubset;  j++ ) {
	    double tx(-1000.), ty(-1000.), dummysigx(-1000.), dummysigy(-1000.);

	    // Don't bother with any failed intersections
	    if ( calc_intersection( tx, ty, dummysigx, dummysigy, *subset[i], *subset[j] )  &&
		 zsep_test( tx, ty, *subset[i], *subset[j] ) ) {
	       trialx.push_back( tx );
	       trialy.push_back( ty );
	       hindex1.push_back( i );
	       hindex2.push_back( j );
	    } // end if good intersection
	 } // end loop over all pairs of helices
      if( trialx.size() == 0 ) return false;

      // Calculate the RMS of the cloud of intersections
      double rms( calc_rms(trialx, trialy, hindex1, hindex2) );
      if ( rms < rmscut ) break;

      // Now that we know the average and rms for all these trial
      // intersections, find the average and rms with one helix
      // missing, for each helix. The helix which, when missing,
      // reduces the rms the most is the first helix to remove.
      int besttoremove(-1);
      double bestsemirms(rms);
      DABoolean anyzero(false);
      for ( i = 0;  i < nsubset;  i++ ) {
	 double semirms( calc_rms(trialx, trialy, hindex1, hindex2, i) );

	 // If removing a helix leaves us with no intersections, this
	 // helix must not be dropped!
	 if ( semirms == 0. ) {
	    anyzero = true;
	    continue;
	 }

	 if ( semirms < bestsemirms ) {
	    bestsemirms = semirms;
	    besttoremove = i;
	 }
      } // end loop over helix indexes

      // If removing any helix just increases the rms, this is the
      // ideal set of helices.
      if ( besttoremove == -1 ) break;

      // I don't want to remove so many helices that I am left with
      // only one intersection.
      if ( anyzero ) break;

      vector< KTHelix* > tmp_copy;
      for ( i = 0;  i < nsubset;  i++ )
	 tmp_copy.push_back( subset[i] );
      subset.erase();
      for ( i = 0;  i < tmp_copy.size();  i++ )
	 if ( i != besttoremove )
	    subset.push_back( tmp_copy[i] );
   } // end while removing helices from the subset

   // Now we have an ideal set of helices. Let's recalculate the
   // intersections for a weighted mean. (So this time we'll need
   // uncertainties.)
   double numerx(0.), denomx(0.), numery(0.), denomy(0.);
   int subset_size( subset.size() );
   for ( i = 0;  i < subset_size;  i++ )
      for ( j = i + 1;  j < subset_size;  j++ ) {
	 double tx(-1000.), ty(-1000.), tsigx(-1000.), tsigy(-1000.);

	 // Don't bother with any failed intersections
	 if ( calc_intersection( tx, ty, tsigx, tsigy, *subset[i], *subset[j], true )  &&
	      zsep_test( tx, ty, *subset[i], *subset[j] ) ) {
	    numerx += tx / sqr(tsigx);
	    denomx += 1. / sqr(tsigx);

	    numery += ty / sqr(tsigy);
	    denomy += 1. / sqr(tsigy);
	 } // end if good intersection
      } // end loop over all pairs of intersections left
   
   if ( denomx == 0.  ||  denomy == 0. ) return false;

   x = numerx / denomx;
   sigx = sqrt( 1. / denomx );
   y = numery / denomy;
   sigy = sqrt( 1. / denomy );

   return true;
}

DABoolean TwoPionsProc::zsep_test( double x, double y, KTHelix& a, KTHelix& b )
{
   // This only affects beamspot determination, it's not sensitive
   // enough to need to be a parameter.
   const double zsepCut = 0.001;

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

   return abs(az - bz) < zsepCut;
}

double TwoPionsProc::calc_rms( vector< double >& trialx, vector< double >& trialy,
				   vector< int >& hindex1, vector< int >& hindex2,
				   int skip )
{
   int ninter( trialx.size() ), nleft(0);

   // Find the center
   double averagex(0.), averagey(0.);
   int i;
   for ( i = 0;  i < ninter;  i++ )
      if ( skip == -1  ||  ( hindex1[i] != skip  &&  hindex2[i] != skip ) ) {
	 averagex += trialx[i];
	 averagey += trialy[i];
	 nleft++;
      }
   if ( nleft == 0 ) {
      return 0.;
   }
   averagex /= double(nleft);
   averagey /= double(nleft);

   // Find the spread away from that center
   double rms(0.);
   for ( i = 0;  i < ninter;  i++ )
      if ( skip == -1  ||  ( hindex1[i] != skip  &&  hindex2[i] != skip ) )
	 rms += sqr(trialx[i] - averagex) + sqr(trialy[i] - averagey);
   rms /= double(nleft);
   rms = sqrt( rms );

   return rms;
}

DABoolean TwoPionsProc::calc_intersection( double& x, double& y, double& sigx, double& sigy,
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

   if ( ! calc_uncerts ) return true;

   // now for the derivatives
   double dpre_dra( (ra*(-xa + xb))/(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) );
   double dpre_dxa( (sqr(ra)*(sqr(xa) - 2.*xa*xb + sqr(xb) - sqr(ya - yb)) + 
		     sqr(rb)*(-sqr(xa) + 2.*xa*xb - sqr(xb) + sqr(ya - yb)) + 
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.))/
		    (2.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   double dpre_dya( ((sqr(ra) - sqr(rb))*(xa - xb)*(ya - yb))/
		    pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.) );
   double dpre_drb( (rb*(xa - xb))/(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) );
   double dpre_dxb( (sqr(rb)*(sqr(xa) - 2.*xa*xb + sqr(xb) - sqr(ya - yb)) + 
		     sqr(ra)*(-sqr(xa) + 2.*xa*xb - sqr(xb) + sqr(ya - yb)) + 
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.))/
		    (2.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   double dpre_dyb( -(((sqr(ra) - sqr(rb))*(xa - xb)*(ya - yb))/
		      pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );

   double ddisc_dra( (ra*sqr(ya - yb)*(-sqr(ra) + sqr(rb) + sqr(xa) - 2.*xa*xb + 
					 sqr(xb) + sqr(ya) - 2.*ya*yb + sqr(yb)))/
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.) );
   double ddisc_dxa( -(((xa - xb)*sqr(ya - yb)*
			(-pow(ra,4.) + sqr(rb)*
			 (-sqr(rb) + sqr(xa) - 2.*xa*xb + sqr(xb) + 
			  sqr(ya) - 2.*ya*yb + sqr(yb)) + 
			 sqr(ra)*(2.*sqr(rb) + sqr(xa) - 2.*xa*xb + sqr(xb) + 
				    sqr(ya) - 2.*ya*yb + sqr(yb))))/
		       pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.)) );
   double ddisc_dya( ((-pow(4.*sqr(ra)*(xa - xb) - 
			    4.*(sqr(rb)*(xa - xb) + 
			       (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
					  sqr(ya - yb))),2.) + 
		       4.*(-((xa + xb)*(4.*sqr(ra)*(xa - xb) - 
				       4.*(sqr(rb)*(xa - xb) + 
					  (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
						     sqr(ya - yb))))) - 
			  4.*(-sqr(ra) - sqr(rb) + sqr(xa) + sqr(xb) + 
			     sqr(ya - yb))*
			  (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) - 
			  2.*(pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			     2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			     2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			     pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			     4.*sqr(rb)*sqr(ya - yb)))*
		       (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) + 
		       16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		       (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			4.*sqr(rb)*sqr(ya - yb)))*(ya - yb))/
		     (1.6*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.)) );
   double ddisc_drb( (rb*sqr(ya - yb)*(sqr(ra) - sqr(rb) + sqr(xa) - 2.*xa*xb + 
					 sqr(xb) + sqr(ya) - 2.*ya*yb + sqr(yb)))/
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.) );
   double ddisc_dxb( ((xa - xb)*sqr(ya - yb)*(-pow(ra,4.) + 
						sqr(rb)*(-sqr(rb) + sqr(xa)
							   - 2.*xa*xb + sqr(xb) + 
							   sqr(ya) - 2.*ya*yb + sqr(yb)) + 
						sqr(ra)*(2.*sqr(rb) + sqr(xa)
							   - 2.*xa*xb + sqr(xb) + 
							   sqr(ya) - 2.*ya*yb + sqr(yb))))/
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.) );
   double ddisc_dyb( ((pow(4.*sqr(ra)*(xa - xb) - 
			   4.*(sqr(rb)*(xa - xb) + 
			      (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
					 sqr(ya - yb))),2.) + 
		       4.*((xa + xb)*(4.*sqr(ra)*(xa - xb) - 
				     4.*(sqr(rb)*(xa - xb) + 
					(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
						   sqr(ya - yb)))) - 
			  4.*(sqr(ra) + sqr(rb) - sqr(xa) - sqr(xb) - 
			     sqr(ya - yb))*
			  (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) + 
			  2.*(pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			     2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			     2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			     pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			     4.*sqr(rb)*sqr(ya - yb)))*
		       (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) - 
		       16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		       (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			4.*sqr(rb)*sqr(ya - yb)))*(ya - yb))/
		     (1.6*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.)) );

   double dx_dcirc[kNumCirc];
   double dy_dcirc[kNumCirc];

   if ( which_num == 1 ) {
      dx_dcirc[kRa] = dpre_dra + ddisc_dra / 2. / sqrt( disc );
      dx_dcirc[kXa] = dpre_dxa + ddisc_dxa / 2. / sqrt( disc );
      dx_dcirc[kYa] = dpre_dya + ddisc_dya / 2. / sqrt( disc );
      dx_dcirc[kRb] = dpre_drb + ddisc_drb / 2. / sqrt( disc );
      dx_dcirc[kXb] = dpre_dxb + ddisc_dxb / 2. / sqrt( disc );
      dx_dcirc[kYb] = dpre_dyb + ddisc_dyb / 2. / sqrt( disc );
   }
   else {
      dx_dcirc[kRa] = dpre_dra - ddisc_dra / 2. / sqrt( disc );
      dx_dcirc[kXa] = dpre_dxa - ddisc_dxa / 2. / sqrt( disc );
      dx_dcirc[kYa] = dpre_dya - ddisc_dya / 2. / sqrt( disc );
      dx_dcirc[kRb] = dpre_drb - ddisc_drb / 2. / sqrt( disc );
      dx_dcirc[kXb] = dpre_dxb - ddisc_dxb / 2. / sqrt( disc );
      dx_dcirc[kYb] = dpre_dyb - ddisc_dyb / 2. / sqrt( disc );
   }

   if ( which_let == 'a' ) {
      dy_dcirc[kRa] = -(x - xb) * dx_dcirc[kRa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXa] = -(x - xb) * dx_dcirc[kXa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYa] = -(x - xb) * dx_dcirc[kYa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kRb] = (rb - (x - xb)*dx_dcirc[kRb]) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXb] = -(x - xb) * (dx_dcirc[kXb] - 1.) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYb] = 1. - (x - xb)*dx_dcirc[kYb]/sqrt( sqr(rb) - sqr(x - xb) );
   }
   else {
      dy_dcirc[kRa] = (x - xb) * dx_dcirc[kRa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXa] = (x - xb) * dx_dcirc[kXa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYa] = (x - xb) * dx_dcirc[kYa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kRb] = (-rb + (x - xb)*dx_dcirc[kRb]) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXb] = (x - xb) * (dx_dcirc[kXb] - 1.) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYb] = 1. + (x - xb)*dx_dcirc[kYb]/sqrt( sqr(rb) - sqr(x - xb) );
   }

   // This is a Jacobian for transforming between circle variables and
   // tracking variables
   double dcirc_dtrack[kNumCirc][kNumTrack];
   int i, j;
   for ( i = 0;  i < kNumCirc;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ )
	 dcirc_dtrack[i][j] = 0;
   
   dcirc_dtrack[kRa][kCurva] = -1. / 2. / sqr( a.curvature() );

   dcirc_dtrack[kXa][kCurva] = -dcirc_dtrack[kRa][kCurva] * sin( a.phi0() );
   dcirc_dtrack[kXa][kD0a]   = -sin( a.phi0() );
   dcirc_dtrack[kXa][kPhi0a] = -(ra + a.d0()) * cos( a.phi0() );

   dcirc_dtrack[kYa][kCurva] = dcirc_dtrack[kRa][kCurva] * cos( a.phi0() );
   dcirc_dtrack[kYa][kD0a]   = cos( a.phi0() );
   dcirc_dtrack[kYa][kPhi0a] = -(ra + a.d0()) * sin( a.phi0() );

   dcirc_dtrack[kRb][kCurvb] = -1. / 2. / sqr( b.curvature() );

   dcirc_dtrack[kXb][kCurvb] = -dcirc_dtrack[kRb][kCurvb] * sin( b.phi0() );
   dcirc_dtrack[kXb][kD0b]   = -sin( b.phi0() );
   dcirc_dtrack[kXb][kPhi0b] = -(rb + b.d0()) * cos( b.phi0() );

   dcirc_dtrack[kYb][kCurvb] = dcirc_dtrack[kRb][kCurvb] * cos( b.phi0() );
   dcirc_dtrack[kYb][kD0b]   = cos( b.phi0() );
   dcirc_dtrack[kYb][kPhi0b] = -(rb + b.d0()) * sin( b.phi0() );

   // Finally--- derivatives of x and y in terms of tracking variables!
   double dx_dtrack[kNumTrack];
   double dy_dtrack[kNumTrack];
   for ( j = 0;  j < kNumTrack;  j++ ) {
      dx_dtrack[j] = 0;
      dy_dtrack[j] = 0;
   }

   for ( i = 0;  i < kNumCirc;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ ) {
	 dx_dtrack[j] += dx_dcirc[i] * dcirc_dtrack[i][j];
	 dy_dtrack[j] += dy_dcirc[i] * dcirc_dtrack[i][j];
      }

   // Propogating errors is a similarity transform. First we need a
   // transformation matrix.
   double sigma[kNumTrack][kNumTrack];
   for ( i = 0;  i < kNumTrack;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ )
	 sigma[i][j] = 0;

   sigma[kCurva][kCurva] = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kCurvature);
   sigma[kCurva][kD0a]   = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kD0);
   sigma[kCurva][kPhi0a] = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kPhi0);
   sigma[kD0a][kCurva]   = a.errorMatrix()(KTHelix::kD0, KTHelix::kCurvature);
   sigma[kD0a][kD0a]     = a.errorMatrix()(KTHelix::kD0, KTHelix::kD0);
   sigma[kD0a][kPhi0a]   = a.errorMatrix()(KTHelix::kD0, KTHelix::kPhi0);
   sigma[kPhi0a][kCurva] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kCurvature);
   sigma[kPhi0a][kD0a]   = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kD0);
   sigma[kPhi0a][kPhi0a] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kPhi0);

   sigma[kCurvb][kCurvb] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kCurvature);
   sigma[kCurvb][kD0b]   = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kD0);
   sigma[kCurvb][kPhi0b] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kPhi0);
   sigma[kD0b][kCurvb]   = b.errorMatrix()(KTHelix::kD0, KTHelix::kCurvature);
   sigma[kD0b][kD0b]     = b.errorMatrix()(KTHelix::kD0, KTHelix::kD0);
   sigma[kD0b][kPhi0b]   = b.errorMatrix()(KTHelix::kD0, KTHelix::kPhi0);
   sigma[kPhi0b][kCurvb] = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kCurvature);
   sigma[kPhi0b][kD0b]   = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kD0);
   sigma[kPhi0b][kPhi0b] = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kPhi0);

   double x_std[kNumTrack];  // (sigma-transformed derivatives... errormatrix * dx_dtrack)
   double y_std[kNumTrack];  // (sigma-transformed derivatives... errormatrix * dy_dtrack)
   for ( j = 0;  j < kNumTrack;  j++ ) {
      x_std[j] = 0;  // (it's better than "vd"--- vector of derivatives...)
      y_std[j] = 0;
   }   

   for ( i = 0;  i < kNumTrack;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ ) {
	 if ( dx_dtrack[i] != 0. )
	    x_std[j] += sigma[i][j] * dx_dtrack[i];
	 if ( dy_dtrack[i] != 0. )
	    y_std[j] += sigma[i][j] * dy_dtrack[i];
      }

   double sig2x(0.);
   double sig2y(0.);
//     double sig2xy(0.);

   for ( i = 0;  i < kNumTrack;  i++ ) {
      sig2x += dx_dtrack[i] * x_std[i];
      sig2y += dy_dtrack[i] * y_std[i];
//        sig2xy += dy_dtrack[i] * x_std[i];
   }

   sigx = sqrt(sig2x);
   sigy = sqrt(sig2y);
}

DABoolean TwoPionsProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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

