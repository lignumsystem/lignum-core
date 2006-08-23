#include <BSPTree.h>
#include <QtOpenGL>
#include <stack>

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

// Destructor
BSPTree::~BSPTree() {
  if(front != NULL)
    delete front;
  if(back != NULL)
    delete back;

}

// Builds a new BSP-tree node. Chooses a dividing polygon for the node,
// and puts the rest of the polygons to the node itself (polygons coincident
// to the dividing polygon), or creates children nodes for the node,
// if some of the polygons are in front of or back of the dividing polygon. 
void BSPTree::buildBSPTree(BSPPolygonSet& polys) {
  opaquePolygons.getOpaquePolygons(&polys);

  if(polys.isEmpty()) {
    return;
  }
  BSPPolygon *root = polys.chooseDivider();
  divider = root;
  if(divider == NULL) {
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
	BSPPolygonSet *front_pieces = new BSPPolygonSet();
	BSPPolygonSet *back_pieces = new BSPPolygonSet();
	poly->split(*divider, front_pieces, back_pieces);
	delete poly;
	back_polygons.addPolygons(back_pieces);
	front_polygons.addPolygons(front_pieces);
	delete back_pieces;
	delete front_pieces;
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
}

// Adds new polygons to a existing BSP-tree. If some of the inserted
// polygons are infront or back of the dividing polygons, and no
// corresponding child node exist for the node, a new node is created
// for the polygons to be inserted.
void BSPTree::addPolygonsToTree(BSPPolygonSet& polys) {
  opaquePolygons.getOpaquePolygons(&polys);

  if(polys.isEmpty()) {
    return;
  }
  // If the existing tree-node is a convex set of polygons.
  if(divider == NULL) {
    polys.addPolygons(&polygons);
    // New divider must be chosen for the polygons.
    divider = polys.chooseDivider();
    // If the new set remains convex.
    if(divider == NULL) {
      polygons.addPolygons(&polys);
      return;
    }
    // Else create new BSP-subtree starting from the current node.
  }

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
	BSPPolygonSet *front_pieces = new BSPPolygonSet();
	BSPPolygonSet *back_pieces = new BSPPolygonSet();
	poly->split(*divider, front_pieces, back_pieces);
	delete poly;
	back_polygons.addPolygons(back_pieces);
	front_polygons.addPolygons(front_pieces);
	delete back_pieces;
	delete front_pieces;
	break;
      }
  }

  if(!front_polygons.isEmpty()) {
    // If front-node doesn't exist create a new one.
    if(!front) {
      front = new BSPTree();
      front->buildBSPTree(front_polygons);
    }
    else
      front->addPolygonsToTree(front_polygons);
  }
  
  if(!back_polygons.isEmpty()) {
    // If back-node doesn't exist create a new one.
    if(!back) {
      back = new BSPTree();
      back->buildBSPTree(back_polygons);
    }
    else
      back->addPolygonsToTree(back_polygons);
  }
}

/*
  // Stack based implementation of drawTransparentTree-method.
  // Might be a bit faster on some processors than the recursive based method,
  // but currently the drawing order doesn't work correctly.
  void BSPTree::drawTransparentTree(Point& eye, PositionVector& direction) {
  BSPTree* tree = this;
  stack<BSPTree*> trees;
  while(true) {
    if(tree->divider == NULL) {
      tree->polygons.drawPolygons();
    }
    else {
      double result = tree->divider->classifyPoint(eye);
      if(result > 0) {
	if(tree->front != NULL)
	  trees.push(tree->front);
	tree->polygons.drawPolygons();
	if(tree->back != NULL)
	  trees.push(tree->back);
      }
      else if(result < 0) {
	if(tree->back != NULL)
	  trees.push(tree->back);
	tree->polygons.drawPolygons();
	if(tree->front != NULL)
	  trees.push(tree->front);
      }
      else {
	if(tree->front != NULL)
	  trees.push(tree->front);
	if(tree->back != NULL)
	  trees.push(tree->back);
      }
    }
    if(!trees.empty()) {
      tree = trees.top();
      trees.pop();
    }
    else
      break;
  }
  }*/

// Draws the whole tree.
void BSPTree::drawTree(Point& eye, PositionVector& direction) {
  // Draw the opaque polygons. Depth-buffer writing is set on during
  // the drawing. 
  opaquePolygons.drawPolygons();
  glDepthMask(GL_FALSE);

  // Draw the transparent polygons. Depth-buffer writing is disabled,
  // but depth-testing is left on. Sorting of the transparent is done
  // using the BSP.
  drawTransparentTree(eye, direction);
  glDepthMask(GL_TRUE);
}

// Draws the transparent polygons.
void BSPTree::drawTransparentTree(Point& eye, PositionVector& direction) {
  // Polygons form a convex set, so they can be drawn in a arbitrary order.
  if(divider == NULL) {
    polygons.drawPolygons();
  }
  // Else the polygons must be drawn in order based on the
  // position of the viewer. 
  else { 
    double result = divider->classifyPoint(eye);
      
    if(result > 0) {
      if(back != NULL) 
	back->drawTransparentTree(eye, direction);
      polygons.drawPolygons();
      if(front != NULL)
	front->drawTransparentTree(eye, direction);
    }
    
    else if(result < 0) {
      if(front != NULL)
	front->drawTransparentTree(eye, direction);
      polygons.drawPolygons();
      if(back != NULL)
	back->drawTransparentTree(eye, direction);
    }
    
    else {
      if(front != NULL)
	front->drawTransparentTree(eye, direction);
      if(back != NULL)
	back->drawTransparentTree(eye, direction);
    }
  }
}

// Counts the number of polygons in the tree.
int BSPTree::countPolygons() const {
  int polys = polygons.size();
  polys += opaquePolygons.size();
  if(front != NULL)
    polys += front->countPolygons();
  if(back != NULL)
    polys += back->countPolygons();
  return polys;
}

// Counts the number of SceneObjectComponents of
// of the tree.
int BSPTree::countComponents() const {
  int comps = polygons.componentCount();
  if(front != NULL)
    comps += front->countComponents();
  if(back != NULL)
    comps += back->countComponents();
  return comps;
}

// Gets the maximum depth of the tree.
int BSPTree::getDepth() const {
  int back_depth = 0;
  int front_depth = 0;
  if(back != NULL)
    back_depth = back->getDepth();
  if(front != NULL)
    front_depth = front->getDepth();
  if(back_depth > front_depth)
    return 1 + back_depth;
  else
    return 1 + front_depth;
}

// Gets the number of nodes in the tree.
int BSPTree::getNodeCount() const {
  int nodes = 1;
  if(back != NULL)
    nodes += back->getNodeCount();
  if(front != NULL)
    nodes += front->getNodeCount();
  return nodes;
}

