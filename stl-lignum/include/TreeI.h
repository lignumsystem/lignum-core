#ifndef TREEI_H
#define TREEI_H

using namespace sky;

namespace Lignum{

template <class TS,class BUD>
Tree<TS,BUD>::Tree()
  :root_axis(Point(0,0,0),PositionVector(0,0,-1),*this)
{
  tree = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
template <class TS,class BUD>
Tree<TS,BUD>::Tree(const Point& p, const PositionVector& d)
  :TreeCompartment<TS,BUD>(p,d,this),f(5,5),axis(p,d,this),
    root_axis(p,d,*this)
{
}


template <class TS,class BUD>
Tree<TS,BUD>::Tree(const Point& p, const PositionVector& d, LGMdouble len, LGMdouble rad, int num_buds)
  :TreeCompartment<TS,BUD>(p,d,this),f(5,5),axis(p,d,this),
    root_axis(p,d,*this)
{
  //force the instantiation of BranchingPoint
  BranchingPoint<TS,BUD>(p,d,this);
  
  TreeSegment<TS,BUD> *ts = new TreeSegment<TS,BUD>(p,d, 0, len, rad,0, this);

  SetValue(*ts, omega, 1);
  SetValue(*ts, age, 0);

  if(TS* tts = dynamic_cast<TS *>(ts))
    {
      SetValue(*tts, Wf, 0.03);
    }
  SetValue(*ts, Rf, rad + 0.02);

  LGMdouble x_i = GetValue(*this, xi);
  LGMdouble ts_rad = GetValue(*ts, R);
  
  //Sapwood area corresponds to foliage mass
  LGMdouble A_s = (1.0 - GetValue(*this, xi)) * 
    GetValue(*ts, Wf)/(2.0*GetValue(*this, af)*
		       GetValue(*this, lr));
  
  if (A_s > PI_VALUE*ts_rad*ts_rad)
    SetValue(*ts, Rh, 0);
  
  
  LGMdouble r_h = sqrt((PI_VALUE*ts_rad*ts_rad - A_s)/PI_VALUE);
  SetValue(*ts, Rh, r_h);
  
  Point end_point = p + Point(0,0,len);
  BranchingPoint<TS,BUD> *bp = 
    new BranchingPoint<TS,BUD>(end_point,
			       PositionVector(0,0,1), 
			       this);
  
  Bud<TS,BUD> *bud1 = new Bud<TS,BUD>(end_point, d, 1, this);
  SetValue(*bud1, age, 1);
  SetValue(*bud1, state, ALIVE);

  Axis<TS,BUD> &axis = GetAxis(*this);
  InsertTreeCompartment(axis, ts);      
  InsertTreeCompartment(axis, bp);
  InsertTreeCompartment(axis , bud1);
  
  Axis<TS,BUD> *new_axes[20];
  int index = 0;
  
  PositionVector v2(0, sqrt(2.0)/2.0, sqrt(2.0)/2.0);
  LGMdouble delta_angle = 2 * PI_VALUE / num_buds;              
  while(num_buds > 0)
    {
      new_axes[index] = new Axis<TS,BUD>();
      
      v2.rotate(Point(0,0,0), PositionVector(0,0,1), delta_angle);
      Bud<TS,BUD> *new_bud = 
	new Bud<TS,BUD>(GetPoint(*bud1), v2, 2, this);
      SetValue(*new_bud,age, 1);
      SetValue(*new_bud,state, ALIVE);
      
      InsertTreeCompartment(*new_axes[index], new_bud);
      index++;
      num_buds--;
    }
}



//Get a parameter value 
template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMPD name)
{
  if (name == af)
    return tree.tp.af;

  else if (name == ar)
     return tree.tp.ar;

  else if (name == lr)
    return tree.tp.lr;
  
  else if (name == mf)
    return tree.tp.mf;

  else if (name == mr)
    return tree.tp.mr;

  else if (name == ms)
    return tree.tp.ms;

  else if (name == na)
    return tree.tp.na;

  else if (name == nl)
    return tree.tp.nl;

  else if (name == pr)
    return tree.tp.pr;

  else if (name == q)
    return tree.tp.q;

  else if (name == sr)
    return tree.tp.sr;

  else if (name == ss)
    return tree.tp.ss;

  else if (name == rho)
    return tree.tp.rho;

  else if (name == rho_root)
    return tree.tp.rho_root;
  
  else if ( name == rho_hair)
    return tree.tp.rho_hair;

  else if (name == xi)
     return tree.tp.xi;

  else if (name == zbrentEpsilon)
     return tree.tp.zbrentEpsilon;

  else{
    cerr << "Tree::GetValue() uknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return 0.0;
}

//Change a parameter value, return the old value
template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMPD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);

