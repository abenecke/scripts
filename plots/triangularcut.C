#include "TH2F.h"


void triangularcut() {
  gStyle->SetOptStat(0);

  // open a file and get a histogram
  TFile *s = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/elec_channel_30GeV/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime1200T_TPrimeToHT.root");
  TFile *q = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/elec_channel_30GeV/uhh2.AnalysisModuleRunner.MC.QCD.root");
 
  TH2F *Signal    = (TH2F*)s->Get("eff_twodcut/met_VS_dphi_lep1");
  TH2F *QCD      = (TH2F*)q->Get("eff_twodcut/met_VS_dphi_lep1");
  TH2F *QCD2      = (TH2F*)q->Get("eff_triangcut/met_VS_dphi_lep1"); 

  TH2F *Signal_jet    = (TH2F*)s->Get("eff_twodcut/met_VS_dphi_jet1");
  TH2F *QCD_jet      = (TH2F*)q->Get("eff_twodcut/met_VS_dphi_jet1"); 
  TH2F *QCD_jet2      = (TH2F*)q->Get("eff_triangcut/met_VS_dphi_jet1"); 

  TH2F *Signal_2jet    = (TH2F*)s->Get("eff_twodcut/met_VS_dphi_jet2");
  TH2F *QCD_2jet      = (TH2F*)q->Get("eff_twodcut/met_VS_dphi_jet2"); 
  TH2F *QCD_2jet2      = (TH2F*)q->Get("eff_triangcut/met_VS_dphi_jet2"); 

  TH2F *Signal_3jet    = (TH2F*)s->Get("eff_twodcut/met_VS_dphi_jet3");
  TH2F *QCD_3jet      = (TH2F*)q->Get("eff_twodcut/met_VS_dphi_jet3"); 
  TH2F *QCD_3jet2      = (TH2F*)q->Get("eff_triangcut/met_VS_dphi_jet3"); 

  //  Signal->Draw("colz");

  TLine *line1 = new TLine(0,0,1800,1584);
  line1->SetLineWidth(2);
  TLine *line2 = new TLine(0,0,1800,1584);
  line2->SetLineWidth(2);

  Signal->SetMarkerStyle(2);
  QCD->SetMarkerStyle(2);
  QCD2->SetMarkerStyle(2);
  Signal->SetMarkerColor(kRed); 
  QCD->SetMarkerColor(kBlue);
  QCD2->SetMarkerColor(kBlack);
  Signal->Scale(1./(Signal->Integral()));
  QCD->Scale(1./(QCD->Integral()));
  QCD2->Scale(1./(QCD2->Integral()));

  TCanvas *c = new TCanvas("c","",10,10,700,900);
  Signal->GetXaxis()->SetRangeUser(0,300);
  Signal->Draw();
  Signal -> SetTitle("");
  Signal->GetXaxis()->SetTitle("p_{T} MET");
  Signal->GetYaxis()->SetTitle("#Delta Phi (ele,MET)");
  QCD->Draw("L same");
  QCD2->Draw("L same");
  // line1 ->Draw("L same");
  // line2->Draw("L same");

  TLegend *leg1;
  leg1 = new TLegend(0.6,0.4,0.98,0.6);//x+0.1
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.035);
  leg1->SetFillColor(10);
  leg1->SetLineColor(1);
  leg1->SetTextFont(42);
  leg1->SetFillStyle(0);

  // leg1->AddEntry(Signal, "MZ'= 2500GeV, MT'= 1200GeV","P");
  leg1->AddEntry(Signal, "Signal","P");
  leg1->AddEntry(QCD, "QCD","P");
  leg1->AddEntry(QCD2, "QCD after cut","P");

  // leg1->Draw();
  c->Print("triang_lep.eps");

  Signal_jet->SetMarkerStyle(2);
  QCD_jet->SetMarkerStyle(2);
  QCD_jet2->SetMarkerStyle(2);
  Signal_jet->SetMarkerColor(kRed); 
  QCD_jet->SetMarkerColor(kBlue);
  QCD_jet2->SetMarkerColor(kBlack);
  Signal_jet->Scale(1./(Signal_jet->Integral()));
  QCD_jet->Scale(1./(QCD_jet->Integral()));
  QCD_jet2->Scale(1./(QCD_jet2->Integral()));

  TCanvas *c2 = new TCanvas("c2","",10,10,700,900);
  Signal_jet->GetXaxis()->SetRangeUser(0,1000);
  Signal_jet->Draw();
  Signal_jet -> SetTitle("");
  Signal_jet->GetXaxis()->SetTitle("p_{T} MET");
  Signal_jet->GetYaxis()->SetTitle("#Delta Phi (jet,MET)");
  QCD_jet->Draw("L same");
  QCD_jet2->Draw("L same");
  // line1 ->Draw("L same");
  // line2->Draw("L same");

  TLegend *leg;
  leg = new TLegend(0.6,0.4,0.98,0.6);//x+0.1
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(10);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);

  // leg1->AddEntry(Signal, "MZ'= 2500GeV, MT'= 1200GeV","P");
  leg->AddEntry(Signal, "Signal","P");
  leg->AddEntry(QCD, "QCD","P");
  leg->AddEntry(QCD2, "QCD after cut","P");

  leg->Draw();
  c2->Print("triang_jet.eps");

  Signal_2jet->SetMarkerStyle(2);
  QCD_2jet->SetMarkerStyle(2);
  QCD_2jet2->SetMarkerStyle(2);
  Signal_2jet->SetMarkerColor(kRed); 
  QCD_2jet->SetMarkerColor(kBlue);
  QCD_2jet2->SetMarkerColor(kBlack);
  Signal_2jet->Scale(1./(Signal_2jet->Integral()));
  QCD_2jet->Scale(1./(QCD_2jet->Integral()));
  QCD_2jet2->Scale(1./(QCD_2jet2->Integral()));

  TCanvas *c3 = new TCanvas("c3","",10,10,700,900);
  Signal_2jet->GetXaxis()->SetRangeUser(0,300);
  Signal_2jet->Draw();
  Signal_2jet -> SetTitle("");
  Signal_2jet->GetXaxis()->SetTitle("p_{T} MET");
  Signal_2jet->GetYaxis()->SetTitle("#Delta Phi (2. jet,MET)");
  QCD_2jet->Draw("L same");
  QCD_2jet2->Draw("L same");
  // line1 ->Draw("L same");
  // line2->Draw("L same");


  leg = new TLegend(0.6,0.4,0.98,0.6);//x+0.1
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(10);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);

  // leg1->AddEntry(Signal, "MZ'= 2500GeV, MT'= 1200GeV","P");
  leg->AddEntry(Signal, "Signal","P");
  leg->AddEntry(QCD, "QCD","P");
  leg->AddEntry(QCD2, "QCD after cut","P");

  // leg->Draw();
  c3->Print("triang_2jet.eps");

  Signal_3jet->SetMarkerStyle(2);
  QCD_3jet->SetMarkerStyle(2);
  QCD_3jet2->SetMarkerStyle(2);
  Signal_3jet->SetMarkerColor(kRed); 
  QCD_3jet->SetMarkerColor(kBlue);
  QCD_3jet2->SetMarkerColor(kBlack);
  Signal_3jet->Scale(1./(Signal_3jet->Integral()));
  QCD_3jet->Scale(1./(QCD_3jet->Integral()));
  QCD_3jet2->Scale(1./(QCD_3jet2->Integral()));


  TCanvas *c4 = new TCanvas("c4","",10,10,700,900);
  Signal_3jet->GetXaxis()->SetRangeUser(0,300);
  Signal_3jet->Draw();
  Signal_3jet -> SetTitle("");
  Signal_3jet->GetXaxis()->SetTitle("p_{T} MET");
  Signal_3jet->GetYaxis()->SetTitle("#Delta Phi (3. jet,MET)");
  QCD_3jet->Draw("L same");
  QCD_3jet2->Draw("L same");
  // line1 ->Draw("L same");
  // line2->Draw("L same");

  leg = new TLegend(0.6,0.4,0.98,0.6);//x+0.1
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(10);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);

  // leg1->AddEntry(Signal, "MZ'= 2500GeV, MT'= 1200GeV","P");
  leg->AddEntry(Signal, "Signal","P");
  leg->AddEntry(QCD, "QCD","P");
  leg->AddEntry(QCD2, "QCD after cut","P");

  // leg->Draw();
  c4->Print("triang_3jet.eps");


}
