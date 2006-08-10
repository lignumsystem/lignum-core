#include "LignumWB.h"

LignumWB::LignumWB(QWidget *parent)
  : QMainWindow(parent), viz_config(NULL), externalProgram(NULL)
{
  ui.setupUi(this);
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui.actionLoad_tree, SIGNAL(triggered()), this, SLOT(loadTree()));
  connect(ui.actionVisualization_settings, SIGNAL(triggered()), this, SLOT(options()));
  connect(ui.actionFree_roam, SIGNAL(triggered()), ui.gldrawer, SLOT(freeRoamMode()));
  connect(ui.actionOrbit, SIGNAL(triggered()), ui.gldrawer, SLOT(orbitCameraMode()));
  connect(ui.actionMove_center, SIGNAL(triggered()), ui.gldrawer, SLOT(moveCenterMode()));
  connect(ui.actionWorking_directory, SIGNAL(triggered()), this, SLOT(setWorkingDirectory()));
  connect(ui.runButton, SIGNAL(clicked()), this, SLOT(startExternalProgram()));
  connect(ui.killButton, SIGNAL(clicked()), this, SLOT(killExternalProgram()));
}

void LignumWB::loadTree() {
  //TreeLoader* loader = new TreeLoader;
  //loader->show();

  QString fileName = QFileDialog::getOpenFileName(this,
						  "Choose a file",
						  QDir::currentPath(),
						  "XML-tree files (*.xml)");
  
  // Should this be implemented with signals & slots?
  if(!fileName.isEmpty()) {
    ui.gldrawer->setTreeFile(fileName);
    ui.gldrawer->changeTree();
  }
}

void LignumWB::options() {
  if(!viz_config) {
    viz_config = new VisualizationConfig();
    viz_config->setModal(true);
    connect(viz_config, SIGNAL(settingsChanged(VisualizationParameters)), ui.gldrawer, SLOT(changeSettings(VisualizationParameters)));
  } 
  viz_config->setSettings(ui.gldrawer->getParameters());
  viz_config->show();
  viz_config->raise();
  viz_config->activateWindow(); 
      
  /*VisualizationConfig* conf = new VisualizationConfig(this);
  conf->show();
  conf->raise();*/
}

void LignumWB::setWorkingDirectory() {
  QString directory = QFileDialog::getExistingDirectory(this,
							"Choose a directory",
							QDir::currentPath(),
							QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  
  // Should this be implemented with signals & slots?
  if(!directory.isEmpty()) {
    if(QDir::setCurrent(directory))
      ui.textBrowser->append(QString("Working directory changed succesfully."));
    else 
      ui.textBrowser->append(QString("Working directory not changed."));
  }
}

void LignumWB::startExternalProgram() {
  if(externalProgram == NULL) {
    QStringList text = ui.console->displayText().split(QString(" "));
    QString program = text.first();
    text.removeFirst();
    
    externalProgram = new QProcess(this);
    externalProgram->start(program, text);
    connect(externalProgram, SIGNAL(finished(int, QProcess::ExitStatus)),
	    this, SLOT(endExternalProgram(int, QProcess::ExitStatus)));
    connect(externalProgram, SIGNAL(readyReadStandardOutput()),
	    this, SLOT(addExternalOutput()));
    connect(externalProgram, SIGNAL(error(QProcess::ProcessError)),
	    this, SLOT(externalError(QProcess::ProcessError)));
  }
  else 
    ui.textBrowser->append(QString("External program is already running! Wait for it to finish."));
}

void LignumWB::endExternalProgram(int exitCode, QProcess::ExitStatus exitStatus) {
  clearExternalProgram();
  if(exitStatus == QProcess::NormalExit)
    ui.textBrowser->append(QString("External program exited normally."));
  else
    ui.textBrowser->append(QString("External program crashed."));
}

void LignumWB::addExternalOutput() {
  if(externalProgram != NULL)
    ui.textBrowser->append(QString(externalProgram->readAllStandardOutput()));
}

void LignumWB::externalError(QProcess::ProcessError error) {
  ui.textBrowser->append(QString("Error running the external program. Exiting."));
  clearExternalProgram();
}

void LignumWB::killExternalProgram() {
  externalProgram->kill();
  //  clearExternalProgram();
}

void LignumWB::clearExternalProgram() {
  disconnect(externalProgram, SIGNAL(finished(int, QProcess::ExitStatus)),
	     this, SLOT(endExternalProgram(int, QProcess::ExitStatus)));
  disconnect(externalProgram, SIGNAL(readyReadStandardOutput()),
	     this, SLOT(addExternalOutput()));
  disconnect(externalProgram, SIGNAL(error(QProcess::ProcessError)),
	     this, SLOT(externalError(QProcess::ProcessError)));
  delete externalProgram;
  externalProgram = NULL;
}
