#ifndef TURTLE_H
#define TURTLE_H

#include <iostream>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>

using namespace std;
using namespace cxxadt;

//See also LsysteI.h for the symbols to be used in L-file
class Turtle{
  friend ostream& operator << (ostream& os, const Turtle& t);
  friend const PositionVector& GetHeading(const Turtle& t);
  friend const Point& GetPoint(const Turtle& t);
  friend void SetPoint(Turtle& t, const Point& p);
 public:
  Turtle();       //Initial turtle heading up at point (0,0,0)
  Turtle(const Point& p);
  Turtle(const Turtle& t);
  Turtle& turn(const RADIAN a);//Turn(): rotation round up
  Turtle& pitch(const RADIAN a);//Pitch(): rotation round left
  Turtle& roll(const RADIAN a);//Roll(): rotation round heding
  Turtle& hroll();//HRoll(): rotation round heading so that left becomes horizontal 
  Turtle& hrz();//Hrz(): rotations  of  HLU so  that  turtle heading  becomes
		//horizontal in world coordinates
  Turtle& forward(const double d);//F() and f(): turtle forward
  Turtle& up();//Up():  rotations  of  HLU  round horizontal  so  that
	       //turtle   up  is   pointing  directly   up   in  world
	       //coordinates
  Turtle& hdir(const RADIAN a);//HDir():  set the  turtles  heading to
			       //angle 'a'  from world up,  rotate HLU
			       //round horizontal.
  Turtle& hup(const RADIAN a);//HUp():  set  the  turtles  heading  to
			      //angle 'a' from world up if and only if
			      //heading  is pointing downwards  in the
			      //world  coordinates,  rotate HLU  round
			      //horizontal
 private:
  Turtle& normalize();
  PositionVector h; //heading (z)
  PositionVector l; //left    (x)
  PositionVector u; //up      (y)
  Point p;          //position 
};

#endif
