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
      SetTSAttributeValue(*myts, Wm, pow(GetTSAttributeValue(*myts, R), 2) * 
			  PI_VALUE * GetTSAttributeValue(*myts, L) * 0.5 *  
			  1000); 
      SetTSAttributeValue(*myts, Pr, -GetTSAttributeValue(*myts, Hm) 
			  * 9.81 * 1000);     
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


template <class TS,class BUD> int&
DisplayStructure<TS,BUD>::operator()(int& depth,TreeCompartment<TS,BUD>* tc)const
{
  if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
    cout << "[" << flush;
    depth++;
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "[" << flush;
    depth++;
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    cout << "TS," << flush;
  }

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc)){
    if (depth > 1){
      cout << "B]]," << flush;
      depth--;depth--;
    }
    else{ //depth == 1
      cout << "B]" << flush;
      depth--;
    }
  }
  else 
    cout << "Who??" << flush;

  return depth;
}





