#include <ConnectionMatrix.h>

template <class TS>
ConnectionMatrix<TS>::ConnectionMatrix(Axis<TS>& axis)
{
  size = CountTreeSegments(axis);
  
  pointer = new TreeSegment<TS>**[size];
  for (int i=0; i<size; i++)
    pointer[i] = new TreeSegment<TS>*[size];

  for (int x=0; x<size; x++)
    for (int y=0; y<size; y++)
      pointer[x][y] = NULL;
  TraverseAxis(axis, NULL);
  
}


template <class TS>
int ConnectionMatrix<TS>::CountTreeSegments(Axis<TS> &ax) const
{
  int count = 0; 
  list<TreeCompartment<TS>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<TS>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(*I))
	{
	  count++;
	}
      if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(*I)){	 
	list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	list<Axis<TS>*>::iterator I = axis_ls.begin();
	while(I != axis_ls.end()){
	  Axis<TS> *axis = *I;
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
template <class TS>
void ConnectionMatrix<TS>::TraverseAxis(Axis<TS>& ax, TreeSegment<TS> *ts)
{
  TreeSegment<TS> *lastSegment = ts;
  list<TreeCompartment<TS>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<TS>*>::iterator I = ls.begin();
  
  while(I != ls.end()){      
    if (TreeSegment<TS>* myts = dynamic_cast<TreeSegment<TS>*>(*I)){
      addConnection(lastSegment, myts);
      lastSegment = myts;
    }      
      if (BranchingPoint<TS>* mybp = dynamic_cast<BranchingPoint<TS>*>(*I)){
	list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	list<Axis<TS>*>::iterator I = axis_ls.begin();
	while(I != axis_ls.end()){
	  Axis<TS> *axis = *I;
	  if (lastSegment)
	    TraverseAxis(*axis, lastSegment);
	  I++;	    
	}
      }
      if (Bud<TS>* mybud = dynamic_cast<Bud<TS>*>(*I))
	{	 
	}
      I++;
    }
}


template <class TS>
void ConnectionMatrix<TS>::addConnection(TreeSegment<TS> *source, TreeSegment<TS> *target)
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

template<class TS>
TreeSegment<TS>* ConnectionMatrix<TS>::getTreeSegment(int x,int y)const
{
  return pointer[x][y];
}


// This method prints the information of the matrix
template<class TS>
void  ConnectionMatrix<TS>::print()const
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





