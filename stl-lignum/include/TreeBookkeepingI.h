#ifndef TREEBOOKKEEPING_I_H
#define TREEBOOKKEEPING_I_H


// Contains functions for evaluating quantities at the level
// of the tree.
// At the moment, photosynthesis realized

namespace Lignum{


template <class TS,class BUD>
LGMdouble SumTreePhotosynthesis(LGMdouble& cumPh, TreeCompartment<TS,BUD>* tc)
{
  if(CfTreeSegment<TS,BUD>* tsc = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc)) {
    LGMdouble PP = GetValue(*tsc, P);
    cumPh += PP;
  }
  else if(HwTreeSegment<TS,BUD>* tsh = dynamic_cast<HwTreeSegment<TS,BUD>*>(tc)) {
    LGMdouble PP = GetValue(*tsh, P);
    cumPh += PP;
  }

  return cumPh;

}

//Sum photosynthesis from all segments and update Tree's photosynthesis P
template <class TS,class BUD>
LGMdouble UpdateTreePhotosynthesis(Tree<TS,BUD>& tree)
{
  LGMdouble SumTreePhotosynthesis(LGMdouble& cumPh, TreeCompartment<TS,BUD>* tc);

  LGMdouble initPh = 0.0;
  LGMdouble sumPh;
  sumPh = Accumulate(tree, initPh, SumTreePhotosynthesis );
  SetValue(tree, P, sumPh);

  return sumPh;
}



} //Closing namespace Lignum

#endif
