
inline SuccessorStorage::SuccessorStorage()
{
  _mem = (char*) malloc(eInitSize);
  _size = eInitSize;
  _appendPos = 0;
}

inline SuccessorStorage::~SuccessorStorage()
{
  free(_mem);
}

inline void SuccessorStorage::_Grow(int requestedSize)
{
  int newsize = 2*_size;
  while (newsize<requestedSize)
    newsize *= 2;
  char* pNew = (char*) realloc(_mem, newsize);
  if (NULL == pNew)
    throw "Out of memory";
  _size = newsize;
  _mem = pNew;
}

inline void SuccessorStorage::_Add(const void* pX, int sz)
{
  if (_appendPos + sz > _size)
    _Grow(_appendPos + sz);

  memcpy(_mem+_appendPos, pX, sz);
  _appendPos += sz;
}

inline void SuccessorStorage::Add(const void* pX, int size)
{ 
  _Add(pX, size); 
}

template <class T>void Append(T t)
{ 
  _Add(&t, sizeof(T)); 
}


