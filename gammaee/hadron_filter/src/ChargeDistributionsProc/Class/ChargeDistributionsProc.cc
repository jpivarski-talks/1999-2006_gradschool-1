// -*- C++ -*-
//
// Package:     ChargeDistributionsProc
// Module:      ChargeDistributionsProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Oct 28 11:11:59 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ChargeDistributionsProc/ChargeDistributionsProc.h"
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
static const char* const kFacilityString = "Processor.ChargeDistributionsProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ChargeDistributionsProc::ChargeDistributionsProc( void )               // anal1
   : Processor( "ChargeDistributionsProc" )
   , m_explicitBeamSpot( "explicitBeamSpot", this, false )
   , m_beamX( "beamX", this, 0. )
   , m_beamY( "beamY", this, 0. )
   , m_beamZ( "beamZ", this, 0. )
   , m_beam_x(0.)
   , m_beam_y(0.)
   , m_beam_z(0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ChargeDistributionsProc::event,    Stream::kEvent );
   bind( &ChargeDistributionsProc::beginRun, Stream::kBeginRun );
   //bind( &ChargeDistributionsProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

ChargeDistributionsProc::~ChargeDistributionsProc()                    // anal5
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
ChargeDistributionsProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ChargeDistributionsProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ChargeDistributionsProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_track_z0 = iHistoManager.histogram(
      100, "Track Z0", 100, -0.2, 0.2 );
   m_track_z0_far = iHistoManager.histogram(
      103, "Track Z0", 100, -1.0, 1.0 );
   m_track_z0_minus_wciz = iHistoManager.histogram(
      200, "Track Z0 - Event Z0", 100, -0.1, 0.1 );
   m_track_z0_minus_wciz_far = iHistoManager.histogram(
      203, "Track Z0 - Event Z0", 100, -1.0, 1.0 );
   m_track_d0 = iHistoManager.histogram(
      300, "Track D0", 100, -0.02, 0.02 );
   m_track_d0_far = iHistoManager.histogram(
      303, "Track D0", 100, -0.5, 0.5 );
   m_track_p = iHistoManager.histogram(
      400, "Track Momentum Magnitude", 100, 0., 3. );
   m_track_pperp = iHistoManager.histogram(
      500, "Track Momentum Perp", 100, 0., 3. );
   m_track_pz = iHistoManager.histogram(
      600, "Track Momentum Z", 100, -2., 2. );
   m_track_chi2 = iHistoManager.histogram(
      700, "Track Chi2", 100, 0., 300 );
   m_track_chi2_close = iHistoManager.histogram(
      800, "Track Chi2", 100, -0.05, 0.05 );
   m_track_chi2dof = iHistoManager.histogram(
      900, "Track Chi2/DOF", 100, 0., 10. );
   m_track_hitfrac = iHistoManager.histogram(
      1000, "Track Hit Fraction", 100, 0., 1.5 );
   m_track_hitexp = iHistoManager.histogram(
      1100, "Track Hits Expected", 60, -0.5, 59.5 );
   m_track_fitabort = iHistoManager.histogram(
      1200, "Track Fit Abort", 2, -0.5, 1.5 );

   m_track_z0_pos = iHistoManager.histogram(
      101, "Positive Track Z0", 100, -0.2, 0.2 );
   m_track_z0_far_pos = iHistoManager.histogram(
      104, "Positive Track Z0", 100, -1.0, 1.0 );
   m_track_z0_minus_wciz_pos = iHistoManager.histogram(
      201, "Positive Track Z0 - Event Z0", 100, -0.1, 0.1 );
   m_track_z0_minus_wciz_far_pos = iHistoManager.histogram(
      204, "Positive Track Z0 - Event Z0", 100, -1.0, 1.0 );
   m_track_d0_pos = iHistoManager.histogram(
      301, "Positive Track D0", 100, -0.02, 0.02 );
   m_track_d0_far_pos = iHistoManager.histogram(
      304, "Positive Track D0", 100, -0.5, 0.5 );
   m_track_p_pos = iHistoManager.histogram(
      401, "Positive Track Momentum Magnitude", 100, 0., 3. );
   m_track_pperp_pos = iHistoManager.histogram(
      501, "Positive Track Momentum Perp", 100, 0., 3. );
   m_track_pz_pos = iHistoManager.histogram(
      601, "Positive Track Momentum Z", 100, -2., 2. );
   m_track_chi2_pos = iHistoManager.histogram(
      701, "Positive Track Chi2", 100, 0., 300 );
   m_track_chi2_close_pos = iHistoManager.histogram(
      801, "Positive Track Chi2", 100, -0.05, 0.05 );
   m_track_chi2dof_pos = iHistoManager.histogram(
      901, "Positive Track Chi2/DOF", 100, 0., 10. );
   m_track_hitfrac_pos = iHistoManager.histogram(
      1001, "Positive Track Hit Fraction", 100, 0., 1.5 );
   m_track_hitexp_pos = iHistoManager.histogram(
      1101, "Positive Track Hits Expected", 60, -0.5, 59.5 );
   m_track_fitabort_pos = iHistoManager.histogram(
      1201, "Positive Track Fit Abort", 2, -0.5, 1.5 );

   m_track_z0_neg = iHistoManager.histogram(
      102, "Negative Track Z0", 100, -0.2, 0.2 );
   m_track_z0_far_neg = iHistoManager.histogram(
      105, "Negative Track Z0", 100, -1.0, 1.0 );
   m_track_z0_minus_wciz_neg = iHistoManager.histogram(
      202, "Negative Track Z0 - Event Z0", 100, -0.1, 0.1 );
   m_track_z0_minus_wciz_far_neg = iHistoManager.histogram(
      205, "Negative Track Z0 - Event Z0", 100, -1.0, 1.0 );
   m_track_d0_neg = iHistoManager.histogram(
      302, "Negative Track D0", 100, -0.02, 0.02 );
   m_track_d0_far_neg = iHistoManager.histogram(
      305, "Negative Track D0", 100, -0.5, 0.5 );
   m_track_p_neg = iHistoManager.histogram(
      402, "Negative Track Momentum Magnitude", 100, 0., 3. );
   m_track_pperp_neg = iHistoManager.histogram(
      502, "Negative Track Momentum Perp", 100, 0., 3. );
   m_track_pz_neg = iHistoManager.histogram(
      602, "Negative Track Momentum Z", 100, -2., 2. );
   m_track_chi2_neg = iHistoManager.histogram(
      702, "Negative Track Chi2", 100, 0., 300 );
   m_track_chi2_close_neg = iHistoManager.histogram(
      802, "Negative Track Chi2", 100, -0.05, 0.05 );
   m_track_chi2dof_neg = iHistoManager.histogram(
      902, "Negative Track Chi2/DOF", 100, 0., 10. );
   m_track_hitfrac_neg = iHistoManager.histogram(
      1002, "Negative Track Hit Fraction", 100, 0., 1.5 );
   m_track_hitexp_neg = iHistoManager.histogram(
      1102, "Negative Track Hits Expected", 60, -0.5, 59.5 );
   m_track_fitabort_neg = iHistoManager.histogram(
      1202, "Negative Track Fit Abort", 2, -0.5, 1.5 );

   m_charge = iHistoManager.histogram(
      1, "Charge", 21, -10.5, 10.5 );

   m_charge_z0_20cm = iHistoManager.histogram(
      111, "Charge w/ (Z0) .lt. 20 cm", 21, -10.5, 10.5 );
   m_charge_z0_10cm = iHistoManager.histogram(
      112, "Charge w/ (Z0) .lt. 10 cm", 21, -10.5, 10.5 );
   m_charge_z0_5cm = iHistoManager.histogram(
      113, "Charge w/ (Z0) .lt. 5 cm", 21, -10.5, 10.5 );

   m_charge_z0_minus_wciz_10cm = iHistoManager.histogram(
      211, "Charge w/ (Z0 - Event Z0) .lt. 10 cm", 21, -10.5, 10.5 );
   m_charge_z0_minus_wciz_5cm = iHistoManager.histogram(
      212, "Charge w/ (Z0 - Event Z0) .lt. 5 cm", 21, -10.5, 10.5 );
   m_charge_z0_minus_wciz_25mm = iHistoManager.histogram(
      213, "Charge w/ (Z0 - Event Z0) .lt. 2.5 cm", 21, -10.5, 10.5 );

   m_charge_d0_20mm = iHistoManager.histogram(
      311, "Charge w/ (D0) .lt. 20 mm", 21, -10.5, 10.5 );
   m_charge_d0_10mm = iHistoManager.histogram(
      312, "Charge w/ (D0) .lt. 10 mm", 21, -10.5, 10.5 );
   m_charge_d0_5mm = iHistoManager.histogram(
      313, "Charge w/ (D0) .lt. 5 mm", 21, -10.5, 10.5 );

   m_charge_p_100MeV = iHistoManager.histogram(
      411, "Charge w/ Momentum Magnitude .gt. 100 MeV", 21, -10.5, 10.5 );
   m_charge_p_200MeV = iHistoManager.histogram(
      412, "Charge w/ Momentum Magnitude .gt. 200 MeV", 21, -10.5, 10.5 );
   m_charge_p_300MeV = iHistoManager.histogram(
      413, "Charge w/ Momentum Magnitude .gt. 300 MeV", 21, -10.5, 10.5 );
   m_charge_p_10GeV = iHistoManager.histogram(
      414, "Charge w/ Momentum Magnitude .lt. 10 GeV", 21, -10.5, 10.5 );
   m_charge_p_6GeV = iHistoManager.histogram(
      415, "Charge w/ Momentum Magnitude .lt. 6 GeV", 21, -10.5, 10.5 );
   m_charge_p_5GeV = iHistoManager.histogram(
      416, "Charge w/ Momentum Magnitude .lt. 5 GeV", 21, -10.5, 10.5 );

   m_charge_pperp_100MeV = iHistoManager.histogram(
      511, "Charge w/ Momentum Perp .gt. 100 MeV", 21, -10.5, 10.5 );
   m_charge_pperp_200MeV = iHistoManager.histogram(
      512, "Charge w/ Momentum Perp .gt. 200 MeV", 21, -10.5, 10.5 );
   m_charge_pperp_300MeV = iHistoManager.histogram(
      513, "Charge w/ Momentum Perp .gt. 300 MeV", 21, -10.5, 10.5 );
   m_charge_pperp_3GeV = iHistoManager.histogram(
      514, "Charge w/ Momentum Perp .lt. 3 GeV", 21, -10.5, 10.5 );
   m_charge_pperp_2GeV = iHistoManager.histogram(
      515, "Charge w/ Momentum Perp .lt. 2 GeV", 21, -10.5, 10.5 );
   m_charge_pperp_1GeV = iHistoManager.histogram(
      516, "Charge w/ Momentum Perp .lt. 1 GeV", 21, -10.5, 10.5 );

   m_charge_pz_200MeV = iHistoManager.histogram(
      611, "Charge w/ (Momentum Z) .lt. 200 MeV", 21, -10.5, 10.5 );
   m_charge_pz_100MeV = iHistoManager.histogram(
      612, "Charge w/ (Momentum Z) .lt. 100 MeV", 21, -10.5, 10.5 );
   m_charge_pz_50MeV = iHistoManager.histogram(
      613, "Charge w/ (Momentum Z) .lt. 50 MeV", 21, -10.5, 10.5 );

   m_charge_chi2_300 = iHistoManager.histogram(
      711, "Charge w/ Chi2 .lt. 300", 21, -10.5, 10.5 );
   m_charge_chi2_200 = iHistoManager.histogram(
      712, "Charge w/ Chi2 .lt. 200", 21, -10.5, 10.5 );
   m_charge_chi2_100 = iHistoManager.histogram(
      713, "Charge w/ Chi2 .lt. 100", 21, -10.5, 10.5 );

   m_charge_chi2_0 = iHistoManager.histogram(
      811, "Charge w/ Chi2 .gt. 0", 21, -10.5, 10.5 );
   m_charge_chi2_0_01 = iHistoManager.histogram(
      812, "Charge w/ Chi2 .gt. 0.01", 21, -10.5, 10.5 );

   m_charge_chi2dof_10 = iHistoManager.histogram(
      911, "Charge w/ Chi2/DOF .lt. 10", 21, -10.5, 10.5 );
   m_charge_chi2dof_5 = iHistoManager.histogram(
      912, "Charge w/ Chi2/DOF .lt. 5", 21, -10.5, 10.5 );
   m_charge_chi2dof_2p5 = iHistoManager.histogram(
      913, "Charge w/ Chi2/DOF .lt. 2.5", 21, -10.5, 10.5 );

   m_charge_hitfrac_notinf = iHistoManager.histogram(
      1011, "Charge w/ Hit Fraction .lt. inf", 21, -10.5, 10.5 );
   m_charge_hitfrac_notinf_5 = iHistoManager.histogram(
      1012, "Charge w/ Hit Fraction .lt. inf AND .gt. 0.5", 21, -10.5, 10.5 );
   m_charge_hitfrac_notinf_5_12 = iHistoManager.histogram(
      1013, "Charge w/ Hit Fraction .lt. inf AND .gt. 0.5 AND .lt. 1.2", 21, -10.5, 10.5 );

   m_charge_hitexp_0 = iHistoManager.histogram(
      1111, "Charge w/ Hits Expected .gt. 0", 21, -10.5, 10.5 );
   m_charge_hitexp_10 = iHistoManager.histogram(
      1112, "Charge w/ Hits Expected .gt. 10", 21, -10.5, 10.5 );
   m_charge_hitexp_20 = iHistoManager.histogram(
      1113, "Charge w/ Hits Expected .gt. 20", 21, -10.5, 10.5 );

   m_charge_fitabort_no = iHistoManager.histogram(
      1211, "Charge w/ No Fit Abort", 21, -10.5, 10.5 );

   m_asycharge = iHistoManager.profile(
      2, "AsyCharge", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_asycharge_z0_20cm = iHistoManager.profile(
      121, "AsyCharge w/ (Z0) .lt. 20 cm", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_z0_10cm = iHistoManager.profile(
      122, "AsyCharge w/ (Z0) .lt. 10 cm", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_z0_5cm = iHistoManager.profile(
      123, "AsyCharge w/ (Z0) .lt. 5 cm", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );

   m_asycharge_z0_minus_wciz_10cm = iHistoManager.profile(
      221, "AsyCharge w/ (Z0 - Event Z0) .lt. 10 cm", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_z0_minus_wciz_5cm = iHistoManager.profile(
      222, "AsyCharge w/ (Z0 - Event Z0) .lt. 5 cm", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_z0_minus_wciz_25mm = iHistoManager.profile(
      223, "AsyCharge w/ (Z0 - Event Z0) .lt. 2.5 cm", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );

   m_asycharge_d0_20mm = iHistoManager.profile(
      321, "AsyCharge w/ (D0) .lt. 20 mm", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_d0_10mm = iHistoManager.profile(
      322, "AsyCharge w/ (D0) .lt. 10 mm", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_d0_5mm = iHistoManager.profile(
      323, "AsyCharge w/ (D0) .lt. 5 mm", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_asycharge_p_100MeV = iHistoManager.profile(
      421, "AsyCharge w/ Momentum Magnitude .gt. 100 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_p_200MeV = iHistoManager.profile(
      422, "AsyCharge w/ Momentum Magnitude .gt. 200 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_p_300MeV = iHistoManager.profile(
      423, "AsyCharge w/ Momentum Magnitude .gt. 300 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_p_10GeV = iHistoManager.profile(
      424, "AsyCharge w/ Momentum Magnitude .lt. 10 GeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_p_6GeV = iHistoManager.profile(
      425, "AsyCharge w/ Momentum Magnitude .lt. 6 GeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_p_5GeV = iHistoManager.profile(
      426, "AsyCharge w/ Momentum Magnitude .lt. 5 GeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );

   m_asycharge_pperp_100MeV = iHistoManager.profile(
      521, "AsyCharge w/ Momentum Perp .gt. 100 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pperp_200MeV = iHistoManager.profile(
      522, "AsyCharge w/ Momentum Perp .gt. 200 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pperp_300MeV = iHistoManager.profile(
      523, "AsyCharge w/ Momentum Perp .gt. 300 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pperp_3GeV = iHistoManager.profile(
      524, "AsyCharge w/ Momentum Perp .lt. 3 GeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pperp_2GeV = iHistoManager.profile(
      525, "AsyCharge w/ Momentum Perp .lt. 2 GeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pperp_1GeV = iHistoManager.profile(
      526, "AsyCharge w/ Momentum Perp .lt. 1 GeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );

   m_asycharge_pz_200MeV = iHistoManager.profile(
      621, "AsyCharge w/ (Momentum Z) .lt. 200 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pz_100MeV = iHistoManager.profile(
      622, "AsyCharge w/ (Momentum Z) .lt. 100 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_pz_50MeV = iHistoManager.profile(
      623, "AsyCharge w/ (Momentum Z) .lt. 50 MeV", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );

   m_asycharge_chi2_300 = iHistoManager.profile(
      721, "AsyCharge w/ Chi2 .lt. 300", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_chi2_200 = iHistoManager.profile(
      722, "AsyCharge w/ Chi2 .lt. 200", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_chi2_100 = iHistoManager.profile(
      723, "AsyCharge w/ Chi2 .lt. 100", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_asycharge_chi2_0 = iHistoManager.profile(
      821, "AsyCharge w/ Chi2 .gt. 0", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_chi2_0_01 = iHistoManager.profile(
      822, "AsyCharge w/ Chi2 .gt. 0.01", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_asycharge_chi2dof_10 = iHistoManager.profile(
      921, "AsyCharge w/ Chi2/DOF .lt. 10", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_chi2dof_5 = iHistoManager.profile(
      922, "AsyCharge w/ Chi2/DOF .lt. 5", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_chi2dof_2p5 = iHistoManager.profile(
      923, "AsyCharge w/ Chi2/DOF .lt. 2.5", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_asycharge_hitfrac_notinf = iHistoManager.profile(
      1021, "AsyCharge w/ Hit Fraction .lt. inf", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_hitfrac_notinf_5 = iHistoManager.profile(
      1022, "AsyCharge w/ Hit Fraction .lt. inf AND .gt. 0.5", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );
   m_asycharge_hitfrac_notinf_5_12 = iHistoManager.profile(
      1023, "AsyCharge w/ Hit Fraction .lt. inf AND .gt. 0.5 AND .lt. 1.2", 10, 0.5, 10.5, -1000, 1000,
      HIHistProf::kErrorOnMean );

   m_asycharge_hitexp_0 = iHistoManager.profile(
      1121, "AsyCharge w/ Hits Expected .gt. 0", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_hitexp_10 = iHistoManager.profile(
      1122, "AsyCharge w/ Hits Expected .gt. 10", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );
   m_asycharge_hitexp_20 = iHistoManager.profile(
      1123, "AsyCharge w/ Hits Expected .gt. 20", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_asycharge_fitabort_no = iHistoManager.profile(
      1221, "AsyCharge w/ No Fit Abort", 10, 0.5, 10.5, -1000, 1000, HIHistProf::kErrorOnMean );

   m_nposneg = iHistoManager.histogram(
      3, "Num Positive VS Negative", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_z0_20cm = iHistoManager.histogram(
      131, "Num Positive VS Negative w/ (Z0) .lt. 20 cm", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_z0_10cm = iHistoManager.histogram(
      132, "Num Positive VS Negative w/ (Z0) .lt. 10 cm", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_z0_5cm = iHistoManager.histogram(
      133, "Num Positive VS Negative w/ (Z0) .lt. 5 cm", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_z0_minus_wciz_10cm = iHistoManager.histogram(
      231, "Num Positive VS Negative w/ (Z0 - Event Z0) .lt. 10 cm", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_z0_minus_wciz_5cm = iHistoManager.histogram(
      232, "Num Positive VS Negative w/ (Z0 - Event Z0) .lt. 5 cm", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_z0_minus_wciz_25mm = iHistoManager.histogram(
      233, "Num Positive VS Negative w/ (Z0 - Event Z0) .lt. 2.5 cm", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_d0_20mm = iHistoManager.histogram(
      331, "Num Positive VS Negative w/ (D0) .lt. 20 mm", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_d0_10mm = iHistoManager.histogram(
      332, "Num Positive VS Negative w/ (D0) .lt. 10 mm", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_d0_5mm = iHistoManager.histogram(
      333, "Num Positive VS Negative w/ (D0) .lt. 5 mm", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_p_100MeV = iHistoManager.histogram(
      431, "Num Positive VS Negative w/ Momentum Magnitude .gt. 100 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_p_200MeV = iHistoManager.histogram(
      432, "Num Positive VS Negative w/ Momentum Magnitude .gt. 200 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_p_300MeV = iHistoManager.histogram(
      433, "Num Positive VS Negative w/ Momentum Magnitude .gt. 300 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_p_10GeV = iHistoManager.histogram(
      434, "Num Positive VS Negative w/ Momentum Magnitude .lt. 10 GeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_p_6GeV = iHistoManager.histogram(
      435, "Num Positive VS Negative w/ Momentum Magnitude .lt. 6 GeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_p_5GeV = iHistoManager.histogram(
      436, "Num Positive VS Negative w/ Momentum Magnitude .lt. 5 GeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_pperp_100MeV = iHistoManager.histogram(
      531, "Num Positive VS Negative w/ Momentum Perp .gt. 100 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pperp_200MeV = iHistoManager.histogram(
      532, "Num Positive VS Negative w/ Momentum Perp .gt. 200 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pperp_300MeV = iHistoManager.histogram(
      533, "Num Positive VS Negative w/ Momentum Perp .gt. 300 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pperp_3GeV = iHistoManager.histogram(
      534, "Num Positive VS Negative w/ Momentum Perp .lt. 3 GeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pperp_2GeV = iHistoManager.histogram(
      535, "Num Positive VS Negative w/ Momentum Perp .lt. 2 GeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pperp_1GeV = iHistoManager.histogram(
      536, "Num Positive VS Negative w/ Momentum Perp .lt. 1 GeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_pz_200MeV = iHistoManager.histogram(
      631, "Num Positive VS Negative w/ (Momentum Z) .lt. 200 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pz_100MeV = iHistoManager.histogram(
      632, "Num Positive VS Negative w/ (Momentum Z) .lt. 100 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_pz_50MeV = iHistoManager.histogram(
      633, "Num Positive VS Negative w/ (Momentum Z) .lt. 50 MeV", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_chi2_300 = iHistoManager.histogram(
      731, "Num Positive VS Negative w/ Chi2 .lt. 300", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_chi2_200 = iHistoManager.histogram(
      732, "Num Positive VS Negative w/ Chi2 .lt. 200", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_chi2_100 = iHistoManager.histogram(
      733, "Num Positive VS Negative w/ Chi2 .lt. 100", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_chi2_0 = iHistoManager.histogram(
      831, "Num Positive VS Negative w/ Chi2 .gt. 0", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_chi2_0_01 = iHistoManager.histogram(
      832, "Num Positive VS Negative w/ Chi2 .gt. 0.01", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_chi2dof_10 = iHistoManager.histogram(
      931, "Num Positive VS Negative w/ Chi2/DOF .lt. 10", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_chi2dof_5 = iHistoManager.histogram(
      932, "Num Positive VS Negative w/ Chi2/DOF .lt. 5", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_chi2dof_2p5 = iHistoManager.histogram(
      933, "Num Positive VS Negative w/ Chi2/DOF .lt. 2.5", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_hitfrac_notinf = iHistoManager.histogram(
      1031, "Num Positive VS Negative w/ Hit Fraction .lt. inf", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_hitfrac_notinf_5 = iHistoManager.histogram(
      1032, "Num Positive VS Negative w/ Hit Fraction .lt. inf AND .gt. 0.5", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_hitfrac_notinf_5_12 = iHistoManager.histogram(
      1033, "Num Positive VS Negative w/ Hit Fraction .lt. inf AND .gt. 0.5 AND .lt. 1.2", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_hitexp_0 = iHistoManager.histogram(
      1131, "Num Positive VS Negative w/ Hits Expected .gt. 0", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_hitexp_10 = iHistoManager.histogram(
      1132, "Num Positive VS Negative w/ Hits Expected .gt. 10", 41, -0.5, 40.5, 41, -0.5, 40.5 );
   m_nposneg_hitexp_20 = iHistoManager.histogram(
      1133, "Num Positive VS Negative w/ Hits Expected .gt. 20", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   m_nposneg_fitabort_no = iHistoManager.histogram(
      1231, "Num Positive VS Negative w/ No Fit Abort", 41, -0.5, 40.5, 41, -0.5, 40.5 );

   

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ChargeDistributionsProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   double wciz( get_weighted_ciz( iFrame ) );

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ) , tracks );
   FATable< NavTrack >::const_iterator tracks_begin = tracks.begin();
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   int charge(0);
   int charge_z0_20cm(0);
   int charge_z0_10cm(0);
   int charge_z0_5cm(0);
   int charge_z0_minus_wciz_10cm(0);
   int charge_z0_minus_wciz_5cm(0);
   int charge_z0_minus_wciz_25mm(0);
   int charge_d0_20mm(0);
   int charge_d0_10mm(0);
   int charge_d0_5mm(0);
   int charge_p_100MeV(0);
   int charge_p_200MeV(0);
   int charge_p_300MeV(0);
   int charge_p_10GeV(0);
   int charge_p_6GeV(0);
   int charge_p_5GeV(0);
   int charge_pperp_100MeV(0);
   int charge_pperp_200MeV(0);
   int charge_pperp_300MeV(0);
   int charge_pperp_3GeV(0);
   int charge_pperp_2GeV(0);
   int charge_pperp_1GeV(0);
   int charge_pz_200MeV(0);
   int charge_pz_100MeV(0);
   int charge_pz_50MeV(0);
   int charge_chi2_300(0);
   int charge_chi2_200(0);
   int charge_chi2_100(0);
   int charge_chi2_0(0);
   int charge_chi2_0_01(0);
   int charge_chi2dof_10(0);
   int charge_chi2dof_5(0);
   int charge_chi2dof_2p5(0);
   int charge_hitfrac_notinf(0);
   int charge_hitfrac_notinf_5(0);
   int charge_hitfrac_notinf_5_12(0);
   int charge_hitexp_0(0);
   int charge_hitexp_10(0);
   int charge_hitexp_20(0);
   int charge_fitabort_no(0);

   int nump(0), numn(0);
   int nump_z0_20cm(0), numn_z0_20cm(0);
   int nump_z0_10cm(0), numn_z0_10cm(0);
   int nump_z0_5cm(0), numn_z0_5cm(0);
   int nump_z0_minus_wciz_10cm(0), numn_z0_minus_wciz_10cm(0);
   int nump_z0_minus_wciz_5cm(0), numn_z0_minus_wciz_5cm(0);
   int nump_z0_minus_wciz_25mm(0), numn_z0_minus_wciz_25mm(0);
   int nump_d0_20mm(0), numn_d0_20mm(0);
   int nump_d0_10mm(0), numn_d0_10mm(0);
   int nump_d0_5mm(0), numn_d0_5mm(0);
   int nump_p_100MeV(0), numn_p_100MeV(0);
   int nump_p_200MeV(0), numn_p_200MeV(0);
   int nump_p_300MeV(0), numn_p_300MeV(0);
   int nump_p_10GeV(0), numn_p_10GeV(0);
   int nump_p_6GeV(0), numn_p_6GeV(0);
   int nump_p_5GeV(0), numn_p_5GeV(0);
   int nump_pperp_100MeV(0), numn_pperp_100MeV(0);
   int nump_pperp_200MeV(0), numn_pperp_200MeV(0);
   int nump_pperp_300MeV(0), numn_pperp_300MeV(0);
   int nump_pperp_3GeV(0), numn_pperp_3GeV(0);
   int nump_pperp_2GeV(0), numn_pperp_2GeV(0);
   int nump_pperp_1GeV(0), numn_pperp_1GeV(0);
   int nump_pz_200MeV(0), numn_pz_200MeV(0);
   int nump_pz_100MeV(0), numn_pz_100MeV(0);
   int nump_pz_50MeV(0), numn_pz_50MeV(0);
   int nump_chi2_300(0), numn_chi2_300(0);
   int nump_chi2_200(0), numn_chi2_200(0);
   int nump_chi2_100(0), numn_chi2_100(0);
   int nump_chi2_0(0), numn_chi2_0(0);
   int nump_chi2_0_01(0), numn_chi2_0_01(0);
   int nump_chi2dof_10(0), numn_chi2dof_10(0);
   int nump_chi2dof_5(0), numn_chi2dof_5(0);
   int nump_chi2dof_2p5(0), numn_chi2dof_2p5(0);
   int nump_hitfrac_notinf(0), numn_hitfrac_notinf(0);
   int nump_hitfrac_notinf_5(0), numn_hitfrac_notinf_5(0);
   int nump_hitfrac_notinf_5_12(0), numn_hitfrac_notinf_5_12(0);
   int nump_hitexp_0(0), numn_hitexp_0(0);
   int nump_hitexp_10(0), numn_hitexp_10(0);
   int nump_hitexp_20(0), numn_hitexp_20(0);
   int nump_fitabort_no(0), numn_fitabort_no(0);

   for ( FATable< NavTrack >::const_iterator track_iter = tracks_begin;
         track_iter != tracks_end;
         track_iter++ ) {
      DABoolean positive( track_iter->pionHelix()->curvature() > 0. );
      int track_charge( positive ? 1 : -1 );

      m_track_z0->fill( track_iter->pionHelix()->z0() );
      m_track_z0_far->fill( track_iter->pionHelix()->z0() );
      m_track_z0_minus_wciz->fill( track_iter->pionHelix()->z0() - wciz );
      m_track_z0_minus_wciz_far->fill( track_iter->pionHelix()->z0() - wciz );
      m_track_d0->fill( track_iter->pionHelix()->d0() );
      m_track_d0_far->fill( track_iter->pionHelix()->d0() );
      m_track_p->fill( track_iter->pionFit()->momentum().mag() );
      m_track_pperp->fill( track_iter->pionFit()->momentum().perp() );
      m_track_pz->fill( track_iter->pionFit()->momentum().z() );
      m_track_chi2->fill( track_iter->pionQuality()->chiSquare() );
      m_track_chi2_close->fill( track_iter->pionQuality()->chiSquare() );
      if ( track_iter->pionQuality()->degreesOfFreedom() > 0 )
	 m_track_chi2dof->fill( track_iter->pionQuality()->chiSquare() /
				float( track_iter->pionQuality()->degreesOfFreedom() ) );
      if ( track_iter->pionQuality()->numberHitsExpected() > 0 )
	 m_track_hitfrac->fill( track_iter->pionQuality()->ratioNumberHitsToExpected() );
      m_track_hitexp->fill( float( track_iter->pionQuality()->numberHitsExpected() ) );
      m_track_fitabort->fill( track_iter->pionQuality()->fitAbort() ? 1. : 0. );

      if ( positive ) {
	 m_track_z0_pos->fill( track_iter->pionHelix()->z0() );
	 m_track_z0_far_pos->fill( track_iter->pionHelix()->z0() );
	 m_track_z0_minus_wciz_pos->fill( track_iter->pionHelix()->z0() - wciz );
	 m_track_z0_minus_wciz_far_pos->fill( track_iter->pionHelix()->z0() - wciz );
	 m_track_d0_pos->fill( track_iter->pionHelix()->d0() );
	 m_track_d0_far_pos->fill( track_iter->pionHelix()->d0() );
	 m_track_p_pos->fill( track_iter->pionFit()->momentum().mag() );
	 m_track_pperp_pos->fill( track_iter->pionFit()->momentum().perp() );
	 m_track_pz_pos->fill( track_iter->pionFit()->momentum().z() );
	 m_track_chi2_pos->fill( track_iter->pionQuality()->chiSquare() );
	 m_track_chi2_close_pos->fill( track_iter->pionQuality()->chiSquare() );
	 if ( track_iter->pionQuality()->degreesOfFreedom() > 0 )
	    m_track_chi2dof_pos->fill( track_iter->pionQuality()->chiSquare() /
				   float( track_iter->pionQuality()->degreesOfFreedom() ) );
	 if ( track_iter->pionQuality()->numberHitsExpected() > 0 )
	    m_track_hitfrac_pos->fill( track_iter->pionQuality()->ratioNumberHitsToExpected() );
	 m_track_hitexp_pos->fill( float( track_iter->pionQuality()->numberHitsExpected() ) );
	 m_track_fitabort_pos->fill( track_iter->pionQuality()->fitAbort() ? 1. : 0. );
      } else {
	 m_track_z0_neg->fill( track_iter->pionHelix()->z0() );
	 m_track_z0_far_neg->fill( track_iter->pionHelix()->z0() );
	 m_track_z0_minus_wciz_neg->fill( track_iter->pionHelix()->z0() - wciz );
	 m_track_z0_minus_wciz_far_neg->fill( track_iter->pionHelix()->z0() - wciz );
	 m_track_d0_neg->fill( track_iter->pionHelix()->d0() );
	 m_track_d0_far_neg->fill( track_iter->pionHelix()->d0() );
	 m_track_p_neg->fill( track_iter->pionFit()->momentum().mag() );
	 m_track_pperp_neg->fill( track_iter->pionFit()->momentum().perp() );
	 m_track_pz_neg->fill( track_iter->pionFit()->momentum().z() );
	 m_track_chi2_neg->fill( track_iter->pionQuality()->chiSquare() );
	 m_track_chi2_close_neg->fill( track_iter->pionQuality()->chiSquare() );
	 if ( track_iter->pionQuality()->degreesOfFreedom() > 0 )
	    m_track_chi2dof_neg->fill( track_iter->pionQuality()->chiSquare() /
				   float( track_iter->pionQuality()->degreesOfFreedom() ) );
	 if ( track_iter->pionQuality()->numberHitsExpected() > 0 )
	    m_track_hitfrac_neg->fill( track_iter->pionQuality()->ratioNumberHitsToExpected() );
	 m_track_hitexp_neg->fill( float( track_iter->pionQuality()->numberHitsExpected() ) );
	 m_track_fitabort_neg->fill( track_iter->pionQuality()->fitAbort() ? 1. : 0. );
      } // end if track is positive/negative

      charge += track_charge;
      ( positive ? nump++ : numn++ );

      if ( abs( track_iter->pionHelix()->z0() ) < 0.20 ) {
	 charge_z0_20cm += track_charge;
	 ( positive ? nump_z0_20cm++ : numn_z0_20cm++ );
      }
      if ( abs( track_iter->pionHelix()->z0() ) < 0.10 ) {
	 charge_z0_10cm += track_charge;
	 ( positive ? nump_z0_10cm++ : numn_z0_10cm++ );
      }
      if ( abs( track_iter->pionHelix()->z0() ) < 0.05 ) {
	 charge_z0_5cm += track_charge;
	 ( positive ? nump_z0_5cm++ : numn_z0_5cm++ );
      }

      if ( abs( track_iter->pionHelix()->z0() - wciz ) < 0.10 ) {
	 charge_z0_minus_wciz_10cm += track_charge;
	 ( positive ? nump_z0_minus_wciz_10cm++ : numn_z0_minus_wciz_10cm++ );
      }
      if ( abs( track_iter->pionHelix()->z0() - wciz ) < 0.05 ) {
	 charge_z0_minus_wciz_5cm += track_charge;
	 ( positive ? nump_z0_minus_wciz_5cm++ : numn_z0_minus_wciz_5cm++ );
      }
      if ( abs( track_iter->pionHelix()->z0() - wciz ) < 0.025 ) {
	 charge_z0_minus_wciz_25mm += track_charge;
	 ( positive ? nump_z0_minus_wciz_25mm++ : numn_z0_minus_wciz_25mm++ );
      }

      if ( abs( track_iter->pionHelix()->d0() ) < 0.020 ) {
	 charge_d0_20mm += track_charge;
	 ( positive ? nump_d0_20mm++ : numn_d0_20mm++ );
      }
      if ( abs( track_iter->pionHelix()->d0() ) < 0.010 ) {
	 charge_d0_10mm += track_charge;
	 ( positive ? nump_d0_10mm++ : numn_d0_10mm++ );
      }
      if ( abs( track_iter->pionHelix()->d0() ) < 0.005 ) {
	 charge_d0_5mm += track_charge;
	 ( positive ? nump_d0_5mm++ : numn_d0_5mm++ );
      }

      if ( track_iter->pionFit()->momentum().mag() > 0.100 ) {
	 charge_p_100MeV += track_charge;
	 ( positive ? nump_p_100MeV++ : numn_p_100MeV++ );
      }
      if ( track_iter->pionFit()->momentum().mag() > 0.200 ) {
	 charge_p_200MeV += track_charge;
	 ( positive ? nump_p_200MeV++ : numn_p_200MeV++ );
      }
      if ( track_iter->pionFit()->momentum().mag() > 0.300 ) {
	 charge_p_300MeV += track_charge;
	 ( positive ? nump_p_300MeV++ : numn_p_300MeV++ );
      }
      if ( track_iter->pionFit()->momentum().mag() < 10. ) {
	 charge_p_10GeV += track_charge;
	 ( positive ? nump_p_10GeV++ : numn_p_10GeV++ );
      }
      if ( track_iter->pionFit()->momentum().mag() < 6. ) {
	 charge_p_6GeV += track_charge;
	 ( positive ? nump_p_6GeV++ : numn_p_6GeV++ );
      }
      if ( track_iter->pionFit()->momentum().mag() < 5. ) {
	 charge_p_5GeV += track_charge;
	 ( positive ? nump_p_5GeV++ : numn_p_5GeV++ );
      }


      if ( track_iter->pionFit()->momentum().perp() > 0.100 ) {
	 charge_pperp_100MeV += track_charge;
	 ( positive ? nump_pperp_100MeV++ : numn_pperp_100MeV++ );
      }
      if ( track_iter->pionFit()->momentum().perp() > 0.200 ) {
	 charge_pperp_200MeV += track_charge;
	 ( positive ? nump_pperp_200MeV++ : numn_pperp_200MeV++ );
      }
      if ( track_iter->pionFit()->momentum().perp() > 0.300 ) {
	 charge_pperp_300MeV += track_charge;
	 ( positive ? nump_pperp_300MeV++ : numn_pperp_300MeV++ );
      }
      if ( track_iter->pionFit()->momentum().perp() < 3. ) {
	 charge_pperp_3GeV += track_charge;
	 ( positive ? nump_pperp_3GeV++ : numn_pperp_3GeV++ );
      }
      if ( track_iter->pionFit()->momentum().perp() < 2. ) {
	 charge_pperp_2GeV += track_charge;
	 ( positive ? nump_pperp_2GeV++ : numn_pperp_2GeV++ );
      }
      if ( track_iter->pionFit()->momentum().perp() < 1. ) {
	 charge_pperp_1GeV += track_charge;
	 ( positive ? nump_pperp_1GeV++ : numn_pperp_1GeV++ );
      }

      if ( abs( track_iter->pionFit()->momentum().z() ) < 0.200 ) {
	 charge_pz_200MeV += track_charge;
	 ( positive ? nump_pz_200MeV++ : numn_pz_200MeV++ );
      }
      if ( abs( track_iter->pionFit()->momentum().z() ) < 0.100 ) {
	 charge_pz_100MeV += track_charge;
	 ( positive ? nump_pz_100MeV++ : numn_pz_100MeV++ );
      }
      if ( abs( track_iter->pionFit()->momentum().z() ) < 0.050 ) {
	 charge_pz_50MeV += track_charge;
	 ( positive ? nump_pz_50MeV++ : numn_pz_50MeV++ );
      }

      if ( track_iter->pionQuality()->chiSquare() < 300. ) {
	 charge_chi2_300 += track_charge;
	 ( positive ? nump_chi2_300++ : numn_chi2_300++ );
      }
      if ( track_iter->pionQuality()->chiSquare() < 200. ) {
	 charge_chi2_200 += track_charge;
	 ( positive ? nump_chi2_200++ : numn_chi2_200++ );
      }
      if ( track_iter->pionQuality()->chiSquare() < 100. ) {
	 charge_chi2_100 += track_charge;
	 ( positive ? nump_chi2_100++ : numn_chi2_100++ );
      }

      if ( track_iter->pionQuality()->chiSquare() > 0. ) {
	 charge_chi2_0 += track_charge;
	 ( positive ? nump_chi2_0++ : numn_chi2_0++ );
      }
      if ( track_iter->pionQuality()->chiSquare() > 0.01 ) {
	 charge_chi2_0_01 += track_charge;
	 ( positive ? nump_chi2_0_01++ : numn_chi2_0_01++ );
      }

      if ( track_iter->pionQuality()->degreesOfFreedom() > 0 ) {
	 if ( track_iter->pionQuality()->chiSquare() /
	      float( track_iter->pionQuality()->degreesOfFreedom() ) < 10. ) {
	    charge_chi2dof_10 += track_charge;
	    ( positive ? nump_chi2dof_10++ : numn_chi2dof_10++ );
	 }
	 if ( track_iter->pionQuality()->chiSquare() /
	      float( track_iter->pionQuality()->degreesOfFreedom() ) < 5. ) {
	    charge_chi2dof_5 += track_charge;
	    ( positive ? nump_chi2dof_5++ : numn_chi2dof_5++ );
	 }
	 if ( track_iter->pionQuality()->chiSquare() /
	      float( track_iter->pionQuality()->degreesOfFreedom() ) < 2.5 ) {
	    charge_chi2dof_2p5 += track_charge;
	    ( positive ? nump_chi2dof_2p5 : numn_chi2dof_2p5 );
	 }
      }

      if ( track_iter->pionQuality()->numberHitsExpected() > 0 ) {
	 charge_hitfrac_notinf += track_charge;
	 ( positive ? nump_hitfrac_notinf++ : numn_hitfrac_notinf );
	 if ( track_iter->pionQuality()->ratioNumberHitsToExpected() > 0.5 ) {
	    charge_hitfrac_notinf_5 += track_charge;
	    ( positive ? nump_hitfrac_notinf_5++ : numn_hitfrac_notinf_5++ );
	    if ( track_iter->pionQuality()->ratioNumberHitsToExpected() < 1.2 ) {
	       charge_hitfrac_notinf_5_12 += track_charge;
	       ( positive ? nump_hitfrac_notinf_5_12++ : numn_hitfrac_notinf_5_12++ );
	    }
	 }
      } // end if hits expected > 0

      if ( track_iter->pionQuality()->numberHitsExpected() > 0 ) {
	 charge_hitexp_0 += track_charge;
	 ( positive ? nump_hitexp_0++ : numn_hitexp_0++ );
      }
      if ( track_iter->pionQuality()->numberHitsExpected() > 10 ) {
	 charge_hitexp_10 += track_charge;
	 ( positive ? nump_hitexp_10++ : numn_hitexp_10++ );
      }
      if ( track_iter->pionQuality()->numberHitsExpected() > 20 ) {
	 charge_hitexp_20 += track_charge;
	 ( positive ? nump_hitexp_20++ : numn_hitexp_20++ );
      }

      if ( ! track_iter->pionQuality()->fitAbort() ) {
	 charge_fitabort_no += track_charge;
	 ( positive ? nump_fitabort_no++ : numn_fitabort_no++ );
      }
   } // end loop over tracks

   m_charge->fill( float( charge ) );
   m_charge_z0_20cm->fill( float( charge_z0_20cm ) );
   m_charge_z0_10cm->fill( float( charge_z0_10cm ) );
   m_charge_z0_5cm->fill( float( charge_z0_5cm ) );
   m_charge_z0_minus_wciz_10cm->fill( float( charge_z0_minus_wciz_10cm ) );
   m_charge_z0_minus_wciz_5cm->fill( float( charge_z0_minus_wciz_5cm ) );
   m_charge_z0_minus_wciz_25mm->fill( float( charge_z0_minus_wciz_25mm ) );
   m_charge_d0_20mm->fill( float( charge_d0_20mm ) );
   m_charge_d0_10mm->fill( float( charge_d0_10mm ) );
   m_charge_d0_5mm->fill( float( charge_d0_5mm ) );
   m_charge_p_100MeV->fill( float( charge_p_100MeV ) );
   m_charge_p_200MeV->fill( float( charge_p_200MeV ) );
   m_charge_p_300MeV->fill( float( charge_p_300MeV ) );
   m_charge_p_10GeV->fill( float( charge_p_10GeV ) );
   m_charge_p_6GeV->fill( float( charge_p_6GeV ) );
   m_charge_p_5GeV->fill( float( charge_p_5GeV ) );
   m_charge_pperp_100MeV->fill( float( charge_pperp_100MeV ) );
   m_charge_pperp_200MeV->fill( float( charge_pperp_200MeV ) );
   m_charge_pperp_300MeV->fill( float( charge_pperp_300MeV ) );
   m_charge_pperp_3GeV->fill( float( charge_pperp_3GeV ) );
   m_charge_pperp_2GeV->fill( float( charge_pperp_2GeV ) );
   m_charge_pperp_1GeV->fill( float( charge_pperp_1GeV ) );
   m_charge_pz_200MeV->fill( float( charge_pz_200MeV ) );
   m_charge_pz_100MeV->fill( float( charge_pz_100MeV ) );
   m_charge_pz_50MeV->fill( float( charge_pz_50MeV ) );
   m_charge_chi2_300->fill( float( charge_chi2_300 ) );
   m_charge_chi2_200->fill( float( charge_chi2_200 ) );
   m_charge_chi2_100->fill( float( charge_chi2_100 ) );
   m_charge_chi2_0->fill( float( charge_chi2_0 ) );
   m_charge_chi2_0_01->fill( float( charge_chi2_0_01 ) );
   m_charge_chi2dof_10->fill( float( charge_chi2dof_10 ) );
   m_charge_chi2dof_5->fill( float( charge_chi2dof_5 ) );
   m_charge_chi2dof_2p5->fill( float( charge_chi2dof_2p5 ) );
   m_charge_hitfrac_notinf->fill( float( charge_hitfrac_notinf ) );
   m_charge_hitfrac_notinf_5->fill( float( charge_hitfrac_notinf_5 ) );
   m_charge_hitfrac_notinf_5_12->fill( float( charge_hitfrac_notinf_5_12 ) );
   m_charge_hitexp_0->fill( float( charge_hitexp_0 ) );
   m_charge_hitexp_10->fill( float( charge_hitexp_10 ) );
   m_charge_hitexp_20->fill( float( charge_hitexp_20 ) );
   m_charge_fitabort_no->fill( float( charge_fitabort_no ) );

   m_asycharge->fill( abs( float( charge ) ), ( charge < 0 ? -1. : 1. ) );
   m_asycharge_z0_20cm->fill( abs( float( charge_z0_20cm ) ), ( charge_z0_20cm < 0 ? -1. : 1. ) );
   m_asycharge_z0_10cm->fill( abs( float( charge_z0_10cm ) ), ( charge_z0_10cm < 0 ? -1. : 1. ) );
   m_asycharge_z0_5cm->fill( abs( float( charge_z0_5cm ) ), ( charge_z0_5cm < 0 ? -1. : 1. ) );
   m_asycharge_z0_minus_wciz_10cm->fill( abs( float( charge_z0_minus_wciz_10cm ) ),
					 ( charge_z0_minus_wciz_10cm < 0 ? -1. : 1. ) );
   m_asycharge_z0_minus_wciz_5cm->fill( abs( float( charge_z0_minus_wciz_5cm ) ),
					( charge_z0_minus_wciz_5cm < 0 ? -1. : 1. ) );
   m_asycharge_z0_minus_wciz_25mm->fill( abs( float( charge_z0_minus_wciz_25mm ) ),
					 ( charge_z0_minus_wciz_25mm < 0 ? -1. : 1. ) );
   m_asycharge_d0_20mm->fill( abs( float( charge_d0_20mm ) ), ( charge_d0_20mm < 0 ? -1. : 1. ) );
   m_asycharge_d0_10mm->fill( abs( float( charge_d0_10mm ) ), ( charge_d0_10mm < 0 ? -1. : 1. ) );
   m_asycharge_d0_5mm->fill( abs( float( charge_d0_5mm ) ), ( charge_d0_5mm < 0 ? -1. : 1. ) );
   m_asycharge_p_100MeV->fill( abs( float( charge_p_100MeV ) ), ( charge_p_100MeV < 0 ? -1. : 1. ) );
   m_asycharge_p_200MeV->fill( abs( float( charge_p_200MeV ) ), ( charge_p_200MeV < 0 ? -1. : 1. ) );
   m_asycharge_p_300MeV->fill( abs( float( charge_p_300MeV ) ), ( charge_p_300MeV < 0 ? -1. : 1. ) );
   m_asycharge_p_10GeV->fill( abs( float( charge_p_10GeV ) ), ( charge_p_10GeV < 0 ? -1. : 1. ) );
   m_asycharge_p_6GeV->fill( abs( float( charge_p_6GeV ) ), ( charge_p_6GeV < 0 ? -1. : 1. ) );
   m_asycharge_p_5GeV->fill( abs( float( charge_p_5GeV ) ), ( charge_p_5GeV < 0 ? -1. : 1. ) );
   m_asycharge_pperp_100MeV->fill( abs( float( charge_pperp_100MeV ) ), ( charge_pperp_100MeV < 0 ? -1. : 1. ) );
   m_asycharge_pperp_200MeV->fill( abs( float( charge_pperp_200MeV ) ), ( charge_pperp_200MeV < 0 ? -1. : 1. ) );
   m_asycharge_pperp_300MeV->fill( abs( float( charge_pperp_300MeV ) ), ( charge_pperp_300MeV < 0 ? -1. : 1. ) );
   m_asycharge_pperp_3GeV->fill( abs( float( charge_pperp_3GeV ) ), ( charge_pperp_3GeV < 0 ? -1. : 1. ) );
   m_asycharge_pperp_2GeV->fill( abs( float( charge_pperp_2GeV ) ), ( charge_pperp_2GeV < 0 ? -1. : 1. ) );
   m_asycharge_pperp_1GeV->fill( abs( float( charge_pperp_1GeV ) ), ( charge_pperp_1GeV < 0 ? -1. : 1. ) );
   m_asycharge_pz_200MeV->fill( abs( float( charge_pz_200MeV ) ), ( charge_pz_200MeV < 0 ? -1. : 1. ) );
   m_asycharge_pz_100MeV->fill( abs( float( charge_pz_100MeV ) ), ( charge_pz_100MeV < 0 ? -1. : 1. ) );
   m_asycharge_pz_50MeV->fill( abs( float( charge_pz_50MeV ) ), ( charge_pz_50MeV < 0 ? -1. : 1. ) );
   m_asycharge_chi2_300->fill( abs( float( charge_chi2_300 ) ), ( charge_chi2_300 < 0 ? -1. : 1. ) );
   m_asycharge_chi2_200->fill( abs( float( charge_chi2_200 ) ), ( charge_chi2_200 < 0 ? -1. : 1. ) );
   m_asycharge_chi2_100->fill( abs( float( charge_chi2_100 ) ), ( charge_chi2_100 < 0 ? -1. : 1. ) );
   m_asycharge_chi2_0->fill( abs( float( charge_chi2_0 ) ), ( charge_chi2_0 < 0 ? -1. : 1. ) );
   m_asycharge_chi2_0_01->fill( abs( float( charge_chi2_0_01 ) ), ( charge_chi2_0_01 < 0 ? -1. : 1. ) );
   m_asycharge_chi2dof_10->fill( abs( float( charge_chi2dof_10 ) ), ( charge_chi2dof_10 < 0 ? -1. : 1. ) );
   m_asycharge_chi2dof_5->fill( abs( float( charge_chi2dof_5 ) ), ( charge_chi2dof_5 < 0 ? -1. : 1. ) );
   m_asycharge_chi2dof_2p5->fill( abs( float( charge_chi2dof_2p5 ) ), ( charge_chi2dof_2p5 < 0 ? -1. : 1. ) );
   m_asycharge_hitfrac_notinf->fill( abs( float( charge_hitfrac_notinf ) ),
				     ( charge_hitfrac_notinf < 0 ? -1. : 1. ) );
   m_asycharge_hitfrac_notinf_5->fill( abs( float( charge_hitfrac_notinf_5 ) ),
				       ( charge_hitfrac_notinf_5 < 0 ? -1. : 1. ) );
   m_asycharge_hitfrac_notinf_5_12->fill( abs( float( charge_hitfrac_notinf_5_12 ) ),
					  ( charge_hitfrac_notinf_5_12 < 0 ? -1. : 1. ) );
   m_asycharge_hitexp_0->fill( abs( float( charge_hitexp_0 ) ), ( charge_hitexp_0 < 0 ? -1. : 1. ) );
   m_asycharge_hitexp_10->fill( abs( float( charge_hitexp_10 ) ), ( charge_hitexp_10 < 0 ? -1. : 1. ) );
   m_asycharge_hitexp_20->fill( abs( float( charge_hitexp_20 ) ), ( charge_hitexp_20 < 0 ? -1. : 1. ) );
   m_asycharge_fitabort_no->fill( abs( float( charge_fitabort_no ) ), ( charge_fitabort_no < 0 ? -1. : 1. ) );

   m_nposneg->fill( nump, numn );
   m_nposneg_z0_20cm->fill( nump_z0_20cm, numn_z0_20cm );
   m_nposneg_z0_10cm->fill( nump_z0_10cm, numn_z0_10cm );
   m_nposneg_z0_5cm->fill( nump_z0_5cm, numn_z0_5cm );
   m_nposneg_z0_minus_wciz_10cm->fill( nump_z0_minus_wciz_10cm, numn_z0_minus_wciz_10cm );
   m_nposneg_z0_minus_wciz_5cm->fill( nump_z0_minus_wciz_5cm, numn_z0_minus_wciz_5cm );
   m_nposneg_z0_minus_wciz_25mm->fill( nump_z0_minus_wciz_25mm, numn_z0_minus_wciz_25mm );
   m_nposneg_d0_20mm->fill( nump_d0_20mm, numn_d0_20mm );
   m_nposneg_d0_10mm->fill( nump_d0_10mm, numn_d0_10mm );
   m_nposneg_d0_5mm->fill( nump_d0_5mm, numn_d0_5mm );
   m_nposneg_p_100MeV->fill( nump_p_100MeV, numn_p_100MeV );
   m_nposneg_p_200MeV->fill( nump_p_200MeV, numn_p_200MeV );
   m_nposneg_p_300MeV->fill( nump_p_300MeV, numn_p_300MeV );
   m_nposneg_p_10GeV->fill( nump_p_10GeV, numn_p_10GeV );
   m_nposneg_p_6GeV->fill( nump_p_6GeV, numn_p_6GeV );
   m_nposneg_p_5GeV->fill( nump_p_5GeV, numn_p_5GeV );
   m_nposneg_pperp_100MeV->fill( nump_pperp_100MeV, numn_pperp_100MeV );
   m_nposneg_pperp_200MeV->fill( nump_pperp_200MeV, numn_pperp_200MeV );
   m_nposneg_pperp_300MeV->fill( nump_pperp_300MeV, numn_pperp_300MeV );
   m_nposneg_pperp_3GeV->fill( nump_pperp_3GeV, numn_pperp_3GeV );
   m_nposneg_pperp_2GeV->fill( nump_pperp_2GeV, numn_pperp_2GeV );
   m_nposneg_pperp_1GeV->fill( nump_pperp_1GeV, numn_pperp_1GeV );
   m_nposneg_pz_200MeV->fill( nump_pz_200MeV, numn_pz_200MeV );
   m_nposneg_pz_100MeV->fill( nump_pz_100MeV, numn_pz_100MeV );
   m_nposneg_pz_50MeV->fill( nump_pz_50MeV, numn_pz_50MeV );
   m_nposneg_chi2_300->fill( nump_chi2_300, numn_chi2_300 );
   m_nposneg_chi2_200->fill( nump_chi2_200, numn_chi2_200 );
   m_nposneg_chi2_100->fill( nump_chi2_100, numn_chi2_100 );
   m_nposneg_chi2_0->fill( nump_chi2_0, numn_chi2_0 );
   m_nposneg_chi2_0_01->fill( nump_chi2_0_01, numn_chi2_0_01 );
   m_nposneg_chi2dof_10->fill( nump_chi2dof_10, numn_chi2dof_10 );
   m_nposneg_chi2dof_5->fill( nump_chi2dof_5, numn_chi2dof_5 );
   m_nposneg_chi2dof_2p5->fill( nump_chi2dof_2p5, numn_chi2dof_2p5 );
   m_nposneg_hitfrac_notinf->fill( nump_hitfrac_notinf, numn_hitfrac_notinf );
   m_nposneg_hitfrac_notinf_5->fill( nump_hitfrac_notinf_5, numn_hitfrac_notinf_5 );
   m_nposneg_hitfrac_notinf_5_12->fill( nump_hitfrac_notinf_5_12, numn_hitfrac_notinf_5_12 );
   m_nposneg_hitexp_0->fill( nump_hitexp_0, numn_hitexp_0 );
   m_nposneg_hitexp_10->fill( nump_hitexp_10, numn_hitexp_10 );
   m_nposneg_hitexp_20->fill( nump_hitexp_20, numn_hitexp_20 );
   m_nposneg_fitabort_no->fill( nump_fitabort_no, numn_fitabort_no );

   return ActionBase::kPassed;
}

ActionBase::ActionResult
ChargeDistributionsProc::beginRun( Frame& iFrame )       // anal2 equiv.
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
ChargeDistributionsProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

double ChargeDistributionsProc::get_weighted_ciz( Frame& iFrame )
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
	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );
	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - m_beam_x) + sqr(ty - m_beam_y) );
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

DABoolean ChargeDistributionsProc::calc_intersection(
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

DABoolean ChargeDistributionsProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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
