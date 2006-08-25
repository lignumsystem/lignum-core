#ifndef XMLVIEWERWINDOW_H
#define XMLVIEWERWINDOW_H

//#include <QMainWindow>
#include <QDockWidget>
#include <QMultiHash>
#include <XMLViewerWidget.h>
//#include "xml_viewer.h"

//class XMLViewer;

class XMLViewerWindow : public QDockWidget
{
  Q_OBJECT
  
public:
  XMLViewerWindow(QWidget *parent = 0);
  
signals: 
  void sceneObjectsSelected(QHash<QString, QList<int> >);
  void fileAdded(QString);
  void updateVisualization(QList<QString>);
  void textOutput(QString);
  void setFocus(Point, PositionVector, double);

private slots:
  void addTree();
  
private:
  //  Ui::TreeViewer ui;
  XMLViewerWidget *xml_widget;
};

#endif
