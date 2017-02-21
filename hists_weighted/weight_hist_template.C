#include "TH1.h"
#include "TH2.h"

using namespace std;

void weight_hist(){

  //read in .root files to weight
  TFile * trigger_BCDEF = new TFile("EfficienciesAndSF_RunBtoF.root");
  TFile * trigger_GH = new TFile("EfficienciesAndSF_Period4.root");

  //read in hists to weight
  // Run BCDEF
  //Trigger Mu 24
  TH1F* h_MU24_BCDEF_eta_ratio = (TH1F*)trigger_BCDEF->Get("IsoMu24_OR_IsoTkMu24_EtaBins/eta_ratio");
  TH2F* h_MU24_BCDEF_abseta_pt_ratio = (TH2F*)trigger_BCDEF->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
  TH2F* h_MU24_BCDEF_pt_abseta_ratio = (TH2F*)trigger_BCDEF->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
  TH1F* h_MU24_BCDEF_pt_ratio = (TH1F*)trigger_BCDEF->Get("IsoMu24_OR_IsoTkMu24_PtBins/pt_ratio");



  // Run GH
  //Trigger Mu 24
  TH1F* h_MU24_GH_eta_ratio = (TH1F*)trigger_GH->Get("IsoMu24_OR_IsoTkMu24_EtaBins/eta_ratio");
  TH2F* h_MU24_GH_abseta_pt_ratio = (TH2F*)trigger_GH->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
  TH2F* h_MU24_GH_pt_abseta_ratio = (TH2F*)trigger_GH->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
  TH1F* h_MU24_GH_pt_ratio = (TH1F*)trigger_GH->Get("IsoMu24_OR_IsoTkMu24_PtBins/pt_ratio");



  ////////////                     Scale Run BCDEF                     /////////////////////////////////////
  double lumi_BCDEF = 20.5;

  //Trigger Mu 24
  h_MU24_BCDEF_eta_ratio->Scale(lumi_BCDEF); 
  h_MU24_BCDEF_abseta_pt_ratio->Scale(lumi_BCDEF); 
  h_MU24_BCDEF_pt_abseta_ratio->Scale(lumi_BCDEF); 
  h_MU24_BCDEF_pt_ratio ->Scale(lumi_BCDEF); 

 

 ////////////                     Scale Run GH                     /////////////////////////////////////
  double lumi_GH = 16;

  //Trigger Mu 24
  h_MU24_GH_eta_ratio->Scale(lumi_GH); 
  h_MU24_GH_abseta_pt_ratio->Scale(lumi_GH); 
  h_MU24_GH_pt_abseta_ratio->Scale(lumi_GH); 
  h_MU24_GH_pt_ratio ->Scale(lumi_GH); 

 

  ////////////                     Add Histogramm Run BCDEF + GH                   /////////////////////////////////////

  //Trigger Mu 24
  h_MU24_BCDEF_eta_ratio->Add(h_MU24_GH_eta_ratio);
  h_MU24_BCDEF_abseta_pt_ratio->Add(h_MU24_GH_abseta_pt_ratio);
  h_MU24_BCDEF_pt_abseta_ratio->Add(h_MU24_GH_pt_abseta_ratio);
  h_MU24_BCDEF_pt_ratio->Add(h_MU24_GH_pt_ratio);

 
  ////////////                    Save new histogramms as new histogramms                  /////////////////////////////////////
  TH1F* new_MU24_eta_ratio = (TH1F*)h_MU24_BCDEF_eta_ratio;
  TH2F* new_MU24_abseta_pt_ratio = (TH2F*)h_MU24_BCDEF_abseta_pt_ratio;
  TH2F* new_MU24_pt_abseta_ratio = (TH2F*)h_MU24_BCDEF_pt_abseta_ratio;
  TH1F* new_MU24_pt_ratio = (TH1F*)h_MU24_BCDEF_pt_ratio;

 
  
  ////////////                     Scale new Histogramms to total lumi                 /////////////////////////////////////
  double lumi_tot = lumi_BCDEF + lumi_GH;



  //Trigger Mu 24
  new_MU24_eta_ratio->Scale(1/lumi_tot); 
  new_MU24_abseta_pt_ratio ->Scale(1/lumi_tot); 
  new_MU24_pt_abseta_ratio->Scale(1/lumi_tot); 
  new_MU24_pt_ratio->Scale(1/lumi_tot); 
  
 

 ////////////                    Save new histogramms in new file                /////////////////////////////////////

  TFile * trigger_allRuns = new TFile("EfficienciesAndSF_RunBtoH.root", "RECREATE");
  

  //Trigger Mu 24
  TDirectory *dir1 =trigger_allRuns ->mkdir("IsoMu24_OR_IsoTkMu24_EtaBins");
  dir1->cd();
  new_MU24_eta_ratio->Write(); 

  TDirectory *dir2 =trigger_allRuns ->mkdir("IsoMu24_OR_IsoTkMu24_PtEtaBins");
  dir2->cd();
  new_MU24_abseta_pt_ratio ->Write(); 
  new_MU24_pt_abseta_ratio->Write(); 

  TDirectory *dir3 =trigger_allRuns ->mkdir("IsoMu24_OR_IsoTkMu24_PtBins");
  dir3->cd();
  new_MU24_pt_ratio->Write(); 
  
  

  trigger_allRuns->Close();
}
