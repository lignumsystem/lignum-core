#ifndef BUD_H
#define BUD_H

#include <Point.h>
#include <LGMdecl.h>

namespace Lignum{

using namespace cxxadt;

class BudAttributes{
public:
  BudAttributes();
  LGMdouble ip;             //Photosynthetic light ratio (shadiness)
  LGMdouble omega;          //Gravelius order
  STATUS state;      //LIVE, DEAD or DORMANT
};


template <class TS,class BUD=DefaultBud<TS> >
class Bud: public TreeCompartment<TS,BUD>{
friend LGMdouble GetValue(const Bud<TS,BUD>& bud, const LGMAD name);
friend LGMdouble SetValue(Bud<TS,BUD>& bud, const LGMAD name, const LGMdouble value);
friend STATUS GetValue(const Bud<TS,BUD>& bud, const LGMAS name);
friend STATUS SetValue(Bud<TS,BUD>& bud, const LGMAS name, const STATUS value);
public:
  Bud();
  Bud(const Point<METER>& p, const PositionVector& d, const LGMdouble omega, Tree<TS,BUD>* tree);
  TS& createTreeSegment()const;
  Bud<TS,BUD>& createBud()const;
  BranchingPoint<TS,BUD>& createBranchingPoint()const;
  virtual void Production(){/*do nothing*/}
  virtual LGMdouble GetProduction(){return 0.0;}
private:
  BudAttributes ba;
};

}//closing namespace Lignum

#include <BudI.h>
#endif
