#ifndef LGMUTILITYI_H
#define LGMUTILITYI_H

namespace Lignum{


  template <class TS,class BUD,class SHAPE>
    int& CountLeaves<TS,BUD,SHAPE>::operator()(int& n,TreeCompartment<TS,BUD>*
					 tc)const
    {
      if (TS* ts =  dynamic_cast<TS*>(tc)) {

	list<BroadLeaf<SHAPE>*>& leaf_list =
            GetLeafList(*ts);
	
	n += leaf_list.size();
      }

      return n;
    }

}//closing namespace Lignum

#endif


