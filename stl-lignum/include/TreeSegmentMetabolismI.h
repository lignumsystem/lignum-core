#ifndef TREESEGMENTMETABOLISMI_H
#define TREESEGMENTMETABOLISMI_H

namespace Lignum{


//Calculate and set the photosynthetic rate of the segment as
//as the function of absorbed radiation

template <class TS,class BUD>
void TreeSegment<TS,BUD>::photosynthesis()
{
  Tree<TS,BUD>& t = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  tsa.P = GetValue(t, pr) * tsa.Qabs;

}

} //Closing namespace Lignum

#endif
