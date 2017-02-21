#include "TH1.h"
#include "TH2.h"
#include <fstream>

using namespace std;

void puppiplotter()
{
  //general
  //  gStyle->SetOptFit(1111);
  //  gStyle->SetOptStat(0);
  bool berror=true;
  TString folder="puppi_test";

  

  //read in all Files: QCD
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/";
  TString output_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/pictures/";
  TFile *QCD_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");;
 
  ///////////////////////      Jet PT Scale       ////////////////////////////////////////////////
  if(berror) std::cout<<"JetPTScale "<<std::endl;
  TString hist_name;

  //defining all Eta ranges
  // std::vector<TString> eta_ranges={"Eta0to1p3","Eta1p3to2","Eta2to2p5","Eta2p5to3","Eta3to10"};
  // std::vector<TString> pt_ranges={"30to40", "100to150"};
  // std::vector<TString> ak_ranges={"topjet", "jet"};

  std::vector<TString> eta_ranges={"Eta0to1p3"};
  std::vector<TString> pt_ranges={"30to40"};
  std::vector<TString> ak_ranges={"jet"};

  for(int i=0;i<ak_ranges.size();i++){
    for(int k=0;k<pt_ranges.size();k++){
      for(int j=0;j<eta_ranges.size();j++){
	
	hist_name = ak_ranges[i];
	hist_name+= "_pt_";
	hist_name+= pt_ranges[k];
	if(ak_ranges[i]=="jet")	hist_name+= "/JetPtScale_";
	else if(ak_ranges[i]=="topjet")	hist_name+= "/TopJetPtScale_";
	hist_name+= eta_ranges[j];

	if(berror) std::cout<<"JetPTScale::read in Hists "<<hist_name<<std::endl;
	//read in Histogramms
	TH2F* hist = (TH2F*)QCD_f->Get(hist_name);
	if (berror){  
	  TCanvas *c1 = new TCanvas("c1","input hist",10,10,1200,900);
	  c1->Clear();
	  c1->cd();
	  hist->Draw("colz");
	  hist->Print("input_hist.eps");
	}


 


	if(berror) std::cout<<"JetPTScale::rebin Hists "<<hist_name<<std::endl;
	//rebin hists as in presentation	  
	Double_t bins_x[11]={0,5,10,15,20,25,30,35,40,60,100};
	TAxis *xaxis = hist->GetXaxis();
	TAxis *yaxis = hist->GetYaxis();
	TH2F* rebinned_hist = new TH2F("rebinned",hist->GetTitle(),10,bins_x,10,-1,1);
	for (int j=1; j<=yaxis->GetNbins();j++) {
	  for (int i=1; i<=xaxis->GetNbins();i++) {
	    rebinned_hist->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist->GetBinContent(i,j));
	  }
	}
	if (berror){  
	  TCanvas *c2 = new TCanvas("c2","rebinned hist",10,10,1200,900);
	  c2->Clear();
	  c2->cd();
	  rebinned_hist->Draw("colz");
	  rebinned_hist->Print("rebinned_hist.eps");
	}

	//Get slice of NPV to see gaussian distribution for Mean and RMS
	TH1D *gaussian;

	 
	  gaussian = rebinned_hist->  ProfileY("_y",8,9);
	
	if (berror){  
	  TCanvas *c3 = new TCanvas("c3","gaussian hist",10,10,700,900);
	  c3->Clear();
	  c3->cd();
	  gaussian->Draw();
	  gaussian->Print("gaussian.eps");
	}


	//	rebinned_hist->GetXaxis()->SetRange(3,3);


      }//eta_ranges
    }//pt_ranges
  }//ak_ranges













}
