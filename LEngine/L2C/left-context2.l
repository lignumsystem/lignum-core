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

module Plus();
module Minus();

ignore: Plus Minus;

Start:
{
  produce A SB Plus B EB  SB Plus J EB C
            SB Minus D EB  SB Plus J EB E
            SB Plus F EB  SB Plus J EB G
            SB Minus H EB  SB Plus J EB I
            SB Plus J EB  SB Plus J EB K;
}

B() < A() :
{
  produce B;
}

A() C() E() G() I ()< K():
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



