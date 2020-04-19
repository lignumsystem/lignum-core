#ifndef LGMGEOMETRY_H
#define LGMGEOMETRY_H

#include <Triangle.h>
#include <list>

//These functions are for geometrical calculations in LIGNUM

using namespace std;
namespace cxxadt{

  //This triangle is as Triangle but it has also attribute normal. Because it is necessary
  //to know (for example for STL) which way (up or down) normal goes - the direction of normal
  // thus determines the upper surface of the triangle. Triangle has not this distinction
  //it always returns the normal that points towards upper hemisphere (z coordinate >= 0).
  class LGMTriangle : public Triangle {
  public:
    //If only coners normal goes either way (up or down)
    LGMTriangle(const Point& leftcorner, const Point& rightcorner,
		const Point& apexcorner) : Triangle(leftcorner,rightcorner,apexcorner) {

      PositionVector norm = Cross(PositionVector(leftcorner-apexcorner),
				  PositionVector(rightcorner-apexcorner));
      norm.normalize();
      setNormal(norm);
    }
    LGMTriangle(const Point& leftcorner, const Point& rightcorner,
		const Point& apexcorner, const PositionVector& no) :
    Triangle(leftcorner,rightcorner,apexcorner), normal(no) {}


    PositionVector getNormal() const {return normal;}
    void setNormal(const PositionVector& no) {normal = no; normal.normalize();}

  private:
    PositionVector normal;

  };

  //This function triangularizes a round frustrum (cylinder if base
  //and top diameters are equal) - not the end disks. The frustrum is
  //first approximated as a set of parallellograms. They are then each
  //divided into two triangles.

  //Input: Number of facets (parallellograms).
  //       Base (middle point) of frustrum
  //       Direction of the frustrum (direction from middle point at base to middlepoint at top)
  //       Height of frustrum
  //       Radii at base and in the top

  //No checks for reasonable input are made.
  //Output: list of triangles
  list<LGMTriangle> LGMTriangularize(const int& n_facets, const Point& begin,
				     const PositionVector& dir, const double& L,
				      const double& R_begin, const double& R_end);


  list<LGMTriangle> LGMTriangularizeCircle(const int& n_facets, const Point& center,
					   const PositionVector& normal, 
					   const double& R);

}//closing namespace cxxadt

#endif
