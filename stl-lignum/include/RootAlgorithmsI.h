/// \file RootAlgorithmsI.h
/// \brief Experimental root system generic algorithms implementation not active 
#ifndef ROOTALGORITHMSI_H
#define ROOTALGORITHMSI_H

#include <RootSystem.h>

using namespace std;

namespace Lignum{

  template <class TREE, class Function>
    RootCompartment<TREE>* ForAllRoots<TREE,Function>::operator()(RootCompartment<TREE>* rc)const{
    
    f(rc); //Apply the functor
    
    if (RootAxis<TREE>* ra = dynamic_cast<RootAxis<TREE>*>(rc)){
      list<RootCompartment<TREE>*>& rc_ls = GetRootCompartmentList(*ra);
      for_each(rc_ls.begin(),rc_ls.end(),*this);
    }
    else if (RootBranchingPoint<TREE>* rbp = 
	     dynamic_cast<RootBranchingPoint<TREE>*>(rc)){
      list<RootAxis<TREE>*>& ra_ls = GetAxisList(*rbp);
      for_each(ra_ls.begin(),ra_ls.end(),*this);
    }

    return rc;
  }

  template <class TREE, class T, class BinOp>
    T& AccumulateRoots<TREE,T,BinOp>::operator()(T& init,
						 RootCompartment<TREE>* rc)const{
    //Accumulate with operatore 'op' 
    init = op(init,rc);

    //Acumulate from root axis and root branching point
    if (RootAxis<TREE>* ra = dynamic_cast<RootAxis<TREE>*>(rc)){
      list<RootCompartment<TREE>*>& rc_ls = GetRootCompartmentList(*ra);
      typename list<RootCompartment<TREE>*>::iterator first = rc_ls.begin();
      typename list<RootCompartment<TREE>*>::iterator last = rc_ls.end();
      //traverse the root axis, list of root compartments
      while (first != last)
	(*this)(init,*first++);
    }
    else if (RootBranchingPoint<TREE>* rbp = 
	     dynamic_cast<RootBranchingPoint<TREE>*>(rc)){
      list<RootAxis<TREE>*>& ra_ls = GetAxisList(*rbp);
      typename list<RootAxis<TREE>*>::iterator first = ra_ls.begin();
      typename list<RootAxis<TREE>*>::iterator last = ra_ls.end();
      //traverse the root branching point, list of root axes
      while (first != last)
	(*this)(init,*first++);
    }

    return init;
  }

  template <class TREE, class T, class BinOp>
    T& AccumulateDownRoots<TREE,T,BinOp>::operator()(T& init, 
						     RootCompartment<TREE>* rc)const{
    //AccumulateDown root segment and root tip
    if (RootSegment<TREE>* rs = dynamic_cast<RootSegment<TREE>*>(rc)){
      init = op(init,rs);
    }
    else if (RootTip<TREE>* rt = dynamic_cast<RootTip<TREE>*>(rc)){
      init = op(init,rt);
    }
    //AccumulateDown root axis in reverse order (note reverse iterators)
    else if (RootAxis<TREE>* ra = dynamic_cast<RootAxis<TREE>*>(rc)){
      list<RootCompartment<TREE>*>& rc_ls = GetRootCompartmentList(*ra);
      typename list<RootCompartment<TREE>*>::reverse_iterator last = rc_ls.rbegin();
      typename list<RootCompartment<TREE>*>::reverse_iterator first = rc_ls.rend();
      while (last != first){
	(*this)(init,*last++);
      }
      //Apply the operator *after* traversing the axis
      init = op(init,rc);
    }
    //AccumulateDown root branching point in reverse order (note reverse iterators)
    else if (RootBranchingPoint<TREE>* rbp = dynamic_cast<RootBranchingPoint<TREE>*>(rc)){
      list<RootAxis<TREE>*>& ra_ls = GetAxisList(*rbp);
      typename list<RootAxis<TREE>*>::reverse_iterator last = ra_ls.rbegin();
      typename list<RootAxis<TREE>*>::reverse_iterator first = ra_ls.rend();
      while (last != first){
	T init_new = T(id); //create new 'init' for each of the axes.
	(*this)(init_new,*last++);
	init += init_new;   //accumulate to original init
      }
       //Apply the operator *after* traversing the axes
      init = op(init,rc);
    }
    return init;
  }

