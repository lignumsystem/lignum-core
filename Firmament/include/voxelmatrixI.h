
#ifndef VOXELMATRIXI_H
#define VOXELMATRIXI_H


template <class TS,class BUD>
Matrix<TS,BUD>::Matrix(vector<Tree<TS, BUD> *> trees, double voxeledge)
{
	edge = voxeledge;
	int i, j, k;
	int num = trees.size();

	BoundingBox bbox;
	FindBoundingBox<ScotsPineVisual, ScotsBud> fbb;
	Tree<ScotsPineVisual, ScotsBud > *tree;

	for(i=0; i<num; i++)
	  {
		tree = trees[i];
		bbox = Accumulate(*tree, bbox, fbb);
	  }
 
	Point span = bbox.getMax() - bbox.getMin();

	

	Point middlepoint = bbox.getMax() + bbox.getMin();
	middlepoint = Point(middlepoint.getX()/2.0, middlepoint.getY()/2.0, middlepoint.getZ()/2.0);
	
	cout << "keskipiste " << middlepoint << endl;

	float xx,yy,zz;
	X = xx = span.getX() / edge + 1;
	Y = yy = span.getY() / edge + 1;
	Z = zz = span.getZ() / edge + 1;

	
	cout << "span " << span << endl;
	cout << "edge " << edge << endl;

	//Nyt tiedetaan todellinen pikkukuutioiden lukumaara. Lasketaan sivujen pituudet isossa kuutiossa.
	float dx = edge * X;
	float dy = edge * Y;
	float dz = edge * Z;

	cout << "dx dy dz " << dx << " " << dy << " " << dz << endl;

	p1 = Point(middlepoint.getX()-dx/2, middlepoint.getY()-dy/2, middlepoint.getZ()-dz/2);
	p2 = Point(middlepoint.getX()+dx/2, middlepoint.getY()+dy/2, middlepoint.getZ()+dz/2);

	cout << " alakulma " << p1 << endl;
	cout << " ylakulma " << p2 << endl;

	cout << " koko " << X << "  " << Y << "  " << Z << endl;
	matrix = new Voxel**[X];
	for (j=0;j<Y;j++)
		matrix[j] = new Voxel*[Y];
	for (i=0;i<X;i++)
		for(j=0;j<Y;j++)
			matrix[i][j] = new Voxel[Z];

	cout << " viedaan puut " << endl;
	Point base(0,0,0);
	for(i=0; i<num; i++)
	  {
	    tree = trees[i];
	    importTree(tree, base);
	    calculateMeanSegment();
	  }

	cout << "puut viety " << endl;
	//calculateMeanSegment();

	Firmament *firm = &GetFirmament(*trees[0]);
	double partsumsum = 0.0;
	double total_foliage = 0.0;
	for (i=0;i<X;i++)
	  for (j=0;j<Y;j++)
	    for (k=0;k<Z;k++) 
	      {
		calculateLight(firm, i, j, k);
		
		float xx = p1.getX() + edge*(i+0.5); 
		float yy = p1.getY() + edge*(j+0.5);
		float zz = p1.getZ() + edge*(k+0.5);
		

		if (matrix[i][j][k].getSTAR() > 0)
		  {
/* 		    cout << "(" << i << "," << j << "," << k << ")   Koordinaatit: ("  */
/* 			 << xx << "," << yy << "," << zz << ")	incoming: "  */
/* 		       << matrix[i][j][k].getRadiationSum() << "  area density " */
/* 			 << matrix[i][j][k].getAreaDensity()  << " Foliage mass "  */
/* 			 << matrix[i][j][k].getFoliageMass() << */
/* 		      endl; */
		  }
		
		
		partsumsum += matrix[i][j][k].getPartSum();
		total_foliage += matrix[i][j][k].getFoliageMass(); 
	      }
/* 	cout << "Foliage mass in voxelspace " << total_foliage << endl; */
/* 	cout << "pulikoita yhteensa voxelspacessa " << partsumsum << endl << endl; */
}







template <class TS,class BUD>
void Matrix<TS,BUD>::printInfo()
{
	for(int a=0; a<X; a++)
		for(int b=0; b<Y; b++)
			for(int c=0; c<Z; c++)
				printInfo(a,b,c);
}

