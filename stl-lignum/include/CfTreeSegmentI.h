#ifndef CF_TREE_SEGMENTI_H
#define CF_TREE_SEGMENTI_H

namespace Lignum{

template <class TS,class BUD>
CfTreeSegment<TS,BUD>::CfTreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
			     const METER l, const METER r, const METER rn, Tree<TS,BUD>* t)
  :TreeSegment<TS,BUD>(p,d,go,l,r,rn,t)
  {
  //compute the radius to foliage limit (Rf)
  //the given parameters are needle length (nl) and the
  //needle angle (na)
  //Rf = hf + tsa.R, where hf is height of the foliage (hf = nl * sin(na))
  LGMdouble needle_length = GetValue(*t,nl);
  LGMdouble needle_angle = GetValue(*t,na);
  SetValue(*this,Rf,needle_length * sin(needle_angle)+ 
		      GetValue(*this,R));

  //compute the initial mass of the foliage
  //1. compute the surface area (sa) of the cylinder representing foliage
  LGMdouble sa =  2.0 * PI_VALUE * GetValue(*this,Rf) * GetValue(*this,L);
  //2. the mass of the foliage (Wf = sa * af) 
  LGMdouble wf =  sa * GetValue(*t,af);
  SetValue(*this,Wf,sa*wf);

  }


template <class TS,class BUD>
LGMdouble GetValue(const CfTreeSegment<TS,BUD>& ts, const LGMAD name)
{
  //  LGMdouble unknown_value = 0.0;

  if (name == P)
    return ts.cftsa.P;

  else if (name == Qin)
    return ts.cftsa.Qin;
  
  else if (name == Qabs)
    return ts.cftsa.Qabs;

  else if (name == Rf)
    return ts.cftsa.Rf;

  else if (name == Wf)
    return ts.cftsa.Wf;

  else
    return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);
}


template <class TS,class BUD>
LGMdouble SetValue(CfTreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);
  
  if (name == P)
    ts.cftsa.P = value;
  
  else if (name == Qin)
   ts.cftsa.Qin = value;
  
  else if (name == Qabs)
    ts.cftsa.Qabs = value;

  else if (name == Rf)
    ts.cftsa.Rf = value;

  else if (name == Wf)
    ts.cftsa.Wf = value;

  else
    old_value = SetValue(dynamic_cast<TreeSegment<TS,BUD>&>(ts), name,value);

  return old_value;
}



} //closing namespace Lignum

#endif









