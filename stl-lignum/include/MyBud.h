#ifndef MYBUD_H
#define MYBUD_H

#include <MyBud.h>
#include <MyTreeSegment.h>

namespace Lignum{
class MyTreeSegment;

class MyBud:public Bud<MyTreeSegment,MyBud>{
 public:
  MyBud(const Point<METER>& p, const PositionVector& d, 
	const TP omega, Tree<MyTreeSegment,MyBud>* tree)
    :Bud<MyTreeSegment,MyBud>(p,d,omega,tree){}
};

}//closing namespace Lignum
#endif


