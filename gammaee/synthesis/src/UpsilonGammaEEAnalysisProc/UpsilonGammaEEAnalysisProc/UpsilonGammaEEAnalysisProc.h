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
// Created:     Tue May  3 14:36:21 EDT 2005
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
#include "HistogramInterface/HINtuple.h"
#include "KinematicTrajectory/KTHelix.h"
#include "CommandPattern/Parameter.h"
#include <vector>
#include <string>

// forward declarations

class GEE_Cut
{
   public:
      enum {
	 k_run,
	 k_event,
	 k_ebeam,
	 k_eventfrac,

	 k_trignum,
	 k_bbtrig,
	 k_tttrig,
	 k_eltrig,
	 k_hadtrig,

	 k_d0close,
	 k_z0close,
	 k_logd0close,
	 k_logz0close,
	 k_wz,
	 k_logwz,
	 k_criticalz0close,
	 k_criticallogz0close,
	 k_anyz,
	 k_loganyz,
	 k_p1,
	 k_p2,
	 k_visen,
	 k_coolvisen,
	 k_frozenvisen,

	 k_tracks,
	 k_rawtk,
	 k_oppositesides,
	 k_e1,
	 k_e2,
	 k_e1GeV,
	 k_e2GeV,
	 k_e3GeV,
	 k_1_is_west,
	 k_ring1,
	 k_ring2,
	 k_cell1,
	 k_cell2,
	 k_westphi,
	 k_eastphi,
	 k_westcotT,
	 k_eastcotT,
	 k_cotT,
	 k_thetab2b,
	 k_phib2b,

	 k_oppositecharge,
	 k_eisr,
	 k_econstr,
	 k_cos1,
	 k_cos2,
	 k_cosp,
	 k_cosn,

	 k_wpz,
	 k_pdotp,
	 k_logpdotp,
	 k_ccen,
	 k_neue,

	 k_l4dec,
	 k_olde1,
	 k_olde2,
	 k_oldccen,
	 k_ccenGeV,
	 k_chen,
	 k_breake1,

	 kNumEntries
      };

      GEE_Cut();
      void prepare_hist(int release, int var, int bins, double low, double high, const char* name);
      void prepare_count(const char* name);
      void histbook(HIHistoManager& iHistoManager);
      virtual void histbook_extra(HIHistoManager& iHistoManager);

      virtual void update(float* event);
      bool survive();
      void fill();
      virtual void fill_extra();

      void print();
      virtual void print_extra();
      void print_hist1(string& name, HIHist1D* hist);
      void print_hist2(string& name, HIHist2D* hist);
      
   protected:
      float* v;
      string m_name;
      int m_run;
      int m_lastevent;
      double m_ebeam;

      vector<bool> m_cut;
      vector<bool> m_cut_tight;

      vector<HIHist1D*> m_hist;
      vector<int> m_hist_var;
      vector<int> m_hist_release;
      vector<string> m_hist_name;
      vector<int> m_hist_bins;
      vector<double> m_hist_loww;
      vector<double> m_hist_high;
      
      int m_count;
      vector<int> m_count_release;
      vector<int> m_count_tighten;
      vector<string> m_count_name;

      HIHist1D* m_vstime;
};

class GEE_Hadron : public GEE_Cut
{
   public:
      GEE_Hadron();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      int m_g2tracks;
      int m_g4tracks;
      HIHist1D* m_trignum;
      HIHist1D* m_d0close;
      HIHist1D* m_logd0close;
      HIHist1D* m_wz;
      HIHist1D* m_logwz;
      HIHist1D* m_criticalz0close;
      HIHist1D* m_criticallogz0close;
      HIHist1D* m_anyz;
      HIHist1D* m_loganyz;
      HIHist1D* m_p1;
      HIHist1D* m_coolvisen;
      HIHist1D* m_hotvisen;
      HIHist1D* m_frozenvisen;
      HIHist1D* m_tracks;
      int m_trignum_count;
      int m_d0close_count;
      int m_wz_count;
      int m_p1_count;
      int m_frozenvisen_count;
      int m_l4dec_count;
      int m_p1fail;
      int m_p1fail_bhabha;
      int m_p1fail_mupair;
};