  if (name == af)
    tree.tp.af = value;

  else if (name == ar)
    tree.tp.ar = value;

  else if (name == lr)
    tree.tp.lr = value;
  
  else if (name == mf)
    tree.tp.mf = value;

  else if (name == mr)
    tree.tp.mr = value;

  else if (name == ms)
    tree.tp.ms = value;

  else if (name == na)
    tree.tp.na = value;

  else if (name == nl)
    tree.tp.nl = value;

  else if (name == pr)
    tree.tp.pr = value;

  else if (name == q)
    tree.tp.q = value;

  else if (name == sr)
    tree.tp.sr = value;

  else if (name == ss)
    tree.tp.ss = value;

  else if (name == rho)
    tree.tp.rho = value;

  else if (name == rho_root)
    tree.tp.rho_root = value;

  else if (name == rho_hair)
    tree.tp.rho_hair = value;

  else if (name == xi)
    tree.tp.xi = value;

  else if (name == zbrentEpsilon)
    tree.tp.zbrentEpsilon = value;

  else{
    cerr << "Tree::SetValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return old_value;
}

template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMTD name)
{
  if (name == lambda)
    return tree.ttp.lambda;
  
  else{
    cerr << "GetValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMTD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);
  
  if (name == lambda)
    tree.ttp.lambda = value;
  else{
    cerr << "SetValue unknown parameter: " << name << " returning "
	 << old_value << endl;
  }
  return old_value;
}

//Index the tree attribute vector with range check.
template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMTAD name)
{ 
  //no need to go to tree compartment, these are tree level attributes
  return  tree.ta.v[name];
}

//Index the tree attribute vector with range check.
template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMTAD name, const LGMdouble value)
{

  LGMdouble old_value = GetValue(tree,name);
  //no need to go to tree compartment, these are tree level attributes
  tree.ta.v[name] = value;
  
  return old_value;
}
  

template <class TS,class BUD>
Axis<TS,BUD>& GetAxis(Tree<TS,BUD>& t)
{
  return t.axis;
}

template <class TS,class BUD>
RootAxis<Tree<TS,BUD> >& GetRootAxis(Tree<TS,BUD>& t)
{
  return t.root_axis;
}

//Return a tree function as a ParametricCurve
template<class TS, class BUD>
const ParametricCurve& GetFunction(const Tree<TS,BUD>& tree, LGMF name)
{  

  if (name == LGMAL){
    return tree.tf.al;
  }

  else if (name == LGMFM){
     return tree.tf.fm;
  }

  else if (name == LGMIP){
    return tree.tf.ip;
  }

  else if (name == LGMNB){
    return tree.tf.nb;
  }

  else if (name == LGMLONB){
    return tree.tf.LightOnNumBuds;
  }

  else if (name == LGMVI){
    return tree.tf.vi;
  }

  else if (name == LGMVIONB){
    return tree.tf.VigourOnNumBuds;
  }

  else{
    cerr << "GetFunction unknown function: " << name << endl;
  }
  //Error happened throw useless ParametricCurve. 
  throw ParametricCurve();
}
  
//At the moment returns the name of the only (ASCII) file that contains
//the definition of the initial tree. Later - maybe - several such files.
template<class TS, class BUD>
string GetTreeInitializationFile(Tree<TS,BUD>& tree) {
  return tree.tif.treeFile;
}


template <class TS,class BUD>
void SetFirmament(const Tree<TS,BUD>& tree, const FirmamentWithMask& frmnt)
{
  tree.f = frmnt;
}
 
template <class TS,class BUD>
FirmamentWithMask& GetFirmament(Tree<TS,BUD>& tree) {
  return tree.f;
}




} //close namespace Lignum

#endif //TREEI_H



#ifdef TREE
#include <stdlib.h>
#include <iostream>

int main()
{
  cout << "OK" << endl;
  exit(0);
}


#endif