//-----------------------------------------------------------------
//
// Constructor. Given arguments are tree, matrix dimensions and
// voxel edge lengths.
//
//-----------------------------------------------------------------
template <class TS,class BUD>
Matrix<TS,BUD>::Matrix(Tree<TS,BUD> *tree, double x, double y, double z, double voxeledge)
{
  int i, j, k;                           // Loop counters
  Point *base = new Point(0,0,0);
  edge = voxeledge;

  //
  // Calculate voxel matrixes dimensions
  //
  X = (int)((int)(x / edge)+2) * 2;              // depth
  Y = (int)((int)(y / edge)+2) * 2;              // width
  Z = (int)(z / edge) + 2;              // heigth of the matrix
  X_0 = (int)X/2;
  Y_0 = (int)Y/2;
  Z_0 = (int)0;

	
  

  voxelSizeX = X;
  voxelSizeY = Y;
  voxelSizeZ = Z;
  
 

  // Reserve the memory for the matrix
  //
  matrix = new Voxel**[X];
  for (j=0;j<Y;j++)
    matrix[j] = new Voxel*[Y];
  for (i=0;i<X;i++)
    for(j=0;j<Y;j++)
      matrix[i][j] = new Voxel[Z];

  importTree(tree, *base);
  calculateMeanSegment();

  Firmament *firm = &GetFirmament(*tree);
  ofstream file2("debug_voxel_info.txt");
  double partsumsum = 0.0;
  for (i=0;i<X;i++)
    for (j=0;j<Y;j++)
      for (k=0;k<Z;k++) 
	  {
		calculateLight(firm, i, j, k);
		
		float xx = -(X/2.0)*edge + (i+0.5)*edge;
		float yy = -(Y/2.0)*edge + (j+0.5)*edge;
		float zz = 0 + (k+0.5)*edge;
		

		if (matrix[i][j][k].getSTAR() > 0)
			file2 << "(" << i << "," << j << "," << k << ")   Koordinaatit: (" << xx << "," << yy << "," << zz << ")	incoming: " << matrix[i][j][k].getRadiationSum() << "  area density "<< matrix[i][j][k].getAreaDensity()  << endl;

		
		partsumsum += matrix[i][j][k].getPartSum();
	  }
	  file2 << " Osia yhteensä " << partsumsum << endl;
	  file2.close();
}




template <class TS,class BUD>
vector<SmallCube> Matrix<TS,BUD>::GetCubes()
{
  int num = 0;
  vector<SmallCube> cubes;
  vector<SmallCube> ordered_cubes;
  for (int i=0;i<X;i++)
    for (int j=0;j<Y;j++)
      for (int k=0;k<Z;k++) 
	{			
	  if (matrix[i][j][k].getSTAR() > 0)
	    {
	      SmallCube cube;
	      cube.x = i;
	      cube.y = j;
	      cube.z = k;
	      cube.ready = false;
	      cube.areaden = matrix[i][j][k].getAreaDensity(); 
	      
	      float xx = p1.getX() + (i+0.5)*edge;
	      float yy = p1.getY() + (j+0.5)*edge;
	      float zz = p1.getZ() + (k+0.5)*edge;
	      
	      cube.dist = pow(cam_x-xx, 2) + pow(cam_y-yy, 2) + pow(cam_z-zz, 2); 
	      

	      cube.x_coord = xx;
	      cube.y_coord = yy;
	      cube.z_coord = zz;

	      cubes.push_back(cube);
	      num ++;
	    }
	}
  return cubes;

}


template <class TS,class BUD>
void Matrix<TS,BUD>::Draw()
{
#ifdef _MSC_VER
	int num = 0;
	vector<SmallCube> cubes;
	vector<SmallCube> ordered_cubes;
	for (int i=0;i<X;i++)
		for (int j=0;j<Y;j++)
			for (int k=0;k<Z;k++) 
			{			
				if (matrix[i][j][k].getSTAR() > 0)
				{
					SmallCube cube;
					cube.x = i;
					cube.y = j;
					cube.z = k;
					cube.ready = false;
					cube.areaden = matrix[i][j][k].getAreaDensity(); 

					float xx = p1.getX() + (i+0.5)*edge;
					float yy = p1.getY() + (j+0.5)*edge;
					float zz = p1.getZ() + (k+0.5)*edge;

					cube.dist = pow(cam_x-xx, 2) + pow(cam_y-yy, 2) + pow(cam_z-zz, 2); 
				
					cubes.push_back(cube);
					num ++;
				}
			}


	for (i = 0; i<num; i++)
	{
		int max_dist = -10;
		int mem_num = -1;
		int a = cubes.size();
		for (int ii=0; ii<a; ii++)
		{
			SmallCube c = cubes[ii];
			if (c.ready == false)
			{
				if (c.dist > max_dist)
					mem_num = ii;
			}
		}
		if (mem_num > -1)
		{
			SmallCube &c = cubes[mem_num];
			c.ready = true;
			ordered_cubes.push_back(c);
		}
	}

	

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
		SmallCube cube = cubes[i];
		int i = cube.x;
		int j = cube.y;
		int k = cube.z;

		glColor3f(0.2,0.2,1);
				
				
		float hedge = 0.5 * edge;
		//pikkukuution keskipiste:
		/*
		float xx = -(X/2.0)*edge + (i+0.5)*edge;
		float yy = -(Y/2.0)*edge + (j+0.5)*edge;
		float zz = 0 + (k+0.5)*edge;
		*/

		float xx = p1.getX() + (i+0.5)*edge;
		float yy = p1.getY() + (j+0.5)*edge;
		float zz = p1.getZ() + (k+0.5)*edge;
		
		glBegin(GL_LINE_LOOP);
		glVertex3f(xx+hedge, yy-hedge, zz+hedge);
		glVertex3f(xx+hedge, yy+hedge, zz+hedge);
		glVertex3f(xx+hedge, yy+hedge, zz-hedge);
		glVertex3f(xx+hedge, yy-hedge, zz-hedge);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(xx-hedge, yy-hedge, zz+hedge);
		glVertex3f(xx-hedge, yy+hedge, zz+hedge);
		glVertex3f(xx-hedge, yy+hedge, zz-hedge);
		glVertex3f(xx-hedge, yy-hedge, zz-hedge);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(xx+hedge, yy-hedge, zz+hedge);
		glVertex3f(xx-hedge, yy-hedge, zz+hedge);
		glVertex3f(xx+hedge, yy+hedge, zz+hedge);
		glVertex3f(xx-hedge, yy+hedge, zz+hedge);
				
		glVertex3f(xx+hedge, yy+hedge, zz-hedge);
		glVertex3f(xx-hedge, yy+hedge, zz-hedge);
		glVertex3f(xx+hedge, yy-hedge, zz-hedge);
		glVertex3f(xx-hedge, yy-hedge, zz-hedge);
		glEnd();

		
		float shadow_odd = 0.1 + cube.areaden * (0.3 * pow(edge,3)); 

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0, 0.8, 0.0, shadow_odd);

		glBegin(GL_POLYGON);
		glVertex3f(xx-hedge, yy-hedge, zz+hedge);
		glVertex3f(xx-hedge, yy+hedge, zz+hedge);
		glVertex3f(xx-hedge, yy+hedge, zz-hedge);
		glVertex3f(xx-hedge, yy-hedge, zz-hedge);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xx+hedge, yy-hedge, zz+hedge);
		glVertex3f(xx+hedge, yy-hedge, zz-hedge);
		glVertex3f(xx+hedge, yy+hedge, zz-hedge);
		glVertex3f(xx+hedge, yy+hedge, zz+hedge);
		glEnd();


		glBegin(GL_POLYGON);
		glVertex3f(xx-hedge, yy+hedge, zz-hedge);
		glVertex3f(xx-hedge, yy+hedge, zz+hedge);
		glVertex3f(xx+hedge, yy+hedge, zz+hedge);
		glVertex3f(xx+hedge, yy+hedge, zz-hedge);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xx-hedge, yy-hedge, zz-hedge);
		glVertex3f(xx+hedge, yy-hedge, zz-hedge);
		glVertex3f(xx+hedge, yy-hedge, zz+hedge);
		glVertex3f(xx-hedge, yy-hedge, zz+hedge);
		glEnd();



		glBegin(GL_POLYGON);
		glVertex3f(xx-hedge, yy-hedge, zz-hedge);
		glVertex3f(xx-hedge, yy+hedge, zz-hedge);
		glVertex3f(xx+hedge, yy+hedge, zz-hedge);
		glVertex3f(xx+hedge, yy-hedge, zz-hedge);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(xx-hedge, yy-hedge, zz+hedge);
		glVertex3f(xx+hedge, yy-hedge, zz+hedge);
		glVertex3f(xx+hedge, yy+hedge, zz+hedge);
		glVertex3f(xx-hedge, yy+hedge, zz+hedge);
		glEnd();

		glDisable(GL_BLEND);
	}
