#include <assert.h>
#include <stdio.h>

#include <iostream.h>

#include <lglobal.h>

#include <lsysintrfc.h>

#include "lstring.h"
#include "lstriter.h"
#include "succstor.h"

LstringIterator::LstringIterator(const Lstring& lstring) : 
_lstring(lstring),
_mem(_lstring._mem)
{
  Reset();
}


LstringIterator::LstringIterator(const LstringIterator& citer) :
_lstring(citer._lstring),
_mem(citer._mem),
_currentPos(citer._currentPos),
_CurrentModuleId(citer._CurrentModuleId)
{}

void LstringIterator::Info() const
{
  cout << _lstring.AllocatedSize() << " bytes allocated\n";
  cout << _lstring.BytesUsed() << " bytes used\n";
}


void LstringIterator::Dump()
{
  while (!AtEnd())
  {
    ModuleIdType mid = GetModuleId();
    cout << GetModuleName(mid) << ' ';
    (*this)++;
  }
  cout << endl;
}

/*********************************************
 *Return the name (i.e. string) of the module*
 *********************************************/
const char* LstringIterator::GetCurrentModuleName()const
{
  ModuleIdType mid = GetModuleId();
  return  GetModuleName(mid);
}

void LstringIterator::Reset()
{
  if (eForward == _lstring._direction)
    _currentPos = 0;
  else
    _currentPos = _lstring._lastByte;

  if (!AtEnd())
    _RetrieveModuleId();
}

void LstringIterator::operator++(int)
{
  assert(!AtEnd());
  int Size = GetSizeOf(_CurrentModuleId);

  if (Size>0)
    _currentPos += 2*sizeof(ModuleIdType) + Size;
  else
    _currentPos += sizeof(ModuleIdType);

  assert
    (
    (eForward == _lstring._direction) && (_currentPos<=_lstring._lastByte) ||
    (eBackward == _lstring._direction) && (_currentPos<=_lstring._size)
    );

  if (!AtEnd())
    _RetrieveModuleId();
}


void LstringIterator::operator--(int)
{
  assert(!AtBeginning());
  _currentPos -= sizeof(ModuleIdType);
  _RetrieveModuleId();
  int Size = GetSizeOf(_CurrentModuleId);
  if (Size>0)
    _currentPos -= Size + sizeof(ModuleIdType);
  assert
    (
    (eForward == _lstring._direction) && (_currentPos>=0) ||
    (eBackward == _lstring._direction) && (_currentPos>=_lstring._lastByte)
    );
}

void LstringIterator::operator+=(int n)
{
  assert(n>0);
  for (int i=0; i<n; i++)
    (*this)++;
}

void LstringIterator::_RetrieveModuleId()
{
  assert(!AtEnd());
  memcpy(&_CurrentModuleId, _mem+_currentPos, sizeof(ModuleIdType));
}


bool LstringIterator::AtEnd() const
{
  if (eForward == _lstring._direction)
  {
    assert(_currentPos<=_lstring._lastByte);
    return _lstring._lastByte==_currentPos;
  } 
  else
  {
    assert(_currentPos<=_lstring._size);
    return _currentPos == _lstring._size;
  }
}


bool LstringIterator::AtBeginning() const
{
  if (eForward == _lstring._direction)
  {
    assert(_currentPos>=0);
    return 0==_currentPos;
  }
  else
  {
    assert(_currentPos>=_lstring._lastByte);
    return _currentPos == _lstring._lastByte;
  }
}

void LstringIterator::AppendCurrent(SuccessorStorage& storage) const
{
  assert(!AtEnd());
  int size = GetSizeOf(GetModuleId());
  if (0 == size)
    storage.Add((const void*)(_mem+_currentPos), (int)sizeof(ModuleIdType));
  else
    storage.Add(_mem+_currentPos, 2*sizeof(ModuleIdType)+size);
}


bool LstringIterator::FindEOB()
{
  int nested = 1;
  while (!AtEnd())
  {
    (*this)++;
    if (SB_id == GetModuleId())
      nested++;
    else if (EB_id == GetModuleId())
    {
      nested--;
      if (0==nested)
        return true;
    }
  }
  return false;
}


bool LstringIterator::FindBOB()
{
  int nested = 1;
  while (!AtBeginning())
  {
    (*this)--;
    if (SB_id == GetModuleId())
    {
      nested--;
      if (0==nested)
        return true;
    }
    else if (EB_id == GetModuleId())
      nested++;
  }
  return false;
}



void LIteratorReset::Reset()
{
  _iter._currentPos = _resetPos;
  if (!_iter.AtEnd())
    _iter._RetrieveModuleId();
}

