
#ifndef RMATRIX_H
#define RMATRIX_H
#include <mathsym.h>
#include <Rotation.h>
#include <TMatrix.h>

namespace cxxadt{
/*===================================================================
**RMatrix ("Rotation Matrix") is a matrix to apply
**table of functions to given angle. The result is a FMatrix
**which in turn can be used to rotate 3D points.
**RMatrix has three tables of functions, one for each axis in 3D.
**For example "RMatrix r1(ROTATE_X)" creates a RMatrix of functions that 
**rotates points round x-axis.
**RMatrix is a transition matrix from one orthonormal
**base to another so the inverse ("undoing" the previous rotation)
**is the transpose of the matrix
*/

#define RMATRIX_SIZE 3

class RMatrix{
  friend RADIAN fn_1(RADIAN angle);
  friend RADIAN fn_0(RADIAN angle);
  friend RADIAN neg_sin(RADIAN angle);
  friend RADIAN neg_cos(RADIAN angle);
public:
  RMatrix(ROTATION direction);
  TMatrix<double> operator()(RADIAN angle)const;
  RMatrix& changeAxis(ROTATION direction);
  RMatrix& transpose();
  RMatrix& inverse();
private:
  ROTATION r_direction;
  RADIAN (*(fn_matrix_table[RMATRIX_SIZE][RMATRIX_SIZE * RMATRIX_SIZE]))(RADIAN);
};

}//close namespace cxxadt

#endif








