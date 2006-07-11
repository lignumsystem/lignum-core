#include <LGMPolygonTree.h>
#include <QtOpenGL>


/*template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::operator() (BSPPolygonSet* polygons, const TreeCompartment<TS,BUD>*tc) const {
  
  if(const TreeSegment<TS,BUD>* ts = dynamic_cast<const TreeSegment<TS,BUD>*>(tc)) {
    double radius = GetValue(*ts, LGAR);
    double length = GetValue(*ts, LGAL);
    Point point = GetPoint(*ts);
    PositionVector direction = GetDirection(*ts);
    cout << "point:" << point.getX() << " " << point.getZ() << " " << -point.getY() << endl;
    cout << "direction:" << direction.getX() << " " << direction.getZ() << " " << -direction.getY() << endl;
    cout << "radius:" << radius << endl;
    cout << "length:" << length << endl;
    
    polygons->addPolygons(drawer->makeCylinder(radius, length, Point(point.getX(), point.getZ(), -point.getY()),
					       PositionVector(direction.getX(), direction.getZ(), -direction.getY()),
							      true, true, drawer->green, 16));
  }
  return polygons;
}

template <class TS, class BUD, class S>
BSPPolygonSet* LGMPolygonTree<TS,BUD,S>::buildTree(Tree<TS,BUD>& tree) {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  PolygonTreeBuilder<TS,BUD> builder(drawer);  
  PropagateUp(tree, polygons, builder);

  return polygons;
}

*/


