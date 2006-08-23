#include <QtGui>

#include "XMLViewerWindow.h"
#include "XMLViewer.h"

XMLViewerWindow::XMLViewerWindow()
{
  xml_viewer = new XMLViewer();
  setCentralWidget(xml_viewer);
  
  createActions();
  createMenus();
  
  statusBar()->showMessage("Ready");
  
  setWindowTitle("XML Viewer");
  resize(480, 320);
  
  connect(xml_viewer, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)),
	  this, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)));

}

void XMLViewerWindow::open()
{
  QString fileName =
    QFileDialog::getOpenFileName(this, tr("Open a XML File"),
				 QDir::currentPath(),
				 tr("XML Files (*.xml)"));
  if (fileName.isEmpty())
    return;
  
  if (xml_viewer->addTree(fileName))
    statusBar()->showMessage(tr("File loaded"), 2000);

  emit fileAdded(fileName);
}



void XMLViewerWindow::createActions()
{
  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
  
  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void XMLViewerWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addAction(exitAct);
}
