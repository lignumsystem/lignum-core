#ifndef TREE_FUNCTORI_H
#define TREE_FUNCTORI_H

namespace Lignum{

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
      SetValue(*myts, Wm, pow(GetValue(*myts, R), 2) * 
			  PI_VALUE * GetValue(*myts, L) * 0.5 *  
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
    cout << "["; //begin of axis
    list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*myaxis);
    list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
    list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
    while (first != last)
      DisplayStructure(*first++);
    cout << "]" << flush; //end of axis
  }

  else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout << "{"; //begin of branching point
    list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);
    list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
    list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
    for (int i = 0; i <axis_ls.size(); i++){
      DisplayStructure(*first++);
    }
    //the end of the branching point
    //the comma is because at least a bud follows  
    cout << "}," << flush; 
  }

  else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    //the comma is because we know that a branching point will follow 
    cout << "TS," << flush;
    
  }

  else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc)){
    cout << "B" << flush;
  }
}

template <class TS,class BUD> TreeCompartment<TS,BUD>* 
DisplayStructureFunctor<TS,BUD>:: operator ()(DisplayStructureData& id,
					      TreeCompartment<TS,BUD>* tc)const
{
  //collect data: number of compartments in an axis and tell the first segment it
  //is the first segment in that axis
  if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    list<TreeCompartment<TS,BUD>*> ls = GetTreeCompartmentList(*axis);
    id.number_of_compartments = ls.size();
    id.first_segment = true;
    cout <<  "[" << flush;
  }

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    cout <<  "{" << flush; 
  }

  else if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    //if not the first segment, ending a branching point
    if (!id.first_segment){
      cout << "}," << flush;
    }
    //tell the next segment it is not the first segment
    id.first_segment = false;
    //a branching point follows
    cout << "TS," << flush; 
  }

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc)){
    //if only one bud in an axis it ends that axis
    if (id.number_of_compartments == 1)
      cout << "B]" << flush;
    else 
      //otherwise ending a branching point and that axis
      cout << "},B]" << flush;
  }
  return tc;
}

}//closing namespace Lignum

#endif
