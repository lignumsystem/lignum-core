#include <mathsym.h>
using namespace cxxadt;

#include <lengine.h>

open CSPlantD;

#include <lsystem.h>

module O();
module I();
module Turn(double);
module F(double);

derivation length: 24;

ignore: Turn F;

Start:
{
  produce F(0.1) O() F(0.1) I() F(0.1) I();
}

O() < O() > O():
{
  produce I();
}

O() < O() >   I() :
{
  produce O();
}

O() < I() > O():
{
  produce O();
}

O() < I() >  I():
{
  produce I() F(0.1) I();
}

I() < O() > O():
{
  produce I();
}

I() < O() >  I():
{
  produce I()SB() Turn(25.75*2.0*PI_VALUE/360.0) F(0.1) I() F(0.1) I() EB();
}

I() < I() >  O():
{
  produce I();
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

close CSPlantD;


