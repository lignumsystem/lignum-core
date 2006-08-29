#include "VisualizationConfig.h"

#include <QDir>
#include <QFileDialog>


VisualizationConfig::VisualizationConfig(QWidget *parent)
  : QDialog(parent) {
  ui.setupUi(this);

  connect(ui.segmentButton, SIGNAL(clicked()), this, SLOT(loadSegmentFile()));
  connect(ui.leafButton, SIGNAL(clicked()), this, SLOT(loadLeafFile()));
  connect(ui.foliageButton, SIGNAL(clicked()), this, SLOT(loadFoliageFile()));
  
  connect(this, SIGNAL(segmentFileChanged(QString)), ui.segmentText, SLOT(setText(QString)));
  connect(this, SIGNAL(leafFileChanged(QString)), ui.leafText, SLOT(setText(QString)));
  connect(this, SIGNAL(foliageFileChanged(QString)), ui.foliageText, SLOT(setText(QString)));

  connect(ui.okButton, SIGNAL(clicked()), this, SLOT(applySettings()));
  connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

VisualizationConfig::~VisualizationConfig() {

}

void VisualizationConfig::setSettings(VisualizationParameters params) {
  if(params.useBSP())
    ui.bspBox->setCheckState(Qt::Checked);
  else
    ui.bspBox->setCheckState(Qt::Unchecked);

  if(params.useLeafTextures())
    ui.leaftexBox->setCheckState(Qt::Checked);
  else
    ui.leaftexBox->setCheckState(Qt::Unchecked);

  if(params.useWireframe())
    ui.wireBox->setCheckState(Qt::Checked);
  else
    ui.wireBox->setCheckState(Qt::Unchecked);

  if(params.useLighting())
    ui.lightBox->setCheckState(Qt::Checked);
  else
    ui.lightBox->setCheckState(Qt::Unchecked);
  
  if(params.useTexturing())
    ui.texBox->setCheckState(Qt::Checked);
  else
    ui.texBox->setCheckState(Qt::Unchecked);

  if(params.useBuds())
    ui.budBox->setCheckState(Qt::Checked);
  else
    ui.budBox->setCheckState(Qt::Unchecked);

  ui.srdetailBox->setValue(params.getSegmentRDetail());
  ui.shdetailBox->setValue(params.getSegmentHDetail());
  ui.ldetailBox->setValue(params.getLeafDetail());
  ui.budloBox->setValue(params.getBudLoDetail());
  ui.budlaBox->setValue(params.getBudLaDetail());
  ui.budsiBox->setValue(params.getBudSize());
  ui.foliageBox->setValue(params.getFoliageDetail());
  ui.fspacingBox->setValue(params.getFoliageSpacing());
  ui.petioleBox->setValue(params.getPetioleDetail());
  ui.petiolerBox->setValue(params.getPetioleRadius());

  
  ui.segmentText->setText(QString(params.getSegmentTextureFile().c_str()));
  ui.leafText->setText(QString(params.getLeafTextureFile().c_str()));
  ui.foliageText->setText(QString(params.getFoliageTextureFile().c_str()));
  

}

void VisualizationConfig::loadSegmentFile() {
  //segmentFile = 
  QString file = QFileDialog::getOpenFileName(this,
					      "Choose a file",
					      QDir::currentPath(),
					      "Images (*.png *.jpg *.xpm)");
  if(!file.isEmpty())
    emit segmentFileChanged(file);
}

void VisualizationConfig::loadLeafFile() {
  QString file = QFileDialog::getOpenFileName(this,
					      "Choose a file",
					      QDir::currentPath(),
					      "Images (*.png *.jpg *.xpm)");
  if(!file.isEmpty())
    emit leafFileChanged(file);
}

void VisualizationConfig::loadFoliageFile() {
  QString file = QFileDialog::getOpenFileName(this,
					      "Choose a file",
					      QDir::currentPath(),
					      "Images (*.png *.jpg *.xpm)");
  if(!file.isEmpty())
    emit foliageFileChanged(file);
}

void VisualizationConfig::applySettings() {
  VisualizationParameters params;
  params.setSegmentRDetail(ui.srdetailBox->value());
  params.setSegmentHDetail(ui.shdetailBox->value());
  params.setLeafDetail(ui.ldetailBox->value());
  params.setBudLoDetail(ui.budloBox->value());
  params.setBudLaDetail(ui.budlaBox->value());
  params.setBudSize(ui.budsiBox->value());
  params.setFoliageDetail(ui.foliageBox->value());
  params.setFoliageSpacing(ui.fspacingBox->value());
  params.setPetioleDetail(ui.petioleBox->value());
  params.setPetioleRadius(ui.petiolerBox->value());

  params.setSegmentTextureFile(ui.segmentText->text().toStdString());
  params.setLeafTextureFile(ui.leafText->text().toStdString());
  params.setFoliageTextureFile(ui.foliageText->text().toStdString());

  if(ui.bspBox->checkState() == Qt::Checked)
    params.setBSPUsage(true);
  else
    params.setBSPUsage(false);

  if(ui.leaftexBox->checkState() == Qt::Checked)
    params.setLeafTextureUsage(true);
  else
    params.setLeafTextureUsage(false);

  if(ui.wireBox->checkState() == Qt::Checked)
    params.setWireframeUsage(true);
  else
    params.setWireframeUsage(false);

  if(ui.lightBox->checkState() == Qt::Checked)
    params.setLightingUsage(true);
  else
    params.setLightingUsage(false);
  
  if(ui.texBox->checkState() == Qt::Checked)
    params.setTexturingUsage(true);
  else
    params.setTexturingUsage(false);

  if(ui.budBox->checkState() == Qt::Checked)
    params.setBudUsage(true);
  else
    params.setBudUsage(false);


  emit settingsChanged(params);
  accept();
}
