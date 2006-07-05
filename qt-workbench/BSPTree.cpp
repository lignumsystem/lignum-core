#include <BSPTree.h>
#include <QtOpenGL>

/*
  5.7.2006
  The BSP-tree should now work OK. There is some problems with the
  heuristic algorithm for choosing the dividing polygon for creating
  a well balanced tree. Some NULL-pointer reference causes an error
  after the call to the function. To get this working properly ain't
  the top priority right now as the algorithm is to slow to be run
  in ailanthus with high polygon counts.
  
  Anyways the BSP (drawing order, splitting, blending, lighting etc.) 
  works now and it's quite fast even with slower CPUs as in ailanthus.
  Without the better function for choosing the dividing polygon (now it
  chooses first polygon in the list) the amount of splitting can be huge.
 

*/


void BSPTree::buildBSPTree(BSPPolygonSet& polys) {
  if(polys.isEmpty()) {
    // DEBUG
    cout << "Cannot create a empty bsp-tree."<< endl;
    return;
  }
  BSPPolygon *root = polys.chooseDivider();
  if(root == NULL) {
    polygons.addPolygons(&polys);
    return;
  }
  divider = root;
  polygons.addPolygon(root);
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
	//cout << "SPLIT" << endl;
	poly->split(*divider, front_pieces, back_pieces);
	back_polygons.addPolygons(back_pieces);
	front_polygons.addPolygons(front_pieces);
	//cout << "SPAN ENDS" << endl;
	//delete back_pieces;
	//delete front_pieces;
	break;
      }
  }
  //  polygons.sort();
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

int BSPTree::countPolygons() {
  int polys = polygons.size();
  if(front != NULL)
    polys += front->countPolygons();
  if(back != NULL)
    polys += back->countPolygons();
  return polys;
}
