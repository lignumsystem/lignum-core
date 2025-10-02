/// \file Kite.h
/// \brief Kite leaf shape
#ifndef KITE_H
#define KITE_H
#include <vector>
#include <utility>
#include <algorithm>
#include <mathsym.h>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <Shape.h>
#include <Triangle.h>


using namespace std;

namespace cxxadt{
  ///\brief Kite leaf shape
  ///It is assumed that the four vertex points of a kite are in one plane.
  ///No check whether this is the case is made.
  class Kite: public Shape{
  public:
    ///Constructor
    ///\param basecorner Base of the kite
    ///\param leftcorner Left corner point
    ///\param rightcorner Right corner point
    ///\param apexcorner Apex of the kite
    ///\pre The four corner points are on the same plane
    ///\post Kite normal points to the upper hemisphere
    ///\attention No checks made for precondition
    Kite(const Point& basecorner, const Point& leftcorner, const Point& rightcorner, 
	     const Point& apexcorner);
    Kite(const Kite& k)
      :basecorner(k.basecorner),leftcorner(k.leftcorner),rightcorner(k.rightcorner),
      apexcorner(k.apexcorner){}
    Kite& operator=(const Kite& t);
    Point  getLeftCorner() const { return leftcorner;}
    Point  getRightCorner() const { return rightcorner;}
    Point  getApexCorner() const { return apexcorner;}
    Point  getBaseCorner() const { return basecorner;}
    ///\brief Retrieve corner points
    ///\param points Vector for corner points
    ///\retval points Corner points in counterclockwise order
    ///\note Corner points are returned counter-clockwise for ParaView
    vector<Point>&  getVertexVector(vector<Point>& points)const;
    void   setLeftCorner(const Point& p){ leftcorner=p;}
    void   setRightCorner(const Point& p){ rightcorner=p;}
    void   setApexCorner(const Point& p){ apexcorner=p;}
    void   setBaseCorner(const Point& p){ basecorner=p;}

    double getArea()const;               //the kite area calculation
    Point  getCenterPoint()const;     //getting the kite center
    //getting the kite normal vector
    PositionVector getNormal()const;
    ///\brief Line-Kite intersection
    ///
    ///Decide if a light beam from point \p o with a direction \p l intersects Kite.
    ///\pre The observation point \p o is \e not above the Kite
    ///\pre The direction vector \p l is \e not parallel with the Kite plane
    ///\param o The observation point
    ///\param l The direction vector from the observation point
    ///\retval true Intersection in the direction of the beam \p l
    ///\retval false No intersection
    bool intersectShape(const Point& o,const PositionVector& l)const;
    ///\brief Line-plane  intersection point
    ///
    ///Kite defines a plane. Decide the line-plane intersection point.
    ///from the point \p o with direction \p l
    ///\pre The intersection point must exist
    ///\param o The observation point
    ///\param l The direction  vector from the observation point towards the plane
    ///\retval std::pair<Point,double> pair.first is the intersection point, pair.second is the distance to the intersection point
    ///\note Negative distance to the intersection point means the intersection point is behind the observation point
    ///\sa Tringle::intersectionPoint
    pair<Point,double> intersectionPoint(const Point& o,const PositionVector& l)const;
    //\brief Determine if a point is inside Kite
    ///\param p The point 
    ///\pre The point \p p must be in the plane defined by the Kite
    ///\retval true The point \p p is inside Kite
    ///\retval false The point \p p is outside Kite 
    ///\note A point is inside Kite if the sum of the angles from the point \p p
    ///      to the four corner points is 360 degrees.
    ///\note The point \p p must be strictly inside the Kite
    bool insideShape(const Point& p)const;
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
  protected:
    ///\brief Maximum height of the Kite
    ///\return Maximum Z-coordinate of the four corner points
    double getMaxZ()const;
  private:
    Point basecorner,leftcorner,rightcorner,apexcorner;//the kite corners
  };


}//closing cxxadt
#endif
