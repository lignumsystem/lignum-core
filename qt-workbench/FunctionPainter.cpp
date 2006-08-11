#include <FunctionPainter.h>
#include <QtGui>

using namespace std;


FunctionPainter::FunctionPainter(QWidget *parent)
: QWidget(parent), xMarginal(1.1), yMarginal(1.1), xTick(1.0), yTick(1.0),
  tickLength(4) {

}

void FunctionPainter::changeFunction(QString values) {
  function = ParametricCurve(values.toStdString(), 1);
  vector<double> t_points = function.getVector();
  if(t_points.size() > 2 && t_points.size() % 2 != 0) {
    points = t_points;

    minXValue = points[0];
    maxXValue = points[points.size()-3];
    
    minYValue = points[1];
    maxYValue = points[1];
    
    for(int i = 1; i < points.size() - 1; i += 2) {
      if(points[i] < minYValue)
	minYValue = points[i];
      else if(points[i] > maxYValue)
	maxYValue = points[i];
    }
    minXValue *= xMarginal;
    maxXValue *= xMarginal; 
    minYValue *= yMarginal;
    maxXValue *= yMarginal;
    
    xRange = maxXValue - minXValue;
    yRange = maxYValue - minYValue;
    
  }
  update();
}


void FunctionPainter::paintEvent(QPaintEvent *event) {
  // Create the painter object
  QPainter painter(this);

  // Set pen and brush parameters here

  // X-axis
  painter.drawLine(QPoint(0,
			  size().height() + minYValue / yRange * size().height()),
		   QPoint(size().width(),
			  size().height() + minYValue / yRange * size().height()));
  // Draw the ticks for x-axis
  if (size().height() + minYValue / yRange * size().height() + tickLength >= 0 &&
      size().height() + minYValue / yRange * size().height() - tickLength <= size().height()) {
    int i = 1;
    while(i*xTick < maxXValue) {
      painter.drawLine(QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() + tickLength),
		       QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() - tickLength));
      i++;
    }
    i = -1;
    while(i*xTick > minXValue) {
      painter.drawLine(QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() + tickLength),
		       QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() - tickLength));
      i--;
    }
  }

  // Y-axis
  painter.drawLine(QPoint(-minXValue / xRange * size().width(),
			  0),
		   QPoint(-minXValue / xRange * size().width(),
			  size().height()));

   // Draw the ticks for y-axis
  if (-minXValue / xRange * size().width() + tickLength >= 0 &&
      -minXValue / xRange * size().width() - tickLength <= size().width()) {
    int i = 1;
    while(i*yTick < maxYValue) {
      painter.drawLine(QPoint(-minXValue / xRange * size().width() + tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()),
		       QPoint(-minXValue / xRange * size().width() - tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()));
      i++;
    }
    i = -1;
    while(i*yTick > minYValue) {
      painter.drawLine(QPoint(-minXValue / xRange * size().width() + tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()),
		       QPoint(-minXValue / xRange * size().width() - tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()));
      i--;
    }
  }

  painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));

  // Draw the function
  if(points.size() > 2) {
    for(int i = 0; i < points.size() - 3; i+=2) {
      painter.drawLine(QPoint((points[i] - minXValue) / xRange * size().width(),
			      size().height() - (points[i+1] - minYValue) / yRange * size().height()),
		       QPoint((points[i+2] - minXValue) / xRange * size().width(),
			    size().height() - (points[i+3] - minYValue) / yRange * size().height()));
    }
  }
  
  //painter.setPen(QPen(Qt::black, 1, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin));
  
  

}

void FunctionPainter::setView(double minX, double minY, double maxX, double maxY) {
  if(minX <= maxX) {
    minXValue = minX;
    maxXValue = maxX;
    xRange = maxXValue - minXValue;
  }

  if(minY <= maxY) {
    minYValue = minY;
    maxYValue = maxY;
    yRange = maxYValue - minYValue;
  }
  update();
}

void FunctionPainter::setTicks(double width, double height) {
  xTick = width;
  yTick = height;
  update();
}
