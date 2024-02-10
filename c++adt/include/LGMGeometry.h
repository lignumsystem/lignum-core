#ifndef LGMGEOMETRY_H
#define LGMGEOMETRY_H

#include <Triangle.h>
#include <list>
///\file LGMGeometry.h
///\brief Classes and functions for geometrical calculations in LIGNUM

using namespace std;
namespace cxxadt{

  ///This triangle is as Triangle but it has also attribute normal. Because it is necessary
  ///to know (for example for STL file format ) which way (up or down) normal goes - the direction of normal
  ///thus determines the upper surface of the triangle. Triangle has not this distinction;
  ///it always returns the normal that points towards upper hemisphere (z coordinate >= 0).
  class LGMTriangle : public Triangle {
  public:
    ///If only corners (left, right and apex) are given
    ///Triangle normal = Cross(left-apex,right-apex)
    ///\param leftcorner Left corner of the Triangle
    ///\param rightcorner Right corner of the Triangle
    ///\param apexcorner Apex corner of the triangle
    LGMTriangle(const Point& leftcorner, const Point& rightcorner,
		const Point& apexcorner) : Triangle(leftcorner,rightcorner,apexcorner) {

      PositionVector norm = Cross(PositionVector(leftcorner-apexcorner),
				  PositionVector(rightcorner-apexcorner));
      norm.normalize();
      setNormal(norm);
    }
    ///The Triangle normal is explicitely given
    ///\param lefcorner Left corner of the Triangle
    ///\param rightcorner Right corner of the Triangle
    ///\param apexcorner Apex corner of the triangle
    ///\param no Triangle normal
    LGMTriangle(const Point& leftcorner, const Point& rightcorner,
		const Point& apexcorner, const PositionVector& no) :
    Triangle(leftcorner,rightcorner,apexcorner), normal(no) {}

    ///\retval normal Triangle normal
    PositionVector getNormal() const {return normal;}
    ///Set Triangle normal
    //\param no Triangle normal
    void setNormal(const PositionVector& no) {normal = no; normal.normalize();}

  private:
    PositionVector normal;

  };

  ///LGMTriangularize triangularizes a round frustrum (cylinder if base
  ///and top diameters are equal) - not the end disks. The frustrum is
  ///first approximated as a set of parallellograms. They are then each
  ///divided into two triangles. This function can be used to triangularize tree segments.
  ///\param n_facets Number of facets (parallellograms).
  ///\param begin Base (middle point) of frustrum
  ///\param dir Direction of the frustrum (direction from middle point at base to middlepoint at top)
  ///\param L Height (length) of the frustrum
  ///\param R_begin Radii at the base of the frustrum
  ///\param R_end Radii at the top of the frustrum
  ///\return List of LGMtriangles
  ///\post The end disks are not triangularized \sa LGMTriangularizeCircle
  ///\note No checks for reasonable input are made.
  list<LGMTriangle> LGMTriangularize(const int& n_facets, const Point& begin,
				     const PositionVector& dir, const double& L,
				      const double& R_begin, const double& R_end);

  ///LGMTriangularizeCirce triangularizes a circle, e.g. the end disks of a frustrum or cylinder
  ///\param n_facets Number of facets in the triangularized circle
  ///\param center Center point of the circle
  ///\param normal Normal of the circle
  ///\param R Radius of the circle
  ///\return Lis of LGMTriangles
  ///\note No checks for reasonable input are made.
  ///\sa LGMTriangularize
  list<LGMTriangle> LGMTriangularizeCircle(const int& n_facets, const Point& center,
					   const PositionVector& normal, 
					   const double& R);

}//closing namespace cxxadt

#endif
