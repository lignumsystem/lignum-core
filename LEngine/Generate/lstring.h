#ifndef __LSTRING_H__
#define __LSTRING_H__


class SuccessorStorage;


class Lstring
{
friend class LstringIterator;

public:

  Lstring();
  ~Lstring();
  void Clear(DerivationDirection dir = eForward);
  void Add(SuccessorStorage&); // after adding clears the storage
  void DumpInfo() const;
  int AllocatedSize() const
  { return _size; }
  int BytesUsed() const;
  void Swap(Lstring&);
  DerivationDirection Direction() const
  { return _direction; }


private:
  void _Append(const SuccessorStorage&);
  void _Prepend(const SuccessorStorage&);
  char* _mem;
  enum
  { eInitSize = 10240 };
  int _size;
  int _lastByte;
  DerivationDirection _direction;
  void _Grow();
};


#else
  #error File already included
#endif

