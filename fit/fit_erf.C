#include "TH1.h"
#include <fstream>

using namespace std;

void fit_erf()
{
  
  bool b_error=true;
  TString unc_name = ""; // "jersmear_up" , "jersmear_down" ,"jecsmear_up" , "jecsmear_down" , "none"
  TString mistag_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/QCD/mass/hists/";
  TString folder ="erf/lowpt_";
  // TString folder ="~/ownCloud/masterarbeit/tex/plots/efficiency/master_";
  TString unc_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/efficiency/hists";


  //setOptFit( pcev (default = 0111)) Probability; Chisquare/Number of degrees of freedom; errors ;values of parameters 
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);

  //All files are read in
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/efficiency_lowpt200-400"+unc_name;
  TString bkgfolder = "";
  TFile * data_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.Data.Data.root", "READ");
  TFile * TTbar_matched_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * TTbar_unmatched_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.TTbar_wrong.root", "READ");
  TFile * WJets_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.WJets.root", "READ");
  TFile * other_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.other.root", "READ");
  TFile * QCD_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");

  //Get all hist from the string hist_name
  TString hist_name = "tagger_chi2cut/reco_mass_W";
  TH1F* data = (TH1F*)data_f->Get(hist_name);
  TH1F* TTbar_matched = (TH1F*)TTbar_matched_f->Get(hist_name);
  TH1F* TTbar_unmatched = (TH1F*)TTbar_unmatched_f->Get(hist_name);
  TH1F* WJets = (TH1F*)WJets_f->Get(hist_name);
  TH1F* other = (TH1F*)other_f->Get(hist_name);
  TH1F* QCD = (TH1F*)QCD_f->Get(hist_name);

 
  // -------------------
  //Background Fit
  // -------------------
  TCanvas *background_c = new TCanvas("background_c","background fit",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();
  background_c->Clear();
  background_c->cd();



  TTbar_unmatched->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  TTbar_unmatched->SetYTitle("Events");
  TTbar_unmatched->SetTitleSize(0.045);
  TTbar_unmatched->GetYaxis()->SetTitleSize(0.045);
  TTbar_unmatched->GetYaxis()->SetTitleOffset(1.1);
  TTbar_unmatched->SetTitle("");
  TTbar_unmatched->SetMarkerStyle(20);
  TTbar_unmatched->SetMarkerSize(1.);
  TTbar_unmatched->SetLineColor(kBlue+1);
  TTbar_unmatched->SetMarkerColor(kBlue+1);
  TTbar_unmatched->GetYaxis()->SetRangeUser(0, 800);
  TTbar_unmatched->Draw("E1");


  TH1D* back = (TH1D*)TTbar_unmatched->Clone();
  back->Add(other);
  back->Add(WJets);
  back->Add(QCD);

  /////////////////////////   Fit function (Background)  ////////////////////////
  TF1* background_fit = new TF1("background_fit", " [0]*(1 - TMath::Erf((x-[1])/(1.4*[2])))", 24, 182);
  background_fit->SetParameter(0, 4);
  background_fit->SetParameter(1, 100);
  background_fit->SetParameter(2, 20);

  background_fit->SetLineColor(kOrange+2);
  // background_fit->SetLineStyle(kDashed);
  background_fit->SetLineStyle(7);
  background_fit->SetLineWidth(5);
  back->GetYaxis()->SetRangeUser(0, 800);


  back->Draw("PZ");
  back->Fit(background_fit, "R");
  background_fit->DrawClone("same");


  TString info = "unmatched t#bar{t} events";
  TString info2 = "24 GeV < m_{W} < 182 GeV";
  //  TString info3 = "f(x) = p0 erf #left(#frac{x-p1}{p2}#right)";
  TString info3 = "bkg(x) = p0 * erf((x-p1)/p2)";
  TLatex* text = new TLatex();
  text->SetTextFont(62);
  text->SetNDC();
  text->SetTextColor(kBlue+1);
  text->SetTextSize(0.035);
  text->DrawLatex(0.15, 0.83, info.Data());
 TLatex* text2 = new TLatex();
  text2->SetTextFont(62);
  text2->SetNDC();
  text2->SetTextColor(kOrange+2);
  text2->SetTextSize(0.035);
  text2->DrawLatex(0.15, 0.79, info3.Data());
  text2->DrawLatex(0.15, 0.75, info2.Data());




  background_c->Print(folder +"background_fit.eps");
  
  // -------------------
  // Signal fit
  // -------------------
  
  TCanvas *signal_c = new TCanvas("signal_c","signal fit",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();
  signal_c->Clear();
  signal_c->cd();
  TTbar_matched->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  TTbar_matched->SetYTitle("Events");
  TTbar_matched->SetTitleSize(0.045);
  TTbar_matched->GetYaxis()->SetTitleSize(0.045);
  TTbar_matched->GetYaxis()->SetTitleOffset(1.1);
  TTbar_matched->SetTitle("");
  TTbar_matched->SetMarkerStyle(24);
  TTbar_matched->SetMarkerSize(1.);
  TTbar_matched->SetLineColor(kRed);
  TTbar_matched->SetMarkerColor(kRed);
  TTbar_matched ->GetYaxis()->SetRangeUser(0, 550);
  TTbar_matched->Draw("PZ");

  /////////////////////////   Fit function (Signal)  ////////////////////////
  TF1 *signal_fit = new TF1("signal_fit","TMath::Voigt(x-[2], [0], [1], 4)*[3]", 70, 120);
  signal_fit->SetParameter(0, 10);
  signal_fit->FixParameter(1, 2.09);
  signal_fit->SetParameter(2, 92);
  signal_fit->SetParameter(3, 40);
 
  // signal_fit->SetLineStyle(kDashed);
  signal_fit->SetLineColor(kGreen+3);
  signal_fit->SetLineStyle(7);
  signal_fit->SetLineWidth(4);

  TTbar_matched->Fit(signal_fit,"R");
  signal_fit->DrawClone("same");

  info = "matched t#bar{t} events";
  info2 = "24 GeV < m_{W} < 182 GeV";
  //  TString info3 = "f(x) = p0 erf #left(#frac{x-p1}{p2}#right)";
  info3 = "sig(x) = p3 * Voigt(x-p2,p0)";
  text->SetTextFont(62);
  text->SetNDC();
  text->SetTextColor(kRed+1);
  text->SetTextSize(0.035);
  text->DrawLatex(0.15, 0.83, info.Data());
 
  text2->SetTextFont(62);
  text2->SetNDC();
  text2->SetTextColor(kGreen+3);
  text2->SetTextSize(0.035);
  text2->DrawLatex(0.15, 0.79, info3.Data());
  text2->DrawLatex(0.15, 0.75, info2.Data());

  TH1D* all = (TH1D*)TTbar_matched->Clone();
  all->Add(back);
 
 
  signal_c->Print(folder +"signal_fit.eps");


  gStyle->SetStatH(0.2);
 

  // ------------------------
  // Signal + Background fit
  // ------------------------
  TCanvas *signal_background_c = new TCanvas("signal_background_c","signal+background fit",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();
  signal_background_c->Clear();
  signal_background_c->cd();



  // TH1D* all = (TH1D*)TTbar_matched->Clone();
  // all->Add(back);
  all->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  all->SetYTitle("Events");
  all->SetTitleSize(0.045);
  all->GetYaxis()->SetTitleSize(0.045);
  all->GetYaxis()->SetTitleOffset(1.1);
  all->SetTitle("");
  all->GetYaxis()->SetRangeUser(0, 1200);
  all->SetMarkerStyle(24);
  all->SetMarkerColor(kBlack);
  all->SetLineColor(kBlack);
  all->Draw("PZ");

  /////////////////////////   Fit function (Signal+background)  ////////////////////////
  TF1 *signal_background_fit = new TF1("signal_background_fit","signal_fit + background_fit", 24,182);

  //Signal
  signal_background_fit->SetParameter(0, signal_fit->GetParameter(0));
  signal_background_fit->FixParameter(1, signal_fit->GetParameter(1));
  signal_background_fit->SetParameter(2, signal_fit->GetParameter(2));
  signal_background_fit->SetParameter(3, signal_fit->GetParameter(3));
  //Background
  signal_background_fit->SetParameter(4, background_fit->GetParameter(0));
  signal_background_fit->SetParameter(5, background_fit->GetParameter(1));
  signal_background_fit->SetParameter(6, background_fit->GetParameter(2));
 

  signal_background_fit->SetLineColor(kViolet);


  all->Fit(signal_background_fit, "R");
  TFitResultPtr fit_all_result = all->Fit(signal_background_fit, "SR");
  signal_background_fit->DrawClone("same");

  //show also background with fit
  TF1* f = (TF1*) back->GetListOfFunctions()->At(0);
  f->SetParameter(0,0);
  f->SetParameter(1,0);
  f->SetParameter(2,0);
  f->SetLineWidth(0);
  f->SetLineColor(kBlack);
  TH1F *back2 = (TH1F*) back->Clone();
  back2->SetStats(0);
  // back2->Draw("same");
  TF1* bc = (TF1*) background_fit->Clone();
  bc->SetParameter(0, signal_background_fit->GetParameter(4));
  bc->SetParameter(1, signal_background_fit->GetParameter(5));  
  bc->SetParameter(2, signal_background_fit->GetParameter(6));  
  bc->SetLineColor(kOrange+2);
  // bc->SetLineStyle(kDashed);
  bc->SetLineStyle(7);
  bc->SetLineWidth(4);
  bc->DrawClone("same");

  info = " t#bar{t} events";
  info2 = "24 GeV < m_{W} < 182 GeV";
  //  TString info3 = "f(x) = p0 erf #left(#frac{x-p1}{p2}#right)";
  info3 = "f(x) = sig(x) + bkg(x)";
  text->SetTextFont(62);
  text->SetNDC();
  text->SetTextColor(kBlack);
  text->SetTextSize(0.035);
  text->DrawLatex(0.15, 0.83, info.Data());
 
  text2->SetTextFont(62);
  text2->SetNDC();
  text2->SetTextColor(kViolet);
  text2->SetTextSize(0.035);
  text2->DrawLatex(0.15, 0.79, info3.Data());
  text2->DrawLatex(0.15, 0.75, info2.Data());
  
 

  signal_background_c->Print(folder +"signal_background_fit.eps");
  // ------------------------
  //        Data
  // ------------------------

  TCanvas *data_c = new TCanvas("data_c","data",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();
  data_c->Clear();
  data_c->cd();

  data->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  data->SetYTitle("Events");
  data->SetTitleSize(0.045);
  data->GetYaxis()->SetTitleSize(0.045);
  data->GetYaxis()->SetTitleOffset(1.1);
  data->SetTitle("");
  data->SetMarkerStyle(20);
  data->SetMarkerSize(1.);
  data->SetLineColor(kBlack);
  data->SetMarkerColor(kBlack);
  data->GetYaxis()->SetRangeUser(0, 1200);
  data->Draw("PZ");

  /////////////////////////   Fit function (Data)  ////////////////////////
  TF1* data_fit = new TF1("data_fit","signal_fit+background_fit" , 24, 182);

  Double_t sc = data->Integral() / all->Integral();
  //signal
  data_fit->SetParameter(0, signal_background_fit->GetParameter(0));
  data_fit->FixParameter(1, signal_background_fit->GetParameter(1));
  data_fit->SetParameter(2, signal_background_fit->GetParameter(2));
  data_fit->SetParameter(3, signal_background_fit->GetParameter(3));
  //background
  data_fit->SetParameter(4, sc*signal_background_fit->GetParameter(4));   
  data_fit->SetParameter(5, sc*signal_background_fit->GetParameter(5));
  data_fit->SetParameter(6, sc*signal_background_fit->GetParameter(6));

  data_fit->SetLineColor(kViolet);
  data_fit->SetLineStyle(kSolid);

  data->Fit(data_fit, "R");
  TFitResultPtr fit_data_result =  data->Fit(data_fit, "SR");
  data_fit->Draw("same");

  cout << "events in data: " << data->Integral() << endl;

  //show also background with fit

  // back2->Draw("same");
  bc = (TF1*) background_fit->Clone();
  bc->SetParameter(0, data_fit->GetParameter(4));
  bc->SetParameter(1, data_fit->GetParameter(5)); 
  bc->SetParameter(2, data_fit->GetParameter(6)); 
 
  bc->SetLineColor(kOrange+2);
  bc->SetLineStyle(7);
  bc->SetLineWidth(4);
  bc->DrawClone("same");

  info = " data events";
  info2 = "24 GeV < m_{W} < 182 GeV";
  //  TString info3 = "f(x) = p0 erf #left(#frac{x-p1}{p2}#right)";
  info3 = "f(x) = sig(x) + bkg(x)";
  text->SetTextFont(62);
  text->SetNDC();
  text->SetTextColor(kBlack);
  text->SetTextSize(0.035);
  text->DrawLatex(0.15, 0.83, info.Data());
 
  text2->SetTextFont(62);
  text2->SetNDC();
  text2->SetTextColor(kViolet);
  text2->SetTextSize(0.035);
  text2->DrawLatex(0.15, 0.79, info3.Data());
  text2->DrawLatex(0.15, 0.75, info2.Data());


  data_c->Print(folder +"data_fit.eps");

  // ---------------------------------------
  //        Calculate Efficency
  // ---------------------------------------
  TCanvas *MC_Eff_c = new TCanvas("MC_Eff_c","MC Eff curve",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();
  MC_Eff_c->Clear();
  MC_Eff_c->cd();

  TF1 *MC_Eff_f =new TF1("MC_Eff_f","signal_fit", 24,182);
   //signal
  MC_Eff_f->SetParameter(0, signal_background_fit->GetParameter(0));
  MC_Eff_f->SetParameter(1, signal_background_fit->GetParameter(1));
  MC_Eff_f->SetParameter(2, signal_background_fit->GetParameter(2));
  MC_Eff_f->SetParameter(3, signal_background_fit->GetParameter(3));
 
  MC_Eff_f->Draw();
  MC_Eff_f->GetHistogram()->GetXaxis()->SetTitle("M_{W}^{rec} [GeV/c^{2}]");
  MC_Eff_f->GetHistogram()->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  MC_Eff_f->GetHistogram()->SetYTitle("Events");
  MC_Eff_f->GetHistogram()->SetTitleSize(0.045);
  MC_Eff_f->GetHistogram()->GetYaxis()->SetTitleSize(0.045);
  MC_Eff_f->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
  MC_Eff_f->GetHistogram()->SetTitle("signal");
  MC_Eff_f->Draw("same");
  MC_Eff_c->Print(folder + "MC_Eff_sig_MC.eps");

  TF1 *data_Eff_f =new TF1("data_Eff_f","signal_fit", 24,182);
  //signal
  data_Eff_f->SetParameter(0, data_fit->GetParameter(0));
  data_Eff_f->SetParameter(1, data_fit->GetParameter(1));
  data_Eff_f->SetParameter(2, data_fit->GetParameter(2));
  data_Eff_f->SetParameter(3, data_fit->GetParameter(3));
 
  // data_Eff_f->SetLineColor(kBlue+2);
  data_Eff_f->SetLineStyle(kDashed);
  data_Eff_f->Draw("");
  MC_Eff_c->Print(folder + "MC_Eff_data.eps");

  Double_t num_MC_before = MC_Eff_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number before tagger:   "<< num_MC_before <<endl;
  Double_t num_data_before = data_Eff_f->Integral(24,182,TMath::Power(10,-8))/2;
  cout<<"data number before tagger:   "<< num_data_before <<endl;

  // integrate background events for tagger and multipy by mistagging rate (MC)
  TF1 *MC_back_f =new TF1("MC_back_f","background_fit", 24,182);
  //background
  MC_back_f->SetParameter(0, signal_background_fit->GetParameter(4));
  MC_back_f->SetParameter(1, signal_background_fit->GetParameter(5));
  MC_back_f->SetParameter(2, signal_background_fit->GetParameter(6));
  Double_t number_back_MC_miss = MC_back_f->Integral(24,182) / 2;
  cout << "number back_MC_miss "<<number_back_MC_miss <<endl;
  MC_back_f->SetLineColor(kBlue+1);
  MC_back_f->Draw("");

  MC_back_f->GetHistogram()->SetXTitle("M_{W}^{rec} [GeV/c^{2}]");
  MC_back_f->GetHistogram()->SetYTitle("Events");
  MC_back_f->GetHistogram()->SetTitleSize(0.045);
  MC_back_f->GetHistogram()->GetYaxis()->SetTitleSize(0.045);
  MC_back_f->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
  MC_back_f->GetHistogram()->SetTitle("background");
  MC_back_f->Draw("Same");
  MC_Eff_c->Print(folder + "MC_Eff_bkg_MC.eps");

  // integrate background events for tagger and multipy by mistagging rate (Data)
  TF1 *data_back_f =new TF1("data_back_f","background_fit", 24,182);
  //background
  data_back_f->SetParameter(0, data_fit->GetParameter(4));
  data_back_f->SetParameter(1, data_fit->GetParameter(5));
  data_back_f->SetParameter(2, data_fit->GetParameter(6));

  Double_t number_back_data_miss = data_back_f->Integral(24,182) / 2;
  cout << "number back_data_miss "<<number_back_data_miss <<endl;
  data_back_f->SetLineColor(kBlue+1);
  data_back_f->Draw("");
  MC_Eff_c->Print(folder + "MC_Eff_bkg_Data.eps");

//count events in signal histogram
  Double_t number_sig_before_true=0;  
  number_sig_before_true =  TTbar_matched->Integral(13,92);
  Double_t error_sig_before_true;
  TTbar_matched->IntegralAndError(13,92,error_sig_before_true);

//count events in signal histogram
  Double_t number_bkg_before_true=0;  
  number_bkg_before_true =  back->Integral(13,92);
  Double_t error_bkg_before_true;
  back->IntegralAndError(13,92,error_bkg_before_true);

  // load histograms after tagger
  hist_name = "tagger_zwtag/reco_mass_W";
  data_after = (TH1F*)data_f->Get(hist_name);
  TTbar_matched = (TH1F*)TTbar_matched_f->Get(hist_name);
  TTbar_unmatched = (TH1F*)TTbar_unmatched_f->Get(hist_name);
  WJets = (TH1F*)WJets_f->Get(hist_name);
  other = (TH1F*)other_f->Get(hist_name);
  QCD = (TH1F*)QCD_f->Get(hist_name);
  
  back = (TH1D*)TTbar_unmatched->Clone();
  back->Add(other);
  back->Add(WJets);
  back->Add(QCD);
  back->SetLineColor(kBlue+1);
  back->Draw();
  MC_Eff_c->Print(folder + "Hist_back_after.eps");

//count events in background histogram
  Double_t number_back=0;  
  for(int i =13 ; i<92;i++){
    number_back = number_back + back->GetBinContent(i);
  }
  cout << "number of background events after tagger:  " << number_back <<endl;
  // cout << "number of background events by integrating:  " << back->Integral(13,92) <<endl;
  Double_t error_back;
  back->IntegralAndError(13,92,error_back);
  cout << "error of background events by integrate and error:  " << error_back <<endl;

  //count events in signal histogram
  Double_t number_sig=0;  
  for(int i =13 ; i<92;i++){
    number_sig = number_sig + TTbar_matched->GetBinContent(i);
  }
  cout << "number of sig events after tagger:  " << number_sig <<endl;
  // cout << "number of sig events by integrating:  " << TTbar_matched->Integral(13,92) <<endl;
  Double_t error_sig;
  TTbar_matched->IntegralAndError(13,92,error_sig);
  cout << "error of sig events by integrate and error:  " << error_sig <<endl;

  //count events in data histogram
  Double_t number_data=0;  
  for(int i =13 ; i<92;i++){
    number_data = number_data + data_after->GetBinContent(i);
  }
  cout << "number of data events after tagger:  " << number_data <<endl;
  // cout << "number of data events by integrating:  " << data->Integral(13,92) <<endl;
  Double_t error_data;
  data->IntegralAndError(13,92,error_data);
  cout << "error of data events by integrate and error:  " << error_data <<endl;

  ofstream myfile;
  myfile.open (folder+"numbers.txt");
  myfile << "MC number before tagger (sig):   "<< num_MC_before <<endl;
  myfile << "true number of MC sig before tagger   "<< number_sig_before_true<<endl;
  myfile<<"Data number before tagger (sig):   "<< num_data_before <<endl;
  myfile << "MC number before tagger (bkg):   "<< number_back_MC_miss <<endl;
 myfile << "true MC number before tagger (bkg):   "<< number_bkg_before_true <<endl;
  myfile << "Data number before tagger (bkg):   "<< number_back_data_miss <<endl;
  myfile<< "number of sig events after tagger:  " << number_sig <<endl;
  myfile<< "number of all events after tagger:  " << number_sig+ number_back <<endl;
  myfile<< "number of data events after tagger:  " << number_data <<endl;


 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                       Error calculation
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "============================================================================================="<<endl;
  cout << "Error calculation "<<endl;
  cout << "============================================================================================="<<endl;

  cout <<"1. N_MC error calculation"<<endl;
  //cov matrix out of fit
  TMatrixDSym cov_MC = fit_all_result->GetCovarianceMatrix();  
  if(b_error){
    cout << "Kovarianzmatrix nach inital fit:" << endl << endl;
    cov_MC.Print();
    cout << endl << endl << endl << endl;
  }
  //resave cov matrix to calculate the eigenvalues and eigenvectors
  const TMatrixDSymEigen eigen_cov_MC(cov_MC);

  //calculate eigenvalues and eigenvectors
  const TVectorD eigen_values_MC = eigen_cov_MC.GetEigenValues();
  const TMatrixD eigen_vectors_MC = eigen_cov_MC.GetEigenVectors();
  if(b_error){
    cout << "eigen_values nach inital fit:" << endl << endl;
    eigen_values_MC.Print();
    cout << endl << endl << endl << endl;
    cout << "eigen_vectors_MC nach inital fit:" << endl << endl;
    eigen_vectors_MC.Print();
    cout << endl << endl << endl << endl;
  }

  if(b_error){
    //multiply eigen values with unitary matrix 
    TMatrixD M_Diag_MC(6,6);
    M_Diag_MC.UnitMatrix();
    for(int i=0; i<6; i++){
      double tmp_MC =eigen_values_MC[i];
      TMatrixDRow(M_Diag_MC,i)(i) = tmp_MC;
    }
 
    cout << "M_Diag_MC nach inital fit:" << endl << endl;
    M_Diag_MC.Print();
    cout << endl << endl << endl << endl;
  }

  //transform eigen vectors into row vectors 
  TMatrixD RT_MC(eigen_vectors_MC);
  RT_MC.T();
  if(b_error){
    cout << "Test: eigenvectorsT * cov * eigenvectors = eigen values * 1 [M_Diag_MC]" << endl << endl;
    TMatrixD test_diag_MC = RT_MC * cov_MC * eigen_vectors_MC;
    test_diag_MC.Print();
    cout << endl << endl << endl << endl;
  }

  //found transformation that diagonalised the cov matrix so we can used it to determine the uncorrelated parameters by P' = einenvectorsT * P


  //save old parameters P in a vector
  const double a_MC = fit_all_result->Parameter(0);
  const double b_MC = fit_all_result->Parameter(1);
  const double c_MC = fit_all_result->Parameter(2);
  const double d_MC = fit_all_result->Parameter(3);
  const double e_MC = fit_all_result->Parameter(4);
  const double f_MC = fit_all_result->Parameter(5);
  const double g_MC = fit_all_result->Parameter(6);
  const double old_params_MC[7] = {a_MC,b_MC,c_MC,d_MC,e_MC,f_MC,g_MC};
  const TVectorD V_Old_Param_MC(7,old_params_MC);

  if(b_error){
    cout << "V_Old_Param_MC nach inital fit:" << endl << endl;
    V_Old_Param_MC.Print();
    cout << endl << endl << endl << endl;
  }

  //calculate parameters in new basis
  TDecompSVD svd_MC(eigen_vectors_MC);
  Bool_t ok_MC;
  const TVectorD V_New_Param_MC = svd_MC.Solve(V_Old_Param_MC,ok_MC);
  if(b_error){
    cout << "V_New_Param_MC nach inital fit:" << endl << endl;
    V_New_Param_MC.Print();
    cout << endl << endl << endl << endl;
  }
 /****************************/
  /*                          */
  /*    expression by new     */
  /*                          */
  /****************************/

  //Express old parameters in fit function by new parameters such that they yield the old ones.
  //should yield similar fit results if they are transformed back afterwards, but the errors on the new ones are uncorrelated by construction
  //simply vary each of the new parameters up and down and take the envelope as systematic uncertainty


  //parametrize old parameters by using new ones with eigen_vectors_MC
  TMatrixD M_Dummy_MC(eigen_vectors_MC);
  double a_tr_MC[7], b_tr_MC[7], c_tr_MC[7], d_tr_MC[7], e_tr_MC[7], f_tr_MC[7], g_tr_MC[7];
  for (int i=0; i<7; i++){
    a_tr_MC[i] = TMatrixDRow(M_Dummy_MC,0)[i];
    b_tr_MC[i] = TMatrixDRow(M_Dummy_MC,1)[i];
    c_tr_MC[i] = TMatrixDRow(M_Dummy_MC,2)[i];
    d_tr_MC[i] = TMatrixDRow(M_Dummy_MC,3)[i];
    e_tr_MC[i] = TMatrixDRow(M_Dummy_MC,4)[i];
    f_tr_MC[i] = TMatrixDRow(M_Dummy_MC,5)[i];
    g_tr_MC[i] = TMatrixDRow(M_Dummy_MC,6)[i];
  }

  //string of new fit function with uncorrelated parameters
  stringstream sstr_MC;
  sstr_MC  << "(" << d_tr_MC[0] << "*[0]+(" <<d_tr_MC[1]<<")*[1]+("<<d_tr_MC[2]<<")*[2]+("<<d_tr_MC[3]<<")*[3]+("<<d_tr_MC[4]<<")*[4]+("<<d_tr_MC[5]<<")*[5]+("<<d_tr_MC[6]<<")*[6]" <<")*TMath::Voigt(x-"<<"(" << c_tr_MC[0] << "*[0]+(" <<c_tr_MC[1]<<")*[1]+("<<c_tr_MC[2]<<")*[2]+("<<c_tr_MC[3]<<")*[3]+("<<c_tr_MC[4]<<")*[4]+("<<c_tr_MC[5]<<")*[5]+("<<c_tr_MC[6]<<")*[6]" <<"),"<<"(" << a_tr_MC[0] << "*[0]+(" <<a_tr_MC[1]<<")*[1]+("<<a_tr_MC[2]<<")*[2]+("<<a_tr_MC[3]<<")*[3]+("<<a_tr_MC[4]<<")*[4]+("<<a_tr_MC[5]<<")*[5]+("<<a_tr_MC[6]<<")*[6]" <<"),"<< "(" << b_tr_MC[0] << "*[0]+(" <<b_tr_MC[1]<<")*[1]+("<<b_tr_MC[2]<<")*[2]+("<<b_tr_MC[3]<<")*[3]+("<<b_tr_MC[4]<<")*[4]+("<<b_tr_MC[5]<<")*[5]+("<<b_tr_MC[6]<<")*[6]" <<")"<<",4)"<< "+" << "(" << e_tr_MC[0] << "*[0]+(" <<e_tr_MC[1]<<")*[1]+("<<e_tr_MC[2]<<")*[2]+("<<e_tr_MC[3]<<")*[3]+("<<e_tr_MC[4]<<")*[4]+("<<e_tr_MC[5]<<")*[5]+("<<e_tr_MC[6]<<")*[6]" <<")*(1-TMath::Erf((x-" <<"(" << f_tr_MC[0] << "*[0]+(" <<f_tr_MC[1]<<")*[1]+("<<f_tr_MC[2]<<")*[2]+("<<f_tr_MC[3]<<")*[3]+("<<f_tr_MC[4]<<")*[4]+("<<f_tr_MC[5]<<")*[5]+("<<f_tr_MC[6]<<")*[6]" <<")" <<")/(1.4 * "<<
    "(" << g_tr_MC[0] << "*[0]+(" <<g_tr_MC[1]<<")*[1]+("<<g_tr_MC[2]<<")*[2]+("<<g_tr_MC[3]<<")*[3]+("<<g_tr_MC[4]<<")*[4]+("<<g_tr_MC[5]<<")*[5]+("<<g_tr_MC[6]<<")*[6]" <<")"<<")))";

  //signal: TMath::Voigt(x-[2], [0], [1], 4)*[3]
  //background:  [0]*(1 - TMath::Erf((x-[1])/(1.4*[2])))
 
  string s_formula_MC = sstr_MC.str();
  const char * c_formula_MC = s_formula_MC.c_str();
  if(b_error){
    cout << "Fit Funktion mit neuen Parametern: " << endl;
    cout << c_formula_MC << endl<<endl<<endl;
  }

  //New fit fuction with uncoorelated parameters
  TF1* f_NewParam_MC = new TF1("f_NewParam_MC",c_formula_MC,24,182);
  f_NewParam_MC->SetParameter(0,V_New_Param_MC[0]);
  f_NewParam_MC->SetParameter(1,V_New_Param_MC[1]);
  f_NewParam_MC->SetParameter(2,V_New_Param_MC[2]);
  f_NewParam_MC->SetParameter(3,V_New_Param_MC[3]);
  f_NewParam_MC->SetParameter(4,V_New_Param_MC[4]);
  f_NewParam_MC->SetParameter(5,V_New_Param_MC[5]);
  f_NewParam_MC->FixParameter(6,V_New_Param_MC[6]);
  f_NewParam_MC->SetLineColor(kGreen+3);

  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "Fit with new parameters: " << endl;
  cout << "=======================================================================" << endl << endl << endl;
  TH1D* all2 = (TH1D*)all->Clone();
  TCanvas* cfitnew_MC = new TCanvas("cfitnewMC", "Fit function in new parameters, MC",10,10,700,900);
  TFitResultPtr fit_result_MC = all2->Fit(f_NewParam_MC,"SR");
  cfitnew_MC->Print("Fit_signal_background_new.eps");
  cout << "Fit in new parameters, MC: " << endl;
  fit_result_MC->Print("V");


  //calculate fit parameter errors by hand: keep 6 fixed and vary one until chi2 increases by 1
  cout << endl << endl << endl << endl << endl;
  cout << "======================================================================="  << endl;
  cout << "Calculate errors by hand " << endl;
  cout << "=======================================================================" << endl << endl << endl;
  
  //define error function
  TF1* f_NewParam_MC_error = new TF1("f_NewParam_MC_error",c_formula_MC,24,182);

  //fix all fit values
  TCanvas* c_dummy_MC = new TCanvas("c_dummy_MC", "Fits for chi2 in MC", 10,10,700,900);
  for(int i=0; i<7; i++){
    f_NewParam_MC_error->FixParameter(i,fit_result_MC->Parameter(i));
  }
  
  cout << endl << endl << endl << "FIT BY HAND for CHI2 calculation: SIGNAL" << endl << endl << endl;

  //smalles chi2 out of the fit before

  all2->Fit(f_NewParam_MC_error,"QR");
  double chi2_best_MC = f_NewParam_MC_error->GetChisquare();

  //set up arrays to save the errors 
  double pars_MC[7], pars_up_MC[7], pars_dn_MC[7], err_pars_up_MC[7], err_pars_dn_MC[7];
  for(int i=0; i<7; i++) pars_MC[i] = f_NewParam_MC_error->GetParameter(i);
  bool pars_up_set_MC[7] = {false,false,false,false,false,false,false};
  bool pars_dn_set_MC[7] = {false,false,false,false,false,false,false};
  TGraph* g_chi2_pars_MC[7];
  for(int i=0; i<7; i++) g_chi2_pars_MC[i] = new TGraph(50000);
  for_percent = 0;


  //varying all parameters in steps of 1/1000*par
  for(int j=0; j<7; j++){

    //reset parameters
    for(int k=0; k<7; k++) f_NewParam_MC_error->FixParameter(k,fit_result_MC->Parameter(k));
    
    double chi2_diff_MC = 0;
    double varied_par_MC_old=0;
    double varied_par_MC =0;
    for(int i=0; i<50000; i++){
      for_percent++;
      varied_par_MC_old = varied_par_MC;
      if(j==0)  varied_par_MC = (pars_MC[j]-160) + pars_MC[j]/1000000 * i;
      if(j==1)  varied_par_MC = (pars_MC[j]-5) + pars_MC[j]/100000 * i;
      if(j==2)  varied_par_MC = (pars_MC[j]+2) + pars_MC[j]/1000000 * i;
      if(j==3)  varied_par_MC = (pars_MC[j]+2) + pars_MC[j]/1000000 * i;
      if(j==4)  varied_par_MC = (pars_MC[j]-2) + pars_MC[j]/1000000 * i;
      if(j==5)  varied_par_MC = (pars_MC[j]-10) + pars_MC[j]/10000 * i;
      if(j==6)  varied_par_MC = (pars_MC[j]-10) + pars_MC[j]/10000 * i;
      
      //original double varied_par_MC = -20*pars_MC[j] + pars_MC[j]/1000 * i;
      f_NewParam_MC_error->FixParameter(j,varied_par_MC);
     
      all2->Fit(f_NewParam_MC_error,"QR");

      double chi2_tmp_MC = f_NewParam_MC_error->GetChisquare();
      chi2_diff_MC = chi2_tmp_MC - chi2_best_MC;

      if(i%500 == 0) cout << "\r"  << for_percent/3500  << "%, " <<  "Parameter " << j << ", Fit No. " << i  << ", current chi2: " << chi2_tmp_MC << " at current parametervalue: " << varied_par_MC << "           "  << flush;
      // if(i%500 == 0) if(j==0)cout << "\r"  << for_percent/3500  << "%, " <<  "Parameter " << j << ", Fit No. " << i  << ", current chi2: " << chi2_tmp_MC << " at current parametervalue: " << varied_par_MC << "           "  << endl;

      if(!pars_dn_set_MC[j] && chi2_diff_MC < 1) {
  	pars_dn_MC[j] = varied_par_MC_old;
  	pars_dn_set_MC[j] = true;
      }
      if(pars_dn_set_MC[j] && !pars_up_set_MC[j] && chi2_diff_MC >= 1){
  	pars_up_MC[j] = varied_par_MC;
  	pars_up_set_MC[j] = true;
      }

      //draw chi2 as function of p0
      g_chi2_pars_MC[j]->SetPoint(i,varied_par_MC, chi2_tmp_MC);
    }
    if(pars_dn_MC[j] > pars_up_MC[j]) swap(pars_dn_MC[j],pars_up_MC[j]);
    
    err_pars_up_MC[j] = abs(pars_MC[j]-pars_up_MC[j]);
    err_pars_dn_MC[j] = abs(pars_MC[j]-pars_dn_MC[j]);
    
  }//varying all parameters in steps of 1/1000*par

  //define Line of the up and down variation in chi2
  TLine* l_pars_dn_MC[7];
  TLine* l_pars_up_MC[7];
  TLine* l_pars_central_MC[7];
  for(int i=0; i<7; i++){
    l_pars_up_MC[i] = new TLine(pars_up_MC[i], chi2_best_MC - 1, pars_up_MC[i], chi2_best_MC+1);
    l_pars_dn_MC[i] = new TLine(pars_dn_MC[i], chi2_best_MC - 1, pars_dn_MC[i], chi2_best_MC+1);
    l_pars_central_MC[i] = new TLine(pars_MC[i], chi2_best_MC, pars_MC[i], chi2_best_MC - 1);
    l_pars_up_MC[i]->SetLineWidth(3);
    l_pars_up_MC[i]->SetLineColor(kRed);
    l_pars_dn_MC[i]->SetLineWidth(3);
    l_pars_dn_MC[i]->SetLineColor(kRed);
    l_pars_central_MC[i]->SetLineWidth(3);
    l_pars_central_MC[i]->SetLineColor(kBlue);
  }
  for(int i=0; i<7; i++){
    stringstream n_MC;
    n_MC << "Parameter " << i+1;
    string s_n_MC = n_MC.str();
    const char * c_n_MC = s_n_MC.c_str();
    g_chi2_pars_MC[i]->SetMinimum(chi2_best_MC - 1);
    g_chi2_pars_MC[i]->SetMaximum(chi2_best_MC + 10);
    g_chi2_pars_MC[i]->SetTitle("");
    g_chi2_pars_MC[i]->GetXaxis()->SetTitle(c_n_MC);
    g_chi2_pars_MC[i]->GetXaxis()->SetTitleSize(0.044);
    g_chi2_pars_MC[i]->GetYaxis()->SetTitle("#chi^{2}");
    g_chi2_pars_MC[i]->GetYaxis()->SetTitleSize(0.044);
    g_chi2_pars_MC[i]->GetXaxis()->SetLimits(pars_dn_MC[i]-2*err_pars_dn_MC[i],pars_up_MC[i]+2*err_pars_up_MC[i]);
  }

  // example of a error calculated parameter by hand
  TCanvas* c_chi2_p1_MC = new TCanvas("c_chi2_p1_MC", "chi2 (p1)_MC", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_MC[1]->Draw();
  l_pars_up_MC[1]->Draw("SAME");
  l_pars_dn_MC[1]->Draw("SAME");
  l_pars_central_MC[1]->Draw("SAME");
  c_chi2_p1_MC->Print(folder + "Chi2_MC_p1.eps");

  TCanvas* c_chi2_p0_MC = new TCanvas("c_chi2_p0_MC", "chi2 (p0)_MC", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_MC[0]->Draw();
  l_pars_up_MC[0]->Draw("SAME");
  l_pars_dn_MC[0]->Draw("SAME");
  l_pars_central_MC[0]->Draw("SAME");
  c_chi2_p0_MC->Print(folder + "Chi2_MC_p0.eps");

  TCanvas* c_chi2_p2_MC = new TCanvas("c_chi2_p2_MC", "chi2 (p2)_MC", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_MC[2]->Draw();
  l_pars_up_MC[2]->Draw("SAME");
  l_pars_dn_MC[2]->Draw("SAME");
  l_pars_central_MC[2]->Draw("SAME");
  c_chi2_p2_MC->Print(folder + "Chi2_MC_p2.eps");

  TCanvas* c_chi2_p3_MC = new TCanvas("c_chi2_p3_MC", "chi2 (p3)_MC", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_MC[3]->Draw();
  l_pars_up_MC[3]->Draw("SAME");
  l_pars_dn_MC[3]->Draw("SAME");
  l_pars_central_MC[3]->Draw("SAME");
  c_chi2_p3_MC->Print(folder + "Chi2_MC_p3.eps");

  TCanvas* c_chi2_p4_MC = new TCanvas("c_chi2_p4_MC", "chi2 (p4)_MC", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_MC[4]->Draw();
  l_pars_up_MC[4]->Draw("SAME");
  l_pars_dn_MC[4]->Draw("SAME");
  l_pars_central_MC[4]->Draw("SAME");
  c_chi2_p4_MC->Print(folder + "Chi2_MC_p4.eps");

  TCanvas* c_chi2_p5_MC = new TCanvas("c_chi2_p5_MC", "chi2 (p5)_MC", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_MC[5]->Draw();
  l_pars_up_MC[5]->Draw("SAME");
  l_pars_dn_MC[5]->Draw("SAME");
  l_pars_central_MC[5]->Draw("SAME");
  c_chi2_p5_MC->Print(folder + "Chi2_MC_p5.eps");


  //print all uncorrelated parameters with errors
  cout<<endl;
  for(int j=0; j<7; j++){
    cout << "Result MC: par " << j << " = " << pars_MC[j] << " (+" << err_pars_up_MC[j] << ") (-" << err_pars_dn_MC[j] << ")" << endl;
  }

  TF1* f_NewParam_MC_up1 = new TF1("f_NewParam_MC_up1", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn1 = new TF1("f_NewParam_MC_dn1", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_up2 = new TF1("f_NewParam_MC_up2", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn2 = new TF1("f_NewParam_MC_dn2", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_up3 = new TF1("f_NewParam_MC_up3", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn3 = new TF1("f_NewParam_MC_dn3", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_up4 = new TF1("f_NewParam_MC_up4", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn4 = new TF1("f_NewParam_MC_dn4", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_up5 = new TF1("f_NewParam_MC_up5", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn5 = new TF1("f_NewParam_MC_dn5", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_up6 = new TF1("f_NewParam_MC_up6", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn6 = new TF1("f_NewParam_MC_dn6", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_up7 = new TF1("f_NewParam_MC_up7", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dn7 = new TF1("f_NewParam_MC_dn7", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_upall = new TF1("f_NewParam_MC_upall", c_formula_MC,24, 182);
  TF1* f_NewParam_MC_dnall = new TF1("f_NewParam_MC_dnall", c_formula_MC,24, 182);

  for(int i=0; i<7; i++){
    f_NewParam_MC_up1->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn1->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_up2->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn2->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_up3->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn3->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_up4->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn4->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_up5->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn5->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_up6->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn6->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_up7->FixParameter(i,fit_result_MC->Parameter(i));
    f_NewParam_MC_dn7->FixParameter(i,fit_result_MC->Parameter(i));

    if(i==0){
      f_NewParam_MC_up1->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn1->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
    else if (i==1){
      f_NewParam_MC_up2->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn2->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
    else if (i==2){
      f_NewParam_MC_up3->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn3->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
    else if (i==3){
      f_NewParam_MC_up4->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn4->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
    else if (i==4){
      f_NewParam_MC_up5->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn5->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
    else if (i==5){
      f_NewParam_MC_up6->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn6->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
    else if (i==6){
      f_NewParam_MC_up7->FixParameter(i,fit_result_MC->Parameter(i) + err_pars_up_MC[i]);
      f_NewParam_MC_dn7->FixParameter(i,fit_result_MC->Parameter(i) - err_pars_dn_MC[i]);
    }
  }

  TCanvas* cupdnMC = new TCanvas("cupdnMC", "Functions varied up and down, MC",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();

  leg = new TLegend(0.6,0.4,0.89,0.89);
  leg->SetBorderSize(0);


  f_NewParam_MC->GetXaxis()->SetTitle("M_{W}^{rec} [GeV/c^{2}]");
  f_NewParam_MC->GetYaxis()->SetTitle("Events");
  f_NewParam_MC->GetXaxis()->SetTitleSize(0.045);
  f_NewParam_MC->GetYaxis()->SetTitleSize(0.045);
  // f_NewParam_MC->GetYaxis()->SetRangeUser(0,50);
  f_NewParam_MC->SetTitle("");

  f_NewParam_MC->Draw();
  leg ->AddEntry(f_NewParam_MC,"nominal", "l");


  f_NewParam_MC_up1->SetLineColor(3);
  f_NewParam_MC_up1->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_up1,"Par. 1 up", "l");
  
  f_NewParam_MC_dn1->SetLineColor(4);
  f_NewParam_MC_dn1->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_dn1,"Par. 1 down", "l");

  f_NewParam_MC_up2->SetLineColor(5);
  f_NewParam_MC_up2->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_up2,"Par. 2 up", "l");

  f_NewParam_MC_dn2->SetLineColor(6);
  f_NewParam_MC_dn2->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_dn2,"Par. 2 down", "l");

  f_NewParam_MC_up3->SetLineColor(7);
  f_NewParam_MC_up3->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_up3,"Par. 3 up", "l");

  f_NewParam_MC_dn3->SetLineColor(8);
  f_NewParam_MC_dn3->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_dn3,"Par. 3 down", "l");

  f_NewParam_MC_up4->SetLineColor(9);
  f_NewParam_MC_up4->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_up4,"Par. 4 up", "l");

  f_NewParam_MC_dn4->SetLineColor(15);
  f_NewParam_MC_dn4->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_dn4,"Par. 4 down", "l");

  f_NewParam_MC_up5->SetLineColor(11);
  f_NewParam_MC_up5->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_up5,"Par. 5 up", "l");

  f_NewParam_MC_dn5->SetLineColor(12);
  f_NewParam_MC_dn5->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_dn5,"Par. 5 down", "l");

  f_NewParam_MC_up6->SetLineColor(40);
  f_NewParam_MC_up6->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_up6,"Par. 6 up", "l");

  f_NewParam_MC_dn6->SetLineColor(42);
  f_NewParam_MC_dn6->Draw("SAME");
  leg ->AddEntry(f_NewParam_MC_dn6,"Par. 6 down", "l");



  leg->Draw("SAME");
  cupdnMC->Print(folder + "variations_MC.eps");
  //integrate over each variation and save the difference to normal number of sig events in MC before tagger
  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "integration of all up and down variations MC sig: " << num_MC_before <<endl;
  cout << "=======================================================================" << endl << endl << endl;

  // signal_fit function has to be express by 7 paramerters
  stringstream sstr_MC_signal;
  sstr_MC_signal  << "(" << d_tr_MC[0] << "*[0]+(" <<d_tr_MC[1]<<")*[1]+("<<d_tr_MC[2]<<")*[2]+("<<d_tr_MC[3]<<")*[3]+("<<d_tr_MC[4]<<")*[4]+("<<d_tr_MC[5]<<")*[5]+("<<d_tr_MC[6]<<")*[6]" <<")*TMath::Voigt(x-"<<"(" << c_tr_MC[0] << "*[0]+(" <<c_tr_MC[1]<<")*[1]+("<<c_tr_MC[2]<<")*[2]+("<<c_tr_MC[3]<<")*[3]+("<<c_tr_MC[4]<<")*[4]+("<<c_tr_MC[5]<<")*[5]+("<<c_tr_MC[6]<<")*[6]" <<"),"<<"(" << a_tr_MC[0] << "*[0]+(" <<a_tr_MC[1]<<")*[1]+("<<a_tr_MC[2]<<")*[2]+("<<a_tr_MC[3]<<")*[3]+("<<a_tr_MC[4]<<")*[4]+("<<a_tr_MC[5]<<")*[5]+("<<a_tr_MC[6]<<")*[6]" <<"),"<< "(" << b_tr_MC[0] << "*[0]+(" <<b_tr_MC[1]<<")*[1]+("<<b_tr_MC[2]<<")*[2]+("<<b_tr_MC[3]<<")*[3]+("<<b_tr_MC[4]<<")*[4]+("<<b_tr_MC[5]<<")*[5]+("<<b_tr_MC[6]<<")*[6]" <<")"<<",4)";
  string s_formula_MC_signal = sstr_MC_signal.str();
  const char * c_formula_MC_signal = s_formula_MC_signal.c_str();

  //Integrate over all up and down variation itself
  //Par1
  TF1 *MC_Eff_NewPar_up1_f =new TF1("MC_Eff_NewPar_up1_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_MC_up1->GetParameter(i));
  Double_t num_MC_NewPar_up1_before = MC_Eff_NewPar_up1_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp1 before tagger:   "<< num_MC_NewPar_up1_before <<endl;

  TF1 *MC_Eff_NewPar_down1_f =new TF1("MC_Eff_NewPar_down1_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_MC_dn1->GetParameter(i));
  Double_t num_MC_NewPar_down1_before = MC_Eff_NewPar_down1_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown1 before tagger:   "<< num_MC_NewPar_down1_before <<endl;

  //Par2
  TF1 *MC_Eff_NewPar_up2_f =new TF1("MC_Eff_NewPar_up2_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_MC_up2->GetParameter(i));
  Double_t num_MC_NewPar_up2_before = MC_Eff_NewPar_up2_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp2 before tagger:   "<< num_MC_NewPar_up2_before <<endl;

  TF1 *MC_Eff_NewPar_down2_f =new TF1("MC_Eff_NewPar_down2_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_MC_dn2->GetParameter(i));
  Double_t num_MC_NewPar_down2_before = MC_Eff_NewPar_down2_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown2 before tagger:   "<< num_MC_NewPar_down2_before <<endl;

  //Par3
  TF1 *MC_Eff_NewPar_up3_f =new TF1("MC_Eff_NewPar_up3_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_MC_up3->GetParameter(i));
  Double_t num_MC_NewPar_up3_before = MC_Eff_NewPar_up3_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp3 before tagger:   "<< num_MC_NewPar_up3_before <<endl;

  TF1 *MC_Eff_NewPar_down3_f =new TF1("MC_Eff_NewPar_down3_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_MC_dn3->GetParameter(i));
  Double_t num_MC_NewPar_down3_before = MC_Eff_NewPar_down3_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown3 before tagger:   "<< num_MC_NewPar_down3_before <<endl;

  //Par4
  TF1 *MC_Eff_NewPar_up4_f =new TF1("MC_Eff_NewPar_up4_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_MC_up4->GetParameter(i));
  Double_t num_MC_NewPar_up4_before = MC_Eff_NewPar_up4_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp4 before tagger:   "<< num_MC_NewPar_up4_before <<endl;

  TF1 *MC_Eff_NewPar_down4_f =new TF1("MC_Eff_NewPar_down4_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_MC_dn4->GetParameter(i));
  Double_t num_MC_NewPar_down4_before = MC_Eff_NewPar_down4_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown4 before tagger:   "<< num_MC_NewPar_down4_before <<endl;

  //Par5
  TF1 *MC_Eff_NewPar_up5_f =new TF1("MC_Eff_NewPar_up5_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_MC_up5->GetParameter(i));
  Double_t num_MC_NewPar_up5_before = MC_Eff_NewPar_up5_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp5 before tagger:   "<< num_MC_NewPar_up5_before <<endl;

  TF1 *MC_Eff_NewPar_down5_f =new TF1("MC_Eff_NewPar_down5_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_MC_dn5->GetParameter(i));
  Double_t num_MC_NewPar_down5_before = MC_Eff_NewPar_down5_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown5 before tagger:   "<< num_MC_NewPar_down5_before <<endl;

  //Par6
  TF1 *MC_Eff_NewPar_up6_f =new TF1("MC_Eff_NewPar_up6_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_MC_up6->GetParameter(i));
  Double_t num_MC_NewPar_up6_before = MC_Eff_NewPar_up6_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp6 before tagger:   "<< num_MC_NewPar_up6_before <<endl;

  TF1 *MC_Eff_NewPar_down6_f =new TF1("MC_Eff_NewPar_down6_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_MC_dn6->GetParameter(i));
  Double_t num_MC_NewPar_down6_before = MC_Eff_NewPar_down6_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown6 before tagger:   "<< num_MC_NewPar_down6_before <<endl;

 //Par7
  TF1 *MC_Eff_NewPar_up7_f =new TF1("MC_Eff_NewPar_up7_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_MC_up7->GetParameter(i));
  Double_t num_MC_NewPar_up7_before = MC_Eff_NewPar_up7_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp7 before tagger:   "<< num_MC_NewPar_up7_before <<endl;

  TF1 *MC_Eff_NewPar_down7_f =new TF1("MC_Eff_NewPar_down7_f",c_formula_MC_signal, 24,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_MC_dn7->GetParameter(i));
  Double_t num_MC_NewPar_down7_before = MC_Eff_NewPar_down7_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown7 before tagger:   "<< num_MC_NewPar_down7_before <<endl;
  
  Double_t par1_up;
  Double_t par1_down;
  Double_t par2_up;
  Double_t par2_down;
  Double_t par3_up;
  Double_t par3_down;
  Double_t par4_up;
  Double_t par4_down;
  Double_t par5_up;
  Double_t par5_down;
  Double_t par6_up;
  Double_t par6_down;
  Double_t par7_up;
  Double_t par7_down;

  if(num_MC_NewPar_up1_before>num_MC_before) {par1_up=num_MC_NewPar_up1_before;par1_down=num_MC_NewPar_down1_before;}
  else {par1_down=num_MC_NewPar_up1_before;par1_up=num_MC_NewPar_down1_before;}

  if(num_MC_NewPar_up2_before>num_MC_before) {par2_up=num_MC_NewPar_up2_before;par2_down=num_MC_NewPar_down2_before;}
  else {par2_down=num_MC_NewPar_up2_before;par2_up=num_MC_NewPar_down2_before;}

  if(num_MC_NewPar_up3_before>num_MC_before) {par3_up=num_MC_NewPar_up3_before;par3_down=num_MC_NewPar_down3_before;}
  else {par3_down=num_MC_NewPar_up3_before;par3_up=num_MC_NewPar_down3_before;}

  if(num_MC_NewPar_up4_before>num_MC_before) {par4_up=num_MC_NewPar_up4_before;par4_down=num_MC_NewPar_down4_before;}
  else {par4_down=num_MC_NewPar_up4_before;par4_up=num_MC_NewPar_down4_before;}

  if(num_MC_NewPar_up5_before>num_MC_before) {par5_up=num_MC_NewPar_up5_before;par5_down=num_MC_NewPar_down5_before;}
  else {par5_down=num_MC_NewPar_up5_before;par5_up=num_MC_NewPar_down5_before;}

  if(num_MC_NewPar_up6_before>num_MC_before) {par6_up=num_MC_NewPar_up6_before;par6_down=num_MC_NewPar_down6_before;}
  else {par6_down=num_MC_NewPar_up6_before;par6_up=num_MC_NewPar_down6_before;}

  if(num_MC_NewPar_up7_before>num_MC_before) {par7_up=num_MC_NewPar_up7_before;par7_down=num_MC_NewPar_down7_before;}
  else {par7_down=num_MC_NewPar_up7_before;par7_up=num_MC_NewPar_down7_before;}

  Double_t all_up= TMath::Power(par1_up-num_MC_before,2)+TMath::Power(par2_up-num_MC_before,2)+TMath::Power(par3_up-num_MC_before,2)+TMath::Power(par4_up-num_MC_before,2)+TMath::Power(par5_up-num_MC_before,2)+TMath::Power(par6_up-num_MC_before,2);
  Double_t all_down= TMath::Power(par1_down-num_MC_before,2)+TMath::Power(par2_down-num_MC_before,2)+TMath::Power(par3_down-num_MC_before,2)+TMath::Power(par4_down-num_MC_before,2)+TMath::Power(par5_down-num_MC_before,2)+TMath::Power(par6_down-num_MC_before,2);
 

  //write differences in file
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile <<"error calculation: MC signal vorher "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "Parameter 1 Upvariation "<< par1_up-num_MC_before<<endl;
  myfile << "Parameter 1 Downvariation "<< par1_down-num_MC_before<<endl;
  myfile << "Parameter 2 Upvariation "<< par2_up-num_MC_before<<endl;
  myfile << "Parameter 2 Downvariation "<< par2_down-num_MC_before<<endl;
  myfile << "Parameter 3 Upvariation "<< par3_up-num_MC_before<<endl;
  myfile << "Parameter 3 Downvariation "<< par3_down-num_MC_before<<endl;
  myfile << "Parameter 4 Upvariation "<< par4_up-num_MC_before<<endl;
  myfile << "Parameter 4 Downvariation "<< par4_down-num_MC_before<<endl;
  myfile << "Parameter 5 Upvariation "<< par5_up-num_MC_before<<endl;
  myfile << "Parameter 5 Downvariation "<< par5_down-num_MC_before<<endl;
  myfile << "Parameter 6 Upvariation "<< par6_up-num_MC_before<<endl;
  myfile << "Parameter 6 Downvariation "<< par6_down-num_MC_before<<endl;
  myfile << "Parameter 7 Upvariation "<< par7_up-num_MC_before<<endl;
  myfile << "Parameter 7 Downvariation "<< par7_down-num_MC_before<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "all up variations quadraticly added: "<<TMath::Sqrt(all_up)<<endl;
  myfile << "all down variations quadraticly added: -"<<TMath::Sqrt(all_down)<<endl;
  Double_t error_MC_before_up = TMath::Sqrt(all_up);
  Double_t error_MC_before_down = TMath::Sqrt(all_down);



 //integrate over each variation and save the difference to normal number of bkg events in MC before tagger
  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "integration of all up and down variations MC bkg: " << number_back_MC_miss <<endl;
  cout << "=======================================================================" << endl << endl << endl;

  // bkg_fit function has to be express by 7 paramerters
  stringstream sstr_MC_bkg;
  sstr_MC_bkg  << "(" << e_tr_MC[0] << "*[0]+(" <<e_tr_MC[1]<<")*[1]+("<<e_tr_MC[2]<<")*[2]+("<<e_tr_MC[3]<<")*[3]+("<<e_tr_MC[4]<<")*[4]+("<<e_tr_MC[5]<<")*[5]+("<<e_tr_MC[6]<<")*[6]" <<")*(1-TMath::Erf((x-" <<"(" << f_tr_MC[0] << "*[0]+(" <<f_tr_MC[1]<<")*[1]+("<<f_tr_MC[2]<<")*[2]+("<<f_tr_MC[3]<<")*[3]+("<<f_tr_MC[4]<<")*[4]+("<<f_tr_MC[5]<<")*[5]+("<<f_tr_MC[6]<<")*[6]" <<")" <<")/(1.4 * "<<
    "(" << g_tr_MC[0] << "*[0]+(" <<g_tr_MC[1]<<")*[1]+("<<g_tr_MC[2]<<")*[2]+("<<g_tr_MC[3]<<")*[3]+("<<g_tr_MC[4]<<")*[4]+("<<g_tr_MC[5]<<")*[5]+("<<g_tr_MC[6]<<")*[6]" <<")"<<")))";
  string s_formula_MC_bkg = sstr_MC_bkg.str();
  const char * c_formula_MC_bkg = s_formula_MC_bkg.c_str();

  //Integrate over all up and down variation itself
  //Par1
  TF1 *MC_bkg_Eff_NewPar_up1_f =new TF1("MC_bkg_Eff_NewPar_up1_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_MC_up1->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up1_before = MC_bkg_Eff_NewPar_up1_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp1 before tagger:   "<< num_MC_bkg_NewPar_up1_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down1_f =new TF1("MC_bkg_Eff_NewPar_down1_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_MC_dn1->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down1_before = MC_bkg_Eff_NewPar_down1_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown1 before tagger:   "<< num_MC_bkg_NewPar_down1_before <<endl;

  //Par2
  TF1 *MC_bkg_Eff_NewPar_up2_f =new TF1("MC_bkg_Eff_NewPar_up2_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_MC_up2->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up2_before = MC_bkg_Eff_NewPar_up2_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp2 before tagger:   "<< num_MC_bkg_NewPar_up2_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down2_f =new TF1("MC_bkg_Eff_NewPar_down2_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_MC_dn2->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down2_before = MC_bkg_Eff_NewPar_down2_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown2 before tagger:   "<< num_MC_bkg_NewPar_down2_before <<endl;

  //Par3
  TF1 *MC_bkg_Eff_NewPar_up3_f =new TF1("MC_bkg_Eff_NewPar_up3_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_MC_up3->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up3_before = MC_bkg_Eff_NewPar_up3_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp3 before tagger:   "<< num_MC_bkg_NewPar_up3_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down3_f =new TF1("MC_bkg_Eff_NewPar_down3_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_MC_dn3->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down3_before = MC_bkg_Eff_NewPar_down3_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown3 before tagger:   "<< num_MC_bkg_NewPar_down3_before <<endl;

  //Par4
  TF1 *MC_bkg_Eff_NewPar_up4_f =new TF1("MC_bkg_Eff_NewPar_up4_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_MC_up4->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up4_before = MC_bkg_Eff_NewPar_up4_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp4 before tagger:   "<< num_MC_bkg_NewPar_up4_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down4_f =new TF1("MC_bkg_Eff_NewPar_down4_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_MC_dn4->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down4_before = MC_bkg_Eff_NewPar_down4_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown4 before tagger:   "<< num_MC_bkg_NewPar_down4_before <<endl;

  //Par5
  TF1 *MC_bkg_Eff_NewPar_up5_f =new TF1("MC_bkg_Eff_NewPar_up5_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_MC_up5->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up5_before = MC_bkg_Eff_NewPar_up5_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp5 before tagger:   "<< num_MC_bkg_NewPar_up5_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down5_f =new TF1("MC_bkg_Eff_NewPar_down5_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_MC_dn5->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down5_before = MC_bkg_Eff_NewPar_down5_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown5 before tagger:   "<< num_MC_bkg_NewPar_down5_before <<endl;

  //Par6
  TF1 *MC_bkg_Eff_NewPar_up6_f =new TF1("MC_bkg_Eff_NewPar_up6_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_MC_up6->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up6_before = MC_bkg_Eff_NewPar_up6_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp6 before tagger:   "<< num_MC_bkg_NewPar_up6_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down6_f =new TF1("MC_bkg_Eff_NewPar_down6_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_MC_dn6->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down6_before = MC_bkg_Eff_NewPar_down6_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown6 before tagger:   "<< num_MC_bkg_NewPar_down6_before <<endl;

 //Par7
  TF1 *MC_bkg_Eff_NewPar_up7_f =new TF1("MC_bkg_Eff_NewPar_up7_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_MC_up7->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up7_before = MC_bkg_Eff_NewPar_up7_f->Integral(24,182) / 2;
  cout<<"MC number for ParUp7 before tagger:   "<< num_MC_bkg_NewPar_up7_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down7_f =new TF1("MC_bkg_Eff_NewPar_down7_f",c_formula_MC_bkg, 24,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_MC_dn7->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down7_before = MC_bkg_Eff_NewPar_down7_f->Integral(24,182) / 2;
  cout<<"MC number for ParDown7 before tagger:   "<< num_MC_bkg_NewPar_down7_before <<endl;

  if(num_MC_bkg_NewPar_up1_before>number_back_MC_miss) {par1_up=num_MC_bkg_NewPar_up1_before;par1_down=num_MC_bkg_NewPar_down1_before;}
  else {par1_down=num_MC_bkg_NewPar_up1_before;par1_up=num_MC_bkg_NewPar_down1_before;}

  if(num_MC_bkg_NewPar_up2_before>number_back_MC_miss) {par2_up=num_MC_bkg_NewPar_up2_before;par2_down=num_MC_bkg_NewPar_down2_before;}
  else {par2_down=num_MC_bkg_NewPar_up2_before;par2_up=num_MC_bkg_NewPar_down2_before;}

  if(num_MC_bkg_NewPar_up3_before>number_back_MC_miss) {par3_up=num_MC_bkg_NewPar_up3_before;par3_down=num_MC_bkg_NewPar_down3_before;}
  else {par3_down=num_MC_bkg_NewPar_up3_before;par3_up=num_MC_bkg_NewPar_down3_before;}

  if(num_MC_bkg_NewPar_up4_before>number_back_MC_miss) {par4_up=num_MC_bkg_NewPar_up4_before;par4_down=num_MC_bkg_NewPar_down4_before;}
  else {par4_down=num_MC_bkg_NewPar_up4_before;par4_up=num_MC_bkg_NewPar_down4_before;}

  if(num_MC_bkg_NewPar_up5_before>number_back_MC_miss) {par5_up=num_MC_bkg_NewPar_up5_before;par5_down=num_MC_bkg_NewPar_down5_before;}
  else {par5_down=num_MC_bkg_NewPar_up5_before;par5_up=num_MC_bkg_NewPar_down5_before;}

  if(num_MC_bkg_NewPar_up6_before>number_back_MC_miss) {par6_up=num_MC_bkg_NewPar_up6_before;par6_down=num_MC_bkg_NewPar_down6_before;}
  else {par6_down=num_MC_bkg_NewPar_up6_before;par6_up=num_MC_bkg_NewPar_down6_before;}

  if(num_MC_bkg_NewPar_up7_before>number_back_MC_miss) {par7_up=num_MC_bkg_NewPar_up7_before;par7_down=num_MC_bkg_NewPar_down7_before;}
  else {par7_down=num_MC_bkg_NewPar_up7_before;par7_up=num_MC_bkg_NewPar_down7_before;}

  all_up= TMath::Power(par1_up-number_back_MC_miss,2)+TMath::Power(par2_up-number_back_MC_miss,2)+TMath::Power(par3_up-number_back_MC_miss,2)+TMath::Power(par4_up-number_back_MC_miss,2)+TMath::Power(par5_up-number_back_MC_miss,2)+TMath::Power(par6_up-number_back_MC_miss,2);
   all_down= TMath::Power(par1_down-number_back_MC_miss,2)+TMath::Power(par2_down-number_back_MC_miss,2)+TMath::Power(par3_down-number_back_MC_miss,2)+TMath::Power(par4_down-number_back_MC_miss,2)+TMath::Power(par5_down-number_back_MC_miss,2)+TMath::Power(par6_down-number_back_MC_miss,2);
 

  //write differences in file
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile <<"error calculation: MC bkg vorher "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "Parameter 1 Upvariation "<< par1_up-number_back_MC_miss<<endl;
  myfile << "Parameter 1 Downvariation "<< par1_down-number_back_MC_miss<<endl;
  myfile << "Parameter 2 Upvariation "<< par2_up-number_back_MC_miss<<endl;
  myfile << "Parameter 2 Downvariation "<< par2_down-number_back_MC_miss<<endl;
  myfile << "Parameter 3 Upvariation "<< par3_up-number_back_MC_miss<<endl;
  myfile << "Parameter 3 Downvariation "<< par3_down-number_back_MC_miss<<endl;
  myfile << "Parameter 4 Upvariation "<< par4_up-number_back_MC_miss<<endl;
  myfile << "Parameter 4 Downvariation "<< par4_down-number_back_MC_miss<<endl;
  myfile << "Parameter 5 Upvariation "<< par5_up-number_back_MC_miss<<endl;
  myfile << "Parameter 5 Downvariation "<< par5_down-number_back_MC_miss<<endl;
  myfile << "Parameter 6 Upvariation "<< par6_up-number_back_MC_miss<<endl;
  myfile << "Parameter 6 Downvariation "<< par6_down-number_back_MC_miss<<endl;
  myfile << "Parameter 7 Upvariation "<< par7_up-number_back_MC_miss<<endl;
  myfile << "Parameter 7 Downvariation "<< par7_down-number_back_MC_miss<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "all up variations quadraticly added: "<<TMath::Sqrt(all_up)<<endl;
  myfile << "all down variations quadraticly added: -"<<TMath::Sqrt(all_down)<<endl;

  // read in histogramm from mistag rate depending on nominal,up,down and correction
  TFile* file = new TFile(mistag_folder+"QCD_"+unc_name+".root", "READ");
  if(unc_name.Contains("btag"))file = new TFile(mistag_folder+"QCD_"+"none"+".root", "READ");
  if(unc_name.Contains("sub"))file = new TFile(mistag_folder+"QCD_"+"none"+".root", "READ");
  TH1F* sf_hist = (TH1F*) file->Get("tot_eff_h");
  Double_t sf = sf_hist->GetBinContent(1);
  
  TFile* file2 = new TFile(mistag_folder+"QCD_none.root", "READ");
  TH1F* error_hist = (TH1F*) file2->Get("tot_err_h");
  Double_t error_sf = error_hist->GetBinContent(1);
 

  //define mistag rate and error
  Double_t corr_mistagrate = sf;
  Double_t error_corr_mistagrate_up = TMath::Sqrt(TMath::Power(error_sf,2));
  Double_t error_corr_mistagrate_down = TMath::Sqrt(TMath::Power(error_sf,2));
  Double_t mistag_rate_MC = number_back/number_back_MC_miss;
  Double_t mistag_rate_data = mistag_rate_MC * corr_mistagrate;
  Double_t error_mistagrate_MC_up = TMath::Sqrt(TMath::Power((1/number_back_MC_miss)*error_back,2) + TMath::Power((number_back/number_back_MC_miss/number_back_MC_miss)*TMath::Sqrt(all_up),2) );
  Double_t error_mistagrate_MC_down = TMath::Sqrt(TMath::Power((1/number_back_MC_miss)*error_back,2) + TMath::Power((number_back/number_back_MC_miss/number_back_MC_miss)*TMath::Sqrt(all_down),2) );
  Double_t error_mistagrate_data_up = TMath::Sqrt((TMath::Power((1/number_back_MC_miss)*error_back,2) + TMath::Power((number_back/number_back_MC_miss/number_back_MC_miss)*TMath::Sqrt(all_up),2)) *TMath::Power(corr_mistagrate,2) + TMath::Power(mistag_rate_MC* error_corr_mistagrate_up,2));
  Double_t error_mistagrate_data_down = TMath::Sqrt((TMath::Power((1/number_back_MC_miss)*error_back,2) + TMath::Power((number_back/number_back_MC_miss/number_back_MC_miss)*TMath::Sqrt(all_down),2)) *TMath::Power(corr_mistagrate,2) + TMath::Power(mistag_rate_MC* error_corr_mistagrate_down,2));

  Double_t num_MC_after = number_sig+ number_back - number_back_MC_miss * mistag_rate_MC;
  cout << "Anzahl sig nachher:  "<<number_sig<<"  +Anzahl nachher back "<< number_back <<" - Anzahl back vorher "<< number_back_MC_miss <<"  *miss" <<mistag_rate_MC<<endl;
  Double_t num_data_after = number_data - number_back_data_miss * mistag_rate_data;
  cout <<"Anzahl nach tagger "<< num_MC_after <<" /Anzahl before tagger  "<<num_MC_before<<endl;
  cout<< "eff MC " << num_MC_after/num_MC_before <<endl;
  cout<< "eff Data " << num_data_after/num_data_before <<endl;
  myfile<< "number of data after subtracting background: "<< num_data_after <<endl;
  myfile<< "number of MC after subtracting background: "<< num_MC_after<<endl;
  myfile<< "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile<< "eff MC " << num_MC_after/num_MC_before <<endl;
  myfile<< "eff data " << num_data_after/num_data_before <<endl;
  myfile<< "-----------------------------------   error -----------------------------------------------------------------"<<endl;
  myfile<< "error MC bkg after tagger:  " << error_back <<endl;
  myfile<< "error MC sig after tagger:  " << error_sig <<endl;
  myfile<< "error Data after tagger:    " << error_data <<endl;


  Double_t error_MC_after_up = TMath::Sqrt(TMath::Power(error_sig,2) + TMath::Power(error_back,2) + TMath::Power((TMath::Sqrt(all_up)*mistag_rate_MC),2) + TMath::Power(number_back_MC_miss * error_mistagrate_MC_up ,2));
  Double_t error_MC_after_down = TMath::Sqrt(TMath::Power(error_sig,2) + TMath::Power(error_back,2) + TMath::Power((TMath::Sqrt(all_down)*mistag_rate_MC),2) + TMath::Power(number_back_MC_miss * error_mistagrate_MC_down ,2));
  myfile<< "error MC after tagger up:  "<<error_MC_after_up <<endl;
  myfile<< "error MC after tagger down:  "<<error_MC_after_down <<endl;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data//
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout<<endl<<endl<<endl;
  cout <<"2. N_Data error calculation"<<endl;
  //cov matrix out of fit
  TMatrixDSym cov_data = fit_data_result->GetCovarianceMatrix();  
  if(b_error){
    cout << "Kovarianzmatrix nach inital fit:" << endl << endl;
    cov_data.Print();
    cout << endl << endl << endl << endl;
  }
  //resave cov matrix to calculate the eigenvalues and eigenvectors
  const TMatrixDSymEigen eigen_cov_data(cov_data);

  //calculate eigenvalues and eigenvectors
  const TVectorD eigen_values_data = eigen_cov_data.GetEigenValues();
  const TMatrixD eigen_vectors_data = eigen_cov_data.GetEigenVectors();
  if(b_error){
    cout << "eigen_values nach inital fit:" << endl << endl;
    eigen_values_data.Print();
    cout << endl << endl << endl << endl;
    cout << "eigen_vectors_data nach inital fit:" << endl << endl;
    eigen_vectors_data.Print();
    cout << endl << endl << endl << endl;
  }

  if(b_error){
    //multiply eigen values with unitary matrix 
    TMatrixD M_Diag_data(6,6);
    M_Diag_data.UnitMatrix();
    for(int i=0; i<6; i++){
      double tmp_data =eigen_values_data[i];
      TMatrixDRow(M_Diag_data,i)(i) = tmp_data;
    }
 
    cout << "M_Diag_data nach inital fit:" << endl << endl;
    M_Diag_data.Print();
    cout << endl << endl << endl << endl;
  }

  //transform eigen vectors into row vectors 
  TMatrixD RT_data(eigen_vectors_data);
  RT_data.T();
  if(b_error){
    cout << "Test: eigenvectorsT * cov * eigenvectors = eigen values * 1 [M_Diag_data]" << endl << endl;
    TMatrixD test_diag_data = RT_data * cov_data * eigen_vectors_data;
    test_diag_data.Print();
    cout << endl << endl << endl << endl;
  }

  //found transformation that diagonalised the cov matrix so we can used it to determine the uncorrelated parameters by P' = einenvectorsT * P


  //save old parameters P in a vector
  const double a_data = fit_data_result->Parameter(0);
  const double b_data = fit_data_result->Parameter(1);
  const double c_data = fit_data_result->Parameter(2);
  const double d_data = fit_data_result->Parameter(3);
  const double e_data = fit_data_result->Parameter(4);
  const double f_data = fit_data_result->Parameter(5);
  const double g_data = fit_data_result->Parameter(6);
  const double old_params_data[7] = {a_data,b_data,c_data,d_data,e_data,f_data,g_data};
  const TVectorD V_Old_Param_data(7,old_params_data);

  if(b_error){
    cout << "V_Old_Param_data nach inital fit:" << endl << endl;
    V_Old_Param_data.Print();
    cout << endl << endl << endl << endl;
  }

  //calculate parameters in new basis
  TDecompSVD svd_data(eigen_vectors_data);
  Bool_t ok_data;
  const TVectorD V_New_Param_data = svd_data.Solve(V_Old_Param_data,ok_data);
  if(b_error){
    cout << "V_New_Param_data nach inital fit:" << endl << endl;
    V_New_Param_data.Print();
    cout << endl << endl << endl << endl;
    cout <<"zuruecktransformierte alte werte:"<<endl;
    test_diag_data = eigen_vectors_data * V_New_Param_data;
    test_diag_data.Print();
    cout << endl << endl << endl << endl;
  }
 /****************************/
  /*                          */
  /*    expression by new     */
  /*                          */
  /****************************/

  //Express old parameters in fit function by new parameters such that they yield the old ones.
  //should yield similar fit results if they are transformed back afterwards, but the errors on the new ones are uncorrelated by construction
  //simply vary each of the new parameters up and down and take the envelope as systematic uncertainty


  //parametrize old parameters by using new ones with eigen_vectors_data
  TMatrixD M_Dummy_data(eigen_vectors_data);
  double a_tr_data[7], b_tr_data[7], c_tr_data[7], d_tr_data[7], e_tr_data[7], f_tr_data[7], g_tr_data[7];
  for (int i=0; i<7; i++){
    a_tr_data[i] = TMatrixDRow(M_Dummy_data,0)[i];
    b_tr_data[i] = TMatrixDRow(M_Dummy_data,1)[i];
    c_tr_data[i] = TMatrixDRow(M_Dummy_data,2)[i];
    d_tr_data[i] = TMatrixDRow(M_Dummy_data,3)[i];
    e_tr_data[i] = TMatrixDRow(M_Dummy_data,4)[i];
    f_tr_data[i] = TMatrixDRow(M_Dummy_data,5)[i];
    g_tr_data[i] = TMatrixDRow(M_Dummy_data,6)[i];
  }

  //string of new fit function with uncorrelated parameters
  stringstream sstr_data;
  sstr_data  << "(" << d_tr_data[0] << "*[0]+(" <<d_tr_data[1]<<")*[1]+("<<d_tr_data[2]<<")*[2]+("<<d_tr_data[3]<<")*[3]+("<<d_tr_data[4]<<")*[4]+("<<d_tr_data[5]<<")*[5]+("<<d_tr_data[6]<<")*[6]" <<")*TMath::Voigt(x-"<<"(" << c_tr_data[0] << "*[0]+(" <<c_tr_data[1]<<")*[1]+("<<c_tr_data[2]<<")*[2]+("<<c_tr_data[3]<<")*[3]+("<<c_tr_data[4]<<")*[4]+("<<c_tr_data[5]<<")*[5]+("<<c_tr_data[6]<<")*[6]" <<"),"<<"(" << a_tr_data[0] << "*[0]+(" <<a_tr_data[1]<<")*[1]+("<<a_tr_data[2]<<")*[2]+("<<a_tr_data[3]<<")*[3]+("<<a_tr_data[4]<<")*[4]+("<<a_tr_data[5]<<")*[5]+("<<a_tr_data[6]<<")*[6]" <<"),"<< "(" << b_tr_data[0] << "*[0]+(" <<b_tr_data[1]<<")*[1]+("<<b_tr_data[2]<<")*[2]+("<<b_tr_data[3]<<")*[3]+("<<b_tr_data[4]<<")*[4]+("<<b_tr_data[5]<<")*[5]+("<<b_tr_data[6]<<")*[6]" <<")"<<",4)"<< "+" << "(" << e_tr_data[0] << "*[0]+(" <<e_tr_data[1]<<")*[1]+("<<e_tr_data[2]<<")*[2]+("<<e_tr_data[3]<<")*[3]+("<<e_tr_data[4]<<")*[4]+("<<e_tr_data[5]<<")*[5]+("<<e_tr_data[6]<<")*[6]" <<")*(1-TMath::Erf((x-" <<"(" << f_tr_data[0] << "*[0]+(" <<f_tr_data[1]<<")*[1]+("<<f_tr_data[2]<<")*[2]+("<<f_tr_data[3]<<")*[3]+("<<f_tr_data[4]<<")*[4]+("<<f_tr_data[5]<<")*[5]+("<<f_tr_data[6]<<")*[6]" <<")" <<")/(1.4 * "<<"(" << g_tr_data[0] << "*[0]+(" <<g_tr_data[1]<<")*[1]+("<<g_tr_data[2]<<")*[2]+("<<g_tr_data[3]<<")*[3]+("<<g_tr_data[4]<<")*[4]+("<<g_tr_data[5]<<")*[5]+("<<g_tr_data[6]<<")*[6]" <<")"<<")))";

  //signal: TMath::Voigt(x-[2], [0], [1], 4)*[3]
  //background:  [0]*(1 - TMath::Erf((x-[1])/(1.4*[2])))
 
  string s_formula_data = sstr_data.str();
  const char * c_formula_data = s_formula_data.c_str();
  if(b_error){
    cout << "Fit Funktion mit neuen Parametern: " << endl;
    cout << c_formula_data << endl<<endl<<endl;
  }

  //New fit fuction with uncoorelated parameters
  TF1* f_NewParam_data = new TF1("f_NewParam_data",c_formula_data,24,182);
  f_NewParam_data->SetParameter(0,V_New_Param_data[0]);
  f_NewParam_data->SetParameter(1,V_New_Param_data[1]);
  f_NewParam_data->SetParameter(2,V_New_Param_data[2]);
  f_NewParam_data->SetParameter(3,V_New_Param_data[3]);
  f_NewParam_data->SetParameter(4,V_New_Param_data[4]);
  f_NewParam_data->SetParameter(5,V_New_Param_data[5]);
  f_NewParam_data->FixParameter(6,V_New_Param_data[6]);
  f_NewParam_data->SetLineColor(kGreen+3);
  if(b_error)for(int i=24;i<183;i=i+5)cout <<"new: "<<f_NewParam_data->Eval(i)<<" old: "<< data_fit->Eval(i)<<endl;

  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "Fit with new parameters: " << endl;
  cout << "=======================================================================" << endl << endl << endl;

  TCanvas* cfitnew_data = new TCanvas("cfitnewdata", "Fit function in new parameters, data",10,10,700,900);
  TFitResultPtr fit_result_data = data->Fit(f_NewParam_data,"SR"); 
  cfitnew_data->Print("Fit_signal_background_new.eps");
  cout << "Fit in new parameters, data: " << endl;
  fit_result_data->Print("V");


  //calculate fit parameter errors by hand: keep 6 fixed and vary one until chi2 increases by 1
  cout << endl << endl << endl << endl << endl;
  cout << "======================================================================="  << endl;
  cout << "Calculate errors by hand " << endl;
  cout << "=======================================================================" << endl << endl << endl;
  
  //define error function
  TF1* f_NewParam_data_error = new TF1("f_NewParam_data_error",c_formula_data,24,182);

  //fix all fit values
  TCanvas* c_dummy_data = new TCanvas("c_dummy_data", "Fits for chi2 in data", 10,10,700,900);
  for(int i=0; i<7; i++){
    f_NewParam_data_error->FixParameter(i,fit_result_data->Parameter(i));
  }
  
  cout << endl << endl << endl << "FIT BY HAND for CHI2 calculation: SIGNAL" << endl << endl << endl;

  //smalles chi2 out of the fit before
  data->Fit(f_NewParam_data_error,"QR");
  double chi2_best_data = f_NewParam_data_error->GetChisquare();
  cout << "chi2_best_data (mimimun out of the fit) "<< chi2_best_data << endl;

  //set up arrays to save the errors 
  double pars_data[7], pars_up_data[7], pars_dn_data[7], err_pars_up_data[7], err_pars_dn_data[7];
  for(int i=0; i<7; i++) pars_data[i] = f_NewParam_data_error->GetParameter(i);
  bool pars_up_set_data[7] = {false,false,false,false,false,false,false};
  bool pars_dn_set_data[7] = {false,false,false,false,false,false,false};
  TGraph* g_chi2_pars_data[7];
  for(int i=0; i<7; i++) g_chi2_pars_data[i] = new TGraph(50000);
  for_percent = 0;


  //varying all parameters in steps of 1/1000*par
  for(int j=0; j<7; j++){

    //reset parameters
    for(int k=0; k<7; k++) f_NewParam_data_error->FixParameter(k,fit_result_data->Parameter(k));
    
    double chi2_diff_data = 0;
    double varied_par_data_old =0;
    double varied_par_data=0;
    for(int i=0; i<50000; i++){
      for_percent++;
      varied_par_data_old = varied_par_data;
      if(j==0)  varied_par_data = (pars_data[j]-800) + pars_data[j]/100000 * i;
      if(j==1)  varied_par_data = (pars_data[j]-80) + pars_data[j]/100000 * i;
      if(j==2)  varied_par_data = (pars_data[j]-20) - pars_data[j]/100000 * i;
      if(j==3)  varied_par_data = (pars_data[j]-2) - pars_data[j]/1000000 * i;
      if(j==4)  varied_par_data = (pars_data[j]-10) - pars_data[j]/100000 * i;
      if(j==5)  varied_par_data = (pars_data[j]-10) + pars_data[j]/100000 * i;
      if(j==6)  varied_par_data = (pars_data[j]-10) + pars_data[j]/10000 * i;

      // if(j==0)  varied_par_data = (pars_data[j]-40) + pars_data[j]/1000000 * i;
      // if(j==1)  varied_par_data = (pars_data[j]-2) + pars_data[j]/100000 * i;
      // if(j==2)  varied_par_data = (pars_data[j]-2) + pars_data[j]/100000 * i;
      // if(j==3)  varied_par_data = (pars_data[j]-2) - pars_data[j]/1000000 * i;
      // if(j==4)  varied_par_data = (pars_data[j]-2) + pars_data[j]/1000000 * i;
      // if(j==5)  varied_par_data = (pars_data[j]-5) - pars_data[j]/100000 * i;
      // if(j==6)  varied_par_data = (pars_data[j]-10) + pars_data[j]/10000 * i;
     
      // varied_par_data = (pars_data[j]-50) + pars_data[j]/10000 * i;

      //original double varied_par_data = -20*pars_data[j] + pars_data[j]/1000 * i;
      f_NewParam_data_error->FixParameter(j,varied_par_data);
     
      data->Fit(f_NewParam_data_error,"QR");

      double chi2_tmp_data = f_NewParam_data_error->GetChisquare();
      chi2_diff_data = chi2_tmp_data - chi2_best_data;

      //  if(i%500 == 0) cout << "\r"  << for_percent/3500  << "%, " <<  "Parameter " << j << ", Fit No. " << i  << ", current chi2: " << chi2_tmp_data << " at current parametervalue: " << varied_par_data << "           "  << flush;
      if(i%500 == 0) if(j==5)cout << "\r"  << for_percent/3500  << "%, " <<  "Parameter " << j << ", Fit No. " << i  << ", current chi2: " << chi2_tmp_data << " at current parametervalue: " << varied_par_data << "           "  << endl;


      if(!pars_dn_set_data[j] && chi2_diff_data < 1) {
 	pars_dn_data[j] =varied_par_data_old;
 	pars_dn_set_data[j] = true;
      }
      if(pars_dn_set_data[j] && !pars_up_set_data[j] && chi2_diff_data >= 1){
 	pars_up_data[j] = varied_par_data;
 	pars_up_set_data[j] = true;
      }

      //draw chi2 as function of p0
      g_chi2_pars_data[j]->SetPoint(i,varied_par_data, chi2_tmp_data);
    }
    if(pars_dn_data[j] > pars_up_data[j]) swap(pars_dn_data[j],pars_up_data[j]);
    
    err_pars_up_data[j] = abs(pars_data[j]-pars_up_data[j]);
    err_pars_dn_data[j] = abs(pars_data[j]-pars_dn_data[j]);
    
  }//varying all parameters in steps of 1/1000*par

  //define Line of the up and down variation in chi2
  TLine* l_pars_dn_data[7];
  TLine* l_pars_up_data[7];
  TLine* l_pars_central_data[7];
  for(int i=0; i<7; i++){
    l_pars_up_data[i] = new TLine(pars_up_data[i], chi2_best_data - 1, pars_up_data[i], chi2_best_data+1);
    l_pars_dn_data[i] = new TLine(pars_dn_data[i], chi2_best_data - 1, pars_dn_data[i], chi2_best_data+1);
    l_pars_central_data[i] = new TLine(pars_data[i], chi2_best_data, pars_data[i], chi2_best_data - 1);
    l_pars_up_data[i]->SetLineWidth(3);
    l_pars_up_data[i]->SetLineColor(kRed);
    l_pars_dn_data[i]->SetLineWidth(3);
    l_pars_dn_data[i]->SetLineColor(kRed);
    l_pars_central_data[i]->SetLineWidth(3);
    l_pars_central_data[i]->SetLineColor(kBlue);
  }
  for(int i=0; i<7; i++){
    stringstream n_data;
    n_data << "Parameter " << i+1;
    string s_n_data = n_data.str();
    const char * c_n_data = s_n_data.c_str();
    g_chi2_pars_data[i]->SetMinimum(chi2_best_data - 1);
    g_chi2_pars_data[i]->SetMaximum(chi2_best_data + 10);
    g_chi2_pars_data[i]->SetTitle("");
    g_chi2_pars_data[i]->GetXaxis()->SetTitle(c_n_data);
    g_chi2_pars_data[i]->GetXaxis()->SetTitleSize(0.044);
    g_chi2_pars_data[i]->GetYaxis()->SetTitle("#chi^{2}");
    g_chi2_pars_data[i]->GetYaxis()->SetTitleSize(0.044);
    g_chi2_pars_data[i]->GetXaxis()->SetLimits(pars_dn_data[i]-2*err_pars_dn_data[i],pars_up_data[i]+2*err_pars_up_data[i]);
  }

  // example of a error calculated parameter by hand
  TCanvas* c_chi2_p1_data = new TCanvas("c_chi2_p1_data", "chi2 (p1)_data", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_data[1]->Draw();
  l_pars_up_data[1]->Draw("SAME");
  l_pars_dn_data[1]->Draw("SAME");
  l_pars_central_data[1]->Draw("SAME");
  c_chi2_p1_data->Print(folder + "Chi2_data_p1.eps");

  TCanvas* c_chi2_p0_data = new TCanvas("c_chi2_p0_data", "chi2 (p0)_data", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_data[0]->Draw();
  l_pars_up_data[0]->Draw("SAME");
  l_pars_dn_data[0]->Draw("SAME");
  l_pars_central_data[0]->Draw("SAME");
  c_chi2_p0_data->Print(folder + "Chi2_data_p0.eps");

  TCanvas* c_chi2_p2_data = new TCanvas("c_chi2_p2_data", "chi2 (p2)_data", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_data[2]->Draw();
  l_pars_up_data[2]->Draw("SAME");
  l_pars_dn_data[2]->Draw("SAME");
  l_pars_central_data[2]->Draw("SAME");
  c_chi2_p2_data->Print(folder + "Chi2_data_p2.eps");

  TCanvas* c_chi2_p3_data = new TCanvas("c_chi2_p3_data", "chi2 (p3)_data", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_data[3]->Draw();
  l_pars_up_data[3]->Draw("SAME");
  l_pars_dn_data[3]->Draw("SAME");
  l_pars_central_data[3]->Draw("SAME");
  c_chi2_p3_data->Print(folder + "Chi2_data_p3.eps");

  TCanvas* c_chi2_p4_data = new TCanvas("c_chi2_p4_data", "chi2 (p4)_data", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_data[4]->Draw();
  l_pars_up_data[4]->Draw("SAME");
  l_pars_dn_data[4]->Draw("SAME");
  l_pars_central_data[4]->Draw("SAME");
  c_chi2_p4_data->Print(folder + "Chi2_data_p4.eps");

  TCanvas* c_chi2_p5_data = new TCanvas("c_chi2_p5_data", "chi2 (p5)_data", 1);
  gPad->SetTickx();
  gPad->SetTicky();
  g_chi2_pars_data[5]->Draw();
  l_pars_up_data[5]->Draw("SAME");
  l_pars_dn_data[5]->Draw("SAME");
  l_pars_central_data[5]->Draw("SAME");
  c_chi2_p5_data->Print(folder + "Chi2_data_p5.eps");

  //print all uncorrelated parameters with errors
  cout<<endl;
  for(int j=0; j<7; j++){
    cout << "Result data: par " << j << " = " << pars_data[j] << " (+" << err_pars_up_data[j] << ") (-" << err_pars_dn_data[j] << ")" << endl;
  }

  TF1* f_NewParam_data_up1 = new TF1("f_NewParam_data_up1", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn1 = new TF1("f_NewParam_data_dn1", c_formula_data,24, 182);
  TF1* f_NewParam_data_up2 = new TF1("f_NewParam_data_up2", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn2 = new TF1("f_NewParam_data_dn2", c_formula_data,24, 182);
  TF1* f_NewParam_data_up3 = new TF1("f_NewParam_data_up3", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn3 = new TF1("f_NewParam_data_dn3", c_formula_data,24, 182);
  TF1* f_NewParam_data_up4 = new TF1("f_NewParam_data_up4", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn4 = new TF1("f_NewParam_data_dn4", c_formula_data,24, 182);
  TF1* f_NewParam_data_up5 = new TF1("f_NewParam_data_up5", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn5 = new TF1("f_NewParam_data_dn5", c_formula_data,24, 182);
  TF1* f_NewParam_data_up6 = new TF1("f_NewParam_data_up6", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn6 = new TF1("f_NewParam_data_dn6", c_formula_data,24, 182);
  TF1* f_NewParam_data_up7 = new TF1("f_NewParam_data_up7", c_formula_data,24, 182);
  TF1* f_NewParam_data_dn7 = new TF1("f_NewParam_data_dn7", c_formula_data,24, 182);
  TF1* f_NewParam_data_upall = new TF1("f_NewParam_data_upall", c_formula_data,24, 182);
  TF1* f_NewParam_data_dnall = new TF1("f_NewParam_data_dnall", c_formula_data,24, 182);

  for(int i=0; i<7; i++){
    f_NewParam_data_up1->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn1->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_up2->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn2->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_up3->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn3->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_up4->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn4->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_up5->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn5->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_up6->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn6->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_up7->FixParameter(i,fit_result_data->Parameter(i));
    f_NewParam_data_dn7->FixParameter(i,fit_result_data->Parameter(i));

    if(i==0){
      f_NewParam_data_up1->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn1->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
    else if (i==1){
      f_NewParam_data_up2->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn2->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
    else if (i==2){
      f_NewParam_data_up3->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn3->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
    else if (i==3){
      f_NewParam_data_up4->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn4->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
    else if (i==4){
      f_NewParam_data_up5->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn5->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
    else if (i==5){
      f_NewParam_data_up6->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn6->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
    else if (i==6){
      f_NewParam_data_up7->FixParameter(i,fit_result_data->Parameter(i) + err_pars_up_data[i]);
      f_NewParam_data_dn7->FixParameter(i,fit_result_data->Parameter(i) - err_pars_dn_data[i]);
    }
  }

  TCanvas* cupdndata = new TCanvas("cupdndata", "Functions varied up and down, data",10,10,700,900);
  gPad->SetTickx();
  gPad->SetTicky();

  leg = new TLegend(0.6,0.4,0.89,0.89);
  leg->SetBorderSize(0);
  
  f_NewParam_data->GetXaxis()->SetTitle("M_{W}^{rec} [GeV/c^{2}]");
  f_NewParam_data->GetYaxis()->SetTitle("Events");
  f_NewParam_data->GetXaxis()->SetTitleSize(0.045);
  f_NewParam_data->GetYaxis()->SetTitleSize(0.045);
  // f_NewParam_data->GetYaxis()->SetRangeUser(0,50);
  f_NewParam_data->SetTitle("");


  // f_NewParam_data->GetYaxis()->SetRangeUser(0, 60);
  f_NewParam_data->Draw();
  leg -> AddEntry(f_NewParam_data,"nominal", "l");

  f_NewParam_data_up1->SetLineColor(3);
  f_NewParam_data_up1->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_up1,"Par. 1 up", "l");

  f_NewParam_data_dn1->SetLineColor(4);
  f_NewParam_data_dn1->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_dn1,"Par. 1 down", "l");

  f_NewParam_data_up2->SetLineColor(5);
  f_NewParam_data_up2->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_up2,"Par. 2 up", "l");

  f_NewParam_data_dn2->SetLineColor(6);
  f_NewParam_data_dn2->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_dn2,"Par. 2 down", "l");

  f_NewParam_data_up3->SetLineColor(7);
  f_NewParam_data_up3->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_up3,"Par. 3 up", "l");

  f_NewParam_data_dn3->SetLineColor(8);
  f_NewParam_data_dn3->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_dn3,"Par. 3 down", "l");

  f_NewParam_data_up4->SetLineColor(9);
  f_NewParam_data_up4->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_up4,"Par. 4 up", "l");

  f_NewParam_data_dn4->SetLineColor(15);
  f_NewParam_data_dn4->Draw("SAME"); 
  leg -> AddEntry(f_NewParam_data_dn4,"Par. 4 down", "l");

  f_NewParam_data_up5->SetLineColor(11);
  f_NewParam_data_up5->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_up5,"Par. 5 up", "l");

  f_NewParam_data_dn5->SetLineColor(12);
  f_NewParam_data_dn5->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_dn5,"Par. 5 down", "l");

  f_NewParam_data_up6->SetLineColor(40);
  f_NewParam_data_up6->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_up6,"Par. 6 up", "l");

  f_NewParam_data_dn6->SetLineColor(42);
  f_NewParam_data_dn6->Draw("SAME");
  leg -> AddEntry(f_NewParam_data_dn6,"Par. 6 down", "l");

  leg->Draw("SAME");
  // f_NewParam_data_up7->SetLineColor(32);
  // f_NewParam_data_up7->Draw("");
  // f_NewParam_data_dn7->SetLineColor(39);
  // f_NewParam_data_dn7->Draw("SAME");
  cupdndata->Print(folder + "variations_data.eps");


  //integrate over each variation and save the difference to normal number of sig events in data before tagger
  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "integration of all up and down variations data sig: " << num_data_before <<endl;
  cout << "=======================================================================" << endl << endl << endl;

  // signal_fit function has to be express by 7 paramerters
  stringstream sstr_data_signal;
  sstr_data_signal  << "(" << d_tr_data[0] << "*[0]+(" <<d_tr_data[1]<<")*[1]+("<<d_tr_data[2]<<")*[2]+("<<d_tr_data[3]<<")*[3]+("<<d_tr_data[4]<<")*[4]+("<<d_tr_data[5]<<")*[5]+("<<d_tr_data[6]<<")*[6]" <<")*TMath::Voigt(x-"<<"(" << c_tr_data[0] << "*[0]+(" <<c_tr_data[1]<<")*[1]+("<<c_tr_data[2]<<")*[2]+("<<c_tr_data[3]<<")*[3]+("<<c_tr_data[4]<<")*[4]+("<<c_tr_data[5]<<")*[5]+("<<c_tr_data[6]<<")*[6]" <<"),"<<"(" << a_tr_data[0] << "*[0]+(" <<a_tr_data[1]<<")*[1]+("<<a_tr_data[2]<<")*[2]+("<<a_tr_data[3]<<")*[3]+("<<a_tr_data[4]<<")*[4]+("<<a_tr_data[5]<<")*[5]+("<<a_tr_data[6]<<")*[6]" <<"),"<< "(" << b_tr_data[0] << "*[0]+(" <<b_tr_data[1]<<")*[1]+("<<b_tr_data[2]<<")*[2]+("<<b_tr_data[3]<<")*[3]+("<<b_tr_data[4]<<")*[4]+("<<b_tr_data[5]<<")*[5]+("<<b_tr_data[6]<<")*[6]" <<")"<<",4)";
  string s_formula_data_signal = sstr_data_signal.str();
  const char * c_formula_data_signal = s_formula_data_signal.c_str();

  //Integrate over all up and down variation itself
  //Par1
  TF1 *data_Eff_NewPar_up1_f =new TF1("data_Eff_NewPar_up1_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_data_up1->GetParameter(i));
  Double_t num_data_NewPar_up1_before = data_Eff_NewPar_up1_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp1 before tagger:   "<< num_data_NewPar_up1_before <<endl;

  TF1 *data_Eff_NewPar_down1_f =new TF1("data_Eff_NewPar_down1_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_data_dn1->GetParameter(i));
  Double_t num_data_NewPar_down1_before = data_Eff_NewPar_down1_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown1 before tagger:   "<< num_data_NewPar_down1_before <<endl;

  //Par2
  TF1 *data_Eff_NewPar_up2_f =new TF1("data_Eff_NewPar_up2_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_data_up2->GetParameter(i));
  Double_t num_data_NewPar_up2_before = data_Eff_NewPar_up2_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp2 before tagger:   "<< num_data_NewPar_up2_before <<endl;

  TF1 *data_Eff_NewPar_down2_f =new TF1("data_Eff_NewPar_down2_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_data_dn2->GetParameter(i));
  Double_t num_data_NewPar_down2_before = data_Eff_NewPar_down2_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown2 before tagger:   "<< num_data_NewPar_down2_before <<endl;

  //Par3
  TF1 *data_Eff_NewPar_up3_f =new TF1("data_Eff_NewPar_up3_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_data_up3->GetParameter(i));
  Double_t num_data_NewPar_up3_before = data_Eff_NewPar_up3_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp3 before tagger:   "<< num_data_NewPar_up3_before <<endl;

  TF1 *data_Eff_NewPar_down3_f =new TF1("data_Eff_NewPar_down3_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_data_dn3->GetParameter(i));
  Double_t num_data_NewPar_down3_before = data_Eff_NewPar_down3_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown3 before tagger:   "<< num_data_NewPar_down3_before <<endl;

  //Par4
  TF1 *data_Eff_NewPar_up4_f =new TF1("data_Eff_NewPar_up4_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_data_up4->GetParameter(i));
  Double_t num_data_NewPar_up4_before = data_Eff_NewPar_up4_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp4 before tagger:   "<< num_data_NewPar_up4_before <<endl;

  TF1 *data_Eff_NewPar_down4_f =new TF1("data_Eff_NewPar_down4_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_data_dn4->GetParameter(i));
  Double_t num_data_NewPar_down4_before = data_Eff_NewPar_down4_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown4 before tagger:   "<< num_data_NewPar_down4_before <<endl;

  //Par5
  TF1 *data_Eff_NewPar_up5_f =new TF1("data_Eff_NewPar_up5_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_data_up5->GetParameter(i));
  Double_t num_data_NewPar_up5_before = data_Eff_NewPar_up5_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp5 before tagger:   "<< num_data_NewPar_up5_before <<endl;

  TF1 *data_Eff_NewPar_down5_f =new TF1("data_Eff_NewPar_down5_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_data_dn5->GetParameter(i));
  Double_t num_data_NewPar_down5_before = data_Eff_NewPar_down5_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown5 before tagger:   "<< num_data_NewPar_down5_before <<endl;

  //Par6
  TF1 *data_Eff_NewPar_up6_f =new TF1("data_Eff_NewPar_up6_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_data_up6->GetParameter(i));
  Double_t num_data_NewPar_up6_before = data_Eff_NewPar_up6_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp6 before tagger:   "<< num_data_NewPar_up6_before <<endl;

  TF1 *data_Eff_NewPar_down6_f =new TF1("data_Eff_NewPar_down6_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_data_dn6->GetParameter(i));
  Double_t num_data_NewPar_down6_before = data_Eff_NewPar_down6_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown6 before tagger:   "<< num_data_NewPar_down6_before <<endl;

 //Par7
  TF1 *data_Eff_NewPar_up7_f =new TF1("data_Eff_NewPar_up7_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_data_up7->GetParameter(i));
  Double_t num_data_NewPar_up7_before = data_Eff_NewPar_up7_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParUp7 before tagger:   "<< num_data_NewPar_up7_before <<endl;

  TF1 *data_Eff_NewPar_down7_f =new TF1("data_Eff_NewPar_down7_f",c_formula_data_signal, 24,182);
  for(int i=0;i<7;i++)data_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_data_dn7->GetParameter(i));
  Double_t num_data_NewPar_down7_before = data_Eff_NewPar_down7_f->Integral(24,182,TMath::Power(10,-8)) / 2;
  cout<<"data number for ParDown7 before tagger:   "<< num_data_NewPar_down7_before <<endl;

  if(num_data_NewPar_up1_before>num_data_before) {par1_up=num_data_NewPar_up1_before;par1_down=num_data_NewPar_down1_before;}
  else {par1_down=num_data_NewPar_up1_before;par1_up=num_data_NewPar_down1_before;}

  if(num_data_NewPar_up2_before>num_data_before) {par2_up=num_data_NewPar_up2_before;par2_down=num_data_NewPar_down2_before;}
  else {par2_down=num_data_NewPar_up2_before;par2_up=num_data_NewPar_down2_before;}

  if(num_data_NewPar_up3_before>num_data_before) {par3_up=num_data_NewPar_up3_before;par3_down=num_data_NewPar_down3_before;}
  else {par3_down=num_data_NewPar_up3_before;par3_up=num_data_NewPar_down3_before;}

  if(num_data_NewPar_up4_before>num_data_before) {par4_up=num_data_NewPar_up4_before;par4_down=num_data_NewPar_down4_before;}
  else {par4_down=num_data_NewPar_up4_before;par4_up=num_data_NewPar_down4_before;}

  if(num_data_NewPar_up5_before>num_data_before) {par5_up=num_data_NewPar_up5_before;par5_down=num_data_NewPar_down5_before;}
  else {par5_down=num_data_NewPar_up5_before;par5_up=num_data_NewPar_down5_before;}

  if(num_data_NewPar_up6_before>num_data_before) {par6_up=num_data_NewPar_up6_before;par6_down=num_data_NewPar_down6_before;}
  else {par6_down=num_data_NewPar_up6_before;par6_up=num_data_NewPar_down6_before;}

  if(num_data_NewPar_up7_before>num_data_before) {par7_up=num_data_NewPar_up7_before;par7_down=num_data_NewPar_down7_before;}
  else {par7_down=num_data_NewPar_up7_before;par7_up=num_data_NewPar_down7_before;}

  all_up= TMath::Power(par1_up-num_data_before,2)+TMath::Power(par2_up-num_data_before,2)+TMath::Power(par3_up-num_data_before,2)+TMath::Power(par4_up-num_data_before,2)+TMath::Power(par5_up-num_data_before,2)+TMath::Power(par6_up-num_data_before,2);
  all_down= TMath::Power(par1_down-num_data_before,2)+TMath::Power(par2_down-num_data_before,2)+TMath::Power(par3_down-num_data_before,2)+TMath::Power(par4_down-num_data_before,2)+TMath::Power(par5_down-num_data_before,2)+TMath::Power(par6_down-num_data_before,2);
 

  //write differences in file
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile <<"error calculation: data signal vorher "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "Parameter 1 Upvariation "<< par1_up-num_data_before<<endl;
  myfile << "Parameter 1 Downvariation "<< par1_down-num_data_before<<endl;
  myfile << "Parameter 2 Upvariation "<< par2_up-num_data_before<<endl;
  myfile << "Parameter 2 Downvariation "<< par2_down-num_data_before<<endl;
  myfile << "Parameter 3 Upvariation "<< par3_up-num_data_before<<endl;
  myfile << "Parameter 3 Downvariation "<< par3_down-num_data_before<<endl;
  myfile << "Parameter 4 Upvariation "<< par4_up-num_data_before<<endl;
  myfile << "Parameter 4 Downvariation "<< par4_down-num_data_before<<endl;
  myfile << "Parameter 5 Upvariation "<< par5_up-num_data_before<<endl;
  myfile << "Parameter 5 Downvariation "<< par5_down-num_data_before<<endl;
  myfile << "Parameter 6 Upvariation "<< par6_up-num_data_before<<endl;
  myfile << "Parameter 6 Downvariation "<< par6_down-num_data_before<<endl;
  myfile << "Parameter 7 Upvariation "<< par7_up-num_data_before<<endl;
  myfile << "Parameter 7 Downvariation "<< par7_down-num_data_before<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "all up variations quadraticly added: "<<TMath::Sqrt(all_up)<<endl;
  myfile << "all down variations quadraticly added: -"<<TMath::Sqrt(all_down)<<endl;

  Double_t error_data_before_up = TMath::Sqrt(all_up);
  Double_t error_data_before_down = TMath::Sqrt(all_down);


 //integrate over each variation and save the difference to normal number of bkg events in data before tagger
  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "integration of all up and down variations data bkg: " << number_back_data_miss <<endl;
  cout << "=======================================================================" << endl << endl << endl;

  // bkg_fit function has to be express by 7 paramerters
  stringstream sstr_data_bkg;
  sstr_data_bkg  << "(" << e_tr_data[0] << "*[0]+(" <<e_tr_data[1]<<")*[1]+("<<e_tr_data[2]<<")*[2]+("<<e_tr_data[3]<<")*[3]+("<<e_tr_data[4]<<")*[4]+("<<e_tr_data[5]<<")*[5]+("<<e_tr_data[6]<<")*[6]" <<")*(1-TMath::Erf((x-" <<"(" << f_tr_data[0] << "*[0]+(" <<f_tr_data[1]<<")*[1]+("<<f_tr_data[2]<<")*[2]+("<<f_tr_data[3]<<")*[3]+("<<f_tr_data[4]<<")*[4]+("<<f_tr_data[5]<<")*[5]+("<<f_tr_data[6]<<")*[6]" <<")" <<")/(1.4 * "<<
    "(" << g_tr_data[0] << "*[0]+(" <<g_tr_data[1]<<")*[1]+("<<g_tr_data[2]<<")*[2]+("<<g_tr_data[3]<<")*[3]+("<<g_tr_data[4]<<")*[4]+("<<g_tr_data[5]<<")*[5]+("<<g_tr_data[6]<<")*[6]" <<")"<<")))";
  string s_formula_data_bkg = sstr_data_bkg.str();
  const char * c_formula_data_bkg = s_formula_data_bkg.c_str();

  //Integrate over all up and down variation itself
  //Par1
  TF1 *data_bkg_Eff_NewPar_up1_f =new TF1("data_bkg_Eff_NewPar_up1_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_data_up1->GetParameter(i));
  Double_t num_data_bkg_NewPar_up1_before = data_bkg_Eff_NewPar_up1_f->Integral(24,182) / 2;
  cout<<"data number for ParUp1 before tagger:   "<< num_data_bkg_NewPar_up1_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down1_f =new TF1("data_bkg_Eff_NewPar_down1_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_data_dn1->GetParameter(i));
  Double_t num_data_bkg_NewPar_down1_before = data_bkg_Eff_NewPar_down1_f->Integral(24,182) / 2;
  cout<<"data number for ParDown1 before tagger:   "<< num_data_bkg_NewPar_down1_before <<endl;

  //Par2
  TF1 *data_bkg_Eff_NewPar_up2_f =new TF1("data_bkg_Eff_NewPar_up2_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_data_up2->GetParameter(i));
  Double_t num_data_bkg_NewPar_up2_before = data_bkg_Eff_NewPar_up2_f->Integral(24,182) / 2;
  cout<<"data number for ParUp2 before tagger:   "<< num_data_bkg_NewPar_up2_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down2_f =new TF1("data_bkg_Eff_NewPar_down2_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_data_dn2->GetParameter(i));
  Double_t num_data_bkg_NewPar_down2_before = data_bkg_Eff_NewPar_down2_f->Integral(24,182) / 2;
  cout<<"data number for ParDown2 before tagger:   "<< num_data_bkg_NewPar_down2_before <<endl;

  //Par3
  TF1 *data_bkg_Eff_NewPar_up3_f =new TF1("data_bkg_Eff_NewPar_up3_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_data_up3->GetParameter(i));
  Double_t num_data_bkg_NewPar_up3_before = data_bkg_Eff_NewPar_up3_f->Integral(24,182) / 2;
  cout<<"data number for ParUp3 before tagger:   "<< num_data_bkg_NewPar_up3_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down3_f =new TF1("data_bkg_Eff_NewPar_down3_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_data_dn3->GetParameter(i));
  Double_t num_data_bkg_NewPar_down3_before = data_bkg_Eff_NewPar_down3_f->Integral(24,182) / 2;
  cout<<"data number for ParDown3 before tagger:   "<< num_data_bkg_NewPar_down3_before <<endl;

  //Par4
  TF1 *data_bkg_Eff_NewPar_up4_f =new TF1("data_bkg_Eff_NewPar_up4_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_data_up4->GetParameter(i));
  Double_t num_data_bkg_NewPar_up4_before = data_bkg_Eff_NewPar_up4_f->Integral(24,182) / 2;
  cout<<"data number for ParUp4 before tagger:   "<< num_data_bkg_NewPar_up4_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down4_f =new TF1("data_bkg_Eff_NewPar_down4_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_data_dn4->GetParameter(i));
  Double_t num_data_bkg_NewPar_down4_before = data_bkg_Eff_NewPar_down4_f->Integral(24,182) / 2;
  cout<<"data number for ParDown4 before tagger:   "<< num_data_bkg_NewPar_down4_before <<endl;

  //Par5
  TF1 *data_bkg_Eff_NewPar_up5_f =new TF1("data_bkg_Eff_NewPar_up5_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_data_up5->GetParameter(i));
  Double_t num_data_bkg_NewPar_up5_before = data_bkg_Eff_NewPar_up5_f->Integral(24,182) / 2;
  cout<<"data number for ParUp5 before tagger:   "<< num_data_bkg_NewPar_up5_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down5_f =new TF1("data_bkg_Eff_NewPar_down5_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_data_dn5->GetParameter(i));
  Double_t num_data_bkg_NewPar_down5_before = data_bkg_Eff_NewPar_down5_f->Integral(24,182) / 2;
  cout<<"data number for ParDown5 before tagger:   "<< num_data_bkg_NewPar_down5_before <<endl;

  //Par6
  TF1 *data_bkg_Eff_NewPar_up6_f =new TF1("data_bkg_Eff_NewPar_up6_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_data_up6->GetParameter(i));
  Double_t num_data_bkg_NewPar_up6_before = data_bkg_Eff_NewPar_up6_f->Integral(24,182) / 2;
  cout<<"data number for ParUp6 before tagger:   "<< num_data_bkg_NewPar_up6_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down6_f =new TF1("data_bkg_Eff_NewPar_down6_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_data_dn6->GetParameter(i));
  Double_t num_data_bkg_NewPar_down6_before = data_bkg_Eff_NewPar_down6_f->Integral(24,182) / 2;
  cout<<"data number for ParDown6 before tagger:   "<< num_data_bkg_NewPar_down6_before <<endl;

 //Par7
  TF1 *data_bkg_Eff_NewPar_up7_f =new TF1("data_bkg_Eff_NewPar_up7_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_data_up7->GetParameter(i));
  Double_t num_data_bkg_NewPar_up7_before = data_bkg_Eff_NewPar_up7_f->Integral(24,182) / 2;
  cout<<"data number for ParUp7 before tagger:   "<< num_data_bkg_NewPar_up7_before <<endl;

  TF1 *data_bkg_Eff_NewPar_down7_f =new TF1("data_bkg_Eff_NewPar_down7_f",c_formula_data_bkg, 24,182);
  for(int i=0;i<7;i++)data_bkg_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_data_dn7->GetParameter(i));
  Double_t num_data_bkg_NewPar_down7_before = data_bkg_Eff_NewPar_down7_f->Integral(24,182) / 2;
  cout<<"data number for ParDown7 before tagger:   "<< num_data_bkg_NewPar_down7_before <<endl;

  if(num_data_bkg_NewPar_up1_before>number_back_data_miss) {par1_up=num_data_bkg_NewPar_up1_before;par1_down=num_data_bkg_NewPar_down1_before;}
  else {par1_down=num_data_bkg_NewPar_up1_before;par1_up=num_data_bkg_NewPar_down1_before;}

  if(num_data_bkg_NewPar_up2_before>number_back_data_miss) {par2_up=num_data_bkg_NewPar_up2_before;par2_down=num_data_bkg_NewPar_down2_before;}
  else {par2_down=num_data_bkg_NewPar_up2_before;par2_up=num_data_bkg_NewPar_down2_before;}

  if(num_data_bkg_NewPar_up3_before>number_back_data_miss) {par3_up=num_data_bkg_NewPar_up3_before;par3_down=num_data_bkg_NewPar_down3_before;}
  else {par3_down=num_data_bkg_NewPar_up3_before;par3_up=num_data_bkg_NewPar_down3_before;}

  if(num_data_bkg_NewPar_up4_before>number_back_data_miss) {par4_up=num_data_bkg_NewPar_up4_before;par4_down=num_data_bkg_NewPar_down4_before;}
  else {par4_down=num_data_bkg_NewPar_up4_before;par4_up=num_data_bkg_NewPar_down4_before;}

  if(num_data_bkg_NewPar_up5_before>number_back_data_miss) {par5_up=num_data_bkg_NewPar_up5_before;par5_down=num_data_bkg_NewPar_down5_before;}
  else {par5_down=num_data_bkg_NewPar_up5_before;par5_up=num_data_bkg_NewPar_down5_before;}

  if(num_data_bkg_NewPar_up6_before>number_back_data_miss) {par6_up=num_data_bkg_NewPar_up6_before;par6_down=num_data_bkg_NewPar_down6_before;}
  else {par6_down=num_data_bkg_NewPar_up6_before;par6_up=num_data_bkg_NewPar_down6_before;}

  if(num_data_bkg_NewPar_up7_before>number_back_data_miss) {par7_up=num_data_bkg_NewPar_up7_before;par7_down=num_data_bkg_NewPar_down7_before;}
  else {par7_down=num_data_bkg_NewPar_up7_before;par7_up=num_data_bkg_NewPar_down7_before;}

  all_up= TMath::Power(par1_up-number_back_data_miss,2)+TMath::Power(par2_up-number_back_data_miss,2)+TMath::Power(par3_up-number_back_data_miss,2)+TMath::Power(par4_up-number_back_data_miss,2)+TMath::Power(par5_up-number_back_data_miss,2)+TMath::Power(par6_up-number_back_data_miss,2);
  all_down= TMath::Power(par1_down-number_back_data_miss,2)+TMath::Power(par2_down-number_back_data_miss,2)+TMath::Power(par3_down-number_back_data_miss,2)+TMath::Power(par4_down-number_back_data_miss,2)+TMath::Power(par5_down-number_back_data_miss,2)+TMath::Power(par6_down-number_back_data_miss,2);
 

  //write differences in file
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile <<"error calculation: data bkg vorher "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "Parameter 1 Upvariation "<< par1_up-number_back_data_miss<<endl;
  myfile << "Parameter 1 Downvariation "<< par1_down-number_back_data_miss<<endl;
  myfile << "Parameter 2 Upvariation "<< par2_up-number_back_data_miss<<endl;
  myfile << "Parameter 2 Downvariation "<< par2_down-number_back_data_miss<<endl;
  myfile << "Parameter 3 Upvariation "<< par3_up-number_back_data_miss<<endl;
  myfile << "Parameter 3 Downvariation "<< par3_down-number_back_data_miss<<endl;
  myfile << "Parameter 4 Upvariation "<< par4_up-number_back_data_miss<<endl;
  myfile << "Parameter 4 Downvariation "<< par4_down-number_back_data_miss<<endl;
  myfile << "Parameter 5 Upvariation "<< par5_up-number_back_data_miss<<endl;
  myfile << "Parameter 5 Downvariation "<< par5_down-number_back_data_miss<<endl;
  myfile << "Parameter 6 Upvariation "<< par6_up-number_back_data_miss<<endl;
  myfile << "Parameter 6 Downvariation "<< par6_down-number_back_data_miss<<endl;
  myfile << "Parameter 7 Upvariation "<< par7_up-number_back_data_miss<<endl;
  myfile << "Parameter 7 Downvariation "<< par7_down-number_back_data_miss<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "all up variations quadraticly added: "<<TMath::Sqrt(all_up)<<endl;
  myfile << "all down variations quadraticly added: -"<<TMath::Sqrt(all_down)<<endl;

  Double_t error_data_after_up = TMath::Sqrt(TMath::Power(error_data,2) + TMath::Power(TMath::Sqrt(all_up)*mistag_rate_data,2) + TMath::Power(number_back_data_miss *error_mistagrate_data_up ,2));
  Double_t error_data_after_down = TMath::Sqrt(TMath::Power(error_data,2) + TMath::Power(TMath::Sqrt(all_down)*mistag_rate_data,2) + TMath::Power(number_back_data_miss *error_mistagrate_data_down ,2));
  myfile<< "error data after tagger up:  "<<error_data_after_up <<endl;
  myfile<< "error data after tagger down:  "<<error_data_after_down <<endl;

  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "                                             Final result                                                 "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  
  // Double_t error_MC_after_up
  // Double_t error_MC_after_down 
  // Double_t error_data_after_up 
  // Double_t error_data_after_down 
  // cout << "error MC_up after:  "<< error_MC_after_up <<" - error MC up before: "<<(error_MC_before_up/num_MC_before) << endl;
  //cout << "error MC_down after:  "<< error_MC_after_down <<" - error MC down before: "<<(error_MC_before_down/num_MC_before) << endl;
  
  
  Double_t error_MC_up = TMath::Sqrt((1/TMath::Power(num_MC_before,2)) *error_MC_after_up *error_MC_after_up + TMath::Power(num_MC_after/num_MC_before/num_MC_before,2) * error_MC_before_up * error_MC_before_up );
  Double_t error_MC_down = TMath::Sqrt((1/TMath::Power(num_MC_before,2)) *error_MC_after_down *error_MC_after_down + TMath::Power(num_MC_after/num_MC_before/num_MC_before,2) * error_MC_before_down * error_MC_before_down );
  Double_t error_data_up = TMath::Sqrt((1/TMath::Power(num_data_before,2)) *error_data_after_up *error_data_after_up + TMath::Power(num_data_after/num_data_before/num_data_before,2) * error_data_before_up * error_data_before_up );
  Double_t error_data_down = TMath::Sqrt((1/TMath::Power(num_data_before,2)) *error_data_after_down *error_data_after_down + TMath::Power(num_data_after/num_data_before/num_data_before,2) * error_data_before_down * error_data_before_down );
  
 
  
  myfile<< "eff MC " << num_MC_after/num_MC_before <<" + "<< error_MC_up/(num_MC_after/num_MC_before) << " - " << error_MC_down/(num_MC_after/num_MC_before) <<endl;
  myfile<< "eff data " << num_data_after/num_data_before <<" + "<< error_data_up/(num_data_after/num_data_before) << " - " << error_data_down/(num_data_after/num_data_before)<<endl;
  myfile<<"-----------------------------------------------------------------------"<<endl;
  myfile << "error MC up: error MC after "<< (1/TMath::Power(num_MC_before,2)) *error_MC_after_up *error_MC_after_up<<" +error MC before "<< TMath::Power(num_MC_after/num_MC_before/num_MC_before,2) * error_MC_before_up * error_MC_before_up <<endl;
  
  myfile << "error MC after: error sig after "<<TMath::Power(error_sig,2)<<" + error back after "<< TMath::Power(error_back,2) <<" + error back before * mistag rate "<< TMath::Power((TMath::Sqrt(all_up)*mistag_rate_MC),2) <<" + error misstag rate "<< TMath::Power(number_back_MC_miss * error_mistagrate_MC_up ,2)<<endl;
  
  
  myfile << "error MC down: error MC after "<< (1/TMath::Power(num_MC_before,2)) *error_MC_after_down *error_MC_after_down<<" +error MC before "<< TMath::Power(num_MC_after/num_MC_before/num_MC_before,2) * error_MC_before_down * error_MC_before_down <<endl;
  
  myfile << "error MC after: error sig after "<<TMath::Power(error_sig,2)<<" + error back after "<< TMath::Power(error_back,2) <<" + error back before * mistag rate "<< TMath::Power((TMath::Sqrt(all_down)*mistag_rate_MC),2) <<" + error misstag rate "<< TMath::Power(number_back_MC_miss * error_mistagrate_MC_down ,2)<<endl;
  
  myfile<<"-----------------------------------------------------------------------"<<endl;
  
  
  myfile << "error data up: error data after "<< (1/TMath::Power(num_data_before,2)) *error_data_after_up *error_data_after_up<<" +error data before "<< TMath::Power(num_data_after/num_data_before/num_data_before,2) * error_data_before_up * error_data_before_up <<endl;
  
  myfile << "error data after: error sig after "<<TMath::Power(error_sig,2)<<" + error back after "<< TMath::Power(error_back,2) <<" + error back before * mistag rate "<< TMath::Power((TMath::Sqrt(all_up)*mistag_rate_data),2) <<" + error misstag rate "<< TMath::Power(number_back_data_miss * error_mistagrate_data_up ,2)<<endl;
  
  
  myfile << "error data down: error data after "<< (1/TMath::Power(num_data_before,2)) *error_data_after_down *error_data_after_down<<" +error data before "<< TMath::Power(num_data_after/num_data_before/num_data_before,2) * error_data_before_down * error_data_before_down <<endl;
  
  myfile << "error data after: error sig after "<<TMath::Power(error_sig,2)<<" + error back after "<< TMath::Power(error_back,2) <<" + error back before * mistag rate "<< TMath::Power((TMath::Sqrt(all_down)*mistag_rate_data),2) <<" + error misstag rate "<< TMath::Power(number_back_data_miss * error_mistagrate_data_down ,2)<<endl;
  

  

  

  //write eff in hists: for none also errors
  
  TFile *g= new TFile(unc_folder +"Eff_"+unc_name+".root","RECREATE");
  TH1F *tot_eff_h = new TH1F("tot_eff_h","tot eff",1,1,2);
  //SF for eff
  Double_t sf_eff = (num_data_after/num_data_before)/(num_MC_after/num_MC_before);
  cout << "sf_eff "<< sf_eff << endl;
  tot_eff_h->Fill(1,sf_eff);
  tot_eff_h->Write();
  if(unc_name == "none"){
    TH1F *tot_err_up_h = new TH1F("tot_err_up_h","tot error",1,1,2);
    Double_t sf_eff_err_up = TMath::Sqrt(TMath::Power((1/(num_MC_after/num_MC_before)) * error_data_up/(num_data_after/num_data_before),2) +TMath::Power(sf_eff/(num_MC_after/num_MC_before) *  error_MC_up/(num_MC_after/num_MC_before)  ,2) );
    tot_err_up_h->Fill(1,sf_eff_err_up);
    tot_err_up_h->Write();

    TH1F *tot_err_down_h = new TH1F("tot_err_down_h","tot error",1,1,2);
    Double_t sf_eff_err_down =  TMath::Sqrt(TMath::Power((1/(num_MC_after/num_MC_before)) * error_data_down/(num_data_after/num_data_before),2) +TMath::Power(sf_eff/(num_MC_after/num_MC_before) *  error_MC_down/(num_MC_after/num_MC_before)  ,2) );
    tot_err_down_h->Fill(1,sf_eff_err_down);
    tot_err_down_h->Write();

    myfile<<"sf_eff_err_up  "<<sf_eff_err_up<<endl;
    myfile<<"sf_eff_err_down  "<<sf_eff_err_down<<endl;
  }
  g->Close();

  myfile<< "sf_eff "<< sf_eff << endl;
 

  myfile.close();



}//End of function

















