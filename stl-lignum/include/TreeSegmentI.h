#ifndef TREE_SEGMENTI_H
#define TREE_SEGMENTI_H

namespace Lignum{

template <class TS,class BUD>
TreeSegment<TS,BUD>::TreeSegment()
{
  tree = NULL;
}


template <class TS,class BUD>
TreeSegment<TS,BUD>::TreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
			     const METER l, const METER r, const METER rn, Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
  SetValue(*this,omega,go);
  SetValue(*this,L,l);
  SetValue(*this,R,r);
  SetValue(*this,Rh,rn);
  SetValue(*this,Rtop,r);

  //the first annual ring
  tsa.annual_rings.push_back(r);

  //compute the sapwood mass
  SetValue(*this,Ws,GetSapwoodMass(*this)); 

  //compute the initial pressure in the TreeSegment    
  SetValue(*this, Wm, 0.5 * 1000 * l * r * r * PI_VALUE);
  SetValue(*this, Pr, -GetValue(*this, Hm) * 9.81 * 1000);   
}

template <class TS,class BUD>
TreeSegment<TS,BUD>::~TreeSegment()
{
}


//This method returns the amount[kg] of transpired water. 
//Time interval[s] is given as parameter
template <class TS,class BUD>
LGMdouble TreeSegment<TS,BUD>::GetTranspiration(LGMdouble time)
{
  return 0.12e-9;
}


template <class TS,class BUD>
list<METER> GetAnnualRings(const TreeSegment<TS,BUD>& ts)
{
  return ts.tsa.annual_rings;
}

template <class TS,class BUD>
Point GetEndPoint(const TreeSegment<TS,BUD>& ts)
{
  return GetPoint(ts)+GetValue(ts,L)*(Point)GetDirection(ts);
}

template <class TS,class BUD>
KGC GetSapwoodMass(const TreeSegment<TS,BUD>& ts)
{
  //volume up to R
  LGMdouble V1 = (PI_VALUE * pow((double)ts.tsa.R,2.0)) * ts.tsa.L;
  //heartwood volume
  LGMdouble V2 = (PI_VALUE * pow((double)ts.tsa.Rh,2.0)) * ts.tsa.L;
  //sapwood volume
  LGMdouble V3 = V1 - V2;

  //mass is density * volume
  return GetValue(*(ts.tree),rho) * V3;
}

template <class TS,class BUD>
LGMdouble GetValue(const TreeSegment<TS,BUD>& ts, const LGMAD name)
{
  //  LGMdouble unknown_value = 0.0;

  if (name == A)
    return PI_VALUE*pow(ts.tsa.R,2.0);

  else if (name == fin)
    return ts.tsa.fin;
  
  else if (name == fout)
    return ts.tsa.fout;
  
  else if (name == H)
    return ts.point.getZ();

  else if (name == Hm)
    return ts.point.getZ() + ts.direction.getVector()[2] * ts.tsa.L;

  else if (name == L)
    return ts.tsa.L;

  else if (name == Pr)
    return ts.tsa.Pr;

  else if (name == M)
    return ts.tsa.M;

  else if (name == omega)
    return ts.tsa.omega;

  else if (name == R)
    return ts.tsa.R;

  else if (name == Rh)
    return ts.tsa.Rh;

  else if (name == Rtop)
    return ts.tsa.Rtop;
  
  else if (name == Wm)
    return ts.tsa.Wm;

  else if (name == Ws) {
    LGMdouble V1 = (PI_VALUE * pow((double)ts.tsa.R,2.0)) * ts.tsa.L;
    //heartwood volume
    LGMdouble V2 = (PI_VALUE * pow((double)ts.tsa.Rh,2.0)) * ts.tsa.L;
    //sapwood volume
    LGMdouble V3 = V1 - V2;
    //mass is density * volume
    return GetValue(*(ts.tree),rho) * V3;
  }

  else if (name == Wh) {
    //heartwood volume
    LGMdouble V2 = (PI_VALUE * pow((double)ts.tsa.Rh,2.0)) * ts.tsa.L;
    //mass is density * volume
    return GetValue(*(ts.tree),rho) * V2;
  }
 
  else
    return GetValue(dynamic_cast<const TreeCompartment<TS,BUD>&>(ts), name);
    //    cout << "Unknown attribute returning" << unknown_value << endl;

  //  return unknown_value;
}


template <class TS,class BUD>
LGMdouble SetValue(TreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(ts,name);
  
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

  else if (name == Pr)
    ts.tsa.Pr = value;

  else if (name == R)
    ts.tsa.R = value;

  else if (name == Rh)
    ts.tsa.Rh = value;

  else if (name == Rtop)
    ts.tsa.Rtop = value;

  else if (name == Wm)
    ts.tsa.Wm = value;

  else if (name == Ws)
    ts.tsa.Ws = value;

  else if (name == Wh)
    ts.tsa.Wh = value;

  else
    //    cerr << "TreeSegment: Unknown attribute " << name << endl;
    old_value = SetValue(dynamic_cast<TreeCompartment<TS,BUD>&>(ts), name,value);

  return old_value;
}





}//close namespace Lignum

#endif









