#ifndef DEFAULTBUD_H
#define DEFAULTBUD_H

#include <Bud.h>


template <class TS>
class DefaultBud:public Bud<TS,DefaultBud<TS> >{
 public:
  DefaultBud(const Point<METER>& p, const PositionVector& d, 
	     const TP omega, Tree<TS,DefaultBud<TS> >* tree)
    :Bud<MyTreeSegment,DefaultBud<TS> >(p,d,omega,tree){}
};
#endif
