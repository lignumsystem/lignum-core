#ifndef CF_TREESEGMENT_METABOLISMI_H
#define CF_TREESEGMENT_METABOLISMI_H

namespace Lignum{


//Calculate PHOTOSYNTHETIC rate of the segment
//as the function of absorbed radiation

template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::photosynthesis()
{
  Tree<TS,BUD>& t = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  SetValue(*this,P, GetValue(t, pr) * GetValue(*this,Qabs));
}


  //RESPIRATION rate of the segment as the function of needle mass
  //and sapwood mass


template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::respiration()
{
  LGMdouble resp;
  Tree<TS,BUD>& t = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  resp = GetValue(t, mf)*GetValue(*this,Wf)+GetValue(t,ms)*GetValue(*this,Ws);
  SetValue(*this,M, resp);
}

} //Closing namespace Lignum


#endif

