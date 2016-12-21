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
class ParametricCurve{
public:
  ParametricCurve();
  ParametricCurve(const string& file_name);
  // In this constructor values for the curve are stored
  // in the string parameter. Second parameter is only
  // used for overloading the function.
  ParametricCurve(const string& values, int dummy);
  ParametricCurve(const vector<double>& v);
  ParametricCurve(const ParametricCurve& pc);
  ParametricCurve(const double c);
  //Function is defined by vectors containing (x,y) pairs & # of such pairs
  ParametricCurve(const int n_elem, const vector<double> x, const vector<double> y);
  ParametricCurve& operator=(const ParametricCurve& f);
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
