
#include <TreeCompartment.h>
#include <stream.h>

TreeCompartment::TreeCompartment()
{
}

TreeCompartment::TreeCompartment(const Point<METER>& p, const PositionVector& d, 
				 Tree* t)
  :point(p),direction(d)
{
  tree = t;
}

TreeCompartment::~TreeCompartment()
{
}
