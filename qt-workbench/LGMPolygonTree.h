#ifndef LGMPOLYGONTREE_H
#define LGMPOLYGONTREE_H

#include <Lignum.h>
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
  PolygonTreeBuilder(int tex):
  texture(tex) { }
  //  PolygonTreeBuilder() { }
  BSPPolygonSet* operator() (BSPPolygonSet* polygons, const TreeCompartment<TS,BUD>* tc) const ;
  
  private:
  
  // BSPPolygonSet* makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, BSPPolygonMaterial* material, int detail = 20) const;
  BSPPolygonSet* makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int detail = 20) const;
  //mutable GLDrawer* drawer;
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
  private:
  //    GLDrawer* drawer;
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
    SceneObject* object = new SceneObject(green, texture);
    polygons->addPolygons(makeCylinder(radius, length, Point(point.getX(), point.getZ(), -point.getY()),
					       PositionVector(direction.getX(), direction.getZ(), -direction.getY()),
							      true, true, object, 4));
  }
  return polygons;
}

template <class TS, class BUD, class S>
  BSPPolygonSet* LGMPolygonTree<TS,BUD,S>::buildTree(Tree<TS,BUD>& tree, int texture) {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  PolygonTreeBuilder<TS,BUD,S> builder(texture);  
  PropagateUp(tree, polygons, builder);
  
  return polygons;
}


// MATERIAALI PITÄÄ VAIHTAA SCENEOBJEKTIIN
template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int detail) const  {
  double PI = 3.14159265;
  double sine, cosine, sine_next, cosine_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();
  //  SceneObject* object = new SceneObject(material, 0);

  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  
  for(int i = 0; i < detail; i++) {
    sine = radius*sin(i*2.0*PI/detail);
    cosine = radius*cos(i*2.0*PI/detail);
    sine_next = radius*sin((i+1)*2.0*PI/detail);
    cosine_next = radius*cos((i+1)*2.0*PI/detail);
    
    PositionVector v1(sine, 0, cosine);
    PositionVector v2(sine, height, cosine);
    PositionVector v3(sine_next, 0, cosine_next);
    v1 = v1.rotate(origo, dir, PI);
    v2 = v2.rotate(origo, dir, PI);
    v3 = v3.rotate(origo, dir, PI);
    
    polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					Point(v2)+point,
					Point(v3)+point,
					Point(i/(double)detail, 0, 0),
					Point(i/(double)detail, 1, 0),
					Point((i+1)/(double)detail, 0, 0),
					object));

    v1 = PositionVector(sine_next, 0, cosine_next);
    v2 = PositionVector(sine, height, cosine);
    v3 = PositionVector(sine_next, height, cosine_next);
    v1 = v1.rotate(origo, dir, PI);
    v2 = v2.rotate(origo, dir, PI);
    v3 = v3.rotate(origo, dir, PI);
    
    polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					Point(v2)+point,
					Point(v3)+point,
					Point((i+1)/(double)detail, 0, 0),
					Point(i/(double)detail, 1, 0),
					Point((i+1)/(double)detail, 1, 0),
					object));
    
    if(drawTop) {
      v1 = PositionVector(sine, height, cosine);
      v2 = PositionVector(0, height, 0);
      v3 = PositionVector(sine_next, height, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
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
