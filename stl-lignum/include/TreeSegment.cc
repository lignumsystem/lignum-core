#include <TreeSegment.h>
#include <Tree.h>

TreeSegmentAttributes::TreeSegmentAttributes()
  :age(0),M(0.0),L(0.0),omega(0.0),P(0.0),Qin(0.0),Qabs(0.0),
   R(0.0),Rn(0.0),Pr(1.0),fin(0.0),fout(0.0)
{
}

template <class TS,class BUD>
TreeSegment<TS,BUD>::TreeSegment()
{
  tree = NULL;
}


template <class TS,class BUD>
TreeSegment<TS,BUD>::TreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
			     const METER l, const METER r, const METER rn, Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
  SetTSAttributeValue(*this,omega,go);
  SetTSAttributeValue(*this,L,l);
  SetTSAttributeValue(*this,R,r);
  SetTSAttributeValue(*this,Rn,rn);

  //the first annual ring
  tsa.annual_rings.push_back(r);

  //compute the radius to foliage limit (Rf)
  //the given parameters are needle length (nl) and the
  //needle angle (na)
  //Rf = hf + tsa.R, where hf is height of the foliage (hf = nl * sin(na))
  SetTSAttributeValue(*this,Rf,
		      GetTreeParameterValue(*t,nl) * 
		      sin((double)GetTreeParameterValue(*t,na)) + 
		      GetTSAttributeValue(*this,R));

  //compute the initial mass of the foliage
  //1. compute the surface area (sa) of the cylinder representing foliage
  TP sa =  2.0 * PI_VALUE * GetTSAttributeValue(*this,Rf) * GetTSAttributeValue(*this,L);
  //2. the mass of the foliage (Wf = sa * af) 
  TP wf =  sa * GetTreeParameterValue(*t,af);
  SetTSAttributeValue(*this,Wf,sa*wf);

  //compute the sapwood mass
  SetTSAttributeValue(*this,Ws,GetSapwoodMass(*this)); 

  //compute the initial pressure in the TreeSegment    
  SetTSAttributeValue(*this, Wm, 0.5 * 1000 * l * r * r * PI_VALUE);
  SetTSAttributeValue(*this, Pr, (-p.getZ()-l/2) * 9.81 * 1000);   
}

template <class TS,class BUD>
TreeSegment<TS,BUD>::~TreeSegment()
{
}


//This method returns the amount[kg] of transpired water. 
//Time interval[s] is given as parameter
template <class TS,class BUD>
TP TreeSegment<TS,BUD>::GetTranspiration(TP time)
{
  return 0.12e-9;
}


template <class TS,class BUD>
list<METER> GetAnnualRings(const TreeSegment<TS,BUD>& ts)
{
  return ts.tsa.annual_rings;
}

template <class TS,class BUD>
KGC GetSapwoodMass(const TreeSegment<TS,BUD>& ts)
{
  //volume up to R
  TP V1 = (PI_VALUE * pow((double)ts.tsa.R,2.0)) * ts.tsa.L;
  //heartwood volume
  TP V2 = (PI_VALUE * pow((double)ts.tsa.Rn,2.0)) * ts.tsa.L;
  //sapwood volume
  TP V3 = V1 - V2;

  //mass is density * volume
  return GetTreeParameterValue(*(ts.tree),rho) * V3;
}

template <class TS,class BUD>
TP GetTSAttributeValue(const TreeSegment<TS,BUD>& ts, const TAD name)
{
  TP unknown_value = 0.0;

  if (name == area)
    return PI_VALUE*pow(ts.tsa.R,2.0);

  else if (name == fin)
    return ts.tsa.fin;
  
  else if (name == fout)
    return ts.tsa.fout;
  
  else if (name == H)
    return ts.point.getZ();

  else if (name == L)
    return ts.tsa.L;

  else if (name == Pr)
    return ts.tsa.Pr;

  else if (name == M)
    return ts.tsa.M;

  else if (name == omega)
    return ts.tsa.omega;

  else if (name == P)
    return ts.tsa.P;

  else if (name == Qin)
    return ts.tsa.Qin;

  else if (name == Qabs)
    return ts.tsa.Qabs;

  else if (name == R)
    return ts.tsa.R;

  else if (name == Rf)
    return ts.tsa.Rf;

  else if (name == Rn)
    return ts.tsa.Rn;

  else if (name == Wf)
    return ts.tsa.Wf;

  else if (name == Wm)
    return ts.tsa.Wm;

  else if (name == Ws)
    return ts.tsa.Ws;

  else
    cout << "Unknown attribute returning" << unknown_value << endl;

  return unknown_value;
}
template <class TS,class BUD>
YEAR GetTSAttributeValue(const TreeSegment<TS,BUD>& ts,const TAI name)
{
  int unknown_value = 0;

  if (name == age)
    return ts.tsa.age;

  else
     cout << "Unknown attribute returning" << unknown_value << endl;

  return unknown_value;
}

template <class TS,class BUD>
TP SetTSAttributeValue(TreeSegment<TS,BUD>& ts, const TAD name, const TP value)
{
  TP old_value = GetTSAttributeValue(ts,name);
  
  if (name == L)
    ts.tsa.L = value;
  
  else if (name == fin)
   ts.tsa.fin = value;
  
  else if (name == fout)
    ts.tsa.fout = value;

  else if (name == M)
    ts.tsa.M = value;

  else if (name == omega)
    ts.tsa.omega = value;

  else if (name == P)
    ts.tsa.P = value;

  else if (name == Pr)
    ts.tsa.Pr = value;

  else if (name == Qabs)
    ts.tsa.Qabs = value;
  
  else if (name == Qin)
    ts.tsa.Qin = value;

  else if (name == R)
    ts.tsa.R = value;

  else if (name == Rf)
    ts.tsa.Rf = value;

  else if (name == Rn)
    ts.tsa.Rn = value;

  else if (name == Wf)
    ts.tsa.Rn = value;

  else if (name == Wm)
    ts.tsa.Wm = value;

  else if (name == Ws)
    ts.tsa.Ws = value;

  else
    cerr << "TreeSegment: Unknown attribute " << name << endl;

  return old_value;
}

template <class TS,class BUD>
YEAR SetTSAttributeValue(TreeSegment<TS,BUD>& ts, const TAI name, const YEAR  value)
{
  YEAR old_value = GetTSAttributeValue(ts,name);

  if (name == age)
    ts.tsa.age = value;
  else
    cerr << "TreeSegment: Unknown attribute " << name << endl;
  return old_value;
}





