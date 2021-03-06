#include "TH1.h"
#include "TH2.h"
#include "vector"

using namespace std;

void weight_hist_MuonID_difference(){

    
 
 
 
  //read in .root files to weight
  TFile * trigger_BCDEF = new TFile("MuonID_EfficienciesAndSF_BCDEF.root");
  
  TFile * trigger_GH = new TFile("MuonID_EfficienciesAndSF_GH.root");
  double lumi_BCDEF = 18.8442;
  double lumi_GH = 15.4089;
  double lumi_tot = lumi_BCDEF + lumi_GH;
  TFile * trigger_allRuns = new TFile("Diff_MuonID_EfficienciesAndSF_average_RunBtoH.root", "RECREATE");
  //std::vector<TString> ID={"LooseID","MediumID2016","MediumID","TightID", "HighPtID"};
  std::vector<TString> ID={"MediumID2016", "HighPtID"};
  std::vector<TString> var={"eta/eta_ratio","pt/pt_ratio","vtx/tag_nVertices_ratio"};
  bool berror =true;
   
  //Define all variables

  
  TH1F* h_MU24_BCDEF_eta_ratio ;
  TH2F* h_MU24_BCDEF_abseta_pt_ratio;
  TH2F* h_MU24_BCDEF_pt_abseta_ratio ;
  TH1F* h_MU24_BCDEF_pt_ratio ;
  TH1F* h_MU24_BCDEF_tag_nVertices_ratio;
  TH1F* h_MU24_GH_eta_ratio ;
  TH2F* h_MU24_GH_abseta_pt_ratio;
  TH2F* h_MU24_GH_pt_abseta_ratio;
  TH1F* h_MU24_GH_pt_ratio ;
  TH1F* h_MU24_GH_tag_nVertices_ratio;
  TH1F* new_MU24_eta_ratio ;
  TH2F* new_MU24_abseta_pt_ratio;
  TH2F* new_MU24_pt_abseta_ratio;
  TH1F* new_MU24_pt_ratio;
  TH1F* new_MU24_tag_nVertices_ratio;
  TDirectory *dir1,*dir2,*dir3,*dir4;
  TString hist;


  for(int i=0;i<ID.size();i++){
    if(berror)   std::cout<<"ID "<<ID[i]<<std::endl;
    if(ID[i]=="HighPtID" ){
      var={"eta/eta_ratio","newpt/pair_ne_ratio"};
    }
      

    for(int j=0;j<var.size();j++){
   if(berror)  std::cout<<"var "<<var[j]<<std::endl;


      //read in hists to weight
      
      hist= "MC_NUM_";
      hist+=ID[i];
      hist+="_DEN_genTracks_PAR_";
      hist+=var[j];
    
      // Run BCDEF & GH
      h_MU24_BCDEF_eta_ratio = (TH1F*)trigger_BCDEF->Get(hist);
      h_MU24_GH_eta_ratio = (TH1F*)trigger_GH->Get(hist);

      
      
      // Add Histogramm Run BCDEF + GH 
      h_MU24_BCDEF_eta_ratio->Add(h_MU24_GH_eta_ratio,-1);
      int nbinsx =h_MU24_BCDEF_eta_ratio->GetXaxis()->GetNbins();
      for (int i=0;i<=nbinsx; i++)  h_MU24_BCDEF_eta_ratio->AddBinContent(i);


      // Save new histogramms as new histogramms    
      new_MU24_eta_ratio = (TH1F*)h_MU24_BCDEF_eta_ratio;
     
	
      dir1 =trigger_allRuns ->mkdir("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_"+var[j]);
      dir1->cd();
      new_MU24_eta_ratio->Write(); 

    }//for-loop j
    std::cout<<"2D"<<std::endl;
    
    if(ID[i]=="HighPtID" ){
      // Run BCDEF
      h_MU24_BCDEF_abseta_pt_ratio = (TH2F*)trigger_BCDEF->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_newpt_eta/abseta_pair_ne_ratio");
      h_MU24_BCDEF_pt_abseta_ratio = (TH2F*)trigger_BCDEF->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_newpt_eta/pair_ne_ratio");
    
      // Run GH
      h_MU24_GH_abseta_pt_ratio = (TH2F*)trigger_GH->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_newpt_eta/abseta_pair_ne_ratio");
      h_MU24_GH_pt_abseta_ratio = (TH2F*)trigger_GH->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_newpt_eta/pair_ne_ratio");
    
    }else{
    // Run BCDEF
      h_MU24_BCDEF_abseta_pt_ratio = (TH2F*)trigger_BCDEF->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
      h_MU24_BCDEF_pt_abseta_ratio = (TH2F*)trigger_BCDEF->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_pt_eta/pt_abseta_ratio");
    
      // Run GH
      h_MU24_GH_abseta_pt_ratio = (TH2F*)trigger_GH->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
      h_MU24_GH_pt_abseta_ratio = (TH2F*)trigger_GH->Get("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_pt_eta/pt_abseta_ratio");
    }
     

    /////////////////                Add Histogramm Run BCDEF + GH                   /////////////////////////////////////
    
    h_MU24_BCDEF_abseta_pt_ratio->Add(h_MU24_GH_abseta_pt_ratio,-1);
    h_MU24_BCDEF_pt_abseta_ratio->Add(h_MU24_GH_pt_abseta_ratio,-1);

    int nbinsx =h_MU24_BCDEF_abseta_pt_ratio->GetXaxis()->GetNbins();
    int nbinsy =h_MU24_BCDEF_abseta_pt_ratio->GetYaxis()->GetNbins();
    if(berror) std::cout <<"Nbinsx"<<nbinsx<<std::endl;
    if(berror) std::cout <<"Nbinsy"<<nbinsy<<std::endl;
    for (int i=0;i<=nbinsx; i++){
      for (int j=0;j<=nbinsy; j++){  
	if(berror) std::cout<< h_MU24_BCDEF_abseta_pt_ratio->GetBinContent(i,j) <<std::endl;
	h_MU24_BCDEF_abseta_pt_ratio ->SetBinContent(i,j,h_MU24_BCDEF_abseta_pt_ratio->GetBinContent(i,j)+1);
	if(berror) std::cout<< h_MU24_BCDEF_abseta_pt_ratio->GetBinContent(i,j) <<std::endl;

	if(berror) 	std::cout<< "--------------" <<std::endl;
      }
    }

    nbinsx =h_MU24_BCDEF_pt_abseta_ratio->GetXaxis()->GetNbins();
    nbinsy =h_MU24_BCDEF_pt_abseta_ratio->GetYaxis()->GetNbins();
 
    for (int i=0;i<=nbinsx; i++){
      for (int j=0;j<=nbinsy; j++){
	h_MU24_BCDEF_pt_abseta_ratio ->SetBinContent(i,j,h_MU24_BCDEF_pt_abseta_ratio->GetBinContent(i,j)+1);
      }
    }
    std::cout<<"old "<<h_MU24_BCDEF_abseta_pt_ratio->GetBinContent(0,0)<<std::endl;
    /////////////////                Save new histogramms as new histogramms                  /////////////////////////////////////
      new_MU24_abseta_pt_ratio = (TH2F*)h_MU24_BCDEF_abseta_pt_ratio;
      new_MU24_pt_abseta_ratio = (TH2F*)h_MU24_BCDEF_pt_abseta_ratio;
     
    
      std::cout<<"new "<< new_MU24_abseta_pt_ratio->GetBinContent(0,0)<<std::endl;

      /////////////////                 Save new histogramms in new file                ////////////////////////////////////

      dir2 =trigger_allRuns ->mkdir("MC_NUM_"+ID[i]+"_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
      dir2->cd();
      new_MU24_abseta_pt_ratio ->Write(); 
      new_MU24_pt_abseta_ratio->Write(); 

     
   
  }//for-loop i

  trigger_allRuns->Close();
}
