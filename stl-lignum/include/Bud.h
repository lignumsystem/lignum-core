#ifndef BUD_H
#define BUD_H

#include <Point.h>
#include <LGMdecl.h>

namespace Lignum{

class BudAttributes{
public:
  BudAttributes();
  TP ip;             //Photosynthetic light ratio (shadiness)
  TP omega;          //Gravelius order
  STATUS state;      //LIVE, DEAD or DORMANT
};


template <class TS,class BUD=DefaultBud<TS> >
class Bud: public TreeCompartment<TS,BUD>{
friend TP GetAttributeValue(const Bud<TS,BUD>& bud, const TAD name);
friend TP SetAttributeValue(Bud<TS,BUD>& bud, const TAD name, const TP value);
friend STATUS GetAttributeValue(const Bud<TS,BUD>& bud, const TAS name);
friend STATUS SetAttributeValue(Bud<TS,BUD>& bud, const TAS name, const STATUS value);
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

}//closing namespace Lignum

#include <BudI.h>
#endif
