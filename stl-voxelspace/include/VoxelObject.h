#ifndef VOXELOBJEXT_H
#define VOXELOBJECT_H
#include <Point.h>
#include <PositionVector.h>
#include <Shading.h>
//Wrapper class for different photosynthesising elements a voxel box
class VoxelObject{
public: 
  virtual int getRoute(const Point& p, const PositionVector& dir,
		       LGMdouble& length)const=0;
  virtual LGMdouble getExtinction(const Point& p, const PositionVector& dir,
				  const ParametricCurve& K)const=0;
};

//The conifer element is the segment itself 
template <class TS>
class CfObject:public VoxelObject{
public:
  CfObject(const CfObject& cfo):ts(cfo.ts){}
  CfObject(const TS& segment):ts(segment){}
  virtual int getRoute(const Point& p, const PositionVector& dir,
		       double& length)const{
    LGMdouble rfol = GetValue(ts,LGARf);
    LGMdouble rwood = GetValue(ts,LGAR);
    LGMdouble l = GetValue(ts,LGAL);
    Point p2 = GetPoint(ts);
    PositionVector dir2 = GetDirection(ts);
    return CylinderBeamShading(p,dir,p2,dir2,rfol,rwood,l,length);
  }

  virtual LGMdouble getExtinction(const Point& p,const PositionVector& dir,
				  const ParametricCurve& K)const{
    LGMdouble af = GetValue(ts,LGAAf);
    LGMdouble vf = GetValue(ts,LGAVf);
    LGMdouble a_dot_b = Dot(GetDirection(ts),dir);
    LGMdouble l = 0.0;
    //Return the path length light beam travels in the shading segment
    int result = this->getRoute(p,dir,l);
    //The angle between the light beam and the segment
    LGMdouble phi = 0.0;
    //Recall the K function has domain [0:pi/2]. We must use the acute
    //angle
    if (a_dot_b < 0.0)//obtuse angle-->take the acute angle
      phi = PI_VALUE - acos(a_dot_b);
    else
      phi = acos(a_dot_b);
 
    double tau = 1.0;//clear sky
    if (result == 0) //Not hit
      tau = 1.0;//clear sky so far
    else if (result == -1)//Wood
      tau = 0.0;//sector blocked
    else{//The equation from EcoMod 98
      if (vf > R_EPSILON)
	tau = exp(-K(phi)*l*af/vf);
      else
	cerr << "Vf < R_EPSILON " << vf << " Af: " << af << endl;
    }
    return tau;
  }
  
private:
  const TS& ts;
};
#endif
