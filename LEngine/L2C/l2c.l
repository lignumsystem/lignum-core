%{

#include <assert.h>
#include <string.h>

#define YY_NEVER_INTERACTIVE 1

#include <lglobal.h>

#include "module.h"
#include "l2c_tab.h"

extern ModuleTable moduleTable;

extern "C" int lwrap()
{ return 1; }

int nested;
int lineno = 1;
bool first_time = true;
int BeforeString;
char FileName[
#ifdef WIN32
_MAX_PATH
#endif
#ifdef IRIX
PATH_MAX
#endif
+3];

void DumpOut(const char*);
void SetCurLine(const char* bf)
{
	sscanf(bf, "%d %s", &lineno, FileName);
	//fprintf(stderr, "Now at %s %d\n", FileName, lineno);
}


%}


%s NRMLSRC MODULE PRODPROTO PRODUCTION CONIGN STRING CHARACTER EXPRESSION

%%

%{
	if (first_time)
	{
		BEGIN NRMLSRC;
		nested = 0;
		first_time = false;
	}
%}


<NRMLSRC>"derivation length:" { BEGIN EXPRESSION; return tDERIVLENGTH; }
<NRMLSRC>"module" { BEGIN MODULE; return tMODULE; }
<NRMLSRC>"consider:" { BEGIN CONIGN; return tCONSIDER; }
<NRMLSRC>"ignore:" { BEGIN CONIGN; return tIGNORE; }
<NRMLSRC>"interpretation:" { return tINTERPRETATION; }
<NRMLSRC>"produce" {
	BEGIN PRODUCTION;
	nested = 0;
	return tPRODUCE;
	}
<NRMLSRC>"Start:" { return tSTART; }
<NRMLSRC>"StartEach:" { return tSTARTEACH; }
<NRMLSRC>"EndEach:" { return tENDEACH; }
<NRMLSRC>"End:" { return tEND; }
<NRMLSRC>[a-zA-Z_][0-9a-zA-Z_]* { 
	if (moduleTable.IsModuleIdent(ltext))
	{
	  strncpy(llval.Ident, ltext, eMaxIdentifierLength); 
	  llval.Ident[eMaxIdentifierLength] = 0;
	  BEGIN PRODPROTO;
	  return tMODULEIDENT;
	} 
	else
	  DumpOut(ltext);
	}

<CONIGN>[a-zA-Z_][0-9a-zA-Z_]* {
	if (moduleTable.IsModuleIdent(ltext))
	{
		strncpy(llval.Ident, ltext, eMaxIdentifierLength);
		llval.Ident[eMaxIdentifierLength] = 0;
		return tMODULEIDENT;
	}
	else
		return tERROR;
	}
<CONIGN>";" { BEGIN NRMLSRC; return tSEMICOLON; }


<MODULE>"(" { return tLPAREN; }
<MODULE>")" { return tRPAREN; }
<MODULE>"," { return tCOMMA; }
<MODULE>";" { BEGIN NRMLSRC; return tSEMICOLON; }
<MODULE>[a-zA-Z_][0-9a-zA-Z_]* { 
	strncpy(llval.Ident, ltext, eMaxIdentifierLength); 
	llval.Ident[eMaxIdentifierLength] = 0;
	return tIDENT; }

<PRODPROTO>"(" { return tLPAREN; }
<PRODPROTO>")" { return tRPAREN; }
<PRODPROTO>"," { return tCOMMA; }
<PRODPROTO>":" { BEGIN NRMLSRC; return tENDPRODPROTO; }
<PRODPROTO>"<" { return tLESSTHAN; }
<PRODPROTO>">" { return tGREATERTHAN; }
<PRODPROTO>[a-zA-Z_][0-9a-zA-Z_]* { 
	strncpy(llval.Ident, ltext, eMaxIdentifierLength); 
	llval.Ident[eMaxIdentifierLength] = 0;
	if (moduleTable.IsModuleIdent(ltext))
		return tMODULEIDENT;
	else
		return tIDENT; 
	}

<PRODUCTION>"(" { nested++; if (1==nested) return tLPAREN; else DumpOut(ltext); }
<PRODUCTION>")" { nested--; if (0==nested) return tRPAREN; else DumpOut(ltext); }
<PRODUCTION>"," { return tCOMMA; }
<PRODUCTION>[a-zA-Z_][0-9a-zA-Z_]* { 
	if (moduleTable.IsModuleIdent(ltext))
	{
	  strncpy(llval.Ident, ltext, eMaxIdentifierLength); 
	  llval.Ident[eMaxIdentifierLength] = 0;
	  return tMODULEIDENT; 
	}
	else
	  DumpOut(ltext);
	}
<PRODUCTION>";" { BEGIN NRMLSRC; return tSEMICOLON; }

<EXPRESSION>";" { BEGIN NRMLSRC; DumpOut(ltext); return tSEMICOLON; }

<STRING>\\\" { DumpOut(ltext); }
<STRING>\" { BEGIN BeforeString; DumpOut(ltext); }

<CHARACTER>\\\' { DumpOut(ltext); }
<CHARACTER>\' { BEGIN BeforeString; DumpOut(ltext); }

^"#line "[0-9]+.+\n	{
	SetCurLine(ltext+6);
	DumpOut(ltext);
	lineno++;
	}
^"# "[0-9]+.+\n	{
	SetCurLine(ltext+2);
	DumpOut(ltext);
	lineno++;
	}

\" { BeforeString = YY_START; BEGIN STRING; DumpOut(ltext); }
\' { BeforeString = YY_START; BEGIN CHARACTER; DumpOut(ltext); }

"\n" { lineno++; DumpOut(ltext); }

[ \t] { DumpOut(ltext); }
. { DumpOut(ltext); }

%%

/*
*/
