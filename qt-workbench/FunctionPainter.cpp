#include <FunctionPainter.h>
#include <QtGui>

using namespace std;

// Creates a new function painter widget used in the
// function editor.
FunctionPainter::FunctionPainter(QWidget* parent)
  :QWidget(parent), xMarginal(1.1), yMarginal(1.1), xTick(1.0), yTick(1.0),
      tickLength(4), circleSize(10) {
  emit xTicksChanged(xTick);
  emit yTicksChanged(yTick);
  emit minXChanged(0);
  emit maxXChanged(0);
  emit minYChanged(0);
  emit maxYChanged(0);
}

// Changes the function to displayed by the painter.
// Argument string contains the 2D-points of the function
// and the painter draws lines between adjacant points.
// Painter ignores comment lines starting with character #,
// but lines of that kind must be placed in the beginning of the
// string.  
void FunctionPainter::changeFunction(QString values) {
  // Parsing of the string is left for ParametricCurve-object to do
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
    xTick = (maxXValue - minXValue) / 10;
    yTick = (maxYValue - minYValue) / 10;
    if(xTick == 0)
      xTick = maxXValue / 10;
    if(yTick == 0)
      yTick = maxYValue / 10;
    emit xTicksChanged(xTick);
    emit yTicksChanged(yTick);  


    minXValue -= xTick;
    maxXValue += xTick; 
    minYValue -= yTick;
    maxYValue += yTick;
    
    xRange = maxXValue - minXValue;
    yRange = maxYValue - minYValue;
   
    emit minXChanged(minXValue);
    emit maxXChanged(maxXValue);
    emit minYChanged(minYValue);
    emit maxYChanged(maxYValue);
  }
  update();
}

void FunctionPainter::clear() {
  xTick = 1;
  yTick = 1;
  minXValue = -xTick;
  maxXValue = xTick;
  minYValue = -yTick;
  maxYValue = yTick;
  xRange = maxXValue - minXValue;
  yRange = maxYValue - minYValue;
  points.clear();
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
    // Positive axis
    int i = 1;
    while(i*xTick < maxXValue) {
      // Draw the ticks
      painter.drawLine(QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() + tickLength),
		       QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() - tickLength));
      // Draw the numbers beside the ticks
      QString text = QString("%1").arg(i*xTick);

      painter.drawText(QPoint((i*xTick - minXValue) / xRange * size().width() - tickLength/2 - text.size()*3,
			      size().height() + minYValue / yRange * size().height() + tickLength*4),
		       QString("%1").arg(i*xTick));
      i++;
    }

    // Negative axis
    i = -1;
    while(i*xTick > minXValue) {
      // Draw the ticks
      painter.drawLine(QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() + tickLength),
		       QPoint((i*xTick - minXValue) / xRange * size().width(),
			      size().height() + minYValue / yRange * size().height() - tickLength));
      // Draw the numbers beside the ticks
      QString text = QString("%1").arg(i*xTick);

      painter.drawText(QPoint((i*xTick - minXValue) / xRange * size().width() - tickLength/2 - text.size()*3,
			      size().height() + minYValue / yRange * size().height() + tickLength*4),
		       QString("%1").arg(i*xTick));
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
    // Positive axis 
    int i = 1;
    while(i*yTick < maxYValue) {
      // Draw the ticks
      painter.drawLine(QPoint(-minXValue / xRange * size().width() + tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()),
		       QPoint(-minXValue / xRange * size().width() - tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()));
      // Draw the number beside the ticks
      QString text = QString("%1").arg(i*yTick);

      painter.drawText(QPoint(-minXValue / xRange * size().width() - text.size()*6 - tickLength*3,
			      size().height() - (i*yTick - minYValue) / yRange * size().height() +
			      tickLength),
		       QString("%1").arg(i*yTick));
      i++;
    }

    // Negative axis
    i = -1;
    while(i*yTick > minYValue) {
      // Draw the ticks
      painter.drawLine(QPoint(-minXValue / xRange * size().width() + tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()),
		       QPoint(-minXValue / xRange * size().width() - tickLength,
			      size().height() - (i*yTick - minYValue) / yRange * size().height()));
      // Draw the numbers beside the ticks
      QString text = QString("%1").arg(i*yTick);

      painter.drawText(QPoint(-minXValue / xRange * size().width() - text.size()*6 - tickLength*3,
			      size().height() - (i*yTick - minYValue) / yRange * size().height() +
			      tickLength),
		       QString("%1").arg(i*yTick));
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

  // Draw the circles around the points
  if(points.size() > 2) {
    for(int i = 0; i < points.size() - 1; i+=2) {
      painter.drawArc(QRect((points[i] - minXValue) / xRange * size().width() - circleSize/2, 
			     size().height() - (points[i+1] - minYValue) / yRange * size().height() - circleSize/2,
			     circleSize, circleSize),
		       0, 16*360);
		       
		       

    }
  }
  
  //painter.setPen(QPen(Qt::black, 1, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin));
  
  

}

void FunctionPainter::setView(double minX, double minY, double maxX, double maxY) {
  if(minX <= maxX) {
    minXValue = minX;
    maxXValue = maxX;
    xRange = maxXValue - minXValue;
    emit minXChanged(minXValue);
    emit maxXChanged(maxXValue);
  }

  if(minY <= maxY) {
    minYValue = minY;
    maxYValue = maxY;
    yRange = maxYValue - minYValue;
    emit minYChanged(minYValue);
    emit maxYChanged(maxYValue);
  }
  update();
}

void FunctionPainter::setTicks(double width, double height) {
  xTick = width;
  yTick = height;
  emit xTicksChanged(xTick);
  emit yTicksChanged(yTick);
  update();
}

void FunctionPainter::setXTicks(double value) {
  xTick = value;
  emit xTicksChanged(xTick);
  update();
}

void FunctionPainter::setYTicks(double value) {
  yTick = value;
  emit yTicksChanged(yTick);
  update();
}

void FunctionPainter::setMinX(double value) {
  if(value < maxXValue) {
    minXValue = value; 
    xRange = maxXValue - minXValue;
  }
  emit minXChanged(minXValue);
  update();
}

void FunctionPainter::setMaxX(double value) {
  if(value > minXValue) {
    maxXValue = value;
    xRange = maxXValue - minXValue;
  }
  emit maxXChanged(maxXValue);
  update();
}

void FunctionPainter::setMinY(double value) {
  if(value < maxYValue) {
    minYValue = value;
    yRange = maxYValue - minYValue;
  }
  emit minYChanged(minYValue);
  update();
}

void FunctionPainter::setMaxY(double value) {
  if(value > minYValue) {
    maxYValue = value;
    yRange = maxYValue - minYValue;
  }
  emit maxYChanged(maxYValue);
  update();
}
