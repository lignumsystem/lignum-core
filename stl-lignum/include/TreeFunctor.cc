#include <TreeFunctor.h>
#include <iostream.h>

template <class TS>
void DisplayType<TS>::operator ()(TreeCompartment<TS>*tc)
{
  if (Axis<TS>* myaxis =  dynamic_cast<Axis<TS>*>(tc)){
    cout << "Hello, I'm Axis" << endl;
    list<TreeCompartment<TS>*>& tc_ls = GetTreeCompartmentList(*myaxis);
    for_each(tc_ls.begin(),tc_ls.end(),DisplayType<MyTreeSegment>());
  }

  else if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(tc)){
    cout << "Hello, I'm BranchingPoint" << endl;
    list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);
    for_each(axis_ls.begin(),axis_ls.end(),DisplayType<MyTreeSegment>());
  }

  else if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(tc))
    cout << "Hello, I'm TreeSegment" << endl;

  else if (Bud<TS>* mybud =  dynamic_cast<Bud<TS>*>(tc))
    cout << "Hello, I'm Bud" << endl;

  else
    cout << "Who am I???" << endl;
}
