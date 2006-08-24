#ifndef XMLVIEWERWINDOW_H
#define XMLVIEWERWINDOW_H

#include <QMainWindow>
#include <QMultiHash>
#include "xml_viewer.h"

class XMLViewer;

class XMLViewerWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  XMLViewerWindow();
  
signals: 
  void sceneObjectsSelected(QHash<QString, QList<int> >);
  void fileAdded(QString);
  void updateVisualization(QList<QString>);

private slots:
  void addTree();
  //  void displayStatusText(
  
private:
  //void createActions();
  //void createMenus();
  //void createToolbar();
  
  //XMLViewer *xml_viewer;
  
  //QMenu *fileMenu;
  //QToolBar *toolBar;
  //QAction *addAct;
  //QAction *exitAct;
  Ui::TreeViewer ui;
};

#endif