  template <class TREE, class T, class BinOp1, class BinOp2>
    T& AccumulateDownRoots2<TREE,T,BinOp1,BinOp2>::operator()(T& init, 
							      RootCompartment<TREE>* rc)const{
    //AccumulateDown root segment and root tip
    if (RootSegment<TREE>* rs = dynamic_cast<RootSegment<TREE>*>(rc)){
      init = op2(init,rs);
    }
    else if (RootTip<TREE>* rt = dynamic_cast<RootTip<TREE>*>(rc)){
      init = op2(init,rt);
    }
    //AccumulateDown root axis in reverse order (note reverse iterators)
    else if (RootAxis<TREE>* ra = dynamic_cast<RootAxis<TREE>*>(rc)){
      list<RootCompartment<TREE>*>& rc_ls = GetRootCompartmentList(*ra);
      typename list<RootCompartment<TREE>*>::reverse_iterator last = rc_ls.rbegin();
      typename list<RootCompartment<TREE>*>::reverse_iterator first = rc_ls.rend();
      while (last != first){
	(*this)(init,*last++);
      }
      //Apply the operator op2 *after* traversing the axis
      init = op2(init,rc);
    }
    //AccumulateDown root branching point in reverse order (note reverse iterators)
    else if (RootBranchingPoint<TREE>* rbp = dynamic_cast<RootBranchingPoint<TREE>*>(rc)){
      list<RootAxis<TREE>*>& ra_ls = GetAxisList(*rbp);
      typename list<RootAxis<TREE>*>::reverse_iterator last = ra_ls.rbegin();
      typename list<RootAxis<TREE>*>::reverse_iterator first = ra_ls.rend();
      while (last != first){
	T init_new = T(id); //create new 'init' for each of the axes.
	(*this)(init_new,*last++);
	init = op1(init,init_new);   //accumulate to original init with op1
      }
       //Apply the operator *after* traversing the axes
      init = op2(init,rc);
    }
    return init;
  } 

   template <class TREE, class T, class BinOp>
     RootCompartment<TREE>* PropagateUpRoots<TREE,T,BinOp>::operator()(T& data, 
								       RootCompartment<TREE>* rc)const{
    //Propagate up root  segment and root tip.  Note  if user wants to
    //modify 'data'  the function operator 'op' should  take 'data' as
    //reference
    if (RootSegment<TREE>* rs = dynamic_cast<RootSegment<TREE>*>(rc)){
      op(data,rs);
    }
    else if (RootTip<TREE>* rt = dynamic_cast<RootTip<TREE>*>(rc)){
      op(data,rt);
    }
    //Propagate up root axis
    else if (RootAxis<TREE>* ra = dynamic_cast<RootAxis<TREE>*>(rc)){
      //Apply operator *before* propagating  'data' up in axis. Create
      //a  fresh copy  of  the  'data' so  each  axis has  independent
      //propagation.
      T new_data = op(data,ra);
      list<RootCompartment<TREE>*>& rc_ls = GetRootCompartmentList(*ra);
      typename list<RootCompartment<TREE>*>::iterator first = rc_ls.begin();
      typename list<RootCompartment<TREE>*>::iterator last  = rc_ls.end();
      while (first != last)
	(*this)(new_data,*first++);
    }
    else if (RootBranchingPoint<TREE>* rbp = dynamic_cast<RootBranchingPoint<TREE>*>(rc)){
      //Apply operator *before* propagating 'data' up.  Create a fresh
      //copy  of  the  'data'   (possibly  modified  in  'op')  to  be
      //propagated in each axis.
      T new_data = op(data,rbp);
      list<RootAxis<TREE>*>& ra_ls = GetAxisList(*rbp);
      typename list<RootAxis<TREE>*>::iterator first = ra_ls.begin();
      typename list<RootAxis<TREE>*>::iterator last  = ra_ls.end();
      while (first != last)
	(*this)(new_data,*first++);
    }
    return rc;
  }

  //ForEach
  template <class TREE, class Function> 
    void  ForEach(RootAxis<TREE>& ra, const Function f){
    
    ForAllRoots<TREE,Function> F(f);
    F(&ra);
  }

  //Accumulate
  template <class TREE, class T, class BinOp>
    T& Accumulate(RootAxis<TREE>& ra, T& init, const BinOp op){
    
    AccumulateRoots<TREE,T,BinOp> Acc(op);

    return Acc(init,&ra);
  }
  
  //AccumulateDown
  template <class TREE, class T, class BinOp>
    T& AccumulateDown(RootAxis<TREE>& ra, T& init, const BinOp op){
    
    AccumulateDownRoots<TREE,T,BinOp> AccDown(op,init);

    return AccDown(init,&ra);
  }

  //AccumulateDown,  '+=' is replaced for op1.
  template <class TREE, class T, class BinOp1, class BinOp2>
    T& AccumulateDown(RootAxis<TREE>& ra, T& init, const BinOp1 op1, const BinOp2 op2){
    
    AccumulateDownRoots2<TREE,T,BinOp1,BinOp2> AccDown(op1,op2,init);

    return AccDown(init,&ra);
  }

  //PropagateUp
  template <class TREE, class T, class BinOp>
    void PropagateUp(RootAxis<TREE>& ra, T& data, const BinOp op){
    
    PropagateUpRoots<TREE,T,BinOp> PUR(op);
    
    PUR(data,&ra);
  }
}//closing namespace Lignum
#endif
