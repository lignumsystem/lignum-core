#ifndef HWTREESEGMENTMETABOLISMI_H
#define HWTREESEGMENTMETABOLISMI_H

namespace Lignum{

  //PHOTOSYNHETIC rate of HwTreeSegment (sum of those of leaves)

template <class TS,class BUD,class S>
void HwTreeSegment<TS,BUD,S>::photosynthesis()
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  LGMdouble p0 = GetValue(tt, LGPpr);

  for(typename list<BroadLeaf<S>*>::iterator i = leaf_ls.begin();
	i != leaf_ls.end(); i++) {
    (*i)->photosynthesis(p0);
  }

}

//RESPIRATION rate  of HwTreeSegment (sum of leaves  + segment sapwood
//resp.)  This  is NOT a good  way to implement  metabolism. We should
//have a  simple basic method  (say, parameter times biomass)  and all
//the experiments with  N or P or whatever nutrient  should be done in
//subclasses plugged in to a final program.
template <class TS,class BUD,class S>
void HwTreeSegment<TS,BUD,S>::respiration()
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));

  LGMdouble m_hw = 0.0;
  LGMdouble mf_par = GetValue(tt, LGPmf);

  for(typename list<BroadLeaf<S>*>::iterator i = leaf_ls.begin(); i != leaf_ls.end(); i++) {
    m_hw += mf_par * GetValue(**i,LGAWf);
  }

  // Respiration of wooden part

  m_hw += GetValue(tt,LGPms)*GetValue(*this,LGAWs);

  SetValue(*this, LGAM, m_hw);
}

} //closing namespace Lignum
#endif
