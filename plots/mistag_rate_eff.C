#include "TH1.h"
#include <fstream>

using namespace std;
///////////                        Variabels to set                           ////////////////////////////////////////////////////////////////////////////
TString unc_name = "none"; // "jersmear_up" , "jersmear_down" ,"jecsmear_up" , "jecsmear_down" , "none"
 TString folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/pictures/eff/mistagrate/"+unc_name+"/";
TString unc_folder = "/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/QCD/mass/hists/";
 
TGraphAsymmErrors* get_eff(TString sample, TString obs, TString hname1,double &tot_eff, double &tot_err,TString hname_all,TString hname_trig )
{

  TFile* file;
  if (sample.CompareTo("data", TString::kIgnoreCase) == 0){ 
    file = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/QCD/mass/"+unc_name+"/uhh2.AnalysisModuleRunner.DATA.Data.root", "READ");
  } else if (sample.CompareTo("QCD", TString::kIgnoreCase) == 0){
      file = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/QCD/mass/"+unc_name+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  } 
 		
  TString name_all =  hname_all + hname1; 
  TH1F* d_all = (TH1F*) file->Get(name_all);
  TCanvas *all_c = new TCanvas("all_c","All",10,10,700,900);
  d_all->Draw();

  TString name_trig = hname_trig + hname1; 
  TH1F* d_trig = (TH1F*) file->Get(name_trig);

  TCanvas *trig_c = new TCanvas("trig_c","trig",10,10,700,900);
  d_trig->Draw();

TCanvas *new_c = new TCanvas("new_c","new",10,10,700,900);
  // // // // calculate total efficiency
  Double_t bx[2] = {d_all->GetXaxis()->GetXmin(), d_all->GetXaxis()->GetXmax()};    
  TH1F* tot_all = (TH1F*)d_all->Rebin(1, "tot_all",bx);
  TH1F* tot_trig = (TH1F*)d_trig->Rebin(1, "tot_trig",bx);
  // // add underflow and overflow bins
  tot_all->AddBinContent(1, d_all->GetBinContent(0)+d_all->GetBinContent(d_all->GetNbinsX()+1));
  tot_trig->AddBinContent(1, d_trig->GetBinContent(0)+d_trig->GetBinContent(d_trig->GetNbinsX()+1));
 
  TGraphAsymmErrors* toteff = new TGraphAsymmErrors( tot_trig, tot_all, "cl=0.683 b(1,1) mode" );
  Double_t x, y;
 
  toteff->GetPoint(0, x, y);


  cout << "\n------------------------------ efficiency calculation -----------------------------------" << endl;
  cout << "sample = " << sample << " observable = " << obs << " histogram = " << hname1 << endl;
  cout << "considering all bins, together with underflow and overflow! " << endl;
  cout << "content of underflow bin for all events: " << d_all->GetBinContent(10) << ", triggered = " << d_trig->GetBinContent(10) << endl;
  cout << "content of overflow bin for all events: " << d_all->GetBinContent(d_all->GetNbinsX()+1) << ", triggered = " << d_trig->GetBinContent(d_trig->GetNbinsX()+1) << endl;
 

    cout << "total eff = " << y << " + " << toteff->GetErrorYhigh(0) << " - " << toteff->GetErrorYlow(0) << endl << endl;
  tot_eff = y;

  tot_err = (toteff->GetErrorYhigh(0)+toteff->GetErrorYlow(0))/2.;
  // // rebin if pt
  // // if (hname.Contains("pt")){
  // //   Double_t binsx[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 160, 170, 180, 190, 200, 220, 240, 260, 280, 300, 350, 400, 500};
  // //   d_all = (TH1F*)d_all->Rebin(43, "all_rebinned", binsx);
  // //   d_trig = (TH1F*)d_trig->Rebin(43, "trig_rebinned", binsx);
  // // }

  // // // rebin if reliso
  // // if (hname.Contains("isolation")){
  // //   //cout << "bins: ";
  // //   //for (int i=1; i<d_all->GetNbinsX(); ++i){
  // //   //  cout << d_all->GetXaxis()->GetBinLowEdge(i) << ", ";
  // //   //}
  // //   //cout << endl;
  // //   Double_t binsx[] = {0, 0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1, 0.11, 0.12, 0.14, 0.16, 0.18, 0.2, 0.24, 0.28, 0.35, 0.5};
  // //   d_all = (TH1F*)d_all->Rebin(28, "all_rebinned", binsx);
  // //   d_trig = (TH1F*)d_trig->Rebin(28, "trig_rebinned", binsx);
  // // }
 
   TGraphAsymmErrors* eff = new TGraphAsymmErrors( d_trig, d_all, "cl=0.683 b(1,1) mode" );

 
  if (sample.CompareTo("data", TString::kIgnoreCase) == 0){
    eff->SetMarkerStyle(20);
    eff->SetMarkerColor(kBlack);
    eff->SetLineColor(kBlack);
  }
  if (sample.CompareTo("QCD", TString::kIgnoreCase) == 0){
    eff->SetMarkerStyle(22);
    eff->SetMarkerColor(kRed+1);
    eff->SetLineColor(kRed+1);
  } 
   return eff;
}

TGraphAsymmErrors* get_eff_weight(TString sample, TString obs, TString hname1,double &tot_eff, double &tot_err,TString hname_all,TString hname_trig )
{

  TFile* file;
  if (sample.CompareTo("data", TString::kIgnoreCase) == 0){
   
    file = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/QCD/mass/"+unc_name+"/uhh2.AnalysisModuleRunner.DATA.Data.root", "READ");
   
  } else if (sample.CompareTo("QCD", TString::kIgnoreCase) == 0){
    file = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/QCD/mass/"+unc_name+"/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  } 
 		
  TString name_all =  hname_all + hname1; 
  TH1F* d_all = (TH1F*) file->Get(name_all);
  TCanvas *all_c = new TCanvas("all_c","All",10,10,700,900);
  d_all->Draw();

  TString name_trig = hname_trig + hname1; 
  TH1F* d_trig = (TH1F*) file->Get(name_trig);

  TCanvas *trig_c = new TCanvas("trig_c","trig",10,10,700,900);
  d_trig->Draw();

TCanvas *new_c = new TCanvas("new_c","new",10,10,700,900);
  // // // // calculate total efficiency
  Double_t bx[2] = {d_all->GetXaxis()->GetXmin(), d_all->GetXaxis()->GetXmax()};    
  TH1F* tot_all = (TH1F*)d_all->Rebin(1, "tot_all",bx);
  TH1F* tot_trig = (TH1F*)d_trig->Rebin(1, "tot_trig",bx);
  // // add underflow and overflow bins
  tot_all->AddBinContent(1, d_all->GetBinContent(0)+d_all->GetBinContent(d_all->GetNbinsX()+1));
  tot_trig->AddBinContent(1, d_trig->GetBinContent(0)+d_trig->GetBinContent(d_trig->GetNbinsX()+1));
 
  TGraphAsymmErrors* toteff = new TGraphAsymmErrors( d_trig, d_all, "cl=0.683 b(1,1) mode" );
  Double_t x, y;
 
  toteff->GetPoint(0, x, y);
  Double_t middle_y=0;
  // Double_t middle_y2=0;
  // Double_t middle_error_high=0;
  // Double_t middle_error_low=0;
  // Double_t middle_error_high2=0;
  // Double_t middle_error_low2=0;

  Double_t all=0;
  for(int i=0;i<d_trig->GetSize();i++) {
    all+=d_trig->GetBinContent(i);
   
  }
  cout <<"all "<<all<<endl;
  for(int i=0;i<d_trig->GetSize();i++){
    toteff->GetPoint(i, x, y);
    middle_y += y * (d_trig->GetBinContent(i)/all);
    //  middle_error_high += TMath::Power(toteff->GetErrorYhigh(i),2);
    //middle_error_low += TMath::Power(toteff->GetErrorYlow(i),2);
    cout<<middle_y<<" das is y "<<y <<"  das ist i "<< i <<"  das ist x "<< x << " das is prozentual "<<(y/all)<<endl;
   }
  // for(int i=2;i<44;i++){
  //   toteff->GetPoint(i, x, y);
  //   middle_y2 += y;
  //   //  cout<<"das is y "<<y <<"  das ist i "<< i <<"  Fehler : " <<toteff->GetErrorYhigh(i) << endl;
  //   middle_error_high2 += TMath::Power(toteff->GetErrorYhigh(i),2);
  //   middle_error_low2 += TMath::Power(toteff->GetErrorYlow(i),2);
  // }
  middle_y= middle_y/d_trig->GetSize();
  // middle_error_high = TMath::Sqrt(middle_error_high/44);
  // middle_error_low= TMath::Sqrt(middle_error_low/44);
  // middle_y2= middle_y2/(44-2);
  // middle_error_high2 = TMath::Sqrt(middle_error_high2/42);
  // middle_error_low2= TMath::Sqrt(middle_error_low2/42);


  cout << "\n------------------------------ efficiency calculation -----------------------------------" << endl;
  cout << "sample = " << sample << " observable = " << obs << " histogram = " << hname1 << endl;
  cout << "considering all bins, together with underflow and overflow! " << endl;
  cout << "content of underflow bin for all events: " << d_all->GetBinContent(10) << ", triggered = " << d_trig->GetBinContent(10) << endl;
  cout << "content of overflow bin for all events: " << d_all->GetBinContent(d_all->GetNbinsX()+1) << ", triggered = " << d_trig->GetBinContent(d_trig->GetNbinsX()+1) << endl;
  cout << "total eff (0-1400) = " <<middle_y  <<endl;//<< " + " << middle_error_high << " - " <<middle_error_low  << endl;
  // cout << "total eff (257-1400) = " <<middle_y2  << " + " << middle_error_high2 << " - " <<middle_error_low2  << endl << endl;
  // tot_eff = middle_y2;
  // tot_err = (middle_error_high + middle_error_low)/2.;

    cout << "total eff = " << y << " + " << toteff->GetErrorYhigh(0) << " - " << toteff->GetErrorYlow(0) << endl << endl;
  tot_eff = y;

  tot_err = (toteff->GetErrorYhigh(0)+toteff->GetErrorYlow(0))/2.;
  // // rebin if pt
  // // if (hname.Contains("pt")){
  // //   Double_t binsx[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 160, 170, 180, 190, 200, 220, 240, 260, 280, 300, 350, 400, 500};
  // //   d_all = (TH1F*)d_all->Rebin(43, "all_rebinned", binsx);
  // //   d_trig = (TH1F*)d_trig->Rebin(43, "trig_rebinned", binsx);
  // // }

  // // // rebin if reliso
  // // if (hname.Contains("isolation")){
  // //   //cout << "bins: ";
  // //   //for (int i=1; i<d_all->GetNbinsX(); ++i){
  // //   //  cout << d_all->GetXaxis()->GetBinLowEdge(i) << ", ";
  // //   //}
  // //   //cout << endl;
  // //   Double_t binsx[] = {0, 0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1, 0.11, 0.12, 0.14, 0.16, 0.18, 0.2, 0.24, 0.28, 0.35, 0.5};
  // //   d_all = (TH1F*)d_all->Rebin(28, "all_rebinned", binsx);
  // //   d_trig = (TH1F*)d_trig->Rebin(28, "trig_rebinned", binsx);
  // // }
 
   TGraphAsymmErrors* eff = new TGraphAsymmErrors( d_trig, d_all, "cl=0.683 b(1,1) mode" );
 
  if (sample.CompareTo("data", TString::kIgnoreCase) == 0){
    eff->SetMarkerStyle(20);
    eff->SetMarkerColor(kBlack);
    eff->SetLineColor(kBlack);
  }
  if (sample.CompareTo("QCD", TString::kIgnoreCase) == 0){
    eff->SetMarkerStyle(22);
    eff->SetMarkerColor(kRed+1);
    eff->SetLineColor(kRed+1);
  } 
   return eff;
}

void draw_eff(TGraphAsymmErrors* eff, TString epsfilename, TString sample, double tot_eff, double tot_err)
{
  gPad->SetTicks();
  eff->Draw("AP");
  double x,y;

  TH1F* painter = eff->GetHistogram();
  TString xtitle = painter->GetTitle();
  if (xtitle.Contains("reliso", TString::kIgnoreCase)){
    xtitle = "electron relative isolation";
  }
  painter->GetXaxis()->SetTitle(painter->GetTitle());
  painter->GetYaxis()->SetTitle("mistag rate Z W tagger");
  painter->SetTitle(sample);
  painter->GetXaxis()->SetTitleSize(0.05);
  painter->GetYaxis()->SetTitleSize(0.05);
  painter->GetXaxis()->SetLabelSize(0.04);
  painter->GetYaxis()->SetLabelSize(0.04);

  painter->GetYaxis()->SetRangeUser(0, 1.2);
  // painter->GetYaxis()->SetRangeUser(0, 0.01);

  gPad->SetTopMargin(0.08);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.15);

  TLine* l = new TLine(painter->GetXaxis()->GetXmin(), 1., painter->GetXaxis()->GetXmax(), 1.);
  l->SetLineColor(kBlue);
  l->Draw();

  eff->Draw("Psame");

  TString info = TString::Format("< #varepsilon > = %4.3f #pm %4.3f", tot_eff, tot_err);
  TLatex* text = new TLatex();
  text->SetTextFont(62);
  text->SetNDC();
  text->SetTextColor(eff->GetLineColor());
  text->SetTextSize(0.04);
  // text->DrawLatex(0.67, 0.2, info.Data());
  text->DrawLatex(0.67, 0.8, info.Data());

  gPad->SaveAs(epsfilename);

}
void draw_both_eff(TGraphAsymmErrors* eff, TString epsfilename, TString sample, double tot_eff, double tot_err,TGraphAsymmErrors* eff2, TString sample2, double tot_eff2, double tot_err2)
{
  gPad->SetTicks();
  eff->Draw("AP");
  
  double x,y;

  TH1F* painter = eff->GetHistogram();
  TString xtitle = painter->GetTitle();
  if (xtitle.Contains("reliso", TString::kIgnoreCase)){
    xtitle = "electron relative isolation";
  }
  painter->GetXaxis()->SetTitle(painter->GetTitle());
  painter->GetYaxis()->SetTitle("mistag rate Z/W tagger [%]");
  painter->SetTitle("");
  painter->GetXaxis()->SetTitleSize(0.05);
  painter->GetYaxis()->SetTitleSize(0.05);
  painter->GetXaxis()->SetLabelSize(0.04);
  painter->GetYaxis()->SetLabelSize(0.04);
 painter->GetXaxis()->SetTitle("p_{T} AK8 jet [GeV/c]");
 painter->GetYaxis()->SetTitleOffset(1.9);

  painter->GetYaxis()->SetRangeUser(0, 0.25);

  gPad->SetTopMargin(0.08);
  gPad->SetRightMargin(0.04);
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.2);

  TLine* l = new TLine(painter->GetXaxis()->GetXmin(), 1., painter->GetXaxis()->GetXmax(), 1.);
  l->SetLineColor(kBlue);
  l->Draw();

  eff->Draw("Psame");
  eff2->Draw("PSAME");

  TPaveText* pt = new TPaveText(0.2,0.18,0.62,0.29,"nbNDC");
  pt->SetFillColor(kGray);
  pt->Draw();


  TString info = TString::Format("< #varepsilon_{MC} > = %4.3f #pm %4.3f", tot_eff, tot_err);
  TString info2 = TString::Format("< #varepsilon_{Data} > = %4.3f #pm %4.3f", tot_eff2, tot_err2);
  TLatex* text = new TLatex();
  text->SetTextFont(62);
  text->SetNDC();
  text->SetTextColor(eff->GetLineColor());
  text->SetTextSize(0.04);
  // text->DrawLatex(0.67, 0.2, info.Data());
  text->DrawLatex(0.2, 0.25, info.Data());
 text->SetTextColor(eff2->GetLineColor());
  text->DrawLatex(0.2, 0.2, info2.Data());

  gPad->SaveAs(epsfilename);

}


