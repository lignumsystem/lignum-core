#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QtGui>
#include "ConsoleWidget.h"
#include <QDockWidget>

class ConsoleWindow : public QDockWidget
{
  Q_OBJECT

public:
  ConsoleWindow(QWidget *parent = 0);

public slots:
  void printText(QString text); 

private:
  ConsoleWidget *console_widget;
};

#endif

