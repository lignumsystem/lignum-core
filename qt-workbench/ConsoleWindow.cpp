#include <QtGui>

#include "ConsoleWindow.h"
#include "ConsoleWidget.h"


ConsoleWindow::ConsoleWindow(QWidget *parent)
  : QDockWidget(parent)
{
  console_widget = new ConsoleWidget(this);
  setWidget(console_widget);
  setWindowTitle("Console");
  resize(100, 120);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  setAllowedAreas(Qt::BottomDockWidgetArea);

  //SIGNAL/SLOT CONNECTIONS...
}

void ConsoleWindow::printText(QString text) {
  if(console_widget)
    console_widget->printText(text);
}
