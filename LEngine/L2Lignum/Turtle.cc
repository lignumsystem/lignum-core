#include <Turtle.h>

//Initial turtle heading up at point (0,0,0)
Turtle::Turtle()
  :h(0,0,1),l(1,0,0),u(0,1,0),p(0,0,0)
{
}

//copy constructor
Turtle::Turtle(const Turtle& t)
  :h(t.h),l(t.l),u(t.u),p(t.p)
{
}

//Rotation round Up axis
Turtle& Turtle::turn(const RADIAN angle)
{
  Point o(0,0,0);
  h.rotate(o,u,angle);
  l.rotate(o,u,angle);
  
  return *this;
}

//Rotation round Left axis
Turtle& Turtle::pitch(const RADIAN angle)
{
  Point o(0,0,0);
  u.rotate(o,l,angle);
  h.rotate(o,l,angle);
  
  return *this;
}

//Rotation round Heading axis
Turtle& Turtle::roll(const RADIAN angle)
{
  Point o(0,0,0);
  u.rotate(o,h,angle);
  l.rotate(o,h,angle);
   
   return *this;
}

//Move the turtle forward,
//Units are in principle arbitrary, but 
//for LIGNUM we will use meters.
//p.x' = p.x + dh.x
//p.y' = p.y + dh.y
//p.z' = p.z + dh.z
Turtle& Turtle::forward(const double d)
{
  p = p + static_cast<Point> (d*h);
  return *this;
}

Turtle& Turtle::normalize()
{
  u.normalize();
  l.normalize();
  h.normalize();
  return *this;
}

const PositionVector& GetHeading(const Turtle& t)
{
  return t.h;
}

const Point& GetPoint(const Turtle& t)
{
  return t.p;
}

//print the status of the turtle
ostream& operator << (ostream& os, const Turtle& t)
{
  cout << endl;
  os << "H: " << t.h;
  os << "L: " << t.l;
  os << "U: " << t.u;
  os << "P: " << t.p;
  return os;
}

#ifdef TURTLE
#include <stdlib.h>


int main()
{
  Turtle t;
  cout << "Turtle : " << t << endl;

  t.forward(1.456);
  cout << "After forward 1.456 : " << t << endl;

  t.turn(PI_VALUE/2.0);
  cout << "After turn PI/2: " << t << endl;

  t.pitch(PI_VALUE/2.0);
  cout <<  "After pitch PI/2 : " << t << endl;
  
  t.roll(I_VALUE/2.0);
  cout <<  "After roll PI/2 : " << t << endl;

  t.forward(1.0);
  cout <<  "After forward 1.0: " << t << endl;

  exit(0);
}

#endif
