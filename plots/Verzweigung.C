#include "TH1.h"

using namespace std;

void Verzweigung()
{
  //TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/Pre/rootfile/test2";
TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/TPrime";
 TFile * infile1 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime700T_TPrimeToHT.root");
TFile * infile2 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime700T_TPrimeToZT.root");
TFile * infile3 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime700T_TPrimeToWB.root");
//TFile * infile4 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.other.root");
//TFile * infile5 = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar.root");
// TString hist = "lepton_eff/MuonMatch";
TString hist = "eff_chi2cut/MuonMatch";
 TString xaxis = "";
  bool bhs=false;
  bool bht = false;
  bool bHZW =true;

 TH1F* M_higgsnotop1 = (TH1F*)infile1->Get(hist);
 double bin1 = M_higgsnotop1->GetBinContent(1);
 double bin2 = M_higgsnotop1->GetBinContent(2);
 double bin3 = M_higgsnotop1->GetBinContent(3);
 double gesamt = bin1 + bin2 + bin3;
 TH1D* eins = new TH1D("HT","",3,0,3);
 eins ->Fill("Muon aus Top",bin1/gesamt);
 eins ->Fill("Muon aus TPrime",bin2/gesamt);
 eins ->Fill("Muon sonst",bin3/gesamt);
 // M_higgsnotop1->Rebin(2);
 // M_higgsnotop1->SetLineColor(416);

 M_higgsnotop1->SetLineWidth(2);
 M_higgsnotop1->SetTitle("");
  gStyle->SetOptStat(0);
 TH1F* M_higgsnotop2 = (TH1F*)infile2->Get(hist);
 bin1 = M_higgsnotop2->GetBinContent(1);
 bin2 = M_higgsnotop2->GetBinContent(2);
 bin3 = M_higgsnotop2->GetBinContent(3);
 gesamt = bin1 + bin2 + bin3;
 TH1D* zwei = new TH1D("ZT","",3,0,3);
 zwei ->Fill("Muon aus Top",bin1/gesamt);
 zwei ->Fill("Muon aus TPrime",bin2/gesamt);
 zwei ->Fill("Muon sonst",bin3/gesamt);
  // M_higgsnotop2->Rebin(2);

 //M_higgsnotop2->SetLineColor(420);
M_higgsnotop2->SetLineWidth(2);

 TH1F* M_higgsnotop3 = (TH1F*)infile3->Get(hist);
 bin1 = M_higgsnotop3->GetBinContent(1);
 bin2 = M_higgsnotop3->GetBinContent(2);
 bin3 = M_higgsnotop3->GetBinContent(3);
 gesamt = bin1 + bin2 + bin3;
 TH1D* drei = new TH1D("WB","",3,0,3);
 drei ->Fill("Muon aus Top",bin1/gesamt);
 drei ->Fill("Muon aus TPrime",bin2/gesamt);
 drei ->Fill("Muon sonst",bin3/gesamt);

 zwei->SetLineColor(416);
 eins->SetLineColor(600);
 drei->SetLineColor(632);


  // M_higgsnotop3->Rebin(2);
 
  //M_higgsnotop3->SetLineColor(414);
M_higgsnotop3->SetLineWidth(2);

 if(bHZW){
  M_higgsnotop2->SetLineColor(416);
 M_higgsnotop1->SetLineColor(600);
 M_higgsnotop3->SetLineColor(632);
 }else{
   if(bht){
     //HT
     M_higgsnotop1->SetLineColor(600);
     M_higgsnotop2->SetLineColor(432);
     M_higgsnotop3->SetLineColor(603);
   }else{
     //Zt
     M_higgsnotop3->SetLineColor(414);
     M_higgsnotop2->SetLineColor(420);
     M_higgsnotop1->SetLineColor(416);
   }

 }



// TH1F* other = (TH1F*)infile4->Get(hist);
// other->Rebin(2);
// other->SetFillColor(920);
// other->SetLineColor(920);

  

// TH1F* ttbar = (TH1F*)infile5->Get(hist);
//  ttbar->Rebin(2);
//  ttbar->SetFillColor(625);
//  ttbar->SetLineColor(625);



// THStack *hs = new THStack("hs","");
//  hs ->Add(other);
//  hs ->Add(ttbar);

 TCanvas* c2 = new TCanvas("c2", " ");

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
eins->Draw("Hist");
 // hs->Draw("Hist SAME");
eins->GetXaxis()->SetTitle(xaxis);
eins->GetXaxis()->SetTitleSize(0.04);
eins->GetYaxis()->SetTitle("Events");
 eins ->SetMaximum(0.8);
 // M_higgsnotop3->SetAxisRange(0, 150);
 // M_higgsnotop3-> SetMaximum(1.4);
eins->Draw("Hist SAME");
//}


 drei->Draw("Hist SAME");
zwei->Draw("Hist SAME");

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
