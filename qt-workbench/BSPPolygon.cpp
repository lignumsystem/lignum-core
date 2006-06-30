#include <BSPPolygon.h>
#include <list>
#include <QtOpenGL>

using namespace std;
using namespace cxxadt;

BSPPolygon::BSPPolygon(Point p1, Point p2, Point p3, PositionVector *norm):
  hasBeenDivider(false), p1(p1), p2(p2), p3(p3), normal(norm) {
  if(normal == NULL) {
    normal = new PositionVector(Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
    normal = &normal->normalize();
  }
  distance = -(p1.getX()*normal->getX() + p1.getY()*normal->getY() + p1.getZ()*normal->getZ());
}

// Splits a triangle polygon to a three smaller polygons based on the dividing polygon.
void BSPPolygon::split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back) {
  //front = new BSPPolygonSet();
  //back = new BSPPolygonSet();

  double sideA = divider.classifyPoint(p1);
  double sideB = divider.classifyPoint(p2);
  double sideC = divider.classifyPoint(p3);

  //cout << "split" << endl;
 
  if(sideB >= 0 && sideC >= 0) {
    //   cout << "1" << endl;
    PositionVector v1(p2 - p1);
    PositionVector v2(p3 - p1);
    double sect1 = - sideA / Dot(*divider.normal, v1);
    double sect2 = - sideA / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p1, p1 + Point(v1*sect1), p1 + Point(v2*sect2), normal);
    back->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v1*sect1), p2, p1 + Point(v2*sect2), normal);
    front->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v2*sect2), p2, p3, normal);
    front->addPolygon(poly);
  }

  else if(sideB <= 0 && sideC <= 0) {
    //  cout << "2" << endl;
    PositionVector v1(p2 - p1);
    PositionVector v2(p3 - p1);
    double sect1 = - sideA / Dot(*divider.normal, v1);
    double sect2 = - sideA / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p1, p1 + Point(v1*sect1), p1 + Point(v2*sect2), normal);
    front->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v1*sect1), p2, p1 + Point(v2*sect2), normal);
    back->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v2*sect2), p2, p3, normal);
    back->addPolygon(poly);
  }

  else if(sideA >= 0 && sideB >= 0) {
    //cout << "3" << endl;
    PositionVector v1(p1 - p3);
    PositionVector v2(p2 - p3);
    double sect1 = - sideC / Dot(*divider.normal, v1);
    double sect2 = - sideC / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p3, p3 + Point(v1*sect1), p3 + Point(v2*sect2), normal);
    back->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v1*sect1), p1, p3 + Point(v2*sect2), normal);
    front->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v2*sect2), p1, p2, normal);
    front->addPolygon(poly);
  }

  else if(sideA <= 0 && sideB <= 0) {
    //cout << "4" << endl;
    PositionVector v1(p1 - p3);
    PositionVector v2(p2 - p3);
    double sect1 = - sideC / Dot(*divider.normal, v1);
    double sect2 = - sideC / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p3, p3 + Point(v1*sect1), p3 + Point(v2*sect2), normal);
    front->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v1*sect1), p1, p3 + Point(v2*sect2), normal);
    back->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v2*sect2), p1, p2, normal);
    back->addPolygon(poly);
  }

  else if(sideA >= 0 && sideC >= 0) {
    //    cout << "5" << endl;
    PositionVector v1(p1 - p2);
    PositionVector v2(p3 - p2);
    double sect1 = - sideB / Dot(*divider.normal, v1);
    double sect2 = - sideB / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p2, p2 + Point(v1*sect1), p2 + Point(v2*sect2), normal);
    back->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p2 + Point(v2*sect2), p3, normal);
    front->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v2*sect2), p3, p1, normal);
    front->addPolygon(poly);
  }

  else if(sideA <= 0 && sideC <= 0) {
    //cout << "6" << endl;
    PositionVector v1(p1 - p2);
    PositionVector v2(p3 - p2);
    double sect1 = - sideB / Dot(*divider.normal, v1);
    double sect2 = - sideB / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p2, p2 + Point(v1*sect1), p2 + Point(v2*sect2), normal);
    front->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p2 + Point(v2*sect2), p3, normal);
    back->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v2*sect2), p3, p1, normal);
    back->addPolygon(poly);
  }
  //cout << "front:" << front->size() << endl;
  //cout << "back:" << back->size() << endl;
  //cout << "split end" << endl;
}

double BSPPolygon::classifyPoint(Point& point) {
  //  cout << "normal: " << normal->getX() << " " << normal->getY() << " " << normal->getZ() << endl;
  double sideValue = normal->getX() * point.getX() +
    normal->getY() * point.getY() +
    normal->getZ() * point.getZ();
  return sideValue + distance;
  /*if(sideValue == distance)
    return COINCIDING;
  else if(sideValue < distance)
    return BEHIND;
  else
  return INFRONT;*/
  
}

