//EffMacro.C
// define a function with 3 parameters
//Now we use the function:
// this function used fitf to fit a histogram
void pt_rel_deltaR() {
  gStyle->SetOptStat(0);

  // open a file and get a histogram
  TFile *s = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/data2016/uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime1200T_TPrimeToHT.root");
  TFile *d = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/data2016/uhh2.AnalysisModuleRunner.Data.Data_G.root");
  TFile *q = new TFile("/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/data2016/uhh2.AnalysisModuleRunner.MC.QCD.root");
 
  TH2F *Signal    = (TH2F*)s->Get("muon_topjet2/deltaRmin_ptrel");
  TH2F *Data    = (TH2F*)d->Get("muon_topjet2/deltaRmin_ptrel");
  TH2F *QCD      = (TH2F*)q->Get("muon_topjet2/deltaRmin_ptrel");

  // TH2F *Signal    = (TH2F*)s->Get("muon_topjet2/deltaRmin_ptrel");
  // TH2F *QCD      = (TH2F*)q->Get("muon_topjet2/deltaRmin_ptrel");

  // TH2F *Signal    = (TH2F*)s->Get("muon_tagger/deltaRmin_ptrel");
  // TH2F *QCD      = (TH2F*)q->Get("muon_tagger/deltaRmin_ptrel");

  // TH2F *Signal    = (TH2F*)s->Get("muon_chi2cut/deltaRmin_ptrel");
  // TH2F *QCD      = (TH2F*)q->Get("muon_chi2cut/deltaRmin_ptrel");


   TLine *line1 = new TLine(0,20,0.4,20);
   line1->SetLineWidth(2);
   TLine *line2 = new TLine(0.4,0,0.4,20);
    line2->SetLineWidth(2);

 Signal->SetMarkerStyle(2);
 Data->SetMarkerStyle(2);
 QCD->SetMarkerStyle(2);
 Signal->SetMarkerColor(kRed); 
 Data->SetMarkerColor(kRed); 
 QCD->SetMarkerColor(kBlue);

 Signal->Scale(1./(Signal->Integral()));
 Data->Scale(1./(Data->Integral()));
 QCD->Scale(1./(QCD->Integral()));

 
 // Signal->Draw();
 // Signal -> SetTitle("");
 // Signal->GetXaxis()->SetTitle("#Delta R_{min}(mu,jet)");
 // Signal->GetYaxis()->SetTitle("p_{T}^{rel}(mu,jet)");
 Data->Draw();
 Data -> SetTitle("");
 Data->GetXaxis()->SetTitle("#Delta R_{min}(mu,jet)");
 Data->GetYaxis()->SetTitle("p_{T}^{rel}(mu,jet)");
 // QCD->Draw("L same");
 line1 ->Draw("L same");
 line2->Draw("L same");



TLegend *leg1;
 leg1 = new TLegend(0.1,0.7,0.48,0.9);//x+0.1
 leg1->SetBorderSize(0);
 leg1->SetTextSize(0.035);
 leg1->SetFillColor(10);
 leg1->SetLineColor(1);
 leg1->SetTextFont(42);

 // leg1->AddEntry(Signal, "MZ'= 2500GeV, MT'= 1200GeV","P");
 leg1->AddEntry(Data, "Data","P");
 leg1->AddEntry(QCD, "QCD","P");

 //leg1->Draw();
}
