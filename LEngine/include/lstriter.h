
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
  ModuleIdType GetModuleId() const;
  const char* GetCurrentModuleName() const;
  int CurrentPosition() const
  { return _currentPos; }
  int GetEndPosition()const{
    return _lstring._lastByte;
  }
  void SetEndPosition(int position){
    const_cast<Lstring&>(_lstring)._lastByte = position;
  }
  //This is intended to be used when deleting dead branches. 
  void prune(int from, int size_to_move);
  void operator++(int);
  void operator--(int);
  void operator+=(int);
  bool FindEOB(); // Find end-of-branch
  bool FindBOB(); // Find beginning-of-branch
  const char* Ptr() const;
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



#include <lstriterI.h>
