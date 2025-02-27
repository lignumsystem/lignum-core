#include <LGMPolygonDomBuilder.h>
#include <Lignum.h>
#include <Point.h>
#include <PositionVector.h>


using namespace cxxadt;
using namespace Lignum;

LGMPolygonDomBuilder::LGMPolygonDomBuilder() :
  sceneObjects(NULL)
{
}

QMultiHash<int, SceneObject*>* LGMPolygonDomBuilder::getSceneObjects() {
  return sceneObjects;
} 

PositionVector LGMPolygonDomBuilder::getAxis(const QDomDocument& doc) {
  QDomElement root = doc.documentElement();
  if(root.tagName() == QString("Tree")) {
    QDomElement child = root.firstChildElement();
    while(!child.isNull()) {     
      if(child.tagName() == "Axis") {
	QDomElement child2 = child.firstChildElement();
	while(!child2.isNull()) {
	  if(child2.tagName() == "AxisAttributes") {
	    QDomElement child3 = child2.firstChildElement();
	    while(!child3.isNull()) {
	      if(child3.tagName() == "direction") {
		return PositionVector(child3.text().section(' ', 0, 0).toDouble(),
				      child3.text().section(' ', 1, 1).toDouble(),
				      child3.text().section(' ', 2, 2).toDouble());
	      }
	      child3 = child3.nextSiblingElement();
	    }
	  }
	  child2 = child2.nextSiblingElement();
	}
      }
      child = child.nextSiblingElement();
    }
  }
  else
    return PositionVector(0,0,1);
}

Point LGMPolygonDomBuilder::getPoint(const QDomDocument& doc) {
  QDomElement root = doc.documentElement();
  if(root.tagName() == QString("Tree")) {
    QDomElement child = root.firstChildElement();
    while(!child.isNull()) {
      if(child.tagName() == "TreeAttributes") {
	QDomElement child2 = child.firstChildElement();
	while(!child2.isNull()) {
	  if(child2.tagName() == "point") {
	    return Point(child2.text().section(' ', 0, 0).toDouble(),
			 child2.text().section(' ', 1, 1).toDouble(),
			 child2.text().section(' ', 2, 2).toDouble());
	  }
	  child2 = child2.nextSiblingElement();
	}
      }
      child = child.nextSiblingElement();
    }
  }
  else
    return Point(0,0,0);
}

double LGMPolygonDomBuilder::getHeight(const QDomDocument& doc) {
  QDomElement root = doc.documentElement();
  if(root.tagName() == QString("Tree")) {
    QDomElement child = root.firstChildElement();
    while(!child.isNull()) {
      if(child.tagName() == "TreeAttributes") {
	QDomElement child2 = child.firstChildElement();
	while(!child2.isNull()) {
	  if(child2.tagName() == "LGAH") {
	    return child2.text().toDouble();
	  }
	  child2 = child2.nextSiblingElement();
	}
      }
      child = child.nextSiblingElement();
    }
  }
  else 
    return 1;
}

BSPPolygonSet* LGMPolygonDomBuilder::createPolygons(const QDomDocument& doc, const VisualizationParameters& parameters) {
  BSPPolygonSet *polygons = new BSPPolygonSet();
  QDomElement root = doc.documentElement();
  sceneObjects = new QMultiHash<int, SceneObject*>;

  if(root.tagName() == QString("Tree"))
    parseTreeElement(root, parameters, polygons);
  
  return polygons;
}

void LGMPolygonDomBuilder::parseTreeElement(const QDomElement& element, const VisualizationParameters& parameters,
					    BSPPolygonSet* polygons)
{
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "Axis") {
      parseAxisElement(child, parameters, polygons);
    }
    child = child.nextSiblingElement();
  }
}

void LGMPolygonDomBuilder::parseAxisElement(const QDomElement& element, const VisualizationParameters& parameters,
						   BSPPolygonSet* polygons)
{
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeSegment") {
      parseTreeSegmentElement(child, parameters, polygons);
    }
    else if(child.tagName() == "BranchingPoint") {
      parseBranchingPointElement(child, parameters, polygons);
    }
    else if(child.tagName() == "Bud") {
      parseBudElement(child, parameters, polygons);
    }
    child = child.nextSiblingElement();
  }
}

