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
    leftcorner=p1; rightcorner=p2; apexcorner=p3;
    
  }
  
  Triangle& Triangle::operator=(const Triangle& t)
  {
    leftcorner = t.leftcorner; rightcorner= t.rightcorner; 
    apexcorner = t.apexcorner;
    return *this;
  }

  //member function uses the same logic (add a vector, i.e. Point)
  //as MoveTree in TreeFunctor.h (stl-lignum)
  //This friend function is used by MoveHwTree (through friend Move of BroadLeaf)
  void Triangle::move(const Point& mov) {
    Point tmp = leftcorner + mov;
    leftcorner = tmp;
    tmp = rightcorner + mov;
    rightcorner = tmp;
    tmp = apexcorner + mov;
    apexcorner = tmp;
  }



vector<Point>& Triangle::getVertexVector(vector<Point>& points)const
{
  points.push_back(leftcorner);
  points.push_back(rightcorner);
  points.push_back(apexcorner);
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
 //  other points of triangle, not P  
 //3.calculation the first angle,a angle between the vector OP and OB   
 //4.calculation the second angle,a angle  between the OP and OPc
 //5.compare these angles.
 //The OB vector crosses the triangle 
 //if for every corner of the triangle 
 //the first angle  less than the second angle 
 //

 bool Triangle::intersectShape(const Point& O,
				  const PositionVector& B)const{

   int i,j,k;
   int counter=0;
   double cos1, cos2, angle1, angle2;
   vector<Point> points;
   points=getVertexVector(points);

   Point pt,p2,p3,pc;

   PositionVector o(O);           //the view point on the light beam
                                  //(the pyramid apex)
   PositionVector beam=B;        //the light beam vector
   PositionVector obeam = beam - o; //the light beam vector from 
                                    //o to b
   
   for(i=0; i<3; i++){
    pt=(Point)points[i];  //the arbitrary triangle corner
    PositionVector ptv(pt);                     
    if (i==0){              //for the other of the remaining points 
         j=1; k=2;          //of the triangle(p2 and p3) 
    }
    else{
      j=0;k=3-i;
    };
                           //the other of the remaining points are p2 and p3
    p2=(Point)points[j]; 
    p3=(Point)points[k]; 

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
    }

    if ( (opt.length()*opc.length()) !=0 )
      cos2=Dot(opt,opc)/(opt.length()*opc.length());
    else{
      cout<<"Check positions for the OB vector "<<
            "and points of the triangle"<<endl;
      cos2=0;
    }
    // cos1=Dot(opt.normalize(),obeam.normalize());
    // cos2=Dot(opt.normalize(),opc.normalize());
    // angle1 = acos(cos1);
    // angle2 = acos(cos2);
    if(angle1 < angle2 ){
      counter ++;
    }

   }

   if (counter != 3) 
     return false;
   else 
     return true;
 }

//Rotate apex point around the base of the triangle by alpha
void Triangle::pitch(const double alpha)
{
  PositionVector v1(leftcorner);
  PositionVector v2(rightcorner);
  PositionVector v3(apexcorner);
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
  double s = rightcorner || apexcorner;
  //cosalpha = l/s --> l = s*cosalpha
  double l = s*cosalpha;
  //The point of rotation: the point of triangle height at the base
  PositionVector p1 = v2 + l*base;
  //Rotate the apex round p1
  v3.rotate(Point(p1),base,alpha);
  //reset apex corner
  apexcorner = Point(v3.getX(),v3.getY(),v3.getZ());
}


    //rotate amount angle around axis defined by p0 and dir
void Triangle::rotate(const Point& p0, const PositionVector& dir, RADIAN angle) {

  PositionVector new_point(leftcorner);
  new_point.rotate(p0,dir,angle);
  leftcorner = Point(new_point);

  new_point = PositionVector(rightcorner);
  new_point.rotate(p0,dir,angle);
  rightcorner = Point(new_point);

  new_point = PositionVector(apexcorner);
  new_point.rotate(p0,dir,angle);
  apexcorner = Point(new_point);
}

}//closing namespace cxxadt

