#line 1 "lychnis-par.l"
#include <stdio.h>
#include <lglobal.h>
#include <lsysintrfc.h>


#define STEPS 23
#define VANG 45
#define S0 100
#define ANG 31
#define L_SIZE 1.5
#define D1 3
#define D2 7
#define LEN1 20
#define LEN2 10
#define T1 1
#define T2 5
#define T3 11

int DerivationLength() { return  STEPS;}

 const ModuleIdType E_id = 2;
 const ModuleIdType Slash_id = 3;
 const ModuleIdType Amp_id = 4;
 const ModuleIdType A_id = 5;
 const ModuleIdType F_id = 6;
 const ModuleIdType X_id = 7;
 const ModuleIdType L_id = 8;
 const ModuleIdType Excl_id = 9;
 const ModuleIdType SemiColon_id = 10;
 const ModuleIdType Q_id = 11;
 const ModuleIdType B_id = 12;
 const ModuleIdType AtV_id = 13;
 const ModuleIdType Minus_id = 14;
 const ModuleIdType Plus_id = 15;
 const ModuleIdType SurfB_id = 16;
 const ModuleIdType Percent_id = 17;
 const ModuleIdType SurfK_id = 18;
 const ModuleIdType Hat_id = 19;
 const ModuleIdType SurfP_id = 20;
 const ModuleIdType SurfF_id = 21;
 const ModuleIdType SurfL_id = 22;
 const ModuleIdType Hash_id = 23;

