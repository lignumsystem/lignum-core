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
  h.rotate(p,u,angle);
  l.rotate(p,u,angle);
  return *this;
}

//Rotation round Left axis
Turtle& Turtle::pitch(const RADIAN angle)
{
  u.rotate(p,l,angle);
  h.rotate(p,l,angle);
  return *this;
}

//Rotation round Heading axis
Turtle& Turtle::roll(const RADIAN angle)
{
   u.rotate(p,h,angle);
   l.rotate(p,h,angle);
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

  t.turn(PI_VALUE/2.0);
  cout << "After turn PI/2: " << t << endl;

  t.pitch(PI_VALUE/2.0);
  cout <<  "After pitch PI/2 : " << t << endl;
  
  t.roll(PI_VALUE/2.0);
  cout <<  "After roll PI/2 : " << t << endl;

  t.forward(1.0);
  cout <<  "After forward 1.0: " << t << endl;

  exit(0);
}

#endif
