#line 2 "test.l"
#include <stdio.h>
#include <lglobal.h>
#include <lsysintrfc.h>

const float R = 1.456;
module F(double);
module A();
module B();
module Turn(double);


derivation length: 1;

Start:
{
  produce A();
}

A():
{
  produce F(1) SB() Turn(60.0) A() EB() SB() Turn(-60.0) A() EB() B();
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
