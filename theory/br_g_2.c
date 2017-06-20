#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float PI=3.141592654;

float alfas = 0.118;
float mt = 174.0;
float mb = 4.62;
float v = 246.0;

float N=3.0;

float Y_comp = 3.0;
float g3_comp = 3.0;
float sen_tR = 0.6;
float sen_bR;

float M_ini=4000., M_fin=4000.;
float dtM=50;


float sen_teta3, cos_teta3, tan_teta3;
float s1, c1, s2, c2, cR, cRb;


float width_ele(float M, float sen);
float width_comp_ele(float M, float sen, float m);
float width_comp_comp(float M, float m);
float width_comp(float M, float sen, float m);


void br_g_2() {


FILE * out_M;
FILE * out_m;

float M,k=1,r=1;


float   ll=0, uu=0, dd=0, ss=0, cc=0, tLtL=0, bLbL=0, tRtR=0, bRbR=0, TtL=0, BbL=0, TstR=0, BsbR=0, TT=0, BB=0, T53T53=0, T23T23=0, B13B13=0, B43B43=0, TsTs=0, BsBs=0, TpTp=0, BpBp=0;
float width, Hl, HH,hh;

float  MQ; /* masse bare */
float MT, MTp, MTs, MBs; /* masse fisiche */


float Col; 

 Col= 1./2.;
s1 = sqrt(2)*mt/(v*Y_comp*sen_tR);
if(s1>1) { 
printf("s1 > 1!! scegliere altri valori di input \n");
//return 1;
}
cR=sqrt(1-pow(sen_tR,2));
/* assumiamo s_bR = s_1 */  
sen_bR=s1;
cRb=sqrt(1-pow(sen_bR,2));
c1=sqrt(1-pow(s1,2));
s2 = sen_tR*mb/mt*s1/sen_bR;
c2=sqrt(1-pow(s2,2));

sen_teta3 = 2*sqrt(alfas*PI)/g3_comp;
cos_teta3=sqrt(1-pow(sen_teta3,2));
tan_teta3 = sen_teta3/cos_teta3;






 out_M =fopen("width_sR06_tan044-MT700-2.txt","w");
    
//    out_M =fopen("width_r175.txt","w");

// fprintf(out_M,"M* \t hh \t Hl \t HH \t width \n ");
    fprintf(out_M,"M*  \t width \n ");

for(M=M_ini; M<=M_fin; M=M+dtM) {
    
   // MT=M/1.75;
    MT=3000;
    
    MQ=MT*c1;
    MTs=k*MT;
    MBs=k*MT;
    MTp=r*MT;
 
 ll=8*width_ele(M, 0);
 tLtL = width_ele(M, s1);
 bLbL = tLtL;
 tRtR = width_ele(M, sen_tR);
 bRbR =  width_ele(M, sen_bR);
if(M>=MT && MT!=0) TtL = width_comp_ele(M, s1, MT);
 BbL = TtL;
if(M>=MTs && MTs!=0) TstR = width_comp_ele(M, sen_tR, MTs);
if(M>=MBs && MBs!=0) BsbR = width_comp_ele(M, sen_bR, MBs);
if(M>=2*MT && MT!=0) TT = width_comp(M, s1, MT);
 BB = TT;
if(M>=2*MQ) T53T53 = width_comp_comp(M, MQ);
 T23T23 = T53T53;
if(M>=2*MTp) B43B43 = width_comp_comp(M, MTp);
 B13B13 = B43B43;
if(M>=2*MTs && MTs!=0) TsTs = width_comp(M, sen_tR, MTs);
if(M>=2*MBs && MBs!=0) BsBs = width_comp(M, sen_bR, MBs);
 TpTp = B43B43;
 BpBp = TpTp;


 
 width = ll+ tLtL + bLbL + tRtR + bRbR + TtL + BbL + TstR + BsbR + TT + BB  + T53T53 + T23T23 + B13B13 + B43B43 + TsTs + BsBs + TpTp + BpBp;
  
 ll=ll/width;
 tLtL = tLtL/width;
 bLbL = bLbL/width;
 tRtR = tRtR/width;
 bRbR = bRbR/width;
 TtL = TtL/width;
 BbL = BbL/width;
 TstR = TstR/width; 
 BsbR = BsbR/width;
 TT = TT/width;
 BB = BB/width;
 T53T53 = T53T53/width;
 T23T23 = T23T23/width;
 B13B13 = B13B13/width;
 B43B43 = B43B43/width;
 TsTs = TsTs/width;
 BsBs = BsBs/width;
 TpTp = TpTp/width;
 BpBp = BpBp/width;
 
 Hl= TtL+BbL+TstR+BsbR;
 HH= 2*TT+BsBs+TsTs+2*T53T53+2*TpTp+2*B13B13;
 hh=tRtR+2*tLtL+bRbR+ll;

 width = width*Col;



//fprintf(out_M," %f \t %f \t %f \t %f \t %f \n",M, hh, Hl, HH, width);
 //   fprintf(out_M," %f \t %f \t %f \t %f \n",M, width, MQ, TstR);
    
    fprintf(out_M," %f \t %f \n",M, width);
    std::cout<< "MG* " << M_ini << " MT  "  <<MT<<std::endl;
    std::cout <<"tltl  " << tLtL << "  trtr  " << tRtR << std::endl;
    std::cout<<"TtL  "<< TtL << "  TstR  "<< TstR << std::endl;
    std::cout<<"TT  "<<TT<<"  TsTs  "<< TsTs <<std::endl;
    std::cout<< "tot width " << width << std::endl; 
    
                             }

     fclose(out_M);


     //	return 0  ;
 }



