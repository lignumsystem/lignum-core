
inline Lstring::Lstring()
{
  _mem = (char*) malloc(eInitSize);
  if (NULL == _mem)
    throw "Out of memory";
  _size = eInitSize;
  _lastByte = 0;
  _direction = eForward;
}

inline Lstring::~Lstring()
{
  free(_mem);
}


inline void Lstring::Clear(DerivationDirection dir)
{
  _direction = dir;
  if (eForward == _direction)
    _lastByte = 0;
  else
    _lastByte = _size;
}

inline void Lstring::_Grow()
{
  cout << "Reallocating string\n";
  int newsize = _size * 2;
  char* aNew = (char*) realloc(_mem, newsize);
  if (NULL == aNew)
    throw "Out of memory\n";
  _mem = aNew;
  if (eBackward == _direction)
  {
    int SizeToMove = _size - _lastByte;
    int TargetOffset = newsize - SizeToMove;
    int SourceOffset = _lastByte;
    memmove(_mem+TargetOffset, _mem+SourceOffset, SizeToMove);
    _lastByte += TargetOffset - SourceOffset;
  }
  _size = newsize;
}


inline void Lstring::_Append(const SuccessorStorage& storage)
{
  while (_size - _lastByte < storage.Size())
    _Grow();
  memcpy(_mem+_lastByte, storage.Bf(), storage.Size());
  _lastByte += storage.Size();
  assert(_lastByte<=_size);
}

inline void Lstring::_Prepend(const SuccessorStorage& storage)
{
  while (_lastByte - storage.Size() < 0)
    _Grow();
  _lastByte -= storage.Size();
  memcpy(_mem+_lastByte, storage.Bf(), storage.Size());
  assert(_lastByte>=0);
}


inline void Lstring::Add(SuccessorStorage& storage)
{
  if (eForward == _direction)
    _Append(storage);
  else
    _Prepend(storage);
  storage.Clear();
}

inline int Lstring::BytesUsed() const
{
  if (eForward == _direction)
    return _lastByte;
  else
    return _size - _lastByte;
}


inline void Lstring::DumpInfo() const
{
  cout << "Allocated size: " << _size << endl;
  cout << "Bytes used: " << BytesUsed() << endl;
}



inline void Lstring::Swap(Lstring& swp)
{
  {
    char* tmp = _mem;
    _mem = swp._mem;
    swp._mem = tmp;
  }

  {
    int tmp = _size;
    _size = swp._size;
    swp._size = tmp;
  }

  {
    int tmp = _lastByte;
    _lastByte = swp._lastByte;
    swp._lastByte = tmp;
  }

  {
    DerivationDirection tmp = _direction;
    _direction = swp._direction;
    swp._direction = tmp;
  }
}

