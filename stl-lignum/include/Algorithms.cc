#include <Algorithms.h>
#include <algorithm>

template <class TS, class Function>
ForEachOp2<TS,Function>::ForEachOp2(const Function& op1)
  :f(op1)
{
}

template <class TS, class Function>
TreeCompartment<TS>*  ForEachOp2<TS,Function>:: operator()(TreeCompartment<TS>* tc)const
{
  if (Axis<TS>* axis = dynamic_cast<Axis<TS>*>(tc)){
    list<TreeCompartment<TS>*>& tc_ls = GetTreeCompartmentList(*axis);
    for_each(tc_ls.begin(),tc_ls.end(),compose1(*this,f));
  }
  else if (BranchingPoint<TS>* bp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    list<Axis<TS>*>& axis_ls = GetAxisList(*bp);
    for_each(axis_ls.begin(),axis_ls.end(),compose1(*this,f));
  }
  return tc;
}

template <class TS, class T, class BinOp>
AccumulateOp2<TS,T,BinOp>::AccumulateOp2(const BinOp& op)
  :op1(op)
{
}

template <class TS, class T, class BinOp>
TreeCompartment<TS>* AccumulateOp2<TS,T,BinOp>:: operator()(T& id,TreeCompartment<TS>* tc)const
{
  if (TreeSegment<TS>* ts = dynamic_cast<TreeSegment<TS>*>(tc))
    op1(id,ts);

  else if (Bud<TS>* bud = dynamic_cast<Bud<TS>*>(tc))
    op1(id,bud);

  else if (Axis<TS>* axis = dynamic_cast<Axis<TS>*>(tc)){
    op1(id,axis);
    list<TreeCompartment<TS>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS>*>::iterator first = tc_ls.begin();
    list<TreeCompartment<TS>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  else if (BranchingPoint<TS>* bp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    op1(id,bp);
    list<Axis<TS>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS>*>::iterator first = axis_ls.begin();
    list<Axis<TS>*>::iterator last = axis_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  return tc;
}

template <class TS, class T, class BinOp>
ReverseAccumulateOp2<TS,T,BinOp>::ReverseAccumulateOp2(const BinOp& op)
  :op1(op)
{
}

template <class TS, class T, class BinOp> 
TreeCompartment<TS>* 
ReverseAccumulateOp2<TS,T,BinOp>::operator()(T& id,
					     TreeCompartment<TS>* tc)const
{
  if (TreeSegment<TS>* ts = dynamic_cast<TreeSegment<TS>*>(tc))
    op1(id,ts);

  else if (Bud<TS>* bud = dynamic_cast<Bud<TS>*>(tc))
    op1(id,bud);

  else if (BranchingPoint<TS>* bp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    list<Axis<TS>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS>*>::reverse_iterator last = axis_ls.rbegin();
    list<Axis<TS>*>::reverse_iterator first = axis_ls.rend();
    while (last != first){
      T id_new = T();
      (*this)(id_new,*last++);
      id += id_new;
    }
    op1(id,tc);
  }

  else if (Axis<TS>* axis = dynamic_cast<Axis<TS>*>(tc)){
    list<TreeCompartment<TS>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS>*>::reverse_iterator last = tc_ls.rbegin();
    list<TreeCompartment<TS>*>::reverse_iterator first = tc_ls.rend();
    while (last != first){
      (*this)(id,*last++);
    }
    op1(id,tc);
  }
  return tc;
}

template <class TS, class T, class BinOp>
PropagateUpOp2<TS,T,BinOp>::PropagateUpOp2(const BinOp& op)
  :op1(op)
{
}

template <class TS, class T, class BinOp> 
TreeCompartment<TS>* 
PropagateUpOp2<TS,T,BinOp>::operator()(T& id,
					     TreeCompartment<TS>* tc)const
{
  if (TreeSegment<TS>* ts = dynamic_cast<TreeSegment<TS>*>(tc))
    op1(id,ts);

  else if (Bud<TS>* bud = dynamic_cast<Bud<TS>*>(tc))
    op1(id,bud);

  else if (Axis<TS>* axis = dynamic_cast<Axis<TS>*>(tc)){
    op1(id,axis);
    list<TreeCompartment<TS>*>& tc_ls = GetTreeCompartmentList(*axis);
    list<TreeCompartment<TS>*>::iterator first = tc_ls.begin();
    list<TreeCompartment<TS>*>::iterator last = tc_ls.end();
    while (first != last)
      (*this)(id,*first++);
  }

  else if (BranchingPoint<TS>* bp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    op1(id,bp);
    list<Axis<TS>*>& axis_ls = GetAxisList(*bp);
    list<Axis<TS>*>::iterator first = axis_ls.begin();
    list<Axis<TS>*>::iterator last = axis_ls.end();
    while (first != last){
      T id_new = id;
      (*this)(id_new,*first++);
    }
  }

  return tc;
}

template <class TS, class Function>
void ForEach(Tree<TS>& tree, const Function& op1)
{
  ForEachOp2<TS,Function> op2(op1);

  Axis<TS>& axis = GetAxis(tree);
  compose1(op2,op1)(&axis);
}

template <class TS, class T, class BinOp>
void Accumulate(Tree<TS>& tree, T& id, const BinOp& op1)
{
  AccumulateOp2<TS,T,BinOp> op2(op1);
  Axis<TS>& axis = GetAxis(tree);
  op2(id,&axis);
}

template <class TS, class T, class BinOp>
void AccumulateDown(Tree<TS>& tree, T& id, const BinOp& op1)
{
  ReverseAccumulateOp2<TS,T,BinOp> op2(op1);
  Axis<TS>& axis = GetAxis(tree);
  op2(id,&axis);
}

template <class TS, class T, class BinOp>
void PropagateUp(Tree<TS>& tree, T& init, const BinOp& op1)
{
  PropagateUpOp2<TS,T,BinOp> op2(op1);
  Axis<TS>& axis = GetAxis(tree);
  op2(init,&axis);
}

