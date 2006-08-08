//#include <Volume.h>
#include <CylinderVolume.h>
//#include <math>
#include <cstdlib>
//#include <Point.h>
//#include <PositionVector.h>

CylinderVolume::CylinderVolume(double r, double h, Point p, PositionVector d, int detail) 
  : real_radius(r), height(h), point(p), direction(d) {
  /*rotationDirection = PositionVector(d.normalize().getX()/2, (d.normalize().getY()+1)/2, d.normalize().getZ()/2);
  if(rotationDirection.getX() == 0 &&
     rotationDirection.getY() == 0 &&
     rotationDirection.getZ() == 0)
    rotationDirection = PositionVector(0,1,0);
    origo = Point(0,0,0);*/
  double sine, cosine;
  sine = r*(sin(2.0/(double)detail*3.14159265)) / 2.0;
  cosine = r*(cos(0.0) + cos(2.0/(double)detail*3.14159265)) / 2.0;
  radius = sqrt(sine*sine + cosine*cosine);
  //cout << radius << endl;
  
  plane = ((h*d)+PositionVector(p))-PositionVector(p);
  a = Dot(plane, p);
  c = Dot(plane, plane);
}

CylinderVolume::~CylinderVolume() {

}

int CylinderVolume::isPointInside(Point p) {
  double b = (Dot(plane, p));
  double t = (b-a)/c;
  //double EPSILON = 0.15*radius;
  double EPSILON = 0;
  /*if ((t < -0.000001 ) || (t > 1.000001))
    return -1;
  if(t <= 0.000001 || t > 0.999999)
  return 0;*/
  if ((t < -EPSILON) || (t > 1+EPSILON))
    return -1;
  if(t <= EPSILON || t >= 1-EPSILON)
    return 0;

  PositionVector q(PositionVector(point) + t*plane);
  double distance = (q-PositionVector(p)).length();
  double d = distance-radius;
  if(d >= 0 && d < real_radius-radius) {
    //cout << "d: " << d << endl;
    return 0;
  }
  else if(distance < radius-EPSILON) {
    //cout << "inside!: " << radius-distance << endl;
    //    cout << "abs(radius-distance): " << abs(radius-distance) << endl;
    return 1;
  }
  /*  else if (distance == radius){
    //     cout << "border!" << endl;
    return 0;
    }*/
  else 
    return -1;
}
