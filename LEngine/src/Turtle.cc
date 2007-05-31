#include <Turtle.h>

//Initial turtle heading up at point (0,0,0)
Turtle::Turtle()
  :h(0,0,1),l(1,0,0),u(0,1,0),p(0,0,0)
{
}

//Initial turtle heading up at point p. Different trees start growing
//in different positions
Turtle::Turtle(const Point& p1)
  :h(0,0,1),l(1,0,0),u(0,1,0),p(p1)
{
}

//copy constructor
Turtle::Turtle(const Turtle& t)
  :h(t.h),l(t.l),u(t.u),p(t.p)
{
}

//Constructor specifying position & direction of heading and left
Turtle::Turtle(const Point& p, const PositionVector& h, const PositionVector& l):
 p(p), h(h), l(l)
{u = Cross(h,l);}


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

//Rotation round Heading axis so that
//Left becomes horizontal 
Turtle& Turtle::hroll()
{
  PositionVector up(0,0,1); //opposite to gravity
  PositionVector new_l = Cross(up,h);
  if (new_l.length() > R_EPSILON){
    l = Cross(up,h); //left becomes horizontal 
    l.normalize();
    u = Cross(h,l);  //adjust up
    u.normalize();
  }
   
  return *this;
}

//Rotations of  HLU round  horizontal (UpxH) so  that heading  will be
//horizontal (c.f. up)
Turtle& Turtle::hrz()
{
  Point o(0,0,0);
  PositionVector up(0,0,1);
  //Check heading not already horizontal 
  if (fabs(h.getZ()) > R_EPSILON){
    //angle  to up
    double angle = acos(Dot(up,h));
    //angle to horizontal
    angle = PI_VALUE/2.0 - angle;
    PositionVector horizontal = Cross(up,h);
    //Check that 'up' and 'h' not both up
    if (horizontal.length() > R_EPSILON){
      horizontal.normalize();
      h.rotate(o,horizontal,angle);
      l.rotate(o,horizontal,angle);
      u.rotate(o,horizontal,angle);
    }
    //If 'up' and 'h' both up then pitch(PI_VALUE/2.0)
    else{
      pitch(PI_VALUE/2.0);
    }
  }
  return *this;
}

//Set the  turtle heading direction pointing to  'angle'.  The 'angle'
//is measured from world up.  Rotate HLU round horizontal (UpxH) as in
//up and hrz
Turtle& Turtle::hdir(const RADIAN angle)
{ 
  Point o(0,0,0);
  PositionVector up(0,0,1);
  //heading angle from up to h
  double hangle = acos(Dot(up,h));
  //the amount of rotation required and the direction (the sign of the
  //subtraction)
  hangle = angle-hangle;
  PositionVector horizontal = Cross(up,h);
  horizontal.normalize();
  h.rotate(o,horizontal,hangle);
  l.rotate(o,horizontal,hangle);
  u.rotate(o,horizontal,hangle);
  return *this;
}

//As in hdir set the  turtle heading direction pointing to 'angle' but
//if and only if heading is pointing downwards The 'angle' is measured
//from world up.  Rotate HLU round horizontal (UpxH) as in up and hrz
Turtle& Turtle::hup(const RADIAN angle)
{ 
  Point o(0,0,0);
  PositionVector up(0,0,1);
  //Check if heading upwards in the world coordinates
  if (h.getZ() >= 0.0){
    return *this;
  }
  else{
    //heading angle from up to h
    double hangle = acos(Dot(up,h));
    //the amount of rotation required and the direction (the sign of the
    //subtraction)
    hangle = angle-hangle;
    PositionVector horizontal = Cross(up,h);
    horizontal.normalize();
    h.rotate(o,horizontal,hangle);
    l.rotate(o,horizontal,hangle);
    u.rotate(o,horizontal,hangle);
  }
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

//Rotate  turtle vectors  HLU to  make the  turtle to  look up  in the
//world coordinates (heading up)
Turtle& Turtle::up()
{
  Point o(0,0,0);
  PositionVector up(0,0,1);
  double angle = acos(Dot(up,h));  //angle from up to h
  //the  direction of  rotation, i.e.  the  sign of  angle, should  be
  //correct
  if (fabs(angle) > R_EPSILON){
    PositionVector horizontal = Cross(up,h);
    horizontal.normalize();
    u.rotate(o,horizontal,-angle);
    l.rotate(o,horizontal,-angle);//maintain turtle coordinate system 
    h.rotate(o,horizontal,-angle);
  }
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

const PositionVector& GetLeft(const Turtle& t)
{
  return t.l;
}

const PositionVector& GetUp(const Turtle& t)
{
  return t.u;
}

const Point& GetPoint(const Turtle& t)
{
  return t.p;
}

void SetPoint(Turtle& t, const Point& p)
{
  t.p = p;
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
