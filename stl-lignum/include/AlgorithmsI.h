#ifndef ALGORITHMSI_H
#define ALGORITHMSI_H

namespace Lignum{


//Helper functors for generic algorithms 

//Functor for ForEach
template <class TS,class BUD,class Function>
ForAllTreeCompartments<TS,BUD,Function>::ForAllTreeCompartments(const Function op1)
  :f(op1)
{
}

template <class TS,class BUD, class Function>
TreeCompartment<TS,BUD>*  ForAllTreeCompartments<TS,BUD,Function>:: operator()(TreeCompartment<TS,BUD>* tc)const
{
  f(tc);

  if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    for_each(tc_ls.begin(),tc_ls.end(),*this);
  }
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    for_each(axis_ls.begin(),axis_ls.end(),*this);
  }

  return tc;
}

//Functor for Accumulate
template <class TS,class BUD, class T, class BinOp>
AccumulateTreeCompartments<TS,BUD,T,BinOp>::AccumulateTreeCompartments(const BinOp op)
  :op1(op)
{
}

template <class TS,class BUD, class T, class BinOp>
T& AccumulateTreeCompartments<TS,BUD,T,BinOp>:: operator()(T& id,TreeCompartment<TS,BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc))
    id = op1(id,ts);
  
  //Why this cannot  be 'BUD* bud = dynamic_cast<BUD*>(tc)'  for CC on
  //SGI? For  g++ it can be.  Also, in other algorithms  the type cast
  //can be to BUD*.
  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
    id = op1(id,bud);

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    id = op1(id,axis);
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    typename list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    typename list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    id = op1(id,bp);
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    typename list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  return id;
}

//Functor for AccummulateDown
template <class TS,class BUD, class T, class BinOp>
AccumulateDownTreeCompartments<TS,BUD,T,BinOp>::AccumulateDownTreeCompartments(const BinOp op, const T& id)
  :op1(op),id_copy(id)
{
}

template <class TS,class BUD, class T, class BinOp> 
T& AccumulateDownTreeCompartments<TS,BUD,T,BinOp>::operator()(T& id,
						TreeCompartment<TS,BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc))
    id = op1(id,ts);

  else if (BUD* bud = dynamic_cast<BUD*>(tc))
    id = op1(id,bud);

  //traverse the axes with "fresh" id elements  
  //"adding and assigning" before applying op1 to the branch whorl
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    typename list<Axis<TS,BUD>*>::reverse_iterator last = axis_ls.rbegin();
    typename list<Axis<TS,BUD>*>::reverse_iterator first = axis_ls.rend();
    while (last != first){
      T id_new = T(id_copy);
      (*this)(id_new,*last++);
      id += id_new;
    }
    id = op1(id,bp);
  }

  //traverse the axis before applying op1 to the axis
  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    typename list<TreeCompartment<TS,BUD>*>::reverse_iterator last = tc_ls.rbegin();
    typename list<TreeCompartment<TS,BUD>*>::reverse_iterator first = tc_ls.rend();
    while (last != first){
      (*this)(id,*last++);
    }
    id = op1(id,axis);
  }
  return id;
}

//Functor for AccumulateDown
template <class TS,class BUD, class T, class BinOp1, class BinOp2>
AccumulateDownTreeCompartments2<TS,BUD,T,BinOp1,BinOp2>::AccumulateDownTreeCompartments2(const BinOp1 usr_op1,
											 const BinOp2 usr_op2,
											 const T& id)
  :op1(usr_op1),op2(usr_op2),id_copy(id)
{
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2> 
T& AccumulateDownTreeCompartments2<TS,BUD,T,BinOp1,BinOp2>::operator()(T& id,
							    TreeCompartment<TS,BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc))
    id = op2(id,ts);

  else if (BUD* bud = dynamic_cast<BUD*>(tc))
    id = op2(id,bud);

  //for branch whorl instead of default += operator apply user defined
  //operator op1 for the identity elements to collect results from
  //branches and after that call user defined operator op2 for the 
  //branch whorl itself
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    typename list<Axis<TS,BUD>*>::reverse_iterator last = axis_ls.rbegin();
    typename list<Axis<TS,BUD>*>::reverse_iterator first = axis_ls.rend();
    while (last != first){
      T id_new = T(id_copy);
      (*this)(id_new,*last++);
      id = op1(id,id_new); //applying user defined op1 for the identity elements
    }
    id = op2(id,bp); //now calling user defined operator op2
  }

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    typename list<TreeCompartment<TS,BUD>*>::reverse_iterator last = tc_ls.rbegin();
    typename list<TreeCompartment<TS,BUD>*>::reverse_iterator first = tc_ls.rend();
    while (last != first){
      (*this)(id,*last++);
    }
    id = op2(id,axis);
  }
  return id;
}


