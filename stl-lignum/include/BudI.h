#ifndef BUDI_H
#define BUDI_H


namespace Lignum{

//default constructor
template <class TS,class BUD>
Bud<TS,BUD>::Bud()
{
  tree = NULL;
}

//Define position and direction in 3D space.
//Define gravelius order 
//Also to access tree level parameters etc., define
//the tree this bud is part of
template <class TS,class BUD>
Bud<TS,BUD>::Bud(const Point& p, const PositionVector& d, const LGMdouble go, 
	     Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
  SetValue(*this,omega,go);
}

template <class TS,class BUD>
TS& Bud<TS,BUD>::createTreeSegment()const
{
  TS* ts = new TS();
  return (TS&) *ts;
}

template <class TS,class BUD>
Bud<TS,BUD>& Bud<TS,BUD>::createBud()const
{
  Bud<TS,BUD>* bud = new Bud<TS,BUD>();
  return (Bud<TS,BUD>&) *bud;
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>& Bud<TS,BUD>::createBranchingPoint()const
{
  BranchingPoint<TS,BUD>* bp = new BranchingPoint<TS,BUD>();
  return (BranchingPoint<TS,BUD>&) *bp;
}

template <class TS,class BUD>   
LGMdouble GetValue(const Bud<TS,BUD>& bud, const LGMAD name)
{
  if (name == omega)
    return bud.ba.omega;

  else if (name == ip)
    return bud.ba.ip;

  else{
    return GetValue(dynamic_cast<const TreeCompartment<TS,BUD>&>(bud), name);

    //    cout << "Unknown attribute: " << name << endl;
    //    cout << "Returning 0.0" << endl;
  }

  //  return 0.0;
}

template<class TS, class BUD>
LGMdouble SetValue(Bud<TS,BUD>& bud, const LGMAD name, const LGMdouble value)
{

  LGMdouble old_value = GetValue(bud,name);

  if (name == omega)
    bud.ba.omega = value;

  else if (name == ip)
    bud.ba.ip = value;

  else{
    //    cout << "Unknown attribute: " << name << endl;
    //    cout << "Returning 0.0" << endl;
        old_value = SetValue(dynamic_cast<TreeCompartment<TS,BUD>&>(bud), name,value);
  }

  return old_value;
}

template<class TS, class BUD>
STATUS GetValue(const Bud<TS,BUD>& bud, const LGMAS name)
{
  if (name == state)
    return bud.ba.state;

  else{
    cout << "Unknown attribute: " << name << endl;
    cout << "Returning 0.0" << endl;
  }

  return DEAD;
}

template <class TS,class BUD>    
STATUS SetValue(Bud<TS,BUD>& bud, const LGMAS name, const STATUS value)
{
  STATUS old_value = GetValue(bud,name);

  if(name == state)
    bud.ba.state = value;

  return old_value;
}

template <class TS,class BUD>
void Bud<TS,BUD>::move(PositionVector dir, LGMdouble length)
{
        Point p = GetPoint(*this);
        Point tmp(dir.getX()*length, dir.getY()*length, dir.getZ()*length);
	p = p + tmp;

        this->point = p;
}



}//closing namespace Lignum

#endif






