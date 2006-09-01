#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QMainWindow>
#include "help.h"

class HelpDialog : public QMainWindow {
  Q_OBJECT

public:

  HelpDialog(QWidget* parent = 0);

private: 

  Ui::HelpWindow ui;
  
};

#endif
