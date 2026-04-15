#ifndef TMATRIXN_H
#define TMATRIXN_H
#include <TMatrix3D.h>
/// \file TMatrixN.h
/// \brief Collection of N dimensional matrices
///
/// N dimensional matrices (> 3) are also known for example
/// as multidimensional arrays, hypercubes and tensors depending
/// on the application.

namespace cxxadt{
  ///\brief 4D matrix with rows, columns, layers and blocks.
  ///
  ///Dimension naming commonly based on data structure they represent.
  template <class T>
  class TMatrix4D: public vector<TMatrix3D<T>>{
  public:
    ///\brief Constructor, empty 4D matrix
    TMatrix4D():a_dim(0),b_dim(0),c_dim(0),d_dim(0){};
    ///\brief Constructor, matrix dimensions only
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    TMatrix4D(int a, int b, int c, int d)
      :vector<TMatrix3D<T> >(a,TMatrix3D<T>(b,c,d)),
       a_dim(a),b_dim(b),c_dim(c),d_dim(d){};
    ///\brief Constructor, initialize matrix with copies of 't'
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    ///\param t Matrix element
    TMatrix4D(int a, int b, int c, int d, const T& t)
      :vector<TMatrix3D<T>>(a,TMatrix3D<T>(b,c,d,t)),
       a_dim(a),b_dim(b),c_dim(c),d_dim(d){}
    ///\brief Constructor, intialize with vector \p v
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    ///\param v Vector
    ///\pre \f$ a \times b \times c \times d  = |v|\f$
    ///\exception TMatrixInitSizeError if preconditon violation
    TMatrix4D(int a, int b, int c, int d, const vector<T>& v);
    ///\name Matrix dimensions
    ///The four matrix dimensions
    ///@{
    ///\brief 1st dimension
    ///\retval a
    int a()const {return a_dim;}
    ///\brief 2nd dimension
    ///\retval b
    int b()const {return b_dim;}
    ///\brief 3rd dimension
    ///\retval c
    int c()const {return c_dim;}
    ///\brief 4th dimension
    ///\retval d
    int d()const {return d_dim;}
    ///@}
    ///\brief Initialize with copies of \p t.
    ///\pre Matrix has dimensions defined
    ///\retval self Initialized matrix
    TMatrix4D<T>& init(const T& t);
    ///\brief Resize matrix
    ///
    ///Previous data will be lost.
    ///\retval self Resized matrix
    ///\post Data undefined in the 4D array
    ///\sa TMarix4D::init
    TMatrix4D<T>& resize(int a, int b, int c, int d);
  private:
    int a_dim;///< 1st dimension, slices to 3D matrices 
    int b_dim;///< 2nd dimension, slices to 2D matrices
    int c_dim;///< 3rd dimension, rows in 2D matrices
    int d_dim;///< 4th dimension, columns in 2D matrices
  };

  ///\brief 5D matrix with rows, columns, layers, blocks and collections.
  ///
  ///Dimension naming commonly based on data structure they represent.
  template <class T>
  class TMatrix5D: public vector<TMatrix4D<T>>{
  public:
    ///\brief Constructor, empty 5D matrix
    TMatrix5D():a_dim(0),b_dim(0),c_dim(0),d_dim(0),e_dim(0){};
    ///\brief Constructor, matrix dimensions only
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    ///\param e 5th dimension
    TMatrix5D(int a, int b, int c, int d, int e)
      :vector<TMatrix4D<T>>(a,TMatrix4D<T>(b,c,d,e)),
       a_dim(a),b_dim(b),c_dim(c),d_dim(d),e_dim(e){};
    ///\brief Constructor, initialize matrix with copies of \p t
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    ///\param e 5th dimension
    ///\param t Matrix element
    TMatrix5D(int a, int b, int c, int d, int e, const T& t)
      :vector<TMatrix4D<T>>(a,TMatrix4D<T>(b,c,d,e,t)),
       a_dim(a),b_dim(b),c_dim(c),d_dim(d),e_dim(e){}
    ///\brief Constructor, initialize matrix with vector \p v
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    ///\param e 5th dimension
    ///\param v Vector
    ///\pre \f$ a \times b \times c \times d \times e  = |v|\f$
    ///\exception TMatrixInitSizeError if preconditon violation
    TMatrix5D(int a, int b, int c, int d, int e, const vector<T>& v);
    ///\name Matrix dimensions
    ///The five matrix dimensions
    ///@{
    ///\brief 1st dimension
    ///\retval a
    int a()const {return a_dim;}
    ///\brief 2nd dimension
    ///\retval b
    int b()const {return b_dim;}
    ///\brief 3rd dimension
    ///\retval c
    int c()const {return c_dim;}
    ///\brief 4th dimension
    ///\retval d
    int d()const {return d_dim;}
    ///\brief 5th dimension
    ///\retval e
    int e()const {return e_dim;}
    ///@}
    ///\brief Initialize with copies of \p t.
    ///\param t Matrix element  
    ///\pre Matrix has dimensions defined
    ///\retval self Initialized matrix
    TMatrix5D<T>& init(const T& t);
    ///\brief Resize matrix
    ///
    ///Previous data will be lost.
    ///\param a 1st dimension
    ///\param b 2nd dimension
    ///\param c 3rd dimension
    ///\param d 4th dimension
    ///\param e 5th dimension
    ///\retval self Resized matrix
    ///\post Data undefined in the 5D array
    ///\sa TMatrix5D::init()
    TMatrix5D<T>& resize(int a,int b,int c,int d,int e);
  private:
    int a_dim;///< 1st dimension, slices to 4D matrices 
    int b_dim;///< 2nd dimension, slices to 3D matrices
    int c_dim;///< 3rd dimension, slices to 2D matrices
    int d_dim;///< 4th dimension, rows in 2D matrices
    int e_dim;///< 5th dimension, columns in 2D matrices
  };

