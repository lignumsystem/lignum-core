typedef union
{
  char Ident[eMaxIdentifierLength+1];
  int ModuleId;
  ParametersList ParamsList;
  FormalModuleDt* pFormalModuleData;
  FormalModuleDtList* pFormalModuleDataList;
} YYSTYPE;
#define	tOPEN	257
#define	tCLOSE	258
#define	tMODULE	259
#define	tPRODUCE	260
#define	tSTART	261
#define	tSTARTEACH	262
#define	tENDEACH	263
#define	tEND	264
#define	tCONSIDER	265
#define	tIGNORE	266
#define	tDERIVLENGTH	267
#define	tINTERPRETATION	268
#define	tLPAREN	269
#define	tRPAREN	270
#define	tSEMICOLON	271
#define	tCOMMA	272
#define	tLESSTHAN	273
#define	tGREATERTHAN	274
#define	tENDPRODPROTO	275
#define	tIDENT	276
#define	tMODULEIDENT	277
#define	tERROR	278


extern YYSTYPE llval;
