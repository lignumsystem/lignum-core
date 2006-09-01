// Qt includes
#include <QtOpenGL>

// Lignum includes
#include <BSPPolygon.h>
#include <SceneObject.h>

// Standard C/C++ includes
#include <list>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace cxxadt;

// Creates a new nontexturized polygon
BSPPolygon::BSPPolygon(Point p1, Point p2, Point p3, SceneObject* obj):
  beenDivider(false), p1(p1), p2(p2), p3(p3), object(obj) {
  normal = PositionVector(-1*Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
  normal = normal.normalize();
  distance = -(p1.getX()*normal.getX() + p1.getY()*normal.getY() + p1.getZ()*normal.getZ());
}

// Creates a new texturized polygon
BSPPolygon::BSPPolygon(Point p1, Point p2, Point p3, Point t_p1, Point t_p2, Point t_p3, SceneObject* obj):
  beenDivider(false), p1(p1), p2(p2), p3(p3), tp1(t_p1), tp2(t_p2), tp3(t_p3), object(obj) {
  normal = PositionVector(-1*Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
  normal = normal.normalize();
  distance = -(p1.getX()*normal.getX() + p1.getY()*normal.getY() + p1.getZ()*normal.getZ());
}

BSPPolygon::~BSPPolygon() {

}

// Splits a triangle polygon to a three smaller polygons based on the dividing polygon.
void BSPPolygon::split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back)  {
  // Determine the side of the each point in the polygon to be splitted
  // in relation to the plane defined by the dividing polygon.
  // Because both polygons are triangles two point always lie in same side, and
  // the third is on the other side. This way we must treat six different cases
  // differently.
  const double sideA = divider.classifyPoint(p1);
  const double sideB = divider.classifyPoint(p2);
  const double sideC = divider.classifyPoint(p3);

  if(sideB >= 0 && sideC >= 0) {
    PositionVector v1(p2 - p1);
    PositionVector v2(p3 - p1);
    PositionVector tv1(tp2 - tp1);
    PositionVector tv2(tp3 - tp1);
    double sect1 = - sideA / Dot(divider.normal, v1);
    double sect2 = - sideA / Dot(divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p1, p1 + Point(v1*sect1), p1 + Point(v2*sect2),
				      tp1, tp1 + Point(tv1*sect1), tp1 + Point(tv2*sect2), 
				      object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v1*sect1), p2, p1 + Point(v2*sect2),
			  tp1 + Point(tv1*sect1), tp2, tp1 + Point(tv2*sect2),
			  object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v2*sect2), p2, p3,
			  tp1 + Point(tv2*sect2), tp2, tp3,
			  object);
    front->addPolygon(poly);
  }

  else if(sideB <= 0 && sideC <= 0) {
    PositionVector v1(p2 - p1);
    PositionVector v2(p3 - p1);
    PositionVector tv1(tp2 - tp1);
    PositionVector tv2(tp3 - tp1);
    double sect1 = - sideA / Dot(divider.normal, v1);
    double sect2 = - sideA / Dot(divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p1, p1 + Point(v1*sect1), p1 + Point(v2*sect2),
				      tp1, tp1 + Point(tv1*sect1), tp1 + Point(tv2*sect2), 
				      object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v1*sect1), p2, p1 + Point(v2*sect2),
			  tp1 + Point(tv1*sect1), tp2, tp1 + Point(tv2*sect2),
			  object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v2*sect2), p2, p3,
			  tp1 + Point(tv2*sect2), tp2, tp3,
			  object);
    back->addPolygon(poly);
  }

  else if(sideA >= 0 && sideB >= 0) {
    PositionVector v1(p1 - p3);
    PositionVector v2(p2 - p3);
    PositionVector tv1(tp1 - tp3); 
    PositionVector tv2(tp2 - tp3);
    double sect1 = - sideC / Dot(divider.normal, v1);
    double sect2 = - sideC / Dot(divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p3, p3 + Point(v1*sect1), p3 + Point(v2*sect2),
				      tp3, tp3 + Point(tv1*sect1), tp3 + Point(tv2*sect2),
				      object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v1*sect1), p1, p3 + Point(v2*sect2),
			  tp3 + Point(tv1*sect1), tp1, tp3 + Point(tv2*sect2),
			  object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v2*sect2), p1, p2,
			  tp3 + Point(tv2*sect2), tp1, tp2, 
			  object);
    front->addPolygon(poly);
  }

  else if(sideA <= 0 && sideB <= 0) {
    PositionVector v1(p1 - p3);
    PositionVector v2(p2 - p3);
    PositionVector tv1(tp1 - tp3); 
    PositionVector tv2(tp2 - tp3);
    double sect1 = - sideC / Dot(divider.normal, v1);
    double sect2 = - sideC / Dot(divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p3, p3 + Point(v1*sect1), p3 + Point(v2*sect2),
				      tp3, tp3 + Point(tv1*sect1), tp3 + Point(tv2*sect2),
				      object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v1*sect1), p1, p3 + Point(v2*sect2),
			  tp3 + Point(tv1*sect1), tp1, tp3 + Point(tv2*sect2),
			  object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v2*sect2), p1, p2,
			  tp3 + Point(tv2*sect2), tp1, tp2,
			  object);
    back->addPolygon(poly);
  }

  else if(sideA >= 0 && sideC >= 0) {
    PositionVector v1(p1 - p2);
    PositionVector v2(p3 - p2);
    PositionVector tv1(tp1 - tp2);
    PositionVector tv2(tp3 - tp2);
    double sect1 = - sideB / Dot(divider.normal, v1);
    double sect2 = - sideB / Dot(divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p2, p2 + Point(v2*sect2), p2 + Point(v1*sect1),
				      tp2, tp2 + Point(tv2*sect2), tp2 + Point(tv1*sect1),
				      object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p2 + Point(v2*sect2), p3,
			  tp2 + Point(tv1*sect1), tp2 + Point(tv2*sect2), tp3,
			  object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p3, p1,
			  tp2 + Point(tv1*sect1), tp3, tp1,
			  object);
    front->addPolygon(poly);
  }

  else if(sideA <= 0 && sideC <= 0) {
    PositionVector v1(p1 - p2);
    PositionVector v2(p3 - p2);
    PositionVector tv1(tp1 - tp2);
    PositionVector tv2(tp3 - tp2);
    double sect1 = - sideB / Dot(divider.normal, v1);
    double sect2 = - sideB / Dot(divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p2, p2 + Point(v2*sect2), p2 + Point(v1*sect1),
				      tp2, tp2 + Point(tv2*sect2), tp2 + Point(tv1*sect1),
				      object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p2 + Point(v2*sect2), p3,
			  tp2 + Point(tv1*sect1), tp2 + Point(tv2*sect2), tp3,
			  object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p3, p1,
			  tp2 + Point(tv1*sect1), tp3, tp1,
			  object);
    back->addPolygon(poly);
  }

}

