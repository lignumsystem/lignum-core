#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lglobal.h>

#include <lsysintrfc.h>

const char* GetModuleName(int mid)
{
  assert(mid>=0);
  assert(mid<NumOfModules());
  const ModuleData* pMData = GetModuleData(mid);
  return pMData->Name;
}

int GetSizeOf(int mid)
{
  assert(mid>=0);
  assert(mid<NumOfModules());
  const ModuleData* pMData = GetModuleData(mid);
  return pMData->size;
}


ActualParameters::ActualParameters()
{
  _count = 0;
}


const char* ActualParameters::pArg(int i) const
{
  assert(i>=0);
  assert(i<Count());
  assert(_arr[i] != NULL);
  return _arr[i]+sizeof(ModuleIdType);
}

void ActualParameters::AddModuleAddr(const char* pX)
{
  assert(_count<eMaxFormalModules);
  _arr[_count] = pX;
  _count++;
}

void ActualParameters::Reset()
{
  _count = 0;
}

void CallerData::Reset()
{
  LCntxt.Reset();
  Strct.Reset();
  RCntxt.Reset();
}

