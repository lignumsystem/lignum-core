#ifndef VOXELMATRIX_H
#define VOXELMATRIX_H

#include <VoxelSpace.h>
#include <Voxel.h>

//#include "OpenGL.h"
#include <Tree.h>
#include <fstream>
#include <vector>
#include <ScotsPineVisual.h>

using namespace std;

using namespace Lignum;

struct SmallCube
{
	int x,y,z;
	float dist;
	float areaden;
	bool ready;
};

extern float cam_x;  //camera position
extern float cam_y;
extern float cam_z;



extern int voxelSizeX;
extern int voxelSizeY;
extern int voxelSizeZ;





Voxel ***matrixxx;

//Functor for getting extinction coefficient
class getExtCoeff
{
public:
	getExtCoeff() { }
	float getExtCoeff::operator()(const PositionVector &v)
	{ 
		int x = (int)v.getX();
		int y = (int)v.getY();
		int z = (int)v.getZ();
	
		float ret = matrixxx[x][y][z].getExtinctionCoefficent();
		return ret; 
	}

	
	

	
};





template <class TS,class BUD>
class Matrix 
{
public:

 
  Matrix();


  Matrix(vector<Tree<TS, BUD> *> trees, double edge);


  Matrix(Tree<TS,BUD> *, double, double, double, double);
  // Constructor for one tree and the dimensions for the matrix
  
  Matrix(Tree<TS,BUD> *, double);
  // Contructor where the size of matrix is taken from trees dimensions
  Matrix(int, int, int, double, double);
  
  ~Matrix();

  double getLight(TreeSegment<TS,BUD> *);  // Calculates the light conditions for a given shoot
  void addTree(Tree<TS,BUD> *, Point);  // Adds more tree to matrix

  void printInfo(int, int, int) const;
  void printIncomingRadiation() const;

  void fill(const Voxel &v); /* Fill voxel space with similar voxels
				(for testing purposes). */

  void makeRadiationField();
  Voxel getVoxel(int, int, int);
  void Draw();

  

  void display() const;
  void printInfo();

  double edge;
	int X, Y, Z, X_0, Y_0, Z_0;
	Voxel ***matrix;



	Point GetMiddlePoint(){ return (p1+p2)/2.0; }
private:
	Point p1;
	Point p2;

	void addToVoxel(Point startpoint, Point endpoint, Point startvoxel, Point endvoxel, TreeSegment<TS,BUD> *ts);
	void addValues(Point voxel, double length, TreeSegment<TS,BUD> *ts);
	void placeSegment(TreeSegment<TS,BUD> *ts, Point base);
	void doBranchingPoint(BranchingPoint<TS,BUD> *bp, Point base);
	void doAxis(Axis<TS,BUD> *axis, Point base);
	void importTree(Tree<TS,BUD> *tree, Point base);




	double calcLength(Point startpoint, Point endpoint);
	Point calcVoxel(Point point);
	double K(double phi);
	double SAc(double phi, double r, double l);
	double S(double phi, double Sf, double Wf, double r, double l);
	void calculateMeanSegment();
	float linePosition(float p, float v, int voxels);
	void newTraversePath(PositionVector direction, double radiation, Point startpoint, Point startvoxel);
	void calculateLight(Firmament *firm, int x, int y, int z);


};






#include <voxelmatrixI.h>


#endif
