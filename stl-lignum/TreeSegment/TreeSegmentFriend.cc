
#include <TreeSegment.h>
#include <Tree.h>

list<METER> GetAnnualRings(const TreeSegment& ts)
{
  return ts.tsa.annual_rings;
}

KGC GetSapwoodMass(const TreeSegment& ts)
{
  //volume up to R
  TP V1 = (PI_VALUE * pow((double)ts.tsa.R,2.0)) * ts.tsa.L;
  //heartwood volume
  TP V2 = (PI_VALUE * pow((double)ts.tsa.Rn,2.0)) * ts.tsa.L;
  //sapwood volume
  TP V3 = V1 - V2;

  //mass is density * volume
  return GetParameterValue(*(ts.tree),rho) * V3;
}

TP GetAttributeValue(const TreeSegment& ts, const TAD name)
{
  TP unknown_value = 0.0;
  
  if (name == L)
    return ts.tsa.L;

  else if (name == M)
    return ts.tsa.M;

  else if (name == P)
    return ts.tsa.P;

  else if (name == Qin)
    return ts.tsa.Qin;

  else if (name == Qabs)
    return ts.tsa.Qabs;

  else if (name == R)
    return ts.tsa.R;

  else if (name == Rn)
    return ts.tsa.Rn;

  else if (name == Wf)
    return ts.tsa.Wf;

  else
    cout << "Unknown parameter returning" << unknown_value << endl;

  return unknown_value;
}

YEAR GetAttributeValue(const TreeSegment& ts,const TAI name)
{
  int unknown_value = 0;

  if (name == age)
    return ts.tsa.age;

  else
     cout << "Unknown parameter returning" << unknown_value << endl;

  return unknown_value;
}

template <class T1,class T2>
T2 SetAttributeValue(TreeSegment& ts, const T1 name, const T2 value)
{
  T2 old_value = GetAttributeValue(ts,name);
  
  if (name == L)
    ts.tsa.L = L;

  else if (name == M)
    ts.tsa.M = value;

  else if (name == omega)
    ts.tsa.omega = value;

  else if (name == P)
    ts.tsa.P = value;

  else if (name == Qabs)
    ts.tsa.Qabs = value;
  
  else if (name == Qin)
    ts.tsa.Qin = value;

  else if (name == R)
    ts.tsa.R = value;
  
  else if (name == Rn)
    ts.tsa.Rn = value;

  else if (name == Wf)
    ts.tsa.Rn = value;
  else
    cerr << "TreeSegment: Unknown attribute " << name << end;

  return old_value;
}

YEAR SetAttributeValue(TreeSegment& ts, const TAI name, const YEAR value)
{
  YEAR old_value = GetAttributeValue(ts,name);

  if (name == age)
    ts.tsa.age = value;

  return old_value;
}





