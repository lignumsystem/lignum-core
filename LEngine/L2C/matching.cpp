
#include "warningset.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lglobal.h>
#include <lsysintrfc.h>

#include "module.h"
#include "file.h"
#include "production.h"

#include <lstring.h>
#include <succstor.h>
#include <lstriter.h>


extern ProdCaller ContextMatch(const LstringIterator&,CallerData&, int& i);

extern ProductionTable productionTable;
extern int lparse();
extern FILE* lin;

FILE* fOut = NULL;

extern int ldebug;
extern bool first_time;

void BuildCallers();
void BuildProdProtos();

extern int GetSizeOf(void);

SuccessorStorage storage;

void _Add(const void* pX, int size)
{
  storage.Add(pX, size);
}  

int main(int argc, char** argv)
{

  Start();
  Lstring lstr;
  lstr.Clear();
  lstr.Add(storage);
  try
    {
      LstringIterator str_iter(lstr);
      str_iter.Dump();
      str_iter.Reset();
      while (!str_iter.AtEnd()){
	CallerData caller_data;
	int prod = 0;
	ContextMatch(str_iter,caller_data,prod);
	str_iter++;
      }
    }
  catch (const char* msg)
    {
      fprintf(stderr, msg);
    }
  return 0;
}

extern int lineno;
extern char *ltext;
extern char FileName[];

void lerror(const char* fmt, ...)
{
  static char msg[1025];
  va_list args;
  va_start(args, fmt);
  vsprintf(msg, fmt, args);
  va_end(args);
  fprintf(stderr, "Error: %s in %s line %d. Current token: %s\n", msg, FileName, lineno, ltext);
}

void lwarning(const char* fmt, ...)
{
  static char msg[1025];
  va_list args;
  va_start(args, fmt);
  vsprintf(msg, fmt, args);
  va_end(args);
  fprintf(stderr, "Warning/Info: %s in %s line %d. Current token: %s\n", msg, FileName, lineno, ltext);
}



void DumpOut(const char* bf)
{
  assert(NULL != fOut);
  fputs(bf, fOut);
}

