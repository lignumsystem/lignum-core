#include <assert.h>
#include <stdio.h>

#include <lglobal.h>

#include "production.h"
#include "module.h"


extern FILE* fOut;

int ProductionProto::_counter = 1;
extern ModuleTable moduleTable;
extern ProductionType ProductionMode();


ProductionProto::ProductionProto
(FormalModuleDtList* pLCntxt, FormalModuleDtList* pStrct, FormalModuleDtList* pRCntxt):
_pLCntxt(pLCntxt), _pStrct(pStrct), _pRCntxt(pRCntxt)
{
	assert(NULL != _pStrct);
	_id = _counter++;
	_type = ProductionMode();
}

ProductionProto::~ProductionProto()
{
	delete _pLCntxt;
	delete _pStrct;
	delete _pRCntxt;
}

void ProductionProto::Generate() const
{
	assert(NULL != fOut);
	switch (_type)
	{
	case eProduction:
		fprintf(fOut, "void _P%d(", _id);
		break;
	case eInterpretation:
		fprintf(fOut, "void _I%d(", _id);
		break;
	}
	int count = 0;
	if (NULL != _pLCntxt)
	{
		count += _pLCntxt->GenerateForPrototype();
	}
	if ((count>0) && (_pStrct->CountParams()>0))
		fprintf(fOut, ",");
	count += _pStrct->GenerateForPrototype();
	if (NULL != _pRCntxt)
	{
		if ((count>0) && (_pRCntxt->CountParams()>0))
			fprintf(fOut, ",");
		_pRCntxt->GenerateForPrototype();
	}
	fprintf(fOut, ")");
}


void ProductionProto::GenerateCaller() const
{
	switch (_type)
	{
	case eProduction:
		fprintf(fOut, "\nvoid _PC%d(const CallerData* pCD)\n", _id);
		break;
	case eInterpretation:
		fprintf(fOut, "\nvoid _IC%d(const CallerData* pCD)\n", _id);
		break;
	}

	fprintf(fOut, "{\n");
	int prmcnt = 0;
	if (NULL != _pLCntxt)
		prmcnt += _pLCntxt->CountParams();
	prmcnt += _pStrct->CountParams();
	if (NULL != _pRCntxt)
		prmcnt += _pRCntxt->CountParams();
	if (prmcnt>0)
		fprintf(fOut, "const char* pArg;\n");
	prmcnt = 0;
	if (NULL != _pLCntxt)
	{
#ifdef GENERATE_COMMENTS
		fprintf(fOut, "/* Extraxt left context params */\n");
#endif
		//fprintf(fOut, "assert(pCD->LCntxt.countParams() == %d);\n", _pLCntxt->CountParams());
		const FormalModuleDt* pCurrentModule = _pLCntxt->GetHead();
		int mdlcnt = 0;
		while (NULL != pCurrentModule)
		{
			const ModuleDeclaration& decl = moduleTable.Find(pCurrentModule->Ident);
#ifdef GENERATE_COMMENTS
			fprintf(fOut, "/* Module %s */\n", pCurrentModule->Ident);
#endif
			if (pCurrentModule->Params.count>0)
				fprintf(fOut, "pArg = pCD->LCntxt.pArg(%d);\n", mdlcnt);
			for (int i=0; i<pCurrentModule->Params.count; i++)
			{
#ifdef GENERATE_COMMENTS
				fprintf(fOut, "/* Parameter %s */\n", pCurrentModule->Params.Params[i]);
#endif
				fprintf(fOut, "%s p%d;\n", decl.Params().Params[i], prmcnt);
				fprintf(fOut, "memcpy(&p%d, pArg, sizeof(%s));\n", prmcnt, decl.Params().Params[i]);
				if (i<pCurrentModule->Params.count-1)
					fprintf(fOut, "pArg += sizeof(%s);\n", decl.Params().Params[i]);
				prmcnt++;
			}
			pCurrentModule = pCurrentModule->pNext;
			mdlcnt++;
		}
	}

	// Strict predecessor
	{
#ifdef GENERATE_COMMENTS
		fprintf(fOut, "/* Extraxt strict predecessor params */\n");
#endif
		//fprintf(fOut, "assert(pCD->Strct.countParams() == %d);\n", _pStrct->CountParams());
		const FormalModuleDt* pCurrentModule = _pStrct->GetHead();
		int mdlcnt = 0;
		while (NULL != pCurrentModule)
		{
			const ModuleDeclaration& decl = moduleTable.Find(pCurrentModule->Ident);
#ifdef GENERATE_COMMENTS
			fprintf(fOut, "/* Module %s */\n", pCurrentModule->Ident);
#endif
			if (pCurrentModule->Params.count>0)
				fprintf(fOut, "pArg = pCD->Strct.pArg(%d);\n", mdlcnt);
			for (int i=0; i<pCurrentModule->Params.count; i++)
			{
#ifdef GENERATE_COMMENTS
				fprintf(fOut, "/* Parameter %s */\n", pCurrentModule->Params.Params[i]);
#endif
				fprintf(fOut, "%s p%d;\n", decl.Params().Params[i], prmcnt);
				fprintf(fOut, "memcpy(&p%d, pArg, sizeof(%s));\n", prmcnt, decl.Params().Params[i]);
				if (i<pCurrentModule->Params.count-1)
					fprintf(fOut, "pArg += sizeof(%s);\n", decl.Params().Params[i]);
				prmcnt++;
			}
			pCurrentModule = pCurrentModule->pNext;
			mdlcnt++;
		}
	}


	if (NULL != _pRCntxt)
	{
#ifdef GENERATE_COMMENTS
		fprintf(fOut, "/* Extraxt right context params */\n");
#endif
		//fprintf(fOut, "assert(pCD->RCntxt.countParams() == %d);\n", _pRCntxt->CountParams());
		const FormalModuleDt* pCurrentModule = _pRCntxt->GetHead();
		int mdlcnt = 0;
		while (NULL != pCurrentModule)
		{
			const ModuleDeclaration& decl = moduleTable.Find(pCurrentModule->Ident);
#ifdef GENERATE_COMMENTS
			fprintf(fOut, "/* Module %s */\n", pCurrentModule->Ident);
#endif
			if (pCurrentModule->Params.count>0)
				fprintf(fOut, "pArg = pCD->RCntxt.pArg(%d);\n", mdlcnt);
			for (int i=0; i<pCurrentModule->Params.count; i++)
			{
#ifdef GENERATE_COMMENTS
				fprintf(fOut, "/* Parameter %s */\n", pCurrentModule->Params.Params[i]);
#endif
				fprintf(fOut, "%s p%d;\n", decl.Params().Params[i], prmcnt);
				fprintf(fOut, "memcpy(&p%d, pArg, sizeof(%s));\n", prmcnt, decl.Params().Params[i]);
				if (i<pCurrentModule->Params.count-1)
					fprintf(fOut, "pArg += sizeof(%s);\n", decl.Params().Params[i]);
				prmcnt++;
			}
			pCurrentModule = pCurrentModule->pNext;
			mdlcnt++;
		}
	}

	switch (_type)
	{
	case eProduction:
		fprintf(fOut, "_P%d(", _id);
		break;
	case eInterpretation:
		fprintf(fOut, "_I%d(", _id);
		break;
        }


	for (int i=0; i<prmcnt; i++)
	{
		fprintf(fOut, "p%d", i);
		if (i<prmcnt-1)
			fprintf(fOut, ",");
	}
	fprintf(fOut, ");\n");
	fprintf(fOut, "}\n\n");
}


