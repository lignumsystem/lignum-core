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

#ifndef BISON_L_C_TAB_H
# define BISON_L_C_TAB_H

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




#ifndef YYSTYPE
#line 53 "l2c.y"
typedef union {
  char Ident[eMaxIdentifierLength+1];
  int ModuleId;
  ParametersList ParamsList;
  FormalModuleDt* pFormalModuleData;
  FormalModuleDtList* pFormalModuleDataList;
} yystype;
/* Line 1281 of /usr/share/bison/yacc.c.  */
#line 96 "l2c.tab.h"
# define YYSTYPE yystype
#endif

extern YYSTYPE llval;


#endif /* not BISON_L_C_TAB_H */

