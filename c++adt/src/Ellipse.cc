//Ellipse.cc
//----------
#include <Ellipse.h>
#include <Polygon.h>
#include <cmath>
namespace cxxadt{

  //For visualization of ellipse it is necessary that the axes
  //are specified as vectors (xdir, ydir). This constructor sets
  //them in a bit arbitrary way (with the aid of position center0).
  //Prefer other constructors for a better spcification of ellipse
  //orientation.
  Ellipse::Ellipse(const Point& center0, 
                   const PositionVector& normal0, 
		   const double& semimajoraxis0,  
                   const double& semiminoraxis0)
    :center(center0),normal(normal0),semimajoraxis(semimajoraxis0),
     semiminoraxis(semiminoraxis0)
  {
    PositionVector v = Cross(normal0,PositionVector(center0));
    v. normalize();
    PositionVector x1(normal0);
    x1.rotate(Point(0,0,0),v,PI_VALUE/2.0);
    x1.normalize();

    PositionVector y1(Cross(normal,x1));
    y1.normalize();

    xdir = x1;
    ydir = y1;
  }

  Ellipse::Ellipse(const Point& petiole_end,
		   const PositionVector& petioledir,
		   const PositionVector& normal0, 
		   const double& semimajoraxis0,  
		   const double& semiminoraxis0)
    :normal(normal0),semimajoraxis(semimajoraxis0),
     semiminoraxis(semiminoraxis0)
  {

    PositionVector v = Cross(normal0,petioledir);
    PositionVector x1(normal0);
    x1.rotate(Point(0,0,0),v,PI_VALUE/2.0);
    x1.normalize();

    PositionVector y1(Cross(normal,x1));
    y1.normalize();
    PositionVector petiolecenter(x1*semimajoraxis0);
    PositionVector center0=PositionVector(petiole_end)+petiolecenter;
    center=Point(center0);
 
    xdir = x1;
    ydir = y1;
  }
  
  Ellipse::Ellipse(const Point& petiole_end,
		   const PositionVector& normal0, 
		   const PositionVector& xdir0,
		   const PositionVector& ydir0,
		   const double& semimajoraxis0,  
		   const double& semiminoraxis0)
    :normal(normal0),xdir(xdir0),ydir(ydir0),semimajoraxis(semimajoraxis0),
     semiminoraxis(semiminoraxis0)
  {

    PositionVector petiolecenter(xdir*semimajoraxis0);
    PositionVector center0=PositionVector(petiole_end)+petiolecenter;
    center=Point(center0);
  }

  Ellipse::Ellipse(const PositionVector& p,
		   const PositionVector& n,
		   const PositionVector& x1, 
		   const double& semimajoraxis0,  
		   const double& semiminoraxis0)
    :normal(n),semimajoraxis(semimajoraxis0),
     semiminoraxis(semiminoraxis0)
  {
    xdir = x1;
    xdir.normalize();
    ydir = Cross(xdir,normal);
    ydir.normalize();
    PositionVector petiolecenter(xdir*semimajoraxis);
    PositionVector center0=p+petiolecenter;
    center=Point(center0);
  }
    
    
  Ellipse::Ellipse(const Ellipse& e)
    :Shape(Ellipse::Shape()),center(e.center),normal(e.normal),
     xdir(e.xdir),ydir(e.ydir),semimajoraxis(e.semimajoraxis),
     semiminoraxis(e.semiminoraxis)
  {
  }

  Ellipse& Ellipse::operator=(const Ellipse& e)
  {
    center = e.center;
    normal = e.normal;
    semimajoraxis = e.semimajoraxis;
    semiminoraxis = e.semiminoraxis;
    xdir = e.xdir;
    ydir = e.ydir;
    return *this;
  }

  PositionVector Ellipse::x1u()const{

    //PositionVector x1(normal.getZ(),0,-normal.getX());
    //x1.normalize();
    //xdir = x1;
    //cout<<"x1u() x1u="<<x1<<endl;
    return xdir; 
  }

  PositionVector Ellipse:: y1u()const{

    //PositionVector y1(Cross(normal,x1u()));
    //y1.normalize();
    return ydir;
  }


  Point  Ellipse::getSemimajorAxisPoint()const{

    Point p=Point((Point)center+Point(semimajoraxis*x1u()));
    return p;
  }

  Point  Ellipse::getSemiminorAxisPoint()const{

    Point p=Point((Point)center+Point(semiminoraxis*y1u()));
    return p;
  }


  void Ellipse::roll(const double& angle)
  {
    Point p(0.0,0.0,0.0);
    normal.rotate(p,xdir,angle);
    normal.normalize();
    ydir.rotate(p,xdir,angle);
    ydir.normalize();
}

