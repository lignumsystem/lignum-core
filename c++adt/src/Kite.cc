//Kite.cc
//----------------------------------
#include <Kite.h>

namespace cxxadt{

//Construct a kite by defining four vertex points;


  Kite::Kite(const Point& p1,const  Point& p2,const Point& p3, const Point& p4)
  {
    basecorner=p1; leftcorner=p2; rightcorner=p3; apexcorner=p4;
    
  }
  
  Kite& Kite::operator=(const Kite& k)
  {
    basecorner = k.basecorner; leftcorner = k.leftcorner; rightcorner= k.rightcorner; 
    apexcorner = k.apexcorner;
    return *this;
  }

  //member function uses the same logic (add a vector, i.e. Point)
  //as MoveTree in TreeFunctor.h (stl-lignum)
  //This friend function is used by MoveHwTree (through friend Move of BroadLeaf)
  void Kite::move(const Point& mov) {
    Point tmp = leftcorner + mov;
    leftcorner = tmp;
    tmp = rightcorner + mov;
    rightcorner = tmp;
    tmp = apexcorner + mov;
    apexcorner = tmp;
    tmp = basecorner + mov;
    basecorner = tmp;
  }



vector<Point>& Kite::getVertexVector(vector<Point>& points)const
{
  points.push_back(basecorner);
  points.push_back(leftcorner);
  points.push_back(rightcorner);
  points.push_back(apexcorner);
  return points;
}


  //the center point according to equation Pc=(P1+P2+P3+p4)/4
  Point  Kite::getCenterPoint()const {
    Point centerp = 0.25 * (basecorner+leftcorner+rightcorner+apexcorner);
    return centerp;
  }

//Normal as cross product of main and secondary axis

PositionVector Kite::getNormal()const
{
  PositionVector p1(leftcorner - rightcorner);
  PositionVector p2(apexcorner - basecorner);

 PositionVector normal= Cross(p1,p2);
 //Normal points always to upper hemisphere
 if(normal.getZ() < 0.0)
   normal = -1.0*normal;

   normal.normalize();
 
 return normal;
} 


  //Area as sum of two Triangles, the area can be expressed
  //as a concise expression. May not be true if the
  //axes of of the kite are not perpendicular

  double Kite::getArea()const{

  double area;
  // sides of the kite + minor axis (= base of the tiangles) are the sides
  // of the kites. Their lengths:

  double axis = (PositionVector(apexcorner-basecorner)).length();
  double diagonal = (PositionVector(rightcorner-leftcorner)).length();
  area = axis * diagonal / 2.0;
  
  return area;
}


  
}//closing namespace cxxadt

