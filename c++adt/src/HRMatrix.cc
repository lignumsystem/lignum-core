
#include <HRMatrix.h>


namespace cxxadt{

HRMatrix::HRMatrix(ROTATION direction)
{
  int i = 0;
  
  r_direction = direction;
  
  static double (*x_rot[])(RADIAN) = 
    {fn_1,fn_0,fn_0,fn_0,
     fn_0,cos,sin,fn_0,
     fn_0,neg_sin,cos,fn_0,
     fn_0,fn_0,fn_0,fn_1
    };

  static double (*y_rot[])(RADIAN) =
    {cos,fn_0,neg_sin,fn_0,
     fn_0,fn_1,fn_0,fn_0,
     sin,fn_0,cos,fn_0,
     fn_0,fn_0,fn_0,fn_1
    };

  static double (*z_rot[])(RADIAN) =
    {cos,sin,fn_0,fn_0,
     neg_sin,cos,fn_0,fn_0,
     fn_0,fn_0,fn_1,fn_0,
     fn_0,fn_0,fn_0,fn_1
    };

  for (i = 0; i < H_RMATRIX_SIZE * H_RMATRIX_SIZE; i++)
    fn_matrix_table[0][i] = x_rot[i];

  for (i = 0; i < H_RMATRIX_SIZE * H_RMATRIX_SIZE; i++)
    fn_matrix_table[1][i] = y_rot[i];

  for (i = 0; i < H_RMATRIX_SIZE * H_RMATRIX_SIZE; i++)
    fn_matrix_table[2][i] = z_rot[i];
}

TMatrix<double> HRMatrix::operator()(RADIAN angle)
{
  int i=0,j=0,k=0;
  TMatrix<double> m_tmp(H_RMATRIX_SIZE,H_RMATRIX_SIZE);

  for (i = 0; i < H_RMATRIX_SIZE; i++){
    for (j = 0; j < H_RMATRIX_SIZE; j++){
      m_tmp[i][j] = 
	(double)(*(fn_matrix_table[r_direction][k++]))((double)angle);
    }
  }

  return m_tmp;
}

HRMatrix& HRMatrix::changeAxis(ROTATION direction)
{
  r_direction = direction;
  return *this;
}

HRMatrix& HRMatrix::transpose()
{
  int i=0,j=0,k=0;
  double (*m_tmp[H_RMATRIX_SIZE][H_RMATRIX_SIZE])(RADIAN);

  for (i = 0; i < H_RMATRIX_SIZE; i++){
    for (j = 0; j < H_RMATRIX_SIZE; j++){
      m_tmp[j][i] = fn_matrix_table[r_direction][k++];
    }
  }

  k=0;
  for (i = 0; i < H_RMATRIX_SIZE; i++){
    for (j = 0; j < H_RMATRIX_SIZE; j++){
      fn_matrix_table[r_direction][k++] = m_tmp[i][j];
    }
  }

  return *this;

}
 
HRMatrix& HRMatrix::inverse()
{
  return transpose();
}
     
  
/*=================================================
**HRVector implementation
*/

HRVector::HRVector(const Point& pos)
:vector<double>(4,1.0)
{
  (*this)[0] = pos.getX();
  (*this)[1] = pos.getY();
  (*this)[2] = pos.getZ();
}

vector<double> operator * (const HRVector& v1,const TMatrix<double>& m1)
{
  vector<double> v_tmp(4);
  double entry;
  int i,j;

  if (m1.rows() != v1.size()){
    cout << "HRVector multiplication with TMatrix<double>: error in matrix dimension\n";
    cout << "aborting\n";
    exit(-1);
  }

  //run through the columns of the matrix
  //compute each entry by summing up the result of
  //the multiplications of element in j:th row and j:th vector element
  for (i = 0; i < m1.cols(); i++){
    entry = 0.0;
    for (j = 0; j < m1.rows(); j++){
      entry = entry + (m1[j][i] * v1[j]);
    }
    v_tmp[i] = entry;
  }

  return v_tmp;
}

}//closing oldadt



  







