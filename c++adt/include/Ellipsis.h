#ifndef ELLIPSIS_H
#define ELLIPSIS_H

#include <math.h>
#include <mathsym.h>

namespace cxxadt{




class Ellipsis{
public:
  Ellipsis(double a, double b);
  double getArea()const{return PI_VALUE*a*b;}
  double getFocus()const;
  double getCenterPoint()const{return getFocus();}
  double getSemimajorAxis()const{return a;}
  double getSemiminorAxis()const{return b;}
  double setArea(double area);
  double setMajor(double a);
  double setMinor(double b);
 private:
  double a;  //Semimajor axis
  double b;  //Semiminor axis
  double b_div_a; //stores the shape of the ellipsis even if area = 0
  //b_div_a should not be == 0
};

}//closing cxxadt
#endif
