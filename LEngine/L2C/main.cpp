
#include "warningset.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lglobal.h>

#include "module.h"
#include "file.h"

extern int lparse();
extern FILE* lin;
FILE* fOut = NULL;

extern int ldebug;
extern bool first_time;

void InitDefault();
void BuildCallers();
void BuildICallers();
void BuildProdProtos();
void BuildIProdProtos();
void BuildModuleSize();
void GenerateFixed();
void GenerateCloseNamespace();

/*
#ifdef WIN32
const char platoptions[] = "/E /D_WIN32 /I\\progra~1\\devstudio\\vc\\include";
#endif
#ifdef IRIX
const char platoptions[] = "-E -I../lsys -I../Globals";
#endif
#ifdef IRIX64
const char platoptions[] = "-E -I../lsys -I../Globals";
#else //Linux
const char platoptions[] = "-E -I../lsys -I../Globals";
#endif
*/


int main(int argc, char** argv)
{
	//ldebug = 1;
	if ((argc != 2) && (argc != 3))
		return -1;
/*
	char bf[256];
#ifdef WIN32
	sprintf(bf, "copy %s input.cpp", argv[1]);
	system(bf);
	sprintf(bf, "cl %s %s > test.i", platoptions, "input.cpp");
#elif defined IRIX64
	sprintf(bf, "cp %s input.cpp", argv[1]);
	system(bf);
	sprintf(bf, "CC %s %s > test.i", platoptions, argv[1]);
#elif defined IRIX
	sprintf(bf, "cp %s test.cpp", argv[1]);
	system(bf);
	sprintf(bf, "CC %s %s > test.i", platoptions, "test.cpp");
#else //Linux
        sprintf(bf, "cp %s test.cpp", argv[1]);
	system(bf);
	sprintf(bf, "g++ %s %s > test.i", platoptions, "test.cpp");
#endif
	system(bf);
*/
	try
	{
		ReadTextFile src(argv[1]);
		WriteTextFile trg((argc==3) ? argv[2] : "lsys.i");
		lin = src.Fp();
		fOut = trg.Fp();
		first_time = true;
		InitDefault();
		lparse();
		BuildCallers();
		BuildICallers();
		BuildProdProtos();
		BuildIProdProtos();
		BuildModuleSize();
		GenerateFixed();
                GenerateCloseNamespace();
		fOut = NULL;
		fprintf(stderr, "%s parsed. OK\n", argv[1]);
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
	static char aux[1025];
	static char msg[1025];
	va_list args;
	va_start(args, fmt);
	vsprintf(aux, fmt, args);
	va_end(args);
	sprintf(msg, "Error: %s in %s line %d. Current token: %s\n", aux, FileName, lineno, ltext);
	throw msg;
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

