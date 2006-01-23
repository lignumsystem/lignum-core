#include "stdafx.h"
#include <math.h>

#include <VoxelBox.h>
#include <VoxelSpace.h>
#include <Bernoulli.h>

#include <fstream>
#include <iomanip>

extern float cam_x;  //camera position
extern float cam_y;
extern float cam_z;

namespace Lignum {



  // 
  //	Default constructor
  //
  VoxelSpace::VoxelSpace():voxboxes(10,10,10),Xn(10),Yn(10),Zn(10),k_b(0.50)
  {
     sky = NULL;
  }


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
    :corner1(c1),corner2(c2),voxboxes(xn,yn,zn),Xn(xn),Yn(yn),Zn(zn),k_b(0.50)
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
    :corner1(c1),corner2(c2),Xbox(xsize),Ybox(ysize),Zbox(zsize),
     voxboxes(xn,yn,zn),Xn(xn),Yn(yn),Zn(zn),k_b(kb)
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
    {cout<<"nX: "<<nX<<" "<<nY<<" "<<nZ<<endl;
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
  // Converts a global point to local point of the VoxelSpace
  //
  // parametres:
  //	p : global point
  //	return : local point
  //
  Point VoxelSpace::getLocalPoint(const Point& p)const
  {
    return p - corner1;
  }




  //
  // Returns indicates the x-index of the VoxBox including
  // then x-coordinate given as parameter
  //
  int VoxelSpace::getXindex(LGMdouble local_xcoord)const
  {
    return (int)(local_xcoord/Xbox);
  }


  //
  // Returns indicates the y-index of the VoxBox including
  // then y-coordinate given as parameter
  //
  int VoxelSpace::getYindex(LGMdouble local_ycoord)const
  {
    return (int)(local_ycoord/Ybox);
  }


  //
  // Returns indicates the z-index of the VoxBox including
  // then z-coordinate given as parameter
  //
  int VoxelSpace::getZindex(LGMdouble local_zcoord)const
  {
    return (int)(local_zcoord/Zbox);
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
	    vm.x = startx;
	    vm.y = starty;
	    vm.z = startz;
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
  // returns : the route stored in a vector, 
  //           extinction of the objects in the voxels 
  //
  //This getRoute is  as getRoute above but uses  user defined 'p0' as
  //the ray starting point.
  vector<VoxelMovement>& VoxelSpace::getRoute(vector<VoxelMovement> &vec, 
					      const Point& p0,
					      const PositionVector& dir,
					      const ParametricCurve& K)const
					
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

    PositionVector n1(1,0,0);//normal of the front face of the box
    PositionVector n2(0,1,0);//normal of the left face of the box
    PositionVector n3(0,0,1);//normal of the bottom face of the box
    PositionVector n4(-1,0,0);//normal of the back face of the box
    PositionVector n5(0,-1,0);//normal of the right face of the box
    PositionVector n6(0,0,-1);//normal of the top face of the box
    LGMdouble boxx0 = startx*Xbox;//corner coordinates (not indices) of the box 
    LGMdouble boxy0 = starty*Ybox;//global   coordinates:
                                  //e.g. (3.7 div 2)*2 =1*2  =  2, 
                                  //(3.7  div 0.5)*0.5=7*0.5=3.5
    LGMdouble boxz0 = startz*Zbox;
    //origo of the box in global (segment) coordinates, i.e. the point
    //on the front, left and bottom faces of the box
    Point p1(boxx0,boxy0,boxz0);
    //opposite point  to origo  in global (segment)  coordinates, i.e.
    //the point on the back, right and top faces of the box
    Point p2(boxx0+Xbox,boxy0+Ybox,boxz0+Zbox);

    LGMdouble xmove=FLT_MAX;
    LGMdouble ymove=FLT_MAX;
    LGMdouble zmove=FLT_MAX;

    //Calculate  the distances  one has  to  move to  cross voxel  box
    //boundaries in x,y and z directions
    if (dir.getX() != R_EPSILON)
      xmove = fabs(Xbox / dir.getX());
    if (dir.getY() != R_EPSILON)
      ymove = fabs(Ybox / dir.getY());
    if (dir.getZ() != R_EPSILON)
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
      t1 = -(d0.getX() + (-p1.getX()))/(dir.getX());//front face
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
    next_x=next_y=next_z=FLT_MAX;
    if (t1 >=0.0){
      //If the  direction component is  positive, the ray  crosses the
      //box   boundary   in   index*box_size+box_size,  if   direction
      //component  is negative  the ray  crosses the  box  boundary in
      //index*box_size.
      if (fabs(d0.getX()+t1*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t1*dir.getX() - p2.getX()) <= R_EPSILON){
	next_x = t1;
      }
      if (fabs(d0.getY()+t1*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t1*dir.getY() - p2.getY()) <= R_EPSILON){
	next_y = t1;
      }
      if (fabs(d0.getZ()+t1*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t1*dir.getZ() - p2.getZ()) <= R_EPSILON){
	next_z = t1;
      }
    }
    if (t2 >=0.0){
      //If the  direction component is  positive, the ray  crosses the
      //box boundary in index*box_size+box_size, if it is negative the
      //ray crosses the box boundary in index*box_size.
      if (fabs(d0.getX()+t2*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t2*dir.getX() - p2.getX()) <= R_EPSILON){
	next_x = t2;
      }
      if (fabs(d0.getY()+t2*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t2*dir.getY() - p2.getY()) <= R_EPSILON){
	next_y = t2;
      }
      if (fabs(d0.getZ()+t2*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t2*dir.getZ() - p2.getZ()) <= R_EPSILON){
	next_z = t2;
      }
    }
    if (t3 >=0.0){
      if (fabs(d0.getX()+t3*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t3*dir.getX() - p2.getX()) < R_EPSILON){
	next_x = t3;
      }
      if (fabs(d0.getY()+t3*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t3*dir.getY() - p2.getY()) <= R_EPSILON){
	next_y = t3;
      }
      if (fabs(d0.getZ()+t3*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t3*dir.getZ() - p2.getZ()) <= R_EPSILON){
	next_z = t3;
      }
    }
    if (t4 >=0.0){
      if (fabs(d0.getX()+t4*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t4*dir.getX() - p2.getX()) <= R_EPSILON){
	next_x = t4;
      }
      if (fabs(d0.getY()+t4*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t4*dir.getY() - p2.getY()) <= R_EPSILON){
	next_y = t4;
      }
      if (fabs(d0.getZ()+t4*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t4*dir.getZ() - p2.getZ()) <= R_EPSILON){
	next_z = t4;
      }
    }
    if (t5 >=0.0){
      if (fabs(d0.getX()+t5*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t5*dir.getX() - p2.getX()) <= R_EPSILON){
	next_x = t5;
      }
      if (fabs(d0.getY()+t5*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t5*dir.getY() - p2.getY()) <= R_EPSILON){
	next_y = t5;
      }
      if (fabs(d0.getZ()+t5*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t5*dir.getZ() - p2.getZ()) <= R_EPSILON){
	next_z = t5;
      }
    }
    if (t6 >=0.0){
      if (fabs(d0.getX()+t6*dir.getX() - p1.getX()) <= R_EPSILON || 
	  fabs(d0.getX()+t6*dir.getX() - p2.getX()) <= R_EPSILON){
	next_x = t6;
      }
      if (fabs(d0.getY()+t6*dir.getY() - p1.getY()) <= R_EPSILON || 
	  fabs(d0.getY()+t6*dir.getY() - p2.getY()) <= R_EPSILON){
	next_y = t6;
      }
      if (fabs(d0.getZ()+t6*dir.getZ() - p1.getZ()) <= R_EPSILON || 
	  fabs(d0.getZ()+t6*dir.getZ() - p2.getZ()) <= R_EPSILON){
	next_z = t6;
      }
    }

    //At this point  we should have exactly 3  crossings, one for each
    //x,y and z  plane. One of next_x, next_y  and next_z contains the
    //minimum t that the ray can travel in the box

    LGMdouble dist = 0;

    while(startx>=0 && starty>=0 && startz>=0 && startx<Xn &&
	  starty<Yn && startz<Zn)
      {
	VoxelMovement vm;
	vm.x = startx;
	vm.y = starty;
	vm.z = startz;
	//Set foliage area,  needle area + leaf area
	vm.af = voxboxes[vm.x][vm.y][vm.z].getFoliageArea(); 
	//Get extinction caused by objects in the box
        if (dist != 0)
	   vm.tau =  voxboxes[vm.x][vm.y][vm.z].getExtinction(p0,dir,K);
        else
           vm.tau = 1;
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
      }



    return vec;
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
  VoxelBox& VoxelSpace::getVoxelBox(Point p)
  {
    Point localP = p - corner1;
    int Xi = static_cast<int>(localP.getX()/Xbox);
    int Yi = static_cast<int>(localP.getY()/Ybox);
    int Zi = static_cast<int>(localP.getZ()/Zbox);
    
    if (Xi < 0 || Yi < 0 || Zi < 0 || Xi >= Xn || Yi >= Yn || Zi >= Zn){
      throw OutOfVoxelSpaceException(Point(Xi,Yi,Zi),p);
    } 
    return voxboxes[Xi][Yi][Zi]; 
  }


 
 //
  //	for Poplar: The function calculates the Qin and Qabs-values to
  //	every VoxelBox.
  //
  LGMdouble VoxelSpace::calculatePoplarLight(LGMdouble diffuse, LGMdouble structureFlag)
  {
    //ofstream file("calculateVoxelSpace.txt");
    // cout << " VoxelSpace::calculatePoplarLight Begin for poplar: " << endl;
    // cout<<"Xn: "<<Xn<<"Yn: "<<Yn<<"Zn: "<<Zn<<endl;
    updateStar();
    srand(time(NULL));

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    // cout<<"diffuse: "<<diffuse<<" lastdiffuse: "<<lastdiffuse<<endl;

	    int num_dirs = sky->numberOfRegions();
	    if (voxboxes[i1][i2][i3].isEmpty() == false)
	      {//	 cout<<"voxelbox not empty. "<<num_dirs<<endl;
  	      if(structureFlag<=0)
	       {
	         double totaliop=0;
		voxboxes[i1][i2][i3].updateValues();
		for(int i = 0; i < num_dirs; i++)
		  {	
		    vector<double> rad_direction(3);
		    PositionVector big_leaf_normal=voxboxes[i1][i2][i3].getBigLeafNormal();
		    LGMdouble iop = 
		      sky->diffuseRegionRadiationSum(i,rad_direction);
		    
		    PositionVector 
		      radiation_direction(rad_direction[0], rad_direction[1], 
					  rad_direction[2]);		    
		    radiation_direction.normalize();
		    LGMdouble maximum_box_project_area= abs(Xbox*Ybox*radiation_direction.getZ())+abs(Xbox*Zbox*radiation_direction.getY()) + abs(Zbox*Ybox*radiation_direction.getX());
		    // cout <<"iop for diffuse: "<< iop << endl;
                    totaliop+= iop;
		    vector<VoxelMovement> vec;		
		    getRoute(vec, i1, i2, i3, radiation_direction);
		    int size = vec.size();
		    long int seed; // = -rand();
		    int a=-1;
		    int flag=0;
		    if (size>1)
		      {			
                      a=size-2;
		      flag=0;
		      // long int seed= time(NULL);
                      double result;
                      Bernoulli ber(seed);

                      while (a>=0 && flag<2)
			{	
			  	  
			  VoxelMovement v1 = vec[a];
			 
			  LGMdouble leaf_area=voxboxes[v1.x][v1.y][v1.z].getLeafArea();	
			  LGMdouble projected_leaf_area=leaf_area*abs(
				   big_leaf_normal.getX()*radiation_direction.getX()
				   + big_leaf_normal.getY()*radiation_direction.getY()
				   + big_leaf_normal.getZ()*radiation_direction.getZ());
			  projected_leaf_area /= maximum_box_project_area;
			  if(projected_leaf_area>0.5 && projected_leaf_area<=0.8)
			    projected_leaf_area = 0.69*projected_leaf_area +0.155;
			  else if(projected_leaf_area>0.8)
			    projected_leaf_area = projected_leaf_area/
			      (projected_leaf_area+exp(1-2.63*projected_leaf_area));


			  // cout<<"leafArea in previous voxel: "<<leafArea<<endl;
                          double p=min(projected_leaf_area, 1.0);     //0.3 is the size of voxelbox in Bounding box
			  seed=-rand();
			   result=ber(p, seed);
			   //cout<<leaf_area<<" "<<projected_leaf_area<<" p: "<<p<<endl;
  			  if (result>0.5)
			    flag+=1;  
                          a--;
			} //while vec
		      }// if size>1
		    // cout<<"a: "<<a<<endl;
		      if (a==-1 && flag<2)
			{double result;
                          Bernoulli ber(seed);
			  /*  LGMdouble leaf_area=voxboxes[i1][i2][i3].getLeafArea();
			  // cout<<"leafArea in current voxel: "<<leafArea<<endl;
                          double p=min(leaf_area/(0.3*0.3), 1.0); //0.3 is the size of voxelbox in Bounding box   
			  seed=-rand();*/
			  result=1.0;   //  result=ber(p, seed);	  
  			  if (result>0.5)
			     flag+=1;			                          
                          double persent;
			  // cout<<"flag value: "<<flag<<endl;
			  if (flag==1)
			    persent=0.8;
			  else if (flag==2)
			    persent=0.08;
                          else
                            persent=0;			  
                          voxboxes[i1][i2][i3].addRadiation(persent*iop*1200/2055.35);//diffuse/1200 *1200/2055.35	
			  //  cout<<"diffuse radiation added into voxboxes: "<<iop<<endl; 
		        }
			     		     
		  }//num_dirs for diffuse
		voxboxes[i1][i2][i3].setQ_inStdDiff(voxboxes[i1][i2][i3].getQin());
	        // cout <<"total iop for diffuse: "<< totaliop << endl;
	      }
	   
		LGMdouble Qin=voxboxes[i1][i2][i3].getQ_inStdDiff()*diffuse/1200;
		voxboxes[i1][i2][i3].addRadiation(Qin);
		//cout<<diffuse<<" Qin in light cal: "<<voxboxes[i1][i2][i3].getQin()<<endl;
	     

    
		//calculate the light for direct beam
		vector<double> direct_direction(3);
		LGMdouble iop= sky->directRadiation(direct_direction); 
		//cout <<"iop for direct: "<< iop << endl;
                 vector<VoxelMovement> vec;
		  getRoute(vec, i1, i2, i3, direct_direction);
	          int size = vec.size();
		    long int seed; // = -rand();
		    int a=-1;
		    int flag=0;
		    if (size>1)
		      {			
                      a=size-2;
		      flag=0;
		      // long int seed= time(NULL);
                      double result;
                      Bernoulli ber(seed);

                      while (a>=0 && flag<2)
			{	
			  	  
			  VoxelMovement v1 = vec[a];
			 
			  LGMdouble leafArea=0;		      
			  leafArea=voxboxes[v1.x][v1.y][v1.z].getLeafArea(); 	                           
			  
                          double p=min(leafArea/(0.3*0.3), 0.7);  //0.3 is the voxelbox size
			  seed=-rand();
			  result=ber(p, seed);
						 
  			  if (result>0.5)
			    flag+=1;
			  
                          a--;
			}
		      }
		   
		      if (a==-1 && flag<2)
			{double result;
                          Bernoulli ber(seed);
			  LGMdouble leafArea=voxboxes[i1][i2][i3].getLeafArea();
                          double p=min(leafArea/(0.3*0.3), 0.7);    
			  seed=-rand();
			  //result=ber(p, seed);
			  result=1.0;			  
  			  if (result>0.5)
			     flag+=1;
			                          
                          double persent;
			  if (flag==1)
			    persent=0.9;
			  else if (flag==2)
			    persent=0.1;
                          else
                            persent=0;
			  
                           voxboxes[i1][i2][i3].addRadiation(persent*iop);
			   //  cout<<"direct radiation added into voxboxes: "<<persent*iop<<endl; 
		        }

              }             	      
	  }   
    // file.close();
    return 0;
  }

 



  //
  //	The function calculates the Qin and Qabs-values to every VoxelBox.
  //    self_shading determines if the box shades itself or not   
  LGMdouble VoxelSpace::calculateTurbidLight(bool self_shading)
  {
    updateStar();
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
		    vector<VoxelMovement> vec;		
		    getRoute(vec, i1, i2, i3, radiation_direction);
		    int size = vec.size();
		    //other boxes
		    if (size>1){
		      if (i == 4){
			cout << "Rdir " <<  radiation_direction << endl;
		      }
		      for (int a=1; a<size; a++)
			{
			  VoxelMovement v1 = vec[a-1];
			  VoxelMovement v2 = vec[a];			  
			  LGMdouble ext = voxboxes[v1.x][v1.y][v1.z].extinction(v2.l); 
			  if (i==4){
			    cout << v1.x << " " << v1.y << " " << v1.z << " " << v1.l <<endl;
			  }
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

  void VoxelSpace::updateStar()
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
    //debug 
    vector<VoxelObject*>::iterator it;
    for (it = shaded_objects.begin(); it != shaded_objects.end(); it++){
      delete *it;//delete wrapper
    }
    shaded_objects.clear();
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

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++)
	  {
	    if (all){
	      file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
	      file << voxboxes[i1][i2][i3] << endl;
	    }
	    else if (voxboxes[i1][i2][i3].getFoliageMass() > R_EPSILON){
	      file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
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

  //Write Qabs, Qin and foliage mass to a GnuPlot file
  void  VoxelSpace::writeVoxelBoxesToGnuPlotFile(const string& filename, const string& sep)
  {
    ofstream file(filename.c_str());

    for(int i1=0; i1<Xn; i1++)
      for(int i2=0; i2<Yn; i2++)
	for(int i3=0; i3<Zn; i3++){
	    if ( voxboxes[i1][i2][i3].getFoliageMass() > R_EPSILON){
	      file << left << setfill(' ')
		   << setw(4) << i1 << sep 
		   << setw(4) << i2 << sep 
		   << setw(4) << i3 << sep
		   << setw(11) << voxboxes[i1][i2][i3].getCenterPoint().getX() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getCenterPoint().getY() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getCenterPoint().getZ() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getQabs() << sep 
		   << setw(11) << voxboxes[i1][i2][i3].getQin() << sep 
		   << setw(11) << voxboxes[i1][i2][i3].getNeedleMass() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getLeafMass() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getFoliageMass() << sep
	           << setw(11) << voxboxes[i1][i2][i3].getNeedleArea() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getLeafArea() << sep
		   << setw(4)  << voxboxes[i1][i2][i3].getNumSegments() << sep
		   << setw(4)  << voxboxes[i1][i2][i3].getNumLeaves() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getStar() << sep
		   << setw(11) << voxboxes[i1][i2][i3].getStarSum() << sep << endl;
	    }
	}
    file.close();
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


