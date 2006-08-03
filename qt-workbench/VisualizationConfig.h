#ifndef VISUALIZATIONCONFIG_H
#define VISUALIZATIONCONFIG_H

#include "viz_config.h"
#include "VisualizationParameters.h"

class VisualizationConfig : public QDialog
{
  Q_OBJECT

public:
  VisualizationConfig(QWidget *parent = 0);

private slots:
  void loadSegmentFile();
  void loadLeafFile();
  
signals:

  void segmentFileChanged(QString fileName);
  void leafFileChanged(QString fileName);
  void setSettings();
  void settingsChanged(VisualizationParameters params);

private:

  Ui::VisualizationConfig ui;
  QString segmentFile;
  QString leafFile;
  bool useBSP;
  bool useLeafTextures;
  int segmentRDetail;
  int segmentHDetail;
  int leafDetail;

};

#endif
