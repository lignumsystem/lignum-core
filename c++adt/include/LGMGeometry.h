/// \file LGMGeometry.h
/// \brief Geometrical calculations in Lignum.
///
/// Currently triangularization of a tree segment cylinder
#ifndef LGMGEOMETRY_H
#define LGMGEOMETRY_H

#include <Triangle.h>
#include <list>


using namespace std;
namespace cxxadt{
  class LGMTriangle;
  ///\brief Triangularize Lignum tree segment cylinder 
  ///\param n_facets Number of facets on the cylinder surface
  ///\param begin The base point of the cylinder
  ///\param dir Direction of the cylinder
  ///\param L Length of the cylinder
  ///\param R_begin Radius at cylinder base
  ///\param R_end Radius at cylinder end
  ///\param disks Triangularize cylinderend disks
  ///\return List of triangles
  ///\sa cxxadt::LGMTriangularizeCircle
  list<LGMTriangle> LGMTriangularize(const int& n_facets, const Point& begin,
   				     const PositionVector& dir, const double& L,
   				     const double& R_begin, const double& R_end,
				     bool disks=true);
  ///\brief Triangularize circular end disk of a tree segment cylinder
  ///\param n_facets Number facets on the end disk surface
  ///\param center Center point of the circle
  ///\param normal Circle normal vector
  ///\param R Radius of the circle
  ///\return List of triangles
  list<LGMTriangle> LGMTriangularizeCircle(const int& n_facets, const Point& center,
					   const PositionVector& normal, const double& R);
  ///\brief LGMTriangle maintains triangle normal more suitable for computer geometry and graphics.
  //
  ///Somemtimes it is necessary to know which way (up or down) normal goes - the direction of normal
  ///thus determines the upper surface of the triangle. Computer geometry and visualization algorithms
  ///use this distinction. The cxxadt::Triangle has not this differentiation; it always returns the normal
  ///that points towards upper hemisphere (triangle normal z coordinate >= 0). This is useful in
  ///radiation calculations.
  class LGMTriangle : public Triangle {
    ///\brief LGMTriangularize triangularizes a round frustrum, cylinder if base
    ///and top diameters are equal.
    ///
    ///The frustrum is first approximated as a set of parallellograms. They are then each
    ///divided into two triangles. This function can be used to triangularize tree segments.
    ///\param n_facets Number of facets (parallellograms).
    ///\param begin Base (middle point) of frustrum
    ///\param dir Direction of the frustrum (direction from middle point at base to middlepoint at top)
    ///\param L Height (length) of the frustrum
    ///\param R_begin Radii at the base of the frustrum
    ///\param R_end Radii at the top of the frustrum
    ///\param disks Triangulate end disks, default *true* (see the function declaration outside the class)
    ///\return List of LGMTriangle
    ///\attention No checks for reasonable input are made.
    friend list<LGMTriangle> LGMTriangularize(const int& n_facets, const Point& begin,
					      const PositionVector& dir, const double& L,
					      const double& R_begin, const double& R_end,
					      bool disks);

    ///\brief LGMTriangularizeCirce triangularizes a circle
    ///
    ///Trianguate for example the end disks of a frustrum or cylinder
    ///\param n_facets Number of facets in the triangularized circle
    ///\param center Center point of the circle
    ///\param normal Normal of the circle
    ///\param R Radius of the circle
    ///\return List of LGMTriangle
    ///\attention No checks for reasonable input are made.
    ///\sa LGMTriangularize
    friend list<LGMTriangle> LGMTriangularizeCircle(const int& n_facets, const Point& center,
						    const PositionVector& normal, 
						    const double& R);
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
    ///\param leftcorner Left corner of the Triangle
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

  
}//closing namespace cxxadt

#endif