// Calculates the distance of the given point from plane
// defined by the calling polygon.
double BSPPolygon::classifyPoint(const Point& point) const {
  double EPSILON = 0.000001;
  double sideValue = normal.getX() * point.getX() +
    normal.getY() * point.getY() +
    normal.getZ() * point.getZ();
  if(abs(sideValue + distance) < EPSILON)
    return 0;
  else 
    return sideValue + distance;
}

// Returns true if the given polygon is infront of the calling polygon,
// and false if it isn't.
bool BSPPolygon::infront(const BSPPolygon& polygon) const {
  if(calculateSide(polygon) == INFRONT)
    return true;
  else 
    return false;
}

// Calculates the relational side of the given polygon to the calling polygon.
// Possible returning values are INFRONT, BEHIND, COINCIDING and SPANNING.
int BSPPolygon::calculateSide(const BSPPolygon& polygon) const {
  int numPositive = 0;
  int numNegative = 0;
  
  double cp1 = classifyPoint(polygon.p1);
  double cp2 = classifyPoint(polygon.p2);
  double cp3 = classifyPoint(polygon.p3);

  if(cp1 > 0)
    numPositive += 1;
  else if (cp1 < 0)
    numNegative += 1;

  if(cp2 > 0)
    numPositive += 1;
  else if (cp2 < 0)
    numNegative += 1;

  if(cp3 > 0)
    numPositive += 1;
  else if (cp3 < 0)
    numNegative += 1;  

  if(numPositive > 0 && numNegative == 0)
    return INFRONT;
  else if(numPositive == 0 && numNegative > 0)
    return BEHIND;
  else if(numPositive == 0 && numNegative == 0) 
    return COINCIDING;
  else
    {
      return SPANNING;
    }
}

