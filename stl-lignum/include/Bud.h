#ifndef BUD_H
#define BUD_H

#include <TreeSegment.h>

class BudAttributes{
public:
  BudAttributes();
  TP ip;             //Photosynthetic light ratio (shadiness)
  TP omega;          //Gravelius order
};

template <class TS>
class Bud: public TreeCompartment<TS>{
friend TP GetBudAttributeValue(const Bud<TS>& bud, const TAD name);
friend TP SetBudAttributeValue(Bud<TS>& bud, const TAD name, const TP value);
public:
  Bud();
  Bud(const Point<METER>& p, const PositionVector& d, const TP omega, Tree<TS>* tree);
  TS& createTreeSegment()const;
  Bud<TS>& createBud()const;
  BranchingPoint<TS>& createBranchingPoint()const;
  virtual void Production(){/*do nothing*/}
  virtual TP GetProduction(){return 0.0;}
private:
  BudAttributes ba;
};

#endif
