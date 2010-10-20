#include "stdafx.h"
#include <Point.h>
#include <PositionVector.h>

using namespace std;

namespace cxxadt{

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
  :v(3)
{
  v = pv.v;
}


PositionVector::PositionVector(const Point& p)
   :v(3)
{
  //  PositionVector(p.getX(),p.getY(),p.getZ()); //This did not work.
  v[0] = p.getX(); v[1] = p.getY(); v[2] = p.getZ();
}

PositionVector::PositionVector(const Point& start, const Point& end)
  :v(3)
{
  v[0] = end.getX()-start.getX();
  v[1] = end.getY()-start.getY();
  v[2] = end.getZ()-start.getZ();
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


PositionVector::operator Point ()
{ 
  return Point(v[0], v[1], v[2]); 
}

PositionVector::operator Point () const 
{ 
  return Point(v[0], v[1], v[2]); 
}

double PositionVector::alpha()const
{
  PositionVector d(*this);
  d.normalize();
  return acos(Dot(PositionVector(1,0,0),d));
}

double PositionVector::beta()const
{
  PositionVector d(*this);
  d.normalize();
  return acos(Dot(PositionVector(0,1,0),d));
}

double PositionVector::gamma()const
{
  PositionVector d(*this);
  d.normalize();
  return acos(Dot(PositionVector(0,0,1),d));
}

PositionVector& PositionVector::rotate(ROTATION direction, RADIAN angle)
{
  RMatrix r(direction);

  v = v*r(angle);

  return *this;
}

//Rotation about an arbitrary axis in space according to
//Rogers&Adams: mathematical Elements for Computer Graphics p. 121-128
// dir does not need to be a unit vector. It is nomalized here. If it is
//not normalized, the distance of the rotated point (end point of vector)
// from the axis of ration = Length_of(dir) * distance_before
PositionVector& PositionVector::rotate(const Point& p0,
				       const PositionVector& dir, RADIAN angle)
{
  // TM = transformation matrix,
  // M = multiplication matrix 
  TMatrix<double> TM(4,4);


  // 1. Make p0 origin of the coordinate system = move

  TMatrix<double> T(4,4);
  T.unitize();
  T[3][0] = -p0.getX();
  T[3][1] = -p0.getY();
  T[3][2] = -p0.getZ();

  TM = T;
  

  // 2. Perform appropriate rotations to make the axis of rotation coincident with
  // the z-axis
  // Normalize the direction vector

  TMatrix<double> Rx(4,4), Ry(4,4);
  double cx, cy, cz;   //direction cosines of the axis =(x,y,z) of a unit vector
  PositionVector cc(dir.getX(), dir.getY(), dir.getZ());
  cc.normalize();
  cx = cc.getX();
  cy = cc.getY();
  cz = cc.getZ();

  double lxy;   //projection of direction (unit) vector on xy plane
  Rx.unitize();

  lxy = sqrt( pow(cy, 2.0) + pow(cz, 2.0) );

  if(lxy > R_EPSILON) {
      Rx[1][1] = cz/lxy;
      Rx[1][2] = cy/lxy;
      Rx[2][1] = -cy/lxy;
      Rx[2][2] = cz/lxy;

      TM = TM * Rx;      // rotation about x-axis

  }

     Ry.unitize();
      Ry[0][0] = lxy;
      Ry[0][2] = cx;
      Ry[2][0] = -cx;
      Ry[2][2] = lxy;
    
      TM = TM * Ry;    //rotation about y-axis


  // 3. Finally, the rotation about the arbitrary axis is given be z-axis rotation
  //    matrix

  TMatrix<double> Ra(4,4);
  double cosa, sina;
  Ra.unitize();
  cosa = cos(angle);
  sina = sin(angle);
  Ra[0][0] = cosa;
  Ra[0][1] = sina;
  Ra[1][0] = -sina;
  Ra[1][1] = cosa;

  TM = TM * Ra;

  // 4. Now, trasformations Ry, Rx and T inversed to get back to
  //    original position

  TM = TM * (Ry.transpose());


  if(lxy > R_EPSILON) {
  TM = TM * (Rx.transpose());
  }

  // Move back
  T.unitize();
  T[3][0] = p0.getX();
  T[3][1] = p0.getY();
  T[3][2] = p0.getZ();


  TM = TM * T;

  
  // Apply transformation to Positionvector

  vector<double> vm(4);
  vm[0] = v[0]; vm[1] = v[1];  vm[2] = v[2];  vm[3] = 1.0;

  vm = vm * TM;

  v[0] = vm[0]; v[1] = vm[1];  v[2] = vm[2];

  return *this;
  
}


//Rotate about an arbitrary axis, specified by two points through
//which it goes. The direction of the axis is specified by first and
//second  point. (Direction: from first to second. Uses rotation
//specified by point and direction vector

PositionVector& PositionVector::rotate(const Point& p1,
				       const Point& p2, RADIAN angle)
{
  PositionVector vv = PositionVector(p2 - p1);

  rotate(p1, vv, angle);  //(direction normalized in the called rotate() )

  return *this;

}




//Dot product of two vectors
double Dot(const PositionVector& pv1,const PositionVector& pv2)
{
  return pv1.v[0]*pv2.v[0] +  pv1.v[1]*pv2.v[1] +  pv1.v[2]*pv2.v[2];
}

PositionVector Cross(const PositionVector& pv1,const PositionVector& pv2)
{
  double x = pv1.v[1]*pv2.v[2] - pv1.v[2]*pv2.v[1];
  double y = pv1.v[2]*pv2.v[0] - pv1.v[0]*pv2.v[2];
  double z = pv1.v[0]*pv2.v[1] - pv1.v[1]*pv2.v[0];
  return PositionVector(x,y,z);
}

//Multiply with a scalar, return the result, do not change the vector itself
PositionVector ScalMult(const PositionVector& pv, double a)
{
  return PositionVector(a*pv.getVector()[0], a*pv.getVector()[1], a*pv.getVector()[2]);
}

//Normalize the vector
//by making its length 1.
//The vector is now directon vector
PositionVector& PositionVector::normalize()
{
  double l = length();
  if(l > R_EPSILON) {   //do not normalize zero vector
    v[0] = v[0] / l;
    v[1] = v[1] / l;
    v[2] = v[2] / l;
  }

  return *this;
}


istream& operator >> (istream& os, PositionVector& pv)
{
  char tmpX[255];
  char tmpY[255];	
  char tmpZ[255];
  double x,y,z;

  os  >> tmpX >> tmpY >> tmpZ;

  x = atof(tmpX);
  y = atof(tmpY);
  z = atof(tmpZ);

  PositionVector p(x,y,z);	
  pv = p;
  return os;
}


ostream& operator << (std::ostream& os, const PositionVector& pv)
{
	std::vector<double> vv = pv.getVector();
  os  << " " << vv[0] << " " << vv[1] << " " << vv[2];
  return os;
}


//Modify the PositionVector by adding another PositionVector to it
PositionVector& PositionVector::operator += (const PositionVector& pv)
{
  v[0] += pv.v[0];
  v[1] += pv.v[1];
  v[2] += pv.v[2];
    
  return *this;
}

//Modify the PositionVector by subtracting another PositionVector from it
PositionVector& PositionVector::operator -= (const PositionVector& pv)
{
  v[0] -= pv.v[0];
  v[1] -= pv.v[1];
  v[2] -= pv.v[2];
    
  return *this;
}

//Modify the PositionVector by multiplying it with a scalar constant
PositionVector& PositionVector::operator *= (const double scalar)
{
  v[0] *= scalar;
  v[1] *= scalar;
  v[2] *= scalar;

  return *this;
}

//friend operator to add two PositionVectors
PositionVector operator + (const PositionVector& pv1, const PositionVector& pv2)
{
  PositionVector p(pv1.v[0] + pv2.v[0], pv1.v[1] + pv2.v[1],
		   pv1.v[2] + pv2.v[2]);

  return p;
}

//friend operator to subtract two PositionVectors
PositionVector operator - (const PositionVector& pv1, const PositionVector& pv2)
{
  PositionVector p(pv1.v[0] - pv2.v[0], pv1.v[1] - pv2.v[1],
		   pv1.v[2] - pv2.v[2]);
    
  return p;
}

//friend operator to multiply a PositionVector with scalar
PositionVector operator * (const double scalar, const PositionVector& pv)
{
  PositionVector p(scalar * pv.v[0], scalar * pv.v[1], scalar * pv.v[2]);
    
  return p;
}

//friend operator to multiply a PositionVector with scalar
PositionVector operator * (const PositionVector& p, const double s)
{
  return s * p;
}

//friend operator to calculate distance between two PositionVectors
double operator || (const PositionVector& pv1, const PositionVector& pv2)
{
  double x, y, z;
  x = pv1.v[0] - pv2.v[0];
  y = pv1.v[1] - pv2.v[1];
  z = pv1.v[2] - pv2.v[2];

  return sqrt(pow(x,2.0) + pow(y,2.0) + pow(z,2.0));
}

//compare equality (in R_EPSILON sense)
bool operator == (const PositionVector& pv1, const PositionVector& pv2)
{
  return (maximum(pv1.getVector()[0]-pv2.getVector()[0],
		  pv2.getVector()[0]-pv1.getVector()[0]) < R_EPSILON) && 
         (maximum(pv1.getVector()[1]-pv2.getVector()[1],
		  pv2.getVector()[1]-pv1.getVector()[1]) < R_EPSILON) &&
         (maximum(pv1.getVector()[2]-pv2.getVector()[2],
		  pv2.getVector()[2]-pv1.getVector()[2]) < R_EPSILON);
}





}//closing namespace cxxadt
#ifdef PV

using namespace cxxadt;

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


