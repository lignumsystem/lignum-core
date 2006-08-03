#ifndef LIGNUMWB_H
#define LIGNUMWB_H

#include <QMainWindow>
#include "qt_wb.h"
#include "VisualizationConfig.h"

class LignumWB : public QMainWindow
{
  Q_OBJECT

public:
  LignumWB(QWidget *parent = 0);

private:
  Ui::MainWindow ui;
  VisualizationConfig* viz_config;

private slots:
  void loadTree();
  void options();
  
};

#endif
