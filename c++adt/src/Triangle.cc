//Triangle.cc
//----------------------------------
#include <Triangle.h>

namespace cxxadt{

//Construct a triangle by defining three triangle corners;
//Getting the triangle area
//Construct a triangle by defining the triangle area
//Getting the center of the triangle


  Triangle::Triangle(const Point& p1,const  Point& p2,const Point& p3)
  {
    leftcorner=p1; rightcorner=p2; apexcorner=p3;
    
  }
  
  Triangle& Triangle::operator=(const Triangle& t)
  {
    leftcorner = t.leftcorner; rightcorner= t.rightcorner; 
    apexcorner = t.apexcorner;
    return *this;
  }



vector<Point>& Triangle::getTriangleCorners(vector<Point>& corners)const
{
  corners.push_back(leftcorner);
  corners.push_back(rightcorner);
  corners.push_back(apexcorner);
  return corners;
}


//the center of the triangle according 
// equation Pc=(P1+P2+P3)/3

Point Triangle::getCenterPoint()const 
{                            
  Point center;

  vector<Point> corners;
  corners=getTriangleCorners(corners);

  for(int i=0; i<3; i++){
   center.setX( ( (Point)corners[i] ).getX() /3);
   center.setY( ( (Point)corners[i] ).getY() /3);
   center.setZ( ( (Point)corners[i] ).getZ() /3);
  }
  return center ;
}

//getting the triangle normal vector

PositionVector Triangle::getNormal()const
{

  
  PositionVector p1(leftcorner);
  PositionVector p2(rightcorner);
  PositionVector p3(apexcorner);

 // these vectors are the triangle sides 
 
 PositionVector p12=p1-p2;
 PositionVector p13=p1-p3;
 PositionVector normal= Cross(p12,p13);
 if (normal.length()!= 0)
   normal=normal*(1/normal.length());
 
 return ( normal  );

} 

//set up the triangle center point
//end change the triangle corners
//according the center point 

void  Triangle::setCenterPoint(const Point& center0){
   Point center;
   center.setX(center0.getX());
   center.setY(center0.getY());
   center.setZ(center0.getZ());
   setArea(getArea(),center);
}


//Calculation  the triangle area 
// using equation 
//A=1/2*|((leftcorner,rightcorner)X(leftcorner,apexcorner))|
//where X is  the cross operation between vectors

double Triangle::getArea()const{

  double area;
   
 // These vectors are based on the origin
  
  PositionVector p1(leftcorner);
  PositionVector p2(rightcorner);
  PositionVector p3(apexcorner);

 // these vectors are the triangle sides 
 
 PositionVector p12=p1-p2;
 PositionVector p13=p1-p3;
 
 area=( fabs( Cross(p12,p13).length() ) )/2.0;
 
 return ( area );
 
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
  double areaold, areanew,
         scalcoef; 
   double adbasex, adbasey, adbasez;
  
  areaold=getArea();
  areanew=area; 

  scalcoef=sqrt(areanew/areaold);

  adbasex=getCenterPoint().getX()*(1-scalcoef);
  adbasey=getCenterPoint().getY()*(1-scalcoef);
  adbasez=getCenterPoint().getZ()*(1-scalcoef);





  vector<Point> corners;
  corners=getTriangleCorners(corners);
  Point x,p;

  for(int i=0; i<3; i++){
   p=(Point)corners[i];
   x.setX(p.getX() *scalcoef  + adbasex);
   x.setY(p.getY() *scalcoef  + adbasey);
   x.setZ(p.getZ() *scalcoef  + adbasez);
   switch(i){
   case 0:
     setLeftCorner(x);
     break;
   case 1:
     setRightCorner(x);
     break;
   case 2:
     setApexCorner(x);
     break;
   };
  };

  return getArea();
}

//This case uses the arbitrary base point as the scaling center 

double Triangle::setArea(double area, const Point& base )
{
  double areaold, areanew,
         scalcoef;
  double adbasex, adbasey, adbasez;
  
  areaold=getArea();
  areanew=area; 

  scalcoef=sqrt(areanew/areaold);

  adbasex= base.getX()*(1-scalcoef);
  adbasey= base.getY()*(1-scalcoef);
  adbasez= base.getZ()*(1-scalcoef);




  vector<Point> corners;
  corners=getTriangleCorners(corners);
  Point x,p; 

  for(int i=0; i<3; i++){
   p=(Point)corners[i];
   x.setX(p.getX() *scalcoef  + adbasex);
   x.setY(p.getY() *scalcoef  + adbasey);
   x.setZ(p.getZ() *scalcoef  + adbasez);
   switch(i){
   case 0:
     setLeftCorner(x);
     break;
   case 1:
     setRightCorner(x);
     break;
   case 2:
     setApexCorner(x);
     break;
   default:
     ;
   };
  };
  return getArea();
}
 //This method checks crossing a triangle 
 //with a straight line in space, 
 //given by the O point(O - the first parameter the method) 
 //and direction B(B - the second parameter the method).
 // 
 //Image a pyramid with the triangle in the base
 //and the O point as the apex of the pyramid
 //Image the vector OB, the vector of direction B 
 //as a vector having the points O and B.
 //For every corner P of the triangle
 //doing the following:  
 //1.calculation the vector OP position
 //2.calculation the vector OPc position,
 //  the  vector  crossing the POB plane 
 //  with the T1OT2 plane, where T1 and T2 the 
 //  other corners of triangle, not P  
 //3.calculation the first angle,a angle between the vector OP and OB   
 //4.calculation the second angle,a angle  between the OP and OPc
 //5.compare these angles.
 //The OB vector crosses the triangle 
 //if for every corner of the triangle 
 //the first angle  less than the second angle 
 //

