#ifndef BUD_H
#define BUD_H

#include <LGMSymbols.h>
#include <LGMUnits.h>
#include <TreeCompartment.h>
#include <TreeSegment.h>

class BranchingPoint;

class BudAttributes{
public:
  BudAttributes();
  TP ip;             //Photosynthetic light ratio (shadiness)
  TP omega;          //Gravelius order
};

class Bud: public TreeCompartment{
friend TP GetAttributeValue(const Bud& bud, const TAD name);
friend TP SetAttributeValue(Bud& bud, const TAD name, const TP value);
public:
  Bud();
  Bud(const Point<METER>& p, const PositionVector& d, const TP omega, Tree* tree);
  TreeSegment& createTreeSegment()const;
  Bud& createBud()const;
  BranchingPoint& createBranchingPoint()const;
private:
  BudAttributes ba;
};

#endif
