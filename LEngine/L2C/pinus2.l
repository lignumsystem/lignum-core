#line 2 "pinus.l"
#include <stdio.h>
#include <lglobal.h>
#include <lsysintrfc.h>

const double L1 = 1.0;
const double L2 = 0.6;
const double L3 = 0.4;
const double L4 = 0.3;
const double L5 = 0.2;
const double L6 = 0.1;
const double PI = 3.1415926535897932384;

module F(double);
module B(int,int,int);
module Pitch(double);
module Roll(double);
module Turn(double);

derivation length: 6;

Start:
{
  produce B(1,1,1);
}

B(A,a,l):
{
   if (A==1)
   produce F(L1) SB() Pitch(PI/4.0)  B(A+1,a,l) EB() 
                 SB() Pitch(-PI/4.0) B(A+1,a,l) EB()
                 SB() Turn(PI/4.0)   B(A+1,a,l) EB() 
                 SB() Turn(-PI/4.0)  B(A+1,a,l) EB()
           B(A,a,l);
  else if (A==2)
  produce F(L3) SB() Pitch(PI/4.0)  B(A+1,a,l) EB() 
                SB() Pitch(-PI/4.0) B(A+1,a,l) EB()
          B(A,a,l);
  else if (A==3)
  produce F(L6) SB() Pitch(PI/4.0)  B(A+1,a,l) EB() 
                SB() Pitch(-PI/4.0) B(A+1,a,l) EB()
           B(A,a,l);
  else 
  produce B(A,a,l);
          
}



interpretation:

F(s) :
{
  ;
}
