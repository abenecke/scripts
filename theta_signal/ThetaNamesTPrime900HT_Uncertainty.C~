#include "TH1.h"

using namespace std;

void ThetaNamesTPrime1200HT_Uncertainty()
{
  const bool top=true;
  const bool notop=true;
  const int nproc=9;

  TString process[nproc] = {"TTbar", "WJets","QCD","ST","DYJetsToLL","MC_ZPrime1500ToTPrime1200T_TPrimeToHT","MC_ZPrime2000ToTPrime1200T_TPrimeToHT","MC_ZPrime2500ToTPrime1200T_TPrimeToHT","DATA"};
  


  const int Nsyst = 11;
  TString systname[Nsyst]={"jec","jer","pu","btag","sub","muf","mur","higgs","zw","eff","default"};
  // TString systshift = "up";
  // TString systshift2 = "plus";
  // if(systshift=="down") systshift2 = "minus";
 TString outfilename = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/thesis/theta_histograms_MZPrime";
 outfilename+=".root";
 std::cout<< outfilename <<std::endl;
 TFile *outfile = new TFile(outfilename,"RECREATE");

 for(int m=0; m<2; m++){
    TString systshift = "down";
    TString systshift2 = "minus";
    if(m==0){
      systshift = "up";
      systshift2 = "plus";
    }

    cout << "*****************************SYSTEMATIC VARIATION IN DIRECTION:   " << systshift << endl;
  
  for(int j=0; j<Nsyst; ++j){
    TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/thesis/";
    if(systname[j]!="default"){
      directory += systname[j];
      directory +="_";
      directory += systshift;
    }
    if (systname[j]=="default")directory += "none";
    std::cout<<"////////////////////////////////////////////" +systname[j]+"////////////////////////////////////////////" <<std::endl;

    // TString outfilename = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/thesis/theta_histograms_MZPrime";
    // if(systname[j]!="default"){
    //   outfilename += systname[j];
    //   outfilename +="_";
    //   outfilename +=systshift;
    // }

    // outfilename+=".root";
    // std::cout<< outfilename <<std::endl;
    // TFile *outfile = new TFile(outfilename,"RECREATE");
     
    int nmax = nproc;
    if(systname[j]!="default") nmax--;
    if(systname[j] == "default" && m == 1){
    	cout << "Don't take nominal histos twice, omit." << endl;
    	continue; //take nominal histos only once
    }

    for(int i=0; i<nmax; ++i){
       
      TString mcdata = "MC";
      std::cout << process[i] <<endl;
       
      if(process[i]=="DATA") mcdata = "DATA";
       
      std::cout<< directory+"/."+mcdata+"."+process[i]+".root" << std::endl;
      TFile * infile = new TFile(directory+"/uhh2.AnalysisModuleRunner."+mcdata+"."+process[i]+".root");
      infile->cd();
       
      std::cout << "   got the file" <<endl;
 
      //600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2160, 2220, 2280, 2340, 2400, 2460, 2520, 2580, 2640, 2700, 2760, 2820, 2880, 2940
       
      TH1F* M_higgstop_old = (TH1F*)infile->Get("higgs_top_chi2min_btag1/M_ZPrime_rec");
      Double_t higgtop[2]={600,3000};
      TH1F* M_higgstop =  (TH1F*) M_higgstop_old->Rebin(1,"M_higgstop",higgtop);
      
      ////////////////////////////////////////////////////////////////////////////////////////
         
      // TH1F* M_higgsnotop = (TH1F*)infile->Get("higgs_notop_chi2min_chi2cut/M_ZPrime_rec");
      // M_higgsnotop ->Rebin(4);
      TH1F* M_higgsnotop_old = (TH1F*)infile->Get("higgs_notop_chi2min_btag1/M_ZPrime_rec");
      //  Double_t higgsnotop[9]= { 600, 840, 1080, 1320, 1560, 1800, 2040, 2280, 2760};//btag
       Double_t higgsnotop[27]={600,660,720,780,840,900,960,1020,1080,1140,1200,1260,1320,1380,1440,1500,1560,1620,1680,1740,1800,1860,1920,1980,2220,2580,3000}; //chi2cut
      TH1F* M_higgsnotop =  (TH1F*) M_higgsnotop_old->Rebin(26,"M_higgsnotop",higgsnotop);
     
      
      ////////////////////////////////////////////////////////////////////////////////////////
     
      // TH1F* M_zwtop = (TH1F*)infile->Get("zw_top_chi2min_btag/M_ZPrime_rec");
      // M_zwtop->Rebin(2);
       TH1F* M_zwtop_old = (TH1F*)infile->Get("zw_top_chi2min_btag1/M_ZPrime_rec");
       Double_t zwtop[19]={600, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2640, 2760, 2880}; //chi2cut
       // Double_t zwtop[19]= {600, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2640, 2760, 2880};//btag
      TH1F* M_zwtop =  (TH1F*) M_zwtop_old ->Rebin(18,"M_zwtop",zwtop);
      
      
      ////////////////////////////////////////////////////////////////////////////////////////
          
       // TH1F* M_zwnotop = (TH1F*)infile->Get("zw_notop_chi2min_chi2cut/M_ZPrime_rec");
       // M_zwnotop ->Rebin(4);
       TH1F* M_zwnotop_old = (TH1F*)infile->Get("zw_notop_chi2min_btag1/M_ZPrime_rec");
        Double_t zwnotop[18]={600, 720, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2880}; //chi2cut
       //  Double_t zwnotop[9]={ 600,840, 1080, 1320, 1560, 1800, 2040, 2280,2760}; //btag
      TH1F* M_zwnotop =  (TH1F*)  M_zwnotop_old->Rebin(17,"M_zwnotop",zwnotop);   
    

       // TH1F* hist = (TH1F*)infile->Get("zw_top_chi2min_btag50/M_ZPrime_rec");
       // // hist->Rebin(4);
       // for (int i=1; i<hist->GetNbinsX()+1; ++i){
       // 	 cout << hist->GetXaxis()->GetBinLowEdge(i) << ", ";}
       
     
      std::cout << "   got the histos" <<endl;
         
      if(systname[j]!="default"){
	cout <<"Set name for not default"<< endl;
	M_higgstop->SetName("MZPrime_TPrime1200HT_higgstop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_higgsnotop->SetName("MZPrime_TPrime1200HT_higgsnotop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_zwtop->SetName("MZPrime_TPrime1200HT_zwtop__"+process[i]+"__"+systname[j]+"__"+systshift2);
	M_zwnotop->SetName("MZPrime_TPrime1200HT_zwnotop__"+process[i]+"__"+systname[j]+"__"+systshift2);
 
      }
      else{
	cout <<"Set name for default"<< endl;
	M_higgstop ->SetName("MZPrime_TPrime1200HT_higgstop__"+process[i]);
	M_higgsnotop->SetName("MZPrime_TPrime1200HT_higgsnotop__"+process[i]);
	M_zwtop->SetName("MZPrime_TPrime1200HT_zwtop__"+process[i]);
	M_zwnotop->SetName("MZPrime_TPrime1200HT_zwnotop__"+process[i]);
	 
      }

      outfile->cd();
      cout<< "Write histos in file "<<endl;
      if(top)     M_higgstop->Write();
      if(notop)     M_higgsnotop->Write();
      if(top)    M_zwtop->Write();
      if(notop)    M_zwnotop->Write();
    }
  }
 }
}
