#include <LGMGeometry.h>

//These functions are for geometrical calculations

namespace cxxadt{

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

  list<LGMTriangle> LGMTriangularize(const int& n_facets, const Point& base, const PositionVector& direction, 
					      const double& H,
					      const double& R_base, const double& R_top) {
    PositionVector dir = direction;
    dir.normalize();

    PositionVector u;
    PositionVector up(0.0,0.0,1.0);
    if((dir == up) || ((PositionVector(0.0,0.0,0.0)-dir) == up))
      u = PositionVector(0.0,1.0,0.0);
    else
      u = up;

    PositionVector pointer = Cross(dir,u);
    pointer.normalize();
	
    double r_angle = 2.0*PI_VALUE/(double)n_facets;

    Point top = Point(PositionVector(base) + H * dir) ;

    Point cb_prev = Point(PositionVector(base) + R_base*pointer);
    Point ce_prev = Point(PositionVector(top) + R_top*pointer);
    PositionVector pointer_prev = pointer;
    PositionVector zero(0.0,0.0,0.0);    
    list<LGMTriangle> output;

    for(int i = 0; i < n_facets; i++) {
      pointer.rotate(zero,dir,r_angle);
      pointer.normalize();

      Point cb_next =  Point(PositionVector(base) + R_base*pointer);
      Point ce_next =  Point(PositionVector(top) + R_top*pointer);
      PositionVector norm = pointer_prev + pointer;
      norm.normalize();
      
      output.push_back(LGMTriangle(cb_prev,cb_next,ce_prev,norm));
      output.push_back(LGMTriangle(cb_next,ce_next,ce_prev,norm));
		       
      cb_prev = cb_next;
      ce_prev = ce_next;
      pointer_prev = pointer;
    }

    return output;

  }

  //This function triangularizes a circle. It follows the convention of LGMTriangularize that
  //triangularizes a round frustrum by defining outside by a normal (it must be input).

  //Input: Number of facets.
  //       Center of the circle
  //       Normal of the circle showing the outside of the 
  //       Radius

  //No checks for reasonable input are made.

  //Output: list of triangles

  list<LGMTriangle> LGMTriangularizeCircle(const int& n_facets, const Point& center, const PositionVector& normal, 
					      const double& R) {
    PositionVector dir = normal;
    dir.normalize();
    PositionVector norm = normal;
    norm.normalize();

    PositionVector u;
    PositionVector up(0.0,0.0,1.0);
    if((dir == up) || ((PositionVector(0.0,0.0,0.0)-dir) == up)) {
      u = PositionVector(0.0,1.0,0.0);
    }
    else {
      u = up;
    }

    PositionVector pointer = Cross(dir,u);
    pointer.normalize();
	
    double r_angle = 2.0*PI_VALUE/(double)n_facets;

    Point c_prev = Point(PositionVector(center) + R*pointer);
    PositionVector pointer_prev = pointer;
    PositionVector zero(0.0,0.0,0.0);    
    list<LGMTriangle> output;

    for(int i = 0; i < n_facets; i++) {
      pointer.rotate(zero,dir,r_angle);
      pointer.normalize();

      Point c_next =  Point(PositionVector(center) + R*pointer);
      output.push_back(LGMTriangle(center, c_prev,c_next,norm));
		       
      c_prev = c_next;
      pointer_prev = pointer;
    }

    return output;

  }

} //closing namespace cxxadt



