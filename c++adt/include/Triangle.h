/// \file Triangle.h
/// \brief 3D Triangle 
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include <utility>
#include <algorithm>
#include <mathsym.h>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <Shape.h>

using namespace std;

namespace cxxadt{
  ///\brief 3D Triangle
  ///
  ///3D Triangle with line-triangle intersection detection
  class Triangle: public Shape{
  public:
    ///\brief Constructor
    ///\param A Leftmost corner
    ///\param B Rightmost corner
    ///\param C Apex corner
    ///\post Triangle normal points to the upper hemisphere
    ///\note The semantics of the corner points define the rotation axis as \f$\vec{\mathrm{AB}}\f$ in Triangle::pitch.
    ///Moreover, when using triangle shaped leaves the attachment point of a petiole
    ///can be for example \f$\|\vec{\mathrm{AB}}\|/2\f$. 
    Triangle(const Point& A, const Point& B, const Point& C);
    ///\brief Copy constructor
    Triangle(const Triangle& t)
      :a(t.a),b(t.b),
      c(t.c){}
    ///\brief Assignment operator
    Triangle& operator=(const Triangle& t);
    ///\return Leftmost corner
    Point  getA() const { return a;};
    ///\return Rightmost corner
    Point  getB() const { return b;};
    ///\return Apex corner
    Point  getC() const { return c;};
    ///\brief Collect triangle points in a vector 
    ///\return Triangle points in a vector
    vector<Point>&  getVertexVector(vector<Point>& points)const;
    ///\brief Set new leftmost corner
    Triangle&   setA(const Point& p){ a=p;return *this;}
    ///\brief Set new rightmost corner
    Triangle&   setB(const Point& p){ b=p;return *this;};
    ///\brief Set new apex corner
    Triangle&   setC(const Point& p){ c=p;return *this;};
    ///\return Triangle area
    double getArea()const;
    ///\brief Maximum height of three coordinate points
    ///\return Maximum Z-value in three coordinate points
    double getMaxZ()const;
    ///\return Triangle center
    Point  getCenterPoint()const;     
    ///\return Triangle normal vector
    virtual PositionVector getNormal()const;
    ///\brief Set new triangle center point
    ///
    ///Set new center point and move triangle corners accoridingly
    ///\param center The new triangle center point
    Triangle&   setCenterPoint(const Point& center);
    ///\brief Set new triangle area
    ///
    ///Set new triangle area with triangle center as the scaling center
    ///\param area The new triangle area
    ///\return The new triangle area
    double setArea(double area);   
    ///\brief Set new triangle area
    ///
    ///Set new triangle area with the Point \p base as the scaling center
    ///\param area The new triangle area
    ///\param base The scaling center
    ///\return new triangle area
    double setArea(double area, const Point& base );
    ///\brief Line-Triangle intersection
    ///
    ///Decide for example if a light beam from point \p o with a direction \p l intersects Triangle.
    ///\pre The observation point \p o is \e not above the tringle
    ///\pre The direction vector \p l is \e not parallel with the triangle plane
    ///\param o The observation point
    ///\param l The direction vector from the observation point
    ///\return True if intersection, False otherwise
    ///
    ///\sa Triangle::intersectShape
    ///\sa Triangle::intersectionPoint
    ///
    ///\note Due to the method chosen in Triangle::insideShape
    ///and inevitable limited floating point accuracy
    ///the intersection point must be strictly inside the triangle.
    ///The intersection point is detected with the cxxadt::EPS18 accuracy.
    ///For the demonstration see the test cases 25,26 and 27 in TriangleExample.cc.
    ///\retval true Intersection
    ///\retval false No intersection
    bool  intersectShape(const Point& o,const PositionVector& l)const;
    ///\brief Line-plane  intersection point
    ///
    ///Triangle defines a plane. Decide the line-plane intersection point
    ///from the point \p o with direction \p l
    ///\pre The intersection point must exists
    ///\param o The observation point
    ///\param l The direction  vector from the observation point towards the plane
    ///\retval std::pair<Point,double> pair.first is the intersection point, pair.second is the distance to the intersection point
    ///\note Negative distance to the intersection point means the intersection point is behind the observation point
    ///\sa intersectShape
    pair<Point,double> intersectionPoint(const Point& o,const PositionVector& l)const;
    ///\brief Determine if a point is inside Triangle
    ///\param p The point
    ///\pre The point \p must be in the plane defined by the Triangle
    ///\retval true The point \p p is inside Triangle
    ///\retval false The point \p p is outtside Triangle
    ///\note A point is inside Triangle if the sum of the angles from the point \p p
    ///      to the three corner points is 360 degrees.
    ///\note The point \p must be strictly inside the Triangle
    bool  insideShape(const Point& p)const;
    ///\brief Rotate triangle 
    ///
    ///Rotate triangle by \p alpha with the triangle base as the rotation axis.
    ///This method can be used to move Triangle shaped leaves up and down.
    ///\param alpha Pitching angle
    ///\note The base of the triangle is defined by vector \f$ \vec{\mathrm{AB}} \f$
    ///and the apex point is \f$\mathrm{C}\f$
    Triangle& pitch(const double alpha);
    ///\brief Add a point to each triangle corner point
    ///\param mov The point to add to each corner point
    Triangle& move(const Point& mov);
    ///\brief Rotate triangle
    ///
    ///Rotate triangle by \p angle around rotation axis defined by \p p0 and and \p dir
    Triangle& rotate(const Point& p0, const PositionVector& dir, RADIAN angle);                                      
  private:
    Point a,b,c;///<Triangle corner points (left corner,right corner,apex corner)
    PositionVector N; ///< Triangle normal 
  };


}//closing cxxadt
#endif
