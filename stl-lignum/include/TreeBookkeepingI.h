#ifndef TREEBOOKKEEPING_I_H
#define TREEBOOKKEEPING_I_H
#include <typeinfo>
// Contains functions for evaluating quantities at the level
// of the tree.
// At the moment, photosynthesis realized

namespace Lignum{

  template <class TS, class BUD>
  class SumTreePhotosynthesis{
  public:
    LGMdouble operator () (LGMdouble& cumPh, 
			   TreeCompartment<TS,BUD>* tc)const{
      //cout << typeid(tc).name() << endl;
      //this should return the photosynthesis 
      if (TS* tsc = dynamic_cast<TS*>(tc)) {
	LGMdouble PP = GetValue(*tsc, P);
	cumPh += PP;
      }
      return cumPh;
    }
  };

  //Sum photosynthesis from all segments and update Tree's photosynthesis P
  template <class TS,class BUD>
    LGMdouble UpdateTreePhotosynthesis(Tree<TS,BUD>& tree)
    {
      //LGMdouble SumTreePhotosynthesis(LGMdouble&,TreeCompartment<TS,BUD>*);
      LGMdouble initPh = 0.0;
      LGMdouble sumPh;
      sumPh = Accumulate(tree, initPh, SumTreePhotosynthesis<TS,BUD>());
      SetValue(tree, P, sumPh);
      
      return sumPh;
    }
} //Closing namespace Lignum

#endif



