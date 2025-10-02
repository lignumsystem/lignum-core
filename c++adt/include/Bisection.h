/// \file Bisection.h
/// \brief Bisection function to find a root of a function.
///
/// cxxadt::Bisection method can be used when the exact functional form is not known.
/// For the LIGNUM model find the allocation of photosynthates.
#ifndef BISECTION_H
#define BISECTION_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <mathsym.h>
using namespace std;
///\brief Useful general purpose classes.
///
///The C++ standard library and STL library most likely have the functionality
///one is looking for a particular application.
///
///The classes in c++adt library implement geometric shapes (ellipse, triangle, parallelogram)
///for leaf models, 2D and 3D matrices, Bisection method for to find root of a function,
///simple HDF5 file interface to save data from Lignum simulations, random number generators etc.

namespace cxxadt{

  const int MAX_ITER = 100;
  ///Exception thrown in BracketFunction if bracket fails
  class BracketFunctionException{
  public:
    BracketFunctionException(double fbe,double be)
      :fb(fbe),b(be){}
    double getFb()const{return fb;}
    double getB()const{return b;}
  private:
    double fb;///< The last function value  tried in BracketFunction and the sign did not change.
    double b; ///< Tthe last b, s.t. fb = F(b)
  };

  ///Exception thrown in Bisection if BracketFunction fails and Bisection fails
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
    double fao;///< The original fa s.t. fa = f(a)
    double fbo;///< The original fb s.t. fb = f(b)
    double fbl;///< The last fbl tried s.t. fbl = f(bl)
    double ao; ///< The original a (fao=F(ao))
    double bo; ///< The original b (fbo=F(bo))
    double bl; ///< The last b, s.t. fbl = F(bl)
  };

  ///Exception thrown by Bisection if the root  of the function F not found after MAX_ITER
  class BisectionMaxIterationException{
  public:
    BisectionMaxIterationException(double fa, double fb, double fmid,
				   double a,double b, double mid, int iter=MAX_ITER)
      :fao(fa),fbo(fb),fc(fmid),ao(a),bo(b),c(mid),max_iter(iter){}
    double getFa()const{return fao;}
    double getFb()const{return fbo;}
    double getFc()const{return fc;}
    double getA()const{return ao;}
    double getB()const{return bo;}
    double getC()const{return c;}
    double getMaxIter()const{return max_iter;}
  private:
    double fao;///< The original fa 
    double fbo;///< The original fb
    double fc; ///< The last fc found, fa < fc < fb
    double ao; ///< The original a (fao=F(ao))
    double bo; ///< The original b (fbo=F(bo))
    double c;  ///< The last c, s.t. fc = F(c)
    int max_iter;///< Maximum iterations
  };

  ///Bracket the function `f` by increasing the value of `b` by 20% in each iteration
  ///\param fa The function value fa=f(a)
  ///\param a The argument s.t. fa=f(a) 
  ///\param b The argument b > a that eventually f(a)*f(b) < 0
  ///\param f The function to be bracketed
  ///\returns fb s.t. fb < 0
  ///\throw BracketFunctionException After MAX_ITER iterations: No a,b s.t. f(a)*f(b) < 0
  ///\note For the LIGNUM we can assume f(a) > 0 (i.e. there is net production to allocate)
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

  ///Find the root of a function with Bisection method.
  ///\param a The argument for the first guess f(a)
  ///\param b The argument for the second guess f(b)
  ///\param f The function f to find the root for
  ///\param acc  Consider a value `e` that when f(`e`) < acc then f(`e`) = 0
  ///\param verbose Verbose output to standard out
  ///\throw BisectionBracketException Bracketing: there is no a,b s.t. f(a)*f(b) < 0
  ///\throw BisectionMaxIterationException After MAX_ITER: there is no `e` s.t. that f(`e`) < acc 
  template <class F>
  double Bisection(double  a, double b, const F& f, double acc = R_EPSILON, 
		   bool verbose = false)
  {
    int i = 0;
    double faorig = f(a);
    double fborig = f(b);
    double aorig = a;
    double borig = b;
    double fa = faorig;
    double fb = fborig;

    //if the initial guess did not bracket the funtion
    //start increasing b. 
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
    if (verbose){
      cout << left << setfill(' ') 
	   << setw(11) << "    L      "
	   << setw(11) << "    C      "
	   << setw(11) << " fabs(dx)  "
	   << setw(11) << "   f(L)    "
	   << endl;
    }
    //cout << "MAX_ITER " << MAX_ITER << endl;
    while (i++ < MAX_ITER){
      mid = c + (dx *= 0.5);
      double fb = f(mid);
      if (fb <= 0.0) c = mid;
      if (verbose){
	cout << left << setfill(' ') 
	     << setw(11) << mid 
	     << setw(11) <<  c 
	     << setw(11) << fabs(dx) 
	     << setw(11) << fb 
	     << endl; 
      }
      if (fabs(dx) < acc || fb==0.0)return c;
    }
    //Root not found, throw exception
    cout << MAX_ITER << endl;
    throw BisectionMaxIterationException(faorig,fborig,fb,aorig,borig,mid);
  }
#undef MAX_ITER
}
 
#endif
