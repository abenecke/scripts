#include "TH1.h"
#include <fstream>

using namespace std;

void fit_gaus_exp()
{
  //setOptFit( pcev (default = 0111)) Probability; Chisquare/Number of degrees of freedom; errors ;values of parameters 
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);

  //All files are read in
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/eff/right/test";
  TFile * Data_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.Data.Data.root", "READ");
  TFile * TTbar_matched_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * TTbar_unmatched_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar_wrong.root", "READ");
  TFile * WJets_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.WJets.root", "READ");
  TFile * other_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.other.root", "READ");
  TFile * QCD_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");

  //Get all hist from the string hist_name
  TString hist_name = "tagger_chi2cut/reco_mass_W";
  TH1F* data = (TH1F*)Data_f->Get(hist_name);
  TH1F* TTbar_matched = (TH1F*)TTbar_matched_f->Get(hist_name);
  TH1F* TTbar_unmatched = (TH1F*)TTbar_unmatched_f->Get(hist_name);
  TH1F* WJets = (TH1F*)WJets_f->Get(hist_name);
  TH1F* other = (TH1F*)other_f->Get(hist_name);
  TH1F* QCD = (TH1F*)QCD_f->Get(hist_name);

  TString folder ="gaus_exp/";
  // -------------------
  //Background Fit
  // -------------------
  TCanvas *background_c = new TCanvas("background_c","background fit",10,10,700,900);
  background_c->Clear();
  background_c->cd();

  TTbar_unmatched->SetMarkerStyle(20);
  TTbar_unmatched->SetMarkerSize(1.);
  TTbar_unmatched->SetLineColor(kBlue+1);
  TTbar_unmatched->SetMarkerColor(kBlue+1);
  TTbar_unmatched->Draw("E1");

  TH1D* back = (TH1D*)TTbar_unmatched->Clone();
  back->Add(other);
  back->Add(WJets);
  back->Add(QCD);

  /////////////////////////   Fit function (Background)  ////////////////////////
  TF1* background_fit = new TF1("background_fit", "[0]*exp(-(x-[1])^2/(2*[2]^2)) + [3]* exp([4]*x)", 4, 182);
  background_fit->SetParameter(0, 1.293);
  background_fit->SetParameter(1, 87.92);
  background_fit->SetParameter(2, 11.57);
  background_fit->SetParameter(3, 1.322);
  background_fit->SetParameter(4, -0.03924);
 
  background_fit->SetLineColor(kOrange+2);
  background_fit->SetLineStyle(kDashed);

  back->Draw("PZ");
  back->Fit(background_fit, "RIEW");
  background_fit->DrawClone("same");
 
  background_c->Print(folder +"FIXED_background_fit.eps");
  
  // -------------------
  // Signal fit
  // -------------------
  
  TCanvas *signal_c = new TCanvas("signal_c","signal fit",10,10,700,900);
  signal_c->Clear();
  signal_c->cd();
  
  TTbar_matched->SetMarkerStyle(24);
  TTbar_matched->SetMarkerSize(1.);
  TTbar_matched->SetLineColor(kRed);
  TTbar_matched->SetMarkerColor(kRed);
  TTbar_matched->Draw("PZ");

  /////////////////////////   Fit function (Signal)  ////////////////////////
  TF1 *signal_fit = new TF1("signal_fit","[0]*exp(-(x-[1])^2/(2*[2]^2))", 4,182);
  signal_fit->SetParameter(0, 40.8);
  signal_fit->SetParameter(1, 92.77);
  signal_fit->SetParameter(2, 11.05);
  signal_fit->SetLineStyle(kDashed);
  signal_fit->SetLineColor(kGreen+3);

  TTbar_matched->Fit(signal_fit,"RIEW");
  signal_fit->DrawClone("same");
 
  signal_c->Print(folder +"FIXED_signal_fit.eps");
  // ------------------------
  // Signal + Background fit
  // ------------------------
  TCanvas *signal_background_c = new TCanvas("signal_background_c","signal+background fit",10,10,700,900);
  signal_background_c->Clear();
  signal_background_c->cd();

  TH1D* all = (TH1D*)TTbar_matched->Clone();
  all->Add(back);
  all->SetMarkerStyle(24);
  all->SetMarkerColor(kRed+1);
  all->SetLineColor(kRed+1);
  all->Draw("PZ");



  /////////////////////////   Fit function (Signal+background)  ////////////////////////
  TF1 *signal_background_fit = new TF1("signal_background_fit","signal_fit + background_fit", 4,182);

  //Signal
  signal_background_fit->SetParameter(0, signal_fit->GetParameter(0));
  signal_background_fit->SetParameter(1, signal_fit->GetParameter(1));
  signal_background_fit->SetParameter(2, signal_fit->GetParameter(2));
  //Background
  signal_background_fit->FixParameter(3, background_fit->GetParameter(0));
  signal_background_fit->FixParameter(4, background_fit->GetParameter(1));
  signal_background_fit->FixParameter(5, background_fit->GetParameter(2));
  signal_background_fit->FixParameter(6, background_fit->GetParameter(3));
  signal_background_fit->FixParameter(7, background_fit->GetParameter(4));
 

  signal_background_fit->SetLineColor(kGreen+3);
  all->Fit(signal_background_fit, "RIEW");
  signal_background_fit->DrawClone("same");

  //show also background with fit
  TF1* f = (TF1*) back->GetListOfFunctions()->At(0);
  f->SetParameter(0,0);
  f->SetParameter(1,0);
  f->SetParameter(2,0);
  f->SetParameter(3,0);
  f->SetParameter(4,0);
  f->SetLineWidth(0);
  f->SetLineColor(kBlack);
  TH1F *back2 = (TH1F*) back->Clone();
  back2->SetStats(0);
  back2->Draw("same");
  TF1* bc = (TF1*) background_fit->Clone();
  bc->SetParameter(0, signal_background_fit->GetParameter(3));
  bc->SetParameter(1, signal_background_fit->GetParameter(4));  
  bc->SetParameter(2, signal_background_fit->GetParameter(5));
  bc->SetParameter(3, signal_background_fit->GetParameter(6));
  bc->SetParameter(4, signal_background_fit->GetParameter(7));
  bc->SetLineColor(kOrange+2);
  bc->SetLineStyle(kDashed);
  bc->DrawClone("same");

  signal_background_c->Print(folder +"FIXED_signal_background_fit.eps");
  // ------------------------
  //        Data
  // ------------------------

  TCanvas *data_c = new TCanvas("data_c","data",10,10,700,900);
  data_c->Clear();
  data_c->cd();
  data->SetMarkerStyle(20);
  data->SetMarkerSize(1.);
  data->SetLineColor(kBlack);
  data->SetMarkerColor(kBlack);
  data->Draw("PZ");

  /////////////////////////   Fit function (Data)  ////////////////////////
  TF1* data_fit = new TF1("data_fit","signal_fit+background_fit" , 4, 182);

  Double_t sc = data->Integral() / all->Integral();
  //signal
  data_fit->SetParameter(0, signal_background_fit->GetParameter(0));
  data_fit->SetParameter(1, signal_background_fit->GetParameter(1));
  data_fit->SetParameter(2, signal_background_fit->GetParameter(2));
  //background
  data_fit->FixParameter(3, sc*signal_background_fit->GetParameter(3));   
  data_fit->FixParameter(4, sc*signal_background_fit->GetParameter(4));
  data_fit->FixParameter(5, sc*signal_background_fit->GetParameter(5));
  data_fit->FixParameter(6, sc*signal_background_fit->GetParameter(6));   
  data_fit->FixParameter(7, signal_background_fit->GetParameter(7));

  data_fit->SetLineColor(kViolet);
  data_fit->SetLineStyle(kSolid);

 
  data->Fit(data_fit, "IEW");
  data_fit->Draw("same");


  //show also background with fit

  back2->Draw("same");
  bc = (TF1*) background_fit->Clone();
  bc->SetParameter(0, data_fit->GetParameter(3));
  bc->SetParameter(1, data_fit->GetParameter(4));  
  bc->SetParameter(2, data_fit->GetParameter(5));
  bc->SetParameter(3, data_fit->GetParameter(6));
  bc->SetParameter(4, data_fit->GetParameter(7));
 
  bc->SetLineColor(kOrange+2);
  bc->SetLineStyle(kDashed);
  bc->DrawClone("same");
  data_c->Print(folder +"FIXED_data_fit.eps");

  // ---------------------------------------
  //        Calculate Efficency
  // ---------------------------------------
  TCanvas *MC_Eff_c = new TCanvas("MC_Eff_c","MC Eff curve",10,10,700,900);
  MC_Eff_c->Clear();
  MC_Eff_c->cd();


  TF1 *MC_Eff_f =new TF1("MC_Eff_f","signal_background_fit - background_fit", 4,182);
   //signal
  MC_Eff_f->SetParameter(0, signal_background_fit->GetParameter(0));
  MC_Eff_f->SetParameter(1, signal_background_fit->GetParameter(1));
  MC_Eff_f->SetParameter(2, signal_background_fit->GetParameter(2));
  //background
  MC_Eff_f->SetParameter(3, signal_background_fit->GetParameter(3));
  MC_Eff_f->SetParameter(4, signal_background_fit->GetParameter(4));
  MC_Eff_f->SetParameter(5, signal_background_fit->GetParameter(5));
  MC_Eff_f->SetParameter(6, signal_background_fit->GetParameter(6));
  MC_Eff_f->SetParameter(7, signal_background_fit->GetParameter(7));

  //poly background only
  MC_Eff_f->SetParameter(8, background_fit->GetParameter(0));
  MC_Eff_f->SetParameter(9,background_fit->GetParameter(1));
  MC_Eff_f->SetParameter(10,background_fit->GetParameter(2));
  MC_Eff_f->SetParameter(11,background_fit->GetParameter(3));
  MC_Eff_f->SetParameter(12,background_fit->GetParameter(4));


  MC_Eff_f->Draw();

  TF1 *Data_Eff_f =new TF1("Data_Eff_f","data_fit - background_fit", 4,182);
  //signal
  Data_Eff_f->SetParameter(0, data_fit->GetParameter(0));
  Data_Eff_f->SetParameter(1, data_fit->GetParameter(1));
  Data_Eff_f->SetParameter(2, data_fit->GetParameter(2));
  //background
  Data_Eff_f->SetParameter(3, data_fit->GetParameter(3));
  Data_Eff_f->SetParameter(4, data_fit->GetParameter(4));
  Data_Eff_f->SetParameter(5, data_fit->GetParameter(5));
  Data_Eff_f->SetParameter(6, data_fit->GetParameter(6));
  Data_Eff_f->SetParameter(7, data_fit->GetParameter(7));

  // background only
  Data_Eff_f->SetParameter(8, background_fit->GetParameter(0));
  Data_Eff_f->SetParameter(9,background_fit->GetParameter(1));
  Data_Eff_f->SetParameter(10,background_fit->GetParameter(2));
  Data_Eff_f->SetParameter(11,background_fit->GetParameter(3));
  Data_Eff_f->SetParameter(12,background_fit->GetParameter(4));


  Data_Eff_f->SetLineColor(kBlue+2);
  Data_Eff_f->SetLineStyle(kDashed);
  Data_Eff_f->Draw("same");




  Double_t num_MC_before = MC_Eff_f->Integral(4,182);
  cout<<"MC number before tagger:   "<< num_MC_before <<endl;
  Double_t num_Data_before = Data_Eff_f->Integral(4,182);
  cout<<"Data number before tagger:   "<< num_Data_before <<endl;

  ofstream myfile;
  myfile.open (folder+"numbers.txt");
  myfile << "MC number before tagger:   "<< num_MC_before <<endl;
  myfile<<"Data number before tagger:   "<< num_Data_before <<endl;
  myfile.close();

}//End of function
