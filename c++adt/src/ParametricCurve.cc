///\file ParametricCurve.cc
///\brief Implementation of piecewise-defined linear function.
#include "stdafx.h"
#include <iostream>
#include <sstream>


#include <ParametricCurve.h>

namespace cxxadt{
using namespace std;

ParametricCurve::ParametricCurve()
{
}

ParametricCurve::ParametricCurve(const string& file_name)
{
  fstream infile(file_name);
  if (!infile.good()){
    cerr << "ParametricCurve: No file " << file_name <<endl;
    cerr << "Throwing ParametricCurveFileException" <<endl;
    throw ParametricCurveFileException(file_name);
  }
  read_xy_file(file_name.c_str());
}

ParametricCurve::ParametricCurve(const string& values, int dummy)
{
  dummy = 0;
  double value = 0.0;
  stringstream v_stream(values,stringstream::in);
  char buffer[100];

  //Skip the comments. A line beginning with '#' is a comment 
  v_stream >> ws;//Skip white space
  while (v_stream.peek() == '#'){
    v_stream.getline(buffer,100);
    v_stream >> ws; //skip white space
  }
 
  //clear the previous function 
  v.clear();
  file = string("");
  
  v_stream.setf(ios::fixed,ios::floatfield);

  while (v_stream >> value){
    v.push_back(value);
  }
  //mark the end of (x,y) value pairs with FLT_MAX 
  //FLT_MAX should be defined in <float.h>
  v.push_back(FLT_MAX);
  num_of_elements = v.size();
  
}


ParametricCurve::ParametricCurve(const vector<double>& v1)
  :v(v1)
{
  num_of_elements = v1.size();
}

ParametricCurve::ParametricCurve(const ParametricCurve& pc)
  :file(pc.file),v(pc.v),num_of_elements(pc.num_of_elements)
{
}

//Constant function
ParametricCurve::ParametricCurve(const double c)
{
  v.clear();
  v.insert(v.end(),0.0);
  v.insert(v.end(),c);
  v.insert(v.end(),1.0);
  v.insert(v.end(),c);
  //mark the end of (x,y) value pairs with FLT_MAX 
  //FLT_MAX should be defined in <float.h>
  v.insert(v.end(),FLT_MAX);
  num_of_elements = v.size();
}

  //Function is defined by vectors containing (x,y) pairs & # of such pairs
ParametricCurve::ParametricCurve(const int n_elem, 
				 const vector<double> x, const vector<double> y){
  for(int i = 0; i < n_elem; i++) {
    v.push_back(x[i]);
    v.push_back(y[i]);
  }
  v.push_back(FLT_MAX);
  num_of_elements = v.size();
}

ParametricCurve& ParametricCurve::operator=(const ParametricCurve& pc)
  {
    v.clear();
    v = pc.v;
    file = pc.file;
    num_of_elements = pc.num_of_elements;
    return *this;
  }

bool ParametricCurve::install(const string& file_name)
{
  read_xy_file(file_name.c_str());
  return ok();
}

bool ParametricCurve::ok()const
{
  return !v.empty();
}

ParametricCurve& ParametricCurve::read_xy_file(const char *file_name)
{
  double value = 0.0;
  fstream in_file(file_name,ios::in);
  char buffer[100];
  
  if (in_file.fail() || strcmp(file_name,"") == 0){
    cout << "ParametricCurve::read_xy_file: error in opening file: " 
         << file_name <<endl;
    return *this;
  }
 
  //Skip the comments. A line beginning with '#' is a comment 
  in_file >> ws;//Skip white space
  while (in_file.peek() == '#'){
    in_file.getline(buffer,100);
    in_file >> ws; //skip white space
  }
 
  //clear the previous function 
  v.clear();

  file = string(file_name);
  
  in_file.setf(ios::fixed,ios::floatfield);

  while (in_file >> value){
    v.insert(v.end(),value);
  }

  //mark the end of (x,y) value pairs with FLT_MAX 
  //FLT_MAX should be defined in <float.h>
  v.insert(v.end(),FLT_MAX);
  num_of_elements = v.size();

  return *this;
}

double ParametricCurve::eval(double x)const
{
  int i = 0;
  //Go to closest point less than x. FLT_MAX denotes end of function definition
  for (i = 0; (v[i] <= x) && (v[i] != FLT_MAX); i+=2)
    ;

  //if x is out of bounds of function definition approximate according to last values
  if (i == 0)
    i+=2;
  else if (v[i] == FLT_MAX)
    i-=2;
  ///\internal
  ///The evaluation of the function:
  ///\snippet{lineno} ParametricCurve.cc Eval
  //[Eval]
  return v[i-1] + (v[i+1] - v[i-1])*((x - v[i-2]) / (v[i] - v[i-2]));
  //[Eval]
  ///\endinternal
}

}//closing namepsace cxxadt



