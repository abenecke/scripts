void setThesisStyle() {
  TStyle *thesisStyle = new TStyle("thesisStyle","Style for Thesis"); //medium
  

// For the canvas:
  thesisStyle->SetCanvasBorderMode(0);
  thesisStyle->SetCanvasColor(kWhite);
  thesisStyle->SetCanvasDefH(600); //Height of canvas
  thesisStyle->SetCanvasDefW(600); //Width of canvas
  thesisStyle->SetCanvasDefX(0);   //POsition on screen
  thesisStyle->SetCanvasDefY(0);

// For the Pad:
  thesisStyle->SetPadBorderMode(0);
  // thesisStyle->SetPadBorderSize(Width_t size = 1);
  thesisStyle->SetPadColor(kWhite);
  thesisStyle->SetPadGridX(false);
  thesisStyle->SetPadGridY(false);
  thesisStyle->SetGridColor(0);
  thesisStyle-> SetPadTickX(1);
  thesisStyle->   SetPadTickY(1);
  //thesisStyle->SetGridStyle(3);
  //thesisStyle->SetGridWidth(1);

// For the frame:
  thesisStyle->SetFrameBorderMode(0);
  thesisStyle->SetFrameBorderSize(3);
  thesisStyle->SetFrameFillColor(0);
  thesisStyle->SetFrameFillStyle(0);
  thesisStyle->SetFrameLineColor(1);
  thesisStyle->SetFrameLineStyle(1);
  thesisStyle->SetFrameLineWidth(3);

// For the histo:
  // thesisStyle->SetHistFillColor(1);
  // thesisStyle->SetHistFillStyle(0);
  thesisStyle->SetHistLineColor(1);
  thesisStyle->SetHistLineStyle(0);
  thesisStyle->SetHistLineWidth(3);
  // thesisStyle->SetLegoInnerR(Float_t rad = 0.5);
  // thesisStyle->SetNumberContours(Int_t number = 20);

  thesisStyle->SetEndErrorSize(2);
//  thesisStyle->SetErrorMarker(20);
  thesisStyle->SetErrorX(0.);
  
  thesisStyle->SetMarkerStyle(20);

//For the fit/function:
  thesisStyle->SetOptFit(0);
  thesisStyle->SetFitFormat("5.4g");
  thesisStyle->SetFuncColor(2);
  thesisStyle->SetFuncStyle(1);
  thesisStyle->SetFuncWidth(3);

//For the date:
  thesisStyle->SetOptDate(0);
  // thesisStyle->SetDateX(Float_t x = 0.01);
  // thesisStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  thesisStyle->SetOptFile(0);
  thesisStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  thesisStyle->SetStatColor(kWhite);
  thesisStyle->SetStatFont(42);
  thesisStyle->SetStatFontSize(0.025);
  thesisStyle->SetStatTextColor(1);
  thesisStyle->SetStatFormat("6.4g");
  thesisStyle->SetStatBorderSize(1);
  thesisStyle->SetStatH(0.1);
  thesisStyle->SetStatW(0.15);
  // thesisStyle->SetStatStyle(Style_t style = 1001);
  // thesisStyle->SetStatX(Float_t x = 0);
  // thesisStyle->SetStatY(Float_t y = 0);

// Margins:
  thesisStyle->SetPadTopMargin(0.05);
  thesisStyle->SetPadBottomMargin(0.13);
  thesisStyle->SetPadLeftMargin(0.16);
  thesisStyle->SetPadRightMargin(0.06);

// For the Global title:

  thesisStyle->SetOptTitle(0);
  thesisStyle->SetTitleFont(42);
  thesisStyle->SetTitleColor(1);
  thesisStyle->SetTitleTextColor(1);
  thesisStyle->SetTitleFillColor(10);
  thesisStyle->SetTitleFontSize(0.05);
  // thesisStyle->SetTitleH(0); // Set the height of the title box
  // thesisStyle->SetTitleW(0); // Set the width of the title box
  // thesisStyle->SetTitleX(0); // Set the position of the title box
  // thesisStyle->SetTitleY(0.985); // Set the position of the title box
  // thesisStyle->SetTitleStyle(Style_t style = 1001);
  // thesisStyle->SetTitleBorderSize(2);

// For the axis titles:

  thesisStyle->SetTitleColor(1, "XYZ");
  thesisStyle->SetTitleFont(42, "XYZ");
  thesisStyle->SetTitleSize(0.06, "XYZ");
  // thesisStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // thesisStyle->SetTitleYSize(Float_t size = 0.02);
  thesisStyle->SetTitleXOffset(0.9);//0.9
  thesisStyle->SetTitleYOffset(1.25);//1.35
  // thesisStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  thesisStyle->SetLabelColor(1, "XYZ");
  thesisStyle->SetLabelFont(42, "XYZ");
  thesisStyle->SetLabelOffset(0.007, "XYZ");
  thesisStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  thesisStyle->SetAxisColor(1, "XYZ");
  thesisStyle->SetStripDecimals(kTRUE);
  thesisStyle->SetTickLength(0.03, "XYZ");
  thesisStyle->SetNdivisions(505, "XYZ");//510
  //thesisStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  //thesisStyle->SetPadTickY(1);
  thesisStyle->SetPadTickX(1); 
  thesisStyle->SetPadTickY(1);
  thesisStyle->SetNdivisions(510, "Z");//510

// Change for log plots:
  thesisStyle->SetOptLogx(0);
  thesisStyle->SetOptLogy(0);
  thesisStyle->SetOptLogz(0);

// Postscript options:
  thesisStyle->SetPaperSize(20.,20.);
  // thesisStyle->SetLineScalePS(Float_t scale = 3);
  // thesisStyle->SetLineStyleString(Int_t i, const char* text);
  // thesisStyle->SetHeaderPS(const char* header);
  // thesisStyle->SetTitlePS(const char* pstitle);

  // thesisStyle->SetBarOffset(Float_t baroff = 0.5);
  // thesisStyle->SetBarWidth(Float_t barwidth = 0.5);
  // thesisStyle->SetPaintTextFormat(const char* format = "g");
  // thesisStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // thesisStyle->SetTimeOffset(Double_t toffset);
  // thesisStyle->SetHistMinimumZero(kTRUE);

  thesisStyle->cd();

}

