#line 2 "test.l"
#include <stdio.h>
#include <lglobal.h>
#include <lsysintrfc.h>

const float r = 0.025;
module F(float,int,float);
module P();
module M();

derivation length: 60;

Start:
{
  produce F(1,1,1) P F(1,1,1) P F(1,1,1) P F(1,1,1);
}


F(l, x, t) :
{
  if (t+r>1.0)
    produce F((t+r)/2,1,t+r-1) P F(t+r-1,2,t+r-1)
      M F(t+r-1,2,t+r-1) M F(t+r-1,2,t+r-1) F(t+r-1,2,t+r-1)
      P F(t+r-1,2,t+r-1) P F(t+r-1,2,t+r-1) M F((t+r)/2,1,t+r-1);
  else if ((x==1)&&(t+r<=1))
    produce F((t+r+1)/2,1,t+r);
  else if ((x==2)&&(t+r<=1))
    produce F(t+r,2,t+r);
}

interpretation:

F(l, x, t) :
{
  fprintf(fOut, "F(%f)", l);
}

P() :
{
  fprintf(fOut, "+");
}

M() :
{
  fprintf(fOut, "-");
}

