/// \file ParametricCurveExample.cc
///
/// \example{lineno} ParametricCurveExample.cc
/// \brief ParametricCurve test cases.
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
