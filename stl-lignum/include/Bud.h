#ifndef BUD_H
#define BUD_H

#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <TreeCompartment.h>

namespace Lignum{

using namespace cxxadt;

class BudAttributes{
public:
  BudAttributes();
  LGMdouble ip;             //Photosynthetic light ratio (shadiness)
  LGMdouble omega;          //Gravelius order
  LGMdouble type;           //dominant, apical, lateral etc.
  LGMdouble status;         //counter from N to 0;
  STATUS state;             //LIVE, DEAD or DORMANT
};


template <class TS,class BUD=DefaultBud<TS> >
class Bud: public TreeCompartment<TS,BUD>{
template <class TS1,class BUD1>
friend LGMdouble GetValue(const Bud<TS1,BUD1>& bud, const LGMAD name);

template <class TS1,class BUD1>
friend LGMdouble SetValue(Bud<TS1,BUD1>& bud, const LGMAD name, const LGMdouble value);

template <class TS1,class BUD1>
friend STATUS GetValue(const Bud<TS1,BUD1>& bud, const LGMAS name);

template <class TS1,class BUD1>
friend STATUS SetValue(Bud<TS1,BUD1>& bud, const LGMAS name, const STATUS value);
public:
  Bud();
  Bud(const Point& p, const PositionVector& d, const LGMdouble omega, Tree<TS,BUD>* tree);
  TS& createTreeSegment()const;
  Bud<TS,BUD>& createBud()const;
  BranchingPoint<TS,BUD>& createBranchingPoint()const;
  virtual void Production(){/*do nothing*/}
  virtual LGMdouble GetProduction(){return 0.0;}
  void move(PositionVector dir, LGMdouble length);
private:
  BudAttributes ba;
};

}//closing namespace Lignum

#include <BudI.h>
#endif
