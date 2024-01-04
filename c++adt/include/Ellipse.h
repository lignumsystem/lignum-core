//Ellipse.h
//----------
#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <vector>
#include <algorithm>
#include <mathsym.h>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <Shape.h>

using namespace std;

namespace cxxadt{

  class Ellipse: public virtual Shape{
  public:
    Ellipse(const Point& center, const PositionVector& normal, 
	    const double& semimajoraxis,  const double& semiminoraxis);
    Ellipse(const Point& petiole_end,
	    const PositionVector& petiole_dir,
	    const PositionVector& leaf_normal, 
	    const double& semimajoraxis,  const double& semiminoraxis);
    Ellipse(const PositionVector& pd,
	    const PositionVector& n,
	    const PositionVector& x1u, 
	    const double& semimajoraxis0,  
	    const double& semiminoraxis0);
    //Used in XMLTree.h and in LGMPolygonDomBuilder.cpp
    Ellipse(const Point& petiole_end,
	    const PositionVector& leaf_normal, 
	    const PositionVector& xdir,
	    const PositionVector& ydir,
	    const double& semimajoraxis,  
	    const double& semiminoraxis);
    Ellipse(const Ellipse& e);
    Ellipse& operator=(const Ellipse& e);
    const Point&  getCenterPoint() const { return center;};
    const PositionVector& getNormal()const { return normal;};
    double getSemimajorAxis()const{ return semimajoraxis;};
    Point  getSemimajorAxisPoint()const;
    double getSemiminorAxis()const{return semiminoraxis;};
    Point  getSemiminorAxisPoint()const;
    void   setCenterPoint(const Point& center0){center=center0;};
    void   setSemimajorAxis( const double& semimajoraxis0)
                 {semimajoraxis=semimajoraxis0;}
    void   setSemiminorAxis( const double& semiminoraxis0)
                 {semiminoraxis=semiminoraxis0;};
                                      
                                  //the ellipse area calculation
    double getArea()const{return semimajoraxis*semiminoraxis*PI_VALUE;}; 


                                 //getting the ellipse as 'n' points 
    vector<Point>&  getVertexVector(vector<Point>& points, int n=50)const;

                                   //it defines a new ellipse from
                                   // the old one
                                   //using the scaling method with the 
                                   //ellipse center point as the scaling center
    inline double setArea(double area);
                                 
                                   //it defines a new triangle from 
                                   //  the old one 
                                   // with the base point as the center
    double setArea(double area,       
		   const Point& base );
                                   
                                     //checking the ellipse intersection 
                                     // with "a light beam"
                                     //the light beam is the ob vector 
                                     // o - the observer position
                                     // b - the vector beam
    bool intersectShape(const Point& o,
 		   const PositionVector& beam)const;
    
					   				       
    PositionVector x1u()const; //unit vector x-axis in the ellipse plane

    PositionVector y1u()const;     //unit vector y-axis in the ellipse plane
 
    //Rotate ellipse around major axis by angle angle
    void roll(const double& angle);

    //Rotate ellipse around minor axis by angle angle
    //Axis of rotation is at end of petiole (at intersection of perimeter and major axis)
    void pitch(const double& angle);

    //Rotate ellipse around normal by angle angle
    //Axis of rotation is at end of petiole (at intersection of perimeter and major axis)
    void turn(const double& angle);

    void move(const Point& mov) {
      center = center + mov;
    }


  private:
    Point center;
    PositionVector normal;
    PositionVector xdir;
    PositionVector ydir;
    double semimajoraxis;
    double semiminoraxis;
  };

  //This case  with the ellipse center as the scaling center 
  inline double Ellipse::setArea(double area){

   double areaold, areanew,
         scalcoef; 
   double adbasex, adbasey, adbasez;
  
   areaold=getArea();
   areanew=area; 

   scalcoef=sqrt(areanew/areaold);

   adbasex=getCenterPoint().getX()*(1-scalcoef);
   adbasey=getCenterPoint().getY()*(1-scalcoef);
   adbasez=getCenterPoint().getZ()*(1-scalcoef);

   vector<Point> points;
   points.push_back(getSemimajorAxisPoint());
   points.push_back(getSemiminorAxisPoint());
   Point x,p;

   for(int i=0; i< static_cast<int>(points.size()); i++){
    p=(Point)points[i];
    x.setX(p.getX() *scalcoef  + adbasex);
    x.setY(p.getY() *scalcoef  + adbasey);
    x.setZ(p.getZ() *scalcoef  + adbasez);
    switch(i){
     case 0:
      setSemimajorAxis(getCenterPoint() || x);
      break;
     case 1:
      setSemiminorAxis(getCenterPoint() || x);
      break;
    };
   };

   return getArea();
  }

}//closing cxxadt
#endif



