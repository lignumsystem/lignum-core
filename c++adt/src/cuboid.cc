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
  Point pll1(0,0,0);
  Point pur1(20,30,20);
  Point pll2(2,2,0);
  Point pur2(22,32,20);
  Point pll3(-2,-2,0);
  Point pur3(18,28,20);
  Point p1(5,10,0);
  Point p2(-5,10,10);
  Point p3(5,-1,10);
  Point p4(5,5,-0.000001);
  Point p5(25,10,10);
  Point p6(0.0001,1,1);
  Point p7(19.99999999,29.99999999,19.99999999);
  Point p8(1,15,20.0000001);
  Point p9(2.00001,31.99999,19.99999);
  Point p10(2,32.000001,20);
  RectangularCuboid cuboid1(pll1,pur1);
  RectangularCuboid cuboid2(pll2,pur2);
  RectangularCuboid cuboid3(pll3,pur3);
  
  std::cout << std::fixed << std::setprecision(8);

  cout << "RectangularCuboid  LL " << pll1 << " UR " << pur1 << endl;
  bool inside = cuboid1.insideVolume(p1);
  if (inside){
    cout << "Point" << " " << p1 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p1 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p2);
  if (inside){
    cout << "Point" << " " << p2 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p2 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p3);
  if (inside){
    cout << "Point" << " " << p3 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p3 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p4);
  if (inside){
    cout << "Point" << " " << p4 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p4 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p5);
  if (inside){
    cout << "Point" << " " << p5 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p5 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p6);
  if (inside){
    cout << "Point" << " " << p6 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p6 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p7);
  if (inside){
    cout << "Point" << " " << p7 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p7 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p8);
  if (inside){
    cout << "Point" << " " << p8 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p8 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p9);
  if (inside){
    cout << "Point" << " " << p9 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p9 << " outside " <<endl;
  }
  inside = cuboid1.insideVolume(p10);
  if (inside){
    cout << "Point" << " " << p10 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p10 << " outside " <<endl;
  }
  
  cout << "RectangularCuboid LL " << pll2 << " UR " << pur2 << endl;
  inside = cuboid2.insideVolume(p1);
  if (inside){
    cout << "Point" << " " << p1 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p1 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p2);
  if (inside){
    cout << "Point" << " " << p2 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p2 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p3);
  if (inside){
    cout << "Point" << " " << p3 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p3 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p4);
  if (inside){
    cout << "Point" << " " << p4 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p4 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p5);
  if (inside){
    cout << "Point" << " " << p5 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p5 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p6);
  if (inside){
    cout << "Point" << " " << p6 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p6 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p7);
  if (inside){
    cout << "Point" << " " << p7 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p7 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p8);
  if (inside){
    cout << "Point" << " " << p8 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p8 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p9);
  if (inside){
    cout << "Point" << " " << p9 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p9 << " outside " <<endl;
  }
  inside = cuboid2.insideVolume(p10);
  if (inside){
    cout << "Point" << " " << p10 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p10 << " outside " <<endl;
  }

  cout << "RectangularCuboid LL " << pll3 << " UR " << pur3 << endl;
  inside = cuboid3.insideVolume(p1);
  if (inside){
    cout << "Point" << " " << p1 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p1 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p2);
  if (inside){
    cout << "Point" << " " << p2 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p2 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p3);
  if (inside){
    cout << "Point" << " " << p3 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p3 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p4);
  if (inside){
    cout << "Point" << " " << p4 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p4 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p5);
  if (inside){
    cout << "Point" << " " << p5 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p5 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p6);
  if (inside){
    cout << "Point" << " " << p6 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p6 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p7);
  if (inside){
    cout << "Point" << " " << p7 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p7 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p8);
  if (inside){
    cout << "Point" << " " << p8 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p8 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p9);
  if (inside){
    cout << "Point" << " " << p9 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p9 << " outside " <<endl;
  }
  inside = cuboid3.insideVolume(p10);
  if (inside){
    cout << "Point" << " " << p10 << " inside " <<endl;
  }
  else{
    cout << "Point" << " " << p10 << " outside " <<endl;
  }
  return 0;
}
#endif
