#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <functional>
#include <Tree.h>


template <class TS>
class AdaptableTCFunction
  :public unary_function<TreeCompartment<TS>*,TreeCompartment<TS>*>{
};

template <class TS, class T, class BinOp>
class AccumulateOp2{
 public:
  AccumulateOp2(const BinOp& op1);
  T& operator()(T& id,TreeCompartment<TS>* tc)const;
 private:
  BinOp op1;
};

template <class TS, class T, class BinOp>
class ReverseAccumulateOp2{
 public:
  ReverseAccumulateOp2(const BinOp& op);
  TreeCompartment<TS>* operator()(T& id,TreeCompartment<TS>* tc)const;
 private:
  BinOp op1;
};

template <class TS, class T, class BinOp>
class PropagateUpOp2{
 public:
  PropagateUpOp2(const BinOp& op);
  TreeCompartment<TS>* operator()(T& id,TreeCompartment<TS>* tc)const;
 private:
  BinOp op1;
};

template <class TS, class Function>
class ForEachOp2:public AdaptableTCFunction<TS>{
 public:
  ForEachOp2(const  Function& op1);
  TreeCompartment<TS>* operator () (TreeCompartment<TS>* tc)const;
 private:
  Function f;
};


template <class TS, class Function>
void ForEach(Tree<TS>& tree, const Function& f);

template <class TS, class T, class BinOp>
T& Accumulate(Tree<TS>& tree, T& init, const BinOp& op);

template <class TS, class T, class BinOp>
void AccumulateDown(Tree<TS>& tree, T& init, const BinOp& op);

template <class TS, class T, class BinOp>
void PropagateUp(Tree<TS>& tree, T& init, const BinOp& op1);

#endif