  PositionVector pv3(2,2,2);
  cout << "PositionVector pv3" << endl;
  cout << " length: " << pv3.length() << endl;
  cout << " alpha: " << pv2.alpha() << endl;
  cout << " beta: "  << pv3.beta() << endl;
  cout << " gamma: " << pv3.gamma() << endl;
  cout << " (x,y,z): " << pv3.getVector() << endl;

  
  cout << "Normalizing pv3" << endl;
  pv3.normalize();
  cout << " length:" << pv3.length() <<endl;
  cout << " alpha: " << pv2.alpha() << endl;
  cout << " beta: "  << pv3.beta() << endl;
  cout << " gamma: " << pv3.gamma() << endl;
  cout << " (x,y,z): " << pv3.getVector() << endl;

  cout << "Cross Products" << endl;
  cout << "Cross(PositionVector(1,0,0),PositionVector(0,1,0))" << endl;
  cout << Cross(PositionVector(1,0,0),PositionVector(0,1,0)) << endl;

  cout << "Cross(PositionVector(1,0,0),PositionVector(0,0,1))" << endl;
  cout <<  Cross(PositionVector(1,0,0),PositionVector(0,0,1))  << endl;

  cout << "Cross(PositionVector(0,1,0),PositionVector(0,0,1))" << endl;
  cout << Cross(PositionVector(0,1,0),PositionVector(0,0,1)) << endl;

