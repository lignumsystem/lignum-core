
class ActualParameters
{
public:
  ActualParameters();
  const char* pArg(int) const;
  void AddModuleAddr(const char*);
  int Count() const
  { return _count; }
  void Reset();
private:
  const char* _arr[eMaxFormalModules];
  int _count;
};

struct CallerData
{
  void Reset();
  ActualParameters RCntxt;
  ActualParameters Strct;
  ActualParameters LCntxt;
};


void _Add(const void*, int);

template<class T>
void Produce(T t)
{
  _Add(&t, sizeof(T));
}

typedef void (*ProdCaller)(const CallerData*);

struct ProductionModules
{
  ModuleIdType arr[eMaxFormalModules];
  int count;
};

struct ProductionPrototype
{
  ProductionModules LCntxt;
  ProductionModules Strct;
  ProductionModules RCntxt;
  ProdCaller pCaller;
};


struct ModuleData
{
  const char* Name;
  int size;
};

const ModuleData* GetModuleData(int);
const char* GetModuleName(int);
int NumOfModules();
int GetSizeOf(int);
int DerivationLength();
int NumOfProductions();
const ProductionPrototype& GetProductionPrototype(int);
int NumOfIProductions();
const ProductionPrototype& GetIProductionPrototype(int);
int NumOfConsidered();
ModuleIdType GetConsidered(int i);
int NumOfIgnored();
ModuleIdType GetIgnored(int i);


void Start();
void StartEach();
void EndEach();
void End();


/* this is output file for dumping homomorphism */
extern FILE* fOut;

#include <lsysintrfcI.h>

