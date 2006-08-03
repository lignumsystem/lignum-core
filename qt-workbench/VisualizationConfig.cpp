#include "VisualizationConfig.h"

#include <QDir>
#include <QFileDialog>

VisualizationConfig::VisualizationConfig(QWidget *parent)
  : QDialog(parent) {
  ui.setupUi(this);
  connect(ui.segmentButton, SIGNAL(clicked()), this, SLOT(loadSegmentFile()));
  connect(ui.leafButton, SIGNAL(clicked()), this, SLOT(loadLeafFile()));
  
  connect(this, SIGNAL(segmentFileChanged(QString)), ui.segmentText, SLOT(setText(QString)));
  connect(this, SIGNAL(leafFileChanged(QString)), ui.leafText, SLOT(setText(QString)));

  connect(ui.okButton, SIGNAL(clicked()), this, SLOT(setSettings()));
  connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

}

void VisualizationConfig::loadSegmentFile() {
  //segmentFile = 
  QString file = QFileDialog::getOpenFileName(this,
					      "Choose a file",
					      QDir::currentPath(),
					      "Image files (*.png *.jpg *.xpm)");
  if(!file.isEmpty())
    emit segmentFileChanged(file);
}

void VisualizationConfig::loadLeafFile() {
  QString file = QFileDialog::getOpenFileName(this,
					      "Choose a file",
					      QDir::currentPath(),
					      "Image files (*.png *.jpg *.xpm)");
  if(!file.isEmpty())
    emit leafFileChanged(file);
}
