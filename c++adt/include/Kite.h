//Kite.h
//----------------------------------
#ifndef KITE_H
#define KITE_H
#include <vector>
#include <algorithm>
#include <mathsym.h>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <Shape.h>

//Note that it is assumed that the four vertex points of a kite are in one plane.
//No check whether this is the case is made.

using namespace std;

namespace cxxadt{

  class Kite: public virtual Shape{
  public:
    Kite(const Point& basecorner, const Point& leftcorner, const Point& rightcorner, 
	     const Point& apexcorner);
    Kite(const Kite& k)
      :Shape(Kite::Shape()),basecorner(k.basecorner),leftcorner(k.leftcorner),rightcorner(k.rightcorner),
      apexcorner(k.apexcorner){}
    Kite& operator=(const Kite& t);
    Point  getLeftCorner() const { return leftcorner;}
    Point  getRightCorner() const { return rightcorner;}
    Point  getApexCorner() const { return apexcorner;}
    Point  getBaseCorner() const { return basecorner;}
    
    vector<Point>&  getVertexVector(vector<Point>& points)const;
    void   setLeftCorner(const Point& p){ leftcorner=p;}
    void   setRightCorner(const Point& p){ rightcorner=p;}
    void   setApexCorner(const Point& p){ apexcorner=p;}
    void   setBaseCorner(const Point& p){ basecorner=p;}

    double getArea()const;               //the kite area calculation
    Point  getCenterPoint()const;     //getting the kite center
    //getting the kite normal vector
    PositionVector getNormal()const;
    //    bool   intersectShape(const Point& o,const PositionVector& beam)const;
    void move(const Point& mov);
    //These are for compatibility with stl-lignum Broadleaf
    //Do nothing for the time being
    void   setCenterPoint(const Point& center) {;}
    double setArea(double area) {return area;}
    double setArea(double area, const Point& base ) {return area;}
    void pitch(const double alpha) {;}
    void roll(const double alpha) {;}
    void rotate(const Point& p0, const PositionVector& dir, RADIAN angle) {;}
    void turn(const double alpha) {;}
                                            
  private:
    Point basecorner,leftcorner,rightcorner,apexcorner;//the kite corners
  };


}//closing cxxadt
#endif
