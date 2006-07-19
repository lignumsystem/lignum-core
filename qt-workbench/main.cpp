#include <QApplication>
#include "GLDrawer.h"
//#include "ui_qt_wb.h"

#include <QFont>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MyWidget : public QWidget
{
public:
  MyWidget(QWidget *parent = 0);
};

MyWidget::MyWidget(QWidget *parent)
  : QWidget(parent)
{
  QPushButton *quit = new QPushButton(tr("Quit"));
  quit->setFont(QFont("Times", 18, QFont::Bold));
  
  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
  GLDrawer *glDrawer = new GLDrawer(this);
  glDrawer->show();
  //  glDrawer->setGeometry(10, 40, 500, 500);
  glDrawer->updateGL();

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(quit);
  layout->addWidget(glDrawer);
  setLayout(layout);
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  //  GLDrawer glDrawer;
  //glDrawer.show();
  //glDrawer.updateGL();
  MyWidget widget;
  widget.resize(400, 400);
  widget.show();
  return app.exec();
} 

/*
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QDialog *window = new QDialog;
  Ui:: ui;
  ui.setupUi(window);
  
  window->show();
  return app.exec();
  }*/
