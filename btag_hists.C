#include "TH1.h"

using namespace std;

void btag_hists()
{
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/elec_channel_30GeV";
  TFile * infile = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbarAll.root");


  // TString hist1 = "higgs_top_chi2min_chi2cut/M_ZPrime_rec";
  // TString hist2 = "higgs_notop_chi2min_chi2cut/M_ZPrime_rec";
  // TString hist3 = "zw_top_chi2min_chi2cut/M_ZPrime_rec";
  // TString hist = "zw_notop_chi2min_chi2cut/M_ZPrime_rec";

  TString hist0 = "BTagMCEfficiencyHistsAK4/BTagMCEffFlavBPassing";
  TString hist1 = "BTagMCEfficiencyHistsAK4/BTagMCEffFlavBTotal";
  TString hist2 = "BTagMCEfficiencyHistsAK4/BTagMCEffFlavCPassing";
  TString hist3 = "BTagMCEfficiencyHistsAK4/BTagMCEffFlavCTotal";
  TString hist4 = "BTagMCEfficiencyHistsAK4/BTagMCEffFlavUDSGPassing";
  TString hist5 = "BTagMCEfficiencyHistsAK4/BTagMCEffFlavUDSGTotal";


  TString xaxis = "";
  

  TH1F* ttbar0 = (TH1F*)infile->Get(hist0);
  TH1F* ttbar1 = (TH1F*)infile->Get(hist1);
  TH1F* ttbar2 = (TH1F*)infile->Get(hist2);
  TH1F* ttbar3 = (TH1F*)infile->Get(hist3);
  TH1F* ttbar4 = (TH1F*)infile->Get(hist4);
  TH1F* ttbar5 = (TH1F*)infile->Get(hist5);


 
  TFile *f5= new TFile(directory + "/BTagMCEfficiencyHists.root","RECREATE");
  ttbar0 ->Write();
  ttbar1 ->Write();
  ttbar2 ->Write();
  ttbar3 ->Write();
  ttbar4 ->Write();
  ttbar5 ->Write();
  f5->Close();

 
}
