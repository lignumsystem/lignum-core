#include <TreeFunctor.h>
#include <iostream.h>

//Use built-in operator dynamic_cast
//to resolve the data_type of a tree compartment
template <class TS,class BUD>
void DisplayType<TS,BUD>::operator ()(TreeCompartment<TS,BUD>*tc)
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "Hello, I'm Axis" << endl;
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*myaxis);
    for_each(tc_ls.begin(),tc_ls.end(),DisplayType<TS,BUD>());
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "Hello, I'm BranchingPoint" << endl;
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);
    for_each(axis_ls.begin(),axis_ls.end(),DisplayType<TS,BUD>());
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    cout << "Hello, I'm TreeSegment" << endl;

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
    cout << "Hello, I'm Bud" << endl;

  else
    cout << "Who am I???" << endl;
}

template <class TS,class BUD>
TreeCompartment<TS,BUD>* DisplayType2<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "Hello, I'm Axis" << endl;
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "Hello, I'm BranchingPoint" << endl;
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    cout << "Hello, I'm TreeSegment" << endl;

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
    cout << "Hello, I'm Bud" << endl;

  else
    cout << "Who am I???" << endl;

  return tc;
}

template <class TS,class BUD>
int& CountTreeSegments<TS,BUD>::operator()(int& n,TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    n+=1;
  
  return n;
}



template <class TS,class BUD>
int& CountCompartments<TS,BUD>::operator()(int& n,TreeCompartment<TS,BUD>* tc)const
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "Hello, I'm Axis ";
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "Hello, I'm BranchingPoint ";
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    cout << "Hello, I'm TreeSegment ";

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
    cout << "Hello, I'm Bud ";

  else
    cout << "Who am I??? ";
  //counting them all
  n+=1;
  cout << n << endl;
  return n;
}


template <class TS,class BUD>
TreeCompartment<TS,BUD>* FillWithWater<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    {
      cout << "Filling water.." << endl;
      SetTSAttributeValue(*myts, Wm, pow(GetTSAttributeValue(*myts, R), 2) * 
			  PI_VALUE * GetTSAttributeValue(*myts, L) * 0.5 *  
			  1000); // korjaaa...1000 GetTree(*myts).ttp.rhow                                                                               
    }
  return tc;
}

template <class TS,class BUD>
int& CountCompartmentsReverse<TS,BUD>::operator()(int& n,
					      TreeCompartment<TS,BUD>* tc)const
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "Hello, I'm Axis ";
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "Hello, I'm BranchingPoint ";
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    cout << "Hello, I'm TreeSegment ";

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
    cout << "Hello, I'm Bud ";

  else
    cout << "Who am I??? ";

  //counting them all
  n+=1;
  cout << n << endl;
  return n;
}

template <class TS,class BUD> TreeCompartment<TS,BUD>* 
MyExampleSignal<TS,BUD>::operator()(int& n,
			        TreeCompartment<TS,BUD>* tc)const
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "Hello, I'm Axis ";
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "Hello, I'm BranchingPoint ";
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
    cout << "Hello, I'm TreeSegment ";

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
    cout << "Hello, I'm Bud ";

  else
    cout << "Who am I??? ";
 
  n+=1;
  cout << n << endl;
  return tc;
}

template <class TS,class BUD> void DisplayStructure(Tree<TS,BUD>& t)
{
  DisplayStructure(&GetAxis(t));
}

template <class TS,class BUD> void DisplayStructure(TreeCompartment<TS,BUD>* tc)
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "[";
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*myaxis);
    list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      DisplayStructure(*first++);
    cout << "]" << flush;
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "[";
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);
    list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    for (int i = 0; i <axis_ls.size(); i++){
      DisplayStructure(*first++);
      if (i < axis_ls.size()-1)
	  cout << "," << flush;
    }
    cout << "]," << flush;
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    cout << "TS," << flush;
  }

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc)){
    cout << "B" << flush;
  }
}
