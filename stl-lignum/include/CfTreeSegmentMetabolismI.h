#ifndef CF_TREESEGMENT_METABOLISMI_H
#define CF_TREESEGMENT_METABOLISMI_H

namespace Lignum{


//Calculate photosynthetic rate of the segment as
//as the function of absorbed radiation

template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::photosynthesis()
{
  Tree<TS,BUD>& t = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  SetValue(*this,P, GetValue(t, pr) * GetValue(*this,Qabs));
}

} //Closing namespace Lignum

#endif
