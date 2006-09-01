#include "HelpDialog.h"
#include <QFile>

HelpDialog::HelpDialog(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  QFile file(":/text/help.txt");
  setWindowTitle("Help");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QString text(file.readAll());
  ui.helpText->append(text);

  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
}
