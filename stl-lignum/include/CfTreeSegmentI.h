#ifndef CF_TREE_SEGMENTI_H
#define CF_TREE_SEGMENTI_H

namespace Lignum{

template <class TS,class BUD>
CfTreeSegment<TS,BUD>::CfTreeSegment(const Point& p, const PositionVector& d, 
				     const LGMdouble go, const METER l, const METER r, 
				     const METER rh, Tree<TS,BUD>* t)
  :TreeSegment<TS,BUD>(p,d,go,l,r,rh,t)
  {
    SetValue(*this,LGAHf,GetValue(*t,nl)*sin(GetValue(*t,na)));
    SetValue(*this,LGARf,GetValue(*this,LGAR)+GetValue(*this,LGAHf));
    //compute the initial mass of the foliage
    //1. compute the surface area (Sa) of the segment cylinder
    //2. initial mass of the foliage is then af*Sa ((kg/m2)*m2)
    LGMdouble wf =  GetValue(*t,af)*GetValue(*this,LGASa);
    SetValue(*this,LGAWf,wf);
    //Remember original sapwood area As0
    SetValue(*this,LGAAs0,GetValue(*this,LGAAs));
  }


template <class TS,class BUD>
LGMdouble GetValue(const CfTreeSegment<TS,BUD>& ts, const LGMAD name)
{
  //  LGMdouble unknown_value = 0.0;

  if (name == LGAAf){
    //Given Wf use sf to compute foliage area: sf*Wf ((m2/kg)*kg) 
    //see also parameter af
    return GetValue(GetTree(ts),sf)*GetValue(ts,LGAWf);
  }
  else if (name == LGAAs0)
    return ts.cftsa.As0;

  else if (name == LGAHf)
    return ts.cftsa.Hf;

  else if (name == LGAP)
    return ts.cftsa.P;

  else if (name == LGAQin)
    return ts.cftsa.Qin;
  
  else if (name == LGAQabs)
    return ts.cftsa.Qabs;

  else if (name == LGARf)
    //Who remebers to update radius to foliage limit after diameter growth
    //Return segment cylinder radius + foliage height.
    return GetValue(ts,LGAR) + GetValue(ts,LGAHf);

  else if (name == LGASa)
    //Wrap out the segment cylinder
    return 2.0*PI_VALUE*GetValue(ts,LGAR)*GetValue(ts,LGAL);

  //Return simply foliage mass
  else if (name == LGAWf)
    return ts.cftsa.Wf;

  else
    return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);
}


template <class TS,class BUD>
LGMdouble SetValue(CfTreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);
  if (name == LGAAs0)
    ts.cftsa.As0 = value;

  else if (name == LGAHf)
    ts.cftsa.Hf = value;
  
  else if (name == LGAP)
    ts.cftsa.P = value;
  
  else if (name == LGAQin)
   ts.cftsa.Qin = value;
  
  else if (name == LGAQabs)
    ts.cftsa.Qabs = value;

  else if (name == LGARf)
    ts.cftsa.Rf = value;

  else if (name == LGAWf)
    ts.cftsa.Wf = value;

  else
    old_value = SetValue(dynamic_cast<TreeSegment<TS,BUD>&>(ts), name,value);

  return old_value;
}



} //closing namespace Lignum

#endif









