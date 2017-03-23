#include "TH1.h"

using namespace std;

void ThetaNamesTPrime1200HT()
{
  const bool top=true;
  const bool notop=true;
  const bool onebtag=true;
  const int nproc=8;

  TString process[nproc] = {"TTbar", "WJets","QCD","ST","DYJetsToLL","MC_ZPrime1500ToTPrime1200T_TPrimeToHT","MC_ZPrime2000ToTPrime1200T_TPrimeToHT","MC_ZPrime2500ToTPrime1200T_TPrimeToHT"};
  


  const int Nsyst = 1;
  TString systname[Nsyst]={"default"};
  TString systshift = "Up";
  TString systshift2 = "plus";
  if(systshift=="Down") systshift2 = "minus";

  
  for(int j=0; j<Nsyst; ++j){
    TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/chsvspuppi";
    if(systname[j]!="default"){
      directory += systname[j];
      directory +="_";
      directory += systshift;
    }
    std::cout<< directory <<std::endl;

    TString outfilename = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/chsvspuppi/theta_histograms_MZPrime";
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
 
      //600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2400, 2460, 2520, 2580, 2640, 2700, 2760, 2820, 2880, 2940
       
      TH1F* M_higgstop_old = (TH1F*)infile->Get("higgs_top_chi2min_chi2cut/M_ZPrime_rec");
      //  Double_t higgtop[2]={600,3000};//btag
      // Double_t higgtop[2]={600,3000};//chi2cut
      // Double_t higgsnotop[40]={600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2400, 2460, 2520, 2580, 2640, 2700, 2760, 2820, 2880, 2940}; //complete
      Double_t higgtop[2]={600,   2940};
      TH1F* M_higgstop =  (TH1F*) M_higgstop_old->Rebin(1,"M_higgstop",higgtop);
      
      ////////////////////////////////////////////////////////////////////////////////////////
         
      TH1F* M_higgsnotop_old = (TH1F*)infile->Get("higgs_notop_chi2min_chi2cut/M_ZPrime_rec");
      //  Double_t higgsnotop[9]= { 600, 840, 1080, 1320, 1560, 1800, 2040, 2280, 2760};//btag
      //  Double_t higgsnotop[29]={600,660,720,780,840,900,960,1020,1080,1140,1200,1260,1320,1380,1440,1500,1560,1620,1680,1740,1800,1860,1920,1980,2100,2220,2400,2580,3000}; //chi2cut
      
      Double_t higgsnotop[31]={600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100,  2220, 2340, 2460, 2580,   2940};
      TH1F* M_higgsnotop =  (TH1F*) M_higgsnotop_old->Rebin(30,"M_higgsnotop",higgsnotop);
     
      
      ////////////////////////////////////////////////////////////////////////////////////////
     
       TH1F* M_zwtop_old = (TH1F*)infile->Get("zw_top_chi2min_chi2cut/M_ZPrime_rec");
       //    Double_t zwtop[19]={600, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2640, 2760, 2880}; //chi2cut
       // Double_t zwtop[19]= {600, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2640, 2760, 2880};//btag
      Double_t zwtop[36]={600,840, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2400, 2460, 2520, 2580, 2640, 2700, 2760, 2820, 2880, 2940};
      TH1F* M_zwtop =  (TH1F*) M_zwtop_old ->Rebin(35,"M_zwtop",zwtop);
      
      
      ////////////////////////////////////////////////////////////////////////////////////////
          
      TH1F* M_zwnotop_old = (TH1F*)infile->Get("zw_notop_chi2min_chi2cut/M_ZPrime_rec");
      //  Double_t zwnotop[18]={600, 720, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2880}; //chi2cut
       //  Double_t zwnotop[9]={ 600,840, 1080, 1320, 1560, 1800, 2040, 2280,2760}; //btag
     
Double_t zwnotop[36]={600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2400, 2460, 2580, 2700,  2820, 2940};
      TH1F* M_zwnotop =  (TH1F*)  M_zwnotop_old->Rebin(35,"M_zwnotop",zwnotop);   
    

       // TH1F* hist = (TH1F*)infile->Get("zw_top_chi2min_btag50/M_ZPrime_rec");
       // // hist->Rebin(4);
       // for (int i=1; i<hist->GetNbinsX()+1; ++i){
       // 	 cout << hist->GetXaxis()->GetBinLowEdge(i) << ", ";}
      ////////////////////////////////////////////////////////////////////////////////////////
      TH1F* M_higgstop_one_btag_old = (TH1F*)infile->Get("one_higgs_top_chi2min_chi2cut/M_ZPrime_rec");
      //      Double_t higgtop_one_btag[2]={600,3000};//chi2cut
      Double_t higgtop_one_btag[29]={600, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2460,  2580,  2700,  2820, 2940};//chi2cu
      TH1F* M_higgstop_one_btag =  (TH1F*) M_higgstop_one_btag_old->Rebin(28,"M_higgstop_one_btag",higgtop_one_btag);
      
      ////////////////////////////////////////////////////////////////////////////////////////
         
     
      TH1F* M_higgsnotop_one_btag_old = (TH1F*)infile->Get("one_higgs_notop_chi2min_chi2cut/M_ZPrime_rec");
      //  Double_t higgsnotop_one_btag[27]={600,660,720,780,840,900,960,1020,1080,1140,1200,1260,1320,1380,1440,1500,1560,1620,1680,1740,1800,1860,1920,1980,2220,2580,3000}; //chi2cut
      Double_t higgsnotop_one_btag[35]={600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2400, 2460, 2520, 2700,  2940};//chi2cut
      TH1F* M_higgsnotop_one_btag =  (TH1F*) M_higgsnotop_one_btag_old->Rebin(34,"M_higgsnotop_one_btag",higgsnotop_one_btag);
       
     
      std::cout << "   got the histos" <<endl;
         
      if(systname[j]!="default"){
	M_higgstop->SetName("MZPrime_TPrime1200HT_higgstop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_higgsnotop->SetName("MZPrime_TPrime1200HT_higgsnotop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_zwtop->SetName("MZPrime_TPrime1200HT_zwtop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_zwnotop->SetName("MZPrime_TPrime1200HT_zwnotop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_higgstop_one_btag->SetName("MZPrime_TPrime1200HT_higgstop_one_btag__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_higgsnotop_one_btag->SetName("MZPrime_TPrime1200HT_higgsnotop_one_btag__"+process[i]+"__"+systname[j]+"__"+systshift2);
      }
      else{
	M_higgstop ->SetName("MZPrime_TPrime1200HT_higgstop__"+process[i]);
	M_higgsnotop->SetName("MZPrime_TPrime1200HT_higgsnotop__"+process[i]);
	M_zwtop->SetName("MZPrime_TPrime1200HT_zwtop__"+process[i]);
	M_zwnotop->SetName("MZPrime_TPrime1200HT_zwnotop__"+process[i]);
	M_higgstop_one_btag ->SetName("MZPrime_TPrime1200HT_higgstop_one_btag__"+process[i]);
	M_higgsnotop_one_btag->SetName("MZPrime_TPrime1200HT_higgsnotop_one_btag__"+process[i]); 
	
      }

      outfile->cd();
      if(top)     M_higgstop->Write();
      if(notop)     M_higgsnotop->Write();
      if(top)    M_zwtop->Write();
      if(notop)    M_zwnotop->Write();
      if(top && onebtag)     M_higgstop_one_btag->Write();
      if(notop && onebtag)     M_higgsnotop_one_btag->Write();
    }
  }

}
