#include "stdafx.h"
#include <Tree.h>

namespace Lignum{

  TreeParameters::TreeParameters()
  {
    af = ar = lr = mf = 0.0;
    mr = ms = na = nl = pr = q = sf = sr = ss = rhoW = xi = 0.0;
  }

  //Initialize the vector with negative value
  //It might capture some situations if user
  //check the value before it is set.
  TreeAttributes::TreeAttributes(int size)
    :v(size,0.0)
  {
  }


}//closing namespace Lignum

