#include "TH1.h"
#include "TH2.h"
#include <fstream>
#include "TGraphAsymmErrors.h"

//parameters
double alpha3 = 0.118;
double sp2 =0.56*0.56;
double sp2R =0.6*0.6;
double st2 =0.40*0.40;
double ctt3= 2.27;
double spq2 = sp2;
double cpq2=1-spq2;
double tt3 = 0.44;

double decaytT(double MG, double MT){

  double br = (alpha3/6) * MG * ((sp2 * (1-sp2))/(st2 * (1 - st2))) * (1-((MT*MT)/(MG*MG))) *  (1-(1/2)*((MT*MT)/(MG*MG))-(1/2)*((MT*MT*MT*MT)/(MG*MG*MG*MG)));

  return br;
}

double decaytrT(double MG, double MT){

  double br = (alpha3/6) * MG * ((sp2R * (1-sp2R))/(st2 * (1 - st2))) * (1-((MT*MT)/(MG*MG))) *  (1-(1/2)*((MT*MT)/(MG*MG))-(1/2)*((MT*MT*MT*MT)/(MG*MG*MG*MG)));

  return br;
}

double decayTT(double MG, double MT){

  double br = (alpha3/12) * MG *(((cpq2*ctt3-spq2 * tt3)*(cpq2*ctt3-spq2 * tt3)+ctt3*ctt3)*(1-((MT*MT)/(MG*MG)))+6*(cpq2*ctt3*ctt3 - spq2)*((MT*MT)/(MG*MG)))*sqrt(1-(4*((MT*MT)/(MG*MG))));

  return br;
}



double decaytt(double MG, double MT){

  double br = (alpha3/12) * MG * (sp2*ctt3 - sqrt(1-sp2)*tt3)*(sp2*ctt3 - sqrt(1-sp2)*tt3);

  return br;
}

double decaytrtr(double MG, double MT){

  double br = (alpha3/12) * MG * (sp2R*ctt3 - sqrt(1-sp2R)*tt3)*(sp2R*ctt3 - sqrt(1-sp2R)*tt3);

  return br;
}

double decayqq(double MG, double MT){

  double br = (alpha3/6) * MG * tt3*tt3;

  return br;
}


// double decaytot(double MG, double MT){
//   double br=0;
//   if(MT > MG){ 
//     br = decaytt(MG, MT) + decayqq(MG, MT);
//   }else  if(MG < 2 * MT){ 
//     br = decaytT(MG, MT) + decaytt(MG, MT) + decayqq(MG, MT);
//   }else{
//    br = decaytT(MG, MT) + decayTT(MG, MT) + decaytt(MG, MT) + decayqq(MG, MT);
//   }
//   return br;
// }

double decaytot(double MG, double MT){
  double br=0;
  if(MT > MG){ 
    br =3* decaytt(MG, MT) + 4*decayqq(MG, MT)+ decaytrtr(MG, MT);
  }else  if(MG < 2 * MT){ 
    br = 3*decaytT(MG, MT)+decaytrT(MG, MT) + 3*decaytt(MG, MT) + 4*decayqq(MG, MT)+ decaytrtr(MG, MT);
  }else{
   br = 3*decaytT(MG, MT) +decaytrT(MG, MT) + 10*decayTT(MG, MT) + 3*decaytt(MG, MT) + 4*decayqq(MG, MT)+ decaytrtr(MG, MT);
  }
  return br;
}

