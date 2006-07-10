#include <BSPPolygon.h>
#include <list>
#include <QtOpenGL>
#include <cstdlib>
#include <SceneObject.h>

using namespace std;
using namespace cxxadt;

/*BSPPolygonMaterial::BSPPolygonMaterial(GLfloat* materials) {
  ambient[0] = materials[0];
  ambient[1] = materials[1];
  ambient[2] = materials[2];
  ambient[3] = materials[3];
  diffuse[0] = materials[4];
  diffuse[1] = materials[5];
  diffuse[2] = materials[6];
  diffuse[3] = materials[7];
  specular[0] = materials[8];
  specular[1] = materials[9];
  specular[2] = materials[10];
  specular[3] = materials[11];
  shine[0] = materials[12];
  
  n_materials++;
  id = n_materials;
}

int BSPPolygonMaterial::n_materials = 0;

inline void BSPPolygonMaterial::setMaterial() {
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shine);
  
}



inline int BSPPolygonMaterial::getId() {
  return id;
}*/

BSPPolygon::BSPPolygon(Point p1, Point p2, Point p3, PositionVector *norm, SceneObject* obj):
  beenDivider(false), p1(p1), p2(p2), p3(p3), normal(norm), object(obj) {
  if(normal == NULL) {
    normal = new PositionVector(-1*Cross(PositionVector(p1-p2), PositionVector(p2-p3)));
    normal = &normal->normalize();
  }
  distance = -(p1.getX()*normal->getX() + p1.getY()*normal->getY() + p1.getZ()*normal->getZ());
}

//int BSPPolygon::last_material = 0;

// Splits a triangle polygon to a three smaller polygons based on the dividing polygon.
void BSPPolygon::split(BSPPolygon& divider, BSPPolygonSet *front, BSPPolygonSet *back) {
  //front = new BSPPolygonSet();
  //back = new BSPPolygonSet();

  double sideA = divider.classifyPoint(p1);
  double sideB = divider.classifyPoint(p2);
  double sideC = divider.classifyPoint(p3);

  //cout << "split" << endl;
 
  if(sideB >= 0 && sideC >= 0) {
    //cout << "1" << endl;
    PositionVector v1(p2 - p1);
    PositionVector v2(p3 - p1);
    double sect1 = - sideA / Dot(*divider.normal, v1);
    double sect2 = - sideA / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p1, p1 + Point(v1*sect1), p1 + Point(v2*sect2), normal, object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v1*sect1), p2, p1 + Point(v2*sect2), normal, object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v2*sect2), p2, p3, normal, object);
    front->addPolygon(poly);
  }

  else if(sideB <= 0 && sideC <= 0) {
    //cout << "2" << endl;
    PositionVector v1(p2 - p1);
    PositionVector v2(p3 - p1);
    double sect1 = - sideA / Dot(*divider.normal, v1);
    double sect2 = - sideA / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p1, p1 + Point(v1*sect1), p1 + Point(v2*sect2), normal, object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v1*sect1), p2, p1 + Point(v2*sect2), normal, object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p1 + Point(v2*sect2), p2, p3, normal, object);
    back->addPolygon(poly);
  }

  else if(sideA >= 0 && sideB >= 0) {
    //cout << "3" << endl;
    PositionVector v1(p1 - p3);
    PositionVector v2(p2 - p3);
    double sect1 = - sideC / Dot(*divider.normal, v1);
    double sect2 = - sideC / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p3, p3 + Point(v1*sect1), p3 + Point(v2*sect2), normal, object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v1*sect1), p1, p3 + Point(v2*sect2), normal, object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v2*sect2), p1, p2, normal, object);
    front->addPolygon(poly);
  }

  else if(sideA <= 0 && sideB <= 0) {
    //cout << "4" << endl;
    PositionVector v1(p1 - p3);
    PositionVector v2(p2 - p3);
    double sect1 = - sideC / Dot(*divider.normal, v1);
    double sect2 = - sideC / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p3, p3 + Point(v1*sect1), p3 + Point(v2*sect2), normal, object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v1*sect1), p1, p3 + Point(v2*sect2), normal, object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p3 + Point(v2*sect2), p1, p2, normal,object);
    back->addPolygon(poly);
  }

  else if(sideA >= 0 && sideC >= 0) {
    //    cout << "5" << endl;
    PositionVector v1(p1 - p2);
    PositionVector v2(p3 - p2);
    double sect1 = - sideB / Dot(*divider.normal, v1);
    double sect2 = - sideB / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p2, p2 + Point(v2*sect2), p2 + Point(v1*sect1), normal, object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p2 + Point(v2*sect2), p3, normal, object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p3, p1, normal, object);
    front->addPolygon(poly);
  }

  else if(sideA <= 0 && sideC <= 0) {
    //cout << "6" << endl;
    PositionVector v1(p1 - p2);
    PositionVector v2(p3 - p2);
    double sect1 = - sideB / Dot(*divider.normal, v1);
    double sect2 = - sideB / Dot(*divider.normal, v2);
    BSPPolygon *poly = new BSPPolygon(p2, p2 + Point(v2*sect2), p2 + Point(v1*sect1), normal, object);
    front->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p2 + Point(v2*sect2), p3, normal, object);
    back->addPolygon(poly);
    poly = new BSPPolygon(p2 + Point(v1*sect1), p3, p1, normal, object);
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
  if(abs(sideValue + distance) < EPSILON)
    return 0;
  else 
    return sideValue + distance;
  /*if(sideValue == distance)
    return COINCIDING;
  else if(sideValue < distance)
    return BEHIND;
  else
  return INFRONT;*/
  
}

