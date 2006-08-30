#ifndef LGMPOLYGONDOMBUILDER_H
#define LGMPOLYGONDOMBUILDER_H

#include <QDomDocument>
#include "BSPPolygon.h"
#include <QHash>
#include <QMultiHash>
#include <SceneObject.h>
#include <VisualizationParameters.h>

#include <Ellipse.h>

class Ellipse;

class LGMPolygonDomBuilder {

public:

  LGMPolygonDomBuilder(); 
  QMultiHash<int, SceneObject*>* getSceneObjects();
  BSPPolygonSet* createPolygons(const QDomDocument& doc, const VisualizationParameters& parameters);
  PositionVector getAxis(const QDomDocument& doc);
  Point getPoint(const QDomDocument& doc);
  double getHeight(const QDomDocument& doc);

  void parseTreeElement(const QDomElement& element, const VisualizationParameters& parameters,
			BSPPolygonSet* polygons);
  void parseAxisElement(const QDomElement& element, const VisualizationParameters& parameters,
			BSPPolygonSet* polygons);
  void parseTreeSegmentElement(const QDomElement& element, const VisualizationParameters& parameters,
			       BSPPolygonSet* polygons);
  void parseBranchingPointElement(const QDomElement& element, const VisualizationParameters& parameters,
				  BSPPolygonSet* polygons);
  void parseBudElement(const QDomElement& element, const VisualizationParameters& parameters,
		       BSPPolygonSet* polygons);
  void parseBroadLeafElement(const QDomElement& element, const VisualizationParameters& parameters,
			     BSPPolygonSet* polygons);
  

private:
  BSPPolygonSet*  makeCylinder(double radius,
			       double height,
			       Point point,
			       PositionVector direction,
			       bool drawBottom,
			       bool drawTop,
			       SceneObject* object,
			       int r_detail,
			       int y_detail) const;
  
  BSPPolygonSet* makeFoliage(double radius, double height, Point point, PositionVector direction,
			     int f_detail, int s_detail, double fmass, double spacing, SceneObject* object) const;
  BSPPolygonSet* makePetiole(Point sp, Point ep, int detail, double radius, SceneObject* object) const;
  BSPPolygonSet* makeTriangleLeaf(Point lc, Point rc, Point ac, bool use_tex, SceneObject* object) const;
  BSPPolygonSet* makeEllipseLeaf(cxxadt::Ellipse ellipse, int detail, bool use_tex, SceneObject* object) const;
  BSPPolygonSet* makeBud(Point point, PositionVector direction, int la_detail, int lo_detail, double size, SceneObject* object) const;
 
  QMultiHash<int, SceneObject*>* sceneObjects; 
};

#endif
