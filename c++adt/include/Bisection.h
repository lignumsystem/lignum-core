#ifndef BISECTION_H
#define BISECTION_H
#include <mathsym.h>
using namespace std;
namespace cxxadt{

#define MAX_ITER 100

  template <class F>
  double BracketFunction(double fa, double&  a, double& b, F f)
  {
    int I = 0;
    double fb = 0.0;
    //increase b by add: 20% of original b. 
    double add = fabs(b)*20.0/100.0;

    while (I++ < MAX_ITER){   
      a = b;
      b = b + add;
      fb = f(b);
      if (fa*fb < 0.0) return fb;
    }
    cerr << "Max iterations " << I
	 << " exceeded in BracketFunctionForward:" << endl;
    cerr << "Returning: " << fb << endl;
    return fb;
  }

  template <class F>
  double Bisection(double  a, double b, F f, double acc = R_EPSILON)
  {
    int I = 0;
    double fa = f(a);
    double fb = f(b);

    //if the initial guess did not bracket the funtion
    //start increasing b. Currently assume f(a) < 0.
    if (fa*fb > 0.0){
      BracketFunction(fa,a,b,f);
    }

    double c = fa < 0.0 ? a : b;
    double dx = fa < 0.0 ? b - a : a - b;

    while (I++ < MAX_ITER){
      double mid = c + (dx *= 0.5);
      double fb = f(mid);
      if (fb <= 0.0) c = mid;
      if (fabs(dx) < acc || fb==0.0)return c;
    }
    cout << "Max iter " << I<< " exceeded, return:  "<< c << endl;
    return c;
  }
#undef MAX_ITER
}
 
#endif
