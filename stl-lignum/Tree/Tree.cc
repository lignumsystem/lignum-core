#include "stdafx.h"
#include <Tree.h>

namespace Lignum{

  TreeParameters::TreeParameters():
    af(0.0),aleafmax(0.0),ar(0.0),dof(0.0),
    lr(0.0),mf(0.0),mr(0.0),ms(0.0),na(0.0),
    nl(0.0),pr(0.0),q(0.0),rhoW(0.0),rho_hair(0.0),
    rho_root(0.0),sf(0.0),sr(0.0),ss(0.0),tauL(0.0),
    yc(0.0),xi(0.0),zbrentEpsilon(0.0)
  {
  }

  //Initialize the vector with negative value
  //It might capture some situations if user
  //check the value before it is set.
  TreeAttributes::TreeAttributes(int size)
    :v(size,0.0)
  {
  }


}//closing namespace Lignum

