
#ifndef TREEBOOKKEEPINGI_H
#define TREEBOOKKEEPINGI_H


namespace Lignum{



//Age TreeCompartments by the given delta_age
template <class TS, class BUD>
TreeCompartment<TS,BUD>*  Age<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
	SetValue(*tc, LGAage, GetValue(*tc,LGAage)+delta_age);

	
	return tc;
}



//Sum photosynthesis from all segments and update Tree's photosynthesis P
template <class TS,class BUD>
LGMdouble UpdateTreePhotosynthesis(Tree<TS,BUD>& tree)
{
      //LGMdouble SumTreePhotosynthesis(LGMdouble&,TreeCompartment<TS,BUD>*);
      LGMdouble initPh = 0.0;
      LGMdouble sumPh;
      sumPh = Accumulate(tree, initPh, SumTreePhotosynthesis<TS,BUD>());
      SetValue(tree, LGAP, sumPh);
      
      return sumPh;
}



}

#endif
