#include "TH1.h"
#include <fstream>

using namespace std;

void fit_erf()
{
  //setOptFit( pcev (default = 0111)) Probability; Chisquare/Number of degrees of freedom; errors ;values of parameters 
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  bool b_error=true;
 

  //All files are read in
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/eff/";
  TString bkgfolder = "";
  TFile * Data_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.Data.Data.root", "READ");
  TFile * TTbar_matched_f = new TFile(directory+"/uhh2.AnalysisModuleRunner.MC.TTbar_right.root", "READ");
  TFile * TTbar_unmatched_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.TTbar_wrong.root", "READ");
  TFile * WJets_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.WJets.root", "READ");
  TFile * other_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.other.root", "READ");
  TFile * QCD_f = new TFile(directory+bkgfolder+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");

  //Get all hist from the string hist_name
  TString hist_name = "tagger_chi2cut/reco_mass_W";
  TH1F* data = (TH1F*)Data_f->Get(hist_name);
  TH1F* TTbar_matched = (TH1F*)TTbar_matched_f->Get(hist_name);
  TH1F* TTbar_unmatched = (TH1F*)TTbar_unmatched_f->Get(hist_name);
  TH1F* WJets = (TH1F*)WJets_f->Get(hist_name);
  TH1F* other = (TH1F*)other_f->Get(hist_name);
  TH1F* QCD = (TH1F*)QCD_f->Get(hist_name);

  TString folder ="erf/ERROR_";
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
  TF1* background_fit = new TF1("background_fit", " [0]*(1 - TMath::Erf((x-[1])/(1.4*[2])))", 25, 182);
  background_fit->SetParameter(0, 4);
  background_fit->SetParameter(1, 100);
  background_fit->SetParameter(2, 20);
 
  background_fit->SetLineColor(kOrange+2);
  background_fit->SetLineStyle(kDashed);

  back->Draw("PZ");
  back->Fit(background_fit, "R");
  background_fit->DrawClone("same");
 
  background_c->Print(folder +"background_fit.eps");
  
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
  TF1 *signal_fit = new TF1("signal_fit","TMath::Voigt(x-[2], [0], [1], 4)*[3]", 65, 115);
  signal_fit->SetParameter(0, 10);
  signal_fit->FixParameter(1, 2.09);
  signal_fit->SetParameter(2, 92);
  signal_fit->SetParameter(3, 40);
 
  signal_fit->SetLineStyle(kDashed);
  signal_fit->SetLineColor(kGreen+3);

  TTbar_matched->Fit(signal_fit,"R");
  signal_fit->DrawClone("same");
 
  signal_c->Print(folder +"signal_fit.eps");
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
  TF1 *signal_background_fit = new TF1("signal_background_fit","signal_fit + background_fit", 25,182);

  //Signal
  signal_background_fit->SetParameter(0, signal_fit->GetParameter(0));
  signal_background_fit->SetParameter(1, signal_fit->GetParameter(1));
  signal_background_fit->SetParameter(2, signal_fit->GetParameter(2));
  signal_background_fit->SetParameter(3, signal_fit->GetParameter(3));
  //Background
  signal_background_fit->SetParameter(4, background_fit->GetParameter(0));
  signal_background_fit->SetParameter(5, background_fit->GetParameter(1));
  signal_background_fit->SetParameter(6, background_fit->GetParameter(2));
 

  signal_background_fit->SetLineColor(kGreen+3);
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
  back2->Draw("same");
  TF1* bc = (TF1*) background_fit->Clone();
  bc->SetParameter(0, signal_background_fit->GetParameter(4));
  bc->SetParameter(1, signal_background_fit->GetParameter(5));  
  bc->SetParameter(2, signal_background_fit->GetParameter(6));  
  bc->SetLineColor(kOrange+2);
  bc->SetLineStyle(kDashed);
  bc->DrawClone("same");

  signal_background_c->Print(folder +"signal_background_fit.eps");
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
  TF1* data_fit = new TF1("data_fit","signal_fit+background_fit" , 25, 182);

  Double_t sc = data->Integral() / all->Integral();
  //signal
  data_fit->SetParameter(0, signal_background_fit->GetParameter(0));
  data_fit->SetParameter(1, signal_background_fit->GetParameter(1));
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
  bc->SetLineStyle(kDashed);
  bc->DrawClone("same");
  data_c->Print(folder +"data_fit.eps");

  // ---------------------------------------
  //        Calculate Efficency
  // ---------------------------------------
  TCanvas *MC_Eff_c = new TCanvas("MC_Eff_c","MC Eff curve",10,10,700,900);
  MC_Eff_c->Clear();
  MC_Eff_c->cd();

  TF1 *MC_Eff_f =new TF1("MC_Eff_f","signal_fit", 25,182);
   //signal
  MC_Eff_f->SetParameter(0, signal_background_fit->GetParameter(0));
  MC_Eff_f->SetParameter(1, signal_background_fit->GetParameter(1));
  MC_Eff_f->SetParameter(2, signal_background_fit->GetParameter(2));
  MC_Eff_f->SetParameter(3, signal_background_fit->GetParameter(3));
 
  MC_Eff_f->Draw();

  TF1 *Data_Eff_f =new TF1("Data_Eff_f","signal_fit", 25,182);
  //signal
  Data_Eff_f->SetParameter(0, data_fit->GetParameter(0));
  Data_Eff_f->SetParameter(1, data_fit->GetParameter(1));
  Data_Eff_f->SetParameter(2, data_fit->GetParameter(2));
  Data_Eff_f->SetParameter(3, data_fit->GetParameter(3));
 
  Data_Eff_f->SetLineColor(kBlue+2);
  Data_Eff_f->SetLineStyle(kDashed);
  Data_Eff_f->Draw("same");
  MC_Eff_c->Print(folder + "MC_Eff.eps");

  Double_t num_MC_before = MC_Eff_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number before tagger:   "<< num_MC_before <<endl;
  Double_t num_Data_before = Data_Eff_f->Integral(25,182,TMath::Power(10,-8))/2;
  cout<<"Data number before tagger:   "<< num_Data_before <<endl;

  // integrate background events for tagger and multipy by mistagging rate (MC)
  TF1 *MC_back_f =new TF1("MC_back_f","background_fit", 25,182);
  //background
  MC_back_f->SetParameter(0, signal_background_fit->GetParameter(4));
  MC_back_f->SetParameter(1, signal_background_fit->GetParameter(5));
  MC_back_f->SetParameter(2, signal_background_fit->GetParameter(6));
  Double_t number_back_MC_miss = MC_back_f->Integral(25,182) / 2;

  // integrate background events for tagger and multipy by mistagging rate (Data)
  TF1 *Data_back_f =new TF1("Data_back_f","background_fit", 25,182);
  //background
  Data_back_f->SetParameter(0, data_fit->GetParameter(4));
  Data_back_f->SetParameter(1, data_fit->GetParameter(5));
  Data_back_f->SetParameter(2, data_fit->GetParameter(6));
  Double_t number_back_Data_miss = Data_back_f->Integral(25,182) / 2;

  // load histograms after tagger
  hist_name = "tagger_zwtag/reco_mass_W";
  data_after = (TH1F*)Data_f->Get(hist_name);
  TTbar_matched = (TH1F*)TTbar_matched_f->Get(hist_name);
  TTbar_unmatched = (TH1F*)TTbar_unmatched_f->Get(hist_name);
  WJets = (TH1F*)WJets_f->Get(hist_name);
  other = (TH1F*)other_f->Get(hist_name);
  QCD = (TH1F*)QCD_f->Get(hist_name);
  
  back = (TH1D*)TTbar_unmatched->Clone();
  back->Add(other);
  back->Add(WJets);
  back->Add(QCD);
  

//count events in background histogram
  Double_t number_back=0;  
  for(int i =0 ; i<back->GetSize();i++){
    number_back = number_back + back->GetBinContent(i);
  }
  cout << "number of background events:  " << number_back <<endl;

  //count events in signal histogram
  Double_t number_sig=0;  
  for(int i =0 ; i<TTbar_matched->GetSize();i++){
    number_sig = number_sig + TTbar_matched->GetBinContent(i);
  }
  cout << "number of sig events after tagger:  " << number_sig <<endl;

  //count events in data histogram
  Double_t number_data=0;  
  for(int i =0 ; i<data_after->GetSize();i++){
    number_data = number_data + data_after->GetBinContent(i);
  }
  cout << "number of data events after tagger:  " << number_data <<endl;

  Double_t mistag_rate_Data=0.194;
  Double_t mistag_rate_MC=0.197;
  Double_t num_MC_after = number_sig+ number_back - number_back_MC_miss * mistag_rate_MC;
  Double_t num_Data_after =number_data - number_back_Data_miss * mistag_rate_Data;

  cout<< "eff MC " << num_MC_after/num_MC_before <<endl;
  cout<< "eff MC " << num_Data_after/num_Data_before <<endl;

  ofstream myfile;
  myfile.open (folder+"numbers.txt");
  myfile << "MC number before tagger:   "<< num_MC_before <<endl;
  myfile<<"Data number before tagger:   "<< num_Data_before <<endl;
  myfile<< "number of sig events after tagger:  " << number_sig+ number_back <<endl;
  myfile<< "number of data events after tagger:  " << number_data <<endl;
  myfile<< "number of data after subtracting background: "<< num_Data_after <<endl;
  myfile<< "number of MC after subtracting background: "<< num_MC_after<<endl;
  myfile<< "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile<< "eff MC " << num_MC_after/num_MC_before <<endl;
  myfile<< "eff MC " << num_Data_after/num_Data_before <<endl;
  

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
  TF1* f_NewParam_MC = new TF1("f_NewParam_MC",c_formula_MC,25,182);
  f_NewParam_MC->SetParameter(0,V_New_Param_MC[0]);
  f_NewParam_MC->SetParameter(1,V_New_Param_MC[1]);
  f_NewParam_MC->SetParameter(2,V_New_Param_MC[2]);
  f_NewParam_MC->SetParameter(3,V_New_Param_MC[3]);
  f_NewParam_MC->SetParameter(4,V_New_Param_MC[4]);
  f_NewParam_MC->SetParameter(5,V_New_Param_MC[5]);
  f_NewParam_MC->SetParameter(6,V_New_Param_MC[6]);
  f_NewParam_MC->SetLineColor(kGreen+3);

  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "Fit with new parameters: " << endl;
  cout << "=======================================================================" << endl << endl << endl;

  TCanvas* cfitnew_MC = new TCanvas("cfitnewMC", "Fit function in new parameters, MC",10,10,700,900);
  TFitResultPtr fit_result_MC = all->Fit(f_NewParam_MC,"SR");
  cfitnew_MC->Print("Fit_signal_background_new.eps");
  cout << "Fit in new parameters, MC: " << endl;
  fit_result_MC->Print("V");


  //calculate fit parameter errors by hand: keep 6 fixed and vary one until chi2 increases by 1
  cout << endl << endl << endl << endl << endl;
  cout << "======================================================================="  << endl;
  cout << "Calculate errors by hand " << endl;
  cout << "=======================================================================" << endl << endl << endl;
  
  //define error function
  TF1* f_NewParam_MC_error = new TF1("f_NewParam_MC_error",c_formula_MC,25,182);

  //fix all fit values
  TCanvas* c_dummy_MC = new TCanvas("c_dummy_MC", "Fits for chi2 in MC", 10,10,700,900);
  for(int i=0; i<7; i++){
    f_NewParam_MC_error->FixParameter(i,fit_result_MC->Parameter(i));
  }
  
  cout << endl << endl << endl << "FIT BY HAND for CHI2 calculation: SIGNAL" << endl << endl << endl;

  //smalles chi2 out of the fit before
  all->Fit(f_NewParam_MC_error,"QR");
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
    for(int i=0; i<50000; i++){
      for_percent++;
      double varied_par_MC = -20*pars_MC[j] + pars_MC[j]/1000 * i;
      f_NewParam_MC_error->FixParameter(j,varied_par_MC);
     
      all->Fit(f_NewParam_MC_error,"QR");

      double chi2_tmp_MC = f_NewParam_MC_error->GetChisquare();
      chi2_diff_MC = chi2_tmp_MC - chi2_best_MC;

      if(i%500 == 0) cout << "\r"  << for_percent/3500  << "%, " <<  "Parameter " << j << ", Fit No. " << i  << ", current chi2: " << chi2_tmp_MC << " at current parametervalue: " << varied_par_MC << "           "  << flush;

      if(!pars_dn_set_MC[j] && chi2_diff_MC < 1) {
	pars_dn_MC[j] = -20*pars_MC[j] + pars_MC[j]/1000 * (i-1);
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
    l_pars_up_MC[i] = new TLine(pars_up_MC[i], chi2_best_MC - 1, pars_up_MC[i], chi2_best_MC+10);
    l_pars_dn_MC[i] = new TLine(pars_dn_MC[i], chi2_best_MC - 1, pars_dn_MC[i], chi2_best_MC+10);
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
    g_chi2_pars_MC[i]->SetTitle("MC");
    g_chi2_pars_MC[i]->GetXaxis()->SetTitle(c_n_MC);
    g_chi2_pars_MC[i]->GetXaxis()->SetTitleSize(0.044);
    g_chi2_pars_MC[i]->GetYaxis()->SetTitle("#chi^{2}");
    g_chi2_pars_MC[i]->GetYaxis()->SetTitleSize(0.044);
    g_chi2_pars_MC[i]->GetXaxis()->SetLimits(pars_dn_MC[i]-2*err_pars_dn_MC[i],pars_up_MC[i]+2*err_pars_up_MC[i]);
  }

  // example of a error calculated parameter by hand
  TCanvas* c_chi2_p0_MC = new TCanvas("c_chi2_p0_MC", "chi2 (p0)_MC", 1);
  g_chi2_pars_MC[0]->Draw();
  l_pars_up_MC[0]->Draw("SAME");
  l_pars_dn_MC[0]->Draw("SAME");
  l_pars_central_MC[0]->Draw("SAME");
  c_chi2_p0_MC->Print("Chi2_MC_p0.eps");

  //print all uncorrelated parameters with errors
  cout<<endl;
  for(int j=0; j<7; j++){
    cout << "Result MC: par " << j << " = " << pars_MC[j] << " (+" << err_pars_up_MC[j] << ") (-" << err_pars_dn_MC[j] << ")" << endl;
  }

  TF1* f_NewParam_MC_up1 = new TF1("f_NewParam_MC_up1", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn1 = new TF1("f_NewParam_MC_dn1", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_up2 = new TF1("f_NewParam_MC_up2", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn2 = new TF1("f_NewParam_MC_dn2", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_up3 = new TF1("f_NewParam_MC_up3", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn3 = new TF1("f_NewParam_MC_dn3", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_up4 = new TF1("f_NewParam_MC_up4", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn4 = new TF1("f_NewParam_MC_dn4", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_up5 = new TF1("f_NewParam_MC_up5", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn5 = new TF1("f_NewParam_MC_dn5", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_up6 = new TF1("f_NewParam_MC_up6", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn6 = new TF1("f_NewParam_MC_dn6", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_up7 = new TF1("f_NewParam_MC_up7", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dn7 = new TF1("f_NewParam_MC_dn7", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_upall = new TF1("f_NewParam_MC_upall", c_formula_MC,25, 182);
  TF1* f_NewParam_MC_dnall = new TF1("f_NewParam_MC_dnall", c_formula_MC,25, 182);

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
  f_NewParam_MC->Draw();
  f_NewParam_MC_up1->SetLineColor(3);
  f_NewParam_MC_up1->Draw("SAME");
  f_NewParam_MC_dn1->SetLineColor(4);
  f_NewParam_MC_dn1->Draw("SAME");
  f_NewParam_MC_up2->SetLineColor(5);
  f_NewParam_MC_up2->Draw("SAME");
  f_NewParam_MC_dn2->SetLineColor(6);
  f_NewParam_MC_dn2->Draw("SAME");
  f_NewParam_MC_up3->SetLineColor(7);
  f_NewParam_MC_up3->Draw("SAME");
  f_NewParam_MC_dn3->SetLineColor(8);
  f_NewParam_MC_dn3->Draw("SAME");
  f_NewParam_MC_up4->SetLineColor(9);
  f_NewParam_MC_up4->Draw("SAME");
  f_NewParam_MC_dn4->SetLineColor(10);
  f_NewParam_MC_dn4->Draw("SAME");
  f_NewParam_MC_up5->SetLineColor(11);
  f_NewParam_MC_up5->Draw("SAME");
  f_NewParam_MC_dn5->SetLineColor(12);
  f_NewParam_MC_dn5->Draw("SAME");
  f_NewParam_MC_up6->SetLineColor(40);
  f_NewParam_MC_up6->Draw("SAME");
  f_NewParam_MC_dn6->SetLineColor(42);
  f_NewParam_MC_dn6->Draw("SAME");
  f_NewParam_MC_up7->SetLineColor(32);
  f_NewParam_MC_up7->Draw("SAME");
  f_NewParam_MC_dn7->SetLineColor(39);
  f_NewParam_MC_dn7->Draw("SAME");

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
  TF1 *MC_Eff_NewPar_up1_f =new TF1("MC_Eff_NewPar_up1_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_MC_up1->GetParameter(i));
  Double_t num_MC_NewPar_up1_before = MC_Eff_NewPar_up1_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp1 before tagger:   "<< num_MC_NewPar_up1_before <<endl;

  TF1 *MC_Eff_NewPar_down1_f =new TF1("MC_Eff_NewPar_down1_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_MC_dn1->GetParameter(i));
  Double_t num_MC_NewPar_down1_before = MC_Eff_NewPar_down1_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown1 before tagger:   "<< num_MC_NewPar_down1_before <<endl;

  //Par2
  TF1 *MC_Eff_NewPar_up2_f =new TF1("MC_Eff_NewPar_up2_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_MC_up2->GetParameter(i));
  Double_t num_MC_NewPar_up2_before = MC_Eff_NewPar_up2_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp2 before tagger:   "<< num_MC_NewPar_up2_before <<endl;

  TF1 *MC_Eff_NewPar_down2_f =new TF1("MC_Eff_NewPar_down2_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_MC_dn2->GetParameter(i));
  Double_t num_MC_NewPar_down2_before = MC_Eff_NewPar_down2_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown2 before tagger:   "<< num_MC_NewPar_down2_before <<endl;

  //Par3
  TF1 *MC_Eff_NewPar_up3_f =new TF1("MC_Eff_NewPar_up3_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_MC_up3->GetParameter(i));
  Double_t num_MC_NewPar_up3_before = MC_Eff_NewPar_up3_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp3 before tagger:   "<< num_MC_NewPar_up3_before <<endl;

  TF1 *MC_Eff_NewPar_down3_f =new TF1("MC_Eff_NewPar_down3_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_MC_dn3->GetParameter(i));
  Double_t num_MC_NewPar_down3_before = MC_Eff_NewPar_down3_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown3 before tagger:   "<< num_MC_NewPar_down3_before <<endl;

  //Par4
  TF1 *MC_Eff_NewPar_up4_f =new TF1("MC_Eff_NewPar_up4_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_MC_up4->GetParameter(i));
  Double_t num_MC_NewPar_up4_before = MC_Eff_NewPar_up4_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp4 before tagger:   "<< num_MC_NewPar_up4_before <<endl;

  TF1 *MC_Eff_NewPar_down4_f =new TF1("MC_Eff_NewPar_down4_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_MC_dn4->GetParameter(i));
  Double_t num_MC_NewPar_down4_before = MC_Eff_NewPar_down4_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown4 before tagger:   "<< num_MC_NewPar_down4_before <<endl;

  //Par5
  TF1 *MC_Eff_NewPar_up5_f =new TF1("MC_Eff_NewPar_up5_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_MC_up5->GetParameter(i));
  Double_t num_MC_NewPar_up5_before = MC_Eff_NewPar_up5_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp5 before tagger:   "<< num_MC_NewPar_up5_before <<endl;

  TF1 *MC_Eff_NewPar_down5_f =new TF1("MC_Eff_NewPar_down5_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_MC_dn5->GetParameter(i));
  Double_t num_MC_NewPar_down5_before = MC_Eff_NewPar_down5_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown5 before tagger:   "<< num_MC_NewPar_down5_before <<endl;

  //Par6
  TF1 *MC_Eff_NewPar_up6_f =new TF1("MC_Eff_NewPar_up6_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_MC_up6->GetParameter(i));
  Double_t num_MC_NewPar_up6_before = MC_Eff_NewPar_up6_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp6 before tagger:   "<< num_MC_NewPar_up6_before <<endl;

  TF1 *MC_Eff_NewPar_down6_f =new TF1("MC_Eff_NewPar_down6_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_MC_dn6->GetParameter(i));
  Double_t num_MC_NewPar_down6_before = MC_Eff_NewPar_down6_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParDown6 before tagger:   "<< num_MC_NewPar_down6_before <<endl;

 //Par7
  TF1 *MC_Eff_NewPar_up7_f =new TF1("MC_Eff_NewPar_up7_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_MC_up7->GetParameter(i));
  Double_t num_MC_NewPar_up7_before = MC_Eff_NewPar_up7_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"MC number for ParUp7 before tagger:   "<< num_MC_NewPar_up7_before <<endl;

  TF1 *MC_Eff_NewPar_down7_f =new TF1("MC_Eff_NewPar_down7_f",c_formula_MC_signal, 25,182);
  for(int i=0;i<7;i++)MC_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_MC_dn7->GetParameter(i));
  Double_t num_MC_NewPar_down7_before = MC_Eff_NewPar_down7_f->Integral(25,182,TMath::Power(10,-8)) / 2;
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

  Double_t all_up= TMath::Power(par1_up-num_MC_before,2)+TMath::Power(par2_up-num_MC_before,2)+TMath::Power(par3_up-num_MC_before,2)+TMath::Power(par4_up-num_MC_before,2)+TMath::Power(par5_up-num_MC_before,2)+TMath::Power(par6_up-num_MC_before,2)+TMath::Power(par7_up-num_MC_before,2);
  Double_t all_down= TMath::Power(par1_down-num_MC_before,2)+TMath::Power(par2_down-num_MC_before,2)+TMath::Power(par3_down-num_MC_before,2)+TMath::Power(par4_down-num_MC_before,2)+TMath::Power(par5_down-num_MC_before,2)+TMath::Power(par6_down-num_MC_before,2)+TMath::Power(par7_down-num_MC_before,2);
 

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
  TF1 *MC_bkg_Eff_NewPar_up1_f =new TF1("MC_bkg_Eff_NewPar_up1_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_MC_up1->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up1_before = MC_bkg_Eff_NewPar_up1_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp1 before tagger:   "<< num_MC_bkg_NewPar_up1_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down1_f =new TF1("MC_bkg_Eff_NewPar_down1_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_MC_dn1->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down1_before = MC_bkg_Eff_NewPar_down1_f->Integral(25,182) / 2;
  cout<<"MC number for ParDown1 before tagger:   "<< num_MC_bkg_NewPar_down1_before <<endl;

  //Par2
  TF1 *MC_bkg_Eff_NewPar_up2_f =new TF1("MC_bkg_Eff_NewPar_up2_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_MC_up2->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up2_before = MC_bkg_Eff_NewPar_up2_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp2 before tagger:   "<< num_MC_bkg_NewPar_up2_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down2_f =new TF1("MC_bkg_Eff_NewPar_down2_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_MC_dn2->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down2_before = MC_bkg_Eff_NewPar_down2_f->Integral(25,182) / 2;
  cout<<"MC number for ParDown2 before tagger:   "<< num_MC_bkg_NewPar_down2_before <<endl;

  //Par3
  TF1 *MC_bkg_Eff_NewPar_up3_f =new TF1("MC_bkg_Eff_NewPar_up3_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_MC_up3->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up3_before = MC_bkg_Eff_NewPar_up3_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp3 before tagger:   "<< num_MC_bkg_NewPar_up3_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down3_f =new TF1("MC_bkg_Eff_NewPar_down3_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_MC_dn3->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down3_before = MC_bkg_Eff_NewPar_down3_f->Integral(25,182) / 2;
  cout<<"MC number for ParDown3 before tagger:   "<< num_MC_bkg_NewPar_down3_before <<endl;

  //Par4
  TF1 *MC_bkg_Eff_NewPar_up4_f =new TF1("MC_bkg_Eff_NewPar_up4_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_MC_up4->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up4_before = MC_bkg_Eff_NewPar_up4_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp4 before tagger:   "<< num_MC_bkg_NewPar_up4_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down4_f =new TF1("MC_bkg_Eff_NewPar_down4_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_MC_dn4->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down4_before = MC_bkg_Eff_NewPar_down4_f->Integral(25,182) / 2;
  cout<<"MC number for ParDown4 before tagger:   "<< num_MC_bkg_NewPar_down4_before <<endl;

  //Par5
  TF1 *MC_bkg_Eff_NewPar_up5_f =new TF1("MC_bkg_Eff_NewPar_up5_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_MC_up5->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up5_before = MC_bkg_Eff_NewPar_up5_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp5 before tagger:   "<< num_MC_bkg_NewPar_up5_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down5_f =new TF1("MC_bkg_Eff_NewPar_down5_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_MC_dn5->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down5_before = MC_bkg_Eff_NewPar_down5_f->Integral(25,182) / 2;
  cout<<"MC number for ParDown5 before tagger:   "<< num_MC_bkg_NewPar_down5_before <<endl;

  //Par6
  TF1 *MC_bkg_Eff_NewPar_up6_f =new TF1("MC_bkg_Eff_NewPar_up6_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_MC_up6->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up6_before = MC_bkg_Eff_NewPar_up6_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp6 before tagger:   "<< num_MC_bkg_NewPar_up6_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down6_f =new TF1("MC_bkg_Eff_NewPar_down6_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_MC_dn6->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down6_before = MC_bkg_Eff_NewPar_down6_f->Integral(25,182) / 2;
  cout<<"MC number for ParDown6 before tagger:   "<< num_MC_bkg_NewPar_down6_before <<endl;

 //Par7
  TF1 *MC_bkg_Eff_NewPar_up7_f =new TF1("MC_bkg_Eff_NewPar_up7_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_MC_up7->GetParameter(i));
  Double_t num_MC_bkg_NewPar_up7_before = MC_bkg_Eff_NewPar_up7_f->Integral(25,182) / 2;
  cout<<"MC number for ParUp7 before tagger:   "<< num_MC_bkg_NewPar_up7_before <<endl;

  TF1 *MC_bkg_Eff_NewPar_down7_f =new TF1("MC_bkg_Eff_NewPar_down7_f",c_formula_MC_bkg, 25,182);
  for(int i=0;i<7;i++)MC_bkg_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_MC_dn7->GetParameter(i));
  Double_t num_MC_bkg_NewPar_down7_before = MC_bkg_Eff_NewPar_down7_f->Integral(25,182) / 2;
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

  all_up= TMath::Power(par1_up-number_back_MC_miss,2)+TMath::Power(par2_up-number_back_MC_miss,2)+TMath::Power(par3_up-number_back_MC_miss,2)+TMath::Power(par4_up-number_back_MC_miss,2)+TMath::Power(par5_up-number_back_MC_miss,2)+TMath::Power(par6_up-number_back_MC_miss,2)+TMath::Power(par7_up-number_back_MC_miss,2);
   all_down= TMath::Power(par1_down-number_back_MC_miss,2)+TMath::Power(par2_down-number_back_MC_miss,2)+TMath::Power(par3_down-number_back_MC_miss,2)+TMath::Power(par4_down-number_back_MC_miss,2)+TMath::Power(par5_down-number_back_MC_miss,2)+TMath::Power(par6_down-number_back_MC_miss,2)+TMath::Power(par7_down-number_back_MC_miss,2);
 

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

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data Data//
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout<<endl<<endl<<endl;
  cout <<"2. N_Data error calculation"<<endl;
  //cov matrix out of fit
  TMatrixDSym cov_Data = fit_data_result->GetCovarianceMatrix();  
  if(b_error){
    cout << "Kovarianzmatrix nach inital fit:" << endl << endl;
    cov_Data.Print();
    cout << endl << endl << endl << endl;
  }
  //resave cov matrix to calculate the eigenvalues and eigenvectors
  const TMatrixDSymEigen eigen_cov_Data(cov_Data);

  //calculate eigenvalues and eigenvectors
  const TVectorD eigen_values_Data = eigen_cov_Data.GetEigenValues();
  const TMatrixD eigen_vectors_Data = eigen_cov_Data.GetEigenVectors();
  if(b_error){
    cout << "eigen_values nach inital fit:" << endl << endl;
    eigen_values_Data.Print();
    cout << endl << endl << endl << endl;
    cout << "eigen_vectors_Data nach inital fit:" << endl << endl;
    eigen_vectors_Data.Print();
    cout << endl << endl << endl << endl;
  }

  if(b_error){
    //multiply eigen values with unitary matrix 
    TMatrixD M_Diag_Data(6,6);
    M_Diag_Data.UnitMatrix();
    for(int i=0; i<6; i++){
      double tmp_Data =eigen_values_Data[i];
      TMatrixDRow(M_Diag_Data,i)(i) = tmp_Data;
    }
 
    cout << "M_Diag_Data nach inital fit:" << endl << endl;
    M_Diag_Data.Print();
    cout << endl << endl << endl << endl;
  }

  //transform eigen vectors into row vectors 
  TMatrixD RT_Data(eigen_vectors_Data);
  RT_Data.T();
  if(b_error){
    cout << "Test: eigenvectorsT * cov * eigenvectors = eigen values * 1 [M_Diag_Data]" << endl << endl;
    TMatrixD test_diag_Data = RT_Data * cov_Data * eigen_vectors_Data;
    test_diag_Data.Print();
    cout << endl << endl << endl << endl;
  }

  //found transformation that diagonalised the cov matrix so we can used it to determine the uncorrelated parameters by P' = einenvectorsT * P


  //save old parameters P in a vector
  const double a_Data = fit_data_result->Parameter(0);
  const double b_Data = fit_data_result->Parameter(1);
  const double c_Data = fit_data_result->Parameter(2);
  const double d_Data = fit_data_result->Parameter(3);
  const double e_Data = fit_data_result->Parameter(4);
  const double f_Data = fit_data_result->Parameter(5);
  const double g_Data = fit_data_result->Parameter(6);
  const double old_params_Data[7] = {a_Data,b_Data,c_Data,d_Data,e_Data,f_Data,g_Data};
  const TVectorD V_Old_Param_Data(7,old_params_Data);

  if(b_error){
    cout << "V_Old_Param_Data nach inital fit:" << endl << endl;
    V_Old_Param_Data.Print();
    cout << endl << endl << endl << endl;
  }

  //calculate parameters in new basis
  TDecompSVD svd_Data(eigen_vectors_Data);
  Bool_t ok_Data;
  const TVectorD V_New_Param_Data = svd_Data.Solve(V_Old_Param_Data,ok_Data);
  if(b_error){
    cout << "V_New_Param_Data nach inital fit:" << endl << endl;
    V_New_Param_Data.Print();
    cout << endl << endl << endl << endl;
    cout <<"zuruecktransformierte alte werte:"<<endl;
    test_diag_Data = eigen_vectors_Data * V_New_Param_Data;
    test_diag_Data.Print();
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


  //parametrize old parameters by using new ones with eigen_vectors_Data
  TMatrixD M_Dummy_Data(eigen_vectors_Data);
  double a_tr_Data[7], b_tr_Data[7], c_tr_Data[7], d_tr_Data[7], e_tr_Data[7], f_tr_Data[7], g_tr_Data[7];
  for (int i=0; i<7; i++){
    a_tr_Data[i] = TMatrixDRow(M_Dummy_Data,0)[i];
    b_tr_Data[i] = TMatrixDRow(M_Dummy_Data,1)[i];
    c_tr_Data[i] = TMatrixDRow(M_Dummy_Data,2)[i];
    d_tr_Data[i] = TMatrixDRow(M_Dummy_Data,3)[i];
    e_tr_Data[i] = TMatrixDRow(M_Dummy_Data,4)[i];
    f_tr_Data[i] = TMatrixDRow(M_Dummy_Data,5)[i];
    g_tr_Data[i] = TMatrixDRow(M_Dummy_Data,6)[i];
  }

  //string of new fit function with uncorrelated parameters
  stringstream sstr_Data;
  sstr_Data  << "(" << d_tr_Data[0] << "*[0]+(" <<d_tr_Data[1]<<")*[1]+("<<d_tr_Data[2]<<")*[2]+("<<d_tr_Data[3]<<")*[3]+("<<d_tr_Data[4]<<")*[4]+("<<d_tr_Data[5]<<")*[5]+("<<d_tr_Data[6]<<")*[6]" <<")*TMath::Voigt(x-"<<"(" << c_tr_Data[0] << "*[0]+(" <<c_tr_Data[1]<<")*[1]+("<<c_tr_Data[2]<<")*[2]+("<<c_tr_Data[3]<<")*[3]+("<<c_tr_Data[4]<<")*[4]+("<<c_tr_Data[5]<<")*[5]+("<<c_tr_Data[6]<<")*[6]" <<"),"<<"(" << a_tr_Data[0] << "*[0]+(" <<a_tr_Data[1]<<")*[1]+("<<a_tr_Data[2]<<")*[2]+("<<a_tr_Data[3]<<")*[3]+("<<a_tr_Data[4]<<")*[4]+("<<a_tr_Data[5]<<")*[5]+("<<a_tr_Data[6]<<")*[6]" <<"),"<< "(" << b_tr_Data[0] << "*[0]+(" <<b_tr_Data[1]<<")*[1]+("<<b_tr_Data[2]<<")*[2]+("<<b_tr_Data[3]<<")*[3]+("<<b_tr_Data[4]<<")*[4]+("<<b_tr_Data[5]<<")*[5]+("<<b_tr_Data[6]<<")*[6]" <<")"<<",4)"<< "+" << "(" << e_tr_Data[0] << "*[0]+(" <<e_tr_Data[1]<<")*[1]+("<<e_tr_Data[2]<<")*[2]+("<<e_tr_Data[3]<<")*[3]+("<<e_tr_Data[4]<<")*[4]+("<<e_tr_Data[5]<<")*[5]+("<<e_tr_Data[6]<<")*[6]" <<")*(1-TMath::Erf((x-" <<"(" << f_tr_Data[0] << "*[0]+(" <<f_tr_Data[1]<<")*[1]+("<<f_tr_Data[2]<<")*[2]+("<<f_tr_Data[3]<<")*[3]+("<<f_tr_Data[4]<<")*[4]+("<<f_tr_Data[5]<<")*[5]+("<<f_tr_Data[6]<<")*[6]" <<")" <<")/(1.4 * "<<"(" << g_tr_Data[0] << "*[0]+(" <<g_tr_Data[1]<<")*[1]+("<<g_tr_Data[2]<<")*[2]+("<<g_tr_Data[3]<<")*[3]+("<<g_tr_Data[4]<<")*[4]+("<<g_tr_Data[5]<<")*[5]+("<<g_tr_Data[6]<<")*[6]" <<")"<<")))";

  //signal: TMath::Voigt(x-[2], [0], [1], 4)*[3]
  //background:  [0]*(1 - TMath::Erf((x-[1])/(1.4*[2])))
 
  string s_formula_Data = sstr_Data.str();
  const char * c_formula_Data = s_formula_Data.c_str();
  if(b_error){
    cout << "Fit Funktion mit neuen Parametern: " << endl;
    cout << c_formula_Data << endl<<endl<<endl;
  }

  //New fit fuction with uncoorelated parameters
  TF1* f_NewParam_Data = new TF1("f_NewParam_Data",c_formula_Data,25,182);
  f_NewParam_Data->SetParameter(0,V_New_Param_Data[0]);
  f_NewParam_Data->SetParameter(1,V_New_Param_Data[1]);
  f_NewParam_Data->SetParameter(2,V_New_Param_Data[2]);
  f_NewParam_Data->SetParameter(3,V_New_Param_Data[3]);
  f_NewParam_Data->SetParameter(4,V_New_Param_Data[4]);
  f_NewParam_Data->SetParameter(5,V_New_Param_Data[5]);
  f_NewParam_Data->FixParameter(6,V_New_Param_Data[6]);
  f_NewParam_Data->SetLineColor(kGreen+3);
  for(int i=25;i<183;i=i+5)cout <<"new: "<<f_NewParam_Data->Eval(i)<<" old: "<< data_fit->Eval(i)<<endl;

  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "Fit with new parameters: " << endl;
  cout << "=======================================================================" << endl << endl << endl;

  TCanvas* cfitnew_Data = new TCanvas("cfitnewData", "Fit function in new parameters, Data",10,10,700,900);
  TFitResultPtr fit_result_Data = data->Fit(f_NewParam_Data,"SR"); 
  cfitnew_Data->Print("Fit_signal_background_new.eps");
  cout << "Fit in new parameters, Data: " << endl;
  fit_result_Data->Print("V");


  //calculate fit parameter errors by hand: keep 6 fixed and vary one until chi2 increases by 1
  cout << endl << endl << endl << endl << endl;
  cout << "======================================================================="  << endl;
  cout << "Calculate errors by hand " << endl;
  cout << "=======================================================================" << endl << endl << endl;
  
  //define error function
  TF1* f_NewParam_Data_error = new TF1("f_NewParam_Data_error",c_formula_Data,25,182);

  //fix all fit values
  TCanvas* c_dummy_Data = new TCanvas("c_dummy_Data", "Fits for chi2 in Data", 10,10,700,900);
  for(int i=0; i<7; i++){
    f_NewParam_Data_error->FixParameter(i,fit_result_Data->Parameter(i));
  }
  
  cout << endl << endl << endl << "FIT BY HAND for CHI2 calculation: SIGNAL" << endl << endl << endl;

  //smalles chi2 out of the fit before
  all->Fit(f_NewParam_Data_error,"QR");
  double chi2_best_Data = f_NewParam_Data_error->GetChisquare();

  //set up arrays to save the errors 
  double pars_Data[7], pars_up_Data[7], pars_dn_Data[7], err_pars_up_Data[7], err_pars_dn_Data[7];
  for(int i=0; i<7; i++) pars_Data[i] = f_NewParam_Data_error->GetParameter(i);
  bool pars_up_set_Data[7] = {false,false,false,false,false,false,false};
  bool pars_dn_set_Data[7] = {false,false,false,false,false,false,false};
  TGraph* g_chi2_pars_Data[7];
  for(int i=0; i<7; i++) g_chi2_pars_Data[i] = new TGraph(50000);
  for_percent = 0;


  //varying all parameters in steps of 1/1000*par
  for(int j=0; j<7; j++){

    //reset parameters
    for(int k=0; k<7; k++) f_NewParam_Data_error->FixParameter(k,fit_result_Data->Parameter(k));
    
    double chi2_diff_Data = 0;
    for(int i=0; i<50000; i++){
      for_percent++;
      double varied_par_Data = -20*pars_Data[j] + pars_Data[j]/1000 * i;
      if(j==6)varied_par_Data = -0.000002*pars_Data[j] + pars_Data[j]/1000000 * i;
      f_NewParam_Data_error->FixParameter(j,varied_par_Data);
     
      all->Fit(f_NewParam_Data_error,"QR");

      double chi2_tmp_Data = f_NewParam_Data_error->GetChisquare();
      chi2_diff_Data = chi2_tmp_Data - chi2_best_Data;

      if(i%500 == 0)if(j==6) cout << "\r"  << for_percent/3500  << "%, " <<  "Parameter " << j << ", Fit No. " << i  << ", current chi2: " << chi2_tmp_Data << " at current parametervalue: " << varied_par_Data << "           "  << endl;

      if(!pars_dn_set_Data[j] && chi2_diff_Data < 1) {
	pars_dn_Data[j] = -20*pars_Data[j] + pars_Data[j]/1000 * (i-1);
	pars_dn_set_Data[j] = true;
      }
      if(pars_dn_set_Data[j] && !pars_up_set_Data[j] && chi2_diff_Data >= 1){
	pars_up_Data[j] = varied_par_Data;
	pars_up_set_Data[j] = true;
      }

      //draw chi2 as function of p0
      g_chi2_pars_Data[j]->SetPoint(i,varied_par_Data, chi2_tmp_Data);
    }
    if(pars_dn_Data[j] > pars_up_Data[j]) swap(pars_dn_Data[j],pars_up_Data[j]);
    
    err_pars_up_Data[j] = abs(pars_Data[j]-pars_up_Data[j]);
    err_pars_dn_Data[j] = abs(pars_Data[j]-pars_dn_Data[j]);
    
  }//varying all parameters in steps of 1/1000*par

  //define Line of the up and down variation in chi2
  TLine* l_pars_dn_Data[7];
  TLine* l_pars_up_Data[7];
  TLine* l_pars_central_Data[7];
  for(int i=0; i<7; i++){
    l_pars_up_Data[i] = new TLine(pars_up_Data[i], chi2_best_Data - 1, pars_up_Data[i], chi2_best_Data+10);
    l_pars_dn_Data[i] = new TLine(pars_dn_Data[i], chi2_best_Data - 1, pars_dn_Data[i], chi2_best_Data+10);
    l_pars_central_Data[i] = new TLine(pars_Data[i], chi2_best_Data, pars_Data[i], chi2_best_Data - 1);
    l_pars_up_Data[i]->SetLineWidth(3);
    l_pars_up_Data[i]->SetLineColor(kRed);
    l_pars_dn_Data[i]->SetLineWidth(3);
    l_pars_dn_Data[i]->SetLineColor(kRed);
    l_pars_central_Data[i]->SetLineWidth(3);
    l_pars_central_Data[i]->SetLineColor(kBlue);
  }
  for(int i=0; i<7; i++){
    stringstream n_Data;
    n_Data << "Parameter " << i+1;
    string s_n_Data = n_Data.str();
    const char * c_n_Data = s_n_Data.c_str();
    g_chi2_pars_Data[i]->SetMinimum(chi2_best_Data - 1);
    g_chi2_pars_Data[i]->SetMaximum(chi2_best_Data + 10);
    g_chi2_pars_Data[i]->SetTitle("Data");
    g_chi2_pars_Data[i]->GetXaxis()->SetTitle(c_n_Data);
    g_chi2_pars_Data[i]->GetXaxis()->SetTitleSize(0.044);
    g_chi2_pars_Data[i]->GetYaxis()->SetTitle("#chi^{2}");
    g_chi2_pars_Data[i]->GetYaxis()->SetTitleSize(0.044);
    g_chi2_pars_Data[i]->GetXaxis()->SetLimits(pars_dn_Data[i]-2*err_pars_dn_Data[i],pars_up_Data[i]+2*err_pars_up_Data[i]);
  }

  // example of a error calculated parameter by hand
  TCanvas* c_chi2_p0_Data = new TCanvas("c_chi2_p0_Data", "chi2 (p0)_Data", 1);
  g_chi2_pars_Data[6]->Draw();
  l_pars_up_Data[6]->Draw("SAME");
  l_pars_dn_Data[6]->Draw("SAME");
  l_pars_central_Data[6]->Draw("SAME");
  c_chi2_p0_Data->Print("Chi2_Data_p0.eps");

  //print all uncorrelated parameters with errors
  cout<<endl;
  for(int j=0; j<7; j++){
    cout << "Result Data: par " << j << " = " << pars_Data[j] << " (+" << err_pars_up_Data[j] << ") (-" << err_pars_dn_Data[j] << ")" << endl;
  }

  TF1* f_NewParam_Data_up1 = new TF1("f_NewParam_Data_up1", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn1 = new TF1("f_NewParam_Data_dn1", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_up2 = new TF1("f_NewParam_Data_up2", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn2 = new TF1("f_NewParam_Data_dn2", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_up3 = new TF1("f_NewParam_Data_up3", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn3 = new TF1("f_NewParam_Data_dn3", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_up4 = new TF1("f_NewParam_Data_up4", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn4 = new TF1("f_NewParam_Data_dn4", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_up5 = new TF1("f_NewParam_Data_up5", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn5 = new TF1("f_NewParam_Data_dn5", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_up6 = new TF1("f_NewParam_Data_up6", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn6 = new TF1("f_NewParam_Data_dn6", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_up7 = new TF1("f_NewParam_Data_up7", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dn7 = new TF1("f_NewParam_Data_dn7", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_upall = new TF1("f_NewParam_Data_upall", c_formula_Data,25, 182);
  TF1* f_NewParam_Data_dnall = new TF1("f_NewParam_Data_dnall", c_formula_Data,25, 182);

  for(int i=0; i<7; i++){
    f_NewParam_Data_up1->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn1->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_up2->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn2->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_up3->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn3->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_up4->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn4->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_up5->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn5->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_up6->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn6->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_up7->FixParameter(i,fit_result_Data->Parameter(i));
    f_NewParam_Data_dn7->FixParameter(i,fit_result_Data->Parameter(i));

    if(i==0){
      f_NewParam_Data_up1->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn1->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
    else if (i==1){
      f_NewParam_Data_up2->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn2->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
    else if (i==2){
      f_NewParam_Data_up3->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn3->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
    else if (i==3){
      f_NewParam_Data_up4->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn4->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
    else if (i==4){
      f_NewParam_Data_up5->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn5->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
    else if (i==5){
      f_NewParam_Data_up6->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn6->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
    else if (i==6){
      f_NewParam_Data_up7->FixParameter(i,fit_result_Data->Parameter(i) + err_pars_up_Data[i]);
      f_NewParam_Data_dn7->FixParameter(i,fit_result_Data->Parameter(i) - err_pars_dn_Data[i]);
    }
  }

 TCanvas* cupdnData = new TCanvas("cupdnData", "Functions varied up and down, Data",10,10,700,900);
  // f_NewParam_Data->Draw();
  // f_NewParam_Data_up1->SetLineColor(3);
  // f_NewParam_Data_up1->Draw("SAME");
  // f_NewParam_Data_dn1->SetLineColor(4);
  // f_NewParam_Data_dn1->Draw("SAME");
  // f_NewParam_Data_up2->SetLineColor(5);
  // f_NewParam_Data_up2->Draw("SAME");
  // f_NewParam_Data_dn2->SetLineColor(6);
  // f_NewParam_Data_dn2->Draw("SAME");
  // f_NewParam_Data_up3->SetLineColor(7);
  // f_NewParam_Data_up3->Draw("SAME");
  // f_NewParam_Data_dn3->SetLineColor(8);
  // f_NewParam_Data_dn3->Draw("SAME");
  // f_NewParam_Data_up4->SetLineColor(9);
  // f_NewParam_Data_up4->Draw("SAME");
  // f_NewParam_Data_dn4->SetLineColor(10);
  // f_NewParam_Data_dn4->Draw("SAME");
  // f_NewParam_Data_up5->SetLineColor(11);
  // f_NewParam_Data_up5->Draw("SAME");
  // f_NewParam_Data_dn5->SetLineColor(12);
  // f_NewParam_Data_dn5->Draw("SAME");
  // f_NewParam_Data_up6->SetLineColor(40);
  // f_NewParam_Data_up6->Draw("");
  // f_NewParam_Data_dn6->SetLineColor(42);
  // f_NewParam_Data_dn6->Draw("SAME");
 f_NewParam_Data_up7->SetLineColor(32);
 f_NewParam_Data_up7->Draw("");
  // f_NewParam_Data_dn7->SetLineColor(39);
  // f_NewParam_Data_dn7->Draw("SAME");

  //integrate over each variation and save the difference to normal number of sig events in Data before tagger
  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "integration of all up and down variations Data sig: " << num_Data_before <<endl;
  cout << "=======================================================================" << endl << endl << endl;

  // signal_fit function has to be express by 7 paramerters
  stringstream sstr_Data_signal;
  sstr_Data_signal  << "(" << d_tr_Data[0] << "*[0]+(" <<d_tr_Data[1]<<")*[1]+("<<d_tr_Data[2]<<")*[2]+("<<d_tr_Data[3]<<")*[3]+("<<d_tr_Data[4]<<")*[4]+("<<d_tr_Data[5]<<")*[5]+("<<d_tr_Data[6]<<")*[6]" <<")*TMath::Voigt(x-"<<"(" << c_tr_Data[0] << "*[0]+(" <<c_tr_Data[1]<<")*[1]+("<<c_tr_Data[2]<<")*[2]+("<<c_tr_Data[3]<<")*[3]+("<<c_tr_Data[4]<<")*[4]+("<<c_tr_Data[5]<<")*[5]+("<<c_tr_Data[6]<<")*[6]" <<"),"<<"(" << a_tr_Data[0] << "*[0]+(" <<a_tr_Data[1]<<")*[1]+("<<a_tr_Data[2]<<")*[2]+("<<a_tr_Data[3]<<")*[3]+("<<a_tr_Data[4]<<")*[4]+("<<a_tr_Data[5]<<")*[5]+("<<a_tr_Data[6]<<")*[6]" <<"),"<< "(" << b_tr_Data[0] << "*[0]+(" <<b_tr_Data[1]<<")*[1]+("<<b_tr_Data[2]<<")*[2]+("<<b_tr_Data[3]<<")*[3]+("<<b_tr_Data[4]<<")*[4]+("<<b_tr_Data[5]<<")*[5]+("<<b_tr_Data[6]<<")*[6]" <<")"<<",4)";
  string s_formula_Data_signal = sstr_Data_signal.str();
  const char * c_formula_Data_signal = s_formula_Data_signal.c_str();

  //Integrate over all up and down variation itself
  //Par1
  TF1 *Data_Eff_NewPar_up1_f =new TF1("Data_Eff_NewPar_up1_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_Data_up1->GetParameter(i));
  Double_t num_Data_NewPar_up1_before = Data_Eff_NewPar_up1_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp1 before tagger:   "<< num_Data_NewPar_up1_before <<endl;

  TF1 *Data_Eff_NewPar_down1_f =new TF1("Data_Eff_NewPar_down1_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_Data_dn1->GetParameter(i));
  Double_t num_Data_NewPar_down1_before = Data_Eff_NewPar_down1_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown1 before tagger:   "<< num_Data_NewPar_down1_before <<endl;

  //Par2
  TF1 *Data_Eff_NewPar_up2_f =new TF1("Data_Eff_NewPar_up2_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_Data_up2->GetParameter(i));
  Double_t num_Data_NewPar_up2_before = Data_Eff_NewPar_up2_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp2 before tagger:   "<< num_Data_NewPar_up2_before <<endl;

  TF1 *Data_Eff_NewPar_down2_f =new TF1("Data_Eff_NewPar_down2_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_Data_dn2->GetParameter(i));
  Double_t num_Data_NewPar_down2_before = Data_Eff_NewPar_down2_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown2 before tagger:   "<< num_Data_NewPar_down2_before <<endl;

  //Par3
  TF1 *Data_Eff_NewPar_up3_f =new TF1("Data_Eff_NewPar_up3_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_Data_up3->GetParameter(i));
  Double_t num_Data_NewPar_up3_before = Data_Eff_NewPar_up3_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp3 before tagger:   "<< num_Data_NewPar_up3_before <<endl;

  TF1 *Data_Eff_NewPar_down3_f =new TF1("Data_Eff_NewPar_down3_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_Data_dn3->GetParameter(i));
  Double_t num_Data_NewPar_down3_before = Data_Eff_NewPar_down3_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown3 before tagger:   "<< num_Data_NewPar_down3_before <<endl;

  //Par4
  TF1 *Data_Eff_NewPar_up4_f =new TF1("Data_Eff_NewPar_up4_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_Data_up4->GetParameter(i));
  Double_t num_Data_NewPar_up4_before = Data_Eff_NewPar_up4_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp4 before tagger:   "<< num_Data_NewPar_up4_before <<endl;

  TF1 *Data_Eff_NewPar_down4_f =new TF1("Data_Eff_NewPar_down4_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_Data_dn4->GetParameter(i));
  Double_t num_Data_NewPar_down4_before = Data_Eff_NewPar_down4_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown4 before tagger:   "<< num_Data_NewPar_down4_before <<endl;

  //Par5
  TF1 *Data_Eff_NewPar_up5_f =new TF1("Data_Eff_NewPar_up5_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_Data_up5->GetParameter(i));
  Double_t num_Data_NewPar_up5_before = Data_Eff_NewPar_up5_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp5 before tagger:   "<< num_Data_NewPar_up5_before <<endl;

  TF1 *Data_Eff_NewPar_down5_f =new TF1("Data_Eff_NewPar_down5_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_Data_dn5->GetParameter(i));
  Double_t num_Data_NewPar_down5_before = Data_Eff_NewPar_down5_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown5 before tagger:   "<< num_Data_NewPar_down5_before <<endl;

  //Par6
  TF1 *Data_Eff_NewPar_up6_f =new TF1("Data_Eff_NewPar_up6_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_Data_up6->GetParameter(i));
  Double_t num_Data_NewPar_up6_before = Data_Eff_NewPar_up6_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp6 before tagger:   "<< num_Data_NewPar_up6_before <<endl;

  TF1 *Data_Eff_NewPar_down6_f =new TF1("Data_Eff_NewPar_down6_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_Data_dn6->GetParameter(i));
  Double_t num_Data_NewPar_down6_before = Data_Eff_NewPar_down6_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown6 before tagger:   "<< num_Data_NewPar_down6_before <<endl;

 //Par7
  TF1 *Data_Eff_NewPar_up7_f =new TF1("Data_Eff_NewPar_up7_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_Data_up7->GetParameter(i));
  Data_Eff_NewPar_up7_f->Draw();
  Double_t num_Data_NewPar_up7_before = Data_Eff_NewPar_up7_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParUp7 before tagger:   "<< num_Data_NewPar_up7_before <<endl;

  TF1 *Data_Eff_NewPar_down7_f =new TF1("Data_Eff_NewPar_down7_f",c_formula_Data_signal, 25,182);
  for(int i=0;i<7;i++)Data_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_Data_dn7->GetParameter(i));
  Double_t num_Data_NewPar_down7_before = Data_Eff_NewPar_down7_f->Integral(25,182,TMath::Power(10,-8)) / 2;
  cout<<"Data number for ParDown7 before tagger:   "<< num_Data_NewPar_down7_before <<endl;

  if(num_Data_NewPar_up1_before>num_Data_before) {par1_up=num_Data_NewPar_up1_before;par1_down=num_Data_NewPar_down1_before;}
  else {par1_down=num_Data_NewPar_up1_before;par1_up=num_Data_NewPar_down1_before;}

  if(num_Data_NewPar_up2_before>num_Data_before) {par2_up=num_Data_NewPar_up2_before;par2_down=num_Data_NewPar_down2_before;}
  else {par2_down=num_Data_NewPar_up2_before;par2_up=num_Data_NewPar_down2_before;}

  if(num_Data_NewPar_up3_before>num_Data_before) {par3_up=num_Data_NewPar_up3_before;par3_down=num_Data_NewPar_down3_before;}
  else {par3_down=num_Data_NewPar_up3_before;par3_up=num_Data_NewPar_down3_before;}

  if(num_Data_NewPar_up4_before>num_Data_before) {par4_up=num_Data_NewPar_up4_before;par4_down=num_Data_NewPar_down4_before;}
  else {par4_down=num_Data_NewPar_up4_before;par4_up=num_Data_NewPar_down4_before;}

  if(num_Data_NewPar_up5_before>num_Data_before) {par5_up=num_Data_NewPar_up5_before;par5_down=num_Data_NewPar_down5_before;}
  else {par5_down=num_Data_NewPar_up5_before;par5_up=num_Data_NewPar_down5_before;}

  if(num_Data_NewPar_up6_before>num_Data_before) {par6_up=num_Data_NewPar_up6_before;par6_down=num_Data_NewPar_down6_before;}
  else {par6_down=num_Data_NewPar_up6_before;par6_up=num_Data_NewPar_down6_before;}

  if(num_Data_NewPar_up7_before>num_Data_before) {par7_up=num_Data_NewPar_up7_before;par7_down=num_Data_NewPar_down7_before;}
  else {par7_down=num_Data_NewPar_up7_before;par7_up=num_Data_NewPar_down7_before;}

  all_up= TMath::Power(par1_up-num_Data_before,2)+TMath::Power(par2_up-num_Data_before,2)+TMath::Power(par3_up-num_Data_before,2)+TMath::Power(par4_up-num_Data_before,2)+TMath::Power(par5_up-num_Data_before,2)+TMath::Power(par6_up-num_Data_before,2)+TMath::Power(par7_up-num_Data_before,2);
  all_down= TMath::Power(par1_down-num_Data_before,2)+TMath::Power(par2_down-num_Data_before,2)+TMath::Power(par3_down-num_Data_before,2)+TMath::Power(par4_down-num_Data_before,2)+TMath::Power(par5_down-num_Data_before,2)+TMath::Power(par6_down-num_Data_before,2)+TMath::Power(par7_down-num_Data_before,2);
 

  //write differences in file
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile <<"error calculation: Data signal vorher "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "Parameter 1 Upvariation "<< par1_up-num_Data_before<<endl;
  myfile << "Parameter 1 Downvariation "<< par1_down-num_Data_before<<endl;
  myfile << "Parameter 2 Upvariation "<< par2_up-num_Data_before<<endl;
  myfile << "Parameter 2 Downvariation "<< par2_down-num_Data_before<<endl;
  myfile << "Parameter 3 Upvariation "<< par3_up-num_Data_before<<endl;
  myfile << "Parameter 3 Downvariation "<< par3_down-num_Data_before<<endl;
  myfile << "Parameter 4 Upvariation "<< par4_up-num_Data_before<<endl;
  myfile << "Parameter 4 Downvariation "<< par4_down-num_Data_before<<endl;
  myfile << "Parameter 5 Upvariation "<< par5_up-num_Data_before<<endl;
  myfile << "Parameter 5 Downvariation "<< par5_down-num_Data_before<<endl;
  myfile << "Parameter 6 Upvariation "<< par6_up-num_Data_before<<endl;
  myfile << "Parameter 6 Downvariation "<< par6_down-num_Data_before<<endl;
  myfile << "Parameter 7 Upvariation "<< par7_up-num_Data_before<<endl;
  myfile << "Parameter 7 Downvariation "<< par7_down-num_Data_before<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "all up variations quadraticly added: "<<TMath::Sqrt(all_up)<<endl;
  myfile << "all down variations quadraticly added: -"<<TMath::Sqrt(all_down)<<endl;



 //integrate over each variation and save the difference to normal number of bkg events in Data before tagger
  cout << endl << endl << endl << endl << endl;
  cout << "=======================================================================" << endl;
  cout << "integration of all up and down variations Data bkg: " << number_back_Data_miss <<endl;
  cout << "=======================================================================" << endl << endl << endl;

  // bkg_fit function has to be express by 7 paramerters
  stringstream sstr_Data_bkg;
  sstr_Data_bkg  << "(" << e_tr_Data[0] << "*[0]+(" <<e_tr_Data[1]<<")*[1]+("<<e_tr_Data[2]<<")*[2]+("<<e_tr_Data[3]<<")*[3]+("<<e_tr_Data[4]<<")*[4]+("<<e_tr_Data[5]<<")*[5]+("<<e_tr_Data[6]<<")*[6]" <<")*(1-TMath::Erf((x-" <<"(" << f_tr_Data[0] << "*[0]+(" <<f_tr_Data[1]<<")*[1]+("<<f_tr_Data[2]<<")*[2]+("<<f_tr_Data[3]<<")*[3]+("<<f_tr_Data[4]<<")*[4]+("<<f_tr_Data[5]<<")*[5]+("<<f_tr_Data[6]<<")*[6]" <<")" <<")/(1.4 * "<<
    "(" << g_tr_Data[0] << "*[0]+(" <<g_tr_Data[1]<<")*[1]+("<<g_tr_Data[2]<<")*[2]+("<<g_tr_Data[3]<<")*[3]+("<<g_tr_Data[4]<<")*[4]+("<<g_tr_Data[5]<<")*[5]+("<<g_tr_Data[6]<<")*[6]" <<")"<<")))";
  string s_formula_Data_bkg = sstr_Data_bkg.str();
  const char * c_formula_Data_bkg = s_formula_Data_bkg.c_str();

  //Integrate over all up and down variation itself
  //Par1
  TF1 *Data_bkg_Eff_NewPar_up1_f =new TF1("Data_bkg_Eff_NewPar_up1_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up1_f->SetParameter(i, f_NewParam_Data_up1->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up1_before = Data_bkg_Eff_NewPar_up1_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp1 before tagger:   "<< num_Data_bkg_NewPar_up1_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down1_f =new TF1("Data_bkg_Eff_NewPar_down1_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down1_f->SetParameter(i, f_NewParam_Data_dn1->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down1_before = Data_bkg_Eff_NewPar_down1_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown1 before tagger:   "<< num_Data_bkg_NewPar_down1_before <<endl;

  //Par2
  TF1 *Data_bkg_Eff_NewPar_up2_f =new TF1("Data_bkg_Eff_NewPar_up2_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up2_f->SetParameter(i, f_NewParam_Data_up2->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up2_before = Data_bkg_Eff_NewPar_up2_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp2 before tagger:   "<< num_Data_bkg_NewPar_up2_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down2_f =new TF1("Data_bkg_Eff_NewPar_down2_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down2_f->SetParameter(i, f_NewParam_Data_dn2->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down2_before = Data_bkg_Eff_NewPar_down2_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown2 before tagger:   "<< num_Data_bkg_NewPar_down2_before <<endl;

  //Par3
  TF1 *Data_bkg_Eff_NewPar_up3_f =new TF1("Data_bkg_Eff_NewPar_up3_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up3_f->SetParameter(i, f_NewParam_Data_up3->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up3_before = Data_bkg_Eff_NewPar_up3_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp3 before tagger:   "<< num_Data_bkg_NewPar_up3_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down3_f =new TF1("Data_bkg_Eff_NewPar_down3_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down3_f->SetParameter(i, f_NewParam_Data_dn3->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down3_before = Data_bkg_Eff_NewPar_down3_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown3 before tagger:   "<< num_Data_bkg_NewPar_down3_before <<endl;

  //Par4
  TF1 *Data_bkg_Eff_NewPar_up4_f =new TF1("Data_bkg_Eff_NewPar_up4_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up4_f->SetParameter(i, f_NewParam_Data_up4->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up4_before = Data_bkg_Eff_NewPar_up4_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp4 before tagger:   "<< num_Data_bkg_NewPar_up4_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down4_f =new TF1("Data_bkg_Eff_NewPar_down4_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down4_f->SetParameter(i, f_NewParam_Data_dn4->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down4_before = Data_bkg_Eff_NewPar_down4_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown4 before tagger:   "<< num_Data_bkg_NewPar_down4_before <<endl;

  //Par5
  TF1 *Data_bkg_Eff_NewPar_up5_f =new TF1("Data_bkg_Eff_NewPar_up5_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up5_f->SetParameter(i, f_NewParam_Data_up5->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up5_before = Data_bkg_Eff_NewPar_up5_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp5 before tagger:   "<< num_Data_bkg_NewPar_up5_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down5_f =new TF1("Data_bkg_Eff_NewPar_down5_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down5_f->SetParameter(i, f_NewParam_Data_dn5->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down5_before = Data_bkg_Eff_NewPar_down5_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown5 before tagger:   "<< num_Data_bkg_NewPar_down5_before <<endl;

  //Par6
  TF1 *Data_bkg_Eff_NewPar_up6_f =new TF1("Data_bkg_Eff_NewPar_up6_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up6_f->SetParameter(i, f_NewParam_Data_up6->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up6_before = Data_bkg_Eff_NewPar_up6_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp6 before tagger:   "<< num_Data_bkg_NewPar_up6_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down6_f =new TF1("Data_bkg_Eff_NewPar_down6_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down6_f->SetParameter(i, f_NewParam_Data_dn6->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down6_before = Data_bkg_Eff_NewPar_down6_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown6 before tagger:   "<< num_Data_bkg_NewPar_down6_before <<endl;

 //Par7
  TF1 *Data_bkg_Eff_NewPar_up7_f =new TF1("Data_bkg_Eff_NewPar_up7_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_up7_f->SetParameter(i, f_NewParam_Data_up7->GetParameter(i));
  Double_t num_Data_bkg_NewPar_up7_before = Data_bkg_Eff_NewPar_up7_f->Integral(25,182) / 2;
  cout<<"Data number for ParUp7 before tagger:   "<< num_Data_bkg_NewPar_up7_before <<endl;

  TF1 *Data_bkg_Eff_NewPar_down7_f =new TF1("Data_bkg_Eff_NewPar_down7_f",c_formula_Data_bkg, 25,182);
  for(int i=0;i<7;i++)Data_bkg_Eff_NewPar_down7_f->SetParameter(i, f_NewParam_Data_dn7->GetParameter(i));
  Double_t num_Data_bkg_NewPar_down7_before = Data_bkg_Eff_NewPar_down7_f->Integral(25,182) / 2;
  cout<<"Data number for ParDown7 before tagger:   "<< num_Data_bkg_NewPar_down7_before <<endl;

  if(num_Data_bkg_NewPar_up1_before>number_back_Data_miss) {par1_up=num_Data_bkg_NewPar_up1_before;par1_down=num_Data_bkg_NewPar_down1_before;}
  else {par1_down=num_Data_bkg_NewPar_up1_before;par1_up=num_Data_bkg_NewPar_down1_before;}

  if(num_Data_bkg_NewPar_up2_before>number_back_Data_miss) {par2_up=num_Data_bkg_NewPar_up2_before;par2_down=num_Data_bkg_NewPar_down2_before;}
  else {par2_down=num_Data_bkg_NewPar_up2_before;par2_up=num_Data_bkg_NewPar_down2_before;}

  if(num_Data_bkg_NewPar_up3_before>number_back_Data_miss) {par3_up=num_Data_bkg_NewPar_up3_before;par3_down=num_Data_bkg_NewPar_down3_before;}
  else {par3_down=num_Data_bkg_NewPar_up3_before;par3_up=num_Data_bkg_NewPar_down3_before;}

  if(num_Data_bkg_NewPar_up4_before>number_back_Data_miss) {par4_up=num_Data_bkg_NewPar_up4_before;par4_down=num_Data_bkg_NewPar_down4_before;}
  else {par4_down=num_Data_bkg_NewPar_up4_before;par4_up=num_Data_bkg_NewPar_down4_before;}

  if(num_Data_bkg_NewPar_up5_before>number_back_Data_miss) {par5_up=num_Data_bkg_NewPar_up5_before;par5_down=num_Data_bkg_NewPar_down5_before;}
  else {par5_down=num_Data_bkg_NewPar_up5_before;par5_up=num_Data_bkg_NewPar_down5_before;}

  if(num_Data_bkg_NewPar_up6_before>number_back_Data_miss) {par6_up=num_Data_bkg_NewPar_up6_before;par6_down=num_Data_bkg_NewPar_down6_before;}
  else {par6_down=num_Data_bkg_NewPar_up6_before;par6_up=num_Data_bkg_NewPar_down6_before;}

  if(num_Data_bkg_NewPar_up7_before>number_back_Data_miss) {par7_up=num_Data_bkg_NewPar_up7_before;par7_down=num_Data_bkg_NewPar_down7_before;}
  else {par7_down=num_Data_bkg_NewPar_up7_before;par7_up=num_Data_bkg_NewPar_down7_before;}

  all_up= TMath::Power(par1_up-number_back_Data_miss,2)+TMath::Power(par2_up-number_back_Data_miss,2)+TMath::Power(par3_up-number_back_Data_miss,2)+TMath::Power(par4_up-number_back_Data_miss,2)+TMath::Power(par5_up-number_back_Data_miss,2)+TMath::Power(par6_up-number_back_Data_miss,2)+TMath::Power(par7_up-number_back_Data_miss,2);
   all_down= TMath::Power(par1_down-number_back_Data_miss,2)+TMath::Power(par2_down-number_back_Data_miss,2)+TMath::Power(par3_down-number_back_Data_miss,2)+TMath::Power(par4_down-number_back_Data_miss,2)+TMath::Power(par5_down-number_back_Data_miss,2)+TMath::Power(par6_down-number_back_Data_miss,2)+TMath::Power(par7_down-number_back_Data_miss,2);
 

  //write differences in file
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile <<"error calculation: Data bkg vorher "<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "Parameter 1 Upvariation "<< par1_up-number_back_Data_miss<<endl;
  myfile << "Parameter 1 Downvariation "<< par1_down-number_back_Data_miss<<endl;
  myfile << "Parameter 2 Upvariation "<< par2_up-number_back_Data_miss<<endl;
  myfile << "Parameter 2 Downvariation "<< par2_down-number_back_Data_miss<<endl;
  myfile << "Parameter 3 Upvariation "<< par3_up-number_back_Data_miss<<endl;
  myfile << "Parameter 3 Downvariation "<< par3_down-number_back_Data_miss<<endl;
  myfile << "Parameter 4 Upvariation "<< par4_up-number_back_Data_miss<<endl;
  myfile << "Parameter 4 Downvariation "<< par4_down-number_back_Data_miss<<endl;
  myfile << "Parameter 5 Upvariation "<< par5_up-number_back_Data_miss<<endl;
  myfile << "Parameter 5 Downvariation "<< par5_down-number_back_Data_miss<<endl;
  myfile << "Parameter 6 Upvariation "<< par6_up-number_back_Data_miss<<endl;
  myfile << "Parameter 6 Downvariation "<< par6_down-number_back_Data_miss<<endl;
  myfile << "Parameter 7 Upvariation "<< par7_up-number_back_Data_miss<<endl;
  myfile << "Parameter 7 Downvariation "<< par7_down-number_back_Data_miss<<endl;
  myfile << "----------------------------------------------------------------------------------------------------------"<<endl;
  myfile << "all up variations quadraticly added: "<<TMath::Sqrt(all_up)<<endl;
  myfile << "all down variations quadraticly added: -"<<TMath::Sqrt(all_down)<<endl;





















  myfile.close();
}//End of function

















