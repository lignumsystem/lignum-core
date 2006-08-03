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
  void buildBSPTree(BSPPolygonSet& polygons); 
  void drawTree(Point& eye, PositionVector& direction);
  void drawTransparentTree(Point& eye, PositionVector& direction);
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
