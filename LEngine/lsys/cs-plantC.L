#include <mathsym.h>
using namespace cxxadt;

#include <lengine.h>

open CSPlantC;

#include <lsys.h>

module O();
module I();
module Turn(double);
module F(double);

derivation length: 26;

ignore: Turn F;

Start:
{
  produce F(0.1) I() F(0.1) I() F(0.1) I();
}

O() < O() > O():
{
  produce O();
}

O() < O() >  I():
{
  produce I();
}

O() < I() > O():
{
  produce O();
}

O() < I() >  I():
{
  produce I()SB() Turn(25.75*2.0*PI_VALUE/360.0) F(0.1) I() F(0.1) I() EB();
}

I() < O() > O():
{
  produce O();
}

I() < O() >  I():
{
  produce I() F(0.1) I();
}

I() < I() >  O():
{
  produce O();
}

I()  < I() > I():
{
  produce O();
}


Turn(a):
{
   produce Turn(-a);
}

interpretation:

F(s):
{
  ;
}

close CSPlantC;


