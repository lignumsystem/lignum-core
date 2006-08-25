#include "XMLViewerWidget.h"
#include <QtGui>

XMLViewerWidget::XMLViewerWidget(QWidget *parent) :
  QWidget(parent) {
  ui.setupUi(this);

  connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addTree()));
  connect(ui.updatevButton, SIGNAL(clicked()),
	  ui.xml_viewer, SLOT(sendVisualizationUpdate()));
  connect(ui.xml_viewer, SIGNAL(updateVisualization(QList<QString>)),
	  this, SIGNAL(updateVisualization(QList<QString>))); 
  connect(ui.xml_viewer, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)),
 	  this, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >))); 
  connect(ui.removeButton, SIGNAL(clicked()), ui.xml_viewer, SLOT(removeSelected()));
  connect(ui.xml_viewer, SIGNAL(textOutput(QString)), this, SIGNAL(textOutput(QString)));
  connect(ui.xml_viewer, SIGNAL(setFocus(Point, PositionVector, double)),
	  this, SIGNAL(setFocus(Point, PositionVector, double)));
}


void XMLViewerWidget::addTree() {
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Open a XML File"),
				 QDir::currentPath(),
				 tr("XML Files (*.xml)"));
  if (fileName.isEmpty())
    return;
  
  if (ui.xml_viewer->addTree(fileName)) {
    emit fileAdded(fileName);
  }
}
