#include <BSPPolygon.h>
#include <list>
#include <QtOpenGL>
#include <cstdlib>
#include <SceneObject.h>

using namespace std;
using namespace cxxadt;

/*BSPPolygon::BSPPolygon(Point p1, Point p2, Point p3, SceneObject* obj):
  beenDivider(false), p1(p1), p2(p2), p3(p3), object(obj) {
  normal = PositionVector(-1*Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
  normal = normal.normalize();
  distance = -(p1.getX()*normal.getX() + p1.getY()*normal.getY() + p1.getZ()*normal.getZ());
}

BSPPolygon::BSPPolygon(Point p1, Point p2, Point p3, Point t_p1, Point t_p2, Point t_p3, SceneObject* obj):
  beenDivider(false), p1(p1), p2(p2), p3(p3), object(obj), tp1(t_p1), tp2(t_p2), tp3(t_p3) {
  normal = PositionVector(-1*Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
  normal = normal.normalize();
  distance = -(p1.getX()*normal.getX() + p1.getY()*normal.getY() + p1.getZ()*normal.getZ());
}*/


BSPPolygon::BSPPolygon(vector<Point> points, SceneObject* obj):
  beenDivider(false), vertices(points), object(obj) {
  if(points.size() < 3) {
    cout << "ERROR: Atleast three vertices are needed to create a BSPPolygon!" << endl;
    return;
  }
  normal = PositionVector(-1*Cross(PositionVector(vertices[0]-vertices[1]),
				   PositionVector(vertices[1]-vertices[2])));
  normal = normal.normalize();
  distance = -(vertices[0].getX()*normal.getX() +
	       vertices[0].getY()*normal.getY() +
	       vertices[0].getZ()*normal.getZ());
  t_vertices = vector<Point>(vertices.size());
  for(int i = 0; i < t_vertices.size(); i++) {
    t_vertices[i] = Point(0,0,0);
  }
}

BSPPolygon::BSPPolygon(vector<Point> points, vector<Point> texturePoints, SceneObject* obj):
  beenDivider(false), vertices(points), t_vertices(texturePoints), object(obj) {
  if(points.size() < 3) {
    cout << "ERROR: Atleast three vertices are needed to create a BSPPolygon!" << endl;
    return;
  }
  normal = PositionVector(-1*Cross(PositionVector(vertices[0]-vertices[1]),
				   PositionVector(vertices[1]-vertices[2])));
  normal = normal.normalize();
  distance = -(vertices[0].getX()*normal.getX() +
	       vertices[0].getY()*normal.getY() +
	       vertices[0].getZ()*normal.getZ());
}

BSPPolygon::~BSPPolygon() {
  //  cout << "Polygon Deleted" << endl;
}

//int BSPPolygon::last_material = 0;

void BSPPolygon::split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back) {
  vector<Point> outpts, t_outpts;
  vector<Point> inpts, t_inpts;
  Point ptA, ptB;
  Point tptA, tptB;
  int count = vertices.size();
  double sideA, sideB;
  ptA = vertices[count-1];
  tptA = t_vertices[count-1];
  sideA = divider.classifyPoint(ptA);
  for(int i = -1; ++i < count;) {

    ptB = vertices[i];
    tptB = t_vertices[i];
    sideB = divider.classifyPoint(ptB);
    if (sideB > 0) {
      if(sideA < 0) {
	PositionVector v(ptB - ptA);
	PositionVector tv(tptB - tptA);
	double sect = - sideA / Dot(divider.normal, v);
	outpts.push_back(ptA + Point(v*sect));
	inpts.push_back(ptA + Point(v*sect));
	t_outpts.push_back(tptA + Point(tv*sect));
	t_inpts.push_back(tptA + Point(tv*sect));
      }
      outpts.push_back(ptB);
      t_outpts.push_back(tptB);
    }
    else if(sideB < 0) {
      if (sideA > 0) {
	PositionVector v(ptB - ptA);
	PositionVector tv(tptB - tptA);
	double sect = - sideA / Dot(divider.normal, v);
	outpts.push_back(ptA + Point(v*sect));
	inpts.push_back(ptA + Point(v*sect));
	t_outpts.push_back(tptA + Point(tv*sect));
	t_inpts.push_back(tptA + Point(tv*sect));
      }
      inpts.push_back(ptB);
      t_inpts.push_back(tptB);
    }
    else {
      outpts.push_back(ptB);
      t_outpts.push_back(tptB);
      inpts.push_back(ptB);
      t_inpts.push_back(tptB);
    }
    ptA = ptB;
    tptA = tptB;
    sideA = sideB;
  }    
  BSPPolygon *poly = new BSPPolygon(outpts, t_outpts, object);
  front->addPolygon(poly);
  poly = new BSPPolygon(inpts, t_inpts,	object);
  back->addPolygon(poly);
  //cout << "vertices: " << vertices.size() << endl;
  //cout << "front:    " << outpts.size() << endl;
  //cout << "back:     " << inpts.size() << endl;
}