void Start()
{
  {  Produce((ModuleIdType)(E_id));Produce((ModuleIdType)(Slash_id));Produce((float)(VANG));Produce((ModuleIdType)(Slash_id)); Produce((ModuleIdType)(Amp_id));Produce((float)(5));Produce((ModuleIdType)(Amp_id)); Produce((ModuleIdType)(A_id));Produce((int)(0));Produce((ModuleIdType)(A_id));return;}
}

 void _P1(int t)
{
  if (t>0)
    { Produce((ModuleIdType)(A_id));Produce((int)(t-1));Produce((ModuleIdType)(A_id));return;}
  else if (t==0)
    { Produce((ModuleIdType)(F_id));Produce((float)(S0));Produce((ModuleIdType)(F_id));Produce((ModuleIdType)(X_id));Produce((int)(LEN1));Produce((ModuleIdType)(X_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(L_id)); Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(Slash_id));Produce((float)(180));Produce((ModuleIdType)(Slash_id));  Produce((ModuleIdType)(L_id));
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Excl_id));Produce((ModuleIdType)(F_id));Produce((float)(S0));Produce((ModuleIdType)(F_id));Produce((ModuleIdType)(X_id));Produce((int)(LEN2));Produce((ModuleIdType)(X_id)); Produce((ModuleIdType)(SemiColon_id));Produce((int)(120));Produce((ModuleIdType)(SemiColon_id));  Produce((ModuleIdType)(Q_id));Produce((ModuleIdType)(B_id));Produce((int)(0));Produce((ModuleIdType)(B_id)); 
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(AtV_id));Produce((ModuleIdType)(Minus_id));Produce((float)(ANG));Produce((ModuleIdType)(Minus_id));  Produce((ModuleIdType)(Excl_id)); Produce((ModuleIdType)(Excl_id)); Produce((ModuleIdType)(Excl_id)); Produce((ModuleIdType)(Excl_id));Produce((ModuleIdType)(A_id));Produce((int)(D2));Produce((ModuleIdType)(A_id)); 
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(AtV_id));Produce((ModuleIdType)(Plus_id));Produce((float)(ANG));Produce((ModuleIdType)(Plus_id));  Produce((ModuleIdType)(Excl_id)); Produce((ModuleIdType)(Excl_id)); Produce((ModuleIdType)(Excl_id)); Produce((ModuleIdType)(Excl_id));Produce((ModuleIdType)(A_id));Produce((int)(D1));Produce((ModuleIdType)(A_id)); Produce((ModuleIdType)(EB_id));return;}
  else
    { Produce((ModuleIdType)(A_id));Produce((int)(t));Produce((ModuleIdType)(A_id));return;}
}

 void _P2(int a)
{
  if (a>0)
    { Produce((ModuleIdType)(F_id));Produce((float)(S0));Produce((ModuleIdType)(F_id));Produce((ModuleIdType)(X_id));Produce((int)(a-1));Produce((ModuleIdType)(X_id));return;}
  else 
    { Produce((ModuleIdType)(X_id));Produce((int)(a));Produce((ModuleIdType)(X_id));return;}
}

 void _P3()
{
  { Produce((ModuleIdType)(SemiColon_id));Produce((int)(1));Produce((ModuleIdType)(SemiColon_id)); Produce((ModuleIdType)(SemiColon_id));Produce((int)(1));Produce((ModuleIdType)(SemiColon_id));Produce((ModuleIdType)(SemiColon_id));Produce((int)(1));Produce((ModuleIdType)(SemiColon_id));Produce((ModuleIdType)(Q_id));return;}
}

 void _P4()
{
  {  Produce((ModuleIdType)(E_id));Produce((ModuleIdType)(Hash_id));return;}
}

 void _P5(int a)
{
  if (a==0) 
    { Produce((ModuleIdType)(B_id));Produce((int)(1));Produce((ModuleIdType)(B_id)); Produce((ModuleIdType)(SurfB_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfB_id));return;}
  else if (a==T1)
    { Produce((ModuleIdType)(B_id));Produce((int)(a+1));Produce((ModuleIdType)(B_id)); Produce((ModuleIdType)(Percent_id));return;}
  else if (a==T1+1)
    { Produce((ModuleIdType)(B_id));Produce((int)(a+1));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(SurfK_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfK_id));Produce((ModuleIdType)(Hat_id));Produce((float)(90));Produce((ModuleIdType)(Hat_id));
       Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(Amp_id));Produce((float)(36));Produce((ModuleIdType)(Amp_id)); Produce((ModuleIdType)(SurfP_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id));Produce((ModuleIdType)(Plus_id));Produce((float)(72));Produce((ModuleIdType)(Plus_id));  Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(Amp_id));Produce((float)(36));Produce((ModuleIdType)(Amp_id)); Produce((ModuleIdType)(SurfP_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id));Produce((ModuleIdType)(Plus_id));Produce((float)(72));Produce((ModuleIdType)(Plus_id));  Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(Amp_id));Produce((float)(36));Produce((ModuleIdType)(Amp_id)); Produce((ModuleIdType)(SurfP_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id));Produce((ModuleIdType)(Plus_id));Produce((float)(72));Produce((ModuleIdType)(Plus_id));  Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(Amp_id));Produce((float)(36));Produce((ModuleIdType)(Amp_id)); Produce((ModuleIdType)(SurfP_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id));Produce((ModuleIdType)(Plus_id));Produce((float)(72));Produce((ModuleIdType)(Plus_id));  Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(Amp_id));Produce((float)(36));Produce((ModuleIdType)(Amp_id)); Produce((ModuleIdType)(SurfP_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfP_id)); Produce((ModuleIdType)(EB_id));return;}
  else if (a==T2)
    { Produce((ModuleIdType)(B_id));Produce((int)(a+1));Produce((ModuleIdType)(B_id)); Produce((ModuleIdType)(Percent_id));return;}
  else if (a==T2+1)
    { Produce((ModuleIdType)(B_id));Produce((int)(a+1));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(SurfK_id));Produce((float)(1.33));Produce((ModuleIdType)(SurfK_id));Produce((ModuleIdType)(Hat_id));Produce((float)(90));Produce((ModuleIdType)(Hat_id));
       Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(SurfP_id));Produce((float)(2.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(SurfP_id));Produce((float)(2.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(SurfP_id));Produce((float)(2.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(SurfP_id));Produce((float)(2.0));Produce((ModuleIdType)(SurfP_id)); 
      Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(SB_id));Produce((ModuleIdType)(SurfP_id));Produce((float)(2.0));Produce((ModuleIdType)(SurfP_id)); Produce((ModuleIdType)(EB_id));return;}
  else if (a==T3)
    { Produce((ModuleIdType)(B_id));Produce((int)(a+1));Produce((ModuleIdType)(B_id)); Produce((ModuleIdType)(Percent_id));return;}
  else if (a==T3+1)
    { Produce((ModuleIdType)(SemiColon_id));Produce((int)(192));Produce((ModuleIdType)(SemiColon_id));  Produce((ModuleIdType)(Q_id));Produce((ModuleIdType)(SurfF_id));Produce((float)(1.0));Produce((ModuleIdType)(SurfF_id));return;}
  else
    { Produce((ModuleIdType)(B_id));Produce((int)(a+1));Produce((ModuleIdType)(B_id));return;}
}


 void _P6(float s)
{
  if (s<1.4)
    { Produce((ModuleIdType)(SurfB_id));Produce((float)(s*1.1));Produce((ModuleIdType)(SurfB_id));return;}
  else
    { Produce((ModuleIdType)(SurfB_id));Produce((float)(s));Produce((ModuleIdType)(SurfB_id));return;}
}


 void _P7(float s)
{
  if (s<1.5)
    { Produce((ModuleIdType)(SurfK_id));Produce((float)(s*1.1));Produce((ModuleIdType)(SurfK_id));return;}
  else 
    { Produce((ModuleIdType)(SurfK_id));Produce((float)(s));Produce((ModuleIdType)(SurfK_id));return;}
}

 void _P8(float s)
{
  if (s<2.5)
    { Produce((ModuleIdType)(SurfP_id));Produce((float)(s*1.15));Produce((ModuleIdType)(SurfP_id));return;}
  else
    { Produce((ModuleIdType)(SurfP_id));Produce((float)(s));Produce((ModuleIdType)(SurfP_id));return;}
}


 void _P9(float s)
{
  if (s>0.6)
    { Produce((ModuleIdType)(SurfF_id));Produce((float)(s*0.9));Produce((ModuleIdType)(SurfF_id));return;}
  else
    { Produce((ModuleIdType)(SurfF_id));Produce((float)(s));Produce((ModuleIdType)(SurfF_id));return;}
}

 void _P10()
{
  { Produce((ModuleIdType)(SurfL_id));Produce((float)(0.1));Produce((ModuleIdType)(SurfL_id));return;}
}

 void _P11(float s)
{
  if (s<L_SIZE)
    { Produce((ModuleIdType)(SurfL_id));Produce((float)(s+0.5));Produce((ModuleIdType)(SurfL_id));return;}
  else 
    { Produce((ModuleIdType)(SurfL_id));Produce((float)(s));Produce((ModuleIdType)(SurfL_id));return;}
}



 void _I12(float a)
{
  fprintf(fOut, "/(%f)", a);
}

 void _I13(float l)
{
  fprintf(fOut, "F(%f)", l);
}

 void _I14()
{
  fprintf(fOut, "!");
}

 void _I15(int i)
{
  fprintf(fOut, ";(%d)", i);
}

 void _I16()
{
  fprintf(fOut, "@v");
}

 void _I17(float f)
{
  fprintf(fOut, "-(%f)", f);
}

 void _I18(float f)
{
  fprintf(fOut, "+(%f)", f);
}

 void _I19(float s)
{
  fprintf(fOut, "~b(%f)", s);
}

 void _I20()
{
  fprintf(fOut, "%%");
}

 void _I21(float s)
{
  fprintf(fOut, "~k(%f)", s);
}

 void _I22(float f)
{
  fprintf(fOut, "^(%f)", f);
}

 void _I23(float s)
{
  fprintf(fOut, "~p(%f)", s);
}

 void _I24(float s)
{
  fprintf(fOut, "~f(%f)", s);
}

 void _I25(float s)
{
  fprintf(fOut, "~l(%f)", s);
}

 void _I26()
{
  fprintf(fOut, "#");
}

