#ifndef BUDI_H
#define BUDI_H

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
Bud<TS,BUD>::Bud(const Point<METER>& p, const PositionVector& d, const TP go, 
	     Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
  SetBudAttributeValue(*this,omega,go);
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
  return (Bud&) *bud;
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>& Bud<TS,BUD>::createBranchingPoint()const
{
  BranchingPoint<TS,BUD>* bp = new BranchingPoint();
  return (BranchingPoint&) *bp;
}

template <class TS,class BUD>   
TP GetBudAttributeValue(const Bud<TS,BUD>& bud, const TAD name)
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

template <class TS,class BUD>    
TP SetBudAttributeValue(Bud<TS,BUD>& bud, const TAD name, const TP value)
{
  TP old_value = GetBudAttributeValue(bud,name);

  if (name == omega)
    bud.ba.omega = value;

  else if (name == ip)
   bud.ba.ip = value;

  return old_value;
}

#endif
