#ifndef POINT_H
#define POINT_H
#include <math.h>
#include <iostream.h>
/*========================================================================
** Point is a class to represent a single point in 3-D world.
** There are operations to add (+) two points, subtract two points (-),
** count the distance between two points (||) and for the output (<<).
** With the methods it is possible to query coordinates, change the cordinates
** as well as "add and assign" and "subtract and assign" points
*/ 


namespace cxxadt{
  class PositionVector;
  template <class T = double>
    class Point{
      template <class T1>
      friend Point<T1> operator + (const Point<T1> &point1, 
				   const Point<T1> &point2);
      template <class T1>
      friend Point<T1> operator - (const Point<T1> &point1, 
				   const Point<T1> &point2);

      template <class T1>
      friend Point<T1> operator * (const T1 scalar, const Point<T1> &point);

      template <class T1>
      friend Point<T1> operator * (const Point<T1>& p, const T1 scalar);

      template <class T1>
      friend T1 operator || (const Point<T1> &point1, const Point<T1> &point2);

      template <class T1>
      friend ostream& operator << (ostream& os, const Point<T1>& point);

      template <class T1>
      friend bool operator == (const Point<T1> &point1, 
			       const Point<T1> &point2);
    public:
      Point(T x1 = 0.0, T y1 = 0.0, T z1 = 0.0)
	{x = x1; y =  y1; z =  z1;}
      inline Point(const Point<T>& point);
      T getX()const{ return x;}
      T getY()const{ return y;}
      T getZ()const{ return z;}
      Point<T>& setX(const T new_x){x = new_x; return *this;}
      Point<T>& setY(const T new_y){y = new_y; return *this;}
      Point<T>& setZ(const T new_z){z = new_z; return *this;}
      Point<T>& operator = (const Point<T>&point);
      Point<T>& operator += (const Point<T>& point); 
      Point<T>& operator -= (const Point<T>& point);
      Point<T>& operator *= (const T scalar);
//        operator PositionVector ();
//        operator PositionVector ()const;
    private:
      T x;
      T y;
      T z;
    };
	  
//make a point from another point
template <class T>
inline Point<T>::Point(const Point<T>& point)
{
  x = point.x;
  y = point.y;
  z = point.z;
}

//compare equality
template <class T>
inline bool operator == (const Point<T>& p1, const Point<T>& p2)
{
  return (p1.x == p2.x) && 
         (p1.y == p2.y) &&
         (p1.z == p2.z);
}

//  template <class T>
//  inline Point<T>::operator PositionVector ()
//  {
//    return PositionVector(*this);
//  }

//  template <class T>
//  inline Point<T>::operator PositionVector ()const
//  {
//    return PositionVector(*this);
//  }

} //closing namspace cxxadt

#include <PointI.h>

#endif