void LGMPolygonDomBuilder::parseTreeSegmentElement(const QDomElement& element, const VisualizationParameters& parameters,
						   BSPPolygonSet* polygons)
{
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeSegmentAttributes") {
      QDomElement child2 = child.firstChildElement();
      double foliage_height = 0.0;
      double radius=0.0;
      double radius_top=0.0;
      double length=0.0;
      double x, y, z;x=y=z=0.0;
      Point point;
      PositionVector direction;
      BSPPolygonMaterial *secondary = NULL;
      int object_index = element.attribute("ObjectIndex").toInt();
      
      while(!child2.isNull()) {
	if (child2.tagName() == "LGAHf"){
	  foliage_height = child2.text().toDouble();
	}
	if(child2.tagName() == "LGAR") {
	  radius = child2.text().toDouble();
	}
	else if (child2.tagName() == "LGARTop") {
	  radius_top =  child2.text().toDouble();
	}
	else if(child2.tagName() == "LGAL") {
	  length = child2.text().toDouble();
	}
	else if(child2.tagName() == "point") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  point = Point(x, y, z);
	}
	else if(child2.tagName() == "direction") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  direction = PositionVector(x, y, z);
	}
	else if(child2.tagName() == "LGAtype") {
	  int value = child2.text().toInt();
	  if(value == 0)
	    secondary = parameters.getDominantMaterial();
	  else if(value == 1)
	    secondary = parameters.getNondominantMaterial();
	  else if(value == 2)
	    secondary = parameters.getShootMaterial();
	  else if(value == 3)
	    secondary = parameters.getShootAboveMaterial();  
	}
	else if(child2.tagName() == "LGAWf") {
	  double f_mass = child2.text().toDouble();
	  if(f_mass > R_EPSILON) {
	    SceneObject *object = new SceneObject(parameters.getMaterial(), object_index,
						  parameters.getFoliageTexture(), parameters.useBSP());
	    sceneObjects->insert(object_index, object);
	    BSPPolygonSet* foliage = makeFoliage(radius, length, point, direction, parameters.getFoliageDetail(),
						 parameters.getSegmentRDetail(), foliage_height, 
						 parameters.getFoliageSpacing(), object);
	    polygons->addPolygons(foliage);
	    delete foliage;
	  }
	}
	child2 = child2.nextSiblingElement();
      }
      SceneObject* object = new SceneObject(parameters.getMaterial(), secondary, object_index, parameters.getSegmentTexture(), false);
      sceneObjects->insert(object_index, object);
      BSPPolygonSet* cyl = makeCylinder(radius, radius_top,length, Point(point.getX(), point.getY(), point.getZ()),
				      PositionVector(direction.getX(), direction.getY(), direction.getZ()),
				      true, true, object,
				      parameters.getSegmentRDetail(), parameters.getSegmentHDetail());
      polygons->addPolygons(cyl);
      delete cyl;
    }
    else if(child.tagName() == "BroadLeaf" && parameters.useLeaves()) {
      parseBroadLeafElement(child, parameters, polygons);
    }

    child = child.nextSiblingElement();
  }
}

