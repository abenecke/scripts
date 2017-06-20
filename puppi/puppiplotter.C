#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"

using namespace std;


bool berror=false; 
bool bCHS=false;
TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/";
TString output_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/pictures/";
TString folder="puppi_92";

#include "function.h"

void puppiplotter()
{
  //general
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);
  // if(berror)gROOT->SetBatch(kFALSE);
  bool bQCD=true;
  bool bGamma=false;
  bool bDY=false;
  bool bscale=true;
  bool beff=true;

 

  if(bQCD){
    //read in all Files: QCD
    TFile *QCD_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_test/uhh2.AnalysisModuleRunner.MC.QCD_8_0.root", "READ");
    TString legend_name1 = "Puppi 80";
    // TFile *QCD_CHS_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_usedzcutfalse/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
    // TString legend_name2 = "Puppi 80 UseDZCut=False";
    // TFile *QCD_CHS_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_test/uhh2.AnalysisModuleRunner.MC.QCD_puppicentral.root", "READ");
    // TString legend_name2 = "Puppi 80 Central";
    // TFile *QCD_CHS_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_test/uhh2.AnalysisModuleRunner.MC.QCD_9_1.root", "READ");
    // TString legend_name2 = "Puppi 91";
    TFile *QCD_CHS_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_test/uhh2.AnalysisModuleRunner.MC.QCD_9_2.root", "READ");
    TString legend_name2 = "Puppi 92";
    // TFile *QCD_CHS_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_test/uhh2.AnalysisModuleRunner.MC.MC_QCD_CHS.root", "READ");
    // TString legend_name2 = "CHS 80";
    std::vector<TString> legend_names = {legend_name1,legend_name2};
    //   TFile *QCD_CHS_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_QCD_CHS.root", "READ");
    //  TFile *QCD_CHS_f = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/puppi_test/uhh2.AnalysisModuleRunner.MC.MC_QCD_CHS.root", "READ");
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

    //   std::vector<TString>  eta_ranges={"Eta0to1p3","Eta2p5to3"};
    // std::vector<TString> pt_ranges={"30to40"};
    // std::vector<TString> ak_ranges={"jet"};
    // std::vector<TString> eff_ranges={"Efficiency_Gen"};
    // std::vector<TString> var_ranges={"JetEta"};
    // std::vector<TString> scale_ranges={"TopJetMassScale_"};

    if(bscale){
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

	      std::vector<TString> ranges = {ak_ranges[i], pt_ranges[k],scale_ranges[l],eta_ranges[j]};

	      if(berror) std::cout<<"JetPTScale::read in Hists "<<hist_name<<std::endl;
	      //read in Histogramms
	      TH2F* hist = (TH2F*)QCD_f->Get(hist_name);
	      TH2F* hist_CHS = (TH2F*)QCD_CHS_f->Get(hist_name);
	      //jec correction applied hist with CHS
	      TString  hist_name_wjec = "uncorrected_";
	      hist_name_wjec+= hist_name;  
	      if(berror) std::cout<<"JetPTScale::read in Hists "<<hist_name_wjec<<std::endl;
	      TH2F* hist_CHS_wjec = (TH2F*)QCD_CHS_f->Get(hist_name_wjec);

	      if (berror) save_canvas("input_hist","input/","colz", hist_CHS_wjec, hist_CHS,ranges );
	     
	      if(berror) std::cout<<"JetPTScale::rebin Hists "<<hist_name<<std::endl;
	      //rebin hists as in presentation	  
	      Double_t bins_x[11]={0,5,10,15,20,25,30,35,40,60,100};
	      std::vector<TH2F*> rebinned_results =rebin(bins_x,hist,hist_CHS, hist_CHS_wjec );
	      TH2F* rebinned_hist = rebinned_results[0];
	      TH2F* rebinned_hist_CHS =rebinned_results[1];
	      TH2F* rebinned_hist_CHS_wjec =rebinned_results[2];

	      if (berror)save_canvas("rebinned_hist","rebinned/","colz", rebinned_hist_CHS_wjec, rebinned_hist_CHS,ranges );

	      std::vector<TH1F*> results = gaussianfit( bins_x,   ranges ,rebinned_hist );
	      TH1F *result_mean = results[0];
	      TH1F *result_rms = results[1];
	      TH1F *rms= results[2];

	     
	      std::vector<TH1F*> results_CHS = gaussianfit( bins_x,   ranges ,rebinned_hist_CHS );
	      TH1F *result_mean_CHS = results_CHS[0];
	      TH1F *result_rms_CHS = results_CHS[1];
	      TH1F *rms_CHS = results_CHS[2];

	      if(bCHS){
		std::vector<TH1F*> results_CHS_wjec = gaussianfit( bins_x,   ranges ,rebinned_hist_CHS_wjec, "_wjec" );
		TH1F *result_mean_CHS_wjec = results_CHS_wjec[0];
		TH1F *result_rms_CHS_wjec = results_CHS_wjec[1];
		TH1F *rms_CHS_wjec = results_CHS_wjec[2];

		////////////////////////////////////////////////////////////////////////////////////////  Save Result mean   //////////////////////////////////////////////////////////////////
		std::vector<TH1F*> mean_results = {result_mean,result_mean_CHS,result_mean_CHS_wjec};
		if(ak_ranges[i]=="jet")  save_result(1, -1,"NPV", "Mean ((P_{T,reco} - P_{T,gen} )/P_{T,gen} )",mean_results, ranges,legend_names,"mean");
		if(ak_ranges[i]=="topjet" &&scale_ranges[l]=="TopJetMassScale_GEV_" ) save_result(20, -40,"NPV", "Mean (M_{T,reco} - M_{T,gen} ) [GeV]",mean_results, ranges,legend_names,"mean");
		if(ak_ranges[i]=="topjet" &&!(scale_ranges[l]=="TopJetMassScale_GEV_")  ) save_result(20, -25,"NPV", "Mean ((M_{T,reco} - M_{T,gen} )/M_{T,gen} )", mean_results,   ranges,legend_names,"mean");
	     
		////////////////////////////////////////////////////////////////////////////////////////  Save Result rms   //////////////////////////////////////////////////////////////////
		std::vector<TH1F*> rms_results = {result_rms,result_rms_CHS,rms,rms_CHS,result_rms_CHS_wjec,rms_CHS_wjec};
		if(ak_ranges[i]=="jet")  save_result(0.6,0,"NPV", "Rms ((P_{T,reco} - P_{T,gen} )/P_{T,gen} )",rms_results, ranges,legend_names,"rms");
		if(ak_ranges[i]=="topjet" &&scale_ranges[l]=="TopJetMassScale_GEV_" ) save_result(20,0,"NPV", "Rms (M_{T,reco} - M_{T,gen} ) [GeV]", rms_results,  ranges,legend_names,"rms");
		if(ak_ranges[i]=="topjet"&&scale_ranges[l]=="TopJetMassScale_")save_result(2,0,"NPV", "Rms (M_{T,reco} - M_{T,gen} ) [GeV]", rms_results, ranges,legend_names,"rms");
	      }else{

	
		////////////////////////////////////////////////////////////////////////////////////////  Save Result mean   //////////////////////////////////////////////////////////////////
		std::vector<TH1F*> mean_results = {result_mean,result_mean_CHS};
		if(ak_ranges[i]=="jet")  save_result(1, -1,"NPV", "Mean ((P_{T,reco} - P_{T,gen} )/P_{T,gen} )",mean_results, ranges,legend_names,"mean");
		if(ak_ranges[i]=="topjet" &&scale_ranges[l]=="TopJetMassScale_GEV_" ) save_result(20, -40,"NPV", "Mean (M_{T,reco} - M_{T,gen} ) [GeV]",mean_results, ranges,legend_names,"mean");
		if(ak_ranges[i]=="topjet" &&!(scale_ranges[l]=="TopJetMassScale_GEV_")  ) save_result(25, -30,"NPV", "Mean ((M_{T,reco} - M_{T,gen} )/M_{T,gen} )", mean_results,   ranges,legend_names,"mean");
		std::cout<<"Hier"<<std::endl;
		////////////////////////////////////////////////////////////////////////////////////////  Save Result rms   //////////////////////////////////////////////////////////////////
		std::vector<TH1F*> rms_results = {result_rms,result_rms_CHS};
		if(ak_ranges[i]=="jet")  save_result(0.6,-0.1,"NPV", "Rms ((P_{T,reco} - P_{T,gen} )/P_{T,gen} )",rms_results, ranges,legend_names,"rms");
		if(ak_ranges[i]=="topjet" &&scale_ranges[l]=="TopJetMassScale_GEV_" ) save_result(20,0,"NPV", "Rms (M_{T,reco} - M_{T,gen} ) [GeV]", rms_results,  ranges,legend_names,"rms");
		if(eta_ranges[j]=="Eta0to1p3") if(ak_ranges[i]=="topjet"&&scale_ranges[l]=="TopJetMassScale_")save_result(20,-5,"NPV", "Rms (M_{T,reco} - M_{T,gen} ) [GeV]", rms_results, ranges,legend_names,"rms");
		if(!(eta_ranges[j]=="Eta0to1p3")) if(ak_ranges[i]=="topjet"&&scale_ranges[l]=="TopJetMassScale_")save_result(20,-5,"NPV", "Rms (M_{T,reco} - M_{T,gen} ) [GeV]", rms_results, ranges,legend_names,"rms");
	      }
	    }//eta_ranges
	  }//pt_ranges
	}//scale_ranges
      }//ak_ranges
      ////////////////////////////////////////////     finished: Jet Pt scale and TopJet mass scale ///////////////////////////////////////////////////
    }

    // ////////////////////////////////////////////     starting: Purity and Efficiency  ///////////////////////////////////////////////////

    if(beff){
      for(int i=0;i<ak_ranges.size();i++){
	for(int j=0;j<eff_ranges.size();j++){
	  for(int k=0;k<var_ranges.size();k++){
	    hist_name = ak_ranges[i];
	    if(ak_ranges[i]=="jet")	hist_name+="_pt_25/Jet";
	    if(ak_ranges[i]=="topjet")	hist_name+="_pt_25/TopJet";
	    hist_name+=eff_ranges[j];
	    if(ak_ranges[i]=="topjet") hist_name+="Top";
	    hist_name+=var_ranges[k];

	    std::vector<TString> ranges = {ak_ranges[i], eff_ranges[j],var_ranges[k],""};

	    if(berror) std::cout<<"Purity and Efficiency::read in Hists "<<hist_name<<std::endl;
	    //read in Histogramms
	    TH1F* hist = (TH1F*)QCD_f->Get(hist_name);
	    TH1F* hist_CHS = (TH1F*)QCD_CHS_f->Get(hist_name); 

	    TCanvas *c1= new TCanvas("c1","hist",10,10,1000,1000);
	    hist->Draw();
	    TCanvas *c2= new TCanvas("c2","hist CHS",10,10,1000,1000);
	    hist_CHS->Draw();

	    //jec correction applied hist with CHS
	    TString  hist_name_wjec = "uncorrected_";
	    hist_name_wjec+= hist_name;  
	    
	    if(ak_ranges[i]=="jet") hist_name+="_matchedjet";
	    if(ak_ranges[i]=="topjet") hist_name+="_matchedTopJet";
	    TH1F* hist_matched = (TH1F*)QCD_f->Get(hist_name);
	    TH1F* hist_CHS_matched = (TH1F*)QCD_CHS_f->Get(hist_name);
	    
	    //jec correction applied hist with CHS
	    if(ak_ranges[i]=="jet") hist_name_wjec+="_matchedjet";
	    if(ak_ranges[i]=="topjet") hist_name_wjec+="_matchedTopJet";
	    if(berror) std::cout<<"JetPTScale::read in Hists "<<hist_name_wjec<<std::endl;
	    TH1F* hist_CHS_wjec = (TH1F*)QCD_CHS_f->Get(hist_name_wjec);
	    TH1F* hist_CHS_wjec_matched = (TH1F*)QCD_CHS_f->Get(hist_name_wjec);


	    //    if (berror) save_canvas("input_hist","input/","colz", hist, hist_CHS,ranges );
	    //    if (berror) save_canvas("input_hist","input/matched_","colz", hist_matched, hist_CHS_matched,ranges );
	   
	  
	    //divide both hists
	    TGraphAsymmErrors* eff = new TGraphAsymmErrors( hist_matched, hist, "cl=0.683 b(1,1) mode" );
	    TGraphAsymmErrors* eff_CHS = new TGraphAsymmErrors( hist_CHS_matched, hist_CHS, "cl=0.683 b(1,1) mode" );
	    TGraphAsymmErrors* eff_CHS_wjec = new TGraphAsymmErrors( hist_CHS_wjec_matched, hist_CHS_wjec, "cl=0.683 b(1,1) mode" );
	
	
	    TCanvas *result_eff_c= new TCanvas("result_eff_c","Result Efficiency",10,10,1000,1000);
	    gPad->SetTickx();
	    gPad->SetTicky();
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
	      eff->SetMinimum(0.5);
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
	    eff_CHS->SetLineColor(kGreen);
	    eff_CHS->SetMarkerColor(kGreen);
	    eff_CHS->Draw("same P");
	    eff_CHS_wjec->SetLineColor(kRed);
	    eff_CHS_wjec->SetMarkerColor(kRed);
	    //  eff_CHS_wjec->Draw("same");
	    //Legend
	    TLegend *leg = new TLegend(0.35,0.33,0.7,0.13, NULL,"brNDC");
	    if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet Efficiency");
	    if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Efficiency");
	    leg->SetBorderSize(0);
	    leg->SetFillStyle(0);
	    leg->AddEntry(eff_CHS,legend_name2,"lpe");
	    //  leg->AddEntry(eff_CHS_wjec,"CHS w JEC","lpe");
	    leg->AddEntry(eff,legend_name1,"lpe");
	    leg->Draw();

	    //save
	    result_eff_c->Print(output_folder+folder+"/"+ak_ranges[i]+"_"+eff_ranges[j]+"_"+var_ranges[k]+".eps");
	    result_eff_c->Destructor();
	    //   hist_c->Destructor();
	    //  hist_matched_c->Destructor();
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
    TH1F* hist_CHS_MET = (TH1F*)QCD_CHS_f->Get("jet_input/MET");
    hist_MET->Scale(1/hist_MET->Integral());
    hist_CHS_MET->Scale(1/hist_CHS_MET->Integral());
    // std::cout<<"PUPPI "<< hist_MET->Integral()<<std::endl;	
    // std::cout<<"CHS "<< hist_CHS_MET->Integral()<<std::endl;

    TCanvas *c14 = new TCanvas("c14","uncorrected MET",10,10,1000,1000);
    c14->Clear();
    c14->cd();
    c14->SetLogy();
    gPad->SetTickx();
    gPad->SetTicky();
    hist_CHS_MET->SetLineColor(kGreen);
    hist_CHS_MET->SetMarkerColor(kGreen);
    hist_CHS_MET->Draw("E1");
    hist_MET->Draw("same E1");
    TLegend *leg_MET = new TLegend(0.65,0.83,0.9,0.73, NULL,"brNDC");
    leg_MET->AddEntry(hist_MET,legend_name1,"lpe");
    leg_MET->AddEntry(hist_CHS_MET,legend_name2,"lpe");
    leg_MET->SetBorderSize(0);
    leg_MET->SetFillStyle(0);
    leg_MET->Draw();
    c14->Print(output_folder+folder+"/general/MET.eps");
    c14->Destructor();


  }//bQCD
  if(bGamma){  
    TFile *Gamma_f = new TFile(directory+folder+"/GJets/uhh2.AnalysisModuleRunner.MC.MC_GJets_HT_40To100.root", "READ");
    TFile *Gamma_CHS_f = new TFile(directory+folder+"/GJets/CHS/uhh2.AnalysisModuleRunner.MC.MC_GJets_HT_40To100_CHS.root", "READ");
    //MET
    TH1F* hist_MET = (TH1F*)Gamma_f->Get("jet_input/MET");
    TH1F* hist_CHS_MET = (TH1F*)Gamma_CHS_f->Get("jet_input/MET");
    // //jec correction applied hist with CHS
    // TH1F* hist_CHS_wjec_MET = (TH1F*)Gamma_CHS_f->Get("uncorrected_jet_input/MET");
	
    TCanvas *c14 = new TCanvas("c14","uncorrected MET",10,10,1000,1000);
    c14->Clear();
    c14->cd();
    gPad->SetTickx();
    gPad->SetTicky();
    gPad->SetLogy();
    hist_MET->Draw("E1");
    hist_CHS_MET->SetLineColor(kGreen);
    hist_CHS_MET->SetMarkerColor(kGreen);
    hist_CHS_MET->Draw("same E1");
    // hist_CHS_wjec_MET->SetLineColor(kRed);
    // hist_CHS_wjec_MET->SetMarkerColor(kRed);
    // hist_CHS_wjec_MET->Draw("same E1");
    TLegend *leg_MET = new TLegend(0.65,0.83,0.9,0.73, NULL,"brNDC");
    leg_MET->AddEntry(hist_MET,"uncorrected MET (Puppi)","lpe");
    leg_MET->AddEntry(hist_CHS_MET,"uncorrected MET (CHS)","lpe");
    //  leg_MET->AddEntry(hist_CHS_wjec_MET,"MET (CHS)","lpe");
    leg_MET->SetBorderSize(0);
    leg_MET->SetFillStyle(0);
    leg_MET->Draw();
    c14->Print(output_folder+folder+"/gamma/MET.eps");
    c14->Destructor();
  }//bGamma

  if(bDY){
    
    std::vector<TString> channel_ranges={"ele","muon"};
    std::vector<TString> sel_ranges={"output","Zptk50","Zptg50"};
    TFile *DY_f,*DY_CHS_f;

    if(berror)channel_ranges={"ele"};

    //over all ranges
    for(int i=0;i<channel_ranges.size();i++){
      //choose the right file 
      if(channel_ranges[i]=="muon"){
	DY_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_DY_muon.root", "READ");
	DY_CHS_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_DY_muon_CHS.root", "READ");
      }
      else if(channel_ranges[i]=="ele"){
	DY_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_DY_elec.root", "READ");
	DY_CHS_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.MC_DY_elec_CHS.root", "READ");
	if(berror) std::cout<<"Histogramms read in"<<std::endl;
      }else std::cout<<"Channel not defined"<<std::endl;

      if(berror) std::cout<<"DY::Met"<<std::endl;
      /////////////////////////////////////////////////////                       MET                  ////////////////////////////////////////////////////////////////
      TH1F* hist_MET = (TH1F*)DY_f->Get("uncorrected_jet_input/MET");
      TH1F* hist_CHS_MET = (TH1F*)DY_CHS_f->Get("uncorrected_jet_input/MET");
     
      TCanvas *c14 = new TCanvas("c14","uncorrected MET",10,10,1000,1000);
      c14->Clear();
      c14->cd();
      gPad->SetTickx();
      gPad->SetTicky();

      hist_MET->Draw("E1");
      hist_CHS_MET->SetLineColor(kGreen);
      hist_CHS_MET->SetMarkerColor(kGreen);
      hist_CHS_MET->Draw("same E1");

      TPaveText *pt = new TPaveText(.60,.32,.80,.38,"nbNDC");
      if(channel_ranges[i] == "ele") pt->AddText("electron channel");
      if(channel_ranges[i] == "muon") pt->AddText("muon channel");
      pt->SetFillColor(0);
      pt->SetTextSize(0.04);
      pt->Draw();

      TLegend *leg_MET = new TLegend(0.65,0.83,0.9,0.73, NULL,"brNDC");
      leg_MET->AddEntry(hist_MET,"uncorrected MET (Puppi)","lpe");
      leg_MET->AddEntry(hist_CHS_MET,"uncorrected MET (CHS)","lpe");
      leg_MET->SetBorderSize(0);
      leg_MET->SetFillStyle(0);
      leg_MET->Draw();
      c14->Print(output_folder+folder+"/DY/"+channel_ranges[i]+"_MET.eps");
      gPad->SetLogy();
      c14->Print(output_folder+folder+"/DY/"+channel_ranges[i]+"_log_MET.eps");
      c14->Destructor();

      if(berror)std::cout<<"DY::Response recoil"<<std::endl;
      /////////////////////////////////////////////////////                       Response of recoil in DY                  ////////////////////////////////////////////////////////////////
      if(true){    
	for(int j=0;j<sel_ranges.size();j++){
	//read in Histogramms
	TString hist_name="DY_";
	hist_name+= sel_ranges[j];
	hist_name+="/";
	if(sel_ranges[j]=="output")hist_name+="response_ZP";
	else hist_name+="response_NPV";
	
	std::vector<TString> ranges = {channel_ranges[i], sel_ranges[j],"",""};

	//input histogramms
	TH2F* hist = (TH2F*)DY_f->Get(hist_name);
	TH2F* hist_CHS = (TH2F*)DY_CHS_f->Get(hist_name);

	if (berror) save_canvas("input_hist","input/","colz", hist, hist_CHS,ranges );

	TH2F *rebinned_hist, *rebinned_hist_CHS;
	TH1F *result_mean , *result_mean_CHS ;
	if(berror) std::cout<<"DY::rebin Hists "<<hist_name<<std::endl;
	if(sel_ranges[j]=="output" ){
	  Double_t bins_x[21]={0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
	  rebinned_hist= rebin(bins_x,hist,rebinned_hist,channel_ranges[i], sel_ranges[j],-1,1);
	  rebinned_hist_CHS= rebin(bins_x,hist_CHS,rebinned_hist_CHS,channel_ranges[i], sel_ranges[j],-1,1);
	  result_mean = new TH1F("result_mean","",10,bins_x);
	  result_mean_CHS = new TH1F("result_mean_CHS","",10,bins_x);
	}else{
	  Double_t bins_x[26]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50};
	  rebinned_hist= rebin(bins_x,hist,rebinned_hist,channel_ranges[i], sel_ranges[j],-1,1);
	  rebinned_hist_CHS= rebin(bins_x,hist_CHS,rebinned_hist_CHS,channel_ranges[i], sel_ranges[j],-1,1);
	  result_mean = new TH1F("result_mean","",10,bins_x);
	  result_mean_CHS = new TH1F("result_mean_CHS","",10,bins_x);
	}

	result_mean= gaussianfit(rebinned_hist,channel_ranges[i],sel_ranges[j],result_mean);
	result_mean_CHS= gaussianfit(rebinned_hist_CHS,channel_ranges[i],sel_ranges[j],result_mean_CHS );

	////////////////////////////////////////////////////////////////////////////////////////   Result Canvas   //////////////////////////////////////////////////////////////////
	
	TCanvas *result_mean_c= new TCanvas("result_mean_c","Result Mean",10,10,1000,1000);
	result_mean_c->Clear();
	result_mean_c->cd();
	gPad->SetTickx();
	gPad->SetTicky();
	result_mean->SetMaximum(1.5);
	result_mean->SetMinimum(-1);
	result_mean->GetXaxis()->SetTitle("NVP");
	result_mean->GetYaxis()->SetTitle("Mean of (-u_{||}/Z_{pt})");
	// result_mean->GetYaxis()->SetTitleOffset(1.1);
	result_mean->Draw("E1");
	result_mean_CHS->SetMarkerColor(kGreen);
	result_mean_CHS->SetLineColor(kGreen);
	result_mean_CHS->Draw("same E1");

	//labels like pt of the jets, eta range
	TPaveText *pt = new TPaveText(.20,.12,.40,.18,"nbNDC");

	if(sel_ranges[j]=="Zptk50")	pt->AddText("P_{T}<50GeV");
	if(sel_ranges[j]=="Zptg50")	pt->AddText("50GeV<P_{T}");

	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->Draw();
	TPaveText *eta = new TPaveText(.75,.12,.85,.18,"nbNDC");
	// if(eta_ranges[j]=="Eta0to1p3")	eta->AddText("0<#eta<1.3");
	// if(eta_ranges[j]=="Eta1p3to2")	eta->AddText("1.3<#eta<2");
	// if(eta_ranges[j]=="Eta2to2p5")	eta->AddText("2<#eta<2.5");
	// if(eta_ranges[j]=="Eta2p5to3")	eta->AddText("2.5<#eta<3");
	// if(eta_ranges[j]=="Eta3to10")	eta->AddText("3<#eta<10");
	eta->SetFillColor(0);
	eta->SetTextSize(0.04);
	eta->Draw();

	//Legend
	TLegend *leg = new TLegend(0.55,0.48,0.8,0.28, NULL,"brNDC");
	// if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet P_{T} Scale");
	// if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Jet Mass Scale");
	leg->SetBorderSize(0);	
	leg->SetFillStyle(0);
	leg->AddEntry(result_mean_CHS,"CHS","lpe");
	leg->AddEntry(result_mean,"Puppi","lpe");
	leg->Draw();

	//save
	result_mean_c->Print(output_folder+folder+"/"+channel_ranges[i]+"_"+sel_ranges[j]+"_result_mean.eps");
	result_mean_c->Destructor();

      }//sel_ranges j
      }
     
      if(false){
      ////////////////            read in Histogramms denominator        //////////////////////////////////////////////////////
      TString  hist_name = "DY_output/response_ZP";
      if(berror) std::cout<<"DY::Response read in Hists "<<hist_name<<std::endl;
      TH2F* hist = (TH2F*)DY_f->Get(hist_name);
      TH2F* hist_CHS = (TH2F*)DY_CHS_f->Get(hist_name);
      //rebin hists
      TH2F *rebinned_hist, *rebinned_hist_CHS;
      Double_t bins_x[21]={0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
      
      rebinned_hist= rebin(bins_x,hist,rebinned_hist,channel_ranges[i], "",-1,1);
      rebinned_hist_CHS= rebin(bins_x,hist_CHS,rebinned_hist_CHS,channel_ranges[i], "",-1,1);
      //gaussian fit
      TH1F *result_mean , *result_mean_CHS ;
      result_mean = new TH1F("result_mean","",20,bins_x);
      result_mean_CHS = new TH1F("result_mean_CHS","",20,bins_x);
     
      result_mean= gaussianfit(rebinned_hist,channel_ranges[i],"",result_mean );
      result_mean_CHS= gaussianfit(rebinned_hist_CHS,channel_ranges[i],"",result_mean_CHS );
      // TCanvas *test= new TCanvas("test","Result Efficiency",10,10,1000,1000);
      // test->Clear();
      // test->cd();
      // result_mean->Draw();
      // test->Print("test.eps");

      // // ////////////////////             read in Histogramms nominator       /////////////////////////////////////////////////////////////

      if(berror) std::cout<<" "<<hist_name<<std::endl;
      hist_name="DY_output/rms_ZP";
      if(berror) std::cout<<"DY::Response read in Hists "<<hist_name<<std::endl;
      TH2F* hist_matched = (TH2F*)DY_f->Get(hist_name);
      TH2F* hist_CHS_matched = (TH2F*)DY_CHS_f->Get(hist_name);
     
      //  Double_t bins_x2[26]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50};
      //rebin hists
      TH2F *rebinned_hist_matched, *rebinned_hist_matched_CHS;
      rebinned_hist_matched= rebin(bins_x,hist_matched ,rebinned_hist_matched,channel_ranges[i],"",-100,100);
      //  rebinned_hist_matched_CHS= rebin(bins_x,hist_CHS_matched ,rebinned_hist_matched_CHS,channel_ranges[i], "");
      //gaussian fit
      TH1F *result_matched_rms , *result_matched_rms_CHS ;
       result_matched_rms = new TH1F("result_matched_rms","",20,bins_x);
      //  result_matched_rms_CHS = new TH1F("result_matched_rms_CHS","",20,bins_x);
      result_matched_rms= gaussianfit(rebinned_hist_matched,channel_ranges[i],"",result_matched_rms,true );
      //  result_matched_rms_CHS= gaussianfit(rebinned_hist_matched_CHS,channel_ranges[i],"",result_matched_rms_CHS,true );
 
            
      //  divide both hists
       TGraphAsymmErrors* eff = new TGraphAsymmErrors(result_matched_rms , result_mean, "pois" );
      //   TGraphAsymmErrors* eff_CHS = new TGraphAsymmErrors( result_matched_rms_CHS,result_mean_CHS , "cl=0.683 b(1,1) mode" );
      
      
      TCanvas *result_eff_c= new TCanvas("result_eff_c","Result Efficiency",10,10,1000,1000);
      result_eff_c->Clear();
      result_eff_c->cd();
      // eff->SetMaximum(1.01);
      // eff->SetTitle("");
      // //X Axis, Min, Max
      // if(var_ranges[k]=="JetPt"){
      // 	eff->SetMinimum(0.9);
      // 	if(eff_ranges[j]=="Efficiency_Gen")eff->GetXaxis()->SetTitle("GenJetPT");
      // 	if(eff_ranges[j]=="Purity_Reco")  eff->GetXaxis()->SetTitle("RecoJetPT");
      // }
      // if(var_ranges[k]=="JetEta"){
      // 	eff->SetMinimum(0.8);
      // 	eff->GetXaxis()->SetRangeUser(-5,5);
      // 	if(eff_ranges[j]=="Efficiency_Gen")eff->GetXaxis()->SetTitle("GenJetEta");
      // 	if(eff_ranges[j]=="Purity_Reco"){
      // 	  eff->GetXaxis()->SetTitle("RecoJetEta");
      // 	  eff->SetMinimum(0.6);
      // 	}
      // }
      // //Y Axis
      // if(eff_ranges[j]=="Efficiency_Gen")eff->GetYaxis()->SetTitle("Efficiency");
      // if(eff_ranges[j]=="Purity_Reco")eff->GetYaxis()->SetTitle("Purity");
      // eff->GetYaxis()->SetTitleOffset(1.4);
      //Draw()
      eff->Draw("AP");
      // eff_CHS->SetLineColor(kGreen);
      // eff_CHS->SetMarkerColor(kGreen);
      // eff_CHS->Draw("same");
      // //Legend
      // TLegend *leg = new TLegend(0.35,0.23,0.7,0.13, NULL,"brNDC");
      // if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet Efficiency");
      // if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Efficiency");
      // leg->SetBorderSize(0);
      // leg->SetFillStyle(0);
      // leg->AddEntry(eff_CHS,"CHS","lpe");
      // leg->AddEntry(eff,"Puppi","lpe");
      // leg->Draw();
      
      //save
      result_eff_c->Print(output_folder+folder+"/rms_upar.eps");
      result_eff_c->Destructor();
      // hist_c->Destructor();
      // hist_matched_c->Destructor();
      
      ////////////////////////   uper  /////////////////////////
     
      hist_name="DY_output/rms_uper_ZP";
      if(berror) std::cout<<"DY::Response read in Hists "<<hist_name<<std::endl;
      hist_matched = (TH2F*)DY_f->Get(hist_name);
      hist_CHS_matched = (TH2F*)DY_CHS_f->Get(hist_name);
     
      //rebin hists
      rebinned_hist_matched= rebin(bins_x,hist_matched ,rebinned_hist_matched,channel_ranges[i],"",-100,100);
      //  rebinned_hist_matched_CHS= rebin(bins_x,hist_CHS_matched ,rebinned_hist_matched_CHS,channel_ranges[i], "");
      //gaussian fit
       result_matched_rms = new TH1F("result_matched_rms","",20,bins_x);
      //  result_matched_rms_CHS = new TH1F("result_matched_rms_CHS","",20,bins_x);
      result_matched_rms= gaussianfit(rebinned_hist_matched,channel_ranges[i],"",result_matched_rms,true );
      //  result_matched_rms_CHS= gaussianfit(rebinned_hist_matched_CHS,channel_ranges[i],"",result_matched_rms_CHS,true );

      // TCanvas *test2= new TCanvas("test2","Result Efficiency2",10,10,1000,1000);
      // test2->Clear();
      // test2->cd();
      // result_matched_rms->Draw();
      // // hist_matched->Draw("colz");
      // // rebinned_hist_matched->Draw("colz");
      // test2->Print("test2.eps");

      //  divide both hists
      eff = new TGraphAsymmErrors(result_matched_rms , result_mean, "pois" );
      //   TGraphAsymmErrors* eff_CHS = new TGraphAsymmErrors( result_matched_rms_CHS,result_mean_CHS , "cl=0.683 b(1,1) mode" );
      
      
      result_eff_c= new TCanvas("result_eff_c","Result Efficiency",10,10,1000,1000);
      result_eff_c->Clear();
      result_eff_c->cd();
      // eff->SetMaximum(1.01);
      // eff->SetTitle("");
      // //X Axis, Min, Max
      // if(var_ranges[k]=="JetPt"){
      // 	eff->SetMinimum(0.9);
      // 	if(eff_ranges[j]=="Efficiency_Gen")eff->GetXaxis()->SetTitle("GenJetPT");
      // 	if(eff_ranges[j]=="Purity_Reco")  eff->GetXaxis()->SetTitle("RecoJetPT");
      // }
      // if(var_ranges[k]=="JetEta"){
      // 	eff->SetMinimum(0.8);
      // 	eff->GetXaxis()->SetRangeUser(-5,5);
      // 	if(eff_ranges[j]=="Efficiency_Gen")eff->GetXaxis()->SetTitle("GenJetEta");
      // 	if(eff_ranges[j]=="Purity_Reco"){
      // 	  eff->GetXaxis()->SetTitle("RecoJetEta");
      // 	  eff->SetMinimum(0.6);
      // 	}
      // }
      // //Y Axis
      // if(eff_ranges[j]=="Efficiency_Gen")eff->GetYaxis()->SetTitle("Efficiency");
      // if(eff_ranges[j]=="Purity_Reco")eff->GetYaxis()->SetTitle("Purity");
      // eff->GetYaxis()->SetTitleOffset(1.4);
      //Draw()
      eff->Draw("AP");
      // eff_CHS->SetLineColor(kGreen);
      // eff_CHS->SetMarkerColor(kGreen);
      // eff_CHS->Draw("same");
      // //Legend
      // TLegend *leg = new TLegend(0.35,0.23,0.7,0.13, NULL,"brNDC");
      // if(ak_ranges[i]=="jet")	leg->SetHeader("AK4 Jet Efficiency");
      // if(ak_ranges[i]=="topjet")	leg->SetHeader("AK8 Efficiency");
      // leg->SetBorderSize(0);
      // leg->SetFillStyle(0);
      // leg->AddEntry(eff_CHS,"CHS","lpe");
      // leg->AddEntry(eff,"Puppi","lpe");
      // leg->Draw();
      
      //save
      result_eff_c->Print(output_folder+folder+"/rms_uper.eps");
      result_eff_c->Destructor();

      ////////////////////////   uper  /////////////////////////
     
      hist_name="DY_output/rms_uper_NPV";
      if(berror) std::cout<<"DY::Response read in Hists "<<hist_name<<std::endl;
      hist_matched = (TH2F*)DY_f->Get(hist_name);
      hist_CHS_matched = (TH2F*)DY_CHS_f->Get(hist_name);
     
      //rebin hists
      rebinned_hist_matched= rebin(bins_x,hist_matched ,rebinned_hist_matched,channel_ranges[i],"",-100,100);
      //  rebinned_hist_matched_CHS= rebin(bins_x,hist_CHS_matched ,rebinned_hist_matched_CHS,channel_ranges[i], "");
      //gaussian fit
       result_matched_rms = new TH1F("result_matched_rms","",20,bins_x);
      //  result_matched_rms_CHS = new TH1F("result_matched_rms_CHS","",20,bins_x);
      result_matched_rms= gaussianfit(rebinned_hist_matched,channel_ranges[i],"",result_matched_rms,true );
      //  result_matched_rms_CHS= gaussianfit(rebinned_hist_matched_CHS,channel_ranges[i],"",result_matched_rms_CHS,true );

      ////////////////////////   upar  /////////////////////////
     
      hist_name="DY_output/rms_NPV";
      if(berror) std::cout<<"DY::Response read in Hists "<<hist_name<<std::endl;
      hist_matched = (TH2F*)DY_f->Get(hist_name);
      hist_CHS_matched = (TH2F*)DY_CHS_f->Get(hist_name);
     
      //rebin hists
      rebinned_hist_matched= rebin(bins_x,hist_matched ,rebinned_hist_matched,channel_ranges[i],"",-100,100);
      //  rebinned_hist_matched_CHS= rebin(bins_x,hist_CHS_matched ,rebinned_hist_matched_CHS,channel_ranges[i], "");
      //gaussian fit
       result_matched_rms = new TH1F("result_matched_rms","",20,bins_x);
      //  result_matched_rms_CHS = new TH1F("result_matched_rms_CHS","",20,bins_x);
      result_matched_rms= gaussianfit(rebinned_hist_matched,channel_ranges[i],"",result_matched_rms,true );
      //  result_matched_rms_CHS= gaussianfit(rebinned_hist_matched_CHS,channel_ranges[i],"",result_matched_rms_CHS,true );

      TCanvas *test2= new TCanvas("test2","Result Efficiency2",10,10,1000,1000);
      test2->Clear();
      test2->cd();
      result_matched_rms->Draw();
      //hist_matched->Draw("colz");
      // rebinned_hist_matched->Draw("colz");
      test2->Print("test2.eps");
      }
    }//channel_ranges i


  }//bDY

}


