#include <iostream>
#include <iomanip>
#include <RectangularCuboid.h>
///\file cuboid.cc
using namespace std;
using namespace cxxadt;
///\example{lineno} cuboid.cc
///\brief This program  demonstrates the use  of RectangularCuboid.
///To compile the program  type `c++ -DCUBOID -g -I../include -L../lib -lcxxadt cuboid.cc -o cuboid` in the
///command line. The program creates RectangularCuboid object together with a set of points and
///tests if these points are inside the cuboid.

#ifdef CUBOID
int main()
{
  Point pll(0,0,0);
  Point pur(20,30,20);
  Point p1(5,10,0);
  Point p2(-5,10,10);
  Point p3(5,-1,10);
  Point p4(5,5,-0.000001);
  Point p5(25,10,10);
  Point p6(0.0001,1,1);
  Point p7(19.99999999,29.99999999,19.99999999);
  Point p8(1,15,20.0000001);
    
  RectangularCuboid cuboid(pll,pur);

  std::cout << std::fixed << std::setprecision(8);
  
  bool inside = cuboid.insideVolume(p1);
  if (inside){
    cout << "Point" << " " << p1 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p1 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p2);
  if (inside){
    cout << "Point" << " " << p2 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p2 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p3);
  if (inside){
    cout << "Point" << " " << p3 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p3 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p4);
  if (inside){
    cout << "Point" << " " << p4 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p4 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p5);
  if (inside){
    cout << "Point" << " " << p5 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p5 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p6);
  if (inside){
    cout << "Point" << " " << p6 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p6 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p7);
  if (inside){
    cout << "Point" << " " << p7 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p7 << " outside " <<endl;
  }
  inside = cuboid.insideVolume(p8);
  if (inside){
    cout << "Point" << " " << p8 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p8 << " outside " <<endl;
  }
  return 0;
}
#endif
