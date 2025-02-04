#ifndef RECTANGULARCUBOID_H
#define RECTANGULARCUBOID_H
///\file RectangularCuboid.h
#include <algorithm>
#include <Point.h>
#include <PositionVector.h>

using namespace cxxadt;
///\brief RectangularCuboid is a convex solid that has all right angles
///and equal opposite rectangular faces. It has six faces, eight vertices and twelve edges.
///
///\remark A special case is a rectangle where the height of the ReactanglarCuboid is zero.
///\note The RectangulaCuboid implementation has six precalculated dot products and three perimeter
///vectors needed when calculating if a point is inside ReactanglarCuboid.
class RectangularCuboid{
 public:
  ///\brief Create RectangularCuboid based on two opposite corner points
  ///\param lower_left Lower left corner point, origo
  ///\param upper_right Upper right corner point, diagonally opposite to \lower_left
  ///\post Dot products and vectors used in RectangularCuboid::insideVolume calculated
  RectangularCuboid(const Point& lower_left, const Point& upper_right);
  ///\brief Create RectangularCuboid based on explicit eight corner points (vertices)
  ///\pre The eight vertices are in clockwise order, first the four bottom corner points
  ///then top four corner points.
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
  ///\brief Determine if a point is inside RectangularCuboid including the perimeter line itself.
  ///
  ///The idea is that dot product can be interpreted as a product of two vector lengths: \f$ A \cdot B =  \|A\|\|B\|\cos(\theta) \f$.
  ///The vectors and their dot products (vector lengths) created in the constructors define limits and the perimeter for the point \p.
  ///By checking the point against these constraints can decide whether the point is inside RectangularCuboid or not.
  ///
  ///\remark The easiest way to understand the algorithm is to use RectangularCuboid with the bottom left point \p p0 at (0,0,0)
  ///and follow the required calculations with their graphical interpretation  for x and y directions. 
  ///\param p The point to examine
  ///\return True if the point \p p is inside ReactangularCuboid, False otherwise
  bool insideVolume(const Point& p);
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

#endif
