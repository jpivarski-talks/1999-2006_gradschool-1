// #include "TLegend"

//   KEY: TH1F      h1010;1 number of tracks
//   KEY: TH1F      h1020;1 closest intersection
//   KEY: TH1F      h1030;1 weighted z0 
//   KEY: TH1F      h1040;1 visible energy  
//   KEY: TH1F      h1050;1 calorimeter energy  
//   KEY: TH1F      h1060;1 biggest shower energy   
//   KEY: TH1F      h1070;1 second biggest shower energy
//   KEY: TH1F      h1080;1 third biggest shower energy 
//   KEY: TH1F      h1090;1 biggest matched shower energy   
//   KEY: TH1F      h1100;1 second biggest matched shower energy
//   KEY: TH1F      h1110;1 biggest track momentum  
//   KEY: TH1F      h1120;1 second biggest track momentum   
//   KEY: TH1F      h1140;1 sphericity  
//   KEY: TH1F      h1150;1 acoplanarity
//   KEY: TH1F      h1160;1 number of showers   
//   KEY: TH1F      h1170;1 event momentum mag  
//   KEY: TH1F      h1180;1 event momentum perp 
//   KEY: TH1F      h1190;1 event momentum z
//   KEY: TH1F      h1200;1 reconstructed upsilon mass  
//   KEY: TH1F      h1210;1 charged momentum mag
//   KEY: TH1F      h1220;1 charged momentum perp   
//   KEY: TH1F      h1230;1 charged momentum z  
//   KEY: TH1F      h1240;1 charge  
//   KEY: TH1F      h1250;1 indiv track z0  
//   KEY: TH1F      h1260;1 indiv track z0 - event weighted z0  
//   KEY: TH1F      h1270;1 indiv track momentum
//   KEY: TH1F      h1280;1 indiv track momentum perp   
//   KEY: TH1F      h1290;1 indiv track momentum z  
//   KEY: TH1F      h1300;1 indiv shower energy 
//   KEY: TH1F      h1310;1 second closest intersection 
//   KEY: TH1F      h1320;1 third closest intersection  

