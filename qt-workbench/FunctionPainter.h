#ifndef FUNCTIONPAINTER_H
#define FUNCTIONPAINTER_H

#include <QWidget>
#include <ParametricCurve.h>

using namespace cxxadt;

class FunctionPainter : public QWidget {
  Q_OBJECT
  
public:
  FunctionPainter(QWidget *parent = 0);
  void setView(double minX, double minY, double maxX, double maxY);
  void setTicks(double width, double height);

public slots:
  void changeFunction(QString values);


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
};

#endif
