#ifndef __XARRAY_H__
#define __XARRAY_H__

template<class T>
class XArray
{
public:
  XArray(T* arr)
  { _arr = arr; }
  ~XArray()
  { delete []_arr; }
  operator T*()
  { return _arr; }
  T* Release()
  {
    T* aRes = _arr;
    _arr = NULL;
    return aRes;
  }
private:
  T* _arr;
};

#else
  #error File already included
#endif

