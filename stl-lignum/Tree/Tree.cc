#include <Tree.h>

TreeParameters::TreeParameters()
{
  af = ar = lr = mf = 0.0;
  mr = ms = na = nl = pr = q = sr = ss = rho = xi = 0.0;
}

TreeAttributes::TreeAttributes()
{
  age = 0; lb = 0.0;
  P = M = Wr = 0.0;
}

TreeTransitVariables::TreeTransitVariables()
{
  lambda = 0.0;
}

Tree::Tree()
{
  tree = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
Tree::Tree(const Point<METER>& p, const PositionVector& d)
  :TreeCompartment(p,d,this),axis(p,d,this)
{
  Bud* bud = new Bud(p,d,1.0,this);
  InsertTreeCompartment(axis,bud);
}
  

#ifdef TREE
#include <stdlib.h>
#include <iostream.h>

int main()
{
  cout << "OK" << endl;
  exit(0);
}

#endif