// Draws the polygon.
void BSPPolygon::drawPolygon() const {
  glNormal3f(normal.getX(), normal.getY(), normal.getZ());

  if((tp1.getX() == 0) && (tp1.getY() == 0) && (tp1.getZ() == 0) &&
     (tp2.getX() == 0) && (tp2.getY() == 0) && (tp2.getZ() == 0) &&
     (tp3.getX() == 0) && (tp3.getY() == 0) && (tp3.getZ() == 0)) {
    glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  }
  else {
    glTexCoord2f(tp1.getX(), tp1.getY());  glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    glTexCoord2f(tp2.getX(), tp2.getY());  glVertex3f(p2.getX(), p2.getY(), p2.getZ());
    glTexCoord2f(tp3.getX(), tp3.getY());  glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  }
}

// Is the polygon transparent. 
bool BSPPolygon::isTransparent() const {
  return object->isTransparent();
}

// Has the polygon been a dividing polygon in a
// BSP-tree.
bool BSPPolygon::hasBeenDivider() const {
  return beenDivider;
}

// Tell that the polygon has been a divider.
void BSPPolygon::setDivider() {
  beenDivider = true;
}

// Returns the SceneObject-id of the polygon.
int BSPPolygon::getObjectId() const {
  return object->getId();
}

// Returns pointer to the SceneObject which contains
// the polygon.
SceneObject* BSPPolygon::getSceneObject() const{
  return object;
}

// Relational operator used when sorting the polygons by
// their SceneObject-ids.
inline bool operator < (const BSPPolygon& polygon1, const BSPPolygon& polygon2) {
  if(polygon1.object->getId() <= polygon2.object->getId())
    return true;
  else 
    return false;
}

vector<Point> BSPPolygon::getVertices() const {
  vector<Point> vertices;
  vertices.push_back(p1);
  vertices.push_back(p2);
  vertices.push_back(p3);
  return vertices;
}

BSPPolygonSet::~BSPPolygonSet() {
  for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); ) {
    delete *i;
    i = polygons.erase(i);
  }

  for(vector<SceneObjectComponent*>::iterator i = components.begin(); i != components.end(); ) {
    delete *i;
    i = components.erase(i);
  }
}    

bool BSPPolygonSet::isConvexSet() const {
  for(list<BSPPolygon*>::const_iterator i = polygons.begin(); i != polygons.end(); i++) {
    for(list<BSPPolygon*>::const_iterator j = polygons.begin(); j != polygons.end(); j++) {
      if(distance(i, j) != 0 && !((**i).infront(**j))) 
	return false;
    }
  }
  return true;
}

void BSPPolygonSet::addPolygon(BSPPolygon *polygon) {
  polygons.push_back(polygon);
}



void BSPPolygonSet::addPolygons(BSPPolygonSet* polys) {
  polygons.insert(polygons.end(), polys->polygons.begin(), polys->polygons.end());
  polys->polygons.clear();
}

BSPPolygon* BSPPolygonSet::getPolygon() {
  BSPPolygon *poly = polygons.front();
  polygons.pop_front();
  return poly;
}

void BSPPolygonSet::getOpaquePolygons(BSPPolygonSet* polys) {
  for(list<BSPPolygon*>::iterator i = polys->polygons.begin(); i != polys->polygons.end(); ) {
    if(!(*i)->isTransparent()) {
      polygons.push_back(*i);
      i = polys->polygons.erase(i);
    }
    else 
      i++;
  }
}

