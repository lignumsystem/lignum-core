#include <mathsym.h>
using namespace cxxadt;

#include <lengine.h>

open CSPlant;

#include <lsystem.h>

module One();
module Zero();
module Turn(double);
module F(double);
module B();

derivation length: 30;

ignore: Turn F B;

Start:
{
  produce F(1.0) One() F(1.0) One() F(1.0) One();
}

Zero() < Zero() > Zero():
{
  cout << "Zero() < Zero() > Zero()" << endl;
  produce Zero();
}

Zero() < Zero() > One() :
{
  cout << "Zero() < Zero() > One()" << endl;
  produce One() SB() Turn(-22.5*2*PI_VALUE/360) F(1.0) One() F(1.0) One() EB();
}

Zero() < One() > Zero():
{
  cout << "Zero() < One() > Zero()" << endl;
  produce One();
}

Zero() < One() > One():
{
  cout << "Zero() < One() > One()" << endl;
  produce One();
}

One() < Zero() > Zero():
{
  cout << "One() < Zero() > Zero()" << endl;
  produce Zero();
}

One() < Zero() > One():
{
  cout << "One() < Zero() > One()" << endl;
  produce One() F(1.0) One();
}

One() < One() > Zero():
{
  cout << "One() < One() > Zero()" << endl;
  produce One();
}

One()  < One() > One():
{
  cout << "One()  < One() > One()" << endl;
  produce Zero();
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

close CSPlant;


