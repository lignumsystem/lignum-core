#include <Bisection.h>
#include <iostream>
using namespace cxxadt;
class F1{
public:
  F1(double a0,double b0):a(a0),b(b0){}
  double operator()(double x){
    return a*x + b;
  }
private:
  double a,b;
};

class F2{
public:
  F2(double a0,double b0,double c0):a(a0),b(b0),c(c0){}
  double operator()(double x){
    return a*pow(x,2.0) + b*x + c;
  }
private:
  double a,b,c;
};

class F3{
public:
  F3(double a0,double b0,double c0,double d0):a(a0),b(b0),c(c0),d(d0){}
  double operator()(double x){
    return a*pow(x,3.0) + b*pow(x,2.0) + x*c +d;
  }
private:
  double a,b,c,d;
};


//To compile type CC -DBISECTION -I../include -lm
#ifdef BISECTION
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
