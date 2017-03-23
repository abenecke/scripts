#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"

using namespace std;

bool berror=false; 
TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/";
TString output_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/pictures/";
TString folder="tagger_priority";

#include "npv_eff_functions.cxx"
void npv_eff()
{
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kFALSE);

  TFile *Data_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.Data.Data.root", "READ");
  TFile *Signal_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime20001200HT.root", "READ");

  TH1F *nvp_nocuts_data = (TH1F*)Data_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_data = (TH1F*)Data_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_data = (TH1F*)Data_f ->Get("event_chi2cut/N_PrimVertices");

  TH1F *nvp_nocuts_signal = (TH1F*)Signal_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_signal = (TH1F*)Signal_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_signal = (TH1F*)Signal_f ->Get("event_chi2cut/N_PrimVertices");

  // TGraphAsymmErrors* eff_presel_data = new TGraphAsymmErrors( nvp_preselection_data, nvp_nocuts_data, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_sel_data = new TGraphAsymmErrors( nvp_selection_data, nvp_nocuts_data, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_tagged_data = new TGraphAsymmErrors( nvp_selection_data, nvp_preselection_data, "cl=0.683 b(1,1) mode" );

  // TGraphAsymmErrors* eff_presel_signal = new TGraphAsymmErrors( nvp_preselection_signal, nvp_nocuts_signal, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_sel_signal = new TGraphAsymmErrors( nvp_selection_signal, nvp_nocuts_signal, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_tagged_signal = new TGraphAsymmErrors( nvp_selection_signal, nvp_preselection_signal, "cl=0.683 b(1,1) mode" );

  folder="chsvspuppi";
  TFile *Data_puppi_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.Data.Data.root", "READ");
  TFile *Signal_puppi_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime20001200HT.root", "READ");

  TH1F *nvp_nocuts_data_puppi = (TH1F*)Data_puppi_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_data_puppi = (TH1F*)Data_puppi_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_data_puppi = (TH1F*)Data_puppi_f ->Get("event_chi2cut/N_PrimVertices");

  TH1F *nvp_nocuts_signal_puppi = (TH1F*)Signal_puppi_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_signal_puppi = (TH1F*)Signal_puppi_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_signal_puppi = (TH1F*)Signal_puppi_f ->Get("event_chi2cut/N_PrimVertices");
  nvp_preselection_signal_puppi->Rebin(2);
  nvp_selection_signal_puppi->Rebin(2);
  nvp_nocuts_signal_puppi->Rebin(2);
  // TGraphAsymmErrors* eff_presel_data_puppi = new TGraphAsymmErrors( nvp_preselection_data_puppi, nvp_nocuts_data_puppi, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_sel_data_puppi = new TGraphAsymmErrors( nvp_selection_data_puppi, nvp_nocuts_data_puppi, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_tagged_data_puppi = new TGraphAsymmErrors( nvp_selection_data_puppi, nvp_preselection_data_puppi, "cl=0.683 b(1,1) mode" );

  // TGraphAsymmErrors* eff_presel_signal_puppi = new TGraphAsymmErrors( nvp_preselection_signal_puppi, nvp_nocuts_signal_puppi, "cl=0.683 b(1,1) mode" );
  // TGraphAsymmErrors* eff_sel_signal_puppi = new TGraphAsymmErrors( nvp_selection_signal_puppi, nvp_nocuts_signal_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_signal_puppi = new TGraphAsymmErrors( nvp_selection_signal_puppi, nvp_preselection_signal_puppi, "cl=0.683 b(1,1) mode" );
  nvp_selection_signal_puppi->Draw("AP");
  nvp_preselection_signal_puppi->SetLineColor(kRed);
  nvp_preselection_signal_puppi->Draw("same");
  // std::vector<TGraphAsymmErrors*> hists={eff_presel_data,eff_presel_signal,eff_presel_data_puppi,eff_presel_signal_puppi};
  // plot_result( hists,  1, 0.001);


  // hists={eff_sel_data,eff_sel_signal,eff_sel_data_puppi,eff_sel_signal_puppi};
  // plot_result( hists,  1, 0.0001);

 
  // hists={eff_tagged_data,eff_tagged_signal,eff_tagged_data_puppi,eff_tagged_signal_puppi};
  // plot_result( hists,  1, 0.00000001);



}//end of void function

