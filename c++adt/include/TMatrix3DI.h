#ifndef MATRIX3DI_H
#define MATRIX3DI_H


namespace cxxadt{

  template <class T>
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
      fill(begin(),end(),vector<T>(y,t));
      return *this;
    }
  
  template <class T>
    TMatrix2D<T>& TMatrix2D<T>::resize(int x, int y)
    {
      clear();
      resize(x,vector<T>(y));
      xd = x;
      yd = y;
      return *this;
    }
  
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
      fill(begin(),end(),TMatrix2D<T>(yd,zd,t));
      return *this;
    }

  template <class T>
    TMatrix3D<T>& TMatrix3D<T>::resize(int x, int y, int z)
    {
      clear();
      vector<TMatrix2D<T> >::resize(x,TMatrix2D<T>(y,z));
      xd = x;
      yd = y;
      zd = z;
      return *this;
    }
 
}   
#endif
