#include <stdio.h>
#include <math.h>
#include <mathsym.h>
using namespace cxxadt;
#include <lglobal.h>
#include <lsysintrfc.h>

const int D    = 1.0; //dominant    apical
const int S    = 2.0; //subdominant apical
const int T    = 3.0; //subdominant lateral
const int N    = 4.0; //nondominant apical
const int O    = 5.0; //nondominat  lateral

const double SEED = 29;
const double COMP = 0.7;  /*7.4/5.1 sandpit/restore */ 
const double DL = 1;      /* =7.4 cm */
const double SL = 0.57;   /* 4.2/7.4 */
const double NL = 0.32;   /* 2.4/7.4 */
const double DA = 30*2.0*PI_VALUE/360.0;
const double SA = 30*2.0*PI_VALUE/360.0;
const double NA = 30*2.0*PI_VALUE/360.0;
const double CU = -5*2.0*PI_VALUE/360.0;
const double CT =0.5*2.0*PI_VALUE/360.0;

module F(double);
module B(double,double); //type and status
module Pitch(double);
module Roll(double);
module Turn(double);

derivation length: 10;

Start:
{
  int seed = -1;
  ran3(&seed);
  produce F(0.1) SB() EB() B(D,0);
}

B(type,status):
{
  int seed = 29;
  double g = 0.0;
  double r1 = ran3(&seed);
  double r2 = ran3(&seed);
  
  if (r1 < CT)
     g = CU;
  else 
     g = -CU;
  
  if (type == D && status == 0.0){
   if (r2 < 0.26)
      produce Turn(g) F(0.6*DL) SB() Turn(NA)  B(N,2) EB() 
              Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1) EB()
              Turn(g) F(0.1*DL) SB() Turn(SA)  B(S,1) EB()
              Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0) EB()
              Turn(g) F(0.1*DL) SB() EB() B(D,0);
  
   else if (r2 >= 0.26 && r2 < 0.52)
     produce Turn(g) F(0.6*DL) SB() Turn(-NA) B(N,2) EB() 
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(SA)  B(S,0) EB()
             Turn(g) F(0.1*DL) SB() EB() B(D,0);
   
   else if (r2 >= 0.52 && r2 < 0.69)
     produce Turn(g) F(0.6*DL)  SB() Turn(-NA) B(N,2) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(NA)  B(N,1) EB()
             Turn(g) F(0.1*DL)  SB() Turn(-SA) B(S,1) EB()
             Turn(g) F(0.15*DL) SB() Turn(DA)  B(S,0) EB()
             Turn(g) F(0.05*DL) SB() EB() B(D,0);
  
   else if (r2 >= 0.69 && r2 < 0.86)
     produce Turn(g) F(0.6*DL)  SB() Turn(NA)  B(N,2) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(-NA) B(N,1) EB()
             Turn(g) F(0.1*DL)  SB() Turn(SA)  B(S,1) EB()
             Turn(g) F(0.15*DL) SB() Turn(-DA) B(S,0) EB()
             Turn(g) F(0.05*DL) SB() EB() B(D,0);

   else if (r2 >= 0.86 && r2 < 0.90)
     produce Turn(g) F(0.6*DL)  SB() Turn(NA)  B(N,2) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(-NA) B(N,1) EB()
             Turn(g) F(0.1*DL)  SB() Turn(SA)  B(S,1) EB()
             Turn(g) F(0.15*DL) SB() Turn(-DA) B(S,0) EB()
             Turn(g) F(0.05*DL) SB() EB() B(T,0);

   else if (r2 >= 0.90 && r2 < 0.94)
     produce Turn(g) F(0.6*DL)  SB() Turn(-NA) B(N,2) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(NA)  B(N,1) EB()
             Turn(g) F(0.1*DL)  SB() Turn(-SA) B(S,1) EB()
             Turn(g) F(0.15*DL) SB() Turn(DA)  B(S,0) EB()
             Turn(g) F(0.05*DL) SB() EB() B(T,0);

   else if (r2 >= 0.94 && r2 < 0.97)
     produce Turn(g) F(0.6*DL) SB() Turn(-NA) B(N,2) EB() 
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0) EB()
             Turn(g) F(0.1*DL) SB() EB() B(T,0);
  
   else if (r2 >= 0.97 && r2 <= 1.0)
     produce Turn(g) F(0.6*DL) SB() Turn(NA)  B(N,2) EB() 
             Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0) EB()
             Turn(g) F(0.1*DL) SB() EB() B(T,0);
  }
  else if (type == S && status == 0.0){
   if (r2 < 0.037)
     produce Turn(g) F(0.85*SL) SB() Turn(-SA) B(S,1) EB()
             Turn(g) F(0.15*SL) SB() EB() B(S,0);

   else if (r2 >= 0.037 &&  r2 < 0.074)
     produce Turn(g) F(0.85*SL) SB() Turn(SA) B(S,1) EB()
             Turn(g) F(0.15*SL) SB() EB() B(S,0);

   else if (r2 >= 0.074 &&  r2 < 0.407)
     produce Turn(g) F(0.75*SL) SB() Turn(NA) B(S,1) EB()
             Turn(g) F(0.25*SL) SB() EB() B(S,0);
   
   else if (r2 >= 0.407 &&  r2 < 0.740)
     produce Turn(g) F(0.75*SL) SB() Turn(-NA) B(S,1) EB()
             Turn(g) F(0.25*SL) SB() EB() B(S,0);

   else if (r2 >= 0.740 &&  r2 < 0.844)
     produce Turn(g) F(0.6*DL) SB() Turn(NA)  B(N,2) EB() 
             Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0) EB()
             Turn(g) F(0.1*DL) SB() EB() B(T,0);  
   
   else if (r2 >= 0.844 &&  r2 < 0.948)
      produce Turn(g) F(0.6*DL) SB() Turn(-NA) B(N,2) EB() 
              Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1) EB()
              Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1) EB()
              Turn(g) F(0.1*DL) SB() Turn(SA)  B(S,0) EB()
              Turn(g) F(0.1*DL) SB() EB() B(T,0); 

   else if (r2 >= 0.948 &&  r2 < 0.974)
      produce Turn(g) F(0.6*SL) SB() Turn(NA)  B(N,2) EB() 
              Turn(g) F(0.1*SL) SB() Turn(-NA) B(N,1) EB()
              Turn(g) F(0.1*SL) SB() Turn(SA)  B(N,1) EB()
              Turn(g) F(0.1*SL) SB() Turn(-SA) B(S,0) EB()
              Turn(g) F(0.1*SL) SB() EB() B(T,0); 
   
   else if (r2 >= 0.974 &&  r2 <= 1.0)
      produce Turn(g) F(0.6*SL) SB() Turn(-NA) B(N,2) EB() 
              Turn(g) F(0.1*SL) SB() Turn(NA)  B(N,1) EB()
              Turn(g) F(0.1*SL) SB() Turn(-SA) B(N,1) EB()
              Turn(g) F(0.1*SL) SB() Turn(SA)  B(S,0) EB()
              Turn(g) F(0.1*SL) SB() EB() B(T,0); 	
  }  
  else if (type == N && status == 0.0){
   if (r2 < 0.39)
      produce  Turn(g) F(NL) SB() EB() B(N,0);

   else if (r2 >= 0.39 && r2 < 0.585)
      produce  Turn(g) F(0.75*NL) SB() Turn(NA) B(N,1) EB() 
               Turn(g) F(0.25) SB() EB() B(N,0);

   else if (r2 >= 0.585 && r2 < 0.780)
      produce  Turn(g) F(0.75*NL) SB() Turn(-NA) B(N,1) EB() 
               Turn(g) F(0.25) SB() EB() B(N,0);

   else if (r2 >= 0.780 && r2 < 0.890)
      produce  Turn(g) F(0.75*NL) SB() Turn(-NA) B(N,0) EB() 
               Turn(g) F(0.25) SB() EB() B(T,0);

   else if (r2 >= 0.890 && r2 <= 1.0)
      produce  Turn(g) F(0.75*NL) SB() Turn(NA) B(N,0) EB() 
               Turn(g) F(0.25) SB() EB() B(T,0);
  }
  else{
   double s = maximum(status-1.0,0.0);
   produce B(type,s);
  }
}



interpretation:

F(s) :
{
  ;
}