void draw_ratio(TGraphAsymmErrors* ratio, TString epsfilename, TString rname)
{
  gPad->SetTicks();
  ratio->Draw("AP");
  double x,y;

  TH1F* painter = ratio->GetHistogram();
  painter->GetXaxis()->SetTitle(painter->GetTitle());
  if(epsfilename.Contains("pt"))  painter->GetXaxis()->SetTitle("p_{T} AK8 jet [GeV/c]");
  painter->GetYaxis()->SetTitle(rname);
  painter->GetYaxis()->CenterTitle(true);
  painter->SetTitle("");
  painter->GetXaxis()->SetTitleSize(0.05);
  painter->GetYaxis()->SetTitleSize(0.05);
  painter->GetXaxis()->SetLabelSize(0.04);
  painter->GetYaxis()->SetLabelSize(0.04);

  painter->GetYaxis()->SetRangeUser(0.4, 2.6);

  gPad->SetTopMargin(0.08);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.15);

  TLine* l = new TLine(painter->GetXaxis()->GetXmin(), 1., painter->GetXaxis()->GetXmax(), 1.);
  l->SetLineColor(kBlue);
  l->SetLineStyle(kDotted);
  l->Draw();

  ratio->Draw("Psame");

  TF1* func;
  if (epsfilename.Contains("isolation", TString::kIgnoreCase)){
    func = new TF1("Ratio", "[0]+[1]*x", painter->GetXaxis()->GetXmin(),  painter->GetXaxis()->GetXmax());
    func->SetParName(0, "p0");
    func->SetParName(0, "p1");
  } else {
    func = new TF1("Ratio", "[0]", painter->GetXaxis()->GetXmin(),  painter->GetXaxis()->GetXmax());
    func->SetParName(0, "Ratio");
  }
  ratio->Fit(func);
  
  if(epsfilename.Contains("pt.eps", TString::kIgnoreCase)){
    TFile *f= new TFile(unc_folder +"QCD_"+unc_name+".root","RECREATE");
    TH1F *tot_eff_h = new TH1F("tot_eff_h","tot eff",1,1,2);
    tot_eff_h->Fill(1,func->GetParameter(0));
    tot_eff_h->Write();
    if(unc_name == "none"){
    TH1F *tot_err_h = new TH1F("tot_err_h","tot error",1,1,2);
    tot_err_h->Fill(1,func->GetParError(0));
    tot_err_h->Write();
    }
    f->Close();
  }

  gPad->SaveAs(epsfilename);

}

