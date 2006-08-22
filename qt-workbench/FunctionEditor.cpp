#include "FunctionEditor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

FunctionEditor::FunctionEditor(QWidget *parent) 
  : QMainWindow(parent), fileSaved(false) {
  ui.setupUi(this);
  ui.f_painter->setTicks(1, 1);
  
  connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
  connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
  connect(ui.actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(closeProgram()));
  connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(updateFunction()));

  setAttribute(Qt::WA_DeleteOnClose);

  setWindowName();
}

void FunctionEditor::newFile() {
  if(!ui.textEdit->toPlainText().isEmpty() && !fileSaved) {
    int message = QMessageBox::question(this,
					QString("Save changes?"),
					QString("Do you want to save changes before starting a new file?"),
					QMessageBox::Yes,
					QMessageBox::No,
					QMessageBox::Cancel);
    if(message == QMessageBox::Cancel)
      return;
    else {
      if(message == QMessageBox::Yes) {
	saveFile();
      }
    }
  }
  fileSaved = false;
  fileName.clear();
  ui.textEdit->clear();
  ui.f_painter->clear();
  setWindowName();

}

void FunctionEditor::openFile() {
  if(!ui.textEdit->toPlainText().isEmpty() && !fileSaved) {
    int message = QMessageBox::question(this,
					QString("Save changes?"),
					QString("Do you want to save changes before opening a file?"),
					QMessageBox::Yes,
					QMessageBox::No,
					QMessageBox::Cancel);
    if(message == QMessageBox::Cancel)
      return;
    else {
      if(message == QMessageBox::Yes) {
	saveFile();
      }
    }
  }
  fileName = QFileDialog::getOpenFileName(this,
					  "Choose a file",
					  QDir::currentPath(),
					  "Function files (*.*)");
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;
    QString text(file.readAll());
    
    ui.textEdit->setPlainText(text);
    ui.f_painter->changeFunction(text);
    fileSaved = true;
    setWindowName();
  
  }
}

void FunctionEditor::saveFile() {
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;
    
    QTextStream out(&file);
    out << ui.textEdit->toPlainText();
    fileSaved = true;
    setWindowName();
  }
  else 
    saveFileAs();
}

void FunctionEditor::saveFileAs() {
  fileName = QFileDialog::getSaveFileName(this,
					  "Choose a filename to save under",
					  QDir::currentPath(),
					  "Function files  (*.*)");
  if(!fileName.isEmpty()) {
    /*    if(!fileName.endsWith(".fun"))
	  fileName.append(".fun");*/
    saveFile();
  }
}

void FunctionEditor::updateFunction() {
  ui.f_painter->changeFunction(ui.textEdit->toPlainText());
  fileSaved = false;
  setWindowName();
  //f_painter->setView(-5, -5, 5, 5);
}

void FunctionEditor::setWindowName() {
  if(fileName.isEmpty()) {
    setWindowTitle(QString("Function Editor - *untitled*"));
  }
  else {
    if(fileSaved)
      setWindowTitle(QString("Function Editor - %1").arg(fileName));
    else
      setWindowTitle(QString("Function Editor - %1*").arg(fileName));
  }
}

void FunctionEditor::closeProgram() {
  if(!ui.textEdit->toPlainText().isEmpty() && !fileSaved) {
    int message = QMessageBox::question(this,
					QString("Save changes?"),
					QString("Do you want to save changes before quitting?"),
					QMessageBox::Yes,
					QMessageBox::No,
					QMessageBox::Cancel);
    if(message == QMessageBox::Cancel)
      return;
    else {
      if(message == QMessageBox::Yes) {
	saveFile();
      }
    }
  }
  close();
}