  void Ellipse::pitch(const double& angle)
  {

    //rotation around axis that goes through point where major axis
    //intersects with perimeter ( -semimajoraxis*xdir = end of
    //petiole, presumably) and is parallel with semiminoraxis =>
    //center of ellipse is changed.
    // Normal, xdir are just rotated
 
    //Position of point of rotation at perimeter
    Point start = center - semimajoraxis*Point(xdir);

    //vector pointing from axis of rotation to center
    PositionVector cc = PositionVector(center-start);

    Point p(0.0,0.0,0.0);

    normal.rotate(p,ydir,angle);
    xdir.rotate(p,ydir,angle);
    normal.normalize();
    xdir.normalize();
    cc.rotate(p,ydir,angle);

    center = start + Point(cc);  
}


 void Ellipse::turn(const double& angle)
 {
    //rotation around axis that goes through point where major axis
    //intersects with perimeter ( -semimajoraxis*xdir = end of
    //petiole, presumably) and is parallel with normal =>
    //center of ellipse is changed
    // xdir, ydir are just rotated
 
    //Position of point of rotation at perimeter
    Point start = center - semimajoraxis*Point(xdir);

    //vector pointing from axis of rotation to center
    PositionVector cc = PositionVector(center-start);

    Point p(0.0,0.0,0.0);
    xdir.rotate(p,normal,angle);
    ydir.rotate(p,normal,angle);
    xdir.normalize();
    ydir.normalize();
    cc.rotate(p,normal,angle);

    center = start + Point(cc);
 }

//getting the ellipse points using the ellipse equation
//X=Center + a*cos(t)*X1u +b*sin(t)*Y1u
//where t:[0,2pi] and the step=[2*pi/n];
//The npoints parameter is defaulted as 50.
    
  vector<Point>& Ellipse::getVertexVector(vector<Point>& points,int npoints)const
{
  Point x;

  double step= 2.0*PI_VALUE/static_cast<double>(npoints);

  for(int i=0; i<npoints; i++){
    double t=(double)(i*step);
    x=getCenterPoint()+Point((getSemimajorAxis()*cos(t))*x1u())
                      +Point((getSemiminorAxis()*sin(t))*y1u());
    points.push_back(x);
  }
  return points;
}



//Creation  a new ellipse from the old one 
//using the new ellipse area
//Scaling equation is X'=S*X
//where X' - a new point
//      X  - a old point
//      S - the 4x4 matrix for scaling 
//(see a book for the computer graphic)
//The scaling coefficient scalcoef in our case
//is calculated as
//scalcoef=sqrt(areanew/areaold);




//This case  with the base point as the scaling center 

  double Ellipse::setArea(double area,  const Point& base){
    
    double areaold, areanew, scalcoef; 
    double adbasex, adbasey, adbasez;

    //Set the scaling around the center point
    setCenterPoint(base);

    areaold=getArea();
    areanew=area; 

    scalcoef=sqrt(areanew/areaold);

    adbasex= base.getX()*(1-scalcoef);
    adbasey= base.getY()*(1-scalcoef);
    adbasez= base.getZ()*(1-scalcoef);

    vector<Point> points;
    points.push_back(getSemimajorAxisPoint());
    points.push_back(getSemiminorAxisPoint());
    Point x,p;

    for(int i=0; i< static_cast<int>(points.size()); i++){
      p=(Point)points[i];
      x.setX(p.getX() *scalcoef  + adbasex);
      x.setY(p.getY() *scalcoef  + adbasey);
      x.setZ(p.getZ() *scalcoef  + adbasez);
      switch(i){
      case 0:
	setSemimajorAxis(getCenterPoint() || x);
	break;
      case 1:
	setSemiminorAxis(getCenterPoint() || x);
	break;
      };
    };

    //Move  the scale  center (i.e.  the ellipse)  to the  new ellipse
    //center
    PositionVector from_base_to_center(x1u()*getSemimajorAxis());
    center=Point((const PositionVector)base+from_base_to_center);
    return getArea();
  }


