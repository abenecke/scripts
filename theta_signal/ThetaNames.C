#include "TH1.h"

using namespace std;

void ThetaNames()
{

  const int nproc=29;

  TString process[nproc] = {"TTbar", "WJets","QCD","ST","DYJetsToLL","MC_ZPrime1500ToTPrime1200T_TPrimeToHT", "MC_ZPrime1500ToTPrime1200T_TPrimeToWB", "MC_ZPrime1500ToTPrime1200T_TPrimeToZT","MC_ZPrime1500ToTPrime700T_TPrimeToHT","MC_ZPrime1500ToTPrime700T_TPrimeToWB","MC_ZPrime1500ToTPrime700T_TPrimeToZT","MC_ZPrime1500ToTPrime900T_TPrimeToHT","MC_ZPrime1500ToTPrime900T_TPrimeToWB","MC_ZPrime1500ToTPrime900T_TPrimeToZT","MC_ZPrime2000ToTPrime1200T_TPrimeToHT","MC_ZPrime2000ToTPrime1200T_TPrimeToWB","MC_ZPrime2000ToTPrime1200T_TPrimeToZT","MC_ZPrime2000ToTPrime1500T_TPrimeToHT","MC_ZPrime2000ToTPrime1500T_TPrimeToWB","MC_ZPrime2000ToTPrime1500T_TPrimeToZT","MC_ZPrime2000ToTPrime900T_TPrimeToHT","MC_ZPrime2000ToTPrime900T_TPrimeToWB","MC_ZPrime2000ToTPrime900T_TPrimeToZT","MC_ZPrime2500ToTPrime1200T_TPrimeToHT","MC_ZPrime2500ToTPrime1200T_TPrimeToWB","MC_ZPrime2500ToTPrime1200T_TPrimeToZT","MC_ZPrime2500ToTPrime1500T_TPrimeToHT","MC_ZPrime2500ToTPrime1500T_TPrimeToWB","MC_ZPrime2500ToTPrime1500T_TPrimeToZT"};
  


  const int Nsyst = 1;
  TString systname[Nsyst]={"default"};
  TString systshift = "Up";
  TString systshift2 = "plus";
  if(systshift=="Down") systshift2 = "minus";

  
  for(int j=0; j<Nsyst; ++j){
     TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/chi2cut";
      if(systname[j]!="default"){
         directory += systname[j];
         directory +="_";
         directory += systshift;
     }
     std::cout<< directory <<std::endl;

     TString outfilename = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/chi2cut/theta_histograms_MZPrime_all";
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
       
       TH1F* pT_Tau = (TH1F*)infile->Get("chi2min_chi2cut/M_ZPrime_rec");
              
       std::cout << "   got the histos" <<endl;
         
       if(systname[j]!="default"){
          pT_Tau->SetName("MZPrime__"+process[i]+"__"+systname[j]+"__"+systshift2);
	 
       }
       else{
          pT_Tau->SetName("MZPrime__"+process[i]);
	 
       }

       outfile->cd();
       pT_Tau->Write();
           
     }
   }
}
