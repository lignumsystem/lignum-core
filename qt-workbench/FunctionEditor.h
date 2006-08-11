#ifndef FUNCTIONEDITOR_H
#define FUNCTIONEDITOR_H

#include <QMainWindow>
#include "FunctionPainter.h"
#include "func_edit.h"

class FunctionEditor : public QMainWindow {
  Q_OBJECT

public:

  FunctionEditor(QWidget *parent = 0);

private slots: 
  void openFile();
  void updateFunction();
  void saveFile();
  void saveFileAs();
  

private: 
  FunctionPainter *f_painter;
  Ui::FunctionEditor ui;
  QString fileName;

};

#endif
