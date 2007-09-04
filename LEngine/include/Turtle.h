#ifndef TURTLE_H
#define TURTLE_H

#include <iostream>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>

using namespace std;
using namespace cxxadt;


// The  symbols the turtle understands are
//    Turn(a)     rotation round turtle up by angle 'a'
//    Pitch(a)    rotation round turtle left by angle 'a'
//    Roll(a)     rotation round turtle heading by angle 'a'
//    F(d)        move turtle forward distance 'd', create segment
//    Fd(d,r,rtop)move turtle forward distance 'd', create segment
//                that has length 'd', radius 'r' and top radius 'rtop'
//    f(d)        move turtle forward distance 'd', do not create segment
//    HRoll()     rotation round heading so that heading is horizontal
//                in world coordinates. Formally:  L = UpxH and U = HxL.
//    Hrz()       rotations of turtle HLU round horizontal, Hrz = UpxH,
//                so that turtle heading becomes horizontal in world coordinates.
//    Up()        rotations of turtle HLU round horizontal, so that turtle up
//                is pointing directly upwards in  world coordinates
//    HDir(a)     set the turtle heading to angle 'a' measured from world up
//                by rotating turtle HLU round horizontal
//    HUp(a)      conditionally set the turtle heading to angle 'a'
//                measured from world up: rotate turtle HLU round horizontal
//                if and only if turtle heading is pointing downwards
//                in world coordinates
//    H(x,y,z)    query turtle heading
//    L(x,y,z) 	  query turtle left
//    U(x,y,z)    query turtle up
//                Note that  lstringToLignum updates the  arguments of
//                H,L,U. After  derive arguments have  values they are
//                given or undefined.


//See also LsysteI.h for the implementation of the symbols
class Turtle{
  friend ostream& operator << (ostream& os, const Turtle& t);
  friend const PositionVector& GetHeading(const Turtle& t);
  friend const PositionVector& GetLeft(const Turtle& t);
  friend const PositionVector& GetUp(const Turtle& t);
  friend const Point& GetPoint(const Turtle& t);
  friend void SetPoint(Turtle& t, const Point& p);
 public:
  Turtle();       //Initial turtle heading up at point (0,0,0)
  Turtle(const Point& p);
  Turtle(const Turtle& t);
  Turtle(const Point& po, const PositionVector& heading, const PositionVector& left);
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
