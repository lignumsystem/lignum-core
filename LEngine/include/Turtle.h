#ifndef TURTLE_H
#define TURTLE_H

#include <iostream>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>

using namespace std;
using namespace cxxadt;


class Turtle{
  friend ostream& operator << (ostream& os, const Turtle& t);
  friend const PositionVector& GetHeading(const Turtle& t);
  friend const Point& GetPoint(const Turtle& t);
  friend void SetPoint(Turtle& t, const Point& p);
 public:
  Turtle();       //Initial turtle heading up at point (0,0,0)
  Turtle(const Point& p);
  Turtle(const Turtle& t);
  Turtle& turn(const RADIAN a);
  Turtle& pitch(const RADIAN a);
  Turtle& roll(const RADIAN a);
  Turtle& hroll();
  Turtle& forward(const double d);
 private:
  Turtle& normalize();
  PositionVector h; //heading (z)
  PositionVector l; //left    (x)
  PositionVector u; //up      (y)
  Point p;          //position 
};

#endif
