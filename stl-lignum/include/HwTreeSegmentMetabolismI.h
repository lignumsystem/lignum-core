#ifndef HWTREESEGMENTMETABOLISMI_H
#define HWTREESEGMENTMETABOLISMI_H

namespace Lignum{

  //PHOTOSYNHETIC rate of HwTreeSegment (sum of those of leaves)

template <class TS,class BUD,class S>
void HwTreeSegment<TS,BUD,S>::photosynthesis()
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));
  LGMdouble p0 = GetValue(tt, pr);

  for(typename list<BroadLeaf<S>*>::iterator i = leaf_ls.begin();
	i != leaf_ls.end(); i++) {
    (*i)->photosynthesis(p0);
  }

}

//RESPIRATION rate of HwTreeSegment (sum of leaves + segment sapwood resp.)
template <class TS,class BUD,class S>
void HwTreeSegment<TS,BUD,S>::respiration()
{
  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));

  LGMdouble m_hw = 0.0;
  LGMdouble mf_par = GetValue(tt, mf);

  for(typename list<BroadLeaf<S>*>::iterator i = leaf_ls.begin();
	i != leaf_ls.end(); i++) {
    m_hw += mf_par * GetValue(**i,Wf);
  }

 Tree<TS,BUD>& t = dynamic_cast<Tree<TS,BUD>&>(GetTree(*this));

  // Effect of nitrogen on leaves
  LGMdouble nit_leaves = GetValue(tt, nitroLeaves);
  LGMdouble nit_wood = GetValue(tt, nitroWood);
 

  m_hw *= tt.tf.nitroRespiration(nit_leaves);

  // Respiration of wooden part, effect of nitrogen.
  m_hw += GetValue(t,ms)*GetValue(*this,Ws) * tt.tf.nitroRespiration(nit_wood);

 

  SetValue(*this, M, m_hw);
}

} //closing namespace Lignum
#endif
