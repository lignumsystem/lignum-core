#ifndef MYTREESEGMENT_H
#define MYTREESEGMENT_H

#include <HwTreeSegment.h>
#include <CfTreeSegment.h>


namespace Lignum{

class MyBud;

class MyTreeSegment:public TreeSegment<MyTreeSegment,MyBud>
{
public:
  MyTreeSegment(const Point<METER>& p, const PositionVector& d, const LGMdouble go,
		const METER l, const METER r, const METER rn, 
		Tree<MyTreeSegment,MyBud>* t)
    :TreeSegment<MyTreeSegment,MyBud>(p,d,go,l,r,rn,t){}
};


class MyHwTreeSegment:public HwTreeSegment<MyHwTreeSegment,MyBud>
{
public:
  MyHwTreeSegment(const Point<METER>& p, const PositionVector& d, const LGMdouble go,
		  const METER l, const METER r, const METER rn,
		  Tree<MyHwTreeSegment,MyBud>* t)
    :HwTreeSegment<MyHwTreeSegment,MyBud>(p,d,go,l,r,rn,t){}
};

class MyCfTreeSegment:public CfTreeSegment<MyCfTreeSegment,MyBud>
{
public:
  MyCfTreeSegment(const Point<METER>& p, const PositionVector& d, const LGMdouble go,
		  const METER l, const METER r, const METER rn,
		  Tree<MyCfTreeSegment,MyBud>* t)
    :CfTreeSegment<MyCfTreeSegment,MyBud>(p,d,go,l,r,rn,t){}
};

} //close namespace Lignum
#endif
