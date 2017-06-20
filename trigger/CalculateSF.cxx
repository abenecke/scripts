{
  gStyle->SetOptStat(0);

  TString outpath = "/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/";

  TFile* input_TTbar = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.MC.TTbar.root","READ");
  TFile* input_DY = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.MC.DYJets.root","READ");
  TFile* input_ST = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.MC.SingleTop.root","READ");
  TFile* input_WJ = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.MC.WJets.root","READ");
  TFile* input_DB = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.MC.Diboson.root","READ");
  TFile* input_QCD = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.MC.QCD.root","READ");
  TFile* input_DATA  = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_80X_v3/TagProbe/Optimization/35867fb_TriggerComb_Iso27_NonIso115/uhh2.AnalysisModuleRunner.DATA.DATA.root","READ");

  
  cout << "only non-iso trigger" << endl;
  //only non-iso trigger
  TH1D* h_noniso_pt_TTbar_before = (TH1D*)input_TTbar->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_noniso_pt_ST_before = (TH1D*)input_ST->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_noniso_pt_DY_before = (TH1D*)input_DY->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_noniso_pt_WJ_before = (TH1D*)input_WJ->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_noniso_pt_DB_before = (TH1D*)input_DB->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_noniso_pt_QCD_before = (TH1D*)input_QCD->Get("TagProbe_NoCuts/pt_ele_fine");
  h_noniso_pt_TTbar_before->Add(h_noniso_pt_ST_before);
  h_noniso_pt_TTbar_before->Add(h_noniso_pt_DY_before);
  h_noniso_pt_TTbar_before->Add(h_noniso_pt_WJ_before);
  h_noniso_pt_TTbar_before->Add(h_noniso_pt_DB_before);
  h_noniso_pt_TTbar_before->Add(h_noniso_pt_QCD_before);
  TH1D* h_noniso_pt_TTbar_after  = (TH1D*)input_TTbar->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_noniso_pt_ST_after = (TH1D*)input_ST->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_noniso_pt_DY_after = (TH1D*)input_DY->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_noniso_pt_WJ_after = (TH1D*)input_WJ->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_noniso_pt_DB_after = (TH1D*)input_DB->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_noniso_pt_QCD_after = (TH1D*)input_QCD->Get("TagProbe_Trigger/pt_ele_fine");
  h_noniso_pt_TTbar_after->Add(h_noniso_pt_ST_after);
  h_noniso_pt_TTbar_after->Add(h_noniso_pt_DY_after);
  h_noniso_pt_TTbar_after->Add(h_noniso_pt_WJ_after);
  h_noniso_pt_TTbar_after->Add(h_noniso_pt_DB_after);
  h_noniso_pt_TTbar_after->Add(h_noniso_pt_QCD_after);
  TH1D* h_noniso_pt_DATA_before  = (TH1D*)input_DATA->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_noniso_pt_DATA_after   = (TH1D*)input_DATA->Get("TagProbe_Trigger/pt_ele_fine");
  
    cout << "iso trigger regardless of what non-iso does" << endl;
  // iso trigger regardless of what non-iso does
  TH1D* h_iso_pt_TTbar_before = (TH1D*)input_TTbar->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_iso_pt_ST_before = (TH1D*)input_ST->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_iso_pt_DY_before = (TH1D*)input_DY->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_iso_pt_WJ_before = (TH1D*)input_WJ->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_iso_pt_DB_before = (TH1D*)input_DB->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_iso_pt_QCD_before = (TH1D*)input_QCD->Get("TagProbe_NoCuts/pt_ele_fine");
  h_iso_pt_TTbar_before->Add(h_iso_pt_ST_before);
  h_iso_pt_TTbar_before->Add(h_iso_pt_DY_before);
  h_iso_pt_TTbar_before->Add(h_iso_pt_WJ_before);
  h_iso_pt_TTbar_before->Add(h_iso_pt_DB_before);
  h_iso_pt_TTbar_before->Add(h_iso_pt_QCD_before);
  TH1D* h_iso_pt_TTbar_after  = (TH1D*)input_TTbar->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_iso_pt_ST_after = (TH1D*)input_ST->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_iso_pt_DY_after = (TH1D*)input_DY->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_iso_pt_WJ_after = (TH1D*)input_WJ->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_iso_pt_DB_after = (TH1D*)input_DB->Get("TagProbe_Trigger/pt_ele_fine");
  TH1D* h_iso_pt_QCD_after = (TH1D*)input_QCD->Get("TagProbe_Trigger/pt_ele_fine");
  h_iso_pt_TTbar_after->Add(h_iso_pt_ST_after);
  h_iso_pt_TTbar_after->Add(h_iso_pt_DY_after);
  h_iso_pt_TTbar_after->Add(h_iso_pt_WJ_after);
  h_iso_pt_TTbar_after->Add(h_iso_pt_DB_after);
  h_iso_pt_TTbar_after->Add(h_iso_pt_QCD_after);
  TH1D* h_iso_pt_DATA_before  = (TH1D*)input_DATA->Get("TagProbe_NoCuts/pt_ele_fine");
  TH1D* h_iso_pt_DATA_after   = (TH1D*)input_DATA->Get("TagProbe_Trigger/pt_ele_fine");
  
  cout << "Plateau of iso trigger" << endl;
  //plateau of iso trigger
  TH1D* h_iso_eta_TTbar_before = (TH1D*)input_TTbar->Get("TagProbe_Ele30to110/eta_ele_binned");
  TH1D* h_iso_eta_ST_before = (TH1D*)input_ST->Get("TagProbe_Ele30to110/eta_ele_binned");
  TH1D* h_iso_eta_DY_before = (TH1D*)input_DY->Get("TagProbe_Ele30to110/eta_ele_binned");
  TH1D* h_iso_eta_WJ_before = (TH1D*)input_WJ->Get("TagProbe_Ele30to110/eta_ele_binned");
  TH1D* h_iso_eta_DB_before = (TH1D*)input_DB->Get("TagProbe_Ele30to110/eta_ele_binned");
  TH1D* h_iso_eta_QCD_before = (TH1D*)input_QCD->Get("TagProbe_Ele30to110/eta_ele_binned");
  h_iso_eta_TTbar_before->Add(h_iso_eta_ST_before);
  h_iso_eta_TTbar_before->Add(h_iso_eta_DY_before);
  h_iso_eta_TTbar_before->Add(h_iso_eta_WJ_before);
  h_iso_eta_TTbar_before->Add(h_iso_eta_DB_before);
  h_iso_eta_TTbar_before->Add(h_iso_eta_QCD_before);
  TH1D* h_iso_eta_TTbar_after  = (TH1D*)input_TTbar->Get("TagProbe_30to110Plateau/eta_ele_binned");
  TH1D* h_iso_eta_ST_after = (TH1D*)input_ST->Get("TagProbe_30to110Plateau/eta_ele_binned");
  TH1D* h_iso_eta_DY_after = (TH1D*)input_DY->Get("TagProbe_30to110Plateau/eta_ele_binned");
  TH1D* h_iso_eta_WJ_after = (TH1D*)input_WJ->Get("TagProbe_30to110Plateau/eta_ele_binned");
  TH1D* h_iso_eta_DB_after = (TH1D*)input_DB->Get("TagProbe_30to110Plateau/eta_ele_binned");
  TH1D* h_iso_eta_QCD_after = (TH1D*)input_QCD->Get("TagProbe_30to110Plateau/eta_ele_binned");
  h_iso_eta_TTbar_after->Add(h_iso_eta_ST_after);
  h_iso_eta_TTbar_after->Add(h_iso_eta_DY_after);
  h_iso_eta_TTbar_after->Add(h_iso_eta_WJ_after);
  h_iso_eta_TTbar_after->Add(h_iso_eta_DB_after);
  h_iso_eta_TTbar_after->Add(h_iso_eta_QCD_after);
  TH1D* h_iso_eta_DATA_before  = (TH1D*)input_DATA->Get("TagProbe_Ele30to110/eta_ele_binned");
  TH1D* h_iso_eta_DATA_after   = (TH1D*)input_DATA->Get("TagProbe_30to110Plateau/eta_ele_binned");
    
  cout << "plateau of only non-iso trigger" << endl;
  //plateau of only non-iso trigger
  TH1D* h_noniso_eta_TTbar_before = (TH1D*)input_TTbar->Get("TagProbe_Ele110/eta_ele_binned");
  TH1D* h_noniso_eta_ST_before = (TH1D*)input_ST->Get("TagProbe_Ele110/eta_ele_binned");
  TH1D* h_noniso_eta_DY_before = (TH1D*)input_DY->Get("TagProbe_Ele110/eta_ele_binned");
  TH1D* h_noniso_eta_WJ_before = (TH1D*)input_WJ->Get("TagProbe_Ele110/eta_ele_binned");
  TH1D* h_noniso_eta_DB_before = (TH1D*)input_DB->Get("TagProbe_Ele110/eta_ele_binned");
  TH1D* h_noniso_eta_QCD_before = (TH1D*)input_QCD->Get("TagProbe_Ele110/eta_ele_binned");
  h_noniso_eta_TTbar_before->Add(h_noniso_eta_ST_before);
  h_noniso_eta_TTbar_before->Add(h_noniso_eta_DY_before);
  h_noniso_eta_TTbar_before->Add(h_noniso_eta_WJ_before);
  h_noniso_eta_TTbar_before->Add(h_noniso_eta_DB_before);
  h_noniso_eta_TTbar_before->Add(h_noniso_eta_QCD_before);
  TH1D* h_noniso_eta_TTbar_after  = (TH1D*)input_TTbar->Get("TagProbe_110Plateau/eta_ele_binned");
  TH1D* h_noniso_eta_ST_after = (TH1D*)input_ST->Get("TagProbe_110Plateau/eta_ele_binned");
  TH1D* h_noniso_eta_DY_after = (TH1D*)input_DY->Get("TagProbe_110Plateau/eta_ele_binned");
  TH1D* h_noniso_eta_WJ_after = (TH1D*)input_WJ->Get("TagProbe_110Plateau/eta_ele_binned");
  TH1D* h_noniso_eta_DB_after = (TH1D*)input_DB->Get("TagProbe_110Plateau/eta_ele_binned");
  TH1D* h_noniso_eta_QCD_after = (TH1D*)input_QCD->Get("TagProbe_110Plateau/eta_ele_binned");
  h_noniso_eta_TTbar_after->Add(h_noniso_eta_ST_after);
  h_noniso_eta_TTbar_after->Add(h_noniso_eta_DY_after);
  h_noniso_eta_TTbar_after->Add(h_noniso_eta_WJ_after);
  h_noniso_eta_TTbar_after->Add(h_noniso_eta_DB_after);
  h_noniso_eta_TTbar_after->Add(h_noniso_eta_QCD_after);
  TH1D* h_noniso_eta_DATA_before  = (TH1D*)input_DATA->Get("TagProbe_Ele110/eta_ele_binned");
  TH1D* h_noniso_eta_DATA_after   = (TH1D*)input_DATA->Get("TagProbe_110Plateau/eta_ele_binned");
  


  TGraphAsymmErrors* gr_iso_pt_TTbar_eff = new TGraphAsymmErrors(h_iso_pt_TTbar_after, h_iso_pt_TTbar_before);
  TGraphAsymmErrors* gr_iso_pt_DATA_eff = new TGraphAsymmErrors(h_iso_pt_DATA_after, h_iso_pt_DATA_before);
  gr_iso_pt_TTbar_eff->SetLineColor(2);
  TGraphAsymmErrors* gr_noniso_pt_TTbar_eff = new TGraphAsymmErrors(h_noniso_pt_TTbar_after, h_noniso_pt_TTbar_before);
  TGraphAsymmErrors* gr_noniso_pt_DATA_eff = new TGraphAsymmErrors(h_noniso_pt_DATA_after, h_noniso_pt_DATA_before);
  gr_noniso_pt_TTbar_eff->SetLineColor(2);
  TGraphAsymmErrors* gr_iso_eta_TTbar_eff = new TGraphAsymmErrors(h_iso_eta_TTbar_after, h_iso_eta_TTbar_before);
  TGraphAsymmErrors* gr_iso_eta_DATA_eff = new TGraphAsymmErrors(h_iso_eta_DATA_after, h_iso_eta_DATA_before);
  gr_iso_eta_TTbar_eff->SetLineColor(2);
  TGraphAsymmErrors* gr_noniso_eta_TTbar_eff = new TGraphAsymmErrors(h_noniso_eta_TTbar_after, h_noniso_eta_TTbar_before);
  TGraphAsymmErrors* gr_noniso_eta_DATA_eff = new TGraphAsymmErrors(h_noniso_eta_DATA_after, h_noniso_eta_DATA_before);
  gr_noniso_eta_TTbar_eff->SetLineColor(2);

  TCanvas* c_iso_pt = new TCanvas();
  gr_iso_pt_DATA_eff->Draw("AP");
  gr_iso_pt_DATA_eff->SetMinimum(0);
  gr_iso_pt_DATA_eff->SetMaximum(1);
  gr_iso_pt_TTbar_eff->Draw("P SAME");
  TLegend* leg_pt = new TLegend(0.5,0.4,0.9,0.6);
  leg_pt->AddEntry(gr_iso_pt_DATA_eff,"DATA");
  leg_pt->AddEntry(gr_iso_pt_TTbar_eff,"MC");
  leg_pt->Draw("lep");
  c_iso_pt->SaveAs(outpath + "TriggerEff_DATA_MC_pt.eps");

  TCanvas* c_iso_eta = new TCanvas();
  gr_iso_eta_DATA_eff->Draw("AP");
  gr_iso_eta_DATA_eff->SetMinimum(0);
  gr_iso_eta_DATA_eff->SetMaximum(1);
  gr_iso_eta_TTbar_eff->Draw("P SAME");
  TLegend* leg_eta_lowpt = new TLegend(0.5,0.4,0.9,0.6);
  leg_eta_lowpt->SetHeader("30 GeV #leq p_{T}^{ele} < 110 GeV");
  leg_eta_lowpt->AddEntry(gr_iso_eta_DATA_eff,"DATA");
  leg_eta_lowpt->AddEntry(gr_iso_eta_TTbar_eff,"MC");
  leg_eta_lowpt->Draw("lep");
  c_iso_eta->SaveAs(outpath + "TriggerEff_DATA_MC_eta_lowpt.eps");

  TCanvas* c_noniso_eta = new TCanvas();
  gr_noniso_eta_DATA_eff->Draw("AP");
  gr_noniso_eta_DATA_eff->SetMinimum(0);
  gr_noniso_eta_DATA_eff->SetMaximum(1);
  gr_noniso_eta_TTbar_eff->Draw("P SAME");
  TLegend* leg_eta_highpt = new TLegend(0.5,0.4,0.9,0.6);
  leg_eta_highpt->SetHeader("p_{T}^{ele} #geq 110 GeV");
  leg_eta_highpt->AddEntry(gr_iso_eta_DATA_eff,"DATA");
  leg_eta_highpt->AddEntry(gr_iso_eta_TTbar_eff,"MC");
  leg_eta_highpt->Draw("lep");
  c_iso_eta->SaveAs(outpath + "TriggerEff_DATA_MC_eta_highpt.eps");

  const int n_bins_iso_pt = gr_iso_pt_DATA_eff->GetN();
  const int n_bins_noniso_pt = gr_noniso_pt_DATA_eff->GetN();
  const int n_bins_iso_eta = gr_iso_eta_DATA_eff->GetN();
  const int n_bins_noniso_eta = gr_noniso_eta_DATA_eff->GetN();
  cout << "Current number of pt iso bins: " << n_bins_iso_pt << endl;
  cout << "Current number of pt noniso bins: " << n_bins_noniso_pt << endl;
  cout << "Current number of eta iso bins: " << n_bins_iso_eta << endl;
  cout << "Current number of eta noniso bins: " << n_bins_noniso_eta << endl;
  if(n_bins_iso_pt != 105) throw runtime_error("Adjust number of pt iso bins.");
  if(n_bins_noniso_pt != 105) throw runtime_error("Adjust number of pt noniso bins.");
  if(n_bins_iso_eta != 8) throw runtime_error("Adjust number of eta iso bins.");
  if(n_bins_noniso_eta != 8) throw runtime_error("Adjust number of eta noniso bins.");
  double SF_iso_pt_x[105], SF_iso_pt_y[105], SF_iso_pt_x_high[105], SF_iso_pt_x_low[105], SF_iso_pt_y_high[105], SF_iso_pt_y_low[105];
  double SF_noniso_pt_x[105], SF_noniso_pt_y[105], SF_noniso_pt_x_high[105], SF_noniso_pt_x_low[105], SF_noniso_pt_y_high[105], SF_noniso_pt_y_low[105];
  double SF_iso_eta_x[8], SF_iso_eta_y[8], SF_iso_eta_y_up[8], SF_iso_eta_y_dn[8], SF_iso_eta_x_high[8], SF_iso_eta_x_low[8], SF_iso_eta_y_high[8], SF_iso_eta_y_low[8];
  double SF_noniso_eta_x[8], SF_noniso_eta_y[8], SF_noniso_eta_y_up[8], SF_noniso_eta_y_dn[8], SF_noniso_eta_x_high[8], SF_noniso_eta_x_low[8], SF_noniso_eta_y_high[8], SF_noniso_eta_y_low[8];

  for(int i=0; i<n_bins_iso_pt; i++){
    double x_MC, y_MC, x_DATA, y_DATA;
    double MC_x_high, MC_x_low, MC_y_high, MC_y_low;
    double DATA_x_high, DATA_x_low, DATA_y_high, DATA_y_low;

    gr_iso_pt_TTbar_eff->GetPoint(i,x_MC,y_MC);
    gr_iso_pt_DATA_eff->GetPoint(i,x_DATA,y_DATA);

    MC_x_high = gr_iso_pt_TTbar_eff->GetErrorXhigh(i);
    MC_x_low = gr_iso_pt_TTbar_eff->GetErrorXlow(i);
    MC_y_high = gr_iso_pt_TTbar_eff->GetErrorYhigh(i);
    MC_y_low = gr_iso_pt_TTbar_eff->GetErrorYlow(i);

    DATA_x_high = gr_iso_pt_DATA_eff->GetErrorXhigh(i);
    DATA_x_low = gr_iso_pt_DATA_eff->GetErrorXlow(i);
    DATA_y_high = gr_iso_pt_DATA_eff->GetErrorYhigh(i);
    DATA_y_low = gr_iso_pt_DATA_eff->GetErrorYlow(i);

    //gaussian error propagation
    SF_iso_pt_x[i] = x_MC;
    SF_iso_pt_x_low[i] = MC_x_low;
    SF_iso_pt_x_high[i] = MC_x_high;
    SF_iso_pt_y[i] = y_DATA/y_MC;
    SF_iso_pt_y_low[i] = sqrt(pow(DATA_y_low/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_high,2));
    SF_iso_pt_y_high[i] = sqrt(pow(DATA_y_high/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_low,2));
  }

 for(int i=0; i<n_bins_noniso_pt; i++){
    double x_MC, y_MC, x_DATA, y_DATA;
    double MC_x_high, MC_x_low, MC_y_high, MC_y_low;
    double DATA_x_high, DATA_x_low, DATA_y_high, DATA_y_low;

    gr_noniso_pt_TTbar_eff->GetPoint(i,x_MC,y_MC);
    gr_noniso_pt_DATA_eff->GetPoint(i,x_DATA,y_DATA);

    MC_x_high = gr_noniso_pt_TTbar_eff->GetErrorXhigh(i);
    MC_x_low = gr_noniso_pt_TTbar_eff->GetErrorXlow(i);
    MC_y_high = gr_noniso_pt_TTbar_eff->GetErrorYhigh(i);
    MC_y_low = gr_noniso_pt_TTbar_eff->GetErrorYlow(i);

    DATA_x_high = gr_noniso_pt_DATA_eff->GetErrorXhigh(i);
    DATA_x_low = gr_noniso_pt_DATA_eff->GetErrorXlow(i);
    DATA_y_high = gr_noniso_pt_DATA_eff->GetErrorYhigh(i);
    DATA_y_low = gr_noniso_pt_DATA_eff->GetErrorYlow(i);

    //gaussian error propagation
    SF_noniso_pt_x[i] = x_MC;
    SF_noniso_pt_x_low[i] = MC_x_low;
    SF_noniso_pt_x_high[i] = MC_x_high;
    SF_noniso_pt_y[i] = y_DATA/y_MC;
    SF_noniso_pt_y_low[i] = sqrt(pow(DATA_y_low/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_high,2));
    SF_noniso_pt_y_high[i] = sqrt(pow(DATA_y_high/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_low,2));
  }

  for(int i=0; i<n_bins_iso_eta; i++){
    double x_MC, y_MC, x_DATA, y_DATA;
    double MC_x_high, MC_x_low, MC_y_high, MC_y_low;
    double DATA_x_high, DATA_x_low, DATA_y_high, DATA_y_low;

    gr_iso_eta_TTbar_eff->GetPoint(i,x_MC,y_MC);
    gr_iso_eta_DATA_eff->GetPoint(i,x_DATA,y_DATA);

    MC_x_high = gr_iso_eta_TTbar_eff->GetErrorXhigh(i);
    MC_x_low = gr_iso_eta_TTbar_eff->GetErrorXlow(i);
    MC_y_high = gr_iso_eta_TTbar_eff->GetErrorYhigh(i);
    MC_y_low = gr_iso_eta_TTbar_eff->GetErrorYlow(i);

    DATA_x_high = gr_iso_eta_DATA_eff->GetErrorXhigh(i);
    DATA_x_low = gr_iso_eta_DATA_eff->GetErrorXlow(i);
    DATA_y_high = gr_iso_eta_DATA_eff->GetErrorYhigh(i);
    DATA_y_low = gr_iso_eta_DATA_eff->GetErrorYlow(i);

    //gaussian error propagation
    SF_iso_eta_x[i] = x_MC;
    SF_iso_eta_x_low[i] = MC_x_low;
    SF_iso_eta_x_high[i] = MC_x_high;
    SF_iso_eta_y[i] = y_DATA/y_MC;
    SF_iso_eta_y_low[i] = sqrt(pow(DATA_y_low/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_high,2));
    SF_iso_eta_y_high[i] = sqrt(pow(DATA_y_high/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_low,2));
    SF_iso_eta_y_up[i] = SF_iso_eta_y[i] + SF_iso_eta_y_high[i];
    SF_iso_eta_y_dn[i] = SF_iso_eta_y[i] - SF_iso_eta_y_low[i];
  }

 for(int i=0; i<n_bins_noniso_eta; i++){
    double x_MC, y_MC, x_DATA, y_DATA;
    double MC_x_high, MC_x_low, MC_y_high, MC_y_low;
    double DATA_x_high, DATA_x_low, DATA_y_high, DATA_y_low;

    gr_noniso_eta_TTbar_eff->GetPoint(i,x_MC,y_MC);
    gr_noniso_eta_DATA_eff->GetPoint(i,x_DATA,y_DATA);

    MC_x_high = gr_noniso_eta_TTbar_eff->GetErrorXhigh(i);
    MC_x_low = gr_noniso_eta_TTbar_eff->GetErrorXlow(i);
    MC_y_high = gr_noniso_eta_TTbar_eff->GetErrorYhigh(i);
    MC_y_low = gr_noniso_eta_TTbar_eff->GetErrorYlow(i);

    DATA_x_high = gr_noniso_eta_DATA_eff->GetErrorXhigh(i);
    DATA_x_low = gr_noniso_eta_DATA_eff->GetErrorXlow(i);
    DATA_y_high = gr_noniso_eta_DATA_eff->GetErrorYhigh(i);
    DATA_y_low = gr_noniso_eta_DATA_eff->GetErrorYlow(i);

    //gaussian error propagation
    SF_noniso_eta_x[i] = x_MC;
    SF_noniso_eta_x_low[i] = MC_x_low;
    SF_noniso_eta_x_high[i] = MC_x_high;
    SF_noniso_eta_y[i] = y_DATA/y_MC;
    SF_noniso_eta_y_low[i] = sqrt(pow(DATA_y_low/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_high,2));
    SF_noniso_eta_y_high[i] = sqrt(pow(DATA_y_high/y_MC,2) + pow(y_DATA/y_MC/y_MC*MC_y_low,2));
    SF_noniso_eta_y_up[i] = SF_noniso_eta_y[i] + SF_noniso_eta_y_high[i];
    SF_noniso_eta_y_dn[i] = SF_noniso_eta_y[i] - SF_noniso_eta_y_low[i];
  }



  TGraphAsymmErrors* gr_iso_pt_SF = new TGraphAsymmErrors(n_bins_iso_pt, SF_iso_pt_x, SF_iso_pt_y, SF_iso_pt_x_low, SF_iso_pt_x_high, SF_iso_pt_y_low, SF_iso_pt_y_high);
  TCanvas* c_iso_pt_sf = new TCanvas();
  gr_iso_pt_SF->GetYaxis()->SetRangeUser(0,1);
  gr_iso_pt_SF->SetTitle("Electron trigger scale factors");
  gr_iso_pt_SF->GetXaxis()->SetTitle("p_{T}^{ele} [GeV]");
  gr_iso_pt_SF->GetYaxis()->SetTitle("DATA / MC");
  gr_iso_pt_SF->Draw("AP");

  /*
  TF1* const_fit_iso_pt = new TF1("const_fit_iso_pt", "[0]", 30,1000);
  gr_iso_pt_SF->Fit(const_fit_iso_pt,"SR");
  double SF_iso_pt = const_fit_iso_pt->GetParameter(0);
  double error_iso_pt = const_fit_iso_pt->GetParError(0);
  stringstream stream_iso_pt;
  stream_iso_pt << setprecision(4) << SF_iso_pt << " +- " << setprecision(2) << error_iso_pt;
  TString s_SF_iso_pt = stream_iso_pt.str();
  TLatex* text_iso_pt = new TLatex();
  text_iso_pt->SetTextColor(kRed);
  text_iso_pt->DrawLatex(65,0.75,s_SF_iso_pt);
  */
  c_iso_pt_sf->SaveAs(outpath + "ElectronTriggerSF_iso_pt.eps");

  
  TGraphAsymmErrors* gr_noniso_pt_SF = new TGraphAsymmErrors(n_bins_noniso_pt, SF_noniso_pt_x, SF_noniso_pt_y, SF_noniso_pt_x_low, SF_noniso_pt_x_high, SF_noniso_pt_y_low, SF_noniso_pt_y_high);
  TCanvas* c_noniso_pt_sf = new TCanvas();
  gr_noniso_pt_SF->GetYaxis()->SetRangeUser(0,1);
  gr_noniso_pt_SF->SetTitle("Electron trigger scale factors");
  gr_noniso_pt_SF->GetXaxis()->SetTitle("p_{T}^{ele} [GeV]");
  gr_noniso_pt_SF->GetYaxis()->SetTitle("DATA / MC");
  gr_noniso_pt_SF->Draw("AP");

  /*
  TF1* const_fit_noniso_pt = new TF1("const_fit_noniso_pt", "[0]", 110,1000);
  gr_noniso_pt_SF->Fit(const_fit_noniso_pt,"SR");
  double SF_noniso_pt = const_fit_noniso_pt->GetParameter(0);
  double error_noniso_pt = const_fit_noniso_pt->GetParError(0);
  stringstream stream_noniso_pt;
  stream_noniso_pt << setprecision(4) << SF_noniso_pt << " +- " << setprecision(2) << error_noniso_pt;
  TString s_SF_noniso_pt = stream_noniso_pt.str();
  TLatex* text_noniso_pt = new TLatex();
  text_noniso_pt->SetTextColor(kRed);
  text_noniso_pt->DrawLatex(65,0.75,s_SF_noniso_pt);
  */
  c_noniso_pt_sf->SaveAs(outpath + "ElectronTriggerSF_noniso_pt.eps");


  TGraphAsymmErrors* gr_iso_eta_SF = new TGraphAsymmErrors(n_bins_iso_eta, SF_iso_eta_x, SF_iso_eta_y, SF_iso_eta_x_low, SF_iso_eta_x_high, SF_iso_eta_y_low, SF_iso_eta_y_high);
  gr_iso_eta_SF->SetName("gr_lowpt_eta_SF");
  TGraphAsymmErrors* gr_iso_eta_SF_up = new TGraphAsymmErrors(n_bins_iso_eta, SF_iso_eta_x, SF_iso_eta_y_up, SF_iso_eta_x_low, SF_iso_eta_x_high, SF_iso_eta_y_low, SF_iso_eta_y_high); //only nominal y-values are changed
  gr_iso_eta_SF_up->SetName("gr_lowpt_eta_SF_up");
  TGraphAsymmErrors* gr_iso_eta_SF_dn = new TGraphAsymmErrors(n_bins_iso_eta, SF_iso_eta_x, SF_iso_eta_y_dn, SF_iso_eta_x_low, SF_iso_eta_x_high, SF_iso_eta_y_low, SF_iso_eta_y_high);
  gr_iso_eta_SF_dn->SetName("gr_lowpt_eta_SF_dn");
  TCanvas* c_iso_eta_sf = new TCanvas();
  gr_iso_eta_SF->GetYaxis()->SetRangeUser(0,1);
  gr_iso_eta_SF->SetTitle("Electron trigger scale factors, 30 GeV #leq p_{T}^{ele} < 110 GeV");
  gr_iso_eta_SF->GetXaxis()->SetTitle("#eta^{ele}");
  gr_iso_eta_SF->GetYaxis()->SetTitle("DATA / MC");
  gr_iso_eta_SF->Draw("AP");
  c_iso_eta_sf->SaveAs(outpath + "ElectronTriggerSF_iso_eta.eps");
  

  TGraphAsymmErrors* gr_noniso_eta_SF = new TGraphAsymmErrors(n_bins_noniso_eta, SF_noniso_eta_x, SF_noniso_eta_y, SF_noniso_eta_x_low, SF_noniso_eta_x_high, SF_noniso_eta_y_low, SF_noniso_eta_y_high);
  gr_noniso_eta_SF->SetName("gr_highpt_eta_SF");
  TGraphAsymmErrors* gr_noniso_eta_SF_up = new TGraphAsymmErrors(n_bins_noniso_eta, SF_noniso_eta_x, SF_noniso_eta_y_up, SF_noniso_eta_x_low, SF_noniso_eta_x_high, SF_noniso_eta_y_low, SF_noniso_eta_y_high);//only nominal y-values are changed
  gr_noniso_eta_SF_up->SetName("gr_highpt_eta_SF_up");
  TGraphAsymmErrors* gr_noniso_eta_SF_dn = new TGraphAsymmErrors(n_bins_noniso_eta, SF_noniso_eta_x, SF_noniso_eta_y_dn, SF_noniso_eta_x_low, SF_noniso_eta_x_high, SF_noniso_eta_y_low, SF_noniso_eta_y_high);
  gr_noniso_eta_SF_dn->SetName("gr_highpt_eta_SF_dn");
  TCanvas* c_noniso_eta_sf = new TCanvas();
  gr_noniso_eta_SF->GetYaxis()->SetRangeUser(0,1);
  gr_noniso_eta_SF->SetTitle("Electron trigger scale factors, p_{T}^{ele} #geq 110 GeV");
  gr_noniso_eta_SF->GetXaxis()->SetTitle("#eta^{ele}");
  gr_noniso_eta_SF->GetYaxis()->SetTitle("DATA / MC");
  gr_noniso_eta_SF->Draw("AP");

  c_noniso_eta_sf->SaveAs(outpath + "ElectronTriggerSF_noniso_eta.eps");
  



  
  TFile* out = new TFile(outpath + "ElectronTriggerSF.root","RECREATE");
  c_iso_eta_sf->Write();
  c_noniso_eta_sf->Write();
  gr_iso_eta_SF->Write();
  gr_noniso_eta_SF->Write();
  gr_iso_eta_SF_up->Write();
  gr_noniso_eta_SF_up->Write();
  gr_iso_eta_SF_dn->Write();
  gr_noniso_eta_SF_dn->Write();
  out->Close();
  








}
