/* A Bison parser, made from l2c.y, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON	1

/* Pure parsers.  */
#define YYPURE	0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse lparse
#define yylex   llex
#define yyerror lerror
#define yylval  llval
#define yychar  lchar
#define yydebug ldebug
#define yynerrs lnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tOPEN = 258,
     tCLOSE = 259,
     tMODULE = 260,
     tPRODUCE = 261,
     tSTART = 262,
     tSTARTEACH = 263,
     tENDEACH = 264,
     tEND = 265,
     tCONSIDER = 266,
     tIGNORE = 267,
     tDERIVLENGTH = 268,
     tINTERPRETATION = 269,
     tLPAREN = 270,
     tRPAREN = 271,
     tSEMICOLON = 272,
     tCOMMA = 273,
     tLESSTHAN = 274,
     tGREATERTHAN = 275,
     tENDPRODPROTO = 276,
     tIDENT = 277,
     tMODULEIDENT = 278,
     tERROR = 279
   };
#endif
#define tOPEN 258
#define tCLOSE 259
#define tMODULE 260
#define tPRODUCE 261
#define tSTART 262
#define tSTARTEACH 263
#define tENDEACH 264
#define tEND 265
#define tCONSIDER 266
#define tIGNORE 267
#define tDERIVLENGTH 268
#define tINTERPRETATION 269
#define tLPAREN 270
#define tRPAREN 271
#define tSEMICOLON 272
#define tCOMMA 273
#define tLESSTHAN 274
#define tGREATERTHAN 275
#define tENDPRODPROTO 276
#define tIDENT 277
#define tMODULEIDENT 278
#define tERROR 279




/* Copy the first part of user declarations.  */
#line 1 "l2c.y"


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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#ifndef YYSTYPE
#line 53 "l2c.y"
typedef union {
  char Ident[eMaxIdentifierLength+1];
  int ModuleId;
  ParametersList ParamsList;
  FormalModuleDt* pFormalModuleData;
  FormalModuleDtList* pFormalModuleDataList;
} yystype;
/* Line 193 of /usr/share/bison/yacc.c.  */
#line 189 "l2c.tab.c"
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLTYPE
typedef struct yyltype
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;
# define YYLTYPE yyltype
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */


