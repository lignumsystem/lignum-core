//Ellipse.cc
//----------
#include <Ellipse.h>
#include <cmath>
namespace cxxadt{

  Ellipse::Ellipse(const Point& center0, 
                   const PositionVector& normal0, 
		   const double& semimajoraxis0,  
                   const double& semiminoraxis0)
    :center(center0),normal(normal0),semimajoraxis(semimajoraxis0),
     semiminoraxis(semiminoraxis0)
  {
    
  }

  Ellipse::Ellipse(const PositionVector& petiole0,
                  const PositionVector& normal0, 
		  const double& semimajoraxis0,  
                  const double& semiminoraxis0)
    :normal(normal0),semimajoraxis(semimajoraxis0),
     semiminoraxis(semiminoraxis0)
  {
    //x1u is (should be) in fact x1u()!
    PositionVector x1u(normal0.getZ(),0,-normal0.getX());
    x1u=x1u.normalize();
 
    PositionVector petiolecenter(x1u*semimajoraxis0);
    PositionVector center0=petiole0+petiolecenter;
    center=Point(center0);

  }


  Ellipse::Ellipse(const Ellipse& e)
    :center(e.center),normal(e.normal),semimajoraxis(e.semimajoraxis),
     semiminoraxis(e.semiminoraxis)
  {
  }

  Ellipse& Ellipse::operator=(const Ellipse& e)
  {
    center = e.center;
    normal = e.normal;
    semimajoraxis = e.semimajoraxis;
    semiminoraxis = e.semiminoraxis;
    return *this;
  }

  PositionVector Ellipse::x1u()const{

    PositionVector x1(normal.getZ(),0,-normal.getX());
    x1=x1.normalize();
    //cout<<"x1u() x1u="<<x1<<endl;
    return x1; 
  }

  PositionVector Ellipse:: y1u()const{

    PositionVector y1(Cross(normal,x1u()));
    y1=y1.normalize();
    return y1;
  }


  Point  Ellipse::getSemimajorAxisPoint()const{

    Point p=Point((Point)center+Point(semimajoraxis*x1u()));
    return p;
  }

  Point  Ellipse::getSemiminorAxisPoint()const{

    Point p=Point((Point)center+Point(semiminoraxis*y1u()));
    return p;
  }


//getting the ellipse points using the ellipse equation
//X=Center + a*cos(t)*X1u +b*sin(t)*Y1u
//where t:[0,2pi] and the step=[2*pi/n];
//now the n parameter is defined as 50.
    
vector<Point>& Ellipse::getVertexVector(vector<Point>& points)const
{
  int i,n;
  double t;
  Point x;

  n=50;

  double step=(double)(2.0*PI_VALUE/n);


    
  for(i=0; i<n; i++){
    t=(double)(i*step);
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

   double areaold, areanew,
         scalcoef; 
   double adbasex, adbasey, adbasez;
  
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

   return getArea();
  }


  //This method checks crossing a ellipse 
  //with a straight line in space, 
  //given by the O point(O - the first parameter the method) 
  //and direction B(B - the second parameter the method).

  
 bool Ellipse::intersectShape(const Point& O,
			      const PositionVector& B0)const{
   double t;
   double cosangleBCXu,angleBCXu;

   PositionVector o(O);           //the view point on the light beam
                                  //(the pyramid apex)
   PositionVector beam=B0;        //the light beam vector

   beam = beam - o; //the vector from O to B0

   PositionVector B;
   PositionVector c(center);


   //Looking for the crossing point B on the ellipse plane with
   // the beam.
   

   if ( ( Dot(normal,o)-Dot(normal,c) ) != 0 
        && Dot(normal,beam) !=0 )
   {
     t=-( Dot(normal,o)-Dot(normal,c)) /
         Dot(normal,beam) ;
     B=o+beam*t;

   }
   else
     return false;
                                 
   PositionVector CB=c-B;


   if ( (CB.length()*x1u().length()) !=0 )
     cosangleBCXu=Dot(CB,x1u())/(CB.length()*x1u().length());
   else{
     cosangleBCXu=1; 
   };
 
   angleBCXu = acos(cosangleBCXu);

   if (semimajoraxis == 0 || semiminoraxis ==0)
     return false;
   
   if (pow(CB.length()*cos(angleBCXu)/semimajoraxis,2.0)+
	 pow(CB.length()*sin(angleBCXu)/semiminoraxis,2.0) <= 1)
       return true;
   else 
     return false;
  
 }
  


}//closing namespace cxxadt

#ifdef ELLIPSE
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

  

