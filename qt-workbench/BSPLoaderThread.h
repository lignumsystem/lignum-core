#ifndef BSPLOADERTHREAD_H
#define BSPLOADERTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QList>

#include <BSPTree.h>
#include <VisualizationParameters.h>

class BSPLoaderThread : public QThread
{
  Q_OBJECT

public: 

  BSPLoaderThread(QObject *parent = 0);
  ~BSPLoaderThread();

  void loadTrees(QList<QString> files, VisualizationParameters parameters);
  
signals:
  void treesLoaded(BSPTree *tree, Point t_point, PositionVector r_axis,
		   double t_height, QHash<QString, QMultiHash<int, SceneObject*>* > *sceneObjects);
  void workStarted();
  void workFinished();

protected:
  void run();

private:
  QMutex mutex;
  QWaitCondition condition;
  
  bool abort;
  
  QList<QString> files;
  VisualizationParameters parameters;

};

#endif