/* Line 213 of /usr/share/bison/yacc.c.  */
#line 210 "l2c.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];	\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
#define YYLAST   67

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  29
/* YYNRULES -- Number of rules. */
#define YYNRULES  52
/* YYNRULES -- Number of states. */
#define YYNSTATES  80

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    37,    41,
      48,    49,    54,    55,    60,    62,    65,    66,    70,    77,
      82,    87,    90,    92,    94,    96,    99,   101,   106,   107,
     112,   115,   116,   117,   118,   119,   127,   129,   130,   134,
     135,   139,   141
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      26,     0,    -1,    26,    27,    -1,    -1,    28,    -1,    30,
      -1,    31,    -1,    33,    -1,    38,    -1,    44,    -1,    36,
      -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,    14,
      -1,    29,    -1,     3,    22,    17,    -1,     4,    22,    17,
      -1,     5,    22,    15,    53,    16,    17,    -1,    -1,    11,
      32,    35,    17,    -1,    -1,    12,    34,    35,    17,    -1,
      23,    -1,    35,    23,    -1,    -1,    13,    37,    17,    -1,
      39,    19,    41,    20,    40,    21,    -1,    39,    19,    41,
      21,    -1,    41,    20,    40,    21,    -1,    41,    21,    -1,
      42,    -1,    42,    -1,    42,    -1,    42,    43,    -1,    43,
      -1,    23,    15,    53,    16,    -1,    -1,     6,    45,    46,
      17,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,    23,
      48,    15,    49,    51,    50,    16,    -1,    23,    -1,    -1,
      51,    52,    18,    -1,    -1,    53,    18,    22,    -1,    22,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    74,    74,    75,    78,    80,    81,    82,    83,    84,
      85,    86,    88,    90,    92,    94,    96,    99,   104,   109,
     117,   117,   121,   121,   126,   128,   132,   132,   136,   142,
     148,   154,   165,   169,   173,   177,   179,   183,   187,   187,
     192,   193,   197,   197,   197,   197,   199,   203,   203,   204,
     207,   215,   220
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tOPEN", "tCLOSE", "tMODULE", "tPRODUCE", 
  "tSTART", "tSTARTEACH", "tENDEACH", "tEND", "tCONSIDER", "tIGNORE", 
  "tDERIVLENGTH", "tINTERPRETATION", "tLPAREN", "tRPAREN", "tSEMICOLON", 
  "tCOMMA", "tLESSTHAN", "tGREATERTHAN", "tENDPRODPROTO", "tIDENT", 
  "tMODULEIDENT", "tERROR", "$accept", "Translate", "TranslationUnit", 
  "OpenNamespace", "CloseNamespace", "ModuleDeclaration", 
  "ConsiderStatement", "@1", "IgnoreStatement", "@2", "ModuleList", 
  "DerivLength", "@3", "ProductionPrototype", "LContext", "RContext", 
  "StrictPred", "FormalModules", "FormalModule", "ProduceStatement", "@4", 
  "ParametricWord", "ParametricLetter", "@5", "@6", "@7", 
  "CallParameters", "@8", "Parameters", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    25,    26,    26,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    28,    29,    30,
      32,    31,    34,    33,    35,    35,    37,    36,    38,    38,
      38,    38,    39,    40,    41,    42,    42,    43,    45,    44,
      46,    46,    48,    49,    50,    47,    47,    52,    51,    51,
      53,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     6,
       0,     4,     0,     4,     1,     2,     0,     3,     6,     4,
       4,     2,     1,     1,     1,     2,     1,     4,     0,     4,
       2,     0,     0,     0,     0,     7,     1,     0,     3,     0,
       3,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     1,     0,     0,     0,    38,    11,    12,    13,
      14,    20,    22,    26,    15,     0,     2,     4,    16,     5,
       6,     7,    10,     8,     0,     0,    34,    36,     9,     0,
       0,     0,    41,     0,     0,     0,    52,     0,     0,    31,
      35,    17,    18,    52,     0,    24,     0,     0,    27,    51,
       0,     0,    34,     0,    33,     0,    39,    46,    40,    21,
      25,    23,    37,     0,     0,    29,    30,     0,     0,    50,
       0,    19,    43,    28,    49,    44,     0,     0,    45,    48
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,    16,    17,    18,    19,    20,    33,    21,    34,
      46,    22,    35,    23,    24,    53,    25,    54,    27,    28,
      32,    44,    58,    68,    74,    76,    75,    77,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -26
