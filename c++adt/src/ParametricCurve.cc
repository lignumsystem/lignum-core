
#include <ParametricCurve.h>
ParametricCurve::ParametricCurve()
{
}

ParametricCurve::ParametricCurve(const CString& file_name)
{
  read_xy_file((const char *)file_name);
}

ParametricCurve::ParametricCurve(const vector<double>& v1)
:v(v1)
{
  num_of_elements = v1.size();
}

bool ParametricCurve::install(const CString& file_name)
{
  read_xy_file((const char *)file_name);
  return ok();
}

bool ParametricCurve::ok()
{
  return !v.empty();
}

ParametricCurve& ParametricCurve::read_xy_file(const char *file_name)
{
  double value = 0.0;
  fstream in_file(file_name,ios::in);
  
  if (in_file.fail() || strcmp(file_name,"") == 0){
    cout << "ParametricCurve::read_xy_file: error in opening file: " 
         << file_name <<endl;
    return *this;
  }
  
  file = CString(file);

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

double ParametricCurve::eval(double x)
{
  int i = 0;

  for (i = 0; (v[i] <= x) && (v[i] != FLT_MAX); i+=2)
    ;

  //if x is out of bounds approximate according to last values
  if (i == 0)
    i+=2;
  else if (v[i] == FLT_MAX)
    i-=2;
  
  //the evaluation of the function
  return v[i-1] + (v[i+1] - v[i-1])*((x - v[i-2]) / (v[i] - v[i-2]));

}
  
#ifdef PCURVE

int main(int argc, char *argv[])
{
  cout << argv[1] << endl;
  ParametricCurve p1(CString(argv[1]));
  
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
}

#endif