class GEE_HadronCool : public GEE_Cut
{
   public:
      GEE_HadronCool();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      int m_g2tracks;
      int m_g4tracks;
      HIHist1D* m_trignum;
      HIHist1D* m_d0close;
      HIHist1D* m_logd0close;
      HIHist1D* m_wz;
      HIHist1D* m_logwz;
      HIHist1D* m_criticalz0close;
      HIHist1D* m_criticallogz0close;
      HIHist1D* m_anyz;
      HIHist1D* m_loganyz;
      HIHist1D* m_p1;
      HIHist1D* m_coolvisen;
      HIHist1D* m_hotvisen;
      HIHist1D* m_frozenvisen;
      HIHist1D* m_tracks;
      int m_trignum_count;
      int m_d0close_count;
      int m_wz_count;
      int m_p1_count;
      int m_coolvisen_count;
      int m_l4dec_count;
      int m_p1fail;
      int m_p1fail_bhabha;
      int m_p1fail_mupair;
};

class GEE_Oldhadron : public GEE_Cut
{
   public:
      GEE_Oldhadron();
      void update(float* event);
};

class GEE_Oldhadronall : public GEE_Cut
{
   public:
      GEE_Oldhadronall();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      HIHist1D* m_trignum;
      HIHist1D* m_d0close;
      HIHist1D* m_logd0close;
      HIHist1D* m_olde1;
      HIHist1D* m_p2;
      HIHist1D* m_wz;
      HIHist1D* m_logwz;
      HIHist1D* m_criticalz0close;
      HIHist1D* m_criticallogz0close;
      HIHist1D* m_anyz;
      HIHist1D* m_loganyz;
      HIHist1D* m_visen;
      HIHist1D* m_tracks;
      HIHist1D* m_oldccen;
      int m_trignum_count;
      int m_d0close_count;
      int m_olde1_count;
      int m_p2_count;
      int m_wz_count;
      int m_visen_count;
      int m_tracks_count;
      int m_ccen_count;
      int m_l4dec_count;
};

class GEE_Gamgam : public GEE_Cut
{
   public:
      GEE_Gamgam();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      HIHist1D* m_numer;
      HIHist1D* m_denom;
      HIHist2D* m_wherewest;
      HIHist2D* m_whereeast;
      HIHist2D* m_wherewest_noexclude;
      HIHist2D* m_whereeast_noexclude;
      HIHist1D* m_e3GeVin;
      HIHist1D* m_e3GeVout;
      int m_pureggin;
      int m_pureggout;
};

class GEE_Trackless : public GEE_Cut
{
   public:
      GEE_Trackless();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      HIHist1D* m_vstime_releasetrack;
      HIHist1D* m_vstime_tightentrack;
};

class GEE_Bhabha : public GEE_Cut
{
   public:
      GEE_Bhabha();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      HIHist1D* m_numer;
      HIHist1D* m_denom;
      HIHist1D* m_phib2b;
};

class GEE_BhabhaTwoTrack : public GEE_Cut
{
   public:
      GEE_BhabhaTwoTrack();
      void update(float* event);
};

class GEE_Mupair : public GEE_Cut
{
   public:
      GEE_Mupair();
      void update(float* event);
};

class GEE_MupairTwoTrack : public GEE_Cut
{
   public:
      GEE_MupairTwoTrack();
      void update(float* event);
};

class GEE_Cosmic : public GEE_Cut
{
   public:
      GEE_Cosmic();
      void update(float* event);
};

class GEE_BeamgasE : public GEE_Cut
{
   public:
      GEE_BeamgasE();
      void update(float* event);
};

class GEE_BeamgasP : public GEE_Cut
{
   public:
      GEE_BeamgasP();
      void update(float* event);
};

class GEE_BrokenShower : public GEE_Cut
{
   public:
      GEE_BrokenShower();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      HIHist2D* m_where;
      HIHist2D* m_where_tight;
};

