//Ellipse.h
//----------
#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <vector>
#include <algorithm>
#include <math.h>
#include <mathsym.h>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>

using namespace std;

namespace cxxadt{

  class Ellipse{
  public:
    Ellipse(const Point& center, const PositionVector& normal, 
	     const double& semimajoraxis,  const double& semiminoraxis);
    Ellipse(const PositionVector& petiole0,
             const PositionVector& normal, 
	     const double& semimajoraxis,  const double& semiminoraxis);
    Point  getCenterPoint()  { return center;};
    PositionVector getNormal() { return normal;};
    double getSemimajorAxis(){ return semimajoraxis;};
    Point  getSemimajorAxisPoint();
    double getSemiminorAxis(){return semiminoraxis;};
    Point  getSemiminorAxisPoint();
    void   setCenterPoint(const Point& center0){center=center0;};
    void   setSemimajorAxis( const double& semimajoraxis0)
                 {semimajoraxis=semimajoraxis0;}
    void   setSemiminorAxis( const double& semiminoraxis0)
                 {semiminoraxis=semiminoraxis0;} ;
                                       //the ellipse area calculation
    double getArea(){return semimajoraxis*semiminoraxis*PI_VALUE;}; 

    double setArea(double area);   //it defines a new ellipse from
                                   // the old one
                                   //using the scaling method with the 
                                   //ellipse center point as the scaling center

    double setArea(double area,       //it defines a new triangle from 
                                      //  the old one 
		   const Point& base );// with the base point as the center
    
    bool intersectEllipse(const Point& o,//checking the ellipse intersection 
                                          // with "a light beam"  
			   const Point& b);//the light beam is the ob vector 
                                           // o - the observer position
                                           // b - the vector beam end
    
					   				       
    PositionVector x1u();      //unit vector x-axis in the ellipse plane

    PositionVector y1u();     //unit vector y-axis in the ellipse plane

   

  private:
    Point center;
    PositionVector normal;
    double semimajoraxis;
    double semiminoraxis;
  };


}//closing cxxadt
#endif