void ProductionProto::GenerateProtoEntry() const
{
#ifdef GENERATE_COMMENTS
	fprintf(fOut, "\t// Production %d\n", _id);
#endif
	fprintf(fOut, "\t{\n");

#ifdef GENERATE_COMMENTS
	fprintf(fOut, "\t\t// LCntxt\n");
#endif
	fprintf(fOut, "\t\t{\n");
	fprintf(fOut, "\t\t\t");

	if (NULL != _pLCntxt)
		_pLCntxt->GenerateProtoEntry();
	else
		fprintf(fOut, "{ 0 }, 0\n");

	fprintf(fOut, "\t\t},");


	fprintf(fOut, "\n\t\t{\n");
#ifdef GENERATE_COMMENTS
	fprintf(fOut, "\t\t// Strct\n");
#endif
	fprintf(fOut, "\t\t\t");

	_pStrct->GenerateProtoEntry();
	fprintf(fOut, "\t\t},");

#ifdef GENERATE_COMMENTS
	fprintf(fOut, "\n\t\t// RCntxt\n");
#endif
	fprintf(fOut, "\n\t\t{\n");
	fprintf(fOut, "\t\t\t");

	if (NULL != _pRCntxt)
		_pRCntxt->GenerateProtoEntry();
	else
		fprintf(fOut, "{ 0 }, 0\n");
        switch (_type)
        {
        case eProduction:
                fprintf(fOut, "\t\t},\n\t\t_PC%d\n\t}", _id);
                break;
        case eInterpretation:
		fprintf(fOut, "\t\t},\n\t\t_IC%d\n\t}", _id);
                break;
        }
}




ProductionTable::ProductionTable()
{
	_arr = new pProductionProto[eInitSize];
	_items = 0;
	_size = eInitSize;
}

ProductionTable::~ProductionTable()
{
	for (int i=0; i<_items; i++)
		delete _arr[i];
	delete []_arr;
}


void ProductionTable::Add(ProductionProto* pProto)
{
	if (_items == _size)
		_Grow();
	_arr[_items] = pProto;
	_items++;
}



void ProductionTable::_Grow()
{
	assert(!"Not implemented yet");
}
