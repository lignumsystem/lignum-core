#ifndef CF_TREE_SEGMENTI_H
#define CF_TREE_SEGMENTI_H

namespace Lignum{
  //Construct   CfTreeSegment   by   giving  all   needed   attributes
  //and parameters explicitely in the constructor.
  template <class TS, class BUD> 
  CfTreeSegment<TS,BUD>::CfTreeSegment(const Point& p, const PositionVector& d, 
				       const LGMdouble go, const METER l, const METER r, 
				       const METER rh, const LGMdouble sf, const LGMdouble af, 
				       const LGMdouble nl, const LGMdouble na, Tree<TS,BUD>* t)
    :TreeSegment<TS,BUD>(p,d,go,l,r,rh,t)
  {
    SetValue(*this,LGAsf,sf);
    //Foliage height = needle length * sin(needle angle)
    SetValue(*this,LGAHf,nl*sin(na));
    //Radius to foliage height
    SetValue(*this,LGARf,GetValue(*this,LGAR)+GetValue(*this,LGAHf));
    //Foliage mass = needle area density * surface area of the segment cylinder
    SetValue(*this,LGAWf,af*GetValue(*this,LGASa));
    //Remember original sapwood area
    SetValue(*this,LGAAs0,GetValue(*this,LGAAs));
    //Rememebr original foliage mass
    SetValue(*this,LGAWf0,GetValue(*this,LGAWf));
  }
  //Construct CfTreeSegment  given point, direction,  gravelius order,
  //length, radius, heartwood radius and the tree. The foliage is then
  //calculated   based   on   parameter   files  given   in   a   file
  //(Tree.txt). These  foliage parameters must  include: Specific leaf
  //area LGPsf (m2/kgC), needle area density LGPaf (kgC/m2), needle angle
  //(radians).
template <class TS,class BUD>
CfTreeSegment<TS,BUD>::CfTreeSegment(const Point& p, const PositionVector& d, 
				     const LGMdouble go, const METER l, const METER r, 
				     const METER rh, Tree<TS,BUD>* t)
  :TreeSegment<TS,BUD>(p,d,go,l,r,rh,t)
  {
    //Specific leaf area, use tree level parameter by default
    SetValue(*this,LGAsf,GetValue(*t,LGPsf));  
    //Height of the foliage cylinder
    SetValue(*this,LGAHf,GetValue(*t,LGPnl)*sin(GetValue(*t,LGPna)));
    //Radius to foliage limit
    SetValue(*this,LGARf,GetValue(*this,LGAR)+GetValue(*this,LGAHf));
    //compute the initial mass of the foliage
    //1. compute the surface area (Sa) of the segment cylinder
    //2. initial mass of the foliage is then af*Sa ((kg/m2)*m2)
    LGMdouble wf =  GetValue(*t,LGPaf)*GetValue(*this,LGASa);
    SetValue(*this,LGAWf,wf);
    //Remember original sapwood area As0 and foliage mass Wf0
    SetValue(*this,LGAAs0,GetValue(*this,LGAAs));
    SetValue(*this,LGAWf0,GetValue(*this,LGAWf));
  }


template <class TS,class BUD>
LGMdouble GetValue(const CfTreeSegment<TS,BUD>& ts, const LGMAD name)
{
  if (name == LGAAf){
    //Given Wf use sf to compute foliage area: sf*Wf ((m2/kg)*kg) 
    //see also parameter af
    return GetValue(ts,LGAsf)*GetValue(ts,LGAWf);
  }
  else if (name == LGAHf)
    return ts.cftsa.Hf;

  else if (name == LGAP){
    return ts.cftsa.P;
  }

  else if (name == LGAQin)
    return ts.cftsa.Qin;
  
  else if (name == LGAQabs)
    return ts.cftsa.Qabs;

  else if (name == LGARf){
    if (GetValue(ts,LGAWf) > R_EPSILON)
      return GetValue(ts,LGAR) + GetValue(ts,LGAHf);
    //Who remebers to update radius to foliage limit after diameter growth
    //Return segment cylinder radius + foliage height.
    else
      return GetValue(ts,LGAR);
  }

  else if (name == LGASa)
    //Wrap out the segment cylinder
    return 2.0*PI_VALUE*GetValue(ts,LGAR)*GetValue(ts,LGAL);

  else if (name == LGAsf)
    return ts.cftsa.sf;

  else if (name == LGAstarm)
    return ts.cftsa.starm;

  //Volume occupied by foliage
  else if (name == LGAVf){
    if (GetValue(ts,LGAWf) > R_EPSILON)
      return PI_VALUE*pow(GetValue(ts,LGARf),2.0)*GetValue(ts,LGAL)
	     -GetValue(ts,LGAV);
    else
      return 0.0;
  }
  //Return simply foliage mass
  else if (name == LGAWf)
    return ts.cftsa.Wf;

  //Return initial foliage mass
  else if (name == LGAWf0)
    return ts.cftsa.Wf0;

  else if (name == LGArue)
    return ts.cftsa.rue;

  else
    return GetValue(dynamic_cast<const TreeSegment<TS,BUD>&>(ts), name);
}


template <class TS,class BUD>
LGMdouble SetValue(CfTreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);
  if (name == LGAHf)
    ts.cftsa.Hf = value;
  
  else if (name == LGAP)
    ts.cftsa.P = value;
  
  else if (name == LGAQin)
   ts.cftsa.Qin = value;
  
  else if (name == LGAQabs)
    ts.cftsa.Qabs = value;

  else if (name == LGARf){
    ts.cftsa.Rf = value;
    SetValue(ts,LGAHf,max(ts.cftsa.Rf-GetValue(ts,LGAR),0.0));
  }

  else if (name == LGAsf)
    ts.cftsa.sf = value;

  else if (name == LGAstarm)
    ts.cftsa.starm = value;

  else if (name == LGAWf)
    ts.cftsa.Wf = value;

  else if (name == LGAWf0)
    ts.cftsa.Wf0 = value;

  else if (name == LGArue)
    ts.cftsa.rue = value;

  else
    old_value = SetValue(dynamic_cast<TreeSegment<TS,BUD>&>(ts), name,value);

  return old_value;
}



} //closing namespace Lignum

#endif









