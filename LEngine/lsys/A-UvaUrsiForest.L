//Defines ran3 etc.
#include <mathsym.h>
using namespace cxxadt;

//Defines headers necessary for lsys.h
#include <lengine.h>

//Start the namespace Bearberry
//Matching "close" closes it
open Bearberry;

//Defines lsystem rewriting process 
#include <lsys.h>


const int D    = 1.0; //dominant    apical
const int S    = 2.0; //subdominant apical
const int T    = 3.0; //subdominant lateral
const int N    = 4.0; //nondominant apical
const int O    = 5.0; //nondominat  lateral

//const double COMP = 0.7;  /*7.4/5.1 sandpit/restore */ 
const double DL = 1;      /* =4 cm */
const double SL = 0.58;  
const double NL = 0.40;  
const double DA = 30*2.0*PI_VALUE/360.0;
const double SA = 31*2.0*PI_VALUE/360.0;
const double NA = 52*2.0*PI_VALUE/360.0;
const double CU = -5.0*2.0*PI_VALUE/360.0;
const double CT = 0.5*2.0*PI_VALUE/360.0;

module F(double);
module B(double,double,double); //Bud: type,status and collision
module Turn(double);

derivation length: 15;
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
    if (r2 < 0.0875)
      produce Turn(g) F(0.70*DL) SB() Turn(NA)  B(N,2,coll) EB() 
              Turn(g) F(0.15*DL) SB() Turn(-DA) B(D,0,coll) EB()
              Turn(g) F(0.15*DL) SB() EB() B(D,0,coll);
  
   else if (r2 < 0.175)
     produce Turn(g) F(0.70*DL) SB() Turn(-NA)  B(N,2,coll) EB() 
             Turn(g) F(0.15*DL) SB() Turn(DA) B(D,0,coll) EB()
             Turn(g) F(0.15*DL) SB() EB() B(D,0,coll);
   
   else if (r2 < 0.3500)
     produce Turn(g) F(0.80*DL) SB() EB() 
             Turn(g) F(0.20*DL) SB() EB() B(D,0,coll);   
  
   else if (r2 < 0.4375)
     produce Turn(g) F(0.70*DL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.30*DL) SB() EB() B(D,0,coll);

   else if (r2 < 0.5250)
     produce Turn(g) F(0.70*DL) SB() Turn(NA) B(N,1,coll) EB()
             Turn(g) F(0.30*DL) SB() EB() B(D,0,coll); 

   else if (r2 < 0.6125)
     produce Turn(g) F(0.65*DL) SB() Turn(NA)  B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-SA) B(S,0,coll) EB()
             Turn(g) F(0.20*DL) SB() EB() B(D,0,coll);
 
   else if (r2 < 0.7000)
     produce Turn(g) F(0.65*DL) SB() Turn(-NA) B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(SA)  B(S,0,coll) EB()
             Turn(g) F(0.20*DL) SB() EB() B(D,0,coll);

   else if (r2 < 0.7750)
     produce Turn(g) F(0.65*DL) SB() Turn(-NA) B(N,2,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(SA)  B(S,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(-DA) B(D,0,coll) EB()
             Turn(g) F(0.15*DL) SB() EB() B(T,0,coll);
   else if (r2 < 0.8500)
     produce Turn(g) F(0.65*DL) SB() Turn(NA)  B(N,2,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(DA)  B(D,0,coll) EB()
             Turn(g) F(0.15*DL) SB() EB() B(T,0,coll);
   else if (r2 < 0.9175)
     produce Turn(g) F(0.55*DL) SB() Turn(NA)  B(N,2,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(SA)  B(S,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(-DA) B(D,0,coll) EB()
             Turn(g) F(0.15*DL) SB() EB() B(T,0,coll);
   else if (r2 < 0.985)
     produce Turn(g) F(0.55*DL) SB() Turn(-NA) B(N,2,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(DA)  B(D,0,coll) EB()
             Turn(g) F(0.15*DL) SB() EB() B(T,0,coll); 
   else if (r2 <= 1.0)
     produce Turn(g) F(0.50*DL) SB() Turn(-NA) B(N,2,coll) EB() 
             Turn(g) F(0.10*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.10*DL) SB() Turn(SA)  B(S,0,coll) EB()
             Turn(g) F(0.20*DL) SB() EB() B(T,0,coll);
  } 
  else if (type == S && status == 0.0){
    if (r2 < 0.257)
     produce Turn(g) F(0.65*SL) SB() Turn(NA)  B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.20)    SB() EB() B(S,0,coll);
    else if (r2 < 0.514)
     produce Turn(g) F(0.65*SL) SB() Turn(-NA) B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(SA)  B(S,1,coll) EB()
             Turn(g) F(0.20)    SB() EB() B(S,0,coll);
    else if (r2 < 0.647)
     produce Turn(g) F(0.60*SL) SB() Turn(NA)  B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.25)    SB() EB() B(S,0,coll); 
    else if (r2 < 0.780)
     produce Turn(g) F(0.60*SL) SB() Turn(-NA) B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(NA)  B(N,1,coll) EB()
             Turn(g) F(0.25)    SB() EB() B(S,0,coll);    
    else if (r2 < 0.853)
     produce Turn(g) F(0.70*SL) SB() Turn(SA)  B(S,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.15)    SB() EB() B(T,0,coll);
    else if (r2 < 0.926)
     produce Turn(g) F(0.70*SL) SB() Turn(-SA) B(S,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(SA)  B(S,1,coll) EB()
             Turn(g) F(0.15)    SB() EB() B(T,0,coll);
    else if (r2 < 0.963)
     produce Turn(g) F(0.65*SL) SB() Turn(NA)  B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(-SA) B(S,1,coll) EB()
             Turn(g) F(0.20)    SB() EB() B(T,0,coll);
    else if (r2 <= 1.0)
     produce Turn(g) F(0.65*SL) SB() Turn(-NA)  B(N,2,coll) EB()
             Turn(g) F(0.15*DL) SB() Turn(SA) B(S,1,coll) EB()
             Turn(g) F(0.20)    SB() EB() B(T,0,coll);   
  }  

  else if (type == N && status == 0.0){
    if (r2 < 0.630)
     produce Turn(g) F(NL) SB() EB() B(N,0,coll);
    else if (r2 < 0.815)
     produce Turn(g) F(0.75*NL) SB() Turn(NA) B(N,1,coll) EB()
             Turn(g) F(0.25)    SB() EB() B(T,0,coll);
    else if (r2 <= 1.0)
     produce Turn(g) F(0.75*NL) SB() Turn(-NA) B(N,1,coll) EB()
             Turn(g) F(0.25)    SB() EB() B(T,0,coll);
  }

  else{
   double s = maximum(status-1.0,0.0);
   produce B(type,s,coll);
  }

}

//This interpretation  is a ToDo for me.
//Now you must define at least one dummy interpretation.
//I must study how to alter the l2c to avoid  interpretation. 
//Interpretation separates model/symbols from 
//their (graphics) interpretation but for us LIGNUM is visualized by 
//Mika.  
interpretation:

F(s):
{
  ;
}

//Closes the namespace (compiles simply to '}')
close Bearberry;



