///\example{lineno} TMatrixExample.cc
/// This program  demonstrates the use  of TMatrix2D, TMatrix3D,
/// TMatrix4D and  TMatrix5D classes.
/// To compile the program  type:
///
///`c++ -DMATRIX_MAIN -g -I../include  TMatrixExample.cc -o matrix`
///
/// in the command line. The program creates  matrices and prints out
/// there contents.
#include <iostream>
#include <TMatrix3D.h>
#include <TMatrixN.h>
using namespace std;
using namespace cxxadt;
#ifdef MATRIX_MAIN
int main() {
  vector<double> v1(5,0);
  vector<double> v2(v1);
  vector<double> v3(4,1);
  TMatrix2D<double> m2(3,5);
  TMatrix3D<double> m3(2,4,5);
  for (int i=0,j=10; i < v1.size(); i++,j++){
    v1[i] = j;
    v2[i] = j+1;
  }
  
  for (int i = 0; i < m2.rows(); i++){
    for (int j = 0; j < m2.cols(); j++){
      m2[i][j] = i+j;
    }
  }
  
  cout << "Testing TMatrix2D(3,5)" <<endl;

  for (int i = 0; i < m2.rows(); i++){
    for (int j = 0; j < m2.cols(); j++){
      cout << m2[i][j] << " " << flush;
    }
    cout << endl;
  }

  cout << "Appending row" << endl;
  
  m2.append(v1);
  for (int i = 0; i < m2.rows(); i++){
    for (int j = 0; j < m2.cols(); j++){
      cout << m2[i][j] << " " << flush;
    }
    cout << endl;
  }

  cout << "Appending row" << endl;

  m2.append(v2);
  for (int i = 0; i < m2.rows(); i++){
    for (int j = 0; j < m2.cols(); j++){
      cout << m2[i][j] << " " << flush;
    }
    cout << endl;
  }
  
  cout << "Testing exception" << endl;

  try{
    m2.append(v3);
  }
  catch (const AppendException& e){
    cout << e.what() << endl;
  }
  cout << "Testing TMatrix3D(2,4,5)" << endl;

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

  vector<int> v10{1,2,3,4,5,6,7,8,9,10};
  TMatrix2D<int> m2d25(2,5,v10);
  cout << "TMatrix2D(2,5,v10) from vector v10" <<endl;
  cout << "Rows: " << m2d25.rows() <<endl;
  cout << "Cols: " << m2d25.cols() <<endl;
  for (int i = 0; i < m2d25.rows(); i++){
    for (int j = 0; j < m2d25.cols(); j++){
      cout << m2d25[i][j] << " " << flush;
    }
    cout << endl;
  }

  vector<int> v30(30);
  for (int i = 0; i < 30; i++){
    v30[i] = i+1;
  }
  TMatrix3D<int> m3d253(2,5,3,v30);
  cout << "TMatrix3D(2,5,3,v30) from vector v30" <<endl;
  for (int i = 0; i < m3d253.rows(); i++){
    cout << "Row (submatrix): " <<  i << endl;
    for (int j = 0; j < m3d253.cols(); j++){
      cout << j << ": " << flush;
      for (int k = 0; k < m3d253.zdim(); k++){
	cout << m3d253[i][j][k] << " " << flush;
      }
      cout << endl;
    }
  }

  vector<int> v120(2*3*4*5);
  for (int i = 0; i < 2*3*4*5; i++){
    v120[i] = i+1;
  }
  TMatrix4D<int> m4d2345(2,3,4,5,v120);
  cout << "TMatrix4D(2,3,4,5,v120) from vector v120" <<endl;
  cout << "First two dimensions" << endl;
  for (int i = 0; i  < m4d2345.c(); i++){
    for (int j = 0; j <  m4d2345.d(); j++){
      cout << m4d2345[0][0][i][j] << " " << flush;
    }
    cout << endl;  
  }
  cout << "Last two dimemnsions" << endl;
  for (int i = 0; i  < m4d2345.c(); i++){
    for (int j = 0; j < m4d2345.d(); j++){
      cout << m4d2345[m4d2345.a()-1][m4d2345.b()-1][i][j] << " " << flush;
    }
    cout << endl;  
  }
  vector<int> v720(2*3*4*5*6);
  for (int i = 0; i < 2*3*4*5*6; i++){
    v720[i] = i+1;
  }
  TMatrix5D<int> m5d23456(2,3,4,5,6,v720);
  cout << "TMatrix5D(2,3,4,5,6,v120) from vector v720" << endl;
  cout << "First matrix" << endl;
  for (int i = 0; i  < m5d23456.d(); i++){
    for (int j = 0; j <  m5d23456.e(); j++){
      cout << m5d23456[0][0][0][i][j] << " " << flush;
    }
    cout << endl;  
  }
  cout << "Second matrix" <<endl;
  for (int i = 0; i  < m5d23456.d(); i++){
    for (int j = 0; j <  m5d23456.e(); j++){
      cout << m5d23456[0][0][1][i][j] << " " << flush;
    }
    cout << endl;  
  }
  cout << "Second last matrix " << endl;
  for (int i = 0; i  < m5d23456.d(); i++){
    for (int j = 0; j <  m5d23456.e(); j++){
      cout << m5d23456[m5d23456.a()-1][m5d23456.b()-1][m5d23456.c()-2][i][j] << " " << flush;
    }
    cout << endl;  
  }
  cout << "Last matrix" << endl;
  for (int i = 0; i  < m5d23456.d(); i++){
    for (int j = 0; j <  m5d23456.e(); j++){
      cout << m5d23456[m5d23456.a()-1][m5d23456.b()-1][m5d23456.c()-1][i][j] << " " << flush;
    }
    cout << endl;  
  }
  return 0;
}
#endif
