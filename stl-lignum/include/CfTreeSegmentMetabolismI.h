#ifndef CFTREESEGMENTMETABOLISMI_H
#define CFTREESEGMENTMETABOLISMI_H

namespace Lignum{


//Calculate photosynthetic rate of the segment as
//as the function of absorbed radiation

template <class TS,class BUD>
void CfTreeSegment<TS,BUD>::photosynthesis()
{
  Tree<TS,BUD>& t = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  cftsa.P = GetValue(t, pr) * cftsa.Qabs;

}

} //Closing namespace Lignum

#endif
