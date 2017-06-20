#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"
int i=0;

void plot_result(std::vector<TGraphAsymmErrors*> hists, double max, double min,TString filename="1", TString leg_title1="Data CHS", TString leg_title2="Data Puppi",TString leg_title3="Signal CHS",TString leg_title4="Signal Puppi", bool b2=false, bool blog=true){
  i++;
  TString name= Form ("%d", i);
  TCanvas *result_eff_preselection_c= new TCanvas(name,name,10,10,1000,1000);
  gPad->SetTickx();
  gPad->SetTicky();

  result_eff_preselection_c->Clear();
  result_eff_preselection_c->cd();
  if(blog)result_eff_preselection_c->SetLogy();
  
  TGraphAsymmErrors *data = hists[0];
  TGraphAsymmErrors *signal = hists[1];
  TGraphAsymmErrors *data_puppi = hists[2];
  TGraphAsymmErrors *signal_puppi = hists[3];
  
  data->SetMaximum(max);
  data->SetMinimum(min);
  data->SetTitle("");
  data->GetXaxis()->SetTitle("NPV");
  data->GetYaxis()->SetTitle("Efficiency");
  data->SetLineColor(kBlue);
  data->SetMarkerColor(kBlue);
  data->Draw("AP");
  signal->SetLineColor(kOrange);
  signal->SetMarkerColor(kOrange);
  signal->Draw("same P");
  data_puppi->SetLineColor(kRed);
  data_puppi->SetMarkerColor(kRed);
  if(!b2)  data_puppi->Draw("same P");
  signal_puppi->SetLineColor(kGreen);
  signal_puppi->SetMarkerColor(kGreen);
  if(!b2) signal_puppi->Draw("same P");
  
  TLegend *leg = new TLegend(0.35,0.23,0.7,0.13, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(data,leg_title1,"lpe");
  if(!b2) leg->AddEntry(data_puppi,leg_title2,"lpe");
  leg->AddEntry(signal,leg_title3,"lpe");
  if(!b2) leg->AddEntry(signal_puppi,leg_title4,"lpe");
  leg->Draw();

  result_eff_preselection_c->Print(filename+".eps");
}
