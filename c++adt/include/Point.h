/// \file Point.h
/// \brief 3D Point class 
#ifndef POINT_H
#define POINT_H
#include <cmath>
#include <iostream>
#include <PositionVector.h>


namespace cxxadt{
  class PositionVector;
  
  ///\brief Point represents a single point in 3D space
  ///
  ///There are algeabric operations such as to add (+) two points, subtract two points (-),
  ///calculate the distance between two points (||) as well as methods to query
  ///and change Point in 3D space.
    class Point{
      inline friend Point operator + (const Point &point1, 
				      const Point &point2);
      
      inline friend Point operator - (const Point &point1, 
				      const Point &point2);

      inline friend Point operator * (const double scalar, const Point &point);

      inline friend Point operator * (const Point& p, const double scalar);
      inline friend Point operator / (const Point& p, const double scalar);
      inline friend Point operator / (const double scalar, const Point& p);

      inline friend double operator || (const Point &point1, const Point &point2);

      inline friend ostream& operator << (ostream& os, const Point& point);

	  inline friend istream& operator >> (istream& os, Point& p);

      inline friend bool operator == (const Point &point1, 
				      const Point &point2);
      inline friend bool operator != (const Point &point1, 
				      const Point &point2);
    public:
      Point(double x1 = 0.0, double y1 = 0.0, double z1 = 0.0)
	{x = x1; y =  y1; z =  z1;}
      inline Point(const Point& point);
      double getX()const{ return x;}
      double getY()const{ return y;}
      double getZ()const{ return z;}
      double getLength()const{ return sqrt(x*x+y*y+z*z); }
      Point& setX(const double new_x){x = new_x; return *this;}
      Point& setY(const double new_y){y = new_y; return *this;}
      Point& setZ(const double new_z){z = new_z; return *this;}
      inline Point& operator = (const Point&point);
      inline Point& operator += (const Point& point); 
      inline Point& operator -= (const Point& point);
      inline Point& operator *= (const double scalar);
      inline operator PositionVector ();
      inline operator PositionVector ()const;
    private:
      double x;
      double y;
      double z;
    };
	  
//make a point from another point
inline Point::Point(const Point& point)
{
  x = point.x;
  y = point.y;
  z = point.z;
}

//compare equality
inline bool operator == (const Point& p1, const Point& p2)
{
  return (p1.x == p2.x) && 
         (p1.y == p2.y) &&
         (p1.z == p2.z);
}

//compare inequality
inline bool operator != (const Point& p1, const Point& p2)
{
  return !(p1 == p2);
}
inline Point::operator PositionVector ()
{
  return PositionVector(x,y,z);
}


inline Point::operator PositionVector ()const
{
  return PositionVector(x,y,z);
}

} //closing namespace cxxadt

#include <PointI.h>

#endif