void limit()
{
  double x[3] = {1500,2000,2500};
  double x2[5]={1500,1500,2000,2500,2500};
  double x3[5]={1500,1500,2000,2500,2500};
  double central[3] = {0.47,0.299,0.254};
  double central1[3] = {2.05,0.522,0.366};
  double central2[3] = {0.497,0.369,0.307};
  double central3[3] = {0.457,0.274, 0.206 };

  double emanuele_HT[3] = {5.5,0.78,0.5};
  double emanuele_ZT[3] = {2.6,0.47,0.3};
  double emanuele_WB[3] = {7.8,0.48,0.23};
  double emanuele_WB_obs[3] = {8.4,0.26,0.29};

  // double marc_HT[3] = {};
  // double marc_ZT[3] = {};
  double marc_WB[3] = {9.22,1.78,1.26};

  //T' 1200 Z' 1500
  double HT_comb_chi50[3] ={0.483,0.265,0.235};
  double HT_comb_chi40[3]={0.496,0.291,0.253};
  double HT_comb_chi35[3]={0.499,0.306,0.262};
  double HT_comb_chi20[3]={0.508,0.302,0.264};

  double HT_comb_btag[3]={0.47,0.299,0.254};

  double HT_notop_chi50[3]={0.567,0.393,0.352};
  double HT_notop_chi40[3]={0.556,0.387,0.343};
  double HT_notop_chi30[3]={0.58,0.417,0.345};
  double HT_notop_chi20[3]={0.584,0.426,0.378};

  double HT_notop_btag[3]={0.497,0.369,0.307};

  double ZT_comb_chi50[3]={0.961,0.381,0.236};
  double ZT_comb_chi20[3]={0.988,0.422,0.255};

  double ZT_comb_btag[3]={0.889,0.407,0.23};

  double ZT_notop_chi50[3]={1.12,0.672,0.378};
  double ZT_notop_chi20[3]={1.2,0.786,0.429};

  double ZT_notop_btag[3]={0.994,0.594,0.319};

  double ZT_top_chi50[3]={2.05,0.522,0.366};

  double ZT_master[3]={0.89,0.41,0.2};
  double HT_master[3]={0.4,0.29,0.23};
  double WB_master[3]={4.11,1.81,0.91};


  ///2016 Data
  double HT_data2016_all[3]={0.0942,0.0429,0.0264};
  double HT_data2016_top[3]={0.316,0.0914,0.0851};
  double HT_data2016_notop[3]={0.0756,0.0527,0.0371};
  double HT_data2016_noH1[3]={0.107,0.062,0.048};
  double HT_data2016_noH1_top[3]={0.524,0.144,0.122};
  double HT_data2016_noH1_notop[3]={0.114,0.077,0.0581};
  double HT_data2016_tagger_priority[3]={0.0982,0.0437,0.0271};
  double HT_data2016_puppi[3]={0.105,0.0427,0.0263};
  double HT_data2016_btag[3]={0.0955,0.0491,0.0297};

  double ZT_data2016_noH1[3]={0.289,0.0932,0.0522};
  double ZT_data2016_all[3]={0.231,0.0795,0.0452};
  double ZT_data2016_tagger_priority[3]={0.228,0.0796,0.046};
  double ZT_data2016_puppi[3]={0.248,0.0835,0.0433};


  double WB_data2016_noH1[3]={1.27,0.483,0.257};
  double WB_data2016_all[3]={0.963,0.376,0.218};
  double WB_data2016_tagger_priority[3]={0.941,0.377,0.217};

 // double observed[17] = {20,2.97,0.399,0.181,0.0684,0.0378,0.0256,0.0198,0.0149,0.0131,0.0127,0.0107,0.00962,0.00909,0.00848,0.00831,0.00788};
  double low_95[5] = {0,0.506,0.226,0.143	,0};
  double up_95[5] = {0,0,0,0,0};
  double low_68[5] = {0,0.668,	0.299,	0.187,0};
  double up_68[5] = {0,1.28,0.586,0.367,0};
 // double theory[18] = {45.24,10.27,2.917,1.042,0.4242,0.1833,0.0861,0.04202,0.0219,0.01201,0.006423,0.003478,0.002067,0.001241,0.0007528,0.000466,0.0002726,0.000168}; // Pythia
 // double theory[17] = {0.174E+02,0.526E+01,0.189E+01,0.769E+00,0.342E+00,0.163E+00,0.820E-01,0.431E-01,0.235E-01,0.132E-01,0.761E-02,0.448E-02,0.269E-02,0.164E-02,0.101E-02,0.634E-03,0.402E-03};
 //  double theory_up[17] = {0.150E+02,0.454E+01,0.163E+01,0.663E+00,0.295E+00,0.140E+00,0.705E-01,0.369E-01,0.201E-01,0.113E-01,0.649E-02,0.381E-02,0.228E-02,0.139E-02,0.856E-03,0.534E-03,0.337E-03};
 // double theory_down[17] = {0.196E+02,0.594E+01,0.213E+01,0.865E+00,0.384E+00,0.183E+00,0.923E-01,0.484E-01,0.264E-01,0.149E-01,0.858E-02,0.506E-02,0.304E-02,0.186E-02,0.115E-02,0.722E-03,0.458E-03};

 // double rel_pdf_unc[17] = {0.05, 0.07, 0.09, 0.11, 0.13, 0.15, 0.17, 0.19, 0.21, 0.23, 0.25, 0.27, 0.29, 0.31, 0.33, 0.35, 0.37};
 // for (int i=0; i<17; ++i){
 //   double pdfu = rel_pdf_unc[i];
 //   double rup = (theory_up[i] - theory[i])/theory[i];
 //   double up2 = pdfu*pdfu + rup*rup;
 //   theory_up[i] = (1+TMath::Sqrt(up2))*theory[i];

 //   double rdn = (theory[i] - theory_down[i])/theory[i];
 //   double dn2 = pdfu*pdfu + rdn*rdn;
 //   theory_down[i] = (1-TMath::Sqrt(dn2))*theory[i];   
 // }

 

 TGraph* g_low_95 = new TGraph(5,x2,low_68);
 TGraph* g_low_68 = new TGraph(5,x2,low_68);
 TGraph* g_up_95_dummy = new TGraph(5,x3,low_95);
 TGraph* g_up_95 = new TGraph(5,x2,up_95);
 TGraph* g_up_68 = new TGraph(5,x2,up_68);
 // TGraph* g_observed = new TGraph(3,x,observed);
 TGraph* g_central = new TGraph(3,x,ZT_data2016_puppi);
 TGraph* g_central1 = new TGraph(3,x,HT_data2016_puppi);
 TGraph* g_central2 = new TGraph(3,x,HT_data2016_btag);
 TGraph* g_central_a = new TGraph(3,x,ZT_data2016_tagger_priority);
 TGraph* g_central1_a = new TGraph(3,x,HT_data2016_tagger_priority);
 TGraph* g_central2_a = new TGraph(3,x,WB_data2016_tagger_priority);
 TGraph* g_central3 = new TGraph(3,x,emanuele_WB_obs);

 


 // TGraph* g_theory = new TGraph(3,x,theory);
 // TGraph* g_theory_up = new TGraph(3,x,theory_up);
 // TGraph* g_theory_down = new TGraph(3,x,theory_down);

 g_up_95->UseCurrentStyle();
 g_up_95_dummy->UseCurrentStyle();
 g_low_95->UseCurrentStyle();
 g_up_68->UseCurrentStyle();
 g_low_68->UseCurrentStyle();
 g_up_95->SetLineColor(kGreen);
 g_up_95->SetFillColor(kGreen); 
 g_up_95_dummy->SetFillColor(0); 
 g_up_68->SetLineColor(kGreen+2);
 g_up_68->SetFillColor(kGreen+2);
 g_low_95->SetLineColor(kGreen);
 g_low_95->SetFillColor(kGreen); 
 g_low_68->SetLineColor(kWhite);
 g_low_68->SetFillColor(kWhite); 
 // g_observed->SetFillColor(0);
 // g_observed->SetLineColor(kBlack);
 // g_observed->SetLineWidth(3);
 g_central->SetFillColor(0);
 // g_central->SetLineStyle(2);
 g_central->SetLineColor(kGreen);
 g_central->SetLineWidth(2);

g_central1->SetFillColor(0);
// g_central1->SetLineStyle(2);
 g_central1->SetLineColor(kBlue);
 g_central1->SetLineWidth(2);

 g_central2->SetFillColor(0);
 // g_central2->SetLineStyle(2);
 g_central2->SetLineColor(kRed);
 g_central2->SetLineWidth(2); 

g_central_a->SetFillColor(0);
 g_central_a->SetLineStyle(2);
 g_central_a->SetLineColor(kGreen);
 g_central_a->SetLineWidth(2);

g_central1_a->SetFillColor(0);
 g_central1_a->SetLineStyle(2);
 g_central1_a->SetLineColor(kBlue);
 g_central1_a->SetLineWidth(2);

 g_central2_a->SetFillColor(0);
 g_central2_a->SetLineStyle(2);
 g_central2_a->SetLineColor(kRed);
 g_central2_a->SetLineWidth(2);

 g_central3->SetFillColor(0);
 g_central3->SetLineStyle(2);
 g_central3->SetLineColor(kBlack);
 g_central3->SetLineWidth(2);


 // g_theory->SetFillColor(0);
 // g_theory->SetLineStyle(9);
 // g_theory->SetLineColor(kBlack);
 // g_theory->SetLineWidth(2);

 // g_theory_up->SetFillColor(0);
 // g_theory_up->SetLineStyle(3);
 // g_theory_up->SetLineColor(kBlack);
 // g_theory_up->SetLineWidth(2);

 // g_theory_down->SetFillColor(0);
 // g_theory_down->SetLineStyle(3);
 // g_theory_down->SetLineColor(kBlack);
 // g_theory_down->SetLineWidth(2);

 g_up_95->SetLineWidth(0);
 g_up_95_dummy->SetLineWidth(0);
 g_up_68->SetLineWidth(0);

 TCanvas * c = new TCanvas("c", "c", 800,600);
  c->SetLogy();
  // g_up_95_dummy->SetMinimum(0.05);
 //g_up_95_dummy->GetXaxis()->SetRangeUser(x[0],x[3]);
 //g_up_95_dummy->Draw("AF");
 double min =0.01 ;
 g_up_95->SetMinimum(min);
 g_up_95->GetXaxis()->SetRangeUser(x[0],x[2]);
 g_up_95->SetMaximum(1);
 g_up_95->Draw("AF");
 // g_up_95->Draw("F SAME");
 // g_up_68->Draw("F SAME"); 
 // g_low_68->Draw("F SAME"); 
 // g_low_95->Draw("F SAME");
 // g_up_95_dummy->Draw("F SAME");
 //g_observed->Draw("L SAME");

 //  g_central3->Draw("L SAME");
 //g_central1->Draw("L SAME");
  g_central2->Draw("L SAME");
 // g_central->Draw("L SAME"); 
 g_central1_a->Draw("L SAME");
 // g_central2_a->Draw("L SAME");
 // g_central_a->Draw("L SAME");
  
 // g_theory->Draw("L SAME");
 // g_theory_up->Draw("L SAME");
 // g_theory_down->Draw("L SAME");
 TLegend *leg1;
 // leg1 = new TLegend(0.25,0.7,0.78,0.9,"","brNDC");//x+0.1
 leg1 = new TLegend(0.35,0.7,0.88,0.9,"","brNDC");//x+0.1
 leg1->SetBorderSize(0);
 leg1->SetTextSize(0.035);
 leg1->SetFillColor(10);
 leg1->SetLineColor(1);
 leg1->SetTextFont(42);
 TLegendEntry* entries[6];
  
 //entries[0]=leg1->AddEntry(g_observed, "observed 95% C.L. upper limits","L");

 // entries[1]=leg1->AddEntry(g_central2, "expected 95% C.L. upper limits Wb (e/mu channel)","L");

 // entries[1]=leg1->AddEntry(g_central3, "2015 data set (B2G-16-013)","L");
 // leg1->AddEntry((TObject*)0, "observed 95% C.L. upper limits (Wb)", ""); 
 // leg1->AddEntry((TObject*)0, " ", "");
 leg1->AddEntry((TObject*)0, "[btag]", "");
 entries[1]=leg1->AddEntry(g_central2, "expected 95% C.L. upper limits  (Ht)","L");
 // entries[1]=leg1->AddEntry(g_central, "expected 95% C.L. upper limits (Zt)","L");
 // entries[1]=leg1->AddEntry(g_central1, "expected 95% C.L. upper limits (Ht)","L");
 leg1->AddEntry((TObject*)0, "[chi2cut]", "");
 // entries[1]=leg1->AddEntry(g_central2_a, "expected 95% C.L. upper limits  (Wb) ","L");
 // entries[1]=leg1->AddEntry(g_central_a, "expected 95% C.L. upper limits (Zt)","L");
  entries[1]=leg1->AddEntry(g_central1_a, "expected 95% C.L. upper limits (Ht)","L");


 // entries[2]=leg1->AddEntry(g_theory, "LQ_{3} (NLO, Kraemer et al.)","L");
 // entries[3]=leg1->AddEntry(g_theory_up, "uncertainties on the theory cross section","L");
 // entries[4]=leg1->AddEntry(g_up_95, "central 95% expected upper limits","F");
 // entries[5]=leg1->AddEntry(g_up_68, "central 68% expected upper limits","F");

//   entries[0]=leg1->AddEntry(g_observed, "gemessene obere Grenze mit 95% Konfidenz","L");
//   entries[1]=leg1->AddEntry(g_central, "erwartete obere Grenze mit 95% Konfidenz","L");
//   entries[2]=leg1->AddEntry(g_up_95, "zentrale 95% der Erwartung","F");
//   entries[3]=leg1->AddEntry(g_up_68, "zentrale 68% der Erwartung","F");


 leg1->Draw();
 
 double m_lumi = 35.9;
 TString infotext = TString::Format("Work in progress, %3.1f fb^{-1} at #sqrt{s} = 13 TeV", m_lumi);
 TLatex *text1 = new TLatex(3.5, 24, infotext);
 text1->SetNDC();
 text1->SetTextAlign(33);
 text1->SetX(0.95);
 text1->SetTextFont(42);
 text1->SetTextSize(0.04);
 text1->SetY(1.00);
 text1->Draw();
 

 TH1F* h =  g_up_95->GetHistogram();
 h->UseCurrentStyle();
  h->UseCurrentStyle();
  h->GetXaxis()->SetRangeUser(200,1000);
 //h->SetXTitle(" m_{t#bar{t}} [GeV/c^{2}]");
 h->SetXTitle(" M_{Z'} [GeV/c^{2}]");
 h->SetYTitle("#sigma(pp#rightarrow Z'#rightarrow t T') #times BR [pb]");
 h->Draw("AXIS SAME");
 c->GetFrame()->Draw("same");
 c->Print("limitplot.eps");
 // c->Print("limitplot.pdf");
 // c->Print("limitplot.png");


}


void LimitPlot() {



    setThesisStyle();

    limit();
 
}


