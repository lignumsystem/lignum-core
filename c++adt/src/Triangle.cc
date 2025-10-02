//Triangle.cc
//----------------------------------
#include <Triangle.h>

namespace cxxadt{

//Construct a triangle by defining three triangle points;
//Getting the triangle area
//Construct a triangle by defining the triangle area
//Getting the center of the triangle


  Triangle::Triangle(const Point& p1,const  Point& p2,const Point& p3)
  {
    a=p1; b=p2; c=p3;
    N = getNormal();
  }
  
  Triangle& Triangle::operator=(const Triangle& t)
  {
    a = t.a; b= t.b; c = t.c;
    N = getNormal();
    return *this;
  }

  //member function uses the same logic (add a vector, i.e. Point)
  //as MoveTree in TreeFunctor.h (stl-lignum)
  //This friend function is used by MoveHwTree (through friend Move of BroadLeaf)
  Triangle& Triangle::move(const Point& mov) {
    Point tmp = a + mov;
    a = tmp;
    tmp = b + mov;
    b = tmp;
    tmp = c + mov;
    c = tmp;
    N = getNormal();
    return *this;
  }



vector<Point>& Triangle::getVertexVector(vector<Point>& points)const
{
  points.push_back(a);
  points.push_back(b);
  points.push_back(c);
  return points;
}


//the center of the triangle according 
// equation Pc=(P1+P2+P3)/3

Point Triangle::getCenterPoint()const 
{                            
  Point center;

  vector<Point> points;
  points=getVertexVector(points);

  Point sum(0.0,0.0,0.0);
  Point tmp;
  for(int i=0; i<3; i++){
    tmp = sum + points[i];
    sum = tmp;
  }
  center.setX(sum.getX()/3.0);
  center.setY(sum.getY()/3.0);
  center.setZ(sum.getZ()/3.0);

  return center;
}

//getting the triangle normal vector

PositionVector Triangle::getNormal()const
{
  PositionVector p1(a);
  PositionVector p2(b);
  PositionVector p3(c);

 // these vectors are the triangle sides 
 
 PositionVector p12=p1-p2;
 PositionVector p13=p1-p3;
 PositionVector normal= Cross(p12,p13);
 //Normal points always to upper hemisphere
 if(normal.getZ() < 0.0)
   normal = -1.0*normal;

 if (normal.length()!= 0.0)
   normal.normalize();
 
 return ( normal  );
} 

//set up the triangle center point
//end change the triangle points
//according the center point 

Triangle&  Triangle::setCenterPoint(const Point& center0){
   Point center;
   center.setX(center0.getX());
   center.setY(center0.getY());
   center.setZ(center0.getZ());
   setArea(getArea(),center);
   return *this;
}


//Calculation  the triangle area 
// using equation 
//A=1/2*|((leftcorner,rightcorner)X(leftcorner,apexcorner))|
//where X is  the cross operation between vectors

double Triangle::getArea()const{

  double area;
   
 // These vectors are based on the origin
  
  PositionVector p1(a);
  PositionVector p2(b);
  PositionVector p3(c);

 // these vectors are the triangle sides 
 
 PositionVector p12=p1-p2;
 PositionVector p13=p1-p3;
 
 area=( fabs( Cross(p12,p13).length() ) )/2.0;
 
 return ( area );
 
}

