#include <Tree.h>

namespace Lignum{

TreeParameters::TreeParameters()
{
  af = ar = lr = mf = 0.0;
  mr = ms = na = nl = pr = q = sr = ss = rho = xi = 0.0;
}

TreeAttributes::TreeAttributes()
{
  lb = 0.0;
  P = M = Wr = 0.0;
}

TreeTransitVariables::TreeTransitVariables()
  :lambda(0.0),g(9.81),eta(1.0/pow(10.0,3.0)),Er((7.993-(6.030e-1))*1000000.0),
   k(1.0/pow(10.0,12.0)),rhow(1000.0)
{
}

}//closing namespace Lignum

