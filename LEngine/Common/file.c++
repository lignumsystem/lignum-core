#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "bool.h"
#include "exception.h"
#include "file.h"

void WriteTextFile::PrintF(const char* format, ...)
{
  assert(Valid());
  va_list args;
  va_start(args, format);
  vfprintf(_fp, format, args);
  va_end(args);
}


