#ifndef TREEMETABOLISMI_H
#define TREEMETABOLISMI_H

namespace Lignum{

template <class TS,class BUD>
TreeCompartment<TS,BUD>* TreePhotosynthesis<TS,BUD>::operator()
  (TreeCompartment<TS,BUD>* tc)const
{
  tc->photosynthesis();
  return tc;
}



template <class TS,class BUD>
void Tree<TS,BUD>::photosynthesis()
{
  //Have TreeCompartments to do photosynthesis

  ForEach(*this, TreePhotosynthesis<TS,BUD>());
 
}

template <class TS,class BUD>
LGMdouble& SumTreePhotosynthesis<TS,BUD>::operator() (LGMdouble& cumPh,
					      TreeCompartment<TS,BUD>* tc)const
{
  if(TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc) ) {
    LGMdouble PP = GetValue(*ts, P);
    cumPh += PP;
  }
  return cumPh;
}

//Sum photosynthesis from all segments and update Tree's photosynthesis P
template <class TS,class BUD>
void Tree<TS,BUD>::sumPhotosynthesis()
{
  LGMdouble initPh = 0.0;
  LGMdouble sumPh;
  sumPh = Accumulate(*this, initPh, SumTreePhotosynthesis<TS,BUD>() );
  SetValue(*this, P, sumPh); 
}

} //Closing namespace Lignum

#endif
