BSPPolygon* BSPPolygonSet::chooseDivider() {
  if(isConvexSet()) {
    return NULL;
  }
  //double minRelation = MINIMUMRELATION;
  double minRelation = 0.8;
  BSPPolygon* bestPolygon = NULL;
  //  int leastSplits = infinity;
  int leastSplits = 1000000000;
  double bestRelation = 0;
  int loop = 0;
  list<BSPPolygon*> candidates;

  if(polygons.size() > 5) {
    while(candidates.empty()) {
      candidates.clear();
      for(list<BSPPolygon*>::const_iterator i = polygons.begin(); i != polygons.end(); i++) {
	if((double)rand() / RAND_MAX < 0.05) {
	  candidates.push_back(*i);
	}
      }
    }
  }
  else {
    for(list<BSPPolygon*>::const_iterator i = polygons.begin(); i != polygons.end(); i++) {
      candidates.push_back(*i);
    }
  }
  while(bestPolygon == NULL) {
    loop++;
    for(list<BSPPolygon*>::const_iterator i = candidates.begin(); i != candidates.end();i++) {
      if(!(**i).hasBeenDivider()) {
	int numPositive = 1;
	int numNegative = 1;
	int numSpanning = 0;
	int value;
	double relation;

	for(list<BSPPolygon*>::const_iterator j = polygons.begin(); j != polygons.end(); j++) {
	  //if(distance(i, j) != 0) { 
	  if(true) {
	    value = (**i).calculateSide(**j);
	    if(value == BSPPolygon::INFRONT)
	      numPositive++;
	    else if(value == BSPPolygon::BEHIND)
	      numNegative++;
	    else if(value == BSPPolygon::SPANNING) 
	      numSpanning++;
	  }
	}
	if(numPositive < numNegative)
	  relation = (double)numPositive / (double)numNegative;
	else
	  relation = (double)numNegative / (double)numPositive;
	if(relation > minRelation && (numSpanning < leastSplits || 
				      numSpanning == leastSplits && relation > bestRelation)) {
	  bestPolygon = *i;
	  leastSplits = numSpanning;
	  bestRelation = relation;
	}
      }
    }
    minRelation = minRelation / 2;
  }
  
  //  if(bestPolygon == NULL) 
  //  cout << "NULL" << endl;

  if(bestPolygon != NULL) {
    bestPolygon->setDivider();
    polygons.remove(bestPolygon);
  }
  return bestPolygon;
    
}

bool BSPPolygonSet::isEmpty() const
{
  return polygons.empty();
}

void BSPPolygonSet::sort() {
  polygons.sort();
}

void BSPPolygonSet::drawPolygons() {
  if(polygons.size() > 1) {
    int dlist;
    SceneObject* object;
    if(polygons.front()->isTransparent()) 
      polygons.sort();
    int current_id = -1;
    int comps = 0;

    for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
      if(current_id != (**i).getObjectId()) {
	current_id = (**i).getObjectId();
	object = (**i).getSceneObject();
	dlist = glGenLists(1);
	if(dlist != 0) {
	   glNewList(dlist, GL_COMPILE);
       
	   glBegin(GL_TRIANGLES);
	   while(i != polygons.end() && current_id == (**i).getObjectId()) {
	     (**i).drawPolygon();
	     if(!(**i).hasBeenDivider())
	       delete (*i);
	     i = polygons.erase(i);
	   }

	   i--;
	   glEnd();
	   glEndList();
	   components.push_back(new SceneObjectComponent(object, dlist));
	   comps++;
	}
      }
    }
    std::sort(components.begin(), components.end());
  }


  for(int i = 0; i < components.size(); i++) {
    components[i]->drawComponent();
  }
  
  /*for(list<SceneObjectComponent*>::iterator i = components.begin(); i != components.end(); i++) {
    (**i).drawComponent();
    }*/
}

int BSPPolygonSet::size() const {
  return polygons.size();
}

int BSPPolygonSet::componentCount() const {
  //  cout << "set components:" << components.size() << endl;
  return components.size();
}

list<BSPPolygon*>& BSPPolygonSet::getPolygons() {
  return polygons;
}

