#include <iostream>
#include <TMatrix3D.h>

using namespace std;
using namespace cxxadt;

/**********************************************************************
 *This program  demonstrates the use  of TMatrix3D class.   To compile*
 *the program  type "CC -LANG:std -g -I../include  matrix3d.cc" on the*
 *command line (SGI).   The program creates 3 matrices  and prints out*
 *there contents. It also tests init() and resize() methods.          *
 *********************************************************************/
int main() {

  TMatrix3D<double> m3(2,4,5);

  for (int i = 0; i < m3.rows(); i++){
    for (int j = 0; j < m3.cols(); j++){
      for (int k = 0; k < m3.zdim(); k++){
	m3[i][j][k] = 100.0*(i+1) + 10.0*(j+1) + (k+1);
      }
    }
  }

  cout << "Matrix3D(2,4,5)" << endl;
  for (int i = 0; i < m3.rows(); i++){
    cout << "Row (submatrix): " <<  i << endl;
    for (int j = 0; j < m3.cols(); j++){
      cout << j << ": " << flush;
      for (int k = 0; k < m3.zdim(); k++){
	cout << m3[i][j][k] << " " << flush;
      }
      cout << endl;
    }
  }

  m3.resize(4,5,6);
  m3.init(6);
  cout << "Matrix3D(4,5,6)" << endl;
  for (int i = 0; i < m3.rows(); i++){
    cout << "Row (submatrix): " <<  i << endl;
    for (int j = 0; j < m3.cols(); j++){
      cout << j << ": " << flush;
      for (int k = 0; k < m3.zdim(); k++){
	cout << m3[i][j][k] << " " << flush;
      }
      cout << endl;
    }
  }
  
  for (int i = 0; i < m3.rows(); i++){
    for (int j = 0; j < m3.cols(); j++){
      for (int k = 0; k < m3.zdim(); k++){
	m3[i][j][k] = 100.0*(i+1) + 10.0*(j+1) + (k+1);
      }
    }
  }

  for (int i = 0; i < m3.rows(); i++){
    cout << "Row (submatrix): " <<  i << endl;
    for (int j = 0; j < m3.cols(); j++){
      cout << j << ": " << flush;
      for (int k = 0; k < m3.zdim(); k++){
	cout << m3[i][j][k] << " " << flush;
      }
      cout << endl;
    }
  }
  return 0;
}
