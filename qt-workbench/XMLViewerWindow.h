#ifndef XMLVIEWERWINDOW_H
#define XMLVIEWERWINDOW_H

#include <QMainWindow>

class XMLViewer;

class XMLViewerWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  XMLViewerWindow();
  
signals: 
  void sceneObjectsSelected(QList<int>);

private slots:
  void open();
  
private:
  void createActions();
  void createMenus();
  
  XMLViewer *xml_viewer;
  
  QMenu *fileMenu;
  QAction *openAct;
  QAction *exitAct;
};

#endif
