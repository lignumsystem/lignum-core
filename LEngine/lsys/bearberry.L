#include <Lsystem.h>
#include <mathsym.h>
using namespace cxxadt;


const int D    = 1.0; //dominant    apical
const int S    = 2.0; //subdominant apical
const int T    = 3.0; //subdominant lateral
const int N    = 4.0; //nondominant apical
const int O    = 5.0; //nondominat  lateral

//const double COMP = 0.7;  /*7.4/5.1 sandpit/restore */ 
const double DL = 1;      /* =7.4 cm */
const double SL = 0.57;   /* 4.2/7.4 */
const double NL = 0.32;   /* 2.4/7.4 */
const double DA = 30*2.0*PI_VALUE/360.0;
const double SA = 30*2.0*PI_VALUE/360.0;
const double NA = 30*2.0*PI_VALUE/360.0;
const double CU = -5.0*2.0*PI_VALUE/360.0;
const double CT = 0.5*2.0*PI_VALUE/360.0;

module F(double);
module B(double,double,double); //type, status and collision
module Turn(double);

derivation length: 10;
int seed = 0;

Start:
{
  int init = -1;
  int seed = 137591;
  ran3(&init);
  produce F(0.1*DL) SB() EB() B(D,0.0,0.0);
}

B(type,status,coll):
{
  double g = 0.0;
  double r1 = ran3(&seed);
  double r2 = ran3(&seed);
  
  if (r1 < CT)
     g = CU;
  else 
     g = -CU;

  if (coll == 1.0){
    produce B(type,status,coll);
  }
  else if (type == D && status == 0.0){
    if (r2 < 0.26)
      produce Turn(g) F(0.6*DL) SB() Turn(NA)  B(N,2,coll) EB() 
              Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1,coll) EB()
              Turn(g) F(0.1*DL) SB() Turn(SA)  B(S,1,coll) EB()
              Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0,coll) EB()
              Turn(g) F(0.1*DL) SB() EB() B(D,0,coll);
  
   else if (r2 < 0.52)
     produce Turn(g) F(0.6*DL) SB() Turn(-NA) B(N,2,coll) EB() 
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(SA)  B(S,0,coll) EB()
             Turn(g) F(0.1*DL) SB() EB() B(D,0,coll);
   
   else if (r2 < 0.69)
     produce Turn(g) F(0.6*DL)  SB() Turn(-NA) B(N,2,coll) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.1*DL)  SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(DA)  B(S,0,coll) EB()
             Turn(g) F(0.05*DL) SB() EB() B(D,0,coll);
  
   else if (r2 < 0.86)
     produce Turn(g) F(0.6*DL)  SB() Turn(NA)  B(N,2,coll) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.1*DL)  SB() Turn(SA)  B(S,1,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-DA) B(S,0,coll) EB()
             Turn(g) F(0.05*DL) SB() EB() B(D,0,coll);

   else if (r2 < 0.90)
     produce Turn(g) F(0.6*DL)  SB() Turn(NA)  B(N,2,coll) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.1*DL)  SB() Turn(SA)  B(S,1,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-DA) B(S,0,coll) EB()
             Turn(g) F(0.05*DL) SB() EB() B(T,0,coll);

   else if (r2 < 0.94)
     produce Turn(g) F(0.6*DL)  SB() Turn(-NA) B(N,2,coll) EB() 
             Turn(g) F(0.1*DL)  SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.1*DL)  SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(DA)  B(S,0,coll) EB()
             Turn(g) F(0.05*DL) SB() EB() B(T,0,coll);

   else if (r2 < 0.97)
     produce Turn(g) F(0.6*DL) SB() Turn(-NA) B(N,2,coll) EB() 
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0,coll) EB()
             Turn(g) F(0.1*DL) SB() EB() B(T,0,coll);
  
   else if (r2 <= 1.0)
     produce Turn(g) F(0.6*DL) SB() Turn(NA)  B(N,2,coll) EB() 
             Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0,coll) EB()
             Turn(g) F(0.1*DL) SB() EB() B(T,0,coll);
  }
  else if (type == S && status == 0.0){
   if (r2 < 0.037)
     produce Turn(g) F(0.85*SL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.15*SL) SB() EB() B(S,0,coll);

   else if (r2 < 0.074)
     produce Turn(g) F(0.85*SL) SB() Turn(SA) B(S,1,coll) EB()
             Turn(g) F(0.15*SL) SB() EB() B(S,0,coll);

   else if (r2 < 0.407)
     produce Turn(g) F(0.75*SL) SB() Turn(NA) B(S,1,coll) EB()
             Turn(g) F(0.25*SL) SB() EB() B(S,0,coll);
   
   else if (r2 < 0.740)
     produce Turn(g) F(0.75*SL) SB() Turn(-NA) B(S,1,coll) EB()
             Turn(g) F(0.25*SL) SB() EB() B(S,0,coll);

   else if (r2 < 0.844)
     produce Turn(g) F(0.6*DL) SB() Turn(NA)  B(N,2,coll) EB() 
             Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.1*DL) SB() Turn(-SA) B(S,0,coll) EB()
             Turn(g) F(0.1*DL) SB() EB() B(T,0,coll);  
   
   else if (r2 < 0.948)
      produce Turn(g) F(0.6*DL) SB() Turn(-NA) B(N,2,coll) EB() 
              Turn(g) F(0.1*DL) SB() Turn(NA)  B(N,1,coll) EB()
              Turn(g) F(0.1*DL) SB() Turn(-NA) B(N,1,coll) EB()
              Turn(g) F(0.1*DL) SB() Turn(SA)  B(S,0,coll) EB()
              Turn(g) F(0.1*DL) SB() EB() B(T,0,coll); 

   else if (r2 < 0.974)
      produce Turn(g) F(0.6*SL) SB() Turn(NA)  B(N,2,coll) EB() 
              Turn(g) F(0.1*SL) SB() Turn(-NA) B(N,1,coll) EB()
              Turn(g) F(0.1*SL) SB() Turn(SA)  B(N,1,coll) EB()
              Turn(g) F(0.1*SL) SB() Turn(-SA) B(S,0,coll) EB()
              Turn(g) F(0.1*SL) SB() EB() B(T,0,coll); 
   
   else if (r2 <= 1.0)
      produce Turn(g) F(0.6*SL) SB() Turn(-NA) B(N,2,coll) EB() 
              Turn(g) F(0.1*SL) SB() Turn(NA)  B(N,1,coll) EB()
              Turn(g) F(0.1*SL) SB() Turn(-SA) B(N,1,coll) EB()
              Turn(g) F(0.1*SL) SB() Turn(SA)  B(S,0,coll) EB()
              Turn(g) F(0.1*SL) SB() EB() B(T,0,coll); 	
  }  
  else if (type == N && status == 0.0){
   if (r2 < 0.39)
      produce  Turn(g) F(NL) SB() EB() B(N,0,coll);

   else if (r2 < 0.585)
      produce  Turn(g) F(0.75*NL) SB() Turn(NA) B(N,1,coll) EB() 
               Turn(g) F(0.25) SB() EB() B(N,0,coll);

   else if (r2 < 0.780)
      produce  Turn(g) F(0.75*NL) SB() Turn(-NA) B(N,1,coll) EB() 
               Turn(g) F(0.25) SB() EB() B(N,0,coll);

   else if (r2 < 0.890)
      produce  Turn(g) F(0.75*NL) SB() Turn(-NA) B(N,0,coll) EB() 
               Turn(g) F(0.25) SB() EB() B(T,0,coll);

   else if (r2 <= 1.0)
      produce  Turn(g) F(0.75*NL) SB() Turn(NA) B(N,0,coll) EB() 
               Turn(g) F(0.25) SB() EB() B(T,0,coll);
  }
  else{
   double s = maximum(status-1.0,0.0);
   produce B(type,s,coll);
  }
}



interpretation:

F(s) :
{
  ;
}






