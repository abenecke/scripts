#include "TH1.h"

using namespace std;

void rebinning()
{
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/one_subjet_btag";



  // TString hist_name = "muon_twodcut/pt";
  // Double_t bins[24]={0,52,73,93,113,133,153,173,193,213,233,253,273,293,313,333,353,373,393,413,433,453,473,493};

  TString hist_name = "topjet_twodcut/pt_1";
  Double_t bins[35]={0,249,269,289,309,329,349,369,389,409,429,449,469,489,509,529,549,569,589,609,629,649,669,689,709,729,749,769,789,809,829,849,869,889,900};
  ///////////////////////////////////////////////////  HT 1500 1200  //////////////////////////////////////////////////////////////
  TString name = "MC.MC_ZPrime15001200HT.root";
  TFile * infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  TH1F* hist = (TH1F*)infile1->Get(hist_name);
  TH1* rebinned = hist->Rebin(34,"rebinned",bins);
 
  TFile *f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();

  ///////////////////////////////////////////////////  HT 2000 1200  //////////////////////////////////////////////////////////////
  name = "MC.MC_ZPrime20001200HT.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();

  ///////////////////////////////////////////////////  HT 2500 1200  //////////////////////////////////////////////////////////////
  name = "MC.MC_ZPrime25001200HT.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();

  ///////////////////////////////////////////////////  other  //////////////////////////////////////////////////////////////
  name = "MC.other.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();

  ///////////////////////////////////////////////////  QCD  //////////////////////////////////////////////////////////////
  name = "MC.QCD.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();

  //////////////////////////////////////////////////  ttbar  //////////////////////////////////////////////////////////////
  name = "MC.TTbar.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();

  //////////////////////////////////////////////////  WJets  //////////////////////////////////////////////////////////////
  name = "MC.MC_WJets.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();
  
  //////////////////////////////////////////////////  WJets  //////////////////////////////////////////////////////////////
  name = "Data.Data.root";
  infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner."+name);
  hist = (TH1F*)infile1->Get(hist_name);
  rebinned = hist->Rebin(34,"rebinned",bins);
 
  f1= new TFile(directory + "/rebin/uhh2.AnalysisModuleRunner."+name,"RECREATE");
  rebinned ->Write();
  f1->Close();
  
}
