#ifndef LIGNUMWB_H
#define LIGNUMWB_H

// Qt includes
#include <QMainWindow>
#include <QProcess>

// Workbench includes
#include "qt_wb.h"
#include "VisualizationConfig.h"
#include "FunctionEditor.h"
#include "XMLViewerWindow.h"
#include "ConsoleWindow.h"
#include "HelpDialog.h"

class LignumWB : public QMainWindow
{
  Q_OBJECT

public:
  LignumWB(QWidget *parent = 0);

private:
  Ui::MainWindow ui;
  XMLViewerWindow *xml_viewer;
  ConsoleWindow *console;
  VisualizationConfig* viz_config;
  HelpDialog* help_dialog;
  QActionGroup *viewActions;

private slots:
  void loadTree();
  void options();
  void xmlviewer();
  void openConsole();
  void functionEditor();
  void setWorkingDirectory();
  void textOutput(QString text);
  void help();
};

#endif
