#ifndef TREERADIATIONI_H
#define TREERADIATIONI_H

namespace Lignum{

template <class TS,class BUD, class F>
  void EvaluateRadiationForTree(Tree<TS,BUD>& tree, const F& f) {
  ForEach(tree,f);
}

//This constructor is for hardwoods that require the extinction
//function: it is read from file s

template<class F, class TS, class BUD>
  WrapRadiationEvaluations<F,TS,BUD>::WrapRadiationEvaluations(string s)
  :K(s)
  {
    radiation_functor.setExtinction(K);
  }

template <class F, class TS, class BUD>
  TreeCompartment<TS,BUD>*  WrapRadiationEvaluations<F,TS,BUD>::operator()
  (TreeCompartment<TS, BUD>* tc)const
{

  if (TS* ts = dynamic_cast<TS*>(tc)) {
    radiation_functor(ts);
  }

  return tc;

}

}   //Closing namespace Lignum

#endif
































