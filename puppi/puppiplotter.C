#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"


using namespace std;

void puppiplotter()
{
  //general
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);
  bool berror=false;
  TString folder="puppi_test";
  if(berror)gROOT->SetBatch(kFALSE);
  

  //read in all Files: QCD
  TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/";
  TString output_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/pictures/";
  TFile *QCD_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  TFile *Result_f = new TFile(output_folder+folder+"/uhh2.AnalysisModuleRunner.MC.Result.root", "RECREATE");
  ///////////////////////      Jet PT Scale       ////////////////////////////////////////////////
  if(berror) std::cout<<"JetPTScale "<<std::endl;
  TString hist_name;

  //defining all Eta ranges
  std::vector<TString> eta_ranges={"Eta0to1p3","Eta1p3to2","Eta2to2p5","Eta2p5to3","Eta3to10"};
  std::vector<TString> pt_ranges={"30to40", "100to150"};
  std::vector<TString> ak_ranges={ "topjet","jet"};
  std::vector<TString> eff_ranges={"Efficiency_Gen", "Purity_Reco"};
  std::vector<TString> var_ranges={"JetEta", "JetPt","JetNPV"};
  std::vector<TString> scale_ranges={"TopJetMassScale_","TopJetMassScale_GEV_"};

  // std::vector<TString>  eta_ranges={"Eta0to1p3"};
  // std::vector<TString> pt_ranges={"100to150"};
  // std::vector<TString> ak_ranges={"topjet","jet"};
  // std::vector<TString> eff_ranges={"Efficiency_Gen"};
  //  std::vector<TString> var_ranges={"JetPt"};

  if(false){
  for(int i=0;i<ak_ranges.size();i++){
    if(ak_ranges[i]=="jet")scale_ranges={"JetPtScale_"};
    if(ak_ranges[i]=="topjet")scale_ranges={"TopJetMassScale_","TopJetMassScale_GEV_"};
    for(int l=0;l<scale_ranges.size();l++){
      for(int k=0;k<pt_ranges.size();k++){
	for(int j=0;j<eta_ranges.size();j++){
	  hist_name = ak_ranges[i];
	  hist_name+= "_pt_";
	  hist_name+= pt_ranges[k];
	  hist_name+= "/";
	  hist_name+= scale_ranges[l];
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
	    c1->Print(output_folder+folder+"/input/"+ak_ranges[i]+"_"+scale_ranges[l]+pt_ranges[k]+"_"+eta_ranges[j]+"_input_hist.eps");
	    c1->Destructor();
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
	    c2->Print(output_folder+folder+"/rebinned/"+ak_ranges[i]+"_"+scale_ranges[l]+pt_ranges[k]+"_"+eta_ranges[j]+"_rebinned_hist.eps");
	    c2->Destructor();
	  }


	  //Get slice of NPV to see gaussian distribution for Mean and RMS
	  TH1D *gaussian;
	  TCanvas *c3= new TCanvas("c3","gaussian hist",10,10,700,900);
	  TCanvas *gaussian_c = new TCanvas("gaussian_c","gaussian fit",10,10,700,900);
	  // TH1F *result_mean = new TH1F("result_mean",hist->GetTitle(),10,bins_x);
	  // TH1F *result_rms = new TH1F("result_rms",hist->GetTitle(),10,bins_x);
	  TH1F *result_mean = new TH1F("result_mean","",10,bins_x);
	  TH1F *result_rms = new TH1F("result_rms","",10,bins_x);
	  TH1F *rms = new TH1F("result_rms","",10,bins_x);

	  for (int p=1; p<=rebinned_hist->GetXaxis()->GetNbins();p++) {
	    gaussian = rebinned_hist->  ProjectionY("_y",p,p+1);
	    rms->SetBinContent(p,gaussian->GetRMS());
	    rms->SetBinError(p,gaussian->GetRMSError());
	    if (berror){  
	      std::cout<<"slice  "<<p<<std::endl;
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
	    ss << p;
	    string str = ss.str();


	    c3->Print(output_folder+folder+"/gaussian/"+ak_ranges[i]+"_"+scale_ranges[l]+pt_ranges[k]+"_"+eta_ranges[j]+"_slice_"+str+"_gaussian.eps");

	    if(berror) std::cout<<"Mean  "<<gaussian_fit->GetParameter(1)<<std::endl;
	    if(berror) std::cout<<"Mean by GetMean "<<gaussian->GetMean()<<std::endl;
	    if(berror) std::cout<<"RMS  "<<gaussian_fit->GetParameter(2)<<std::endl;

	    result_mean->SetBinContent(p,gaussian_fit->GetParameter(1));
	    result_mean->SetBinError(p,gaussian_fit->GetParError(1));

	    result_rms->SetBinContent(p,gaussian_fit->GetParameter(2));
	    result_rms->SetBinError(p,gaussian_fit->GetParError(2));
	  }//over all slices

	
	  TCanvas *result_mean_c= new TCanvas("result_mean_c","Result Mean",10,10,1000,1000);
	  result_mean_c->Clear();
	  result_mean_c->cd();
	  gPad->SetTickx();
	  gPad->SetTicky();
	  result_mean->SetMaximum(1);
	  result_mean->SetMinimum(-1);
	  if(ak_ranges[i]=="topjet" &&scale_ranges[l]=="TopJetMassScale_GEV_" ){
	    result_mean->SetMaximum(20);
	    result_mean->SetMinimum(-20);
	  }
	  result_mean->GetXaxis()->SetTitle("NVP");
	  if(ak_ranges[i]=="jet")	{
	    result_mean->GetYaxis()->SetTitle("Mean ((P_{T,reco} - P_{T,gen} )/P_{T,gen} )");
	    //  result_mean->SetTitle("AK4 Jet P_{T} Scale");
	  }
	  if(ak_ranges[i]=="topjet"){
	    result_mean->GetYaxis()->SetTitle("Mean ((M_{T,reco} - M_{T,gen} )/M_{T,gen} )");
	    if(scale_ranges[l]=="TopJetMassScale_GEV_") result_mean->GetYaxis()->SetTitle("Mean (M_{T,reco} - M_{T,gen} ) [GeV]");
	    //  result_mean->SetTitle("AK8 Jet Mass Scale");
	  }
	  result_mean->GetYaxis()->SetTitleOffset(1.4);
	  result_mean->Draw("E1");
	  //labels like pt of the jets, eta range
	  TPaveText *pt = new TPaveText(.20,.12,.40,.18,"nbNDC");
	  if(pt_ranges[k]=="30to40")	pt->AddText("30GeV<P_{T}<40GeV");
	  if(pt_ranges[k]=="100to150")	pt->AddText("100GeV<P_{T}<150GeV");
	  pt->SetFillColor(0);
	  pt->SetTextSize(0.04);
	  pt->Draw();
	  TPaveText *eta = new TPaveText(.75,.12,.85,.18,"nbNDC");
	  if(eta_ranges[j]=="Eta0to1p3")	eta->AddText("0<#eta<1.3");
	  if(eta_ranges[j]=="Eta1p3to2")	eta->AddText("1.3<#eta<2");
	  if(eta_ranges[j]=="Eta2to2p5")	eta->AddText("2<#eta<2.5");
	  if(eta_ranges[j]=="Eta2p5to3")	eta->AddText("2.5<#eta<3");
	  if(eta_ranges[j]=="Eta3to10")	eta->AddText("3<#eta<10");
	  eta->SetFillColor(0);
	  eta->SetTextSize(0.04);
	  eta->Draw();
	  //Legend
	  TLegend *leg = new TLegend(0.15,0.88,0.5,0.78, NULL,"brNDC");
	  if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet P_{T} Scale");
	  if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Jet Mass Scale");
	  leg->SetBorderSize(0);	
	  leg->SetFillStyle(0);
	  leg->AddEntry(result_mean,"Puppi","lpe");
	  //	leg->AddEntry("CHS","lpe");
	  leg->Draw();
	  //save
	  result_mean_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+scale_ranges[l]+pt_ranges[k]+"_"+eta_ranges[j]+"_result_mean.eps");
	  result_mean_c->Destructor();

	  TCanvas *result_rms_c= new TCanvas("result_rms_c","Result Rms",10,10,1000,1000);
	  result_rms_c->Clear();
	  result_rms_c->cd();
	  gPad->SetTickx();
	  gPad->SetTicky();
	  result_rms->SetMaximum(0.6);
	  result_rms->SetMinimum(0);
	  if(ak_ranges[i]=="topjet"&&scale_ranges[l]=="TopJetMassScale_GEV_")result_rms->SetMaximum(20);
	  if(ak_ranges[i]=="topjet"&&scale_ranges[l]=="TopJetMassScale_")result_rms->SetMaximum(2);
	  result_rms->GetXaxis()->SetTitle("NVP");
	  if(ak_ranges[i]=="jet"){
	    result_rms->GetYaxis()->SetTitle("RMS ((P_{T,reco} - P_{T,gen} )/P_{T,gen} )");
	    // result_rms->SetTitle("AK4 Jet P_{T} Resolution");
	  }
	  if(ak_ranges[i]=="topjet"){
	    result_rms->GetYaxis()->SetTitle("RMS ((M_{T,reco} - M_{T,gen} )/M_{T,gen} )");
	    if(scale_ranges[l]=="TopJetMassScale_GEV_")result_rms->GetYaxis()->SetTitle("RMS (M_{T,reco} - M_{T,gen} )[GEV]");
	    //  result_rms->SetTitle("AK8 Jet Mass Resolution");
	  }
	  result_rms->GetYaxis()->SetTitleOffset(1.4);
	  result_rms->Draw("E1");
	  rms ->SetMarkerColor(kRed);
	  rms ->SetLineColor(kRed);
	  rms->Draw("same E1");
	  //labels like pt of the jets, eta range
	  pt->Draw();
	  eta->Draw();
	  leg = new TLegend(0.15,0.88,0.6,0.78, NULL,"brNDC");
	  leg->SetBorderSize(0);	
	  leg->SetFillStyle(0);
	  leg->AddEntry(result_rms,"Puppi 1#sigma","lpe");
	  leg->AddEntry(rms,"Puppi RMS","lpe");
	  //	leg->AddEntry("CHS","lpe");
	  if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet P_{T} Resolutuion");
	  if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Jet Mass Resolution");
	  leg->Draw();
	  result_rms_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+scale_ranges[l]+pt_ranges[k]+"_"+eta_ranges[j]+"_result_rms.eps");

	  result_rms_c->Destructor();

	  Result_f->cd();
	  result_mean->Write();
	  result_rms->Write();

	}//eta_ranges
      }//pt_ranges
    }//scale_ranges
  }//ak_ranges
  ////////////////////////////////////////////     finished: Jet Pt scale and TopJet mass scale ///////////////////////////////////////////////////
  }

  // ////////////////////////////////////////////     starting: Purity and Efficiency  ///////////////////////////////////////////////////

  if(false){
  for(int i=0;i<ak_ranges.size();i++){
    for(int j=0;j<eff_ranges.size();j++){
      for(int k=0;k<var_ranges.size();k++){
      	hist_name = ak_ranges[i];
	if(ak_ranges[i]=="jet")	hist_name+="_pt_25/Jet";
	if(ak_ranges[i]=="topjet")	hist_name+="_pt_25/TopJet";
  	hist_name+=eff_ranges[j];
  	if(ak_ranges[i]=="topjet") hist_name+="Top";
  	hist_name+=var_ranges[k];

  	if(berror) std::cout<<"Purity and Efficiency::read in Hists "<<hist_name<<std::endl;
  	//read in Histogramms
  	TH1F* hist = (TH1F*)QCD_f->Get(hist_name);
  	if(ak_ranges[i]=="jet") hist_name+="_matchedjet";
  	if(ak_ranges[i]=="topjet") hist_name+="_matchedTopJet";
  	TH1F* hist_matched = (TH1F*)QCD_f->Get(hist_name);

	TCanvas *hist_c= new TCanvas("hist_c","hist",10,10,1000,1000);
 	hist_c->Clear();
  	hist_c->cd();
	hist->Draw();
  	hist_c->Print(output_folder+folder+"/input/"+ak_ranges[i]+"_"+eff_ranges[j]+"_"+var_ranges[k]+".eps");
	TCanvas *hist_matched_c= new TCanvas("hist_matched_c","hist_matched",10,10,1000,1000);
 	hist_matched_c->Clear();
  	hist_matched_c->cd();
	hist_matched->Draw();

  	//divide both hists
	TGraphAsymmErrors* eff = new TGraphAsymmErrors( hist_matched, hist, "cl=0.683 b(1,1) mode" );
	
	
  	TCanvas *result_eff_c= new TCanvas("result_eff_c","Result Efficiency",10,10,1000,1000);
  	result_eff_c->Clear();
  	result_eff_c->cd();
  	eff->SetMaximum(1.01);
	eff->SetTitle("");
      	//X Axis, Min, Max
	if(var_ranges[k]=="JetPt"){
	  eff->SetMinimum(0.9);
	  if(eff_ranges[j]=="Efficiency_Gen")eff->GetXaxis()->SetTitle("GenJetPT");
	  if(eff_ranges[j]=="Purity_Reco")  eff->GetXaxis()->SetTitle("RecoJetPT");
	}
	if(var_ranges[k]=="JetEta"){
	  eff->SetMinimum(0.8);
	  eff->GetXaxis()->SetRangeUser(-5,5);
	  if(eff_ranges[j]=="Efficiency_Gen")eff->GetXaxis()->SetTitle("GenJetEta");
	  if(eff_ranges[j]=="Purity_Reco"){
	    eff->GetXaxis()->SetTitle("RecoJetEta");
	    eff->SetMinimum(0.6);
	  }
	}
	//Y Axis
	if(eff_ranges[j]=="Efficiency_Gen")eff->GetYaxis()->SetTitle("Efficiency");
	if(eff_ranges[j]=="Purity_Reco")eff->GetYaxis()->SetTitle("Purity");
	eff->GetYaxis()->SetTitleOffset(1.4);
	//Draw()
	eff->Draw("AP");
	//Legend
	TLegend *leg = new TLegend(0.35,0.23,0.7,0.13, NULL,"brNDC");
	if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet Efficiency");
	if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Efficiency");
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	leg->AddEntry(eff,"Puppi","lpe");
	//	leg->AddEntry("CHS","lpe");
	leg->Draw();

	//save
  	result_eff_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+eff_ranges[j]+"_"+var_ranges[k]+".eps");
	result_eff_c->Destructor();
	hist_c->Destructor();
	hist_matched_c->Destructor();
      }//var_ranges
    }//eff or Purity
  }//ak_ranges
  	
  }
 



  // ////////////////////////////////////////////     general hist like MET, JetPT ///////////////////////////////////////////////////
  //AK4 Jet PT
  TH1F* hist_jetrecopt = (TH1F*)QCD_f->Get("jet_input/JetRecoPT");
  TH1F* hist_jetgenpt = (TH1F*)QCD_f->Get("jet_input/JetGenPT");
	
  TCanvas *c12 = new TCanvas("c12","Jet P_{T}",10,10,1000,1000);
  c12->Clear();
  c12->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  hist_jetgenpt->GetXaxis()->SetTitle("P_{T}");
  hist_jetgenpt->SetMinimum(10000);
  hist_jetgenpt->Draw("E1");
  gPad->SetLogy();
  hist_jetgenpt ->SetLineColor(kRed);
  hist_jetrecopt ->Draw("same E1");

 

  TLegend *leg_AK4 = new TLegend(0.65,0.83,0.9,0.73, NULL,"brNDC");
  leg_AK4->SetHeader("AK4 Jet P_{T}");
  leg_AK4->SetBorderSize(0);
  leg_AK4->SetFillStyle(0);
  leg_AK4->AddEntry(hist_jetgenpt,"Gen P_{T}","lpe");
  leg_AK4->AddEntry(hist_jetrecopt,"Reco P_{T}","lpe");
  leg_AK4->Draw();
  c12->Print(output_folder+folder+"/general/AK4_pt.eps");
  c12->Destructor();

  //AK8 Jet pt
  TH1F* hist_topjetrecopt = (TH1F*)QCD_f->Get("topjet_input/TopJetRecoPT");
  TH1F* hist_topjetgenpt = (TH1F*)QCD_f->Get("topjet_input/TopJetGenPT");
	
  TCanvas *c13 = new TCanvas("c13","AK8 Jet P_{T}",10,10,1000,1000);
  c13->Clear();
  c13->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  hist_topjetrecopt->Draw("E1");
  hist_topjetgenpt->SetLineColor(kRed);
  hist_topjetgenpt->SetMarkerColor(kRed);
  hist_topjetgenpt->Draw("same E1");

  TLegend *leg_AK8 = new TLegend(0.65,0.83,0.9,0.73, NULL,"brNDC");
  leg_AK8 ->SetHeader("AK8 Jet P_{T}");
  leg_AK8 ->SetBorderSize(0);
  leg_AK8 ->SetFillStyle(0);
  leg_AK8 ->AddEntry(hist_topjetgenpt,"Gen P_{T}","lpe");
  leg_AK8 ->AddEntry(hist_topjetrecopt,"Reco P_{T}","lpe");
  leg_AK8 ->Draw();
  c13->Print(output_folder+folder+"/general/AK8_pt.eps");
  c13->Destructor();

  //MET
  TH1F* hist_MET = (TH1F*)QCD_f->Get("jet_input/MET");
	
  TCanvas *c14 = new TCanvas("c14","uncorrected MET",10,10,1000,1000);
  c14->Clear();
  c14->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  hist_MET->Draw("E1");
  TLegend *leg_MET = new TLegend(0.65,0.83,0.9,0.73, NULL,"brNDC");
  leg_MET->AddEntry(hist_MET,"uncorrected MET","lpe");
  leg_MET->SetBorderSize(0);
  leg_MET->SetFillStyle(0);
  leg_MET->Draw();
  c14->Print(output_folder+folder+"/general/MET.eps");
  c14->Destructor();

}