  cout << "Cross(PositionVector(0,0,1),PositionVector(0,0,1))" << endl;
  cout << Cross(PositionVector(0,0,1),PositionVector(0,0,1)) << endl;

  cout << "Cross(PositionVector(0,1,1),PositionVector(0,0,1))" << endl;
  cout << Cross(PositionVector(0,1,1),PositionVector(0,0,1)) << endl;
  
  cout << "Cross(PositionVector(0,0.01,9.1),PositionVector(0,0,1))" <<endl;
  cout << Cross(PositionVector(0,0.01,9.1),PositionVector(0,0,1))  <<endl;
  
  cout << "Cross(PositionVector(0,-1,0),PositionVector(0,0,-1))" <<endl;
  cout << Cross(PositionVector(0,-1,0),PositionVector(0,0,-1)) <<endl;
  
  cout << "Cross(PositionVector(1,2,-2),PositionVector(3,0,1))" <<endl;
  cout << Cross(PositionVector(1,2,-2),PositionVector(3,0,1)) <<endl;

  PositionVector x(1,0,0), y(0,1,0), z(0,0,1);
  cout << "Testing operations programmed (copied from Point) by Risto." << endl;
  cout << "(1,0,0) + (0,1,0) = " << x + y << endl;
  cout << "(1,0,0) - (0,0,1) = " << x - z << endl;
  cout << "10 * (0,1,0) = " << 10.0 * y << endl;
  cout << "(0,1,0) * 10 = " << y * 10.0 << endl;
  cout << "Distance of (1,0,0) and (0,1,0) by || = " << (double)(x || y) << endl;
  cout << "(0,0,1) == (0,0,1), yes! " << (bool)(z == z) << endl;
  cout << "(0,0,1) == (0,0,1.0001), no! " <<
    (bool)(z == (z+PositionVector(0,0,0.0001))) << endl;
  cout << "(1,0,0) += (0,1,0) = " << (PositionVector)(x += y) << endl;
  cout << "Restore (1,0,0), ((1,0,0)+=(0,1,0))-=(0,1,0) = " <<
    (PositionVector)(x-=y) << " yes" << endl;
  cout << "(1,0,0) *= 10 = " << (PositionVector)(x *= 10.0) << endl;

  cout << "Type casting PostitionVector -> Point:" << endl;
  Point dd;
  dd = (Point)x;
  cout << dd << endl;

//    cout << "Testing using the Point-argument constructor" << endl;
//    Point pp(2, 2, 2);
//    cout << "Point pp(2,2,2) as PositionVector: " << PositionVector(pp) << endl;

  
  z = PositionVector(1,0,0);
  PositionVector dir(0,1,0);
  RADIAN angle = -PI_VALUE/2.0;
  Point p0(0,0,0);

  cout << endl;
  z.rotate(p0,dir,angle);
  cout << z << endl;
  dir = PositionVector(1,0,0);
  z.rotate(p0,dir,angle);
  cout << z << endl;
  dir = PositionVector(0,0,1);
  z.rotate(p0,dir,angle);
  cout << z << endl;

  // the other rotation

  z = PositionVector(1,0,0);
  Point begin(0,0,0);
  angle = -PI_VALUE/2.0;
  Point end(0,5,0);

  cout << endl;
  z.rotate(begin,end,angle);
  cout << z << endl;
  end  = Point(2,0,0);
  z.rotate(begin,end,angle);
  cout << z << endl;
  end = Point(0,0,3);
  z.rotate(begin, end, angle);
  cout << z << endl;


}

#endif



