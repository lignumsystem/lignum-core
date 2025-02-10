#ifndef RECTANGULARCUBOID_H
#define RECTANGULARCUBOID_H
///\file RectangularCuboid.h
#include <algorithm>
#include <Point.h>
#include <PositionVector.h>

namespace cxxadt{
  ///\brief RectangularCuboid implements a convex solid.
  ///
  ///RectangularCuboid is a convex solid that has all right angles
  ///and equal opposite rectangular faces. It has six faces, eight vertices and twelve edges.
  ///\note The RectangulaCuboid constructors precalculate six dot products and three perimeter
  ///vectors needed when calculating if a point is inside ReactanglarCuboid.
  ///\remark A special case of a RectangularCuboid is a rectangle where the height of the ReactanglarCuboid is zero.
  ///\sa RectangularCuboid::insideVolume
  class RectangularCuboid{
  public:
    ///\brief Delegating constructor.
    ///
    ///Create default empty rectangular cuboid
    ///\post Empty RectangularCuboid with \p p0 = (0,0,0) and \p p6 = (0,0,0)
    ///\sa RectangularCuboid::RectangularCuboid(const Point&, const Point&)
    RectangularCuboid():RectangularCuboid(Point(0,0,0),Point(0,0,0)){}
    ///\brief Create RectangularCuboid based on two diagonally opposite corner points
    ///\param lower_left Lower left corner point, origo
    ///\param upper_right Upper right corner point, diagonally opposite to the \p lower_left point
    ///\post The six other vertices calculated to form rectangular cuboid
    ///\post Dot products and vectors used in RectangularCuboid::insideVolume calculated
    RectangularCuboid(const Point& lower_left, const Point& upper_right);
    ///\brief Create RectangularCuboid based on explicit eight corner points (vertices)
    ///\pre The eight vertices are in clockwise order, first the four bottom corner points
    ///followed by the top four corner points.
    ///\param bll Bottom lower left point, origo
    ///\param bul Bottom upper left point
    ///\param bur Bottom upper right point
    ///\param blr Bottom lower right point
    ///\param tll Top lower left point
    ///\param tul Top upper left point
    ///\param tur Top upper right point
    ///\param tlr Top lower right point
    ///\post Dot products and vectors used in RectangularCuboid::insideVolume calculated
    ///\attention It is not (yet) checked if the points form RectangularCuboid
    ///\todo Build a test if the points form a RectangularCuboid 
    RectangularCuboid(const Point& bll,const Point& bul,const Point& bur,const Point& blr,
		      const Point& tll,const Point& tul,const Point& tur,const Point& tlr);
    ///\brief Copy constructor
    RectangularCuboid(const RectangularCuboid& c)
      :p0(c.p0),p1(c.p1),p2(c.p2),p3(c.p3),p4(c.p4),p5(c.p5),p6(c.p6),p7(c.p7),
       u(c.u),v(c.v),w(c.w),u0(c.u0),u1(c.u1),v0(c.v0),v3(c.v3),w0(c.w0),w4(c.w4){}
    ///\brief Assignment operator
    ///\retval this Reference to current instance
    RectangularCuboid& operator=(const RectangularCuboid& c);
    ///\brief Null cuboid
    ///\return True if the cuboid volume is 0, True otherwise 
    bool isVoid()const{return volume() == 0.0;}
    ///\brief Resize RectancularCuboid using lower left and uppper right corner points
    ///\param lower_left Lower left corner point, origo
    ///\param upper_right Upper right corner point, diagonally opposite to the \p lower_left point
    ///\retval this Reference to the current instance 
    ///\post The six other vertices calculated to form rectangular cuboid
    ///\post Dot products and vectors used in RectangularCuboid::insideVolume calculated
    ///\note The same algorithm as the constructor RectangularCuboid(const Point& lower_left, const Point& upper_right);
    ///\sa RectangularCuboid::RectangularCuboid(const Point&, const Point&);
    RectangularCuboid& resize(const Point& lower_left, const Point& upper_right);
    ///\brief Determine if a point is inside RectangularCuboid including the perimeter line itself.
    ///
    ///The idea is that a dot product can be interpreted as a product of two vector lengths: \f$ A \cdot B =  \|A\|\|B\|\cos(\theta) \f$.
    ///The vectors and their dot products (vector lengths) created in the constructors define limits and the perimeter for the point \p p.
    ///By checking the point \p p against these constraints (with the vector projections) can decide whether the point is inside RectangularCuboid or not.
    ///\remark The easiest way to understand the algorithm is to use RectangularCuboid with the bottom left point \p p0 at (0,0,0)
    ///and then following the required calculations for the point \p p with their graphical interpretation as an illustration for  x and y directions. 
    ///\param p The point to examine
    ///\return True if the point \p p is inside ReactangularCuboid, False otherwise
    bool insideVolume(const Point& p)const;
    ///\brief RectangularCuboid volume
    ///\return \f$ (p_0 \parallel p_3) \times (p_0 \parallel p_1) \times (p_0 \parallel p_4) \f$
    double volume()const;
  private:
    Point p0; ///< Bottom lower left, origo
    Point p1; ///< Bottom upper left
    Point p2; ///< Bottom upper right
    Point p3; ///< Bottom lower right
    Point p4; ///< Top lower left
    Point p5; ///< Top upper left
    Point p6; ///< Top upper right
    Point p7; ///< Top lower right
    PositionVector u;///< Vector p0-p1
    PositionVector v;///< Vector p0-p3
    PositionVector w;///< Vector p0-p4
    double u0;///< Dot(u,p0)
    double u1;///< Dot(u,p1)
    double v0;///< Dot(v,p0)
    double v3;///< Dot(v,p3)
    double w0;///< Dot(w,p0)
    double w4;///< Dot(w,p4)
  };
}
#endif