// Splits a triangle polygon to a three smaller polygons based on the dividing polygon.
/*void BSPPolygon::split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back)  {
  const double sideA = divider.classifyPoint(p1);
  const double sideB = divider.classifyPoint(p2);
  const double sideC = divider.classifyPoint(p3);

  //cout << "split" << endl;
 
  if(sideB >= 0 && sideC >= 0) {
    //cout << "1" << endl;
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
    //cout << "2" << endl;
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
    //cout << "3" << endl;
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
    //cout << "4" << endl;
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
    //    cout << "5" << endl;
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
    //cout << "6" << endl;
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
*/


double BSPPolygon::classifyPoint(const Point& point) const {
  double EPSILON = 0.0001;
  double sideValue = normal.getX() * point.getX() +
    normal.getY() * point.getY() +
    normal.getZ() * point.getZ();
  if(abs(sideValue + distance) < EPSILON)
    return 0;
  else 
    return sideValue + distance;
}

bool BSPPolygon::infront(const BSPPolygon& polygon) const {
  if(calculateSide(polygon) == INFRONT)
    return true;
  else 
    return false;
}

/*int BSPPolygon::calculateSide(const BSPPolygon& polygon) const {
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
    }*/


int BSPPolygon::calculateSide(const BSPPolygon& polygon) const {
  int numPositive = 0;
  int numNegative = 0;


  for(int i = 0; i < polygon.vertices.size() ; i++) {
    double cp = classifyPoint(polygon.vertices[i]);
    if(cp > 0)
      numPositive += 1;
    else if (cp < 0)
      numNegative += 1;
  }
  if(numPositive > 0 && numNegative == 0)
    return INFRONT;
  else if(numPositive == 0 && numNegative > 0)
    return BEHIND;
  else if(numPositive == 0 && numNegative == 0)
    return COINCIDING;
  else
    return SPANNING;
}

/*inline void BSPPolygon::drawPolygon() const {
  glNormal3f(normal.getX(), normal.getY(), normal.getZ());
  glTexCoord2f(tp1.getX(), tp1.getY());  glVertex3f(p1.getX(), p1.getY(), p1.getZ());
  glTexCoord2f(tp2.getX(), tp2.getY());  glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glTexCoord2f(tp3.getX(), tp3.getY());  glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  }*/


void BSPPolygon::drawPolygon() const {
  if(vertices.size() == 3)
    glBegin(GL_TRIANGLES);
  else if(vertices.size() == 4)
    glBegin(GL_QUADS);
  else
    glBegin(GL_POLYGON);
  glNormal3f(normal.getX(), normal.getY(), normal.getZ());
  for(int i = 0; i < vertices.size(); i++) {
    glTexCoord2f(t_vertices[i].getX(), t_vertices[i].getY());
    glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
  }
  glEnd();
  //cout << "size:" << vertices.size() << endl;
}
	


bool BSPPolygon::hasBeenDivider() const {
  return beenDivider;
}

void BSPPolygon::setDivider() {
  beenDivider = true;
}

int BSPPolygon::getObjectId() const {
  return object->getId();
}

SceneObject* BSPPolygon::getSceneObject() const{
  return object;
}

inline bool operator < (const BSPPolygon& polygon1, const BSPPolygon& polygon2) {
  if(polygon1.object->getId() <= polygon2.object->getId())
    return true;
  else 
    return false;
}

vector<Point> BSPPolygon::getVertices() const {
  return vertices;
}

