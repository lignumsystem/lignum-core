#line 1 "test.l"
#include <stdio.h>
#include <string.h>
#include <lglobal.h>
#include <lsysintrfc.h>

derivation length: 8;

module A();
module B();
module C();
module D();
module E();
module F();
module G();
module H();
module I();
module J();
module K();
module L();

module Plus();
module Minus();

ignore: Plus Minus;

Start:
{
  produce A C D E SB Plus B SB Plus J EB  SB Plus K EB EB SB A EB C
            SB Minus D EB  SB Plus J EB E
            SB Plus F EB  SB Plus J EB SB A EB G
            SB Minus H EB  SB Plus J EB I
            SB Plus J EB  SB Plus J EB K;
}

A()  C() D() < E():
{
}

A() > SB()B()EB() C() E() SB()EB()  G() SB()H()EB() I() SB()J()EB() K() :
{
}
A() > C():
{
}

A() > C() SB() F() SB() K() EB() EB() E() G() SB() K() EB() I () K():
{
}

A() > SB() EB() C():
{
}
A() > C():
{
}

A() > C():
{
}



A() > SB() B() EB() C():
{
}

A() > SB()EB() C() :
{
  produce B;
}

A() > SB()EB() SB()EB() SB()EB() C():
{
}

A() > SB() J() EB() SB()EB() C():
{
}

interpretation:


Plus() :
{
  fprintf(fOut, "+");
}

Minus() :
{
  fprintf(fOut, "-");
}

A() :
{
  fprintf(fOut, ";(1)F");
}

B() :
{
  fprintf(fOut, ";(2)F");
}

SB() :
{
  fprintf(fOut, "[");
}

EB() : 
{
  fprintf(fOut, "]");
}