  double Triangle::getMaxZ()const
  {
    double maxL = a.getZ();
    double maxA = b.getZ();
    double maxR = c.getZ();

    double maxLA = max(maxL,maxA);
    double maxLAR = max(maxR,maxLA);
    return maxLAR;
  }

//Creation  a new triangle from the old one 
//using the new triangle area
//Scaling equation is X'=S*X
//where X' - a new point
//      X  - a old point
//      S - the 4x4 matrix for scaling 
//(see a book for the computer graphic)
//The scaling coefficient scalcoef in our case
//is calculated as
//scalcoef=sqrt(areanew/areaold);


//This case  with the triangle centroid as the scaling center 

double Triangle::setArea(double area)
{
  double areaold,areanew,scalcoef;
  areaold=areanew=scalcoef=0.0;
  double adbasex,adbasey,adbasez;
  adbasex=adbasey=adbasez=0.0;
  
  areaold=getArea();
  areanew=area; 

  scalcoef=sqrt(areanew/areaold);

  adbasex=getCenterPoint().getX()*(1-scalcoef);
  adbasey=getCenterPoint().getY()*(1-scalcoef);
  adbasez=getCenterPoint().getZ()*(1-scalcoef);

  vector<Point> points;
  points=getVertexVector(points);
  Point x,p;

  for(int i=0; i<3; i++){
   p=(Point)points[i];
   x.setX(p.getX() *scalcoef  + adbasex);
   x.setY(p.getY() *scalcoef  + adbasey);
   x.setZ(p.getZ() *scalcoef  + adbasez);
   switch(i){
   case 0:
     setA(x);
     break;
   case 1:
     setB(x);
     break;
   case 2:
     setC(x);
     break;
   };
  };

  return getArea();
}

//This case uses the arbitrary base point as the scaling center 

double Triangle::setArea(double area, const Point& base )
{
  double areaold,areanew,scalcoef;
  areaold=areanew=scalcoef=0.0;
  double adbasex,adbasey,adbasez;
  adbasex=adbasey=adbasez=0.0;
  
  areaold=getArea();
  areanew=area; 

  scalcoef=sqrt(areanew/areaold);

  adbasex= base.getX()*(1-scalcoef);
  adbasey= base.getY()*(1-scalcoef);
  adbasez= base.getZ()*(1-scalcoef);

  vector<Point> points;
  points=getVertexVector(points);
  Point x,p; 

  for(int i=0; i<3; i++){
   p=(Point)points[i];
   x.setX(p.getX() *scalcoef  + adbasex);
   x.setY(p.getY() *scalcoef  + adbasey);
   x.setZ(p.getZ() *scalcoef  + adbasez);
   switch(i){
   case 0:
     setA(x);
     break;
   case 1:
     setB(x);
     break;
   case 2:
     setC(x);
     break;
   default:
     ;
   };
  };
  return getArea();
}
 
  bool Triangle::intersectShape(const Point& o, const PositionVector& l)const
  {
    ///\par Line-Triangle intersection detection
    /// -# Check that the observation point \p o is \e not above the Triangle
    /// -# Check the line \p l is not parallel with the Triangle plane
    /// -# Calculate intersection point \f$ p_i \f$ between the line \p l and the plane
    ///    determined by the Triangle
    /// -# Calculate if the  \f$ p_i \f$ is inside the Triangle
  
    //Check if the observation point is strictly below the Triangle,
    double o_maxz = o.getZ();
    double maxz = getMaxZ();
    //If above return false
    if (o_maxz > maxz){
      return false;
    }
    //Check if beam direction parallel to the Triangle plane
    double cosalpha = Dot(PositionVector(l).normalize(),N);
    if (fabs(cosalpha) <= EPS18){
      return false;
    } 
    //Calculate intersection point
    pair<Point,double> p_intersect = intersectionPoint(o,l);
    //If the scalar 'd' in 'o+dl', distance to intersect point, is negative -> intersection point is behind
    if (p_intersect.second < 0.0){
      return false;
    }
    //Check if the point is inside Triangle
    bool p_inside = insideShape(p_intersect.first);
    if (p_inside == true){
      return true;
    }
    else{
      return false;
    }
  }
  
