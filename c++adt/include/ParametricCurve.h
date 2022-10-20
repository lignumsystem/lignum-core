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
  ///\brief Constructor exception if file does not exist
  class PCurveFileException{
  public:
    ///\param fname File name for the missing file
    PCurveFileException(const string& fname):
      file_name(fname){}
    ///After catching exception user can query missing file name
    const string getFileName(){return file_name;}
  private:
    const string file_name;
  };
  ///\brief Class to implement piecewise-defined linear function, a.k.a parametric curve.
  ///
  ///Constructors give various options to define the function.
  ///The most used is to define the function in a text file as (x,f(x)) pairs.
  ///As an example a function y=2x.
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
  ///two last values. Lines beginning with hash mark (#) before the function definition are comments.
class ParametricCurve{
public:
  /// Constructor
  /// \note To be useful the function must be installed
  /// \sa install 
  ParametricCurve();
  /// \brief Create piecewise linear function from file.
  /// \param file_name File containing function values at specific points in two columns
  /// \exception PCurveException If file does not exists throw exception
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
  ParametricCurve& operator=(const ParametricCurve& f);
  /// \brief Evaluate the function at point *x*.
  ///
  /// Overloaded function operator. Interpolate or extrapolate if needed.
  /// \param x Find the function value at *x*.
  /// \return The function value for argument *x*.
  /// \sa eval
  double operator()(double x)const{return eval(x);}
  /// Reinstall a new function from a file.
  bool install(const string& file_name);
  /// Check if a function technically correct.
  /// \return *true* if the vector *v* has technically correct function, *false* otherwise.
  bool ok()const;
  /// Evaluate the function. Interpolate or extrapolate if needed.
  /// \param x Find the function value at *x*.
  /// \return The function value at *x*.
  double eval(double x)const;
  string getFile()const{return file;}
  vector<double> getVector()const{return v;}
  ///\todo Has someone implemented ParametriCurve::withXYvectors and forgot to commit work?
  void withXYvectors(const int n, const vector<double> x,
  const vector<double> y);

private:
  ///Read the function definition file and install it-
  ParametricCurve& read_xy_file(const char *file_name);
  string file;///<File where the function  is
  vector<double> v;///<The internal vector for function
  unsigned long num_of_elements;///<Number of elements in the vector *v*.
};

} //close namespace cxxadt
#endif
