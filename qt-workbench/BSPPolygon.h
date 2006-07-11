#ifndef BSPPOLYGON_H
#define BSPPOLYGON_H

#include <Point.h>
#include <PositionVector.h> 
#include <list>
#include <QtOpenGL>
#include <SceneObject.h>

using namespace std;
using namespace cxxadt;

class SceneObject;
class SceneObjectComponent;

class BSPPolygonSet;

/*class BSPPolygonMaterial {
public :
  BSPPolygonMaterial(GLfloat* materials);
  inline void setMaterial();
  inline int getId();
  static int n_materials;
private : 
  GLfloat diffuse[4];
  GLfloat ambient[4];
  GLfloat specular[4];
  GLfloat shine[1];
  int id;
  };*/
  
  
class BSPPolygon {
public :
  BSPPolygon(Point p1, Point p2, Point p3, SceneObject* object);
  BSPPolygon(Point p1, Point p2, Point p3, Point tp1, Point tp2, Point tp3, SceneObject* object);
  ~BSPPolygon();
  void         split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back);
  double       classifyPoint(Point& point);
  bool         infront(BSPPolygon polygon);
  int          calculateSide(BSPPolygon polygon);
  inline void  drawPolygon();
  void         setDivider();
  bool         hasBeenDivider();
  int          getObjectId();
  SceneObject* getSceneObject();
  
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
  bool isConvexSet();
  void addPolygon(BSPPolygon *polygon);
  void addPolygons(BSPPolygonSet *polys);
  BSPPolygon* getPolygon();
  BSPPolygon* chooseDivider();
  bool isEmpty();
  void drawPolygons();
  //  void applyMaterial(BSPPolygonMaterial* mat);
  int size();
  void sort();
  
  //static const int infinity = 1000000000;
  //static const double MINIMUMRELATION = 0.3;
  //static const double MINRELATIONSCALE = 2;
  
 private:
  list<BSPPolygon*> polygons;
  list<SceneObjectComponent*> components;

  static const int infinity = 1000000000;
  static const double MINIMUMRELATION = 0.3;
  static const double MINRELATIONSCALE = 2;
};
  
//int BSPPolygonSet::infinity = 1000000000;
//double BSPPolygonSet::MINIMUMRELATION = 0.3;
//double BSPPolygonSet::MINRELATIONSCALE = 2;

#endif