void LGMPolygonDomBuilder::parseBranchingPointElement(const QDomElement& element, const VisualizationParameters& parameters,
						      BSPPolygonSet* polygons)
{
  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "Axis") {
      parseAxisElement(child, parameters, polygons);
    }
    child = child.nextSiblingElement();
  }
}
void LGMPolygonDomBuilder::parseBudElement(const QDomElement& element, const VisualizationParameters& parameters,
					   BSPPolygonSet* polygons)
{
  if(parameters.useBuds()) {
    QDomElement child = element.firstChildElement();
    while (!child.isNull()) {
      if(child.tagName() == "BudAttributes") {
	QDomElement child2 = child.firstChildElement();
	double x, y, z;
	Point point;
	PositionVector direction;
	BSPPolygonMaterial *primary = NULL;
	BSPPolygonMaterial *secondary = NULL;
	int object_index = element.attribute(QString("ObjectIndex")).toInt();

	
	while(!child2.isNull()) {
	  if(child2.tagName() == "point") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    point = Point(x, y, z);
	  }
	  else if(child2.tagName() == "direction") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    direction = PositionVector(x, y, z);
	  }
	  else if(child2.tagName() == "LGAstate") {
	    int value = child2.text().toInt();
	    if(value == ALIVE)
	      primary = parameters.getBudAliveMaterial();
	    else if(value == DEAD)
	      primary = parameters.getBudDeadMaterial();
	    else if(value == DORMANT)
	      primary = parameters.getBudDormantMaterial();
	    else if(value == FLOWER)
	      primary = parameters.getBudFlowerMaterial();
	    else
	      primary = parameters.getMaterial();
	  }
	  else if(child2.tagName() == "LGAtype") {
	    int value = child2.text().toInt();
	    if(value == 0)
	      secondary = parameters.getDominantMaterial();
	    else if(value == 1)
	      secondary = parameters.getNondominantMaterial();
	    else if(value == 2)
	      secondary = parameters.getShootMaterial();
	    else if(value == 3)
	      secondary = parameters.getShootAboveMaterial();  
	  }
	  child2 = child2.nextSiblingElement();
	}
	SceneObject *object = new SceneObject(primary, secondary, object_index, 0, false);
	sceneObjects->insert(object_index, object);
	
	BSPPolygonSet* budi = makeBud(point, direction, parameters.getBudLoDetail(),
				      parameters.getBudLaDetail(), parameters.getBudSize(), object);
	polygons->addPolygons(budi);
	delete budi;

      }
      else if(child.tagName() == "BroadLeaf") {
	parseBroadLeafElement(child, parameters, polygons);
      }
      
      child = child.nextSiblingElement();
    }
  }
}

