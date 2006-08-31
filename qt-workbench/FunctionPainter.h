#ifndef FUNCTIONPAINTER_H
#define FUNCTIONPAINTER_H

#include <QWidget>
#include <ParametricCurve.h>

using namespace cxxadt;

class FunctionPainter : public QWidget {
  Q_OBJECT
  
public:
  FunctionPainter(QWidget *parent);

  void setView(double minX, double minY, double maxX, double maxY);
  void setTicks(double width, double height);

public slots:
  void clear();
  void changeFunction(QString values);
  void setXTicks(double value);
  void setYTicks(double value);
  void setMinX(double value);
  void setMaxX(double value);
  void setMinY(double value);
  void setMaxY(double value);

signals:
  void xTicksChanged(double value);
  void yTicksChanged(double value);
  void minXChanged(double value);
  void maxXChanged(double value);
  void minYChanged(double value);
  void maxYChanged(double value);


protected:
  void paintEvent(QPaintEvent *event);

private: 
  ParametricCurve function;
  double xRange, yRange;
  double minXValue, maxXValue;
  double minYValue, maxYValue;
  vector<double> points;
  double xMarginal, yMarginal;
  double xTick, yTick;
  int tickLength;
  int circleSize;
};

#endif
