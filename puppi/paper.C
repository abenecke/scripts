#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"

using namespace std;


bool berror=true; 
TString directory = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/";
TString output_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/pictures/";
TString folder="paper_trigger";
TString postfix = "";

#include "function.h"

void paper(){

 //general
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);

 TFile *Paper_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.MC.Paper"+postfix+".root", "READ");
 TFile *Data_Paper_f = new TFile(directory+folder+"/uhh2.AnalysisModuleRunner.Data.Data_Paper"+postfix+".root", "READ");


//alpha charged without data
 TH1F *h_alpha_charged_pu = (TH1F*)Paper_f->Get("alpha_p_charged_pu/Alpha");
 TH1F *h_alpha_charged_pv = (TH1F*)Paper_f->Get("alpha_p_charged_pv/Alpha");

 std::vector<TH1F*> hists={h_alpha_charged_pu,h_alpha_charged_pv};
 std::vector<TString> names ={"PU","PV"};
 std::vector<Color_t> colors={kRed,kBlue};
 save_paper_canvas (hists, names,0.1,0,"#alpha","Charged Particles",output_folder + folder + "/alpha_charged_wodata",colors);

 //alpha charged 
 TH1F *h_alpha_charged_pu_d = (TH1F*)Data_Paper_f->Get("alpha_p_charged_pu/Alpha");
 TH1F *h_alpha_charged_pv_d = (TH1F*)Data_Paper_f->Get("alpha_p_charged_pv/Alpha");

 hists={h_alpha_charged_pu,h_alpha_charged_pv,h_alpha_charged_pu_d,h_alpha_charged_pv_d};
 names ={"PU","PV","Data PU","Data PV"};
 colors={kRed,kBlue,kBlack,kGreen};
 save_paper_canvas (hists, names,0.1,0,"#alpha","Charged Particles",output_folder + folder + "/alpha_charged",colors);


 //alpha not_charged 
 TH1F *h_alpha_not_charged_pu = (TH1F*)Paper_f->Get("alpha_p_not_charged_pu/Alpha");
 TH1F *h_alpha_not_charged_pv = (TH1F*)Paper_f->Get("alpha_p_not_charged_pv/Alpha");
 TH1F *h_alpha_not_charged_pu_d = (TH1F*)Data_Paper_f->Get("alpha_p_not_charged_pu/Alpha");
 TH1F *h_alpha_not_charged_pv_d = (TH1F*)Data_Paper_f->Get("alpha_p_not_charged_pv/Alpha");

 hists={h_alpha_not_charged_pu,h_alpha_not_charged_pv,h_alpha_not_charged_pu_d,h_alpha_not_charged_pv_d};
 names ={"PU","PV","Data PU","Data PV"};
 colors={kRed,kBlue,kBlack,kGreen};
 save_paper_canvas (hists, names,0.16,0,"#alpha","Neutral Particles",output_folder + folder + "/alpha_neutral",colors);

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//alpha MED vs eta charged 2D
 TH2F *alpha_med_vs_eta_pu = (TH2F*) Paper_f->Get("alpha_p_charged_pu/alphaMED_eta");
 TH2F *alpha_med_vs_eta_pu_d = (TH2F*) Data_Paper_f->Get("alpha_p_charged_pu/alphaMED_eta");
 TH2F *alpha_med_vs_eta_pv = (TH2F*) Paper_f->Get("alpha_p_charged_pv/alphaMED_eta");
 TH2F *alpha_med_vs_eta_pv_d = (TH2F*) Data_Paper_f->Get("alpha_p_charged_pv/alphaMED_eta");

 save_paper_canvas ({alpha_med_vs_eta_pu},{"MC"},10,"colz","#eta","Alpha MED","PU (Charged)",output_folder + folder + "/alpha_med_vs_eta_pu_charged");
 save_paper_canvas ({alpha_med_vs_eta_pv},{"MC"},10,"colz","#eta","Alpha MED","PV (Charged)",output_folder + folder + "/alpha_med_vs_eta_pv_charged");


