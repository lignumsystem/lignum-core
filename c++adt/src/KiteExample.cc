/// \example{lineno} KiteExample.cc
/// Test Kite interface.
/// To compile (on Mac) type. 
///
///       clang++  -DKITE -I../include -L../lib -lcxxadt KiteExample.cc -o kitetest
///
/// libcxxadt.a must also be compiled and installed in -L/../lib with clang++. 

#ifdef KITE
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <cmath>
#include <Point.h>
#include <PositionVector.h>
#include <Kite.h>
using namespace cxxadt;

void printing(const  Point& p){
  
  cout<<"----------------------------------------------"<<endl;
  cout<< "x=" << p.getX()<< "  y=" << p.getY()<< "  z=" << p.getZ()<<endl;
  cout<<"----------------------------------------------"<<endl;
}

void TestKiteIntersection(int i, const Point& o, const PositionVector& l, const Kite& k)
{
  cout << "Test " << i << endl;
  cout<<"From point " << o << " the beam vector "<< l << flush;
  if (k.intersectShape(o,l)) {
    pair<Point,double> p_d = k.intersectionPoint(o,l);
    if (p_d.second >= 0.0){
      cout<<" crosses the Kite at point "<< p_d.first << " Direction " << PositionVector(p_d.first-o).normalize()  << " Distance " << p_d.second << endl;
    }
    else{
      cout<<" does not cross the Kite at point "<< p_d.first << " Direction " << PositionVector(p_d.first-o).normalize()  << " Distance (behind) " << p_d.second << endl;
    }
  }
  else{
    cout<<" does not cross the Kite" <<endl;
  }
}

int main()
{
  Point p1 = Point(0,-1,0);
  Point p2 = Point(-2,-1,4);
  Point p3 = Point(2,-1,4);
  Point p4 = Point(0,-1,6);
  Kite k1 = Kite(p1,p2,p3,p4);
  
  cout<< "----------------------------------------------"<<endl;
  cout << "The Kite points are   "<< endl;
  vector<Point> pv1;
  pv1=k1.getVertexVector(pv1);
  for_each(pv1.begin(),pv1.end(),printing);   
  cout << "For these points  " << endl;  
  cout << "Area is   " << k1.getArea() << endl;
  cout << "Center is " << k1.getCenterPoint()
       << endl;
  cout <<"Normal vector is "<<k1.getNormal()
       <<endl<<endl;
  
  cout << "Checking intersections with Kite" <<endl;
  cout<< "----------------------------------------------"<<endl;
  Point o1=Point(0,0,0);
  PositionVector d1=PositionVector(0,-0.4,1).normalize();
  TestKiteIntersection(1,o1,d1,k1);
  cout << "----------------------------------------------"<<endl;
  Point o2=Point(0,0,0);
  PositionVector d2=PositionVector(0,0.4,1).normalize();
  TestKiteIntersection(2,o2,d2,k1);
  cout << "----------------------------------------------"<<endl;
  Point o3=Point(0,3,0);
  PositionVector d3=PositionVector(0,-0.4,0.4).normalize();
  TestKiteIntersection(3,o3,d3,k1);
  cout << "----------------------------------------------"<<endl;
  Point o4=Point(0,3,0);
  PositionVector d4=PositionVector(0,0.4,0.4).normalize();
  TestKiteIntersection(4,o4,d4,k1);
  cout << "----------------------------------------------"<<endl;
  Point o5=Point(0,-0.9,1);
  PositionVector d5=PositionVector(0,-0.4,0.4).normalize();
  TestKiteIntersection(5,o5,d5,k1);
  cout << "----------------------------------------------"<<endl;
  Point o6=Point(0,-0.9,1);
  PositionVector d6=PositionVector(0,0.4,0.4).normalize();
  TestKiteIntersection(6,o6,d6,k1);
  cout << "----------------------------------------------"<<endl;
  Point o7=Point(0,-0.9,1);
  PositionVector d7=PositionVector(0.2,-0.4,0.4).normalize();
  TestKiteIntersection(7,o7,d7,k1);
  cout << "----------------------------------------------"<<endl;
  Point o8=Point(0,-0.9,1);
  PositionVector d8=PositionVector(0.2,0.4,0.4).normalize();
  TestKiteIntersection(8,o8,d8,k1);
  cout << "----------------------------------------------"<<endl;
  return 0;
}
#endif 
