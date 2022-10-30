///\file ParametricCurve.h
///\brief Piecewise-defined linear function, a.k.a parametric curve.
#ifndef PARAMETRIC_CURVE_H
#define PARAMETRIC_CURVE_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <float.h>
#include <string.h>
#include <string>
#include <iostream>
namespace cxxadt{

using namespace  std;
  ///\brief File does not exist exception class
  class PCurveFileException{
  public:
    ///Constructor
    ///\param fname File name for the missing file
    PCurveFileException(const string& fname):
      file_name(fname){}
    ///After catching exception user can query the missing file name
    const string getFileName(){return file_name;}
  private:
    const string file_name;///<File for the parametric curve
  };
  ///\brief Create piecewise-defined linear function, a.k.a parametric curve.
  ///
  ///Constructors give various options to define the function.
  ///The most used is to define the function in a text file as (x,f(x)) pairs.
  ///As an example a function y=2x:
  ///
  ///```
  /// #Function y = 2x 
  /// #x      f(x)
  /// 0.0     0.0
  /// 1.0     2.0
  /// 2.0     4.0
  ///```
  ///
  ///The x-values must be in increasing order. Function values between the exact definitions are
  ///interpolated. Function values outside the function definition are extrapolated with two first or
  ///two last function values in the file. Lines beginning with hash mark (#) before the function
  ///definition are comments.
  ///
  ///Due to implementation the maximum x-value must be strictly less than FLT_MAX.
  ///Also at least two function values must be defined.
  ///\sa ParametricCurve::ParametricCurve(const string&)
  ///\sa FLT_MAX in \<float.h\> or \<cfloat\>
class ParametricCurve{
public:
  /// Constructor
  /// \note To be useful parameric curve the function must be installed
  /// \sa install
  /// \sa operator=()
  ParametricCurve();
  /// \brief Create parametric curve from file.
  /// \param file_name File containing function values at specific points in two columns
  /// \exception PCurveException If file does not exists throw PCurveException 
  ParametricCurve(const string& file_name);
  /// Values for the parametric curve are read from a string.
  /// \param values Function values at specific points are in a linear string separated by white space
  /// \param dummy  technically needed to overload the constructor.
  ParametricCurve(const string& values, int dummy);
  /// Values for the parametric curve are read from a vector.
  /// \param v Function values at specific points are in a vector
  /// \attention The very last element in the vector must be FLT_MAX. It is needed as a marker
  /// to denote the end of function definition.
  ParametricCurve(const vector<double>& v);
  ParametricCurve(const ParametricCurve& pc);
  /// Constant function
  /// \param c Constant value of the function
  ParametricCurve(const double c);
  /// Function is defined by two vectors containing the points and the respective function values
  /// \param n_elem Number of elements (lengths of vectors *x* and *y*)
  /// \param x Vector of points where the function values are specified
  /// \param y Vector of function values at points specified in vector *x*.  
  ParametricCurve(const int n_elem, const vector<double> x, const vector<double> y);
  /// Assignment
  /// \param f Parametric curve 
  ParametricCurve& operator=(const ParametricCurve& f);
  /// \brief Evaluate the function at point *x*.
  ///
  /// Overloaded function operator. Interpolate or extrapolate if needed.
  /// \pre Parameter *x* < FLT_MAX
  /// \pre ok() == *true*
  /// \param x Find the function value at *x*.
  /// \return The function value at *x*.
  /// \sa eval ok()
  double operator()(double x)const{return eval(x);}
  /// Reinstall a new function from a file.
  bool install(const string& file_name);
  /// Check if the function is technically correct.
  /// \return *true* if the vector *v* has technically correct function, *false* otherwise.
  /// \sa vector v.
  bool ok()const;
  /// Evaluate the function. Interpolate or extrapolate if needed.
  /// \pre Parameter *x* < FLT_MAX
  /// \param x Find the function value at *x*.
  /// \return The function value at *x*.
  double eval(double x)const;
  string getFile()const{return file;}
  vector<double> getVector()const{return v;}
  ///\todo Has someone implemented ParametriCurve::withXYvectors and forgot to commit work?
  void withXYvectors(const int n, const vector<double> x,
  const vector<double> y);

private:
  ///Read the function definition file and install it in vector *v*.
  ///\param file_name File for the function definition
  ///\post Vector *v* has FLT_MAX as the last element to denote end of function definition.
  ///\sa Vector v.
  ///\sa FLT_MAX in \<float.h\> or \<cfloat\>
  ParametricCurve& read_xy_file(const char *file_name);
  string file;///<File for the function definition
  vector<double> v;///<The internal vector for function definition
  unsigned long num_of_elements;///<Number of elements in the vector *v*.
};

} //close namespace cxxadt
#endif
