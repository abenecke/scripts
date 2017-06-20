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
  //  TFile *Signal_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime20001200HT.root", "READ");
  TFile *Signal_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime700T_TPrimeToHT.root", "READ");
  TFile *Bkg_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.background.root", "READ");

  TH1F *nvp_nocuts_data = (TH1F*)Data_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_data = (TH1F*)Data_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_data = (TH1F*)Data_f ->Get("event_chi2cut/N_PrimVertices");

  TH1F *nvp_nocuts_signal = (TH1F*)Signal_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_signal = (TH1F*)Signal_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_signal = (TH1F*)Signal_f ->Get("event_chi2cut/N_PrimVertices");

  TH1F *nvp_nocuts_bkg = (TH1F*)Bkg_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_bkg = (TH1F*)Bkg_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_bkg = (TH1F*)Bkg_f ->Get("event_chi2cut/N_PrimVertices");

  nvp_nocuts_data->Rebin(4);
  nvp_preselection_data->Rebin(4);
  nvp_selection_data->Rebin(4);

  nvp_nocuts_signal->Rebin(4);
  nvp_preselection_signal->Rebin(4);
  nvp_selection_signal->Rebin(4);

  nvp_nocuts_bkg->Rebin(4);
  nvp_preselection_bkg->Rebin(4);
  nvp_selection_bkg->Rebin(4);


  TGraphAsymmErrors* eff_presel_data = new TGraphAsymmErrors( nvp_preselection_data, nvp_nocuts_data, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_sel_data = new TGraphAsymmErrors( nvp_selection_data, nvp_nocuts_data, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_data = new TGraphAsymmErrors( nvp_selection_data, nvp_preselection_data, "cl=0.683 b(1,1) mode" );

  TGraphAsymmErrors* eff_presel_signal = new TGraphAsymmErrors( nvp_preselection_signal, nvp_nocuts_signal, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_sel_signal = new TGraphAsymmErrors( nvp_selection_signal, nvp_nocuts_signal, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_signal = new TGraphAsymmErrors( nvp_selection_signal, nvp_preselection_signal, "cl=0.683 b(1,1) mode" );

  TGraphAsymmErrors* eff_presel_bkg = new TGraphAsymmErrors( nvp_preselection_bkg, nvp_nocuts_bkg, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_sel_bkg = new TGraphAsymmErrors( nvp_selection_bkg, nvp_nocuts_bkg, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_bkg = new TGraphAsymmErrors( nvp_selection_bkg, nvp_preselection_bkg, "cl=0.683 b(1,1) mode" );

  folder="chsvspuppi";
  TFile *Data_puppi_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.Data.Data.root", "READ");
  TFile *Signal_puppi_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime20001200HT.root", "READ");
  TFile *Bkg_puppi_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.background.root", "READ");

  TH1F *nvp_nocuts_data_puppi = (TH1F*)Data_puppi_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_data_puppi = (TH1F*)Data_puppi_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_data_puppi = (TH1F*)Data_puppi_f ->Get("event_chi2cut/N_PrimVertices");

  TH1F *nvp_nocuts_signal_puppi = (TH1F*)Signal_puppi_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_signal_puppi = (TH1F*)Signal_puppi_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_signal_puppi = (TH1F*)Signal_puppi_f ->Get("event_chi2cut/N_PrimVertices");

  TH1F *nvp_nocuts_bkg_puppi = (TH1F*)Bkg_puppi_f ->Get("input/N_PrimVertices");
  TH1F *nvp_preselection_bkg_puppi = (TH1F*)Bkg_puppi_f ->Get("event_twodcut/N_PrimVertices");
  TH1F *nvp_selection_bkg_puppi = (TH1F*)Bkg_puppi_f ->Get("event_chi2cut/N_PrimVertices");

  // TH1F *hist = nvp_nocuts_signal_puppi;
  // for (int i=1; i<hist->GetNbinsX()+1; ++i){
  //   cout << hist->GetXaxis()->GetBinLowEdge(i) << ", ";}
  // Double_t bins[55]={0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5, 30.5, 31.5, 32.5, 33.5, 34.5, 35.5, 36.5, 37.5, 38.5, 39.5, 40.5, 41.5, 42.5, 43.5, 44.5, 45.5, 46.5, 47.5, 48.5, 49.5, 50.5, 51.5, 52.5, 53.5, 54.5};
  // nvp_preselection_signal_puppi->Rebin(54, "nvp_preselection_signal_puppi",bins);
  // nvp_selection_signal_puppi->Rebin(54, "nvp_selection_signal_puppi",bins);
  // nvp_nocuts_signal_puppi->Rebin(54, "nvp_nocuts_signal_puppi",bins);

  nvp_nocuts_data_puppi->Rebin(4);
  nvp_preselection_data_puppi->Rebin(4);
  nvp_selection_data_puppi ->Rebin(4);

  nvp_nocuts_signal_puppi ->Rebin(4);
  nvp_preselection_signal_puppi ->Rebin(4);
  nvp_selection_signal_puppi ->Rebin(4);

  nvp_nocuts_bkg_puppi->Rebin(4);
  nvp_preselection_bkg_puppi->Rebin(4);
  nvp_selection_bkg_puppi ->Rebin(4);





  TGraphAsymmErrors* eff_presel_data_puppi = new TGraphAsymmErrors( nvp_preselection_data_puppi, nvp_nocuts_data_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_sel_data_puppi = new TGraphAsymmErrors( nvp_selection_data_puppi, nvp_nocuts_data_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_data_puppi = new TGraphAsymmErrors( nvp_selection_data_puppi, nvp_preselection_data_puppi, "cl=0.683 b(1,1) mode" );

  TGraphAsymmErrors* eff_presel_signal_puppi = new TGraphAsymmErrors( nvp_preselection_signal_puppi, nvp_nocuts_signal_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_sel_signal_puppi = new TGraphAsymmErrors( nvp_selection_signal_puppi, nvp_nocuts_signal_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_signal_puppi = new TGraphAsymmErrors( nvp_selection_signal_puppi, nvp_preselection_signal_puppi, "cl=0.683 b(1,1) mode" );

  TGraphAsymmErrors* eff_presel_bkg_puppi = new TGraphAsymmErrors( nvp_preselection_bkg_puppi, nvp_nocuts_bkg_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_sel_bkg_puppi = new TGraphAsymmErrors( nvp_selection_bkg_puppi, nvp_nocuts_bkg_puppi, "cl=0.683 b(1,1) mode" );
  TGraphAsymmErrors* eff_tagged_bkg_puppi = new TGraphAsymmErrors( nvp_selection_bkg_puppi, nvp_preselection_bkg_puppi, "cl=0.683 b(1,1) mode" );
  // nvp_selection_signal_puppi->Draw("AP");
  // nvp_preselection_signal_puppi->SetLineColor(kRed);
  // nvp_preselection_signal_puppi->Draw("same");
  std::vector<TGraphAsymmErrors*> hists={eff_presel_data,eff_presel_signal,eff_presel_data_puppi,eff_presel_signal_puppi,eff_presel_bkg,eff_presel_bkg_puppi};
  plot_result( hists,  1, 0.001,"presel_eff");


  hists={eff_sel_data,eff_sel_signal,eff_sel_data_puppi,eff_sel_signal_puppi,eff_sel_bkg,eff_sel_bkg_puppi};
  plot_result( hists,  1, 0.0001,"sel_eff");

 
  hists={eff_tagged_data,eff_tagged_signal,eff_tagged_data_puppi,eff_tagged_signal_puppi,eff_tagged_bkg,eff_tagged_bkg_puppi};
  plot_result( hists,  1, 0.001,"tagger_eff");



  hists={eff_presel_bkg,eff_presel_signal,eff_presel_bkg_puppi,eff_presel_signal_puppi};
  plot_result( hists,  1, 0.001,"presel_bkg_eff", "Bkg CHS", "Bkg Puppi");


  hists={eff_sel_bkg,eff_sel_signal,eff_sel_bkg_puppi,eff_sel_signal_puppi};
  plot_result( hists,  1, 0.0001,"sel_bkg_eff", "Bkg CHS", "Bkg Puppi");

 
  hists={eff_tagged_bkg,eff_tagged_signal,eff_tagged_bkg_puppi,eff_tagged_signal_puppi};
  plot_result( hists,  1, 0.001,"tagger_bkg_eff", "Bkg CHS", "Bkg Puppi");



  


  hists={eff_tagged_bkg_puppi,eff_tagged_data_puppi,eff_tagged_bkg_puppi,eff_tagged_data_puppi,};
  plot_result( hists,  0.12, 0.001,"eff_CHSvsPUPPI", "Bkg Puppi", "Data CHS","Data Puppi", "Data Puppi (#times 10)", true, false);

  // for (int i=0;i<eff_tagged_bkg_puppi->GetN();i++) eff_tagged_bkg_puppi->GetY()[i] *= 2;
  // for (int i=0;i<eff_tagged_data_puppi->GetN();i++) eff_tagged_data_puppi->GetY()[i] *= 2;

  hists={eff_tagged_bkg_puppi,eff_tagged_bkg,eff_tagged_data_puppi,eff_tagged_data};
  plot_result( hists,  0.06, 0.001,"eff_CHSvsPUPPI", "Bkg Puppi", "Data Puppi","Bkg CHS", "Data CHS",false,false);

  // hists={eff_tagged_bkg_puppi,eff_tagged_signal,eff_tagged_data_puppi,eff_tagged_signal_puppi};
  // plot_result( hists,  1, 0.00000001,"eff_PUPPI", "Bkg Puppi", "Data Puppi");
}//end of void function

