#ifndef PARAMETRIC_CURVE_H
#define PARAMETRIC_CURVE_H

#include <vector>
#include <stdio.h>
#include <fstream.h>
#include <float.h>
#include <string.h>
#include <CString.h>

namespace cxxadt{

using namespace  std;
class ParametricCurve{
public:
  ParametricCurve();
  ParametricCurve(const CString& file_name);
  ParametricCurve(const vector<double>& v);
  bool install(const CString& file_name);
  bool ok();
  double eval(double x);
  CString getFile()const{return file;}
private:
  ParametricCurve& read_xy_file(const char *file_name);
  CString file;
  vector<double> v;
  int num_of_elements;
};

} //close namespace cxxadt
#endif
