//#include <Volume.h>
#include <CylinderVolume.h>
//#include <math>
#include <cstdlib>
//#include <Point.h>
//#include <PositionVector.h>

CylinderVolume::CylinderVolume(double r, double h, Point p, PositionVector d) 
  : radius(r), height(h), point(p), direction(d) {
  rotationDirection = PositionVector(d.normalize().getX()/2, (d.normalize().getY()+1)/2, d.normalize().getZ()/2);
  if(rotationDirection.getX() == 0 &&
     rotationDirection.getY() == 0 &&
     rotationDirection.getZ() == 0)
    rotationDirection = PositionVector(0,1,0);
  origo = Point(0,0,0);
}

CylinderVolume::~CylinderVolume() {

}

int CylinderVolume::isPointInside(Point p) {
  p = p - point;
  
  PositionVector v(p.getX(), p.getY(), p.getZ());
  v = v.rotate(origo, rotationDirection, 3.14159265);
  
  if(v.getY() > height || v.getY() < 0)
    return -1;
  
  double distance = sqrt(v.getX()*v.getX() + v.getY()*v.getY());
  if(distance < radius) {
    if(((p.getY() - height) == 0) || (p.getY() == 0))
      return 0;
    else 
      return 1;
  }
  else if (distance == radius)
    return 0;
  else 
    return -1;
  
}
