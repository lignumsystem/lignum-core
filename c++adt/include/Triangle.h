//Triangle.h
//----------------------------------
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include <algorithm>
#include <math.h>
#include <mathsym.h>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>

using namespace std;

namespace cxxadt{

  class Triangle{
  public:
    Triangle(const Point& leftcorner, const Point& rightcorner, 
	     const Point& apexcorner);
    Triangle(const Triangle& t)
      :leftcorner(t.leftcorner),rightcorner(t.rightcorner),
      apexcorner(t.apexcorner){}
    Triangle& operator=(const Triangle& t);
    Point  getLeftCorner()  { return leftcorner;};
    Point  getRightCorner() { return rightcorner;};
    Point  getApexCorner()  { return apexcorner;};
    PositionVector getNormal()const;
    vector<Point>&  getTriangleCorners(vector<Point>& corners)const;
    void   setLeftCorner(const Point& p){ leftcorner=p;};
    void   setRightCorner(const Point& p){ rightcorner=p;};
    void   setApexCorner(const Point& p){ apexcorner=p;};
    double getArea()const;               //the triangle area calculation
    Point  getCenterPoint()const;     //getting the triangle center 

                                 //getting the triangle normal vector
    PositionVector getNormal()const;
                                 //set up the triangle center point
                                 //end change the triangle corners
                                 //according the center point 
    void   setCenterPoint(const Point& center);
  
    double setArea(double area);   //it defines a new triangle from
                                   // the old one
                                   //using the scaling method with the 
                                   //triangle centroid as the scaling center

                                   //it defines a new triangle from 
                                   //  the old one 
                                   // with the base point as the center
    double setArea(double area, const Point& base );

                                   //checking the triangle intersection 
                                   // with "a light beam" 
                                   //the light beam is the ob vector 
                                   // o - the observer position
                                   // b - the vector beam 
    bool   intersectShape(const Point& o,const PositionVector& beam); 
                                            
  private:
    Point leftcorner,rightcorner,apexcorner;//the triangle corners
  };


}//closing cxxadt
#endif
