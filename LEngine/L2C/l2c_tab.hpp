/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

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
/* Tokens.  */
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE

{
  char Ident[eMaxIdentifierLength+1];
  int ModuleId;
  ParametersList ParamsList;
  FormalModuleDt* pFormalModuleData;
  FormalModuleDtList* pFormalModuleDataList;
}
/* Line 1529 of yacc.c.  */

	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE llval;

