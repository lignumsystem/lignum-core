#ifndef BISECTION_H
#define BISECTION_H
#include <cmath>
#include <mathsym.h>
using namespace std;
namespace cxxadt{

#define MAX_ITER 100
  //Thrown in BracketFunction if bracket fails
  class BracketFunctionException{
  public:
    BracketFunctionException(double fbe,double be)
      :fb(fbe),b(be){}
    double getFb()const{return fb;}
    double getB()const{return b;}
  private:
    double fb;//the last function value  tried in BracketFunction and the
	      //sign did not change.
    double b; //the last b, s.t. fb = F(b)
  };

  //Thrown in Bisection if BracketFunction fails and Bisection cannot be used
  class BisectionBracketException{
  public:
    BisectionBracketException(double fa,double fb, double fblast,
			      double a, double b, double blast)
      :fao(fa),fbo(fb),fbl(fblast),ao(a),bo(b),bl(blast){}
    double getFa()const{return fao;}
    double getFb()const{return fbo;}
    double getFbl()const{return fbl;}
    double getA()const{return ao;}
    double getB()const{return bo;}
    double getBl()const{return bl;}
  private:
    double fao;//the original fa
    double fbo;//the original fb
    double fbl;//the last fb tried
    double ao; //the original a (fao=F(ao))
    double bo; //the original b (fbo=F(bo))
    double bl; //the last b, s.t. fbl = F(bl)
  };

  //Thrown by Bisection if the root  of the function F not found after
  //MAX_ITER
  class BisectionMaxIterationException{
  public:
    BisectionMaxIterationException(double fa, double fb, double fmid,
				   double a,double b, double mid)
      :fao(fa),fbo(fb),fc(fmid),ao(a),bo(b),c(mid){}
    double getFa()const{return fao;}
    double getFb()const{return fbo;}
    double getFc()const{return fc;}
    double getA()const{return ao;}
    double getB()const{return bo;}
    double getC()const{return c;}
  private:
    double fao;//the original fa 
    double fbo;//the original fb
    double fc; //the last fc found, fa < fc < fb
    double ao; //the original a (fao=F(ao))
    double bo; //the original b (fbo=F(bo))
    double c;  //the last c, s.t. fc = F(c)
  };


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
    throw BracketFunctionException(fb,b);
  }

  template <class F>
  double Bisection(double  a, double b, F f, double acc = R_EPSILON)
  {
    int i = 0;
    double faorig = f(a);
    double fborig = f(b);
    double aorig = a;
    double borig = b;
    double fa = faorig;
    double fb = fborig;

    //if the initial guess did not bracket the funtion
    //start increasing b. Currently assume f(a) < 0.
    if (fa*fb > 0.0){
      try{
	BracketFunction(fa,a,b,f);
      }
      catch (BracketFunctionException eb){
	throw BisectionBracketException(faorig,fborig,eb.getFb(),
					aorig,borig,eb.getB());
      }
    }
    double c = fa < 0.0 ? a : b;
    double dx = fa < 0.0 ? b - a : a - b;
    double mid = 0;
    while (i++ < MAX_ITER){
      mid = c + (dx *= 0.5);
      double fb = f(mid);
      if (fb <= 0.0) c = mid;
      if (fabs(dx) < acc || fb==0.0)return c;
    }
    //Root not found, throw exception
    throw BisectionMaxIterationException(faorig,fborig,fb,aorig,borig,mid);
  }
#undef MAX_ITER
}
 
#endif
