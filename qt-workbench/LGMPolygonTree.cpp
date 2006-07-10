/*#include <LGMPolygonTree.h>
#include <QtOpenGL>

class BSPPolygonSet;
template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::operator() (BSPPolygonSet* polygons, TreeCompartment<TS,BUD>*tc) const {
  
  if(TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)) {
    double radius = GetValue(ts, LGAR);
    double length = GetValue(ts, LGAL);
    Point point = GetPoint(ts);
    PositionVector direction = GetDirection(ts);
    polygons.addPolygons(gldrawer->makeCylinder(radius, length, point, direction, false, false, gldrawer->green, 20));
  }

}

template <class TS, class BUD, class S>
BSPPolygonSet* LGMPolygonTree<TS,BUD,S>::buildTree(Tree<TS,BUD>& tree) {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  PolygonTreeBuilder<TS,BUD> builder(drawer);  
  PropagateUp(tree, polygons, builder);

  return polygons;
}

template <class TS, class BUD, class S>
void LGMPolygonTree<TS,BUD,S>::foo() {
  cout << "foo" << endl;
}*/
