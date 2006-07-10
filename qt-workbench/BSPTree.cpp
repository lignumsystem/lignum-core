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
 
  6.7.2006

  The heuristic function (BSPPolygon::chooseDivider()) for choosing
  the choosing the best dividing polygon for non-convex polygon set
  now works. I'll have to experiment with different parameter values
  to get the BSP work efficiently. I'm also interested to see how
  the function performs in Kauri. The worst case time complexity is
  O(N^2*logN), which isn't that bad for a NP complete problem as
  the usual case is O(N^2).

  The visualization code (LGMPolygonTree) is also able to create
  cylinder-objects from tree segments. Polygon count is still way too large
  as the segments overlap causing useless polygon splitting. I'll have
  to change the code somehow not to split overlapping opaque polygons.

  

*/


void BSPTree::buildBSPTree(BSPPolygonSet& polys) {
  if(polys.isEmpty()) {
    // DEBUG
    cout << "Cannot create a empty bsp-tree."<< endl;
    return;
  }
  BSPPolygon *root = polys.chooseDivider();
  divider = root;
  if(divider == NULL) {
    //cout << "NULL" << endl;
    polygons.addPolygons(&polys);
    return;
  }

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
  if(divider == NULL) {
    polygons.drawPolygons();
  }
  else { 
    double result = divider->classifyPoint(eye);

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
  }
}

int BSPTree::countPolygons() {
  int polys = polygons.size();
  if(front != NULL)
    polys += front->countPolygons();
  if(back != NULL)
    polys += back->countPolygons();
  return polys;
}
