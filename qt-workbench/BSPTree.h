#ifndef BSPTREE_H
#define BSPTREE_H

#include <BSPPolygon.h>
#include <Point.h>
#include <CylinderVolume.h>

using namespace cxxadt;

class BSPTree {
public:
  BSPTree():
divider(NULL), front(NULL), back(NULL){ }
  ~BSPTree();  
  void buildBSPTree(BSPPolygonSet& polygons, list<CylinderVolume>* cylinders); 
  void drawTree(Point& eye, PositionVector& direction);
  void drawTransparentTree(Point& eye, PositionVector& direction);
  bool removeHiddenPolygons(list<CylinderVolume>* volumes);
  int countPolygons() const;
  int countComponents() const;
  int getDepth() const;
  int getNodeCount() const;
private:
  BSPPolygon *divider;
  BSPPolygonSet opaquePolygons;
  BSPPolygonSet polygons;
  BSPTree *front, *back;
};

#endif
