#ifndef __SUCCESSORSTORAGE_H__
#define __SUCCESSORSTORAGE_H__

class SuccessorStorage
{
public:
  SuccessorStorage();
  ~SuccessorStorage();
  void Clear()
  { _appendPos = 0; }
  template <class T>void Append(T t)
  { _Add(&t, sizeof(T)); }
  int Size() const
  { return _appendPos; }
  const char* Bf() const
  { return _mem; }
  void Add(const void* pX, int size)
  { _Add(pX, size); }
private:
  void _Add(const void*, int); 
  void _Grow(int);
  char* _mem;
  int _size;
  int _appendPos;
  enum
  { eInitSize = 4096 };
};

#else
  #error File already included
#endif

