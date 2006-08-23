#include <QtGui>

#include "XMLViewerWindow.h"
#include "XMLViewer.h"


XMLViewerWindow::XMLViewerWindow()
{
  //xml_viewer = new XMLViewer();
  //setCentralWidget(xml_viewer);
  
  //createActions();
  //createMenus();
  //createToolbar();
  ui.setupUi(this);

  statusBar()->showMessage("Ready");
  
  setWindowTitle("XML Viewer");
  resize(480, 320);
  
  connect(ui.xml_viewer, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)),
	  this, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)));
  connect(ui.actionAdd_tree, SIGNAL(triggered()), this, SLOT(addTree()));
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui.actionUpdate_visualization, SIGNAL(triggered()), ui.xml_viewer, SLOT(sendVisualizationUpdate()));
  connect(ui.xml_viewer, SIGNAL(updateVisualization(QList<QString>)), this, SIGNAL(updateVisualization(QList<QString>)));
}

void XMLViewerWindow::addTree()
{
  QString fileName =
    QFileDialog::getOpenFileName(this, tr("Open a XML File"),
				 QDir::currentPath(),
				 tr("XML Files (*.xml)"));
  if (fileName.isEmpty())
    return;
  
  if (ui.xml_viewer->addTree(fileName)) {
    statusBar()->showMessage(tr("File loaded"), 2000);
    emit fileAdded(fileName);
  }
}



/*void XMLViewerWindow::createActions()
{
  addAct = new QAction(tr("A&dd tree..."), this);
  addAct->setShortcut(tr("Ctrl+A"));
  connect(addAct, SIGNAL(triggered()), this, SLOT(addTree()));
  
  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void XMLViewerWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(addAct);
  fileMenu->addAction(exitAct);
}

void XMLViewerWindow::createToolbar() {
  toolBar = new QToolBar(this);
  addToolBar(toolBar);
  toolBar->addAction(addAct);	
  		
}*/
