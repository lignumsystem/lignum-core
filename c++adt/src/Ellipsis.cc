#include <Ellipsis.h>

namespace cxxadt{

//Construct ellipsis by giving semi major and semiminor axes
//and the center of the ellipsis
//All the computations will be done assuming 
//the ellipsis is cenetered at the origin
Ellipsis::Ellipsis(double a1, double b1)
{
  a = a1;
  b = b1;
  if(a1 > 0.0 && b1 > 0.0)
    b_div_a = b1/a1;
  else
    b_div_a = 1.0; //prevents from being stupid in constructing
}

double Ellipsis::getFocus()const
{
  return sqrt(pow(a,2.0) - pow(b,2.0));
}

//Set new area for ellipsis 
//The shape of the ellipsis
//is preserved by assuming that a/b = a1/b1.
double Ellipsis::setArea(double area)
{
//    double b_old = b;
//    double a_old = a;

//    a = sqrt((a*area)/(PI_VALUE*b));
//    b = (a*b_old)/a_old;


  a = sqrt(area/(PI_VALUE*b_div_a));
  b = b_div_a * a;

  return getArea();
}

double Ellipsis::setMajor(double a1)
{
  a = a1;
  if(a1 > 0.0 && b > 0.0)
    b_div_a = b / a1;
  else
    b_div_a = 1.0;

  return a;
}

double Ellipsis::setMinor(double b1)
{
  b = b1;
  if(b1 > 0.0 && a > 0.0)
    b_div_a = b1 / a;
  else
    b_div_a = 1.0;
  return b;
}

}//closing namespace cxxadt

#ifdef ELLIPSIS
#include <stream.h>
#include <stdlib.h>
using namespace cxxadt;
int main()
{
  Ellipsis e1(3.0,1.0);
  cout << "Area    " <<"Major axis  " << "Minor axis " << "Focus  " << endl;

  cout << e1.getArea() << "  " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;
  
  e1.setArea(10.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;
  
  e1.setArea(11.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() <<endl;

  e1.setArea(12.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;

  e1.setArea(13.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;

  e1.setArea(50.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl; 

  e1.setArea(100.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;

  e1.setArea(500.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;
  
  e1.setArea(1000.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;

  e1.setArea(9.42478);
  
  cout << e1.getArea() << " " << e1.getSemimajorAxis() << " " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl;

  e1.setArea(2.0);

  cout << e1.getArea() << " " << e1.getSemimajorAxis() << "  " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl; 

  e1.setArea(1.0);
  
  cout << e1.getArea() << " " << e1.getSemimajorAxis() << "  " 
       << e1. getSemiminorAxis() << " " << e1.getFocus() << endl; 
  
  exit(0);
}


#endif



