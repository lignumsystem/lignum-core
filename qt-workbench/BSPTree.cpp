#include <BSPTree.h>
#include <QtOpenGL>

void BSPTree::buildBSPTree(BSPPolygonSet& polys) {
  if(polys.isEmpty()) {
    // DEBUG
    cout << "Cannot create a empty bsp-tree."<< endl;
    return;
  }
  BSPPolygon *root = polys.chooseDivider();
  divider = root;
  polygons.addPolygon(root);
  //cout << "here2" << endl;
  BSPPolygonSet front_polygons, back_polygons;
  BSPPolygon *poly;
  
  while(!polys.isEmpty()) {
    poly = polys.getPolygon();
    int result = divider->calculateSide(*poly);
    switch(result)
      {
      case BSPPolygon::COINCIDING:
	polygons.addPolygon(poly);
	break;
      case BSPPolygon::BEHIND:
	back_polygons.addPolygon(poly);
	break;
      case BSPPolygon::INFRONT:
	front_polygons.addPolygon(poly);
	break;
      case BSPPolygon::SPANNING:
	//cout << "SPANS" << endl;
	BSPPolygonSet *front_pieces = new BSPPolygonSet();
	BSPPolygonSet *back_pieces = new BSPPolygonSet();
	poly->split(*divider, front_pieces, back_pieces);
	back_polygons.addPolygons(back_pieces);
	front_polygons.addPolygons(front_pieces);
	//cout << "SPAN ENDS" << endl;
	break;
      }
  }
  if(!front_polygons.isEmpty()) {
    front = new BSPTree();
    front->buildBSPTree(front_polygons);
  }
  
  if(!back_polygons.isEmpty()) {
    back = new BSPTree();
    back->buildBSPTree(back_polygons);
  }

  //cout << "here3" << endl;
}

void BSPTree::drawTree(Point& eye) {
  double result = divider->classifyPoint(eye);
  //cout << "drawTree, result:" << result << endl;

  if(result > 0) {
    if(back != NULL) 
      back->drawTree(eye);
    polygons.drawPolygons();
    if(front != NULL)
      front->drawTree(eye);
  }

  else if(result < 0) {
    if(front != NULL)
      front->drawTree(eye);
    polygons.drawPolygons();
    if(back != NULL)
      back->drawTree(eye);
  }
  
  else {
    if(front != NULL)
      front->drawTree(eye);
    if(back != NULL)
      back->drawTree(eye);
  }
  //cout << "drawTreeEnd" << endl;
}
