#ifndef TMATRIX_H
#define TMATRIX_H
#include <iostream>
#include <vector>





#include <vector>
#include <iostream>



namespace cxxadt{

using namespace std;

template <class T> 
class TMatrix {

  friend TMatrix<T> operator + (const TMatrix<T>& m1,const TMatrix<T>& m2);

  friend TMatrix<T> operator * (const TMatrix<T>& m1,const TMatrix<T>& m2);  

  friend std::vector<T> operator * (const std::vector<T>& v1, const TMatrix<T>& m1);

  friend std::vector<T> operator * (const TMatrix<T>& m1, const std::vector<T>& v1);

  friend TMatrix<T> operator * (const TMatrix<T>& m1,const T scalar);

  friend TMatrix<T> operator * (const T scalar,const TMatrix<T>& m1);

  friend std::ostream& operator << (std::ostream& os, const TMatrix<T>& v1);
public:
  TMatrix();    
  TMatrix(const int rows, const int cols);
  TMatrix(const TMatrix<T>& m);
  ~TMatrix();
  TMatrix<T>& operator = (const TMatrix<T>& m);
  T* operator[](int row)const;
  TMatrix<T>& operator -();
  TMatrix<T> transpose()const;
  int rows() const {return n_of_rows;}
  int cols() const {return n_of_cols;}
  void resize( const int rows, const int cols);  //This destroys the existing content
 
  TMatrix<T>& unitize(); //makes diag(1 1 1 ... 1) matrix
  TMatrix<T>& zero(); //makes all elements = (T)0


  int n_of_rows;
  int n_of_cols;
private:
  T* matrix_table;
};



}//closing namespace cxxadt

#include <TMatrixI.h>

#endif











