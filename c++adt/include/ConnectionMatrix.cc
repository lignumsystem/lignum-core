#include <ConnectionMatrix.h>

template <class TS,class BUD>
ConnectionMatrix<TS,BUD>::ConnectionMatrix(Axis<TS,BUD>& axis)
{
  size = CountTreeSegments(axis);
  
  pointer = new TreeSegment<TS,BUD>**[size];
  for (int i=0; i<size; i++)
    pointer[i] = new TreeSegment<TS,BUD>*[size];

  for (int x=0; x<size; x++)
    for (int y=0; y<size; y++)
      pointer[x][y] = NULL;
  TraverseAxis(axis, NULL);
  
}


template <class TS,class BUD>
int ConnectionMatrix<TS,BUD>::CountTreeSegments(Axis<TS,BUD> &ax) const
{
  int count = 0; 
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<TS,BUD>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(*I))
	{
	  count++;
	}
      if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(*I)){	 
	list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);  	  
	list<Axis<TS,BUD>*>::iterator I = axis_ls.begin();
	while(I != axis_ls.end()){
	  Axis<TS,BUD> *axis = *I;
	  count = count + CountTreeSegments(*axis);
	  I++;	    
	}
      }      
      I++;
    }
  return count;
}


//This method goes throw the given axis, and adds TreeSegments connected each other
//to the connection matrix. The first found TreeSegment is connected to the 
//TreeSegment given as parameter.   
template <class TS,class BUD>
void ConnectionMatrix<TS,BUD>::TraverseAxis(Axis<TS,BUD>& ax, TreeSegment<TS,BUD> *ts)
{
  TreeSegment<TS,BUD> *lastSegment = ts;
  list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<TS,BUD>*>::iterator I = ls.begin();
  
  while(I != ls.end()){      
    if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(*I)){
      addConnection(lastSegment, myts);
      lastSegment = myts;
    }      
      if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(*I)){
	list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);  	  
	list<Axis<TS,BUD>*>::iterator I = axis_ls.begin();
	while(I != axis_ls.end()){
	  Axis<TS,BUD> *axis = *I;
	  if (lastSegment)
	    TraverseAxis(*axis, lastSegment);
	  I++;	    
	}
      }
      if (Bud<TS,BUD>* mybud = dynamic_cast<Bud<TS,BUD>*>(*I))
	{	 
	}
      I++;
    }
}


template <class TS,class BUD>
void ConnectionMatrix<TS,BUD>::addConnection(TreeSegment<TS,BUD> *source, TreeSegment<TS,BUD> *target)
{  
  if (source == NULL || target == NULL)
    return;

  int i=0, a=0;
  while(pointer[i][i] != source) // source [TreeSegment] is not in the matrix yet
    {
      if (pointer[i][i] == NULL)
	{
	  pointer[i][i] = source;
	  break;
	}
      if (i>=size-1)
	{
	  cout << "Error in program (Tree.cc)" << endl;
	  return;
	}
      i++;
    }
  while(pointer[a][a]!=target) // target [TreeSegment] is not in the matrix yet
    {
      if (pointer[a][a] == NULL) 
	{
	  pointer[a][a] = target;
	  break;
	}

      if (a>=size-1)
	{
	  cout << "This shouldn't happen (ConnectionMatrix.cc)" << endl;
	  return;
	}
      a++;
    }
  pointer[i][a] = target;
} 

template<class TS,class BUD>
TreeSegment<TS,BUD>* ConnectionMatrix<TS,BUD>::getTreeSegment(int x,int y)const
{
  return pointer[x][y];
}


// This method prints the information of the matrix
template<class TS,class BUD>
void  ConnectionMatrix<TS,BUD>::print()const
{
  cout << "ConnectionMatrix:"<< endl;
  float ms = 0;
  for(int i=0; i<size; i++)
    {
      
      for(int a=0; a<size; a++)
	{
	  if (i == a)
	    cout << "   -   ";
	  else if (pointer[i][a]==NULL)
	    cout << "  NULL ";
	  else cout << " conne ";
	}
      if (pointer[i][i] != NULL)
	{
	  cout << "WaterMass[kg]" << " " << pointer[i][i]->getTsa().Wm; 
	  cout << "  paine " << pointer[i][i]->getTsa().Pr << endl;
	  ms = ms +  pointer[i][i]->getTsa().Wm;
	}
    }
  cout << "vetta yhteensa " << ms;
  cout << endl << endl;
}





