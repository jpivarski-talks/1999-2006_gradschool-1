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
   TFile f_bhabha_mc("bhabha_mc.root");
   TFile f_cont_fl_mc("cont_fl_mc.root");
   TFile f_cont_mn_mc("cont_mn_mc.root");
   TFile f_electrons("electrons.root");
   TFile f_gamgam("gamgam.root");
   TFile f_monte_carlo("monte_carlo.root");
   TFile f_positrons("positrons.root");
   TFile f_ups3s_cont("ups3s_cont.root");
   TFile f_ups3s_peak("ups3s_peak.root");

   gStyle->SetOptStat(0);

   // Assuming a 1/s background, Y(3s) cont/total fraction is 0.4586 +/- 0.0010.
   double data_scale(1.0);
   double cont_scale(0.4586);
   double gam_scale(0.05);
   double sb_scale(0.05);
   double peak_scale(1. - cont_scale - gam_scale - sb_scale);

   TH1F* data = ((TH1F*) ((TDirectory*) f_ups3s_peak.Get("HADRONFILTERPROC"))->Get(hist));
   TH1F* peak_mc = ((TH1F*) ((TDirectory*) f_monte_carlo.Get("HADRONFILTERPROC"))->Get(hist));
   TH1F* cont_mc = ((TH1F*) ((TDirectory*) f_cont_fl_mc.Get("HADRONFILTERPROC"))->Get(hist));
   cont_mc->Add( ((TH1F*) ((TDirectory*) f_cont_mn_mc.Get("HADRONFILTERPROC"))->Get(hist)) );
   TH1F* gam_mc = ((TH1F*) ((TDirectory*) f_gamgam.Get("HADRONFILTERPROC"))->Get(hist));
   TH1F* e_sb = ((TH1F*) ((TDirectory*) f_electrons.Get("HADRONFILTERPROC"))->Get(hist));
   TH1F* p_sb = ((TH1F*) ((TDirectory*) f_positrons.Get("HADRONFILTERPROC"))->Get(hist));

   data->Sumw2();
   peak_mc->Sumw2();
   cont_mc->Sumw2();
   gam_mc->Sumw2();
   e_sb->Sumw2();
   p_sb->Sumw2();

   data->Scale(data_scale/data->GetEntries());
   peak_mc->Scale(peak_scale/peak_mc->GetEntries());
   cont_mc->Scale(cont_scale/cont_mc->GetEntries());
   gam_mc->Scale(gam_scale/gam_mc->GetEntries());
   e_sb->Scale(sb_scale/(e_sb->GetEntries() + p_sb->GetEntries()));
   p_sb->Scale(sb_scale/(e_sb->GetEntries() + p_sb->GetEntries()));

   data->DrawCopy("E");

   p_sb->Add(e_sb);
   gam_mc->Add(p_sb);
   cont_mc->Add(gam_mc);
   peak_mc->Add(cont_mc);

   peak_mc->SetFillColor(0);  peak_mc->Draw("samehist");
   cont_mc->SetFillColor(5);  cont_mc->Draw("samehist");
   gam_mc->SetFillColor(3);   gam_mc->Draw("samehist");
   p_sb->SetFillColor(2);     p_sb->Draw("samehist");
   e_sb->SetFillColor(4);     e_sb->Draw("samehist");

   TLegend* leg = new TLegend(0.63, 0.6, 0.97, 0.97);
   data->SetMarkerStyle(2);
   leg->AddEntry(data, "#Upsilon(3S) Data", "p");
   leg->AddEntry(peak_mc, "#Upsilon(3S) Monte Carlo", "f");
   leg->AddEntry(cont_mc, "#Upsilon(3S) Continuum Monte Carlo", "f");
   leg->AddEntry(gam_mc, "Two-photon Monte Carlo", "f");
   leg->AddEntry(p_sb, "Positron Single-Beam Data", "f");
   leg->AddEntry(e_sb, "Electron Single-Beam Data", "f");
   leg->SetTextSizePixels(12);
   leg->Draw();
}