bool BSPPolygon::infront(BSPPolygon polygon) {
  if((classifyPoint(polygon.p1) <= 0) ||
     (classifyPoint(polygon.p2) <= 0) ||
     (classifyPoint(polygon.p3) <= 0))
    return false;
  return true;

}

int BSPPolygon::calculateSide(BSPPolygon polygon) {
  int numPositive = 0;
  int numNegative = 0;
  
  if(classifyPoint(polygon.p1) > 0)
    numPositive += 1;
  else if (classifyPoint(polygon.p1) < 0)
    numNegative += 1;

  if(classifyPoint(polygon.p2) > 0)
    numPositive += 1;
  else if (classifyPoint(polygon.p2) < 0)
    numNegative += 1;

  if(classifyPoint(polygon.p3) > 0)
    numPositive += 1;
  else if (classifyPoint(polygon.p3) < 0)
    numNegative += 1;  

  if(numPositive > 0 && numNegative == 0)
    return INFRONT;
  else if(numPositive == 0 && numNegative > 0)
    return BEHIND;
  else if(numPositive == 0 && numNegative == 0)
    return COINCIDING;
  else
    return SPANNING;
}

void BSPPolygon::drawPolygon() {
  //glBegin(GL_TRIANGLES);
  //  glColor3f(p1.getX()/2, p1.getY()/2, -p1.getZ()/2); 
  //cout << p1.getX() << " " << p1.getY() << " " << p1.getZ() << endl;;
  //cout << p2.getX() << " " << p2.getY() << " " << p2.getZ() << endl;;
  //cout << p3.getX() << " " << p3.getY() << " " << p3.getZ() << endl;;
  glVertex3f(p1.getX(), p1.getY(), p1.getZ());
  glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  //glEnd();
}

bool BSPPolygon::hasBeenDivisor() {
  return hasBeenDivisor;
}

void BSPPolygon::setDivisor() {
  hasBeenDivisor = true;
}

bool BSPPolygonSet::isConvexSet() {
  /*int count = polygons.size();

  for(int i = 0; i < count ; i++) {
    for(int j = 0; j < count; j++) {
      if(i != j && !polygons[i].infront(polygons[j]))
	return false;
    }
    }*/

  for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
    for(list<BSPPolygon*>::iterator j = polygons.begin(); j != polygons.end(); j++) {
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
  //return getPolygon();
  if(isConvexSet())
    return NULL;
  double minRelation = MINIMUMRELATION;
  BSPPolygon* bestPolygon = NULL;
  int leastSplits = INFINITY;
  double bestRelation = 0;

  while(bestPolygon == NULL) {
    for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
      if(!(**i).hasBeenDivisor()) {
	int numPositive = 0;
	int numNegatice = 0;
	int numSpanning = 0;
	int value;
	double relation;

	for(list<BSPPolygon*>::iterator j = polygons.begin(); j != polygons.end(); j++) {
	  if(distance(i, j) != 0) { 
	    value = (**i).calculateSide(**j);
	    if(value == BSPPolygon::INFRONT)
	      numPositive++;
	    else if(value == BSPPolygon::BEHIND)
	      numNegativa++;
	    else if(value == BSPPolygon::SPANNING)
	      numSpanning++;
	  }
	}
	if(numPositive < numNegative)
	  relation = numPositive / numNegative;
	else
	  relation = numNegative / numPositive;

	if(relation > minRelation && (numSpanning < leastSplits || 
				      numSpanning == leastSplits && relation > bestRelation)) {
	  bestPolygon = *i;
	  leastSplits = numSpanning;
	  bestRelation = relation;
	}
      }
    }
    minRelation = minRelation / MINRELATIONSCALE;
  }
  
  if(bestPolygon != NULL)
    bestPolygon->setDivisor();
  return bestPolygon;
}

bool BSPPolygonSet::isEmpty() {
  return polygons.empty();
}

void BSPPolygonSet::drawPolygons() {
  //  cout << "drawPolygons" << endl;
  if(!dlist_initialized) {
    dlist=glGenLists(1);
    if(dlist != 0) {
      glNewList(dlist, GL_COMPILE);
         glBegin(GL_TRIANGLES);
         for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
             (**i).drawPolygon();
         }
         glEnd();
      glEndList();
    }
    dlist_initialized = true;
  }
  else {
    glCallList(dlist);
  }
}

int BSPPolygonSet::size() {
  return polygons.size();
}
