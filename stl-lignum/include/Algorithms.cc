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
    op1(id,ts);

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
    op1(id,bud);

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS,BUD>*>::reverse_iterator last = axis_ls.rbegin();
    list<Axis<TS,BUD>*>::reverse_iterator first = axis_ls.rend();
    while (last != first){
      T id_new = T();
      (*this)(id_new,*last++);
      id += id_new;
    }
    op1(id,tc);
  }

  else if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS,BUD>*>::reverse_iterator last = tc_ls.rbegin();
    list<TreeCompartment<TS,BUD>*>::reverse_iterator first = tc_ls.rend();
    while (last != first){
      (*this)(id,*last++);
    }
    op1(id,tc);
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

template <class TS,class BUD, class T, class BinOp>
void PropagateUp(Tree<TS,BUD>& tree, T& init, const BinOp& op1)
{
  PropagateUpOp2<TS,BUD,T,BinOp> op2(op1);
  Axis<TS,BUD>& axis = GetAxis(tree);
  op2(init,&axis);
}

