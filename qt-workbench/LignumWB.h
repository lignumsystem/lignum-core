#ifndef LIGNUMWB_H
#define LIGNUMWB_H

#include <QMainWindow>
#include <QProcess>
#include "qt_wb.h"
#include "VisualizationConfig.h"
#include "FunctionEditor.h"

class LignumWB : public QMainWindow
{
  Q_OBJECT

public:
  LignumWB(QWidget *parent = 0);

private:
  Ui::MainWindow ui;
  VisualizationConfig* viz_config;
  QProcess *externalProgram;
  FunctionEditor *function_editor;

  void clearExternalProgram();

private slots:
  void loadTree();
  void options();
  void functionEditor();
  void setWorkingDirectory();
  void startExternalProgram();
  void endExternalProgram(int, QProcess::ExitStatus);
  void addExternalOutput();
  void externalError(QProcess::ProcessError error);
  void killExternalProgram();
};

#endif