#endif
}


//--------------------------------------------------------------------
//
// Constructor. Given arguments are tree and voxels edge lengths
//
//--------------------------------------------------------------------
template <class TS,class BUD>
Matrix<TS,BUD>::Matrix(Tree<TS,BUD> *tree, double voxeledge)
{
  int i, j, k;                           // Loop counters
  Point *base = new Point(0,0,0);
 
  edge = voxeledge;

  //
  // Calculate voxel matrixes dimensions
  //
  BoundingBox init, bbox;
 
  bbox = Accumulate(*tree, init, FindBoundingBox<TS,BUD>() );
 
  Point span = bbox.getMax() - bbox.getMin();
  LGMdouble max_branch = sqrt(pow(span.getX()/2.0,2.0) +
                              pow(span.getY()/2.0,2.0));

  X = (int)(2*info.max_branch/edge)+2;          // depth
  Y = (int)(2*info.max_branch/edge)+2;          // width
  Z = (int)(info.tree_length/edge)+1;           // heigth of the matrix
  X_0 = X/2;
  Y_0 = Y/2;
  Z_0 = 0;

  //
  // Reserve the memory for the matrix
  //
  matrix = new Voxel**[X];
  for (j=0;j<Y;j++)
    matrix[j] = new Voxel*[Y];
  for (i=0;i<X;i++)
    for(j=0;j<Y;j++)
      matrix[i][j] = new Voxel[Z];

  importTree(tree, *base);
  calculateMeanSegment();

  for (i=0;i<X;i++)
    for (j=0;j<Y;j++)
      for (k=0;k<Z;k++)
	calculateLight(i, j, k);

	delete point;
}


//------------------------------------------------------------------------
//
// Destructor
//
//------------------------------------------------------------------------
template <class TS,class BUD>
Matrix<TS,BUD>::~Matrix()
{
  /* Destructor should not be used since there is no member data.
  int i, j ,k;
  for (i=0;i<X;i++)
    for (j=0;j<Y;j++)
      delete [] matrix[i][j];
  for (i=0;i<X;i++)
    delete [] matrix[i];
  delete [] matrix;
  */
}


//-------------------------------------------------------------------------
//
// addTree. Adds a tree into matrix.
//
//-------------------------------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::addTree(Tree<TS,BUD> *tree, Point base)
{
  importTree(tree, base);
  calculateMeanSegment();
}

