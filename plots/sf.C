#include "TH1.h"
#include <fstream>



void sf(){


  TCanvas *new_c = new TCanvas("new_c","new",10,10,700,900);

  TH1F* sf_h = new TH1F("sf_h","SF",20,200,1600);
  Double_t binsx[3] = {200, 300, 1600};
  TH1F* sf_hnew= (TH1F*)sf_h->Rebin(2,"sf_hnew",binsx);


  sf_hnew->Fill(200,0.906);
  sf_hnew->SetBinError(1,0.16);
  sf_hnew->Fill(400,1.052);
  sf_hnew->SetBinError(2,0.375);
  TLine* line = new TLine(200, 0.912, 1600, 0.912);
  line->SetLineColor(kRed);
  line-> SetLineWidth(2);

  sf_hnew->Draw();
  line->Draw("SAME");

}
