#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"


int i=0;

TH1F* gaussianfit(TH2F *rebinned_hist,TString channel_ranges,TString sel_ranges, TH1F *result_mean, bool brms=false ){
  //Get slice of NPV to see gaussian distribution for Mean and RMS
  TH1D *gaussian;
  TH1D *gaussian_CHS;
  TCanvas *c3= new TCanvas("c3","gaussian hist",10,10,700,900);
  TCanvas *gaussian_c = new TCanvas("gaussian_c","gaussian fit",10,10,700,900);
  if(berror)std::cout<<"in Gaussian fit" <<std::endl;
  for (int p=1; p<=rebinned_hist->GetXaxis()->GetNbins();p++) {
    gaussian = rebinned_hist->ProjectionY("_y",p,p+1);

    if(brms)result_mean->SetBinContent(p,gaussian->GetRMS());
    if(brms)result_mean->SetBinError(p,gaussian->GetRMSError());
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
    /* gaussian_fit->SetParameter(0, 0); */
    /* gaussian_fit->SetParameter(1, 0.2); */
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
	  
	  
    c3->Print(output_folder+folder+"/gaussian/"+channel_ranges+"_"+sel_ranges+"_slice_"+str+"_gaussian.eps");
	  
    if(berror) std::cout<<"Mean  "<<gaussian_fit->GetParameter(1)<<std::endl;
    if(berror) std::cout<<"Mean by GetMean "<<gaussian->GetMean()<<std::endl;
    if(berror) std::cout<<"RMS fit "<<gaussian_fit->GetParameter(2)<<std::endl;
    if(berror) std::cout<<"RMS  "<<gaussian->GetRMS()<<std::endl;

    if(!brms) result_mean->SetBinContent(p,gaussian_fit->GetParameter(1));
    if(!brms) result_mean->SetBinError(p,gaussian_fit->GetParError(1));
  }//over all slices
  return result_mean;
}

TH2F* rebin(Double_t *bins_x,TH2F *hist,TH2F *rebinned_hist,  TString channel_ranges, TString sel_ranges , int miny, int maxy){
  
  rebinned_hist = new TH2F("rebinned",hist->GetTitle(),20,bins_x,200,miny,maxy);
  // rebinned_hist = new TH2F("rebinned",hist->GetTitle(),20,bins_x,200,-1,1);//original
    
  TAxis *xaxis = hist->GetXaxis();
  TAxis *yaxis = hist->GetYaxis();
  
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
    c2->Print(output_folder+folder+"/rebinned/"+channel_ranges+"_"+sel_ranges+"_rebinned_hist.eps");
    c2->Destructor();
  }
  return rebinned_hist;
}

std::vector<TH2F*> rebin(Double_t *bins_x,TH2F *hist,TH2F *hist_CHS, TH2F *hist_CHS_wjec ){
  
  TH2F *rebinned_hist = new TH2F("rebinned",hist->GetTitle(),10,bins_x,200,-1,1);
  TH2F *rebinned_hist_CHS = new TH2F("rebinned_CHS",hist->GetTitle(),10,bins_x,200,-1,1);
  TH2F *rebinned_hist_CHS_wjec = new TH2F("rebinned_CHS_wjec",hist->GetTitle(),10,bins_x,200,-1,1);

  TAxis *xaxis = hist->GetXaxis();
  TAxis *yaxis = hist->GetYaxis();
  
  for (int j=1; j<=yaxis->GetNbins();j++) {
    for (int i=1; i<=xaxis->GetNbins();i++) {
      rebinned_hist->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist->GetBinContent(i,j));
      rebinned_hist_CHS->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist_CHS->GetBinContent(i,j));
      rebinned_hist_CHS_wjec->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist_CHS_wjec->GetBinContent(i,j));
    }
  }
 
  std::vector<TH2F*> results ={rebinned_hist,rebinned_hist_CHS,rebinned_hist_CHS_wjec};
  return results;
}

