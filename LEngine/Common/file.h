#ifndef __FILE_H__
#define __FILE_H__

class File
{
protected:
  File(const char* fname, const char* mode)
  {
    _fp = fopen(fname, mode);
  }
public:
  ~File()
  {
    if (NULL != _fp)
      fclose(_fp);
  }
  bool Valid() const
  { return NULL != _fp; }
  operator FILE*()
  { return _fp; }
  FILE* fp()
  { return _fp; }
protected:
  FILE* _fp;
};


class ReadTextFile : public File
{
public:
  ReadTextFile(const char* fname) : File(fname, "rt")
  {}
};


class WriteTextFile : public File
{
public:
  WriteTextFile(const char* fname) : File(fname, "wt")
  {}
  void PrintF(const char*, ...);
};


#else
  #error File already included
#endif

