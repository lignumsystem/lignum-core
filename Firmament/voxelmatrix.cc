#include <stdafx.h>
#include <math.h>
//#include <unistd.h>
//#include <float.h>
//#include <Array3.h>
#include "voxelmatrix.h"
//#include <Vec3.h>
//#include <Array3.h>
#include "voxellattice.h"
#include "interlen.h"




double edge;
int X, Y, Z, X_0, Y_0, Z_0;
Voxel ***matrix;

template <class TS,class BUD>
void doAxis(Axis<TS,BUD>* , Point);




int voxelSizeX;
int voxelSizeY;
int voxelSizeZ;


//----------------------------------------------------
//
// Calculates the distance between two points
//
//----------------------------------------------------

double calcLength(Point startpoint, Point endpoint)
{
  return sqrt(pow((startpoint.getX()-endpoint.getX()),2)+
	      pow((startpoint.getY()-endpoint.getY()),2)+
	      pow((startpoint.getZ()-endpoint.getZ()),2));
}


//----------------------------------------------------
//
// Calculates the voxel coordinates from a given point
//
//----------------------------------------------------
Point calcVoxel(Point point)
{

  Point tmp;

  //
  // edge/2 fixes trees 0,0,0 coordinates in the middle of a voxel
  // z does not need alignment check since it is presumed to be positive
  //

  float xx = point.getX();

  int x, y, z;
  
  x = X_0+point.getX()/edge;
  y = Y_0+point.getY()/edge;
  z = Z_0+point.getZ()/edge;


  tmp = Point(x, y, z);	

  return tmp;
}


//-----------------------------------------------------
//
// Calculates the transmission coefficient (table value)
//
//-----------------------------------------------------

double K(double phi)
{
  double inclination;

  inclination = phi * 180 / PI_VALUE;

  if (inclination <= 9.9)
    return 0.23;
  if (inclination <= 19.9)
    return 0.215;
  if (inclination <= 29.9)
    return 0.2;
  if (inclination <= 39.9)
    return 0.19;
  if (inclination <= 49.9)
    return 0.18;
  if (inclination <= 59.9)
    return 0.172;
  if (inclination <= 69.9)
    return 0.168;
  if (inclination <= 79.9)
    return 0.170;
  if (inclination <= 90)
    return 0.184;
  
  return 0;
}



//----------------------------------------------------
//
// Functions to calculate needed values for the STAR
//
//----------------------------------------------------

double SAc(double phi, double r, double l)
{
  return 2 * l * cos(phi) * r + PI_VALUE * r * r * sin(phi);
}


double S(double phi, double Sf, double Wf, double r, double l)
{
  
	
	if (Sf * Wf == 0)
		return 0;
	if (SAc(phi, r, l) == 0)
		return 0;
	
	return SAc(phi, r, l) * (1 - exp(-K(phi) * Sf * Wf 
				   / SAc(phi, r, l))) / (Sf * Wf);
}


//----------------------------------------------------
//
// Calculates the mean segment and foliageareadensity
//
//----------------------------------------------------

void calculateMeanSegment()
{
  int i, j, k;

  for (i=0;i<X;i++)
    for (j=0;j<Y;j++)
      for (k=0;k<Z;k++) 
	  {
		  //tarkistaako osuuko segmentteja voxeliin		
		  if (matrix[i][j][k].getPartSum() > 0) 
			{
				  matrix[i][j][k].setMeanSegment();
				  matrix[i][j][k].setMeanWoodRadius();
				  matrix[i][j][k].setMeanTotalRadius();
				  
				  
				  float areaden = matrix[i][j][k].getFoliageArea()  / (edge * edge * edge);
				  matrix[i][j][k].setAreaDensity(areaden);

				  
				  // STAR value for the calculation of the transmission
				  //
				  double STARtmp = 0;
				  double r = matrix[i][j][k].getMeanTotalRadius();
				  double l = matrix[i][j][k].getMeanLength();
     			
				  //Sf = shoot->getFoliageCoverage();  
				  double Sf = 28.0;  //tree(get sf...
				  double Wf = matrix[i][j][k].getFoliageArea()/matrix[i][j][k].getPartSum();
				  if (Wf < .0000000001)
					STARtmp = 0.2;     // ~ limit value when Wf < 0
				  else  for (double phi=0;phi<PI_VALUE/2;phi+=PI_VALUE/16) {
					STARtmp += .5 * (S(phi, Sf, Wf, r, l) + S(phi + PI_VALUE/16, Sf, Wf, r, l)) 
					  * cos(phi + PI_VALUE/32) * PI_VALUE/16;
				  }
				  matrix[i][j][k].addSTAR(STARtmp);
	  
			}
      }
}


