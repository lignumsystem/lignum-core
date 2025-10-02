/// \example{lineno} Parallelogramexample.cc
/// Test Parallelogram interface.
/// To compile (on Mac) type: 
///
///       clang++  -DPARALLELOGRAM -I../include -L../lib -lcxxadt Parallelogram.cc ParallelogramExample.cc -o pgram
///
/// libcxxadt.a also compiled with clang++.
/// \sa PrintPGram Intersection
#include <string>
#include <Parallelogram.h>
using namespace cxxadt;
///Print Parallelogram 
void PrintPGram(const string& name, Parallelogram& pgram)
{
  Point a = pgram.getA();
  Point b = pgram.getB();
  Point c = pgram.getC();
  Point d = pgram.getD();
  cout << name << endl;
  cout << "N: " << pgram.getNormal() << endl;
  cout << "Area                : " << pgram.getArea() << endl;
  cout << "Area (with equation): " << (a||b)*(a||d)*sin(pgram.getAlpha()) <<endl;
  cout << "alpha: " << pgram.getAlpha() << endl;
  cout << "Center: " << pgram.getCenterPoint() << flush;
  cout << "Center with line ac: " << (a+c)/2.0;
  cout << "Center with line bd: " << (b+d)/2.0;
  cout << "a " << a << flush;
  cout << "b " << b << flush;
  cout << "c " << c << flush;
  cout << "d " << d << flush;
  cout << "a||b " << (a||b) << endl;
  cout << "c||d " << (c||d) << endl;
  cout << "b||c " << (b||c) << endl;
  cout << "a||d " << (a||d) << endl;
  cout <<endl;
}

///Test line - Parallelogram intersection. Create Parallelogram and an observation point below it.
///Create vertical line point horizontally and rotate it step by step 180 degrees. Each step
///test for line - plane intersection and line - Parallelogram intersection.
void Intersection(const string& name, Parallelogram& pgram, const Point& o, const PositionVector& beam,const PositionVector& raxis)
{
  //Rotate beam upwards and check for intersections
  cout << name <<endl;
  Point a = pgram.getA();
  Point b = pgram.getB();
  Point c = pgram.getC();
  Point d = pgram.getD();
  for (double deg=0; deg<= 180.0; deg=deg+10){
    PositionVector beam_tmp(beam);
    double rad = deg*PI_VALUE/180.0;
    beam_tmp.rotate(o,raxis,-rad);
    cout << "Angle of rotation: " << rad  << " Beam before rotation: " << beam << endl;
    bool intersect = pgram.intersectShape(o,beam_tmp);
    cout << "Calculated intersect at " << rad*180.0/PI_VALUE << " degree rotation " << " result " << intersect <<endl;
    cout << "N:                " << pgram.getNormal() << endl;
    cout << "Beam:             " << beam_tmp << endl;
    cout << "Beam normalized   " << PositionVector(beam_tmp).normalize() <<endl;
    cout << "Observation point " << o << flush;
    cout << "Area:               : " << pgram.getArea() << endl;
    cout << "Area (with equation): " << (a||b)*(a||d)*sin(pgram.getAlpha()) <<endl;
    cout << "alpha: " << pgram.getAlpha() << endl;
    cout << "Center: " << pgram.getCenterPoint() << flush;
    cout << "Center with line ac: " << (a+c)/2.0;
    cout << "Center with line bd: " << (b+d)/2.0;
    cout << "a " << a << flush;
    cout << "b " << b << flush;
    cout << "c " << c << flush;
    cout << "d " << d << flush;
    double cosalpha = Dot(pgram.getNormal(),beam_tmp);
    if (fabs(cosalpha) < EPS15){
      cout << "No intersect plane " << deg << " " << fabs(cosalpha) << " " << EPS15 << endl;
    }
    else{
      Point p = pgram.intersectionPoint(o,beam_tmp);
      cout << "Intersect plane         " << deg << " degrees" << endl;
      cout << "Point "  << p << flush;
    }
    if (intersect){
      cout << "Intersect Paralellogrm " << deg << " degrees" << endl;
      Point p = pgram.intersectionPoint(o,beam_tmp);
      cout << "p " << p <<flush;
    }
    else{
      cout << "No intersect with Parallelogram" <<endl;
    }
    cout << "----" << endl;
  }
}

#ifdef PARALLELOGRAM
int main()
{ //STL library std::numbers is (will be) in C++20.
  //const double pi_v = std::numbers::pi;
  Parallelogram pgram0(Point(1,0,0),Point(1,5,2),Point(6,5,2),Point(6,0,0));
  Parallelogram pgram1(Point(1,0,0),Point(0,5,2),Point(5,5,2),Point(6,0,0));
  Parallelogram pgram2(Point(1,1,1),Point(1,5,3),Point(6,1,1));
  Parallelogram pgram3(Point(1,0,0),Point(1,5,2),Point(6,0,0));
  Parallelogram pgram4(2.0,Point(1,0,1),PositionVector(0,1,0),PI_VALUE/4.0,1.0,false);
  Parallelogram pgram5(3.1,Point(0,1,0),PositionVector(1,1,1),PI_VALUE/4.0,1.0,false);
  Parallelogram pgram6(3.1,Point(1,0,0),PositionVector(0,1,0),PI_VALUE/4.0,0.5,false);
  Parallelogram pgram7(3.0,Point(1,0,0),PositionVector(0,1,0),PI_VALUE/4.0,1.0,false);
  Parallelogram pgram8(4.5,Point(0,0,0),PositionVector(0,1,0),PI_VALUE/4.0,1.0,false);
  Parallelogram pgram9(6.0,Point(0,0,1),PositionVector(0,0,1),PI_VALUE/4.0,1.0,false);
  Parallelogram pgram10(7.0,Point(-1,-1,2),PositionVector(1,1,1),PI_VALUE/4.0,1.0,false);
  Point o(0.0,0.0,0.0);
  PositionVector beam(1,0,0);
  PositionVector raxis(0,1,0);
  PositionVector beam1(1,1,0);
  PositionVector raxis1(Cross(PositionVector(0,0,1),beam1));

  PrintPGram("PGRAM0",pgram0);
  PrintPGram("PGRAM1",pgram1);
  PrintPGram("PGRAM2",pgram2);
  PrintPGram("PGRAM3",pgram3);
  PrintPGram("PGRAM4",pgram4);
  PrintPGram("PGRAM5",pgram5);
  PrintPGram("PGRAM6",pgram6);
  PrintPGram("PGRAM7",pgram7);
  pgram7.setArea(6.0);
  PrintPGram("PGRAM7 after setArea",pgram7);
  pgram7.pitch(PI_VALUE/2.0);
  PrintPGram("PGRAM7 after pitch down",pgram7);
  PrintPGram("PGRAM8",pgram8);
  pgram8.roll(PI_VALUE/2.0);
  PrintPGram("PGRAM8 after roll right",pgram8);
  Intersection("PGRAM9",pgram9,o,beam,raxis);
  Intersection("PGRAM10",pgram10,o,beam1,raxis1);
  exit(0);
}
#endif