std::vector<TH1F*> gaussianfit(Double_t *bins_x, std::vector<TString> ranges,TH2F *rebinned_hist, TString post_fix =""){

  //Get slice of NPV to see gaussian distribution for Mean and RMS
  TH1D *gaussian;
  TCanvas *c3= new TCanvas("c3","gaussian hist",10,10,700,900);
  TCanvas *gaussian_c = new TCanvas("gaussian_c","gaussian fit",10,10,700,900);
  TH1F *result_mean = new TH1F("result_mean","",10,bins_x);
  TH1F *result_rms = new TH1F("result_rms","",10,bins_x);
  TH1F *rms = new TH1F("result_rms","",10,bins_x);
  TString ak_ranges=ranges[0];
  TString pt_ranges=ranges[1];
  TString scale_ranges=ranges[2];
  TString eta_ranges=ranges[3];

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
    for(int i=0; i<4;i++){
      /* double lower_bound = gaussian_fit->GetParameter(1) -1.5*gaussian_fit->GetParameter(2); */
      /* double higher_bound = gaussian_fit->GetParameter(1)+1.5*gaussian_fit->GetParameter(2); */
      double lower_bound = gaussian_fit->GetParameter(1) -1.0*gaussian_fit->GetParameter(2);
      double higher_bound = gaussian_fit->GetParameter(1)+1.0*gaussian_fit->GetParameter(2);
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
    

    c3->Print(output_folder+folder+"/gaussian/"+ak_ranges+"_"+scale_ranges+pt_ranges+"_"+eta_ranges+"_slice_"+str+"_gaussian"+post_fix+".eps");
    
    if(berror) std::cout<<"Mean  "<<gaussian_fit->GetParameter(1)<<std::endl;
    if(berror) std::cout<<"Mean by GetMean "<<gaussian->GetMean()<<std::endl;
    if(berror) std::cout<<"RMS  "<<gaussian_fit->GetParameter(2)<<std::endl;
    
    result_mean->SetBinContent(p,gaussian_fit->GetParameter(1));
    result_mean->SetBinError(p,gaussian_fit->GetParError(1));
    
    result_rms->SetBinContent(p,gaussian_fit->GetParameter(2));
    result_rms->SetBinError(p,gaussian_fit->GetParError(2));
  }//over all slices
  std::vector<TH1F*> results ={result_mean,result_rms,rms};
  return results;
}


void save_result(double max, double min,TString Xtitle,TString Ytitle,std::vector< TH1F*> result_hist, std::vector<TString> ranges,std::vector<TString>legend_names,TString meanvsrms="mean" ){
  TString ak_ranges=ranges[0];
  TString pt_ranges=ranges[1];
  TString scale_ranges=ranges[2];
  TString eta_ranges=ranges[3];
  TCanvas *result_mean_c= new TCanvas("result_mean_c","Result Mean",10,10,1000,1000);
  result_mean_c->Clear();
  result_mean_c->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetLegendTextSize(0.05);
  TH1F *result_mean = result_hist[0];
  result_mean->SetMaximum(max);
  result_mean->SetMinimum(min);
  
  result_mean->GetXaxis()->SetTitle(Xtitle);
  result_mean->GetYaxis()->SetTitle(Ytitle);
  
  result_mean->GetYaxis()->SetTitleOffset(1.4);
  result_mean->Draw("E1");
 
  for(int i=1;i<result_hist.size();i++){
    if(i==1) result_hist[i]->SetMarkerColor(kGreen);
    if(i==1) result_hist[i]->SetLineColor(kGreen);

    if(i==2) result_hist[i]->SetMarkerColor(kRed);
    if(i==2) result_hist[i]->SetLineColor(kRed);
    if(i==3) result_hist[i]->SetMarkerColor(kOrange);
    if(i==3) result_hist[i]->SetLineColor(kOrange);
    if(i==4) result_hist[i]->SetMarkerColor(kViolet);
    if(i==4) result_hist[i]->SetLineColor(kViolet);
    if(i==5) result_hist[i]->SetMarkerColor();
    if(i==5) result_hist[i]->SetLineColor(kBlack);
    result_hist[i]->Draw("same E1");
  
  }
 
  //labels like pt of the jets, eta range
  TPaveText *pt = new TPaveText(.20,.12,.40,.18,"nbNDC");
  if(pt_ranges=="30to40")	pt->AddText("30GeV<P_{T}<40GeV");
  if(pt_ranges=="100to150")	pt->AddText("100GeV<P_{T}<150GeV");
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->Draw();
  TPaveText *eta = new TPaveText(.75,.12,.85,.18,"nbNDC");
  if(eta_ranges=="Eta0to1p3")	eta->AddText("0<#eta<1.3");
  if(eta_ranges=="Eta1p3to2")	eta->AddText("1.3<#eta<2");
  if(eta_ranges=="Eta2to2p5")	eta->AddText("2<#eta<2.5");
  if(eta_ranges=="Eta2p5to3")	eta->AddText("2.5<#eta<3");
  if(eta_ranges=="Eta3to10")	eta->AddText("3<#eta<10");
  eta->SetFillColor(0);
  eta->SetTextSize(0.04);
  eta->Draw();
  //Legend
  TLegend *leg = new TLegend(0.25,0.88,0.5,0.68, NULL,"brNDC");
  for(int i=0;i<legend_names.size();i++){
    leg->AddEntry(result_hist[i],legend_names[i],"lpe");
  }
  /* if(meanvsrms=="mean"){ */
  /*   leg->AddEntry(result_hist[1],"CHS","lpe"); */
  /*   if(bCHS)   leg->AddEntry(result_hist[2],"CHS w JEC","lpe"); */
  /*   leg->AddEntry(result_mean,"Puppi","lpe"); */
  /* }else{ */
  /*   leg = new TLegend(0.25,0.88,0.5,0.58, NULL,"brNDC"); */
  /*   leg->AddEntry(result_hist[3],"CHS RMS","lpe"); */
  /*   if(bCHS)  leg->AddEntry(result_hist[5],"CHS w JEC RMS","lpe"); */
  /*   leg->AddEntry(result_hist[2],"Puppi RMS","lpe"); */
  /*   leg->AddEntry(result_hist[1],"CHS 1#sigma","lpe"); */
  /*   if(bCHS)  leg->AddEntry(result_hist[4],"CHS w JEC 1#sigma","lpe"); */
  /*   leg->AddEntry(result_hist[0],"Puppi 1#sigma","lpe"); */
  /* } */
  if(ak_ranges=="jet")	leg->SetHeader("AK4 Jet P_{T} Scale");
  if(ak_ranges=="topjet")	leg->SetHeader("AK8 Jet Mass Scale");
  if(meanvsrms=="rms"&&ak_ranges=="jet")	leg->SetHeader("AK4 Jet P_{T} Resolutuion");
  if(meanvsrms=="rms"&&ak_ranges=="topjet")	leg->SetHeader("AK8 Jet Mass Resolution");
  leg->SetBorderSize(0);	
  leg->SetFillStyle(0);
  leg->Draw();
  //save
  result_mean_c->Print(output_folder+folder+"/"+ak_ranges+"_"+scale_ranges+pt_ranges+"_"+eta_ranges+"_result_"+meanvsrms+".eps");
  result_mean_c->Destructor();
}



