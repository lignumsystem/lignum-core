#ifndef BSPPOLYGON_H
#define BSPPOLYGON_H

#include <Point.h>
#include <PositionVector.h> 
#include <list>
#include <vector>
#include <QtOpenGL>
#include <SceneObject.h>
#include <CylinderVolume.h>

using namespace std;
using namespace cxxadt;

class SceneObject;
class SceneObjectComponent;

class BSPPolygonSet;

/*class BSPPolygon {
  public :
  BSPPolygon(vector<Point> points, SceneObject* object);
  BSPPolygon(vector<Point> points, vector<Point> texturePoints, SceneObject* object);
   ~BSPPolygon();
  void          split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back) ;
  double        classifyPoint(const Point& point) const;
  bool          infront(const BSPPolygon& polygon) const;
  int           calculateSide(const BSPPolygon& polygon) const;
  void          drawPolygon() const;
  void          setDivider();
  bool          hasBeenDivider() const;
  int           getObjectId() const;
  SceneObject*  getSceneObject() const;
  vector<Point> getVertices()const;
  bool         isTransparent() const;
  //Point        getCenter() const;
  inline friend bool operator < (const BSPPolygon& polygon1, const BSPPolygon& polygon2);

  enum {COINCIDING, BEHIND, INFRONT, SPANNING};
  //static const double EPSILON = 0.0001;
  //  static int last_material;  
private:
  bool beenDivider;
  vector<Point> vertices;
  vector<Point> t_vertices;
  PositionVector normal;
  //BSPPolygonMaterial* material;
  SceneObject* object;
  double distance;

};*/


class BSPPolygon {
public :
  BSPPolygon(Point p1, Point p2, Point p3, SceneObject* object);
  BSPPolygon(Point p1, Point p2, Point p3, Point tp1, Point tp2, Point tp3, SceneObject* object);
   ~BSPPolygon();
  void         split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back) ;
  double       classifyPoint(const Point& point) const;
  bool         infront(const BSPPolygon& polygon) const;
  int          calculateSide(const BSPPolygon& polygon) const;
  void         drawPolygon() const;
  void         setDivider();
  bool         hasBeenDivider() const;
  int          getObjectId() const;
  SceneObject* getSceneObject() const;
  vector<Point> getVertices() const;
  bool         isTransparent() const;
  //  Point        getCenter() const;
  inline friend bool operator < (const BSPPolygon& polygon1, const BSPPolygon& polygon2);

  enum {COINCIDING, BEHIND, INFRONT, SPANNING};
  //static const double EPSILON = 0.0001;
  //  static int last_material;  
private:
  bool beenDivider;
  Point p1, p2, p3;
  Point tp1, tp2, tp3;
  PositionVector normal;
  //BSPPolygonMaterial* material;
  SceneObject* object;
  double distance;

  };



class BSPPolygonSet {
public:
  BSPPolygonSet() { }
  ~BSPPolygonSet();
  bool               isConvexSet() const;
  void               addPolygon(BSPPolygon *polygon);
  void               addPolygons(BSPPolygonSet *polys);
  BSPPolygon*        getPolygon();
  BSPPolygon*        chooseDivider();
  bool               isEmpty() const;
  void               drawPolygons() ;
  //  void applyMaterial(BSPPolygonMaterial* mat);
  int                size() const;
  int                componentCount() const;
  void               sort();
  list<BSPPolygon*>& getPolygons();
  void               removeHiddenPolygons(list<CylinderVolume>* cylinders);
  void               getOpaquePolygons(BSPPolygonSet* polys);
  
  //static const int infinity = 1000000000;
  //static const double MINIMUMRELATION = 0.3;
  //static const double MINRELATIONSCALE = 2;
  
 private:
  list<BSPPolygon*>  polygons;
  list<SceneObjectComponent*> components;

  static const int infinity = 1000000000;
  static const double MINIMUMRELATION = 0.3;
  static const double MINRELATIONSCALE = 2;
};
  
//int BSPPolygonSet::infinity = 1000000000;
//double BSPPolygonSet::MINIMUMRELATION = 0.3;
//double BSPPolygonSet::MINRELATIONSCALE = 2;

#endif
