#ifndef LGMPOLYGONTREE_H
#define LGMPOLYGONTREE_H

#include <list>
#include <Lignum.h>
#include "CylinderVolume.h"
//#include <GLDrawer.h>
#include <BSPPolygon.h>
#include <BSPPolygonMaterial.h>
#include <Point.h>
#include <PositionVector.h>
#include <SceneObject.h>



using namespace Lignum;
using namespace cxxadt;

//class GLDrawer;

template <class TS, class BUD=DefaultBud<TS>, class S=Ellipse>
class PolygonTreeBuilder {
  public:
  //PolygonTreeBuilder(GLDrawer* gldrawer):
  //drawer(gldrawer) { }
  PolygonTreeBuilder(int tex, list<CylinderVolume>* cyls):
  texture(tex), cylinders(cyls) { }
  //  PolygonTreeBuilder() { }
  BSPPolygonSet* operator() (BSPPolygonSet* polygons, const TreeCompartment<TS,BUD>* tc) const ;
  //  list<CylinderVolume> getCylinders();
  private:
  
  // BSPPolygonSet* makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, BSPPolygonMaterial* material, int detail = 20) const;
  BSPPolygonSet* makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int r_detail, int y_detail) const;
  //mutable GLDrawer* drawer;
  mutable list<CylinderVolume>* cylinders;
  int texture;
};


template <class TS, class BUD=DefaultBud<TS>, class S=Ellipse>
  class LGMPolygonTree {
  public:
  //  LGMPolygonTree(GLDrawer* gldrawer)
  //:drawer(gldrawer) { }
  LGMPolygonTree() { }
  //LGMPolygonTree() { }
  BSPPolygonSet* buildTree(Tree<TS,BUD>& tree, int texture);
  list<CylinderVolume>* getCylinders();

  private:
  //    GLDrawer* drawer;
  list<CylinderVolume>* cylinders;
};


template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::operator() (BSPPolygonSet* polygons, const TreeCompartment<TS,BUD>*tc) const {

  if(const TreeSegment<TS,BUD>* ts = dynamic_cast<const TreeSegment<TS,BUD>*>(tc)) {
    double radius = GetValue(*ts, LGAR);
    double length = GetValue(*ts, LGAL);
    Point point = GetPoint(*ts);
    PositionVector direction = GetDirection(*ts);
    //    cout << "point:" << point.getX() << " " << point.getZ() << " " << -point.getY() << endl;
    //cout << "direction:" << direction.getX() << " " << direction.getZ() << " " << -direction.getY() << endl;
    //cout << "radius:" << radius << endl;
    //cout << "length:" << length << endl;
    
    /*GLfloat color1[] = {0.2, 0.9, 0.2, 1.0,
			0.1, 0.9, 0.1, 1.0,
			0.1, 0.9, 0.1, 1.0,
			50};*/
    GLfloat color1[] = {1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0,
			50};
    BSPPolygonMaterial* green = new BSPPolygonMaterial(color1);
    SceneObject* object = new SceneObject(green, texture, false);
    int detail = 20;
    polygons->addPolygons(makeCylinder(radius+0.01, length, Point(point.getX(), point.getZ(), -point.getY()),
					       PositionVector(direction.getX(), direction.getZ(), -direction.getY()),
				       false, true, object, detail, 1));
    CylinderVolume cylinder((radius+0.01), length, Point(point.getX(), point.getZ(), -point.getY()),
			    PositionVector(direction.getX(), direction.getZ(), -direction.getY()),
			    detail);
    cylinders->push_back(cylinder);
  }
  return polygons;
}

/*template <class TS, class BUD, class S>
  list<CylinderVolume> PolygonTreeBuilder<TS,BUD,S>::getCylinders() {
  return cylinders;
  }*/

template <class TS, class BUD, class S>
  BSPPolygonSet* LGMPolygonTree<TS,BUD,S>::buildTree(Tree<TS,BUD>& tree, int texture) {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  cylinders = new list<CylinderVolume>();
  PolygonTreeBuilder<TS,BUD,S> builder(texture, cylinders);  
  PropagateUp(tree, polygons, builder);

  return polygons;
}

template <class TS, class BUD, class S>
  list<CylinderVolume>* LGMPolygonTree<TS,BUD,S>::getCylinders() {
  return cylinders;
}