/******************************************************************************
 * Trying to rewrite traversePath
 */

float linePosition(float p, float v, int voxels)
{
  float t;
  if(v == 0) return FLT_MAX;           // infinitum
  if(v > 0) t = ((float)voxels - p)/v; // check against plane at "voxels",
  if(v < 0) t = (0 - p)/v;             // or chech against plane at 0.
  return t;
}





void newTraversePath(PositionVector direction, double radiation, Point startpoint, Point startvoxel)
{
  // Here's the voxel
  PositionVector vox((int)startvoxel.getX(), (int)startvoxel.getY(), (int)startvoxel.getZ());

  // start point is in the middle of voxel
  PositionVector startp((PositionVector)vox + PositionVector(0.5*edge, 0.5*edge, 0.5*edge)); //*************?????? Lisätty kerroin: edge

  // Now find the end point point on the edge of voxel lattice
  PositionVector t = PositionVector(linePosition(startp.getX(), direction.getX(), X),
									linePosition(startp.getY(), direction.getY(), Y),
									linePosition(startp.getZ(), direction.getZ(), Z));

  

  if(t.getX() > t.getY()) 
	  t = PositionVector(t.getY(), t.getY(), t.getZ());
  if(t.getX() > t.getZ()) 
	  t = PositionVector(t.getZ(), t.getY(), t.getZ());

  PositionVector endp =
    startp + t.getX()*PositionVector(direction.getX(), direction.getY(), direction.getZ());

  float s1 = startp.getX();
  float s2 = startp.getY();
  float s3 = startp.getZ();

  float e1 = endp.getX();
  float e2 = endp.getY();
  float e3 = endp.getZ();
  // Rounding errors may move end point slightly out of "the big cube".
  if(endp.getX() < 0) endp = PositionVector(0			,	endp.getY()	, endp.getZ());
  if(endp.getY() < 0) endp = PositionVector(endp.getX()	,			   0, endp.getZ());
  if(endp.getZ() < 0) endp = PositionVector(endp.getX()	, endp.getY()	,			0);

  if(endp.getX() > X) endp = PositionVector(X			,	endp.getY()	, endp.getZ());
  if(endp.getY() > Y) endp = PositionVector(endp.getX()	,			   Y, endp.getZ());
  if(endp.getZ() > Z) endp = PositionVector(endp.getX()	, endp.getY()	,			Z);

  //give endp and startp in reverse order to prevent escape from voxel lattice
  //due to rounding errors.

  getExtCoeff ec;
  float through = 0.0; 
  through = interExt(ec, edge, endp, startp);

  matrix[(int)vox.getX()][(int)vox.getY()][(int)vox.getZ()].addRadiationSum(radiation*through);
}

//-----------------------------------------------------
//
//  Calculates the light coming to a voxel
//
//-----------------------------------------------------

void calculateLight(Firmament *firm, int x, int y, int z)
{
  matrix[x][y][z].setIncomingRadiation(0);
  matrix[x][y][z].setRadiationSum(0);
  //
  // Initialize the sky
  //
  //Firmament *firm = new Firmament(9, 24); //*****************

  //
  // Get the number of the regions in the sky
  //
  int num_dirs = firm->numberOfRegions();

  vector<double> direction(3);
  double radiationsum;
  int i;

  //
  // Middlepoint of the voxel
  //
  Point *point = new Point((x+.5)*edge, (y+.5)*edge, (z+.5)*edge);
  Point *startvoxel = new Point(x, y, z);

  //
  // Calculate the diffuse radiation
  //
  for (i=0;i<num_dirs;i++) 
  {
	  radiationsum = firm->diffuseRegionRadiationSum(i, direction);
	  newTraversePath(direction, radiationsum, *point, *startvoxel);
  }

  //
  // Calculate the direct radiation
  //
  //radiationsum = firm->directRadiation(direction);
  //traversePath(direction, radiationsum, *point, *startvoxel);

 // delete firm;
  delete point;
  delete startvoxel;
}



