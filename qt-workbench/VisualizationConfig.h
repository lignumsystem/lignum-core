#ifndef VISUALIZATIONCONFIG_H
#define VISUALIZATIONCONFIG_H

#include "viz_config.h"
#include "VisualizationParameters.h"

class VisualizationConfig : public QDialog
{
  Q_OBJECT

public:
  VisualizationConfig(QWidget *parent = 0);
  void setSettings(VisualizationParameters params);
  ~VisualizationConfig();

private slots:
  void loadSegmentFile();
  void loadLeafFile();
  void loadFoliageFile();
  void applySettings();

signals:

  void segmentFileChanged(QString fileName);
  void leafFileChanged(QString fileName);
  void foliageFileChanged(QString fileName);
  void settingsChanged(VisualizationParameters params);

private:

  Ui::VisualizationConfig ui;
  VisualizationParameters parameters;

};

#endif
