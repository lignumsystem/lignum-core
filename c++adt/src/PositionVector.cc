#include <PositionVector.h>

//default constructor
PositionVector::PositionVector()
  :v(3)
{
  v[0] = 0.0;
  v[1] = 0.0;
  v[2] = 1.0;
}

PositionVector::PositionVector(const double x, const double y, const double z)
  :v(3)
{
  v[0] = x;
  v[1] = y;
  v[2] = z;
}

//copy constructor
PositionVector::PositionVector(const PositionVector& pv)
{
  v = pv.v;
}

//The assignment
PositionVector& PositionVector::operator = (const PositionVector& pv)
{
  v = pv.v;

  return *this;
}

double PositionVector::length()const
{
  return sqrt(pow(v[0],2.0) + pow(v[1],2.0) + pow(v[2],2.0));
}

double PositionVector::alpha()const
{
  return acos(v[0] / this->length());
}

double PositionVector::beta()const
{
  return acos(v[1] / this->length());
}

double PositionVector::gamma()const
{
  return acos(v[2] / this->length());
}

PositionVector& PositionVector::rotate(ROTATION direction, RADIAN angle)
{
  RMatrix r(direction);

  v = v*r(angle);

  return *this;
}

#ifdef PV

ostream& operator << (ostream& os, const vector<double>& v1)
{
  for (int i = 0; i < v1.size(); i++){
    os << v1[i] << " ";
  }
  os << endl;

  return os;
}

int main()
{
  PositionVector pv1;
  vector<double> v;
  vector<double> v2(3);
  v2[0]=1.0; v2[1]=1.0; v2[2]=1.0;
  PositionVector pv2(v2);

  cout << "Position vector pv1" << endl;
  cout << "  length:" << pv1.length() << endl;
  cout << "  alpha: " << pv1.alpha() << endl;
  cout << "  beta: "  << pv1.beta() << endl;
  cout << "  gamma: " << pv1.gamma() << endl;
  cout << "  (x,y,z): " << pv1.getVector() << endl;

  pv1.rotate(ROTATE_Y,PI_VALUE/2.0);
  cout << "Position vector pv1" << endl;
  cout << "  length:" << pv1.length() << endl;
  cout << "  alpha: " << pv1.alpha() << endl;
  cout << "  beta: "  << pv1.beta() << endl;
  cout << "  gamma: " << pv1.gamma() << endl;
  cout << "  (x,y,z): " << pv1.getVector() << endl;

  pv1.rotate(ROTATE_Y,-PI_VALUE);
  cout << "Position vector pv1" << endl;
  cout << "  length:" << pv1.length() << endl;
  cout << "  alpha: " << pv1.alpha() << endl;
  cout << "  beta: "  << pv1.beta() << endl;
  cout << "  gamma: " << pv1.gamma() << endl;
  cout << "  (x,y,z): " << pv1.getVector() << endl;

  pv1.rotate(ROTATE_Y,-PI_VALUE/2.0);
  cout << "Position vector pv1" << endl;
  cout << "  length:" << pv1.length() << endl;
  cout << "  alpha: " << pv1.alpha() << endl;
  cout << "  beta: "  << pv1.beta() << endl;
  cout << "  gamma: " << pv1.gamma() << endl;
  cout << "  (x,y,z): " << pv1.getVector() << endl;

  cout << "Position vector pv2" << endl;
  cout << "  length:" << pv2.length() << endl;
  cout << "  alpha: " << pv2.alpha() << endl;
  cout << "  beta: "  << pv2.beta() << endl;
  cout << "  gamma: " << pv2.gamma() << endl;
  cout << "  (x,y,z): " << pv2.getVector() << endl;

  pv2.rotate(ROTATE_Z,atan(pv2.getVector()[0]/pv2.getVector()[1]));
  cout << "  length:" << pv2.length() << endl;
  cout << "  alpha: " << pv2.alpha() << endl;
  cout << "  beta: "  << pv2.beta() << endl;
  cout << "  gamma: " << pv2.gamma() << endl;
  cout << "  (x,y,z): " << pv2.getVector() << endl;

  pv2.rotate(ROTATE_X,pv2.gamma());
  cout << "  length:" << pv2.length() << endl;
  cout << "  alpha: " << pv2.alpha() << endl;
  cout << "  beta: "  << pv2.beta() << endl;
  cout << "  gamma: " << pv2.gamma() << endl;
  cout << "  (x,y,z): " << pv2.getVector() << endl;
}

#endif
