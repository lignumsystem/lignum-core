#ifndef TMATRIXI_H
#define TMATRIXI_H


#include <stdlib.h>
#include <vector>
#include <iostream>

namespace cxxadt{

using namespace std;

template <class T> TMatrix<T>::TMatrix()
{
  matrix_table = new T[1];

  n_of_rows = 1;
  n_of_cols = 1;

  (&matrix_table[0])[0] = T();
}

template <class T> void TMatrix<T>::resize(const int rows, const int cols)
{
  //Free the existing space
  delete[] matrix_table;

  //Allocate memory again 
  int i = 0, j = 0;
  matrix_table = new T[rows*cols];

  n_of_rows = rows;
  n_of_cols = cols;

  for (i = 0; i <  n_of_rows; i++){
    for (j = 0; j < n_of_cols; j++){
      (&matrix_table[i*n_of_cols])[j] = T();
    }
  }
}


template <class T> TMatrix<T>::TMatrix(const int rows,const int cols)
{
  int i = 0, j = 0;
  matrix_table = new T[rows*cols];

  n_of_rows = rows;
  n_of_cols = cols;

  for (i = 0; i <  n_of_rows; i++){
    for (j = 0; j < n_of_cols; j++){
      (&matrix_table[i*n_of_cols])[j] = T();
    }
  }
}

template <class T> TMatrix<T>::TMatrix(const TMatrix<T>& m)
{
  int i = 0, j = 0;

  this->n_of_rows = m.n_of_rows;
  this->n_of_cols = m.n_of_cols;
  this->matrix_table =  new T[n_of_rows*n_of_cols];
  
  for (i = 0; i < n_of_rows; i++){
    for (j = 0; j < n_of_cols; j++){
      (&matrix_table[i*n_of_cols])[j] = (&m.matrix_table[i*n_of_cols])[j];
    }
  }

}

template <class T> TMatrix<T>::~TMatrix()
{
  delete [] matrix_table;
  n_of_rows = 0;
  n_of_cols = 0;
}


template <class T> TMatrix<T>& TMatrix<T>::operator = (const TMatrix<T>& m)
{
  int i = 0, j = 0;
  
  if ((m.n_of_rows != this->n_of_rows) || (m.n_of_cols != this->n_of_cols)){
    cerr << "TMatrix,T>& TMatrix<T>::operator = (const TMatrix<T>& m)\n"
	 << "Error in assignment; matrix m has wrong  size\n"
	 << "Aborting...\n";
    exit(-1);
  }
  
  for (i = 0; i < n_of_rows; i++){
    for (j = 0; j < n_of_cols; j++){
      (&matrix_table[i*n_of_cols])[j] = (&m.matrix_table[i*n_of_cols])[j];
    }
  }
  
  return *this;
  
}

template <class T> T* TMatrix<T>::operator[](int row)const
{
  if (row >= n_of_rows){
    cerr << "T* TMatrix<T>::operator[](int row)\n"
	 << "Indexing error" <<"row: "<<row<<"n_of_rows: "<<n_of_rows<<'\n'
         << "Aborting...\n";
  }

  return &matrix_table[row*n_of_cols];
}

template <class T> TMatrix<T>& TMatrix<T>::operator -()
{
  int i = 0, j= 0;
  
  for (i = 0; i < n_of_rows; i++){
    for (j = 0; j < n_of_cols; j++){
      (&matrix_table[i*n_of_cols])[j] = -(&matrix_table[i*n_of_cols])[j];
    }
  }
  
  return *this;
}

template <class T> TMatrix<T> TMatrix<T>::transpose()const
{
  int i = 0, j = 0;
  TMatrix<T> m_tmp(this->n_of_cols,this->n_of_rows);
  
  for (i = 0; i < this->n_of_rows; i++){
    for (j = 0; j < this->n_of_cols; j++){
      m_tmp[j][i] = (&matrix_table[i*n_of_cols])[j];
    }
  }
  
  return m_tmp;
}


template <class T> TMatrix<T> operator + (const TMatrix<T>& m1, 
					  const TMatrix<T>& m2)
{
  int i = 0, j = 0;
  TMatrix<T> m_tmp(m1.n_of_rows,m1.n_of_cols);

  if ((m1.n_of_rows != m2.n_of_rows) || (m1.n_of_cols != m2.n_of_cols)){
    cerr << "friend TMatrix<T>::operator +(const TMatrix<T>& m1,\n"
         << "                              const TMatrix<T>& m1) \n"
	 << "Error in addition; matrix m1,m2 of different  size\n"
	 << "Aborting...\n";
    exit(-1);
  }
  
  for (i = 0; i < m1.n_of_rows; i++){
    for (j = 0; j < m1.n_of_cols; j++){
      m_tmp[i][j] = m1[i][j] + m2[i][j];
    }
  }

  return m_tmp;
}

template <class T> TMatrix<T> operator * (const TMatrix<T>& m1, 
					  const TMatrix<T>& m2)
{
  int i = 0, j = 0, k = 0;
  T entry = T();
  
  TMatrix<T> m_tmp(m1.n_of_rows,m2.n_of_cols);

  
  if (m1.n_of_cols != m2.n_of_rows){
    cerr <<"friend TMatrix<T> operator * (const TMatrix<T>& m1,\n"
	 <<"                              const TMatrix<T>& m2)\n"
	 <<"Error in multiplication: m1.n_of_cols != m2.n_of_rows \n"
	 <<"Aborting....\n";
    exit(-1);
  }

  for (i = 0; i < m1.n_of_rows; i++){
    for (j = 0; j < m2.n_of_cols; j++){
      entry = T();
      for (k = 0; k < m1.n_of_cols; k++)
	entry = entry + (m1[i][k] * m2[k][j]);
      m_tmp[i][j] = entry;
    }
  }
  
  return m_tmp;
}

template <class T> 
std::vector<T> operator * (const std::vector<T>& v1, const TMatrix<T>& m1)
{
  vector<T> v_tmp(m1.cols());
  T entry = T();

  if (static_cast<int>(v1.size()) != (m1.rows())){
    cerr << "Error: vector*matrix" << endl;
    cerr << "v1.size() != m1.rows()" << endl;
    cerr << "Aborting ...." << endl;
    exit(-1);
  }

  for (int i = 0; i < static_cast<int>(v_tmp.size()); i++){
    entry = T();
    for (int k = 0; k < static_cast<int>(v1.size()); k++){
      entry += v1[k]*m1[k][i];
    }
    v_tmp[i] = entry;
  }

  return v_tmp;
}

template <class T> 
std::vector<T> operator * (const TMatrix<T>& m1, const std::vector<T>& v1)
{
  vector<T> v_tmp(m1.rows());
  T entry = T();

  if (m1.cols() != v1.size()){
    cerr << "Error: vector*matrix" << endl;
    cerr << "v1.size() != m1.cols()" << endl;
    cerr << "Aborting ...." << endl;
    exit(-1);
  }

  for (int i = 0; i < m1.rows(); i++){
    entry = T();
    for (int k = 0; k < m1.cols(); k++){
      entry += m1[i][k]*v1[k];
    }
    v_tmp[i] = entry;
  }

  return v_tmp;
}

template <class T> TMatrix<T> operator * (const TMatrix<T>& m1,
					  const T scalar)
{
  int i = 0, j = 0;
  
  TMatrix<T> m_tmp(m1);
  
  for (i = 0; i < m_tmp.n_of_rows; i++){
    for (j = 0; j< m_tmp.n_of_cols; j++){
      m_tmp[i][j] = m_tmp[i][j] * scalar;
    }
  }
  
  return m_tmp;
}


template <class T> TMatrix<T> operator * (const T scalar,
					  const TMatrix<T>& m1)
{
  return m1 * scalar;
}

template <class T>  std::ostream& operator << (std::ostream& os, const TMatrix<T>& m1)
{
  int i=0,j=0;

  for (i = 0; i < m1.rows();i++){
    for (j = 0; j < m1.cols(); j++){
      os << m1[i][j] << " ";
    }
    os << endl;
  }

  return os;
}

template <class T>  
std::ostream& operator << (std::ostream& os, const std::vector<T>& v1)
{
  for (size_t i = 0; i < v1.size(); i++){
    os << v1[i] << " ";
  }
  os << endl;

  return os;
}

//Make diagonal matrix (1 1 1 ... 1), if # of rows != # of cols,
//assigns 1's to max(# of rows, # of cols)
//Other elements are set equal to (T)0
template <class T>
TMatrix<T>& TMatrix<T>::unitize()
{
  int i=0, j = 0;

  for (i = 0; i < this->rows();i++){
    for (j = 0; j < this->cols(); j++){
      if(i == j)
	(&this->matrix_table[i*n_of_cols])[j]  = (T)1.0;
      else
	(&this->matrix_table[i*n_of_cols])[j] = (T)0.0;
    
    }
  }

  return *this;
}

//Set all elemets equal to (T)0
template <class T>
TMatrix<T>& TMatrix<T>::zero()
{
  int i=0, j = 0;

  for (i = 0; i < this->rows();i++){
    for (j = 0; j < this->cols(); j++){
	(&this->matrix_table[i*n_of_cols])[j]  = (T)0.0;
    }
  }

  return *this;
}



} //namespace cxxadt

