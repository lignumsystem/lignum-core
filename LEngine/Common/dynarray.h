#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

template<class T>
class DynArray
{
public: 
  DynArray(int n)
  {
    assert(n>0);
    _size = n;
    _arr = new T[_size];
    _items = 0;
  }
  virtual ~DynArray()
  {
    delete []_arr;
  }
  int Count() const
  { return _items; }
  T& operator[](int i)
  {
    assert(i>=0);
    assert(i<_items);
    return _arr[i];
  }
  const T& operator[](int i) const
  {
    assert(i>=0);
    assert(i<_items);
    return _arr[i];
  }
  int Add(const T& item)
  {
    if (_size == _items)
      _Grow();
    _arr[_items] = item;
    return _items++;
  }
protected:
  T* _arr;
  int _size;
  int _items;
  void _Grow()
  {
    T* pNew = new T[_size*2];
    _size *= 2;
    for (int i=0; i<_items; i++)
      pNew[i] = _arr[i];
    delete []_arr;
    _arr = pNew;
  }
};

#else
  #error File already included
#endif

