#ifndef VOXELOBJEXT_H
#define VOXELOBJECT_H
#include <Point.h>
#include <PositionVector.h>
#include <Shading.h>
//Wrapper class for different photosynthesising elements a voxel box
class VoxelObject{
public: 
  virtual int getRoute(const Point& p, const PositionVector& dir,
		       LGMdouble& length){/*implement in sub classes*/};
  virtual LGMdouble getExtinction(const Point& p, const PositionVector& dir){};
};

//The conifer element is the segment itself 
template <class TS>
class CfObject:public VoxelObject{
public:
  CfObject(TS& ts);
  virtual int getRoute(const Point& p, const PositionVector& dir,
		       double& length){
    LGMdouble rfol = GetValue(*ts,LGARf);
    LGMdouble rwood = GetValue(*ts,LGAR);
    LGMdouble l = GetValue(*ts,LGAL);
    Point p2 = GetPoint(*ts);
    PositionVector dir2 = GetDirection(*ts);
    return CylinderBeamShading(p,dir,p2,dir2,rfol,rwood,l,length);
  }
  virtual LGMdouble getExtinction(const Point& p, const PositionVector& dir){}
private:
  TS& ts;
};
#endif
