#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QProcess>
#include "console_window.h"

class ConsoleWidget : public QWidget
{
  Q_OBJECT

public:
  ConsoleWidget(QWidget *parent = 0);

public slots:
  void printText(QString text);

private slots:
  void startExternalProgram();
  void endExternalProgram(int, QProcess::ExitStatus);
  void addExternalOutput();
  void externalError(QProcess::ProcessError error);
  void killExternalProgram();

private:
  Ui::Console ui;
  QProcess *externalProgram;

  void clearExternalProgram();
};

#endif
