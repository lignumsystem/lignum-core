
#include <BranchingPoint.h>

void InsertTerminatingBud(BranchingPoint& bp, Bud* bud)
{
  Axis *axis = new Axis();
  
  InsertTreeCompartment(*axis,bud);
  bp.axis_ls.push_back(axis);
}
