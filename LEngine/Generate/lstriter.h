#ifndef __LSTRINGITERATOR_H__
#define __LSTRINGITERATOR_H__
extern int GetSizeOf(int);
class Lstring;

class LstringIterator
{
friend class LIteratorReset;
public:
  LstringIterator(const Lstring&);
  LstringIterator(const LstringIterator&);
  void Info() const;
  void Dump();
  void Reset();
  bool AtEnd() const;
  bool AtBeginning() const;
  void AppendCurrent(SuccessorStorage&) const;
  ModuleIdType GetModuleId() const
  {
    assert(!AtEnd());
    return _CurrentModuleId;
  }
  const char* GetCurrentModuleName() const;
  int CurrentPosition() const
  { return _currentPos; }
  void operator++(int);
  void operator--(int);
  void operator+=(int);
  bool FindEOB(); // Find end-of-branch
  bool FindBOB(); // Find beginning-of-branch
  const char* Ptr() const
  {
/*
   In the debug version it will return NULL
   if the module has no parameters
*/
#ifndef NDEBUG
    if (GetSizeOf(GetModuleId())==0)
      return NULL;
    else
#endif
      return _mem+_currentPos;
  }

private:
  const Lstring& _lstring;
  const char* _mem;
  int _currentPos;
  ModuleIdType _CurrentModuleId;
  void _RetrieveModuleId();
};


class LIteratorReset
{
public:
  LIteratorReset(LstringIterator& iter) : _iter(iter)
  { _resetPos = _iter._currentPos; }
  void Reset();
private:
  LstringIterator& _iter;
  int _resetPos;
};



#else
  #error File already included
#endif