//-------------------------------------------------------------------------
//
// getLight. Gets the shoot as argument and calculates the light
// conditions for it.  Pretty much the function as addToVoxel. Maybe
// they could be combined...
//
//-------------------------------------------------------------------------
template <class TS,class BUD>
double Matrix<TS,BUD>::getLight(TreeSegment<TS,BUD> *ts)
{
  Point middlepoint = GetPoint(*ts)+(Point)((0.5*GetValue(*ts,L))*GetDirection(*ts));

  double light = 0, tmplen, length = GetValue(*ts, L);
  int i, x, y, z;
  Point midvoxel; //, endvoxel, intersection = startpoint;
  Point last_intersection = middlepoint; //
  double tmp_x, tmp_y, tmp_z, dist_x = 9999, dist_y = 9999, dist_z = 9999;

  //
  // Calculate the starting voxel
  //
  midvoxel = calcVoxel(middlepoint);
  x = midvoxel.getX();
  y = midvoxel.getY();
  z = midvoxel.getZ();

  ts->voxel_id = Point(x,y,z);

  PositionVector dir = GetDirection(*ts);
  dir.normalize();

  
  LGMdouble q_in = matrix[x][y][z].getRadiationSum();
  //  SetValue(*ts, Qin, q_in);

  //compute the surface area (sa) of the cylinder representing foliage
  LGMdouble sf = 0.0;  
  LGMdouble W_f = 0.0;	
 

  //Note Qin and the following calculations made only for
  //CfTreeSegment --ONLY PRELIMINARY SOLUTION --- MUST BE REVISED to
  //include also HwTreeSegment !!!!!!!!!!!!!!!!!!!!!!
  LGMdouble needle_rad = 0.0;
  if (CfTreeSegment<TS, BUD>* cfts = dynamic_cast<CfTreeSegment<TS, BUD>*>(ts))  	  
    {
/*       cout << "TreeSegment   Position:" << GetPoint(*cfts) << "  Direction:" << GetDirection(*cfts) << endl; */
/*       cout << "Length " << GetValue(*cfts, L) << "  Radius:"<< GetValue(*cfts, R) << endl; */

/*       cout << "FoliageMass:"<< GetValue(*cfts, Wf) << endl; */


      SetValue(*cfts, Qin, q_in);
      W_f = GetValue(*cfts, Wf);
      sf = 2.0 * PI_VALUE * GetValue(*cfts,Rf) * GetValue(*ts,L);
      
      LGMdouble needle_length = GetValue(GetTree(*cfts),nl);
      LGMdouble needle_angle = GetValue(GetTree(*cfts),na);
      SetValue(*cfts, Rf,needle_length * sin(needle_angle)+ GetValue(*ts,R));
      needle_rad = GetValue(*cfts, Rf);
  
      sf = 28.1;
      LGMdouble star = 0;
  
	
      //ofstream file("starsum.txt"); file << "kaava : star += S(phi,
      //sa, W_f, GetValue(*ts, R), GetValue(*ts, L))/8;" << endl <<
      //endl;
      for (double phi=0;phi<PI_VALUE/2;phi+=PI_VALUE/16)
	{  
	  star += S(phi, sf, W_f, needle_rad, GetValue(*ts, L))/8.0;
	  
/* 	  cout << "star += S()/8.0" << endl; */
/* 	  cout << "eli star += S(phi, sf, W_f, needle_rad, GetValue(*ts, L))/8.0; " << endl; */
/* 	  cout << "jossa S() =S(" << phi <<","<<sf<< ","<<W_f<<","<< needle_rad<<","<<GetValue(*ts, L) <<")"<< endl; */


	  //cout  << "S()="<< S(phi, sf, W_f, GetValue(*ts, R),
	  //GetValue(*ts, L)) << " parametrit: phi="<<phi<<" sf="<<
	  //sf<<" Wf="<<W_f<<" R="<<GetValue(*ts, R)<<"
	  //L="<<GetValue(*ts, L); file << " summa=" << star << endl;
	}
      LGMdouble Q_abs = q_in * star * W_f * sf;
      //file << "Q_abs = q_in * star * wf * sf: " << q_in << " * " <<
      //star << " * " << W_f << " * " << sf << " = " << Q_abs << endl;
      //file.close();
  
      SetValue(*cfts, Qabs, Q_abs);

/*       cout << "pikku kuution indeksit (" << x << ", " << y << ", " << z << endl; */
/*       cout << "Star segmentille " << star << "  Q_abs = q_in * star * W_f * sf " << endl;   */
/*       cout << "Qin  " << q_in << endl; */
/*       cout << "Qabs " << Q_abs << endl << endl << endl; */

      return Q_abs;
    }

  return 0.0;  //THIS if not CfTreeSegment --- PRELIMINARY!!!!!!!
}




// Default constructor
template <class TS,class BUD>
Matrix<TS,BUD>::Matrix()
{
  X = Y = Z = 0;
}

