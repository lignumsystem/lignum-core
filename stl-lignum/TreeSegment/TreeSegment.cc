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
  SetAttributeValue(*this,omega,go);
  SetAttributeValue(*this,L,l);
  SetAttributeValue(*this,R,r);
  SetAttributeValue(*this,Rn,rn);

  //the first annual ring
  tsa.annual_rings.push_back(r);

  //compute the radius to foliage limit (Rf)
  //the given parameters are needle length (nl) and the
  //needle angle (na)
  //Rf = hf + tsa.R, where hf is height of the foliage (ihf = nl * sin(na))
  SetAttributeValue(*this,Rf,
		    GetParameterValue(*t,nl) * 
		    sin((double)GetParameterValue(*t,na)) + 
		    GetAttributeValue(*this,R));

  //compute the initial mass of the foliage
  //1. compute the surface area (sa) of the cylinder representing foliage
  TP sa =  2.0 * PI_VALUE * GetAttributeValue(*this,Rf) * GetAttributeValue(*this,L);
  //2. the mass of the foliage (Wf = sa * af) 
  TP wf =  sa * GetParameterValue(*t,af);
  SetAttributeValue(*this,Wf,sa*GetParameterValue(*t,af));

  //compute the sapwood mass
  SetAttributeValue(*this,Ws,GetSapwoodMass(*this)); 
}

TreeSegment::~TreeSegment()
{
}

void TreeSegment::Production()
{
  TP p = 5.0; //GetParameterValue(*tree,pr) * GetAttributeValue(*this,Qabs);
  SetAttributeValue(*this,P,p);
}

TP TreeSegment::GetProduction()
{
  return GetAttributeValue(*this,P);
}
