#line 1 "test.l"
#include <stdio.h>
#include <string.h>
#include <lglobal.h>
#include <lsysintrfc.h>

derivation length: 8;

module A();
module B();
module Plus();
module Minus();

ignore: Plus Minus;

Start:
{
  produce B SB Plus A EB A
            SB Minus A EB A
            SB Plus A EB A
            SB Minus A EB A
            SB Plus A EB A;
}

B() < A() :
{
  produce B;
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