//alpha MED vs eta neutral 2D
 TH2F *alpha_med_vs_eta = (TH2F*) Paper_f->Get("alpha_p_not_charged/alphaMED_eta");
 TH2F *alpha_med_vs_eta_d = (TH2F*) Data_Paper_f->Get("alpha_p_not_charged/alphaMED_eta");

 save_paper_canvas ({alpha_med_vs_eta_pu},{"MC"},10,"colz","#eta","Alpha MED","(Neutral)",output_folder + folder + "/alpha_med_vs_eta_neutral");

 // Gauss fitted
 // Double_t bins[21]={-5,  -4.5,  -4,  -3.5,  -3,  -2.5,  -2,  -1.5, -1, -0.5, 0,  0.5,  1, 1.5, 2, 2.5, 3, 3.5,  4,  4.5, 5};
 //  TH2F* alpha_med_vs_eta_pu_r  =  paper_rebin(bins,20,alpha_med_vs_eta_pu, 0, 10);
 //  TH2F* alpha_med_vs_eta_pu_d_r  =  paper_rebin(bins,20,alpha_med_vs_eta_pu_d, 0, 10);


 //alpha_med_vs_eta_pu (Gausfit)
 std::vector<TH1F*> result = paper_gaussianfit(alpha_med_vs_eta_pu, output_folder + folder + "/slides/alpha_med_vs_eta_pu");
 std::vector<TH1F*> result_d = paper_gaussianfit(alpha_med_vs_eta_pu_d, output_folder + folder + "/slides/alpha_med_vs_eta_pu_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Charged Particles PU",output_folder + folder + "/alpha_med_vs_eta_pu_charged_average",colors,"",false,{1,4},false,"Alpha MED",0.58,0.38);

 //alpha_med_vs_eta_pv (Gausfit)
 result = paper_gaussianfit(alpha_med_vs_eta_pv, output_folder + folder + "/slides/alpha_med_vs_eta_pv");
 result_d = paper_gaussianfit(alpha_med_vs_eta_pv_d, output_folder + folder + "/slides/alpha_med_vs_eta_pv_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Charged Particles PV",output_folder + folder + "/alpha_med_vs_eta_pv_charged_average",colors,"",false,{1,4},false,"Alpha MED",0.58,0.38);

 //alpha_med_vs_eta (Gausfit)
 result = paper_gaussianfit(alpha_med_vs_eta, output_folder + folder + "/slides/alpha_med_vs_eta");
 result_d = paper_gaussianfit(alpha_med_vs_eta_d, output_folder + folder + "/slides/alpha_med_vs_eta_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Neutral Particles",output_folder + folder + "/alpha_med_vs_eta_average",colors,"",false,{1,4},false,"Alpha MED",0.58,0.38);


//alpha MED vs eta neutral 2D
 alpha_med_vs_eta_pu = (TH2F*) Paper_f->Get("alpha_p_not_charged_pu/alphaMED_eta");
 alpha_med_vs_eta_pu_d = (TH2F*) Data_Paper_f->Get("alpha_p_not_charged_pu/alphaMED_eta");
 alpha_med_vs_eta_pv = (TH2F*) Paper_f->Get("alpha_p_not_charged_pv/alphaMED_eta");
 alpha_med_vs_eta_pv_d = (TH2F*) Data_Paper_f->Get("alpha_p_not_charged_pv/alphaMED_eta");

 save_paper_canvas ({alpha_med_vs_eta_pu},{"MC"},10,"colz","#eta","Alpha MED","PU (Neutral)",output_folder + folder + "/alpha_med_vs_eta_pu_not_charged");
 save_paper_canvas ({alpha_med_vs_eta_pv},{"MC"},10,"colz","#eta","Alpha MED","PV (Neutral)",output_folder + folder + "/alpha_med_vs_eta_pv_not_charged");

//alpha_med_vs_eta_pu (Gausfit)
 result = paper_gaussianfit(alpha_med_vs_eta_pu, output_folder + folder + "/slides/alpha_med_vs_eta_pu");
 result_d = paper_gaussianfit(alpha_med_vs_eta_pu_d, output_folder + folder + "/slides/alpha_med_vs_eta_pu_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Neutral Particles PU",output_folder + folder + "/alpha_med_vs_eta_pu_not_charged_average",colors,"",false,{1,4},false,"Alpha MED",0.58,0.38);

 //alpha_med_vs_eta_pv (Gausfit)
 result = paper_gaussianfit(alpha_med_vs_eta_pv, output_folder + folder + "/slides/alpha_med_vs_eta_pv");
 result_d = paper_gaussianfit(alpha_med_vs_eta_pv_d, output_folder + folder + "/slides/alpha_med_vs_eta_pv_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Neutral Particles PV",output_folder + folder + "/alpha_med_vs_eta_pv_not_charged_average",colors,"",false,{1,4},false,"Alpha MED",0.58,0.38);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//alpha RMS vs eta charged
 TH2F *alpha_rms_vs_eta_pu = (TH2F*) Paper_f->Get("alpha_p_charged_pu/alphaRMS_eta");
 TH2F *alpha_rms_vs_eta_pu_d = (TH2F*) Data_Paper_f->Get("alpha_p_charged_pu/alphaRMS_eta");
 TH2F *alpha_rms_vs_eta_pv = (TH2F*) Paper_f->Get("alpha_p_charged_pv/alphaRMS_eta");
 TH2F *alpha_rms_vs_eta_pv_d = (TH2F*) Data_Paper_f->Get("alpha_p_charged_pv/alphaRMS_eta");

 save_paper_canvas ({alpha_rms_vs_eta_pu},{"MC"},10,"colz","#eta","Alpha RMS","PU (Charged)",output_folder + folder + "/alpha_rms_vs_eta_pu_charged");
 save_paper_canvas ({alpha_rms_vs_eta_pv},{"MC"},10,"colz","#eta","Alpha RMS","PV (Charged)",output_folder + folder + "/alpha_rms_vs_eta_pv_charged");

