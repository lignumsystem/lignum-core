#line 2 "test.l"
#include <lglobal.h>
#include <lsysintrfc.h>

module l();
module r();
module F();
module Left();
module Right();

derivation length: 10;

Start:
{
  produce l;
}

l() :
{
  produce Left l Right Right r Left;
}

r() :
{
  produce Right l Left Left r Right;
}

