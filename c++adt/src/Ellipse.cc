//Ellipse.cc
//----------
#include <Ellipse.h>

namespace cxxadt{

  Ellipse::Ellipse(const Point& center0, 
                   const PositionVector& normal0, 
		   const double& semimajoraxis0,  
                   const double& semiminoraxis0)
  {
    center=center0;
    normal=normal0;
    semimajoraxis=semimajoraxis0;
    semiminoraxis=semiminoraxis0;
    /*
    cout<<"Ellips:ellipse with parameters"<<endl;
    cout<<"center="<<center<<endl;
    cout<<"vector normal="<<normal<<endl;
    cout<<"semimajoraxis="<<semimajoraxis<<endl;
    cout<<"semiminoraxis="<<semiminoraxis<<endl;
    */
  }

  Ellipse::Ellipse(const PositionVector& petiole0,
                  const PositionVector& normal0, 
		  const double& semimajoraxis0,  
                  const double& semiminoraxis0)
  {
    PositionVector x1u(normal0.getZ(),0,-normal0.getX());
    x1u=x1u.normalize();

    PositionVector y1u(Cross(normal0,x1u));
    y1u=y1u.normalize();
 
    PositionVector petiolecenter(x1u*semimajoraxis0);
    PositionVector center0=petiole0+petiolecenter;
    Point center=Point(center0);

    //cout<<"in Ellips with petiole x1u="<<x1u<<endl;

    normal=normal0;
    semimajoraxis=semimajoraxis0;
    semiminoraxis=semiminoraxis0;
    /*
    cout<<"Ellipse petiole with parameters"<<endl;
    cout<<"center="<<center<<endl;
    cout<<"vector normal="<<normal<<endl;
    cout<<"semimajoraxis="<<semimajoraxis<<endl;
    cout<<"semiminoraxis="<<semiminoraxis<<endl;
    */
  }


  PositionVector Ellipse::x1u(){

    PositionVector x1(normal.getZ(),0,-normal.getX());
    x1=x1.normalize();
    //cout<<"x1u() x1u="<<x1<<endl;
    return x1; 
  }

  PositionVector Ellipse:: y1u(){

    PositionVector y1(Cross(normal,x1u()));
    y1=y1.normalize();
    //cout<<"y1u() y1u="<<y1<<endl;
    return y1;
  }


  Point  Ellipse::getSemimajorAxisPoint(){

    Point p=Point((Point)center+Point(semimajoraxis*x1u()));
    //cout<<"getSemimajorAxisPoint ="<<p<<endl;
    return p;
  }

  Point  Ellipse::getSemiminorAxisPoint(){

    Point p=Point((Point)center+Point(semiminoraxis*y1u()));
    //cout<<"getSemiminorAxisPoint ="<<p<<endl;
    return p;
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

   for(int i=0; i< points.size(); i++){
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
  //Image a angle with the O point as the apex of the angle
  //and two sides:
  //the one with the vector OB, the vector of direction B 
  //as a vector having the points O and B 
  //and the second with the OC vector(the ellipse center) 
  //Let the B point is the intersection point 
  //between the ellipse plane and the beam.
  //Let CB - vector between two points:
  //the C and the B.
  //Let X the point where the CB vector crosses the ellipse.
  //The OB vector crosses the ellipce
  //if the COB angle less the COX angle

 bool Ellipse::intersectEllipse(const Point& O,
				const Point& B){
   double cosangleBCXu,angleBCXu;
   double cosangleCOX, angleCOX;
   double cosangleCOB, angleCOB;

   PositionVector o(O);           //the view point on the light beam
                                  //(the pyramid apex)
   PositionVector beam(B);        //the light beam vector
   PositionVector OB = beam - o; //the light beam vector from 
                                    //o to b
   PositionVector c(center);
   PositionVector OC= c - o;
   PositionVector CB=OB-OC;

   if ( (CB.length()*x1u().length()) !=0 )
     cosangleBCXu=Dot(CB,x1u())/(CB.length()*x1u().length());
   else{
     cout <<"1. Check positions for the OB vector "
          << "and the ellipse plane"<<endl;
      return false;
   };
 
   angleBCXu = acos(cosangleBCXu);

   Point X=center+semimajoraxis*cos(angleBCXu)
                +semiminoraxis*sin( angleBCXu);

   PositionVector CX=X-center;
   PositionVector OX=OC+CX;
  
   if ( (OC.length()*OX.length()) !=0 )
     cosangleCOX=Dot(OC,OX)/(OC.length()*OX.length());
   else{
     cout<<"2. Check positions for the OB vector "
	 <<"and the ellipse plane"<<endl;
      return false;
   };
  
   angleCOX=acos(cosangleCOX);

   if ( (OB.length()*OC.length()) !=0 )
     cosangleCOB=Dot(OB,OC)/(OB.length()*OC.length());
   else{
     cout<<"3. Check positions for the OB vector "
	 <<"and the ellipse plane"<<endl;
      return false;
   };
  
   angleCOB=acos(cosangleCOB);

   if (angleCOB <= angleCOX)
    return true;
   else
    return false;

 }
  


}//closing namespace cxxadt

#ifdef ELLIPSE
#include <iostream>
#include <stdlib.h>
using namespace cxxadt;


int main()
{


  Point c1=Point(1,1,1);
  PositionVector n1(2,1,1);
  PositionVector petiole(1,1,1);

  double a1=2;
  double b1=1;

  Ellipse e1(c1,n1,a1,b1);
  //Ellipse e2(petiole, n1, a1,b1);
  
    

  a1=e1.getCenterPoint() || e1.getSemimajorAxisPoint();
  cout<<"distance a1="<<a1<<endl;
  b1=e1.getCenterPoint() || e1.getSemiminorAxisPoint();
  cout<<"distance b1="<<b1<<endl;

  double area1=e1.getArea();
  cout<<"area1="<<area1<<endl;

  e1.setArea(12, Point(1,1,1) );

  double a2=e1.getCenterPoint() || e1.getSemimajorAxisPoint();
  cout<<"distance a2="<<a2<<endl;
  double b2=e1.getCenterPoint() || e1.getSemiminorAxisPoint();
  cout<<"distance b2="<<b2<<endl;

  double area2=e1.getArea();
  cout<<"area2="<<area2<<endl;

  bool intersection;
  
  Point PO1(0,0,3);//this case doesn't cross the ellipse
  Point PB1(0,0,0);
  PositionVector POB1=PB1-PO1;
 
  intersection=e1.intersectEllipse(PO1,PB1);
  if( intersection){
    cout<<"1. vector"<< POB1<<endl;
    cout<<" crosses the ellipse"<<endl;
  }
  else{
    cout<<"1. vector"<< POB1<<endl;
    cout<<" doesn't cross the ellipse"<<endl;
  }

  Point PO2(4,4,4);//this case crosses the ellipse
  Point PB2(0,0,0);
  PositionVector POB2=PB2-PO2;
  intersection=e1.intersectEllipse(PO2,PB2);

  if( intersection){
    cout<<"2. vector"<< POB2<<endl;
    cout<<" crosses the ellipse"<<endl;
  }
  else{
    cout<<"2. vector"<< POB2<<endl;
    cout<<" doesn't cross the ellipse"<<endl;
  }


  exit(0);
}


#endif

  

