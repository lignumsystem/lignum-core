#ifndef __MODULE_H__
#define __MODULE_H__

#ifdef WIN32
#pragma warning (disable: 4786)
#endif


#include <map>
#include <string>
#include <dynarray.h>


struct ParametersList
{
        char Params[eMaxParams][eMaxIdentifierLength+1];
        int count;
};



class ModuleDeclaration
{
public:
	ModuleDeclaration();
	ModuleDeclaration(const char*, const ParametersList*, int);
	const char* Ident() const
	{ return _Ident; }
	void operator=(const ModuleDeclaration&);
	const ParametersList& Params() const
	{ return _Params; }
	int Id() const
	{ return _id; }
	void GenerateModId() const;
	void DumpSize(FILE*) const;
private:
	char _Ident[eMaxIdentifierLength+1];
	ParametersList _Params;
	int _id;
};

typedef std::map<std::string,int> AssocTableOfModuleDeclaration;


class ModuleTable
{
public:
	ModuleTable();
	void Add(const ModuleDeclaration&);
	const ModuleDeclaration& Find(const char*) const;
	bool IsModuleIdent(const char*) const;
	void DumpSize(FILE*) const;
	int Items() const
	{ return _arr.Count(); }
private:
	DynArray<ModuleDeclaration> _arr;
	AssocTableOfModuleDeclaration _Table;
};



class FormalModuleDt
{
public:
	FormalModuleDt(const char*, const ParametersList*);
	int NumOfParams() const
	{ return Params.count; }
	int GenerateForPrototype() const;
	char Ident[eMaxIdentifierLength+1];
	ParametersList Params;
	FormalModuleDt* pNext;
private:
	void operator=(const FormalModuleDt&);
};

class FormalModuleDtList
{
public:
	FormalModuleDtList(FormalModuleDt*);
	~FormalModuleDtList();
	void Add(FormalModuleDt*);
	FormalModuleDt* GetHead() const
	{ return _pFirst; }
	int CountParams() const;
	int GenerateForPrototype() const;
	void GenerateProtoEntry() const;
private:
	FormalModuleDt* _pFirst;
	FormalModuleDt* _pLast;
	void operator=(const FormalModuleDtList&);
};

#else
	#error File already included
#endif
