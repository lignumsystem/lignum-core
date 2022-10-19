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
  ///\brief Class to implement piecewise-defined linear function.
  ///
  ///Constructors give various options to define the function.
  ///One of the most used is to define the function in a text file as (x,f(x)) pairs.
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
  ///interpolated. Function values outside min and max x-values are extrapolated. Lines beginning
  ///with hash mark (#) before the function definition are comments.
class ParametricCurve{
public:
  ParametricCurve();
  /// Create ParametricCurve from file
  /// \param file_name File containing (x,f(x)) values in two columns
  /// \exception PCurveException If file does not exists throw exception
  ParametricCurve(const string& file_name);
  /// In this constructor values for the curve are stored
  /// in the string parameter.
  /// \param values (x,f(x)) values in a linear string separated by white space
  /// \param dummy  technically needed to overload the function.
  ParametricCurve(const string& values, int dummy);
  ParametricCurve(const vector<double>& v);
  ParametricCurve(const ParametricCurve& pc);
  ParametricCurve(const double c);
  ///Function is defined by vectors containing (x,y) pairs & # of such pairs
  ParametricCurve(const int n_elem, const vector<double> x, const vector<double> y);
  ParametricCurve& operator=(const ParametricCurve& f);
  ///The overloaded function operator
  ///\param x The function argument 
  ///\return The function value for argument *x*. 
  double operator()(double x)const{return eval(x);} 
  bool install(const string& file_name);
  bool ok()const;
  double eval(double x)const;
  string getFile()const{return file;}
  vector<double> getVector()const{return v;}
  void withXYvectors(const int n, const vector<double> x,
  const vector<double> y);

private:
  ParametricCurve& read_xy_file(const char *file_name);
  string file;
  vector<double> v;
  unsigned long num_of_elements;
};

} //close namespace cxxadt
#endif
