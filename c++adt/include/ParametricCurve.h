#ifndef PARAMETRIC_CURVE_H
#define PARAMETRIC_CURVE_H

#include <vector>
#include <stdio.h>
#include <fstream.h>
#include <float.h>
#include <string.h>
#include <string>

namespace cxxadt{

using namespace  std;
class ParametricCurve{
public:
  ParametricCurve();
  ParametricCurve(const string& file_name);
  ParametricCurve(const vector<double>& v);
  ParametricCurve(const ParametricCurve& pc);
  double operator()(double x)const{return eval(x);} 
  bool install(const string& file_name);
  bool ok()const;
  double eval(double x)const;
  string getFile()const{return file;}
private:
  ParametricCurve& read_xy_file(const char *file_name);
  string file;
  vector<double> v;
  int num_of_elements;
};

} //close namespace cxxadt
#endif