//alpha RMS vs eta neutral
 TH2F *alpha_rms_vs_eta = (TH2F*) Paper_f->Get("alpha_p_not_charged/alphaRMS_eta");
 TH2F *alpha_rms_vs_eta_d = (TH2F*) Data_Paper_f->Get("alpha_p_not_charged/alphaRMS_eta");

 save_paper_canvas ({alpha_rms_vs_eta_pu},{"MC"},10,"colz","#eta","Alpha RMS","(Neutral)",output_folder + folder + "/alpha_rms_vs_eta_neutral");


 //alpha_rms_vs_eta_pu
 result = paper_gaussianfit(alpha_rms_vs_eta_pu, output_folder + folder + "/slides/alpha_rms_vs_eta_pu");
 result_d = paper_gaussianfit(alpha_rms_vs_eta_pu_d, output_folder + folder + "/slides/alpha_rms_vs_eta_pu_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Charged Particles PU",output_folder + folder + "/alpha_rms_vs_eta_pu_charged_average",colors,"",false,{1,4},false,"Alpha RMS",0.48,0.28,0.35,0.5);

 //alpha_rms_vs_eta_pv
 result = paper_gaussianfit(alpha_rms_vs_eta_pv, output_folder + folder + "/slides/alpha_rms_vs_eta_pv");
 result_d = paper_gaussianfit(alpha_rms_vs_eta_pv_d, output_folder + folder + "/slides/alpha_rms_vs_eta_pv_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Charged Particles PV",output_folder + folder + "/alpha_rms_vs_eta_pv_charged_average",colors,"",false,{1,4},false,"Alpha RMS",0.48,0.28,0.35,0.5);

 //alpha_rms_vs_eta
 result = paper_gaussianfit(alpha_rms_vs_eta, output_folder + folder + "/slides/alpha_rms_vs_eta");
 result_d = paper_gaussianfit(alpha_rms_vs_eta_d, output_folder + folder + "/slides/alpha_rms_vs_eta_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Neutral Particles",output_folder + folder + "/alpha_rms_vs_eta_average",colors,"",false,{1,4},false,"Alpha RMS",0.48,0.28,0.35,0.5);