void save_canvas(TString canvas_name,TString add_folder,TString draw_opt, TH2F *hist, TH2F *hist_CHS,std::vector<TString> ranges ){
 
  TString ak_ranges=ranges[0];
  TString pt_ranges=ranges[1];
  TString scale_ranges=ranges[2];
  TString eta_ranges=ranges[3];
  TCanvas *c1 = new TCanvas("c1",canvas_name,10,10,1200,900);
  c1->Clear();
  c1->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetLegendTextSize(0.05);
  hist->Draw(draw_opt);
  c1->Print(output_folder+folder+"/"+add_folder+ak_ranges+"_"+scale_ranges+pt_ranges+"_"+eta_ranges+canvas_name+".eps");
  hist_CHS->Draw(draw_opt);
  c1->Print(output_folder+folder+"/"+add_folder+ak_ranges+"_"+scale_ranges+pt_ranges+"_"+eta_ranges+canvas_name+"_CHS.eps");
  c1->Destructor();

}

void save_paper_canvas (std::vector<TH1F*> hists,std::vector<TString> names,double max,double min,TString xaxis,TString leg_header,TString filename="test",std::vector<Color_t> colors={kRed,kBlue,kGreen,kOrange},TString title="",bool bscale = true, std::vector<double> markerstyle={1,1,20,20},bool blog=false,TString yaxis ="Events",double legymin=0.68, double legymax=0.88,double legxmin=0.45,double legxmax=0.85){
  i++;
  TString name= Form ("%d", i);
  TCanvas *c1= new TCanvas(name,title,10,10,600,600);
  c1->Clear();
  c1->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.15); 
  c1->SetRightMargin(0.05);
  c1->SetLeftMargin(0.14);
  if(blog)c1->SetLogy();

  hists[0]->SetLineColor(colors[0]); 
  hists[0]->SetMarkerColor(colors[0]);
  hists[0]->SetMarkerStyle(markerstyle[0]);
  if(bscale) hists[0]->Scale(1/hists[0]->Integral());

  hists[0]->SetMaximum(max);
  hists[0]->SetMinimum(min);
  hists[0]->GetXaxis()->SetTitle(xaxis);
  hists[0]->GetXaxis()->SetTitleSize(.08);
  hists[0]->GetXaxis()->SetTitleOffset(0.5);
  if(bscale) hists[0]->GetYaxis()->SetTitle("#Delta N/N");
  else hists[0]->GetYaxis()->SetTitle(yaxis);
  hists[0]->GetYaxis()->SetTitleSize(.07);
  hists[0]->SetTitle("");
  hists[0]->Draw();

 TLegend *leg = new TLegend(legxmin,legymax,legxmax,legymin, NULL,"brNDC");
  leg->SetBorderSize(0);	
  leg->SetFillStyle(0);
  gStyle->SetLegendTextSize(0.05);
  leg->SetHeader(leg_header);
  leg->AddEntry(hists[0],names[0],"lpe");

  for(unsigned int k=1; k<hists.size(); k++){
    hists[k]->SetLineColor(colors[k]); 
    hists[k]->SetMarkerColor(colors[k]);
    hists[k]->SetMarkerStyle(markerstyle[k]);
    if(bscale) hists[k]->Scale(1/hists[k]->Integral());
    hists[k]->Draw("same");
    leg->AddEntry(hists[k],names[k],"lpe");
  }

 
 
  leg->Draw();

  c1->Print(filename+".eps");

}

