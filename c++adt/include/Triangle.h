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
    Point getLeftCorner()  { return leftcorner;};
    Point getRightCorner() { return rightcorner;};
    Point getApexCorner()  { return apexcorner;};
    vector<Point>&  getTriangleCorners(vector<Point>& corners);
    void  setLeftCorner(const Point& p){ leftcorner=p;};
    void  setRightCorner(const Point& p){ rightcorner=p;};
    void  setApexCorner(const Point& p){ apexcorner=p;};
    double getArea();               //the triangle area calculation
    Point  getCentroidPoint();     //getting the triangle centroid 
  
    double setArea(double area);   //it defines a new triangle from
                                   // the old one
                                   //using the scaling method with the 
                                   //triangle centroid as the scaling center

    double setArea(double area,       //it defines a new triangle from 
                                      //  the old one 
		   const Point& base );// with the base point as the center

    bool intersectTriangle(const Point& o,//checking the triangle intersection 
                                          // with "a light beam"  
			   const Point& b);//the light beam is the ob vector 
                                           // o - the observer position
                                           // b - the vector beam end
  private:
    Point leftcorner,rightcorner,apexcorner;//the triangle corners
  };


}//closing cxxadt
#endif
