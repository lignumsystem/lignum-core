#ifndef XMLVIEWERWIDGET_H
#define XMLVIEWERWIDGET_H

#include <QWidget>

#include "xml_viewer.h"

class XMLViewerWidget : public QWidget
{
  Q_OBJECT

public:
  XMLViewerWidget(QWidget *parent = 0);

signals:
  void sceneObjectsSelected(QHash<QString, QList<int> >);
  void fileAdded(QString);
  void updateVisualization(QList<QString>);
  void textOutput(QString);
  void setFocus(Point, PositionVector, double);
private slots:
  void addTree();

private:
  Ui::TreeViewer ui;
};

#endif
