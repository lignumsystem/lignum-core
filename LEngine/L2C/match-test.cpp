#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <lglobal.h>
#include <lsysintrfc.h>         
#include <succstor.h>

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

derivation length: 51 - strlen("module and produce");

module A();
module B(int,float);
module C();
module D(int,int);
module E();
module F();
module G();
module H();
module I(int);
module J();
module K();
module L();
module Plus();
module Minus();

ignore: Plus Minus;

Start:
{
  /*Axiom A [B(1,2.0) [C D(3,4) E] F G] [H I(5) J] K L*/
  produce A() SB()Plus()B(1,2.0) SB()Minus()C()D(3,4)E()EB() F()G()EB() SB()H()I(5)J()EB() K()L();
}

End:
{
}


A() >  SB() B(a,b)  EB() :
{
  produce B(a,b) A();
}

A() >   SB() B(a,b) SB() C() EB() EB() :
{
  produce A() SB() B(a,b)  C() EB();
}

A() > SB() B(a,b) SB() C() EB() F() EB() :
{
  produce A() SB() C() EB() B(a,b) F();
}

A() > SB() EB()  SB() H() I(c) EB()  :
{
  produce  A() I(c) H();
}

A() > SB() B(a,b) EB() SB() H() EB() K():
{
  produce A() SB()B(a,b)EB() SB()H()EB() K() L();
}

A()K() < L():
{
  produce L()I(1);
}

A() SB() B(a,b) SB() C()   < D(c,d):
{
  produce D(c,d) I(1);
}



Plus() :
{

}

Minus() :
{

}
           