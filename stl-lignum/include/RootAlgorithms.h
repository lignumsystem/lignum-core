#ifndef ROOTALGORITHMS_H
#define ROOTALGORITHMS_H

namespace Lignum{
  //Generic algorithms for root system (c.f. generic algorithms for Tree).
  template <class TREE, class Function>
    void ForEach(RootAxis<TREE>& ra, const Function f);

  template <class TREE, class T, class BinOp>
    T& Accumulate(RootAxis<TREE>& ra, T& init, const BinOp op);

  template <class TREE, class T, class BinOp>
    T& AccumulateDown(RootAxis<TREE>& ra, T& init, const BinOp op);

  template <class TREE, class T, class BinOp1, class BinOp2>
    T& AccumulateDown(RootAxis<TREE>& ra, T& init, const BinOp1 op1, 
		      const BinOp2 op2);

  template <class TREE, class T, class BinOp>
    void PropagateUp(RootAxis<TREE>& ra, T& data, const BinOp op);

  //Classes implementing the actual generic algorithms 
  template <class TREE, class Function>
    class ForAllRoots{
  public:
    ForAllRoots(const Function& func):f(func){}
    RootCompartment<TREE>* operator () (RootCompartment<TREE>* rc)const;
  private:
    const Function& f;
  };

  template <class TREE, class T, class BinOp>
    class AccumulateRoots{
  public:
    AccumulateRoots(const BinOp& op1):op(op1){}
    T& operator()(T& init, RootCompartment<TREE>* rc)const;
  private:
    const BinOp& op;
  };

  template <class TREE, class T, class BinOp>
    class AccumulateDownRoots{
  public:
    AccumulateDownRoots(const BinOp& op1, const T& init):op(op1),id(init){}
    T& operator()(T& init,RootCompartment<TREE>* rc)const;
  private:
    const BinOp& op;
    T id;
  };

  template <class TREE, class T, class BinOp1, class BinOp2>
    class AccumulateDownRoots2{
  public:
    AccumulateDownRoots2(const BinOp1& o1, const BinOp2& o2, 
			 const T& init):op1(o1),op2(o2),id(init){}
    T& operator()(T& init,RootCompartment<TREE>* rc)const;
  private:
    const BinOp1& op1;
    const BinOp2& op2;
    T id;
  };

  template <class TREE, class T, class BinOp>
    class PropagateUpRoots{
  public:
    PropagateUpRoots(const BinOp& op1):op(op1){}
    RootCompartment<TREE>* operator()(T& data, RootCompartment<TREE>* rc)const;
  private:
    const BinOp& op;
  };
}//closing namespace Lignum

#endif

#include <RootAlgorithmsI.h>
