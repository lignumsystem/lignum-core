
#include <QApplication>
#include "LignumWB.h"

// Main function for the Lignum Workbench.
// Basically just creates the main window
// and passes the control to Qt.
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  LignumWB *window = new LignumWB;
  window->show();
  
  return app.exec();
}
