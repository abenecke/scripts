#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"

using namespace std;


bool berror=false; 
TString directory = "/afs/desy.de/user/a/abenecke/madanalysis5/rho/Output/";
TString output_folder = "/afs/desy.de/user/a/abenecke/madanalysis5/rho/Output/";

#include "madgraph_plotter_func.h"

void madgraph_plotter()
{

  //general
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);

  if(berror) std::cout<<"Read in Files"<<std::endl;
  ///////////////////////     Read in Files        ////////////////////////////////////////////////
  TFile *rho_HT = new TFile(directory + "rho_HT.root", "READ");
  TFile *rho_HT_wrong = new TFile(directory + "rho_HT_wrong.root", "READ");
  TFile *rho_ZT = new TFile(directory + "rho_ZT.root", "READ");
  TFile *rho_ZT_wrong = new TFile(directory + "rho_ZT_wrong.root", "READ");
  TFile *rho_WB = new TFile(directory + "rho_WB.root", "READ");

  TFile *rho_HT_RH = new TFile(directory + "rho_HT_RH.root", "READ");
  TFile *rho_ZT_RH = new TFile(directory + "rho_ZT_RH.root", "READ");
  TFile *rho_WB_RH = new TFile(directory + "rho_WB_RH.root", "READ");
  TFile *rho_WB_30_10 = new TFile(directory + "rho_WB_30_10.root", "READ");
  TFile *rho_WB_30_1 = new TFile(directory + "rho_WB_30_1.root", "READ");
  TFile *rho_WB_10_10 = new TFile(directory + "rho_WB_10_10.root", "READ");
  TFile *rho_WB_10_1 = new TFile(directory + "rho_WB_10_1.root", "READ");


  TFile *gstar_HT = new TFile(directory + "gstar_HT.root", "READ");
  TFile *gstar_ZT = new TFile(directory + "gstar_ZT.root", "READ");
  TFile *gstar_WB = new TFile(directory + "gstar_WB.root", "READ");

  TFile *gstar_ZT_10_1 = new TFile(directory + "gstar_ZT_10_1.root", "READ");
  TFile *gstar_ZT_30_1 = new TFile(directory + "gstar_ZT_30_1.root", "READ");

  TFile *rho_ZT_10_1 = new TFile(directory + "rho_ZT_10_1.root", "READ");
  TFile *rho_ZT_10_10 = new TFile(directory + "rho_ZT_10_10.root", "READ");
  TFile *rho_ZT_30_1 = new TFile(directory + "rho_ZT_30_1.root", "READ");
  TFile *rho_ZT_30_10 = new TFile(directory + "rho_ZT_30_10.root", "READ");

  std::vector<TH1F*> hists;
  std::vector<Color_t> colors;
  std::vector<TString> names;
  std::vector<TH1F*> rebinned;

  if(berror) std::cout<<"Read in pT t/b quark"<<std::endl;
  ///////////////////////     Read in pT t/b quark    diff. decay modes    ////////////////////////////////////////////////
  TString histname = "PT_t";
  // hists = {(TH1F*)rho_HT->Get(histname),(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_WB->Get("PTb") };
  // colors = {kBlue, kGreen, kRed};
  // names = {"T' #rightarrow Ht","T' #rightarrow Zt","T' #rightarrow Wb"};


  // rebinned =rebin(25 ,hists );

  // save_result (rebinned,colors,names,"pt_tb.eps","#rho^{0} model", "t_{T'}/b_{T'} p_{T} [GeV]", "N. of t_{T'}/b_{T'}");