 bool Triangle::intersectShape(const Point& O,
				  const PositionVector& B){

   int i,j,k;
   int counter=0;
   double cos1, cos2, angle1, angle2;
   vector<Point> corners;
   corners=getTriangleCorners(corners);

   Point pt,p2,p3,pc;

   PositionVector o(O);           //the view point on the light beam
                                  //(the pyramid apex)
   PositionVector beam=B;        //the light beam vector
   PositionVector obeam = beam - o; //the light beam vector from 
                                    //o to b
   
   for(i=0; i<3; i++){
    pt=(Point)corners[i];  //the arbitrary triangle corner
    PositionVector ptv(pt);                     
    if (i==0){              //for the other of the remaining corners 
         j=1; k=2;          //of the triangle(p2 and p3) 
    }
    else{
      j=0;k=3-i;
    };
                           //the other of the remaining corners are p2 and p3
    p2=(Point)corners[j]; 
    p3=(Point)corners[k]; 

    PositionVector p2v(p2);
    PositionVector p3v(p3);  
    
    PositionVector op2= p2v - o;
    PositionVector op3= p3v - o;
    PositionVector opt= ptv - o;  

    PositionVector pc=Cross(Cross(opt,obeam),Cross(op2,op3));
    PositionVector opc= pc - o;
    
    if ( (opt.length()*obeam.length())!=0 )
     cos1=Dot(opt,obeam)/(opt.length()*obeam.length());
    else{
      cout<<"Check positions for the OB vector "<<
            "and points of the triangle"<<endl;
      cos1=0;
    };
     

    if ( (opt.length()*opc.length()) !=0 )
      cos2=Dot(opt,opc)/(opt.length()*opc.length());
    else{
      cout<<"Check positions for the OB vector "<<
            "and points of the triangle"<<endl;
      cos2=0;
    };
    
    angle1 = acos(cos1);
    angle2 = acos(cos2);

    if(angle1 < angle2 )
     counter ++;

   }

   if (counter != 3) 
     return false;
   else 
     return true;
 }




}//closing namespace cxxadt

#ifdef TRIANGLE
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
  
  Point p1=Point();
  Point p2=Point(2.0,0.0,0.0);
  Point p3=Point(2.0,4.0,0.0);
  Triangle t1(p1,p2,p3);
  


  vector<Point> corners;
  corners=t1.getTriangleCorners(corners);

  cout<<"----------------------------------------------"<<endl;
  cout << "0.The triangle points are   "<< endl;
    
  for_each(corners.begin(),corners.end(),printing);   
  
  cout << "1.For these points  " << endl;  
  cout << "2.Area is   " << t1.getArea() << endl;
  cout << "3.Center is " << t1.getCenterPoint().getX()
       << endl;
  cout <<"3a. Normal vector is "<<t1.getNormal()
       <<endl<<endl;

  Point base=Point(2.0,0.0,0.0);

  t1.setArea(2.0, base );
  cout << "4.After scaling the triangle  " << endl;

  cout << "5.Area is   " <<     t1.getArea() << endl;
  cout << "6.Center is " <<     t1.getCenterPoint().getX() << endl;

  corners.clear();
  corners=t1.getTriangleCorners(corners);
  
  for_each(corners.begin(),corners.end(),printing);   

  cout<<endl;


  //checking intersection

  cout<<"----------------------------------------------"<<endl;

  cout << "Checking intersection the new triangle" << endl;
  cout << "with the vector of b direction and the o point"<<endl;
  cout<<"----------------------------------------------"<<endl;

  Point o=Point(0.0,0.0,3.0);

  PositionVector b(0,1,3);//not intersection

  //  PositionVector b(1.5,1.5,0.0);//there is  intersection

  
  cout<<"From point O " <<o<< " the beam vector "<<b;
  if (t1.intersectShape(o,b) ) 
    cout<<" crosses the triangle "<<endl<<endl;
  else
    cout<<" does not cross the triangle "<<endl<<endl;


  exit(0);
}


#endif