  template <class T>
  TMatrix4D<T>::TMatrix4D(int a, int b, int c, int d, const vector<T>& v)
    :vector<TMatrix3D<T>>(a,TMatrix3D<T>(b,c,d)),a_dim(a),b_dim(b),
     c_dim(c),d_dim(d)
  {
    //Check requested size matches vector length, other checks can follow
    if (a*b*c*d != v.size()){
      int s = v.size();
      vector<int> v1{a,b,c,d,s};
      throw TMatrixInitSizeError(v1);
    }
    //Short cut to data vector
    const T* data = v.data();
    for (int i = 0; i < a_dim; i++){
      for (int j = 0; j < b_dim; j++){
	for (int k = 0; k < c_dim; k++){
	  for (int l = 0; l < d_dim; l++){
	    (*this)[i][j][k][l] = data[i*b_dim*c_dim*d_dim + j*c_dim*d_dim + k*d_dim + l];
	  }
	}
      }
    }
  }
  
  template <class T>
  TMatrix4D<T>& TMatrix4D<T>::init(const T& t)
  {
    fill(vector<TMatrix3D<T>>::begin(),vector<TMatrix3D<T>>::end(),
	 TMatrix3D<T>(b_dim,c_dim,d_dim,t));
    return *this;
  }

  template <class T>
  TMatrix4D<T>& TMatrix4D<T>::resize(int a,int b,int c,int d)
  {
    vector<TMatrix3D<T>>::clear();
    vector<TMatrix3D<T>>::resize(a,TMatrix3D<T>(b,c,d));
    a_dim=a;b_dim=b;c_dim=c;d_dim=d;
    return *this;
  }

  template <class T>
  TMatrix5D<T>::TMatrix5D(int a, int b, int c, int d, int e, const vector<T>& v)
    :vector<TMatrix4D<T>>(a,TMatrix4D<T>(b,c,d,e)),a_dim(a),b_dim(b),
			  c_dim(c),d_dim(d),e_dim(e)
  {
    //Check requested size matches vector length, other checks can follow
    if (a*b*c*d*e != v.size()){
      int s = v.size();
      vector<int> v1{a,b,c,d,e,s};
      throw TMatrixInitSizeError(v1);
    }
    //Short cut to data vector
    const T* data = v.data();
    for (int i = 0; i < a_dim; i++){
      for (int j = 0; j < b_dim; j++){
	for (int k = 0; k < c_dim; k++){
	  for (int l = 0; l < d_dim; l++){
	    for (int m = 0; m < e_dim; m++){
	    (*this)[i][j][k][l][m] = data[i*b_dim*c_dim*d_dim*e_dim + j*c_dim*d_dim*e_dim + k*d_dim*e_dim + l*e_dim + m];
	    }
	  }
	}
      }
    }
  }
  
  template <class T>
  TMatrix5D<T>& TMatrix5D<T>::init(const T& t)
  {
    fill(vector<TMatrix4D<T>>::begin(),vector<TMatrix4D<T>>::end(),
	 TMatrix4D<T>(b_dim,c_dim,d_dim,e_dim,t));
    return *this;
  }

  template <class T>
  TMatrix5D<T>& TMatrix5D<T>::resize(int a,int b,int c,int d,int e)
  {
    vector<TMatrix4D<T>>::clear();
    vector<TMatrix4D<T>>::resize(a,TMatrix4D<T>(b,c,d,e));
    a_dim=a;b_dim=b;c_dim=c;d_dim=d;e_dim=e;
    return *this;
  }

  
}

#endif