//alpha RMS vs eta charged
 alpha_rms_vs_eta_pu = (TH2F*) Paper_f->Get("alpha_p_not_charged_pu/alphaRMS_eta");
 alpha_rms_vs_eta_pu_d = (TH2F*) Data_Paper_f->Get("alpha_p_not_charged_pu/alphaRMS_eta");
 alpha_rms_vs_eta_pv = (TH2F*) Paper_f->Get("alpha_p_not_charged_pv/alphaRMS_eta");
 alpha_rms_vs_eta_pv_d = (TH2F*) Data_Paper_f->Get("alpha_p_not_charged_pv/alphaRMS_eta");


 //alpha_rms_vs_eta_pu
 result = paper_gaussianfit(alpha_rms_vs_eta_pu, output_folder + folder + "/slides/alpha_rms_vs_eta_pu");
 result_d = paper_gaussianfit(alpha_rms_vs_eta_pu_d, output_folder + folder + "/slides/alpha_rms_vs_eta_pu_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Neutral Particles PU",output_folder + folder + "/alpha_rms_vs_eta_pu_not_charged_average",colors,"",false,{1,4},false,"Alpha RMS",0.38,0.18,0.35,0.5);

 //alpha_rms_vs_eta_pv
 result = paper_gaussianfit(alpha_rms_vs_eta_pv, output_folder + folder + "/slides/alpha_rms_vs_eta_pv");
 result_d = paper_gaussianfit(alpha_rms_vs_eta_pv_d, output_folder + folder + "/slides/alpha_rms_vs_eta_pv_d");
 save_paper_canvas ({result[0],result_d[0]},{"MC","Data"},5,0,"#eta","Neutral Particles PV",output_folder + folder + "/alpha_rms_vs_eta_pv_not_charged_average",colors,"",false,{1,4},false,"Alpha RMS",0.38,0.18,0.35,0.5);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//weight function charged
 TH1F *h_weight_charged_pu = (TH1F*)Paper_f->Get("alpha_p_charged_pu/Weight");
 TH1F *h_weight_charged_pv = (TH1F*)Paper_f->Get("alpha_p_charged_pv/Weight");
 TH1F *h_weight_charged_pu_d = (TH1F*)Data_Paper_f->Get("alpha_p_charged_pu/Weight");
 TH1F *h_weight_charged_pv_d = (TH1F*)Data_Paper_f->Get("alpha_p_charged_pv/Weight");


 hists={h_weight_charged_pu_d,h_weight_charged_pv_d,h_weight_charged_pu,h_weight_charged_pv};
 names ={"Data PU","Data PV","PU","PV"};
 colors={kBlack,kGreen,kRed,kBlue};
 save_paper_canvas (hists, names,2,0,"weight","Charged Particles",output_folder + folder + "/weight_charged",colors,"",true,{20,20,1,1});

 //weight function neutral
 TH1F *h_weight_not_charged_pu = (TH1F*)Paper_f->Get("alpha_p_not_charged_pu/Weight");
 TH1F *h_weight_not_charged_pv = (TH1F*)Paper_f->Get("alpha_p_not_charged_pv/Weight");
 TH1F *h_weight_not_charged_pu_d = (TH1F*)Data_Paper_f->Get("alpha_p_not_charged_pu/Weight");
 TH1F *h_weight_not_charged_pv_d = (TH1F*)Data_Paper_f->Get("alpha_p_not_charged_pv/Weight");

 TH1F *h_weight_not_charged_central = (TH1F*)Paper_f->Get("alpha_p_not_charged_central/Weight");
 TH1F *h_weight_not_charged_forward = (TH1F*)Paper_f->Get("alpha_p_not_charged_forward/Weight");
 TH1F *h_weight_not_charged_central_d = (TH1F*)Data_Paper_f->Get("alpha_p_not_charged_central/Weight");
 TH1F *h_weight_not_charged_forward_d = (TH1F*)Data_Paper_f->Get("alpha_p_not_charged_forward/Weight");

 h_weight_not_charged_pu->GetXaxis()->SetRangeUser(-0.1,1.1);
 h_weight_not_charged_pv->GetXaxis()->SetRangeUser(-0.1,1.1);
 h_weight_not_charged_pu_d->GetXaxis()->SetRangeUser(-0.1,1.1);
 h_weight_not_charged_pv_d->GetXaxis()->SetRangeUser(-0.1,1.1);

 h_weight_not_charged_central->GetXaxis()->SetRangeUser(-0.1,1.1);
 h_weight_not_charged_forward->GetXaxis()->SetRangeUser(-0.1,1.1);
 h_weight_not_charged_central_d->GetXaxis()->SetRangeUser(-0.1,1.1);
 h_weight_not_charged_forward_d->GetXaxis()->SetRangeUser(-0.1,1.1);

 hists={h_weight_not_charged_pu,h_weight_not_charged_pv,h_weight_not_charged_pu_d,h_weight_not_charged_pv_d};
 names ={"PU","PV","Data PU","Data PV"};
 colors={kRed,kBlue,kBlack,kGreen};
 save_paper_canvas (hists, names,1.1,00.0001,"weight","Neutral Particles",output_folder + folder + "/weight_not_charged",colors,"",true,{1,1,20,20},true);



 hists={h_weight_not_charged_pu,h_weight_not_charged_pv};
 save_paper_canvas (hists, names,1.1,0,"weight","Neutral Particles",output_folder + folder + "/weight_not_charged_wodata",colors);

 TH1F *h_weight_not_charged = (TH1F*)Paper_f->Get("alpha_p_not_charged/Weight");
 h_weight_not_charged->GetXaxis()->SetRangeUser(-0.1,1.1);
 save_paper_canvas ({h_weight_not_charged}, {"MC"},1.1,0.0001,"weight","Neutral Particles",output_folder + folder + "/weight_not_charged_wodata_all",{kBlue},"",true,{20},true);


 hists={h_weight_not_charged_forward,h_weight_not_charged_central,h_weight_not_charged_forward_d,h_weight_not_charged_central_d};
 names ={"Forward","Central","Data Forward","Data Central"};
 colors={kRed,kBlue,kBlack,kGreen};
 save_paper_canvas (hists, names,1.1,00.0001,"weight","Neutral Particles",output_folder + folder + "/weight_not_charged_cf",colors,"",true,{1,1,20,20},true);
}


 // Double_t bins[100]={-5, -4.9, -4.8, -4.7, -4.6, -4.5, -4.4, -4.3, -4.2, -4.1, -4, -3.9, -3.8, -3.7, -3.6, -3.5, -3.4, -3.3, -3.2, -3.1, -3, -2.9, -2.8, -2.7, -2.6, -2.5, -2.4, -2.3, -2.2, -2.1, -2, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9};
// for (int i=1; i<alpha_med_vs_eta_pu->GetNbinsY()+1; ++i){
//   cout << alpha_med_vs_eta_pu->GetXaxis()->GetBinLowEdge(i) << ", ";}
//  cout<<"("<<alpha_med_vs_eta_pu->GetNbinsX()<<")"<<endl;