  pair<Point,double> Triangle::intersectionPoint(const Point& o, const PositionVector& l)const
  {
    /// \par Calculatation line - plane intersection
    ///
    /// Given observation point  \f$ \mathit{o} \f$ is below the Triangle (leaf) calculate the intersection point.
    /// With vector notation a plane is defined by a set of all points \f$ P \f$ that satisfy
    /// the equation \f$ (P - p_0) \cdot \vec{N} \f$  where \f$ p_0 \f$ is
    /// a point in the plane and \f$ \vec{N} \f$ is the normal to the plane.
    ///
    /// The set of all points \f$ P_l \f$ on a line can be defined as \f$ P_l = l_0 + d\hat{l} \f$
    /// where \f$l_0 \f$ is a point on the line, \f$\hat{l} \f$ is a unit vector defining the
    /// direction of the line and \f$ \mathit{d} \f$  is a scalar.
    ///
    /// Substituting \f$ P \f$ for the line equation in the plane equation gives \f$ (l_0 + d\hat{l}-p_0) \cdot \vec{N})=0 \f$.
    /// Expanding gives \f$(\hat{l} \cdot d\vec{N}) + (l_0-p0) \cdot \vec{N} = 0 \f$  and solving for \f$ d \f$ gives
    /// \f$ d = (p_0-l_0) \cdot \vec{N} / \hat{l} \cdot \vec{N} \f$.
    /// When denominator \f$ \hat{l} \cdot \vec{N} != 0 \f$ we can solve for \f$ d \f$ and find the line-plane intersection point (Wikipedia).
    ///+ Geometric interpretation: when denominator \f$ \hat{l} \cdot \vec{N} = 0 \f$ then \f$ d \f$ is undefined. The line is perpendicular
    ///  plane normal and parallel with the plane. When the numerator is 0 the line is in the plane.
    ///  For our purposes (Triangle as a leaf model) we skip both of these cases.
    ///
    ///  \sa Parallelogram::intersectionPoint()

    double dot = Dot(N,l);
    Point p0(getA());
    Point l0(o);
    PositionVector p1(p0-l0);
    double d =  Dot(N,p1)/dot;
    Point p = Point(PositionVector(l0)+(d*l));
    //cout << " Distance d " << d << endl;
    pair<Point,double> p_d(p,d);
    return p_d;
  }

  bool Triangle::insideShape(const Point& p)const
  {
    /// \par Calculation point inside Triangle
    ///
    /// Calculate the three angles between the line-plane intersection point \p p
    /// and the Triangle corner points. If the sum of the angles is 360 degrees, \f$2\pi\f$,
    /// the point \p p  is inside Triangle.
    
    //Construct the vectors from intersection point to
    //triangle corners
    PositionVector pL = PositionVector(getA()-p).normalize();
    PositionVector pA = PositionVector(getC()-p).normalize();
    PositionVector pR = PositionVector(getB()-p).normalize();

    //calculate the three angles between intersection point and
    //corner points, Dot(a,b) = cos(ab)
    double cosLA = Dot(pL,pA);
    double cosRA = Dot(pA,pR);
    double cosRL = Dot(pR,pL);

    //If the sum of the angles is 360 degrees, 2pi radians,
    //the intersection point is inside triangle.
    //The angle ab in radians: acos(cos(ab)) 
    double radLA = acos(cosLA);
    double radRA = acos(cosRA);
    double radRL = acos(cosRL);
    double sum = radLA+radRA+radRL;

    //If the sum is close enough 2*pi return true
    if (fabs(sum - 2.0*PI_VALUE) <= EPS18){
      //cout << " " << sum << " " << 180.0*sum/PI_VALUE << " " << fabs(sum - 2.0*PI_VALUE) <<endl;
      return true;
    }
    else{
      //cout << " " << sum << " " << 180.0*sum/PI_VALUE << " " << fabs(sum - 2.0*PI_VALUE) <<endl;
      return false;
    }
  }
    
//Rotate apex point around the base of the triangle by alpha
Triangle& Triangle::pitch(const double alpha)
{
  PositionVector v1(a);
  PositionVector v2(b);
  PositionVector v3(c);
  //Axis of rotation is the base
  PositionVector base(v1-v2);
  //Right edge of the triangle
  PositionVector right_edge(v3-v2);
  base.normalize();
  right_edge.normalize();
  //The angle between those two
  double cosalpha = Dot(base,right_edge);
  //Find the the  point of rotation: the point  of the triangle height
  //on the base
  double s = a || c;
  //cosalpha = l/s --> l = s*cosalpha
  double l = s*cosalpha;
  //The point of rotation: the point of triangle height at the base
  PositionVector p1 = v2 + l*base;
  //Rotate the apex round p1
  v3.rotate(Point(p1),base,alpha);
  //reset apex corner
  c = Point(v3.getX(),v3.getY(),v3.getZ());
  return *this;
}


//rotate amount angle around axis defined by p0 and dir
Triangle& Triangle::rotate(const Point& p0, const PositionVector& dir, RADIAN angle) {

  PositionVector new_point(a);
  new_point.rotate(p0,dir,angle);
  a = Point(new_point);

  new_point = PositionVector(c);
  new_point.rotate(p0,dir,angle);
  b = Point(new_point);

  new_point = PositionVector(c);
  new_point.rotate(p0,dir,angle);
  c = Point(new_point);
  return *this;
}

}//closing namespace cxxadt

