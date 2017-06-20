#include "TH2F.h"

TString folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/uncertainties/muon/none/";
bool berror=false;


void eff_2D_plots(){

  gStyle->SetOptStat(0);
 

 std::vector<TString> Zmasspoints = {"1500","2000","2500"};
 std::vector<TString> Tmasspoints = {"700","900","1200","1500"};
 std::vector<TString> decays = {"HT","ZT","WB"};
 // std::vector<TString> decays = {"HT"};


 for(int i=0;i<decays.size();i++){
   if(berror)  std::cout<<decays[i]<<std::endl;

   Tmasspoints = {"700","900","1200","1500"};
   TH2F *eff_hist = new TH2F("eff_hist","Eff hist",Zmasspoints.size(),0,3,Tmasspoints.size(),0,3);

   for(int j=0;j<Zmasspoints.size();j++){
     for(int k=0;k<Tmasspoints.size();k++){
       eff_hist->Fill(Zmasspoints[j],Tmasspoints[k],0);
     }
   }

   for(int j=0;j<Zmasspoints.size();j++){
     if(j==0) Tmasspoints = {"700","900","1200"};
     if(j==1) Tmasspoints = {"900","1200","1500"};
     if(j==2) Tmasspoints = {"1200","1500"};
     for(int k=0;k<Tmasspoints.size();k++){

    
	 TFile *file2 = new TFile(folder+"uhh2.AnalysisModuleRunner.MC.MC_ZPrime"+Zmasspoints[j]+"ToTPrime"+Tmasspoints[k]+"T_TPrimeTo"+decays[i]+".root");
	 TFile *file1 = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/PreSelection/rootfiles/none/uhh2.AnalysisModuleRunner.MC.MC_ZPrime"+Zmasspoints[j]+"ToTPrime"+Tmasspoints[k]+"T_TPrimeTo"+decays[i]+".root");

	 TFile *file2_elec = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/uncertainties/elec/none/uhh2.AnalysisModuleRunner.MC.MC_ZPrime"+Zmasspoints[j]+"ToTPrime"+Tmasspoints[k]+"T_TPrimeTo"+decays[i]+".root");
	 TFile *file1_elec = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/PreSelection/rootfiles/none/elec/uhh2.AnalysisModuleRunner.MC.MC_ZPrime"+Zmasspoints[j]+"ToTPrime"+Tmasspoints[k]+"T_TPrimeTo"+decays[i]+".root");

	 TH1D *hist1  = (TH1D*)file1 ->Get("input_eff/eff;1");
	 TH1D *hist2  = (TH1D*)file2 ->Get("eff_chi2cut/eff;1");

	 TH1D *hist1_elec  = (TH1D*)file1_elec ->Get("input_eff/eff;1");
	 TH1D *hist2_elec  = (TH1D*)file2_elec ->Get("eff_chi2cut/eff;1");
	 Float_t eff = hist2->GetBinContent(2)/hist1->GetBinContent(2);
	 Float_t eff_elec = hist2_elec->GetBinContent(2)/hist1_elec->GetBinContent(2);
	 if(berror)   std::cout<<"eff"<<eff<<std::endl;
	 if(berror)   std::cout<<"eff elec"<<eff_elec<<std::endl;

	 eff_hist->Fill(Zmasspoints[j],Tmasspoints[k],eff+eff_elec);
     
     }//Tmasspoints
   }//Zmasspoints
   TCanvas *c1= new TCanvas("c1","",10,10,600,600);
   c1->Clear();
   c1->cd();
   gPad->SetTickx();
   gPad->SetTicky();
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.15); 
   c1->SetRightMargin(0.15);
   c1->SetLeftMargin(0.1);
   eff_hist->SetTitle("");
   eff_hist->GetXaxis()->SetTitle("M_{Z'}");
   eff_hist->GetYaxis()->SetTitle("M_{T'}");
   eff_hist->Draw("colz");
   eff_hist->Draw("same TEXT");

   TPaveText *pt = new TPaveText(.625,.16,.84,.26,"nbNDC");
   pt->SetFillColor(0);
   if(decays[i]=="HT")pt->AddText("T ' #rightarrow H t");
   if(decays[i]=="ZT")pt->AddText("T ' #rightarrow Z t");
   if(decays[i]=="WB")pt->AddText("T ' #rightarrow W b");
   pt->Draw();


   c1->Print(folder+"eff_"+decays[i]+".eps");
 }//decays



}