// Print stuff about matrix
template <class TS,class BUD>
void Matrix<TS,BUD>::printInfo(int x, int y, int z) const
{
#ifdef _MSC_VER
	ofstream file("voxel_info.txt");
	
		file << "edge = " << edge << endl
       << "X = " << X << endl
       << "Y = " << Y << endl
       << "Z = " << Z << endl
       << "X_0 = " << X_0 << endl
       << "Y_0 = " << Y_0 << endl
       << "Z_0 = " << Z_0 << endl << endl;
  file << "Voxel index: " << x << " " << y << " " << z << endl;
  file << "Reprecented volume: "
       << (x - X_0 - 0.5)*edge << " "
       << (y - Y_0 - 0.5)*edge << " "
       << (z - Z_0)*edge << " -- "
       << (x - X_0 + 0.5)*edge << " "
       << (y - Y_0 + 0.5)*edge << " "
       << (z - Z_0 + 1.0)*edge << endl;

	file.close();
	RunHide("voxel_info.txt");

#else
	cout << "edge = " << edge << endl
       << "X = " << X << endl
       << "Y = " << Y << endl
       << "Z = " << Z << endl
       << "X_0 = " << X_0 << endl
       << "Y_0 = " << Y_0 << endl
       << "Z_0 = " << Z_0 << endl << endl;
  cout << "Voxel index: " << x << " " << y << " " << z << endl;
  cout << "Reprecented volume: "
       << (x - X_0 - 0.5)*edge << " "
       << (y - Y_0 - 0.5)*edge << " "
       << (z - Z_0)*edge << " -- "
       << (x - X_0 + 0.5)*edge << " "
       << (y - Y_0 + 0.5)*edge << " "
       << (z - Z_0 + 1.0)*edge << endl;
  matrix[x][y][z].printInfo();
  cout << endl;
#endif
}

template <class TS,class BUD>
void Matrix<TS,BUD>::printIncomingRadiation() const
{
  int x, y, z;

  #ifdef _MSC_VER
	ofstream file("voxel_info.txt");
	
	file << "edge = " << edge << endl
       << "X = " << X << endl
       << "Y = " << Y << endl
       << "Z = " << Z << endl
       << "X_0 = " << X_0 << endl
       << "Y_0 = " << Y_0 << endl
       << "Z_0 = " << Z_0 << endl << endl;

  for(x=0; x<X; x++)  
    for(y=0; y<Y; y++) 
      for(z=0; z<Z; z++) 
	  {
		file	<< "voxelmidpoint "
				<< (x-X_0)*edge << " "
				<< (y-Y_0)*edge << " "
				<< (z-Z_0)*edge + 0.5*edge << " "
				<< "incomingradiation ";
		matrix[x][y][z].printIncomingRadiation();
		file << endl;
      }

	file.close();
	RunHide("voxel_info.txt");

#else

  cout << "edge = " << edge << endl
       << "X = " << X << endl
       << "Y = " << Y << endl
       << "Z = " << Z << endl
       << "X_0 = " << X_0 << endl
       << "Y_0 = " << Y_0 << endl
       << "Z_0 = " << Z_0 << endl << endl;

  for(x=0; x<X; x++)  
    for(y=0; y<Y; y++) 
      for(z=0; z<Z; z++) {
	cout << "voxelmidpoint "
	     << (x-X_0)*edge << " "
	     << (y-Y_0)*edge << " "
	     << (z-Z_0)*edge + 0.5*edge << " "
	     << "incomingradiation ";
	matrix[x][y][z].printIncomingRadiation();
	cout << endl;
      }
#endif
}     

template <class TS,class BUD>
void Matrix<TS,BUD>::fill(const Voxel &v)
{
  for(int x=0; x<X; x++)
    for(int y=0; y<Y; y++)
      for(int z=0; z<Z; z++)
	matrix[x][y][z] = v;
}

template <class TS,class BUD>
void Matrix<TS,BUD>::makeRadiationField()
{
  for(int x=0; x<X; x++)
    for(int y=0; y<Y; y++)
      for(int z=0; z<Z; z++)
	calculateLight(x, y, z);
}


template <class TS,class BUD>
Voxel Matrix<TS,BUD>::getVoxel(int x, int y, int z)
{
  return matrix[x][y][z];
}


template <class TS,class BUD>
Matrix<TS,BUD>::Matrix(int xdim, int ydim, int zdim, double voxeledge, double ext)
{
  int i, j, k;                           // Loop counters

  edge = voxeledge; // added by norrman

  //
  // Calculate voxel matrixes dimensions
  //
  X = xdim;
  Y = ydim;
  Z = zdim;
  X_0 = X/2;
  Y_0 = Y/2;
  Z_0 = 0;

  //
  // Reserve the memory for the matrix
  //
  matrix = new Voxel**[X];
  for (j=0;j<Y;j++)
    matrix[j] = new Voxel*[Y];
  for (i=0;i<X;i++)
    for(j=0;j<Y;j++)
      matrix[i][j] = new Voxel[Z];

  for (i=0;i<X;i++)
    for (j=0;j<Y;j++)
      for (k=0;k<Z;k++) {
	matrix[i][j][k].addSTAR(0.1);
	matrix[i][j][k].setAreaDensity(ext/0.1);
      }
}


template <class TS,class BUD>
void Matrix<TS,BUD>::display() const
{
  for(int x=0;x<X;x++)
    for(int y=0;y<Y;y++)
      for (int z=0;z<Z;z++) 
	  {
#ifdef _MSC_VER
			 file << x << " " << y << " " << z << endl;
			 file << matrix[x][y][z].getAreaDensity()
			 
#else
			cout.width(3); cout << x;
			cout.width(3); cout << y;
			cout.width(3); cout << z;
			cout.width(12); cout << matrix[x][y][z].getAreaDensity();
			cout.width(12); cout << matrix[x][y][z].getSTAR();
			cout.width(12); cout << matrix[x][y][z].getExtinctionCoefficent();
			cout.width(12); cout << matrix[x][y][z].getRadiationSum();
			cout << endl;
#endif
      }
}






