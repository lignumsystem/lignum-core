#include "stdafx.h"
#include "OpenGL.h"

#ifdef MSC_VER
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>
#endif

#include <VoxelSpace.h>
#include <fstream>


extern float cam_x;  //camera position
extern float cam_y;
extern float cam_z;

namespace Lignum {



// 
//	Default constructor
//
VoxelSpace::VoxelSpace()
  :voxboxes(10,10,10)
{
	Xn = 10;
	Yn = 10;
	Zn = 10;


	for (int i1=0; i1<Xn; i1++)
		for (int i2=0; i2<Xn; i2++)
			for (int i3=0; i3<Xn; i3++)
	sky = NULL;
}




//
// Constructor
//
// parametres
//	corner1 : the corner from the VoxelSpace where x,y and z have their minimum values
//  corner2 : opposite corner to corner1
//	xn		: number of VoxBoxes in x direction
//	yn		: number of VoxBoxes in y direction
//  zn		: number of VoxBoxes in z direction
//	f		: Firmament
//
VoxelSpace::VoxelSpace(Point corner1, Point corner2, 
		       int xn, int yn, int zn, Firmament &f)
  :voxboxes(xn,yn,zn)
{
	Xn = xn;
	Yn = yn;
	Zn = zn;

	Xbox = (corner2.getX() - corner1.getX()) / xn;
	Ybox = (corner2.getY() - corner1.getY()) / yn;
	Zbox = (corner2.getZ() - corner1.getZ()) / zn;


	for(int i1=0; i1<Xn; i1++)
		for(int i2=0; i2<Yn; i2++)
			for(int i3=0; i3<Zn; i3++)
			{
				Point corner = corner1 + Point(i1*Xbox, i2*Ybox, i3*Zbox); 
				voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
			}
			
	
	
	sky = &f;
}




// 
// Converts a global point to local point of the VoxelSpace
//
// parametres:
//	p : global point
//	return : local point
//
Point VoxelSpace::getLocalPoint(Point p)
{
	return p - corner1;
}




//
// Returns indicates the x-index of the VoxBox including
// then x-coordinate given as parameter
//
int VoxelSpace::getXindex(LGMdouble local_xcoord)
{
	return (int)(local_xcoord/Xbox);
}


//
// Returns indicates the y-index of the VoxBox including
// then y-coordinate given as parameter
//
int VoxelSpace::getYindex(LGMdouble local_ycoord)
{
	return (int)(local_ycoord/Xbox);
}


//
// Returns indicates the z-index of the VoxBox including
// then z-coordinate given as parameter
//
int VoxelSpace::getZindex(LGMdouble local_zcoord)
{
	return (int)(local_zcoord/Xbox);
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
std::vector<VoxelMovement>& VoxelSpace::getRoute(std::vector<VoxelMovement> &vec, int startx, int starty, int startz, PositionVector dir)
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

	if (dir.getX() != 0);
		xmove = fabs(Xbox / dir.getX());

	if (dir.getY() != 0);
		ymove = fabs(Ybox / dir.getY());
	
	if (dir.getZ() != 0)
		zmove = fabs(Zbox / dir.getZ());

	LGMdouble next_x = xmove / 2;
	LGMdouble next_y = ymove / 2;
	LGMdouble next_z = zmove / 2;

	LGMdouble dist = 0;


	while(startx>=0 && starty>=0 && startz>=0 && startx<Xn && starty<Yn && startz<Zn)
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
		
		
		
		if (startx>=-1 && starty>=-1 && startz>=-1 && startx<Xn+1 && starty<Yn+1 && startz<Zn+1)
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
// A function used to fill all the VoxBoxes with a initial
// value
//
void VoxelSpace::fillVoxelBoxes(LGMdouble inivalue)
{
	for(int i1=0; i1<Xn; i1++)
		for(int i2=0; i2<Yn; i2++)
			for(int i3=0; i3<Yn; i3++)
			{
				voxboxes[i1][i2][i3].setArea(inivalue,inivalue);
			}
}




//
// Returns the VoxelBox where the global Point p belongs
//
VoxelBox& VoxelSpace::getVoxelBox(Point p)
{
	TMatrix3D<VoxelBox> &vb = voxboxes;

	Point localP = p - corner1;

	int Xi = static_cast<int>(localP.getX()/Xbox);
	int Yi = static_cast<int>(localP.getY()/Ybox);
	int Zi = static_cast<int>(localP.getZ()/Zbox);

/*
	assert<Xi>-1);
	assert<Yi>-1);
	assert<Zi>-1);

	assert<Xi<0);
	assert<Yi<0);
	assert<Zi<0);
*/	
	return vb[Xi][Yi][Zi]; 
}





//
//	The function calculates the Qin and Qabs-values to every VoxelBox.
//
LGMdouble VoxelSpace::calculateLight()
{
	ofstream file("calculateVoxelSpace.txt");


	for(int i1=0; i1<Xn; i1++)
		for(int i2=0; i2<Yn; i2++)
			for(int i3=0; i3<Zn; i3++)
			{
				int num_dirs = 1; //sky->numberOfRegions();
				if (voxboxes[i1][i2][i3].isEmpty() == false)
				{
					file << "VoxelBox["<<i1<<"]["<<i2<<"]["<<i3<<"]"<<endl;
					file << "taivaankannen suuntia " << num_dirs << endl;

					for(int i=0; i<num_dirs; i++)
					{
						
						
						std::vector<double> rad_direction(3);
						LGMdouble iop = sky->diffuseRegionRadiationSum(i,rad_direction);
						PositionVector radiation_direction(rad_direction[0], rad_direction[1], rad_direction[2]);
						radiation_direction.normalize();

						file << "suunta "<<i+1<<". Säteily:"<<iop<< endl;
						
						file << "Suunta:"<< radiation_direction << endl;
						file << "Reitti:"<<endl;
						std::vector<VoxelMovement> vec;
									
						getRoute(vec, i1, i2, i3, radiation_direction);
						int size = vec.size();

						file << "Säteily " << iop << endl;
						if (size>1)
							for (int a=1; a<size; a++)
							{
								VoxelMovement v1 = vec[a-1];
								VoxelMovement v2 = vec[a];
								
								iop = iop * voxboxes[v1.x][v1.y][v1.z].extinction(v2.l);
								
								file << v1.x << "  " << v1.y << "  " << v1.z << "   matka:"<< v2.l << endl;	
								file << "Säteily " << iop << endl;	
							}

						if (size>0)
						{
							LGMdouble qin = iop;
							LGMdouble qout = iop * voxboxes[i1][i2][i3].extinction(vec[0].l*2);

							voxboxes[i1][i2][i3].addQabs(qin - qout);

							iop = iop * voxboxes[i1][i2][i3].extinction(vec[0].l);
							file << "oman boksin matka " << vec[0].l << endl;
							file << "Säteily " << iop << endl;
						}


						voxboxes[i1][i2][i3].addRadiation(iop);	//säteily joka tulee..
						file << endl << endl;
					}
				}
			}
			
	file.close();
	return 0;
}



//
//	This function adds a ScotsPine to the VoxelSpace 
//
void VoxelSpace::AddScotspine(Tree<ScotsPineVisual, ScotsBud> &tree)
{
	vecScotspines.push_back(&tree);
}



//
//	This function searches for the minimum BoundingBox where every tree is included in

//
BoundingBox& VoxelSpace::searchDimensions(BoundingBox &bbox)
{
	int size, i;


	//Scotspines
	size = vecScotspines.size();
	for (i = 0; i<size; i++)
	{
		
		FindBoundingBox<ScotsPineVisual, ScotsBud> fbb;	
		bbox = Accumulate(*vecScotspines[i], bbox, fbb);
	}


	LGMdouble scaleOdd = 1.1;
	LGMdouble scaleOdd2 = 0.05;

	LGMdouble dx = (bbox.getMax().getX() - bbox.getMin().getX()) * scaleOdd;
	LGMdouble dy = (bbox.getMax().getY() - bbox.getMin().getY()) * scaleOdd;
	LGMdouble dz = (bbox.getMax().getZ() - bbox.getMin().getZ()) * scaleOdd;

	Xn = (int)(dx / Xbox)+1;
	Yn = (int)(dy / Ybox)+1;
	Zn = (int)(dz / Zbox)+1;
	
	
	corner1 = Point(bbox.getMin().getX()-dx*scaleOdd2,
					bbox.getMin().getY()-dy*scaleOdd2,
					bbox.getMin().getZ()-dz*scaleOdd2); 

	double fx = corner1.getX();
	double fy = corner1.getY();
	double fz = corner1.getZ();



	voxboxes.resize(Xn, Yn, Zn);

	for(int i1=0; i1<Xn; i1++)
		for(int i2=0; i2<Yn; i2++)
			for(int i3=0; i3<Zn; i3++)
			{
				Point corner = corner1 + Point(i1*Xbox, i2*Ybox, i3*Zbox); 
				voxboxes[i1][i2][i3].setVoxelSpace(this, corner); 
			}

	return bbox;
}



//
//	This function dumps every tree included in the VoxelSpace to
//	VoxelBoxes.
//
void VoxelSpace::dumpTrees()
{
	int size, i;


	//Scotspines first
	size = vecScotspines.size();
	for (i = 0; i<size; i++)
	{
		dumpCfTree(*this, *vecScotspines[i]);
	}
}




//
//	This function is called after calculateLight-function. The light values calculated in VoxelBoxes
//	are now tranformed to treesegments.
//
void VoxelSpace::setLightValues()
{
	int size, i;

	//Scotspines
	size = vecScotspines.size();
	for (i = 0; i<size; i++)
	{
		setCfTreeQabs(*this, *vecScotspines[i]);
	}
} 








//
//	Visualizes the VoxelSpace
//
void VoxelSpace::draw()
{
#ifdef _MSC_VER
	int num = 0;
	vector<VisualCube> cubes;
	vector<VisualCube> ordered_cubes;

	for(int i1=0; i1<Xn; i1++)
		for(int i2=0; i2<Yn; i2++)
			for(int i3=0; i3<Zn; i3++)
			{			
				if (voxboxes[i1][i2][i3].isEmpty() == false)
				{
					VisualCube cube;
					Point c1 = voxboxes[i1][i2][i3].getCornerPoint();

					cube.x = c1.getX();
					cube.y = c1.getY();
					cube.z = c1.getZ();

					cube.ready = false;
					cube.areaden = voxboxes[i1][i2][i3].getAreaDen(); 

					Point cpoint;
					voxboxes[i1][i2][i3].getCenterPoint(cpoint); 

					float xx = cpoint.getX();
					float yy = cpoint.getY();
					float zz = cpoint.getZ();

					cube.dist = pow(cam_x-xx, 2) + pow(cam_y-yy, 2) + pow(cam_z-zz, 2); 
				
					cubes.push_back(cube);
					num ++;
				}
			}

	for (int i = 0; i<num; i++)
	{
		int max_dist = -10;
		int mem_num = -1;
		int a = cubes.size();
		for (int ii=0; ii<a; ii++)
		{
			VisualCube c = cubes[ii];
			if (c.ready == false)
			{
				if (c.dist > max_dist)
					mem_num = ii;
			}
		}
		if (mem_num > -1)
		{
			VisualCube &c = cubes[mem_num];
			c.ready = true;
			ordered_cubes.push_back(c);
		}
	}

	glPushMatrix();
					
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glLineWidth(1);
	glColor3f(1,0.2,0.2);

	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(5,0,0);

	glVertex3f(0,0,0);
	glVertex3f(0,5,0);

	glVertex3f(0,0,0);
	glVertex3f(0,0,5);
	glEnd();

	glLineWidth(1);

	int s = ordered_cubes.size();
	for (i = 0; i< s; i++)
	{
		VisualCube cube = cubes[i];
		

		glColor3f(0.2,0.2,1);
				
				
		float half_edgeX = Xbox/2.0;
		float half_edgeY = Ybox/2.0;
		float half_edgeZ = Zbox/2.0;



		//pikkukuution keskipiste
		float xx = cube.x + half_edgeX;
		float yy = cube.y + half_edgeY;
		float zz = cube.z + half_edgeZ;
		

		glBegin(GL_LINE_LOOP);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
				
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();

		
		float shadow_odd = 0.1 + cube.areaden * (0.3 * half_edgeX*half_edgeY*half_edgeZ); 

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0, 0.8, 0.0, shadow_odd);

		glBegin(GL_POLYGON);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glEnd();


		glBegin(GL_POLYGON);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glEnd();



		glBegin(GL_POLYGON);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glEnd();

		glDisable(GL_BLEND);
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glEndList();
#endif
}


void VoxelSpace::writeVoxBoxesToFile(string& filename)
{
	ofstream file(filename.c_str());
	for(int i1=0; i1<Xn; i1++)
		for(int i2=0; i2<Yn; i2++)
			for(int i3=0; i3<Zn; i3++)
			{
				file << "[" << i1 << "," << i2 << "," << i3 << "]   ";
				file << voxboxes[i1][i2][i3];


			}
	file.close();

}	



}  // closing namespace Lignum
