#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H

//#include <iostream>
#include <math.h>
#include <mathsym.h>
//#include <vector>
//#include <Point.h>
#include <RMatrix.h>
#include <TMatrix.h>
#include <fstream>

namespace cxxadt{

using namespace std;

class Point;

class PositionVector{
  friend double Dot(const PositionVector& pv1,const PositionVector& pv2);
  friend PositionVector Cross(const PositionVector& pv1,const PositionVector& pv2);
  friend PositionVector operator + (const PositionVector &pv1, const PositionVector &pv2);
  friend PositionVector operator - (const PositionVector &pv1, const PositionVector &pv2);
  friend PositionVector operator * (const double scalar, const PositionVector &pv);
  friend PositionVector operator * (const PositionVector& pv, const double scalar);
  friend double operator || (const PositionVector &pv1, const PositionVector &pv2);
  friend ostream& operator << (ostream& os, const PositionVector& pv);
  friend istream& operator >> (istream& os, PositionVector& pv);
  friend bool operator == (const PositionVector &pv1, const PositionVector &pv2);
public:
  PositionVector();
  PositionVector(const double x, const double y, const double z);
  PositionVector(const PositionVector& pv);
  PositionVector(const vector<double>& v1):v(v1){}
  PositionVector(const Point& p);
  PositionVector& rotate(ROTATION direction, RADIAN angle);
  PositionVector& rotate(const Point& p0, const PositionVector& dir,
			 RADIAN angle);
  PositionVector& rotate(const Point& begin, const Point& end,
			 RADIAN angle);
  PositionVector& operator = (const PositionVector& pv);
  PositionVector& operator += (const PositionVector& point); 
  PositionVector& operator -= (const PositionVector& point);
  PositionVector& operator *= (const double scalar);
  operator Point ();
  operator Point () const;
  double length()const;
  double alpha()const;
  double beta()const;
  double gamma()const;
  vector<double> getVector()const{return v;}
  PositionVector& normalize();
  double getX() { return v[0]; }
  double getY() { return v[1]; }
  double getZ() { return v[2]; }
  double getX()const { return v[0]; }
  double getY()const { return v[1]; }
  double getZ()const { return v[2]; }
private:
  vector<double> v;
};

}//close namespace cxxadt
#endif

