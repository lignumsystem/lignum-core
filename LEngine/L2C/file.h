#ifndef __FILE_H__
#define __FILE_H__

class ReadTextFile
{
public:
	ReadTextFile(const char* fn)
	{
		_fp = fopen(fn, "r");
		if (NULL == _fp)
			throw "Cannot open file for reading";
	}
	~ReadTextFile()
	{
		fclose(_fp);
	}
	FILE* Fp()
	{ return _fp; }
private:
	FILE* _fp;
};

class WriteTextFile
{
public:
	WriteTextFile(const char* fn)
	{
		_fp = fopen(fn, "w");
		if (NULL == _fp)
			throw "Cannot open file for writing";
	}
	~WriteTextFile()
	{
		fclose(_fp);
	}
	FILE* Fp()
	{ return _fp; }
private:
	FILE* _fp;
};

#else
	#error File already included
#endif
