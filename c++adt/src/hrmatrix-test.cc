#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <HRMatrix.h>


using namespace cxxadt;
int main(int argc, char *argv[])
{
  Point p1(1,2,3);
  HRVector v1(p1);
  HRMatrix m1(ROTATE_Z);
  vector<double> v2(4);
  double angle = 0.0;

  if (argc != 2)
    cout << "Usage: hrmatrix <angle in degrees> " <<endl;
  else{
    cout << "Angle (degrees): " << argv[argc-1] << endl;
    angle = PI_VALUE*atof((const char*)argv[argc-1])/180.0;
  }

  cout << "Point:" << p1;
  cout << "Angle (radians): " << angle << endl; 
  cout << "Rotating round z-axis" << endl;
  v2 = v1 * (m1(angle));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;
  cout << "Rotating back"<< endl;
  m1.inverse();
  v2 = v2 * (m1(angle));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;

  cout << "Rotating round y-axis" << endl;
  m1.changeAxis(ROTATE_Y);
  v2 = v1 * (m1(angle));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;
  cout << "Rotating back"<< endl;
  m1.inverse();
  v2 = v2 * (m1(angle));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;
  
  cout << "Rotating round x-axis" << endl;;
  m1.changeAxis(ROTATE_X);
  v2 = v1 * (m1(angle));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;
  cout << "Rotating back"<< endl;
  m1.inverse();
  v2 = v2 * (m1(angle));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;

  cout << "Rotating round z-axis 0-degree" << endl;
  m1.changeAxis(ROTATE_Z);
  v2 = v1 * (m1(0.0));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;
  cout << "Rotating back"<< endl;
  m1.inverse();
  v2 = v2 * (m1(0.0));
  copy(v2.begin(),v2.end(),ostream_iterator<double>(cout, " "));
  cout << endl;

  exit(0);

}








