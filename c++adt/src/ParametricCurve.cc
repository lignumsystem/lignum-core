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
  
#ifdef PCURVEMAIN
#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <mathsym.h>
using namespace std;
using namespace cxxadt;
int main(int argc, char *argv[])
{
  /*
  cout << argv[1] << endl;
  //ParametricCurve p1(string(argv[1]));
  cout << "Plotting out some function values\n";

  cout.setf(ios::fixed,ios::floatfield);

  cout << "x: " << -100.0 << " y: " << p1.eval(-100.0) << '\n';
  cout << "x: " <<  -5.0 << " y: " << p1.eval(-5.0)  << '\n';
  cout << "x: " <<  -1.0 << " y: " << p1.eval(-1.0)  << '\n';
  cout << "x: " <<   0.0 << " y: " << p1.eval(0.0)   << '\n'; 
  cout << "x: " <<   1.0 << " y: " << p1.eval(1.0)   << '\n'; 
  cout << "x: " <<   2.0 << " y: " << p1.eval(2.0)   << '\n';
  cout << "x: " <<   3.0 << " y: " << p1.eval(3.0)   << '\n';
  cout << "x: " <<   3.5 << " y: " << p1.eval(3.5)   << '\n';
  cout << "x: " <<   4.0 << " y: " << p1.eval(4.0)   << '\n';
  cout << "x: " <<   8.0 << " y: " << p1.eval(8.0)   << '\n';
  cout << "x: " <<  10.0 << " y: " << p1.eval(10.0)  << '\n';
  cout << "x: " <<  85.0 << " y: " << p1.eval(85.0)  << '\n';
  cout << "x: " <<  91.0 << " y: " << p1.eval(91.0)  << '\n';
  cout << "x: " << 100.0 << " y: " << p1.eval(100.0) << '\n';
  */
  int init = -1;
  int next = 1;
  ran3(&init);
  ostringstream oss;
  for (double i = -3.0 ; i < 3.0; i=i+0.1){
    oss << i << " " << pow(i,3.0) << " " ;
  }

  //Testing vector constructor
  vector<double> v;
  for (double i = -3.0 ; i < 3.0; i=i+0.1){
    v.push_back(i);
    v.push_back(pow(i,3.0));
  }
  v.push_back(FLT_MAX);
  ofstream f1("vpc.txt");
  ofstream f2("vdata.txt");
  ParametricCurve p2(v);
  for (double i = -3.0,j=-3.3; i < 3.0; i=i+0.1,j=j+0.12){
    f1 << i << " " << p2(i) << endl;
    f2 << j << " " << p2(j) <<endl;
  }

  ofstream f3("strpc.txt");
  ofstream f4("strdata.txt");
  //Testing string constructor
  ParametricCurve p3(oss.str(),0);
  for (double i = -3.0,j=-3.3; i < 3.0; i=i+0.1,j=j+0.11){
    f3 << i << " " << p3(i) << endl;
    f4 << j << " " << p3(j) <<endl;
  }
  
}

#endif