//To compile: g++ -DTRIANGLE RMatrix.cc PositionVector.cc Triangle.cc -I../include 
#ifdef TRIANGLEMAIN
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
  


  vector<Point> points;
  points=t1.getVertexVector(points);

  cout<<"----------------------------------------------"<<endl;
  cout << "0.The triangle points are   "<< endl;
    
  for_each(points.begin(),points.end(),printing);   
  
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

  points.clear();
  points=t1.getVertexVector(points);
  
  for_each(points.begin(),points.end(),printing);   

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

  Point lc(-1,0.0);
  Point rc(1,0,0);
  Point ac(0,1,0);
  Triangle t2(lc,rc,ac);

  cout << "Pitching Triangle A " << 180*(-PI_VALUE/2.0)/PI_VALUE << endl;
  cout << "Area before " << t2.getArea()<<endl;
  cout  << t2.getLeftCorner() << t2.getRightCorner() << t2.getApexCorner()<<endl;
  t2.pitch(-PI_VALUE/2.0);
  cout  << t2.getLeftCorner() << t2.getRightCorner() << t2.getApexCorner();
  cout << "Area after " << t2.getArea() <<endl <<endl;
  cout << "Pitching A back" << 180*(PI_VALUE/2.0)/PI_VALUE << endl;
  t2.pitch(PI_VALUE/2.0);
  cout  << t2.getLeftCorner() << t2.getRightCorner() << t2.getApexCorner();
  cout << "Area after " << t2.getArea() <<endl<<endl;;

  Point lc1(-1,0.0);
  Point rc1(1,0,0);
  Point ac1(1,1,0);
  Triangle t3(lc1,rc1,ac1);

  cout << "Pitching triangle B " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t3.getArea() <<endl;
  cout  << t3.getLeftCorner() << t3.getRightCorner() << t3.getApexCorner()<<endl;
  t3.pitch(-PI_VALUE/2.0);
  cout  << t3.getLeftCorner() << t3.getRightCorner() << t3.getApexCorner() ;
  cout << "Area after " << t3.getArea() <<endl <<endl;
  cout << "Pitching B back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t3.pitch(PI_VALUE/2.0);
  cout  << t3.getLeftCorner() << t3.getRightCorner() << t3.getApexCorner() ;
  cout << "Area after " << t3.getArea() <<endl<<endl;

  Point lc2(0,1,0);
  Point rc2(1,0,0);
  Point ac2(1,1,0);
  Triangle t4(lc2,rc2,ac2);

  cout << "Pitching triangle C " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t4.getArea() <<endl;
  cout  << t4.getLeftCorner() << t4.getRightCorner() << t4.getApexCorner()<<endl;
  t4.pitch(-PI_VALUE/2.0);
  cout  << t4.getLeftCorner() << t4.getRightCorner() << t4.getApexCorner() ;
  cout << "Area after " << t4.getArea() <<endl <<endl;
  cout << "Pitching C back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t4.pitch(PI_VALUE/2.0);
  cout  << t4.getLeftCorner() << t4.getRightCorner() << t4.getApexCorner() ;
  cout << "Area after " << t4.getArea() <<endl <<endl;

  Point lc3(-1,1,0);
  Point rc3(1,-1,0);
  Point ac3(2,2,0);
  Triangle t5(lc3,rc3,ac3);
  cout << "Pitching triangle D " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t5.getArea() <<endl;
  cout  << t5.getLeftCorner() << t5.getRightCorner() << t5.getApexCorner()<<endl;
  t5.pitch(-PI_VALUE/2.0);
  cout  << t5.getLeftCorner() << t5.getRightCorner() << t5.getApexCorner() ;
  cout << "Area after " << t5.getArea() <<endl <<endl;
  cout << "Pitching D back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t5.pitch(PI_VALUE/2.0);
  cout  << t5.getLeftCorner() << t5.getRightCorner() << t5.getApexCorner() ;
  cout << "Area after " << t5.getArea() <<endl <<endl;

  Point lc4(-4,2,0);
  Point rc4(-1,-1,0);
  Point ac4(2,2,0);
  Triangle t6(lc4,rc4,ac4);
  cout << "Pitching triangle E " << 180*(-PI_VALUE/2.0)/PI_VALUE<< endl;
  cout << "Area before " << t6.getArea() <<endl;
  cout  << t6.getLeftCorner() << t6.getRightCorner() << t6.getApexCorner()<<endl;
  t6.pitch(-PI_VALUE/2.0);
  cout  << t6.getLeftCorner() << t6.getRightCorner() << t6.getApexCorner() ;
  cout << "Area after " << t6.getArea() <<endl <<endl;
  cout << "Pitching E back " << 180*(PI_VALUE/2.0)/PI_VALUE<< endl;
  t6.pitch(PI_VALUE/2.0);
  cout  << t6.getLeftCorner() << t6.getRightCorner() << t6.getApexCorner() ;
  cout << "Area after " << t6.getArea() <<endl;
  cout << "Dist Apex and Right in E " << (ac4 || rc4) <<endl;

}


#endif



