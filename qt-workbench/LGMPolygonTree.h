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

#include <VisualizationParameters.h>

template <class TS, class BUD=DefaultBud<TS>, class S=Ellipse>
class PolygonTreeBuilder {
  public:
  PolygonTreeBuilder(VisualizationParameters params, list<CylinderVolume>* cyls):
  parameters(params), cylinders(cyls) { }
  
  BSPPolygonSet* operator() (BSPPolygonSet* polygons, TreeCompartment<TS,BUD>* tc) const ;
  
  private:
  
  BSPPolygonSet*  makeCylinder(double radius,
			       double height,
			       Point point,
			       PositionVector direction,
			       bool drawBottom,
			       bool drawTop,
			       SceneObject* object,
			       int r_detail,
			       int y_detail) const;

  BSPPolygonSet* makeFoliage(double radius, double height, Point point, PositionVector direction,
			     SceneObject* object) const;
  BSPPolygonSet* makePetiole(Point sp, Point ep, SceneObject* object) const;
  BSPPolygonSet* makeTriangleLeaf(Point lc, Point rc, Point ac, SceneObject* object) const;
  BSPPolygonSet* makeEllipseLeaf(const Ellipse* ellipse, int detail, SceneObject* object) const;
  
  mutable list<CylinderVolume>* cylinders;
  VisualizationParameters parameters;
};


template <class TS, class BUD=DefaultBud<TS>, class S=Ellipse>
  class LGMPolygonTree {
  public:
  LGMPolygonTree() { }
  BSPPolygonSet* buildTree(Tree<TS,BUD>& tree, VisualizationParameters params);
  list<CylinderVolume>* getCylinders();

  private:
  list<CylinderVolume>* cylinders;
};


template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::operator() (BSPPolygonSet* polygons, TreeCompartment<TS,BUD>*tc) const {

  if(TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)) {
    double radius = GetValue(*ts, LGAR);
    double length = GetValue(*ts, LGAL);
    Point point = GetPoint(*ts);
    PositionVector direction = GetDirection(*ts);
    SceneObject* object = new SceneObject(parameters.getMaterial(), parameters.getCylinderTexture(), false);
    BSPPolygonSet* cyl = makeCylinder(radius, length, Point(point.getX(), point.getY(), point.getZ()),
					   PositionVector(direction.getX(), direction.getY(), direction.getZ()),
					   false, true, object,
					   parameters.getCylinderRDetail(), parameters.getCylinderHDetail());
    polygons->addPolygons(cyl);
    delete cyl;
    CylinderVolume cylinder(radius, length, Point(point.getX(), point.getY(), point.getZ()),
			    PositionVector(direction.getX(), direction.getY(), direction.getZ()),
			    parameters.getCylinderRDetail());
    cylinders->push_back(cylinder);

    if(HwTreeSegment<TS,BUD,S>* hw = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(ts)) {
      list<BroadLeaf<S>*>& ll = GetLeafList(*hw);
      for(typename list<BroadLeaf<S>*>::iterator i = ll.begin(); i != ll.end(); i++) {
	const Shape& s = static_cast<const Shape&>(GetShape(**i));
	Petiole p = GetPetiole(**i);
	SceneObject* p_object = new SceneObject(parameters.getPetioleMaterial(), 0, false);
	BSPPolygonSet* petiole = makePetiole(GetStartPoint(p),
					     GetEndPoint(p),
					     p_object);
	polygons->addPolygons(petiole);
	delete petiole;
	if(const Triangle* t = dynamic_cast<const Triangle*>(&s)) {
	  SceneObject* object = new SceneObject(parameters.getLeafMaterial(), parameters.getLeafTexture(), parameters.useBSP());
	  BSPPolygonSet* leaf = makeTriangleLeaf(t->getLeftCorner(),
						 t->getRightCorner(),
						 t->getApexCorner(),
						 object);
	  polygons->addPolygons(leaf);
	  delete leaf;
	}
	else if(const Ellipse* e = dynamic_cast<const Ellipse*>(&s)) {
	  SceneObject* object = new SceneObject(parameters.getLeafMaterial(), parameters.getLeafTexture(), parameters.useBSP());
	  vector<Point> vertices;
	  BSPPolygonSet* leaf = makeEllipseLeaf(e, 10, 
						//e->getVertexVector(vertices, 10), e->getSemimajorAxis(), e->getSemiMinorAxis(),
						object);
	  polygons->addPolygons(leaf);
	  delete leaf;
	}
      }
    }
  }
  return polygons;
}

