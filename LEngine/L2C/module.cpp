#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <lglobal.h>

#include "module.h"
#include "production.h"
#include "file.h"


extern FILE* fOut;

ModuleTable moduleTable;

ProductionTable productionTable;
ProductionTable interpretationTable;

static ProductionType productionMode = eProduction;
ProductionType ProductionMode()
{ return productionMode; }


void SwitchToInterpretation()
{
  productionMode = eInterpretation;
}


static const ModuleDeclaration DclEmpty;


ModuleDeclaration::ModuleDeclaration()
{
	_Ident[0] = 0;
}

ModuleDeclaration::ModuleDeclaration(const char* ident, const ParametersList* pParams, int id)
{
	_id = id;
	strcpy(_Ident, ident);
	memcpy(&_Params, pParams, sizeof(ParametersList));
}


void ModuleDeclaration::operator=(const ModuleDeclaration& src)
{
	if (this != &src)
	{
		strcpy(_Ident, src._Ident);
		memcpy(&_Params, &(src._Params), sizeof(ParametersList));
		_id = src._id;
	}
}

void ModuleDeclaration::GenerateModId() const
{
#ifndef MODIDS
	fprintf(fOut, "const ModuleIdType %s_id = %d;", _Ident, _id);
#endif
}

void ModuleDeclaration::DumpSize(FILE* fp) const
{
	fprintf(fp, "{ \"%s\", ", _Ident);
	if (0==_Params.count)
		fputs(" 0 ", fp);
	else
	{
		for (int i=0; i<_Params.count; i++)
		{
			fprintf(fp, "sizeof(%s)", _Params.Params[i]);
			if (i<_Params.count-1)
				fputs("+", fp);
		}
	}
	fprintf(fp, "}");
#ifdef GENERATE_COMMENTS
	fprintf(fp, "/* %s_id = %d */", _Ident, _id);
#endif

}

void ModuleTable::Add(const ModuleDeclaration& Decl)
{
	int ix = _arr.Add(Decl);
	_Table[Decl.Ident()] = ix;
}


const ModuleDeclaration& ModuleTable::Find(const char* ident) const
{
	std::map<std::string, int>::const_iterator it;
	it = _Table.find(ident);
	if (it != _Table.end())
		return _arr[it->second];
	else
		return DclEmpty;
}


ModuleTable::ModuleTable() : _arr(128)
{}

bool ModuleTable::IsModuleIdent(const char* ident) const
{
	const ModuleDeclaration& Res = Find(ident);
	return (strcmp(ident, Res.Ident())==0);
}


void ModuleTable::DumpSize(FILE* fp) const
{
	for (int i=0; i<_arr.Count(); i++)
	{
		assert(i == _arr[i].Id());
		_arr[i].DumpSize(fp);
		if (i<_arr.Count()-1)
			fputs(",\n", fp);
	}
}


static bool StartDeclared = false;
static bool StartEachDeclared = false;
static bool EndDeclared = false;
static bool EndEachDeclared = false;
static bool ConsiderDeclared = false;
static bool IgnoreDeclared = false;

extern void lerror(const char*, ...);


const ModuleDeclaration* pMDecl = NULL;
int curprm = 0;

void StartGenerateProduce(const char* idnt)
{
	assert(NULL != fOut);
	assert(NULL == pMDecl);
	pMDecl = &(moduleTable.Find(idnt));
#ifdef NOMODIDS
	fprintf(fOut, "Produce((ModuleIdType)(%d));", pMDecl->Id());
#else
	fprintf(fOut, "Produce((ModuleIdType)(%s_id));", pMDecl->Ident());
#endif
	curprm = 0;
}


void EndGenerateProduce()
{
	if (pMDecl->Params().count>0)
#ifdef NOMIDIDS
		fprintf(fOut, "Produce((ModuleIdType)(%d));", pMDecl->Id());
#else
		fprintf(fOut, "Produce((ModuleIdType)(%s_id));", pMDecl->Ident());
#endif
	if (curprm != pMDecl->Params().count)
		lerror("Invalid number of parameters in module %s", pMDecl->Ident());
	pMDecl = NULL;
}


void ParameterCast()
{
	if (pMDecl->Params().count>0)
	{
		if (curprm<pMDecl->Params().count)
			fprintf(fOut, "Produce((%s)(", pMDecl->Params().Params[curprm]);
		else
			lerror("Too many parameters in module %s", pMDecl->Ident());
	}
}

void EndParameterCast()
{
	if (curprm<pMDecl->Params().count)
	{
		fprintf(fOut, "));");
		curprm++;
	}
}