void LGMPolygonDomBuilder::parseBroadLeafElement(const QDomElement& element, const VisualizationParameters& parameters,
						 BSPPolygonSet* polygons)
{
  QDomElement child = element.firstChildElement();
  if(element.attribute("Shape") == "Ellipse") {
    if(child.tagName() == "BroadLeafAttributes") {
      QDomElement child2 = child.firstChildElement();
      double x, y, z;
      Point pstart;
      Point pend;
      PositionVector normal,x1u,y1u;
      double major, minor;

      int object_index = element.attribute(QString("ObjectIndex")).toInt();
      
      
      while(!child2.isNull()) {
	if(child2.tagName() == "PetioleStart") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  pstart = Point(x, y, z);
	}
	else if(child2.tagName() == "PetioleEnd") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  pend = Point(x, y, z);
	}
	else if(child2.tagName() == "LeafNormal") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  normal = PositionVector(x, y, z);
	}
	else if(child2.tagName() == "xdir") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  x1u = PositionVector(x, y, z);
	}
	else if(child2.tagName() == "ydir") {
	  QString temp = child2.text();
	  x = temp.section(' ', 0, 0).toDouble();
	  y = temp.section(' ', 1, 1).toDouble();
	  z = temp.section(' ', 2, 2).toDouble();
	  y1u = PositionVector(x, y, z);
	}
	else if(child2.tagName() == "EllipseSMajorA") {
	  major = child2.text().toDouble();
	}
	else if(child2.tagName() == "EllipseSMinorA") {
	  minor = child2.text().toDouble();
	}
	child2 = child2.nextSiblingElement();
      }
      SceneObject *object;
      if(parameters.useLeafTextures())
	object = new SceneObject(parameters.getMaterial(), object_index,
				 parameters.getLeafTexture(), parameters.useBSP());
      else 
	object = new SceneObject(parameters.getLeafMaterial(), object_index, 0, false);
      sceneObjects->insert(object_index, object);
      
      BSPPolygonSet* leaf = makeEllipseLeaf(cxxadt::Ellipse(pend,normal,x1u,y1u,major, minor), 
					    parameters.getLeafDetail(), 
					    parameters.useLeafTextures(), 		    
					    object);
      polygons->addPolygons(leaf);
      delete leaf;

      SceneObject* p_object = new SceneObject(parameters.getPetioleMaterial(), object_index, 0, false);
      sceneObjects->insert(object_index, p_object);
      BSPPolygonSet* petiole = makePetiole(pstart, pend,
					   parameters.getPetioleDetail(),
					   parameters.getPetioleRadius(),
					   p_object);
      polygons->addPolygons(petiole);
      delete petiole;
      
    }
    child = child.nextSiblingElement();
  }

  else if(element.attribute("Shape") == "Triangle") {

    while (!child.isNull()) {
      if(child.tagName() == "BroadLeafAttributes") {
	QDomElement child2 = child.firstChildElement();
	double x, y, z;
	Point pstart;
	Point pend;
	Point lc, rc, ac;
	PositionVector normal;
	
	int object_index = element.attribute(QString("ObjectIndex")).toInt();
      
	
	while(!child2.isNull()) {
	  if(child2.tagName() == "PetioleStart") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    pstart = Point(x, y, z);
	  }
	  else if(child2.tagName() == "PetioleEnd") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    pend = Point(x, y, z);
	  }
	  else if(child2.tagName() == "LeafNormal") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    normal = PositionVector(x, y, z);
	  }
	  else if(child2.tagName() == "TriangleLC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    lc = Point(x, y, z);
	  }
	  else if(child2.tagName() == "TriangleRC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    rc = Point(x, y, z);
	  }
	  else if(child2.tagName() == "TriangleAC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    ac = Point(x, y, z);
	  }
	  child2 = child2.nextSiblingElement();
	}
	SceneObject *object;
	if(parameters.useLeafTextures())
	  object = new SceneObject(parameters.getMaterial(), object_index,
				   parameters.getLeafTexture(), parameters.useBSP());
	else 
	  object = new SceneObject(parameters.getLeafMaterial(), object_index, 0, false);
	sceneObjects->insert(object_index, object);
	
	BSPPolygonSet* leaf = makeTriangleLeaf(lc, rc, ac, 
					       parameters.useLeafTextures(),
					       object);
	polygons->addPolygons(leaf);
	delete leaf;
	
	SceneObject* p_object = new SceneObject(parameters.getPetioleMaterial(), object_index, 0, false);
	sceneObjects->insert(object_index, p_object);
	BSPPolygonSet* petiole = makePetiole(pstart, pend,
					     parameters.getPetioleDetail(),
					     parameters.getPetioleRadius(),
					     p_object);
	polygons->addPolygons(petiole);
	delete petiole;
	
      }
      
      child = child.nextSiblingElement();
    }
  }
  else if (element.attribute("Shape") == "Kite") {

    while (!child.isNull()) {
      if(child.tagName() == "BroadLeafAttributes") {
	QDomElement child2 = child.firstChildElement();
	double x, y, z;
	Point pstart;
	Point pend;
	Point bc, lc, rc, ac;
	PositionVector normal;
	
	int object_index = element.attribute(QString("ObjectIndex")).toInt();
      
	
	while(!child2.isNull()) {
	  if(child2.tagName() == "PetioleStart") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    pstart = Point(x, y, z);
	  }
	  else if(child2.tagName() == "PetioleEnd") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    pend = Point(x, y, z);
	  }
	  else if(child2.tagName() == "LeafNormal") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    normal = PositionVector(x, y, z);
	  }
	  else if(child2.tagName() == "KiteBC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    bc = Point(x, y, z);
	  }
	  else if(child2.tagName() == "KiteLC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    lc = Point(x, y, z);
	  }
	  else if(child2.tagName() == "KiteRC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    rc = Point(x, y, z);
	  }
	  else if(child2.tagName() == "KiteAC") {
	    QString temp = child2.text();
	    x = temp.section(' ', 0, 0).toDouble();
	    y = temp.section(' ', 1, 1).toDouble();
	    z = temp.section(' ', 2, 2).toDouble();
	    ac = Point(x, y, z);
	  }
	  child2 = child2.nextSiblingElement();
	}
	cout << "Kite leaf found " <<endl;
	SceneObject *object = new SceneObject(parameters.getLeafMaterial(), object_index, 0, false);
	sceneObjects->insert(object_index, object);
	
	BSPPolygonSet* leaf = makeKiteLeaf(bc, lc, rc, ac, object);
	polygons->addPolygons(leaf);
	delete leaf;
	
	SceneObject* p_object = new SceneObject(parameters.getPetioleMaterial(), object_index, 0, false);
	sceneObjects->insert(object_index, p_object);
	BSPPolygonSet* petiole = makePetiole(pstart, pend,
					     parameters.getPetioleDetail(),
					     parameters.getPetioleRadius(),
					     p_object);
	polygons->addPolygons(petiole);
	delete petiole;
	
      }
      
      child = child.nextSiblingElement();
    }
  }

}