//----------------------------------------------------
//
// Calculates the distance between two points
//
//----------------------------------------------------
template <class TS,class BUD>
double Matrix<TS,BUD>::calcLength(Point startpoint, Point endpoint)
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
template <class TS,class BUD>
Point Matrix<TS,BUD>::calcVoxel(Point point)
{
	// Uusi toteutus

	int x = (int)(point.getX() - p1.getX()) / edge;
	int y = (int)(point.getY() - p1.getY()) / edge;
	int z = (int)(point.getZ() - p1.getZ()) / edge;

	if (x<0 || x>X-1)
	{
#ifdef _MSC_VER
		MessageBox(NULL, "Pisteen x-koordinaatti menee vokselin yli (liian pieni arvo)", NULL, NULL);	
#else
		cerr << "Piste " << point << " ei kuulu vokseliin. Vokselin rajat "<< p1 << " ja " << p2 << "."<< endl;
#endif
	}


	if (y<0 || y>Y-1)
	{
#ifdef _MSC_VER
		MessageBox(NULL, "Pisteen y-koordinaatti menee vokselin yli (liian pieni arvo)", NULL, NULL);	
#else
		cerr << "Piste " << point << " ei kuulu vokseliin. Vokselin rajat "<< p1 << " ja " << p2 << "."<< endl;
#endif
	}


	if (z<0 || z>Z-1)
	{
#ifdef _MSC_VER
		MessageBox(NULL, "Pisteen z-koordinaatti menee vokselin yli (liian pieni arvo)", NULL, NULL);	
#else
		cerr << "Piste " << point << " ei kuulu vokseliin. Vokselin rajat "<< p1 << " ja " << p2 << "."<< endl;
#endif
	}




	return Point(x,y,z);
}


//-----------------------------------------------------
//
// Calculates the transmission coefficient (table value)
//
//-----------------------------------------------------
template <class TS,class BUD>
double Matrix<TS,BUD>::K(double phi)
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
template <class TS,class BUD>
double Matrix<TS,BUD>::SAc(double phi, double r, double l)
{
  return 2 * l * cos(phi) * r + PI_VALUE * r * r * sin(phi);
}


template <class TS,class BUD>
double Matrix<TS,BUD>::S(double phi, double Sf, double Wf, double r, double l)
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

template <class TS,class BUD>
void Matrix<TS,BUD>::calculateMeanSegment()
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
template <class TS,class BUD>
float Matrix<TS,BUD>::linePosition(float p, float v, int voxels)
{
  float t;
  if(v == 0) return FLT_MAX;           // infinitum
  if(v > 0) t = ((float)voxels - p)/v; // check against plane at "voxels",
  if(v < 0) t = (0 - p)/v;             // or chech against plane at 0.
  return t;
}




template <class TS,class BUD>
void Matrix<TS,BUD>::newTraversePath(PositionVector direction, double radiation, Point startpoint, Point startvoxel)
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
  matrixxx = this->matrix;
  

  float through = 0.0; 
  through = interExt(ec, edge, endp, startp);

  matrix[(int)vox.getX()][(int)vox.getY()][(int)vox.getZ()].addRadiationSum(radiation*through);
}




//-----------------------------------------------------
//
//  Calculates the light coming to a voxel
//
//-----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::calculateLight(Firmament *firm, int x, int y, int z)
{
  matrix[x][y][z].setIncomingRadiation(0);
  matrix[x][y][z].setRadiationSum(0);
  //
  // Initialize the sky
 
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


  double total_radiation = 0.0;
  //
  // Calculate the diffuse radiation
  //
  for (i=0;i<num_dirs;i++) 
    {
          
      radiationsum = firm->diffuseRegionRadiationSum(i, direction);
/*       cout << "Taivaankannen suunta " << direction << endl; */
      total_radiation += radiationsum;
      newTraversePath(direction, radiationsum, *point, *startvoxel);
    }

  //  cout << "Total radiation " << total_radiation << endl;

  //
  // Calculate the direct radiation
  //
  //radiationsum = firm->directRadiation(direction);
  //traversePath(direction, radiationsum, *point, *startvoxel);

 // delete firm;
  delete point;
  delete startvoxel;
}









//----------------------------------------------------
//
// Import tree into matrix
//
//----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::importTree(Tree<TS,BUD> *tree, Point base)
{
 
  Axis<TS,BUD> &main_stem = GetAxis(*tree);

  doAxis(&main_stem, base);
}


//----------------------------------------------------
//
// Subroutine to recurse tree.
//
//----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::doAxis(Axis<TS,BUD> *axis, Point base)
{
	Bud<TS,BUD> *bud;
	BranchingPoint<TS,BUD> *bp;

	list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(*axis);
	list<TreeCompartment<TS,BUD>*>::iterator I = ls.begin();
  
	while(I != ls.end())
	{
		if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(*I))
		{
			placeSegment(ts, base);
		}
		
		if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(*I))
		{
			doBranchingPoint(bp, base);
		}



		I++;
	}
}



//----------------------------------------------------
//
// Handles stems of the current branchwhorl.
//
//----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::doBranchingPoint(BranchingPoint<TS,BUD> *bp, Point base)
{
	list<Axis<TS,BUD>*>::iterator first = GetAxisList(*bp).begin();
	list<Axis<TS,BUD>*>::iterator last = GetAxisList(*bp).end();

	while (first != last)
	{
		doAxis(*first++, base);	
	}  
}


