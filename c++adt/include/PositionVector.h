#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H

#include <math.h>
#include <mathsym.h>
#include <vector>
#include <Point.h>
#include <RMatrix.h>

namespace cxxadt{

using namespace std;

class PositionVector{
  friend double Dot(const PositionVector& pv1,const PositionVector& pv2);
  friend PositionVector Cross(const PositionVector& pv1,const PositionVector& pv2);
  friend PositionVector operator + (const PositionVector &pv1, const PositionVector &pv2);
  friend PositionVector operator - (const PositionVector &pv1, const PositionVector &pv2);
  friend PositionVector operator * (const double scalar, const PositionVector &pv);
  friend PositionVector operator * (const PositionVector& pv, const double scalar);
  friend double operator || (const PositionVector &pv1, const PositionVector &pv2);
  //  friend T operator && (const PositionVector &pv1, const PositionVector &pv2);
  friend ostream& operator << (ostream& os, const PositionVector& pv);
  friend bool operator == (const PositionVector &pv1, const PositionVector &pv2);
public:
  PositionVector();
  PositionVector(const double x, const double y, const double z);
  PositionVector(const PositionVector& pv);
  PositionVector(const vector<double>& v1):v(v1){}
  PositionVector(const Point<>& p);
  PositionVector& rotate(ROTATION direction, RADIAN angle);
  PositionVector& operator = (const PositionVector& pv);
  PositionVector& operator += (const PositionVector& point); 
  PositionVector& operator -= (const PositionVector& point);
  PositionVector& operator *= (const double scalar);
  double length()const;
  double alpha()const;
  double beta()const;
  double gamma()const;
  vector<double> getVector()const{return v;}
  PositionVector& normalize();
private:
  vector<double> v;
};

}//close namespace cxxadt
#endif