BSPPolygonSet* LGMPolygonDomBuilder::makeCylinder(double radius, double radius_top, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int r_detail, int y_detail) const  {
  double PI = 3.14159265;
  double sine, cosine, sine_next, cosine_next, y, y_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();

  if(radius == 0)
    return polygons;
  if (fabs(radius_top) < R_EPSILON)//probably not defined radius top of the cylinder
    radius_top=radius;
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  //  vector<Point> vertices(3);
  //vector<Point> t_vertices(3);
  double tex_length = 1;
  //double tex_start = rand()/(double)RAND_MAX;
  
  PositionVector v1, v2, v3, v4;
  double PI2_PER_DETAIL = 2.0*PI/r_detail;
  double TEXL_PER_DETAIL = tex_length/(double)r_detail;
  sine_next = radius*sin(0*PI2_PER_DETAIL);
  cosine_next = radius*cos(0*PI2_PER_DETAIL);

  for(int i = 0; i < r_detail; i++) {
    sine = sine_next;
    cosine = cosine_next;
    sine_next = radius*sin((i+1)*PI2_PER_DETAIL);
    cosine_next = radius*cos((i+1)*PI2_PER_DETAIL);
    double temp1 = TEXL_PER_DETAIL*i;
    double temp2 = TEXL_PER_DETAIL*(i+1);

    for(int j = 0; j < y_detail; j++) {
      y = j / (double)y_detail * height;
      y_next = (j+1) / (double)y_detail * height;
      
      PositionVector v1(sine, y, cosine);
      PositionVector v2(sine*(radius_top/radius), y_next, cosine*(radius_top/radius));
      PositionVector v3(sine_next, y, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
	    
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(temp1, y/height, 0),
					  Point(temp1, y_next/height, 0),
					  Point(temp2, y/height, 0),
					  object));
      
      v1 = PositionVector(sine_next, y, cosine_next);
      v2 = PositionVector(sine*(radius_top/radius), y_next, cosine*(radius_top/radius));
      v3 = PositionVector(sine_next*(radius_top/radius), y_next, cosine_next*(radius_top/radius));
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
	    
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(temp2, y/height, 0),
					  Point(temp1, y_next/height, 0),
					  Point(temp2, y_next/height, 0),
					  object));
    }
  
    if(drawTop) {
      v1 = PositionVector(sine*(radius_top/radius), height, cosine*(radius_top/radius));
      v2 = PositionVector(0, height, 0);
      v3 = PositionVector(sine_next*(radius_top/radius), height, cosine_next*(radius_top/radius));
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
    }
    
    if(drawBottom) {
      v1 = PositionVector(sine, 0, cosine);
      v2 = PositionVector(sine_next, 0, cosine_next);
      v3 = PositionVector(0, 0, 0);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
      
    }

  }
  return polygons;
}

BSPPolygonSet* LGMPolygonDomBuilder::makeFoliage(double radius, double height, Point point, PositionVector direction,
						 int f_detail, int s_detail, double foliage_height, 
						 double spacing, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  if(f_detail == 0 || s_detail == 0)
    return polygons;

  double sine, cosine, sine_next, cosine_next;
  double y, y_next;
  double PI = 3.14159265;
  double needle_length = foliage_height;

  LGMdouble tex_len = 0.1;
  LGMdouble tex_per_plane = height / tex_len;
  int needles_per_tex = 30;

  int needles_per_plane = static_cast<int>(tex_per_plane * needles_per_tex);
  if (needles_per_plane == 0)
    return polygons;


  int y_detail = (int)(height/spacing);
  if(y_detail == 0)
    y_detail = 1;
  
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);

  Point p1(radius*sin(0.0), radius*cos(0.0), 0);
  Point p2(radius*sin(1.0/s_detail*2*PI), radius*cos(1.0/s_detail*2*PI), 0);
  radius = PositionVector(0.5*(p1+p2)).length();

  double PI2_PER_FDETAIL = 2*PI/(double)f_detail;
  for(int j = 0; j < y_detail; j++) {
    y = j/(double)y_detail*height;
    y_next = (j+1)/(double)y_detail*height;

    for(int i = 0; i < f_detail; i++) {
      sine = radius*sin(i/PI2_PER_FDETAIL);
      cosine = radius*cos(i/PI2_PER_FDETAIL);
      sine_next = sine*(needle_length+radius)/radius;
      cosine_next = cosine*(needle_length+radius)/radius;

      PositionVector v1(sine, y, cosine);
      PositionVector v2(sine_next, y, cosine_next);
      PositionVector v3(sine, y_next, cosine);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(1, 0, 0),
					  Point(0, 0, 0),
					  Point(1, 1, 0),
					  object));
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v3)+point,
					  Point(v2)+point,
					  Point(1, 0, 0),
					  Point(1, 1, 0),
					  Point(0, 0, 0),
					  object));

      v1 = PositionVector(sine_next, y, cosine_next);
      v2 = PositionVector(sine_next, y_next, cosine_next);
      v3 = PositionVector(sine, y_next, cosine);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(0, 0, 0),
					  Point(0, 1, 0),
					  Point(1, 1, 0),
					  object));
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v3)+point,
					  Point(v2)+point,
					  Point(0, 0, 0),
					  Point(1, 1, 0),
					  Point(0, 1, 0),
					  object));
    }
  }
  
  return polygons;


}