// ///////////////////////     Read in pT t/b quark   LH &RH Ht    ////////////////////////////////////////////////
//   histname = "PT_H";
//   hists = {(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname),(TH1F*)rho_HT_wrong->Get(histname) };
//   colors = { kBlack,kGreen, kOrange};
//   names = {"LH","RH","LH (current MC)"};
//   rebinned =rebin(25 ,hists );
//   save_result (rebinned,colors,names,"pt_t_HT.eps","#rho^{0} model, T' #rightarrow Ht", " p_{T}[t_{T'}] (GeV)", "N. of t_{T'}",0.37,0.52,0.61,0.17);

 ///////////////////////     Read in pT t/b quark   LH &RH Ht    ////////////////////////////////////////////////
   histname = "PT_t";
  hists = {(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname),(TH1F*)rho_HT_wrong->Get(histname) };
  colors = { kBlack,kGreen, kOrange};
  names = {"LH","RH","LH (current MC)"};
  rebinned =rebin(25 ,hists );
  save_result (rebinned,colors,names,"pt_t_HT.eps","#rho^{0} model, T' #rightarrow Ht", " p_{T}[t_{T'}] (GeV)", "N. of t_{T'}",0.4,0.52,0.64,0.17);

///////////////////////     Read in pT t quark decay products   LH &RH Ht    ////////////////////////////////////////////////
   histname = "PT_tb";
  hists = {(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname),(TH1F*)rho_HT_wrong->Get(histname) };
  colors = { kBlack,kGreen, kOrange};
  names = {"LH","RH","LH (current MC)"};
  rebinned =rebin(25 ,hists );
  save_result (rebinned,colors,names,"pt_tb_HT.eps","#rho^{0} model, T' #rightarrow Ht", " p_{T}[tb_{T'}] (GeV)", "N. of t_{b}",0.4,0.52,0.64,0.17);

///////////////////////     Read in pT t quark decay products   LH &RH Ht    ////////////////////////////////////////////////
   histname = "PT_tW";
  hists = {(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname),(TH1F*)rho_HT_wrong->Get(histname) };
  colors = { kBlack,kGreen, kOrange};
  names = {"LH","RH","LH (current MC)"};
  rebinned =rebin(25 ,hists );
  save_result (rebinned,colors,names,"pt_tW_HT.eps","#rho^{0} model, T' #rightarrow Ht", " p_{T}[tb_{T'}] (GeV)", "N. of t_{b}",0.4,0.52,0.64,0.17);

 // ///////////////////////     Read in pT T'   LH &RH Ht    ////////////////////////////////////////////////
  histname = "PT_T23";
  
  hists = {(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname),(TH1F*)rho_HT_wrong->Get(histname) };
  colors = { kBlack,kGreen, kOrange};
  names = {"LH","RH", "LH (current MC)"};
  rebinned =rebin(25 ,hists );
  save_result (rebinned,colors,names,"pt_T23_HT.eps","#rho^{0} model, T' #rightarrow Ht", " p_{T}[t_{T'}] (GeV)", "N. of t_{T'}",0.2,0.82,0.44,0.52);


