#include "ConsoleWidget.h"
#include <QtGui>

ConsoleWidget::ConsoleWidget(QWidget *parent)
  : QWidget(parent), externalProgram(NULL) 
{
  ui.setupUi(this);

  // connections..
  connect(ui.console, SIGNAL(returnPressed()), this, SLOT(startExternalProgram()));
  connect(ui.runButton, SIGNAL(clicked()), this, SLOT(startExternalProgram()));
  connect(ui.killButton, SIGNAL(clicked()), this, SLOT(killExternalProgram()));
}

void ConsoleWidget::startExternalProgram() {
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

void ConsoleWidget::endExternalProgram(int exitCode, QProcess::ExitStatus exitStatus) {
  clearExternalProgram();
  delete externalProgram;
  externalProgram = NULL;
  if(exitStatus == QProcess::NormalExit)
    ui.textBrowser->append(QString("External program exited normally."));
  else
    ui.textBrowser->append(QString("External program crashed."));
}

void ConsoleWidget::addExternalOutput() {
  if(externalProgram != NULL)
    ui.textBrowser->append(QString(externalProgram->readAllStandardOutput()));
}

void ConsoleWidget::externalError(QProcess::ProcessError error) {
  ui.textBrowser->append(QString("Error running the external program. Exiting(%1).").arg(error));
  clearExternalProgram();
  externalProgram = NULL;
}

void ConsoleWidget::killExternalProgram() {
  if(externalProgram)
    externalProgram->kill();
  //  clearExternalProgram();
}

void ConsoleWidget::clearExternalProgram() {
  disconnect(externalProgram, SIGNAL(finished(int, QProcess::ExitStatus)),
	     this, SLOT(endExternalProgram(int, QProcess::ExitStatus)));
  disconnect(externalProgram, SIGNAL(readyReadStandardOutput()),
	     this, SLOT(addExternalOutput()));
  disconnect(externalProgram, SIGNAL(error(QProcess::ProcessError)),
	     this, SLOT(externalError(QProcess::ProcessError)));
}

void ConsoleWidget::printText(QString text) {
  ui.textBrowser->append(text);
}
