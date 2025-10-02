#ifndef TURTLE_H
#define TURTLE_H
/// \file Turtle.h
/// \brief Implementation of the 3D turtle graphics
#include <iostream>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>

using namespace std;
using namespace cxxadt;


///\brief Turtle graphics
///
/// 3D Turtle graphics is a vector graphics where the
/// cursor (*turtle*) moves in 3D Euclidian space.
///
/// The  symbols the turtle understands are:
/// \arg \c Turn(a)     rotation round turtle up by angle 'a'
/// \arg \c   Pitch(a)    rotation round turtle left by angle 'a'
/// \arg \c   Roll(a)     rotation round turtle heading by angle 'a'
/// \arg \c   F(d)        move turtle forward distance 'd', create segment
/// \arg \c   Fd(d,r,rtop) move turtle forward distance 'd', create segment
///                that has length 'd', radius 'r' and top radius 'rtop'
/// \arg \c   f(d)        move turtle forward distance 'd', do not create segment
/// \arg \c   HRoll()     rotation round heading so that left is horizontal
///                in world coordinates. Formally:  L = UpxH and U = HxL.
/// \arg \c   Hrz()       rotations of turtle HLU round horizontal, Hrz = UpxH,
///                so that turtle heading becomes horizontal in world coordinates.
/// \arg \c   Up()        rotations of turtle HLU round horizontal, so that turtle up
///                is pointing directly upwards in  world coordinates
/// \arg \c   HDir(a)     set the turtle heading to angle 'a' measured from world up
///                by rotating turtle HLU round horizontal
/// \arg \c   HUp(a)      conditionally set the turtle heading to angle 'a'
///                measured from world up: rotate turtle HLU round horizontal
///                if and only if turtle heading is pointing downwards
///                in world coordinates
/// \arg \c   H(x,y,z)    query turtle heading
/// \arg \c   L(x,y,z) 	  query turtle left
/// \arg \c   U(x,y,z)    query turtle up
///                Note that  lstringToLignum updates the  arguments of
///                H,L,U. After  derive arguments have  values they are
///                given or undefined.
/// \arg \c   MoveTo(x,y,z) set turtle to given position Point(x,y,z), orientation not changed
/// \arg \c   GetPoint(x,y,z) get the position of the turtle (global coordinates)
/// \arg \c   SetHeadUp(hx,hy,hz,ux,uy,uz) set turtle heading to PositionVector(hx,hy,hz) and
///                  turtle up to PositionVector(ux,uy,uz). The vectors
///                  need  not  be   normalized  (they  are  normalized
///                  here). Turtle left is defined as Cross(turtle_up,heading).
///                  The turtle position is not changed.
///                  The module is ignored if
///                  1.  the angle  between heading  and up  is  not 90
///                  degrees (Dot product > R_EPSILON)
///                  2. the length of either of the two vectors is less than R_EPSILON
/// \arg \c  SetHead(hx,hy,hz) set  turtle  heading to  PositionVector(hx,hy,hz),
///                  the  turtle left will  be Cross(global_up,heading)
///                  and the turtle up will be Cross(heading,left)
///
///As a reminder U = H x L, L = U x H and H = L x U
///See also LSystemI.h for the implementation of the symbols
class Turtle{
  friend ostream& operator << (ostream& os, const Turtle& t);
  friend const PositionVector& GetHeading(const Turtle& t);
  friend const PositionVector& GetLeft(const Turtle& t);
  friend const PositionVector& GetUp(const Turtle& t);
  friend void SetHeading(Turtle& t, const PositionVector& h);
  friend void SetLeft(Turtle& t, const PositionVector& l);
  friend void SetUp(Turtle& t, const PositionVector& u);
  friend const Point& GetPoint(const Turtle& t);
  friend void SetPoint(Turtle& t, const Point& p);
 public:
  Turtle();       //Initial turtle heading up at point (0,0,0)
  Turtle(const Point& p);
  Turtle(const Turtle& t);
  Turtle(const Point& po, const PositionVector& heading, const PositionVector& left);
  Turtle& operator=(const Turtle& t);
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