///////////////////////     Read in pT t/b quark   LH &RH Zt    ////////////////////////////////////////////////
  histname = "PT_t";
  hists = {(TH1F*)rho_ZT_wrong->Get(histname) ,(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_ZT_RH->Get(histname) };
  colors = {kOrange, kBlack,kGreen};
  names = {"RH (current MC)","LH","RH"};
  rebinned =rebin(25 ,hists );
  save_result (rebinned,colors,names,"pt_t_ZT.eps","#rho^{0} model, T' #rightarrow Zt", " p_{T}[t_{T'}] (GeV)", "N. of t_{T'}");

///////////////////////     Read in pT t/b quark   LH &RH Wb    ////////////////////////////////////////////////
  
  histname = "PTb";
  hists = {(TH1F*)rho_WB_RH->Get(histname), (TH1F*)rho_WB->Get(histname)};
  colors = {kGreen, kBlack};
  names = {"RH","LH"};
  rebinned =rebin(25 ,hists );
  save_result (rebinned,colors,names,"pt_t_WB.eps","#rho^{0} model, T' #rightarrow Wb", " p_{T}[b_{T'}] (GeV)", "N. of b_{T'}");

 ///////////////////////     Read in pT T'    diff. decay modes    ////////////////////////////////////////////////
  histname = "PT_T23";
  hists = {(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_WB->Get(histname) };
  colors = {kBlue, kGreen, kRed};
  names = {"T' #rightarrow Ht","T' #rightarrow Zt","T' #rightarrow Wb"};

  rebinned =rebin(25 ,hists );
  hists = {(TH1F*)rho_HT->Get(histname),rebinned[0],rebinned[1]};
  save_result (hists,colors,names,"pt_T23.eps","#rho^{0} model", " p_{T}[T'] (GeV)", "N. of T'",0.2,0.82,0.44,0.52);


 ///////////////////////     Read in pT T'   diff. decay modes    ////////////////////////////////////////////////
  histname = "PT_T23";
  hists = {(TH1F*)gstar_HT->Get(histname),(TH1F*)gstar_ZT->Get(histname),(TH1F*)gstar_WB->Get(histname) };
  colors = {kBlue, kGreen, kRed};
  names = {"T' #rightarrow Ht","T' #rightarrow Zt","T' #rightarrow Wb"};

  rebinned =rebin(25 ,hists );

  save_result (rebinned,colors,names,"gstar_pt_T23.eps","G* model", " p_{T}[T'] (GeV)", "N. of T'",0.2,0.82,0.44,0.52);



 ///////////////////////     Read in pT T'   diff. decay modes    ////////////////////////////////////////////////
  histname = "PT_t";
  hists = {(TH1F*)gstar_HT->Get(histname),(TH1F*)gstar_ZT->Get(histname),(TH1F*)gstar_WB->Get("PTb") };
  colors = {kBlue, kGreen, kRed};
  names = {"T' #rightarrow Ht","T' #rightarrow Zt","T' #rightarrow Wb"};

  rebinned =rebin(25 ,hists );

  save_result (rebinned,colors,names,"gstar_pt_tb.eps","G* model", "  p_{T}[t_{T'}/b_{T'}] (GeV)", "N. of t_{T'}/b_{T'}");



///////////////////////     Read in cos(Z',T')  differnt decay channels    ////////////////////////////////////////////////
  histname = "angle_ZP_T23";
  hists={(TH1F*)rho_HT->Get(histname),(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_WB->Get(histname)};
  colors = {kBlue, kGreen, kRed};
  names = {"T' #rightarrow Ht","T' #rightarrow Zt","T' #rightarrow Wb"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_ZP_T23.eps","#rho^{0} model, LH", "cos(#theta(Z',T'))", "Events",0.7,0.92,0.94,0.62);

///////////////////////     Read in cos(boson,T')  differnt decay channels    ////////////////////////////////////////////////

  hists={(TH1F*)rho_WB->Get("angle_W_T23"),(TH1F*)rho_ZT->Get("angle_Z_T23"),(TH1F*)rho_HT->Get("angle_H_T23")};
  colors = {kRed, kGreen,kBlue};
  names = {"T' #rightarrow Wb","T' #rightarrow Zt","T' #rightarrow Ht"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_boson_T23.eps","#rho^{0} model, LH", "cos(#theta(H/Z/W,T'))", "Events",0.7,0.92,0.94,0.62);

///////////////////////     Read in cos(t/b,T')  differnt decay channels    ////////////////////////////////////////////////
  histname = "angle_t_T23";
  hists={(TH1F*)rho_WB->Get("angle_b_T23"),(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_HT->Get(histname)};
  names = {"T' #rightarrow Wb","T' #rightarrow Zt","T' #rightarrow Ht"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_tb_T23.eps","#rho^{0} model, LH", "cos(#theta(t/b,T'))", "Events",0.7,0.92,0.94,0.62);


///////////////////////     Read in cos(Z',T')  HT    ////////////////////////////////////////////////
  histname = "angle_ZP_T23";
  hists={(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname)};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_ZP_T23_HT.eps","#rho^{0} model, T' #rightarrow Ht", "cos(#theta(Z',T'))", "Events",0.6,0.92,0.84,0.62, true);

///////////////////////     Read in cos(boson,T')  HT    ////////////////////////////////////////////////

  hists={(TH1F*)rho_HT->Get("angle_H_T23"),(TH1F*)rho_HT_RH->Get("angle_H_T23")};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_boson_T23_HT.eps","#rho^{0} model, T' #rightarrow Ht ", "cos(#theta(H,T'))", "Events",0.6,0.92,0.84,0.62,true);

///////////////////////     Read in cos(t/b,T')  HT    ////////////////////////////////////////////////
  histname = "angle_t_T23";
  hists={(TH1F*)rho_HT->Get(histname),(TH1F*)rho_HT_RH->Get(histname)};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_tb_T23_HT.eps","#rho^{0} model, T' #rightarrow Ht ", "cos(#theta(t,T'))", "Events",0.6,0.92,0.84,0.62,true);


///////////////////////     Read in cos(Z',T')  ZT    ////////////////////////////////////////////////
  histname = "angle_ZP_T23";
  hists={(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_ZT_RH->Get(histname)};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_ZP_T23_ZT.eps","#rho^{0} model, T' #rightarrow Zt", "cos(#theta(Z',T'))", "Events",0.6,0.92,0.84,0.62, true);

///////////////////////     Read in cos(boson,T')  ZT    ////////////////////////////////////////////////

  hists={(TH1F*)rho_ZT->Get("angle_Z_T23"),(TH1F*)rho_ZT_RH->Get("angle_Z_T23")};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_boson_T23_ZT.eps","#rho^{0} model, T' #rightarrow Zt ", "cos(#theta(Z,T'))", "Events",0.6,0.92,0.84,0.62,true);

///////////////////////     Read in cos(t/b,T')  ZT    ////////////////////////////////////////////////
  histname = "angle_t_T23";
  hists={(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_ZT_RH->Get(histname)};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_tb_T23_ZT.eps","#rho^{0} model, T' #rightarrow Zt ", "cos(#theta(t,T'))", "Events",0.6,0.92,0.84,0.62,true);




///////////////////////     Read in cos(Z',T')  WB    ////////////////////////////////////////////////
  histname = "angle_ZP_T23";
  hists={(TH1F*)rho_WB->Get(histname),(TH1F*)rho_WB_RH->Get(histname)};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_ZP_T23_WB.eps","#rho^{0} model, T' #rightarrow Wb", "cos(#theta(Z',T'))", "Events",0.6,0.92,0.84,0.62, true);

///////////////////////     Read in cos(boson,T')  WB    ////////////////////////////////////////////////

  hists={(TH1F*)rho_WB->Get("angle_W_T23"),(TH1F*)rho_WB_RH->Get("angle_W_T23")};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_boson_T23_WB.eps","#rho^{0} model, T' #rightarrow Wb ", "cos(#theta(W,T'))", "Events",0.6,0.92,0.84,0.62,true);

///////////////////////     Read in cos(t/b,T')  WB    ////////////////////////////////////////////////
  histname = "angle_b_T23";
  hists={(TH1F*)rho_WB->Get(histname),(TH1F*)rho_WB_RH->Get(histname)};
  colors = {kBlack, kGreen};
  names = {"LH","RH"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"rho_angle_tb_T23_WB.eps","#rho^{0} model, T' #rightarrow Wb ", "cos(#theta(b,T'))", "Events",0.6,0.92,0.84,0.62,true);



///////////////////////     Read in cos(boson,T')  differnt decay channels    ////////////////////////////////////////////////

  hists={(TH1F*)gstar_WB->Get("angle_W_T23"),(TH1F*)gstar_ZT->Get("angle_Z_T23"),(TH1F*)gstar_HT->Get("angle_H_T23")};
  colors = {kRed, kGreen,kBlue};
  names = {"T' #rightarrow Wb","T' #rightarrow Zt","T' #rightarrow Ht"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"gstar_angle_boson_T23.eps","G* model, LH", "cos(#theta(H/Z/W,T'))", "Events",0.7,0.92,0.94,0.62, true);

///////////////////////     Read in cos(t/b,T')  differnt decay channels    ////////////////////////////////////////////////
  histname = "angle_t_T23";
  hists={(TH1F*)gstar_WB->Get("angle_b_T23"),(TH1F*)gstar_ZT->Get(histname),(TH1F*)gstar_HT->Get(histname)};
  names = {"T' #rightarrow Wb","T' #rightarrow Zt","T' #rightarrow Ht"};
  // rebinned =rebin(4 ,hists );
  save_result (hists,colors,names,"gstar_angle_tb_T23.eps","G* model, LH", "cos(#theta(t/b,T'))", "Events",0.7,0.92,0.94,0.62,true);




///////////////////////    Widthstudies ZT  rho  ////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////    PT ZT    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_Z";
 hists={(TH1F*)rho_ZT_10_1->Get(histname),(TH1F*)rho_ZT_30_1->Get(histname),(TH1F*)rho_ZT->Get(histname)};
 rebinned =rebin(25 ,hists );

  colors = {kRed,kBlue, kOrange};
 names = {"Z' 10% T' 1%","Z' 30% T' 1%","Z' 1% T' 1%"}; 
 save_result (rebinned,colors,names,"width_ZT_PT.eps","#rho^{0} model, LH", "P_{T}[Z] (GeV)", "Events");

///////////////////////    PT T23    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_T23";
 hists={(TH1F*)rho_ZT_10_1->Get(histname),(TH1F*)rho_ZT_30_1->Get(histname)};
 rebinned =rebin(25 ,hists );
 // rebinned.push_back((TH1F*)rho_ZT->Get(histname));
 hists={(TH1F*)rho_ZT->Get(histname),rebinned[0],rebinned[1]};
 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_T23_PT.eps","#rho^{0} model, LH", "P_{T}[T'] (GeV)", "Events",0.2,0.92,0.44,0.57,false);


///////////////////////    PT t    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_t";
 hists={(TH1F*)rho_ZT_10_1->Get(histname),(TH1F*)rho_ZT_30_1->Get(histname)};
 rebinned =rebin(25 ,hists );
 hists={(TH1F*)rho_ZT->Get(histname),rebinned[0],rebinned[1]};
 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_t_PT.eps","#rho^{0} model, LH", "P_{T}[t_{T'}] (GeV)", "Events");

///////////////////////    Eta ZT    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_Z";
 hists={(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_ZT_10_1->Get(histname),(TH1F*)rho_ZT_30_1->Get(histname)};
 // rebinned =rebin(2 ,hists );

 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_ZT_Eta.eps","#rho^{0} model, LH", "#eta[Z] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);

///////////////////////    Eta T23    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_T23";
 hists={(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_ZT_10_1->Get(histname),(TH1F*)rho_ZT_30_1->Get(histname)};
 // rebinned =rebin(2 ,hists );

 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_T23_Eta.eps","#rho^{0} model, LH", "#eta[T'] (GeV)", "Events",0.73,0.92,0.88,0.57, true, false,0.04);

///////////////////////    Eta t    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_t";
 hists={(TH1F*)rho_ZT->Get(histname),(TH1F*)rho_ZT_10_1->Get(histname),(TH1F*)rho_ZT_30_1->Get(histname)};
 // rebinned =rebin(2 ,hists );

 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_t_Eta.eps","#rho^{0} model, LH", "#eta[t] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);


///////////////////////    Widthstudies ZT  G*  ////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////    PT ZT    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_Z";
 hists={(TH1F*)gstar_ZT_10_1->Get(histname),(TH1F*)gstar_ZT_30_1->Get(histname),(TH1F*)gstar_ZT->Get(histname)};
 rebinned =rebin(25 ,hists );

 colors = {kRed,kBlue, kOrange};
 names = {"Z' 10% T' 1%","Z' 30% T' 1%","Z' 1% T' 1%"}; 
 save_result (rebinned,colors,names,"width_gstar_ZT_PT.eps","G*^{0} model, LH", "P_{T}[Z] (GeV)", "Events");

///////////////////////    PT T23    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_T23";
 hists={(TH1F*)gstar_ZT_10_1->Get(histname),(TH1F*)gstar_ZT_30_1->Get(histname)};
 rebinned =rebin(25 ,hists );
 // rebinned.push_back((TH1F*)gstar_ZT->Get(histname));
 hists={(TH1F*)gstar_ZT->Get(histname),rebinned[0],rebinned[1]};
 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_gstar_T23_PT.eps","G*^{0} model, LH", "P_{T}[T'] (GeV)", "Events",0.2,0.92,0.44,0.57,false);


///////////////////////    PT t    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_t";
 hists={(TH1F*)gstar_ZT_10_1->Get(histname),(TH1F*)gstar_ZT_30_1->Get(histname)};
 rebinned =rebin(25 ,hists );
 hists={(TH1F*)gstar_ZT->Get(histname),rebinned[0],rebinned[1]};
 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (hists,colors,names,"width_gstar_t_PT.eps","G*^{0} model, LH", "P_{T}[t_{T'}] (GeV)", "Events");

///////////////////////    Eta ZT    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_Z";
 hists={(TH1F*)gstar_ZT->Get(histname),(TH1F*)gstar_ZT_10_1->Get(histname),(TH1F*)gstar_ZT_30_1->Get(histname)};
 rebinned =rebin(2 ,hists );

 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (rebinned,colors,names,"width_gstar_ZT_Eta.eps","G*^{0} model, LH", "#eta[Z] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);

///////////////////////    Eta T23    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_T23";
 hists={(TH1F*)gstar_ZT->Get(histname),(TH1F*)gstar_ZT_10_1->Get(histname),(TH1F*)gstar_ZT_30_1->Get(histname)};
 rebinned =rebin(2 ,hists );

 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (rebinned,colors,names,"width_gstar_T23_Eta.eps","G*^{0} model, LH", "#eta[T'] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);

///////////////////////    Eta t    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_t";
 hists={(TH1F*)gstar_ZT->Get(histname),(TH1F*)gstar_ZT_10_1->Get(histname),(TH1F*)gstar_ZT_30_1->Get(histname)};
 rebinned =rebin(2 ,hists );

 colors = {kOrange,kRed,kBlue};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 30% T' 1%"}; 
 save_result (rebinned,colors,names,"width_gstar_t_Eta.eps","G*^{0} model, LH", "#eta[t] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);







 cout<<"Integral 30 10  "<<(((TH1F*)rho_WB_30_10->Get("PT_T23"))->Integral()-((TH1F*)rho_WB->Get("PT_T23"))->Integral() )<<endl;
 cout<<"Integral 10 1   "<<(((TH1F*)rho_WB_10_1->Get("PT_T23"))->Integral()-((TH1F*)rho_WB->Get("PT_T23"))->Integral() )<<endl;
 cout<<"Integral 30 1  "<<(((TH1F*)rho_WB_30_1->Get("PT_T23"))->Integral()-((TH1F*)rho_WB->Get("PT_T23"))->Integral() )<<endl;
 cout<<"Integral 10 10   "<<(((TH1F*)rho_WB_10_10->Get("PT_T23"))->Integral()-((TH1F*)rho_WB->Get("PT_T23"))->Integral() )<<endl;


///////////////////////    Widthstudies WB  rho  ////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////    PT WB    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_W";
 hists={(TH1F*)rho_WB_10_1->Get(histname),(TH1F*)rho_WB_10_10->Get(histname),(TH1F*)rho_WB_30_1->Get(histname),(TH1F*)rho_WB_30_10->Get(histname),(TH1F*)rho_WB->Get(histname)};
 rebinned =rebin(25 ,hists );

 colors = {kOrange,kBlack,kBlue,kRed,kGreen};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 10% T' 10%","Z' 30% T' 1%","Z' 30% T' 10%"}; 
 save_result (rebinned,colors,names,"width_W_PT.eps","#rho^{0} model, LH", "P_{T}[W] (GeV)", "Events");

///////////////////////    PT T23    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PT_T23";
 hists={(TH1F*)rho_WB_10_1->Get(histname),(TH1F*)rho_WB_10_10->Get(histname),(TH1F*)rho_WB_30_1->Get(histname),(TH1F*)rho_WB_30_10->Get(histname)};
 rebinned =rebin(25 ,hists );
 // rebinned.push_back((TH1F*)rho_WB->Get(histname));
 hists={(TH1F*)rho_WB->Get(histname),rebinned[0],rebinned[1],rebinned[2],rebinned[3]};
 colors = {kOrange,kBlack,kBlue,kRed,kGreen};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 10% T' 10%","Z' 30% T' 1%","Z' 30% T' 10%"}; 
 save_result (hists,colors,names,"width_T23_PT_WB.eps","#rho^{0} model, LH", "P_{T}[T'] (GeV)", "Events",0.6,0.92,0.84,0.57,false);


// ///////////////////////    PT t    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "PTb";
 hists={(TH1F*)rho_WB_10_1->Get(histname),(TH1F*)rho_WB_10_10->Get(histname),(TH1F*)rho_WB_30_1->Get(histname),(TH1F*)rho_WB_30_10->Get(histname)};
 rebinned =rebin(25 ,hists );
 colors = {kOrange,kBlack,kBlue,kRed,kGreen};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 10% T' 10%","Z' 30% T' 1%","Z' 30% T' 10%"}; 
 hists={(TH1F*)rho_WB->Get(histname),rebinned[0],rebinned[1],rebinned[2],rebinned[3]};
 save_result (hists,colors,names,"width_b_PT_WB.eps","#rho^{0} model, LH", "P_{T}[b_{T'}] (GeV)", "Events");

///////////////////////    Eta WB    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_W";
 hists={(TH1F*)rho_WB->Get(histname),(TH1F*)rho_WB_10_1->Get(histname),(TH1F*)rho_WB_10_10->Get(histname),(TH1F*)rho_WB_30_1->Get(histname),(TH1F*)rho_WB_30_10->Get(histname)};
 // rebinned =rebin(2 ,hists );
 colors = {kOrange,kBlack,kBlue,kRed,kGreen};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 10% T' 10%","Z' 30% T' 1%","Z' 30% T' 10%"}; 
 save_result (hists,colors,names,"width_WB_Eta.eps","#rho^{0} model, LH", "#eta[W] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);

///////////////////////    Eta T23    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_T23";
 hists={(TH1F*)rho_WB->Get(histname),(TH1F*)rho_WB_10_1->Get(histname),(TH1F*)rho_WB_10_10->Get(histname),(TH1F*)rho_WB_30_1->Get(histname),(TH1F*)rho_WB_30_10->Get(histname)};
 // rebinned =rebin(2 ,hists );
 colors = {kOrange,kBlack,kBlue,kRed,kGreen};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 10% T' 10%","Z' 30% T' 1%","Z' 30% T' 10%"}; 
 save_result (hists,colors,names,"width_T23_Eta_WB.eps","#rho^{0} model, LH", "#eta[T'] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);

///////////////////////    Eta t    ////////////////////////////////////////////////////////////////////////////////////////////////
 histname = "Eta_b";
 // rebinned =rebin(2 ,hists );
 hists={(TH1F*)rho_WB->Get(histname),(TH1F*)rho_WB_10_1->Get(histname),(TH1F*)rho_WB_10_10->Get(histname),(TH1F*)rho_WB_30_1->Get(histname),(TH1F*)rho_WB_30_10->Get(histname)};
 colors = {kOrange,kBlack,kBlue,kRed,kGreen};
 names = {"Z' 1% T' 1%","Z' 10% T' 1%","Z' 10% T' 10%","Z' 30% T' 1%","Z' 30% T' 10%"}; 
 save_result (hists,colors,names,"width_b_Eta_WB.eps","#rho^{0} model, LH", "#eta[t] (GeV)", "Events",0.73,0.92,0.88,0.57, false, false,0.04);



}
