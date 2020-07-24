// -*- C++ -*-
//
// Package:     UpsilonGammaEEAnalysisProc
// Module:      UpsilonGammaEEAnalysisProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr 25 15:04:32 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "UpsilonGammaEEAnalysisProc/UpsilonGammaEEAnalysisProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "CleoDB/DBEventHeader.h"
#include "RunInfo/RunStats.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"

#include "TriggerL1Data/TriggerL1Data.h"
#include "Level4Proc/Level4Decision.h"
#include "BunchFinder/BunchDecision.h"

#include "Navigation/NavTrack.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavTkShMatch.h"

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
static const char* const kFacilityString = "Processor.UpsilonGammaEEAnalysisProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
UpsilonGammaEEAnalysisProc::UpsilonGammaEEAnalysisProc( void )               // anal1
   : Processor( "UpsilonGammaEEAnalysisProc" )
   , m_goodBunch("goodBunch", this, true)
   , m_ellell("ellell", this, false)
   , m_photos("photos", this, false)
   , m_runstats("runstats", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &UpsilonGammaEEAnalysisProc::event,    Stream::kEvent );
   //bind( &UpsilonGammaEEAnalysisProc::beginRun, Stream::kBeginRun );
   //bind( &UpsilonGammaEEAnalysisProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

UpsilonGammaEEAnalysisProc::~UpsilonGammaEEAnalysisProc()                    // anal5
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
UpsilonGammaEEAnalysisProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
UpsilonGammaEEAnalysisProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   cout << "PYTHON import Numeric" << endl;
   cout << "PYTHON class RunRecord: pass" << endl;
   cout << "PYTHON rec = RunRecord()" << endl;

   print_int("run", m_run);
   print_int("last", m_last);
   print_int("ebeam", m_ebeam);

   print_int("c_all", mc_all);
   print_hist1("t_all", mt_all);
   print_hist1("T_all", mT_all);
   print_int("c_reallyeverything", mc_reallyeverything);
   print_int("c_badbunch", mc_badbunch);
   print_int("c_ellell", mc_ellell);
   print_int("c_photos", mc_photos);

   print_hist1("h_had_trig", mh_had_trig);
   print_hist1("h_had_d0close1", mh_had_d0close1);
   print_hist1("h_had_d0close2", mh_had_d0close2);
   print_hist1("h_had_p2", mh_had_p2);
   print_hist1("h_had_wz1", mh_had_wz1);
   print_hist1("h_had_wz2", mh_had_wz2);
   print_hist1("h_had_z0close1", mh_had_z0close1);
   print_hist1("h_had_z0close2", mh_had_z0close2);
   print_hist1("h_had_visen", mh_had_visen);
   print_hist1("H_had_trig", mH_had_trig);
   print_hist1("H_had_d0close1", mH_had_d0close1);
   print_hist1("H_had_d0close2", mH_had_d0close2);
   print_hist1("H_had_p2", mH_had_p2);
   print_hist1("H_had_wz1", mH_had_wz1);
   print_hist1("H_had_wz2", mH_had_wz2);
   print_hist1("H_had_z0close1", mH_had_z0close1);
   print_hist1("H_had_z0close2", mH_had_z0close2);
   print_hist1("H_had_visen", mH_had_visen);
   print_int("c_had", mc_had);
   print_int("c_had_trig", mc_had_trig);
   print_int("c_had_d0close", mc_had_d0close);
   print_int("c_had_p2", mc_had_p2);
   print_int("c_had_wz", mc_had_wz);
   print_int("c_had_visen", mc_had_visen);
   print_int("c_had_l4dec", mc_had_l4dec);
   print_int("w_had_d0close", mw_had_d0close);
   print_int("w_had_p2", mw_had_p2);
   print_int("w_had_wz", mw_had_wz);
   print_int("w_had_visen", mw_had_visen);
   print_int("C_had_trig", mC_had_trig);
   print_int("C_had_d0close", mC_had_d0close);
   print_int("C_had_p2", mC_had_p2);
   print_int("C_had_wz", mC_had_wz);
   print_int("C_had_visen", mC_had_visen);
   print_int("C_had_l4dec", mC_had_l4dec);
   print_int("c_old_hadron", mc_old_hadron);
   print_hist1("h_had_ntracks", mh_had_ntracks);
   print_int("c_had_gt2track", mc_had_gt2track);
   print_int("c_had_gt4track", mc_had_gt4track);
   print_hist1("h_had_coolvisen", mh_had_coolvisen);
   print_hist1("h_had_coolvisen_nol4dec", mh_had_coolvisen_nol4dec);
   print_hist1("t_had", mt_had);
   print_hist1("T_had", mT_had);

   print_hist1("h_gam_e2", mh_gam_e2);
   print_hist1("h_gam_ntracks", mh_gam_ntracks);
   print_hist1("h_gam_zback", mh_gam_zback);
   print_hist1("h_gam_z1", mh_gam_z1);
   print_hist1("h_gam_z2", mh_gam_z2);
   print_hist1("h_gam_z1_noexclude", mh_gam_z1_noexclude);
   print_hist1("h_gam_z2_noexclude", mh_gam_z2_noexclude);
   print_hist1("h_gam_phiback", mh_gam_phiback);
   print_hist1("h_gam_phiback_notracks", mh_gam_phiback_notracks);
   print_int("c_gam", mc_gam);
   print_int("c_gam_trig", mc_gam_trig);
   print_int("c_gam_oppositesides", mc_gam_oppositesides);
   print_int("c_gam_e2", mc_gam_e2);
   print_int("c_gam_ntracks", mc_gam_ntracks);
   print_int("c_gam_zback", mc_gam_zback);
   print_int("c_gam_zouter", mc_gam_zouter);
   print_int("c_gam_zinner", mc_gam_zinner);
   print_int("c_gam_phiback", mc_gam_phiback);
   print_int("c_gam_excludebadtrig", mc_gam_excludebadtrig);
   print_int("c_gam_excludebadwiremap", mc_gam_excludebadwiremap);
   print_int("c_gam_l4dec", mc_gam_l4dec);
   print_int("w_gam_e2", mw_gam_e2);
   print_int("w_gam_ntracks", mw_gam_ntracks);
   print_int("w_gam_zback", mw_gam_zback);
   print_int("w_gam_zouter", mw_gam_zouter);
   print_int("w_gam_zinner", mw_gam_zinner);
   print_int("w_gam_phiback", mw_gam_phiback);
   print_int("w_gam_excludebadtrig", mw_gam_excludebadtrig);
   print_int("w_gam_excludebadwiremap", mw_gam_excludebadwiremap);
   print_int("C_gam_trig", mC_gam_trig);
   print_int("C_gam_oppositesides", mC_gam_oppositesides);
   print_int("C_gam_e2", mC_gam_e2);
   print_int("C_gam_ntracks", mC_gam_ntracks);
   print_int("C_gam_zback", mC_gam_zback);
   print_int("C_gam_zouter", mC_gam_zouter);
   print_int("C_gam_zinner", mC_gam_zinner);
   print_int("C_gam_phiback", mC_gam_phiback);
   print_int("C_gam_excludebadtrig", mC_gam_excludebadtrig);
   print_int("C_gam_excludebadwiremap", mC_gam_excludebadwiremap);
   print_int("C_gam_l4dec", mC_gam_l4dec);
   print_int("c_old_gamgam", mc_old_gamgam);
   print_hist1("h_gam_trigcorrect", mh_gam_trigcorrect);
   print_hist1("h_gam_e3in", mh_gam_e3in);
   print_hist1("h_gam_e3out", mh_gam_e3out);
   print_hist1("t_gam", mt_gam);
   print_hist1("T_gam", mT_gam);
   print_hist2("2_gam_cellringwest", m2_gam_cellringwest);
   print_hist2("2_gam_cellringeast", m2_gam_cellringeast);
   print_hist2("2_gam_cellringwest_noexclude", m2_gam_cellringwest_noexclude);
   print_hist2("2_gam_cellringeast_noexclude", m2_gam_cellringeast_noexclude);

   print_hist1("h_tkl_e2", mh_tkl_e2);
   print_hist1("h_tkl_ntracks", mh_tkl_ntracks);
   print_hist1("h_tkl_zback", mh_tkl_zback);
   print_hist1("h_tkl_z1", mh_tkl_z1);
   print_hist1("h_tkl_z2", mh_tkl_z2);
   print_hist1("h_tkl_z1_noexclude", mh_tkl_z1_noexclude);
   print_hist1("h_tkl_z2_noexclude", mh_tkl_z2_noexclude);
   print_hist1("h_tkl_phiback", mh_tkl_phiback);
   print_hist1("h_tkl_phiback_notrackcut", mh_tkl_phiback_notrackcut);
   print_int("c_tkl", mc_tkl);
   print_int("c_tkl_trig", mc_tkl_trig);
   print_int("c_tkl_oppositesides", mc_tkl_oppositesides);
   print_int("c_tkl_e2", mc_tkl_e2);
   print_int("c_tkl_ntracks", mc_tkl_ntracks);
   print_int("c_tkl_zback", mc_tkl_zback);
   print_int("c_tkl_zouter", mc_tkl_zouter);
   print_int("c_tkl_zinner", mc_tkl_zinner);
   print_int("c_tkl_phiback", mc_tkl_phiback);
   print_int("c_tkl_excludebadtrig", mc_tkl_excludebadtrig);
   print_int("c_tkl_excludebadwiremap", mc_tkl_excludebadwiremap);
   print_int("c_tkl_l4dec", mc_tkl_l4dec);
   print_int("w_tkl_e2", mw_tkl_e2);
   print_int("w_tkl_zback", mw_tkl_zback);
   print_int("w_tkl_zouter", mw_tkl_zouter);
   print_int("w_tkl_zinner", mw_tkl_zinner);
   print_int("w_tkl_phiback1", mw_tkl_phiback1);
   print_int("w_tkl_phiback2", mw_tkl_phiback2);
   print_int("w_tkl_excludebadtrig", mw_tkl_excludebadtrig);
   print_int("w_tkl_excludebadwiremap", mw_tkl_excludebadwiremap);
   print_int("w_tkl_eltrack", mw_tkl_eltrack);
   print_int("c_old_trackless", mc_old_trackless);
   print_hist1("t_tkl", mt_tkl);
   print_hist1("t_tkl_nontracks", mt_tkl_nontracks);
   print_hist1("t_tkl_eltrack", mt_tkl_eltrack);
   print_hist1("T_tkl", mT_tkl);
   print_hist1("T_tkl_nontracks", mT_tkl_nontracks);
   print_hist1("T_tkl_eltrack", mT_tkl_eltrack);

   print_hist1("h_bha_trig", mh_bha_trig);
   print_hist1("h_bha_p2", mh_bha_p2);
   print_hist1("h_bha_d0close1", mh_bha_d0close1);
   print_hist1("h_bha_d0close2", mh_bha_d0close2);
   print_hist1("h_bha_wz1", mh_bha_wz1);
   print_hist1("h_bha_wz2", mh_bha_wz2);
   print_hist1("h_bha_z0close1", mh_bha_z0close1);
   print_hist1("h_bha_z0close2", mh_bha_z0close2);
   print_hist1("h_bha_eisr", mh_bha_eisr);
   print_hist1("h_bha_econstraint", mh_bha_econstraint);
   print_hist1("h_bha_costheta1", mh_bha_costheta1);
   print_hist1("h_bha_costheta2", mh_bha_costheta2);
   print_hist1("h_bha_e2", mh_bha_e2);
   print_int("c_bha", mc_bha);
   print_int("c_bha_trig", mc_bha_trig);
   print_int("c_bha_oppositecharge", mc_bha_oppositecharge);
   print_int("c_bha_p2", mc_bha_p2);
   print_int("c_bha_d0close", mc_bha_d0close);
   print_int("c_bha_wz", mc_bha_wz);
   print_int("c_bha_eisr", mc_bha_eisr);
   print_int("c_bha_econstraint", mc_bha_econstraint);
   print_int("c_bha_costheta", mc_bha_costheta);
   print_int("c_bha_e2", mc_bha_e2);
   print_int("c_bha_l4dec", mc_bha_l4dec);
   print_int("w_bha_p2", mw_bha_p2);
   print_int("w_bha_d0close", mw_bha_d0close);
   print_int("w_bha_wz", mw_bha_wz);
   print_int("w_bha_eisr", mw_bha_eisr);
   print_int("w_bha_econstraint", mw_bha_econstraint);
   print_int("w_bha_costheta", mw_bha_costheta);
   print_int("w_bha_e2", mw_bha_e2);
   print_int("c_old_bhabha", mc_old_bhabha);
   print_hist1("h_bha_trignumer", mh_bha_trignumer);
   print_hist1("h_bha_trigdenom", mh_bha_trigdenom);
   print_hist1("h_bha_trignumer_showergeometry", mh_bha_trignumer_showergeometry);
   print_hist1("h_bha_trigdenom_showergeometry", mh_bha_trigdenom_showergeometry);
   print_hist1("h_bha_trignumer_showergeometry2", mh_bha_trignumer_showergeometry2);
   print_hist1("h_bha_trigdenom_showergeometry2", mh_bha_trigdenom_showergeometry2);
   print_hist1("h_bha_trignumer_excludeblocks", mh_bha_trignumer_excludeblocks);
   print_hist1("h_bha_trigdenom_excludeblocks", mh_bha_trigdenom_excludeblocks);
   print_hist1("h_bha_trignumer_showergeometry_excludeblocks", mh_bha_trignumer_showergeometry_excludeblocks);
   print_hist1("h_bha_trigdenom_showergeometry_excludeblocks", mh_bha_trigdenom_showergeometry_excludeblocks);
   print_hist1("h_bha_trignumer_showergeometry2_excludeblocks", mh_bha_trignumer_showergeometry2_excludeblocks);
   print_hist1("h_bha_trigdenom_showergeometry2_excludeblocks", mh_bha_trigdenom_showergeometry2_excludeblocks);
   print_hist1("t_bha", mt_bha);
   print_hist1("T_bha", mT_bha);
   print_hist2("2_bha_trignumer_cellringwest", m2_bha_trignumer_cellringwest);
   print_hist2("2_bha_trignumer_cellringeast", m2_bha_trignumer_cellringeast);
   print_hist2("2_bha_trigdenom_cellringwest", m2_bha_trigdenom_cellringwest);
   print_hist2("2_bha_trigdenom_cellringeast", m2_bha_trigdenom_cellringeast);
   print_hist2("2_bha_trignumer_cellringwest_showergeometry", m2_bha_trignumer_cellringwest_showergeometry);
   print_hist2("2_bha_trignumer_cellringeast_showergeometry", m2_bha_trignumer_cellringeast_showergeometry);
   print_hist2("2_bha_trigdenom_cellringwest_showergeometry", m2_bha_trigdenom_cellringwest_showergeometry);
   print_hist2("2_bha_trigdenom_cellringeast_showergeometry", m2_bha_trigdenom_cellringeast_showergeometry);
   print_hist2("2_bha_trignumer_cellringwest_showergeometry2", m2_bha_trignumer_cellringwest_showergeometry2);
   print_hist2("2_bha_trignumer_cellringeast_showergeometry2", m2_bha_trignumer_cellringeast_showergeometry2);
   print_hist2("2_bha_trigdenom_cellringwest_showergeometry2", m2_bha_trigdenom_cellringwest_showergeometry2);
   print_hist2("2_bha_trigdenom_cellringeast_showergeometry2", m2_bha_trigdenom_cellringeast_showergeometry2);
   print_hist2("2_bha_trignumer_cellringwest_excludeblocks", m2_bha_trignumer_cellringwest_excludeblocks);
   print_hist2("2_bha_trignumer_cellringeast_excludeblocks", m2_bha_trignumer_cellringeast_excludeblocks);
   print_hist2("2_bha_trigdenom_cellringwest_excludeblocks", m2_bha_trigdenom_cellringwest_excludeblocks);
   print_hist2("2_bha_trigdenom_cellringeast_excludeblocks", m2_bha_trigdenom_cellringeast_excludeblocks);
   print_hist2("2_bha_trignumer_cellringwest_showergeometry_excludeblocks", m2_bha_trignumer_cellringwest_showergeometry_excludeblocks);
   print_hist2("2_bha_trignumer_cellringeast_showergeometry_excludeblocks", m2_bha_trignumer_cellringeast_showergeometry_excludeblocks);
   print_hist2("2_bha_trigdenom_cellringwest_showergeometry_excludeblocks", m2_bha_trigdenom_cellringwest_showergeometry_excludeblocks);
   print_hist2("2_bha_trigdenom_cellringeast_showergeometry_excludeblocks", m2_bha_trigdenom_cellringeast_showergeometry_excludeblocks);
   print_hist2("2_bha_trignumer_cellringwest_showergeometry2_excludeblocks", m2_bha_trignumer_cellringwest_showergeometry2_excludeblocks);
   print_hist2("2_bha_trignumer_cellringeast_showergeometry2_excludeblocks", m2_bha_trignumer_cellringeast_showergeometry2_excludeblocks);
   print_hist2("2_bha_trigdenom_cellringwest_showergeometry2_excludeblocks", m2_bha_trigdenom_cellringwest_showergeometry2_excludeblocks);
   print_hist2("2_bha_trigdenom_cellringeast_showergeometry2_excludeblocks", m2_bha_trigdenom_cellringeast_showergeometry2_excludeblocks);

   print_hist1("h_mup_trig", mh_mup_trig);
   print_hist1("h_mup_p2", mh_mup_p2);
   print_hist1("h_mup_d0close1", mh_mup_d0close1);
   print_hist1("h_mup_d0close2", mh_mup_d0close2);
   print_hist1("h_mup_wz1", mh_mup_wz1);
   print_hist1("h_mup_wz2", mh_mup_wz2);
   print_hist1("h_mup_z0close1", mh_mup_z0close1);
   print_hist1("h_mup_z0close2", mh_mup_z0close2);
   print_hist1("h_mup_eisr", mh_mup_eisr);
   print_hist1("h_mup_econstraint", mh_mup_econstraint);
   print_hist1("h_mup_costheta1", mh_mup_costheta1);
   print_hist1("h_mup_costheta2", mh_mup_costheta2);
   print_hist1("h_mup_e2", mh_mup_e2);
   print_int("c_mup", mc_mup);
   print_int("c_mup_trig", mc_mup_trig);
   print_int("c_mup_oppositecharge", mc_mup_oppositecharge);
   print_int("c_mup_p2", mc_mup_p2);
   print_int("c_mup_d0close", mc_mup_d0close);
   print_int("c_mup_wz", mc_mup_wz);
   print_int("c_mup_eisr", mc_mup_eisr);
   print_int("c_mup_econstraint", mc_mup_econstraint);
   print_int("c_mup_costheta", mc_mup_costheta);
   print_int("c_mup_e2", mc_mup_e2);
   print_int("c_mup_l4dec", mc_mup_l4dec);
   print_int("w_mup_p2", mw_mup_p2);
   print_int("w_mup_d0close", mw_mup_d0close);
   print_int("w_mup_wz", mw_mup_wz);
   print_int("w_mup_eisr", mw_mup_eisr);
   print_int("w_mup_econstraint", mw_mup_econstraint);
   print_int("w_mup_costheta", mw_mup_costheta);
   print_int("w_mup_e2", mw_mup_e2);
   print_hist1("t_mup", mt_mup);
   print_hist1("T_mup", mT_mup);

   print_hist1("h_cos_trig", mh_cos_trig);
   print_hist1("h_cos_ntracks", mh_cos_ntracks);
   print_hist1("h_cos_d0close1", mh_cos_d0close1);
   print_hist1("h_cos_d0close2", mh_cos_d0close2);
   print_hist1("h_cos_pdotp1", mh_cos_pdotp1);
   print_hist1("h_cos_pdotp2", mh_cos_pdotp2);
   print_hist1("h_cos_ccen", mh_cos_ccen);
   print_int("c_cos", mc_cos);
   print_int("c_cos_trig", mc_cos_trig);
   print_int("c_cos_ntracks", mc_cos_ntracks);
   print_int("c_cos_d0close", mc_cos_d0close);
   print_int("c_cos_pdotp", mc_cos_pdotp);
   print_int("c_cos_ccen", mc_cos_ccen);
   print_int("c_cos_l4dec", mc_cos_l4dec);
   print_int("w_cos_d0close1", mw_cos_d0close1);
   print_int("w_cos_d0close2", mw_cos_d0close2);
   print_int("w_cos_pdotp", mw_cos_pdotp);
   print_int("w_cos_ccen", mw_cos_ccen);
   print_hist1("t_cos", mt_cos);
   print_hist1("T_cos", mT_cos);
   print_hist1("h_cos_visen", mh_cos_visen);

   print_hist1("h_bge_trig", mh_bge_trig);
   print_hist1("h_bge_ntracks", mh_bge_ntracks);
   print_hist1("h_bge_d0close1", mh_bge_d0close1);
   print_hist1("h_bge_d0close2", mh_bge_d0close2);
   print_hist1("h_bge_wz1", mh_bge_wz1);
   print_hist1("h_bge_wz2", mh_bge_wz2);
   print_hist1("h_bge_z0close1", mh_bge_z0close1);
   print_hist1("h_bge_z0close2", mh_bge_z0close2);
   print_hist1("h_bge_pdotp1", mh_bge_pdotp1);
   print_hist1("h_bge_pdotp2", mh_bge_pdotp2);
   print_hist1("h_bge_wpz", mh_bge_wpz);
   print_int("c_bge", mc_bge);
   print_int("c_bge_trig", mc_bge_trig);
   print_int("c_bge_ntracks", mc_bge_ntracks);
   print_int("c_bge_d0close", mc_bge_d0close);
   print_int("c_bge_wz", mc_bge_wz);
   print_int("c_bge_pdotp", mc_bge_pdotp);
   print_int("c_bge_wpz", mc_bge_wpz);
   print_int("c_bge_l4dec", mc_bge_l4dec);
   print_int("w_bge_ntracks", mw_bge_ntracks);
   print_int("w_bge_d0close", mw_bge_d0close);
   print_int("w_bge_wz", mw_bge_wz);
   print_int("w_bge_pdotp", mw_bge_pdotp);
   print_int("w_bge_wpz", mw_bge_wpz);
   print_hist1("t_bge", mt_bge);
   print_hist1("T_bge", mT_bge);
   print_hist1("h_bge_visen", mh_bge_visen);

   print_hist1("h_bgp_trig", mh_bgp_trig);
   print_hist1("h_bgp_ntracks", mh_bgp_ntracks);
   print_hist1("h_bgp_d0close1", mh_bgp_d0close1);
   print_hist1("h_bgp_d0close2", mh_bgp_d0close2);
   print_hist1("h_bgp_wz1", mh_bgp_wz1);
   print_hist1("h_bgp_wz2", mh_bgp_wz2);
   print_hist1("h_bgp_z0close1", mh_bgp_z0close1);
   print_hist1("h_bgp_z0close2", mh_bgp_z0close2);
   print_hist1("h_bgp_pdotp1", mh_bgp_pdotp1);
   print_hist1("h_bgp_pdotp2", mh_bgp_pdotp2);
   print_hist1("h_bgp_wpz", mh_bgp_wpz);
   print_int("c_bgp", mc_bgp);
   print_int("c_bgp_trig", mc_bgp_trig);
   print_int("c_bgp_ntracks", mc_bgp_ntracks);
   print_int("c_bgp_d0close", mc_bgp_d0close);
   print_int("c_bgp_wz", mc_bgp_wz);
   print_int("c_bgp_pdotp", mc_bgp_pdotp);
   print_int("c_bgp_wpz", mc_bgp_wpz);
   print_int("c_bgp_l4dec", mc_bgp_l4dec);
   print_int("w_bgp_ntracks", mw_bgp_ntracks);
   print_int("w_bgp_d0close", mw_bgp_d0close);
   print_int("w_bgp_wz", mw_bgp_wz);
   print_int("w_bgp_pdotp", mw_bgp_pdotp);
   print_int("w_bgp_wpz", mw_bgp_wpz);
   print_hist1("t_bgp", mt_bgp);
   print_hist1("T_bgp", mT_bgp);
   print_hist1("h_bgp_visen", mh_bgp_visen);

   print_hist1("h_ccs_d0close1", mh_ccs_d0close1);
   print_hist1("h_ccs_d0close2", mh_ccs_d0close2);
   print_hist1("h_ccs_p2", mh_ccs_p2);
   print_hist1("h_ccs_wz1", mh_ccs_wz1);
   print_hist1("h_ccs_wz2", mh_ccs_wz2);
   print_hist1("h_ccs_z0close1", mh_ccs_z0close1);
   print_hist1("h_ccs_z0close2", mh_ccs_z0close2);
   print_hist1("h_ccs_ntracks", mh_ccs_ntracks);
   print_hist1("h_ccs_chen", mh_ccs_chen);
   print_int("c_ccs", mc_ccs);
   print_int("c_ccs_d0close", mc_ccs_d0close);
   print_int("c_ccs_p2", mc_ccs_p2);
   print_int("c_ccs_wz", mc_ccs_wz);
   print_int("c_ccs_ntracks", mc_ccs_ntracks);
   print_int("c_ccs_chen", mc_ccs_chen);
   print_int("c_ccs_l4dec", mc_ccs_l4dec);
   print_int("c_ccs_hadtrig", mc_ccs_hadtrig);
   print_hist1("h_ccs_hadtrig", mh_ccs_hadtrig);
   print_hist1("h_ccs_e1", mh_ccs_e1);
   print_hist1("h_ccs_e2", mh_ccs_e2);
   print_double("s_ccs_e1", ms_ccs_e1);
   print_double("S_ccs_e1", mS_ccs_e1);
   print_int("n_ccs_e1", mn_ccs_e1);
   print_double("s_ccs_e2", ms_ccs_e2);
   print_double("S_ccs_e2", mS_ccs_e2);
   print_int("n_ccs_e2", mn_ccs_e2);
   print_int("c_ncs", mc_ncs);
   print_int("c_ncs_d0close", mc_ncs_d0close);
   print_int("c_ncs_p2", mc_ncs_p2);
   print_int("c_ncs_wz", mc_ncs_wz);
   print_int("c_ncs_ntracks", mc_ncs_ntracks);
   print_int("c_ncs_chen", mc_ncs_chen);
   print_int("c_ncs_l4dec", mc_ncs_l4dec);
   print_hist1("h_ncs_hadtrig", mh_ncs_hadtrig);
   print_hist1("h_ncs_e1", mh_ncs_e1);
   print_hist1("h_ncs_e2", mh_ncs_e2);
   print_double("s_ncs_e1", ms_ncs_e1);
   print_double("S_ncs_e1", mS_ncs_e1);
   print_int("n_ncs_e1", mn_ncs_e1);
   print_double("s_ncs_e2", ms_ncs_e2);
   print_double("S_ncs_e2", mS_ncs_e2);
   print_int("n_ncs_e2", mn_ncs_e2);
   print_hist1("t_ccs", mt_ccs);
   print_hist1("t_ncs", mt_ncs);
   print_hist1("T_ccs", mT_ccs);
   print_hist1("T_ncs", mT_ncs);
}

