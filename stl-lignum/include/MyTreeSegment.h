#ifndef MYTREESEGMENT_H
#define MYTREESEGMENT_H

#include <HwTreeSegment.h>
#include <CfTreeSegment.h>
#include <Ellipse.h>

namespace Lignum{



  class MyBud;
  class MyHwBud;
  class MyCfBud;

  class MyTreeSegment:public TreeSegment<MyTreeSegment,MyBud>
  {
  public:
    MyTreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
		  const METER l, const METER r, const METER rn, 
		  Tree<MyTreeSegment,MyBud>* t)
      :TreeSegment<MyTreeSegment,MyBud>(p,d,go,l,r,rn,t){}
  };


  class MyHwTreeSegment:public HwTreeSegment<MyHwTreeSegment,MyHwBud, cxxadt::Ellipse>
  {
  public:
    MyHwTreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
		    const METER l, const METER r, const METER rn,
		    Tree<MyHwTreeSegment,MyHwBud>* t)
      :HwTreeSegment<MyHwTreeSegment,MyHwBud, Ellipse>(p,d,go,l,r,rn,t){}
  };

  class MyCfTreeSegment:public CfTreeSegment<MyCfTreeSegment,MyCfBud>{
  public:
    MyCfTreeSegment(const cxxadt::Point& p, const PositionVector& d, const LGMdouble go,
		    const METER l, const METER r, const METER rn,
		    Tree<MyCfTreeSegment,MyCfBud>* t)
      :CfTreeSegment<MyCfTreeSegment,MyCfBud>(p,d,go,l,r,rn,t){}
  };

} //close namespace Lignum

#endif
