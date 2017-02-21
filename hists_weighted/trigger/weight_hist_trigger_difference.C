#include "TH1.h"
#include "TH2.h"

using namespace std;

void weight_hist_trigger_difference(){

  //read in .root files to weight
  TFile * trigger_BCDEF = new TFile("MuonTrigger_EfficienciesAndSF_RunBtoF.root");
  TFile * trigger_GH = new TFile("MuonTrigger_EfficienciesAndSF_RunGtoH.root");

  TFile * trigger_allRuns = new TFile("Diff_MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "RECREATE");
  double lumi_BCDEF = 18.8442;
  double lumi_GH = 15.4089;

  //read in hists to weight
  // Run BCDEF
   //Trigger Mu 50
  TH1F* h_MU50_BCDEF_eta_ratio = (TH1F*)trigger_BCDEF->Get("Mu50_OR_TkMu50_EtaBins/eta_ratio");
  TH2F* h_MU50_BCDEF_abseta_pt_ratio = (TH2F*)trigger_BCDEF->Get("Mu50_OR_TkMu50_PtEtaBins/abseta_pt_ratio");
  TH2F* h_MU50_BCDEF_pt_abseta_ratio = (TH2F*)trigger_BCDEF->Get("Mu50_OR_TkMu50_PtEtaBins/pt_abseta_ratio");
  TH1F* h_MU50_BCDEF_pt_ratio = (TH1F*)trigger_BCDEF->Get("Mu50_OR_TkMu50_PtBins/pt_ratio");

  // Run GH
  //Trigger Mu 50
  TH1F* h_MU50_GH_eta_ratio = (TH1F*)trigger_GH->Get("Mu50_OR_TkMu50_EtaBins/eta_ratio");
  TH2F* h_MU50_GH_abseta_pt_ratio = (TH2F*)trigger_GH->Get("Mu50_OR_TkMu50_PtEtaBins/abseta_pt_ratio");
  TH2F* h_MU50_GH_pt_abseta_ratio = (TH2F*)trigger_GH->Get("Mu50_OR_TkMu50_PtEtaBins/pt_abseta_ratio");
  TH1F* h_MU50_GH_pt_ratio = (TH1F*)trigger_GH->Get("Mu50_OR_TkMu50_PtBins/pt_ratio");

 //  ////////////                     Scale Run BCDEF                     /////////////////////////////////////
 

 //  //Trigger Mu 50
 //  h_MU50_BCDEF_eta_ratio ->Scale(lumi_BCDEF); 
 //  h_MU50_BCDEF_abseta_pt_ratio ->Scale(lumi_BCDEF); 
 //  h_MU50_BCDEF_pt_abseta_ratio ->Scale(lumi_BCDEF); 
 //  h_MU50_BCDEF_pt_ratio ->Scale(lumi_BCDEF); 


 // ////////////                     Scale Run GH                     /////////////////////////////////////
 

 //  //Trigger Mu 50
 //  h_MU50_GH_eta_ratio ->Scale(lumi_GH); 
 //  h_MU50_GH_abseta_pt_ratio ->Scale(lumi_GH); 
 //  h_MU50_GH_pt_abseta_ratio ->Scale(lumi_GH); 
 //  h_MU50_GH_pt_ratio ->Scale(lumi_GH); 


  ////////////                     Add Histogramm Run BCDEF + GH                   /////////////////////////////////////

   //Trigger Mu 50
  h_MU50_BCDEF_eta_ratio->Add(h_MU50_GH_eta_ratio,-1);
  h_MU50_BCDEF_abseta_pt_ratio->Add(h_MU50_GH_abseta_pt_ratio,-1);
  h_MU50_BCDEF_pt_abseta_ratio->Add(h_MU50_GH_pt_abseta_ratio,-1);
  h_MU50_BCDEF_pt_ratio->Add(h_MU50_GH_pt_ratio,-1);

 ////////////                     Add 1 to all entries in the histogramm                   /////////////////////////////////////
  int nbinsx =h_MU50_BCDEF_pt_ratio->GetXaxis()->GetNbins();
 
  for (int i=0;i<=nbinsx; i++){
    //  std::cout << h_MU50_BCDEF_pt_ratio->GetBinContent(i)<<std::endl;
    h_MU50_BCDEF_pt_ratio->AddBinContent(i);
    //  std::cout << h_MU50_BCDEF_pt_ratio->GetBinContent(i)<<std::endl;
  }

  nbinsx =h_MU50_BCDEF_abseta_pt_ratio->GetXaxis()->GetNbins();
 int nbinsy =h_MU50_BCDEF_abseta_pt_ratio->GetYaxis()->GetNbins();
 
  for (int i=0;i<=nbinsx; i++){
    for (int j=0;j<=nbinsy; j++){
      // std::cout << h_MU50_BCDEF_abseta_pt_ratio->GetBinContent(i,j)<<std::endl;
      h_MU50_BCDEF_abseta_pt_ratio ->SetBinContent(i,j,h_MU50_BCDEF_abseta_pt_ratio->GetBinContent(i,j)+1);
      //  std::cout << h_MU50_BCDEF_abseta_pt_ratio->GetBinContent(i,j)<<std::endl;
      //  std::cout<<"------------"<<std::endl;
    }
  }

  nbinsx =h_MU50_BCDEF_pt_abseta_ratio->GetXaxis()->GetNbins();
  nbinsy =h_MU50_BCDEF_pt_abseta_ratio->GetXaxis()->GetNbins();

  for (int i=0;i<=nbinsx; i++){
    for (int j=0;j<=nbinsy; j++){
      h_MU50_BCDEF_pt_abseta_ratio->SetBinContent(i,j,h_MU50_BCDEF_pt_abseta_ratio->GetBinContent(i,j)+1);
    }
  }

  ////////////                    Save new histogramms as new histogramms                  /////////////////////////////////////
  //Trigger Mu 50
  TH1F* new_MU50_eta_ratio = (TH1F*) h_MU50_BCDEF_eta_ratio;
  TH2F* new_MU50_abseta_pt_ratio = (TH2F*)h_MU50_BCDEF_abseta_pt_ratio;
  TH2F* new_MU50_pt_abseta_ratio = (TH2F*)h_MU50_BCDEF_pt_abseta_ratio;
  TH1F* new_MU50_pt_ratio = (TH1F*)h_MU50_BCDEF_pt_ratio;

  
  // ////////////                     Scale new Histogramms to total lumi                 /////////////////////////////////////
  // double lumi_tot = lumi_BCDEF + lumi_GH;


  // //Trigger Mu 50
  // new_MU50_eta_ratio->Scale(1/lumi_tot); 
  // new_MU50_abseta_pt_ratio ->Scale(1/lumi_tot); 
  // new_MU50_pt_abseta_ratio ->Scale(1/lumi_tot); 
  // new_MU50_pt_ratio->Scale(1/lumi_tot); 



 ////////////                    Save new histogramms in new file                /////////////////////////////////////

 
    
  //Trigger Mu 50
  TDirectory *dir4 =trigger_allRuns ->mkdir("Mu50_OR_TkMu50_EtaBins");
  dir4->cd();
  new_MU50_eta_ratio->Write(); 

  TDirectory *dir5 =trigger_allRuns ->mkdir("Mu50_OR_TkMu50_PtEtaBins");
  dir5->cd();
  new_MU50_abseta_pt_ratio ->Write(); 
  new_MU50_pt_abseta_ratio ->Write(); 

  TDirectory *dir6 =trigger_allRuns ->mkdir("Mu50_OR_TkMu50_PtBins");
  dir6->cd();
  new_MU50_pt_ratio->Write();


  trigger_allRuns->Close();
}
