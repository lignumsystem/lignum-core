#include <RMatrix.h>

namespace cxxadt{

//======================================================
//RMatrix "Rotation matrix"
//
//
//Create a rotation matrix with given direction
//"direction" can be one of ROTATE_X,ROTATE_Y,ROTATE_Z
//======================================================
RMatrix::RMatrix(ROTATION direction)
{
  int i;
  //three rotation matrices for each axis (x,y, and z)
  static double  (*x_rot[])(RADIAN)= {fn_1,fn_0,fn_0,fn_0,cos,sin,fn_0,neg_sin,cos};
  static double  (*y_rot[])(RADIAN)= {cos,fn_0,neg_sin,fn_0,fn_1,fn_0,sin,fn_0,cos};
  static double  (*z_rot[])(RADIAN)= {cos,sin,fn_0,neg_sin,cos,fn_0,fn_0,fn_0,fn_1}; 
 
  //given status will tell which of the matrices will be used
  r_direction = direction;

  for (i = 0; i < RMATRIX_SIZE*RMATRIX_SIZE; i++)
      fn_matrix_table[0][i] = x_rot[i];
  
  for (i = 0; i < RMATRIX_SIZE*RMATRIX_SIZE; i++)
    fn_matrix_table[1][i] = y_rot[i]; 
  
  for (i = 0; i < RMATRIX_SIZE*RMATRIX_SIZE; i++)
    fn_matrix_table[2][i] = z_rot[i]; 

}

//operator (): Apply functions of the rotation matrix
//to given angle in radians. Return FMatrix<RADIAN>
//which in turn can be applied to some
//coordinate vector/matrix in transformation/rotation
TMatrix<double> RMatrix::operator()(RADIAN angle)const
{
  int i,j,k;
  TMatrix<double> m_tmp(RMATRIX_SIZE,RMATRIX_SIZE);
  
  //this one is a little bit complicated
  //but basically this is done:
  //1.index the matrix of functions according the "r_direction"
  //2.then in the matrix of functions index the right column with "k"
  //3.finally apply the function to "angle"
  //4.insert the result in resulting transformation matrix 
  //be sure that the argument is "double" to sin and cos functions
  k = 0;
  for (i = 0; i < RMATRIX_SIZE; i++){
    for(j = 0; j < RMATRIX_SIZE; j++){
      (m_tmp[i])[j] = 
	(double)(*(fn_matrix_table[r_direction][k++]))((double)angle);
    }
  }
  
  return m_tmp;
}

//Change the rotation direction
//"direction" can be one of ROTATE_X,ROTATE_Y,ROTATE_Z
RMatrix& RMatrix::changeAxis(ROTATION direction)
{
  r_direction = direction;
  return *this;
}

//Transpose the rotation matrix 
//to undo previous rotations
RMatrix& RMatrix::transpose()
{
  static double (*m_tmp[RMATRIX_SIZE][RMATRIX_SIZE])(RADIAN);
  int i,j,k;
  
  k = 0;
  for (i = 0; i < RMATRIX_SIZE; i++){
    for (j = 0; j < RMATRIX_SIZE; j++){
      m_tmp[j][i] =  fn_matrix_table[r_direction][k++];
    }
  }

  k = 0;
  for (i = 0; i < RMATRIX_SIZE; i++){
    for (j = 0; j < RMATRIX_SIZE; j++){
      fn_matrix_table[r_direction][k++] = m_tmp[i][j];
    }
  }

  return *this;
}

RMatrix& RMatrix::inverse()
{
  return transpose();
}

}//namespace cxxadt  

#ifdef RMATRIX

void print_matrix(TMatrix<double>& matrix)
{
  cout << matrix;
}


int main()
{
  TMatrix<double> m1(1,3);
  TMatrix<double> m2(1,3);
  RMatrix r1(ROTATE_Z);

  m2[0][0] = 0.0;
  m2[0][1] = 0.0;
  m2[0][2] = 1.0;

  cout << "Demonstrating rotations of vector (0,0,1)" << endl;
  cout << "in a right hand coordinate system:" << endl;
  cout << "z-axis is \"north\", x-axis is \"south\" and y-axis is \"east\" "
       << endl << endl;

  cout << "Rotation pi/2 round z-axis (should be (0,0,1))" << endl;
  m1 = m2*r1(PI_VALUE/2.0);
  cout << m1 << endl;

  cout << "Rotation pi/2 round y-axis (should be (1,0,0))" << endl;
  r1.changeAxis(ROTATE_Y);
  m1 = m2*r1(PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation -pi/2 back round y-axis (should be (0,0,1))" << endl;
  m1 = m1*r1(-PI_VALUE/2.0);
  cout << m1 << endl;

  cout << "Rotation -pi/2 round y-axis (should be (-1,0,0))" << endl;
  m1 = m2*r1(-PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation pi/2 back round y-axis (should be (0,0,1))" << endl;
  m1 = m1*r1(PI_VALUE/2.0);
  cout << m1 << endl;

  cout << "Rotation pi/2 round x-axis (should be (0,-1,0))" << endl;
  r1.changeAxis(ROTATE_X);
  m1 = m2*r1(PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation -pi/2 back round x-axis (should be (0,0,1))" << endl;
  m1 = m1*r1(-PI_VALUE/2.0);
  cout << m1 << endl;

  cout << "Rotation -pi/2 round x-axis (should be (0,1,0))" << endl;
  m1 = m2*r1(-PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation pi/2 back round x-axis (should be (0,0,1))" << endl;
  m1 = m1*r1(PI_VALUE/2.0);
  cout << m1 << endl;

  
  cout << "Rotation pi/2 round y-axis (should be (1,0,0))" << endl;
  r1.changeAxis(ROTATE_Y);
  m1 = m2*r1(PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation pi/2 round z-axis (should be (0,1,0))" << endl;
  r1.changeAxis(ROTATE_Z);
  m1 = m1*r1(PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation -pi/2 back round z-axis (should be (1,0,0))" << endl;
  m1 = m1*r1(-PI_VALUE/2.0);
  cout << m1;
  cout << "Rotation -pi/2 back round y-axis (should be (0,0,1))" << endl;
  r1.changeAxis(ROTATE_Y);
  m1 = m1*r1(-PI_VALUE/2.0);
  cout << m1 << endl;

  cout << "Starting (0,0,1), first rotate 3/4*pi round y-axis," << endl
       << "then 2*pi with pi/4 intervals round z axis," <<endl
       << "finally  -3/4*pi round y-axis should end with (0,0,1)" 
       << endl << endl; 
    
  cout << "Rotation 3/4*pi round y-axis" << endl;
  r1.changeAxis(ROTATE_Y);
  m1 = m2*r1(3.0/4.0*PI_VALUE);
  cout << m1 << endl;
  cout << "8 rotations pi/4 round z-axis" << endl;
  r1.changeAxis(ROTATE_Z);
  for (int i = 0; i < 8; i++){
     m1 = m1*r1(PI_VALUE/4.0);
     cout << m1;
  }
  cout << endl;
  cout << "Rotation  -3/4*pi round y-axis" << endl;
  r1.changeAxis(ROTATE_Y);
  m1  = m1*r1(-3.0/4.0*PI_VALUE);
  cout << m1;

}
#endif