TGraphAsymmErrors* get_ratio(TGraphAsymmErrors* top, TGraphAsymmErrors* bottom)
{
  TGraphAsymmErrors* ratio = new TGraphAsymmErrors(*top);

  for (int i=0; i<top->GetN(); ++i){
    double xt,yt,xb,yb;
    top->GetPoint(i,xt,yt);
    bottom->GetPoint(i,xb,yb);
    double r = yt / yb;
    ratio->SetPoint(i,xt,r);
    
    // up error
    double ut = top->GetErrorYhigh(i)/yb;
    double ub = (bottom->GetErrorYlow(i)*yt)/(yb*yb);
    double up = TMath::Sqrt(ut*ut+ub*ub);

    ratio->SetPointEYhigh(i, up*r);

    // down error
    double dt = top->GetErrorYlow(i)/yb;
    double db = (bottom->GetErrorYhigh(i)*yt)/(yb*yb);
    double down = TMath::Sqrt(dt*dt+db*db);
    ratio->SetPointEYlow(i, down*r);
  }

  return ratio;

}


void mistag_rate_eff()
{
  gStyle->SetOptFit(1111);
 
  

   TString snames[] = {"Data", "QCD" };
  //TString snames[] = { "QCD" };
  TString prefix = "";
  
  for (int i=0; i<2; ++i){
    TString sample = snames[i];

    TString obs = "TopJet";
    double tot_eff, tot_err;
    TString hist = "pt";
    TString hname_all="topjet_topjet2/";
    TString hname_trig="topjet_pass_zwtag/";
    // TString hname_all="topjet_chi2cut_W/";
    // TString hname_trig="topjet_zwtag_W/";
    TString filename = folder+prefix + sample + "_" + obs + "_" + hist + ".eps";
    TGraphAsymmErrors* eff = get_eff(sample, obs, hist,  tot_eff, tot_err,hname_all,hname_trig);
 
    draw_eff(eff, filename, sample, tot_eff, tot_err);
    

    // hist = "eta";
    // filename = folder+prefix + sample + "_" + obs + "_" + hist + ".eps";
    // eff = get_eff(sample, obs, hist, tot_eff, tot_err,hname_all,hname_trig);
    // draw_eff(eff, filename, sample, tot_eff, tot_err);


    // hist = "pt_1";
    // hname_all="topjet_first_topjet2/";
    // hname_trig="topjet_first_pass_zwtag/";
    // filename = folder+prefix + sample + "_" + obs + "_" + hist + ".eps";
    // eff = get_eff(sample, obs, hist, tot_eff, tot_err,hname_all,hname_trig);
    // draw_eff(eff, filename, sample, tot_eff, tot_err);

    // hist = "pt_1";
    // hname_all="topjet_seconde_topjet2/";
    // hname_trig="topjet_seconde_pass_zwtag/";
    // filename = folder+prefix + sample + "_" + obs + "_" +"pt_2" + ".eps";
    // eff = get_eff(sample, obs, hist, tot_eff, tot_err,hname_all,hname_trig);
    // draw_eff(eff, filename, sample, tot_eff, tot_err);

    // hist = "pt_1";
    // hname_all="topjet_third_topjet2/";
    // hname_trig="topjet_third_pass_zwtag/";
    // filename =folder+ prefix + sample + "_" + obs + "_"  +"pt_3"+ ".eps";
    // eff = get_eff(sample, obs, hist, tot_eff, tot_err,hname_all,hname_trig);
    // draw_eff(eff, filename, sample, tot_eff, tot_err);

   

  }
 TString obs = "TopJet";
 double tot_eff2, tot_err2;
 double tot_eff, tot_err;
 TString hist = "pt";
 TString hname_all="topjet_topjet2/";
 TString hname_trig="topjet_pass_zwtag/";
 TString filename = folder+"draw_both.eps";
 TGraphAsymmErrors* eff = get_eff(snames[1], obs, hist,  tot_eff, tot_err,hname_all,hname_trig);
 TGraphAsymmErrors* eff2 = get_eff(snames[0], obs, hist,  tot_eff2, tot_err2,hname_all,hname_trig);
 draw_both_eff(eff, filename, snames[1], tot_eff, tot_err,eff2, snames[0], tot_eff2, tot_err2 );

  
 //  TString obs = "TopJet";
 //  TString hist = "pt";
 //  TString hname_all="topjet_topjet2/";
 //  TString hname_trig="topjet_pass_zwtag/";
 //  double tot_eff, tot_err;
 //  TGraphAsymmErrors* deff =get_eff("Data", obs, hist,  tot_eff, tot_err ,hname_all,hname_trig);
 //  TGraphAsymmErrors* mceff = get_eff("QCD", obs, hist, tot_eff, tot_err ,hname_all,hname_trig);
 //  TGraphAsymmErrors* ratio = get_ratio(deff, mceff);
 obs = "TopJet";
 hist = "pt";
 hname_all="topjet_topjet2/";
 hname_trig="topjet_pass_zwtag/";
 TGraphAsymmErrors* deff =get_eff("Data", obs, hist,  tot_eff, tot_err ,hname_all,hname_trig);
 TGraphAsymmErrors* mceff = get_eff("QCD", obs, hist, tot_eff, tot_err ,hname_all,hname_trig);
 TGraphAsymmErrors* ratio = get_ratio(deff, mceff);
   
  draw_ratio(ratio, folder+prefix + "ratio_"+hist+".eps", "Data / MC");

 //  hist = "eta";
 //  deff = get_eff("Data", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  mceff = get_eff("QCD", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  ratio = get_ratio(deff, mceff);
 //  draw_ratio(ratio, folder+prefix + "ratio_"+hist+".eps", "Data / MC");

 
 //  hist = "pt_1";
 //  hname_all="topjet_first_topjet2/";
 //  hname_trig="topjet_first_pass_zwtag/";
 //  deff = get_eff("Data", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  mceff = get_eff("QCD", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  ratio = get_ratio(deff, mceff);
 //  draw_ratio(ratio, folder+prefix + "ratio_"+hist+".eps", "Data / MC");

  
 //  hist = "pt_1";
 //  hname_all="topjet_seconde_topjet2/";
 //  hname_trig="topjet_seconde_pass_zwtag/";
 //  deff = get_eff("Data", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  mceff = get_eff("QCD", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  ratio = get_ratio(deff, mceff);
 //  draw_ratio(ratio, folder+prefix + "ratio_"+"pt_2"+".eps", "Data / MC");

 //  hist = "pt_1";
 //  hname_all="topjet_third_topjet2/";
 //  hname_trig="topjet_third_pass_zwtag/";
 //  deff = get_eff("Data", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  mceff = get_eff("QCD", obs, hist, tot_eff, tot_err,hname_all,hname_trig);
 //  ratio = get_ratio(deff, mceff);
 //  draw_ratio(ratio, folder+prefix + "ratio_"+"pt_3"+".eps", "Data / MC");

 


  // TString hist = "isolation";
  // TGraphAsymmErrors* deff = get_eff("Data", obs, hist, tot_eff, tot_err);
  // TGraphAsymmErrors* mceff = get_eff("QCD", obs, hist, tot_eff, tot_err);
  // TGraphAsymmErrors* ratio = get_ratio(deff, mceff);
  // draw_ratio(ratio, folder+prefix + "ratio_electron_isolation.eps", "Data / MC");
  
  

}

