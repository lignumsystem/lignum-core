//Defines ran3 etc
#include <mathsym.h>
using namespace cxxadt;

//Defines headers necessary for lsystem
#include <lengine.h>

//Start the namespace (compiles to "namespace Pine{")
//The matching "close" statement closes the namespace 
open Birch;

//Defines the lsystem rewriting process. 
#include <lsystem.h>

const double a0 = 25.0*2.0*PI_VALUE/360.0;
const double a1 = 25.0*2.0*PI_VALUE/360.0;
const double d  = 137.5*2.0*PI_VALUE/360.0;
const double r1 = 1.0;
const double r2 = 0.5;

module B(int,double);
module F(double);
module Pitch(double);
module Roll(double);
module Turn(double);
module HRoll();

derivation length: 12;

Start:
{
  produce B(0,0.6);
}

B(order,l):
{
  if (order == 0)
    produce F(l) SB() Pitch(a0) B(1,l*r2) EB() Roll(-d) B(0,l*r1);
  else if (order == 1) 
    produce F(l) SB() Turn(-a1) HRoll() B(2,l*r2) EB() B(2,l*r1);
  else if (order == 2)
    produce F(l) SB() Turn(a1)  HRoll() B(2,l*r2) EB() B(1,l*r1);
}
interpretation:

F(s) :
{
  ;
}

close Birch;