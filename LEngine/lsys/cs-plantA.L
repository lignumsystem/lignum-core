#include <mathsym.h>
using namespace cxxadt;

#include <lengine.h>

open CSPlantA;

#include <lsystem.h>

module O();
module I();
module Turn(double);
module F(double);

derivation length: 30;

ignore: Turn F;

Start:
{
  produce F(0.1) I() F(0.1) I() F(0.1) I();
}

O() < O() > O():
{
  produce O();
}

O() < O() >   I() :
{
  produce I() SB() Turn(22.5*2.0*PI_VALUE/360.0) F(0.1) I() F(0.1) I() EB();
}

O() < I() > O():
{
  produce I();
}

O() < I() >  I():
{
  produce I();
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

close CSPlantA;


