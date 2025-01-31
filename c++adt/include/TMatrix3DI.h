#ifndef MATRIX3DI_H
#define MATRIX3DI_H


namespace cxxadt{
  
  template <class T>
  TMatrix2D<T>::TMatrix2D()
    :xd(0),yd(0){}
  template <class T>
  ///By inheritance the matrix is a vector of rows.
  ///Each row is a vector of elements 
  TMatrix2D<T>::TMatrix2D(int x, int y)
    :vector<vector<T> >(x,vector<T>(y)),xd(x),yd(y)
  {
  }
  
  template <class T>
    TMatrix2D<T>::TMatrix2D(int x, int y, const T& t)
    :vector<vector<T> >(x,vector<T>(y,t)),xd(x),yd(y)
    {
    }
  
  template <class T>
    TMatrix2D<T>& TMatrix2D<T>::init(const T& t)
    {
      fill(vector<vector<T> >::begin(),vector<vector<T> >::end(),
	   vector<T>(yd,t));
      return *this;
    }
  
  template <class T>
    TMatrix2D<T>& TMatrix2D<T>::resize(int x, int y)
    {
      vector<vector<T> >::clear();
      vector<vector<T> >::resize(x,vector<T>(y));
      xd = x;
      yd = y;
      return *this;
    }

  template <class T>
  TMatrix2D<T>& TMatrix2D<T>::append(const vector<T>& v){
    if (yd != 0 && v.size() != yd){
      throw(AppendException("AppendException: vector length differs from number of columns",xd,yd,v.size()));
    }
    vector<vector<T> >::push_back(v);
    xd = xd + 1;
    yd = v.size();
    return *this;
  }
    
  template <class T>
  TMatrix3D<T>::TMatrix3D()
    :xd(0),yd(0),zd(0){}
  template <class T>
    TMatrix3D<T>::TMatrix3D(int x, int y, int z)
    :vector<TMatrix2D<T> >(x,TMatrix2D<T>(y,z)),xd(x),yd(y),zd(z)
    {
    }
  
  template <class T>
    TMatrix3D<T>::TMatrix3D(int x, int y, int z,const T& t)
    :vector<TMatrix2D<T> >(x,TMatrix2D<T>(y,z,t)),xd(x),yd(y),zd(z)
    {
    }

  template <class T>
    TMatrix3D<T>& TMatrix3D<T>::init(const T& t)
    {
      fill(vector<TMatrix2D<T> >::begin(),vector<TMatrix2D<T> >::end(),
	   TMatrix2D<T>(yd,zd,t));
      return *this;
    }

  template <class T>
    TMatrix3D<T>& TMatrix3D<T>::resize(int x, int y, int z)
    {
      vector<TMatrix2D<T> >::clear();
      vector<TMatrix2D<T> >::resize(x,TMatrix2D<T>(y,z));
      xd = x;
      yd = y;
      zd = z;
      return *this;
    }
 
}   
#endif
