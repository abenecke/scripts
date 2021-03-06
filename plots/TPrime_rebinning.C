#include "TH1.h"

using namespace std;

void TPrime_rebinning()
{
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/TPrime";
  TFile * infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime700T_TPrimeToHT.root");
  TFile * infile2 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime900T_TPrimeToHT.root");
  TFile * infile3 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2500ToTPrime1200T_TPrimeToHT.root");
  TFile * infile8 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2500ToTPrime1500T_TPrimeToHT.root");
 //  TFile * infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar_right.root");
  TFile * infile4 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.other.root");
  TFile * infile5 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar.root");
  TFile * infile6 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.WJets.root");
  // TFile * infile7 = new TFile(directory+"/uhh2.AnalysisModuleRunner.Data.Data.root");

  // TString hist1 = "higgs_top_chi2min_chi2cut/M_ZPrime_rec";
  // TString hist2 = "higgs_notop_chi2min_chi2cut/M_ZPrime_rec";
  // TString hist3 = "zw_top_chi2min_chi2cut/M_ZPrime_rec";
 // TString hist = "zw_notop_chi2min_chi2cut/M_ZPrime_rec";
  
  //TString hist = "higgs_top_chi2min_chi2cut/M_ZPrime_rec";
  //TString hist = "muon_chi2cut/pt";
  //TString hist = "tagger_chi2cut/reco_mass_W";
  TString hist = "higgs_notop_chi2min_chi2cut/M_TPrime_rec3";
  
  TString xaxis = "";
  bool bhs=false;
  bool bht = true;
  bool bHZW =false;
  
  TH1F* M_higgsnotop1 = (TH1F*)infile1->Get(hist);
  M_higgsnotop1->Rebin(2);

  TH1F* M_higgsnotop4 = (TH1F*)infile8->Get(hist);
  M_higgsnotop4->Rebin(2);
 // Double_t rebin[]={0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510};
// TH1F* M_neu1 =  (TH1F*) M_higgsnotop1 ->Rebin(,"M_zwnotop",zwnotop); 

//  for (int i=1; i<M_higgsnotop1->GetNbinsX()+1; ++i){
//   cout << M_higgsnotop1->GetXaxis()->GetBinLowEdge(i) << ", ";
//  }


 // M_higgsnotop1->SetLineColor(416);

 // M_higgsnotop1->SetLineWidth(2);
 // M_higgsnotop1->SetTitle("");
  gStyle->SetOptStat(0);
 TH1F* M_higgsnotop2 = (TH1F*)infile2->Get(hist);
  M_higgsnotop2->Rebin(2);

// //  M_higgsnotop2->SetLineColor(420);
// // M_higgsnotop2->SetLineWidth(2);

 TH1F* M_higgsnotop3 = (TH1F*)infile3->Get(hist);
  M_higgsnotop3->Rebin(2);
 
//   M_higgsnotop3->SetLineColor(414);
// M_higgsnotop3->SetLineWidth(2);

//  if(bHZW){
//   M_higgsnotop1->SetLineColor(416);
//  M_higgsnotop2->SetLineColor(600);
//  M_higgsnotop3->SetLineColor(632);
//  }else{
//    if(bht){
//      //HT
//      M_higgsnotop1->SetLineColor(600);
//      M_higgsnotop2->SetLineColor(432);
//      M_higgsnotop3->SetLineColor(603);
//    }else{
//      //Zt
//      M_higgsnotop3->SetLineColor(414);
//      M_higgsnotop2->SetLineColor(420);
//      M_higgsnotop1->SetLineColor(416);
//    }

//  }



  TH1F* other = (TH1F*)infile4->Get(hist);
  other->Rebin(2);
  other->SetFillColor(920);
  other->SetLineColor(920);
  
  
  
  TH1F* ttbar = (TH1F*)infile5->Get(hist);
  ttbar->Rebin(2);
  ttbar->SetFillColor(625);
  ttbar->SetLineColor(625);
  TH1F* wjets = (TH1F*)infile6->Get(hist);
  wjets->Rebin(2);
  wjets->SetFillColor(791);
  wjets->SetLineColor(791);

  // TH1F* data = (TH1F*)infile7->Get(hist);
  // data->Rebin(2);
 
  
  TFile *f1= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime700T_TPrimeToHT.root","RECREATE");
  M_higgsnotop1 ->Write();
  f1->Close();
  
  TFile *f2= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime900T_TPrimeToHT.root","RECREATE");
  M_higgsnotop2 ->Write();
  f2->Close();
  TFile *f3= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2500ToTPrime1200T_TPrimeToHT.root","RECREATE");
  M_higgsnotop3 ->Write();
  f3->Close();

  TFile *f8= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.MC_ZPrime2500ToTPrime1500T_TPrimeToHT.root","RECREATE");
  M_higgsnotop4 ->Write();
  f8->Close();
  
  // TFile *f1= new TFile(directory + "/uhh2.AnalysisModuleRunner.MC.TTbar_right_rebinned.root","RECREATE");
  //  M_higgsnotop1 ->Write();
  //  f1->Close();
  
  TFile *f4= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.other.root","RECREATE");
  other ->Write();
  f4->Close();
  TFile *f5= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.TTbar.root","RECREATE");
  ttbar ->Write();
  f5->Close();
  
  TFile *f6= new TFile(directory + "/rebinned/uhh2.AnalysisModuleRunner.MC.WJets.root","RECREATE");
  wjets ->Write();
  f6->Close();
  
  // TFile *f7= new TFile(directory + "rebinned/uhh2.AnalysisModuleRunner.Data.Data.root","RECREATE");
  // data ->Write();
  // f7->Close();
  
  // THStack *hs = new THStack("hs","");
  //  hs ->Add(other);
  //  hs ->Add(ttbar);

  //  TCanvas* c2 = new TCanvas("c2", " ");
  
  //  if(bhs){
  // hs->Draw("Hist");
  // hs->GetXaxis()->SetTitle(xaxis);
  // hs->GetXaxis()->SetTitleSize(0.04);
  // hs->GetYaxis()->SetTitle("Events");
  // hs->SetMinimum(1);
  // hs->SetMaximum(10000);
  // //hs->SetAxisRange(0, 150);
  
  // //hs->GetYaxis()->SetRangeUser(0, 10^3);
  //  M_higgsnotop3->Draw("Hist SAME");
  //  }else{
  // M_higgsnotop3->Draw("Hist");
  //  hs->Draw("Hist SAME");
  // M_higgsnotop3->GetXaxis()->SetTitle(xaxis);
  // M_higgsnotop3->GetXaxis()->SetTitleSize(0.04);
  // M_higgsnotop3->GetYaxis()->SetTitle("Events");
  //  M_higgsnotop3->SetAxisRange(0, 150);
  //  M_higgsnotop3-> SetMaximum(1.4);
  // M_higgsnotop3->Draw("Hist SAME");
  //  }
  
  
  //  M_higgsnotop1->Draw("Hist SAME");
  //  M_higgsnotop2->Draw("Hist SAME");
  
  // hs->Draw("Hist SAME");
  // M_higgsnotop3->GetXaxis()->SetTitle(xaxis);
  // M_higgsnotop3->GetXaxis()->SetTitleSize(0.04);
  // M_higgsnotop3->GetYaxis()->SetTitle("Events");
  
  
  // TLegend * legbg = new TLegend(0.5,0.6,0.89,0.89);
  // legbg -> AddEntry(M_higgsnotop1,"M_{Z'}=1.5TeV (Zt)");
  // legbg -> AddEntry(M_higgsnotop2,"M_{Z'}=1.5TeV (Ht)");
  // legbg -> AddEntry(M_higgsnotop3,"M_{Z'}=1.5TeV (Wb)");
  // legbg -> AddEntry(ttbar,"t#bar t");
  // legbg -> AddEntry(other,"other");
  // legbg ->SetBorderSize(0); 
  // legbg->SetTextSize(0.05); 
  // legbg ->Draw();
  
  // c2->SetLogy();
  
}
