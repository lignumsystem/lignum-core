#ifndef __SIMPLEARRAY_H__
#define __SIMPLEARRAY_H__


template <class T>
class SimpleArray
{
public:
  SimpleArray(int size) : _size(size)
  { 
    _arr = new T[_size];
    _items = 0;
  }
  ~SimpleArray()
  {
    delete []_arr;
  }
  T& operator[](int i) const
  {
    assert(i>=0);
    assert(i<_size);
    return _arr[i];
  }
  void Add(const T& src)
  {
    assert(_items<_size);
    _arr[_items] = src;
    _items++;
  }
  int Items() const
  { return _items; }
  void Clear()
  { _items = 0; }
private:
  int _size;
  int _items;
  T* _arr;
};


#else
  #error File already included
#endif

