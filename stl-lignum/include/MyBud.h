#ifndef MYBUD_H
#define MYBUD_H

#include <Bud.h>
#include <MyTreeSegment.h>

class MyTreeSegment;

class MyBud:public Bud<MyTreeSegment,MyBud>{
 public:
  MyBud(const Point<METER>& p, const PositionVector& d, 
	const TP omega, Tree<MyTreeSegment,MyBud>* tree)
    :Bud<MyTreeSegment,MyBud>(p,d,omega,tree){}
};
#endif