//----------------------------------------------------
//
// placeSegment
// Calculates the sarting and ending voxels of the
// segment and then calls addToVoxel which calculates
// the needed parameters for the voxels.
//
//----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::placeSegment(TreeSegment<TS,BUD> *ts, Point base)
{
  if(TS* tts = dynamic_cast<TS *>(ts)) 
    {
      double  w_f = GetValue(*tts, Wf);
      if (w_f < R_EPSILON)
	return;
    }


  Point startpoint = GetPoint(*ts); // + base; 
  PositionVector direction = GetDirection(*ts);
  Point endpoint, voxel_coord, startvoxel, endvoxel;

  double length = GetValue(*ts, L) * 0.5;

  int start_x, start_y, start_z, end_x, end_y, end_z;

  //
  // First the ending points...
  //
  Point middlepoint = Point((startpoint.getX() + base.getX() + length*direction.getX()),
			    (startpoint.getY() + base.getY() + length*direction.getY()),
			    (startpoint.getZ() + base.getZ() + length*direction.getZ()));

  Point voxel = calcVoxel(middlepoint);   
  addValues(voxel, GetValue(*ts, L), ts);
  

  /* Point startpoint = GetPoint(*ts); // + base;
/*   PositionVector direction = GetDirection(*ts); */
/*   Point endpoint, voxel_coord, startvoxel, endvoxel; */

/*   double length = GetValue(*ts, L); */

/*   int start_x, start_y, start_z, end_x, end_y, end_z; */

/*   // */
/*   // First the ending points... */
/*   // */
/*   endpoint = Point(	(startpoint.getX() + base.getX() + length*direction.getX()),  */
/* 					(startpoint.getY() + base.getY() + length*direction.getY()),  */
/* 					(startpoint.getZ() + base.getZ() + length*direction.getZ()));  */

/*   // */
/*   // Calculate the starting voxel. */
/*   // */
/*   startvoxel = calcVoxel(startpoint); */
/*   start_x = (int) startvoxel.getX(); */
/*   start_y = (int) startvoxel.getY(); */
/*   start_z = (int) startvoxel.getZ(); */


/*   if (start_z < 0 || startpoint.getZ() < 0) */
/* 	  start_z += 0; */
/*   // */
/*   // Calculate the ending voxel of a segment. */
/*   // */
/*   endvoxel = calcVoxel(endpoint); */
/*   end_x = (int) endvoxel.getX(); */
/*   end_y = (int) endvoxel.getY(); */
/*   end_z = (int) endvoxel.getZ(); */

/*   // */
/*   // Check if the segment fits in one voxel */
/*   // Placing of the segment fitting in one voxel is done here to */
/*   // avoid the extra calculations */
/*   if (start_x == end_x && start_y == end_y && start_z == end_z) */
/*     addValues(startvoxel, GetValue(*ts, L), ts); */
/*   else  */
/*     addToVoxel(startpoint, endpoint, startvoxel, endvoxel, ts); */
  
}



//----------------------------------------------------
//
// Adds values to a voxel
// Just to make it simppler by adding all in one place
//
//----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::addValues(Point voxel, double length, TreeSegment<TS,BUD> *ts)
{
  int x = (int) voxel.getX();
  int y = (int) voxel.getY();
  int z = (int) voxel.getZ();
  

  LGMdouble r_f = 0.0;
  LGMdouble w_f = 0.0;
  if(TS* tts = dynamic_cast<TS *>(ts)) 
    {
      r_f = GetValue(*tts, Rf);
      w_f = GetValue(*tts, Wf);
    }

  
  matrix[x][y][z].setMeanLength(matrix[x][y][z].getMeanLength()*matrix[x][y][z].getSumLength());
  matrix[x][y][z].addSumVector(length * GetDirection(*ts));
  double part_sum = length / GetValue(*ts, L);
  matrix[x][y][z].addPartSum(part_sum);
  matrix[x][y][z].addSumLength(length);
  matrix[x][y][z].addSumWoodRadius(length * GetValue(*ts, R));
  matrix[x][y][z].addSumTotalRadius(length * r_f); 
  matrix[x][y][z].addFoliageMass(length / GetValue(*ts, L) * w_f);
  LGMdouble le = GetValue(*ts, L);
 
  LGMdouble foliage_area = GetValue(*ts, L) * r_f * 2 * PI_VALUE;
  matrix[x][y][z].addFoliageArea(length / GetValue(*ts, L) * foliage_area); //*****shoot->getFoliageArea());  
  matrix[x][y][z].setMeanLength((matrix[x][y][z].getMeanLength() + length*GetValue(*ts,L))/matrix[x][y][z].getSumLength()); //*** meniko lasku nain??

}




