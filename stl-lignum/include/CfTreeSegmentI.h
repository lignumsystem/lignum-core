#ifndef CF_TREE_SEGMENTI_H
#define CF_TREE_SEGMENTI_H

namespace Lignum{

template <class TS,class BUD>
CfTreeSegment<TS,BUD>::CfTreeSegment(const Point& p, const PositionVector& d, 
				     const LGMdouble go, const METER l, const METER r, 
				     const METER rh, Tree<TS,BUD>* t)
  :TreeSegment<TS,BUD>(p,d,go,l,r,rh,t)
  {
    SetValue(*this,Hf,GetValue(*t,nl)*sin(GetValue(*t,na)));
    SetValue(*this,Rf,GetValue(*this,R)+GetValue(*this,Hf));
    //compute the initial mass of the foliage
    //1. compute the surface area (Sa) of the segment cylinder
    //2. initial mass of the foliage is then af*Sa ((kg/m2)*m2)
    LGMdouble wf =  GetValue(*t,af)*GetValue(*this,Sa);
    SetValue(*this,Wf,wf);
    //Remember original sapwood area As0
    SetValue(*this,As0,GetValue(*this,As));
  }


template <class TS,class BUD>
LGMdouble GetValue(const CfTreeSegment<TS,BUD>& ts, const LGMAD name)
{
  //  LGMdouble unknown_value = 0.0;

  if (name == Af){
    //Given Wf use sf to compute foliage area: sf*Wf ((m2/kg)*kg) 
    //see also parameter af
    return GetValue(GetTree(ts),sf)*GetValue(ts,Wf);
  }
  else if (name == As0)
    return ts.cftsa.As0;

  else if (name == Hf)
    return ts.cftsa.Hf;

  else if (name == P)
    return ts.cftsa.P;

  else if (name == Qin)
    return ts.cftsa.Qin;
  
  else if (name == Qabs)
    return ts.cftsa.Qabs;

  else if (name == Rf)
    //Who remebers to update radius to foliage limit after diameter growth
    //Return segment cylinder radius + foliage height.
    return GetValue(ts,R) + GetValue(ts,Hf);

  else if (name == Sa)
    //Wrap out the segment cylinder
    return 2.0*PI_VALUE*GetValue(ts,R)*GetValue(ts,L);

  //Return simply foliage mass
  else if (name == Wf)
    return ts.cftsa.Wf;

  else
    return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);
}


template <class TS,class BUD>
LGMdouble SetValue(CfTreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);
  if (name == As0)
    ts.cftsa.As0 = value;

  else if (name == Hf)
    ts.cftsa.Hf = value;
  
  else if (name == P)
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









