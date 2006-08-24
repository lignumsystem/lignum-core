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

  setAllowedAreas(Qt::RightDockWidgetArea);

  connect(xml_widget, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)),
 	  this, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)));
  connect(xml_widget, SIGNAL(updateVisualization(QList<QString>)), this, SIGNAL(updateVisualization(QList<QString>)));

  //connect(xml_widget, SIGNAL(statusText(QString, int)), statusBar(), SLOT(showMessage(QString, int)));

  //connect(ui.actionAdd_tree, SIGNAL(triggered()), this, SLOT(addTree()));
  //connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  //connect(ui.actionUpdate_visualization, SIGNAL(triggered()), ui.xml_viewer, SLOT(sendVisualizationUpdate()));
  
//connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addTree()));
  //connect(ui.updatevButton, SIGNAL(clicked()), ui.xml_viewer, SLOT(sendVisualizationUpdate())); 
  //connect(ui.xml_viewer, SIGNAL(updateVisualization(QList<QString>)), this, SIGNAL(updateVisualization(QList<QString>)));

}

void XMLViewerWindow::addTree()
{
  /*  QString fileName =
    QFileDialog::getOpenFileName(this, tr("Open a XML File"),
				 QDir::currentPath(),
				 tr("XML Files (*.xml)"));
  if (fileName.isEmpty())
    return;
  
  if (ui.xml_viewer->addTree(fileName)) {
    //statusBar()->showMessage(tr("File loaded"), 2000);
    emit fileAdded(fileName);
    }*/
}



