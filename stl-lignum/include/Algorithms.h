#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <functional>
#include <list>
#include <LGMdecl.h>
/// \file Algorithms.h
/// \brief Generic algorithms for the Lignum tree.
///
/// There are four generic algorithms in the Lignum system: ForEach, Accumulate,
/// AccumulateDown (two flavours) and PropagetUp (two flavours). These are inspired by
/// C++ STL library and encourages Generic programming when implementing specific
/// applications with the Lignum system.  
using namespace std;

namespace Lignum{
  ///Function to find maximum value in a vector
  ///\return Iterator to max element in a vector
  ///\note Can be replaced in C++11 with std::max_element when available
  template<class ForwardIt>
  ForwardIt max_elmnt(ForwardIt first, ForwardIt last)
  {
    if (first == last)
        return last;
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first)
        if (*largest < *first)
            largest = first;
    return largest;
  }
  
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

/// For each applies the user defined function `f` to each Tree compertment in the tree.
/// \tparam TS Tree segment
/// \tparam BUD Bud
/// \tparam Function User defined function 
/// \param[in,out] tree Lignum tree
/// \param f Function of one parameter f(TreeCompartment<TS,BUD>* tc) that returns void.
template <class TS,class BUD, class Function>
void ForEach(Tree<TS,BUD>& tree, const Function f);

/// Accumulate applies user defined binary operator to each tree compartment
/// with the initial value.
/// \tparam TS Tree segment
/// \tparam BUD Bud
/// \tparam T Type of the initial value
/// \tparam BinOp Binary operator
/// \param[in,out] tree Lignum tree
/// \param[in,out] init The initial value for Accumulate
/// \param op The binary operator with two arguments: op(T& init,TreeCompartment<TS,BUD>* tc)
/// \pre The initial value type T must have assginment (`=`) operator
/// \remark The order the Lignum tree is traversed is not defined 
/// \retval The altered initial value `init`.
/// \sa AccumulateTreeCompartments
template <class TS,class BUD, class T, class BinOp>
T& Accumulate(Tree<TS,BUD>& tree, T& init, const BinOp op);

/// AccumulateDown applies user defined binary operator to each tree compartment
/// with the initial value.
/// \tparam TS Tree segment
/// \tparam BUD Bud
/// \tparam T Type of the initial value
/// \tparam BinOp Binary operator
/// \param[in,out] tree Lignum tree
/// \param[in,out] init The initial value for AccumulateDown
/// \param op The binary operator with two arguments: op(T& init,TreeCompartment<TS,BUD>* tc)
/// \pre The initial value type T must have copy constructor (`T(init)`), assginment (`=`)
///      and add-assign (`+=`) operators
/// \remark The Lignum tree is traversed from the tip of the branches towards the main stem and
/// to the base of the tree.
/// \return The altered intial value
/// \sa AccumulateDownTreeCompartments
template <class TS,class BUD, class T, class BinOp>
T& AccumulateDown(Tree<TS,BUD>& tree, T& init, const BinOp op);

/// AccumulateDown applies user defined binary operator to each tree compartment
/// with the initial value.
/// \tparam TS Tree segment
/// \tparam BUD Bud
/// \tparam T Type of the initial value
/// \tparam BinOp1 Binary operator
/// \tparam BinOp2 Binary operator
/// \param[in,out] tree Lignum tree
/// \param[in,out] init The initial value for AccumulateDown
/// \param op1 The binary operator with two arguments: op1(T& init,T& init_from_axis)
/// \param op2 The binary operator with two arguments: op2(T& init,TreeCompartment<TS,BUD>* tc
/// \pre The initial value type T must have copy constructor (`T(init)`) and the assginment (`=`)
///      operator.
/// \remark The Lignum tree is traversed from the tip of the branches towards the main stem and
/// to the base of the tree. The operator `op2` is applied to each TreeCompartment.
/// At BranchingPoint the operator `op1` is applied the to each return value from Axes first
/// before `op2`.
/// \retval The altered intial value `init`.
/// \sa AccumulateDownTreeCompartments2
template <class TS,class BUD, class T, class BinOp1, class BinOp2>
T& AccumulateDown(Tree<TS,BUD>& tree, T& init, const BinOp1 op1, const BinOp2 op2);

/// PropagateUp applies  user defined binary operator to each tree compartment with a value
/// \tparam TS Tree segment
/// \tparam BUD Bud
/// \tparam T Type of the initial value
/// \tparam BinOp Binary operator
/// \param[in,out] tree The Lignum tree
/// \param[in,out] init The initial value
/// \param op1 The binary operator with two arguments: op1(T& init,TreeCompartment<TS,BUD>* tc)
/// \pre The intial value type T  must have the assignment (`=`) operator.
/// \remark PropagateUp traverses the tree from the base to the tip of the branches and passes the initial value forward.
///         Each tree compartment may change the initial value with `op1` and this changed value is received by
///         TreeCompartments thereafter.
/// \sa PropagateUpTreeCompartments
template <class TS,class BUD, class T, class BinOp>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp op1);

/// PropagateUp applies  user defined binary operator to each tree compartment with a value
/// \tparam TS Tree segment
/// \tparam BUD Bud
/// \tparam T Type of the initial value
/// \tparam BinOp1 Binary operator with two arguments: op1(T& init,T& default)
/// \tparam BinOp2 Binary operator with two arguments: op2(T& init, TreeCompartment<TS,BUD>* tc)
/// \param[in,out] tree The Lignum tree
/// \param[in,out] init The initial value
/// \param op1 Binary operator
/// \param op2 Binary operator
/// \pre The initial value must have default constructor T().
/// \remark PropagateUp  traverses the tree from the base to the tip of the branches and passes the initial value forward.
///         Each tree compartment may change the initial value with `op2` and this changed value is received by
///         TreeCompartments thereafter. Each BranchingPoint calls also T id_new = op1(T(),init) and id_new is  passed
///         on to Axes connected to he BranchingPoint
/// \sa PropagateUpTreeCompartments2
template <class TS,class BUD, class T, class BinOp1, class BinOp2>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp1 op1, const BinOp2 op2);


} //closing namespace Lignum

 
//The implementations of Generic Algorithms
#include <AlgorithmsI.h>

#endif



