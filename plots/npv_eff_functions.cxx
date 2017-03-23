#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"
int i=0;

void plot_result(std::vector<TGraphAsymmErrors*> hists, double max, double min){
  i++;
  TString name= Form ("%d", i);
  TCanvas *result_eff_preselection_c= new TCanvas(name,name,10,10,1000,1000);
  result_eff_preselection_c->Clear();
  result_eff_preselection_c->cd();
  result_eff_preselection_c->SetLogy();
  
  TGraphAsymmErrors *data = hists[0];
  TGraphAsymmErrors *signal = hists[1];
  TGraphAsymmErrors *data_puppi = hists[2];
  TGraphAsymmErrors *signal_puppi = hists[3];
  
  data->SetMaximum(max);
  data->SetMinimum(min);
  data->Draw("AP");
  signal->SetLineColor(kRed);
  signal->SetMarkerColor(kRed);
  signal->Draw("same P");
  data_puppi->SetLineColor(kOrange);
  data_puppi->SetMarkerColor(kOrange);
  data_puppi->Draw("same P");
  signal_puppi->SetLineColor(kGreen);
  signal_puppi->SetMarkerColor(kGreen);
  signal_puppi->Draw("same P");
  
  TLegend *leg = new TLegend(0.35,0.23,0.7,0.13, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(data,"Data CHS","lpe");
  leg->AddEntry(data_puppi,"Data Puppi","lpe");
  leg->AddEntry(signal,"Signal CHS","lpe");
  leg->AddEntry(signal_puppi,"Signal Puppi","lpe");
  leg->Draw();
}
