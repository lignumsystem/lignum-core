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
  points.push_back(rightcorner);
  points.push_back(apexcorner);
  points.push_back(leftcorner);
  return points;
}

  bool Kite::intersectShape(const Point& o,const PositionVector& l)const
  {
    ///\par Line-Kite intersection detection
    /// -# Check that the observation point \p o is \e not above the Kite
    /// -# Check the line \p l is not parallel with the Kite plane
    /// -# Calculate intersection point \f$ p_i \f$ between the line \p l and the plane
    ///    determined by the Kite
    /// -# Calculate if the  \f$ p_i \f$ is inside the Kite

    //Observation point strictly below Kite
    double o_maxz = o.getZ();
    double maxZ = getMaxZ();
    if (o_maxz > maxZ){
      //cout << "Point "<< o <<" above" <<endl; 
      return false;
    }
    //Check if beam direction parrallel with leaf blade
    double cosalpha = Dot(PositionVector(l).normalize(),getNormal());
    if (fabs(cosalpha) <= EPS18){
      //cout << "Beam " << l << " parallel" <<endl;
      return false;
    }
    //Use Triangle to determine intersection with plane
    pair<Point,double> p_intersect = intersectionPoint(o,l);
    //Check if intersection point in the direction of 'l'
    //If the scalar 'd' in 'o+dl', distance to intersection point, is negative -> intersection point is behind
    if (p_intersect.second < 0.0){
      return false;
    }
    //Determine if p_intersect inside Kite
    bool p_inside = insideShape(p_intersect.first);
    return p_inside;
  }

  ///Triangle is used to determine intersection point with plane
  ///\sa Triangle::intersectShape
  pair<Point,double> Kite::intersectionPoint(const Point& o,const PositionVector& l)const
  {
    Triangle t(basecorner,leftcorner,rightcorner);
    pair<Point,double> p_intersect = t.intersectionPoint(o,l);
    return p_intersect;
  }

  bool Kite::insideShape(const Point& p)const
  {
    /// \par Calculation point inside Kite
    ///
    /// Calculate the four angles between the line-plane intersection point \p p
    /// and the Kite corner points. If the sum of the angles is 360 degrees, \f$2\pi\f$,
    /// the point \p p  is inside Kite.

    //Construct vectors from intersection point to Kite corners
    PositionVector pB = PositionVector(basecorner-p).normalize();
    PositionVector pL = PositionVector(leftcorner-p).normalize();
    PositionVector pA = PositionVector(apexcorner-p).normalize();
    PositionVector pR = PositionVector(rightcorner-p).normalize();
    //Calculate the four angles between intersection point and corner points
    double cosBL = Dot(pB,pL);
    double cosLA = Dot(pL,pA);
    double cosAR = Dot(pA,pR);
    double cosRB = Dot(pR,pB);
    //If the sum of the angles is 360 degrees, 2pi radians,
    //the intersection point is inside triangle.
    //The angle ab in radians: acos(cos(ab)) 
    double radBL = acos(cosBL);
    double radLA = acos(cosLA);
    double radAR = acos(cosAR);
    double radRB = acos(cosRB);
    double sum = radBL+radLA+radAR+radRB;
    //If the sum is close enough 2*pi return true
    if (fabs(sum - 2.0*PI_VALUE) <= EPS15){
      //cout << "Point " << p << endl;
      //cout << "Inside " << sum << " " << 180.0*sum/PI_VALUE << " " << fabs(sum - 2.0*PI_VALUE) <<endl;
      return true;
    }
    else{
      cout << "Point " << p << endl;
      cout << "Outside " << sum << " " << 180.0*sum/PI_VALUE << " " << fabs(sum - 2.0*PI_VALUE) <<endl;
      return false;
    }
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

  double Kite::getArea()const
  {

  double area;
  // sides of the kite + minor axis (= base of the tiangles) are the sides
  // of the kites. Their lengths:

  double axis = (PositionVector(apexcorner-basecorner)).length();
  double diagonal = (PositionVector(rightcorner-leftcorner)).length();
  area = axis * diagonal / 2.0;
  
  return area;
  }

  double Kite::getMaxZ()const
  {
    double maxB = basecorner.getZ();
    double maxL = leftcorner.getZ();
    double maxR = rightcorner.getZ();
    double maxA = apexcorner.getZ();
    double maxZ = std::max({maxB,maxL,maxR,maxA});
    return maxZ;
  }
  
}//closing namespace cxxadt

