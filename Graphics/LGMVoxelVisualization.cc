#include <stdafx.h>

#include <LGMVoxelVisualization.h>

#include <VoxelSpace.h>
#include <vector>


namespace Lignum
{


  // Function visualizes given VoxelSpace. Background color 
  //is either white or black, depending on the blackBG-valua
  void LGMVoxelVisualization::DrawVoxelSpace(VoxelSpace &space, bool blackBG)
  {
    glEnable(GL_LIGHTING);
    int num = 0;
    vector<VisualCube> cubes;
    vector<VisualCube> ordered_cubes;
    
    pair<double, double> pa = space.getMinMaxNeedleMass();
    double max = pa.second;
    
    if (max == 0) return;
    
    //cout << "koko " << Xn << " " << Yn << " " << Zn << endl;
    for(int i1=0; i1<space.Xn; i1++)
      for(int i2=0; i2<space.Yn; i2++)
	for(int i3=0; i3<space.Zn; i3++)
	  {			
	    if (space.voxboxes[i1][i2][i3].isEmpty() == false)
	      {
		VisualCube cube;
		Point c1 = space.voxboxes[i1][i2][i3].getCornerPoint();
		
		cube.x = c1.getX();
		cube.y = c1.getY();
		cube.z = c1.getZ();
		
		cube.ready = false;
		cube.areaden = space.voxboxes[i1][i2][i3].getAreaDensity(); 
		
		LGMdouble nmass = space.voxboxes[i1][i2][i3].getNeedleMass();
		
		
		
		float half_edgeX = space.Xbox/2.0;
		float half_edgeY = space.Ybox/2.0;
		float half_edgeZ = space.Zbox/2.0;
		
		
		
		//pikkukuution keskipiste
		float xx = cube.x + half_edgeX;
		float yy = cube.y + half_edgeY;
		float zz = cube.z + half_edgeZ;
		
		
		half_edgeX = half_edgeX / 10.0;
		half_edgeY = half_edgeX;
		half_edgeZ = half_edgeX;
		
		//cout << cube.areaden << endl;
		
		
		double green=0.0;
		double red=0.0;
		double blue=0.0;
		if (blackBG)
		  {
		    red = 0.0;
		    blue = 0.0;
		    green = nmass / max; 
		  }
		else
		  {
		    green = 1.0;
		    red = (max-nmass)/max;
		    blue= (max-nmass)/max;
		  }
		
		
		
		
		GLfloat mat_amb[] = { red, green, blue, 1.0 }; 
		GLfloat mat_dif[] = { red, green, blue, 1.0 }; 
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb); 
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
		
		
		
		glBegin(GL_POLYGON);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();
		
		glBegin(GL_POLYGON);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glEnd();
		
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glEnd();
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glEnd();
		
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz-half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz-half_edgeZ);
		glEnd();
		
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(xx-half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy-half_edgeY, zz+half_edgeZ);
		glVertex3f(xx+half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glVertex3f(xx-half_edgeX, yy+half_edgeY, zz+half_edgeZ);
		glEnd();
	      }
	  }
  }
  
}



