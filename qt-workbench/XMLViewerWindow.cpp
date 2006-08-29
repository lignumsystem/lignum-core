#include <QtGui>

#include "XMLViewerWindow.h"
#include "XMLViewer.h"
#include <iostream>

using namespace std;


XMLViewerWindow::XMLViewerWindow(QWidget *parent) 
  : QDockWidget(parent)
{
  //ui.setupUi(this);

  //statusBar()->showMessage("Ready");
  
  xml_widget = new XMLViewerWidget(this);
  setWidget(xml_widget);

  setWindowTitle("XML Viewer");
  resize(480, 320);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

  connect(xml_widget, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)),
 	  this, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)));
  connect(xml_widget, SIGNAL(updateVisualization(QList<QString>)), this, SIGNAL(updateVisualization(QList<QString>)));
  connect(xml_widget, SIGNAL(textOutput(QString)), this, SIGNAL(textOutput(QString)));
  connect(xml_widget, SIGNAL(setFocus(Point, PositionVector, double)),
	  this, SIGNAL(setFocus(Point, PositionVector, double)));

}

void XMLViewerWindow::addTree()
{

}

void XMLViewerWindow::startProgressBarAnimation() {
  xml_widget->startProgressBarAnimation();
}

void XMLViewerWindow::stopProgressBarAnimation() {
  xml_widget->stopProgressBarAnimation();
}
