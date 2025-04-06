/// \example{lineno} TriangleExample.cc
/// Test Triangle interface.
/// To compile (on Mac) type. 
///
///       clang++  -DTRIANGLE -I../include -L../lib -lcxxadt TriangleExample.cc
///
/// libcxxadt.a must also be compiled with clang++.
#ifdef TRIANGLE
#include <iostream>
#include <stdlib.h>
#include <Point.h>
#include <PositionVector.h>
#include <Triangle.h>
using namespace cxxadt;

void printing(const  Point& p){
  
  cout<<"----------------------------------------------"<<endl;
  cout<< "x=" << p.getX()<< "  y=" << p.getY()<< "  z=" << p.getZ()<<endl;
  cout<<"----------------------------------------------"<<endl;
}

void TestIntersection(int i, const Point& o, const PositionVector& l, const Triangle& t)
{
  cout << "Test " << i << endl;
  cout<<"From point " <<o<< " the beam vector "<<l;
  if (t.intersectShape(o,l) ) 
    cout<<" crosses the triangle at point "<< t.intersectionPoint(o,l) << endl;
  else
    cout<<" does not cross the triangle at point "<< t.intersectionPoint(o,l) << endl;
}

int main()
{
  
  Point p1=Point(0,0,1);
  Point p2=Point(2.0,0.0,1.0);
  Point p3=Point(2.0,4.0,1.0);
  Triangle t1(p1,p2,p3);
  Triangle t2(p1,p2,p3);
  Triangle t12(Point(0,0,2),Point(2.0,0.0,2.0),Point(2.0,4.0,2.0));
  vector<Point> points1;
  points1=t1.getVertexVector(points1);

  cout<<"----------------------------------------------"<<endl;
  cout << "The triangle points are   "<< endl;
    
  for_each(points1.begin(),points1.end(),printing);   
  
  cout << "For these points  " << endl;  
  cout << "Area is   " << t1.getArea() << endl;
  cout << "Center is " << t1.getCenterPoint().getX()
       << endl;
  cout <<"Normal vector is "<<t1.getNormal()
       <<endl<<endl;
  cout << "----------------------------------------------"<<endl;
  cout << "Scaling the triangle" <<endl; 
  Point base=Point(2.0,0.0,0.0);
  t2.setArea(2.0, base );
  cout << "After scaling the triangle  " << endl;
  cout << "Area is   " <<     t2.getArea() << endl;
  cout << "Center is " <<     t2.getCenterPoint().getX() << endl;
  cout << "Normal vector is "<<t2.getNormal() <<endl;
  vector<Point> points2;
  points2=t2.getVertexVector(points2);
  for_each(points2.begin(),points2.end(),printing);   
  cout<<endl;
  cout<<"----------------------------------------------"<<endl;
  
  cout << "Checking intersection with triangle" << endl;
  for_each(points1.begin(),points1.end(),printing);   

  Point o=Point(0.0,0.0,0.0);
  Point o1=Point(0.5,0.1,0.0);
  Point o2=Point(2,0,0);
  Point o3=Point(2,4,0);
  Point o4=Point(0,1,0);
  Point o5=Point(1.9,0.2,0);
  Point o6=Point(0,4,0);
  Point o7(2,3.999999999,0);
  Point o8(1e-19,0,0);
  Point o9(1e-20,0,0);
  PositionVector b1(0,1,3);
  b1.normalize();
  PositionVector b2(1,1,1);
  b2.normalize();
  PositionVector b3(1,1,-1);
  b3.normalize();
  PositionVector b4(1,1,0.01);
  b4.normalize();
  PositionVector b5(1,1,0.1);
  b5.normalize();
  PositionVector b6(1,1,0.2);
  b6.normalize();
  PositionVector b7(1,1,0.5);
  b7.normalize();
  PositionVector b8(1,1,0.6);
  b8.normalize();
  PositionVector b9(0.00000001,0.00000001,1.0);
  b9.normalize();
  PositionVector b10(-0.00000001,-0.00000001,1.0);
  b10.normalize();
  PositionVector b11(0.0,0.0,1.0);
  b11.normalize();
  TestIntersection(1,o,b1,t1);
  TestIntersection(2,o,b2,t1);
  TestIntersection(3,o,b3,t1);
  TestIntersection(4,o,b4,t1);
  TestIntersection(5,o,b5,t1);
  TestIntersection(6,o,b6,t1);
  TestIntersection(7,o,b7,t1);
  TestIntersection(8,o,b8,t1);
  TestIntersection(9,o,b9,t1);
  TestIntersection(10,o,b10,t1);
  TestIntersection(11,o1,b11,t1);
  TestIntersection(12,o2,b11,t1);
  TestIntersection(13,o3,b11,t1);
  TestIntersection(14,o4,b11,t1);
  TestIntersection(15,o5,b11,t1);
  TestIntersection(16,o6,b11,t1);
  vector<Point> points12;
  points12 = t12.getVertexVector(points12);
  cout << "Checking intersection with triangle" << endl;
  for_each(points12.begin(),points12.end(),printing);
  TestIntersection(17,o,b11,t12);
  TestIntersection(18,o1,b11,t12);
  TestIntersection(19,o2,b11,t12);
  TestIntersection(20,o3,b11,t12);
  TestIntersection(21,o4,b11,t12);
  TestIntersection(22,o5,b11,t12);
  TestIntersection(23,o6,b11,t12);
  TestIntersection(24,o7,b11,t12);
  TestIntersection(25,o,b11,t12);
  TestIntersection(26,o8,b11,t12);
  TestIntersection(27,o9,b11,t12);
  Point lc(-1,0.0);
  Point rc(1,0,0);
  Point ac(0,1,0);
  Triangle t3(lc,rc,ac);

  cout << "Pitching Triangle A " << 180*(-PI_VALUE/2.0)/PI_VALUE << endl;
  cout << "Area before " << t3.getArea()<<endl;
  cout  << "A " << t3.getA() << " B " << t3.getB() << " C " << t3.getC()<<endl;
  t3.pitch(-PI_VALUE/2.0);
  cout  << "A " << t3.getA() << " B " << t3.getB() << " C " << t3.getC()<<endl;
  cout << "Area after " << t3.getArea() <<endl;
  cout << "Pitching A back" << 180*(PI_VALUE/2.0)/PI_VALUE << endl;
  t3.pitch(PI_VALUE/2.0);
  cout  << "A " << t3.getA() << " B " << t3.getB() << " C " << t3.getC()<<endl;
  cout << "Area after " << t3.getArea() <<endl<<endl;;

  Point lc1(-1,0.0);
  Point rc1(1,0,0);
  Point ac1(1,1,0);
  Triangle t4(lc1,rc1,ac1);

  cout << "Pitching triangle B " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t4.getArea() <<endl;
  cout  << "A " << t4.getA() << " B " << t4.getB() << " C " << t4.getC()<<endl;
  t4.pitch(-PI_VALUE/2.0);
  cout  << "A " << t4.getA() << " B " << t4.getB() << " C " << t4.getC()<<endl;
  cout << "Area after " << t4.getArea() <<endl;
  cout << "Pitching B back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t4.pitch(PI_VALUE/2.0);
  cout  << "A " << t4.getA() << " B "  << t4.getB() << " C " << t4.getC()<<endl;
  cout << "Area after " << t4.getArea() <<endl<<endl;

  Point lc2(0,1,0);
  Point rc2(1,0,0);
  Point ac2(1,1,0);
  Triangle t5(lc2,rc2,ac2);

  cout << "Pitching triangle C " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t5.getArea() <<endl;
  cout  << "A " << t5.getA() << " B " << t5.getB() << " C " << t5.getC()<<endl;
  t5.pitch(-PI_VALUE/2.0);
  cout  << "A " << t5.getA() << " B " << t5.getB() << " C " << t5.getC()<<endl;
  cout << "Area after " << t5.getArea() <<endl;
  cout << "Pitching C back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t5.pitch(PI_VALUE/2.0);
  cout  << "A " << t5.getA() << " B " << t5.getB() << " C " << t5.getC()<<endl;
  cout << "Area after " << t5.getArea() <<endl <<endl;

  Point lc3(-1,1,0);
  Point rc3(1,-1,0);
  Point ac3(2,2,0);
  Triangle t6(lc3,rc3,ac3);
  cout << "Pitching triangle D " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t6.getArea() <<endl;
  cout  << "A " << t6.getA() << " B " << t6.getB() << " C " << t6.getC()<<endl;
  t6.pitch(-PI_VALUE/2.0);
  cout  << "A " << t6.getA() << " B " << t6.getB() << " C " << t6.getC() << endl;
  cout << "Area after " << t6.getArea() <<endl;
  cout << "Pitching D back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t6.pitch(PI_VALUE/2.0);
  cout  << "A " << t6.getA() << " B " << t6.getB() << " C " << t6.getC()<<endl;
  cout << "Area after " << t6.getArea() <<endl <<endl;

  Point lc4(-4,2,0);
  Point rc4(-1,-1,0);
  Point ac4(2,2,0);
  Triangle t7(lc4,rc4,ac4);
  cout << "Pitching triangle E " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t7.getArea() <<endl;
  cout  << "A " << t7.getA() << " B " << t7.getB() << " C " << t7.getC()<<endl;
  t7.pitch(-PI_VALUE/2.0);
  cout  << "A " << t7.getA() << " B " << t7.getB() << " C " << t7.getC()<<endl;
  cout << "Area after " << t7.getArea() <<endl;
  cout << "Pitching E back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t7.pitch(PI_VALUE/2.0);
  cout  << "A " << t7.getA() << " B " << t7.getB() << " C " << t7.getC()<<endl;
  cout << "Area after " << t7.getArea() <<endl;
  cout << "Dist Apex and Right in E " << (ac4 || rc4) <<endl;

}
#endif
