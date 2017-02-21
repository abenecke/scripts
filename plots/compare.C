#include "TH1.h"
#include <fstream>

using namespace std;

void compare()
{
  //setOptFit( pcev (default = 0111)) Probability; Chisquare/Number of degrees of freedom; errors ;values of parameters 
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
 

  //All files are read in
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/eff/";
  TFile * Signal08_f = new TFile(directory+"uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * Background08_f = new TFile(directory+"uhh2.AnalysisModuleRunner.MC.background.root", "READ");
  TFile * Signal06_f = new TFile(directory+"match06/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * Background06_f = new TFile(directory+"match06/uhh2.AnalysisModuleRunner.MC.background.root", "READ");
  TFile * Signal04_f = new TFile(directory+"match04/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * Background04_f = new TFile(directory+"match04/uhh2.AnalysisModuleRunner.MC.background.root", "READ");
  TFile * Signal10_f = new TFile(directory+"match10/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * Background10_f = new TFile(directory+"match10/uhh2.AnalysisModuleRunner.MC.background.root", "READ");
  TFile * Signal12_f = new TFile(directory+"match12/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * Background12_f = new TFile(directory+"match12/uhh2.AnalysisModuleRunner.MC.background.root", "READ");
  TFile * Signal_chi2cut_f = new TFile(directory+"chi2cut30/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * Background_chi2cut_f = new TFile(directory+"chi2cut30/uhh2.AnalysisModuleRunner.MC.background.root", "READ");
  

  //Get all hist from the string hist_name
  TString hist_name = "tagger_chi2cut/reco_mass_W";
  TH1F* sig08 = (TH1F*)Signal08_f->Get(hist_name);
  TH1F* background08 = (TH1F*)Background08_f->Get(hist_name);
  TH1F* sig06 = (TH1F*)Signal06_f->Get(hist_name);
  TH1F* background06 = (TH1F*)Background06_f->Get(hist_name);
  TH1F* sig04 = (TH1F*)Signal04_f->Get(hist_name);
  TH1F* background04 = (TH1F*)Background04_f->Get(hist_name);
  TH1F* sig10 = (TH1F*)Signal10_f->Get(hist_name);
  TH1F* background10 = (TH1F*)Background10_f->Get(hist_name);
  TH1F* sig12 = (TH1F*)Signal12_f->Get(hist_name);
  TH1F* background12 = (TH1F*)Background12_f->Get(hist_name);
  TH1F* sig_chi2cut = (TH1F*)Signal_chi2cut_f->Get(hist_name);
  TH1F* background_chi2cut = (TH1F*)Background_chi2cut_f->Get(hist_name);


  // TString folder =directory +"compare/NJET_";
  // TString folder ="~/ownCloud/masterarbeit/Bilder/analyse/master_";
  TString folder ="~/ownCloud/masterarbeit/tex/plots/efficiency/master_";
  // -------------------
  //Background 
  // -------------------
  TCanvas *background_c = new TCanvas("background_c","background fit",10,10,900,1100);
  gPad->SetTickx();
  gPad->SetTicky();

  background_c->Clear();
  background_c->cd();

  background08->SetMarkerStyle(20);
  background08->SetMarkerSize(1.);
  background08->SetLineColor(kBlue+1);
  background08->SetMarkerColor(kBlue+1);
  background08->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  background08->SetYTitle("Events");
  background08->SetTitleSize(0.045);
  background08->GetYaxis()->SetTitleSize(0.045);
  background08->GetYaxis()->SetTitleOffset(1.1);
  background08->SetTitle("");


  background08->Draw("PZ");
  background06->SetLineColor(kRed);
  background06->SetLineWidth(3);
  background04->SetLineColor(kMagenta);
  background04->SetLineWidth(3);
  background10->SetLineColor(kBlack);
  background10->SetLineWidth(3);
  background12->SetLineColor(kGreen);
  background12->SetLineWidth(3);
  background_chi2cut->SetLineColor(kCyan);
  background_chi2cut->SetLineWidth(3);
  // background06->Draw("Hist SAME");
  background04->Draw("Hist SAME");
  // background10->Draw("Hist SAME");
  background12->Draw("Hist SAME");
  // background_chi2cut->Draw("Hist SAME");

  leg1 = new TLegend(0.6,0.7,0.89,0.89);
  leg1-> SetTextSize(0.05);
  leg1 -> AddEntry(background04,"#Delta R=0.4","l");
  leg1 -> AddEntry(background08,"#Delta R=0.8","p");
  //  leg1 -> AddEntry(background06,"matching 0.6","l");
  // leg1 -> AddEntry(background10,"matching 1.0","l");
  leg1 -> AddEntry(background12,"#Delta R=1.2","l");
  // leg1 -> AddEntry(background_chi2cut,"chi2cut 30","l");
  leg1->SetBorderSize(0);
  leg1->Draw("Same");

  background_c->Print(folder +"background.eps");

  // -------------------
  //Signal 
  // -------------------
  TCanvas *signal_c = new TCanvas("signal_c","signal fit",10,10,900,1100);
  gPad->SetTickx();
  gPad->SetTicky();

  signal_c->Clear();
  signal_c->cd();

  sig08->SetMarkerStyle(20);
  sig08->SetMarkerSize(1.);
  sig08->SetLineColor(kBlue+1);
  sig08->SetMarkerColor(kBlue+1);
  sig08->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  sig08->SetYTitle("Events");
  sig08->SetTitle("");
  sig08->SetTitleSize(0.045);
  sig08->GetYaxis()->SetTitleSize(0.045);
  // sig08->GetYaxis()->SetTitleOffset(1);

  sig08->Draw("PZ");
  sig06->SetLineColor(kRed);
  sig06->SetLineWidth(3);
  sig04->SetLineColor(kMagenta);
  sig04->SetLineWidth(3);
  sig10->SetLineColor(kBlack);
  sig10->SetLineWidth(3);
  sig12->SetLineColor(kGreen);
  sig12->SetLineWidth(3);
  sig_chi2cut->SetLineColor(kCyan);
  sig_chi2cut->SetLineWidth(3);
  // sig06->Draw("Hist SAME");
  sig04->Draw("Hist SAME");
  // sig10->Draw("Hist SAME");
  sig12->Draw("Hist SAME");
  // sig_chi2cut->Draw("Hist SAME");
 
  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg -> SetTextSize(0.05);
  leg -> AddEntry(background12,"#Delta R=1.2","l");
  leg -> AddEntry(sig08,"#Delta R=0.8","p");
  // leg -> AddEntry(sig06,"matching 0.6","l");
  leg -> AddEntry(background04,"#Delta R=0.4","l");
  // leg -> AddEntry(background10,"matching 1.0","l");
  // leg -> AddEntry(background_chi2cut,"chi2cut 30","l");
  leg->SetBorderSize(0);
  leg->Draw("Same");


  signal_c->Print(folder +"signal.eps");


 


}//End of function
