#ifndef ROOTSYSTEM_H
#define ROOTSYSTEM_H

/*********************************************************************
 *Implementing root system for  LIGNUM. The idea of the implementation
 *is as above ground part of the tree. Root system is represented with
 *a class hierarchy of  RootCompartment (the base class), RootSegment,
 *RootTip,  RootAxis and  RootBranchingPoint. RootSegment  and RootTip
 *will be the main  functioning units, RootBranchingPoint will capture
 *the branching structure of the  root system and RootAxis is the list
 *of  RootCompartments. As  for above  ground part  generic algorithms
 *will be provided  to traverse the root system  and apply functors to
 *root compartments.  Also an  L-system implementation will follow for
 *modeling the dynamics of architectural development of the rot system
 *********************************************************************/

#include <LGMSymbols.h>
#include <LGMUnits.h>
#include <Point.h>
#include <PositionVector.h>
#include <list>
using namespace cxxadt;
using namespace std;
namespace Lignum {

  class RootCompartment{
    friend Point GetPoint(const RootCompartment& rc){return rc.p;}
    friend PositionVector GetDirection(const RootCompartment& rc){return rc.d;}
    void friend SetPoint(RootCompartment& rc,const Point& pos){rc.p = pos;}
    void friend SetDirection(RootCompartment& rc,
			     const PositionVector& dir){rc.d = dir;}
  public:
    RootCompartment(const Point& pos, const PositionVector& dir):
      p(pos),d(dir) {}
  protected:
    Point p;
    PositionVector d;
  };

  class RootAxis:public RootCompartment{
  public:
    RootAxis(const Point& pos, const PositionVector& dir):
      RootCompartment(pos,dir){}
  private:
    list<RootCompartment*> rc_ls; //list of root compartments
  };

  class RootBranchingPoint:public RootCompartment{
  public:
    RootBranchingPoint(const Point& pos, const PositionVector& dir):
      RootCompartment(pos,dir){}
  private:
    list<RootAxis*> ra_ls; //list of root axes
  };


  class RootSegmentAttributes{
  public:
    RootSegmentAttributes(METER Length,METER Radius,METER RTopRadius,
			  METER Rheartwood, METER RhairRadius):
      L(Length),R(Radius),RTop(RTopRadius),Rh(Rheartwood),Rhair(RhairRadius){}
  public:
    METER L;      //Length
    METER R;      //Radius including bark
    METER RTop;   //Radius at top
    METER Rh;     //Heartwood radius
    METER Rhair;  //Radius including root hair
  };

  //RootSegment  is the  main functioning  unit.  As  tree  segment it
  //consists of cylindrical layers  of heartwood and sapwood. The root
  //hair, i.e. fine roots, is  aggregated as the third third cyndrical
  //layer (c.f foliage for CfTreeSegment)
  class RootSegment:public RootCompartment{
    friend LGMdouble GetValue(const RootSegment& rs, LGMAD name);
    friend LGMdouble SetValue(RootSegment& rs, LGMAD name, LGMdouble value);
  public:
    RootSegment(const Point& pos, const PositionVector& dir,
		METER Length,METER Radius,METER RTopRadius,
		METER RheartwoodRadius, METER RhairRadius):
      RootCompartment(pos,dir),rsa(Length,Radius,RTopRadius,
				   RheartwoodRadius,RhairRadius){}
  private:
    RootSegmentAttributes rsa;
  };

  class RootTipAttributes{
  public:
    RootTipAttributes(LGMdouble coll, LGMdouble st, STATUS s):
      collision(coll),state(st),status(s){}
    RootTipAttributes():collision(0),state(0),status(ALIVE){}
  public:
    LGMdouble collision; //collision with another root compartment
    LGMdouble state;     //user defined counter
    STATUS status;       //DEAD or ALIVE (c.f. Bud) 
  };

  class RootTip:public RootCompartment{
    friend LGMdouble GetValue(const RootTip& rt, LGMAD name);
    friend LGMdouble SetValue(RootTip& rt, LGMAD name, LGMdouble value);
    friend STATUS GetValue(const RootTip& rt, LGMAS name);
    friend STATUS SetValue(RootTip& rt, LGMAS name, STATUS value);
  public:
    RootTip(const Point& pos, const PositionVector& dir,
	    LGMdouble coll, LGMdouble state, STATUS status):
      RootCompartment(pos,dir),rta(coll,state,status){}  
    RootTip(const Point& pos, const PositionVector& dir):
      RootCompartment(pos,dir){}
  private:
    RootTipAttributes rta;
  };

}//close namespace Lignum
#endif