void StartProduce()
{
	fprintf(fOut, "{");
}

void EndProduce()
{
  //fprintf(fOut, "return;}");
  fprintf(fOut, "}");
}


void ExpandStart()
{
	if (StartDeclared)
		lerror("Start statement already declared");
	else
	{
		fprintf(fOut, "void Start()");
		StartDeclared = true;
	}
}


void ExpandStartEach()
{
	if (StartEachDeclared)
		lerror("StartEach statement already declared");
	else
	{
		fprintf(fOut, "void StartEach()");
		StartEachDeclared = true;
	}
}


void ExpandEndEach()
{
	if (EndEachDeclared)
		lerror("EndEach statement already declared");
	else
	{
		fprintf(fOut, "void EndEach()");
		EndEachDeclared = true;
	}
}


void ExpandEnd()
{
	if (EndDeclared)
		lerror("End statement already declared");
	else
	{
		fprintf(fOut, "void End()");
		EndDeclared = true;
	}
}


void BuildCallers()
{
	ProductionTableIterator iter(productionTable);
	while (!(iter.AtEnd()))
	{
		const ProductionProto* pProto = iter.GetCurrent();
		pProto->GenerateCaller();
		iter++;
	}
}

void BuildICallers()
{
	ProductionTableIterator iter(interpretationTable);
	while (!(iter.AtEnd()))
	{
		const ProductionProto* pProto = iter.GetCurrent();
		pProto->GenerateCaller();
		iter++;
	}
}



void BuildProdProtos()
{
	fputs("static const ProductionPrototype proto[] =\n{\n", fOut);
	ProductionTableIterator iter(productionTable);
	while (!(iter.AtEnd()))
	{
		const ProductionProto* pProto = iter.GetCurrent();
		pProto->GenerateProtoEntry();
		iter++;
		if (!(iter.AtEnd()))
			fputs(",\n", fOut);
	}
	fputs("\n};\n", fOut);
}

void BuildIProdProtos()
{
	fputs("static const ProductionPrototype iproto[] =\n{\n", fOut);
	ProductionTableIterator iter(interpretationTable);
	while (!(iter.AtEnd()))
	{
		const ProductionProto* pProto = iter.GetCurrent();
		pProto->GenerateProtoEntry();
		iter++;
		if (!(iter.AtEnd()))
			fputs(",\n", fOut);
	}
	fputs("\n};\n", fOut);
}


void BuildModuleSize()
{
	fputs("static const ModuleData moduleData[] =\n{\n", fOut);
	moduleTable.DumpSize(fOut);
	fputs("\n};\n\n", fOut);
}

void GenerateFixed()
{
  fputs(
  "\nconst ModuleData* GetModuleData(int i)\n"
  "{ return &(moduleData[i]); }\n\n"
  ,fOut);

  fprintf(fOut, 
  "\nint NumOfModules()\n"
  "{ return %d; }\n", moduleTable.Items());

  if (!StartDeclared)
    fputs("void Start() {}\n", fOut);

  if (!StartEachDeclared)
    fputs("void StartEach() {}\n", fOut);

  if (!EndEachDeclared)
    fputs("void EndEach() {}\n", fOut);

  if (!EndDeclared)
    fputs("void End() {}\n", fOut);

  fputs(
  "\nint NumOfProductions()\n"
  "{ return sizeof(proto)/sizeof(proto[0]); }", fOut);
  //"{ return CountOf(proto); }", fOut);

  fputs(
  "\nconst ProductionPrototype& GetProductionPrototype(int i)\n"
  "{ return proto[i]; }\n", fOut);

  fputs(
  "\nint NumOfIProductions()\n"
  "{ return sizeof(iproto)/sizeof(iproto[0]); }", fOut);
  //"{ return CountOf(proto); }", fOut);

  fputs(
  "\nconst ProductionPrototype& GetIProductionPrototype(int i)\n"
  "{ return iproto[i]; }\n", fOut);

  if (!ConsiderDeclared)
  {
    fputs(
    "int NumOfConsidered() { return 0; }\n"
    "ModuleIdType GetConsidered(int) { return -1; }\n",
    fOut);
  }
  if (!IgnoreDeclared)
  {
    fputs(
    "int NumOfIgnored() { return 0; }\n"
    "ModuleIdType GetIgnored(int) { return -1; }\n",
    fOut);
  }

}



FormalModuleDt::FormalModuleDt(const char* idnt, const ParametersList* pParams)
{
	strcpy(Ident, idnt);
	memcpy(&Params, pParams, sizeof(ParametersList));
	pNext = NULL;
}


