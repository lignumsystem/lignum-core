//Defines ran3 etc
#include <mathsym.h>
using namespace cxxadt;

//Defines headers necessary for lsystem
#include <lengine.h>

//Start the namespace (compiles to "namespace Pine{")
//The matching "close" statement closes the namespace 
open Pine;

//Defines the lsystem rewriting process. 
#include <lsystem.h>

const double d1 = 0.8;
const double d2 = 0.6;
const double d3 = 0.5;
const double d4 = 0.4;

const double PI = 3.1415926535897932384;
const double angle = PI/4.0;
const double bend = 1.09;

module F(double);
module B(int,double);
module Pitch(double);
module Roll(double);
module Turn(double);

derivation length: 9;

Start:
{
  produce B(1,1.0);
}

B(A,l):
{
   if (A==1)
   produce F(l) SB() Pitch(PI/4.0)  B(A+1,l*d2) EB() 
                SB() Roll(PI/2.0) Pitch(PI/4.0) B(A+1,l*d2) EB()
                SB() Roll(PI) Pitch(PI/4.0) B(A+1,l*d2) EB() 
                SB() Roll(3.0*PI/2.0) Pitch(PI/4.0)  B(A+1,l*d2) EB()
           B(A,l*d1);
  else if (A==2)
  produce F(l) SB() Turn(PI/4.0)  B(A+1,l*d3) EB() 
                SB() Turn(-PI/4.0) B(A+1,l*d3) EB()
          Pitch(-0.1)B(A,l*d2);
  else if (A==3)
  produce F(l) SB() Turn(PI/4.0)  B(A+1,l*d4) EB() 
                  SB() Turn(-PI/4.0) B(A+1,l*d4) EB()
           B(A,l*d3);
  else if (A==4)
  produce F(l) SB() B(A+1,l)  EB() B(A,l);
  else
  produce B(A,l);          
}

F(s):
{
  produce F(s);
}

Pitch(a):
{
  produce Pitch(a*bend);
}

Turn(a):
{
  produce Turn(a*bend);
}

//This interpretation  is a ToDo for me.
//Now you must define at least one dummy interpretation.
//I must study how to alter the l2c to avoid  interpretation. 
//Interpretation separates model/symbols from 
//their (graphics) interpretation but for us LIGNUM is visualized by 
//Mika.  
interpretation:

F(s) :
{
  ;
}

//Closes the namespace (compiles simply to '}')
close Pine;
