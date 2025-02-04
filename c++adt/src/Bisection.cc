#include <Bisection.h>
#include <iostream>

using namespace cxxadt;
///Linear function, 1st order
class F1{
public:
  F1(double a0,double b0):a(a0),b(b0){}
  ///Example oveloaded function operator for Bisection, single argument 
  double operator()(double x){
    return a*x + b;
  }
private:
  double a,b;
};

///Parabolic function, 2nd order
class F2{
public:
  F2(double a0,double b0,double c0):a(a0),b(b0),c(c0){}
  ///Example oveloaded function operator for Bisection, single argument 
  double operator()(double x){
    return a*pow(x,2.0) + b*x + c;
  }
private:
  double a,b,c;
};

///Cubic function, 3rd order
class F3{
public:
  F3(double a0,double b0,double c0,double d0):a(a0),b(b0),c(c0),d(d0){}
  ///Example oveloaded function operator for Bisection, single argument 
  double operator()(double x){
    return a*pow(x,3.0) + b*pow(x,2.0) + x*c +d;
  }
private:
  double a,b,c,d;
};



/// \example{lineno} Bisection.cc
/// Examples to test the Bisection function method with linear, parabolic and cubic functions.
/// To compile type:
///
/// `c++ -DBISECTIONMAIN -I../include -lm Bisection.cc -o bisection`
///
/// Run the `bisection` binary.
#ifdef BISECTIONMAIN
int main()
{
  F3 f31(-1,1,1,100);
  F2 f21(1,1,-10);
  F1 f11(5,6);

  cout << "Testing Bisection only: " << endl; 
  double c = Bisection(-5.0,1000.0,f31);
  cout << "Root f(-1,1,1,100) [-5,1000]: " << c << endl;
  cout << "f(c): " << f31(c) << endl;

  c =  Bisection(-5.0,2.0,f21);
  cout << "Root f(1,1,-10) [-5,2]: " << c << endl;  
  cout << "f(c): " << f21(c) << endl;

  c = Bisection(-2.0,-1.0,f11);
  cout << "Root f(5,6): [-2,-1]: " << c << endl;
  cout << "f(c): " << f11(c) << endl;

  cout << "Testing bracketing and Bisection" << endl;
  c = Bisection(-15.0,-10.0,f31);
  cout << "Root f(-1,1,1,100) [-15,-10]: " << c << endl;
  cout << "f(c): " << f31(c) << endl;

  c =  Bisection(-7.0,-5.0,f21);
  cout << "Root f(1,1,-10) [-7,-5.0]: " << c << endl;  
  cout << "f(c): " << f21(c) << endl;
  
  c = Bisection(-200.0,-100.0,f11);
  cout << "Root f(5,6): [-200,-100]: " << c << endl;
  cout << "f(c): " << f11(c) << endl;

  return 0;
}

#endif
