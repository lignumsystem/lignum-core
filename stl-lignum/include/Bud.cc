
#include <Bud.h>

BudAttributes::BudAttributes()
  :ip(0.0),omega(0.0)
{
}

//default constructor
template <class TS>
Bud<TS>::Bud()
{
  tree = NULL;
}

//Define position and direction in 3D space.
//Define gravelius order 
//Also to access tree level parameters etc., define
//the tree this bud is part of
template <class TS>
Bud<TS>::Bud(const Point<METER>& p, const PositionVector& d, const TP go, 
	     Tree<TS>* t)
  :TreeCompartment<TS>(p,d,t)
{
  SetBudAttributeValue(*this,omega,go);
}

template <class TS>
TS& Bud<TS>::createTreeSegment()const
{
  TS* ts = new TS();
  return (TS&) *ts;
}

template <class TS>
Bud<TS>& Bud<TS>::createBud()const
{
  Bud<TS>* bud = new Bud<TS>();
  return (Bud&) *bud;
}

template <class TS>
BranchingPoint<TS>& Bud<TS>::createBranchingPoint()const
{
  BranchingPoint<TS>* bp = new BranchingPoint();
  return (BranchingPoint&) *bp;
}

template <class TS>   
TP GetBudAttributeValue(const Bud<TS>& bud, const TAD name)
{
  if (name == omega)
    return bud.ba.omega;

  else if (name == ip)
    return bud.ba.ip;

  else{
    cout << "Unknown attribute: " << name << endl;
    cout << "Returning 0.0" << endl;
  }

  return 0.0;
}

template <class TS>    
TP SetBudAttributeValue(Bud<TS>& bud, const TAD name, const TP value)
{
  TP old_value = GetBudAttributeValue(bud,name);

  if (name == omega)
    bud.ba.omega = value;

  else if (name == ip)
   bud.ba.ip = value;

  return old_value;
}
