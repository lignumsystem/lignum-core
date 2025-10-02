/// \file VoxelObject.h
/// \brief Geometric representation for coniferous segments and broad leafleaves.
///
///Represent coniferous and broad leaf tree species photosynthesising elements
///uniformly as geometric objects with VoxelObject. There must be enough geometric data
///to calculate object - light beam intersections and radiation attenuation.
#ifndef VOXELOBJECT_H
#define VOXELOBJECT_H
#include <vector>
#include <Point.h>
#include <PositionVector.h>
#include <Shading.h>

namespace voxelspace{
///\brief Base class for different photosynthesising elements a voxel box.
///
///Provides uniform representation to calculate radiation interception.
///\sa CfCylinder HwEllipse
class VoxelObject{
public: 
  VoxelObject(const VoxelObject& vo):tag(vo.tag){}
  VoxelObject(long_size t):hit_self(false),tag(t){}
  virtual ~VoxelObject(){}
  virtual int getRoute(const Point& p, const PositionVector& dir,
		       LGMdouble& length)const=0;
  virtual LGMdouble getExtinction(const Point& p, const PositionVector& dir,
				  const ParametricCurve& K)const=0;
  virtual long_size getTag()const{return tag;}
  mutable bool hit_self;///<debug: true if segment compares itself 
private:
  ////A  unique tag for the voxel object.  If two  objects denote  the same
  ///element (segment, leaf), they have the same tag
  long_size tag;
};


///Cylindrical coniferous shading element
class CfCylinder:public VoxelObject{
public:
  CfCylinder(const CfCylinder& cfobj)
    :VoxelObject(cfobj.getTag()),p0(cfobj.p0),p2(cfobj.p2),
     d(cfobj.d),l(cfobj.l),rw(cfobj.rw),rf(cfobj.rf),
     af(cfobj.af),vf(cfobj.vf),sp(cfobj.sp){}
  CfCylinder(const Point&p, const PositionVector& dir,double length, double rwood, 
	     double rfol, double folarea, double folvol, double beam_start,int tag)
    :VoxelObject(tag),p0(p),d(dir),l(length),rw(rwood),rf(rfol),
     af(folarea),vf(folvol),sp(beam_start)
  {
    PositionVector tmp = PositionVector(p0)+sp*l*d;//Possibly the start point of the light beam    
    p2 = Point(tmp);
  }
  ///Calculate the path length light beam travels in the shading segment
  ///\param p Start point of the light beam
  ///\param dir Direction of the light beam
  ///\param [out] length Length light beam travels in shading foliage
  ///\return 0 (HIT), -1 (HIT_THE_WOOD), +1 (HIT_THE_FOLIAGE) 
  virtual int getRoute(const Point& p, const PositionVector& dir,
		       double& length)const
  {
    hit_self = false;
    if (fabs(p||p2) < R_EPSILON){//Check if start point of the light beam
      hit_self = true;
      //The light beam starts from the shading segment
      //cout << p << dir << endl << p0 << d << endl << p2 << " " << sp << " " << l << endl<< endl; 
      return 0;
    } 
    if(af < R_EPSILON) {
      return CylinderBeamShading(p,dir,p0,d,rw,l);
    } else {
      return CylinderBeamShading(p,dir,p0,d,rf,l,length);
    }
  }

  ///Radiation extinction for the length light beam travels in shading foliage
  ///\param p Starting point of the light beam
  ///\param dir direction of the light beam
  ///\param K The extinction function \f$K(\phi)\f$ where \f$\phi\f$ is the angle between light beam and shaded segment
  ///\retval tau  Radiation extinction  
  virtual LGMdouble getExtinction(const Point& p,const PositionVector& dir,
				  const ParametricCurve& K)const{
    LGMdouble length = 0.0;//path length 
    LGMdouble tau = 1.0;//clear sky
    
    //Return the path length light beam travels in the shading segment
    int result = this->getRoute(p,dir,length);
    //Check the two extreme cases
    if (result == 0){ //Not hit
      tau = 1.0;//clear sky so far
      //Debug misses
      //cout << tau << " " << p0.getX() << " "  << p0.getY() << " " << p0.getZ() << " "
      //     << d.getX() << " " << d.getY() << " " << d.getZ() << " "
      //     << p.getX() << " " << p.getY() << " " << p.getZ() << " " 
      //     << dir.getX() << " "  << dir.getY() << " "  << dir.getZ() << " " 
      //     << l << " " << rw << " " << rf << " " << rf-rw << endl;
      return tau;
    }
    else if (result == -1){//Wood hit
      tau = 0.0;//sector blocked
      return tau;
    }

    //The angle between the light beam and the segment
    LGMdouble a_dot_b = Dot(d,dir);
    LGMdouble phi = 0.0;

    phi = PI_DIV_2 - acos(fabs(a_dot_b));
    
    tau = exp(-K(phi)*length*af/vf);

    return tau;
  }
private:
  Point p0;///<Start point of the cylinder
  Point p2;///<p0+sp*l*Point(d), point that could be the start point of the light beam
  PositionVector d;///<direction of the cylinder
  double l;///<Length of the cylinder
  double rw;///<Wood radius
  double rf;///<Foliage radius
  double af;///<Foliage area
  double vf;///<Foliage volume
  double sp;///<start point [0:1] of the light beam (e.g. 0.5 is the mid
	    ///<point of the segment)
};

class HwEllipse: public VoxelObject{
public:
  HwEllipse(const Ellipse& e1, double dof1, double tauL1, int tag1, BroadLeaf<Ellipse>* leaf1)
    :VoxelObject(tag1),e(e1),dof(dof1),tauL(tauL1),leaf(leaf1){}
  HwEllipse(const HwEllipse& hwe)
    :VoxelObject(hwe.getTag()),e(hwe.e),dof(hwe.dof),tauL(hwe.tauL),leaf(hwe.leaf){}
  //Check if the beam hits the ellipse
  //p: start point of the beam
  //d: direction of the light beam
  //length: returns the length light beam travels in foliage
  //getRoute is virtual and for hardwood species 'length' is set to zero
  int getRoute(const Point& p, const PositionVector& d,double& length)const
  {
    length = 0.0;
    //Use the geometric information
    Ellipse ellipse(e);
    //Use the leaf itself
    if (leaf){
      ellipse = GetShape(*leaf);
    }
    //Check for self hit    
    if (fabs(ellipse.getCenterPoint() || p) < R_EPSILON){
      hit_self = true;
      return 0;//self hit
    }
    else if (ellipse.intersectShape(p,d)){
      return 1;//hit
    }
    else{
      return 0;//no hit
    }
  }
  //Calculate the extinction for this  leaf 
  //p: start point of the beam
  //d:  direction  of  the  light  beam 
  //K:  Extinction  for conifers,  getExtinction  is  virtual and  for
  //hardwood species K is not used
  LGMdouble getExtinction(const Point& p, const PositionVector& d,
			  const ParametricCurve& K)const
  {
    K(0.0);
    double vp = 1.0;//clear sector
    double length = 0.0;
    int result = getRoute(p,d,length);
    if (result == 1){
      vp = 1.0-dof+dof*tauL;//extinction if hit
    }
    return vp;
  }
private:
  Ellipse e;//Leaf ellipse
  double dof;//Degree of filling of the leaf shape model
  double tauL;//Extinction coefficient if beam hits the leaf shape
  BroadLeaf<Ellipse>* leaf;//the leaf itself
};
}//end namespace voxelspace
#endif
