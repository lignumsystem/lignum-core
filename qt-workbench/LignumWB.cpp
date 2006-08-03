#include "LignumWB.h"

LignumWB::LignumWB(QWidget *parent)
  : QMainWindow(parent), viz_config(NULL)
{
  ui.setupUi(this);
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui.actionLoad_tree, SIGNAL(triggered()), this, SLOT(loadTree()));
  connect(ui.actionVisualization_settings, SIGNAL(triggered()), this, SLOT(options()));
}

void LignumWB::loadTree() {
  //TreeLoader* loader = new TreeLoader;
  //loader->show();

  QString fileName = QFileDialog::getOpenFileName(this,
						  "Choose a file",
						  QDir::currentPath(),
						  "XML-tree files (*.xml)");
  
  // Should this be implemented with signals & slots?
  ui.gldrawer->setTreeFile(fileName);
  ui.gldrawer->changeTree();
}

void LignumWB::options() {
  if(!viz_config) {
    viz_config = new VisualizationConfig();
  } 
  viz_config->show();
  viz_config->raise();
  viz_config->activateWindow(); 
      
  /*VisualizationConfig* conf = new VisualizationConfig(this);
  conf->show();
  conf->raise();*/
}


