/// \file PositionVector.h
/// \brief Vector in 3D euclidian space.
#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H

#include <mathsym.h>
#include <RMatrix.h>
#include <TMatrix.h>
#include <fstream>

namespace cxxadt{

using namespace std;

class Point;

///\brief 3D vector in euclidian space
class PositionVector{
  ///\brief Dot product
  friend double Dot(const PositionVector& pv1,const PositionVector& pv2);
  ///\brief Cross product
  friend PositionVector Cross(const PositionVector& pv1,const PositionVector& pv2);
  ///\brief Cosine of the angle between two vectors
  ///\pre For both vectors \f$ ||\mathit{pv1}|| > 0\f$ and \f$ ||\mathit{pv2}|| > 0\f$ 
  friend double CosAlpha(const PositionVector& pv1,const PositionVector& pv2);
  ///\brief The angle between two vectors
  ///\pre For both vectors \f$ ||\mathit{pv1}|| > 0 \f$ and \f$ ||\mathit{pv2}|| > 0\f$ 
  friend double Alpha(const PositionVector& pv1,const PositionVector& pv2);
  friend PositionVector operator + (const PositionVector &pv1, const PositionVector &pv2);
  friend PositionVector operator - (const PositionVector &pv1, const PositionVector &pv2);
  friend PositionVector operator * (const double scalar, const PositionVector &pv);
  friend PositionVector operator * (const PositionVector& pv, const double scalar);
  ///\brief Distance between two vectors (end points)
  friend double operator || (const PositionVector &pv1, const PositionVector &pv2);
  friend ostream& operator << (ostream& os, const PositionVector& pv);
  friend istream& operator >> (istream& os, PositionVector& pv);
  ///\brief Compare two vectors, R_EPSILON accuracy
  ///\return *true* if each \f$ (x_1-x_2,y_1-y_2,z_1-z_2) \f$ differ at most R_EPSILON, *false* otherwise
  friend bool operator == (const PositionVector &pv1, const PositionVector &pv2);
public:
  PositionVector();
  PositionVector(const double x, const double y, const double z);
  PositionVector(const PositionVector& pv);
  PositionVector(const vector<double>& v1):v(v1){}
  PositionVector(const Point& p);
  //PositionVector d from two points, d = end - start.
  PositionVector(const Point& start, const Point& end);
  PositionVector& rotate(ROTATION direction, RADIAN angle);
  ///\brief Generic rotation: rotate vector around a point.
  ///\param p0 Rotation around point p0
  ///\param dir Axis of rotation
  ///\param angle Angle (magnitude) of rotation
  ///\note The sign of the *angle* specifies rotation direction
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
  ///\brief Resize to unit vector
  ///\return PositionVector length 1.
  PositionVector& normalize();
  double getX() { return v[0]; }
  double getY() { return v[1]; }
  double getZ() { return v[2]; }
  double getX()const { return v[0]; }
  double getY()const { return v[1]; }
  double getZ()const { return v[2]; }
  double getLength()const{ return sqrt(pow(v[0],2.0)
                          +pow(v[1],2.0)+pow(v[2],2.0)); }
private:
  vector<double> v;
};

}//close namespace cxxadt
#endif