BSPPolygonSet::~BSPPolygonSet() {
  for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
    delete *i;
    polygons.erase(i);
  }
  for(list<SceneObjectComponent*>::iterator i = components.begin(); i != components.end(); i++) {
    delete *i;
    components.erase(i);
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



void BSPPolygonSet::addPolygons(BSPPolygonSet *polys) {
  //cout << "size:" << polys->size() << endl;
  while(!polys->isEmpty()) {
    addPolygon(polys->getPolygon());
  }
  //cout << "size:" << polys->size() << endl;
}

BSPPolygon* BSPPolygonSet::getPolygon() {
  BSPPolygon *poly = polygons.front();
  polygons.pop_front();
  return poly;
}

BSPPolygon* BSPPolygonSet::chooseDivider() {
  // IMPLEMENT BETTER CHOOSING OF THE DIVIDING POLYGON
  BSPPolygon* poly = getPolygon();
  poly->setDivider();
  return poly;
  
  if(isConvexSet())
    return NULL;
  //double minRelation = MINIMUMRELATION;
  double minRelation = 0.3;
  BSPPolygon* bestPolygon = NULL;
  //  int leastSplits = infinity;
  int leastSplits = 1000000000;
  double bestRelation = 0;
  int loop = 0;
  while(bestPolygon == NULL) {
    loop++;
    //  cout << "try " << loop << endl;
    for(list<BSPPolygon*>::const_iterator i = polygons.begin(); i != polygons.end();i++) {
      if(!(**i).hasBeenDivider()) {
	int numPositive = 1;
	int numNegative = 1;
	int numSpanning = 0;
	int value;
	double relation;

	for(list<BSPPolygon*>::const_iterator j = polygons.begin(); j != polygons.end(); j++) {
	  if(distance(i, j) != 0) { 
	    value = (**i).calculateSide(**j);
	    if(value == BSPPolygon::INFRONT)
	      numPositive++;
	    else if(value == BSPPolygon::BEHIND)
	      numNegative++;
	    else if(value == BSPPolygon::SPANNING) 
	      numSpanning++;
	    /*	    else if(value == BSPPolygon::COINCIDING) {
	      numCoinciding++;
	      cout << "COINCIDING" << endl;
	      }*/
	  }
	}
	if(numPositive < numNegative)
	  relation = (double)numPositive / (double)numNegative;
	else
	  relation = (double)numNegative / (double)numPositive;
	//	cout << "size: " << polygons.size() << endl;
	//cout << "relation: " << relation << endl;
	//eeeeeee	cout << numPositive << " " << numNegative << " " << numCoinciding << " " << numSpanning << endl;
	if(relation > minRelation && (numSpanning < leastSplits || 
				      numSpanning == leastSplits && relation > bestRelation)) {
	  /* bestPolygon = *i;
	  polygons.remove(*i);
	  if(bestPolygon != NULL)
	  polygons.push_back(bestPolygon);*/
	  bestPolygon = *i;
	  leastSplits = numSpanning;
	  bestRelation = relation;
	}
      }
    }

    //    cout << "minRelation: " << minRelation << endl;
    //minRelation = minRelation / MINRELATIONSCALE;
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
  if(components.size() == 0 && polygons.size() > 0) {
    int dlist;
    SceneObject* object;
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
	   //glBegin(GL_TRIANGLES);
	   while(i != polygons.end() && current_id == (**i).getObjectId()) {
	     (**i).drawPolygon();
	     if(!(**i).hasBeenDivider())
	       delete (*i);
	     polygons.erase(i);
	     i++;
	   }
	   i--;
	   //glEnd();
	   glEndList();
	   components.push_back(new SceneObjectComponent(object, dlist));
	   comps++;
	}
      }
    }
    //polygons.clear();

    //cout << "components:" << comps << endl;
  }
  else {
    for(list<SceneObjectComponent*>::iterator i = components.begin(); i != components.end(); i++) {
      (**i).drawComponent();
    }
  }
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

void BSPPolygonSet::removeHiddenPolygons(list<CylinderVolume>* cylinders) {
  //  cout << "cylinders: " << cylinders->size() << endl;
  int count = 0;
  int size = polygons.size();
  int numBorder, numInside;
  int t_i = 0;
  int t_b = 0;
  int t_o = 0;
  bool deleted, isOutside;
  list<BSPPolygon*>::iterator i = polygons.begin();
  while(i != polygons.end()) {
    //  for (list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
    deleted = false;
    vector<Point> vertices = (**i).getVertices();
    count++;
    for (list<CylinderVolume>::iterator j = cylinders->begin(); j != cylinders->end(); j++) {
      numInside = numBorder = 0;
      isOutside = false;
      for(int k = 0; k < vertices.size(); k++) {
	int result = (*j).isPointInside(vertices[k]);
	if(result == -1) {
	  isOutside = true;
	  t_o++;
	  break;
	}
	else if(result == 1) {
	  numInside++;
	  t_i++;
	}
	else if(result == 0) {
	  numBorder++;
	  t_b++;
	}
      }
      //if(isOutside)
	//cout << "is outside" << endl;
	//cout << "inside: " << numInside << endl;
	//cout << "border: " << numBorder << endl;
      if(!isOutside && numInside > 0) {
	//cout << "DELETED!" << endl;
	if(!(**i).hasBeenDivider()) 
	  delete (*i);
	i = polygons.erase(i);
	//	cout << "DELETE ENDS!" << endl;
	//i++;
	deleted = true;
	break;
      }
    }
    if(deleted)
      continue;
    else
      i++;
  }
  //cout << "total outside: " << t_o << endl;
  //cout << "total inside: " << t_i << endl;
  //cout << "total border: " << t_b << endl;
  if(count != size)
    cout << "ERROR" << endl;
}