BSPPolygonSet* LGMPolygonDomBuilder::makePetiole(Point sp, Point ep, int detail, double radius, SceneObject* object) const {
  
  BSPPolygonSet* polygons = makeCylinder(radius, radius, PositionVector(sp-ep).length(), sp, PositionVector(ep-sp), false, false, object, detail, 1);

  return polygons;
}

BSPPolygonSet* LGMPolygonDomBuilder::makeTriangleLeaf(Point lc, Point rc, Point ac, bool use_tex, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  if(use_tex) {
    polygons->addPolygon(new BSPPolygon(lc,
					rc,
					ac+0.5*(lc-rc),
					Point(0,0,0),
					Point(1,0,0),
					Point(0,1,0),
					object));
    polygons->addPolygon(new BSPPolygon(lc,
					ac+0.5*(lc-rc),
					rc,
					Point(0,0,0),
					Point(0,1,0),
					Point(1,0,0),
					object));
    polygons->addPolygon(new BSPPolygon(rc,
					ac+0.5*(rc-lc),
					ac+0.5*(lc-rc),
					Point(1,0,0),
					Point(1,1,0),
					Point(0,1,0),
					object));
    polygons->addPolygon(new BSPPolygon(rc,
					ac+0.5*(lc-rc),
					ac+0.5*(rc-lc),
					Point(1,0,0),
					Point(0,1,0),
					Point(1,1,0),
					object));
  }
  else {
    polygons->addPolygon(new BSPPolygon(lc, rc, ac, object));
    polygons->addPolygon(new BSPPolygon(lc, ac, rc, object));
  }
  
  return polygons;

}

BSPPolygonSet* LGMPolygonDomBuilder::makeKiteLeaf(Point bc, Point lc, Point rc, Point ac,SceneObject* object) const{
  BSPPolygonSet* polygons = new BSPPolygonSet();
  polygons->addPolygon(new BSPPolygon(bc, lc, ac, object));
  polygons->addPolygon(new BSPPolygon(lc, ac, rc, object));
  polygons->addPolygon(new BSPPolygon(bc, ac, rc, object));
  polygons->addPolygon(new BSPPolygon(bc, lc, rc, object));
  return polygons;
}

