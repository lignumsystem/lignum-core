#include <assert.h>

#include <lglobal.h>
#include "dummies.h"

struct SimpleModuleData
{
  char Name[32];
  int size;
};


static const SimpleModuleData ModuleDecls[] =
{
  { "A", 0 },
  { "B", sizeof(int) + sizeof(float) },
  { "C", 0 },
  { "D", sizeof(int) + sizeof(int) },
  { "E", 0 },
  { "F", 0 },
  { "G", 0 },
  { "H", 0 },
  { "I", sizeof(int) },
  { "J", 0 },
  { "K", 0 },
  { "L", 0 },
  { "LBRCT", 0 },
  { "RBRCT", 0 }
};

const char* GetModuleName(ModuleIdType mid)
{
  int n = mid;
  assert(n>=0);
  assert(n<CountOf(ModuleDecls));
  return ModuleDecls[n].Name;
}

int GetSizeOf(ModuleIdType mid)
{
  int n = mid;
  assert(n>=0);
  assert(n<CountOf(ModuleDecls));
  return ModuleDecls[n].size;
}

