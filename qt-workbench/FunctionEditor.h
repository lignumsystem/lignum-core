#ifndef FUNCTIONEDITOR_H
#define FUNCTIONEDITOR_H

#include <QMainWindow>
#include "func_edit.h"

class FunctionEditor : public QMainWindow {
  Q_OBJECT

public:

  FunctionEditor(QWidget *parent = 0);

private slots:
  void newFile();
  void openFile();
  void updateFunction();
  void saveFile();
  void saveFileAs();

private:
  void setWindowName();
  Ui::FunctionEditor ui;
  QString fileName;
  bool fileSaved;
};

#endif
