
#ifndef H_RMATRIX_H
#define H_RMATRIX_H

/*=====================================================================
**H_RMatrix ("Homogenious Rotation Matrix") is a matrix to
**apply table of function to given angle. The result is
**FMatrix which in turn can be used to rotate 3D points.
**HRMATRIX is like RMatrix but it overcomes the problem
**with point (0,0,0) wich is the invariant in 3D point transformations
*/

#include <vector.h>
#include <Rotation.h>
#include <mathsym.h>
#include <Point.h>
#include <TMatrix.h>

#define N_OF_AXIS      3
#define H_RMATRIX_SIZE 4

namespace cxxadt {

class HRMatrix{
friend RADIAN fn_1(RADIAN angle);
friend RADIAN fn_0(RADIAN angle);
friend RADIAN neg_sin(RADIAN angle);
friend RADIAN neg_cos(RADIAN angle);
public:
  HRMatrix(ROTATION direction);
  TMatrix<double> operator()(RADIAN angle);
  HRMatrix& changeAxis(ROTATION direction);
  HRMatrix& transpose();
  HRMatrix& inverse();
private:
  ROTATION r_direction;
  RADIAN (*(fn_matrix_table[N_OF_AXIS][H_RMATRIX_SIZE * H_RMATRIX_SIZE]))(RADIAN);
};

#endif


#ifndef H_RVECTOR_H
#define H_RVECTOR_H

/*==========================================================================
**class H_RVector ("Homogenious Rotation Vector") is a vector of [x,y,x,1]
**It is meant to be used with TMatrix which is created by application 
**of HRMatrix to an rotation angle in 3-D transformations.
**The constructor takes a Point(x,y,z) and transfers it to
**a 4-D vector [x,y,z,1].  
*/

class HRVector:public vector<double>{
friend vector<double> operator * (const HRVector& v,const TMatrix<double>& m);
public:
  HRVector(const Point& pos);
};

}//closing oldadt

#endif


