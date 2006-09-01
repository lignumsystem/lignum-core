#include <QtGui>

#include "BSPLoaderThread.h"
#include <Lignum.h>
#include <GenericCfTree.h>
#include <GenericHwTree.h>
#include <XMLTree.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMPolygonDomBuilder.h>
#include <QProgressDialog>

using namespace cxxadt;

// Creates a new loader thread.
BSPLoaderThread::BSPLoaderThread(QObject *parent)
  : QThread(parent)
{
  abort = false;
}

// Destructor for the thread.
BSPLoaderThread::~BSPLoaderThread()
{
  mutex.lock();
  abort = true;
  condition.wakeOne();
  mutex.unlock();

  wait();
}

// Loads trees for visualization. Stores
// the names of the files to be loaded and
// and visualization parameters, and awakes the 
// thread, if it were sleeping.
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

// Function, where all the actual job is done.
void BSPLoaderThread::run()
{
  forever {
    // loadTrees-function also access these members
    // (from the main thread), so protection is needed.
    mutex.lock();
    QList<QString> files = this->files;
    VisualizationParameters parameters = this->parameters;
    mutex.unlock();
    
    emit workStarted();
    BSPTree *tree = new BSPTree;
    
    PositionVector r_axis;
    Point t_point;
    double t_height = 0;
    QHash<QString, QMultiHash<int, SceneObject*>* > *sceneObjects = new QHash<QString, QMultiHash<int, SceneObject*>*>;
    
    BSPPolygonSet polygons;
    LGMPolygonDomBuilder builder;
    
    for(int i = 0; i < files.size(); i++) {
      QDomDocument doc("LMODEL") ;
      QString fileName = files[i];
      QFile file(fileName);
      if(!file.open(QIODevice::ReadOnly))
	continue;
      if(!doc.setContent(&file)) {
	file.close();
	continue;
      }
      file.close();
      
      BSPPolygonSet *temp = builder.createPolygons(doc, parameters);
      polygons.addPolygons(temp);
      delete temp;

      sceneObjects->insert(fileName, builder.getSceneObjects());
      r_axis = builder.getAxis(doc);
      t_point = builder.getPoint(doc);
      t_height = builder.getHeight(doc);
      r_axis = r_axis.normalize();
      r_axis = PositionVector(-r_axis.getX(), r_axis.getZ(), -r_axis.getY());
      t_point = Point(-t_point.getX(), t_point.getZ(), -t_point.getY());
    }
    
    tree->buildBSPTree(polygons);

    emit treesLoaded(tree, t_point, r_axis, t_height, sceneObjects);
    emit workFinished();
    
    // Put the thread to sleep.
    mutex.lock();
    condition.wait(&mutex);
    mutex.unlock();
    //tree->addPolygonsToTree(polygons);
  }
}
