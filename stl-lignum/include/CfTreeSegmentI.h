#ifndef CF_TREE_SEGMENTI_H
#define CF_TREE_SEGMENTI_H

namespace Lignum{

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
  else
    old_value = SetValue(dynamic_cast<TreeSegment<TS,BUD>&>(ts), name,value);

  return old_value;
}



} //closing namespace Lignum

#endif









