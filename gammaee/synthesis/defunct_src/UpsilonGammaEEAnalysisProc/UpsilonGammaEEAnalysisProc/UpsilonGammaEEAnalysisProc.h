// -*- C++ -*-
#if !defined(UPSILONGAMMAEEANALYSISPROC_UPSILONGAMMAEEANALYSISPROC_H)
#define UPSILONGAMMAEEANALYSISPROC_UPSILONGAMMAEEANALYSISPROC_H
//
// Package:     <UpsilonGammaEEAnalysisProc>
// Module:      UpsilonGammaEEAnalysisProc
//
/**\class UpsilonGammaEEAnalysisProc UpsilonGammaEEAnalysisProc.h UpsilonGammaEEAnalysisProc/UpsilonGammaEEAnalysisProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr 25 15:04:32 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "KinematicTrajectory/KTHelix.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class UpsilonGammaEEAnalysisProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      UpsilonGammaEEAnalysisProc( void );                      // anal1 
      virtual ~UpsilonGammaEEAnalysisProc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      UpsilonGammaEEAnalysisProc( const UpsilonGammaEEAnalysisProc& );

      // ------------ assignment operator(s) ---------------------
      const UpsilonGammaEEAnalysisProc& operator=( const UpsilonGammaEEAnalysisProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (UpsilonGammaEEAnalysisProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void print_int(const char *name, int num);
      void print_double(const char *name, double num);
      void print_hist1(const char *name, HIHist1D* hist);
      void print_hist2(const char *name, HIHist2D* hist);

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_goodBunch;
      Parameter<DABoolean> m_ellell;
      Parameter<DABoolean> m_photos;
      Parameter<DABoolean> m_runstats;

      int m_run;
      int m_last;
      double m_ebeam;

      // extension of the m_ convention:
      //   mc_all is a count of everything
      //   mc_grp is the number that pass a group's cuts
      //   mc_grp_cut is the number that pass a group with that one cut relaxed
      //   mw_grp_cut is the number that pass a group with that one cut tightened
      //   mh_grp_var are histograms of var, subject to group's cuts (except the one plotted)
      //   mH_grp_var are histograms of var, with the group's cuts applied cumulatively and in order
      //   ms_grp_var is the sum of some variable (for calculating the mean)
      //   mS_grp_var is the sum of some variable squared (for calculating the stdev)
      //   mn_grp_var is a counter for the variable (needed for both the mean and the stdev)
      //   mt_grp is a count of the number of events over time (100'ths of the run)
      //   mT_grp counts as a fraction of available events rather than all events
      //   m2_grp_vars is a 2-D histogram

      int mc_all;
      HIHist1D* mt_all;
      HIHist1D* mT_all;
      int mc_reallyeverything;
      int mc_badbunch;
      int mc_ellell;
      int mc_photos;

      HIHist1D* mh_had_trig;
      HIHist1D* mh_had_d0close1;
      HIHist1D* mh_had_d0close2;
      HIHist1D* mh_had_p2;
      HIHist1D* mh_had_wz1;
      HIHist1D* mh_had_wz2;
      HIHist1D* mh_had_z0close1;
      HIHist1D* mh_had_z0close2;
      HIHist1D* mh_had_visen;
      HIHist1D* mH_had_trig;
      HIHist1D* mH_had_d0close1;
      HIHist1D* mH_had_d0close2;
      HIHist1D* mH_had_p2;
      HIHist1D* mH_had_wz1;
      HIHist1D* mH_had_wz2;
      HIHist1D* mH_had_z0close1;
      HIHist1D* mH_had_z0close2;
      HIHist1D* mH_had_visen;
      int mc_had;
      int mc_had_trig;
      int mc_had_d0close;
      int mc_had_p2;
      int mc_had_wz;
      int mc_had_visen;
      int mc_had_l4dec;
      int mw_had_d0close;
      int mw_had_p2;
      int mw_had_wz;
      int mw_had_visen;
      int mC_had_trig;
      int mC_had_d0close;
      int mC_had_p2;
      int mC_had_wz;
      int mC_had_visen;
      int mC_had_l4dec;
      int mc_old_hadron;
      HIHist1D* mh_had_ntracks;
      int mc_had_gt2track;
      int mc_had_gt4track;
      HIHist1D* mh_had_coolvisen;
      HIHist1D* mh_had_coolvisen_nol4dec;
      HIHist1D* mt_had;
      HIHist1D* mT_had;

      HIHist1D* mh_gam_e2;
      HIHist1D* mh_gam_ntracks;
      HIHist1D* mh_gam_zback;
      HIHist1D* mh_gam_z1;
      HIHist1D* mh_gam_z2;
      HIHist1D* mh_gam_z1_noexclude;
      HIHist1D* mh_gam_z2_noexclude;
      HIHist1D* mh_gam_phiback;
      HIHist1D* mh_gam_phiback_notracks;
      int mc_gam;
      int mc_gam_trig;
      int mc_gam_oppositesides;
      int mc_gam_e2;
      int mc_gam_ntracks;
      int mc_gam_zback;
      int mc_gam_zouter;
      int mc_gam_zinner;
      int mc_gam_phiback;
      int mc_gam_excludebadtrig;
      int mc_gam_excludebadwiremap;
      int mc_gam_l4dec;
      int mw_gam_e2;
      int mw_gam_ntracks;
      int mw_gam_zback;
      int mw_gam_zouter;
      int mw_gam_zinner;
      int mw_gam_phiback;
      int mw_gam_excludebadtrig;
      int mw_gam_excludebadwiremap;
      int mC_gam_trig;
      int mC_gam_oppositesides;
      int mC_gam_e2;
      int mC_gam_ntracks;
      int mC_gam_zback;
      int mC_gam_zouter;
      int mC_gam_zinner;
      int mC_gam_phiback;
      int mC_gam_excludebadtrig;
      int mC_gam_excludebadwiremap;
      int mC_gam_l4dec;
      int mc_old_gamgam;
      HIHist1D* mh_gam_trigcorrect;
      HIHist1D* mh_gam_e3in;
      HIHist1D* mh_gam_e3out;
      HIHist1D* mt_gam;
      HIHist1D* mT_gam;
      HIHist2D* m2_gam_cellringwest;
      HIHist2D* m2_gam_cellringeast;
      HIHist2D* m2_gam_cellringwest_noexclude;
      HIHist2D* m2_gam_cellringeast_noexclude;

      HIHist1D* mh_tkl_e2;
      HIHist1D* mh_tkl_ntracks;
      HIHist1D* mh_tkl_zback;
      HIHist1D* mh_tkl_z1;
      HIHist1D* mh_tkl_z2;
      HIHist1D* mh_tkl_z1_noexclude;
      HIHist1D* mh_tkl_z2_noexclude;
      HIHist1D* mh_tkl_phiback;
      HIHist1D* mh_tkl_phiback_notrackcut;
      int mc_tkl;
      int mc_tkl_trig;
      int mc_tkl_oppositesides;
      int mc_tkl_e2;
      int mc_tkl_ntracks;
      int mc_tkl_zback;
      int mc_tkl_zouter;
      int mc_tkl_zinner;
      int mc_tkl_phiback;
      int mc_tkl_excludebadtrig;
      int mc_tkl_excludebadwiremap;
      int mc_tkl_l4dec;
      int mw_tkl_e2;
      int mw_tkl_zback;
      int mw_tkl_zouter;
      int mw_tkl_zinner;
      int mw_tkl_phiback1;
      int mw_tkl_phiback2;
      int mw_tkl_excludebadtrig;
      int mw_tkl_excludebadwiremap;
      int mw_tkl_eltrack;
      int mc_old_trackless;
      HIHist1D* mt_tkl;
      HIHist1D* mt_tkl_nontracks;
      HIHist1D* mt_tkl_eltrack;
      HIHist1D* mT_tkl;
      HIHist1D* mT_tkl_nontracks;
      HIHist1D* mT_tkl_eltrack;

      HIHist1D* mh_bha_trig;
      HIHist1D* mh_bha_p2;
      HIHist1D* mh_bha_d0close1;
      HIHist1D* mh_bha_d0close2;
      HIHist1D* mh_bha_wz1;
      HIHist1D* mh_bha_wz2;
      HIHist1D* mh_bha_z0close1;
      HIHist1D* mh_bha_z0close2;
      HIHist1D* mh_bha_eisr;
      HIHist1D* mh_bha_econstraint;
      HIHist1D* mh_bha_costheta1;
      HIHist1D* mh_bha_costheta2;
      HIHist1D* mh_bha_e2;
      int mc_bha;
      int mc_bha_trig;
      int mc_bha_oppositecharge;
      int mc_bha_p2;
      int mc_bha_d0close;
      int mc_bha_wz;
      int mc_bha_eisr;
      int mc_bha_econstraint;
      int mc_bha_costheta;
      int mc_bha_e2;
      int mc_bha_l4dec;
      int mw_bha_p2;
      int mw_bha_d0close;
      int mw_bha_wz;
      int mw_bha_eisr;
      int mw_bha_econstraint;
      int mw_bha_costheta;
      int mw_bha_e2;
      int mc_old_bhabha;
      HIHist1D* mh_bha_trignumer;
      HIHist1D* mh_bha_trigdenom;
      HIHist1D* mh_bha_trignumer_showergeometry;
      HIHist1D* mh_bha_trigdenom_showergeometry;
      HIHist1D* mh_bha_trignumer_showergeometry2;
      HIHist1D* mh_bha_trigdenom_showergeometry2;
      HIHist1D* mh_bha_trignumer_excludeblocks;
      HIHist1D* mh_bha_trigdenom_excludeblocks;
      HIHist1D* mh_bha_trignumer_showergeometry_excludeblocks;
      HIHist1D* mh_bha_trigdenom_showergeometry_excludeblocks;
      HIHist1D* mh_bha_trignumer_showergeometry2_excludeblocks;
      HIHist1D* mh_bha_trigdenom_showergeometry2_excludeblocks;
      HIHist1D* mt_bha;
      HIHist1D* mT_bha;
      HIHist2D* m2_bha_trignumer_cellringwest;
      HIHist2D* m2_bha_trignumer_cellringeast;
      HIHist2D* m2_bha_trigdenom_cellringwest;
      HIHist2D* m2_bha_trigdenom_cellringeast;
      HIHist2D* m2_bha_trignumer_cellringwest_showergeometry;
      HIHist2D* m2_bha_trignumer_cellringeast_showergeometry;
      HIHist2D* m2_bha_trigdenom_cellringwest_showergeometry;
      HIHist2D* m2_bha_trigdenom_cellringeast_showergeometry;
      HIHist2D* m2_bha_trignumer_cellringwest_showergeometry2;
      HIHist2D* m2_bha_trignumer_cellringeast_showergeometry2;
      HIHist2D* m2_bha_trigdenom_cellringwest_showergeometry2;
      HIHist2D* m2_bha_trigdenom_cellringeast_showergeometry2;
      HIHist2D* m2_bha_trignumer_cellringwest_excludeblocks;
      HIHist2D* m2_bha_trignumer_cellringeast_excludeblocks;
      HIHist2D* m2_bha_trigdenom_cellringwest_excludeblocks;
      HIHist2D* m2_bha_trigdenom_cellringeast_excludeblocks;
      HIHist2D* m2_bha_trignumer_cellringwest_showergeometry_excludeblocks;
      HIHist2D* m2_bha_trignumer_cellringeast_showergeometry_excludeblocks;
      HIHist2D* m2_bha_trigdenom_cellringwest_showergeometry_excludeblocks;
      HIHist2D* m2_bha_trigdenom_cellringeast_showergeometry_excludeblocks;
      HIHist2D* m2_bha_trignumer_cellringwest_showergeometry2_excludeblocks;
      HIHist2D* m2_bha_trignumer_cellringeast_showergeometry2_excludeblocks;
      HIHist2D* m2_bha_trigdenom_cellringwest_showergeometry2_excludeblocks;
      HIHist2D* m2_bha_trigdenom_cellringeast_showergeometry2_excludeblocks;

      HIHist1D* mh_mup_trig;
      HIHist1D* mh_mup_p2;
      HIHist1D* mh_mup_d0close1;
      HIHist1D* mh_mup_d0close2;
      HIHist1D* mh_mup_wz1;
      HIHist1D* mh_mup_wz2;
      HIHist1D* mh_mup_z0close1;
      HIHist1D* mh_mup_z0close2;
      HIHist1D* mh_mup_eisr;
      HIHist1D* mh_mup_econstraint;
      HIHist1D* mh_mup_costheta1;
      HIHist1D* mh_mup_costheta2;
      HIHist1D* mh_mup_e2;
      int mc_mup;
      int mc_mup_trig;
      int mc_mup_oppositecharge;
      int mc_mup_p2;
      int mc_mup_d0close;
      int mc_mup_wz;
      int mc_mup_eisr;
      int mc_mup_econstraint;
      int mc_mup_costheta;
      int mc_mup_e2;
      int mc_mup_l4dec;
      int mw_mup_p2;
      int mw_mup_d0close;
      int mw_mup_wz;
      int mw_mup_eisr;
      int mw_mup_econstraint;
      int mw_mup_costheta;
      int mw_mup_e2;
      HIHist1D* mt_mup;
      HIHist1D* mT_mup;

      HIHist1D* mh_cos_trig;
      HIHist1D* mh_cos_ntracks;
      HIHist1D* mh_cos_d0close1;
      HIHist1D* mh_cos_d0close2;
      HIHist1D* mh_cos_pdotp1;
      HIHist1D* mh_cos_pdotp2;
      HIHist1D* mh_cos_ccen;
      int mc_cos;
      int mc_cos_trig;
      int mc_cos_ntracks;
      int mc_cos_d0close;
      int mc_cos_pdotp;
      int mc_cos_ccen;
      int mc_cos_l4dec;
      int mw_cos_d0close1;
      int mw_cos_d0close2;
      int mw_cos_pdotp;
      int mw_cos_ccen;
      HIHist1D* mt_cos;
      HIHist1D* mT_cos;
      HIHist1D* mh_cos_visen;

      HIHist1D* mh_bge_trig;
      HIHist1D* mh_bge_ntracks;
      HIHist1D* mh_bge_d0close1;
      HIHist1D* mh_bge_d0close2;
      HIHist1D* mh_bge_wz1;
      HIHist1D* mh_bge_wz2;
      HIHist1D* mh_bge_z0close1;
      HIHist1D* mh_bge_z0close2;
      HIHist1D* mh_bge_pdotp1;
      HIHist1D* mh_bge_pdotp2;
      HIHist1D* mh_bge_wpz;
      int mc_bge;
      int mc_bge_trig;
      int mc_bge_ntracks;
      int mc_bge_d0close;
      int mc_bge_wz;
      int mc_bge_pdotp;
      int mc_bge_wpz;
      int mc_bge_l4dec;
      int mw_bge_ntracks;
      int mw_bge_d0close;
      int mw_bge_wz;
      int mw_bge_pdotp;
      int mw_bge_wpz;
      HIHist1D* mt_bge;
      HIHist1D* mT_bge;
      HIHist1D* mh_bge_visen;

      HIHist1D* mh_bgp_trig;
      HIHist1D* mh_bgp_ntracks;
      HIHist1D* mh_bgp_d0close1;
      HIHist1D* mh_bgp_d0close2;
      HIHist1D* mh_bgp_wz1;
      HIHist1D* mh_bgp_wz2;
      HIHist1D* mh_bgp_z0close1;
      HIHist1D* mh_bgp_z0close2;
      HIHist1D* mh_bgp_pdotp1;
      HIHist1D* mh_bgp_pdotp2;
      HIHist1D* mh_bgp_wpz;
      int mc_bgp;
      int mc_bgp_trig;
      int mc_bgp_ntracks;
      int mc_bgp_d0close;
      int mc_bgp_wz;
      int mc_bgp_pdotp;
      int mc_bgp_wpz;
      int mc_bgp_l4dec;
      int mw_bgp_ntracks;
      int mw_bgp_d0close;
      int mw_bgp_wz;
      int mw_bgp_pdotp;
      int mw_bgp_wpz;
      HIHist1D* mt_bgp;
      HIHist1D* mT_bgp;
      HIHist1D* mh_bgp_visen;

      HIHist1D* mh_ccs_d0close1;
      HIHist1D* mh_ccs_d0close2;
      HIHist1D* mh_ccs_p2;
      HIHist1D* mh_ccs_wz1;
      HIHist1D* mh_ccs_wz2;
      HIHist1D* mh_ccs_z0close1;
      HIHist1D* mh_ccs_z0close2;
      HIHist1D* mh_ccs_ntracks;
      HIHist1D* mh_ccs_chen;
      int mc_ccs;
      int mc_ccs_d0close;
      int mc_ccs_p2;
      int mc_ccs_wz;
      int mc_ccs_ntracks;
      int mc_ccs_chen;
      int mc_ccs_l4dec;
      int mc_ccs_hadtrig;
      HIHist1D* mh_ccs_hadtrig;
      HIHist1D* mh_ccs_e1;
      HIHist1D* mh_ccs_e2;
      double ms_ccs_e1;
      double mS_ccs_e1;
      int mn_ccs_e1;
      double ms_ccs_e2;
      double mS_ccs_e2;
      int mn_ccs_e2;
      int mc_ncs;
      int mc_ncs_d0close;
      int mc_ncs_p2;
      int mc_ncs_wz;
      int mc_ncs_ntracks;
      int mc_ncs_chen;
      int mc_ncs_l4dec;
      HIHist1D* mh_ncs_hadtrig;
      HIHist1D* mh_ncs_e1;
      HIHist1D* mh_ncs_e2;
      double ms_ncs_e1;
      double mS_ncs_e1;
      int mn_ncs_e1;
      double ms_ncs_e2;
      double mS_ncs_e2;
      int mn_ncs_e2;
      HIHist1D* mt_ccs;
      HIHist1D* mt_ncs;
      HIHist1D* mT_ccs;
      HIHist1D* mT_ncs;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* UPSILONGAMMAEEANALYSISPROC_UPSILONGAMMAEEANALYSISPROC_H */
