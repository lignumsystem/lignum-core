#ifndef ELLIPSIS_H
#define ELLIPSIS_H

#include <math.h>
#include <mathsym.h>

class Ellipsis{
public:
  Ellipsis(double a, double b);
  double getArea()const{return PI_VALUE*a*b;}
  double getFocus()const;
  double getSemimajorAxis()const{return a;}
  double getSemiminorAxis()const{return b;}
  double setArea(double area);
  double setMajor(double a);
  double setMinor(double b);
private:
  double a;  //Semimajor axis
  double b;  //Semiminor axis
};

#endif
