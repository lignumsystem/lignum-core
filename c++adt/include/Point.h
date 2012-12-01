#ifndef POINT_H
#define POINT_H
#include <cmath>
#include <iostream>
#include <PositionVector.h>
/*========================================================================
** Point is a class to represent a single point in 3-D world.
** There are operations to add (+) two points, subtract two points (-),
** count the distance between two points (||) and for the output (<<).
** With the methods it is possible to query coordinates, change the cordinates
** as well as "add and assign" and "subtract and assign" points
*/ 


namespace cxxadt{
  class PositionVector;
    class Point{
      inline friend Point operator + (const Point &point1, 
				      const Point &point2);
      
      inline friend Point operator - (const Point &point1, 
				      const Point &point2);

      inline friend Point operator * (const double scalar, const Point &point);

      inline friend Point operator * (const Point& p, const double scalar);

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







