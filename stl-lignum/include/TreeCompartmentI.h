#ifndef TREECOMPARTMENTI_H
#define TREECOMPARTMENTI_H

namespace Lignum{


template <class TS,class BUD>
TreeCompartment<TS,BUD>::TreeCompartment()
{
}

template <class TS,class BUD>
TreeCompartment<TS,BUD>::TreeCompartment(const Point& p, const PositionVector& d, 
				 Tree<TS,BUD>* t)
  :point(p),direction(d), tc_age(0.0)
{
  //normalize the direction vector
  //to avoid domain problems e.g., with visualization
  //using built-in acos etc. functions. 
  direction.normalize();

  tree = t;

}

template <class TS,class BUD>
TreeCompartment<TS,BUD>::~TreeCompartment()
{
}

template <class TS,class BUD>
Point GetPoint(const TreeCompartment<TS,BUD>& tc)
{
  return tc.point;
}

template <class TS,class BUD>
PositionVector GetDirection(const TreeCompartment<TS,BUD>& tc)
{
  return  tc.direction;
}


template <class TS,class BUD>
void SetPoint(TreeCompartment<TS,BUD>& tc, const Point& p)
{
	tc.point = p;
}

template <class TS,class BUD>
void SetDirection(TreeCompartment<TS,BUD>& tc, const PositionVector& pv)
{
	tc.direction = pv;
	tc.direction.normalize();
}


template <class TS,class BUD>
Tree<TS,BUD>& GetTree(const TreeCompartment<TS,BUD>& tc)
{
  return *(tc.tree);
}






template <class TS,class BUD>
LGMdouble GetValue(const TreeCompartment<TS,BUD>& tc, const LGMAD name)
{
  LGMdouble unknown_value = 0.0;

  if (name == LGAage)
    return tc.tc_age;

  else
  {
		cout << "SetValue: unknown attribute:" << name << endl;
		//MessageBox(NULL, "Setvalue " + name, NULL, NULL);
	}

  return unknown_value;
}



template <class TS,class BUD>
LGMdouble SetValue(TreeCompartment<TS,BUD>& tc, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tc,name);
  
  if (name == LGAage)
    tc.tc_age = value;
  
  else{
    cerr << "Tree Compartment GetValue: Unknown attribute " << name << endl;
  }

  return old_value;
}



}//closing namespace Lignum

#endif