void _PC1(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
int p0;
memcpy(&p0, pArg, sizeof(int));
_P1(p0);
}


void _PC2(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
int p0;
memcpy(&p0, pArg, sizeof(int));
_P2(p0);
}


void _PC3(const CallerData* pCD)
{
_P3();
}


void _PC4(const CallerData* pCD)
{
_P4();
}


void _PC5(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
int p0;
memcpy(&p0, pArg, sizeof(int));
_P5(p0);
}


void _PC6(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_P6(p0);
}


void _PC7(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_P7(p0);
}


void _PC8(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_P8(p0);
}


void _PC9(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_P9(p0);
}


void _PC10(const CallerData* pCD)
{
_P10();
}


void _PC11(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_P11(p0);
}


void _IC12(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I12(p0);
}


void _IC13(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I13(p0);
}


void _IC14(const CallerData* pCD)
{
_I14();
}


void _IC15(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
int p0;
memcpy(&p0, pArg, sizeof(int));
_I15(p0);
}


void _IC16(const CallerData* pCD)
{
_I16();
}


void _IC17(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I17(p0);
}


void _IC18(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I18(p0);
}


void _IC19(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I19(p0);
}


void _IC20(const CallerData* pCD)
{
_I20();
}


void _IC21(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I21(p0);
}


