#include "LignumWB.h"
#include "FunctionEditor.h"

LignumWB::LignumWB(QWidget *parent)
  : QMainWindow(parent), xml_viewer(NULL), console(NULL), viz_config(NULL)
{
  ui.setupUi(this);
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui.actionLoad_tree, SIGNAL(triggered()), this, SLOT(loadTree()));
  connect(ui.actionVisualization_settings, SIGNAL(triggered()), this, SLOT(options()));
  connect(ui.actionFree_roam, SIGNAL(triggered()), ui.gldrawer, SLOT(freeRoamMode()));
  connect(ui.actionOrbit, SIGNAL(triggered()), ui.gldrawer, SLOT(orbitCameraMode()));
  connect(ui.actionMove_center, SIGNAL(triggered()), ui.gldrawer, SLOT(moveCenterMode()));
  connect(ui.actionWorking_directory, SIGNAL(triggered()), this, SLOT(setWorkingDirectory()));
  connect(ui.actionFunction_editor, SIGNAL(triggered()), this, SLOT(functionEditor()));
  connect(ui.actionConsole, SIGNAL(triggered()), this, SLOT(openConsole()));
  connect(ui.actionXML_Viewer, SIGNAL(triggered()), this, SLOT(xmlviewer()));
  connect(ui.actionSwitch_materials, SIGNAL(triggered()), ui.gldrawer, SLOT(switchMaterials()));

  viewActions = new QActionGroup(this);
  viewActions->addAction(ui.actionFree_roam);
  viewActions->addAction(ui.actionOrbit);
  viewActions->addAction(ui.actionMove_center);
  ui.actionOrbit->setChecked(true);
  
  viewActions->setExclusive(true);

  ui.toolBar->setWindowTitle("Toolbar");

  setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
  
  xmlviewer();
  openConsole();
}

void LignumWB::loadTree() {
  QString fileName = QFileDialog::getOpenFileName(this,
						  "Choose a file",
						  QDir::currentPath(),
						  "XML-tree files (*.xml)");
  
  // Should this be implemented with signals & slots?
  if(!fileName.isEmpty()) {
    ui.gldrawer->addTree(fileName);
  }
}

void LignumWB::xmlviewer() {
  if(!xml_viewer) {
    xml_viewer = new XMLViewerWindow(this);
    connect(xml_viewer, SIGNAL(sceneObjectsSelected(QHash<QString, QList<int> >)),
	    ui.gldrawer, SLOT(setObjectsSelected(QHash<QString, QList<int> >)));
    connect(xml_viewer, SIGNAL(updateVisualization(QList<QString>)),
	    ui.gldrawer, SLOT(resetVisualization(QList<QString>)));
    connect(xml_viewer, SIGNAL(textOutput(QString)), this, SLOT(textOutput(QString)));
    connect(xml_viewer, SIGNAL(setFocus(Point, PositionVector, double)),
	    ui.gldrawer, SLOT(setFocus(Point, PositionVector, double)));
    connect(ui.gldrawer, SIGNAL(loadingTrees()), xml_viewer, SLOT(startProgressBarAnimation()));
    connect(ui.gldrawer, SIGNAL(treesLoaded()), xml_viewer, SLOT(stopProgressBarAnimation()));
    addDockWidget(Qt::RightDockWidgetArea, xml_viewer);
  } 
  xml_viewer->show();
  xml_viewer->raise();
  xml_viewer->activateWindow();
}

// Opens the console. Creates a new console object if there isn't
// a one created before.
void LignumWB::openConsole() {
  if(!console) {
    console = new ConsoleWindow(this);
    addDockWidget(Qt::BottomDockWidgetArea, console);
  } 
  console->show();
  console->raise();
  console->activateWindow();
}

// Opens a new function editor.
void LignumWB::functionEditor() {
  FunctionEditor* function_editor = new FunctionEditor();
  function_editor->show();
  function_editor->raise();
  function_editor->activateWindow(); 
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
							"Choose a working directory",
							QDir::currentPath(),
							QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  
  // Should this be implemented with signals & slots?
  if(!directory.isEmpty() && console != NULL) {
    if(QDir::setCurrent(directory))
      //ui.textBrowser->append(QString("Working directory changed to ")+QDir::currentPath());
      textOutput(QString("Working directory changed to ")+QDir::currentPath());
    else 
      //ui.textBrowser->append(QString("Working directory not changed."));*/
      textOutput(QString("Working directory not changed."));
  }
}

/*void LignumWB::startExternalProgram() {
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
    }*/

/*void LignumWB::endExternalProgram(int exitCode, QProcess::ExitStatus exitStatus) {
  clearExternalProgram();
  delete externalProgram;
  externalProgram = NULL;
  if(exitStatus == QProcess::NormalExit)
    ui.textBrowser->append(QString("External program exited normally."));
  else
    ui.textBrowser->append(QString("External program crashed."));
    }*/

/*void LignumWB::addExternalOutput() {
  if(externalProgram != NULL)
    ui.textBrowser->append(QString(externalProgram->readAllStandardOutput()));
    }*/

/*void LignumWB::externalError(QProcess::ProcessError error) {
  ui.textBrowser->append(QString("Error running the external program. Exiting(%1).").arg(error));
  clearExternalProgram();
  externalProgram = NULL;
}

void LignumWB::killExternalProgram() {
  if(externalProgram)
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

	     }*/
void LignumWB::textOutput(QString text) {
  if(console)
    console->printText(text);
}
