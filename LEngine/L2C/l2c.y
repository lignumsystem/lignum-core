%{

#define YYDEBUG 1
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <lglobal.h>

#include <module.h>
#include <production.h>

extern int llex(void);
extern void lerror(const char*, ...);
extern void lwarning(const char*, ...);
extern void StartGenerateProduce(const char*);
extern void ParameterCast();
extern void EndParameterCast();
extern void EndGenerateProduce();
extern void StartProduce();
extern void EndProduce();
extern void ExpandStart();
extern void ExpandStartEach();
extern void ExpandEndEach();
extern void ExpandEnd();
extern void GenerateProto(FormalModuleDtList*, FormalModuleDtList*, FormalModuleDtList*);
extern void StartConsider();
extern void StartIgnore();
extern void EndConsider();
extern void EndIgnore();
extern void AppendConIgnModule(const char*);
extern void StartDerivLength();
extern void EndDerivLength();
extern void SwitchToInterpretation();

extern void GenerateOpenNamespace(const char*);
extern void GenerateCloseNamespace();

extern ProductionType ProductionMode();


extern ModuleTable moduleTable;
extern ProductionTable productionTable;
extern ProductionTable interpretationTable;

static int counter = eFirstModuleId;
bool namespace_close = false;

%}

%union
{
  char Ident[eMaxIdentifierLength+1];
  int ModuleId;
  ParametersList ParamsList;
  FormalModuleDt* pFormalModuleData;
  FormalModuleDtList* pFormalModuleDataList;
};
 
%token tOPEN tCLOSE tMODULE tPRODUCE tSTART tSTARTEACH tENDEACH tEND 
%token tCONSIDER tIGNORE tDERIVLENGTH tINTERPRETATION
%token tLPAREN tRPAREN tSEMICOLON tCOMMA tLESSTHAN tGREATERTHAN tENDPRODPROTO
%token <Ident> tIDENT tMODULEIDENT
%token tERROR


%type <ParamsList> Parameters
%type <pFormalModuleData> FormalModule
%type <pFormalModuleDataList> LContext RContext StrictPred FormalModules

%%

Translate:  Translate TranslationUnit
        |
	;

TranslationUnit:
        OpenNamespace
        |ModuleDeclaration
	| ConsiderStatement
	| IgnoreStatement
	| ProductionPrototype
	| ProduceStatement
	| DerivLength
	| tSTART
	{ ExpandStart(); }
	| tSTARTEACH
	{ ExpandStartEach(); }
	| tENDEACH
	{ ExpandEndEach(); }
	| tEND
	{ ExpandEnd(); }
	| tINTERPRETATION
          { SwitchToInterpretation(); }
        | CloseNamespace
	;

OpenNamespace: tOPEN tIDENT tSEMICOLON
        {
          GenerateOpenNamespace($2);
        }
        ;
CloseNamespace: tCLOSE tIDENT tSEMICOLON
        {
          namespace_close = true;
        }
        ;
ModuleDeclaration: tMODULE tIDENT tLPAREN Parameters tRPAREN tSEMICOLON
	{ 
		ModuleDeclaration mdecl($2, &($4), counter++);
		mdecl.GenerateModId();
		moduleTable.Add(mdecl); 
	}
	;

ConsiderStatement: tCONSIDER { StartConsider(); } ModuleList tSEMICOLON
	{ EndConsider(); }
	;

IgnoreStatement: tIGNORE { StartIgnore(); } ModuleList tSEMICOLON
	{ EndIgnore(); }
	;


ModuleList: tMODULEIDENT
	{ AppendConIgnModule($1); }
	| ModuleList tMODULEIDENT
	{ AppendConIgnModule($2); }
	;

DerivLength: tDERIVLENGTH { StartDerivLength(); } tSEMICOLON
	{ EndDerivLength(); }
        ;

ProductionPrototype: LContext tLESSTHAN StrictPred tGREATERTHAN RContext tENDPRODPROTO
	{ 
		ProductionProto* pNew = new ProductionProto($1, $3, $5); 
		pNew->Generate();
		productionTable.Add(pNew);
	}
	| LContext tLESSTHAN StrictPred tENDPRODPROTO
	{ 
		ProductionProto* pNew = new ProductionProto($1, $3, NULL);
		pNew->Generate();
		productionTable.Add(pNew);
	}
	| StrictPred tGREATERTHAN RContext tENDPRODPROTO
	{ 
		ProductionProto* pNew = new ProductionProto(NULL, $1, $3); 
		pNew->Generate();
		productionTable.Add(pNew);
	}
	| StrictPred tENDPRODPROTO
	{ 
		ProductionProto* pNew = new ProductionProto(NULL, $1, NULL); 
		pNew->Generate();
		if (eInterpretation == ProductionMode())
			interpretationTable.Add(pNew);
		else
			productionTable.Add(pNew);
	}
	;

LContext: FormalModules
	{ $$ = $1; }
	;

RContext: FormalModules
	{ $$ = $1; }
	;

StrictPred: FormalModules
	{ $$ = $1; }
	;

FormalModules: FormalModules FormalModule
	{ $$ = $1; $$->Add($2); }
	| FormalModule
	{ $$ = new FormalModuleDtList($1); }
	;

FormalModule: tMODULEIDENT tLPAREN Parameters tRPAREN
	{ $$ = new FormalModuleDt($1, &($3)); }
	;

ProduceStatement: tPRODUCE { StartProduce(); } ParametricWord tSEMICOLON
	{ EndProduce(); }
	;


ParametricWord: ParametricWord ParametricLetter
	|
	;


ParametricLetter: tMODULEIDENT { StartGenerateProduce($1); } tLPAREN { ParameterCast(); } CallParameters { EndParameterCast(); } tRPAREN 
	{ EndGenerateProduce(); }
	| tMODULEIDENT
	{ StartGenerateProduce($1); EndGenerateProduce(); }
	;

CallParameters: CallParameters { EndParameterCast(); } tCOMMA { ParameterCast(); }
	|
	;

Parameters: Parameters tCOMMA tIDENT
	{
	  if ($1.count == eMaxParams)
	    lerror("Too many parameters");
	  strcpy($1.Params[$1.count], $3);
	  $1.count++;
	  $$ = $1;
	}
	| tIDENT
	{
	  strcpy($$.Params[0], $1);
	  $$.count = 1;
	}
	|
	{ $$.count = 0; }
	;


%%