void _IC22(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I22(p0);
}


void _IC23(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I23(p0);
}


void _IC24(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I24(p0);
}


void _IC25(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
float p0;
memcpy(&p0, pArg, sizeof(float));
_I25(p0);
}


void _IC26(const CallerData* pCD)
{
_I26();
}

static const ProductionPrototype proto[] =
{
	{
		{
			{ 0 }, 0
		},
		{
			{ A_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC1
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ X_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC2
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Q_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC3
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ E_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC4
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ B_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC5
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfB_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC6
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfK_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC7
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfP_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC8
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfF_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC9
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ L_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC10
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfL_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC11
	}
};
static const ProductionPrototype iproto[] =
{
	{
		{
			{ 0 }, 0
		},
		{
			{ Slash_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC12
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ F_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC13
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Excl_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC14
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SemiColon_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC15
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ AtV_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC16
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Minus_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC17
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Plus_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC18
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfB_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC19
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Percent_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC20
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfK_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC21
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Hat_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC22
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfP_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC23
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfF_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC24
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ SurfL_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC25
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ Hash_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC26
	}
};
static const ModuleData moduleData[] =
{
{ "SB",  0 },
{ "EB",  0 },
{ "E",  0 },
{ "Slash", sizeof(float)},
{ "Amp", sizeof(float)},
{ "A", sizeof(int)},
{ "F", sizeof(float)},
{ "X", sizeof(int)},
{ "L",  0 },
{ "Excl",  0 },
{ "SemiColon", sizeof(int)},
{ "Q",  0 },
{ "B", sizeof(int)},
{ "AtV",  0 },
{ "Minus", sizeof(float)},
{ "Plus", sizeof(float)},
{ "SurfB", sizeof(float)},
{ "Percent",  0 },
{ "SurfK", sizeof(float)},
{ "Hat", sizeof(float)},
{ "SurfP", sizeof(float)},
{ "SurfF", sizeof(float)},
{ "SurfL", sizeof(float)},
{ "Hash",  0 }
};


const ModuleData* GetModuleData(int i)
{ return &(moduleData[i]); }


int NumOfModules()
{ return 24; }
void StartEach() {}
void EndEach() {}
void End() {}

int NumOfProductions()
{ return sizeof(proto)/sizeof(proto[0]); }
const ProductionPrototype& GetProductionPrototype(int i)
{ return proto[i]; }

int NumOfIProductions()
{ return sizeof(iproto)/sizeof(iproto[0]); }
const ProductionPrototype& GetIProductionPrototype(int i)
{ return iproto[i]; }
int NumOfConsidered() { return 0; }
ModuleIdType GetConsidered(int) { return -1; }
int NumOfIgnored() { return 0; }
ModuleIdType GetIgnored(int) { return -1; }