// MATERIAALI PITÄÄ VAIHTAA SCENEOBJEKTIIN
template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int r_detail, int y_detail) const  {
  double PI = 3.14159265;
  double sine, cosine, sine_next, cosine_next, y, y_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();
  //  SceneObject* object = new SceneObject(material, 0);

  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  vector<Point> vertices(3);
  vector<Point> t_vertices(3);
  
  vector<Point> vertices2(4);
  vector<Point> t_vertices2(4);
  PositionVector v1, v2, v3, v4;

  for(int i = 0; i < r_detail; i++) {
    sine = radius*sin(i*2.0*PI/r_detail);
    cosine = radius*cos(i*2.0*PI/r_detail);
    sine_next = radius*sin((i+1)*2.0*PI/r_detail);
    cosine_next = radius*cos((i+1)*2.0*PI/r_detail);

    for(int j = 0; j < y_detail; j++) {
      y = j / (double)y_detail * height;
      y_next = (j+1) / (double)y_detail * height;
      
      /*v1 = PositionVector(sine, y, cosine);
      v2 = PositionVector(sine, y_next, cosine);
      v3 = PositionVector(sine_next, y_next, cosine_next);
      v4 = PositionVector(sine_next, y, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      v4 = v4.rotate(origo, dir, PI);
    
      vertices2[0] = Point(v1)+point;
      vertices2[1] = Point(v2)+point;
      vertices2[2] = Point(v3)+point;
      vertices2[3] = Point(v4)+point;
      t_vertices2[0] = Point(i/(double)r_detail, y/height, 0);
      t_vertices2[1] = Point(i/(double)r_detail, y_next/height, 0);
      t_vertices2[2] = Point((i+1)/(double)r_detail, y_next/height, 0);
      t_vertices2[3] = Point((i+1)/(double)r_detail, y/height, 0);
      polygons->addPolygon(new BSPPolygon(vertices2, t_vertices2, object));*/
      
      PositionVector v1(sine, y, cosine);
      PositionVector v2(sine, y_next, cosine);
      PositionVector v3(sine_next, y, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
	    
	    /*    vertices[0] = Point(v1)+point;
	    vertices[1] = Point(v2)+point;
	    vertices[2] = Point(v3)+point;
	    t_vertices[0] = Point(i/(double)r_detail, y/height, 0);
	    t_vertices[1] = Point(i/(double)r_detail, y_next/height, 0);
	    t_vertices[2] = Point((i+1)/(double)r_detail, y/height, 0);
	    polygons->addPolygon(new BSPPolygon(vertices, t_vertices, object));*/
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(i/(double)r_detail, y/height, 0),
					  Point(i/(double)r_detail, y_next/height, 0),
					  Point((i+1)/(double)r_detail, y/height, 0),
					  object));
      
      
      v1 = PositionVector(sine_next, y, cosine_next);
      v2 = PositionVector(sine, y_next, cosine);
      v3 = PositionVector(sine_next, y_next, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
	    
      /*vertices[0] = Point(v1)+point;
	    vertices[1] = Point(v2)+point;
	    vertices[2] = Point(v3)+point;
	    t_vertices[0] = Point((i+1)/(double)r_detail, y, 0);
	    t_vertices[1] = Point(i/(double)r_detail, y_next/height, 0);
	    t_vertices[2] = Point((i+1)/(double)r_detail, y_next/height, 0);
	    polygons->addPolygon(new BSPPolygon(vertices, t_vertices, object));*/
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point((i+1)/(double)r_detail, y/height, 0),
					  Point(i/(double)r_detail, y_next/height, 0),
					  Point((i+1)/(double)r_detail, y_next/height, 0),
					  object));
    }
  
    if(drawTop) {
      v1 = PositionVector(sine, height, cosine);
      v2 = PositionVector(0, height, 0);
      v3 = PositionVector(sine_next, height, cosine_next);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      /* vertices[0] = Point(v1)+point;
      vertices[1] = Point(v2)+point;
      vertices[2] = Point(v3)+point;
      polygons->addPolygon(new BSPPolygon(vertices, object));*/
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
    }
    
    if(drawBottom) {
      v1 = PositionVector(sine, 0, cosine);
      v2 = PositionVector(sine_next, 0, cosine_next);
      v3 = PositionVector(0, 0, 0);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      /*vertices[0] = Point(v1)+point;
      vertices[1] = Point(v2)+point;
      vertices[2] = Point(v3)+point;
      polygons->addPolygon(new BSPPolygon(vertices, object));*/
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
      
    }

  }
  //cout << "Cylinder size:" << polygons->size() << endl;
  return polygons;
}

#endif
