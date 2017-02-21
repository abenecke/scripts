#include "TH1.h"

using namespace std;

void BackgroundNames_HT()
{
  const int nproc=9;

  TString process[nproc] = {"TTbar", "WJets","QCD","ST","DYJetsToLL","MC_ZPrime1500ToTPrime1200T_TPrimeToHT","MC_ZPrime2000ToTPrime1200T_TPrimeToHT","MC_ZPrime2500ToTPrime1200T_TPrimeToHT","DATA"};
   //TString process[nproc] = {"TTbar", "WJets","QCD","ST","DYJetsToLL"};


  const int Nsyst = 1;
  TString systname[Nsyst]={"default"};
  TString systshift = "Up";
  TString systshift2 = "plus";
  if(systshift=="Down") systshift2 = "minus";

  
  for(int j=0; j<Nsyst; ++j){
    TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/Sideband_Data";
    if(systname[j]!="default"){
      directory += systname[j];
      directory +="_";
      directory += systshift;
    }
    std::cout<< directory <<std::endl;

    TString outfilename = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/Sideband_Data/theta_histograms_background_MZPrime";
    if(systname[j]!="default"){
      outfilename += systname[j];
      outfilename +="_";
      outfilename +=systshift;
    }

    outfilename+=".root";
    std::cout<< outfilename <<std::endl;
    TFile *outfile = new TFile(outfilename,"RECREATE");
     
    int nmax = nproc;
    if(systname[j]!="default") nmax--;

    for(int i=0; i<nmax; ++i){
       
      TString mcdata = "MC";
      std::cout << process[i] <<endl;
       
      if(process[i]=="DATA") mcdata = "DATA";
       
      std::cout<< directory+"/."+mcdata+"."+process[i]+".root" << std::endl;
      TFile * infile_side1 = new TFile(directory+"/side1/uhh2.AnalysisModuleRunner."+mcdata+"."+process[i]+".root");
      infile_side1->cd();
      TFile * infile_side2 = new TFile(directory+"/side2/uhh2.AnalysisModuleRunner."+mcdata+"."+process[i]+".root");
      infile_side2->cd();
      TFile * infile_side3 = new TFile(directory+"/side3/uhh2.AnalysisModuleRunner."+mcdata+"."+process[i]+".root");
      infile_side3->cd();
       
      std::cout << "   got the file" <<endl;
 
     TH1F* side1_btag1 =  (TH1F*)infile_side1->Get("chi2min_btag1/M_ZPrime_rec");
     TH1F* side1_btag0 =  (TH1F*)infile_side1->Get("chi2min_btag0/M_ZPrime_rec");
     TH1F* side2_btag1 =  (TH1F*)infile_side2->Get("chi2min_btag1/M_ZPrime_rec");
     TH1F* side2_btag0 =  (TH1F*)infile_side2->Get("chi2min_btag0/M_ZPrime_rec");
     TH1F* side3_btag1 =  (TH1F*)infile_side3->Get("chi2min_btag1/M_ZPrime_rec");
     TH1F* side3_btag0 =  (TH1F*)infile_side3->Get("chi2min_btag0/M_ZPrime_rec");
       
     
          
      //  // TH1F* M_zwnotop = (TH1F*)infile->Get("zw_notop_chi2min_chi2cut/M_ZPrime_rec");
      //  // M_zwnotop ->Rebin(4);
      //  TH1F* M_zwnotop_old = (TH1F*)infile->Get("zw_notop_chi2min_btag50/M_ZPrime_rec");
      //   Double_t zwnotop[18]={600, 720, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2880}; //chi2cut
      //  //  Double_t zwnotop[9]={ 600,840, 1080, 1320, 1560, 1800, 2040, 2280,2760}; //btag
      // TH1F* M_zwnotop =  (TH1F*)  M_zwnotop_old->Rebin(17,"M_zwnotop",zwnotop);   
    

       // TH1F* hist = (TH1F*)infile->Get("zw_top_chi2min_btag50/M_ZPrime_rec");
       // // hist->Rebin(4);
       // for (int i=1; i<hist->GetNbinsX()+1; ++i){
       // 	 cout << hist->GetXaxis()->GetBinLowEdge(i) << ", ";}
       
     
      std::cout << "   got the histos" <<endl;
         
      if(systname[j]!="default"){

	side1_btag1 ->SetName("MZPrime_TPrime1200HT_side1_btag1__"+process[i]+"__"+systname[j]+"__"+systshift2);
	side1_btag0 ->SetName("MZPrime_TPrime1200HT_side1_btag0__"+process[i]+"__"+systname[j]+"__"+systshift2);
	side2_btag1 ->SetName("MZPrime_TPrime1200HT_side2_btag1__"+process[i]+"__"+systname[j]+"__"+systshift2);
	side2_btag0 ->SetName("MZPrime_TPrime1200HT_side2_btag0__"+process[i]+"__"+systname[j]+"__"+systshift2);
	side3_btag1 ->SetName("MZPrime_TPrime1200HT_side3_btag1__"+process[i]+"__"+systname[j]+"__"+systshift2);
	side3_btag0->SetName("MZPrime_TPrime1200HT_side3_btag0__"+process[i]+"__"+systname[j]+"__"+systshift2);

      }
      else{
	side1_btag1 ->SetName("MZPrime_TPrime1200HT_side1_btag1__"+process[i]);
	side1_btag0 ->SetName("MZPrime_TPrime1200HT_side1_btag0__"+process[i]);
	side2_btag1 ->SetName("MZPrime_TPrime1200HT_side2_btag1__"+process[i]);
	side2_btag0 ->SetName("MZPrime_TPrime1200HT_side2_btag0__"+process[i]);
	side3_btag1 ->SetName("MZPrime_TPrime1200HT_side3_btag1__"+process[i]);
	side3_btag0->SetName("MZPrime_TPrime1200HT_side3_btag0__"+process[i]);
	 
      }

      outfile->cd();
      side1_btag1->Write();
      side1_btag0->Write();
      side2_btag1->Write();
      side2_btag0->Write();
      side3_btag1->Write();
      side3_btag0->Write();

    }
  }

}