//----------------------------------------------------
//
// Adds a segment to a voxel. Calculates the intersection
// points and places the parts into to the meansegments
// in the matrix
//
//----------------------------------------------------
template <class TS,class BUD>
void Matrix<TS,BUD>::addToVoxel(Point startpoint, Point endpoint, Point startvoxel,
		Point endvoxel, TreeSegment<TS,BUD> *ts)
{
  int start_x = (int) startvoxel.getX();
  int start_y = (int) startvoxel.getY();
  int start_z = (int) startvoxel.getZ();
  int end_x = (int) endvoxel.getX();
  int end_y = (int) endvoxel.getY();
  int end_z = (int) endvoxel.getZ();

  if (end_z < 0)
	end_z = end_z;

  if (start_z < 0)
	end_z = end_z;

  // 
  // Number of segments intersection points
  //
  int nr_intersections = (abs)(start_x - end_x) + (abs)(start_y - end_y)
    + (abs)(start_z - end_z);

  Point intersection = startpoint, last_intersection = startpoint;
  int i;
  double tmp_x, tmp_y, tmp_z, dist_x=9999, dist_y=9999, dist_z=9999, length;
  Point xyz;

  //
  // Calculate the first intersection value for each direction
  // 0.5 values are used to move the 0,0 values of trees x,y
  // coordinates in the middle of a voxel. edge/2 is used to 
  // remove the rounding errors made by (int)
  // 0 value of z cooordinate is presumed to be in the bottom 
  // of a voxel and so it's a bit easier to calculate.
  //
  if (last_intersection.getX() == 0)
    tmp_x = 0;
  else if (last_intersection.getX() < 0)
    tmp_x = (int)((last_intersection.getX() - edge/2) / edge);
  else
    tmp_x = (int)((last_intersection.getX() + edge/2) / edge);
  if (GetDirection(*ts).getX() < 0)
    tmp_x = (tmp_x - .5) * edge;
  else
    tmp_x = (tmp_x + .5) * edge;
  
  if (last_intersection.getY() == 0)
    tmp_y = 0;
  else if (last_intersection.getY() < 0)
    tmp_y = (int)((last_intersection.getY() - edge/2) / edge);
  else
    tmp_y = (int)((last_intersection.getY() + edge/2) / edge);
  if (GetDirection(*ts).getY() < 0)
    tmp_y = (tmp_y - .5) * edge;
  else
    tmp_y = (tmp_y + .5) * edge;
  
  if (GetDirection(*ts).getZ() < 0)
    tmp_z = (int)(last_intersection.getZ()/edge) * edge;
  else 
    tmp_z = (int)((last_intersection.getZ()/edge) + 1) * edge;

  //
  // Cycle through the intersection points
  // max points calculated above
  //
  for (i=0;i<nr_intersections;i++) {

    //
    // Re-initialize for every round.
    //
    dist_x = dist_y = dist_z = 9999;

    //
    // Calculate the distances to the possible next intersection points.
    //
    if (GetDirection(*ts).getX() != 0)
		dist_x = fabs((tmp_x - last_intersection.getX()) / GetDirection(*ts).getX());
    
	if (GetDirection(*ts).getY() != 0)
		dist_y = fabs((tmp_y - last_intersection.getY()) / GetDirection(*ts).getY());
    
	if (GetDirection(*ts).getZ() != 0)
		dist_z = fabs((tmp_z - last_intersection.getZ()) / GetDirection(*ts).getZ());

    //
    // Find out which point is the next intersection point
    // (shortest distance)
    //
    if (dist_x < dist_y && dist_x < dist_z && dist_x != 0) 
	{
      intersection = Point((tmp_x),
						   (last_intersection.getY() + dist_x * GetDirection(*ts).getY()),
						   (last_intersection.getZ() + dist_x * GetDirection(*ts).getZ()));

      // 
      // Calculate the voxel coordinates
      //
      xyz = calcVoxel(last_intersection);

      //
      // Add the wanted values to the voxel
      //
      length = calcLength(last_intersection, intersection);
      
	  
	  //if (xyz.getZ() < 0)
		//  MessageBox(NULL, "123:virhe täällä", NULL, NULL);
	  addValues(xyz, length, ts);
      
      //
      // Calculate the next possible intersection point
      //
      if (GetDirection(*ts).getX() < 0)
			tmp_x -= edge;
      else
			tmp_x += edge;
      
      last_intersection = intersection;
    }
    
    if (dist_y < dist_x && dist_y < dist_z && dist_y != 0) 
	{
      intersection = Point((last_intersection.getX() + dist_y * GetDirection(*ts).getX()),
							(tmp_y),
							(last_intersection.getZ() + dist_y * GetDirection(*ts).getZ()));

	  
      xyz = calcVoxel(last_intersection);
      
      length = calcLength(last_intersection, intersection);
      
	  addValues(xyz, length, ts);
      
      if (GetDirection(*ts).getY() < 0)
			tmp_y -= edge;
      else
			tmp_y += edge;
      
      last_intersection = intersection;
    }
    
    if (dist_z < dist_x && dist_z < dist_y && dist_z != 0) 
	{
		intersection = Point((last_intersection.getX() + dist_z * GetDirection(*ts).getX()),
							 (last_intersection.getY() + dist_z * GetDirection(*ts).getY()),
							 (tmp_z));
	
      
      xyz = calcVoxel(last_intersection);
      
      length = calcLength(last_intersection, intersection);
      
	  //if (xyz.getZ() < 0)
	//	  MessageBox(NULL, "125:virhe täällä", NULL, NULL);
	  addValues(xyz, length, ts);

      if (GetDirection(*ts).getZ() < 0)
		tmp_z -= edge;
      else
		tmp_z += edge;
      
      last_intersection = intersection;
    }
  } 

  //
  // Add the last part from the last intersection point to the ending point
  // into the matrix
  //
  length = calcLength(last_intersection, endpoint);
  //if (endvoxel.getZ() < 0)
	//	  MessageBox(NULL, "126:virhe täällä", NULL, NULL);
  addValues(endvoxel, length, ts);
}




#endif
