#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream.h>


#include <lglobal.h>

#include <lsysintrfc.h>

#include "lstring.h"
#include "lstriter.h"
#include "succstor.h"

Lstring mainstring;
Lstring derivedstring;

SuccessorStorage succstrg;
FILE* fOut;

void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

void Derive();
void Draw(int);
ProdCaller FindIMatch(const LstringIterator&, CallerData&);

ProdCaller  ContextMatch(const LstringIterator& pos,CallerData& caller_data,int& prod);

ProdCaller TryIMatch
  (const LstringIterator&, CallerData&, const ProductionPrototype&);
bool Considered(ModuleIdType);

char outputpth[PATH_MAX+1];

int main(int argc, char** argv)
{
  if (2==argc)
    strcpy(outputpth, argv[1]);
  else
    outputpth[0] = 0;

  Start();
  mainstring.Add(succstrg);
  Draw(0);
  sleep(1);

  {
    cout << "Axiom:\n";
    LstringIterator iterator(mainstring);
    iterator.Dump();
    cout << "\n\n";
  }

  for (int i=0; i<DerivationLength(); i++)
  {
    Derive();
    Draw(i);
    sleep(1);
/*
    cout << "After " << i+1 << " step:\n";
    LstringIterator iterator(mainstring);
    iterator.Dump();
    cout << "\n\n";
*/
  }
  End();

  {
    cout << "Final string:\n";
    LstringIterator iterator(mainstring);
    iterator.Dump();
    cout << "\n\n";
  }

  {
    Draw(100);
  }

}


void Draw(int i)
{
  LstringIterator iterator(mainstring);
  fOut = fopen(outputpth[0] ? outputpth : "dump.txt", "w");
  while (!iterator.AtEnd())
  {
    CallerData cd;
    ProdCaller pCaller = FindIMatch(iterator, cd);
    if (NULL != pCaller)
      pCaller(&cd);
    iterator++;
  }
  fclose(fOut);
  char bf[128];
/*
  sprintf(bf, "cp %s str%03d", outputpth, i);
  system(bf);
*/
  //system("echo \"Input|String|text|Input from *\" | command_client 3000");
}

void Derive()
{
  StartEach();
  LstringIterator iterator(mainstring);
  derivedstring.Clear();

  while (!iterator.AtEnd())
  {
    CallerData cd;
    int i;
    //ProdCaller pCaller = FindMatch(iterator, cd);
    ProdCaller pCaller = ContextMatch(iterator, cd, i);
    if (NULL == pCaller)
    {
      iterator.AppendCurrent(succstrg);
      iterator++;
    }
    else
    {
      pCaller(&cd);
      iterator+=cd.Strct.Count();
    }
    derivedstring.Add(succstrg);
  }
  mainstring.Swap(derivedstring);
  EndEach();
}


ProdCaller FindIMatch(const LstringIterator& citer, CallerData& cd)
{
  for (int i=0; i<NumOfIProductions(); i++)
  {
    ProdCaller res = TryIMatch(citer, cd, GetIProductionPrototype(i));
    if (NULL != res)
      return res;
  }
  return NULL;
}

ProdCaller TryIMatch
  (
  const LstringIterator& citer,
  CallerData& cd,
  const ProductionPrototype& proto
  )
{
  assert(proto.Strct.count==1);
  assert(proto.LCntxt.count==0);
  assert(proto.RCntxt.count==0);
  if (citer.GetModuleId() == proto.Strct.arr[0])
  {
    cd.Strct.AddModuleAddr(citer.Ptr());
    return proto.pCaller;
  }
  else
    return NULL;
}


