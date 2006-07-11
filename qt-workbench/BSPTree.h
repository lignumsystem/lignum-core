#ifndef BSPTREE_H
#define BSPTREE_H

#include <BSPPolygon.h>
#include <Point.h>

using namespace cxxadt;

class BSPTree {
public:
  BSPTree():
divider(NULL), front(NULL), back(NULL){ }
  ~BSPTree();  
  void buildBSPTree(BSPPolygonSet& polygons);
  void drawTree(Point& eye);
  int countPolygons();
  
private:
  BSPPolygon *divider;
  BSPPolygonSet polygons;
  BSPTree *front, *back;
};

#endif
