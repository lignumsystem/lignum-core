#include <TreeSegment.h>
#include <Tree.h>

TreeSegmentAttributes::TreeSegmentAttributes()
  :age(0),M(0.0),L(0.0),omega(0.0),P(0.0),Qin(0.0),Qabs(0.0),
   R(0.0),Rn(0.0)
{
}
TreeSegment::TreeSegment()
{
  tree = NULL;
}

TreeSegment::TreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
			 const METER l, const METER r, const METER rn, Tree* t)
  :TreeCompartment(p,d,t)
{
  tsa.omega = go;
  tsa.L = l;
  tsa.R = r;
  tsa.Rn = rn;

  //the first annual ring
  tsa.annual_rings.push_back(r);

  //compute the radius to foliage limit (Rf)
  //the given parameters are needle length (nl) and the
  //needle angle (na)
  //Rf = hf + tsa.R, where hf is height of the foliage (ihf = nl * sin(na))
  tsa.Rf = GetParameterValue(*tree,nl) * sin((double)GetParameterValue(*tree,na)) + 
    tsa.R;

  //compute the initial mass of the foliage
  //1. compute the surface area (Af) of the cylinder representing foliage
  TP Af =  (2.0 * PI_VALUE * tsa.Rf) * tsa.L;
  //2. the mass of the foliage (Wf = Af * af) 
  tsa.Wf = Af * GetParameterValue(*tree,af);

  //compute the sapwood mass
  tsa.Ws = GetSapwoodMass(*this); 
}

TreeSegment::~TreeSegment()
{
}
