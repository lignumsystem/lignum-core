#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <functional>
#include <list>
#include <LGMdecl.h>


namespace Lignum{

template <class TS,class BUD>
class AdaptableTCFunction
  :public unary_function<TreeCompartment<TS,BUD>*,TreeCompartment<TS,BUD>*>{
};

template <class TS,class BUD, class T, class BinOp>
class AccumulateTreeCompartments{
 public:
  AccumulateTreeCompartments(const BinOp op1);
  T& operator()(T& id,TreeCompartment<TS,BUD>* tc)const;
 private:
  BinOp op1;
};

template <class TS,class BUD, class T, class BinOp>
class AccumulateDownTreeCompartments{
 public:
  AccumulateDownTreeCompartments(const BinOp op, const T& id);
  T& operator()(T& id,TreeCompartment<TS,BUD>* tc)const;
 private:
  BinOp op1;
  T id_copy;
};

template <class TS,class BUD, class T, class BinOp1, class BinOp2>
class AccumulateDownTreeCompartments2{
 public:
  AccumulateDownTreeCompartments2(const BinOp1 op1, const BinOp2 op2, const T& id);
  T& operator()(T& id,TreeCompartment<TS,BUD>* tc)const;
 private:
  BinOp1 op1;
  BinOp2 op2;
  T id_copy;
};

template <class TS,class BUD, class T, class BinOp>
class PropagateUpTreeCompartments{
 public:
  PropagateUpTreeCompartments(const BinOp op);
  TreeCompartment<TS,BUD>* operator()(T& id,TreeCompartment<TS,BUD>* tc)const;
 private:
  BinOp op1;
};

template <class TS,class BUD, class T, class BinOp1,class BinOp2>
class PropagateUpTreeCompartments2{
 public:
  PropagateUpTreeCompartments2(const BinOp1 op1, const BinOp2 op2);
  TreeCompartment<TS,BUD>* operator()(T& id,TreeCompartment<TS,BUD>* tc)const;
 private:
  BinOp1 op1;
  BinOp2 op2;
};


template <class TS,class BUD, class Function>
class ForAllTreeCompartments{
 public:
  ForAllTreeCompartments(const  Function op1);
  TreeCompartment<TS,BUD>* operator () (TreeCompartment<TS,BUD>* tc)const;
 private:
  Function f;
};


template <class TS,class BUD, class Function>
void ForEach(Tree<TS,BUD>& tree, const Function f);

template <class TS,class BUD, class T, class BinOp>
T& Accumulate(Tree<TS,BUD>& tree, T& init, const BinOp op);

template <class TS,class BUD, class T, class BinOp>
T& AccumulateDown(Tree<TS,BUD>& tree, T& init, const BinOp op);

template <class TS,class BUD, class T, class BinOp1, class BinOp2>
T& AccumulateDown(Tree<TS,BUD>& tree, T& init, const BinOp1 op1, const BinOp2 op2);
template <class TS,class BUD, class T, class BinOp>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp op1);
 
template <class TS,class BUD, class T, class BinOp1, class BinOp2>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp1 op1, const BinOp2 op2);


} //closing namespace Lignum

 
//The implementations of Generic Algorithms
#include <AlgorithmsI.h>

#endif



