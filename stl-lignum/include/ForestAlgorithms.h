#ifndef FORESTALGORITHM_H
#define FORESTALGORITHM_H

#include <Forest.h>
#include <Algorithms.h>

namespace Lignum{
  //Forest Accumulate  takes the tree,  id and the functor  f, traverses
  //coniferous and  hardwood tree lists  and applies Accumulate  to each
  //tree. How to smartly decide if a tree is coniferous or heartwood?
  template <class TREE, class T, class F>
    T& Accumulate(Forest& f, T& id, F func) 
    {
      list<VTree*>& ls1 =  GetCfTreeList(f);
      list<VTree*>::iterator b1 = ls1.begin();
      list<VTree*>::iterator e1 = ls1.end();
      while (b1 != e1){
	//I can  check that the tree type  matches but how to  decide if a
	//tree is coniferous or hardwood, how to see what is behind TREE?
	if (TREE* t = dynamic_cast<TREE*>(*b1)){
	  id = Accumulate(*t,id,func);
	}
	b1++;
      }
      //Recall references can (and must) be initialized once
      //can't use ls1 here (see Stroustrup, pp. 97-99)
      list<VTree*>& ls2 = GetHwTreeList(f);
      list<VTree*>::iterator b2 = ls2.begin();
      list<VTree*>::iterator e2 = ls2.end();

      while (b2 != e2){
	if (TREE* t = dynamic_cast<TREE*>(*b2)){
	  id = Accumulate(*t,id,func);
	}
	b2++;
      }

      return id;
    }


  template <class TREE, class F>
    void ForEach (Forest& f, F func) 
    {
      list<VTree*>& ls1 =  GetCfTreeList(f);
      list<VTree*>::iterator b1 = ls1.begin();
      list<VTree*>::iterator e1 = ls1.end();
      while (b1 != e1){
	//I can  check that the tree type  matches but how to  decide if a
	//tree is coniferous or hardwood, how to see what is behind TREE?
	if (TREE* t = dynamic_cast<TREE*>(*b1)){
	  ForEach(*t,func);
	}
	b1++;
      }
      //Recall references can (and must) be initialized once
      //can't use ls1 here (see Stroustrup, pp. 97-99)
      list<VTree*>& ls2 = GetHwTreeList(f);
      list<VTree*>::iterator b2 = ls2.begin();
      list<VTree*>::iterator e2 = ls2.end();

      while (b2 != e2){
	if (TREE* t = dynamic_cast<TREE*>(*b2)){
	  ForEach(*t,func);
	}
	b2++;
      }

    }
  //In a similar fashion  implement AccumulateDown and PropagateUp for
  //forests here.
}
#endif
