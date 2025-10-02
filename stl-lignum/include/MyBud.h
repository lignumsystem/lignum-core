/// \file MyBud.h
/// \brief Example tree bud not active
#ifndef MYBUD_H
#define MYBUD_H

#include <Bud.h>
#include <MyTreeSegment.h>


namespace Lignum{
  class MyTreeSegment;
  class MyHwTreeSegment;
  class MyCfTreeSegment;

  class MyBud:public Bud<MyTreeSegment,MyBud>{
  public:
    MyBud(const Point& p, const PositionVector& d, 
	  const LGMdouble omega, Tree<MyTreeSegment,MyBud>* tree)
      :Bud<MyTreeSegment,MyBud>(p,d,omega,tree){}
  };

  class MyHwBud:public Bud<MyHwTreeSegment,MyHwBud>{
  public:
    MyHwBud(const Point& p, const PositionVector& d, 
	    const LGMdouble omega, Tree<MyHwTreeSegment,MyHwBud>* tree)
      :Bud<MyHwTreeSegment,MyHwBud>(p,d,omega,tree){}
  };

  class MyCfBud:public Bud<MyCfTreeSegment,MyCfBud>{
  public:
    MyCfBud(const Point& p, const PositionVector& d, 
	    const LGMdouble omega, Tree<MyCfTreeSegment,MyCfBud>* tree)
      :Bud<MyCfTreeSegment,MyCfBud>(p,d,omega,tree){}
  };
}//closing namespace Lignum

#endif