void save_paper_canvas (std::vector<TH2F*> hists,std::vector<TString> names,double max,TString drawopt,TString xaxis,TString yaxis,TString leg_header,TString filename="test",TString title="",bool blog=false,double legxmin=0.45,double legxmax=0.85,double legymin=0.68, double legymax=0.88 ){
  i++;
  TString name= Form ("%d", i);
  TCanvas *c1= new TCanvas(name,title,10,10,600,600);
  c1->Clear();
  c1->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.15); 
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.1);
  if(blog)c1->SetLogy();

  hists[0]->GetYaxis()->SetRangeUser(0,max);
  hists[0]->GetXaxis()->SetTitle(xaxis);
  hists[0]->GetXaxis()->SetTitleSize(.08);
  hists[0]->GetXaxis()->SetTitleOffset(0.5);
  hists[0]->GetYaxis()->SetTitle(yaxis);
  hists[0]->GetYaxis()->SetTitleSize(.04);
  hists[0]->SetTitle("");
  hists[0]->Draw(drawopt);

 TLegend *leg = new TLegend(legxmin,legymax,legxmax,legymin, NULL,"brNDC");
  leg->SetBorderSize(0);	
  leg->SetFillStyle(0);
  gStyle->SetLegendTextSize(0.05);
  leg->SetHeader(leg_header);
  leg->AddEntry(hists[0],names[0],"lpe");

  for(unsigned int k=1; k<hists.size(); k++){
    hists[k]->Draw("same");
    leg->AddEntry(hists[k],names[k],"lpe");
  }

 
 
  leg->Draw();

  c1->Print(filename+".eps");

}



std::vector<TH1F*> paper_gaussianfit(TH2F *rebinned_hist, TString filename="test"){
  Double_t nbins = rebinned_hist->GetXaxis()->GetNbins();
  Double_t xmin=rebinned_hist->GetXaxis()->GetBinCenter(1);
  Double_t xmax=rebinned_hist->GetXaxis()->GetBinCenter(nbins);


  //Get slice of NPV to see gaussian distribution for Mean and RMS
  TH1D *gaussian;
  TCanvas *c3= new TCanvas("c3","gaussian hist",10,10,700,900);
  TCanvas *gaussian_c = new TCanvas("gaussian_c","gaussian fit",10,10,700,900);
  TH1F *result_mean=new TH1F("result_rms","",nbins,xmin,xmax);
  TH1F *result_rms=new TH1F("result_rms","",nbins,xmin,xmax);
  TH1F *rms=new TH1F("rms","",nbins,xmin,xmax);
 

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
    /* gaussian_fit->SetParameter(0, 0); */
    /* gaussian_fit->SetParameter(1, 0.2); */
    gaussian->Fit(gaussian_fit);
    for(int i=0; i<4;i++){
      /* double lower_bound = gaussian_fit->GetParameter(1) -1.5*gaussian_fit->GetParameter(2); */
      /* double higher_bound = gaussian_fit->GetParameter(1)+1.5*gaussian_fit->GetParameter(2); */
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
    

    c3->Print(filename+"slice_"+str+".eps");
    
    if(berror) std::cout<<"Mean  "<<gaussian_fit->GetParameter(1)<<std::endl;
    if(berror) std::cout<<"Mean by GetMean "<<gaussian->GetMean()<<std::endl;
    if(berror) std::cout<<"RMS  "<<gaussian_fit->GetParameter(2)<<std::endl;
    
    result_mean->SetBinContent(p,gaussian_fit->GetParameter(1));
    result_mean->SetBinError(p,gaussian_fit->GetParError(1));
    
    result_rms->SetBinContent(p,gaussian_fit->GetParameter(2));
    result_rms->SetBinError(p,gaussian_fit->GetParError(2));
  }//over all slices
  std::vector<TH1F*> results ={result_mean,result_rms,rms};
  return results;
}


TH2F* paper_rebin(Double_t *bins_x,Double_t nbins,TH2F *hist, int miny, int maxy){
  
  
  
  TH2F *rebinned_hist = new TH2F("rebinned",hist->GetTitle(),nbins,bins_x,10,miny,maxy);
    
  TAxis *xaxis = hist->GetXaxis();
  TAxis *yaxis = hist->GetYaxis();
  
  for (int j=1; j<=yaxis->GetNbins();j++) {
    for (int i=1; i<=xaxis->GetNbins();i++) {
      rebinned_hist->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist->GetBinContent(i,j));
    }
  }
 
  return rebinned_hist;
}
