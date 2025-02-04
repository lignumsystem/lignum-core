#include <iostream>
#include <TMatrix3D.h>
///\file matrix3d.cc
using namespace std;
using namespace cxxadt;
///\example{lineno} matrix3d.cc
///\brief This program  demonstrates the use  of TMatrix2D and TMatrix3D classes.
///To compile the program  type `c++ -DMATRIX3DMAIN -g -I../include  matrix3d.cc -o matrix3d` in the
///command line. The program creates TMatrix2D and TMatrix3D matrices  and prints out
///there contents.
#ifdef MATRIX3DMAIN
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
  return 0;
}
#endif
