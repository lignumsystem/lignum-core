#include "FunctionEditor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

// Creates a new function editor.
FunctionEditor::FunctionEditor(QWidget *parent) 
  : QMainWindow(parent), fileSaved(false) {
  ui.setupUi(this);
  ui.f_painter->setTicks(1, 1);
  
  // Connecting signals
  connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
  connect(ui.actionNew_window, SIGNAL(triggered()), this, SLOT(newWindow()));
  connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
  connect(ui.actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
  connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(closeProgram()));
  connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(updateFunction()));

  // Clear memory when the window is closed
  setAttribute(Qt::WA_DeleteOnClose);

  setWindowName();
}

// Starts a blank file and asks whether to save the existing file first,
// if there is need to do so.
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

// Opens a new file to the editor. Pops a dialog where the user selects the
// file to open.
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

// Saves the current file in the editor.
void FunctionEditor::saveFile() {
  // If the file name is specified
  if(!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;
    
    QTextStream out(&file);
    out << ui.textEdit->toPlainText();
    fileSaved = true;
    setWindowName();
  }
  // If the file name is not specified
  else 
    saveFileAs();
}

// Asks the user a name for the file to be saved.
void FunctionEditor::saveFileAs() {
  fileName = QFileDialog::getSaveFileName(this,
					  "Choose a filename to save under",
					  QDir::currentPath(),
					  "Function files  (*.*)");
  if(!fileName.isEmpty()) {
    saveFile();
  }
  // Do nothing if the user didn't specify a file name
}

// Updates the painter
void FunctionEditor::updateFunction() {
  ui.f_painter->changeFunction(ui.textEdit->toPlainText());
  fileSaved = false;
  setWindowName();
}

//  Sets the title for the window according to the file name
//  of the file currently opened.
void FunctionEditor::setWindowName() {
  // File name not specified
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

// Closes the window. Asks the user whether to save changes before
// quitting.
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

// Creates a new editor window.
void FunctionEditor::newWindow() {
  FunctionEditor* function_editor = new FunctionEditor();
  function_editor->show();
  function_editor->raise();
  function_editor->activateWindow(); 
}
