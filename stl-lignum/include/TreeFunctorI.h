#ifndef TREE_FUNCTORI_H
#define TREE_FUNCTORI_H

namespace Lignum{

//Use built-in operator dynamic_cast
//to resolve the data_type of a tree compartment
template <class TS,class BUD>
TreeCompartment<TS,BUD>*  DisplayType<TS,BUD>::operator ()(TreeCompartment<TS,BUD>*tc)const
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
    if (ls.empty())
      cout <<  "]" << flush;
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


template <class TS,class BUD>
CheckCoordinates<TS,BUD>::CheckCoordinates(double e)
  :epsilon(e)
{
}

//Check coordinates: Each tree compartment should match
//the "id" given. Segment changes the "id" to its end point 
template <class TS,class BUD> TreeCompartment<TS,BUD>* 
CheckCoordinates<TS,BUD>::operator ()(Point& id,
				       TreeCompartment<TS,BUD>* tc)const
{
  Point p = GetPoint(*tc);

  if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
    if (id != p && (p || id) > epsilon)
      cout << "A: p || id " << (p || id) << endl;
  }

  else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
    if (id != p && (p || id) > epsilon)
      cout <<  "BP: p || id " << (p || id) << endl;
  }

  else if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
    if (id != p && (p || id) > epsilon)
      cout << "TS: p || id " << (p || id) << endl; 
    id = GetEndPoint(*ts);
  }

  else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc)){
    if (id != p && (p || id) > epsilon)
      cout << "B: p || id " << (p || id) << endl; 
  }
  return tc;
}




template <class TS, class BUD>
Point GetBoundingBox(Tree<TS,BUD> &tree, Point &p)
{
        return GetBoundingBox(GetAxis(tree), p);
}




template <class TS, class BUD>
Point GetBoundingBox(Axis<TS,BUD> &ax, Point &p)
{
  std::list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(ax);
  std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

        
        
  while(I != ls.end())
    {                   
      TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I);   
      
      if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
	{  
	  Point pp = GetPoint(*myts);     
	  PositionVector dir = GetDirection(*myts);
	  LGMdouble l = GetValue(*myts, L);
			
	  pp = pp + Point(dir.getX()*l, dir.getY()*l, dir.getZ()*l);
	  
	  double x = pp.getX();
	  double y = pp.getY();
	  double z = pp.getZ();
	  
	  x = sqrt(x*x);
	  y = sqrt(y*y);
	  z = sqrt(z*z);
	  
	  if (x > p.getX())
	    p += Point(x - p.getX(),0,0);
	  
	  if (y > p.getY())
	    p += Point(0, y - p.getY(), 0);
	  
	  if (z > p.getZ())
	    p += Point(0, 0, z - p.getZ());
                } 
      
      if (BranchingPoint<TS, BUD>* mybp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I))
	{ 
	  std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*mybp);          
	  std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	  
	  
	  while(II != axis_ls.end())
	    {
	      Axis<TS,BUD> *axis = *II;       
	      p = GetBoundingBox(*axis, p);                     
	      II++;   
	    }
	  
	}
      I++;
    }
  return p;
}











}//closing namespace Lignum

#endif
