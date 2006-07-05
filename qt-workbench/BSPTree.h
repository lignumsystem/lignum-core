#ifndef BSPTREE_H
#define BSPTREE_H

#include <BSPPolygon.h>
#include <Point.h>

using namespace cxxadt;

class BSPTree {
public:
  BSPTree():
  front(NULL), back(NULL){ }
  void buildBSPTree(BSPPolygonSet& polygons);
  void drawTree(Point& eye);
  int countPolygons();

private:
  BSPPolygon *divider;
  BSPPolygonSet polygons;
  BSPTree *front, *back;
};

#endif
