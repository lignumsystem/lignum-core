#ifndef __DYNSTACK_H__
#define __DYNSTACK_H__

template<class T>
class DynStack
{
public:
  DynStack(int size) : _size(size), _top(0)
  {
    _arr = new T[_size];
  }
  ~DynStack()
  {
    delete []_arr;
  }
  bool IsEmpty() const
  { return 0 == _top; }
  void Push(const T& p)
  {
    if (_top == _size)
      _Grow();
    _arr[_top] = p;
    _top++;
  }
  void Pop(T& p)
  {
    assert(_top>0);
    _top--;
    p = _arr[_top];
  }
  void GetTop(T& p)
  { 
    assert(_top>0);
    p = _arr[_top-1];
  }

protected:
  T* _arr;
  int _size;
  int _top;
  void _Grow()
  { 
    T* aTmp = new T[_size*2];
    _size *= 2;
    for (int i=0; i<_top; i++)
      aTmp[i] = _arr[i];
    delete []_arr;
    _arr = aTmp;
  }
};


#else
  #error File already included
#endif