// ---------------- standard place to book histograms ---------------
void
UpsilonGammaEEAnalysisProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   m_run = 0;
   m_last = 0;

   mc_all = 0;
   mt_all = iHistoManager.histogram("all events through the run", 100, 0., 1.);
   mT_all = iHistoManager.histogram("all EVENTS through the run", 100, 0., 1.);
   mc_reallyeverything = 0;
   mc_badbunch = 0;
   mc_ellell = 0;
   mc_photos = 0;

   mh_had_trig = iHistoManager.histogram("trigger | other hadron cuts", 8, -0.5, 7.5);
   mh_had_d0close1 = iHistoManager.histogram("d0close | other hadron cuts", 120, -0.06, 0.06);
   mh_had_d0close2 = iHistoManager.histogram("log10(d0close) | other hadron cuts", 140, -7., 0.);
   mh_had_p2 = iHistoManager.histogram("p2 | other hadron cuts", 120, 0., 1.2);
   mh_had_wz1 = iHistoManager.histogram("wz | other hadron cuts", 100, -0.10, 0.10);
   mh_had_wz2 = iHistoManager.histogram("log10(wz) | other hadron cuts", 120, -6., 0.);
   mh_had_z0close1 = iHistoManager.histogram("z0close | other hadron cuts and wz failure", 100, -0.10, 0.10);
   mh_had_z0close2 = iHistoManager.histogram("log10(z0close) | other hadron cuts and wz failure", 120, -6., 0.);
   mh_had_visen = iHistoManager.histogram("visen | other hadron cuts", 120, 0., 1.2);
   mH_had_trig = iHistoManager.histogram("hadron trigger | no other cuts", 8, -0.5, 7.5);
   mH_had_d0close1 = iHistoManager.histogram("d0close | previous hadron cuts", 120, -0.06, 0.06);
   mH_had_d0close2 = iHistoManager.histogram("log10(d0close) | previous hadron cuts", 120, -6., 0.);
   mH_had_p2 = iHistoManager.histogram("p2 | previous hadron cuts", 120, 0., 1.2);
   mH_had_wz1 = iHistoManager.histogram("wz | previous hadron cuts", 100, -0.10, 0.10);
   mH_had_wz2 = iHistoManager.histogram("log10(wz) | previous hadron cuts", 120, -6., 0.);
   mH_had_z0close1 = iHistoManager.histogram("z0close | previous hadron cuts and wz failure", 100, -0.10, 0.10);
   mH_had_z0close2 = iHistoManager.histogram("log10(z0close) | previous hadron cuts and wz failure", 120, -6., 0.);
   mH_had_visen = iHistoManager.histogram("visen | previous hadron cuts", 120, 0., 1.2);
   mc_had = 0;
   mc_had_trig = 0;
   mc_had_d0close = 0;
   mc_had_p2 = 0;
   mc_had_wz = 0;
   mc_had_visen = 0;
   mc_had_l4dec = 0;
   mw_had_d0close = 0;
   mw_had_p2 = 0;
   mw_had_wz = 0;
   mw_had_visen = 0;
   mC_had_trig = 0;
   mC_had_d0close = 0;
   mC_had_p2 = 0;
   mC_had_wz = 0;
   mC_had_visen = 0;
   mC_had_l4dec = 0;
   mc_old_hadron = 0;
   mh_had_ntracks = iHistoManager.histogram("ntracks | hadron cuts", 19, -0.5, 18.5);
   mc_had_gt2track = 0;
   mc_had_gt4track = 0;
   mh_had_coolvisen = iHistoManager.histogram("coolvisen | hadron cuts other than visen", 120, 0., 1.2);
   mh_had_coolvisen_nol4dec = iHistoManager.histogram("coolvisen | hadron cuts other than visen and l4dec", 120, 0., 1.2);
   mt_had = iHistoManager.histogram("hadron events through the run", 100, 0., 1.);
   mT_had = iHistoManager.histogram("hadron EVENTS through the run", 100, 0., 1.);

   mh_gam_e2 = iHistoManager.histogram("e2 | other gamgam cuts", 120, 0., 1.2);
   mh_gam_ntracks = iHistoManager.histogram("ntracks | gamgam cuts", 5, -0.5, 4.5);
   mh_gam_zback = iHistoManager.histogram("ring1+ring2-69 | other gamgam cuts", 9, -4.5, 4.5);
   mh_gam_z1 = iHistoManager.histogram("ring1-34.5 | other gamgam cuts", 48, -24., 24.);
   mh_gam_z2 = iHistoManager.histogram("ring2-34.5 | other gamgam cuts", 48, -24., 24.);
   mh_gam_z1_noexclude = iHistoManager.histogram("ring1-34.5 | other gamgam cuts except exclude regions", 48, -24., 24.);
   mh_gam_z2_noexclude = iHistoManager.histogram("ring2-34.5 | other gamgam cuts except exclude regions", 48, -24., 24.);
   mh_gam_phiback = iHistoManager.histogram("cell1-cell2+-64 | other gamgam cuts", 11, -5.5, 5.5);
   mh_gam_phiback_notracks = iHistoManager.histogram("cell1-cell2+-64 | other gamgam cuts and no tracks", 11, -5.5, 5.5);
   mc_gam = 0;
   mc_gam_trig = 0;
   mc_gam_oppositesides = 0;
   mc_gam_e2 = 0;
   mc_gam_ntracks = 0;
   mc_gam_zback = 0;
   mc_gam_zouter = 0;
   mc_gam_zinner = 0;
   mc_gam_phiback = 0;
   mc_gam_excludebadtrig = 0;
   mc_gam_excludebadwiremap = 0;
   mc_gam_l4dec = 0;
   mw_gam_e2 = 0;
   mw_gam_ntracks = 0;
   mw_gam_zback = 0;
   mw_gam_zouter = 0;
   mw_gam_zinner = 0;
   mw_gam_phiback = 0;
   mw_gam_excludebadtrig = 0;
   mw_gam_excludebadwiremap = 0;
   mC_gam_trig = 0;
   mC_gam_oppositesides = 0;
   mC_gam_e2 = 0;
   mC_gam_ntracks = 0;
   mC_gam_zback = 0;
   mC_gam_zouter = 0;
   mC_gam_zinner = 0;
   mC_gam_phiback = 0;
   mC_gam_excludebadtrig = 0;
   mC_gam_excludebadwiremap = 0;
   mC_gam_l4dec = 0;
   mc_old_gamgam = 0;
   mh_gam_trigcorrect = iHistoManager.histogram("cotT | gamgam cuts", 130, 0., 1.3);
   mh_gam_e3in = iHistoManager.histogram("e3 | gamgam cuts and all rings but the last one", 125, 0.060, 0.185);
   mh_gam_e3out = iHistoManager.histogram("e3 | gamgam cuts and only last ring", 125, 0.060, 0.185);
   mt_gam = iHistoManager.histogram("gamgam events through the run", 100, 0., 1.);
   mT_gam = iHistoManager.histogram("gamgam EVENTS through the run", 100, 0., 1.);
   m2_gam_cellringwest = iHistoManager.histogram("west cell, ring | gamgam cuts", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_gam_cellringeast = iHistoManager.histogram("east cell, ring | gamgam cuts", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_gam_cellringwest_noexclude = iHistoManager.histogram("west cell, ring | gamgam cuts except exclude blocks", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_gam_cellringeast_noexclude = iHistoManager.histogram("east cell, ring | gamgam cuts except exclude blocks", 128, -0.5, 127.5, 24, 10.5, 34.5);

   mh_tkl_e2 = iHistoManager.histogram("e2 | other trackless bhabha cuts", 120, 0., 1.2);
   mh_tkl_ntracks = iHistoManager.histogram("ntracks | trackless bhabha cuts", 5, -0.5, 4.5);
   mh_tkl_zback = iHistoManager.histogram("ring1+ring2-69 | other trackless bhabha cuts", 9, -4.5, 4.5);
   mh_tkl_z1 = iHistoManager.histogram("ring1-34.5 | other trackless bhabha cuts", 48, -24., 24.);
   mh_tkl_z2 = iHistoManager.histogram("ring2-34.5 | other trackless bhabha cuts", 48, -24., 24.);
   mh_tkl_z1_noexclude = iHistoManager.histogram("ring1-34.5 | other trackless bhabha cuts except exclude regions", 48, -24., 24.);
   mh_tkl_z2_noexclude = iHistoManager.histogram("ring2-34.5 | other trackless bhabha cuts except exclude regions", 48, -24., 24.);
   mh_tkl_phiback = iHistoManager.histogram("cell1-cell2+-64 | other trackless bhabha cuts", 11, -5.5, 5.5);
   mh_tkl_phiback_notrackcut = iHistoManager.histogram("cell1-cell2+-64 | other trackless bhabha cuts except track cut", 11, -5.5, 5.5);
   mc_tkl = 0;
   mc_tkl_trig = 0;
   mc_tkl_oppositesides = 0;
   mc_tkl_e2 = 0;
   mc_tkl_ntracks = 0;
   mc_tkl_zback = 0;
   mc_tkl_zouter = 0;
   mc_tkl_zinner = 0;
   mc_tkl_phiback = 0;
   mc_tkl_excludebadtrig = 0;
   mc_tkl_excludebadwiremap = 0;
   mc_tkl_l4dec = 0;
   mw_tkl_e2 = 0;
   mw_tkl_zback = 0;
   mw_tkl_zouter = 0;
   mw_tkl_zinner = 0;
   mw_tkl_phiback1 = 0;
   mw_tkl_phiback2 = 0;
   mw_tkl_excludebadtrig = 0;
   mw_tkl_excludebadwiremap = 0;
   mw_tkl_eltrack = 0;
   mc_old_trackless = 0;
   mt_tkl = iHistoManager.histogram("trackless bhabha events through the run", 100, 0., 1.);
   mt_tkl_nontracks = iHistoManager.histogram("trackless bhabha events, relaxing ntracks constraint, through the run", 100, 0., 1.);
   mt_tkl_eltrack = iHistoManager.histogram("trackless bhabha events, requiring no eltrack, through the run", 100, 0., 1.);
   mT_tkl = iHistoManager.histogram("trackless bhabha EVENTS through the run", 100, 0., 1.);
   mT_tkl_nontracks = iHistoManager.histogram("trackless bhabha EVENTS, relaxing ntracks constraint, through the run", 100, 0., 1.);
   mT_tkl_eltrack = iHistoManager.histogram("trackless bhabha EVENTS, requiring no eltrack, through the run", 100, 0., 1.);

   mh_bha_trig = iHistoManager.histogram("trigger | other bhabha cuts", 4, -0.5, 3.5);
   mh_bha_p2 = iHistoManager.histogram("p2 | other bhabha cuts", 120, 0., 1.2);
   mh_bha_d0close1 = iHistoManager.histogram("d0close | other bhabha cuts", 120, -0.06, 0.06);
   mh_bha_d0close2 = iHistoManager.histogram("log10(d0close) | other bhabha cuts", 140, -7., 0.);
   mh_bha_wz1 = iHistoManager.histogram("wz | other bhabha cuts", 100, -0.10, 0.10);
   mh_bha_wz2 = iHistoManager.histogram("log10(wz) | other bhabha cuts", 120, -6., 0.);
   mh_bha_z0close1 = iHistoManager.histogram("z0close | other bhabha cuts and wz failure", 100, -0.10, 0.10);
   mh_bha_z0close2 = iHistoManager.histogram("log10(z0close) | other bhabha cuts and wz failure", 120, -6., 0.);
   mh_bha_eisr = iHistoManager.histogram("eisr | other bhabha cuts", 100, 0., 1.);
   mh_bha_econstraint = iHistoManager.histogram("econstraint | other bhabha cuts", 100, 0., 1.);
   mh_bha_costheta1 = iHistoManager.histogram("positive costheta | other bhabha cuts", 100, -1., 1.);
   mh_bha_costheta2 = iHistoManager.histogram("negative costheta | other bhabha cuts", 100, -1., 1.);
   mh_bha_e2 = iHistoManager.histogram("e2 | other bhabha cuts", 120, 0., 1.2);
   mc_bha = 0;
   mc_bha_trig = 0;
   mc_bha_oppositecharge = 0;
   mc_bha_p2 = 0;
   mc_bha_d0close = 0;
   mc_bha_wz = 0;
   mc_bha_eisr = 0;
   mc_bha_econstraint = 0;
   mc_bha_costheta = 0;
   mc_bha_e2 = 0;
   mc_bha_l4dec = 0;
   mw_bha_p2 = 0;
   mw_bha_d0close = 0;
   mw_bha_wz = 0;
   mw_bha_eisr = 0;
   mw_bha_econstraint = 0;
   mw_bha_costheta = 0;
   mw_bha_e2 = 0;
   mc_old_bhabha = 0;
   mh_bha_trignumer = iHistoManager.histogram("cotT | bhabha cuts and gamgam trigger", 130, 0., 1.3);
   mh_bha_trigdenom = iHistoManager.histogram("cotT | bhabha cuts", 130, 0., 1.3);
   mh_bha_trignumer_showergeometry = iHistoManager.histogram("cotT | bhabha cuts and showergeometry and gamgam trigger", 130, 0., 1.3);
   mh_bha_trigdenom_showergeometry = iHistoManager.histogram("cotT | bhabha cuts and showergeometry", 130, 0., 1.3);
   mh_bha_trignumer_showergeometry2 = iHistoManager.histogram("cotT | bhabha cuts and showergeometry2 and gamgam trigger", 130, 0., 1.3);
   mh_bha_trigdenom_showergeometry2 = iHistoManager.histogram("cotT | bhabha cuts and showergeometry2", 130, 0., 1.3);
   mh_bha_trignumer_excludeblocks = iHistoManager.histogram("cotT | bhabha cuts and excludeblocks and gamgam trigger", 130, 0., 1.3);
   mh_bha_trigdenom_excludeblocks = iHistoManager.histogram("cotT | bhabha cuts and excludeblocks", 130, 0., 1.3);
   mh_bha_trignumer_showergeometry_excludeblocks = iHistoManager.histogram("cotT | bhabha cuts and showergeometry and excludeblocks and gamgam trigger", 130, 0., 1.3);
   mh_bha_trigdenom_showergeometry_excludeblocks = iHistoManager.histogram("cotT | bhabha cuts and showergeometry and excludeblocks", 130, 0., 1.3);
   mh_bha_trignumer_showergeometry2_excludeblocks = iHistoManager.histogram("cotT | bhabha cuts and showergeometry2 and excludeblocks and gamgam trigger", 130, 0., 1.3);
   mh_bha_trigdenom_showergeometry2_excludeblocks = iHistoManager.histogram("cotT | bhabha cuts and showergeometry2 and excludeblocks", 130, 0., 1.3);
   mt_bha = iHistoManager.histogram("bhabha events through the run", 100, 0., 1.);
   mT_bha = iHistoManager.histogram("bhabha EVENTS through the run", 100, 0., 1.);
   m2_bha_trignumer_cellringwest = iHistoManager.histogram("west cell, ring | bhabha cuts and gamgam trigger", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trignumer_cellringeast = iHistoManager.histogram("east cell, ring | bhabha cuts and gamgam trigger", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trigdenom_cellringwest = iHistoManager.histogram("west cell, ring | bhabha cuts", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trigdenom_cellringeast = iHistoManager.histogram("east cell, ring | bhabha cuts", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trignumer_cellringwest_showergeometry = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry and gamgam trigger", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trignumer_cellringeast_showergeometry = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry and gamgam trigger", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trigdenom_cellringwest_showergeometry = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trigdenom_cellringeast_showergeometry = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trignumer_cellringwest_showergeometry2 = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry2 and gamgam trigger", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trignumer_cellringeast_showergeometry2 = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry2 and gamgam trigger", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trigdenom_cellringwest_showergeometry2 = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry2", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trigdenom_cellringeast_showergeometry2 = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry2", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trignumer_cellringwest_excludeblocks = iHistoManager.histogram("west cell, ring | bhabha cuts and excludeblocks and gamgam trigger", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trignumer_cellringeast_excludeblocks = iHistoManager.histogram("east cell, ring | bhabha cuts and excludeblocks and gamgam trigger", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trigdenom_cellringwest_excludeblocks = iHistoManager.histogram("west cell, ring | bhabha cuts and excludeblocks", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trigdenom_cellringeast_excludeblocks = iHistoManager.histogram("east cell, ring | bhabha cuts and excludeblocks", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trignumer_cellringwest_showergeometry_excludeblocks = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry and excludeblocks and gamgam trigger", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trignumer_cellringeast_showergeometry_excludeblocks = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry and excludeblocks and gamgam trigger", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trigdenom_cellringwest_showergeometry_excludeblocks = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry and excludeblocks", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trigdenom_cellringeast_showergeometry_excludeblocks = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry and excludeblocks", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trignumer_cellringwest_showergeometry2_excludeblocks = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry2 and excludeblocks and gamgam trigger", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trignumer_cellringeast_showergeometry2_excludeblocks = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry2 and excludeblocks and gamgam trigger", 128, -0.5, 127.5, 24, 10.5, 34.5);
   m2_bha_trigdenom_cellringwest_showergeometry2_excludeblocks = iHistoManager.histogram("west cell, ring | bhabha cuts and showergeometry2 and excludeblocks", 128, -0.5, 127.5, 24, 34.5, 58.5);
   m2_bha_trigdenom_cellringeast_showergeometry2_excludeblocks = iHistoManager.histogram("east cell, ring | bhabha cuts and showergeometry2 and excludeblocks", 128, -0.5, 127.5, 24, 10.5, 34.5);

   mh_mup_trig = iHistoManager.histogram("trigger | other mupair cuts", 4, -0.5, 3.5);
   mh_mup_p2 = iHistoManager.histogram("p2 | other mupair cuts", 120, 0., 1.2);
   mh_mup_d0close1 = iHistoManager.histogram("d0close | other mupair cuts", 120, -0.06, 0.06);
   mh_mup_d0close2 = iHistoManager.histogram("log10(d0close) | other mupair cuts", 140, -7., 0.);
   mh_mup_wz1 = iHistoManager.histogram("wz | other mupair cuts", 100, -0.10, 0.10);
   mh_mup_wz2 = iHistoManager.histogram("log10(wz) | other mupair cuts", 120, -6., 0.);
   mh_mup_z0close1 = iHistoManager.histogram("z0close | other mupair cuts and wz failure", 100, -0.10, 0.10);
   mh_mup_z0close2 = iHistoManager.histogram("log10(z0close) | other mupair cuts and wz failure", 120, -6., 0.);
   mh_mup_eisr = iHistoManager.histogram("eisr | other mupair cuts", 100, 0., 1.);
   mh_mup_econstraint = iHistoManager.histogram("econstraint | other mupair cuts", 100, 0., 1.);
   mh_mup_costheta1 = iHistoManager.histogram("positive costheta | other mupair cuts", 100, -1., 1.);
   mh_mup_costheta2 = iHistoManager.histogram("negative costheta | other mupair cuts", 100, -1., 1.);
   mh_mup_e2 = iHistoManager.histogram("e2*ebeam | other mupair cuts", 120, 0., 6.);
   mc_mup = 0;
   mc_mup_trig = 0;
   mc_mup_oppositecharge = 0;
   mc_mup_p2 = 0;
   mc_mup_d0close = 0;
   mc_mup_wz = 0;
   mc_mup_eisr = 0;
   mc_mup_econstraint = 0;
   mc_mup_costheta = 0;
   mc_mup_e2 = 0;
   mc_mup_l4dec = 0;
   mw_mup_p2 = 0;
   mw_mup_d0close = 0;
   mw_mup_wz = 0;
   mw_mup_eisr = 0;
   mw_mup_econstraint = 0;
   mw_mup_costheta = 0;
   mw_mup_e2 = 0;
   mt_mup = iHistoManager.histogram("mupair events through the run", 100, 0., 1.);
   mT_mup = iHistoManager.histogram("mupair EVENTS through the run", 100, 0., 1.);

   mh_cos_trig = iHistoManager.histogram("trigger | other cosmics cuts", 8, -0.5, 7.5);
   mh_cos_ntracks = iHistoManager.histogram("rawtracks | other cosmics cuts", 19, -0.5, 18.5);
   mh_cos_d0close1 = iHistoManager.histogram("d0close | other cosmics cuts", 120, -0.06, 0.06);
   mh_cos_d0close2 = iHistoManager.histogram("log10(d0close) | other cosmics cuts", 140, -7., 0.);
   mh_cos_pdotp1 = iHistoManager.histogram("pdotp | other cosmics cuts", 100, -1., 1.);
   mh_cos_pdotp2 = iHistoManager.histogram("log10(1-abs(pdotp)) | other cosmics cuts", 100, -10., 0.);
   mh_cos_ccen = iHistoManager.histogram("ccen | other cosmics cuts", 120, 0., 1.2);
   mc_cos = 0;
   mc_cos_trig = 0;
   mc_cos_ntracks = 0;
   mc_cos_d0close = 0;
   mc_cos_pdotp = 0;
   mc_cos_ccen = 0;
   mc_cos_l4dec = 0;
   mw_cos_d0close1 = 0;
   mw_cos_d0close2 = 0;
   mw_cos_pdotp = 0;
   mw_cos_ccen = 0;
   mt_cos = iHistoManager.histogram("cosmic-ray events through the run", 100, 0., 1.);
   mT_cos = iHistoManager.histogram("cosmic-ray EVENTS through the run", 100, 0., 1.);
   mh_cos_visen = iHistoManager.histogram("visen | cosmic-ray cuts", 120, 0., 1.2);

   mh_bge_trig = iHistoManager.histogram("trigger | other bge cuts", 8, -0.5, 7.5);
   mh_bge_ntracks = iHistoManager.histogram("ntracks | other bge cuts", 19, -0.5, 18.5);
   mh_bge_d0close1 = iHistoManager.histogram("d0close | other bge cuts", 120, -0.06, 0.06);
   mh_bge_d0close2 = iHistoManager.histogram("log10(d0close) | other bge cuts", 140, -7., 0.);
   mh_bge_wz1 = iHistoManager.histogram("wz | other bge cuts", 100, -0.50, 0.50);
   mh_bge_wz2 = iHistoManager.histogram("log10(wz) | other bge cuts", 120, -6., 0.);
   mh_bge_z0close1 = iHistoManager.histogram("z0close | other bge cuts", 100, -0.10, 0.10);
   mh_bge_z0close2 = iHistoManager.histogram("log10(z0close) | other bge cuts", 120, -6., 0.);
   mh_bge_pdotp1 = iHistoManager.histogram("pdotp | other bge cuts", 100, -1., 1.);
   mh_bge_pdotp2 = iHistoManager.histogram("log10(1-abs(pdotp)) | other bge cuts", 100, -10., 0.);
   mh_bge_wpz = iHistoManager.histogram("wpz | other bge cuts", 100, -1., 1.);
   mc_bge = 0;
   mc_bge_trig = 0;
   mc_bge_ntracks = 0;
   mc_bge_d0close = 0;
   mc_bge_wz = 0;
   mc_bge_pdotp = 0;
   mc_bge_wpz = 0;
   mc_bge_l4dec = 0;
   mw_bge_ntracks = 0;
   mw_bge_d0close = 0;
   mw_bge_wz = 0;
   mw_bge_pdotp = 0;
   mw_bge_wpz = 0;
   mt_bge = iHistoManager.histogram("bge events through the run", 100, 0., 1.);
   mT_bge = iHistoManager.histogram("bge EVENTS through the run", 100, 0., 1.);
   mh_bge_visen = iHistoManager.histogram("visen | bge cuts", 120, 0., 1.2);

   mh_bgp_trig = iHistoManager.histogram("trigger | other bgp cuts", 8, -0.5, 7.5);
   mh_bgp_ntracks = iHistoManager.histogram("ntracks | other bgp cuts", 19, -0.5, 18.5);
   mh_bgp_d0close1 = iHistoManager.histogram("d0close | other bgp cuts", 120, -0.06, 0.06);
   mh_bgp_d0close2 = iHistoManager.histogram("log10(d0close) | other bgp cuts", 140, -7., 0.);
   mh_bgp_wz1 = iHistoManager.histogram("wz | other bgp cuts", 100, -0.50, 0.50);
   mh_bgp_wz2 = iHistoManager.histogram("log10(wz) | other bgp cuts", 120, -6., 0.);
   mh_bgp_z0close1 = iHistoManager.histogram("z0close | other bgp cuts", 100, -0.10, 0.10);
   mh_bgp_z0close2 = iHistoManager.histogram("log10(z0close) | other bgp cuts", 120, -6., 0.);
   mh_bgp_pdotp1 = iHistoManager.histogram("pdotp | other bgp cuts", 100, -1., 1.);
   mh_bgp_pdotp2 = iHistoManager.histogram("log10(1-abs(pdotp)) | other bgp cuts", 100, -10., 0.);
   mh_bgp_wpz = iHistoManager.histogram("wpz | other bgp cuts", 100, -1., 1.);
   mc_bgp = 0;
   mc_bgp_trig = 0;
   mc_bgp_ntracks = 0;
   mc_bgp_d0close = 0;
   mc_bgp_wz = 0;
   mc_bgp_pdotp = 0;
   mc_bgp_wpz = 0;
   mc_bgp_l4dec = 0;
   mw_bgp_ntracks = 0;
   mw_bgp_d0close = 0;
   mw_bgp_wz = 0;
   mw_bgp_pdotp = 0;
   mw_bgp_wpz = 0;
   mt_bgp = iHistoManager.histogram("bgp events through the run", 100, 0., 1.);
   mT_bgp = iHistoManager.histogram("bgp EVENTS through the run", 100, 0., 1.);
   mh_bgp_visen = iHistoManager.histogram("visen | bgp cuts", 120, 0., 1.2);

   mh_ccs_d0close1 = iHistoManager.histogram("d0close | other ccs cuts", 120, -0.06, 0.06);
   mh_ccs_d0close2 = iHistoManager.histogram("log10(d0close) | other ccs cuts", 140, -7., 0.);
   mh_ccs_p2 = iHistoManager.histogram("p2 | other ccs cuts", 120, 0., 1.2);
   mh_ccs_wz1 = iHistoManager.histogram("wz | other ccs cuts", 100, -0.10, 0.10);
   mh_ccs_wz2 = iHistoManager.histogram("log10(wz) | other ccs cuts", 120, -6., 0.);
   mh_ccs_z0close1 = iHistoManager.histogram("z0close | other ccs cuts", 100, -0.10, 0.10);
   mh_ccs_z0close2 = iHistoManager.histogram("log10(z0close) | other ccs cuts", 120, -6., 0.);
   mh_ccs_ntracks = iHistoManager.histogram("ntracks | other ccs cuts", 19, -0.5, 18.5);
   mh_ccs_chen = iHistoManager.histogram("chen | other ccs cuts", 120, 0., 1.2);
   mc_ccs = 0;
   mc_ccs_d0close = 0;
   mc_ccs_p2 = 0;
   mc_ccs_wz = 0;
   mc_ccs_ntracks = 0;
   mc_ccs_chen = 0;
   mc_ccs_l4dec = 0;
   mc_ccs_hadtrig = 0;
   mh_ccs_hadtrig = iHistoManager.histogram("hadron trigger | css cuts", 8, -0.5, 7.5);
   mh_ccs_e1 = iHistoManager.histogram("e1 | css cuts", 80, 0., 4.);
   mh_ccs_e2 = iHistoManager.histogram("e2 | css cuts", 80, 0., 4.);
   ms_ccs_e1 = 0.;
   mS_ccs_e1 = 0.;
   mn_ccs_e1 = 0;
   ms_ccs_e2 = 0.;
   mS_ccs_e2 = 0.;
   mn_ccs_e2 = 0;
   mc_ncs = 0;
   mc_ncs_d0close = 0;
   mc_ncs_p2 = 0;
   mc_ncs_wz = 0;
   mc_ncs_ntracks = 0;
   mc_ncs_chen = 0;
   mc_ncs_l4dec = 0;
   mh_ncs_hadtrig = iHistoManager.histogram("hadron trigger | hadron but not css", 8, -0.5, 7.5);
   mh_ncs_e1 = iHistoManager.histogram("e1 | hadron but not css", 80, 0., 4.);
   mh_ncs_e2 = iHistoManager.histogram("e2 | hadron but not css", 80, 0., 4.);
   ms_ncs_e1 = 0.;
   mS_ncs_e1 = 0.;
   mn_ncs_e1 = 0;
   ms_ncs_e2 = 0.;
   mS_ncs_e2 = 0.;
   mn_ncs_e2 = 0;
   mt_ccs = iHistoManager.histogram("ccs events through the run", 100, 0., 1.);
   mt_ncs = iHistoManager.histogram("ncs events through the run", 100, 0., 1.);
   mT_ccs = iHistoManager.histogram("ccs EVENTS through the run", 100, 0., 1.);
   mT_ncs = iHistoManager.histogram("ncs EVENTS through the run", 100, 0., 1.);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
UpsilonGammaEEAnalysisProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // cout << "one" << endl;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);

   FAItem<RunStats> stats;
   if (m_runstats.value()) extract(iFrame.record(Stream::kBeginRun), stats);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<EventType> type;
   extract(iFrame.record(Stream::kEvent), type);

   FAItem<TriggerL1Data> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   FAItem<BunchDecision> bunch;
   if (head->monteCarlo()) extract(iFrame.record(Stream::kEvent), bunch);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   // cout << "two" << endl;

   FAItem<MCDecayTree> tree;
   if (head->monteCarlo()) extract(iFrame.record(Stream::kEvent), tree, "Generator");

   // cout << "three" << endl;

   if (!head->monteCarlo()) {
      if (m_run == 0) m_run = head->run();
      // this should only be used on one run at a time
      assert(m_run == head->run());
   }

   if (m_runstats.value()) {
      if (head->number() > stats->lastEvNum()) {
	 report(SYSTEM, kFacilityString)
	    << "DISASTERA: event " << head->number() << " is beyond lastEvNum = " << stats->lastEvNum()
	    << " ; type is " << (type->known() ? "known" : "unknown") << endl;
      }
      if (mc_all > stats->nEvents()) {
	 report(SYSTEM, kFacilityString)
	    << "DISASTERB: event " << head->number() << " is beyond nEvents = " << stats->nEvents()
	    << " ; type is " << (type->known() ? "known" : "unknown") << endl;
      }
   }

   if (head->monteCarlo()) {
      mc_reallyeverything++;

      bool goodbunch = (bunch->numberOfTestedBunches() < 15  &&
			bunch->bestBunchNumber() < 10);
      if (!goodbunch) mc_badbunch++;

      bool ellell = false;
      bool photos = false;
      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();
      const int ups1 = mcppstore.nameToQQId("Upsilon");
      const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
      const int ups3 = mcppstore.nameToQQId("Upsilon(3S)");
      const int eplus = mcppstore.nameToQQId("e+");
      const int eminus = mcppstore.nameToQQId("e-");
      const int muplus = mcppstore.nameToQQId("mu+");
      const int muminus = mcppstore.nameToQQId("mu-");
      const int photon = mcppstore.nameToQQId("gamma");
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().QQId() == ups1  ||
	     viter->parent().properties().QQId() == ups2  ||
	     viter->parent().properties().QQId() == ups3    ) {
	    bool saw_eplus = false, saw_eminus = false;
	    bool saw_muplus = false, saw_muminus = false;
	    bool saw_photon = false;

	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == eplus) saw_eplus = true;
	       if (chiter->properties().QQId() == eminus) saw_eminus = true;
	       if (chiter->properties().QQId() == muplus) saw_muplus = true;
	       if (chiter->properties().QQId() == muminus) saw_muminus = true;
	       if (chiter->properties().QQId() == photon) saw_photon = true;
	    }

	    if ((saw_eplus && saw_eminus) || (saw_muplus && saw_muminus)) ellell = true;
	    if (ellell && saw_photon) photos = true;
	 }
      }

      if (ellell) mc_ellell++;
      if (photos) mc_photos++;

      if (m_goodBunch.value() && !goodbunch) return ActionBase::kFailed;
      if (!m_goodBunch.value() && goodbunch) return ActionBase::kFailed;

      if (m_ellell.value() && !ellell) return ActionBase::kFailed;
      if (!m_ellell.value() && ellell) return ActionBase::kFailed;

      if (m_photos.value() && !photos) return ActionBase::kFailed;
      if (!m_photos.value() && photos) return ActionBase::kFailed;
   }

   // cout << "four" << endl;

   /////////////////////////////////////////////////////////////

   ////////// variables relevant for hadrons
   int triggernumber = (trig->isHadron() ? 4 : 0) + (trig->isRadTau() ? 2 : 0) + (trig->isElTrack() ? 1 : 0);

   double d0close = -1000.;
   double z0close = -1000.;
   double znumer = 0.;
   double zdenom = 0.;
   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
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

	 // Secondary track loop to calculate pairwise intersections
	 for (FATable<NavTrack>::const_iterator other_iter = track_iter;
	      other_iter != tracks_end;  ++other_iter) {
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

   double wz = -1000.;
   if (zdenom != 0.) {
      wz = znumer / zdenom;
      wz -= spot->center().z();
   }   

   double p2 = props->secondLargestPTrack() / eBeam->value();
   double visen = (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value();
   double coolvisen = props->chargedEnergy();
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;  ++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01*eBeam->value()   &&
	  shower_iter->attributes().status()                         &&
	  // differs from EventProperties in requiring !hot
	  !shower_iter->attributes().hot()                           &&
	  shower_iter->noTrackMatch()                                &&
	  // data was processed in pre-2004 releases, so include ConReg
	  showerItr->noTrackMatchConReg()                            &&
	  (!shower_iter->bremTrack().valid()  ||
	   (shower_iter->bremTrack()->trackShowerMatch().valid()  &&
	    shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5)))
	 coolvisen += shower_iter->attributes().energy();
   }
   coolvisen = coolvisen / 2. / eBeam->value();

   // cout << "five" << endl;

   ////////// variables relevant for gamgams/trackless bhabhas

   int ntracks = props->nbChargedTracks();  // these are "quality" tracks
   int rawtracks = tracks.size();

   FATable<NavShower>::const_iterator s1 = showers_end;
   FATable<NavShower>::const_iterator s2 = showers_end;
   FATable<NavShower>::const_iterator s3 = showers_end;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;  ++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01*eBeam->value()   &&
	  shower_iter->attributes().status()                         &&
          // differs from EventProperties in requiring !hot
	  !shower_iter->attributes().hot()) {
	 if (s1 == showers_end  ||  s1->attributes().energy() < shower_iter->attributes().energy()) {
	    s3 = s2;
	    s2 = s1;
	    s1 = shower_iter;
	 }
	 else if (s2 == showers_end  ||  s2->attributes().energy() < shower_iter->attributes().energy()) {
	    s3 = s2;
	    s2 = shower_iter;
	 }
	 else if (s3 == showers_end  ||  s3->attributes().energy() < shower_iter->attributes().energy()) {
	    s3 = shower_iter;
	 }
      }
   }

   bool oppositesides = false;
   double e1 = -1000.;
   double e2 = -1000.;
   double e3 = -1000.;
   int ring1 = -1000;
   int ring2 = -1000;
   int cell1 = -1000;
   int cell2 = -1000;
   double westphi = -1000.;
   double eastphi = -1000.;
   double westcotT = -1000.;
   double eastcotT = -1000.;
   double cotT = -1000.;
   if (s1 != showers_end  &&  s2 != showers_end) {
      oppositesides = cos(s1->attributes().theta()) * cos(s2->attributes().theta()) < 0.;
      e1 = s1->attributes().energy() / eBeam->value();
      e2 = s2->attributes().energy() / eBeam->value();
      ring1 = s1->attributes().ringId();
      ring2 = s2->attributes().ringId();
      cell1 = (s1->attributes().bigCellId() + 11) % 128;
      cell2 = (s2->attributes().bigCellId() + 11) % 128;

      if (oppositesides) {
	 FATable<NavShower>::const_iterator west = (cos(s1->attributes().theta()) > 0. ? s1 : s2);
	 FATable<NavShower>::const_iterator east = (cos(s1->attributes().theta()) > 0. ? s2 : s1);
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
	 cotT = (westcotT - eastcotT)/2.;
      }

      if (s3 != showers_end) {
	 e3 = s3->attributes().energy() / eBeam->value();
      }
   }

   // cout << "six" << endl;

   ////////// variables relevant for bhabhas/mupairs
   bool oppositecharge = false;
   double eisr = -1000.;
   double econstraint = -1000.;
   double cos1 = -1000.;
   double cos2 = -1000.;
   double cosp = -1000.;
   double cosn = -1000.;
   FATable<NavTrack>::const_iterator t1 = tracks.find(props->firstTrackIdentifier());
   FATable<NavTrack>::const_iterator t2 = tracks.find(props->secondTrackIdentifier());
   if (t1 != tracks_end  &&  t2 != tracks_end) {
      oppositecharge = t1->pionHelix()->curvature() * t2->pionHelix()->curvature() < 0.;
      eisr = (t1->pionFit()->momentum() + t2->pionFit()->momentum()).mag();
      econstraint = 2.*eBeam->value() - t1->pionFit()->momentum().mag() - t2->pionFit()->momentum().mag() - eisr;
      
      eisr = eisr / eBeam->value();
      econstraint = econstraint / 2. / eBeam->value();

      cos1 = t1->pionHelix()->cotTheta() / sqrt(1. + sqr(t1->pionHelix()->cotTheta()));
      cos2 = t2->pionHelix()->cotTheta() / sqrt(1. + sqr(t2->pionHelix()->cotTheta()));

      if (oppositecharge) {
	 if (t1->pionHelix()->curvature() > 0.) {
	    cosp = cos1;
	    cosn = cos2;
	 }
	 else {
	    cosp = cos2;
	    cosn = cos1;
	 }
      }
   }

   // cout << "seven" << endl;

   ////////// variables relevant for cosmic rays/beamgas
   double wpz = -1000.;
   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
      if (! track_iter->seedQuality()->originUsed()             &&
	  ! track_iter->pionQuality()->fitAbort()               &&
	  1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	  ! track_iter->pionHelix()->hasNullErrorMatrix()       &&
	  // this is what differs from the wz cuts:
	  sqrt(fabs(track_iter->pionFit()->errorMatrix()(
		       KTKinematicData::kPz, KTKinematicData::kPz))) < 1.) {
	 if (wpz == -1000.) wpz = 0.;
	 wpz += track_iter->pionFit()->pz();
      }
   }
   if (wpz != -1000.) wpz = wpz / eBeam->value();

   double pdotp = 0.;  // this defaults to NOT back-to-back
   FATable<NavTrack>::const_iterator anyt1 = tracks_end;
   FATable<NavTrack>::const_iterator anyt2 = tracks_end;
   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
      if (anyt1 == tracks_end  ||  anyt1->pionFit()->momentum().mag() < track_iter->pionFit()->momentum().mag()) {
	 anyt2 = anyt1;
	 anyt1 = track_iter;
      }
      else if (anyt2 == tracks_end  ||  anyt2->pionFit()->momentum().mag() < track_iter->pionFit()->momentum().mag()) {
	 anyt2 = track_iter;
      }
   }
   if (anyt1 != tracks_end  &&  anyt2 != tracks_end) {
      pdotp = anyt1->pionFit()->momentum().unit().dot(anyt2->pionFit()->momentum().unit());
   }

   double ccen = 0.;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;  ++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01*eBeam->value()   &&
	  shower_iter->attributes().status()                         &&
          // differs from EventProperties in requiring !hot
	  !shower_iter->attributes().hot()) {
	 ccen += shower_iter->attributes().energy();
      }
   }
   ccen = ccen / 2. / eBeam->value();

   // cout << "eight" << endl;

   ////////// variables relevant for the CC trigger study
   double chen = props->chargedEnergy() / 2. / eBeam->value();

   ////////// variables relevant for finding how far we are through the run
   double fraction = -1000.;
   double FRACTION = -1000.;
   if (m_runstats.value()) {
      fraction = double(head->number()) / double(stats->lastEvNum());
      FRACTION = double(mc_all) / double(stats->nEvents());
   }

   /////////////////////////////////////////////////////////////

   // cout << "nine" << endl;

   // hadron cuts
   bool had_trig = trig->isHadron() || trig->isRadTau() || trig->isElTrack();
   bool had_d0close = fabs(d0close) < 0.005;
   bool had_p2 = p2 < 0.7;
   bool had_wz = fabs(wz) < 0.075  ||  (wz == -1000.  &&  fabs(z0close) < 0.075);
   bool had_visen = visen > 0.4;
   bool had_l4dec = l4dec->decision() > 0;
   
   bool had_d0close_wiggle = fabs(d0close) < 0.002;
   bool had_p2_wiggle = p2 < 0.6;
   bool had_wz_wiggle = fabs(wz) < 0.05  ||  (wz == -1000.  &&  fabs(z0close) < 0.05);
   bool had_visen_wiggle = visen > 0.5;

   bool had = had_trig && had_d0close && had_p2 && had_wz && had_visen && had_l4dec;
   bool old_hadron = had_trig && had_d0close && had_wz && had_l4dec &&
      (props->firstLargestEShower() / eBeam->value() < 0.85)  &&
      (props->secondLargestPTrack() / eBeam->value() < 0.85)  &&
      (visen > 0.35)                                          &&
      (ntracks >= 2)                                          &&
      (props->ccTotalEnergy() / 2. / eBeam->value() < 0.85);

   // cout << "ten" << endl;

   // gamgam cuts
   bool gam_trig = trig->isBarrelBhabha();
   bool gam_oppositesides = oppositesides;  // implies two showers
   bool gam_e2 = e2 > 0.7;                  // implies visen > 0.4
   bool gam_ntracks = true;                 // any number of tracks
   bool gam_zback = abs(ring1 + ring2 - 69) <= 2;
   // with zback, zouter is an asymmetric cut near cos(theta) == 0.7
   bool gam_zouter = (fabs(double(ring1) - 34.5) < 18.5  ||
		      fabs(double(ring2) - 34.5) < 18.5     );
   // with zback, zinner is an asymmetric cut near cos(theta) == 0.1
   bool gam_zinner = (fabs(double(ring1) - 34.5) > 1.5  ||
		      fabs(double(ring2) - 34.5) > 1.5     );
   bool gam_phiback = (abs(cell1 - cell2 + 64) <= 1  ||
		       abs(cell1 - cell2 - 64) <= 1     );
   bool gam_excludebadtrig = !((57 <= cell1  &&  cell1 <= 66  &&  36 <= ring1  &&  ring1 <= 45)  ||
			       (57 <= cell2  &&  cell2 <= 66  &&  36 <= ring2  &&  ring2 <= 45)     );
   bool gam_excludebadwiremap = !((55 <= cell1  &&  cell1 <= 58  &&  40 <= ring1  &&  ring1 <= 51)  ||
				  (55 <= cell1  &&  cell1 <= 58  &&  40 <= ring1  &&  ring1 <= 51)     );
   bool gam_l4dec = l4dec->decision() > 0;

   bool gam_e2_wiggle = e2 > 0.8;
   bool gam_ntracks_wiggle = (ntracks == 0);
   bool gam_zback_wiggle = abs(ring1 + ring2 - 69) <= 1;
   bool gam_zouter_wiggle = (fabs(double(ring1) - 34.5) < 17.5  ||
			     fabs(double(ring2) - 34.5) < 17.5     );
   bool gam_zinner_wiggle = (fabs(double(ring1) - 34.5) > 2.5  ||
			     fabs(double(ring2) - 34.5) > 2.5     );
   bool gam_phiback_wiggle = (abs(cell1 - cell2 + 64) == 0  ||
			      abs(cell1 - cell2 - 64) == 0     );
   bool gam_excludebadtrig_wiggle = !((56 <= cell1  &&  cell1 <= 67  &&  35 <= ring1  &&  ring1 <= 46)  ||
				      (56 <= cell2  &&  cell2 <= 67  &&  35 <= ring2  &&  ring2 <= 46)     );
   bool gam_excludebadwiremap_wiggle = !((54 <= cell1  &&  cell1 <= 59  &&  39 <= ring1  &&  ring1 <= 52)  ||
					 (54 <= cell1  &&  cell1 <= 59  &&  39 <= ring1  &&  ring1 <= 52)     );
   bool gam_1_is_west = false;
   if (oppositesides) gam_1_is_west = cos(s1->attributes().theta()) > 0.;

   bool gam = gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback &&
      gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec;
   
   bool old_gamgam = gam_trig && gam_l4dec && gam_oppositesides && gam_ntracks           &&
      (e2 > 0.9)                                                                         &&
      (0.15 < fabs(cotT) && fabs(cotT) < 1.28)                                           &&
      (fabs(westcotT + eastcotT) < 0.1)                                                  &&
      (fabs(sin(westphi - eastphi)) < 0.04)                                              &&
      !(-14.0/64.0*M_PI < westphi  &&  westphi < 9.0/64.0*M_PI  &&  fabs(cotT) < 0.54)   &&
      !(-53.0/64.0*M_PI < westphi  &&  westphi < -14.0/64.0*M_PI  &&  fabs(cotT) > 0.95);

   // cout << "eleven" << endl;

   // trackless bhabha cuts
   bool tkl_trig = gam_trig;
   bool tkl_oppositesides = gam_oppositesides;
   bool tkl_e2 = gam_e2;
   bool tkl_ntracks = (rawtracks == 0);
   bool tkl_zback = gam_zback;
   bool tkl_zouter = gam_zouter;
   bool tkl_zinner = gam_zinner;
   bool tkl_phiback = ((1 < abs(cell1 - cell2 + 64)  &&  abs(cell1 - cell2 + 64) <= 5)  ||
		       (1 < abs(cell1 - cell2 - 64)  &&  abs(cell1 - cell2 - 64) <= 5)     );
   bool tkl_excludebadtrig = gam_excludebadtrig;
   bool tkl_excludebadwiremap = gam_excludebadwiremap;
   bool tkl_l4dec = gam_l4dec;

   bool tkl_e2_wiggle = gam_e2_wiggle;
   bool tkl_zback_wiggle = gam_zback_wiggle;
   bool tkl_zouter_wiggle = gam_zouter_wiggle;
   bool tkl_zinner_wiggle = gam_zinner_wiggle;
   bool tkl_phiback_wiggle1 = ((2 < abs(cell1 - cell2 + 64)  &&  abs(cell1 - cell2 + 64) <= 5)  ||
			       (2 < abs(cell1 - cell2 - 64)  &&  abs(cell1 - cell2 - 64) <= 5)     );
   bool tkl_phiback_wiggle2 = ((1 < abs(cell1 - cell2 + 64)  &&  abs(cell1 - cell2 + 64) <= 4)  ||
			       (1 < abs(cell1 - cell2 - 64)  &&  abs(cell1 - cell2 - 64) <= 4)     );
   bool tkl_excludebadtrig_wiggle = gam_excludebadtrig_wiggle;
   bool tkl_excludebadwiremap_wiggle = gam_excludebadwiremap_wiggle;
   bool tkl_eltrack_wiggle = !trig->isElTrack();

   bool tkl = tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback &&
      tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec;

   // only the acolinearity cut is different
   bool old_trackless = gam_trig && gam_l4dec && gam_oppositesides && gam_ntracks        &&
      (e2 > 0.9)                                                                         &&
      (0.15 < fabs(cotT) && fabs(cotT) < 1.28)                                           &&
      (fabs(westcotT + eastcotT) < 0.1)                                                  &&
      (0.04 < fabs(sin(westphi - eastphi))  &&  fabs(sin(westphi - eastphi)) < 0.25)     &&
      !(-14.0/64.0*M_PI < westphi  &&  westphi < 9.0/64.0*M_PI  &&  fabs(cotT) < 0.54)   &&
      !(-53.0/64.0*M_PI < westphi  &&  westphi < -14.0/64.0*M_PI  &&  fabs(cotT) > 0.95);

   // cout << "twelve" << endl;

   // bhabha cuts
   bool bha_trig = trig->isRadTau()  ||  trig->isElTrack();
   bool bha_oppositecharge = oppositecharge;  // implies two quality tracks
   bool bha_p2 = p2 > 0.7;                    // implies visen > 0.4
   bool bha_d0close = had_d0close;
   bool bha_wz = had_wz;
   bool bha_eisr = eisr < 0.2;
   bool bha_econstraint = econstraint < 0.2;
   bool bha_costheta = (cos1 < 0.79  &&  cos2 < 0.76) || (cos1 < 0.76  &&  cos2 < 0.79);
   bool bha_e2 = e2 > 0.4;
   bool bha_l4dec = l4dec->decision() > 0;

   bool bha_p2_wiggle = p2 > 0.8;
   bool bha_d0close_wiggle = had_d0close_wiggle;
   bool bha_wz_wiggle = had_wz_wiggle;
   bool bha_eisr_wiggle = eisr < 0.1;
   bool bha_econstraint_wiggle = econstraint < 0.1;
   bool bha_costheta_wiggle = (cos1 < 0.69  &&  cos2 < 0.66) || (cos1 < 0.66  &&  cos2 < 0.69);
   bool bha_e2_wiggle = e2 > 0.5;

   bool bha = bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz &&
      bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec;

   bool old_bhabha = had_trig && bha_d0close && bha_eisr              &&
      (visen > 0.75)                                                  &&
      (props->ccTotalEnergy() / 2. / eBeam->value())                  &&
      (fabs(wz) < 0.05  ||  (wz == -1000.  &&  fabs(z0close) < 0.05)) &&
      (2 <= ntracks && ntracks <= 4) && (fabs(econstraint) < 0.2);

   // cout << "thirteen" << endl;

   // mupair cuts
   bool mup_trig = bha_trig;
   bool mup_oppositecharge = bha_oppositecharge;
   bool mup_p2 = bha_p2;
   bool mup_d0close = bha_d0close;
   bool mup_wz = bha_wz;
   bool mup_eisr = bha_eisr;
   bool mup_econstraint = bha_econstraint;
   bool mup_costheta = bha_costheta;
   bool mup_e2 = e2*eBeam->value() < 2.;  // 2 GeV or -1000.*eBeam (not found)
   bool mup_l4dec = bha_l4dec;

   bool mup_p2_wiggle = bha_p2_wiggle;
   bool mup_d0close_wiggle = bha_d0close_wiggle;
   bool mup_wz_wiggle = bha_wz_wiggle;
   bool mup_eisr_wiggle = bha_eisr_wiggle;
   bool mup_econstraint_wiggle = bha_econstraint_wiggle;
   bool mup_costheta_wiggle = bha_costheta_wiggle;
   bool mup_e2_wiggle = e2*eBeam->value() < 1.;

   bool mup = mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz &&
      mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec;

   // cout << "fourteen" << endl;

   // cosmic ray cuts
   bool cos_trig = had_trig;
   bool cos_ntracks = rawtracks >= 2;
   bool cos_d0close = 0.005 < fabs(d0close)  &&  fabs(d0close) < 0.10;
   bool cos_pdotp = abs(pdotp) > 0.999;
   bool cos_ccen = ccen * 2. * eBeam->value() < 4.;  // 4 GeV
   bool cos_l4dec = l4dec->decision() > 0;

   bool cos_d0close_wiggle1 = 0.010 < fabs(d0close)  &&  fabs(d0close) < 0.10;
   bool cos_d0close_wiggle2 = 0.005 < fabs(d0close)  &&  fabs(d0close) < 0.7;
   bool cos_pdotp_wiggle = abs(pdotp) > 0.9999;
   bool cos_ccen_wiggle = ccen * 2. * eBeam->value() < 2.;

   bool cos = cos_trig && cos_ntracks && cos_d0close && cos_pdotp && cos_ccen && cos_l4dec;

   // cout << "fifteen" << endl;

   // electron beam-gas cuts
   bool bge_trig = had_trig;
   bool bge_ntracks = ntracks >= 2;
   bool bge_d0close = fabs(d0close) < 0.005;
   bool bge_wz = (fabs(wz) > 0.075)  ||  (wz == -1000.  &&  (fabs(z0close) > 0.075));
   bool bge_pdotp = abs(pdotp) < 0.9;
   bool bge_wpz = wpz != -1000.  &&  wpz < -0.2;
   bool bge_l4dec = l4dec->decision() > 0;

   bool bge_ntracks_wiggle = ntracks >= 3;
   bool bge_d0close_wiggle = fabs(d0close) < 0.01;
   bool bge_wz_wiggle = fabs(wz) > 0.010  ||  (wz == -1000.  &&  fabs(z0close) > 0.010);
   bool bge_pdotp_wiggle = abs(pdotp) < 0.8;
   bool bge_wpz_wiggle = wpz != -1000.  &&  wpz < -0.4;

   bool bge = bge_trig && bge_ntracks && bge_d0close && bge_wz && bge_pdotp && bge_wpz && bge_l4dec;

   // cout << "sixteen" << endl;

   // positron beam-gas cuts
   bool bgp_trig = bge_trig;
   bool bgp_ntracks = bge_ntracks;
   bool bgp_d0close = bge_d0close;
   bool bgp_wz = bge_wz;
   bool bgp_pdotp = bge_pdotp;
   bool bgp_wpz = wpz != -1000.  &&  wpz > 0.2;
   bool bgp_l4dec = bge_l4dec;

   bool bgp_ntracks_wiggle = bge_ntracks_wiggle;
   bool bgp_d0close_wiggle = bge_d0close_wiggle;
   bool bgp_wz_wiggle = bge_wz_wiggle;
   bool bgp_pdotp_wiggle = bge_pdotp_wiggle;
   bool bgp_wpz_wiggle = wpz != -1000.  &&  wpz > 0.4;

   bool bgp = bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec;

   // cout << "seventeen" << endl;

   // CC trigger study cuts
   bool ccs_trig = trig->isTwoTrack();
   bool ccs_d0close = had_d0close;
   bool ccs_p2 = had_p2;
   bool ccs_wz = had_wz;
   bool ccs_ntracks = ntracks >= 2;  // all events with visen > 0.04 and ntracks >= 2 are available in the database
   bool ccs_chen = chen > 0.04;      // implies visen > 0.04 without needing to invoke the crystals
   bool ccs_l4dec = had_l4dec;

   bool ccs = ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec;

   // different modes for gamgam trigger correction
   bool showergeometry = gam_zback && tkl_phiback;
   bool showergeometry2 = gam_zback && tkl_phiback && gam_zouter && gam_zinner;
   bool excludeblocks = gam_excludebadtrig && gam_excludebadwiremap;

   // for the Upsilon --> gamma chi_b --> gamma gamma gamma search
   bool lastring = (fabs(double(ring1) - 34.5) == 17.5) || (fabs(double(ring2) - 34.5) == 17.5);

   // cout << "eighteen" << endl;

   /////////////////////////////////////////////////////////////

   m_last = head->number();
   m_ebeam = eBeam->value();

   mc_all++;
   mt_all->fill(fraction);
   mT_all->fill(FRACTION);

   //  had_trig && had_d0close && had_p2 && had_wz && had_visen && had_l4dec
   if (            had_d0close && had_p2 && had_wz && had_visen && had_l4dec) mh_had_trig->fill(triggernumber);
   if (had_trig &&                had_p2 && had_wz && had_visen && had_l4dec) mh_had_d0close1->fill(d0close);
   if (had_trig &&                had_p2 && had_wz && had_visen && had_l4dec) mh_had_d0close2->fill(log10(fabs(d0close)));
   if (had_trig && had_d0close &&           had_wz && had_visen && had_l4dec) mh_had_p2->fill(p2);
   if (had_trig && had_d0close && had_p2 &&           had_visen && had_l4dec) mh_had_wz1->fill(wz);
   if (had_trig && had_d0close && had_p2 &&           had_visen && had_l4dec) mh_had_wz2->fill(log10(fabs(wz)));
   if (had_trig && had_d0close && had_p2 &&           had_visen && had_l4dec && wz == -1000.) mh_had_z0close1->fill(z0close);
   if (had_trig && had_d0close && had_p2 &&           had_visen && had_l4dec && wz == -1000.) mh_had_z0close2->fill(log10(fabs(z0close)));
   if (had_trig && had_d0close && had_p2 && had_wz &&              had_l4dec) mh_had_visen->fill(visen);
   if (true) mH_had_trig->fill(triggernumber);
   if (had_trig) mH_had_d0close1->fill(d0close);
   if (had_trig) mH_had_d0close2->fill(log10(fabs(d0close)));
   if (had_trig && had_d0close) mH_had_p2->fill(p2);
   if (had_trig && had_d0close && had_p2) mH_had_wz1->fill(wz);
   if (had_trig && had_d0close && had_p2) mH_had_wz2->fill(log10(fabs(wz)));
   if (had_trig && had_d0close && had_p2 && wz == -1000.) mH_had_z0close1->fill(z0close);
   if (had_trig && had_d0close && had_p2 && wz == -1000.) mH_had_z0close2->fill(log10(fabs(z0close)));
   if (had_trig && had_d0close && had_p2 && had_wz) mH_had_visen->fill(visen);
   //  had_trig && had_d0close && had_p2 && had_wz && had_visen && had_l4dec
   if (had) mc_had++;
   if (            had_d0close && had_p2 && had_wz && had_visen && had_l4dec) mc_had_trig++;
   if (had_trig &&                had_p2 && had_wz && had_visen && had_l4dec) mc_had_d0close++;
   if (had_trig && had_d0close &&           had_wz && had_visen && had_l4dec) mc_had_p2++;
   if (had_trig && had_d0close && had_p2 &&           had_visen && had_l4dec) mc_had_wz++;
   if (had_trig && had_d0close && had_p2 && had_wz &&              had_l4dec) mc_had_visen++;
   if (had_trig && had_d0close && had_p2 && had_wz && had_visen             ) mc_had_l4dec++;
   if (had && had_d0close_wiggle) mw_had_d0close++;
   if (had && had_p2_wiggle) mw_had_p2++;
   if (had && had_wz_wiggle) mw_had_wz++;
   if (had && had_visen_wiggle) mw_had_visen++;
   if (had_trig) mC_had_trig++;
   if (had_trig && had_d0close) mC_had_d0close++;
   if (had_trig && had_d0close && had_p2) mC_had_p2++;
   if (had_trig && had_d0close && had_p2 && had_wz) mC_had_wz++;
   if (had_trig && had_d0close && had_p2 && had_wz && had_visen) mC_had_visen++;
   if (had_trig && had_d0close && had_p2 && had_wz && had_visen && had_l4dec) mC_had_l4dec++;
   if (old_hadron) mc_old_hadron++;
   if (had) mh_had_ntracks->fill(ntracks);
   if (had && (ntracks > 2)) mc_had_gt2track++;
   if (had && (ntracks > 4)) mc_had_gt4track++;
   //  had_trig && had_d0close && had_p2 && had_wz && had_visen && had_l4dec
   if (had_trig && had_d0close && had_p2 && had_wz &&              had_l4dec) mh_had_coolvisen->fill(coolvisen);
   if (had_trig && had_d0close && had_p2 && had_wz                          ) mh_had_coolvisen_nol4dec->fill(coolvisen);
   if (had) mt_had->fill(fraction);
   if (had) mT_had->fill(FRACTION);

   // cout << "ninteen" << endl;

   //  gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec
   if (gam_trig && gam_oppositesides && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mh_gam_e2->fill(e2);
   if (gam_trig && gam_oppositesides && gam_e2 && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mh_gam_ntracks->fill(ntracks);
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mh_gam_zback->fill(ring1+ring2-69);
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) {
      mh_gam_z1->fill(double(ring1)-34.5);
      mh_gam_z2->fill(double(ring2)-34.5);
   }
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_phiback && gam_l4dec) {
      mh_gam_z1_noexclude->fill(double(ring1)-34.5);
      mh_gam_z2_noexclude->fill(double(ring2)-34.5);
   }
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) { mh_gam_phiback->fill(cell1-cell2+64); mh_gam_phiback->fill(cell1-cell2-64); }
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec && (ntracks == 0)) { mh_gam_phiback_notracks->fill(cell1-cell2+64); mh_gam_phiback_notracks->fill(cell1-cell2-64); }
   if (gam) mc_gam++;
   if (            gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_trig++;
   if (gam_trig &&                      gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_oppositesides++;
   if (gam_trig && gam_oppositesides &&           gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_e2++;
   if (gam_trig && gam_oppositesides && gam_e2 &&                gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_ntracks++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks &&              gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_zback++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback &&               gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_zouter++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter &&               gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_zinner++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner &&                gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mc_gam_phiback++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback &&                       gam_excludebadwiremap && gam_l4dec) mc_gam_excludebadtrig++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig &&                          gam_l4dec) mc_gam_excludebadwiremap++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap             ) mc_gam_l4dec++;
   if (gam && gam_e2_wiggle) mw_gam_e2++;
   if (gam && gam_ntracks_wiggle) mw_gam_ntracks++;
   if (gam && gam_zback_wiggle) mw_gam_zback++;
   if (gam && gam_zouter_wiggle) mw_gam_zouter++;
   if (gam && gam_zinner_wiggle) mw_gam_zinner++;
   if (gam && gam_phiback_wiggle) mw_gam_phiback++;
   if (gam && gam_excludebadtrig_wiggle) mw_gam_excludebadtrig++;
   if (gam && gam_excludebadwiremap_wiggle) mw_gam_excludebadwiremap++;
   if (gam_trig) mC_gam_trig++;
   if (gam_trig && gam_oppositesides) mC_gam_oppositesides++;
   if (gam_trig && gam_oppositesides && gam_e2) mC_gam_e2++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks) mC_gam_ntracks++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback) mC_gam_zback++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter) mC_gam_zouter++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner) mC_gam_zinner++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback) mC_gam_phiback++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig) mC_gam_excludebadtrig++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap) mC_gam_excludebadwiremap++;
   if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec) mC_gam_l4dec++;
   if (old_gamgam) mc_old_gamgam++;
   if (gam) mh_gam_trigcorrect->fill(cotT);
   if (gam && !lastring) mh_gam_e3in->fill(e3 * eBeam->value());
   if (gam && lastring) mh_gam_e3out->fill(e3 * eBeam->value());
   if (gam) mt_gam->fill(fraction);
   if (gam) mT_gam->fill(FRACTION);
   if (oppositesides) {
      if (gam && gam_1_is_west) { m2_gam_cellringwest->fill(cell1, ring1);  m2_gam_cellringeast->fill(cell2, ring2); }
      if (gam && !gam_1_is_west) { m2_gam_cellringwest->fill(cell2, ring2);  m2_gam_cellringeast->fill(cell1, ring1); }
      //  gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_excludebadtrig && gam_excludebadwiremap && gam_l4dec
      if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_l4dec && gam_1_is_west) { m2_gam_cellringwest_noexclude->fill(cell1, ring1);  m2_gam_cellringeast_noexclude->fill(cell2, ring2); }
      if (gam_trig && gam_oppositesides && gam_e2 && gam_ntracks && gam_zback && gam_zouter && gam_zinner && gam_phiback && gam_l4dec && !gam_1_is_west) { m2_gam_cellringwest_noexclude->fill(cell2, ring2);  m2_gam_cellringeast_noexclude->fill(cell1, ring1); }
   }

   // cout << "twenty" << endl;

   //  tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec
   if (tkl_trig && tkl_oppositesides && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mh_tkl_e2->fill(e2);
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mh_tkl_ntracks->fill(rawtracks);
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mh_tkl_zback->fill(ring1+ring2-69);
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) {
      mh_tkl_z1->fill(double(ring1)-34.5);
      mh_tkl_z2->fill(double(ring2)-34.5);
   }
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_phiback && tkl_l4dec) {
      mh_tkl_z1_noexclude->fill(double(ring1)-34.5);
      mh_tkl_z2_noexclude->fill(double(ring2)-34.5);
   }
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) { mh_tkl_phiback->fill(cell1-cell2+64); mh_tkl_phiback->fill(cell1-cell2-64); }
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_zback && tkl_zouter && tkl_zinner && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) { mh_tkl_phiback_notrackcut->fill(cell1-cell2+64); mh_tkl_phiback_notrackcut->fill(cell1-cell2-64); }
   //  tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec
   if (tkl) mc_tkl++;
   if (            tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_trig++;
   if (tkl_trig &&                      tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_oppositesides++;
   if (tkl_trig && tkl_oppositesides &&           tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_e2++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 &&                tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_ntracks++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks &&              tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_zback++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback &&               tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_zouter++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter &&               tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_zinner++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner &&                tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mc_tkl_phiback++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback &&                       tkl_excludebadwiremap && tkl_l4dec) mc_tkl_excludebadtrig++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig &&                          tkl_l4dec) mc_tkl_excludebadwiremap++;
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_ntracks && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap             ) mc_tkl_l4dec++;
   if (tkl && tkl_e2_wiggle) mw_tkl_e2++;
   if (tkl && tkl_zback_wiggle) mw_tkl_zback++;
   if (tkl && tkl_zouter_wiggle) mw_tkl_zouter++;
   if (tkl && tkl_zinner_wiggle) mw_tkl_zinner++;
   if (tkl && tkl_phiback_wiggle1) mw_tkl_phiback1++;
   if (tkl && tkl_phiback_wiggle2) mw_tkl_phiback2++;
   if (tkl && tkl_excludebadtrig_wiggle) mw_tkl_excludebadtrig++;
   if (tkl && tkl_excludebadwiremap_wiggle) mw_tkl_excludebadwiremap++;
   if (tkl && tkl_eltrack_wiggle) mw_tkl_eltrack++;
   if (old_trackless) mc_old_trackless++;
   if (tkl) mt_tkl->fill(fraction);
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mt_tkl_nontracks->fill(fraction);
   if (tkl && tkl_eltrack_wiggle) mt_tkl_eltrack->fill(fraction);
   if (tkl) mT_tkl->fill(FRACTION);
   if (tkl_trig && tkl_oppositesides && tkl_e2 && tkl_zback && tkl_zouter && tkl_zinner && tkl_phiback && tkl_excludebadtrig && tkl_excludebadwiremap && tkl_l4dec) mT_tkl_nontracks->fill(FRACTION);
   if (tkl && tkl_eltrack_wiggle) mT_tkl_eltrack->fill(FRACTION);

   // cout << "twenty-one" << endl;

   //  bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec
   if (            bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_trig->fill(triggernumber);
   if (bha_trig && bha_oppositecharge &&           bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_p2->fill(p2);
   if (bha_trig && bha_oppositecharge && bha_p2 &&                bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_d0close1->fill(d0close);
   if (bha_trig && bha_oppositecharge && bha_p2 &&                bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_d0close2->fill(log10(fabs(d0close)));
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close &&           bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_wz1->fill(wz);
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close &&           bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_wz2->fill(log10(fabs(wz)));
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close &&           bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec && wz == -1000.) mh_bha_z0close1->fill(z0close);
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close &&           bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec && wz == -1000.) mh_bha_z0close2->fill(log10(fabs(z0close)));
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz &&             bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mh_bha_eisr->fill(eisr);
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr &&                    bha_costheta && bha_e2 && bha_l4dec) mh_bha_econstraint->fill(econstraint);
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint &&                 bha_e2 && bha_l4dec) mh_bha_costheta1->fill(cosp);
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint &&                 bha_e2 && bha_l4dec) mh_bha_costheta2->fill(cosn);
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta &&           bha_l4dec) mh_bha_e2->fill(e2);
   //  bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec
   if (bha) mc_bha++;
   if (            bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mc_bha_trig++;
   if (bha_trig &&                       bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mc_bha_oppositecharge++;
   if (bha_trig && bha_oppositecharge &&           bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mc_bha_p2++;
   if (bha_trig && bha_oppositecharge && bha_p2 &&                bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mc_bha_d0close++;
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close &&           bha_eisr && bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mc_bha_wz++;
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz &&             bha_econstraint && bha_costheta && bha_e2 && bha_l4dec) mc_bha_eisr++;
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr &&                    bha_costheta && bha_e2 && bha_l4dec) mc_bha_econstraint++;
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint &&                 bha_e2 && bha_l4dec) mc_bha_costheta++;
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta &&           bha_l4dec) mc_bha_e2++;
   if (bha_trig && bha_oppositecharge && bha_p2 && bha_d0close && bha_wz && bha_eisr && bha_econstraint && bha_costheta && bha_e2             ) mc_bha_l4dec++;
   if (bha && bha_p2_wiggle) mw_bha_p2++;
   if (bha && bha_d0close_wiggle) mw_bha_d0close++;
   if (bha && bha_wz_wiggle) mw_bha_wz++;
   if (bha && bha_eisr_wiggle) mw_bha_eisr++;
   if (bha && bha_econstraint_wiggle) mw_bha_econstraint++;
   if (bha && bha_costheta_wiggle) mw_bha_costheta++;
   if (bha && bha_e2_wiggle) mw_bha_e2++;
   if (old_bhabha) mc_old_bhabha++;
   if (bha && bha_trig) mh_bha_trignumer->fill(cotT);
   if (bha) mh_bha_trigdenom->fill(cotT);
   if (bha && showergeometry && bha_trig) mh_bha_trignumer_showergeometry->fill(cotT);
   if (bha && showergeometry) mh_bha_trigdenom_showergeometry->fill(cotT);
   if (bha && showergeometry2 && bha_trig) mh_bha_trignumer_showergeometry2->fill(cotT);
   if (bha && showergeometry2) mh_bha_trigdenom_showergeometry2->fill(cotT);
   if (bha && excludeblocks && bha_trig) mh_bha_trignumer_excludeblocks->fill(cotT);
   if (bha && excludeblocks) mh_bha_trigdenom_excludeblocks->fill(cotT);
   if (bha && showergeometry && excludeblocks && bha_trig) mh_bha_trignumer_showergeometry_excludeblocks->fill(cotT);
   if (bha && showergeometry && excludeblocks) mh_bha_trigdenom_showergeometry_excludeblocks->fill(cotT);
   if (bha && showergeometry2 && excludeblocks && bha_trig) mh_bha_trignumer_showergeometry2_excludeblocks->fill(cotT);
   if (bha && showergeometry2 && excludeblocks) mh_bha_trigdenom_showergeometry2_excludeblocks->fill(cotT);
   if (bha) mt_bha->fill(fraction);
   if (bha) mT_bha->fill(FRACTION);
   if (oppositesides) {
      if (bha && bha_trig && gam_1_is_west) { m2_bha_trignumer_cellringwest->fill(cell1, ring1);  m2_bha_trignumer_cellringeast->fill(cell2, ring2); }
      if (bha && bha_trig && !gam_1_is_west) { m2_bha_trignumer_cellringwest->fill(cell2, ring2);  m2_bha_trignumer_cellringeast->fill(cell1, ring1); }
      if (bha && gam_1_is_west) { m2_bha_trigdenom_cellringwest->fill(cell1, ring1);  m2_bha_trigdenom_cellringeast->fill(cell2, ring2); }
      if (bha && !gam_1_is_west) { m2_bha_trigdenom_cellringwest->fill(cell2, ring2);  m2_bha_trigdenom_cellringeast->fill(cell1, ring1); }
      if (bha && showergeometry && bha_trig && gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry->fill(cell1, ring1);  m2_bha_trignumer_cellringeast_showergeometry->fill(cell2, ring2); }
      if (bha && showergeometry && bha_trig && !gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry->fill(cell2, ring2);  m2_bha_trignumer_cellringeast_showergeometry->fill(cell1, ring1); }
      if (bha && showergeometry && gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry->fill(cell1, ring1);  m2_bha_trigdenom_cellringeast_showergeometry->fill(cell2, ring2); }
      if (bha && showergeometry && !gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry->fill(cell2, ring2);  m2_bha_trigdenom_cellringeast_showergeometry->fill(cell1, ring1); }
      if (bha && showergeometry2 && bha_trig && gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry2->fill(cell1, ring1);  m2_bha_trignumer_cellringeast_showergeometry2->fill(cell2, ring2); }
      if (bha && showergeometry2 && bha_trig && !gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry2->fill(cell2, ring2);  m2_bha_trignumer_cellringeast_showergeometry2->fill(cell1, ring1); }
      if (bha && showergeometry2 && gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry2->fill(cell1, ring1);  m2_bha_trigdenom_cellringeast_showergeometry2->fill(cell2, ring2); }
      if (bha && showergeometry2 && !gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry2->fill(cell2, ring2);  m2_bha_trigdenom_cellringeast_showergeometry2->fill(cell1, ring1); }
      if (bha && excludeblocks && bha_trig && gam_1_is_west) { m2_bha_trignumer_cellringwest_excludeblocks->fill(cell1, ring1);  m2_bha_trignumer_cellringeast_excludeblocks->fill(cell2, ring2); }
      if (bha && excludeblocks && bha_trig && !gam_1_is_west) { m2_bha_trignumer_cellringwest_excludeblocks->fill(cell2, ring2);  m2_bha_trignumer_cellringeast_excludeblocks->fill(cell1, ring1); }
      if (bha && excludeblocks && gam_1_is_west) { m2_bha_trigdenom_cellringwest_excludeblocks->fill(cell1, ring1);  m2_bha_trigdenom_cellringeast_excludeblocks->fill(cell2, ring2); }
      if (bha && excludeblocks && !gam_1_is_west) { m2_bha_trigdenom_cellringwest_excludeblocks->fill(cell2, ring2);  m2_bha_trigdenom_cellringeast_excludeblocks->fill(cell1, ring1); }
      if (bha && showergeometry && excludeblocks && bha_trig && gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry_excludeblocks->fill(cell1, ring1);  m2_bha_trignumer_cellringeast_showergeometry_excludeblocks->fill(cell2, ring2); }
      if (bha && showergeometry && excludeblocks && bha_trig && !gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry_excludeblocks->fill(cell2, ring2);  m2_bha_trignumer_cellringeast_showergeometry_excludeblocks->fill(cell1, ring1); }
      if (bha && showergeometry && excludeblocks && gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry_excludeblocks->fill(cell1, ring1);  m2_bha_trigdenom_cellringeast_showergeometry_excludeblocks->fill(cell2, ring2); }
      if (bha && showergeometry && excludeblocks && !gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry_excludeblocks->fill(cell2, ring2);  m2_bha_trigdenom_cellringeast_showergeometry_excludeblocks->fill(cell1, ring1); }
      if (bha && showergeometry2 && excludeblocks && bha_trig && gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry2_excludeblocks->fill(cell1, ring1);  m2_bha_trignumer_cellringeast_showergeometry2_excludeblocks->fill(cell2, ring2); }
      if (bha && showergeometry2 && excludeblocks && bha_trig && !gam_1_is_west) { m2_bha_trignumer_cellringwest_showergeometry2_excludeblocks->fill(cell2, ring2);  m2_bha_trignumer_cellringeast_showergeometry2_excludeblocks->fill(cell1, ring1); }
      if (bha && showergeometry2 && excludeblocks && gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry2_excludeblocks->fill(cell1, ring1);  m2_bha_trigdenom_cellringeast_showergeometry2_excludeblocks->fill(cell2, ring2); }
      if (bha && showergeometry2 && excludeblocks && !gam_1_is_west) { m2_bha_trigdenom_cellringwest_showergeometry2_excludeblocks->fill(cell2, ring2);  m2_bha_trigdenom_cellringeast_showergeometry2_excludeblocks->fill(cell1, ring1); }
   }

   // cout << "twenty-two" << endl;

   //  mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec
   if (            mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_trig->fill(triggernumber);
   if (mup_trig && mup_oppositecharge &&           mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_p2->fill(p2);
   if (mup_trig && mup_oppositecharge && mup_p2 &&                mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_d0close1->fill(d0close);
   if (mup_trig && mup_oppositecharge && mup_p2 &&                mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_d0close2->fill(log10(fabs(d0close)));
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close &&           mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_wz1->fill(wz);
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close &&           mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_wz2->fill(log10(fabs(wz)));
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close &&           mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec && wz == -1000.) mh_mup_z0close1->fill(z0close);
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close &&           mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec && wz == -1000.) mh_mup_z0close2->fill(log10(fabs(z0close)));
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz &&             mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mh_mup_eisr->fill(eisr);
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr &&                    mup_costheta && mup_e2 && mup_l4dec) mh_mup_econstraint->fill(econstraint);
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint &&                 mup_e2 && mup_l4dec) mh_mup_costheta1->fill(cosp);
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint &&                 mup_e2 && mup_l4dec) mh_mup_costheta2->fill(cosn);
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta &&           mup_l4dec) mh_mup_e2->fill(e2*eBeam->value());
   //  mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec
   if (mup) mc_mup++;
   if (            mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mc_mup_trig++;
   if (mup_trig &&                       mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mc_mup_oppositecharge++;
   if (mup_trig && mup_oppositecharge &&           mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mc_mup_p2++;
   if (mup_trig && mup_oppositecharge && mup_p2 &&                mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mc_mup_d0close++;
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close &&           mup_eisr && mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mc_mup_wz++;
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz &&             mup_econstraint && mup_costheta && mup_e2 && mup_l4dec) mc_mup_eisr++;
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr &&                    mup_costheta && mup_e2 && mup_l4dec) mc_mup_econstraint++;
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint &&                 mup_e2 && mup_l4dec) mc_mup_costheta++;
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta &&           mup_l4dec) mc_mup_e2++;
   if (mup_trig && mup_oppositecharge && mup_p2 && mup_d0close && mup_wz && mup_eisr && mup_econstraint && mup_costheta && mup_e2             ) mc_mup_l4dec++;
   if (mup && mup_p2_wiggle) mw_mup_p2++;
   if (mup && mup_d0close_wiggle) mw_mup_d0close++;
   if (mup && mup_wz_wiggle) mw_mup_wz++;
   if (mup && mup_eisr_wiggle) mw_mup_eisr++;
   if (mup && mup_econstraint_wiggle) mw_mup_econstraint++;
   if (mup && mup_costheta_wiggle) mw_mup_costheta++;
   if (mup && mup_e2_wiggle) mw_mup_e2++;
   if (mup) mt_mup->fill(fraction);
   if (mup) mT_mup->fill(FRACTION);

   // cout << "twenty-three" << endl;

   //  cos_trig && cos_ntracks && cos_d0close && cos_pdotp && cos_ccen && cos_l4dec
   if (            cos_ntracks && cos_d0close && cos_pdotp && cos_ccen && cos_l4dec) mh_cos_trig->fill(triggernumber);
   if (cos_trig                && cos_d0close && cos_pdotp && cos_ccen && cos_l4dec) mh_cos_ntracks->fill(rawtracks);
   if (cos_trig && cos_ntracks &&                cos_pdotp && cos_ccen && cos_l4dec) mh_cos_d0close1->fill(d0close);
   if (cos_trig && cos_ntracks &&                cos_pdotp && cos_ccen && cos_l4dec) mh_cos_d0close2->fill(log10(fabs(d0close)));
   if (cos_trig && cos_ntracks && cos_d0close &&              cos_ccen && cos_l4dec) mh_cos_pdotp1->fill(pdotp);
   if (cos_trig && cos_ntracks && cos_d0close &&              cos_ccen && cos_l4dec && pdotp != 1.) mh_cos_pdotp2->fill(log10(1.-fabs(pdotp)));
   if (cos_trig && cos_ntracks && cos_d0close && cos_pdotp &&             cos_l4dec) mh_cos_ccen->fill(ccen*2.*eBeam->value());
   //  cos_trig && cos_ntracks && cos_d0close && cos_pdotp && cos_ccen && cos_l4dec
   if (cos) mc_cos++;
   if (            cos_ntracks && cos_d0close && cos_pdotp && cos_ccen && cos_l4dec) mc_cos_trig++;
   if (cos_trig &&                cos_d0close && cos_pdotp && cos_ccen && cos_l4dec) mc_cos_ntracks++;
   if (cos_trig && cos_ntracks &&                cos_pdotp && cos_ccen && cos_l4dec) mc_cos_d0close++;
   if (cos_trig && cos_ntracks && cos_d0close &&              cos_ccen && cos_l4dec) mc_cos_pdotp++;
   if (cos_trig && cos_ntracks && cos_d0close && cos_pdotp &&             cos_l4dec) mc_cos_ccen++;
   if (cos_trig && cos_ntracks && cos_d0close && cos_pdotp && cos_ccen             ) mc_cos_l4dec++;
   if (cos && cos_d0close_wiggle1) mw_cos_d0close1++;
   if (cos && cos_d0close_wiggle2) mw_cos_d0close2++;
   if (cos && cos_pdotp_wiggle) mw_cos_pdotp++;
   if (cos && cos_ccen_wiggle) mw_cos_ccen++;
   if (cos) mt_cos->fill(fraction);
   if (cos) mT_cos->fill(FRACTION);
   if (cos) mh_cos_visen->fill(visen);

   // cout << "twenty-four" << endl;

   //  bge_trig && bge_ntracks && bge_d0close && bge_wz && bge_pdotp && bge_wpz && bge_l4dec
   if (            bge_ntracks && bge_d0close && bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mh_bge_trig->fill(triggernumber);
   if (bge_trig &&                bge_d0close && bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mh_bge_ntracks->fill(ntracks);
   if (bge_trig && bge_ntracks &&                bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mh_bge_d0close1->fill(d0close);
   if (bge_trig && bge_ntracks &&                bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mh_bge_d0close2->fill(log10(fabs(d0close)));
   if (bge_trig && bge_ntracks && bge_d0close &&           bge_pdotp && bge_wpz && bge_l4dec) mh_bge_wz1->fill(wz);
   if (bge_trig && bge_ntracks && bge_d0close &&           bge_pdotp && bge_wpz && bge_l4dec) mh_bge_wz2->fill(log10(fabs(wz)));
   if (bge_trig && bge_ntracks && bge_d0close &&           bge_pdotp && bge_wpz && bge_l4dec && wz == -1000.) mh_bge_z0close1->fill(z0close);
   if (bge_trig && bge_ntracks && bge_d0close &&           bge_pdotp && bge_wpz && bge_l4dec && wz == -1000.) mh_bge_z0close2->fill(log10(fabs(z0close)));
   if (bge_trig && bge_ntracks && bge_d0close && bge_wz &&              bge_wpz && bge_l4dec) mh_bge_pdotp1->fill(pdotp);
   if (bge_trig && bge_ntracks && bge_d0close && bge_wz &&              bge_wpz && bge_l4dec && pdotp != 1.) mh_bge_pdotp2->fill(log10(1.-fabs(pdotp)));
   if (bge_trig && bge_ntracks && bge_d0close && bge_wz && bge_pdotp &&            bge_l4dec) mh_bge_wpz->fill(wpz);
   if (bge) mc_bge++;
   if (            bge_ntracks && bge_d0close && bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mc_bge_trig++;
   if (bge_trig &&                bge_d0close && bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mc_bge_ntracks++;
   if (bge_trig && bge_ntracks &&                bge_wz && bge_pdotp && bge_wpz && bge_l4dec) mc_bge_d0close++;
   if (bge_trig && bge_ntracks && bge_d0close &&           bge_pdotp && bge_wpz && bge_l4dec) mc_bge_wz++;
   if (bge_trig && bge_ntracks && bge_d0close && bge_wz &&              bge_wpz && bge_l4dec) mc_bge_pdotp++;
   if (bge_trig && bge_ntracks && bge_d0close && bge_wz && bge_pdotp &&            bge_l4dec) mc_bge_wpz++;
   if (bge_trig && bge_ntracks && bge_d0close && bge_wz && bge_pdotp && bge_wpz             ) mc_bge_l4dec++;
   if (bge && bge_ntracks_wiggle) mw_bge_ntracks++;
   if (bge && bge_d0close_wiggle) mw_bge_d0close++;
   if (bge && bge_wz_wiggle) mw_bge_wz++;
   if (bge && bge_pdotp_wiggle) mw_bge_pdotp++;
   if (bge && bge_wpz_wiggle) mw_bge_wpz++;
   if (bge) mt_bge->fill(fraction);
   if (bge) mT_bge->fill(FRACTION);
   if (bge) mh_bge_visen->fill(visen);

   // cout << "twenty-five" << endl;

   //  bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec
   if (            bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mh_bgp_trig->fill(triggernumber);
   if (bgp_trig &&                bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mh_bgp_ntracks->fill(ntracks);
   if (bgp_trig && bgp_ntracks &&                bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mh_bgp_d0close1->fill(d0close);
   if (bgp_trig && bgp_ntracks &&                bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mh_bgp_d0close2->fill(log10(fabs(d0close)));
   if (bgp_trig && bgp_ntracks && bgp_d0close &&           bgp_pdotp && bgp_wpz && bgp_l4dec) mh_bgp_wz1->fill(wz);
   if (bgp_trig && bgp_ntracks && bgp_d0close &&           bgp_pdotp && bgp_wpz && bgp_l4dec) mh_bgp_wz2->fill(log10(fabs(wz)));
   if (bgp_trig && bgp_ntracks && bgp_d0close &&           bgp_pdotp && bgp_wpz && bgp_l4dec && wz == -1000.) mh_bgp_z0close1->fill(z0close);
   if (bgp_trig && bgp_ntracks && bgp_d0close &&           bgp_pdotp && bgp_wpz && bgp_l4dec && wz == -1000.) mh_bgp_z0close2->fill(log10(fabs(z0close)));
   if (bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz &&              bgp_wpz && bgp_l4dec) mh_bgp_pdotp1->fill(pdotp);
   if (bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz &&              bgp_wpz && bgp_l4dec && pdotp != 1.) mh_bgp_pdotp2->fill(log10(1.-fabs(pdotp)));
   if (bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp &&            bgp_l4dec) mh_bgp_wpz->fill(wpz);
   if (bgp) mc_bgp++;
   if (            bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mc_bgp_trig++;
   if (bgp_trig &&                bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mc_bgp_ntracks++;
   if (bgp_trig && bgp_ntracks &&                bgp_wz && bgp_pdotp && bgp_wpz && bgp_l4dec) mc_bgp_d0close++;
   if (bgp_trig && bgp_ntracks && bgp_d0close &&           bgp_pdotp && bgp_wpz && bgp_l4dec) mc_bgp_wz++;
   if (bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz &&              bgp_wpz && bgp_l4dec) mc_bgp_pdotp++;
   if (bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp &&            bgp_l4dec) mc_bgp_wpz++;
   if (bgp_trig && bgp_ntracks && bgp_d0close && bgp_wz && bgp_pdotp && bgp_wpz             ) mc_bgp_l4dec++;
   if (bgp && bgp_ntracks_wiggle) mw_bgp_ntracks++;
   if (bgp && bgp_d0close_wiggle) mw_bgp_d0close++;
   if (bgp && bgp_wz_wiggle) mw_bgp_wz++;
   if (bgp && bgp_pdotp_wiggle) mw_bgp_pdotp++;
   if (bgp && bgp_wpz_wiggle) mw_bgp_wpz++;
   if (bgp) mt_bgp->fill(fraction);
   if (bgp) mT_bgp->fill(FRACTION);
   if (bgp) mh_bgp_visen->fill(visen);

   // cout << "twenty-six" << endl;

   //  ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec
   if (ccs_trig &&                ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec) mh_ccs_d0close1->fill(d0close);
   if (ccs_trig &&                ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec) mh_ccs_d0close2->fill(log10(fabs(d0close)));
   if (ccs_trig && ccs_d0close &&           ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec) mh_ccs_p2->fill(p2);
   if (ccs_trig && ccs_d0close && ccs_p2 &&           ccs_ntracks && ccs_chen && ccs_l4dec) mh_ccs_wz1->fill(wz);
   if (ccs_trig && ccs_d0close && ccs_p2 &&           ccs_ntracks && ccs_chen && ccs_l4dec) mh_ccs_wz2->fill(log10(fabs(wz)));
   if (ccs_trig && ccs_d0close && ccs_p2 &&           ccs_ntracks && ccs_chen && ccs_l4dec && wz == -1000.) mh_ccs_z0close1->fill(z0close);
   if (ccs_trig && ccs_d0close && ccs_p2 &&           ccs_ntracks && ccs_chen && ccs_l4dec && wz == -1000.) mh_ccs_z0close2->fill(log10(fabs(z0close)));
   if (ccs_trig && ccs_d0close && ccs_p2 && ccs_wz &&                ccs_chen && ccs_l4dec) mh_ccs_ntracks->fill(ntracks);
   if (ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks &&             ccs_l4dec) mh_ccs_chen->fill(chen);
   if (ccs) mc_ccs++;
   if (ccs_trig &&                ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec) mc_ccs_d0close++;
   if (ccs_trig && ccs_d0close &&           ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec) mc_ccs_p2++;
   if (ccs_trig && ccs_d0close && ccs_p2 &&           ccs_ntracks && ccs_chen && ccs_l4dec) mc_ccs_wz++;
   if (ccs_trig && ccs_d0close && ccs_p2 && ccs_wz &&                ccs_chen && ccs_l4dec) mc_ccs_ntracks++;
   if (ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks &&             ccs_l4dec) mc_ccs_chen++;
   if (ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen             ) mc_ccs_l4dec++;
   if (ccs && had_trig) mc_ccs_hadtrig++;
   if (ccs) mh_ccs_hadtrig->fill(triggernumber);
   if (ccs) mh_ccs_e1->fill(e1);
   if (ccs) mh_ccs_e2->fill(e2);
   if (ccs && e1 >= 0.) { ms_ccs_e1 += e1;  mS_ccs_e1 += sqr(e1);  mn_ccs_e1++; }
   if (ccs && e2 >= 0.) { ms_ccs_e2 += e2;  mS_ccs_e2 += sqr(e2);  mn_ccs_e2++; }
   if (had && !ccs) mc_ncs++;
   if (had && !(ccs_trig &&                ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec)) mc_ncs_d0close++;
   if (had && !(ccs_trig && ccs_d0close &&           ccs_wz && ccs_ntracks && ccs_chen && ccs_l4dec)) mc_ncs_p2++;
   if (had && !(ccs_trig && ccs_d0close && ccs_p2 &&           ccs_ntracks && ccs_chen && ccs_l4dec)) mc_ncs_wz++;
   if (had && !(ccs_trig && ccs_d0close && ccs_p2 && ccs_wz &&                ccs_chen && ccs_l4dec)) mc_ncs_ntracks++;
   if (had && !(ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks &&             ccs_l4dec)) mc_ncs_chen++;
   if (had && !(ccs_trig && ccs_d0close && ccs_p2 && ccs_wz && ccs_ntracks && ccs_chen             )) mc_ncs_l4dec++;
   if ((had && !ccs)) mh_ncs_hadtrig->fill(triggernumber);
   if ((had && !ccs)) mh_ncs_e1->fill(e1*eBeam->value());
   if ((had && !ccs)) mh_ncs_e2->fill(e2*eBeam->value());
   if (had && !ccs && e1 >= 0.) { ms_ncs_e1 += e1;  mS_ncs_e1 += sqr(e1);  mn_ncs_e1++; }
   if (had && !ccs && e2 >= 0.) { ms_ncs_e2 += e2;  mS_ncs_e2 += sqr(e2);  mn_ncs_e2++; }
   if (ccs) mt_ccs->fill(fraction);
   if (had && !ccs) mt_ncs->fill(fraction);
   if (ccs) mT_ccs->fill(FRACTION);
   if (had && !ccs) mT_ncs->fill(FRACTION);

   // cout << "twenty-seven" << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
UpsilonGammaEEAnalysisProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
UpsilonGammaEEAnalysisProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

void UpsilonGammaEEAnalysisProc::print_int(const char *name, int num)
{
   cout << "PYTHON rec." << name << " = " << num << endl;
}

void UpsilonGammaEEAnalysisProc::print_double(const char *name, double num)
{
   cout << "PYTHON rec." << name << " = " << num << endl;
}

void UpsilonGammaEEAnalysisProc::print_hist1(const char *name, HIHist1D* hist)
{
   cout << "PYTHON rec." << name << " = (" << hist->underflow() << ", Numeric.array([";
   for (int i = 1;  i <= hist->nChannels();  i++) {
      cout << hist->channelValue(i) << ", ";
   }
   cout << "]), " << hist->overflow() << ")" << endl;
}

void UpsilonGammaEEAnalysisProc::print_hist2(const char *name, HIHist2D* hist)
{
   cout << "PYTHON rec." << name << " = Numeric.array([";
   for (int i = 1;  i <= hist->nChannelsX();  i++) {
      cout << "[";
      for (int j = 1;  j <= hist->nChannelsY();  j++) {
	 cout << hist->channelValue(i,j) << ", ";
      }
      cout << "], ";
   }
   cout << "])" << endl;
}

DABoolean UpsilonGammaEEAnalysisProc::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean UpsilonGammaEEAnalysisProc::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
