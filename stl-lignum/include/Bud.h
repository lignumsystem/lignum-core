#ifndef BUD_H
#define BUD_H

template <class TS> class DefaultBud;
#include <TreeSegment.h>

class BudAttributes{
public:
  BudAttributes();
  TP ip;             //Photosynthetic light ratio (shadiness)
  TP omega;          //Gravelius order
};

template <class TS,class BUD=DefaultBud<TS> >
class Bud: public TreeCompartment<TS,BUD>{
friend TP GetBudAttributeValue(const Bud<TS,BUD>& bud, const TAD name);
friend TP SetBudAttributeValue(Bud<TS,BUD>& bud, const TAD name, const TP value);
public:
  Bud();
  Bud(const Point<METER>& p, const PositionVector& d, const TP omega, Tree<TS,BUD>* tree);
  TS& createTreeSegment()const;
  Bud<TS,BUD>& createBud()const;
  BranchingPoint<TS,BUD>& createBranchingPoint()const;
  virtual void Production(){/*do nothing*/}
  virtual TP GetProduction(){return 0.0;}
private:
  BudAttributes ba;
};

#include <BudI.h>
#endif