class GEE_BrokenShower2 : public GEE_Cut
{
   public:
      GEE_BrokenShower2();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      HIHist2D* m_where;
      HIHist2D* m_where_tight;
};

class GEE_CCStudy1 : public GEE_Cut
{
   public:
      GEE_CCStudy1();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      int m_analtrigcount;
      int m_analtrigcount_fail;
      HIHist1D* m_analtrig_fail;
      HIHist1D* m_e1GeV_fail;
      HIHist1D* m_e2GeV_fail;
};

class GEE_CCStudy2 : public GEE_Cut
{
   public:
      GEE_CCStudy2();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      int m_analtrigcount;
      int m_analtrigcount_fail;
      HIHist1D* m_analtrig_fail;
      HIHist1D* m_e1GeV_fail;
      HIHist1D* m_e2GeV_fail;
};

class GEE_CCStudy3 : public GEE_Cut
{
   public:
      GEE_CCStudy3();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      int m_analtrigcount;
      int m_analtrigcount_fail;
      HIHist1D* m_analtrig_fail;
      HIHist1D* m_e1GeV_fail;
      HIHist1D* m_e2GeV_fail;
};

class GEE_CCStudy4 : public GEE_Cut
{
   public:
      GEE_CCStudy4();
      void update(float* event);
      void histbook_extra(HIHistoManager& iHistoManager);
      void fill_extra();
      void print_extra();
   private:
      int m_analtrigcount;
      int m_analtrigcount_fail;
      HIHist1D* m_analtrig_fail;
      HIHist1D* m_e1GeV_fail;
      HIHist1D* m_e2GeV_fail;
};

class UpsilonGammaEEAnalysisProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_run,
	 k_event,
	 k_trig,
	 k_type,
	 k_d0close,
	 k_anyz,
	 k_p1x,
	 k_p1y,
	 k_p1z,
	 k_p2x,
	 k_p2y,
	 k_p2z,
	 k_visen,
	 k_coolvisen,
	 k_frozenvisen,
	 k_tracks,
	 k_rawtk,
	 k_oppositesides,
	 k_e1,
	 k_e2,
	 k_e3,
	 k_phi1,
	 k_cos1,
	 k_phi2,
	 k_cos2,
	 k_oppositecharge,
	 k_eisr,
	 k_econstr,
	 k_cosp,
	 k_cosn,
	 k_wpz,
	 k_pdotp,
	 k_ccen,
	 k_neue,
	 k_l4dec,
	 k_chen,

	 kNumEntries
      };

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

      bool calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      bool arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;
      GEE_Cut m_cut;
      GEE_Hadron m_hadron;
      GEE_HadronCool m_hadroncool;
      GEE_Oldhadron m_oldhadron;
      GEE_Oldhadronall m_oldhadronall;
      GEE_Gamgam m_gamgam;
      GEE_Trackless m_trackless;
      GEE_Bhabha m_bhabha;
      GEE_Mupair m_mupair;
      GEE_BhabhaTwoTrack m_bhabhatwotrack;
      GEE_MupairTwoTrack m_mupairtwotrack;
      GEE_Cosmic m_cosmic;
      GEE_BeamgasE m_beamgase;
      GEE_BeamgasP m_beamgasp;
      GEE_BrokenShower m_brokenshower;
      GEE_BrokenShower2 m_brokenshower2;
      GEE_CCStudy1 m_ccstudy1;
      GEE_CCStudy2 m_ccstudy2;
      GEE_CCStudy3 m_ccstudy3;
      GEE_CCStudy4 m_ccstudy4;

      int m_mc_all;
      int m_mc_badbunch;
      int m_mc_ellell;
      int m_mc_photos;

      Parameter<DABoolean> m_goodBunch;
      Parameter<DABoolean> m_ellell;
      Parameter<DABoolean> m_photos;
      Parameter<DABoolean> m_runstats;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* UPSILONGAMMAEEANALYSISPROC_UPSILONGAMMAEEANALYSISPROC_H */
