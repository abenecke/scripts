#include "TH1.h"
#include "TH2.h"
#include <fstream>
int i=0;

std::vector<TH1F*> rebin(int rebin ,std::vector<TH1F*> hists ){

  std::vector<TH1F*> results;
  results.reserve(hists.size());

  for(int i=0;i <hists.size(); i++){
    
    TH1F *hist = hists[i];
    hist->Rebin(rebin);
   
    results.push_back(hist);
  }//end forloop over all hists

  return results;
}// rebin function end


void save_result (std::vector< TH1F*> hists, std::vector<Color_t> colors, std::vector<TString> names,TString save_name,TString legendheader="", TString Xtitle="", TString Ytitle ="",double TL_x1=.4,double TL_y1=.52,double TL_x2=.64,double TL_y2=.17, bool bscale=false, bool blogy=false, double textsize=0.05){
  i++;
  TString name= Form ("%d", i);
  TCanvas *c= new TCanvas(name,name,0,0,1000,800);
  c->Clear();
  c->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  c->SetBorderMode(0);
  c->SetBorderSize(3);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderSize(0);
  if(blogy) c->SetLogy();

  c->SetTopMargin(0.05);
  c->SetBottomMargin(0.15);
  hists[0]->GetXaxis()->SetTitle(Xtitle);
  hists[0]->GetXaxis()->SetTitleOffset(0.9);
  hists[0]->GetXaxis()->SetTitleSize(0.06);
  hists[0]->GetXaxis()->SetTitleFont(22);


  c->SetRightMargin(0.05);
  c->SetLeftMargin(0.14);
  hists[0]->GetYaxis()->SetTitle(Ytitle);
  hists[0]->GetYaxis()->SetTitleOffset(1.15);
  hists[0]->GetYaxis()->SetTitleSize(0.06);
  hists[0]->GetYaxis()->SetTitleFont(22);
  if(bscale)  hists[0]->Scale(1/hists[0]->Integral());
  hists[0]->Draw();

  TLegend *leg = new TLegend(TL_x1,TL_y1,TL_x2,TL_y2, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetHeader(legendheader);
  leg->SetTextSize(textsize);//0.05
  leg->SetTextFont(22);

  for(int j=0; j < hists.size();j++){

    hists[j]->SetLineColor(colors[j]);
    hists[j]->SetMarkerColor(colors[j]);
    if(bscale)  hists[j]->Scale(1/hists[j]->Integral());
    hists[j]->Draw("same");
    leg->AddEntry(hists[j],names[j]);

  }//end forloop all hists

  leg->Draw();

  c->Print(output_folder+ save_name);

}//save_result function end