/********************************* ALFA STRONG *********************************************************/

float as(float mu, int nf){

float als,l,b0,b1,b2,lam;

//lam=0.216;
/* arXiv:hep-ph/9604210v1 */
lam=0.233;
l=log(pow(mu/lam,2.));
b0=11.-2./3.*nf;
b1=51.-19./3.*nf;
b2=2857.-5033./9.*nf+325./27.*nf*nf;
if(l>0) als=(4.*PI/b0/l*(1.-2.*b1/b0/b0*log(l)/l+4.*b1*b1/pow(b0,4)/(l*l)*(pow((log(l)-0.5),2.)+b2*b0/8./(b1*b1)-5./4.)));

return als;
}

/*************************************************************************************************************/

float width_ele( float M, float sen){

float y;
float cos =sqrt(1-sen*sen);

y=M*as(M,5)/6.*pow((sen*sen/tan_teta3-cos*cos*tan_teta3),2);
return y;
}


float width_comp_ele(float M, float sen, float m){

float y;
float cos =sqrt(1-sen*sen);

/* devo considerare sia Ttbar che tTbar */

y= M*as(M,5)/3.*pow(sen*cos,2)/pow(sen_teta3*cos_teta3,2)*(1-pow(m/M,2))*(1-1./2.*pow(m/M,2)-1./2.*pow(m/M,4));
return y;
}


float width_comp(float M, float sen, float m){

float y;
float cos =sqrt(1-sen*sen);

y= M*as(M,5)/6.*(pow((cos*cos/tan_teta3-sen*sen*tan_teta3),2)+pow(1./tan_teta3,2))*sqrt(1-4*pow(m/M,2))*(1-pow(m/M,2))+M*alfas*(cos*cos/tan_teta3/tan_teta3-sen*sen)*pow(m/M,2)*sqrt(1-4*pow(m/M,2)) ;
return y;
}


float width_comp_comp(float M, float m){

float y;

y= M*as(M,5)/6.*(2*pow(1./tan_teta3,2))*sqrt(1-4*pow(m/M,2))*(1-pow(m/M,2))+ M*alfas*(1./tan_teta3/tan_teta3)*pow(m/M,2)*sqrt(1-4*pow(m/M,2));
return y;
}