#endif //TMATRIXI_H

#ifdef TMATRIX

int main()
{
  int i=0,j=0;
  double k = 0.0;
  TMatrix<double> m1(3,4);
  TMatrix<double> m2(4,3);
  TMatrix<double> m3(3,4);
  TMatrix<double> m4(3,3);
  TMatrix<double> m5(3,4);
  vector<double> v1(3);
  vector<double> v2(4);

  for (i = 0; i < v1.size(); i++)
    v1[i] = i + 1;
  for (i = 0; i < v2.size(); i++)
    v2[i] = i + 1;

  for (i = 0; i < m1.rows(); i++){
    for (j = 0; j < m1.cols(); j++){
      m1[i][j] = m3[i][j] = k++;
    }
  }

   for (i = 0; i < m2.rows(); i++){
    for (j = 0; j < m2.cols(); j++){
      m2[i][j] = m2[i][j] = k++;
    }
  }

  cout << "m1:" << endl << m1 << endl;
  cout << "m2:" << endl << m2 << endl;
  cout << "m3:" << endl << m3 << endl;

  m4 = m1 * m2;
  cout << "m4 = m1 * m2: " << endl;
  cout << m4 << endl;

  m3 = m3 * 2.0;
  cout << "m3 = m3 * 2:" << endl;
  cout << m3 << endl;

  m5 = m1 + m3;
  cout << "m5 = m1 + m3:" << endl;
  cout << m5 << endl;

  -m5;
  cout << "-m5:" << endl;
  cout << m5 << endl;
  

  cout << "m5 transpose " << endl;
  cout << m5.transpose() << endl;
   
  m4.resize(2,2);
  for(i = 0; i < m4.rows(); i++)
    for(j = 0; j < m4.cols(); j++)
      m4[i][j] = (double)(i+j);

  cout << "resized m4" << endl;
  cout << m4 << endl;

  cout << "v1*m1" << endl;
  cout << v1 << endl;
  cout << m1 << endl;
  v1 = v1 * m1;
  cout << v1 << endl;

  cout << "m1*v2" << endl;
  cout << m1 << endl;
  cout << v2 << endl;
  v2 = m1*v2;
  cout << v2 << endl;

  v2.unitize();
  cout << " unit matrix" << endl;
  cout << v2 << endl;

  v2.zero();
    cout << " zero matrix" << endl;
  cout << v2 << endl;

 return 0;
}

#endif 

  


