#ifndef CONNECTION_MATRIX_H
#define CONNECTION_MATRIX_H

#include <vector>
#include <LGMUnits.h>

/*
template <class TS,class BUD=DefaultBud<TS> > class Axis;
template <class TS,class BUD=DefaultBud<TS> > class TreeSegment;
*/

namespace Lignum{

template <class TS,class BUD> class Axis;
template <class TS,class BUD> class TreeSegment;


template <class TS,class BUD>
class ConnectionMatrix{
public:
  ConnectionMatrix(Axis<TS,BUD>& axis);    
  void print()const;
  int getSize()const{return size;}
  int getNumberOfAxes(void)const;
  bool lastTreeSegment(TreeSegment<TS,BUD> *ts)const;
  TreeSegment<TS,BUD>* getTreeSegment(int,int)const;
  void saveDeltaPressure(TreeSegment<TS,BUD> *ts, LGMdouble delta_pressure);
  LGMdouble getDeltaPressure(TreeSegment<TS,BUD> *ts);
  TreeSegment<TS,BUD>* getTreeSegment(int i)const{ return pointer[i][i];}
private:
  TreeSegment<TS,BUD> ***pointer;
  std::vector<double> pressure;
  int size;
  int CountTreeSegments(Axis<TS,BUD> &ax) const;
  void TraverseAxis(Axis<TS,BUD> &ax, TreeSegment<TS,BUD> *ts);
  void addConnection(TreeSegment<TS,BUD> *ts1, TreeSegment<TS,BUD> *ts2);
};



template <class TS,class BUD>
ConnectionMatrix<TS,BUD>::ConnectionMatrix(Axis<TS,BUD>& axis)
{
  size = CountTreeSegments(axis);
  
  pointer = new TreeSegment<TS,BUD>**[size];
  for (int i=0; i<size; i++)
    pointer[i] = new TreeSegment<TS,BUD>*[size];

  pressure.resize(size);
  for (int x=0; x<size; x++)
    {      
      for (int y=0; y<size; y++)
	pointer[x][y] = NULL;
    }
  this->TraverseAxis(axis, NULL);
}


template <class TS,class BUD>
int ConnectionMatrix<TS,BUD>::CountTreeSegments(Axis<TS,BUD> &ax) const
{
  int count = 0; 
  std::list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(ax);
  std::list<TreeCompartment<TS,BUD>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(*I))
	{
	  count++;
	}
      if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(*I)){	 
    std::list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);  	  
	std::list<Axis<TS,BUD>*>::iterator I = axis_ls.begin();
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
  std::list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(ax);
  std::list<TreeCompartment<TS,BUD>*>::iterator I = ls.begin();
  
  while(I != ls.end()){      
    if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(*I)){
      addConnection(lastSegment, myts);
      lastSegment = myts;
    }      
      if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(*I)){
	std::list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);  	  
	std::list<Axis<TS,BUD>*>::iterator I = axis_ls.begin();
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
LGMdouble ConnectionMatrix<TS,BUD>::getDeltaPressure(TreeSegment<TS,BUD> *ts)
{
  int i=0;

  while(pointer[i][i] != ts && i<size)
    {
      i++;
    }
  if (i == size)
    {
      cout << "CONNECTIONMATRIX:: segment not found" << endl;
      return 0;
    }
  else
    return pressure[i];
}
 

template <class TS,class BUD>
void ConnectionMatrix<TS,BUD>::saveDeltaPressure(TreeSegment<TS,BUD> *ts, LGMdouble delta_pressure)
{
  int i=0;

  while(pointer[i][i] != ts && i<size)
    {
      i++;
    }
  if (i == size)
    {
      cout << "CONNECTIONMATRIX:: segment not found" << endl;
      return;
    }
  else
    pressure[i] = delta_pressure;
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


// This method counts and return the number of ending shoots.
template<class TS,class BUD>
int ConnectionMatrix<TS,BUD>::getNumberOfAxes()const
{
  int count = 0;
  for(int i=0; i<size; i++)
    {
      bool no_connection = true;
      for(int a=0; a<size; a++)
	 if (pointer[i][a]!=NULL && i!=a)
	   no_connection = false;
      if (no_connection)
	count++;
    }
  return count;
}


template<class TS,class BUD>
bool ConnectionMatrix<TS,BUD>::lastTreeSegment(TreeSegment<TS,BUD> *ts)const
{
  for(int i=0; i<size; i++)
    {
      if (pointer[i][i] == ts)
	{
	  for(int a=0; a<size; a++)
	    if (pointer[i][a]!=NULL  && i!=a)
	      return false;
	  return true;
	}
    }
  return false;
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
	    cout << "0";
	  else if (pointer[i][a]==NULL)
	    cout << "-";
	  else cout << "X";
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



}

#endif
