#ifndef HWTREESEGMENTMETABOLISMI_H
#define HWTREESEGMENTMETABOLISMI_H

namespace Lignum{

template <class TS,class BUD>
void HwTreeSegment<TS,BUD>::photosynthesis()
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  LGMdouble p0 = GetValue(tt, pr);

  for(list<BroadLeaf*>::iterator i = leaf_ls.begin();
	i != leaf_ls.end(); i++) {
    (*i)->photosynthesis(p0);
  }

}

} //closing namespace Lignum
#endif
