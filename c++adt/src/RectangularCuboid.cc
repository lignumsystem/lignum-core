#include <RectangularCuboid.h>

RectangularCuboid::RectangularCuboid(const Point& lower_left, const Point& upper_right)
{
  p0 = lower_left;
  p1 = Point(lower_left.getX(),upper_right.getY(),lower_left.getZ());
  p2 = Point(upper_right.getX(),upper_right.getY(),lower_left.getZ());
  p3 = Point(upper_right.getX(),lower_left.getY(),lower_left.getZ());
  p4 = Point(lower_left.getX(),lower_left.getY(),upper_right.getZ());
  p5 = Point(lower_left.getX(),upper_right.getY(),upper_right.getZ());
  p6 = upper_right;
  p7 = Point(upper_right.getX(),lower_left.getY(),upper_right.getZ());
  //Calculate dot products needed to determine if a point is inside
  //RectangularCuboid
  u = PositionVector(p0-p1);
  v = PositionVector(p0-p3);
  w = PositionVector(p0-p4);
  u0 = Dot(u,PositionVector(p0));  
  u1 = Dot(u,PositionVector(p1));
  v0 = Dot(v,PositionVector(p0));
  v3 = Dot(v,PositionVector(p3));
  w0 = Dot(w,PositionVector(p0));
  w4 = Dot(w,PositionVector(p4));
}

RectangularCuboid::RectangularCuboid(const Point& bll,const Point& bul,const Point& bur,const Point& blr,
				   const Point& tll,const Point& tul,const Point& tur,const Point& tlr)
  :p0(bll),p1(bul),p2(bur),p3(blr),p4(tll),p5(tul),p6(tur),p7(tlr)
{
  //Calculate dot products needed to determine if a point is inside RectangularCuboid
  u = PositionVector(p0-p1);
  v = PositionVector(p0-p3);
  w = PositionVector(p0-p4);
  u0 = Dot(u,PositionVector(p0));
  u1 = Dot(u,PositionVector(p1));
  v0 = Dot(v,PositionVector(p0));
  v3 = Dot(v,PositionVector(p3));
  w0 = Dot(w,PositionVector(p0));
  w4 = Dot(w,PositionVector(p4));
}


bool RectangularCuboid::insideVolume(const Point& p)
{
  double dot_up = Dot(u,PositionVector(p));
  double dot_vp = Dot(v,PositionVector(p));
  double dot_wp = Dot(w,PositionVector(p));
  double min_u0u1 = std::min(u0,u1);
  double max_u0u1 = std::max(u0,u1);
  double min_v0v3 = std::min(v0,v3);
  double max_v0v3 = std::max(v0,v3);
  double min_w0w4 = std::min(w0,w4);
  double max_w0w4 = std::max(w0,w4);
  //The dot products of point p with the vectors u,v,and w must be within the perimeter,
  //i.e. within the three min-max dot product values. The less or equal operator
  //includes also the perimeter line itself.
  return  ((min_u0u1 <= dot_up) && (dot_up <= max_u0u1) && (min_v0v3 <= dot_vp) && (dot_vp <= max_v0v3) &&
	   (min_w0w4 <= dot_wp) && (dot_wp <= max_w0w4));
}
