#include <Algorithms.h>
#include <algorithm>

template <class TS,class BUD,class Function>
ForEachOp2<TS,BUD,Function>::ForEachOp2(const Function& op1)
  :f(op1)
{
}

template <class TS,class BUD, class Function>
TreeCompartment<TS,BUD>*  ForEachOp2<TS,BUD,Function>:: operator()(TreeCompartment<TS,BUD>* tc)const
{
  if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    for_each(tc_ls.begin(),tc_ls.end(),compose1(*this,f));
  }
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    for_each(axis_ls.begin(),axis_ls.end(),compose1(*this,f));
  }
  return tc;
}

template <class TS,class BUD, class T, class BinOp>
AccumulateOp2<TS,BUD,T,BinOp>::AccumulateOp2(const BinOp& op)
  :op1(op)
{
}

template <class TS,class BUD, class T, class BinOp>
T& AccumulateOp2<TS,BUD,T,BinOp>:: operator()(T& id,TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    id = op1(id,ts);

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
    id = op1(id,bud);

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    id = op1(id,axis);
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    id = op1(id,bp);
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  return id;
}

template <class TS,class BUD, class T, class BinOp>
ReverseAccumulateOp2<TS,BUD,T,BinOp>::ReverseAccumulateOp2(const BinOp& op)
  :op1(op)
{
}

template <class TS,class BUD, class T, class BinOp> 
T& ReverseAccumulateOp2<TS,BUD,T,BinOp>::operator()(T& id,
						TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    id = op1(id,ts);

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
    id = op1(id,bud);

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS,BUD>*>::reverse_iterator last = axis_ls.rbegin();
    list<Axis<TS,BUD>*>::reverse_iterator first = axis_ls.rend();
    while (last != first){
      T id_new = T();
      (*this)(id_new,*last++);
      id += id_new;
    }
    id = op1(id,tc);
  }

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS,BUD>*>::reverse_iterator last = tc_ls.rbegin();
    list<TreeCompartment<TS,BUD>*>::reverse_iterator first = tc_ls.rend();
    while (last != first){
      (*this)(id,*last++);
    }
    id = op1(id,tc);
  }
  return id;
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2>
ReverseAccumulateOp3<TS,BUD,T,BinOp1,BinOp2>::ReverseAccumulateOp3(const BinOp1& usr_op1,
								   const BinOp2& usr_op2)
  :op1(usr_op1),op2(usr_op2)
{
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2> 
T& ReverseAccumulateOp3<TS,BUD,T,BinOp1,BinOp2>::operator()(T& id,
							    TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    id = op2(id,ts);

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
    id = op2(id,bud);

  //for branch whorl instead of default += operator apply user defined
  //operator op1 for the identity elements to collect results from
  //branches and after that call user defined operator op2 for the 
  //branch whorl itself
  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS,BUD>*>::reverse_iterator last = axis_ls.rbegin();
    list<Axis<TS,BUD>*>::reverse_iterator first = axis_ls.rend();
    while (last != first){
      T id_new = T();
      (*this)(id_new,*last++);
      id = op1(id,id_new); //applying op1 for the identity elements
    }
    id = op2(id,tc); //now calling user defined operator op2
  }

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS,BUD>*>::reverse_iterator last = tc_ls.rbegin();
    list<TreeCompartment<TS,BUD>*>::reverse_iterator first = tc_ls.rend();
    while (last != first){
      (*this)(id,*last++);
    }
    id = op2(id,tc);
  }
  return id;
}


template <class TS,class BUD, class T, class BinOp>
PropagateUpOp2<TS,BUD,T,BinOp>::PropagateUpOp2(const BinOp& op)
  :op1(op)
{
}

template <class TS,class BUD, class T, class BinOp> 
TreeCompartment<TS,BUD>* 
PropagateUpOp2<TS,BUD,T,BinOp>::operator()(T& id,
					     TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    op1(id,ts);

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
    op1(id,bud);

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    op1(id,axis);
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    op1(id,bp);
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    while (first != last){
      T id_new = id;
      (*this)(id_new,*first++);
    }
  }

  return tc;
}

template <class TS,class BUD, class Function>
void ForEach(Tree<TS,BUD>& tree, const Function& op1)
{
  ForEachOp2<TS,BUD,Function> op2(op1);

  Axis<TS,BUD>& axis = GetAxis(tree);
  compose1(op2,op1)(&axis);
}

template <class TS,class BUD, class T, class BinOp>
T& Accumulate(Tree<TS,BUD>& tree, T& id, const BinOp& op1)
{
  AccumulateOp2<TS,BUD,T,BinOp> op2(op1);
  Axis<TS,BUD>& axis = GetAxis(tree);
  return op2(id,&axis);
}

template <class TS,class BUD, class T, class BinOp>
T& AccumulateDown(Tree<TS,BUD>& tree, T& id, const BinOp& op1)
{
  ReverseAccumulateOp2<TS,BUD,T,BinOp> op2(op1);
  Axis<TS,BUD>& axis = GetAxis(tree);
  return op2(id,&axis);
}

template <class TS,class BUD, class T, class BinOp1, class BinOp2>
T& AccumulateDown(Tree<TS,BUD>& tree, T& id, 
		  const BinOp1& op1, const BinOp2& op2)
{
  ReverseAccumulateOp3<TS,BUD,T,BinOp1,BinOp2> op3(op1,op2);
  Axis<TS,BUD>& axis = GetAxis(tree);
  return op3(id,&axis);
}

template <class TS,class BUD, class T, class BinOp>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp& op1)
{
  PropagateUpOp2<TS,BUD,T,BinOp> op2(op1);
  Axis<TS,BUD>& axis = GetAxis(tree);
  op2(init,&axis);
}


