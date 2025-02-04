#ifndef POINTI_H
#define POINTI_H

namespace cxxadt{

  //The assignment

  inline Point& Point::operator = (const Point& point)
  {
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
  }

  //Modify the Point by adding another point to it

  inline Point& Point::operator += (const Point& point)
  {
    x += point.x;
    y += point.y;
    z += point.z;
    
    return *this;
  }

  //Modify the Point by subtracting another point from it

  inline Point& Point::operator -= (const Point& point)
  {
    x -= point.x;
    y -= point.y;
    z -= point.z;
    
    return *this;
  }

  //Modify the Point by multiplying it with a scalar constant

  inline Point& Point::operator *= (const double scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
  }

  //friend operator to add two points
  inline Point operator + (const Point& point1, const Point& point2)
  {
    Point p;
  
    p.x = point1.x + point2.x;
    p.y = point1.y + point2.y;
    p.z = point1.z + point2.z;

    return p;
  }

  //friend operator to subtract two points
  inline Point operator - (const Point& point1, const Point& point2)
  {
    Point p;
 
    p.x = point1.x - point2.x;
    p.y = point1.y - point2.y;
    p.z = point1.z - point2.z;
    
    return p;
  }

  //friend operator to multiply a point with scalar
  inline Point operator * (const double scalar, const Point& point)
  {
    Point p;
 
    p.x = scalar * point.x;
    p.y = scalar * point.y;
    p.z = scalar * point.z;
    
    return p;
  }

  //friend operator to multiply a point with scalar
  inline Point operator * (const Point& p, const double s)
  {
    return s * p;
  }

  //friend operator for division with scalar (though one could replace division with multiplication as here)
  inline Point operator / (const Point& p, const double s)
  {
    return p*(1/s);
  }
  //friend operator for division with scalar (though one could replace division with multiplication as here)
  inline Point operator / (const double s, const Point& p)
  {
    return p*(1/s);
  }
  
  //friend operator to calculate distance between two points
  inline double operator || (const Point& point1, const Point& point2)
  {
    double x,y,z;
    x = point1.x - point2.x;
    y = point1.y - point2.y;
    z = point1.z - point2.z;

    return (double)sqrt(pow((double)x,2.0) + pow((double)y,2.0) + pow((double)z,2.0));
  }

  inline ostream& operator << (ostream& os, const Point& point)
  {
    os << point.x << " " << point.y << " " << point.z << flush;
    return os;
  }




  inline istream& operator >> (istream& os, Point& p)
  {
    char tmpX[255];
    char tmpY[255];	
    char tmpZ[255];

    os  >> tmpX >> tmpY >> tmpZ;

    p.setX(atof(tmpX));
    p.setY(atof(tmpY));
    p.setZ(atof(tmpZ));

    return os;
  }




} //close namespace cxxadt

#endif //POINTI_H

#ifdef POINT
#define  NL endl

int main()
{
  Point p1(0,0,0);
  Point p2(p1);
  Point p3(4,5,6);
  Point p4(0,0,8);
  Point p5(-3,-4,-5);
  Point p6(-8,0,0);
  Point p7; 
  Point *p8 = new Point(7,8,9);
  Point p9(*p8);
  Point p10(9,8);
  Point *p11 = p8;
  Point p12(1.0,2.0,1.95);
  Point p13(p7);
  Point p14(1,1,1);
  Point p15(1,1,1);

  double distance;
  cout << "Testing class Point\n";
  cout << "The points are:\n";
  
  cout << "p1: " << p1;
  cout << "p2: " << p2;
  cout << "p3: " << p3;
  cout << "p4: " << p4;
  cout << "p5: " << p5;
  cout << "p6: " << p6;
  cout << "p7: " << p7;
  cout << "p8: " << *p8;
  cout << "p9: " << p9;
  cout << "p10: " << p10;
  cout << "p11: " << *p11;
  cout << "p12: " << p12;
  cout << "p13: " << p13;
  
  delete p8;
  
  distance = p1 || p2;
  cout << "Distance between p1 p2 :" << distance << " (should be 0)\n"<<flush;
  distance = p1 || p3;
  cout << "Distance between p1 p3 :" << distance << " (should be 8.77)\n"<<flush;
  distance = p1 || p4;
  cout << "Distance between p1 p4 :" << distance << " (should be 8)\n"<<flush;
  distance = p1 || p5;
  cout << "Distance between p1 p5 :" << distance << " (should be 7.07)\n"<<flush;
  distance = p1 || p6;
  cout << "Distance between p1 p6 :" << distance << " (should be 8)\n"<<flush;
  
  p7 = p3 - p1;
  cout << "Subtracting p3-p1 (should be (4,5,6))\n";
  cout << "p7: " <<p7;
  
  p7 = p5 - p3;
  cout << "Subtracting p5-p3 (should be (-7,-9,-11))\n";
  cout << "p5: " << p5;
  cout << "p3: " << p3;
  cout << "p7: " <<p7;
  
  p7 = p5 + p3;
  cout << "Adding p5+p3 (should be (1,1,1))\n";
  cout << "p7: " << p7;
  
  p7 += p3;
  cout << "Assign p7 += p3 (should be (5,6,7))\n";
  cout << "p7: " << p7;
  
  
  cout << "Deleted p8, p9 should remain\n";
  cout << "p9 : " << p9;
  cout << "Deleted p8, p11 is undefined\n";
  cout << "p11 : " << *p11;
  cout << "p8 (just happens to be) : " << *p8;
  
  p7 -= p5 -= p3;
  cout << "Assign p7 -= p5 -= p3 (p5 should be (-7.-9.-11), " 
       << "p7 should be (12,15,18)\n";
  cout << "p3 : " << p3;
  cout << "p5 : " << p5;
  cout << "p7 : " << p7;
  
  p7.setX(-100).setY(-200).setZ(-300);
  cout << "Setting p7.setX(-100).setY(-200).setZ(-300)\n"; 
  cout <<  "p7: x:" <<  p7.getX() << " y: " << p7.getY() << " z: " << p7.getZ()
       << NL;
  
  p7 *= 0.4;
  cout << "Multiplying p7 with 0.4, p13 should be (0,0,0)\n";
  cout << "p7  : " << p7 ;
  cout << "p13 : " << p13;

  cout << "Points p14 and p15 should be equal (true == 1) " << endl;
  if (p14 == p15)
    cout << true << endl;
  else
    cout << false << endl;

  cout << "Points p1 and p3 should not be equal (false == 0) " << endl;
  if (p1 == p3)
    cout << true << endl;
  else
    cout << false << endl;

  Point p16(2,2,2);
  cout << "Multiplying p16(2,2,2) with 3 (i.e., 3*p16)" << endl; 
  cout << "3*p16: " << 3 * p16 << endl;
  cout << "Multiplying 3 with p16(2,2,2) (i.e., p16*3)" << endl;
  cout << "p16*3: " << p16 * 3 << endl;

}

#endif