  //This method checks crossing a ellipse 
  //with a straight line in space, 
  //given by the O point(O - the first parameter the method) 
  //and direction B(B - the second parameter the method).

  
  bool Ellipse::intersectShape(const Point& O,
			       const PositionVector& B0)const{

    //If the beam (starting from Point p0 with direction v) hits
    //the ellipsis?
    //It has its center at Point ps
    //other properties are defined by BroadLeaf leaf, PosVector petiole


    bool NO_HIT = false;
    bool HIT_THE_FOLIAGE = true;

    //  Point pc =  GetCenterPoint(leaf);
    Point pc = center;
    Point p0 = O;
    const PositionVector v = B0;

    //    1.      Rough testing, if point p0 is higher (z-axis=height) than
    //      pc + max width of the ellipsis, the beam
    //      cannot hit the ellipsis
    //   double a;
    //   a = (double)GetShape(leaf).getSemimajorAxis();
    double a = semimajoraxis;
    if( p0.getZ() > pc.getZ() + 2.0*a) {
      return NO_HIT;
    }

    //  PositionVector n  = GetShape(leaf).getNormal();
    PositionVector n = normal;

    //    2. Where does line starting at p0 and having direction b intersect the plane
    //       that contains the ellipsis leaf

    double vn = Dot(v, n);


    if( maximum(vn, -vn) < R_EPSILON ) {
      return NO_HIT;
    }           // if v * n = 0 => beam parallel with the plane; cannot
    // we forget here the possibility that the beam is in the plane

  
    // 3. Calculate the point where beam hits the plane (=vector pointing to this point)

    // 3.2 Calculate the hit point

    double u;
    u = (Dot(n, PositionVector( pc  - p0 )) ) / vn;

    //If u < 0 the hit point is in the opposite dirction to that where the sky
    //sector is (it is pointed by v)

    if(u <= 0.0)
      return NO_HIT;

    PositionVector hit(3);
    hit = PositionVector(p0) + u * v;


    // 4. Test if the hit point is inside the ellipse

    double coord_a, coord_b;
    PositionVector diff(3);


    //  double b = (double)GetShape(leaf).getSemiminorAxis();
    double b = semiminoraxis;
    diff = hit - PositionVector(pc);
    //  Point pend = GetEndPoint(GetPetiole(leaf));
    //  coord_b = Dot(PositionVector(pend - pc), diff);
    coord_b = Dot(diff,ydir);                //len of ydir == 1
    // coord_b /= b;            
    //  if(maximum(coord_b, -coord_b) > b) {
    if(abs(coord_b) > b) {
      return NO_HIT;
    }


    coord_a = sqrt( Dot(diff, diff) - coord_b * coord_b );

    // if(maximum(coord_a, -coord_a) > a) {
    if(abs(coord_a) > a) {
      return NO_HIT;
    }

    if(pow(coord_a/a, 2.0) +
       pow(coord_b/b, 2.0) > 1.0)
      return NO_HIT;
    else
      return HIT_THE_FOLIAGE;
 
  }


}//closing namespace cxxadt

#ifdef ELLIPSEMAIN
#include <iostream>
#include <stdlib.h>
using namespace cxxadt;


void printing(const  Point& p){
  
  cout<<"----------------------------------------------"<<endl;
  cout<< "x=" << p.getX()<< "  y=" << p.getY()<< "  z=" << p.getZ()<<endl;
  cout<<"----------------------------------------------"<<endl;

}

int main()
{


  Point c1=Point(0,0,0);
  PositionVector n1(0,0,1);
  PositionVector petiole(1,1,1);

  double a1=2;
  double b1=1;

  Ellipse e1(c1,n1,a1,b1);
  //Ellipse e2(petiole, n1, a1,b1);
  
    
  PositionVector normal(e1.getNormal());
  cout<<"ellipse normal vector="<<normal<<endl;
  a1=e1.getCenterPoint() || e1.getSemimajorAxisPoint();
  cout<<"semimajoraxis a1="<<a1<<endl;
  b1=e1.getCenterPoint() || e1.getSemiminorAxisPoint();
  cout<<"semiminoraxis b1="<<b1<<endl;

  double area1=e1.getArea();
  cout<<"area1="<<area1<<endl;

//   e1.setArea(12, Point(1,1,1) );

//   double a2=e1.getCenterPoint() || e1.getSemimajorAxisPoint();
//   cout<<"semimajoraxis  a2="<<a2<<endl;
//   double b2=e1.getCenterPoint() || e1.getSemiminorAxisPoint();
//   cout<<"semiminoraxis b2="<<b2<<endl;

//   double area2=e1.getArea();
//   cout<<"area2="<<area2<<endl;

  bool intersection;
  
  Point PO1(0,0,1);//this case doesn't cross the ellipse
  PositionVector PB1(1,1,0);
 
  intersection=e1.intersectShape(PO1,PB1);
  if( intersection){
    cout<<"1. vector"<< PB1<<endl;
    cout<<" crosses the ellipse"<<endl;
  }
  else{
    cout<<"1. vector"<< PB1<<endl;
    cout<<" doesn't cross the ellipse"<<endl;
  }

  Point PO2(4,4,4);//this case crosses the ellipse
  PositionVector PB2(-4,-4,-4);
  intersection=e1.intersectShape(PO2,PB2);

  if( intersection){
    cout<<"2. vector"<< PB2<<endl;
    cout<<" crosses the ellipse"<<endl;
  }
  else{
    cout<<"2. vector"<< PB2<<endl;
    cout<<" doesn't cross the ellipse"<<endl;
  }

  vector<Point> points;
  points=e1.getVertexVector(points);

  cout<<"----------------------------------------------"<<endl;
  cout << "3.The ellipse points are   "<< endl;

    
  for_each(points.begin(),points.end(),printing);   
 

  exit(0);
}


#endif

  

