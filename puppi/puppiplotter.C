#include "TH1.h"
#include "TH2.h"
#include <fstream>

using namespace std;

void puppiplotter()
{
  //general
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  bool berror=false;
  TString folder="puppi_test";

  

  //read in all Files: QCD
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/";
  TString output_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/pictures/";
  TFile *QCD_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  TFile *Result_f = new TFile(output_folder+folder+"/uhh2.AnalysisModuleRunner.MC.Result.root", "RECREATE");
  ///////////////////////      Jet PT Scale       ////////////////////////////////////////////////
  if(berror) std::cout<<"JetPTScale "<<std::endl;
  TString hist_name;

  //defining all Eta ranges
  // std::vector<TString> eta_ranges={"Eta0to1p3","Eta1p3to2","Eta2to2p5","Eta2p5to3","Eta3to10"};
  // std::vector<TString> pt_ranges={"30to40", "100to150"};
  // std::vector<TString> ak_ranges={"topjet", "jet"};
  // std::vector<TString> eff_ranges={"Efficiency_Gen", "Purity_Reco"};
  // std::vector<TString> var_ranges={"JetEta", "JetPt","JetNPV"};

  std::vector<TString>  eta_ranges={"Eta0to1p3"};
  std::vector<TString> pt_ranges={"100to150"};
  std::vector<TString> ak_ranges={"jet"};
  std::vector<TString> eff_ranges={"Efficiency_Gen"};
  std::vector<TString> var_ranges={"JetEta"};


  if(false){
  for(int i=0;i<ak_ranges.size();i++){
    for(int k=0;k<pt_ranges.size();k++){
      for(int j=0;j<eta_ranges.size();j++){
	
	hist_name = ak_ranges[i];
	hist_name+= "_pt_";
	hist_name+= pt_ranges[k];
	if(ak_ranges[i]=="jet")	hist_name+= "/JetPtScale_";
	else if(ak_ranges[i]=="topjet")	hist_name+= "/TopJetMassScale_";
	hist_name+= eta_ranges[j];

	if(berror) std::cout<<"JetPTScale::read in Hists "<<hist_name<<std::endl;
	//read in Histogramms
	TH2F* hist = (TH2F*)QCD_f->Get(hist_name);
	if (berror){  
	  TCanvas *c1 = new TCanvas("c1","input hist",10,10,1200,900);
	  c1->Clear();
	  c1->cd();
	  gPad->SetTickx();
	  gPad->SetTicky();
	  hist->Draw("colz");
	  c1->Print(output_folder+folder+"/input/"+ak_ranges[i]+"_"+pt_ranges[k]+"_"+eta_ranges[j]+"_input_hist.eps");
	}


	if(berror) std::cout<<"JetPTScale::rebin Hists "<<hist_name<<std::endl;
	//rebin hists as in presentation	  
	Double_t bins_x[11]={0,5,10,15,20,25,30,35,40,60,100};
	TAxis *xaxis = hist->GetXaxis();
	TAxis *yaxis = hist->GetYaxis();
	TH2F* rebinned_hist = new TH2F("rebinned",hist->GetTitle(),10,bins_x,200,-1,1);
	for (int j=1; j<=yaxis->GetNbins();j++) {
	  for (int i=1; i<=xaxis->GetNbins();i++) {
	    rebinned_hist->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist->GetBinContent(i,j));
	  }
	}
	if (berror){  
	  TCanvas *c2 = new TCanvas("c2","rebinned hist",10,10,1200,900);
	  c2->Clear();
	  c2->cd();
	  gPad->SetTickx();
	  gPad->SetTicky();
	  rebinned_hist->Draw("colz");
	  c2->Print(output_folder+folder+"/rebinned/"+ak_ranges[i]+"_"+pt_ranges[k]+"_"+eta_ranges[j]+"_rebinned_hist.eps");
	}


	//Get slice of NPV to see gaussian distribution for Mean and RMS
	TH1D *gaussian;
	TCanvas *c3= new TCanvas("c3","gaussian hist",10,10,700,900);
	TCanvas *gaussian_c = new TCanvas("gaussian_c","gaussian fit",10,10,700,900);
	TH1F *result_mean = new TH1F("result_mean",hist->GetTitle(),10,bins_x);
	TH1F *result_rms = new TH1F("result_rms",hist->GetTitle(),10,bins_x);

	for (int l=1; l<=rebinned_hist->GetXaxis()->GetNbins();l++) {
	gaussian = rebinned_hist->  ProjectionY("_y",l,l+1);

	if (berror){  
	  std::cout<<"slice  "<<l<<std::endl;
	  c3->Clear();
	  c3->cd();
	  gPad->SetTickx();
	  gPad->SetTicky();
	  gaussian->Draw();
	}

	//Fit a Gaussian distribution
	gaussian_c->Clear();
	gaussian_c->cd();
	gPad->SetTickx();
	gPad->SetTicky();
 	gaussian->Draw("PZ");

	//do the fit serveral times to fit only interesting region
	TF1* gaussian_fit = new TF1("gaussian_fit", "gaus");
	gaussian_fit->SetParameter(0, 0);
	gaussian_fit->SetParameter(1, 0.2);
	gaussian->Fit(gaussian_fit);
	for(int i=0; i<2;i++){
	  double lower_bound = gaussian_fit->GetParameter(1) -1.5*gaussian_fit->GetParameter(2);
	  double higher_bound = gaussian_fit->GetParameter(1)+1.5*gaussian_fit->GetParameter(2);
	  if(berror) std::cout<<"lower boundary  "<<lower_bound << "higher boundary  "<<higher_bound<<std::endl;
	  if(berror) std::cout<<"mean  "<<gaussian_fit->GetParameter(1) <<"rms  "<< gaussian_fit->GetParameter(2)<<std::endl;

	  gaussian_fit = new TF1("gaussian_fit", "gaus",lower_bound,higher_bound);
	  gaussian_fit->SetParameter(0, gaussian_fit->GetParameter(1));
	  gaussian_fit->SetParameter(1,gaussian_fit->GetParameter(2));
	  gaussian->Fit(gaussian_fit,"R");
	}

	stringstream ss;
	ss << l;
	string str = ss.str();


	c3->Print(output_folder+folder+"/gaussian/"+ak_ranges[i]+"_"+pt_ranges[k]+"_"+eta_ranges[j]+"_slice_"+str+"_gaussian.eps");

	if(berror) std::cout<<"Mean  "<<gaussian_fit->GetParameter(1)<<std::endl;
	if(berror) std::cout<<"Mean by GetMean "<<gaussian->GetMean()<<std::endl;
	if(berror) std::cout<<"RMS  "<<gaussian_fit->GetParameter(2)<<std::endl;

	result_mean->SetBinContent(l,gaussian_fit->GetParameter(1));
	result_mean->SetBinError(l,gaussian_fit->GetParError(1));

	result_rms->SetBinContent(l,gaussian_fit->GetParameter(2));
	result_rms->SetBinError(l,gaussian_fit->GetParError(2));
	}//over all slices

	
	TCanvas *result_mean_c= new TCanvas("result_mean_c","Result Mean",10,10,700,900);
	result_mean_c->Clear();
	result_mean_c->cd();
	gPad->SetTickx();
	gPad->SetTicky();
	result_mean->SetMaximum(1);
	result_mean->SetMinimum(-1);
	result_mean->Draw("E1");
	result_mean_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+pt_ranges[k]+"_"+eta_ranges[j]+"_result_mean.eps");
	TCanvas *result_rms_c= new TCanvas("result_rms_c","Result Rms",10,10,700,900);
	result_rms_c->Clear();
	result_rms_c->cd();
	gPad->SetTickx();
	gPad->SetTicky();
	result_rms->SetMaximum(1);
	result_rms->SetMinimum(0);
	result_rms->Draw("E1");
	result_rms_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+pt_ranges[k]+"_"+eta_ranges[j]+"_result_rms.eps");
	
	Result_f->cd();
	result_mean->Write();
	result_rms->Write();

      }//eta_ranges
    }//pt_ranges
  }//ak_ranges
  ////////////////////////////////////////////     finished: Jet Pt scale and TopJet mass scale ///////////////////////////////////////////////////
  }

  // ////////////////////////////////////////////     starting: Purity and Efficiency  ///////////////////////////////////////////////////

  
  for(int i=0;i<ak_ranges.size();i++){
    for(int j=0;j<eff_ranges.size();j++){
      for(int k=0;k<var_ranges.size();k++){
      	hist_name = ak_ranges[i];
  	hist_name+="_pt_25/Jet";
  	hist_name+=eff_ranges[j];
  	if(ak_ranges[i]=="topjet") hist_name+="Top";
  	hist_name+=var_ranges[k];

  	if(berror) std::cout<<"Purity and Efficiency::read in Hists "<<hist_name<<std::endl;
  	//read in Histogramms
  	TH1F* hist = (TH1F*)QCD_f->Get(hist_name);
  	if(ak_ranges[i]=="jet") hist_name+="_matchedjet";
  	if(ak_ranges[i]=="topjet") hist_name+="_matchedTopjet";
  	TH1F* hist_matched = (TH1F*)QCD_f->Get(hist_name);

	TCanvas *hist_c= new TCanvas("hist_c","hist",10,10,700,900);
 	hist_c->Clear();
  	hist_c->cd();
	hist->Draw();
	TCanvas *hist_matched_c= new TCanvas("hist_matched_c","hist_matched",10,10,700,900);
 	hist_matched_c->Clear();
  	hist_matched_c->cd();
	hist_matched->Draw();

  	//divide both hists
	TGraphAsymmErrors* eff = new TGraphAsymmErrors( hist_matched, hist, "cl=0.683 b(1,1) mode" );
	
  	TCanvas *result_eff_c= new TCanvas("result_eff_c","Result Efficiency",10,10,700,900);
  	result_eff_c->Clear();
  	result_eff_c->cd();
  	eff->SetMaximum(1);
	//	eff->SetMinimum(0.8);
	eff->GetXaxis()->SetRangeUser(-5,5);
	eff->Draw("AP");
  	result_eff_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+eff_ranges[j]+"_"+var_ranges[k]+".eps");
      
      }//var_ranges
    }//eff or Purity
  }//ak_ranges
  	

 






}
