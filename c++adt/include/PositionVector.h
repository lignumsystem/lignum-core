#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H

#include <math.h>
#include <mathsym.h>
#include <vector>
#include <RMatrix.h>

using namespace std;

class PositionVector{
public:
  PositionVector();
  PositionVector(const double x, const double y, const double z);
  PositionVector(const PositionVector& pv);
  PositionVector(const vector<double>& v1):v(v1){}
  PositionVector& rotate(ROTATION direction, RADIAN angle);
  PositionVector& operator = (const PositionVector& pv);
  double length()const;
  double alpha()const;
  double beta()const;
  double gamma()const;
  vector<double> getVector()const{return v;}
  PositionVector& normalize();
private:
  vector<double> v;
};

#endif