bool BSPPolygon::infront(BSPPolygon polygon) {
  /*if((classifyPoint(polygon.p1) < 0) ||
     (classifyPoint(polygon.p2) < 0) ||
     (classifyPoint(polygon.p3) < 0))
    return false;
    return true;*/
  if(calculateSide(polygon) == INFRONT)
    return true;
  else 
    return false;
  

}

int BSPPolygon::calculateSide(BSPPolygon polygon) {
  int numPositive = 0;
  int numNegative = 0;
  
  double cp1 = classifyPoint(polygon.p1);
  double cp2 = classifyPoint(polygon.p2);
  double cp3 = classifyPoint(polygon.p3);

  /*cout << "cp1:" << cp1 << endl;
  cout << "cp2:" << cp2 << endl;
  cout << "cp3:" << cp3 << endl;*/
  
  /*  if(abs(cp1) < EPSILON)
    cp1 = 0;
  if(abs(cp2) < EPSILON)
    cp2 = 0;
  if(abs(cp3) < EPSILON)
  cp3 = 0;*/
  
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
      /*    cout << "p1: " << p1.getX() << " " << p1.getY() << " " << p1.getZ() << endl;
      cout << "p2: " << p2.getX() << " " << p2.getY() << " " << p2.getZ() << endl;
      cout << "p3: " << p3.getX() << " " << p3.getY() << " " << p3.getZ() << endl;
      cout << "polygon.p1: " << polygon.p1.getX() << " " << polygon.p1.getY() << " " << polygon.p1.getZ() << endl;
      cout << "polygon.p2: " << polygon.p2.getX() << " " << polygon.p2.getY() << " " << polygon.p2.getZ() << endl;
      cout << "polygon.p3: " << polygon.p3.getX() << " " << polygon.p3.getY() << " " << polygon.p3.getZ() << endl;*/
      return SPANNING;
    }
}

inline void BSPPolygon::drawPolygon() {
  //glBegin(GL_TRIANGLES);
  //  glColor3f(p1.getX()/2, p1.getY()/2, -p1.getZ()/2); 
  //cout << p1.getX() << " " << p1.getY() << " " << p1.getZ() << endl;;
  //cout << p2.getX() << " " << p2.getY() << " " << p2.getZ() << endl;;
  //cout << p3.getX() << " " << p3.getY() << " " << p3.getZ() << endl;;
  /*  if(last_material != material->getId()) {
    material->setMaterial();
    last_material = material->getId();
    }*/
  glNormal3f(normal->getX(), normal->getY(), normal->getZ());
  glVertex3f(p1.getX(), p1.getY(), p1.getZ());
  glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  //glEnd();
}

bool BSPPolygon::hasBeenDivider() {
  return beenDivider;
}

void BSPPolygon::setDivider() {
  beenDivider = true;
}

int BSPPolygon::getObjectId() {
  return object->getId();
}

SceneObject* BSPPolygon::getSceneObject() {
  return object;
}

inline bool operator < (const BSPPolygon& polygon1, const BSPPolygon& polygon2) {
  if(polygon1.object->getId() <= polygon2.object->getId())
    return true;
  else 
    return false;
}

/*void BSPPolygon::setMaterial(BSPPolygonMaterial* mat) {
  material = mat;
  }*/

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
  //   return getPolygon();
  
  if(isConvexSet())
    return NULL;
  double minRelation = MINIMUMRELATION;
  BSPPolygon* bestPolygon = NULL;
  int leastSplits = INFINITY;
  double bestRelation = 0;
  int loop = 0;
  while(bestPolygon == NULL) {
    loop++;
    //  cout << "try " << loop << endl;
    for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end();i++) {
      if(!(**i).hasBeenDivider()) {
	int numPositive = 1;
	int numNegative = 1;
	int numSpanning = 0;
	int value;
	double relation;

	for(list<BSPPolygon*>::iterator j = polygons.begin(); j != polygons.end(); j++) {
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
    minRelation = minRelation / MINRELATIONSCALE;
  }
  
  //  if(bestPolygon == NULL) 
  //  cout << "NULL" << endl;

  if(bestPolygon != NULL) {
    bestPolygon->setDivider();
    //    polygons.remove(bestPolygon);
  }
  return bestPolygon;
    
}

bool BSPPolygonSet::isEmpty() {
  return polygons.empty();
}

void BSPPolygonSet::sort() {
  polygons.sort();
}

void BSPPolygonSet::drawPolygons() {
  //  cout << "drawPolygons" << endl;
  /*  if(!dlist_initialized) {
    //    polygons.sort();
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
    }*/
  
  /*
  glBegin(GL_TRIANGLES);
  for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
    (**i).drawPolygon();
  }
  glEnd();
  */

  if(components.size() == 0 && polygons.size() > 0) {
    int dlist;
    SceneObject* object;
    polygons.sort();
    int current_id = -1;
    
    
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
	     i++;
	   }
	   i--;
	   glEnd();
	   glEndList();
	   components.push_back(new SceneObjectComponent(object, dlist));
	}
      }
    }
  }
  else {
    for(list<SceneObjectComponent*>::iterator i = components.begin(); i != components.end(); i++) {
      (**i).drawComponent();
    }
  }
}

int BSPPolygonSet::size() {
  return polygons.size();
}

/*void BSPPolygonSet::applyMaterial(BSPPolygonMaterial* material) {
  for(list<BSPPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++) {
  (**i).setMaterial(material);
  }
  }*/