{
//     TFile f_bhabha_mc("bhabha_mc.root");
   TFile f_cont_fl_mc("cont_fl_mc_cut3.root");
   TFile f_cont_mn_mc("cont_mn_mc_cut3.root");
//     TFile f_electrons("electrons.root");
//     TFile f_gamgam("gamgam.root");
   TFile f_tau("tau_mc_cut3.root");
//     TFile f_monte_carlo("monte_carlo.root");
//     TFile f_positrons("positrons.root");
   TFile f_ups3s_cont("ups3s_cont_cut3.root");
//     TFile f_ups3s_peak("ups3s_peak.root");

   gStyle->SetOptStat(0);

//     double data_scale(1.0);
//     double gam_scale(0.10);
//     double sb_scale(0.10);
//     double cont_scale(1. - gam_scale - sb_scale);

   const char* hists[31] = {
      "h1010", "h1020", "h1030", "h1040", "h1050", "h1060", "h1070",
      "h1080", "h1090", "h1100", "h1110", "h1120", "h1140", "h1150",
      "h1160", "h1170", "h1180", "h1190", "h1200", "h1210", "h1220",
      "h1230", "h1240", "h1250", "h1260", "h1270", "h1280", "h1290",
      "h1300", "h1310", "h1320" };
//   int i;
//   for ( i = 0;  i < 31;  i++ ) {
   {
      TH1F* data = ((TH1F*) ((TDirectory*) f_ups3s_cont.Get("HADRONFILTERPROC"))->Get(hists[i]));
      TH1F* cont_mc = ((TH1F*) ((TDirectory*) f_cont_fl_mc.Get("HADRONFILTERPROC"))->Get(hists[i]));
      cont_mc->Add( ((TH1F*) ((TDirectory*) f_cont_mn_mc.Get("HADRONFILTERPROC"))->Get(hists[i])) );
//        TH1F* gam_mc = ((TH1F*) ((TDirectory*) f_gamgam.Get("HADRONFILTERPROC"))->Get(hists[i]));
      TH1F* tau_mc = ((TH1F*) ((TDirectory*) f_tau.Get("HADRONFILTERPROC"))->Get(hists[i]));
//        TH1F* e_sb = ((TH1F*) ((TDirectory*) f_electrons.Get("HADRONFILTERPROC"))->Get(hists[i]));
//        TH1F* p_sb = ((TH1F*) ((TDirectory*) f_positrons.Get("HADRONFILTERPROC"))->Get(hists[i]));

      data->Sumw2();
      cont_mc->Sumw2();
//        gam_mc->Sumw2();
      tau_mc->Sumw2();
//        e_sb->Sumw2();
//        p_sb->Sumw2();

      cont_mc->Scale(0.2048767);
      tau_mc->Scale(0.097459);

//        data->Scale(data_scale/data->GetEntries());
//        cont_mc->Scale(cont_scale/cont_mc->GetEntries());
//        gam_mc->Scale(gam_scale/gam_mc->GetEntries());
//        e_sb->Scale(sb_scale/(e_sb->GetEntries() + p_sb->GetEntries()));
//        p_sb->Scale(sb_scale/(e_sb->GetEntries() + p_sb->GetEntries()));

//        p_sb->Add(e_sb);
//        gam_mc->Add(p_sb);
//        tau_mc->Add(gam_mc);
      cont_mc->Add(tau_mc);

//     TPad* pad = new TCanvas("pad", "Compare Data and Monte Carlo", 0, 30, 800, 800);  pad->Divide(1,2);
      pad->cd(1);

      data->DrawCopy("E");

      cont_mc->SetFillColor(0);  cont_mc->Draw("samehist");
//        gam_mc->SetFillColor(3);   gam_mc->Draw("samehist");
      tau_mc->SetFillColor(2);   tau_mc->Draw("samehist");
//        p_sb->SetFillColor(2);     p_sb->Draw("samehist");
//        e_sb->SetFillColor(4);     e_sb->Draw("samehist");

      TLegend* leg = new TLegend(0.63, 0.6, 0.97, 0.97);
      data->SetMarkerStyle(2);
      leg->AddEntry(data, "#Upsilon(3S) Continuum Data", "p");
      leg->AddEntry(cont_mc, "#Upsilon(3S) Continuum Monte Carlo", "f");
//        leg->AddEntry(gam_mc, "Two-photon Monte Carlo", "f");
      leg->AddEntry(tau_mc, "Tau Monte Carlo", "f");
//        leg->AddEntry(p_sb, "Positron Single-Beam Data", "f");
//        leg->AddEntry(e_sb, "Electron Single-Beam Data", "f");
      leg->SetTextSizePixels(12);
      leg->Draw();

      pad->cd(2);
      TH1F* residual = new TH1F( *data );
      residual->Add( cont_mc, -1. );
      residual->SetTitle( "residual" );
      residual->Draw();

      TLine line;
      line.DrawLine(-100., 0., 100., 0.);

      char name[100];
      sprintf(name, "%s.ps", hists[i]);
      pad->Print(name, "ps");
   } // end loop over histograms
}


//  ***    1010 (1)   number of tracks
//         1020 (1)   closest intersection
//         1030 (1)   weighted z0 
//  ***    1040 (1)   visible energy  
//         1050 (1)   calorimeter energy  
//         1060 (1)   biggest shower energy   
//         1070 (1)   second biggest shower energy
//         1080 (1)   third biggest shower energy 
//         1090 (1)   biggest matched shower energy   
//         1100 (1)   second biggest matched shower energy
//  ***    1110 (1)   biggest track momentum  
//         1120 (1)   second biggest track momentum   
//  ***    1140 (1)   sphericity  
//         1150 (1)   acoplanarity
//  ***    1160 (1)   number of showers   
//         1170 (1)   event momentum mag  
//  ***    1180 (1)   event momentum perp 
//         1190 (1)   event momentum z
//         1200 (1)   reconstructed upsilon mass  
//         1210 (1)   charged momentum mag
//         1220 (1)   charged momentum perp   
//  ***    1230 (1)   charged momentum z  
//  ***    1240 (1)   charge  
//         1250 (1)   indiv track z0  
//  ***    1260 (1)   indiv track z0 - event weighted z0  
//         1270 (1)   indiv track momentum mag
//         1280 (1)   indiv track momentum perp   
//         1290 (1)   indiv track momentum z  
//         1300 (1)   indiv shower energy 
//         1310 (1)   second closest intersection 
//         1320 (1)   third closest intersection  
