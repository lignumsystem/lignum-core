#include "FunctionEditor.h"

#include <QFileDialog>
#include <QTextStream>

FunctionEditor::FunctionEditor(QWidget *parent) 
  : QMainWindow(parent) {
  ui.setupUi(this);
  f_painter = new FunctionPainter(this);
  f_painter->show();
  f_painter->setGeometry(5, 30, 400, 400);
  // f_painter->changeFunction(QString("-2 2 -0.2 -3.1 0.5 0.5 1.0 2.0 1.5 0.5"));
  //  f_painter->setView(-5, -5, 5, 5);
  f_painter->setTicks(0.5, 0.5);
  
  connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
  connect(ui.actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui.updateButton, SIGNAL(clicked()), this, SLOT(updateFunction()));
  connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(updateFunction()));
}

void FunctionEditor::openFile() {
  fileName = QFileDialog::getOpenFileName(this,
					  "Choose a file",
					  QDir::currentPath(),
					  "Function files (*.fun)");
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;
    QString text(file.readAll());
    
    ui.textEdit->setPlainText(text);
    f_painter->changeFunction(text);
  }
}

void FunctionEditor::saveFile() {
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;
    QTextStream out(&file);
    out << ui.textEdit->toPlainText();
  }
  else 
    saveFileAs();
}

void FunctionEditor::saveFileAs() {
  fileName = QFileDialog::getSaveFileName(this,
					  "Choose a filename to save under",
					  QDir::currentPath(),
					  "Function files  (*.fun)");
  if(!fileName.isEmpty()) {
    if(!fileName.endsWith(".fun"))
      fileName.append(".fun");
    saveFile();
  }
}

void FunctionEditor::updateFunction() {
  f_painter->changeFunction(ui.textEdit->toPlainText());
  //f_painter->setView(-5, -5, 5, 5);
}
