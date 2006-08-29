#include <QtGui>

#include "BSPLoaderThread.h"
#include <Lignum.h>
#include <GenericCfTree.h>
#include <GenericHwTree.h>
#include <XMLTree.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMPolygonTree.h>
#include <QProgressDialog>

using namespace cxxadt;

BSPLoaderThread::BSPLoaderThread(QObject *parent)
  : QThread(parent)
{
  abort = false;
}

BSPLoaderThread::~BSPLoaderThread()
{
  mutex.lock();
  abort = true;
  condition.wakeOne();
  mutex.unlock();

  wait();
}


void BSPLoaderThread::loadTrees(QList<QString> files, VisualizationParameters parameters) 
{

  QMutexLocker locker(&mutex);

  this->files = files;
  this->parameters = parameters;

  if(!isRunning()){
    start(LowPriority);
  } else {
    condition.wakeOne();
  }

}

void BSPLoaderThread::run()
{
  forever {
    mutex.lock();
    QList<QString> files = this->files;
    VisualizationParameters parameters = this->parameters;
    mutex.unlock();

    emit workStarted();
    BSPTree *tree = new BSPTree;

    PositionVector r_axis;
    Point t_point;
    double t_height;
    QHash<QString, QMultiHash<int, SceneObject*>* > *sceneObjects = new QHash<QString, QMultiHash<int, SceneObject*>*>;

    BSPPolygonSet polygons;


    for(int i = 0; i < files.size(); i++) {
      QDomDocument doc;
      QString fileName = files[i];
      QFile file(fileName);
      if(!file.open(QIODevice::ReadOnly))
         continue;
      if(!doc.setContent(&file)) {
         file.close();
         continue;
      }
      XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud> cf_reader;

      int treeType = cf_reader.treeType(doc);
      if(treeType == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::Cf) {	
      //if(cf_reader.treeType(fileName.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::Cf) {
	Tree<GenericCfTreeSegment, GenericCfBud> cftree(Point(0,0,0), PositionVector(0,1,0));
	cf_reader.readXMLToTree(cftree, doc);
	
	LGMPolygonTree<GenericCfTreeSegment, GenericCfBud> constructor;
	BSPPolygonSet* treePolygons = constructor.buildTree(cftree, parameters,
							    cf_reader.getTreeCompartmentHash(),
							    cf_reader.getLeafHash());
	polygons.addPolygons(treePolygons);
	delete treePolygons;
	sceneObjects->insert(fileName, constructor.getSceneObjects());
	r_axis = GetDirection(GetRootAxis(cftree));
	t_point = GetPoint(cftree);
	t_height = GetValue(cftree, LGAH);
	r_axis = r_axis.normalize();
	r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
      }
      else {
            int leafType = cf_reader.leafType(doc);

	if(leafType == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::Cf) {
    //if(cf_reader.leafType(fileName.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::TRIANGLE) {
	  
	  XMLDomTreeReader<GenericHwTriangleTreeSegment, GenericHwTriangleBud, Triangle> hwt_reader;	
	  Tree<GenericHwTriangleTreeSegment, GenericHwTriangleBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
	  hwt_reader.readXMLToTree(hwtree, doc);
	  
	  LGMPolygonTree<GenericHwTriangleTreeSegment, GenericHwTriangleBud, Triangle> constructor;
	  BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters,
							      hwt_reader.getTreeCompartmentHash(),
							      hwt_reader.getLeafHash());
	  polygons.addPolygons(treePolygons);
	  delete treePolygons;
	  sceneObjects->insert(fileName, constructor.getSceneObjects());
	  
	  r_axis = GetDirection(GetRootAxis(hwtree));
	  t_point = GetPoint(hwtree);
	  t_height = GetValue(hwtree, LGAH);
	  r_axis = r_axis.normalize();
	  r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	  t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
	}
	else if(leafType == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::ELLIPSE) {
    //else if (cf_reader.leafType(fileName.toStdString()) == XMLDomTreeReader<GenericCfTreeSegment, GenericCfBud>::ELLIPSE) {
	  XMLDomTreeReader<GenericHwEllipseTreeSegment, GenericHwEllipseBud, cxxadt::Ellipse> hwt_reader;
	
	  Tree<GenericHwEllipseTreeSegment, GenericHwEllipseBud> hwtree(Point(0,0,0), PositionVector(0,1,0));
	  hwt_reader.readXMLToTree(hwtree, doc);

	  
	  LGMPolygonTree<GenericHwEllipseTreeSegment, GenericHwEllipseBud, cxxadt::Ellipse> constructor;
	  BSPPolygonSet* treePolygons = constructor.buildTree(hwtree, parameters,
							      hwt_reader.getTreeCompartmentHash(),
							      hwt_reader.getLeafHash());

	  polygons.addPolygons(treePolygons);
	  delete treePolygons;

	  //sceneObjects->insert(fileName, constructor.getSceneObjects());
	  
	  r_axis = GetDirection(GetRootAxis(hwtree));
	  t_point = GetPoint(hwtree);
	  t_height = GetValue(hwtree, LGAH);
	  r_axis = r_axis.normalize();
	  r_axis = PositionVector(r_axis.getX(), r_axis.getZ(), -r_axis.getY());
	  t_point = Point(t_point.getX(), t_point.getZ(), -t_point.getY());
	}
      }
    }

    tree->buildBSPTree(polygons);

    emit treesLoaded(tree, t_point, r_axis, t_height, sceneObjects);
    emit workFinished();
    
    mutex.lock();
    condition.wait(&mutex);
    mutex.unlock();
    //tree->addPolygonsToTree(polygons);
  }
}