//Functor for PropagateUp
template <class TS,class BUD, class T, class BinOp>
PropagateUpTreeCompartments<TS,BUD,T,BinOp>::PropagateUpTreeCompartments(const BinOp op)
  :op1(op)
{
}

template <class TS,class BUD, class T, class BinOp> 
TreeCompartment<TS,BUD>* 
PropagateUpTreeCompartments<TS,BUD,T,BinOp>::operator()(T& id,
					     TreeCompartment<TS,BUD>* tc)const
{
	#ifdef _MSC_VER //cvs
	#else
  if (TS* ts = dynamic_cast<TS*>(tc))
    op1(id,ts);

  else if (BUD* bud = dynamic_cast<BUD*>(tc))
    op1(id,bud);

  //when propagating up apply op1 before continuing along the axis.
  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    T id_new = op1(id,axis);
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    typename list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    typename list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id_new,*first++);
  }
  //when propagating up apply op1 before continuing to the axes.
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    T id_changed = op1(id,bp);
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    typename list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    while (first != last){
      T id_new = id_changed;
      (*this)(id_new,*first++);
    }
  }
#endif
  return tc;
}

//Functor for PropagateUp
template <class TS,class BUD, class T, class BinOp1, class BinOp2>
PropagateUpTreeCompartments2<TS,BUD,T,BinOp1,BinOp2>::PropagateUpTreeCompartments2(const BinOp1 usr_op1, 
										   const BinOp2 usr_op2)
  :op1(usr_op1),op2(usr_op2)
{
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2> 
TreeCompartment<TS,BUD>* 
PropagateUpTreeCompartments2<TS,BUD,T,BinOp1,BinOp2>::operator()(T& id,
								 TreeCompartment<TS,BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc))
    op2(id,ts);

  else if (BUD* bud = dynamic_cast<BUD*>(tc))
    op2(id,bud);

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    op2(id,axis);
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    typename list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    typename list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    op2(id,bp);
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    typename list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    while (first != last){
      T id_new = T();
      id_new = op1(id_new,id);
      (*this)(id_new,*first++);
    }
  }

  return tc;
}


//The Generic algorithms themselves
template <class TS,class BUD, class Function>
void ForEach(Tree<TS,BUD>& tree, const Function op1)
{
  ForAllTreeCompartments<TS,BUD,Function> op2(op1);

  Axis<TS,BUD>& axis = GetAxis(tree);
  op2(&axis);
}

template <class TS,class BUD, class T, class BinOp>
T& Accumulate(Tree<TS,BUD>& tree, T& id, const BinOp op1)
{
  AccumulateTreeCompartments<TS,BUD,T,BinOp> op2(op1);
  Axis<TS,BUD>& axis = GetAxis(tree);
  return op2(id,&axis);
}

template <class TS,class BUD, class T, class BinOp>
T& AccumulateDown(Tree<TS,BUD>& tree, T& id, const BinOp op1)
{
  AccumulateDownTreeCompartments<TS,BUD,T,BinOp> op2(op1,id);
  Axis<TS,BUD>& axis = GetAxis(tree);
  return op2(id,&axis);
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2>
T& AccumulateDown(Tree<TS,BUD>& tree, T& id, 
		  const BinOp1 op1, const BinOp2 op2)
{
  AccumulateDownTreeCompartments2<TS,BUD,T,BinOp1,BinOp2> op3(op1,op2,id);
  Axis<TS,BUD>& axis = GetAxis(tree);
  return op3(id,&axis);
}

template <class TS,class BUD, class T, class BinOp>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp op1)
{
  PropagateUpTreeCompartments<TS,BUD,T,BinOp> op2(op1);
  Axis<TS,BUD>& axis = GetAxis(tree);
  op2(init,&axis);
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp1 op1,  const BinOp2 op2)
{
  PropagateUpTreeCompartments2<TS,BUD,T,BinOp1,BinOp2> op3(op1,op2);
  Axis<TS,BUD>& axis = GetAxis(tree);
  op2(init,&axis);
}

}//closing namespace Lignum

#endif