static const yysigned_char yypact[] =
{
     -26,     2,   -26,    -3,     8,    12,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,     6,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,    21,   -17,     9,   -26,   -26,     5,
      24,    27,   -26,    20,    20,    28,    22,    23,    23,   -26,
     -26,   -26,   -26,    22,     0,   -26,     1,     3,   -26,   -26,
      15,    18,    23,    26,    23,    19,   -26,    33,   -26,   -26,
     -26,   -26,   -26,    29,    23,   -26,   -26,    32,    35,   -26,
      31,   -26,   -26,   -26,   -26,    36,    37,    38,   -26,   -26
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
      25,   -26,   -26,   -26,   -26,    -9,    30,    -1,   -25,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,    14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, parse error.  */
#define YYTABLE_NINF -48
static const yysigned_char yytable[] =
{
      26,    40,     2,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    56,    59,    29,
      61,    36,    41,    57,    60,    15,    60,    40,   -32,    40,
      30,    62,    15,    63,    31,    67,    52,    63,    64,    65,
      37,    42,    43,    45,    49,    48,    15,    66,   -42,    71,
      72,    69,    73,    78,   -47,    70,    79,    55,     0,    47,
       0,     0,     0,     0,     0,     0,     0,    51
};

static const yysigned_char yycheck[] =
{
       1,    26,     0,    20,    21,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    17,    17,    22,
      17,    15,    17,    23,    23,    23,    23,    52,    19,    54,
      22,    16,    23,    18,    22,    16,    37,    18,    20,    21,
      19,    17,    15,    23,    22,    17,    23,    21,    15,    17,
      15,    22,    21,    16,    18,    64,    18,    43,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    26,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    23,    27,    28,    29,    30,
      31,    33,    36,    38,    39,    41,    42,    43,    44,    22,
      22,    22,    45,    32,    34,    37,    15,    19,    20,    21,
      43,    17,    17,    15,    46,    23,    35,    35,    17,    22,
      53,    41,    42,    40,    42,    53,    17,    23,    47,    17,
      23,    17,    16,    18,    20,    21,    21,    16,    48,    22,
      40,    17,    15,    21,    49,    51,    50,    52,    16,    18
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)           \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#define YYLEX	yylex ()

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*-----------------------------.
| Print this symbol on YYOUT.  |
`-----------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yysymprint (FILE* yyout, int yytype, YYSTYPE yyvalue)
#else
yysymprint (yyout, yytype, yyvalue)
    FILE* yyout;
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyout, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyout, yytoknum[yytype], yyvalue);
# endif
    }
  else
    YYFPRINTF (yyout, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyout, ")");
}
#endif /* YYDEBUG. */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yydestruct (int yytype, YYSTYPE yyvalue)
#else
yydestruct (yytype, yyvalue)
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  switch (yytype)
    {
      default:
        break;
    }
}



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of parse errors so far.  */
int yynerrs;


int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with.  */

  if (yychar <= 0)		/* This means end of input.  */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more.  */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

      /* We have to keep this `#if YYDEBUG', since we use variables
	 which are defined only if `YYDEBUG' is set.  */
      YYDPRINTF ((stderr, "Next token is "));
      YYDSYMPRINT ((stderr, yychar1, yylval));
      YYDPRINTF ((stderr, "\n"));
    }

  /* If the proper action on seeing token YYCHAR1 is to reduce or to
     detect an error, take that action.  */
  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];



#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn - 1, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] >= 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif
  switch (yyn)
    {
        case 11:
#line 87 "l2c.y"
    { ExpandStart(); }
    break;

  case 12:
#line 89 "l2c.y"
    { ExpandStartEach(); }
    break;

  case 13:
#line 91 "l2c.y"
    { ExpandEndEach(); }
    break;

  case 14:
#line 93 "l2c.y"
    { ExpandEnd(); }
    break;

  case 15:
#line 95 "l2c.y"
    { SwitchToInterpretation(); }
    break;

  case 17:
#line 100 "l2c.y"
    {
          GenerateOpenNamespace(yyvsp[-1].Ident);
        }
    break;

  case 18:
#line 105 "l2c.y"
    {
          namespace_close = true;
        }
    break;

  case 19:
#line 110 "l2c.y"
    { 
		ModuleDeclaration mdecl(yyvsp[-4].Ident, &(yyvsp[-2].ParamsList), counter++);
		mdecl.GenerateModId();
		moduleTable.Add(mdecl); 
	}
    break;

  case 20:
#line 117 "l2c.y"
    { StartConsider(); }
    break;

  case 21:
#line 118 "l2c.y"
    { EndConsider(); }
    break;

  case 22:
#line 121 "l2c.y"
    { StartIgnore(); }
    break;

  case 23:
#line 122 "l2c.y"
    { EndIgnore(); }
    break;

  case 24:
#line 127 "l2c.y"
    { AppendConIgnModule(yyvsp[0].Ident); }
    break;

  case 25:
#line 129 "l2c.y"
    { AppendConIgnModule(yyvsp[0].Ident); }
    break;

  case 26:
#line 132 "l2c.y"
    { StartDerivLength(); }
    break;

  case 27:
#line 133 "l2c.y"
    { EndDerivLength(); }
    break;

  case 28:
#line 137 "l2c.y"
    { 
		ProductionProto* pNew = new ProductionProto(yyvsp[-5].pFormalModuleDataList, yyvsp[-3].pFormalModuleDataList, yyvsp[-1].pFormalModuleDataList); 
		pNew->Generate();
		productionTable.Add(pNew);
	}
    break;

  case 29:
#line 143 "l2c.y"
    { 
		ProductionProto* pNew = new ProductionProto(yyvsp[-3].pFormalModuleDataList, yyvsp[-1].pFormalModuleDataList, NULL);
		pNew->Generate();
		productionTable.Add(pNew);
	}
    break;

  case 30:
#line 149 "l2c.y"
    { 
		ProductionProto* pNew = new ProductionProto(NULL, yyvsp[-3].pFormalModuleDataList, yyvsp[-1].pFormalModuleDataList); 
		pNew->Generate();
		productionTable.Add(pNew);
	}
    break;

  case 31:
#line 155 "l2c.y"
    { 
		ProductionProto* pNew = new ProductionProto(NULL, yyvsp[-1].pFormalModuleDataList, NULL); 
		pNew->Generate();
		if (eInterpretation == ProductionMode())
			interpretationTable.Add(pNew);
		else
			productionTable.Add(pNew);
	}
    break;

  case 32:
#line 166 "l2c.y"
    { yyval.pFormalModuleDataList = yyvsp[0].pFormalModuleDataList; }
    break;

  case 33:
#line 170 "l2c.y"
    { yyval.pFormalModuleDataList = yyvsp[0].pFormalModuleDataList; }
    break;

  case 34:
#line 174 "l2c.y"
    { yyval.pFormalModuleDataList = yyvsp[0].pFormalModuleDataList; }
    break;

  case 35:
#line 178 "l2c.y"
    { yyval.pFormalModuleDataList = yyvsp[-1].pFormalModuleDataList; yyval.pFormalModuleDataList->Add(yyvsp[0].pFormalModuleData); }
    break;

  case 36:
#line 180 "l2c.y"
    { yyval.pFormalModuleDataList = new FormalModuleDtList(yyvsp[0].pFormalModuleData); }
    break;

  case 37:
#line 184 "l2c.y"
    { yyval.pFormalModuleData = new FormalModuleDt(yyvsp[-3].Ident, &(yyvsp[-1].ParamsList)); }
    break;

  case 38:
#line 187 "l2c.y"
    { StartProduce(); }
    break;

  case 39:
#line 188 "l2c.y"
    { EndProduce(); }
    break;

  case 42:
#line 197 "l2c.y"
    { StartGenerateProduce(yyvsp[0].Ident); }
    break;

  case 43:
#line 197 "l2c.y"
    { ParameterCast(); }
    break;

  case 44:
#line 197 "l2c.y"
    { EndParameterCast(); }
    break;

  case 45:
#line 198 "l2c.y"
    { EndGenerateProduce(); }
    break;

  case 46:
#line 200 "l2c.y"
    { StartGenerateProduce(yyvsp[0].Ident); EndGenerateProduce(); }
    break;

  case 47:
#line 203 "l2c.y"
    { EndParameterCast(); }
    break;

  case 48:
#line 203 "l2c.y"
    { ParameterCast(); }
    break;

  case 50:
#line 208 "l2c.y"
    {
	  if (yyvsp[-2].ParamsList.count == eMaxParams)
	    lerror("Too many parameters");
	  strcpy(yyvsp[-2].ParamsList.Params[yyvsp[-2].ParamsList.count], yyvsp[0].Ident);
	  yyvsp[-2].ParamsList.count++;
	  yyval.ParamsList = yyvsp[-2].ParamsList;
	}
    break;

  case 51:
#line 216 "l2c.y"
    {
	  strcpy(yyval.ParamsList.Params[0], yyvsp[0].Ident);
	  yyval.ParamsList.count = 1;
	}
    break;

  case 52:
#line 221 "l2c.y"
    { yyval.ParamsList.count = 0; }
    break;


    }

/* Line 1016 of /usr/share/bison/yacc.c.  */
#line 1320 "l2c.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyssp > yyss)
	    {
	      YYDPRINTF ((stderr, "Error: popping "));
	      YYDSYMPRINT ((stderr,
			    yystos[*yyssp],
			    *yyvsp));
	      YYDPRINTF ((stderr, "\n"));
	      yydestruct (yystos[*yyssp], *yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yydestruct (yychar1, yylval);
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDPRINTF ((stderr, "Error: popping "));
      YYDSYMPRINT ((stderr,
		    yystos[*yyssp], *yyvsp));
      YYDPRINTF ((stderr, "\n"));

      yydestruct (yystos[yystate], *yyvsp);
      yyvsp--;
      yystate = *--yyssp;


#if YYDEBUG
      if (yydebug)
	{
	  short *yyssp1 = yyss - 1;
	  YYFPRINTF (stderr, "Error: state stack now");
	  while (yyssp1 != yyssp)
	    YYFPRINTF (stderr, " %d", *++yyssp1);
	  YYFPRINTF (stderr, "\n");
	}
#endif
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 225 "l2c.y"


