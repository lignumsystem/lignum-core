#include "stdafx.h"
#include <cmath>
#include <cstdlib>

#include <VoxelBox.h>
#include <VoxelSpace.h>
#include <Bernoulli.h>

#include <fstream>
#include <iterator>
#include <iomanip>

extern float cam_x;  //camera position
extern float cam_y;
extern float cam_z;

//used in sensitivity analysis for calculatePoplarLight
//extern int gradseed;

namespace Lignum {




  //
  // Constructor
  //
  // parametres
  //	corner1 : the corner from the VoxelSpace where x,y and z have their minimum values
  //  corner2 : opposite corner to corner1
  //	xn		: number of VoxBoxescd  in x direction
  //	yn		: number of VoxBoxes in y direction
  //  zn		: number of VoxBoxes in z direction
  //	f		: Firmament
  //
  VoxelSpace::VoxelSpace(Point c1, Point c2, int xn, int yn, int zn, Firmament &f)
    :Xn(xn),Yn(yn),Zn(zn),voxboxes(xn,yn,zn),corner1(c1),corner2(c2),k_b(0.50)
  {
    Xbox = (corner2-corner1).getX()/static_cast<int>(Xn);
    Ybox = (corner2-corner1).getY()/static_cast<int>(Yn);
    Zbox = (corner2-corner1).getZ()/static_cast<int>(Zn);
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox,(LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner);
	  }
    sky = &f;
  }

  //Constructor: 
  //c1, c2: the corner points
  //xsize, ysize, zsize: voxel box size
  //xn, yn, zn: number of voxel boxes (size of the matrix)
  //f: the firmament
  //kb: angle of incidence of a broad leaf (c.f star for coniferous)
  VoxelSpace::VoxelSpace(Point c1, Point c2, 
			 double xsize, double ysize, double zsize,
			 int xn, int yn, int zn, 
			 Firmament &f, LGMdouble kb)
    :Xbox(xsize),Ybox(ysize),Zbox(zsize),
     Xn(xn),Yn(yn),Zn(zn),voxboxes(xn,yn,zn),corner1(c1),corner2(c2),k_b(kb)
  {   
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }
    sky = &f;
  }


  void PrintVoxelObjectLocations(const VoxelSpace& s, const string& fname)
  {
    cout << "PrintVoxelObjectLocations" <<endl;
    ofstream f(fname.c_str());
    for (int i = 0; i < s.Xn; i++){
      for (int j = 0; j < s.Yn; j++){
	for (int k = 0; k < s.Zn; k++){
	  int size = s.voxboxes[i][j][k].getObjects().size();
	  if (size > 0)
	    f << i << " " << j << " " << k << " " << size <<endl;
	}
      }
    }
  }

  void PrintBoxCfData(const VoxelSpace& s, const string& fname, bool empty = false)
  {
    cout << "PrintBoxCfData" <<endl;
    ofstream f(fname.c_str());
    f << "i j k Center_x y z Af Wf BoxVol STAR_mean No_segs" << endl;
    for (int i = 0; i < s.Xn; i++){
      for (int j = 0; j < s.Yn; j++){
	for (int k = 0; k < s.Zn; k++){
	  if(s.voxboxes[i][j][k].getNumSegmentsReal() > 0.0 || empty) {
	  Point c = s.voxboxes[i][j][k].getCenterPoint();
	  LGMdouble b_vol = s.getBoxVolume();
	  f << i << " " << j << " " << k << " " << c.getX() << " " << c.getY()
	    << " " << c.getZ() << " "  << s.voxboxes[i][j][k].getNeedleArea() << " "
	    << s.voxboxes[i][j][k].getNeedleMass() << " " << b_vol << " "
	    <<  s.voxboxes[i][j][k].getStar() << " " << s.voxboxes[i][j][k].getNumSegmentsReal()
	    << endl;
	  }
	}
      }
    }
  }


 //Change number (=input) of VoxelBoxes in x, y, and z-directions. The whole
 //VoxelSpace, that is, the big box from corner1 to corner2 retains
 //its size => size of VoxelBox changes.

  void VoxelSpace::resize(int x, int y, int z) {
    if(x < 1) x = 1;
    if(y < 1) y = 1;
    if(z < 1) z = 1;
    voxboxes.resize(x, y, z);
    Xn = x, Yn = y, Zn = z;

    //Update now the size of VoxelBox
    Xbox = (LGMdouble)Xn*Xbox / (LGMdouble)Xn;
    Ybox = (LGMdouble)Yn*Ybox / (LGMdouble)Yn;
    Zbox = (LGMdouble)Zn*Zbox / (LGMdouble)Zn;

    //The coordinates (=lower left corners) of the VoxelBoxes have to
    //be set and also the Voxelspace
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }

  }

 //Change sizes of VoxelBoxes => number of VoxelBoxes in x, y, and
 //z-direction change, since the the big box from corner1 to corner2
 //retains (approximately) its size (slight change due to change of
 //voxelbox size; corner2 changes). 

  void VoxelSpace::resize(LGMdouble lX, LGMdouble lY, LGMdouble lZ) {
    if(lX < R_EPSILON) lX = 1.0;
    if(lY < R_EPSILON) lY = 1.0;
    if(lZ < R_EPSILON) lZ = 1.0;

    Xn = static_cast<int>((LGMdouble)Xn*Xbox / lX) + 1;
    Yn = static_cast<int>((LGMdouble)Yn*Ybox / lY) + 1;
    Zn = static_cast<int>((LGMdouble)Zn*Zbox / lZ) + 1;

    voxboxes.resize(Xn, Yn, Zn);

    Xbox = lX, Ybox = lY, Zbox = lZ;

    //Update also the other corner. Lover left corner1 = origo,
    //corner2 is the opposite corner.It may have changed slightly.
    corner2 = corner1 + Point((LGMdouble)Xn*Xbox, (LGMdouble)Yn*Ybox,
			      (LGMdouble)Zn*Zbox);


    //The coordinates (=lower left corners) of the VoxelBoxes have to
    //be set and also the Voxelspace
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }

  }


 //Change sizes & numbers of VoxelBoxes => the extent of VoxelSpace
 //changes (i.e. corner2)

    void VoxelSpace::resize(LGMdouble lX, LGMdouble lY, LGMdouble lZ,
			    int nX, int nY, int nZ )
    {
      if(nX < 1) nX = 1;
      if(nY < 1) nY = 1;
      if(nZ < 1) nZ = 1;
      if(lX < R_EPSILON) lX = 1.0;
      if(lY < R_EPSILON) lY = 1.0;
      if(lZ < R_EPSILON) lZ = 1.0;
      
      Xn = nX, Yn = nY, Zn = nZ;
      voxboxes.resize(Xn, Yn, Zn);

      Xbox = lX, Ybox = lY, Zbox = lZ;

      //Update the other corner. Lover left corner1 = origo,
      //corner2 is the opposite corner.It may have changed slightly.
      
      corner2 = corner1 + Point((LGMdouble)Xn*Xbox, (LGMdouble)Yn*Ybox,
			      (LGMdouble)Zn*Zbox);

 
      //The coordinates (=lower left corners) of the VoxelBoxes have to
      //be set and also the Voxelspace
      for(int i1=0; i1<Xn; i1++)
	for(int i2=0; i2<Yn; i2++)
	  for(int i3=0; i3<Zn; i3++)
	    {
	      Point corner = corner1 +
		Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		      (LGMdouble)i3*Zbox); 
	      voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	    }
      
    }

  //Change physical dimensions of voxelspace (i.e. extent, i.e. opposite
  //corners) The number of VoxelBoxes may change, their dimensions
  //remain the same. Contents are lost (because TMatrix3D resize
  //destroys contents). Note that upper right corner of the resized
  //voxelspace is the same as the given corner; it is adjusted to match
  //number of voxboxes.

  void VoxelSpace::resize(const Point lower_left, const Point upper_right)
  {
    corner1 = lower_left;

    Xn = static_cast<int>((upper_right.getX()-lower_left.getX())/Xbox) + 1;
    Yn = static_cast<int>((upper_right.getY()-lower_left.getY())/Ybox) + 1;
    Zn = static_cast<int>((upper_right.getZ()-lower_left.getZ())/Zbox) + 1;

    voxboxes.resize(Xn, Yn, Zn);

    corner2 = Point(corner1.getX()+(LGMdouble)Xn*Xbox, corner1.getY()+(LGMdouble)Yn*Ybox,
		    corner1.getZ()+(LGMdouble)Zn*Zbox);


    //The coordinates (=lower left corners) of the VoxelBoxes have to
    //be set and also the Voxelspace
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point corner = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
	  }
      
  }




  //Move Voxelspace so that its lower left corner is set at corner

  void VoxelSpace::move(const Point corner)
  {
    corner1 = corner;
    
    //Update also the other corner
    corner2 = corner1 + Point((LGMdouble)Xn*Xbox, (LGMdouble)Yn*Ybox,
			      (LGMdouble)Zn*Zbox);
    
    
    //Set also the coordinates (=lower left corners) of the VoxelBoxes
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    Point c = corner1 +
	      Point((LGMdouble)i1*Xbox, (LGMdouble)i2*Ybox,
		    (LGMdouble)i3*Zbox); 
	    voxboxes[i1][i2][i3].setVoxelSpace(this, c); 
	  }
    
  }

  //
  // Returns indicates the x-index of the VoxBox including
  // then x-coordinate given as parameter
  //
  int VoxelSpace::getXindex(LGMdouble local_xcoord)const
  {
    return (int)((local_xcoord-corner1.getX())/Xbox);
   }


  //
  // Returns indicates the y-index of the VoxBox including
  // then y-coordinate given as parameter
  //
  int VoxelSpace::getYindex(LGMdouble local_ycoord)const
  {
     return (int)((local_ycoord-corner1.getY())/Ybox);
  }


  //
  // Returns indicates the z-index of the VoxBox including
  // then z-coordinate given as parameter
  //
  int VoxelSpace::getZindex(LGMdouble local_zcoord)const
  {
   return (int)((local_zcoord-corner1.getZ())/Zbox);
  }



  //
  // The Function calculates the root from start point to the direction given as parameter.
  // The route is stored to a vector
  //
  // Parametres:
  // vec	:	the vector where the route is stored
  // startx : the x-index of the starting VoxelBox
  // starty : the y-index of the starting VoxelBox
  // startz : the z-index of the starting VoxelBox
  // dir	  : direction
  // returns : the route stored in a vector
  //
  //This getRoute assumes that the initial point is at the center of the box. 
  std::vector<VoxelMovement>& VoxelSpace::getRoute(std::vector<VoxelMovement> &vec, int startx, 
						   int starty, int startz, PositionVector dir)const
  {
    dir.normalize();	

    int x_jump = +1;
    int y_jump = +1;
    int z_jump = +1;
	

    if (dir.getX()<0)
      x_jump = -1;
    if (dir.getY()<0)
      y_jump = -1;
    if (dir.getZ()<0)
      z_jump = -1;

    LGMdouble xmove=9999;
    LGMdouble ymove=9999;
    LGMdouble zmove=9999;

    if (dir.getX() != R_EPSILON)
      xmove = fabs(Xbox / dir.getX());

    if (dir.getY() != R_EPSILON)
      ymove = fabs(Ybox / dir.getY());
	
    if (dir.getZ() != R_EPSILON)
      zmove = fabs(Zbox / dir.getZ());

    LGMdouble next_x = xmove / 2.0;
    LGMdouble next_y = ymove / 2.0;
    LGMdouble next_z = zmove / 2.0;

    LGMdouble dist = 0;


    while(startx>=0 && starty>=0 && startz>=0 && startx<Xn &&
	  starty<Yn && startz<Zn)
      {
	VoxelMovement vm;
	vm.x = startx;
	vm.y = starty;
	vm.z = startz;
	if (next_x <= next_y && next_x<= next_z)
	  {
	    startx = startx + x_jump;
	    vm.l = next_x - dist;
	    dist = next_x;
	    next_x = next_x + xmove;
			
	  }
	else if (next_y <= next_x && next_y<= next_z)
	  {
	    starty = starty + y_jump;
	    vm.l = next_y - dist;
	    dist = next_y;
	    next_y = next_y + ymove;
			
	  }
	else if (next_z <= next_y && next_z<= next_x)
	  {
	    startz = startz + z_jump;
	    vm.l = next_z - dist;
	    dist = next_z;
	    next_z = next_z + zmove;
	  }
		
	if (startx>=-1 && starty>=-1 && startz>=-1 && startx<Xn+1 &&
	    starty<Yn+1 && startz<Zn+1)
	  {
	    //vm.x = startx;
	    //vm.y = starty;
	    //vm.z = startz;
	    vec.push_back(vm);
	  }
      }



    return vec;
  }



  //
  // The function  calculates the route  through the voxel  space from
  // the start point  to the direction given as  parameter.  The route
  // is stored into a vector
  //
  // Parametres:
  // vec:     the vector where the route is stored
  // p0:      the start position of the ray (e.g. segment midpoint)
  // dir:     direction of the light beam, NOTE: |dir| == 1 (!!!!)
  // K:       extinction 
  // pairwise: if true calcuate the extinction using pairwise comparison 
  //           to voxel objects, if false calculate only the path lengths 
  //           in voxels  
  // returns : the route stored in a vector, 
  //           extinction of the objects in the voxels 
  //
  //This getRoute is  as getRoute above but uses  user defined 'p0' as
  //the ray starting point.
  vector<VoxelMovement>& VoxelSpace::getRoute(vector<VoxelMovement> &vec, 
					      const Point& p0,
					      const PositionVector& dir,
					      const ParametricCurve& K,
					      bool pairwise)const
					
  { 
    PositionVector d0(p0);

    int x_jump = +1;
    int y_jump = +1;
    int z_jump = +1;
	
    //The x,y,z indices of the box the point belongs to 
    int startx = getXindex(p0.getX());
    int starty = getYindex(p0.getY());
    int startz = getZindex(p0.getZ());

    if (dir.getX()<0)
      x_jump = -1;
    if (dir.getY()<0)
      y_jump = -1;
    if (dir.getZ()<0)
      z_jump = -1;
    //Normals to faces of the box
    //PositionVector n1(1,0,0);//normal of the front face of the box
    //PositionVector n2(0,1,0);//normal of the left face of the box
    //PositionVector n3(0,0,1);//normal of the bottom face of the box
    //PositionVector n4(-1,0,0);//normal of the back face of the box
    //PositionVector n5(0,-1,0);//normal of the right face of the box
    //PositionVector n6(0,0,-1);//normal of the top face of the box
//    LGMdouble boxx0 = startx*Xbox;//corner coordinates (not indices) of the box
  //  LGMdouble boxy0 = starty*Ybox;//global   coordinates:
                                  //e.g. (3.7 div 2)*2 =1*2  =  2, 
                                  //(3.7  div 0.5)*0.5=7*0.5=3.5
//    LGMdouble boxz0 = startz*Zbox;
    //origo of the box in global (segment) coordinates, i.e. the point
    //on the front, left and bottom faces of the box
//    Point p1(boxx0,boxy0,boxz0);
    Point p1 = voxboxes[startx][starty][startz].getCornerPoint();
    //opposite point  to origo  in global (segment)  coordinates, i.e.
    //the point on the back, right and top faces of the box
//    Point p2(boxx0+Xbox,boxy0+Ybox,boxz0+Zbox);
    Point p2(p1.getX()+Xbox,p1.getY()+Ybox,p1.getZ()+Zbox);
    LGMdouble xmove=R_HUGE;
    LGMdouble ymove=R_HUGE;
    LGMdouble zmove=R_HUGE;

    //Calculate  the distances  one has  to  move to  cross voxel  box
    //boundaries in x,y and z directions
    if (fabs(dir.getX()) > R_EPSILON)
      xmove = fabs(Xbox / dir.getX());
    if (fabs(dir.getY()) > R_EPSILON)
      ymove = fabs(Ybox / dir.getY());
    if (fabs(dir.getZ()) > R_EPSILON)
      zmove = fabs(Zbox / dir.getZ());

    //Initialize: calculate the distances light beam can travel before
    //crossing the box in x,y and z directions. This is the problem of
    //deciding  if  a  ray  intersects  with  a  plane.   The  ray  is
    //represented as r0+t*r1, where r0 is the starting point and r1 is
    //the direction (unit  vector) of the ray. 't'  is the distance to
    //the plane. The plane is  represented as Ax+By+Cz+D=0, where A, B
    //and C  is the  normal to the  plane (unit  vector) and D  is the
    //(shortest)  distance of  the plane  to  origo. At  the point  of
    //intersection   the    ray   satisfies   the    plane   equation:
    //A*(r0.x+t*r1.x)+B*(r0.y+t*r1.y)+C*(r0.z+t*r1.z)+D=0   Solve  the
    //equation for t:
    //t=-(A*r0.x+B*r0.y+C*r0.z+D)/(A*r1.x+B*r1.y+C*r1.z) Note the sign
    //of  D; it is  a positive  number in  Ax+By+Cz=D and  negative in
    //Ax+By+Cz+D=0. Note also that the  normals are simple and we know
    //the D, so the equation for t simplifies quite a lot.
    double t1,t2,t3,t4,t5,t6;
    t1=t2=t3=t4=t5=t6=-1.0;//initialize to negative (i.e. no  intersection)
    if (fabs(dir.getX()) > R_EPSILON){
      //A=1,B=C=0,D=-p1.getX()
      t1 = -(d0.getX() + (-p1.getX()))/(dir.getX());//front face
      //A=1,B=C=0,D=-p2.getX()
      t4 = -(d0.getX() + (-p2.getX()))/(dir.getX());//back face
    }
    if (fabs(dir.getY()) > R_EPSILON){
      t2 = -(d0.getY() + (-p1.getY()))/(dir.getY());//left face
      t5 = -(d0.getY() + (-p2.getY()))/(dir.getY());//right face
    }
    if  (fabs(dir.getZ()) > R_EPSILON){
      t3 = -(d0.getZ() + (-p1.getZ()))/(dir.getZ());//bottom face
      t6 = -(d0.getZ() + (-p2.getZ()))/(dir.getZ());//top face
    }
    //For  each t>=0  check in  which direction  (x, y  or z)  the box
    //boundary was crossed.   (If t < 0 the plane  was in the opposite
    //direction). Set  it as  the value of  next_[x,y,z]. That  is the
    //distance the ray can travel  before crossing the box boundary in
    //x,y and z direction.  The "Fast voxel space traversal algorithm"
    //then in its incremental  phase calculates the total distance the
    //ray traverses in the boxes.
    double next_x,next_y,next_z;
    next_x=next_y=next_z=R_HUGE;
    if (t1 >=0.0){
      //If the  direction component is  positive, the ray  crosses the
      //box   boundary   in   index*box_size+box_size,  if   direction
      //component  is negative  the ray  crosses the  box  boundary in
      //index*box_size.
      if (fabs(d0.getX()+t1*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t1*dir.getX() - p2.getX()) <= R_EPSILON){
	//Check the special case: X does have a direction
	if (fabs(dir.getX()) > R_EPSILON)
	  next_x = t1;
      }
      if (fabs(d0.getY()+t1*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t1*dir.getY() - p2.getY()) <= R_EPSILON){
	//Check the special case: Y does have a direction
	if (fabs(dir.getY()) > R_EPSILON)
	  next_y = t1;
      }
      if (fabs(d0.getZ()+t1*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t1*dir.getZ() - p2.getZ()) <= R_EPSILON){
	//Check the special case: Z does have a direction
	if (fabs(dir.getZ()) > R_EPSILON)
	  next_z = t1;
      }
    }
    //The same for t2-->t6
    if (t2 >=0.0){
      if (fabs(d0.getX()+t2*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t2*dir.getX() - p2.getX()) <= R_EPSILON){
	if (fabs(dir.getX()) > R_EPSILON)
	  next_x = t2;
      }
      if (fabs(d0.getY()+t2*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t2*dir.getY() - p2.getY()) <= R_EPSILON){
	if (fabs(dir.getY()) > R_EPSILON)
	  next_y = t2;
      }
      if (fabs(d0.getZ()+t2*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t2*dir.getZ() - p2.getZ()) <= R_EPSILON){
	if (fabs(dir.getZ()) > R_EPSILON)
	  next_z = t2;
      }
    }
    if (t3 >=0.0){
      if (fabs(d0.getX()+t3*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t3*dir.getX() - p2.getX()) < R_EPSILON){
	if (fabs(dir.getX()) > R_EPSILON)
	  next_x = t3;
      }
      if (fabs(d0.getY()+t3*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t3*dir.getY() - p2.getY()) <= R_EPSILON){
	if (fabs(dir.getY()) > R_EPSILON)
	  next_y = t3;
      }
      if (fabs(d0.getZ()+t3*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t3*dir.getZ() - p2.getZ()) <= R_EPSILON){
	if (fabs(dir.getZ()) > R_EPSILON)
	  next_z = t3;
      }
    }
    if (t4 >=0.0){
      if (fabs(d0.getX()+t4*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t4*dir.getX() - p2.getX()) <= R_EPSILON){
	if (fabs(dir.getX()) > R_EPSILON)
	  next_x = t4;
      }
      if (fabs(d0.getY()+t4*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t4*dir.getY() - p2.getY()) <= R_EPSILON){
	if (fabs(dir.getY()) > R_EPSILON)
	  next_y = t4;
      }
      if (fabs(d0.getZ()+t4*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t4*dir.getZ() - p2.getZ()) <= R_EPSILON){
	if (fabs(dir.getZ()) > R_EPSILON)
	  next_z = t4;
      }
    }
    if (t5 >=0.0){
      if (fabs(d0.getX()+t5*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t5*dir.getX() - p2.getX()) <= R_EPSILON){
	if (fabs(dir.getX()) > R_EPSILON)
	  next_x = t5;
      }
      if (fabs(d0.getY()+t5*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t5*dir.getY() - p2.getY()) <= R_EPSILON){
	if (fabs(dir.getY()) > R_EPSILON)
	  next_y = t5;
      }
      if (fabs(d0.getZ()+t5*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t5*dir.getZ() - p2.getZ()) <= R_EPSILON){
	if (fabs(dir.getZ()) > R_EPSILON)
	  next_z = t5;
      }
    }
    if (t6 >=0.0){
      if (fabs(d0.getX()+t6*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t6*dir.getX() - p2.getX()) <= R_EPSILON){
	if (fabs(dir.getX()) > R_EPSILON)
	  next_x = t6;
      }
      if (fabs(d0.getY()+t6*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t6*dir.getY() - p2.getY()) <= R_EPSILON){
	if (fabs(dir.getY()) > R_EPSILON)
	  next_y = t6;
      }
      if (fabs(d0.getZ()+t6*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t6*dir.getZ() - p2.getZ()) <= R_EPSILON){
	if (fabs(dir.getZ()) > R_EPSILON)
	  next_z = t6;
      }
    }

    //At this point  we should have exactly 3  crossings, one for each
    //x,y and  z plane. The  special cases are  when some of x,y  or z
    //directions are 0.  But these  special cases should be taken care
    //above before the next_[x,y,z] are initialized. If some direction
    //is  not possible,  next_[x,y,z]  is FLT_MAX.   Otherwise one  of
    //next_x, next_y  and next_z contains  the minimum t that  the ray
    //can travel in the box 
    
    // cout << "T: " << t1 << " "  << t2 << " " << t3 << " " <<  t4 << " " << t5  //!!!!!!!!!!!!!!!!!!!!!!!!
    //  << " " << t6 <<endl;
    LGMdouble dist = 0.0;
    //cout << "P: " << p0 << dir <<endl;
    while(startx>=0 && starty>=0 && startz>=0 && startx<Xn &&
	  starty<Yn && startz<Zn)
      {
	VoxelMovement vm;
	vm.x = startx;
	vm.y = starty;
	vm.z = startz;

	vm.STAR_mean = voxboxes[vm.x][vm.y][vm.z].getStar();
	vm.n_segs_real = voxboxes[vm.x][vm.y][vm.z].getNumSegmentsReal();

	//	cout << "index: " << vm.x << " " << vm.y << " " << vm.z << endl;  //!!!!!!!!!!!!!!!!!!!!!!
	//	cout << "Next: " << next_x << " " << next_y << " " << next_z << endl;
       
	vm.tau = 1.0;//Initalize tau to 1 so we do not exit with DiffuseVoxelSpaceRadiation
	//Set foliage area,  needle area + leaf area
	vm.af = voxboxes[vm.x][vm.y][vm.z].getFoliageArea(); 
	//Get extinction  caused by objects  in the box Avoid  the box
	//where the shaded segment is cout << vm.x << " " << vm.y << "
	//" << vm.z << " " <<endl << next_x << " " << next_y << " " <<
	//next_z  << "  "  << dist  <<  endl; If  the  user wants  the

	//In pairwise comparison  we need to go through  the vector of
	//voxel objects in each box. Otherwise the lengths of the beam
	//paths in voxels is enough
	if (pairwise == true){
	  vm.tau =  voxboxes[vm.x][vm.y][vm.z].getExtinction(p0,dir,K);
	}
	if (next_x <= next_y && next_x<= next_z)
	  {
	    startx = startx + x_jump;
	    vm.l = next_x - dist;
	    dist = next_x;
	    next_x = next_x + xmove;
	  }
	else if (next_y <= next_x && next_y<= next_z)
	  {
	    starty = starty + y_jump;
	    vm.l = next_y - dist;
	    dist = next_y;
	    next_y = next_y + ymove;			
	  }
	else if (next_z <= next_y && next_z<= next_x)
	  {
	    startz = startz + z_jump;
	    vm.l = next_z - dist;
	    dist = next_z;
	    next_z = next_z + zmove;
	  }
		
	if (startx>=-1 && starty>=-1 && startz>=-1 && startx<Xn+1 &&
	    starty<Yn+1 && startz<Zn+1)
	  {
	    vec.push_back(vm);
	  }
	//break the voxel traversal if wood hit
	if (vm.tau == 0.0 && !pairwise){
	  cout << "vm.tau should not be 0 in DiffuseVoxelSpace Radiation " << vm.tau <<endl;;
	  return vec;
	}
      }
    return vec;
  }

  //Return the extinction caused by the border stand
  //Input: p0   start point of the light beam
  //       dir  direction of the light beam, |dir| == 1 (!!!)
  //Calculate the  point where  the light beam  exits the  voxel space
  //(there  must be  one). NearByShading  then returns  the extinction
  //coeffcient
  double VoxelSpace::getBorderStandExtinction(const Point& p0, const PositionVector& dir)const
  {
    //Start point of the light beam
    PositionVector d0(p0);
    //Normals to the faces of the voxel space
    //PositionVector n1(1,0,0);//normal of the front face of the voxel space
    //PositionVector n2(0,1,0);//normal of the left face of the voxel space
    //PositionVector n3(0,0,1);//normal of the bottom face of the voxel space
    //PositionVector n4(-1,0,0);//normal of the back face of the voxel space
    //PositionVector n5(0,-1,0);//normal of the right face of the voxel space
    //PositionVector n6(0,0,-1);//normal of the top face of the voxel space
    //Origo  of  the  voxel  space in  global  (segment)  coordinates,
    //i.e. the point on the front,  left and bottom faces of the voxel
    //space
    Point p1(corner1);
    //opposite point  to origo  in global (segment)  coordinates, i.e.
    //the point on the back, right and top faces of the voxel space
    Point p2(corner2);
    //Calculate the  distances light  beam can travel  before crossing
    //the voxel space in x,y and  z directions. This is the problem of
    //deciding  if  a  ray  intersects  with  a  plane.   The  ray  is
    //represented as d0+t*dir, where d0  is the starting point and dir
    //is the direction  (unit vector) of the ray.  't' is the distance
    //to the plane. The plane is represented as Ax+By+Cz+D=0, where A,
    //B and C  is the normal to  the plane (unit vector) and  D is the
    //(shortest)  distance of  the plane  to  origo. At  the point  of
    //intersection   the    ray   satisfies   the    plane   equation:
    //A*(d0.x+t*dir.x)+B*(d0.y+t*dir.y)+C*(d0z+t*dir.z)+D=0  Solve the
    //equation for t:
    //t=-(A*d0.x+B*d0.y+C*d0.z+D)/(A*dir.x+B*dir.y+C*dir.z)  Note  the
    //sign of D; it is a positive number in Ax+By+Cz=D and negative in
    //Ax+By+Cz+D=0. Note also that the  normals are simple and we know
    //the D, so the equation for t simplifies quite a lot.
    double t1,t2,t3,t4,t5,t6;
    t1=t2=t3=t4=t5=t6=-1.0;//initialize to negative (i.e. no  intersection)
    if (fabs(dir.getX()) > R_EPSILON){
      //A=1,B=C=0,D=-corner1.X 
      t1 = -(d0.getX() + (-p1.getX()))/(dir.getX());//front face
      //A=1,B=C=0,D=-corner2.X
      t4 = -(d0.getX() + (-p2.getX()))/(dir.getX());//back face
    }
    if (fabs(dir.getY()) > R_EPSILON){
      t2 = -(d0.getY() + (-p1.getY()))/(dir.getY());//left face
      t5 = -(d0.getY() + (-p2.getY()))/(dir.getY());//right face
    }
    if  (fabs(dir.getZ()) > R_EPSILON){
      t3 = -(d0.getZ() + (-p1.getZ()))/(dir.getZ());//bottom face
      t6 = -(d0.getZ() + (-p2.getZ()))/(dir.getZ());//top face
    }
    vector<double> v(6,0.0);
    v[0] = t1; v[1] = t2; v[2] = t3; v[3] = t4; 
    v[4] = t5; v[5] = t6;
    //Sort in ascending order
    sort(v.begin(),v.end());
    //Take  the first nonnegative  t, i.e.  the shortest  distance the
    //beam can travel in the voxel space before crossing some wall
    vector<double>::iterator it = find_if(v.begin(),v.end(),
					  bind2nd(greater_equal<double>(),0.0));
    double tdist = R_HUGE;
    if (it == v.end()){
      cerr << "No Exit point from voxel space (All t < 0). Error!!!" << endl;
      cerr << "Start point " << d0 <<endl;
      cerr << "Beam direction " << dir <<endl;
      cerr << "t1,....,t6 " << flush;
      copy(v.begin(),v.end(),ostream_iterator<double>(cerr," "));
      cerr << endl;
    }
    else{
      tdist = *it;
    }
    //The exit point from the voxel space
    PositionVector exit = d0+tdist*dir;
    double tau = NearbyShading(Point(exit),dir,
			       GetValue(forest_descriptor,LGAH),
			       GetValue(forest_descriptor,LGAcbase),
			       GetValue(forest_descriptor,LGALAIc),
			       GetValue(forest_descriptor,LGALAIb));
    return tau;
  }
    
  //
  // A function used to fill all the VoxBoxes with a initial
  // value
  //
  void VoxelSpace::fillVoxelBoxes(M2 needleA, M2 leafA)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    voxboxes[i1][i2][i3].setArea(needleA,leafA);
	  }
  }

  //
  // A function used to fill all the VoxBoxes with a initial
  // value downwards 
  //
  void VoxelSpace::fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (i3 >= beginZ && i3 <= endZ){
	      voxboxes[i1][i2][i3].setArea(inivalue,inivalue);
	    }
	    else
	      voxboxes[i1][i2][i3].setArea(0,0);
	  }
  }


    
  void VoxelSpace::fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf,
					     LGMdouble Rf, LGMdouble L,
					     int beginZ, int endZ)
  {
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (i3 >= beginZ && i3 <= endZ){
	      voxboxes[i1][i2][i3].addNeedleArea(Sf*Wf);
	      voxboxes[i1][i2][i3].addNeedleMass(Wf);
	      //for-loop runs eight times (says mika).
	      for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
		{
		  //As in DumpSegment
		  voxboxes[i1][i2][i3].addStarSum(voxboxes[i1][i2][i3].
						  S(phi,Sf,Wf,Rf,L)/8.0);
		  voxboxes[i1][i2][i3].updateValues();
		}
	      voxboxes[i1][i2][i3].increaseNumberOfSegments();
	      voxboxes[i1][i2][i3].updateValues();
	    }
	  }
  }

  //
  // Returns the VoxelBox where the global Point p belongs
  //
  VoxelBox& VoxelSpace::getVoxelBox(const Point& p)
  {
    Point localP = p - corner1;
    int Xi = static_cast<int>(localP.getX()/Xbox);
    int Yi = static_cast<int>(localP.getY()/Ybox);
    int Zi = static_cast<int>(localP.getZ()/Zbox);
    if (Xi < 0 || Yi < 0 || Zi < 0 || Xi >= Xn || Yi >= Yn || Zi >= Zn){
      cout << "getVoxelBox for " << p << flush;
      cout << "voxel " << Point(Xi,Yi,Zi) << flush;
      cout << "voxel space " << Point(Xn,Yn,Zn) << flush;
      throw OutOfVoxelSpaceException(Point(Xi,Yi,Zi),p);
    } 

    return voxboxes[Xi][Yi][Zi]; 
  }


  //
  // Returns the indexes of box  where the global Point p belongs
  //
  vector<int> VoxelSpace::getBoxIndexes(const Point& p)
  {
    Point localP = p - corner1;
    int Xi = static_cast<int>(localP.getX()/Xbox);
    int Yi = static_cast<int>(localP.getY()/Ybox);
    int Zi = static_cast<int>(localP.getZ()/Zbox);

    vector<int> vec(3);
    vec[0] = Xi;
    vec[1] = Yi;
    vec[2] = Zi;
    return vec;
  }


  //
  //	for Poplar: The function calculates the Qin and Qabs-values to
  //	every VoxelBox.
  //
  LGMdouble VoxelSpace::calculatePoplarLight(LGMdouble diffuse, LGMdouble structureFlag)      
  {
    //intialize the sequence with some negative number
    int bernoulli_seed = -1;//gradseed;//-1;
    //produce the next number from sequence
    int bernoulli_sequence = 1;
    Bernoulli ber(bernoulli_seed);
    updateBoxValues();
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    int num_dirs = sky->numberOfRegions();
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		//Calculate diffuse light only once during the short time step model
	        if(structureFlag<=0)
		  {
		    voxboxes[i1][i2][i3].updateValues();
		    for(int i = 0; i < num_dirs; i++)
		      {	
			vector<double> rad_direction(3);
			LGMdouble iop = 
			  sky->diffuseRegionRadiationSum(i,rad_direction);
			PositionVector rd(rad_direction[0], rad_direction[1], rad_direction[2]);		    
			rd.normalize();
			LGMdouble maximum_box_project_area= fabs(Xbox*Ybox*rd.getZ())+fabs(Xbox*Zbox*rd.getY())+ fabs(Zbox*Ybox*rd.getX());
			vector<VoxelMovement> vec;		
			getRoute(vec, i1, i2, i3, rd);
			//Trace the  path from one  sector towards the
			//tree (getRoute follows the light beam from a
			//leaf towards a sector)
			int hits=0;

			//stop conition i > 0 means no self shading
			for (int i = vec.size()-1; i > 0; i--){ 
			  VoxelMovement& vm = vec[i];
			  //cout << "VM " << i << " x " << vm.x << " y " << vm.y << " z "  << vm.z << endl;
			  //cout << "Xn " << Xn << " Yn " << Yn << " Zn " << Zn << endl; 
			  LGMdouble leaf_area = voxboxes[vm.x][vm.y][vm.z].getLeafArea();
			  PositionVector big_leaf_normal=voxboxes[vm.x][vm.y][vm.z].getBigLeafNormal();
			  LGMdouble projected_leaf_area=leaf_area*fabs(big_leaf_normal.getX()*rd.getX()
								       + big_leaf_normal.getY()*rd.getY()
								       + big_leaf_normal.getZ()*rd.getZ());
			  double area_ratio = projected_leaf_area/maximum_box_project_area;
			  if (area_ratio>0.2 && area_ratio<=0.8)
			    area_ratio = 0.51*area_ratio +0.1;
			  else if (area_ratio>0.8)
			    area_ratio = 0.7*area_ratio/(area_ratio+exp(1-2.63*area_ratio));
			  //if projected leaf area > maximum_box_project_area then several layers
			  if (area_ratio){
			    //there is foliage (area_ratio > 0), so if
			    //layers == 0 after the cast to int then 1
			    //layer, if  1 then 2 layers, if  2 then 3
			    //layers
			    int layers = static_cast<int>(projected_leaf_area / maximum_box_project_area) + 1; 
			    //probability 'p' to hit one or several layers is determined by area_ratio.
			    double p=min(area_ratio, 1.0);
			    //....comes from the bernoulli distribution
			    double s=ber(p,bernoulli_sequence);
			    //cout <<  "leaf_area " << leaf_area << " area_ratio " << area_ratio 
			    //   << " p " << p << " s " << s << endl;
			    //there was a hit
			    if (s == 1)
			      hits = hits + layers;
			    if (hits == 3)
			      //third hit will extinguish the beam completely
			      break;
			  }
			}//for (int = v.size()-1
			//assume free path
			double percent = 1.0;
			if (hits == 1)
			  //10 percent received by this focal voxel MS: section 2.3.3
			  percent = 10.0/100.0;
			else if (hits == 2)
			  //1 percent received by this focal voxel if two layers of foliage
			  percent = (10.0/100.0)*(10.0/100.0);
			else if (hits > 2)
			  //three layers completely shades the focal voxel
			  percent = 0.0;
			//set the incoming radiation from one sector;
			//cout << "hits " << hits <<  " % " << percent << " iop " << iop <<endl<<endl;
			//if (hits)
			//cout << "Hits " << hits << " % "  << percent << " iop " << iop << " " 
			//     << " Qin " << percent*iop <<endl;
			voxboxes[i1][i2][i3].addRadiation(percent*iop);
		      }//for (int = 0; i < num_dirs; i++)
		  }//if (structureFlag <= 0)
	      }//if (voxboxes[i1][i2][i3].isEmpty() == false)
	    //cout << "Qin diffuse voxel " << i1 << " "  << i2 << " "  << i3 << " Qin " << voxboxes[i1][i2][i3].getQin() <<endl; 

	    //Calculate the light for direct beam, this is exactly the
	    //same as  for diffuse light  but computed each  time step
	    //during the short time step
	    vector<double> direct_direction(3);
	    LGMdouble iop= sky->directRadiation(direct_direction); 
	    PositionVector dr(direct_direction[0],direct_direction[1],direct_direction[2]);
	    dr.normalize();
	    LGMdouble maximum_box_project_area= fabs(Xbox*Ybox*dr.getZ())+fabs(Xbox*Zbox*dr.getY())+ fabs(Zbox*Ybox*dr.getX());
	    vector<VoxelMovement> vec;
	    getRoute(vec, i1, i2, i3,dr);
	    //Trace the  path from one  sector towards the
	    //tree (getRoute follows the light beam from a
	    //leaf towards a sector)
	    int hits=0;
	    //stop condition i > 0 means no self shading
	    for (int i = vec.size()-1; i > 0; i--){ 
	      VoxelMovement vm = vec[i];
	      LGMdouble leaf_area = voxboxes[vm.x][vm.y][vm.z].getLeafArea();
	      PositionVector big_leaf_normal=voxboxes[vm.x][vm.y][vm.z].getBigLeafNormal();
	      LGMdouble projected_leaf_area=leaf_area*fabs(big_leaf_normal.getX()*dr.getX()
							   + big_leaf_normal.getY()*dr.getY()
							   + big_leaf_normal.getZ()*dr.getZ());
	      double area_ratio = projected_leaf_area/maximum_box_project_area;
	      if (area_ratio>0.2 && area_ratio<=0.8)
		area_ratio = 0.51*area_ratio +0.1;
	      else if (area_ratio>0.8)
		area_ratio = 0.7*area_ratio/(area_ratio+exp(1-2.63*area_ratio));
	      //probability 'p' to hit a leaf....
	      double p=min(area_ratio, 1.0);
	      //....comes from the bernoulli distribution
	      double s=ber(p,bernoulli_sequence);
	      //cout <<  "Qin direct leaf_area " << leaf_area << " area_ratio " << area_ratio 
	      //	   << " p " << p << " s " << s << endl;
	      if (s == 1)
		hits = hits + 1;
	      if (hits == 3)
		break;
	    }//for (int = vec.size()-1
	    //assume free path
	    double percent = 1.0;
	    if (hits == 1)
	      //10 percent received by this focal voxel MS: section 2.3.3
	      percent = 10.0/100.0;
	    else if (hits == 2)
	      //1 percent received by this focal voxel if two layers of foliage
	      percent = (10.0/100.0)*(10.0/100.0);
	    else if (hits > 2) 
	      //three layers completely shades the focal voxel
	      percent = 0.0;
	    //set the incoming direct radiation from one sector;
	    //cout << "hits " << hits <<  " % " << percent << " iop " << iop <<endl<<endl;
	    voxboxes[i1][i2][i3].addRadiation(percent*iop);
	    //cout << "Qin diffuse + direct voxel " << i1 << " "  << i2 << " "  << i3 << " Qin " << voxboxes[i1][i2][i3].getQin() <<endl;
	  }//for (int i3=0; i3 < Zn; i3++)
    return 0;
  }



  //
  //	The function calculates the Qin and Qabs-values to every VoxelBox.
  //    self_shading determines if the box shades itself or not   
  LGMdouble VoxelSpace::calculateTurbidLight(bool self_shading)
  {
    updateBoxValues();
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    int num_dirs = sky->numberOfRegions();
	    //This might  make the voxel  space slow in  execution: if
	    //there  is something  in the  voxel boxes,  the following
	    //loop is executed.
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {		
			
		for(int i = 0; i < num_dirs; i++)
		  {	
		    vector<double> rad_direction(3);
		    LGMdouble iop = sky->
		      diffuseRegionRadiationSum(i,rad_direction);
                 
		    PositionVector
		      radiation_direction(rad_direction[0],
					  rad_direction[1], rad_direction[2]);
		    radiation_direction.normalize();
		    double ext = getBorderStandExtinction(voxboxes[i1][i2][i3].getCenterPoint(),radiation_direction);
		    vector<VoxelMovement> vec;		
		    getRoute(vec, i1, i2, i3, radiation_direction);
		    int size = vec.size();
                                       
		    //other boxes
		    if (size>1){
		      for (int a=1; a<size; a++)
			{
			  VoxelMovement v1 = vec[a-1];
			  VoxelMovement v2 = vec[a];	 		  
			  ext = voxboxes[v1.x][v1.y][v1.z].extinction(v2.l); 
			  iop = iop * ext;
			}
		    }
		    //the self shading 
		    if (size>0 && self_shading)
		      {
			// qin is here the value on the surface of VoxelBox
			LGMdouble qin = iop;

			//The distance the beam travels inside this
			//VoxelBox (from surface to middle)

			LGMdouble inner_length = vec[0].l*2;

			//extinction coefficient on the way through VoxBox
			LGMdouble ext2 = voxboxes[i1][i2][i3].extinction(inner_length);
							
			//radiant intensity of the beam when it comes
			//out of the VoxBox
			LGMdouble qout = iop * ext2;

			//and attenuation inside the VoxBox
			voxboxes[i1][i2][i3].addQabs(qin - qout);
			//Now we calculate only to the mid point; the
			//radiation the VoxBox receives is the one at
			//the mid point.

			LGMdouble ext = voxboxes[i1][i2][i3].extinction(inner_length/2.0);
			iop = iop * ext;
		      }
		    //radiation coming, Qin,  to the VoxBox
		    voxboxes[i1][i2][i3].addRadiation(iop); 
		  }
	      }
	  }   
    return 0;
  }

  void VoxelSpace::updateBoxValues()
  {
    for(int i1=0; i1<Xn; i1++){
      for(int i2=0; i2<Yn; i2++){
	for(int i3=0; i3<Zn; i3++){
	    voxboxes[i1][i2][i3].updateValues(); 
	}
      }
    }
  }

  void VoxelSpace::reset()
  {
    for(int i1=0; i1<Xn; i1++){
      for(int i2=0; i2<Yn; i2++){
	for(int i3=0; i3<Zn; i3++){
	    voxboxes[i1][i2][i3].reset(); 
	}
      }
    }
    //Reset the book keeping of tags for voxel objects
    book_keeper.reset();
    //Reset the descriptive data for forest 
    forest_descriptor.reset();
    sgmnt = 0;
    hitw = 0;
    hitfol = 0;
    nohit = 0;
    hitself = 0;
  } 

  void VoxelSpace::resetQinQabs()
  {
    for(int i1=0; i1<Xn; i1++){
      for(int i2=0; i2<Yn; i2++){
	for(int i3=0; i3<Zn; i3++){
	    voxboxes[i1][i2][i3].resetQinQabs(); 
	}
      }
    }
  } 

  LGMdouble VoxelSpace::getQabs()const
  {
    LGMdouble qabs = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    qabs = qabs + voxboxes[i1][i2][i3].getQabs(); 
	  }
    return qabs;
  }  

  LGMdouble VoxelSpace::getQin()const
  {
    LGMdouble qin = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    qin = qin + voxboxes[i1][i2][i3].getQin(); 
	  }
    return qin;
  }  

  //Return Min and Max foliage mass in the voxel boxes. The first holds
  //the minimum value and the second the maximum value
  pair<double,double> VoxelSpace::getMinMaxNeedleMass()const
  {
    pair<double,double> p(0.0,0.0);

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    double fm = voxboxes[i1][i2][i3].getNeedleMass();
	    //new minimum
	    if (fm < p.first)
	      p.first = fm;
	    //new maximum
	    if (fm > p.second)
	      p.second = fm;
	  }
    return p;
  }


  //Write utilities for VoxelSpace ==================================


  //Write voxel boxes  to file. If 'all' is true  write all boxes else
  //write  only boxes  with foliage.  By  default 'all'  is true  (old
  //beaviour)
  void VoxelSpace::writeVoxBoxesToFile(const string& filename, bool all)
  {
    ofstream file(filename.c_str());
    file << "Vokselien koko " << Xbox << " " << Ybox << " " << Zbox << endl;
    file << " Xn Yn Zn  x y z  Qabs  Q_in  star  needleArea leafArea woodMass woodArea" << endl;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (all){
	      file << i1 << " " << i2 << " " << i3 << " ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	    else if (voxboxes[i1][i2][i3].getFoliageMass() > R_EPSILON){
	      file << i1 << " " << i2 << " " << i3 << " ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	  }
    file.close();

  }	

  void VoxelSpace::writeVoxBoxesToFile(const string& filename, int z)
  {
    ofstream file(filename.c_str());
    file << "Vokselien koko " << Xbox << " " << Ybox << " " << Zbox << endl;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (i3 <= z){
	      file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	  }
    file.close();
    
  }	
  
  void VoxelSpace::writeVoxBoxesToFile2(const string& filename)
  {
    ofstream file(filename.c_str());

    file << "Index "; 
    file << "Qabs " <<  "    Qin " << "     star " << "   needleArea " << " leafarea ";
    file << "  centerpoint " << endl;
	
    LGMdouble sumQabs = 0.0;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		file <<  i1 << ":" << i2 << ":" << i3 << "   ";
		Point p;
		p = voxboxes[i1][i2][i3].getCenterPoint();
					
		file << voxboxes[i1][i2][i3];
		file << "  " << p << " ";
	
		sumQabs += voxboxes[i1][i2][i3].getQabs();
	      }
	  }
    file << endl << endl << "Sum of Qabs " << sumQabs << endl;
  }

  //Write voxels  to a GnuPlot file
  void  VoxelSpace::writeVoxelBoxesToGnuPlotFile(const string& filename, const string& sep)
  {
    ofstream file(filename.c_str());
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++){
	    if ( voxboxes[i1][i2][i3].getFoliageMass() > R_EPSILON){
	      file << left << setfill(' ')
		   << /*1*/setw(4) << i1 << sep 
		   << /*2*/setw(4) << i2 << sep 
		   << /*3*/setw(4) << i3 << sep
		   << /*4*/setw(11) << voxboxes[i1][i2][i3].getCenterPoint().getX() << sep
		   << /*5*/setw(11) << voxboxes[i1][i2][i3].getCenterPoint().getY() << sep
		   << /*6*/setw(11) << voxboxes[i1][i2][i3].getCenterPoint().getZ() << sep
		   << /*7*/setw(11) << voxboxes[i1][i2][i3].getQabs() << sep 
		   << /*8*/setw(11) << voxboxes[i1][i2][i3].getQin() << sep 
		   << /*9*/setw(11) << voxboxes[i1][i2][i3].getNeedleMass() << sep
		   << /*10*/setw(11) << voxboxes[i1][i2][i3].getLeafMass() << sep
		   << /*11*/setw(11) << voxboxes[i1][i2][i3].getFoliageMass() << sep
	           << /*12*/setw(11) << voxboxes[i1][i2][i3].getNeedleArea() << sep
		   << /*13*/setw(11) << voxboxes[i1][i2][i3].getLeafArea() << sep
		   << /*14*/setw(4)  << voxboxes[i1][i2][i3].getNumSegments() << sep
		   << /*15*/setw(4)  << voxboxes[i1][i2][i3].getNumLeaves() << sep
		   << /*16*/setw(11) << voxboxes[i1][i2][i3].getStar() << sep
		   << /*17*/setw(11) << voxboxes[i1][i2][i3].getStarSum() << sep 
		   << /*18*/setw(11) << voxboxes[i1][i2][i3].getQabsMean() << sep
		   << /*19*/setw(11) << voxboxes[i1][i2][i3].getQinMean() << endl;
	    }
	}
    file.close();
  }

  //Calculate mean Qabs and Qin
  void VoxelSpace::calculateMeanQabsQin()
  {
    for(int i1=0; i1<Xn; i1++){
       for(int i2=0; i2<Yn; i2++){
	for(int i3=0; i3<Zn; i3++){
	  if (voxboxes[i1][i2][i3].getNumSegments() > 0){
	    double qabs_mean = 
	      voxboxes[i1][i2][i3].getQabs()/voxboxes[i1][i2][i3].getNumSegments();
	    double qin_mean = 
	      voxboxes[i1][i2][i3].getQin()/voxboxes[i1][i2][i3].getNumSegments();
	    voxboxes[i1][i2][i3].setQabsMean(qabs_mean);
	    voxboxes[i1][i2][i3].setQinMean(qin_mean);
	  }
	}
       }
    }
  }

  //Calculate some key variables of VoxelSpace contetnts and output to
  //console

  void VoxelSpace::writeVoxelSpaceContents() {

    LGMdouble laSum = 0.0, naSum = 0.0, lmSum = 0.0, nmSum = 0.0;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    laSum += voxboxes[i1][i2][i3].getLeafArea();
	    naSum += voxboxes[i1][i2][i3].getNeedleArea();
	    lmSum += voxboxes[i1][i2][i3].getLeafMass();
	    nmSum += voxboxes[i1][i2][i3].getNeedleMass();
	    }

    cout << endl;
    cout << " Foliage contents of Voxelspace (m2 and kg C):" << endl;
    cout << " Needle area: " << naSum << "  Needle mass: " << nmSum
	 << " Leaf area: " << laSum << "  Leaf mass: " << lmSum << endl;
  }



  // This sums up needle mass + leaf mass

  LGMdouble VoxelSpace::getFoliageMass(void)
  {
    LGMdouble ret = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    ret += voxboxes[i1][i2][i3].getFoliageMass();
	  }
    return ret;
  }

  LGMdouble VoxelSpace::getNeedleArea(void)
  {
    LGMdouble ret = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    ret += voxboxes[i1][i2][i3].getNeedleArea();
	  }
    return ret;
  }
  LGMdouble VoxelSpace::getLeafArea(void)
  {
    LGMdouble ret = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    ret += voxboxes[i1][i2][i3].getLeafArea();
	  }
    return ret;
  }
  LGMdouble VoxelSpace::getFoliageArea(void)
  {
    LGMdouble ret = 0.0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    ret += voxboxes[i1][i2][i3].getFoliageArea();
	  }
    return ret;
  }


  int VoxelSpace::getNumberOfFilledBoxes()const
  {
    int count = 0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		count++;
	      }
	  }
    return count;
  }

  int VoxelSpace::getNumberOfTreeSegments()const
  {
    int count=0;
    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		count += voxboxes[i1][i2][i3].getNumSegments();
	      }
	  }
    return count;
  }


  void VoxelSpace::writeStarMean()
  {
    for(int i1=0; i1<Xn; i1++){
      for(int i2=0; i2<Yn; i2++){
	for(int i3=0; i3<Zn; i3++){
	  if(voxboxes[i1][i2][i3].getNumSegments() > 0){
	    LGMdouble sm = 0.0;
	    if (voxboxes[i1][i2][i3].getWeight() > 0.0){
	      sm = voxboxes[i1][i2][i3].getStarSum()/voxboxes[i1][i2][i3].getWeight();
	      cerr << "Weighted starm: " << sm << " StarSum: " << voxboxes[i1][i2][i3].getStarSum() 
		   << " WeightsSum: " << voxboxes[i1][i2][i3].getWeight() 
		   << " NumSegments: " << voxboxes[i1][i2][i3].getNumSegments() << endl;
	    }
	    else{
	      sm = voxboxes[i1][i2][i3].getStarSum()/voxboxes[i1][i2][i3].getNumSegments();
	      cerr << "Arithmetic starm: " << sm << " StarSum: " << voxboxes[i1][i2][i3].getStarSum()
		   << " NumSegments: " << voxboxes[i1][i2][i3].getNumSegments() << endl;
	    }

	  }
	}
      }
    }
  }




  double VoxelSpace::getMeanFoliageAreaDensity()
  {
    double meanD = 0.0;
    int nb = 0;
    double vol = Xbox*Ybox*Zbox;

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if(voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		nb++;
		meanD += (voxboxes[i1][i2][i3].getLeafArea()+
			  voxboxes[i1][i2][i3].getNeedleArea())/vol;
	      }
	  }
    if(nb > 0)
      return meanD/(double)nb;
    else
      return 0.0;
  }

  

}  // closing namespace Lignum