BSPPolygonSet* LGMPolygonDomBuilder::makeEllipseLeaf(cxxadt::Ellipse ellipse, int detail, bool use_tex, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  if(use_tex) {
    Point p1(ellipse.getCenterPoint() +
	     Point(ellipse.getSemimajorAxis()*ellipse.x1u()) + 
	     Point(ellipse.getSemiminorAxis()*ellipse.y1u()));
    Point p2(ellipse.getCenterPoint() +
	     Point(ellipse.getSemimajorAxis()*ellipse.x1u()) - 
	     Point(ellipse.getSemiminorAxis()*ellipse.y1u()));
    Point p3(ellipse.getCenterPoint() - 
	     Point(ellipse.getSemimajorAxis()*ellipse.x1u()) + 
	     Point(ellipse.getSemiminorAxis()*ellipse.y1u()));
    Point p4(ellipse.getCenterPoint() -
	     Point(ellipse.getSemimajorAxis()*ellipse.x1u()) - 
	     Point(ellipse.getSemiminorAxis()*ellipse.y1u()));

    polygons->addPolygon(new BSPPolygon(p1, p2, p3,
					Point(1, 1, 0), Point(0, 1, 0), Point(1, 0, 0),object));
    polygons->addPolygon(new BSPPolygon(p3, p2, p4,
					Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 0),object));

    polygons->addPolygon(new BSPPolygon(p4, p2, p3,
					Point(0, 0, 0), Point(0, 1, 0), Point(1, 0, 0),object));
    polygons->addPolygon(new BSPPolygon(p2, p1, p3,
					Point(0, 1, 0), Point(1, 1, 0), Point(1, 0, 0),object));    
    return polygons;
  }
  // If textures are not used
  else {
    vector<Point> vertices;
    vertices = ellipse.getVertexVector(vertices, detail);

    int size = vertices.size();
    
    //double step = 1.0/(size/2.0 );
    polygons->addPolygon(new BSPPolygon(vertices[0], vertices[size-1], vertices[1], object));
        
    for(int i = 1; i < size/2-1; i++) {
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i], vertices[size-i-1], object));
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i-1], vertices[i+1], object));
    }

    polygons->addPolygon(new BSPPolygon(vertices[size/2-1], vertices[size/2+1], vertices[size/2], object));


    polygons->addPolygon(new BSPPolygon(vertices[size/2-1], vertices[size/2], vertices[size/2+1], object));    

    for(int i = size/2-2; i >= 1; i--) {
      polygons->addPolygon(new BSPPolygon(vertices[size-i-1], vertices[i], vertices[i+1],  object));          
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i-1], vertices[size-i], object));
    }

    polygons->addPolygon(new BSPPolygon(vertices[1], vertices[size-1], vertices[0], object));
    return polygons;
  }
}

BSPPolygonSet* LGMPolygonDomBuilder::makeBud(Point point, PositionVector direction, int la_detail, int lo_detail,
						     double scale, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  double PI = 3.14159265;  
  int i, j;
  double y_scale = 2;
  double z_scale = 0.75;
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);
  
  Point origo(0,0,0);
  double PI2_PER_LODETAIL = 2 * PI / lo_detail;
  for (i = 0; i < la_detail; i++) {
    double lat0 = PI * (-0.5 + (double) i / la_detail);
    double z0 = sin(lat0);
    double zr0 = cos(lat0);
    
    double lat1 = PI * (-0.5 + (double) (i + 1) / la_detail);
    double z1 = sin(lat1);
    double zr1 = cos(lat1);
    for (j = 0; j < lo_detail; j++) {
      double lng1 = PI2_PER_LODETAIL * (double)j;
      double lng2 = PI2_PER_LODETAIL * (double)(j + 1);
      double x1 = cos(lng1);
      double y1 = sin(lng1);

      double x2 = cos(lng2);
      double y2 = sin(lng2);
      
      PositionVector v1(scale * (Point(0,y_scale,0) + Point(x1 * zr0, y_scale * y1 * zr0, z_scale * z0)));
      PositionVector v2(scale * (Point(0,y_scale,0) + Point(x1 * zr1, y_scale * y1 * zr1, z_scale * z1)));
      PositionVector v3(scale * (Point(0,y_scale,0) + Point(x2 * zr1, y_scale * y2 * zr1, z_scale * z1)));
      PositionVector v4(scale * (Point(0,y_scale,0) + Point(x2 * zr0, y_scale * y2 * zr0, z_scale * z0)));
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      v4 = v4.rotate(origo, dir, PI);

      if(i != la_detail - 1) {
	polygons->addPolygon(new BSPPolygon(point + Point(v2),
					    point + Point(v3),
					    point + Point(v1),
					    object));
      }

      if(i != 0) {
      polygons->addPolygon(new BSPPolygon(point + Point(v3),
					  point + Point(v4),
					  point + Point(v1),
					  object));
      }
				       
      /*polygons->addPolygon(new BSPPolygon(point + Point(scale * x1 * zr0, scale * y1 * zr0, scale * z0),
					  point + Point(scale * x1 * zr1, scale * y1 * zr1, scale * z1),
					  point + Point(scale * x2 * zr1, scale * y2 * zr1, scale * z1),
					  object));
      polygons->addPolygon(new BSPPolygon(point + Point(scale * x2 * zr1, scale * y2 * zr1, scale * z1),
					  point + Point(scale * x2 * zr0, scale * y2 * zr0, scale * z0),
					  point + Point(scale * x1 * zr0, scale * y1 * zr0, scale * z0),
					  object));*/
    }
  }
  return polygons;
}

