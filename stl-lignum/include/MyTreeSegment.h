#ifndef MYTREESEGMENT_H
#define MYTREESEGMENT_H

#include <Tree.h>
#include <HwTreeSegment.h>
#include <CfTreeSegment.h>

class MyTreeSegment:public TreeSegment<MyTreeSegment>
{
  public:
  MyTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
		const METER l, const METER r, const METER rn, 
		Tree<MyTreeSegment>* t)
    :TreeSegment<MyTreeSegment>(p,d,go,l,r,rn,t){}
};


class MyHwTreeSegment:public HwTreeSegment<MyHwTreeSegment>
{
public:
  MyHwTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
		  const METER l, const METER r, const METER rn,
		  Tree<MyHwTreeSegment>* t)
    :HwTreeSegment<MyHwTreeSegment>(p,d,go,l,r,rn,t){}
};

class MyCfTreeSegment:public CfTreeSegment<MyCfTreeSegment>
{
public:
  MyCfTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
		  const METER l, const METER r, const METER rn,
		  Tree<MyCfTreeSegment>* t)
    :CfTreeSegment<MyCfTreeSegment>(p,d,go,l,r,rn,t){}
};

#endif