int FormalModuleDt::GenerateForPrototype() const
{
	const ModuleDeclaration& decl = moduleTable.Find(Ident);
	const ParametersList& ParamList = decl.Params();
	if (Params.count != ParamList.count)
		lerror("Invalid number of parameters for module %s", Ident);

	for (int i=0; i<Params.count; i++)
	{
		fprintf(fOut, "%s %s", ParamList.Params[i], Params.Params[i]);
		if (i<Params.count-1)
			fputs(",", fOut);
	}

	return Params.count;
}


FormalModuleDtList::FormalModuleDtList(FormalModuleDt* pFirst)
{
	assert(NULL == pFirst->pNext);
	_pFirst = _pLast = pFirst;
}


FormalModuleDtList::~FormalModuleDtList()
{
	while (NULL != _pFirst)
	{
		FormalModuleDt* pNext = _pFirst->pNext;
		delete _pFirst;
		_pFirst = pNext;
	}
}

void FormalModuleDtList::Add(FormalModuleDt* pNext)
{
	assert(NULL == pNext->pNext);
	_pLast->pNext = pNext;
	_pLast = pNext;
}


int FormalModuleDtList::CountParams() const
{
	const FormalModuleDt* pCur = _pFirst;
	int res = 0;
	while (NULL != pCur)
	{
		res += pCur->NumOfParams();
		pCur = pCur->pNext;
	}
	return res;
}

int FormalModuleDtList::GenerateForPrototype() const
{
	const FormalModuleDt* pCur = _pFirst;
	int res = 0;
	while (NULL != pCur)
	{
		if ((res>0) && (pCur->NumOfParams()>0))
			fputs(",", fOut);
		res += pCur->GenerateForPrototype();
		pCur = pCur->pNext;
	}
	return res;	
}

void FormalModuleDtList::GenerateProtoEntry() const
{
	const FormalModuleDt* pCur = _pFirst;
	int count = 0;
	fprintf(fOut, "{ ");
	while (NULL != pCur)
	{
		fprintf(fOut, "%s_id", pCur->Ident);
		count++;
		pCur = pCur->pNext;
		if (NULL != pCur)
			fprintf(fOut, ", ");
	}
	fprintf(fOut, " }, %d\n", count);
}

void StartConsider()
{
	if (ConsiderDeclared)
		lerror("Considered previously declared");
	if (IgnoreDeclared)
		lerror("Ignore previously declared");
	fputs("static const ModuleIdType __considerArr[] = { ", fOut);
}


void StartIgnore()
{
	if (ConsiderDeclared)
		lerror("Considered previously declared");
	if (IgnoreDeclared)
		lerror("Ignore previously declared");
	fputs("static const ModuleIdType __ignoreArr[] = { ", fOut);
}


void AppendConIgnModule(const char* midnt)
{
	fputs(midnt, fOut);
	fputs("_id,", fOut);
}

void EndConsider()
{
	fputs("0 };\n", fOut);
	fputs(
	"int NumOfConsidered()\n"
	"{ return sizeof(__considerArr)/sizeof(__considerArr[0])-1; }\n"
	"ModuleIdType GetConsidered(int i)\n"
	"{ return __considerArr[i]; }\n",
	fOut);
	ConsiderDeclared = true;
}

void EndIgnore()
{
	fputs("0 };\n", fOut);
	fputs(
	"int NumOfIgnored()\n"
	"{ return sizeof(__ignoreArr)/sizeof(__ignoreArr[0])-1; }\n"
	"ModuleIdType GetIgnored(int i)\n"
	"{ return __ignoreArr[i]; }\n",
	fOut);
	IgnoreDeclared = true;
}


void StartDerivLength()
{
	fputs("int DerivationLength() { return ", fOut);
}

void EndDerivLength()
{
	fputs("}", fOut);
}


void InitDefault()
{
	ParametersList params;
	params.count = 0;
	{
		ModuleDeclaration md("SB", &params, SB_id);
		moduleTable.Add(md);
	}
	{
		ModuleDeclaration md("EB", &params, EB_id);
		moduleTable.Add(md);
	}
}


void GenerateOpenNamespace(const char* id)
{
  fputs("namespace ", fOut);
  fputs(id, fOut);
  fputs("{ \n", fOut);
}

//defined in l2c.y
extern bool namespace_close;
void GenerateCloseNamespace()
{
  if (namespace_close)
    fputs("} //closing namespace\n", fOut);
}
