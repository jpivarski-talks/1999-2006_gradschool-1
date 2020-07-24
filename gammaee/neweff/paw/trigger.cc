void trigger()
{
   TCanvas can;
   gStyle->SetOptStat(kFALSE);

// Incorporate _2.root files
   TFile eg1file("../rzn/egY1trig.root");
   TFile eg2file("../rzn/egY2trig.root");
   TFile eg3file("../rzn/egY3trig.root");
   TFile qq1file("../rzn/qqY1trig.root");
   TFile qq2file("../rzn/qqY2trig.root");
   TFile qq3file("../rzn/qqY3trig.root");

   TFile peak1file("../rzn/trig123864.root");
   TFile peak2file("../rzn/trig129564.root");
   TFile peak3file("../rzn/trig122079.root");
   TFile cont1file("../rzn/trig123570.root");
   TFile cont2file("../rzn/trig127680.root");
   TFile cont3file("../rzn/trig122081.root");

   TNtuple *eg1 = eg1file->Get("Cuts/nt2");
   TNtuple *eg2 = eg2file->Get("Cuts/nt2");
   TNtuple *eg3 = eg3file->Get("Cuts/nt2");
   TNtuple *qq1 = qq1file->Get("Cuts/nt2");
   TNtuple *qq2 = qq2file->Get("Cuts/nt2");
   TNtuple *qq3 = qq3file->Get("Cuts/nt2");

   TNtuple *peak1 = peak1file->Get("CUTS/h2");
   TNtuple *peak2 = peak2file->Get("CUTS/h2");
   TNtuple *peak3 = peak3file->Get("CUTS/h2");
   TNtuple *cont1 = cont1file->Get("CUTS/h2");
   TNtuple *cont2 = cont2file->Get("CUTS/h2");
   TNtuple *cont3 = cont3file->Get("CUTS/h2");

// These are what you multiply to the CONTINUUM to make it
// subtractable from the PEAK.
   Double_t ptoc1 = (
      double(peak1->Draw("t1_trst", "(0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.9998)")) /
      double(cont1->Draw("t1_trst", "(0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.9998)"))
      );
   Double_t ptoc2 = (
      double(peak2->Draw("t1_trst", "(0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.9998)")) /
      double(cont2->Draw("t1_trst", "(0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.9998)"))
      );
   Double_t ptoc3 = (
      double(peak3->Draw("t1_trst", "(0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.9998)")) /
      double(cont3->Draw("t1_trst", "(0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.9998)"))
      );
// From official luminosities.  But the jobs didn't finish!
//    Double_t ptoc1 = 2266.2/1691.5;
//    Double_t ptoc2 = 2711.4/2295.1;
//    Double_t ptoc3 = 1962.3/1714.4;

   TH1D *eg1_trax_cut = new TH1D("eg1_trax_cut", "#Upsilon(1S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *eg2_trax_cut = new TH1D("eg2_trax_cut", "#Upsilon(2S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *eg3_trax_cut = new TH1D("eg3_trax_cut", "#Upsilon(3S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *qq1_trax_cut = new TH1D("qq1_trax_cut", "#Upsilon(1S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *qq2_trax_cut = new TH1D("qq2_trax_cut", "#Upsilon(2S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *qq3_trax_cut = new TH1D("qq3_trax_cut", "#Upsilon(3S) Axial Tracks", 16, -0.5, 15.5);

   TH1D *eg1_trst_cut = new TH1D("eg1_trst_cut", "#Upsilon(1S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *eg2_trst_cut = new TH1D("eg2_trst_cut", "#Upsilon(2S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *eg3_trst_cut = new TH1D("eg3_trst_cut", "#Upsilon(3S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *qq1_trst_cut = new TH1D("qq1_trst_cut", "#Upsilon(1S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *qq2_trst_cut = new TH1D("qq2_trst_cut", "#Upsilon(2S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *qq3_trst_cut = new TH1D("qq3_trst_cut", "#Upsilon(3S) Stereo Tracks", 16, -0.5, 15.5);

   TH1D *eg1_cblo_cut = new TH1D("eg1_cblo_cut", "#Upsilon(1S) CB Low", 8, -0.5, 7.5);
   TH1D *eg2_cblo_cut = new TH1D("eg2_cblo_cut", "#Upsilon(2S) CB Low", 8, -0.5, 7.5);
   TH1D *eg3_cblo_cut = new TH1D("eg3_cblo_cut", "#Upsilon(3S) CB Low", 8, -0.5, 7.5);
   TH1D *qq1_cblo_cut = new TH1D("qq1_cblo_cut", "#Upsilon(1S) CB Low", 8, -0.5, 7.5);
   TH1D *qq2_cblo_cut = new TH1D("qq2_cblo_cut", "#Upsilon(2S) CB Low", 8, -0.5, 7.5);
   TH1D *qq3_cblo_cut = new TH1D("qq3_cblo_cut", "#Upsilon(3S) CB Low", 8, -0.5, 7.5);

   TH1D *eg1_cbmd_cut = new TH1D("eg1_cbmd_cut", "#Upsilon(1S) CB Medium", 8, -0.5, 7.5);
   TH1D *eg2_cbmd_cut = new TH1D("eg2_cbmd_cut", "#Upsilon(2S) CB Medium", 8, -0.5, 7.5);
   TH1D *eg3_cbmd_cut = new TH1D("eg3_cbmd_cut", "#Upsilon(3S) CB Medium", 8, -0.5, 7.5);
   TH1D *qq1_cbmd_cut = new TH1D("qq1_cbmd_cut", "#Upsilon(1S) CB Medium", 8, -0.5, 7.5);
   TH1D *qq2_cbmd_cut = new TH1D("qq2_cbmd_cut", "#Upsilon(2S) CB Medium", 8, -0.5, 7.5);
   TH1D *qq3_cbmd_cut = new TH1D("qq3_cbmd_cut", "#Upsilon(3S) CB Medium", 8, -0.5, 7.5);

   eg1->Project("eg1_trax_cut", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg2->Project("eg2_trax_cut", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg3->Project("eg3_trax_cut", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq1->Project("qq1_trax_cut", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq2->Project("qq2_trax_cut", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq3->Project("qq3_trax_cut", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");

   eg1->Project("eg1_trst_cut", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg2->Project("eg2_trst_cut", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg3->Project("eg3_trst_cut", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq1->Project("qq1_trst_cut", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq2->Project("qq2_trst_cut", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq3->Project("qq3_trst_cut", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");

   eg1->Project("eg1_cblo_cut", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg2->Project("eg2_cblo_cut", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg3->Project("eg3_cblo_cut", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq1->Project("qq1_cblo_cut", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq2->Project("qq2_cblo_cut", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq3->Project("qq3_cblo_cut", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");

   eg1->Project("eg1_cbmd_cut", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg2->Project("eg2_cbmd_cut", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   eg3->Project("eg3_cbmd_cut", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq1->Project("qq1_cbmd_cut", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq2->Project("qq2_cbmd_cut", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");
   qq3->Project("qq3_cbmd_cut", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntracks==0)");

   Double_t eg1_entries = eg1_cblo_cut->GetEntries();
   Double_t eg2_entries = eg2_cblo_cut->GetEntries();
   Double_t eg3_entries = eg3_cblo_cut->GetEntries();
   Double_t qq1_entries = qq1_cblo_cut->GetEntries();
   Double_t qq2_entries = qq2_cblo_cut->GetEntries();
   Double_t qq3_entries = qq3_cblo_cut->GetEntries();

   eg1_trax_cut->Sumw2();
   eg2_trax_cut->Sumw2();
   eg3_trax_cut->Sumw2();
   qq1_trax_cut->Sumw2();
   qq2_trax_cut->Sumw2();
   qq3_trax_cut->Sumw2();

   eg1_trst_cut->Sumw2();
   eg2_trst_cut->Sumw2();
   eg3_trst_cut->Sumw2();
   qq1_trst_cut->Sumw2();
   qq2_trst_cut->Sumw2();
   qq3_trst_cut->Sumw2();

   eg1_cblo_cut->Sumw2();
   eg2_cblo_cut->Sumw2();
   eg3_cblo_cut->Sumw2();
   qq1_cblo_cut->Sumw2();
   qq2_cblo_cut->Sumw2();
   qq3_cblo_cut->Sumw2();

   eg1_cbmd_cut->Sumw2();
   eg2_cbmd_cut->Sumw2();
   eg3_cbmd_cut->Sumw2();
   qq1_cbmd_cut->Sumw2();
   qq2_cbmd_cut->Sumw2();
   qq3_cbmd_cut->Sumw2();

   eg1_trax_cut->Scale(1./eg1_entries);
   eg2_trax_cut->Scale(1./eg2_entries);
   eg3_trax_cut->Scale(1./eg3_entries);
   qq1_trax_cut->Scale(1./qq1_entries);
   qq2_trax_cut->Scale(1./qq2_entries);
   qq3_trax_cut->Scale(1./qq3_entries);

   eg1_trst_cut->Scale(1./eg1_entries);
   eg2_trst_cut->Scale(1./eg2_entries);
   eg3_trst_cut->Scale(1./eg3_entries);
   qq1_trst_cut->Scale(1./qq1_entries);
   qq2_trst_cut->Scale(1./qq2_entries);
   qq3_trst_cut->Scale(1./qq3_entries);

   eg1_cblo_cut->Scale(1./eg1_entries);
   eg2_cblo_cut->Scale(1./eg2_entries);
   eg3_cblo_cut->Scale(1./eg3_entries);
   qq1_cblo_cut->Scale(1./qq1_entries);
   qq2_cblo_cut->Scale(1./qq2_entries);
   qq3_cblo_cut->Scale(1./qq3_entries);

   eg1_cbmd_cut->Scale(1./eg1_entries);
   eg2_cbmd_cut->Scale(1./eg2_entries);
   eg3_cbmd_cut->Scale(1./eg3_entries);
   qq1_cbmd_cut->Scale(1./qq1_entries);
   qq2_cbmd_cut->Scale(1./qq2_entries);
   qq3_cbmd_cut->Scale(1./qq3_entries);

   eg1_trax_cut->SetLineColor(kRed);
   eg2_trax_cut->SetLineColor(kRed);
   eg3_trax_cut->SetLineColor(kRed);
   qq1_trax_cut->SetLineColor(kBlue);
   qq2_trax_cut->SetLineColor(kBlue);
   qq3_trax_cut->SetLineColor(kBlue);

   eg1_trst_cut->SetLineColor(kRed);
   eg2_trst_cut->SetLineColor(kRed);
   eg3_trst_cut->SetLineColor(kRed);
   qq1_trst_cut->SetLineColor(kBlue);
   qq2_trst_cut->SetLineColor(kBlue);
   qq3_trst_cut->SetLineColor(kBlue);

   eg1_cblo_cut->SetLineColor(kRed);
   eg2_cblo_cut->SetLineColor(kRed);
   eg3_cblo_cut->SetLineColor(kRed);
   qq1_cblo_cut->SetLineColor(kBlue);
   qq2_cblo_cut->SetLineColor(kBlue);
   qq3_cblo_cut->SetLineColor(kBlue);

   eg1_cbmd_cut->SetLineColor(kRed);
   eg2_cbmd_cut->SetLineColor(kRed);
   eg3_cbmd_cut->SetLineColor(kRed);
   qq1_cbmd_cut->SetLineColor(kBlue);
   qq2_cbmd_cut->SetLineColor(kBlue);
   qq3_cbmd_cut->SetLineColor(kBlue);

   TH1D *eg1_trax = new TH1D("eg1_trax", "#Upsilon(1S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *eg2_trax = new TH1D("eg2_trax", "#Upsilon(2S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *eg3_trax = new TH1D("eg3_trax", "#Upsilon(3S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *qq1_trax = new TH1D("qq1_trax", "#Upsilon(1S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *qq2_trax = new TH1D("qq2_trax", "#Upsilon(2S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *qq3_trax = new TH1D("qq3_trax", "#Upsilon(3S) Axial Tracks", 16, -0.5, 15.5);

   TH1D *eg1_trst = new TH1D("eg1_trst", "#Upsilon(1S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *eg2_trst = new TH1D("eg2_trst", "#Upsilon(2S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *eg3_trst = new TH1D("eg3_trst", "#Upsilon(3S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *qq1_trst = new TH1D("qq1_trst", "#Upsilon(1S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *qq2_trst = new TH1D("qq2_trst", "#Upsilon(2S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *qq3_trst = new TH1D("qq3_trst", "#Upsilon(3S) Stereo Tracks", 16, -0.5, 15.5);

   TH1D *eg1_cblo = new TH1D("eg1_cblo", "#Upsilon(1S) CB Low", 8, -0.5, 7.5);
   TH1D *eg2_cblo = new TH1D("eg2_cblo", "#Upsilon(2S) CB Low", 8, -0.5, 7.5);
   TH1D *eg3_cblo = new TH1D("eg3_cblo", "#Upsilon(3S) CB Low", 8, -0.5, 7.5);
   TH1D *qq1_cblo = new TH1D("qq1_cblo", "#Upsilon(1S) CB Low", 8, -0.5, 7.5);
   TH1D *qq2_cblo = new TH1D("qq2_cblo", "#Upsilon(2S) CB Low", 8, -0.5, 7.5);
   TH1D *qq3_cblo = new TH1D("qq3_cblo", "#Upsilon(3S) CB Low", 8, -0.5, 7.5);

   TH1D *eg1_cbmd = new TH1D("eg1_cbmd", "#Upsilon(1S) CB Medium", 8, -0.5, 7.5);
   TH1D *eg2_cbmd = new TH1D("eg2_cbmd", "#Upsilon(2S) CB Medium", 8, -0.5, 7.5);
   TH1D *eg3_cbmd = new TH1D("eg3_cbmd", "#Upsilon(3S) CB Medium", 8, -0.5, 7.5);
   TH1D *qq1_cbmd = new TH1D("qq1_cbmd", "#Upsilon(1S) CB Medium", 8, -0.5, 7.5);
   TH1D *qq2_cbmd = new TH1D("qq2_cbmd", "#Upsilon(2S) CB Medium", 8, -0.5, 7.5);
   TH1D *qq3_cbmd = new TH1D("qq3_cbmd", "#Upsilon(3S) CB Medium", 8, -0.5, 7.5);

   eg1->Project("eg1_trax", "t1_trax", "t1had>-1");
   eg2->Project("eg2_trax", "t1_trax", "t1had>-1");
   eg3->Project("eg3_trax", "t1_trax", "t1had>-1");
   qq1->Project("qq1_trax", "t1_trax", "t1had>-1");
   qq2->Project("qq2_trax", "t1_trax", "t1had>-1");
   qq3->Project("qq3_trax", "t1_trax", "t1had>-1");

   eg1->Project("eg1_trst", "t1_trst", "t1had>-1");
   eg2->Project("eg2_trst", "t1_trst", "t1had>-1");
   eg3->Project("eg3_trst", "t1_trst", "t1had>-1");
   qq1->Project("qq1_trst", "t1_trst", "t1had>-1");
   qq2->Project("qq2_trst", "t1_trst", "t1had>-1");
   qq3->Project("qq3_trst", "t1_trst", "t1had>-1");

   eg1->Project("eg1_cblo", "t1_cblo", "t1had>-1");
   eg2->Project("eg2_cblo", "t1_cblo", "t1had>-1");
   eg3->Project("eg3_cblo", "t1_cblo", "t1had>-1");
   qq1->Project("qq1_cblo", "t1_cblo", "t1had>-1");
   qq2->Project("qq2_cblo", "t1_cblo", "t1had>-1");
   qq3->Project("qq3_cblo", "t1_cblo", "t1had>-1");

   eg1->Project("eg1_cbmd", "t1_cbmd", "t1had>-1");
   eg2->Project("eg2_cbmd", "t1_cbmd", "t1had>-1");
   eg3->Project("eg3_cbmd", "t1_cbmd", "t1had>-1");
   qq1->Project("qq1_cbmd", "t1_cbmd", "t1had>-1");
   qq2->Project("qq2_cbmd", "t1_cbmd", "t1had>-1");
   qq3->Project("qq3_cbmd", "t1_cbmd", "t1had>-1");

   eg1_trax->Sumw2();
   eg2_trax->Sumw2();
   eg3_trax->Sumw2();
   qq1_trax->Sumw2();
   qq2_trax->Sumw2();
   qq3_trax->Sumw2();

   eg1_trst->Sumw2();
   eg2_trst->Sumw2();
   eg3_trst->Sumw2();
   qq1_trst->Sumw2();
   qq2_trst->Sumw2();
   qq3_trst->Sumw2();

   eg1_cblo->Sumw2();
   eg2_cblo->Sumw2();
   eg3_cblo->Sumw2();
   qq1_cblo->Sumw2();
   qq2_cblo->Sumw2();
   qq3_cblo->Sumw2();

   eg1_cbmd->Sumw2();
   eg2_cbmd->Sumw2();
   eg3_cbmd->Sumw2();
   qq1_cbmd->Sumw2();
   qq2_cbmd->Sumw2();
   qq3_cbmd->Sumw2();

   eg1_trax->Scale(1./eg1_entries);
   eg2_trax->Scale(1./eg2_entries);
   eg3_trax->Scale(1./eg3_entries);
   qq1_trax->Scale(1./qq1_entries);
   qq2_trax->Scale(1./qq2_entries);
   qq3_trax->Scale(1./qq3_entries);

   eg1_trst->Scale(1./eg1_entries);
   eg2_trst->Scale(1./eg2_entries);
   eg3_trst->Scale(1./eg3_entries);
   qq1_trst->Scale(1./qq1_entries);
   qq2_trst->Scale(1./qq2_entries);
   qq3_trst->Scale(1./qq3_entries);

   eg1_cblo->Scale(1./eg1_entries);
   eg2_cblo->Scale(1./eg2_entries);
   eg3_cblo->Scale(1./eg3_entries);
   qq1_cblo->Scale(1./qq1_entries);
   qq2_cblo->Scale(1./qq2_entries);
   qq3_cblo->Scale(1./qq3_entries);

   eg1_cbmd->Scale(1./eg1_entries);
   eg2_cbmd->Scale(1./eg2_entries);
   eg3_cbmd->Scale(1./eg3_entries);
   qq1_cbmd->Scale(1./qq1_entries);
   qq2_cbmd->Scale(1./qq2_entries);
   qq3_cbmd->Scale(1./qq3_entries);

   eg1_trax->SetLineColor(kRed);
   eg2_trax->SetLineColor(kRed);
   eg3_trax->SetLineColor(kRed);
   qq1_trax->SetLineColor(kBlue);
   qq2_trax->SetLineColor(kBlue);
   qq3_trax->SetLineColor(kBlue);

   eg1_trst->SetLineColor(kRed);
   eg2_trst->SetLineColor(kRed);
   eg3_trst->SetLineColor(kRed);
   qq1_trst->SetLineColor(kBlue);
   qq2_trst->SetLineColor(kBlue);
   qq3_trst->SetLineColor(kBlue);

   eg1_cblo->SetLineColor(kRed);
   eg2_cblo->SetLineColor(kRed);
   eg3_cblo->SetLineColor(kRed);
   qq1_cblo->SetLineColor(kBlue);
   qq2_cblo->SetLineColor(kBlue);
   qq3_cblo->SetLineColor(kBlue);

   eg1_cbmd->SetLineColor(kRed);
   eg2_cbmd->SetLineColor(kRed);
   eg3_cbmd->SetLineColor(kRed);
   qq1_cbmd->SetLineColor(kBlue);
   qq2_cbmd->SetLineColor(kBlue);
   qq3_cbmd->SetLineColor(kBlue);

   TH1D *peak1_trax = new TH1D("peak1_trax", "#Upsilon(1S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *peak2_trax = new TH1D("peak2_trax", "#Upsilon(2S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *peak3_trax = new TH1D("peak3_trax", "#Upsilon(3S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *cont1_trax = new TH1D("cont1_trax", "#Upsilon(1S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *cont2_trax = new TH1D("cont2_trax", "#Upsilon(2S) Axial Tracks", 16, -0.5, 15.5);
   TH1D *cont3_trax = new TH1D("cont3_trax", "#Upsilon(3S) Axial Tracks", 16, -0.5, 15.5);

   TH1D *peak1_trst = new TH1D("peak1_trst", "#Upsilon(1S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *peak2_trst = new TH1D("peak2_trst", "#Upsilon(2S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *peak3_trst = new TH1D("peak3_trst", "#Upsilon(3S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *cont1_trst = new TH1D("cont1_trst", "#Upsilon(1S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *cont2_trst = new TH1D("cont2_trst", "#Upsilon(2S) Stereo Tracks", 16, -0.5, 15.5);
   TH1D *cont3_trst = new TH1D("cont3_trst", "#Upsilon(3S) Stereo Tracks", 16, -0.5, 15.5);

   TH1D *peak1_cblo = new TH1D("peak1_cblo", "#Upsilon(1S) CB Low", 8, -0.5, 7.5);
   TH1D *peak2_cblo = new TH1D("peak2_cblo", "#Upsilon(2S) CB Low", 8, -0.5, 7.5);
   TH1D *peak3_cblo = new TH1D("peak3_cblo", "#Upsilon(3S) CB Low", 8, -0.5, 7.5);
   TH1D *cont1_cblo = new TH1D("cont1_cblo", "#Upsilon(1S) CB Low", 8, -0.5, 7.5);
   TH1D *cont2_cblo = new TH1D("cont2_cblo", "#Upsilon(2S) CB Low", 8, -0.5, 7.5);
   TH1D *cont3_cblo = new TH1D("cont3_cblo", "#Upsilon(3S) CB Low", 8, -0.5, 7.5);

   TH1D *peak1_cbmd = new TH1D("peak1_cbmd", "#Upsilon(1S) CB Medium", 8, -0.5, 7.5);
   TH1D *peak2_cbmd = new TH1D("peak2_cbmd", "#Upsilon(2S) CB Medium", 8, -0.5, 7.5);
   TH1D *peak3_cbmd = new TH1D("peak3_cbmd", "#Upsilon(3S) CB Medium", 8, -0.5, 7.5);
   TH1D *cont1_cbmd = new TH1D("cont1_cbmd", "#Upsilon(1S) CB Medium", 8, -0.5, 7.5);
   TH1D *cont2_cbmd = new TH1D("cont2_cbmd", "#Upsilon(2S) CB Medium", 8, -0.5, 7.5);
   TH1D *cont3_cbmd = new TH1D("cont3_cbmd", "#Upsilon(3S) CB Medium", 8, -0.5, 7.5);

   peak1->Project("peak1_trax", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak2->Project("peak2_trax", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak3->Project("peak3_trax", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont1->Project("cont1_trax", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont2->Project("cont2_trax", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont3->Project("cont3_trax", "t1_trax", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");

   peak1->Project("peak1_trst", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak2->Project("peak2_trst", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak3->Project("peak3_trst", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont1->Project("cont1_trst", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont2->Project("cont2_trst", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont3->Project("cont3_trst", "t1_trst", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");

   peak1->Project("peak1_cblo", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak2->Project("peak2_cblo", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak3->Project("peak3_cblo", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont1->Project("cont1_cblo", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont2->Project("cont2_cblo", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont3->Project("cont3_cblo", "t1_cblo", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");

   peak1->Project("peak1_cbmd", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak2->Project("peak2_cbmd", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   peak3->Project("peak3_cbmd", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont1->Project("cont1_cbmd", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont2->Project("cont2_cbmd", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");
   cont3->Project("cont3_cbmd", "t1_cbmd", "(t1had>0||t1tau>0||t1el>0)&&((abs(d0close)<0.001&&abs(z0close)<0.04)||rawntrac==0)&&!((0.9<abs(e1)<1.1&&0.9<abs(e2)<1.1&&shxy+shz<-0.98)||(0.9<abs(p1)<1.1&&0.9<abs(p2)<1.1&&trxy+trz<-0.99))");

   peak1_trax->Sumw2();
   peak2_trax->Sumw2();
   peak3_trax->Sumw2();
   cont1_trax->Sumw2();
   cont2_trax->Sumw2();
   cont3_trax->Sumw2();

   peak1_trst->Sumw2();
   peak2_trst->Sumw2();
   peak3_trst->Sumw2();
   cont1_trst->Sumw2();
   cont2_trst->Sumw2();
   cont3_trst->Sumw2();

   peak1_cblo->Sumw2();
   peak2_cblo->Sumw2();
   peak3_cblo->Sumw2();
   cont1_cblo->Sumw2();
   cont2_cblo->Sumw2();
   cont3_cblo->Sumw2();

   peak1_cbmd->Sumw2();
   peak2_cbmd->Sumw2();
   peak3_cbmd->Sumw2();
   cont1_cbmd->Sumw2();
   cont2_cbmd->Sumw2();
   cont3_cbmd->Sumw2();

   peak1_trax->Add(cont1_trax, -ptoc1);
   peak2_trax->Add(cont2_trax, -ptoc2);
   peak3_trax->Add(cont3_trax, -ptoc3);

   peak1_trst->Add(cont1_trst, -ptoc1);
   peak2_trst->Add(cont2_trst, -ptoc2);
   peak3_trst->Add(cont3_trst, -ptoc3);

   peak1_cblo->Add(cont1_cblo, -ptoc1);
   peak2_cblo->Add(cont2_cblo, -ptoc2);
   peak3_cblo->Add(cont3_cblo, -ptoc3);

   peak1_cbmd->Add(cont1_cbmd, -ptoc1);
   peak2_cbmd->Add(cont2_cbmd, -ptoc2);
   peak3_cbmd->Add(cont3_cbmd, -ptoc3);

   Double_t peak1_entries = peak1_cblo->Integral();
   Double_t peak2_entries = peak2_cblo->Integral();
   Double_t peak3_entries = peak3_cblo->Integral();

   peak1_trax->Scale(1./peak1_entries);
   peak2_trax->Scale(1./peak2_entries);
   peak3_trax->Scale(1./peak3_entries);

   peak1_trst->Scale(1./peak1_entries);
   peak2_trst->Scale(1./peak2_entries);
   peak3_trst->Scale(1./peak3_entries);

   peak1_cblo->Scale(1./peak1_entries);
   peak2_cblo->Scale(1./peak2_entries);
   peak3_cblo->Scale(1./peak3_entries);

   peak1_cbmd->Scale(1./peak1_entries);
   peak2_cbmd->Scale(1./peak2_entries);
   peak3_cbmd->Scale(1./peak3_entries);

   peak1_trax->Draw("e1");
   eg1_trax->Draw("same");
   eg1_trax_cut->Draw("same");
   qq1_trax->Draw("same");
   qq1_trax_cut->Draw("same");
   can->Print("trigger1_trax.eps");
   
   peak1_trst->Draw("e1");
   eg1_trst->Draw("same");
   eg1_trst_cut->Draw("same");
   qq1_trst->Draw("same");
   qq1_trst_cut->Draw("same");
   can->Print("trigger1_trst.eps");

   peak1_cblo->Draw("e1");
   eg1_cblo->Draw("same");
   eg1_cblo_cut->Draw("same");
   qq1_cblo->Draw("same");
   qq1_cblo_cut->Draw("same");
   can->Print("trigger1_cblo.eps");

   peak1_cbmd->Draw("e1");
   eg1_cbmd->Draw("same");
   eg1_cbmd_cut->Draw("same");
   qq1_cbmd->Draw("same");
   qq1_cbmd_cut->Draw("same");
   can->Print("trigger1_cbmd.eps");

   peak2_trax->Draw("e1");
   eg2_trax->Draw("same");
   eg2_trax_cut->Draw("same");
   qq2_trax->Draw("same");
   qq2_trax_cut->Draw("same");
   can->Print("trigger2_trax.eps");
   
   peak2_trst->Draw("e1");
   eg2_trst->Draw("same");
   eg2_trst_cut->Draw("same");
   qq2_trst->Draw("same");
   qq2_trst_cut->Draw("same");
   can->Print("trigger2_trst.eps");

   peak2_cblo->Draw("e1");
   eg2_cblo->Draw("same");
   eg2_cblo_cut->Draw("same");
   qq2_cblo->Draw("same");
   qq2_cblo_cut->Draw("same");
   can->Print("trigger2_cblo.eps");

   peak2_cbmd->Draw("e1");
   eg2_cbmd->Draw("same");
   eg2_cbmd_cut->Draw("same");
   qq2_cbmd->Draw("same");
   qq2_cbmd_cut->Draw("same");
   can->Print("trigger2_cbmd.eps");

   peak3_trax->Draw("e1");
   eg3_trax->Draw("same");
   eg3_trax_cut->Draw("same");
   qq3_trax->Draw("same");
   qq3_trax_cut->Draw("same");
   can->Print("trigger3_trax.eps");
   
   peak3_trst->Draw("e1");
   eg3_trst->Draw("same");
   eg3_trst_cut->Draw("same");
   qq3_trst->Draw("same");
   qq3_trst_cut->Draw("same");
   can->Print("trigger3_trst.eps");

   peak3_cblo->Draw("e1");
   eg3_cblo->Draw("same");
   eg3_cblo_cut->Draw("same");
   qq3_cblo->Draw("same");
   qq3_cblo_cut->Draw("same");
   can->Print("trigger3_cblo.eps");

   peak3_cbmd->Draw("e1");
   eg3_cbmd->Draw("same");
   eg3_cbmd_cut->Draw("same");
   qq3_cbmd->Draw("same");
   qq3_cbmd_cut->Draw("same");
   can->Print("trigger3_cbmd.eps");

}
