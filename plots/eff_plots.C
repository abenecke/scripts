void eff_plots(){
 // All root files TPrime to HT
  TFile *Z1500T1200HT = new TFile("uhh2.AnalysisModuleRunner.MC.MC_ZPrime1500ToTPrime1200T_TPrimeToHT.root");
  TDirectory *Z1500T1200HT_input = Z1500T1200HT -> GetDirectory("input_eff");
  TDirectory *Z1500T1200HT_Lepton = Z1500T1200HT -> GetDirectory("eff_lep1");
  TDirectory *Z1500T1200HT_Topjet2 = Z1500T1200HT -> GetDirectory("eff_topjet2");
  TDirectory *Z1500T1200HT_twodcut = Z1500T1200HT -> GetDirectory("eff_twodcut");
  TDirectory *Z1500T1200HT_reliso = Z1500T1200HT -> GetDirectory("eff_reliso");
  TDirectory *Z1500T1200HT_higgstag = Z1500T1200HT -> GetDirectory("eff_higgstag");
  TDirectory *Z1500T1200HT_ZWtag = Z1500T1200HT -> GetDirectory("eff_zwtag");
  TDirectory *Z1500T1200HT_toptag = Z1500T1200HT -> GetDirectory("eff_toptag");
  TDirectory *Z1500T1200HT_chi2cut = Z1500T1200HT -> GetDirectory("eff_chi2cut");
  TDirectory *Z1500T1200HT_met = Z1500T1200HT -> GetDirectory("eff_met");
  TDirectory *Z1500T1200HT_ht = Z1500T1200HT -> GetDirectory("eff_ht");


  TFile *Z2000T1200HT = new TFile("uhh2.AnalysisModuleRunner.MC.MC_ZPrime2000ToTPrime1200T_TPrimeToHT.root");
  TDirectory *Z2000T1200HT_input = Z2000T1200HT -> GetDirectory("input_eff");
  TDirectory *Z2000T1200HT_Lepton = Z2000T1200HT -> GetDirectory("eff_lep1");
  TDirectory *Z2000T1200HT_Topjet2 = Z2000T1200HT -> GetDirectory("eff_topjet2");
  TDirectory *Z2000T1200HT_twodcut = Z2000T1200HT -> GetDirectory("eff_twodcut");
  TDirectory *Z2000T1200HT_reliso = Z2000T1200HT -> GetDirectory("eff_reliso");
  TDirectory *Z2000T1200HT_higgstag = Z2000T1200HT -> GetDirectory("eff_higgstag");
  TDirectory *Z2000T1200HT_ZWtag = Z2000T1200HT -> GetDirectory("eff_zwtag");
  TDirectory *Z2000T1200HT_toptag = Z2000T1200HT -> GetDirectory("eff_toptag");
  TDirectory *Z2000T1200HT_chi2cut = Z2000T1200HT -> GetDirectory("eff_chi2cut");
TDirectory *Z2000T1200HT_met = Z2000T1200HT -> GetDirectory("eff_met");
TDirectory *Z2000T1200HT_ht = Z2000T1200HT -> GetDirectory("eff_ht");

 TFile *Z2500T1500HT = new TFile("uhh2.AnalysisModuleRunner.MC.MC_ZPrime2500ToTPrime1500T_TPrimeToHT.root");
  TDirectory *Z2500T1500HT_input = Z2500T1500HT -> GetDirectory("input_eff");
  TDirectory *Z2500T1500HT_Lepton = Z2500T1500HT -> GetDirectory("eff_lep1");
  TDirectory *Z2500T1500HT_Topjet2 = Z2500T1500HT -> GetDirectory("eff_topjet2");
  TDirectory *Z2500T1500HT_twodcut = Z2500T1500HT -> GetDirectory("eff_twodcut");
  TDirectory *Z2500T1500HT_reliso = Z2500T1500HT -> GetDirectory("eff_reliso");
  TDirectory *Z2500T1500HT_higgstag = Z2500T1500HT -> GetDirectory("eff_higgstag");
  TDirectory *Z2500T1500HT_ZWtag = Z2500T1500HT -> GetDirectory("eff_zwtag");
  TDirectory *Z2500T1500HT_toptag = Z2500T1500HT -> GetDirectory("eff_toptag");
  TDirectory *Z2500T1500HT_chi2cut = Z2500T1500HT -> GetDirectory("eff_chi2cut");
 TDirectory *Z2500T1500HT_met = Z2500T1500HT -> GetDirectory("eff_met");
 TDirectory *Z2500T1500HT_ht = Z2500T1500HT -> GetDirectory("eff_ht");

 TFile *Background = new TFile("uhh2.AnalysisModuleRunner.MC.QCD.root");
  TDirectory *Background_input = Background -> GetDirectory("input_eff");
  TDirectory *Background_Lepton = Background -> GetDirectory("eff_lep1");
  TDirectory *Background_Topjet2 = Background -> GetDirectory("eff_topjet2");
  TDirectory *Background_twodcut = Background -> GetDirectory("eff_twodcut");
  TDirectory *Background_reliso = Background -> GetDirectory("eff_reliso");
  TDirectory *Background_higgstag = Background -> GetDirectory("eff_higgstag");
  TDirectory *Background_ZWtag = Background -> GetDirectory("eff_zwtag");
  TDirectory *Background_toptag = Background -> GetDirectory("eff_toptag");
  TDirectory *Background_chi2cut = Background -> GetDirectory("eff_chi2cut");
  TDirectory *Background_met = Background -> GetDirectory("eff_met");
  TDirectory *Background_ht = Background -> GetDirectory("eff_ht");
 

 TFile *ttbar = new TFile("uhh2.AnalysisModuleRunner.MC.TTbar.root");
  TDirectory *ttbar_input = ttbar -> GetDirectory("input_eff");
  TDirectory *ttbar_Lepton = ttbar -> GetDirectory("eff_lep1");
  TDirectory *ttbar_Topjet2 = ttbar -> GetDirectory("eff_topjet2");
  TDirectory *ttbar_twodcut = ttbar -> GetDirectory("eff_twodcut");
  TDirectory *ttbar_reliso = ttbar -> GetDirectory("eff_reliso");
  TDirectory *ttbar_higgstag = ttbar -> GetDirectory("eff_higgstag");
  TDirectory *ttbar_ZWtag = ttbar -> GetDirectory("eff_zwtag");
  TDirectory *ttbar_toptag = ttbar -> GetDirectory("eff_toptag");
  TDirectory *ttbar_chi2cut = ttbar -> GetDirectory("eff_chi2cut");
 TDirectory *ttbar_met = ttbar -> GetDirectory("eff_met");
 TDirectory *ttbar_ht = ttbar -> GetDirectory("eff_ht");
 

 TFile *wjets = new TFile("uhh2.AnalysisModuleRunner.MC.other.root");
  TDirectory *wjets_input = wjets -> GetDirectory("input_eff");
  TDirectory *wjets_Lepton = wjets -> GetDirectory("eff_lep1");
  TDirectory *wjets_Topjet2 = wjets -> GetDirectory("eff_topjet2");
  TDirectory *wjets_twodcut = wjets -> GetDirectory("eff_twodcut");
  TDirectory *wjets_reliso = wjets -> GetDirectory("eff_reliso");
  TDirectory *wjets_higgstag = wjets -> GetDirectory("eff_higgstag");
  TDirectory *wjets_ZWtag = wjets -> GetDirectory("eff_zwtag");
  TDirectory *wjets_toptag = wjets -> GetDirectory("eff_toptag");
  TDirectory *wjets_chi2cut = wjets -> GetDirectory("eff_chi2cut");
 TDirectory *wjets_met = wjets -> GetDirectory("eff_met");
 TDirectory *wjets_ht = wjets -> GetDirectory("eff_ht");
 

  /*****************************          Eff Hists       (SELECTIONS)                        ******************************/


 /*****************************      Ht           ******************************/
  //Ht Z'1500 T'1200
 TH1D *Selection_eff_HT = new TH1D("Selection_eff_HT","Selection eff.",8,0,8);

 //Get all bin content
 TH1D *eff_input_HT  = (TH1D*)Z1500T1200HT_input ->Get("eff;1");
 Float_t Input_HT = eff_input_HT->GetBinContent(2);
 TH1D *eff_Lepton_HT  = (TH1D*)Z1500T1200HT_Lepton->Get("eff;1");
 Float_t Lepton_HT = eff_Lepton_HT->GetBinContent(2);
 TH1D *eff_Topjet2_HT  = (TH1D*)Z1500T1200HT_Topjet2->Get("eff;1");
 Float_t Topjet2_HT = eff_Topjet2_HT->GetBinContent(2);
 TH1D *eff_twodcut_HT  = (TH1D*)Z1500T1200HT_twodcut->Get("eff;1");
 Float_t twodcut_HT =eff_twodcut_HT ->GetBinContent(2);
 TH1D *eff_reliso_HT  = (TH1D*)Z1500T1200HT_reliso->Get("eff;1");
 Float_t reliso_HT =eff_reliso_HT ->GetBinContent(2);
 TH1D *eff_higgstag_HT  = (TH1D*)Z1500T1200HT_higgstag->Get("eff;1");
 Float_t higgstag_HT = eff_higgstag_HT->GetBinContent(2);
 TH1D *eff_zwtag_HT  = (TH1D*)Z1500T1200HT_ZWtag->Get("eff;1");
 Float_t zwtag_HT = eff_zwtag_HT->GetBinContent(2);
 TH1D *eff_toptag_HT  = (TH1D*)Z1500T1200HT_toptag->Get("eff;1");
 Float_t toptag_HT = eff_toptag_HT->GetBinContent(2);
 TH1D *eff_chi2cut_HT  = (TH1D*)Z1500T1200HT_chi2cut->Get("eff;1");
 Float_t chi2cut_HT = eff_chi2cut_HT->GetBinContent(2);
 TH1D *eff_met_HT  = (TH1D*)Z1500T1200HT_met->Get("eff;1");
 Float_t met_HT = eff_met_HT->GetBinContent(2);
 TH1D *eff_ht_HT  = (TH1D*)Z1500T1200HT_ht->Get("eff;1");
 Float_t ht_HT = eff_ht_HT->GetBinContent(2);


 //Fill Histogram
 Selection_eff_HT->Fill(" Input",Input_HT/Input_HT);
Selection_eff_HT->Fill(" 1 muon",Lepton_HT/Input_HT);
 Selection_eff_HT->Fill(" AK8 >= 2",Topjet2_HT/Input_HT);
 Selection_eff_HT->Fill(" QCD supression",twodcut_HT/Input_HT);
 //Selection_eff_HT->Fill(" reliso",reliso_HT/Input_HT);
 Selection_eff_HT->Fill("H tag",higgstag_HT/Input_HT);
 Selection_eff_HT->Fill(" Z/W tag",zwtag_HT/Input_HT);
 Selection_eff_HT->Fill(" top tag",toptag_HT/Input_HT);
 Selection_eff_HT->Fill(" Chi2 < 50",chi2cut_HT/Input_HT);
 // Selection_eff_HT->Fill("MET>50",met_HT/Input_HT);
 //Selection_eff_HT->Fill("HT>800",ht_HT/Input_HT);

 //Attributes
 Selection_eff_HT->SetLineColor(600); 
 Selection_eff_HT->GetXaxis()->SetTitle("");
 Selection_eff_HT->GetYaxis()->SetTitle("");
 Selection_eff_HT->GetXaxis()->SetLabelSize(0.05);
/*****************************      Ht           ******************************/
  //Ht Z'2000 T'1200
 TH1D *Selection_eff2000_HT = new TH1D("Selection_eff2000_HT","Selection eff. Ht (Z' 2000 T' 1200)",8,0,8);

 //Get all bin content
 eff_input_HT  = (TH1D*)Z2000T1200HT_input->Get("eff;1");
 Input_HT = eff_input_HT->GetBinContent(2);
 eff_Lepton_HT  = (TH1D*)Z2000T1200HT_Lepton->Get("eff;1");
 Lepton_HT = eff_Lepton_HT->GetBinContent(2);
 eff_Topjet2_HT  = (TH1D*)Z2000T1200HT_Topjet2->Get("eff;1");
 Topjet2_HT = eff_Topjet2_HT->GetBinContent(2);
 eff_twodcut_HT  = (TH1D*)Z2000T1200HT_twodcut->Get("eff;1");
 twodcut_HT =eff_twodcut_HT ->GetBinContent(2);
 eff_reliso_HT  = (TH1D*)Z2000T1200HT_reliso->Get("eff;1");
 reliso_HT =eff_reliso_HT ->GetBinContent(2);
 eff_higgstag_HT  = (TH1D*)Z2000T1200HT_higgstag->Get("eff;1");
 higgstag_HT = eff_higgstag_HT->GetBinContent(2);
 eff_zwtag_HT  = (TH1D*)Z2000T1200HT_ZWtag->Get("eff;1");
 zwtag_HT = eff_zwtag_HT->GetBinContent(2);
 eff_toptag_HT  = (TH1D*)Z2000T1200HT_toptag->Get("eff;1");
 toptag_HT = eff_toptag_HT->GetBinContent(2);
 eff_chi2cut_HT  = (TH1D*)Z2000T1200HT_chi2cut->Get("eff;1");
 chi2cut_HT = eff_chi2cut_HT->GetBinContent(2);
eff_met_HT  = (TH1D*)Z2000T1200HT_met->Get("eff;1");
 met_HT = eff_met_HT->GetBinContent(2);
eff_ht_HT  = (TH1D*)Z2000T1200HT_ht->Get("eff;1");
 ht_HT = eff_ht_HT->GetBinContent(2);

 //Fill Histogram
 Selection_eff2000_HT->Fill(" Input",Input_HT/Input_HT);
 Selection_eff2000_HT->Fill(" 1 Muon",Lepton_HT/Input_HT);
 Selection_eff2000_HT->Fill(" AK8 >= 2",Topjet2_HT/Input_HT);
 Selection_eff2000_HT->Fill("QCD supression",twodcut_HT/Input_HT);
 //Selection_eff2000_HT->Fill(" reliso",reliso_HT/Input_HT);
 Selection_eff2000_HT->Fill("H tag",higgstag_HT/Input_HT);
 Selection_eff2000_HT->Fill(" Z/W tag",zwtag_HT/Input_HT);
 Selection_eff2000_HT->Fill(" top tag",toptag_HT/Input_HT);
 Selection_eff2000_HT->Fill(" Chi2 < 50",chi2cut_HT/Input_HT);
 //Selection_eff2000_HT->Fill("MET>50",met_HT/Input_HT);
 // Selection_eff2000_HT->Fill("HT>800",ht_HT/Input_HT);
 //Attributes
 Selection_eff2000_HT->SetLineColor(432); 
 Selection_eff2000_HT->GetXaxis()->SetTitle("Selections");
 Selection_eff2000_HT->GetYaxis()->SetTitle("");

/*****************************      Ht           ******************************/
  //Ht Z'2500 T'1500
 TH1D *Selection_eff2500_HT = new TH1D("Selection_eff2500_HT","Selection eff. Ht (Z' 2500 T' 1500)",8,0,8);

 //Get all bin content
 eff_input_HT  = (TH1D*)Z2500T1500HT_input->Get("eff;1");
 Input_HT = eff_input_HT->GetBinContent(2);
 eff_Lepton_HT  = (TH1D*)Z2500T1500HT_Lepton->Get("eff;1");
 Lepton_HT = eff_Lepton_HT->GetBinContent(2);
 eff_Topjet2_HT  = (TH1D*)Z2500T1500HT_Topjet2->Get("eff;1");
 Topjet2_HT = eff_Topjet2_HT->GetBinContent(2);
 eff_twodcut_HT  = (TH1D*)Z2500T1500HT_twodcut->Get("eff;1");
 twodcut_HT =eff_twodcut_HT ->GetBinContent(2);
 eff_reliso_HT  = (TH1D*)Z2500T1500HT_reliso->Get("eff;1");
 reliso_HT =eff_reliso_HT ->GetBinContent(2);
 eff_higgstag_HT  = (TH1D*)Z2500T1500HT_higgstag->Get("eff;1");
 higgstag_HT = eff_higgstag_HT->GetBinContent(2);
 eff_zwtag_HT  = (TH1D*)Z2500T1500HT_ZWtag->Get("eff;1");
 zwtag_HT = eff_zwtag_HT->GetBinContent(2);
 eff_toptag_HT  = (TH1D*)Z2500T1500HT_toptag->Get("eff;1");
 toptag_HT = eff_toptag_HT->GetBinContent(2);
 eff_chi2cut_HT  = (TH1D*)Z2500T1500HT_chi2cut->Get("eff;1");
 chi2cut_HT = eff_chi2cut_HT->GetBinContent(2);
 eff_met_HT  = (TH1D*)Z2500T1500HT_met->Get("eff;1");
 met_HT = eff_met_HT->GetBinContent(2);
 eff_ht_HT  = (TH1D*)Z2500T1500HT_ht->Get("eff;1");
 ht_HT = eff_ht_HT->GetBinContent(2);

 //Fill Histogram
 Selection_eff2500_HT->Fill(" Input",Input_HT/Input_HT);
Selection_eff2500_HT->Fill(" Lepton",Lepton_HT/Input_HT);
 Selection_eff2500_HT->Fill(" AK8 >= 2",Topjet2_HT/Input_HT);
 Selection_eff2500_HT->Fill(" QCD supression",twodcut_HT/Input_HT);
 //Selection_eff2500_HT->Fill(" reliso",reliso_HT/Input_HT);
 Selection_eff2500_HT->Fill("H tag",higgstag_HT/Input_HT);
 Selection_eff2500_HT->Fill(" Z/W tag",zwtag_HT/Input_HT);
 Selection_eff2500_HT->Fill(" top tag",toptag_HT/Input_HT);
 Selection_eff2500_HT->Fill(" Chi2 < 50",chi2cut_HT/Input_HT);
 // Selection_eff2500_HT->Fill("MET>50",met_HT/Input_HT);
 //Selection_eff2500_HT->Fill("HT>800",ht_HT/Input_HT);
 //Attributes
 Selection_eff2500_HT->SetLineColor(603); 
 Selection_eff2500_HT->GetXaxis()->SetTitle("Selections");
 Selection_eff2500_HT->GetYaxis()->SetTitle("");



/*****************************      Background           ******************************/
  //QCD
 TH1D *Selection_eff_BG = new TH1D("Selection_eff_BG","Selection eff. Background",8,0,8);

 //Get all bin content
 TH1D *eff_input_BG  = (TH1D*)Background_input->Get("eff;1");
 Float_t Input_BG = eff_input_BG->GetBinContent(2);
 TH1D *eff_Lepton_BG  = (TH1D*)Background_Lepton->Get("eff;1");
 Float_t Lepton_BG = eff_Lepton_BG->GetBinContent(2);
 TH1D *eff_Topjet2_BG  = (TH1D*)Background_Topjet2->Get("eff;1");
 Float_t Topjet2_BG = eff_Topjet2_BG->GetBinContent(2);
 TH1D *eff_twodcut_BG  = (TH1D*)Background_twodcut->Get("eff;1");
 Float_t twodcut_BG =eff_twodcut_BG ->GetBinContent(2);
 TH1D *eff_reliso_BG  = (TH1D*)Background_reliso->Get("eff;1");
 Float_t reliso_BG =eff_reliso_BG ->GetBinContent(2);
 TH1D *eff_higgstag_BG  = (TH1D*)Background_higgstag->Get("eff;1");
 Float_t higgstag_BG = eff_higgstag_BG->GetBinContent(2);
 TH1D *eff_zwtag_BG  = (TH1D*)Background_ZWtag->Get("eff;1");
 Float_t zwtag_BG = eff_zwtag_BG->GetBinContent(2);
 TH1D *eff_toptag_BG  = (TH1D*)Background_toptag->Get("eff;1");
 Float_t toptag_BG = eff_toptag_BG->GetBinContent(2);
 TH1D *eff_chi2cut_BG  = (TH1D*)Background_chi2cut->Get("eff;1");
 Float_t chi2cut_BG = eff_chi2cut_BG->GetBinContent(2);
TH1D *eff_met_BG  = (TH1D*)Background_met->Get("eff;1");
 Float_t met_BG = eff_met_BG->GetBinContent(2);
TH1D *eff_ht_BG  = (TH1D*)Background_ht->Get("eff;1");
 Float_t ht_BG = eff_ht_BG->GetBinContent(2);

 //Fill Histogram
 Selection_eff_BG->Fill(" Input",Input_BG/Input_BG);
 Selection_eff_BG->Fill(" 1 Muon",Lepton_BG/Input_BG);
 Selection_eff_BG->Fill(" AK8 >= 2",Topjet2_BG/Input_BG);
 Selection_eff_BG->Fill(" QCD supression",twodcut_BG/Input_BG);
 //Selection_eff_BG->Fill(" reliso",reliso_BG/Input_BG);
 Selection_eff_BG->Fill("H tag",higgstag_BG/Input_BG);
 Selection_eff_BG->Fill(" Z/W tag",zwtag_BG/Input_BG);
 Selection_eff_BG->Fill(" top tag",toptag_BG/Input_BG);
 Selection_eff_BG->Fill(" Chi2 < 50",chi2cut_BG/Input_BG);
 // Selection_eff_BG->Fill("met>50",met_BG/Input_BG);
 // Selection_eff_BG->Fill("ht>800",ht_BG/Input_BG);

 //Attributes
 Selection_eff_BG->SetLineColor(880); 
 Selection_eff_BG->GetXaxis()->SetTitle("Selections");
 Selection_eff_BG->GetYaxis()->SetTitle("");


/*****************************      Background           ******************************/
  //TTbar
 TH1D *Selection_eff_tt = new TH1D("Selection_eff_tt","Selection eff. TTbar",8,0,8);
//Get all bin content
 TH1D *eff_input_ttbar  = (TH1D*)ttbar_input->Get("eff;1");
 Float_t Input_ttbar = eff_input_ttbar->GetBinContent(2);
 TH1D *eff_Lepton_ttbar  = (TH1D*)ttbar_Lepton->Get("eff;1");
 Float_t Lepton_ttbar = eff_Lepton_ttbar->GetBinContent(2);
 TH1D *eff_Topjet2_ttbar  = (TH1D*)ttbar_Topjet2->Get("eff;1");
 Float_t Topjet2_ttbar = eff_Topjet2_ttbar->GetBinContent(2);
 TH1D *eff_twodcut_ttbar  = (TH1D*)ttbar_twodcut->Get("eff;1");
 Float_t twodcut_ttbar =eff_twodcut_ttbar ->GetBinContent(2);
 TH1D *eff_reliso_ttbar  = (TH1D*)ttbar_reliso->Get("eff;1");
 Float_t reliso_ttbar =eff_reliso_ttbar ->GetBinContent(2);
 TH1D *eff_higgstag_ttbar  = (TH1D*)ttbar_higgstag->Get("eff;1");
 Float_t higgstag_ttbar = eff_higgstag_ttbar->GetBinContent(2);
 TH1D *eff_zwtag_ttbar  = (TH1D*)ttbar_ZWtag->Get("eff;1");
 Float_t zwtag_ttbar = eff_zwtag_ttbar->GetBinContent(2);
 TH1D *eff_toptag_ttbar  = (TH1D*)ttbar_toptag->Get("eff;1");
 Float_t toptag_ttbar = eff_toptag_ttbar->GetBinContent(2);
 TH1D *eff_chi2cut_ttbar  = (TH1D*)ttbar_chi2cut->Get("eff;1");
 Float_t chi2cut_ttbar = eff_chi2cut_ttbar->GetBinContent(2);
  TH1D *eff_met_ttbar  = (TH1D*)ttbar_met->Get("eff;1");
 Float_t met_ttbar = eff_met_ttbar->GetBinContent(2);
  TH1D *eff_ht_ttbar  = (TH1D*)ttbar_ht->Get("eff;1");
 Float_t ht_ttbar = eff_ht_ttbar->GetBinContent(2);


 //Fill Histogram
 Selection_eff_tt->Fill(" Input",Input_ttbar/Input_ttbar);
 Selection_eff_tt->Fill(" 1 Muon",Lepton_ttbar/Input_ttbar);
 Selection_eff_tt->Fill(" AK8 >= 2",Topjet2_ttbar/Input_ttbar);
 Selection_eff_tt->Fill(" QCD supression",twodcut_ttbar/Input_ttbar);
 //Selection_eff_tt->Fill(" reliso",reliso_ttbar/Input_ttbar);
 Selection_eff_tt->Fill("H tag",higgstag_ttbar/Input_ttbar);
 Selection_eff_tt->Fill(" Z/W tag",zwtag_ttbar/Input_ttbar);
 Selection_eff_tt->Fill(" top tag",toptag_ttbar/Input_ttbar);
 Selection_eff_tt->Fill(" Chi2 < 50",chi2cut_ttbar/Input_ttbar);
 //Selection_eff_tt->Fill("met>50",met_ttbar/Input_ttbar);
 //Selection_eff_tt->Fill("ht>800",ht_ttbar/Input_ttbar);

 //Attributes
 Selection_eff_tt->SetLineColor(625); 
 Selection_eff_tt->GetXaxis()->SetTitle("Selections");
 Selection_eff_tt->GetYaxis()->SetTitle("");

/*****************************      Background           ******************************/
  //Wjets
 TH1D *Selection_eff_wjets = new TH1D("Selection_eff_wjets","Selection eff. Wjets",8,0,8);
//Get all bin content
 TH1D *eff_input_wjets  = (TH1D*)wjets_input->Get("eff;1");
 Float_t Input_wjets = eff_input_wjets->GetBinContent(2);
 TH1D *eff_Lepton_wjets  = (TH1D*)wjets_Lepton->Get("eff;1");
 Float_t Lepton_wjets = eff_Lepton_wjets->GetBinContent(2);
 TH1D *eff_Topjet2_wjets  = (TH1D*)wjets_Topjet2->Get("eff;1");
 Float_t Topjet2_wjets = eff_Topjet2_wjets->GetBinContent(2);
 TH1D *eff_twodcut_wjets  = (TH1D*)wjets_twodcut->Get("eff;1");
 Float_t twodcut_wjets =eff_twodcut_wjets ->GetBinContent(2);
 TH1D *eff_reliso_wjets  = (TH1D*)wjets_reliso->Get("eff;1");
 Float_t reliso_wjets =eff_reliso_wjets ->GetBinContent(2);
 TH1D *eff_higgstag_wjets  = (TH1D*)wjets_higgstag->Get("eff;1");
 Float_t higgstag_wjets = eff_higgstag_wjets->GetBinContent(2);
 TH1D *eff_zwtag_wjets  = (TH1D*)wjets_ZWtag->Get("eff;1");
 Float_t zwtag_wjets = eff_zwtag_wjets->GetBinContent(2);
 TH1D *eff_toptag_wjets  = (TH1D*)wjets_toptag->Get("eff;1");
 Float_t toptag_wjets = eff_toptag_wjets->GetBinContent(2);
 TH1D *eff_chi2cut_wjets  = (TH1D*)wjets_chi2cut->Get("eff;1");
 Float_t chi2cut_wjets = eff_chi2cut_wjets->GetBinContent(2);
  TH1D *eff_met_wjets  = (TH1D*)wjets_met->Get("eff;1");
 Float_t met_wjets = eff_met_wjets->GetBinContent(2);
 TH1D *eff_ht_wjets  = (TH1D*)wjets_ht->Get("eff;1");
 Float_t ht_wjets = eff_ht_wjets->GetBinContent(2);
 

 //Fill Histogram
 Selection_eff_wjets->Fill(" Input",Input_wjets/Input_wjets);
 Selection_eff_wjets->Fill(" 1 Muon",Lepton_wjets/Input_wjets);
 Selection_eff_wjets->Fill(" AK8 >= 2",Topjet2_wjets/Input_wjets);
 Selection_eff_wjets->Fill(" QCD supression",twodcut_wjets/Input_wjets);
 //Selection_eff_wjets->Fill(" reliso",reliso_wjets/Input_wjets);
 Selection_eff_wjets->Fill("H tag",higgstag_wjets/Input_wjets);
 Selection_eff_wjets->Fill(" Z/W tag",zwtag_wjets/Input_wjets);
 Selection_eff_wjets->Fill(" top tag",toptag_wjets/Input_wjets);
 Selection_eff_wjets->Fill(" Chi2 < 50",chi2cut_wjets/Input_wjets);
 //Selection_eff_wjets->Fill("met>50",met_wjets/Input_wjets);
 //Selection_eff_wjets->Fill("ht>800",ht_wjets/Input_wjets);

 //Awjetsributes
 Selection_eff_wjets->SetLineColor(408); 
 Selection_eff_wjets->GetXaxis()->SetTitle("Selections");
 Selection_eff_wjets->GetYaxis()->SetTitle("");


 

 

  
 /*****************************         Write to file                   ******************************/
 TFile *f= new TFile("Eff.root","RECREATE");


Selection_eff_HT ->Write();
Selection_eff2000_HT ->Write();
Selection_eff2500_HT ->Write();
Selection_eff_BG ->Write();
Selection_eff_tt ->Write();
Selection_eff_wjets ->Write();
 f->Close();

 TCanvas* c1 = new TCanvas("c1", "Selection Efficency", 800,800);

 Selection_eff_HT->SetStats(0);
 Selection_eff_HT -> SetLineWidth(2);
Selection_eff2000_HT -> SetLineWidth(2);
Selection_eff2500_HT -> SetLineWidth(2);
 Selection_eff_BG -> SetLineWidth(2);
 Selection_eff_BG->SetLineStyle(7);
 Selection_eff_tt -> SetLineWidth(2);
Selection_eff_tt->SetLineStyle(7);
 Selection_eff_wjets -> SetLineWidth(2);
Selection_eff_wjets->SetLineStyle(7);

 Selection_eff_HT->Draw("Hist");
 Selection_eff2000_HT->Draw("Hist SAME");
 Selection_eff2500_HT->Draw("Hist SAME");
 Selection_eff_tt->Draw("Hist SAME");
 Selection_eff_BG->Draw("Hist SAME");
 Selection_eff_wjets->Draw("Hist SAME");

 leg = new TLegend(0.6,0.7,0.89,0.89);
 leg -> AddEntry("Selection_eff_HT","Z'1500T'1200");
 leg -> AddEntry("Selection_eff2000_HT","Z'2000T'1200");
 leg -> AddEntry("Selection_eff2500_HT","Z'2500T'1500");
 leg -> AddEntry("Selection_eff_BG","QCD");
 leg -> AddEntry("Selection_eff_tt","ttbar");
 leg -> AddEntry("Selection_eff_wjets","W+Jets");
 leg->Draw("Same");
 //c1->SetLogy();
 c1->Print("signal_eff.eps");

 TCanvas* c2 = new TCanvas("c2", "Selection Efficency Background Samples", 600,600);

 Selection_eff_tt->SetStats(0);
 Selection_eff_BG -> SetLineWidth(2);
 Selection_eff_tt -> SetLineWidth(2);
 Selection_eff_wjets -> SetLineWidth(2);

 Selection_eff_tt->Draw("Hist ");
 Selection_eff_BG->Draw("Hist SAME");
 Selection_eff_wjets->Draw("Hist SAME");
 
 legbg = new TLegend(0.6,0.7,0.89,0.89);
 legbg -> AddEntry("Selection_eff_BG","QCD");
 legbg -> AddEntry("Selection_eff_tt","ttbar");
 legbg -> AddEntry("Selection_eff_wjets","W+Jets");
 legbg->Draw("Same");
 c2->SetLogy();
 c2->Print("background_eff.eps");
}//end effplots
