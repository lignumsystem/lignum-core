#ifndef TMATRIX_H
#define TMATRIX_H
#include <stream.h>
#include <vector>

namespace cxxadt{

using namespace std;

template <class T> class TMatrix;

template <class T>
TMatrix<T> operator + (const TMatrix<T>& m1,const TMatrix<T>& m2);
template <class T>
TMatrix<T> operator * (const TMatrix<T>& m1,const TMatrix<T>& m2);
template <class T>
TMatrix<T> operator * (const T scalar,const TMatrix<T>& m1);
template <class T>
TMatrix<T> operator * (const T scalar,const TMatrix<T>& m1);
template <class T>
ostream& operator << (ostream& os, const TMatrix<T>& v1);


template <class T> class TMatrix {
  friend TMatrix<T> operator + (const TMatrix<T>& m1,const TMatrix<T>& m2);
  friend TMatrix<T> operator * (const TMatrix<T>& m1,const TMatrix<T>& m2);
  friend vector<T> operator * (const vector<T>& v1, const TMatrix<T>& m1);
  friend vector<T> operator * (const TMatrix<T>& m1, const vector<T>& v1);
  friend TMatrix<T> operator * (const TMatrix<T>& m1,const T scalar);
  friend TMatrix<T> operator * (const T scalar,const TMatrix<T>& m1);
  friend ostream& operator << (ostream& os, const TMatrix<T>& v1);
public:
  TMatrix();    
  TMatrix(const int rows,const int cols);
  TMatrix(const TMatrix<T>& m);
  ~TMatrix();
  TMatrix<T>& operator = (const TMatrix<T>& m);
  T* operator[](int row)const;
  TMatrix<T>& operator -();
  TMatrix<T> transpose()const;
  int rows() const {return n_of_rows;}
  int cols() const {return n_of_cols;}
  void resize( const int rows, const int cols);  //This destroys the existing contents
private:
  T* matrix_table;
  int n_of_rows;
  int n_of_cols;
};

}//closing namespace cxxadt

#include <TMatrixI.h>

#endif











