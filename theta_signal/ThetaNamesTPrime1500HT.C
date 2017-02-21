#include "TH1.h"

using namespace std;

void ThetaNamesTPrime1500HT()
{

  const int nproc=7;

  TString process[nproc] = {"TTbar", "WJets","QCD","ST","DYJetsToLL","MC_ZPrime2000ToTPrime1500T_TPrimeToHT","MC_ZPrime2500ToTPrime1500T_TPrimeToHT"};
  


  const int Nsyst = 1;
  TString systname[Nsyst]={"default"};
  TString systshift = "Up";
  TString systshift2 = "plus";
  if(systshift=="Down") systshift2 = "minus";

  
  for(int j=0; j<Nsyst; ++j){
     TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/dpg";
      if(systname[j]!="default"){
         directory += systname[j];
         directory +="_";
         directory += systshift;
     }
     std::cout<< directory <<std::endl;

     TString outfilename = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/dpg/theta_histograms_MZPrime";
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
       TFile * infile = new TFile(directory+"/uhh2.AnalysisModuleRunner."+mcdata+"."+process[i]+".root");
       infile->cd();
       
       std::cout << "   got the file" <<endl;
       
       TH1F* M_higgstop = (TH1F*)infile->Get("higgs_top_chi2min_chi2cut/M_ZPrime_rec");
       // Double_t higgtop[]={600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2050,2100,2150,2200,2250,2300,2350,2400,2450,2500,2550,2600,2650,2700,2750,2800,2850,2900,2950,3000};
       M_higgstop->Rebin(40);
       ////////////////////////////////////////////////////////////////////////////////////////
       TH1F* M_higgsnotop_old = (TH1F*)infile->Get("higgs_notop_chi2min_chi2cut/M_ZPrime_rec");
       Double_t higgsnotop[31]={600,660,720,780,840,900,960,1020,1080,1140,1200,1260,1320,1380,1440,1500,1560,1620,1680,1740,1800,1860,1920,1980,2040,2100,2160,2280,2460,2700,3000};
     TH1F* M_higgsnotop =  (TH1F*) M_higgsnotop_old->Rebin(30,"M_higgsnotop",higgsnotop);
       ////////////////////////////////////////////////////////////////////////////////////////
       TH1F* M_zwtop_old = (TH1F*)infile->Get("zw_top_chi2min_chi2cut/M_ZPrime_rec");
       Double_t zwtop[33]={600,660,720,780,840,900,960,1020,1080,1140,1200,1260,1320,1380,1440,1500,1560,1620,1680,1740,1800,1860,1920,1980,2040,2100,2160,2220,2280,2340,2500,2700,3000};
       TH1F* M_zwtop =  (TH1F*) M_zwtop_old ->Rebin(32,"M_zwtop",zwtop);
       ////////////////////////////////////////////////////////////////////////////////////////
       TH1F* M_zwnotop = (TH1F*)infile->Get("zw_notop_chi2min_chi2cut/M_ZPrime_rec");
              
       std::cout << "   got the histos" <<endl;
         
       if(systname[j]!="default"){
	 M_higgstop->SetName("MZPrime_TPrime1200HT_higgstop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	 M_higgsnotop->SetName("MZPrime_TPrime1200HT_higgsnotop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	 M_zwtop->SetName("MZPrime_TPrime1200HT_zwtop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	 M_zwnotop->SetName("MZPrime_TPrime1200HT_zwnotop__"+process[i]+"__"+systname[j]+"__"+systshift2);
 
       }
       else{
         M_higgstop ->SetName("MZPrime_TPrime1200HT_higgstop__"+process[i]);
	 M_higgsnotop->SetName("MZPrime_TPrime1200HT_higgsnotop__"+process[i]);
	 M_zwtop->SetName("MZPrime_TPrime1200HT_zwtop__"+process[i]);
	 M_zwnotop->SetName("MZPrime_TPrime1200HT_zwnotop__"+process[i]);
	 
       }

       outfile->cd();
       M_higgstop->Write();
       M_higgsnotop->Write();
       M_zwtop->Write();
       M_zwnotop->Write();
     }
   }
}
