#ifndef XMLVIEWERWINDOW_H
#define XMLVIEWERWINDOW_H

#include <QMainWindow>
#include <QMultiHash>

class XMLViewer;

class XMLViewerWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  XMLViewerWindow();
  
signals: 
  void sceneObjectsSelected(QHash<QString, QList<int> >);
  void fileAdded(QString);

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
