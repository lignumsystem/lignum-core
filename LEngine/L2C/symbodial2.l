#line 2 "test.l"
#include <stdio.h>
#include <lglobal.h>
#include <lsysintrfc.h>
 
const double PI =  3.1415926535897932384; 
const double R = 1.456;
module F(double);
module A();
module B();
module Turn(double);
module Pitch(double);


derivation length: 3;

Start:
{
  produce A();
}

A():
{
  produce F(0.3) SB() Turn(PI/2.0) A() EB() 
                 SB() Turn(-PI/2.0) A() EB()
          B();
}

F(s) :
{
  produce F(s*R);
}

interpretation:

F(s) :
{
  ;
}
