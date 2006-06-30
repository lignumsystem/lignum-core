#ifndef BSPPOLYGON_H
#define BSPPOLYGON_H

#include <Point.h>
#include <PositionVector.h> 
#include <list>

using namespace std;
using namespace cxxadt;
class BSPPolygonSet;

class BSPPolygon {
public :
  BSPPolygon(Point p1, Point p2, Point p3, PositionVector *normal);
   
  void split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back);
  double classifyPoint(Point& point);
  bool infront(BSPPolygon polygon);
  int calculateSide(BSPPolygon polygon);
  void drawPolygon();
  void setDivisor();
  
  enum {COINCIDING, BEHIND, INFRONT, SPANNING};
private:
  bool hasBeenDivider;
  Point p1, p2, p3;
  PositionVector *normal;
  double distance;
  static const double EPSILON = 0.0005;
};

class BSPPolygonSet {
public:
  BSPPolygonSet():
  dlist_initialized(false){}
  bool isConvexSet();
  void addPolygon(BSPPolygon *polygon);
  void addPolygons(BSPPolygonSet *polys);
  BSPPolygon* getPolygon();
  BSPPolygon* chooseDivider();
  bool isEmpty();
  void drawPolygons();
  int size();
  
private:
  list<BSPPolygon*> polygons;
  int dlist;
  bool dlist_initialized;
  static const double INFINITY = 1000000000;
  static const double MINIMUMRELATION = 1;
  static const double MINRELATIONSCALE = 2;
};
  
#endif