template <class TS, class BUD, class S>
  BSPPolygonSet* LGMPolygonTree<TS,BUD,S>::buildTree(Tree<TS,BUD>& tree, VisualizationParameters params) {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  cylinders = new list<CylinderVolume>();
  PolygonTreeBuilder<TS,BUD,S> builder(params, cylinders);  
  PropagateUp(tree, polygons, builder);

  return polygons;
}

template <class TS, class BUD, class S>
  list<CylinderVolume>* LGMPolygonTree<TS,BUD,S>::getCylinders() {
  return cylinders;
}

template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int r_detail, int y_detail) const  {
  double PI = 3.14159265;
  double sine, cosine, sine_next, cosine_next, y, y_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();

  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  vector<Point> vertices(3);
  vector<Point> t_vertices(3);
  
  // vector<Point> vertices2(4);
  //vector<Point> t_vertices2(4);
  PositionVector v1, v2, v3, v4;
  sine_next = radius*sin(0*2.0*PI/r_detail);
  cosine_next = radius*cos(0*2.0*PI/r_detail);

  for(int i = 0; i < r_detail; i++) {
    //sine = radius*sin(i*2.0*PI/r_detail);
    //cosine = radius*cos(i*2.0*PI/r_detail);
    sine = sine_next;
    cosine = cosine_next;
    sine_next = radius*sin((i+1)*2.0*PI/r_detail);
    cosine_next = radius*cos((i+1)*2.0*PI/r_detail);

    for(int j = 0; j < y_detail; j++) {
      y = j / (double)y_detail * height;
      y_next = (j+1) / (double)y_detail * height;
      
      /*  v1 = PositionVector(sine, y, cosine);
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
      
      /*vertices[0] = Point(v1)+point;
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

template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeFoliage(double radius, double height, Point point, PositionVector direction,
							 SceneObject* object) const {
  return NULL;
}





template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makePetiole(Point sp, Point ep, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  /*  double temp = sp.getY();
  sp.setY(sp.getZ());
  sp.setZ(-temp);

  temp = ep.getY();
  ep.setY(ep.getZ());
  ep.setZ(-temp);*/
  
  /*  vector<Point> vertices(3);

  vertices[0] = sp;
  vertices[1] = Point(ep.getX()+0.0005, ep.getY(),ep.getZ());
  vertices[2] = ep;
  polygons->addPolygon(new BSPPolygon(vertices, object));

  vertices[0] = sp;
  vertices[1] = Point(sp.getX()+0.0005, sp.getY(),sp.getZ());
  vertices[2] = Point(ep.getX()+0.0005, ep.getY(),ep.getZ());
  polygons->addPolygon(new BSPPolygon(vertices, object));

  vertices[0] = sp;
  vertices[1] = ep;
  vertices[2] = Point(ep.getX()+0.0005, ep.getY(),ep.getZ());
  polygons->addPolygon(new BSPPolygon(vertices, object));

  vertices[0] = sp;
  vertices[1] = Point(ep.getX()+0.0005, ep.getY(),ep.getZ());
  vertices[2] = Point(sp.getX()+0.0005, sp.getY(),sp.getZ());
  polygons->addPolygon(new BSPPolygon(vertices, object));*/


  polygons->addPolygon(new BSPPolygon(sp,
				      Point(ep.getX()+0.005, ep.getY(),ep.getZ()),
				      ep,
				      object));
  polygons->addPolygon(new BSPPolygon(sp,
				      Point(sp.getX()+0.005, sp.getY(), sp.getZ()),
				      Point(ep.getX()+0.005, ep.getY(), ep.getZ()),
				      object));
  polygons->addPolygon(new BSPPolygon(sp,
				      ep,
				      Point(ep.getX()+0.005, ep.getY(),ep.getZ()),
				      object));
  polygons->addPolygon(new BSPPolygon(sp,
				      Point(ep.getX()+0.005, ep.getY(), ep.getZ()),
				      Point(sp.getX()+0.005, sp.getY(), sp.getZ()),
				      object));
  return polygons;
}

template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeTriangleLeaf(Point lc, Point rc, Point ac, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  /*vector<Point> vertices(3);
  vertices[0] = lc;
  vertices[1] = rc;
  vertices[2] = ac;
  polygons->addPolygon(new BSPPolygon(vertices, object));

  vertices[0] = lc;
  vertices[1] = ac;
  vertices[2] = rc;
  polygons->addPolygon(new BSPPolygon(vertices, object));*/
  
  polygons->addPolygon(new BSPPolygon(lc, rc, ac, object));
  polygons->addPolygon(new BSPPolygon(lc, ac, rc, object));
  
  return polygons;

}

template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeEllipseLeaf(const Ellipse* ellipse, int detail, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  if(object->hasTexture()) {
    Point p1(ellipse->getCenterPoint() +
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) + 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));
    Point p2(ellipse->getCenterPoint() +
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) - 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));
    Point p3(ellipse->getCenterPoint() - 
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) + 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));
    Point p4(ellipse->getCenterPoint() -
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) - 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));

    double temp = p1.getY();
    /*    p1.setY(p1.getZ());
    p1.setZ(-temp);
    temp = p2.getY();
    p2.setY(p2.getZ());
    p2.setZ(-temp);
    temp = p3.getY();
    p3.setY(p3.getZ());
    p3.setZ(-temp);
    temp = p4.getY();
    p4.setY(p4.getZ());
    p4.setZ(-temp);*/


    polygons->addPolygon(new BSPPolygon(p1, p2, p3,
					Point(1, 1, 0), Point(0, 1, 0), Point(1, 0, 0), object));
    polygons->addPolygon(new BSPPolygon(p1, p3, p2,
					Point(1, 1, 0), Point(1, 0, 0), Point(0, 1, 0), object));
    
    polygons->addPolygon(new BSPPolygon(p2, p4, p3,
					Point(0, 1, 0), Point(0, 0, 0), Point(1, 0, 0), object));
    polygons->addPolygon(new BSPPolygon(p2, p3, p4,
					Point(0, 1, 0), Point(1, 0, 0), Point(0, 0, 0), object));
    return polygons;
  }
  else {
    vector<Point> vertices;
    vertices = ellipse->getVertexVector(vertices, 10);

    int size = vertices.size();
    /*for(int i = 0; i < size; i++) {
      double temp = vertices[i].getY();
      vertices[i].setY(vertices[i].getZ());
      vertices[i].setZ(-temp);
      }*/
    //polygons->addPolygon(new BSPPolygon(vertices, object));
    
    double step = 1.0/(size/2.0 );
    polygons->addPolygon(new BSPPolygon(vertices[0], vertices[1], vertices[size-1],
					Point(0.5,1,0), Point(1,1-step,0), Point(0,1-step,0), object));
    polygons->addPolygon(new BSPPolygon(vertices[0], vertices[size-1], vertices[1],
					Point(0.5,1,0), Point(0,1-step,0), Point(1,1-step,0), object));
    
    polygons->addPolygon(new BSPPolygon(vertices[size/2-1], vertices[size/2], vertices[size/2+1],
					Point(1,step,0), Point(0.5,0,0), Point(0,step,0), object));
    polygons->addPolygon(new BSPPolygon(vertices[size/2-1], vertices[size/2+1], vertices[size/2],
					Point(1,step,0), Point(0,step,0), Point(0.5,0,0), object));
    
    for(int i = 1; i < size/2-1; i++) {
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[i+1], vertices[size-i],
					  Point(1,1-step*i,0), Point(1,1-step*(i+1),0), Point(0,1-step*i,0), object));
      
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i], vertices[i+1],
					  Point(1,1-step*i,0), Point(0,1-step*i,0),  Point(1,1-step*(i+1),0), object));
      
      polygons->addPolygon(new BSPPolygon(vertices[i+1], vertices[size-i-1], vertices[size-i],
					  Point(1,1-step*(i+1),0), Point(0,1-step*(i+1),0),  Point(0,1-step*i,0), object));
      
      polygons->addPolygon(new BSPPolygon(vertices[i+1], vertices[size-i], vertices[size-i-1],
					  Point(1,1-step*(i+1),0), Point(0,1-step*i,0), Point(0,1-step*(i+1),0), object));    
      
      
    }
    
    return polygons;
  }
}
  
#endif
