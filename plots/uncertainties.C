#include "TH1.h"
#include <fstream>
using namespace std;


void uncertainties(){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  
  //read in histograms
  TFile *file = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/uncertainties/sideband/muon/none/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2000ToTPrime1200T_TPrimeToHT.root", "READ");
  TFile *file_up = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/uncertainties/sideband/muon/pu_up/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2000ToTPrime1200T_TPrimeToHT.root", "READ");
  TFile *file_down = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/uncertainties/sideband/muon/pu_down/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2000ToTPrime1200T_TPrimeToHT.root", "READ");
  
  TString hname = "chi2min_chi2cut/M_ZPrime_rec";

  TH1F* hist = (TH1F*) file->Get(hname);
  TH1F* hist_up = (TH1F*) file_up->Get(hname);
  TH1F* hist_down = (TH1F*) file_down->Get(hname);

  hist->Rebin(4);
  hist_up->Rebin(4);
  hist_down->Rebin(4);

  TCanvas *c = new TCanvas("c","",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();

  hist->SetLineColor(kBlack);
  hist->SetMarkerColor(kBlack);
  hist->Draw("Hist");
  hist_up->SetLineColor(kRed);
  hist_up->SetMarkerColor(kRed);
  hist_up->Draw("Hist same");
  hist_down->SetLineColor(kBlue);
  hist_down->SetMarkerColor(kBlue);
  hist_down->Draw("Hist same");

  TLegend *leg = new TLegend(0.35,0.23,0.7,0.13, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(hist_up,"up","lpe");
  leg->AddEntry(hist,"nominal","lpe");
  leg->AddEntry(hist_down,"down","lpe");
  leg->Draw();

  c->Print("~/CMS_notes/notes/AN-17-103/trunk/material/uncertainties/pu.eps");

}
