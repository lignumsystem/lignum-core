#line 1 "test.l"
#include <stdio.h>
#include <string.h>
#include <lglobal.h>
#include <lsysintrfc.h>

#define STEPS 30

derivation length: STEPS;

module F();
module Plus();
module Minus();
module IncClr();
module DecWdth();
module IncElast();
module Zero();
module One();

ignore: Plus Minus IncElast IncClr DecWdth F;


Start:
{
  produce F One F One F One;
}


Zero() < Zero() > Zero() :
{
  produce Zero;
}

Zero() < Zero() > One() :
{
  produce One SB IncClr DecWdth IncElast Minus F One F One EB;
}

Zero() < One() > Zero() :
{
  produce One;
}

Zero() < One() > One() :
{
  produce One;
}

One() < Zero() > Zero() :
{
  produce Zero;
}

One() < Zero() > One() :
{
  produce One F One;
}

One() < One() > Zero() :
{
  produce One;
}

One() < One() > One() :
{
  produce Zero;
}

Minus() :
{
  produce Plus;
}

Plus() :
{
  produce Minus;
}



interpretation:

F() :
{
  fprintf(fOut, "F");
}


Plus() :
{
  fprintf(fOut, "+");
}

Minus() :
{
  fprintf(fOut, "-");
}

SB() :
{
  fprintf(fOut, "[");
}

EB() : 
{
  fprintf(fOut, "]");
}

IncClr() :
{
  fprintf(fOut, ";");
}

DecWdth() :
{
  fprintf(fOut, "!");
}

IncElast() :
{
  fprintf(fOut, "_");
}

One():
{
  fprintf(fOut, "1");
}

Zero():
{
  fprintf(fOut, "0");
}



/***********

#define STEPS 30
lsystem: 0
derivation length: STEPS
ignore: +-_;!F

axiom: F1F1F1

0 < 0 > 0 --> 0
0 < 0 > 1 --> 1[;!_-F1F1]
0 < 1 > 0 --> 1
0 < 1 > 1 --> 1
1 < 0 > 0 --> 0
1 < 0 > 1 --> 1F1
1 < 1 > 0 --> 1
1 < 1 > 1 --> 0
* < - > * --> +
* < + > * --> -

endlsystem



*************/
